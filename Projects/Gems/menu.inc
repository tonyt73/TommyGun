;---------------------------------------------------------------;
;                                                               ;
;   Menu.inc                                                    ;
;                                                               ;
;   This file contains routines for dealing with the Main Menu  ;
;                                                               ;
;---------------------------------------------------------------;

MainMenu:       call EraseMenuPtr
                ld hl, TITLE_TUNE
        	    call SND_INIT_HL
                ld a, (GameFlags)
                and GF_PLAYING
                call z, CreditsWindow

                ld a, 72
                call WindowSetColor
                ld b, 16
                ld c, 80
                ld d, 12
                ld e, 19
                call WindowOpen

                ld hl,MainMenu_0
                ld de,MainMenu_0_Txt
                ld a,0 ; Indicating default menu item not required here so set to 0
                call ShowMenu
                
MM_Lp1:         ld hl,MM_Lp2          ; tell the 'CheckCursorPos' function where
                ld (CCRtn_Addr+1),hl  ; to jump back to
                
MM_Lp2:         call MoveMenuCursor  ; Main Menu return loop
                ld ix,MainMenu_0_Rect
                jp CheckCursorPos

;---------------------------------------------------------------;
; MainMenuRet                                                   ;
;   Returns control to the main loop                            ;
;---------------------------------------------------------------;
MainMenuRet:    ld a, GF_MENU
                call ResetGameFlag ; remove the menu flag
                call MenuPause
                call WindowClose
                call WindowClose
                call RefreshPtrBuf
                ld hl, (GameTune)
        	    call SND_INIT_HL
                ret
                
;---------------------------------------------------------------;
; MainGameNormal                                                ;
;   Setups a normal game                                        ;
;---------------------------------------------------------------;
MainGameNormal: ld a, GF_START_GAME + GF_PLAY_MODE  ; choose start & normal game
                call SetGameFlag                    ; set the flags
                jr MainMenuRet

;---------------------------------------------------------------;
; MainGameTimed                                                 ;
;   Setups a timed game                                         ;
;---------------------------------------------------------------;
MainGameTimed:  ld a, GF_START_GAME
                call SetGameFlag
                ld a, GF_PLAY_MODE
                call ResetGameFlag
                jr MainMenuRet
                
;---------------------------------------------------------------;
; MainMenuCont                                                  ;
;   Continues the game currently being played                   ;
;---------------------------------------------------------------;
MainMenuCont:   ld a, (GameFlags)                   ; get game flags
                and GF_PLAYING                      ; are we playing a game?
                jr z, MM_Lp1                        ; no, then return to menu
                jr MainMenuRet

;---------------------------------------------------------------;
; MenuQuit                                                      ;
;   Sets the QUIT game flag                                     ;
;---------------------------------------------------------------;
MenuQuit:       ld a, GF_QUIT
                call SetGameFlag
                call ISR_Stop
                ld a, 7
                call 8859           ; set border colour to white
                jp MainMenuRet

;---------------------------------------------------------------;
; Credits                                                       ;
;   Show the Credits Window                                     ;
;---------------------------------------------------------------;
CreditsWindow:  ld a, 79
                call WindowSetColor
                ld b, 144
                ld c, 0
                ld d, 5
                ld e, 32
                call WindowOpen
                
                ld hl,CreditsMenu_0
                ld de,CredMenu_0_Txt
                ld a,0
                call ShowMenu
                ret
                
;---------------------------------------------------------------;
; MenuControl                                                   ;
;   Executes the Control sub-menu                               ;
;---------------------------------------------------------------;
MenuControl:    call EraseMenuPtr
                ld b, 64
                ld c, 96
                ld d, 9
                ld e, 18
                call WindowOpen

                ld hl,ControlMenu_0
                ld de,CtrlMenu_0_Txt
                ld a, (ControlFlags)
                call ShowMenu
                
                ld hl,MC_Lp1
                ld (CCRtn_Addr+1),hl
                
