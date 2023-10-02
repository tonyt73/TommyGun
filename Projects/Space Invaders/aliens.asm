;---------------------------------------------------------------;
;                                                               ;
;  ALIENS.ASM                                                   ;
;                                                               ;
;  This file contains functions to control the alien wave       ;
;                                                               ;
;---------------------------------------------------------------;

ALIEN_ROWS          equ         5   ; should be between 3 and 7
ALIEN_COLS          equ        11   ; must be between 9 and 14
ALIEN_ROW_MASK      equ      0x07   ; the bits on the end that don't represent aliens (12 = 4 unused bits, 13 = 0x1F, 14 = 0x3F, 11 = 0x07 etc)
ALIEN_DOWN          equ         4   ; the number of pixels to move the rows down
ALIEN_ROW_HEIGHT    equ        16   ; the gap between the top of each alien
KILL_WAIT           equ        25   ; the number of frames to wait while showing the explosion sprite  

AF_DRAW             equ         1   ; draw the aliens
AF_CLEAR            equ         2   ; clear the row above the aliens
AF_KILL             equ         4   ; kill an alien
AF_ERASE            equ         8   ; erase the alien explosion

;---------------------------------------------------------------;
; VARIABLES                                                     ;
;---------------------------------------------------------------;

;
; Table of Aliens (the wave of invaders) 
;
; Each bit represents if an alien is present of not.
; This is handy because it means we can find out where the lowest
; alien is by ORing the 2 bytes of the word to see if its 0 or not.
; If zero then no aliens present.
;
; Bit 0 represents the left most alien and Bit 11 represents the right most.
;
AlienTable:
ALIEN_WAVE:         defw $FFFF, $FFFF, $FFFF, $FFFF, $FFFF
; backup store of player 1's wave of aliens
P1_ALIEN_WAVE:      defw $FFFF, $FFFF, $FFFF, $FFFF, $FFFF
 
; backup store of player 2's wave of aliens
P2_ALIEN_WAVE:      defw $FFFF, $FFFF, $FFFF, $FFFF, $FFFF 

AliensX:            defb       40               ; the start X position of the aliens
AliensY:            defb       40               ; the start Y position of the aliens
WaveDirection:      defb      129               ; the direction the aliens are moving in
AlienWaveToDraw:    defb        5               ; the current wave to draw
AlienMinX:          defb      255               ; the minimum x position of an alien
AlienMaxX:          defb        0               ; the maximum x position of an alien
AlienMaxY:          defb        0               ; the maximum y position of an alien during the wave
AlienFlags:         defb  AF_DRAW               ; flags: bit 0 - erase old sprite first
AlienEraseX:        defb        0               ; x position (in wave) of alien to erase
AlienEraseY:        defb        0               ; y position (row) of alient to erase
AlienEraseD:        defb        0               ; the direction the wave is moving when erase happened
AlienEraseXX:       defb        0
AlienEraseYY:       defb        0
AlienKillFrame:     defb        0

; backup of the table above for alien wave reset
AlienTableBackup:   defs AlienTableBackup - AlienTable  

WAVE_SPEED          equ       800                ; 800 seems to be the nicest start value
AliensWaveOffset:   defb        0               ; the offset to add to AliensY after each successful wave
MarchCount:         defw  WAVE_SPEED            ; the wave speed counter
MarchCountWave:     defw  WAVE_SPEED            ; the max speed of the wave after each alien is shot down
MarchCountMax:      defw  WAVE_SPEED            ; the max speed of the wave after each successful wave (each wave gets faster)  

;---------------------------------------------------------------;
; FUNCTIONS                                                     ;
;---------------------------------------------------------------;

BackupAlienTable:   push hl
                    push de
                    push bc
                    ld hl, AlienTable
                    ld de, AlienTableBackup
                    ld bc, AlienTableBackup - AlienTable
                    ldir
                    pop bc
                    pop de
                    pop hl
                    ret
                    
RestoreAlienTable:  push hl
                    push de
                    push bc
                    push af
                    ld hl, AlienTableBackup
                    ld de, AlienTable 
                    ld bc, AlienTableBackup - AlienTable
                    ldir
                    pop af
                    jr c, RAT1
                    xor a
                    ld (AliensWaveOffset), a
                    jr RAT2
