;---------------------------------------------------------------;
;                                                               ;
;   the Gem Machine - A Bejewelled clone for the ZX Spectrum    ;
;                                                               ;
;       Programmed by Tony Thompson and Ian Munro               ;
;       Developed as part of Team WoS                           ;
;       Start Date  25 Apr 2006                                 ;
;       Last Update 21 May 2006                                 ;
;         Reorganised main loop                                 ;
;         Integrate new hi score table                          ;
;         Added main menu                                       ;
;         Added Graphics themes                                 ;
;         Added control types (Keys, Joystick, Mouse)           ;
;                                                               ;
;---------------------------------------------------------------;

include "isr.inc"
;main:           org 24860
;Test codes (commented)
main:           push af             ; save the registers
                push bc
                push de
                push  hl
                xor a               ; clear accum
                call 8859           ; set border colour to black
                xor a
                call SND_SETSFXM    ; turn off sound fx
                call ClrScr         ; clear the screen
                call SFX_INIT
                ld hl, ScorePanel   ; hl points to score panel tile
                ld bc, 0            ; set x,y to 0,0
                xor a               ; clear accum
                ld (Level), a
                ld (MatchesSoFar), a
                call DrwTile        ; draw the score panel tile with attributes
                call PrintLevel
                ld a, GF_MENU       ; set the game flags to show the menu
                ld (GameFlags), a   ; clear the game flags
                ld bc, (PointerPos) ; get the mouse pointer position
                call DrawPointer    ; draw the pointer
                ld hl, TITLE_TUNE
        	    call SND_INIT_HL
        	    call ISR_Start
;---------------------------------------------------------------;
; Programs main loop                                            ;
;   Controls the flow of the program                            ;
;---------------------------------------------------------------;
MainLoop:       ld a, (GameFlags)   ; get game flags
                and GF_QUIT         ; check for quit flag
                jr nz, Quit         ; quit if set
                ld a, (GameFlags)   ; get game flags
                and GF_MENU         ; check for menu flag
                call nz, MainMenu   ; show menu if set
                ld a, (GameFlags)   ; get game flags
                and GF_START_GAME   ; check the start a new game flag
                call nz,GameStartNew; start a new game if set
                ld a, (GameFlags)   ; get game flags
                and GF_GAME_OVER    ; check the game over flag
                call nz, GameOver   ; game over if set
                ld a, (GameFlags)   ; get game flags
                and GF_PLAYING      ; check playing flag
                call nz, GamePlay   ; continue playing game if set
                call MoveGameCursor ; move the games cursor
                jp MainLoop

;---------------------------------------------------------------;
; Quit                                                          ;
;   Returns control back to BASIC                               ;
;---------------------------------------------------------------;
Quit:           call ISR_Stop
                xor a               ; reset accum
                ld (CursorLive), a  ; reset the cursorlive variable
                call ClrScr         ; clear the screen
                pop hl              ; restore the registers
                pop de
                pop bc
                pop af
                ret                 ; return to BASIC


;---------------------------------------------------------------;
; Pause                                                         ;
;   A generic pause function                                    ;
;---------------------------------------------------------------;
Pause:          push bc
                push de
                push hl
                ld bc, PAUSETIME
                ld de, 0
                ld hl, 0
                ldir
                pop hl
                pop de
                pop bc
                ret


;---------------------------------------------------------------;
; Set Game Flag                                                 ;
;   Sets the specified bit(s) in the game flags variable        ;
;   a - contains the flag(s) to set                             ;
;---------------------------------------------------------------;
SetGameFlag:    push bc                 ; save bc
                ld b, a                 ; put the flag bits into b
                ld a, (GameFlags)       ; get the game flags
                or b                    ; set the flags
                ld (GameFlags), a       ; save the game flags
                pop bc                  ; restore bc
                ret
                
;---------------------------------------------------------------;
; Reset Game Flag                                               ;
;   Resets the specified bit(s) in the game flags variable      ;
;   a - contains the flag(s) to reset                           ;
;---------------------------------------------------------------;
ResetGameFlag:  push bc                 ; save bc
                cpl                     ; invert the flags to reset (ie turn them into a mask)
                ld b, a                 ; put inverted flags into b
                ld a, (GameFlags)       ; get the game flags
                and b                   ; reset the game flags bits
                ld (GameFlags), a       ; save the game flags
                pop bc                  ; restore bc
                ret

;---------------------------------------------------------------;
;                                                               ;
; LIBRARY SOURCE CODE                                           ;
;                                                               ;
;---------------------------------------------------------------;
;include "isr.inc"
include "gameplay.inc"
include "control.inc"
include "hiscore.inc"
include "screen.inc"
include "math.inc"
include "window.inc"
include "menu.inc"
include "ay_player.inc"

