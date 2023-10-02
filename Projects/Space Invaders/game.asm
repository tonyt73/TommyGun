;---------------------------------------------------------------;
;                                                               ;
;  SPACE INVADERS                                               ;
;                                                               ;
;  Space Invaders was designed and programmed by                ;
;  Toshihiro Nishikado for Taito, Japan in 1978                 ;
;  and remains one of the most popular arcade games ever made   ;
;                                                               ;
;       Programmed by Tony Thompson                             ;
;       Start Date  10 Nov 2007                                 ;
;           Simple player movement and wave animation           ;
;           Wave rendering was slow                             ;
;       Update 17 Mar 2015                                      ;
;           Sped up wave animation                              ;
;               Only draw 1 row of the wave each frame          ;
;           Added in interrupt driven player movement           ;
;               Smoothed out the movement                       ;
;           Added a cool loading screen                         ;
;           Added alien explosion animation and scoring         ;
;           Started scoring system                              ;
;       Update 2 Sep 2015                                       ;
;           Added player missile                                ;
;               Based on interrupt counter smooths out movement ;
;           Added player missile collision detection            ;
;       Update 4 Sep 2015                                       ;
;           Added new wave                                      ;
;           Added player life handling                          ;
;           Added no lifes = game over                          ;
;       Update 5 Sep 2015                                       ;
;           Fixed player missile collision with aliens          ;
;           Fixed alien wave speed mechanism                    ;
;           Added base destruction                              ;
;           Added mothership                                    ;
;           Added mothership collision detection                ;
;       Update 6 Sep 2015                                       ;
;           Fixed mothership score bug                          ;
;           Add joystick start code                             ;
;               Keyboard (Z,X,Space)                            ;
;               Cursor keys/joystick                            ;
;               Interface II joystick port 1                    ;
;               Interface II joystick port 2                    ;
;               Kempston joystick                               ;
;           Added Kempston joystick detection                   ;
;       Update 7 Sep 2015                                       ;
;           Added new waves starting lower                      ;
;           Added start of 1 or 2 player mode                   ;
;               show active player                              ;
;       Update 16 Feb 2016                                      ;
;           Added play sound fx to interrupt routine            ;
;               only plays last requested sound                 ;
;               minimises time spent playing sounds             ;
;               still minor frame pause on long sounds          ;
;               need a better solution and/or beeper routine    ;
;       Update 17 Feb 2016                                      ;
;           Fixed scoring bug (not showing over 10,000)         ;
;           Animated menu screen                                ;            
;       Update 18 Feb 2016                                      ;
;           Add explosion at top of screen                      ;
;           Add extra life logic                                ;
;           Fixed inverted scoring bug                          ;
;           Add Game Over screen                                ;
;               Add when aliens get to bottom row - game over   ;
;               When all lives lost - game over                 ;
;           Flash current player                                ;
;           Added queued sounds                                 ;
;               1 per interrupt                                 ;
;           Added player name when flashing before start        ;
;       To Be Done                                              ;
;           Attract screen cycles                               ;
;               <1 or 2 PLAYERS>                                ;
;               *1 PLAYER     PRESS 1                           ;
;               *2 PLAYERS    PRESS 2                           ;
;           Finish start menu                                   ;
;               Player 1 or 2 selection                         ;
;           Add 2 player mode                                   ;
;               switch between player, restore wave and ship    ;
;               when reset player hide P1, show P2              ;
;           Add waves starting on right side                    ;
;           Add mothership starting on right side               ;
;           Add Alien missiles                                  ;
;           Add alien missile collision detection               ;
;           Proper space invader sounds                         ;
;                                                               ;
;---------------------------------------------------------------;
; Document assembly files                                       ;
; file              header      functions   code                ;
; game.asm            X            X         .                  ;
; player.asm          X            .         .                  ;
; aliens.asm          X            .         X                  ;
; mothership.asm      X            X         X                  ;
; menu.asm            X            X         X                  ;
; libinput.asm        X            X         X                  ;
; libisr.asm          X            X         X                  ;
; libmath.asm         X            X         X                  ;
; libscreen.asm       X            X         X                  ;
; libsprite.asm       X            X         X                  ;
; libtext.asm         X            X         X                  ;
; libosb.asm          X            X         X                  ;
;---------------------------------------------------------------;
include "libisr.asm"
;            org 24860
;            jp Start
; place an off screen buffer here in non contended memory
include "libosb.asm"