RAT1:               ld a, (AliensY)
                    ld b, a
                    ld a, (AliensWaveOffset)
                    cp 64
                    jr z, RAT3                    
                    add a, 4
                    ld (AliensWaveOffset), a
RAT3:               add a, b
                    ld (AliensY), a                    
RAT2:               pop bc
                    pop de
                    pop hl
                    ret

; hl - player wave to restore as current    
RestoreAlienWave:   ld de, ALIEN_WAVE           ; set the DEstination table (default wave table)
RAW_COPY:           ld bc, 10                   ; set the number of bytes to copy (5 lines * 2 bytes)
                    ldir                        ; do the copy
                    ret

; hl - player wave to save from the current wave
SaveAlienWave:      ex de, hl                   ; swap the table pointers
                    ld hl, ALIEN_WAVE           ; set the source as the alien table
                    jr RAW_COPY                 ; do the copy

MarchAliens:        ld a, (AlienFlags)          ; are we erasing an alien
                    and AF_ERASE 
                    call nz, EraseAlien         ; erase the alien 
                    ld a, (AlienFlags)          ; are we killing an alien
                    and AF_KILL 
                    call nz, KillAlien          ; kill the alien
                    call CheckWaveEnd           ; have we killed all the aliens
                    ret c                       ; if we have then no need to march or draw
                    ld a, (AlienFlags)          ; are we drawing the rows?
                    and AF_DRAW                 ; check if the flag is set
                    jp nz, DrawAliens           ; if set, jp to draw aliens
                    ld hl, (MarchCount)         ; get the march count
                    dec hl                      ; dec it                                                   
                    ld (MarchCount), hl         ; store the count
                    ld a, l
                    or h                      
                    ret nz                      ; ret if not zero yet
                    ld hl, (MarchCountWave)     ; reset the march count
                    ld (MarchCount), hl
                    ld a, (AlienFlags)          ; get the alien flags
                    or AF_DRAW                  ; set the draw alien rows flag                                                  
                    ld (AlienFlags), a          ; set the flags
                    ld a, (WaveDirection)       ; get the wave direction
                    ld b, a                     ; store in B
                    ld a, (AliensX)             ; get the current x position
                    add a, b                    ; add the direction
                    ld (AliensX), a             ; store x position
                    ld a, (AlienMinX)
                    cp 4
                    call c, SwapWaveDirection
                    ld a, (AlienMaxX)
                    cp 240
                    call nc, SwapWaveDirection
                    call ResetLimits
                    ret
                    
SwapWaveDirection:  ld a, (WaveDirection)       ; get the current direction
                    xor 254                     ; complement it (change -1 to 1, 1 to -1)
                    ld (WaveDirection), a       ; save the new direction
                    ld b, a                     ; b = current direction
                    ld a, (AliensX)             ; a = aliens x
                    add a, b                    ; a = aliens x + direction
                    ld (AliensX), a             ; save new position
                    ld a, (AlienMaxY)           ; get max alien y position
                    cp 160                      ; is it at the bottom of the play area?
                    jp nc, GameIsOver           ; yes, then game is over
                    ld a, (AliensY)             ; no, move the wave down
                    add a, ALIEN_DOWN
                    ld (AliensY), a             
                    ld a, (AlienFlags)          ; a = alien flags
                    or AF_CLEAR                 ; clear row above the aliens after dropping down
                    ld (AlienFlags), a          ; store flags
                    ret

CheckWaveEnd:       ld a, (MotherState)         ; get the state of the mothership
                    cp MOTHER_COUNTDOWN         ; is it off screen? 
                    ret nz                      ; potentially no, so wait for it to finish
                    ld hl, ALIEN_WAVE           ; hl = alien wave table
                    ld b, 5                     ; b = 5 rows
