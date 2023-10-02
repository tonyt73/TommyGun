;---------------------------------------------------------------;
;                                                               ;
;  MENU.ASM                                                     ;
;                                                               ;
;  This file contains functions to control the main menu        ;
;                                                               ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; ShowStart                                                     ;
;                                                               ;
; This routine shows the main start screen text and then waits  ;
; for the user to start the game.                               ;
;                                                               ;
; They can start the game by pressing:                          ;
;  1 - to choose a one player game                              ;
;  2 - to choose a two player game                              ;
;  fire to play                                                 ;
;   depending on the fire button pressed will determine the     ;
;   joystick or keyboard option to use.                         ;
;   fire buttons used                                           ;
;    0             - Cursor keys or Interface II port 2         ;
;                    Cursor keys                                ; 
;                       5 left                                  ;
;                       8 right                                 ;
;                    Interface II port 2                        ;
;                       5 left                                  ;
;                       6 right                                 ;
;    5             - Interface II port 1                        ;
;                       1 left                                  ;
;                       2 right                                 ;
;    Kempston fire - Kempston joystick                          ;
;    Space         - Keyboard                                   ;
;                       Z left                                  ;
;                       X right                                 ;
;                                                               ;
;---------------------------------------------------------------;
ShowStart:  call DrawStart              ; draw the start screen text
            call DrawScores             ; draw the player scores
            call GetPlayOptions         ; wait for the user to press space
            ret    

;---------------------------------------------------------------;
; DrawMain                                                      ;
; Draw the main screen text                                     ;
; This text is always visible                                   ;
;---------------------------------------------------------------;
DrawMain:   ld de, TITLE            
            call DrwStrP                ; SCORE<1> HI-SCORE SCORE<2>
            ld de, CREDIT
            call DrwStrP                ; CREDIT oo
            ld de, LIVES
            call DrwStrP                ; n [][][][]
            ld de, LINE
            call DrwStrP                ; __________________________
            ; show the mothership area in red
            ld a, BRIGHT + PAP_BLK + INK_RED
            ld bc, $2000                ; X:  0($00), Y: 32($20)
            ld de, $0120                ; W: 32($20), H:  1($01)
            call ClrAttr
            ; draw black borders
            ;ld a, PAP_BLK + INK_BLK
            ;ld bc, $00F8
            ;ld de, $1502
            ;call ClrAttr
            ret
;---------------------------------------------------------------;
; DrawStart                                                     ;  
; Draw the start screen text                                    ;
;---------------------------------------------------------------;
DrawStart:  ; hide all text
            ld a, PAP_BLK + INK_BLK
            ld bc, $2800
            ld de, $1020
            call ClrAttr
            ld de, PLAY
            call DrwStrN                ; PLAY       
            ld de, GAME             
            call DrwStrN                ; SPACE INVADERS
            ld de, SCORES
            call DrwStrN                ; *SCORE ADVANCE TABLE*
            ld de, SCORE1
            call DrwStrN                ; =? MYSTERY
            ld de, SCORE2
            call DrwStrN                ; =30 POINTS
            ld de, SCORE3
            call DrwStrN                ; =20 POINTS
            ld de, SCORE4
            call DrwStrN                ; =10 POINTS
            ld de, SPACETOPLAY      
            call DrwStrP                ; PRESS SPACE TO PLAY
            ; hide all text
            ld a, PAP_BLK + INK_BLK
            ld bc, $2800
            ld de, $1020
            call ClrAttr
            ret

;---------------------------------------------------------------;
; ClrPlayScr                                                    ;  
; Clear the main play screen                                    ;
;---------------------------------------------------------------;
ClrPlayScr: ld c, 0
            ld b, 28
            call Pix
            push hl
            ld b, 152                   ; clear to line 180
CPS_Lp1:    push bc
            push hl
            push hl
            pop de
            inc de
            ld (hl), 0
            ld bc, 31
            ldir
            pop hl
            call Incy
            pop bc
            djnz CPS_Lp1
            pop hl
            call Attr
            ld bc, 18 * 32
            push hl
            pop de
            inc de
            ld (hl), BRIGHT + INK_GRN
            ldir
            ret

