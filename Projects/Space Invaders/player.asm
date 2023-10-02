;---------------------------------------------------------------;
;                                                               ;
;  PLAYER.ASM                                                   ;
;                                                               ;
;  This file contains functions to control the player(s)        ;
;                                                               ;
;---------------------------------------------------------------;

BE_State MACRO state
    ld a, state
    ld (BulletExplodeF), a
ENDM


MIN_X           equ       8
MAX_X           equ     232
PLAYER_Y        equ     168                 ; the y position of the player ship
BULLET_SPEED    equ       4
PLAYER_CENTER   equ     120
EXPLODE_TIME    equ      10

BE_NONE         equ       0                 ; do nothing
BE_DRAW         equ       1                 ; draw the bullet explosion
BE_WAIT         equ       2                 ; wait for explosion to finish 
BE_ERASE        equ       4                 ; erase the bullet explosion

PlayerX:        defb PLAYER_CENTER          ; the position of the player ship
PlayerXOld:     defb PLAYER_CENTER          ; the old position of the player ship
PlayerBulletX:  defb      0                 ; the current X position of the player Bullet
PlayerBulletY:  defb      0                 ; the current Y position of the player Bullet (bottom of Bullet) - 0 - means not active
PlayerBulletS:  defw      0                 ; Bullet speed counter
BulletFlags:    defb      0                 ; bit 0: collision
BulletCollX:    defb      0                 ; the X position of a collision
BulletCollY :   defb      0                 ; the Y position of a collision       
PlayerEnabled:  defb      0
BulletExplodeX: defb      0                 ; the x position of the bullet explosion
BulletExplodeY: defb      0                 ; the y position of the bullet explosion
BulletExplodeT: defw      0                 ; the time(frames) the bullet explosion stays on screen
BulletExplodeF: defb BE_NONE                ; bullet explosion flag

ResetPlayerWave:ld a, PLAYER_CENTER
                ld (PlayerX), a
                ld (PlayerXOld), a
                xor a
                ld (PlayerBulletX), a
                ld (PlayerBulletY), a
                ld (PlayerBulletS), a
                ld (BulletFlags), a
                ld (BulletCollX), a
                ld (BulletCollY), a
                ld (BulletExplodeF), a
                ret 

EnablePlayer:   ld a, 1
                ld (PlayerEnabled), a
                ret    
DisablePlayer:  xor a
                ld (PlayerEnabled), a
                ret    


MovePlayer:     ld a, (PlayerEnabled)
                and a
                ret z
                call ReadKeys
                ld b, a
                and ACTION_LEFT
                call nz, PlayerLeft
                ld a, b
                and ACTION_RIGHT
                call nz, PlayerRight
                ld a, b
                and ACTION_FIRE
                call nz, PlayerFire
                ret
                
MovePBullet:    ld a, (PlayerBulletY)       ; get the Bullet y position
                and a                       ; is it zero?
                ret z                       ; if so, nothing to do
                ld hl, (PlayerBulletS)      ; get the current frame count (speed of movement)
                ld bc, (ISRCounter)
                sbc hl, bc
                ret z                       ; is bc is equal to hl?, no? continue
                ld h, b
                ld l, c
                ld (PlayerBulletS), hl      
                ld a, (PlayerBulletY)       ; get the Bullet y position
                push af
                call ErasePBullet           ; erase the old Bullet
                pop af
                sub BULLET_SPEED
                push af
                call DrawPBullet            ; draw the new Bullet
                pop af                      
                ld (PlayerBulletY), a       ; store the new position
                cp 32                       ; is the Bullet at the top of the screen?
                jr nc, CheckForCollision    ; if not then check for collision
                ; show explosion at top of screen
                BE_State BE_DRAW
                ld bc, EXPLODE_TIME
                ld hl, (ISRCounter)
                add hl, bc
                ld (BulletExplodeT), hl
                ld a, (PlayerBulletX)
                sub 4
                ld (BulletExplodeX), a
                ld a, 24
                ld (BulletExplodeY), a
                
ResetBullet:    call ErasePBullet           ; erase the Bullet
                xor a
                ld (PlayerBulletY), a       ; reset the Bullet y position ready for another firing
                ld a, (BulletExplodeY)
                ret
                