CWE1:               ld a, (hl)                  ; get row 1st byte
                    and a                       ; is it zero?
                    jr nz, CWENotOver           ; no, aliens exist so not over yet
                    inc hl                      ; move to next row byte
                    ld a, (hl)                  ; get row 2nd byte 
                    and ALIEN_ROW_MASK          ; is the row empty?            
                    jr nz, CWENotOver           ; no, aliens exist so not over yet 
                    inc hl                      ; next row
                    djnz CWE1                   ; check all rows
                    ld hl, (MarchCountMax)      ; get the max speed of the wave
                    ld bc, 50                   ; speed it up for new wave
                    sbc hl, bc                  ; adjust
                    jr z, CWE2                  ; is it <= 0 yes, then leave at 50
                    jr c, CWE2
                    ld (MarchCountMax), hl      ; save the new max speed for the wave
                    ld (MarchCountWave), hl     ; reset wave speed 
                    ld (MarchCount), hl         ; reset speed counter
CWE2:               scf                         ; signal reset screen to move the start position of the aliens down
                    call ResetScreen            ; reset the screen
                    scf                         ; signal the wave ended
                    ret
                    
CWENotOver:         and a                       ; signal wave is still running
                    ret                                                            
                    
ResetLimits:        ld a, 255                   ; set minimum values to the maximum
                    ld (AlienMinX), a
                    xor a                       ; set maximum values to the minimum
                    ld (AlienMaxX), a
                    ld (AlienMaxY), a
                    ret                                                                          

KillAlien:          ld a, (AlienKillFrame)      ; get the kill frame count (time the explosion stays on screen)
                    inc a                       ; count
                    cp KILL_WAIT                ; has it finished
                    jr nc, KillAlienNext        ; yes, then no move explosion
                    ld (AlienKillFrame), a      ; no, draw the explosion
                    ld a, (AlienEraseY)         ; convert the row into a screen y position
                    sla a                       
                    sla a
                    sla a 
                    sla a                       ; row * 16
                    ld b, a                     
                    ld a, (AlienEraseYY)
                    add a, b
                    ld b, a                     ; b = y position
                    ld a, (AlienEraseX)
                    sla a
                    sla a
                    sla a
                    sla a                       ; column * 16
                    ld c, a
                    ld a, (AlienEraseXX)
                    add a, c
                    ld c, a                     ; c = x position
                    ld a, (WaveDirection)
                    add a, c
                    ld c, a
                    ld hl, AlienExplosion000    ; hl = alien explosion frame 0
                    call DrwSpr16               ; draw it
                    ret
KillAlienNext:      xor a
                    ld (AlienKillFrame), a      ; reset the kill frame
                    ld a, (AlienFlags)          ; get flags
                    and ~AF_KILL                ; stop killing the alien
                    or AF_ERASE                 ; erase the explosion
                    ld (AlienFlags), a          ; store result
                    ret                    
                    

EraseAlien:         ld hl, ErzSpr16             ; change the alien sprite routine
                    ld (DACE + 1), hl           ; change to ErzSpr16
                    ld (DACO + 1), hl           ; change to ErzSpr16
                    ld a, (AlienEraseY)         ; convert the row in a screen y position
                    push af                     ; save row                      (row)
                    ld b, a                     ; convert row
                    ld a, 5                     ; from 0 - 5, to 5 - 0
                    sub b
                    ld b, a                     ; b = alien type
                    pop af                      ; restore row                   () 
                    sla a                       
                    sla a
                    sla a 
                    sla a                       ; row * 16
                    ld c, a                     
                    ld a, (AlienEraseYY)
                    add a, c
                    ld c, a                     ; c = y position
                    ld a, (AlienEraseX)
                    sla a
                    sla a
                    sla a
                    sla a                       ; column * 16
                    ld e, a
                    ld a, (AlienEraseXX)
                    add a, e
                    ld e, a                     ; e = x position
                    ld a, (WaveDirection)
                    add a, e
                    ld e, a
                    call DrawAlien
                    ld hl, DrwSpr16             ; change the alien sprite routine
                    ld (DACE + 1), hl           ; back to DrwSpr16
                    ld (DACO + 1), hl           ; back to DrwSpr16
                    ld a, (AlienFlags)
                    and ~AF_ERASE
                    ld (AlienFlags), a
                    ret

                                        
