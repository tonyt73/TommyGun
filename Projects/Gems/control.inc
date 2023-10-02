;---------------------------------------------------------------;
;                                                               ;
;   Control.inc                                                 ;
;                                                               ;
;   This file contains routines for dealing with the control    ;
;   of the Game cursor using either the keyboard, Interface II  ;
;   joystick, Kempston Joystick or the Kempston Mouse           ;
;                                                               ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; MoveGameCursor                                                ;
;                                                               ;
; Reads the current input device which is either the            ;
;    Keyboard                                                   ;
;    Interface Joysticks or                                     ;
;    Kempston joystick and the                                  ;
;    Kempston Left Mouse Button (movement is done directly)     ;
; Then moves the arrow pointer on the screen and execute any    ;
; appropreiate action if needed                                 ;
;                                                               ;
;---------------------------------------------------------------;
MoveGameCursor: ld bc, (PointerPos)     ; get the mouse pointer position
                call ErasePointer       ; erase the old pointer
                ld a, (ControlFlags)
                and CF_KEYBOARD
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
                call MoveCursor
                call UpdateCursor
                call DrawPointer
                halt
                ld a, (CursorFlags)
                and CF_ACTION
                call nz, MoveAction     ; if set then yes, so do the action command
                ld bc, (PointerPos)
                call DrawGemCursor      ; draw the gem board cursor
                ret

;---------------------------------------------------------------;
; MoveCursor                                                    ;
;                                                               ;
; Applies the movement from the current input device            ;
; Either the                                                    ;
;    Keyboard                                                   ;
;    Interface Joysticks or                                     ;
;    Kempston joystick and the                                  ;
;    Kempston Left Mouse Button (movement is done directly)     ;
;                                                               ;
;---------------------------------------------------------------;
MoveCursor:     ld a, (CursorFlags)
                ld bc, (PointerPos)
                and CF_LEFT
                call nz, MoveLeft
                ld a, (CursorFlags)
                and CF_RIGHT
                call nz, MoveRight
                ld a, (CursorFlags)
                and CF_UP
                call nz, MoveUp
                ld a, (CursorFlags)
                and CF_DOWN
                call nz, MoveDown
                ld (PointerPos), bc
                ld a, (CursorFlags)
                and CF_ACTION
                ld (CursorFlags), a
                ret
                
;---------------------------------------------------------------;
; MoveXXX                                                       ;
;                                                               ;
; Moves the cursor position                                     ;
;                                                               ;
;---------------------------------------------------------------;
MoveUp:         ld a, b
                and 252
                ret z
                sub 4
                ld b, a
                ret

MoveDown:       ld a, b
                and 252
                cp 180
                ret z
                add a, 4
                ld b, a
                ret

MoveRight:      ld a, c
                and 252
                cp 248
                ret z
                add a, 4
                ld c, a
                ret

MoveLeft:       ld a, c
                and 252
                ret z
                sub 4
                ld c, a
                ret
                
;---------------------------------------------------------------;
; MoveAction                                                    ;
;                                                               ;
; Provides the action handler for when the player presses FIRE  ;
; button or the left mouse button                               ;
;                                                               ;
;---------------------------------------------------------------;
MoveAction:     ld a, (CursorFlags)         ; get cursor flags
                and CF_ACTION               ; is action pressed
                ret z                       ; no, so return
                ld a, (CursorFlags)         ; yes, then
                xor CF_ACTION               ; reset the action bit
                ld (CursorFlags), a         ; and store the result
                call CheckButtons           ; has menu or quit being clicked?
                ret c                       ; return if clicked
                call CalcGridPos            ; get the new cursor position (bc)
                ld hl, (CursorPosOld)       ; get the old position in hl
                ld e, 1                     ; use e to indicate swap direction(s) default is up
                ld a, h                     ; get old Y
                sub b                       ; sub new Y
                cp 24                       ; is oldY - newY = -24? ie 1 position UP
                jr z, MA_CheckX             ; yes, then check x diff is zero
                sla e                       ; move to down
                cp -24                      ; is oldY - newY = 24? ie 1 position DOWN
                jr z, MA_CheckX             ; yes, then check x diff is zero
                sla e                       ; move to left
                ld a, l                     ; get old X
                sub c                       ; sub new Y
                cp 24                       ; is oldX - newX = -24? ie. 1 position LEFT
                jr z, MA_CheckY             ; yes, then check y diff is zero
                sla e                       ; move to right
                cp -24                      ; is oldX - newX = 24? ie. 1 position RIGHT
                jr z, MA_CheckY             ; yes, then check y diff is zero
MA_End:         xor a                       ; no swaps, so
                ld (SwapFlags), a           ; reset the swap flags
                call DrawGemCursor          ; and redraw the cursor
                ret                         ; done for now