CheckForCollision: ; call ShowCollision
                ld a, (BulletFlags)         ; get bullet flags
                and a                       ; test for zero
                ret z                       ; if zero, done for now
                xor a
                ld (BulletFlags), a
                ld a, (BulletCollY)         ; get bullet collision y position
                ld d, a                     ; put y collision into d
                ; check for mothership collision
                ld a, MOTHERSHIP_Y
                add a, 9
                cp d
                jp nc, HitMothership
                ; test for alien row collision
                call GetAlienBottomRow
                cp d                        ; compare to coll y
                jr c, NotAnAlien            ; if coll y > alien max y then not an alien; must be a base or missile
                ld a, (AliensY)             ; get top of alien waves
                cp d                        ; compare to coll x                       
                jr nc, NotAnAlien           ; if colly < alien min y then not an alien; must be mothership
                ; work out which alien it is
                ld b, a                     ; b = aliens y
                ld a, d                     ; a = coll y
                sub b                       ; a = coll y - aliens y
                srl a                       ; 
                srl a                       ; 
                srl a                       ; 
                srl a                       ; a = (coll y - aliens y) / 16
                ld b, a                     ; d = alien row
                ld a, (AliensX)
                ld c, a                     ; c = aliens x
                ld a, (BulletCollX)         ; a = coll x
                sub c                       ; a = coll x - 1 - aliens x
                srl a                       ; 
                srl a                       ; 
                srl a                       ; 
                srl a                       ; a = (coll x - aliens x) / 16
                ld c, a                     ; e = column
                call ShootAlien
                ret nc
                ld a, (PlayerBulletY)
                call ResetBullet
                ld a, ALIEN_HIT_SFX
                call playsfx
                ret
                
NotAnAlien:     ; check for base collision
                ld a, BASE_TOP
                cp d
                jr nc, HitAlienBullet
                ; hit base - erase part of base
                ld a, (BulletCollX)
                sub 4
                ld c, a
                ld a, (BulletCollY)         ; get bullet collision y position
                sub 6                       ; move it up the screen a little bit    
                ld b, a
                call Pix                    ; hl = screen address
                ld de, BaseMask + 2         ; de = explosion mask data
                ld b, 8                     ; need to erase 8 lines             
                and a                       ; do we need to rotation the mask into position?
                jr z, EraseBase             ; no, erase base without rotation
                ; yes, erase base - rotating mask into position
EraseBaseRotate:push bc                     ; save the loop counter (b)
                push af                     ; save the rotations needed
                ld b, a                     ; put rotation count in b             
                ld a, (de)                  ; get mask
                ld c, 0xFF                  ; set c as mask to rotate into
ESR1:           scf                         ; set carry as a mask bit to rotate into. carry => a => c
                rra
                rr c
                djnz ESR1
                ld b, a
                ; mask is in b and c
                ld a, (hl)                 
                and b
                ld (hl), a
                inc hl
                ld a, (hl)
                and c
                ld (hl), a
                dec hl
                call Incy
                inc de
                pop af
                pop bc
                djnz EraseBaseRotate
                ld a, (PlayerBulletY)
                call ResetBullet
                ret 
                ; draw the base with no rotation needed
EraseBase:      ld b, 8
DBE1:           ld a, (de)                  ; get explosion mask
                and (hl)                    ; remove pixels from screen
                ld (hl), a                  ; store result on screen
                call Incy
                inc de
                djnz DBE1
                ld a, (PlayerBulletY)
                call ResetBullet
                ret                                          
HitAlienBullet: ret

ShowCollision:  push af
                push bc
                push de
                push hl
                ld a, (BulletCollY)
                ld b, a
                ld a, (BulletCollX)
                ld c, a
                call Pix
                ld (hl), 255
                call Attr
                ld (hl), PAP_RED | INK_WHT
                pop hl
                pop de
                pop bc
                pop af
                ret

HitMothership:  ld a, MOTHERSHIP_HIT_SFX
                call playsfx
                call ResetBullet
                ld a, (MotherX)
                ld b, a
                ld a, (BulletCollX)
                sub b
                cp 4
                jr c, HMS20
                cp 7
                jr c, HMS50
                cp 9
                jr c, HMS100
                cp 12
                jr c, HMS50
HMS20:          ld a, 5
                call IncScore
                xor a
                call KillMothership                
                ret                
HMS50:          ld a, 6
                call IncScore
                ld a, 1
                call KillMothership                
                ret                
HMS100:         ld a, 7
                call IncScore
                ld a, 2
                call KillMothership
                ret                
               