DrawAliens:         ld hl, ALIEN_WAVE           ; point to top row of aliens
                    ld b, ALIEN_ROWS            ; loop for all rows
                    ld a, (AliensY)             ; get the wave y position
                    ld c, a                     ; and put it in C  
                    ld a, (AlienWaveToDraw)
                    ld e, a
DA_Lp1:             ld a, e                    
                    cp b
                    jr z, DA_Dw
                    ld a, ALIEN_ROW_HEIGHT      ; get row jump for alien rows
                    add a, c                    ; move wave y to next y position
                    ld c, a                     ; store in C
                    inc hl                      ; move to next row
                    inc hl                      ;
                    djnz DA_Lp1                 ; draw all rows
DA_Dw:              call DrawAliensRow          ; draw the current row
                    ld a, (AlienWaveToDraw)
                    dec a
                    ld (AlienWaveToDraw), a
                    ret nz
                    ld a, ALIEN_ROWS
                    ld (AlienWaveToDraw), a
                    ld a, (AlienFlags)          ; get the alien flags
                    and ~(AF_DRAW | AF_CLEAR)
                    ld (AlienFlags), a
                    ret


;
; IN:
;   b  - row 
;   c  - y position
;   hl - wave row
;
DrawAliensRow:      call SetErase
                    ld a, (AliensX)             ; get the x position of the wave
                    ld e, a
                    ld a, (hl)                  ; get first part of row                                 
                    push hl                     ; save the wave row pointer
                    ld d, 8                     ; do 1st 8 aliens
                    call DrawPartRow            ; call the first 8 aliens
                    pop hl                      ; restore the wave row pointer
                    inc hl                      ; move to next row value
                    ld a, (hl)                  ; get second part of row
                    ld d, ALIEN_COLS - 8        ; do next 1-8 aliens
                    call DrawPartRow            ; draw the second 0-8 aliens
                    ld a, (AlienFlags)          ; get the flags
                    and AF_CLEAR                ; is clear row above flag set
                    ret z                       ; no, finished
                    call ClearRowAbove          ; yes, clear the row above
                    ret                                         
                    
                    
;
; IN:
;   a  - alien bits
;   b  - row 
;   c  - y position
;   d  - no of aliens to draw
;   e  - x position
;
DrawPartRow:        rra                         ; get alien bit into carry flag
                    push af                     ; save alien bits
                    push bc                     ; save row and y position
                    push de                     ; save alien count and x position                        
                    call nc, SetErase           ; draw the next sprite with a clear edge
                    call c, DrawAlienSprite     ; draw the alien
                    pop de                      ; restore alien count and x position
                    pop bc                      ; restore row and y position      
                    ld a, 16                    ; amount to inc x position by
                    add a, e                    ; move to next x position    
                    ld e, a                     ; save x position in E
                    pop af                      ; restore alien bits
                    dec d                       ; dec alien count
                    jr nz, DrawPartRow          ; loop until all alien
                    ret
                    
;
; IN:
;   b  - row 
;   c  - y position
;   e  - x position
;
DrawAlienSprite:    push bc                     ; save row and y position
                    push de                     ; save and x position
                    ld a, (WaveDirection)       ; get wave direction
                    add a, e                    ; add it to the x position
                    ld e, a                     ; update x position 
                    call DrawAlien              ; draw the new alien
                    pop de                      ; restore previous position
                    pop bc                      ; restore row and y position
                    ret
                    
;
; IN:
;   b  - row 
;   c  - y position
;   e  - x position
;
DrawAlien:          ld a, b                     ; set a with row number
                    ld b, c                     ; set B with y position
                    ld c, e                     ; set C with x position
                    cp 5                        ; is it row 5 (top row)
                    jr z, DrawAlien3            ; if zero (yes) then draw the 3rd alien type
                    cp 4                        ; is it row 4 (2nd from top)
                    jr z, DrawAlien2            ; if zero (yes) then draw the 2nd alien type    
                    cp 3                        ; is it row 3 (middle)
                    jr z, DrawAlien2            ; if zero (yes) then draw the 2nd alien type
                    ld hl, Alien1               ; must be 1 of the lower 2 rows 