MC_Lp1:         call MoveMenuCursor
                ld ix,CtrlMenu_Rect
                jp CheckCursorPos

MC_Keys:        ld a, CF_KEYBOARD
MC_End:         ld (ControlFlags), a
MC_Back:        call MenuPause
                call WindowClose
                call RefreshPtrBuf
                jp MM_Lp1 ; return to main loop

MC_Intf_II:     ld a, CF_INTERFACE_II
                jr MC_End

MC_Kemp:        ld a, CF_KEM_JOYSTICK
                jr MC_End

MC_Mouse:       ld a, CF_KEM_MOUSE
                jr MC_End

;---------------------------------------------------------------;
; MenuMusic                                                     ;
;   Executes the Music sub-menu                                 ;
;---------------------------------------------------------------;
MenuMusic:      call EraseMenuPtr
                ld b, 72
                ld c, 96
                ld d, 8
                ld e, 19
                call WindowOpen

                ld hl,MusicMenu_0
                ld de,MusMenu_0_Txt
                ld a,(MusicFlags)
                call ShowMenu
                
                ld hl,MMS_Lp1
                ld (CCRtn_Addr+1),hl
                
MMS_Lp1:        call MoveMenuCursor
                ld ix,MusMenu_0_Rect
                jp CheckCursorPos

MMS_Theme1:     ld a, GF_THEME_1
                ld (MusicFlags), a
                ld hl, TUNE_A
MMS_End:        ld (GameTune), hl
MMS_Back:       call MenuPause
                call WindowClose
                call RefreshPtrBuf
                jp MM_Lp1  ; return to main menu loop

MMS_Theme2:     ld a, GF_THEME_2
                ld (MusicFlags), a
                ld hl, TUNE_B
                jr MMS_End

MMS_Theme3:     ld a, GF_THEME_3
                ld (MusicFlags), a
                ld hl, TUNE_C
                jr MMS_End

;---------------------------------------------------------------;
; MenuGraphics                                                  ;
;   Executes the Graphics sub-menu                              ;
;---------------------------------------------------------------;
MenuGraphics:   call EraseMenuPtr
                ld b, 40-16
                ld c, 96
                ld d, 19
                ld e, 18
                call WindowOpen

                xor a
                ld hl, Tile0
                ld c, 120
                ld b, 56
                call DrwTile
                xor a
                ld hl, Tile3
                ld c, 144
                ld b, 56
                call DrwTile
                ld hl, Tile4
                ld c, 168
                ld b, 56
                call DrwTile
                ld hl, Tile5
                ld c, 192
                ld b, 56
                call DrwTile
                xor a
                ld hl, Tile11
                ld c, 120
                ld b, 96
                call DrwTile
                xor a
                ld hl, Tile15
                ld c, 144
                ld b, 96
                call DrwTile
                ld hl, Tile12
                ld c, 168
                ld b, 96
                call DrwTile
                ld hl, Tile14
                ld c, 192
                ld b, 96
                call DrwTile
                xor a
                ld hl, Tile20
                ld c, 120
                ld b, 136
                call DrwTile
                xor a
                ld hl, Tile21
                ld c, 144
                ld b, 136
                call DrwTile
                ld hl, Tile26
                ld c, 168
                ld b, 136
                call DrwTile
                ld hl, Tile23
                ld c, 192
                ld b, 136
                call DrwTile

                ld hl,GraphicsMenu_0
                ld de,GrphMenu_0_Txt
                ld a,(GemTheme)
                call ShowMenu
                
                ld hl,MG_Lp1
                ld (CCRtn_Addr+1),hl
                
MG_Lp1:         call MoveMenuCursor
                ld ix,GrphMenu_0_Rect
                jp CheckCursorPos