;---------------------------------------------------------------;
; ShowLoadingScreen                                             ;  
; Show a loading screen$ for 5 seconds                          ;
;---------------------------------------------------------------;
ShowLoadingScreen:
            ld hl, LoadingScreen + SCRLEN + ATTRLEN
            ld de, SCREEN + SCRLEN + ATTRLEN
            ld bc, SCRLEN + ATTRLEN
            lddr                        ; draw screen backwards
            call KeyOrWait
            ret
            
;---------------------------------------------------------------;
; KeyOrWait                                                     ;  
; Wait for 10 seconds or a Space key to be pressed              ;
;---------------------------------------------------------------;
KeyOrWait:  ld hl, (ISRCounter)
            ld b, h
            ld c, l
            ld de, 500                  ; 500 = 50 interrupts per second * 10 => a 10 second wait
            add hl, de
            ex de, hl
KoW1:       call IsSpacePressed
            jr c, KoW2
            ld hl, (ISRCounter)
            sbc hl, de
            jr c, KoW1
            ret
KoW2:       call IsSpacePressed
            ret nc
            ld a, SPACE_SFX
            call playsfx
            jr KoW2                        

;---------------------------------------------------------------;
; GetPlayOptions                                                ;  
; Gets the input method the player is to use to play the game   ;
;                                                               ;
; They can start the game by pressing:                          ;
;  1 - to choose a one player game                              ;
;  2 - to choose a two player game                              ;
;  fire to play                                                 ;
;   depending on the fire button pressed will determine the     ;
;   joystick or keyboard option to use.                         ;
;   fire buttons used                                           ;
;    0             - Cursor keys or Interface II port 2         ;
;                    Cursor keys                                ; 
;                       5 left                                  ;
;                       8 right                                 ;
;                    Interface II port 2                        ;
;                       5 left                                  ;
;                       6 right                                 ;
;    5             - Interface II port 1                        ;
;                       1 left                                  ;
;                       2 right                                 ;
;    Kempston fire - Kempston joystick                          ;
;    Space         - Keyboard                                   ;
;                       Z left                                  ;
;                       X right                                 ;
;---------------------------------------------------------------;
GetPlayOptions:
            ld hl, 22662
            ld (Aa), hl
            ld a, 21
            ld (Aw), a
            ld a, 8
            ld (Ah), a
            ld a, BRIGHT + INK_WHT + PAP_BLK
            ld (Ac), a 
GPOL1:      call AnimateMenu
            ; press fire to play
            call DetectInput
            jr nc, GPOL1
            ld a, 128 + 10
            call playsfx
            ; show all text
            ld a, BRIGHT + INK_WHT + PAP_BLK
            ld bc, $0500
            ld de, $0E20
            call ClrAttr
            ret
            
;---------------------------------------------------------------;
; AnimateMenu                                                   ;  
; Reveal the menu text                                          ;
;---------------------------------------------------------------;
Aa  defw 22662
Aw  defb 21
Ah  defb 8
Ac  defb BRIGHT + INK_WHT + PAP_BLK
AnimateMenu:ld a, (Ah)
            and a
            ret z
            call Pause
            ld hl, (Aa)
            ld a, (Ac)
            ld (hl), a
            push hl
            ld bc, 32
            add hl, bc
            ld (hl), a
            pop hl
            inc hl
            ld (Aa), hl
            ld a, (Aw)
            dec a
            ld (Aw), a
            ret nz
            ld a, 21
            ld (Aw), a
            ld bc, 11 + 32
            add hl, bc
            ld (Aa), hl
            ld a, (Ah)
            dec a
            ld (Ah), a
            cp 1
            ret nz
            ld a, BRIGHT + INK_GRN + PAP_BLK
            ld (Ac), a
            ret
            
             

;---------------------------------------------------------------;
; Pause                                                         ;  
; Wait for short delay period                                   ;
;---------------------------------------------------------------;
PAUSE_DELAY equ 2500            
Pause:      push bc                     ; save bc
            push de                     ; save de
            push hl                     ; hl
            ld bc, PAUSE_DELAY          ; define the pause length
            ld de, 0                    ; define block transfer destination
            ld hl, 0                    ; define block transfer source
            ldir                        ; do a block transfer (takes a little while)
            pop hl                      ; restore hl
            pop de                      ; restore de
            pop bc                      ; restore bc
            ret                         ; pause complete