;---------------------------------------------------------------;
;                                                               ;
;   Global Variables                                            ;
;                                                               ;
;---------------------------------------------------------------;
EXTRA_LIFE  equ   150
PLAYERLIVES equ     3
P1Score     defw    0                   ; the score for player 1
P1Lives     defb    PLAYERLIVES         ; the number of lives for player 1 
P1ExtraLife defb    0                   ; indicates if player 1 got an extra life
P2Score     defw    0                   ; the score for player 2
P2Lives     defb    PLAYERLIVES         ; the number of lives for player 2
P2ExtraLife defb    0                   ; indicates if player 2 got an extra life
HiScore     defw    100                 ; the highest score achieved
GameOver    defb    0                   ; game over flag
CurPlayer   defw    P1Score             ; the current player 
LastScore   defw    0                   ; last score displayed
FlashPlayer defb    1                   ; indicates to flash player score

;---------------------------------------------------------------;
;                                                               ;
;   Start of Game (Main game loop)                              ;
;                                                               ;
;    This is the main game loop. It isn't much but then again   ;
;    it doesn't need to be. :-)                                 ;
;                                                               ;
;    We simply show the start screen and then the play the game ;
;    the we repeat.                                             ;
;                                                               ;
;---------------------------------------------------------------;
GameStart:  call DisablePlayer
            call DetectKempston         ; detect if a kempston joystick available
            call ISR_Start
            call BackupAlienTable       ; backup the alien tables
mainLp:     call ShowLoadingScreen      ; show the cool loading screen
            call ClearScr               ; clear the screen
            call DrawMain               ; draw the main area that never changes
            call ShowStart              ; show the start screen text
            call DrawMain               ; draw the main area that never changes
            call PlayGame               ; play the game
            and a                       ; signal to reset the wave offset
            call RestoreAlienTable      ; restore the alien tables
            jr mainLp                   ; when dead repeat
            call ISR_Stop               ; yes, you can't get here yet            
            ret

;---------------------------------------------------------------;
; PlayGame                                                      ;
; Plays a single game                                           ;
;---------------------------------------------------------------;
PlayGame:   xor a
            ld (GameOver), a
            call ResetPlayer
            and a
            call ResetScreen
            call EnablePlayer
PG_Lp1:     call FastRNG                ; add some randomness
            call MarchAliens            ; march the alien wave
            call FastRNG                ; add some randomness
            call MothershipFSM          ; control the mothership
            call DrawPlayer             ; draw the player
            call MovePBullet            ; move the player bullet
            call BulletExplosion        ; bullet explosion
            ;call WaitVBlank
            ld a, (GameOver)
            and a
            jr z, PG_Lp1
            ld a, BRIGHT + INK_WHT + PAP_BLK
            ld bc, $0000
            ld de, $0232                ; show player 2 score
            call DisablePlayer
            ret
            
;---------------------------------------------------------------;
; ResetScreen                                                   ;
; Resets the screen to start a new wave of aliens               ;
;---------------------------------------------------------------;
FLASH_SPEED equ 15000            
ResetScreen:push af
            call ClrPlayScr
            ; hide scores
            ld a, BRIGHT + INK_WHT + PAP_BLK
            ld bc, $0000
            ld de, $0232
            call ClrAttr                ; hide player 1 score
            ld a, BRIGHT + INK_BLK + PAP_BLK
            ld bc, $00A8
            ld de, $0308
            call ClrAttr                ; hide player 2 score
            ; show bottom line
            ld de, LINE                 ;
            call DrwStrP                ; draw the line at the bottom
            call ShowLives              ; show the lives
            call FlashPlayerUp
            call ClrPlayScr       
            call DrawBases              ; draw the bases
            call ResetMothership        ; reset the mothership
            call ResetLimits            ; reset wave limits
            call ResetPlayerWave        ; reset player position, bullets for next wave
            ld hl, PlayerX              ; point to player position
            call DrawPlayerShip         ; draw the player ship
            pop af
            call RestoreAlienTable      ; restore the alien wave formation
            xor a                       ;
            ld (WaveDirection), a       ; set wave direction to stay still
            call DrawAliens             ; draw a wave of aliens
            ld a, 1                     ; set wave direction to ->
            ld (WaveDirection), a       ; update direction
            ; show the bases, player and green line
            ld a, BRIGHT + PAP_BLK + INK_GRN
            ld bc, $9008                ; X:  8($08), Y: 144($90)
            ld de, $051E                ; W: 30($1E), H:   5($05)
            call ClrAttr
            ld a, BRIGHT + PAP_BLK + INK_WHT
            ld bc, $0000                ; X:  0($00), Y:   0($00)
            ld de, $1220                ; W: 32($20), H:  18($12)
            call ClrAttr
            ld a, BRIGHT + PAP_BLK + INK_RED
            ld bc, $1800                ; X:  0($00), Y:  24($18)
            ld de, $0220                ; W: 32($20), H:   2($02)
            call ClrAttr                ;
            ret
            