;---------------------------------------------------------------;
;                                                               ;
; DATA FILES                                                    ;
;                                                               ;
;---------------------------------------------------------------;
include "images.inc"
include "hiscoredata.inc"
include "font.inc"

;---------------------------------------------------------------;
;                                                               ;
; VARIABLES                                                     ;
;                                                               ;
;---------------------------------------------------------------;
;Cursor:         defb 0
CursorPos:      defb 136, 96            ; the current position of the gem cursor
CursorPosOld:   defb 136, 96            ; the previous position of the gem cursor
CursorLive:     defb 0                  ; cursor is being displayed on the screen
PointerPos:     defb 128, 96            ; the currently valid position of the mouse pointer
MovePosLast:    defb 0  ,  0            ; the last position of the mouse
MouseHasMoved:  defb 0                  ; indicates whether the kempstom mouse has moved
MouseStartPos:  defb 0  ,  0            ; the start position of the kempston mouse
GameFlags:      defb GF_MENU            ; start with the main menu
ControlFlags:   defb CF_INTERFACE_II    ; default to the Interface II joystick
;ControlFlags:   defb CF_KEM_JOYSTICK    ; default to the Interface II joystick
MusicFlags:     defb GF_THEME_1         ; default is theme 1
GameTune:       defw TUNE_A             ; the default game music
GemTheme:       defb GF_THEME_1         ; default is theme 1
CursorFlags:    defb CF_NONE            ; default is no buttons pressed
SwapFlags:      defb 0                  ; 1 - left/right, 2 up/down
MatchesSoFar:   defb 0                  ; number of matches for the level
Level:          defb 0                  ; the current level

;---------------------------------------------------------------;
; Gem Tile Themes Table                                         ;
;---------------------------------------------------------------;
TileTheme1:     defw Tile0
                defw Tile1
                defw Tile2
                defw Tile3
                defw Tile4
                defw Tile5
                defw Tile6
TileTheme2:     defw Tile10
                defw Tile11
                defw Tile12
                defw Tile13
                defw Tile14
                defw Tile15
                defw Tile16
TileTheme3:     defw Tile20
                defw Tile21
                defw Tile22
                defw Tile23
                defw Tile24
                defw Tile25
                defw Tile26

;---------------------------------------------------------------;
;                                                               ;
; FLAG DEFINITIONS                                              ;
;                                                               ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; Game Flags                                                    ;
;---------------------------------------------------------------;
GF_QUIT         equ  1          ; user has requested to quit
GF_MENU         equ  2          ; we are currently in the menu system
GF_START_GAME   equ  4          ; we are to start a gane
GF_PLAYING      equ  8          ; we are playing a game
GF_PLAY_MODE    equ 16          ; 1 - normal game, 0 - timed game
GF_GAME_OVER    equ 32          ; game has finished

;---------------------------------------------------------------;
; Control Keys                                                  ;
;---------------------------------------------------------------;
CF_KEYBOARD     equ  1          ; QAOP and Space
CF_INTERFACE_II equ  2          ; interface II ports 1 & 2
CF_KEM_JOYSTICK equ  4          ; kempston joystick
CF_KEM_MOUSE    equ  8          ; kempston mouse

CF_MOUSE_RIGHT  equ  1          ; the kempston right mouse button bit
CF_MOUSE_LEFT   equ  2          ; the kempston left mouse button bit

;---------------------------------------------------------------;
; Graphics Themes                                               ;
;---------------------------------------------------------------;
GF_THEME_1      equ  1          ; Programmer Art
GF_THEME_2      equ  2          ; Square Gems
GF_THEME_3      equ  4          ; Different Shaped Gems

;---------------------------------------------------------------;
; Cursor Flags                                                  ;
;---------------------------------------------------------------;
CF_NONE         equ  0          ; nothing set
CF_ACTION       equ  1          ; fire button pressed or left mouse button
CF_LEFT         equ  2          ; cursor moved left
CF_RIGHT        equ  4          ; cursor moved right
CF_UP           equ  8          ; cursor moved up
CF_DOWN         equ 16          ; cursor moved down


;---------------------------------------------------------------;
; Swap Flags                                                    ;
;---------------------------------------------------------------;
SF_NONE         equ 0           ; nothing to swap
SF_UP           equ 1           ; swap up
SF_DOWN         equ 2           ; swap down
SF_LEFT         equ 4           ; swap left
SF_RIGHT        equ 8           ; swap right

AAA_END:        defb 0
;---------------------------------------------------------------;
; Program start location                                        ;
;---------------------------------------------------------------;
end start