MG_Theme1:      ld a, GF_THEME_1
MG_End:         ld (GemTheme), a
MG_Back:        call MenuPause
                call WindowClose
                call RefreshPtrBuf
                jp MM_Lp1 ; return to main menu loop

MG_Theme2:      ld a, GF_THEME_2
                jr MG_End

MG_Theme3:      ld a, GF_THEME_3
                jr MG_End
                
;---------------------------------------------------------------;
; MenuHighScore                                                 ;
;   Executes the HighScore sub-menu                             ;
;---------------------------------------------------------------;
MenuHighScore:  call EraseMenuPtr
                ld b, 24
                ld c, 72
                ld d, 15
                ld e, 21
                call WindowOpen

                call DisplayHiScore
                
                ld hl,HiScoreMenu_0
                ld de,HiSMenu_0_Txt
                ld a,0
                call ShowMenu
                
                ld hl,MHS_Lp1
                ld (CCRtn_Addr+1),hl
                
MHS_Lp1:        call MoveMenuCursor
                ld ix,HiSMenu_0_Rect
                jp CheckCursorPos


MHS_Close:      call MenuPause
                call WindowClose
                call RefreshPtrBuf
                jp MM_Lp1 ; return to main menu loop

;---------------------------------------------------------------;
; MenuQuit                                                      ;
;   Executes the Quit verification sub-menu                     ;
;---------------------------------------------------------------;
MenuQuitVerify: call EraseMenuPtr
                ld b, 48
                ld c, 72
                ld d, 6
                ld e, 21
                call WindowOpen

                ld hl,QuitMenu_0
                ld de,QuitMnu_0_Txt
                ld a,0
                call ShowMenu

                ld hl,MQ_Lp1
                ld (CCRtn_Addr+1),hl

MQ_Lp1:         call MoveMenuCursor
                ld ix,QuitMnu_0_Rect
                jp CheckCursorPos

MQ_Close:       call MenuPause
                call WindowClose
                call RefreshPtrBuf
                jp MM_Lp1 ; return to main menu loop
                
;---------------------------------------------------------------;
; CheckCursorPos                                                ;
;                                                               ;
;   Checks to see if the pointer is located within a menus text ;
;   rectangle. If it is and "fire" has been pressed, it will    ;
;   jump to the menu items callback address                     ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         4th July 2006                               ;
;   Last Changed    4th July 2006                               ;
;                                                               ;
;   Inputs                                                      ;
;       ix = Start of a menu tables rect section                ;
;                                                               ;
;   Outputs                                                     ;
;       If pointer in rectangle and "fire" is pressed this      ;
;       function will not exit but control will be passed to    ;
;       address defined in the menu items callback              ;
;                                                               ;
;   Regs Used                                                   ;
;       af, bc, de, hl, ix                                      ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, bc, de, hl, ix                                      ;
;---------------------------------------------------------------;

CheckCursorPos: ld b,(ix+0)     ; b = the number of menu sub items
                inc ix
ChkCurPosLoop:  jp IsPtrInRect  ; check to see if pointer is in the texts rectangle
PtrRectRtn:     ld de,7         ; pointer may have been in rect but fire wasn't pressed
                add ix,de       ; move to the next rectangle in the table
                djnz ChkCurPosLoop
                
                ld a,CF_ACTION
                cpl
                ld b,a
                ld a,(CursorFlags)
                and b              ; clear the action flag so we don't get any
                ld (CursorFlags),a ; false triggers when moving into a rectangle
                
CCRtn_Addr:     jp 0               ; the jp address is set dynamically