FlashPlayerUp:
            ; flash current player
            ld a, (FlashPlayer)
            and a
            ret z
            xor a
            ld (FlashPlayer), a
            ld hl, (CurPlayer)
            ld bc, P1Score
            sbc hl, bc
            ld c, BRIGHT + INK_WHT + PAP_BLK
            ld b, 10
            ld a, c 
            jr nz, FPU2
            push bc
            ; show play player<1>
            ld de, PLAYER1
            call DrwStrP
            pop bc
FPU1:       push bc
            xor c
            push af
            ld bc, $1018                ; x = 40, y = 16                     
            ld de, $0108
            call ClrAttr
            ld hl, 0
            ld de, 0
            ld bc, FLASH_SPEED
            ldir
            pop af
            pop bc
            djnz FPU1            
            ret
FPU2:       push bc
            ; show play player<2>
            ld de, PLAYER2
            call DrwStrP
            pop bc
FPU2l:      push bc
            xor c
            push af
            ld bc, $10A8                ; x = 168, y = 16                     
            ld de, $0108
            call ClrAttr
            ld hl, 0
            ld de, 0
            ld bc, FLASH_SPEED
            ldir
            pop af
            pop bc
            djnz FPU2l
            ret
                        

;---------------------------------------------------------------;
; DrawBases                                                     ;
; Draws the player bases                                        ;
;---------------------------------------------------------------;
BASE_TOP    equ     144
BASE_HEIGHT equ      16
DrawBases:  ld hl, Base
            ld c, 32
            ld b, BASE_TOP
            ld a, INK_BLK
            call DrwSprNC               ; draw left most base 
            ld hl, Base
            ld c, 88
            ld b, BASE_TOP
            ld a, INK_BLK
            call DrwSprNC               ; draw left middle base
            ld hl, Base
            ld c, 144
            ld b, BASE_TOP
            ld a, INK_BLK
            call DrwSprNC               ; draw right middle base
            ld hl, Base
            ld c, 200
            ld b, BASE_TOP
            ld a, INK_BLK
            call DrwSprNC               ; draw right most base
            ret              

;---------------------------------------------------------------;
; DrawScores                                                    ;
; Draws the player scores and high score                        ;
;---------------------------------------------------------------;
DrawScores: ld hl, (P1Score)
            ld a, 4 
            call DrawScore              ; draw P1 score
            ld hl, (P2Score)
            ld a, 22
            call DrawScore              ; draw P2 score
            ld hl, (HiScore)
            ld a, 13
            call DrawScore              ; draw Hi score
            ret
            
;---------------------------------------------------------------;
; Score text string                                             ;
; column, row, 00000                                            ;
;---------------------------------------------------------------;
Score:      defb  0                     ; column to print at
            defb  2                     ; row to print on
            defb 32                     ; 1,000s not shown if score < 10,000
            defb 48                     ; 100s 
            defb 48                     ; 10s
            defb 48                     ; units     
            defb 48                     ; always 0, scoring is in 1,2,3, etc increments 
                                        ; allows for max score of 655350, but only displays 99,990
            defb  0                     ; string terminator (end of string)

;---------------------------------------------------------------;
; DrawScore                                                     ;
; Displays the score value on screen                            ;
;---------------------------------------------------------------;
DrawScore:  ld (Score + 0), a           ; store the column position
            ld a, 32                    ; don't show 1,000's by default
            ld (Score + 2), a
            ld de, 1000                 ; count the 1000's
            call IntDiv
            jr z, DS1
            add a, 48                   
            ld (Score + 2), a           ; show the 1,000's value 
DS1:        ld de, 100
            call IntDiv                 ; count the 100's
            add a, 48
            ld (Score + 3), a           ; store the 0-9 character of the 100's
            ld de, 10
            call IntDiv                 ; count the 10's
            add a, 48
            ld (Score + 4), a           ; store the 0-9 character of the 10's
            ld a, l                     ; l should have the units in it
            add a, 48   
            ld (Score + 5), a           ; store the 0-9 character of the units
            ld de, Score
            call DrwStrN                ; draw the score
            ret

;---------------------------------------------------------------;
; ShowLives                                                     ;
; Shows the lives available to the player                       ;
;---------------------------------------------------------------;
LivesText:  defb 71, 0, 23, 32, 48, 0 
ShowLives:  ; blank out all lives
            ld a, 0
            ld bc, $B818                ; X: 24($18), Y: 184($B8)
            ld de, $0114                ; W: 20($14), H:   1($1)
            call ClrAttr
            ld ix, (CurPlayer)
            ld a, (ix+2)
            dec a
            rla
            and a
            jr z, SLSkip             
            ; show the lives available
            ld d, 1
            ld e, a 
            ld a, BRIGHT + PAP_BLK + INK_GRN
            ld bc, $B818                ; X: 24($18), Y: 184($B8)
            call ClrAttr