PlayerLeft:     ld a, (PlayerX)
                cp MIN_X
                ret c
                dec a
                dec a
                ld (PlayerX), a
                ret
                                 

PlayerRight:    ld a, (PlayerX)
                cp MAX_X
                ret nc
                inc a
                inc a
                ld (PlayerX), a
                ret
 
;
; DrawPlayer
; Only redraws the player if it has moved
;
DrawPlayer:     ld a, (PlayerXOld)          ; get the previous x position
                ld b, a                     ; put it into b
                ld a, (PlayerX)             ; get the current x position
                cp b                        ; compare previous to current
                ret z                       ; return if they are the same                   
                ld hl, PlayerX              ; point hl to the player x position
                call DrawPlayerShip         ; draw the player ship
                ld a, (PlayerX)             ; put the current position
                ld (PlayerXOld), a          ; into the previously drawn position
                ret

DrawPlayerShip: ld b, PLAYER_Y              ; get the Y position
                ld c, (hl)                  ; get the x position
                ld hl, Player               ; pointer hl to player sprite data
                call SetErase               ; set edge erase on
                call DrwSpr16               ; draw the player sprite
                ret
 
;
; Draw the bullet and test for collisions as we go
; a - y position of the Bullet
;
DrawPBullet:    ld b, a                     ; put the y position into b
                ld a, (PlayerBulletX)       ; get the x position 
                ld c, a                     ; put into c
                call Pix                    ; get the screen address of the bullet
                ld b, a                     ; put the pixel position (rotations) into b
                ld a, 128                   ; set the last bit
DPB1:           rr a                        ; move it 
                djnz DPB1                   ; into position                   
                ld d, a                     ; save the byte value of the pixel in d 
                ld b, 5                     ; draw 5 of them
DPB2:           ld a, (hl)                  ; get the screen contents
                ld e, a                     ; save the screen contents in e
                and d                       ; test if the bullet pixel already set?           
                call nz, BulletCollision    ; if set, then a collision has occurred 
                ld a, e                     ; get the screen contents
                or d                        ; set the bullet pixel
                ld (hl), a                  ; put the result on screen
                call Decy                   ; go up a pixel
                djnz DPB2                   ; draw all the pixels
                ret

;
; Erase the player bullet
; 
; a - y position of the Bullet
;
ErasePBullet:   ld b, a                     ; put the y position into b
                ld a, (PlayerBulletX)       ; get the x position 
                ld c, a                     ; put into c
                call Pix                    ; get the screen address of the bullet
                ld b, a                     ; put the pixel position (rotations) into b
                ld a, 128                   ; set the last bit
EPM1:           rr a                        ; move it 
                djnz EPM1                   ; into position
                cpl                   
                ld d, a                     ; save the byte value of the pixel in d 
                ld b, 5                     ; draw 5 of them
EPM2:           ld a, (hl)                  ; get the screen contents
                and d                       ; reset the bullet pixel
                ld (hl), a                  ; put the result on screen
                call Decy                   ; go up a pixel
                djnz EPM2                   ; draw all the pixels
                ret


                
BulletCollision:ld a, (BulletFlags)         ; get the bullet flags
                and a                       ; has a collision already been detected?
                ret nz                      ; if yes, finished
                ld a, 1                     ; set the collision flag
                ld (BulletFlags), a         ; save to the flags
                ld a, (PlayerBulletX)       ; get the bullet x position
                ld c, a
                ld (BulletCollX), a         ; store bullet x collision positon 
                ld a, (PlayerBulletY)       ; get the bullet y position
                sub b                       ; move to top
                ld (BulletCollY), a         ; store bullet y collision position
                ret
 
SwapPlayers:    ret
 

PlayerFire:     ld a, (AlienFlags)          ; get the alien flags
                and AF_KILL | AF_ERASE      ; are killing an alien
                ret nz                      ; yes, then wait until its dead
                ld a, (PlayerBulletY)       ; get the current bullet y position
                and a                       ; is it zero?
                ret nz                      ; if not, then wait for bullet to hit something or go off the screen
                ld hl, (ISRCounter)         ; get the current ISR counter
                ld (PlayerBulletS), hl      ; save the move time      
                ld a, (PlayerX)             ; get the player x position
                add a, 7                    ; adjust for Bullet position     
                ld (PlayerBulletX), a       ; set as player Bullet x position 
                ld a, PLAYER_Y - 1          ; get the player y position - 1 pixel
                ld (PlayerBulletY), a       ; set a Bullet y position
                call DrawPBullet            ; draw the Bullet
                ld a, FIRE_SFX
                call playsfx                
                ret 
 
 