DrawAlienDraw:      push hl                     ; save sprite frame table pointer
                    pop ix                      ; put sprite frame table pointer into IX 
                    ld a, c                     ; get x position
                    and 1                       ; is it odd?
                    jr nz, DrawAlienOdd         ; if yes then draw the odd frame of the sprite
DrawAlienDrawFrame: ld a, (AlienMinX)           ; get the current minimum x position of any alien
                    cp c                        ; compare to this x position
                    jr c, DADF1                 ; is it smaller?
                    ld a, c                     ; yes, then 
                    ld (AlienMinX), a           ; set this aliens position as the minimum so far
DADF1:              ld a, (AlienMaxX)           ; get the current maximum x position of any alien
                    cp c                        ; compare to this x position 
                    jr nc, DADF2                ; is it larger?
                    ld a, c                     ; yes, then
                    ld (AlienMaxX), a           ; set this x position as the maximum so far               
DADF2:              ld a, (AlienMaxY)
                    cp b
                    jr nc, DADF3
                    ld a, b
                    ld (AlienMaxY), a           ; set this y as the maximum so far
DADF3:              ld l, (ix + 1)              ; ld hl with the sprite frame 0 address
                    ld h, (ix + 2)
DACE:               call DrwSpr16               ; draw frame 0 of the alien
                    ret
DrawAlienOdd:       ld l, (ix + 3)              ; ld hl with the sprite frame 1 address
                    ld h, (ix + 4)              
DACO:               call DrwSpr16               ; draw frame 1 of the alien
                    ret                                        
DrawAlien3:         ld hl, Alien3               ; point to 3rd alien type         
                    jr DrawAlienDraw            ; draw it                    
DrawAlien2:         ld hl, Alien2               ; point to 2nd alien type
                    jr DrawAlienDraw            ; draw it                    
                    

ClearRowAbove:      ld a, (AlienMaxY)           ; get the y position of the lowest alien
                    cp c                        ; is the current row to clear greater than the lowest sprite?
                    ret c                       ; yes, then exit
                    push bc                     ; save bc                       (bc)
                    push de                     ; save de                       (bc, de)
                    push hl                     ; save hl                       (bc, de, hl)
                    ld b, c                     ; get y position into b
                    ld c, 0                     ; reset x to 0
                    ld e, 32                    ; width is 32 columns
                    ld d, ALIEN_DOWN            ; do ALIEN_DOWN number of lines
                    ld a, b                     ; move b to above alien sprite
                    sub d
                    ld b, a                     ; b is n pixels above alien
                    call ClrBlock               ; clear the pixels
                    pop hl                      ; restore hl                    (bc, de)
                    pop de                      ; restore de                    (bc)
                    pop bc                      ; restore bc                    ()
                    ret


;
; GetAlienBottomRow
; Find the Y value of the lowest alien row and the bottom of the alien
; out a = bottom of lowest alien sprite
;
GetAlienBottomRow:  push bc                     ; save bc
                    push hl                     ; save hl
                    ld c, ((ALIEN_ROWS-1)*16)+8 ; pixel range for entire alien wave
                    ld b, 4                     ; 5 row (0-4)
                    ld hl, P1_ALIEN_WAVE - 1    ; end of AlienWave table (bottom)
LSR1:               ld a, (hl)                  ; get the alien wave data          
                    and ALIEN_ROW_MASK          ; mask off the right end bits that are not used
                    jr nz, LSR2                 ; if not zero then aliens exist and we are done
                    dec hl                      ; move to the left most bits of alien wave 
                    ld a, (hl)                  ; get the alien data                  
                    dec hl                      ; up to next row
                    and a                       ; is current data zero?
                    jr nz, LSR2                 ; no?, then we are done
                    ld a, c                     ; get pixel range count
                    sub ALIEN_ROW_HEIGHT        ; remove a row of aliens
                    ld c, a                     ; save in c
                    djnz LSR1                   ; test next row of aliens
LSR2:               ld a, (AliensY)             ; get the top of the alien wave 
                    add a, c                    ; add the pixel range of the aliens found 
                    pop hl                      ; restore hl
                    pop bc                      ; restore bc                                      
                    ret 