IsPtrInRect:    ld a,(PointerPos)  ; if pointer isn't in the rectangle then exit
                cp (ix+0)
                jp c,PtrNotInRect
                cp (ix+2)
                jp nc,PtrNotInRect
                ld a,(PointerPos+1)
                cp (ix+1)
                jp c,PtrNotInRect
                cp (ix+3)
                jp nc,PtrNotInRect
                
                ld a,(ix+5)         ; if callback addr is zero then exit
                and a               ; and don't show the menu highlight
                jp z,PtrRectRtn
                                    ; We are in a rect
                ld a, (CursorFlags) ; see if fire button pressed
                and CF_ACTION
                jp z,InRectExit     ; fire is not pressed so exit

                ld a,0              ; clear movement and action flags
                ld (CursorFlags), a

                call IndicateMnuSel ; show some feedback that an item has been 'clicked'

                ld h,(ix+5)  ; load hl with the callback address
                ld l,(ix+4)
                jp (hl)      ; jump to the menu items callback function

InRectExit:     ld a,74  ; this is the colour for the menu high light
                call MenuHighLight
                jp PtrRectRtn
                
PtrNotInRect:   ld a,77  ; this is the 'normal' menu item colour
                call MenuHighLight
                jp PtrRectRtn

;---------------------------------------------------------------;
; MenuHighLight                                                 ;
;                                                               ;
;   Sets the colour of a menu item                              ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         4th July 2006                               ;
;   Last Changed    7th July 2006                               ;
;                                                               ;
;   Inputs                                                      ;
;       a  = the colour of the menu item                        ;
;       ix = start address of a menu items rectangle values     ;
;                                                               ;
;   Outputs                                                     ;
;       Sets the colour of a menu item                          ;
;                                                               ;
;   Regs Used                                                   ;
;       af, bc, de, hl, ix                                      ;
;                                                               ;
;   Regs destroyed                                              ;
;       f, hl                                                   ;
;---------------------------------------------------------------;
MenuHighLight:  push bc
                push af
                ld b,(ix+1)
                ld c,(ix+0)
                call CoordAttr
                ld a,(ix+2)
                sub (ix+0)
                srl a
                srl a
                srl a
                ld b,a
                pop af
HighLightLoop:  ld (hl),a
                inc hl
                djnz HighLightLoop
                pop bc
                ret

;---------------------------------------------------------------;
; IndicateMnuSel                                                ;
;                                                               ;
;   Flashes a menu item                                         ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         4th July 2006                               ;
;   Last Changed    7th July 2006                               ;
;                                                               ;
;   Inputs                                                      ;
;       ix = start address of a menu items rectangle values     ;
;                                                               ;
;   Outputs                                                     ;
;       Menu item flashes several times and then returns to     ;
;       the normal menu item colour                             ;
;                                                               ;
;   Regs Used                                                   ;
;       af, bc, de, hl, ix                                      ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, b, hl                                               ;
;---------------------------------------------------------------;
IndicateMnuSel: ld b,3              ; how long to flash for
IndMnuSelLp:    push bc
                ld a,79             ; this is the colour for the menu high light
                call MenuHighLight
                call Pause          ; pause so we can see the effect
                call Pause
                ld a,77             ; this is the 'normal' menu item colour
                call MenuHighLight
                call Pause          ; pause so we can see the effect
                pop bc
                djnz IndMnuSelLp
                ret