SLSkip:     ld a, (ix + 2)
            add a, 48
            ld (LivesText + 4), a
            ld de, LivesText
            call DrwStrP
            ret
            
;---------------------------------------------------------------;
; TakeALife                                                     ;
; Take a player life                                            ;
;---------------------------------------------------------------;
TakeALife:  ld ix, (CurPlayer)          ; get the player details
            ld a, (ix + 2)              ; get the lives
            dec a                       ; decrement it
            jr z, GameIsOver            ; if zero, the Game is Over
            ld (ix + 2), a              ; update player lives
            call ShowLives              ; show them
            and a
            call ResetScreen            ; reset the screen
            ret
            
;---------------------------------------------------------------;
; GameIsOver                                                    ;
; Game is over. Reset the waves, set game over flag.            ;
;---------------------------------------------------------------;
GameIsOver: ld hl, WAVE_SPEED
            ld (MarchCountMax), hl
            ld (MarchCountWave), hl
            ld (MarchCount), hl
            ld (GameOver), a
            ld (FlashPlayer), a
            ld de, GAMEOVER
            call DrwStrN
            call KeyOrWait
            ld a, 1
            ret
            
;---------------------------------------------------------------;
; ResetPlayer                                                   ;
; Reset the player scores and lives.                            ;
;---------------------------------------------------------------;
ResetPlayer:ld ix, P1Score
            ld (ix + 0), 0
            ld (ix + 1), 0              ; player 1 score reset
            ld (ix + 2), PLAYERLIVES    ; player 1 lives reset
            ld (ix + 3), 0              ; player 1 extra life reset              
            ld (ix + 4), 0              
            ld (ix + 5), 0              ; player 2 score reset
            ld (ix + 6), PLAYERLIVES    ; player 2 lives reset
            ld (ix + 7), 0              ; player 2 extra life reset
            call DrawScores
            ret
            
;---------------------------------------------------------------;
; ExtraLife                                                     ;
; Check if the player gets an extra life and give it if they do ;
;---------------------------------------------------------------;
ExtraLife:  ld ix, (CurPlayer)
            ld a, (ix + 3)
            and a
            ret nz
            ld l, (ix + 0)
            ld h, (ix + 1)
            ld bc, EXTRA_LIFE
            sbc hl, bc
            ret c
            ld (ix + 3), 1
            inc (ix + 2)
            call ShowLives
            ret                       
             
;---------------------------------------------------------------;
; IncScore                                                      ;
; Increment the score by the specified value                    ;
;                                                               ;
; Inputs                                                        ;
;   a - alien row                                               ;
;       0 - 4 is the alien wave rows                            ;
;       5 - 7 is the position in the mothership                 ;
;           2 left/right side                                   ;
;           5 not quite middle                                  ;
;           10 middle                                           ;
;---------------------------------------------------------------;
RowPoints:  defb 3, 2, 2, 1, 1, 2, 5, 10
IncScore:   ld hl, RowPoints
            ld c, a
            ld b, 0
            add hl, bc
            ld c, (hl)
            ld ix, (CurPlayer)
            ld l, (ix + 0)
            ld h, (ix + 1)
            add hl, bc
ISL1:       ld (ix + 0), l
            ld (ix + 1), h
            ld bc, 10000         
            sbc hl, bc                  ; check if score is greater than 99,990
            jr nc, ISL1                 ; loop it back around to 0 if it is
            ld e, (ix + 0)
            ld d, (ix + 1)
            ld hl, (HiScore)            ; hl = hi score
            sbc hl, de                  ; is score > hi score 
            jr nc, IS2                  ; no, then just draw scores             
            ld (HiScore), de            ; yes, update hi score
IS2:        call DrawScores
            call ExtraLife              ; check for extra life 
            ret



GameEnd:

;
; game modules
;
ModulesStart:
include "player.asm"
include "aliens.asm"
include "mothership.asm"
include "menu.asm"
ModulesEnd: 

;
; additional library modules
;
LibrariesStart:
include "libbeeper.asm"
include "libscreen.asm"
include "libsprite.asm"
include "libtext.asm" 
include "libmath.asm"
include "libinput.asm"
LibrariesEnd: 

;
; game resources
;
org 32768
ResourcesStart: 
include "sprites.inc"
include "tables.inc"
include "strings.inc"
include "font.inc"
ResourcesEnd:
LoadingScreenStart: 
include "screen.inc"
LoadingScreenEnd:

; start tape execution at this address
end GameStart