MA_CheckX:      ld a, l                     ; get old x
                sub c                       ; sub new x
                jr nz, MA_End               ; if not zero, then up/down swap is illegal
MA_CheckEnd:    ld a, e                     ; doing up/down swap
                ld (SwapFlags), a           ; so set the flags
                call ActionSwap             ; swap is legal, so do the swap
                ret
                
MA_CheckY:      ld a, h                     ; get old y
                sub b                       ; sub new y
                jr nz, MA_End               ; if not zero, then left/right swap is illegal
                jr MA_CheckEnd              ; continue to action swap


;---------------------------------------------------------------;
; SetMoveXXX                                                    ;
;                                                               ;
; Sets the cursor flags for the given direction or action       ;
;                                                               ;
;---------------------------------------------------------------;
SetMoveUp:      push af                     ; save af
                ld b, CF_UP                 ; set the up bit
SetMove:        ld a, (CursorFlags)         ; get the cursor flags
                or b                        ; merge in the direction bit
                ld (CursorFlags), a         ; save the cursor flags
                pop af                      ; restore af
                ret                         ; done

SetMoveDown:    push af                     ; save af
                ld b, CF_DOWN               ; set the down bit
                jr SetMove                  ; continue with setting the flags

SetMoveLeft:    push af                     ; save af
                ld b, CF_LEFT               ; set the left bit
                jr SetMove                  ; continue with setting the flags

SetMoveRight:   push af                     ; save af
                ld b, CF_RIGHT              ; set the right bit
                jr SetMove                  ; continue with setting the flags

SetMoveAction:  push af                     ; save af
                ld b, CF_ACTION             ; set the action bit
                jr SetMove                  ; continue with setting the flags


;---------------------------------------------------------------;
; UpdateCursor                                                  ;
;                                                               ;
; Restricts the y position of the cursor to by less than 180    ;
;                                                               ;
;---------------------------------------------------------------;
UpdateCursor:   ld a, b                 ; get the y coord
                add a, 72               ; is it less than 184 (adding 72 will cause an overflow/carry)
                ret nc                  ; if no carry then less than 180
                ld b, 180               ; restrict to 180
                ld (PointerPos), bc     ; save the clamped y position
                ret


;---------------------------------------------------------------;
; ReadKeyboard                                                  ;
;                                                               ;
; Reads the Keyboard                                            ;
;  Q-T -> UP                                                    ;
;  A-G -> DOWN                                                  ;
;  PIY -> RIGHT                                                 ;
;  OU  -> LEFT                                                  ;
; Sp-B -> ACTION                                                ;
;                                                               ;
;---------------------------------------------------------------;
ReadKeyboard:   ld bc, 64510
                in a, (c)
                cpl
                and 31
                call nz, SetMoveUp
                ld bc, 65022
                in a,(c)
                cpl
                and 31
                call nz, SetMoveDown
                ld bc, 57342
                in a, (c)
                cpl
                ld c, a
                and 21
                call nz, SetMoveRight
                ld a, c
                and 42
                call nz, SetMoveLeft
                ld bc, 32766
                in a, (c)
                cpl
                and 31
                call nz, SetMoveAction
                ret

;---------------------------------------------------------------;
; ReadInterface2                                                ;
;                                                               ;
; Reads the Interface II joystick, Port 1 & 2                   ;
;                                                               ;
;---------------------------------------------------------------;
ReadInterface2: ld bc, 61438            ; read interface II port 2
                in a, (c)
                bit 1, a
                call z, SetMoveUp
                bit 2, a
                call z, SetMoveDown
                bit 3, a
                call z, SetMoveRight
                bit 4, a
                call z, SetMoveLeft
                bit 0, a
                call z, SetMoveAction
                ld bc, 63486            ; read interface II port 1
                in a, (c)
                bit 0, a
                call z, SetMoveLeft
                bit 1, a
                call z, SetMoveRight
                bit 2, a
                call z, SetMoveDown
                bit 3, a
                call z, SetMoveUp
                bit 4, a
                call z, SetMoveAction
                ret

;---------------------------------------------------------------;
; ReadKempJoystick                                              ;
;                                                               ;
; Reads the Kempston joystick                                   ;
;                                                               ;
; Reading from port 0x1f returns the current state of the       ;
; Kempston joystick in the form 000FUDLR, with active bits high ;                                                   ;
;---------------------------------------------------------------;
ReadKempJoystick:
                ld bc, 31
                in a, (c) ; read the kempston joystick data from port 31
                bit 0, a
                call nz, SetMoveRight
                bit 1, a
                call nz, SetMoveLeft
                bit 2, a
                call nz, SetMoveDown
                bit 3, a
                call nz, SetMoveUp
                bit 4, a
                call nz, SetMoveAction
                ret