;
; b - alien row
; c - alien column
;
ShootAlien:     ld a, b                     ; get the row
                and 7                       ;                        
                cp 5                        ; is it < 5
                ret nc                      ; no then finished
                ld (AlienEraseY), a         ; set the alien erase row
                ld a, c                     ; get the column
                and 15                      ; 
                cp 12                       ; is it < 12
                ret nc                      ; no then finished
                ld (AlienEraseX), a         ; set the alien erase column
                ld hl, (MarchCountWave)     ; get alien wave speed
                ld de, 10                   ; decrease by 10
                sbc hl, de                  ; reduce the alien wave speed
                jr z, SA2                   ; if = 0, no update
                jr nc, SA1                  ; if > 0, update speed
                jr SA2                      ; we are going as fast as we can                
SA1:            ld (MarchCountWave), hl     ; speed up the aliens                
                ; make a masking bit for the alien to remove
SA2:            ld de, 0                    ; reset mask bits 
                inc a                       ; increase bit count by 1
                ; move the bit into position for reset
                ld b, a                     ; b = bit count
                scf                         ; set carry - most MSB
SA3:            rl d                        ; move bit into e and d
                rl e 
                djnz SA3                    ; rotate bit into position
                ; 1's compliment the masking bit
                ld a, d                     ; invert the mask bits
                cpl
                ld d, a                     ; e mask inverted
                ld a, e
                cpl
                ld e, a                     ; d mask inverted
                ; remove the bit from the alien wave row                                
                ld hl, ALIEN_WAVE           ; point to current alien wave
                ld a, (AlienEraseY)         ; a = alien erase y                                         
                and a                       ; is it zero?
SA4:            jr z, SA5                   ; yes, found correct row
                inc hl                      ; move to next row                      
                inc hl
                dec a                       ; decrease row
                jr SA4                      ; repeat
                ; mask the alien from the row
SA5:            ld a, (hl)                  ; get 1st row byte
                ld b, a                     ; b = 1st row byte
                and d                       ; mask 1st row byte with e
                ld (hl), a                  ; save masked result
                xor b                       ; remove 1st row byte from result (mask result only) 
                ld b, a                     ; save result in b    
                inc hl                      ; move to 2nd row byte
                ld a, (hl)                  ; a = 2nd row byte
                ld c, a                     ; c = 2nd row byte
                and e                       ; mask 2nd row byte with d
                ld (hl), a                  ; save masked result
                xor c                       ; remove 2nd row byte                       
                xor b                       ; merge with 1st row byte result (0 or bit set)
                and a                       ; if zero, then alien is already gone
                ret z                       ; if zero, then done for now
                ld a, (AlienEraseY)         ; get the alien row hit
                call IncScore               ; score it
                ld a, (AlienFlags)          ; get the alien flags
                or AF_KILL                  ; mark as killed
                ld (AlienFlags), a          ; save the flags                
                ld a, (WaveDirection)       ; get the direction
                ld (AlienEraseD), a         ; set erase sprite direction
                ld a, (AliensY)             ; get the alien row
                ld (AlienEraseYY), a        ; set the row for erase
                ld a, (AliensX)             ; get the alien column
                ld (AlienEraseXX), a        ; set the column for erase
                scf                         ; set alien hit
                ret

BulletExplosion:ld a, (BulletExplodeF)
                and a
                ret z
                cp BE_DRAW
                jr z, DBE_Draw
                cp BE_ERASE
                jr z, DBE_Erase
                ; bullet explosion wait state
                ld hl, (BulletExplodeT)
                ld bc, (ISRCounter)
                sbc hl, bc
                ret nc
                BE_State BE_ERASE
                ret
                
DBE_Draw:       ld a, BULLET_HIT_SFX
                call playsfx
                BE_State BE_WAIT
                ld bc, EXPLODE_TIME  
                ld hl, (ISRCounter)
                add hl, bc
                ld hl, PlayerBulletExplosion
                ld bc, (BulletExplodeX)
                call DrwSpr8
                ret
                
DBE_Erase:      BE_State BE_NONE
                ld hl, PlayerBulletExplosion
                ld bc, (BulletExplodeX)
                call ErzSpr8
                ret
                                      