;---------------------------------------------------------------;
; ShowMenu                                                      ;
;                                                               ;
;   Displays all the menu items from a given menu table         ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         4th July 2006                               ;
;   Last Changed    10th July 2006                              ;
;       Added code to show defalt menu item                     ;
;                                                               ;
;   Inputs                                                      ;
;       a  = default menu item flag (0 if not used              ;
;       hl = start address of a menu table                      ;
;       de = start address of menu table text block             ;
;   Outputs                                                     ;
;       A menu's text will be displayed                         ;
;                                                               ;
;   Regs Used                                                   ;
;       af, af', bc, de, hl, ix                                 ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, af', bc, de, hl                                     ;
;---------------------------------------------------------------;
ShowMenu:       ex af,af'
                call ShowMenuTitle   ; draw the menu's title
                ld b,(hl)
ShowMenuLoop:   push bc   ; get the number of menu items to draw
                inc hl
                ld c,(hl) ; c = x
                inc hl
                ld b,(hl) ; b = y

                inc hl    ; move past the remainder or the rectangle
                inc hl    ; and callback function address
                inc hl    ;
                inc hl    ;
                inc hl
                ld a,(hl) ; get ID flag

                push hl
                push de   ; store text
                ex de,hl
                push af
                call Pix  ; convert x,y into an address
                pop af
                ex de,hl  ; de = screen address
                pop hl    ; hl = text to draw

                call ShowAsDefault
                call PrintLine ; draw the text
                inc hl
                ex de,hl
                pop hl
                pop bc
                djnz ShowMenuLoop
                call RefreshPtrBuf  ; as the background has changed we need to
                ret                 ; reload the pointers stored background data

ShowAsDefault:  cp 0               ; if 0 then no default item so return
                ret z
                ld b,a
                ex af,af'
                cp b
                jp nz, ShowDefExit  ; menu item ID <> default item so return

                push hl
                push de
                dec de
                ld hl,DefaultCursor
                call PrintLine      ; draw '>' next to current default item
                pop de
                pop hl
                ret
ShowDefExit:    ex af,af'
                ret
;---------------------------------------------------------------;
; ShowMenuTitle                                                 ;
;   Draws a Menus title                                         ;
;---------------------------------------------------------------;
 ShowMenuTitle: push de
                ld e,(hl)      ; get the screen address of the menu title
                inc hl
                ld d,(hl)
                inc hl
                call PrintLine ; draw the menu title
                inc hl
                pop de
                ret
                
;---------------------------------------------------------------;
; MenuPause                                                     ;
;   Executes a generic long pause                               ;
;---------------------------------------------------------------;
MenuPause:      ld b, 5
MenuPause_Lp:   call Pause
                djnz MenuPause_Lp
                ret

;---------------------------------------------------------------;
; RefreshPtrBuf                                                 ;
;   Saves the background behind the pointer                     ;
;---------------------------------------------------------------;
RefreshPtrBuf:  ld bc, (PointerPos)
                call SavePointer
                ret
                
;---------------------------------------------------------------;
; EraseMenuPtr                                                  ;
;   Removes the pointer by restoring its background             ;
;---------------------------------------------------------------;
EraseMenuPtr:   push hl
                push de
                ld bc, (PointerPos)
                call ErasePointer
                pop de
                pop hl
                ret
                
;---------------------------------------------------------------;
; MoveMenuCursor                                                ;
;                                                               ;
;   Moves the cursor when the menus are in use                  ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         5th July 2006                               ;
;   Last Changed    7th July 2006                               ;
;        Added a call to UpdateCursor                           ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
;                                                               ;
;   Outputs                                                     ;
;       position of pointer is updated                          ;
;                                                               ;
;   Regs Used                                                   ;
;       af, af', bc, de, hl                                     ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, af', bc, de, hl                                     ;
;---------------------------------------------------------------;

MoveMenuCursor: ld bc, (PointerPos)     ; get the pointer position
                call ErasePointer       ; erase the old pointer
                ld a, (ControlFlags)    ; read the correct input device
                and CF_KEYBOARD         ; to update the pointer position
                call nz, ReadKeyboard
                ld a, (ControlFlags)
                and CF_INTERFACE_II
                call nz, ReadInterface2
                ld a, (ControlFlags)
                and CF_KEM_JOYSTICK
                call nz, ReadKempJoystick
                ld a, (ControlFlags)
                and CF_KEM_MOUSE
                call nz, ReadKempMouse
                call MoveCursor         ; move pointer to new location
                call UpdateCursor       ; restrict the y position of the cursor
                ld bc, (PointerPos)     ; get the pointer position
                call DrawPointer        ; draw the poinet in the new position
                halt                    ; small delay else the pointer moves
                halt                    ; about too fast
                ret
                
;---------------------------------------------------------------;
; Menu tables                                                   ;
;   The menu text strings                                       ;
;---------------------------------------------------------------;

;-----------------------------------------------------------------------;
; Menu Table                                                            ;
;                                                                       ;
; Each table is stored as follows:                                      ;
; Title Address = 2 bytes                                               ;
; Title Colour = 1 byte                                                 ;
; Title = As required                                                   ;
; EOL char = 1 byte (must be set to $ff)                                ;
; Item Count = 1 byte (set to the number of menu sub items)             ;
; Item Rectangle = 4 bytes (left, top, right, bottom)                   ;
; Item Callback Address = 2 bytes (set to 0 if not required)            ;
; Item ID flag = 1 byte, used when its the currently selected menu item ;
; Repeat Item Rectangle and Callback as required (see Item Count)       ;
; Item Colour = 1 byte (colour is overridden by 'CheckCursorPos')       ;
; Item Text = As required                                               ;
; EOL char = 1 byte (must be set to $ff)                                ;
; Repeat Item Colour, Text and EOL as required (see Item Count)         ;
;-----------------------------------------------------------------------;

; Credits Menu

CreditsMenu_0:  defw 20588      ; title address
                defb 79         ; title colour
                defm "Credits"  ; title
                defb $ff        ; EOL
CredMenu_0_Rect defb 3          ; item count
                defb 16, 160, 232, 168  ; item 1 rectangle
                defw 0                  ; item 1 callback function address
                defb 0                  ; item 1 ID flag (set to 0 if not used)
                defb 16, 168, 200, 176  ; item 2 rectangle
                defw 0                  ; item 2 callback function address
                defb 0                  ; item 2 ID flag (set to 0 if not used)
                defb 16, 176, 144, 184  ; item 3 rectangle
                defw 0                  ; item 3 callback function address
                defb 0                  ; item 3 ID flag (set to 0 if not used)
CredMenu_0_Txt: defb 78                              ; item 1 colour
                defm "Program : Kiwi + RetroCoder"   ; item 1 text
                defb $ff                             ; item 1 EOL
                defb 78                              ; item 2 colour
                defm "Graphics: Sadako + Kiwi"       ; item 2 text
                defb $ff                             ; item 2 EOL
                defb 78                              ; item 3 colour
                defm "Music   : Lee_Dc"              ; item 3 text
                defb $ff                             ; item 3 EOL

; Main Menu

MainMenu_0:     defw 16495
                defb 79
                defm "Game Menu"
                defb $ff
MainMenu_0_Rect defb 8
                defb 104, 40, 192, 48
                defw MainGameNormal
                defb 0
                defb 104, 48, 184, 56
                defw MainGameTimed
                defb 0
                defb 104, 56, 168, 64
                defw MenuControl
                defb 0
                defb 104, 64, 144, 72
                defw MenuMusic
                defb 0
                defb 104, 72, 168, 80
                defw MenuGraphics
                defb 0
                defb 104, 80, 208, 88
                defw MainMenuCont
                defb 0
                defb 104, 88, 192, 96
                defw MenuHighScore
                defb 0
                defb 104, 96, 136, 104
                defw MenuQuitVerify
                defb 0
MainMenu_0_Txt: defb 77
                defm "Normal Game"
                defb $ff
                defb 77
                defm "Timed Game"
                defb $ff
                defb 77
                defm "Controls"
                defb $ff
                defb 77
                defm "Music"
                defb $ff
                defb 77
                defm "Graphics"
                defb $ff
                defb 77
                defm "Continue Game"
                defb $ff
                defb 77
                defm "View Scores"
                defb $ff
                defb 77
                defm "QUIT"
                defb $ff

; Control Menu

ControlMenu_0:  defw 18481
                defb 79
                defm "Controls"
                defb $ff
CtrlMenu_Rect   defb 5
                defb 120, 88, 184, 94
                defw MC_Keys
                defb CF_KEYBOARD
                defb 120, 96, 216, 104
                defw MC_Intf_II
                defb CF_INTERFACE_II
                defb 120, 104, 184, 112
                defw MC_Kemp
                defb CF_KEM_JOYSTICK
                defb 120, 112, 208, 120
                defw MC_Mouse
                defb CF_KEM_MOUSE
                defb 120, 128, 192, 136
                defw MC_Back
                defb 0
CtrlMenu_0_Txt: defb 77
                defm "Keyboard"
                defb $ff
                defb 77
                defm "Interface II"
                defb $ff
                defb 77
                defm "Kempston"
                defb $ff
                defb 77
                defm "Kemp. Mouse"
                defb $ff
                defb 77
                defm "Main Menu"
                defb $ff
; Graphics Menu

GraphicsMenu_0: defw 16529
                defb 79
                defm "Graphics"
                defb $ff
GrphMenu_0_Rect defb 4
                defb 120, 48, 216, 56
                defw MG_Theme1
                defb GF_THEME_1
                defb 120, 88, 168, 96
                defw MG_Theme2
                defb GF_THEME_2
                defb 120, 128, 176, 136
                defw MG_Theme3
                defb GF_THEME_3
                defb 120, 168, 192, 208
                defw MG_Back
                defb 0
GrphMenu_0_Txt: defb 77
                defm "TommyGun Art"
                defb $ff
                defb 77
                defm "Gems I"
                defb $ff
                defb 77
                defm "Gems II"
                defb $ff
                defb 77
                defm "Main Menu"
                defb $ff
; Music Menu

MusicMenu_0:    defw 18515
                defb 79
                defm "Music"
                defb $ff
MusMenu_0_Rect  defb 4
                defb 120, 96, 224, 104
                defw MMS_Theme1
                defb GF_THEME_1
                defb 120, 104, 216, 112
                defw MMS_Theme2
                defb GF_THEME_2
                defb 120, 112, 192, 120
                defw MMS_Theme3
                defb GF_THEME_3
                defb 120, 128, 192, 136
                defw MMS_Back
                defb 0
MusMenu_0_Txt:  defb 77
                defm "Rock 'n' Roll"
                defb $ff
                defb 77
                defm "Funky Monkey"
                defb $ff
                defb 77
                defm "Classical"
                defb $ff
                defb 77
                defm "Main Menu"
                defb $ff
; High Score Menu

HiScoreMenu_0:  defw 16523
                defb 79
                defm "High Score Table"
                defb $ff
HiSMenu_0_Rect: defb 1
                defb 88, 136, 184, 144
                defw MHS_Close
                defb 0
HiSMenu_0_Txt:  defb 77
                defm "Main Menu"
                defb $ff
; Quit verification Menu

QuitMenu_0:     defw 16523+96
                defb 79
                defm "Exit Gem Machine?"
                defb $ff
QuitMnu_0_Rect: defb 2
                defb 88, 72, 88+24, 72+8
                defw MenuQuit
                defb 0
                defb 88, 72+8, 88+16, 72+16
                defw MQ_Close
                defb 0
QuitMnu_0_Txt:  defb 77
                defm "Yes"
                defb $ff
                defb 77
                defm "No"
                defb $ff

; This data is used to show which menu item is the current 'default'
DefaultCursor:  defb 78
                defm ">"
                defb $ff
                
GameOverTxt1:   defb 120, 40
                defb 64 + 8 + 7
                defm "Game Over"
                defb 255
                
GameOverTxt2:   defb 88, 64
                defb 64 + 8 + 7
                defm "There are no moves"
                defb 255

GameOverTxt3:   defb 88, 72
                defb 64 + 8 + 7
                defm "left to make.     "
                defb 255

GameOverTxt4:   defb 112, 88
                defb 64 + 8 + 7
                defm "Press Space"
                defb 255
                