;---------------------------------------------------------------;
; ReadKempMouse                                                 ;
;                                                               ;
; Reads the Kempston mouse                                      ;
;                                                               ;
;---------------------------------------------------------------;
ReadKempMouse:  ld bc, 64479            ; read the mouse x axis
                in a, (c)               ; get the x axis value
                ld e, a                 ; save in e reg
                ld bc, 65503            ; read the mouse y axis
                in a, (c)               ; get the y axis value
                ld d, a                 ; save in the d reg
                ld a, 255               ; invert the y axis value
                sub d                   ; do inversion
                ld d, a                 ; save the result in d
                ld bc, 64223            ; read the mouse buttons
                in a, (c)               ; get the button values
                and CF_MOUSE_LEFT       ; check the left mouse button
                call z, SetMoveAction   ; set action if left mouse button pressed
                ld b, d                 ; put y value in b
                ld c, e                 ; put x value in c
                ld (PointerPos), bc
                ret                     ; done


;---------------------------------------------------------------;
; CheckButtons                                                  ;
;                                                               ;
; Checks to see if the on screen MENU buttons have been clicked ;
; on by the cursor                                              ;
;                                                               ;
;---------------------------------------------------------------;
CheckButtons:   ld de, (PointerPos)
                srl d
                srl d
                srl d                   ; divide y / 8
                srl e
                srl e
                srl e                   ; divide x / 8
                ld a, e                 ; get x coord
                cp 1                    ; < 1?
                ret c                   ; carry set if < 1
                cp 7                    ; < 6?
                ret nc                  ; finished if > 6
                                        ; check the Menu button
                ld a, d                 ; get the y coord
                cp 18
                ret c                   ; carry set if < 18
                cp 20                   ; ok, > 18 but < 20?
                ret nc
                ld a, GF_MENU           ; menu button clicked
                call SetGameFlag
                scf
                ret

CalcGridPos:    ld bc, (PointerPos)     ; get the pointer position
                ld a, c                 ; get x position
                sub 64                  ; is it less than 64
                jr c, CGPSkip           ; yes, then grid cursor position not changed
                ld c, a                 ; save the adjusted x position
                ld a, b                 ; get y position
                add a, 40               ; is it less than 192?
                jr c, CGPSkip           ; no, so grid cursor position is not changed
                ld a, c                 ; get the x position
                call Snap24             ; snap to 24 pixel grid
                add a, 64               ; add the width of the score panel
                ld c, a                 ; save the grid snapped x position
                ld a, b                 ; get the y position
                call Snap24             ; snap to 24 pixel grid
                ld b, a                 ; save the snapped grid position
                ld (CursorPos), bc      ; save the snapped grid coordinates
                ret                     ; done
CGPSkip         ld bc, (CursorPos)      ; use the current cursor position
                ret                     ; done

;---------------------------------------------------------------;
; DrawGemCursor                                                 ;
;                                                               ;
; Draws the Gem board Cursor                                    ;
;                                                               ;
;---------------------------------------------------------------;
DrawGemCursor:  ld a, (CursorLive)
                and a
                jr nz, DCIsLive
                or 1
                ld (CursorLive), a
                ld bc, (CursorPosOld)
                jr DrawCursorDo
DCIsLive:       ld bc, (CursorPos)
                ld hl, (CursorPosOld)
                sbc hl, bc
                ret z
                ld bc, (CursorPosOld)
                call DrawCursorDo
                ld bc, (CursorPos)
                ld (CursorPosOld), bc
DrawCursorDo:   call CoordAttr
                inc hl
                inc hl
                call ChangePaper
                dec hl
                call ChangePaper
                dec hl
                call ChangePaper
                ld de, 32
                add hl, de
                call ChangePaper
                add hl, de
                call ChangePaper
                inc hl
                call ChangePaper
                inc hl
                call ChangePaper
                sbc hl, de
                call ChangePaper
                dec hl
                call ChangePaper
                ret

EraseGameCursor:
                ld bc, (CursorPos)
                jr DrawCursorDo

;---------------------------------------------------------------;
; ChangePaper                                                   ;
;                                                               ;
; Swaps the paper and ink colours at the attr address in hl     ;
;                                                               ;
;---------------------------------------------------------------;
ChangePaper:    ld a, (hl)
                ld c, a
                and 7
                sla a
                sla a
                sla a
                ld b, a
                ld a, c
                and 56
                sra a
                sra a
                sra a
                or b
                or 64
                ld (hl), a
                ret


;---------------------------------------------------------------;
; WaitForSpace                                                  ;
;   wait for space key to be pressed                            ;
;---------------------------------------------------------------;
WaitForSpace:   ld bc, 32766           ; check keys from Space-B
                in a, (c)              ; get keys
                bit 0, a               ; if space pressed
                jr nz, WaitForSpace    ; no, then check again
                ret                    ; yes, return to caller

