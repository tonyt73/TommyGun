;------------------------------------------------------------------------------;
;  Caret_draw.inc                                                              ;
;  Contains routines to draw the caret (cursor)                                ;
;------------------------------------------------------------------------------;


; draws the mouse caret at the given position
; a faster way would probably be to use preshifted carets/masks

MAX_X_POS equ 250
MAX_Y_POS equ 182

Cursor:     defb 0      ; + 0 The currently selected Caret
                        ; 0 - arrow, 1 - wait, 2 - text
CursorX:    defb 128    ; + 1 x position
CursorY:    defb 96     ;     y position
CursorOldX: defb 128    ; + 3 old x position  
CursorOldY: defb 96     ;     old y position

; Space to save the current caret background
Caret_BG:
DEFS 40

CursorHide: halt
            push bc
            push de
            push hl
            ld bc, (CursorOldX)
            call Pix
            ld de, Caret_BG
            ld b, 10
CE_L1:      ld a, (de)
            ld (hl), a
            inc l
            inc de            
            ld a, (de)
            ld (hl), a
            dec l
            inc de
            call Incy
            djnz CE_L1
            pop hl
            pop de
            pop bc
            ret
            
; save the background where the caret would be drawn
CursorSave: push bc
            push de
            push hl
            ld bc, (CursorX)
            ld (CursorOldX), bc
            call Pix
            ld de, Caret_BG
            ld b, 10
CS_L1:      ld a, (hl)
            ld (de), a
            inc de
            inc l
            ld a, (hl)
            ld (de), a
            inc de
            dec l
            call Incy
            djnz CS_L1
            pop hl
            pop de
            pop bc
            ret
            
CursorDraw: push bc
            push de
            push hl
            ld a, (Cursor)
            inc a
            ld b, a
            ld hl, Caret_Arrow - 20
            ld de, 20
DC_L1:      add hl, de
            djnz DC_L1
DC_L2:      ld bc, (CursorX)            ; bc = caret current position
            ex de, hl                   ; de = caret gfx
            call Pix                    ; hl = caret scr addr, a = offset
            and a
            ld b, 10
            jr nz, DC_Slow
            ; draw the cursor fast (on character boundary)
DC_L3:      ld a, (de)                  ; get mask
            inc de                      ; move to gfx
            ld c, a
            ld a, (hl)
            and c
            ld c, a
            ld a, (de)                  ; get gfx                  
            inc de                      ; next mask
            or c
            ld (hl), a                  ; masked background with gfx
            call Incy
            djnz DC_L3
            pop hl
            pop de
            pop bc
            ret
            ; draw it slowly using shifting
            ; need to shift the mask and gfx into place and apply to screen gfx
DC_Shifts:  defb 0
DC_Slow:    ld c, 10                    ; de = caret gfx, hl = screen
            ld b, a                     ; b = shifts
            ld (DC_Shifts), a
DCS_L1:     push bc                     ; S: BC
            ld a, (de)
            inc de
            push de                     ; S: BC DE      save caret addr
            ld d, 255                   ; set low order mask to fully masked
DCS_L2:     srl a                       ; move mask right
            rr d                        ; shift into next character block
            or 128                      ; set the high order bit to masked
            djnz DCS_L2                 ; do for all required shifts
            ld e, a                 
            ld a, (hl)
            and e
            ld c, a
            inc l
            ld a, (hl)
            and d
            ld b, a                     ; bc = masked screen gfx
            pop de                      ; S: BC         get caret gfx addr         
            ld a, (de)                  ; get caret gfx
            inc de                      ; move to next mask
            push de                     ; S: BC DE      save caret addr    
            ld e, a
            ld d, 0
            ld a, (DC_Shifts)
DCS_L3:     srl e
            rr d
            dec a
            jr nz, DCS_L3               ; de = caret gfx shifted
            ld a, l
            and 31
            jr z, DCS_L4                  
            ld a, b
            or d
            ld b, a
            ld (hl), a
DCS_L4:     dec l
            ld a, c
            or e
            ld (hl), a
            call Incy
            pop de                      ; S: BC                          
            pop bc                      ; S:
            dec c
            jr nz, DCS_L1
            pop hl
            pop de
            pop bc
            ret

;---------------------------------------------------------------;
; ReadKempMouse                                                 ;
;                                                               ;
; Reads the Kempston mouse                                      ;
;                                                               ;
;---------------------------------------------------------------;
MouseLastX: defb 0
MouseLastY: defb 0
InitKempstonMouse:  
            ld bc, 64479
            in a,(c)
            ld (MouseLastX), a
            ld bc,65503
            in a,(c)
            ld (MouseLastY), a
            ret

KempstonMouse:  
            ld bc, 64479            ; read x axis
            ld a, (MouseLastX)
            ld d, a
            in a, (c)
            ld (MouseLastX), a
            sub d
            ; mouse left/right
            ld b, a
            cp 0x80
            jr nc, KempMoveLeft
            ; moving right
            ld a, (CursorX)
            add a, b
            ld b, a
            ld a, (CursorX)
            cp b
            jr z, ChkMouseY
            jr nc, RightEdge
            ld a, b
            ld (CursorX), a
            jr ChkMouseY
RightEdge:  ld a, 255
            ld (CursorX), a
            jr ChkMouseY
            ; moving left
KempMoveLeft:   
            ld a, (CursorX)
            add a, b
            ld b, a
            ld a, (CursorX)
            cp b
            jr c, LeftEdge
            ld a, b
            ld (CursorX), a
            jr ChkMouseY
LeftEdge:   xor a
            ld (CursorX), a
            ; read y axis
ChkMouseY:  ld bc, 65503        
            ld a, (MouseLastY)
            ld d, a
            in a, (c)
            ld (MouseLastY), a
            sub d
            ld b, a
            ld a, (CursorY)
            sub b
            cp MAX_Y_POS
            jr nc, SetVertEdge
            ld (CursorY), a
            jr MouseBtn
            ; moving down
SetVertEdge:ld a, (CursorY)
            cp 0x80
            jr c, SetTopEdge
            ld a, MAX_Y_POS
            ld (CursorY), a
            jr MouseBtn
            ; moving down
SetTopEdge: xor a
            ld (CursorY), a
MouseBtn:   ; read mouse buttons
            call CursorHide
            call CursorSave
            ld bc, 64223
            in a, (c)
            cp 255
            jr z, MBReset
            xor 255
            bit 0, a
            jp nz, MouseRightButton
            bit 1, a
            jr nz, MouseLeftButton
MBReset:    ld a, (BtnState)
            and a
            jr z, MouseDone
            xor a
            ld (BtnState), a
            call ShowScreen
            ; cheat by reseting the green attribute to white
            ld hl, 22528
            ld c, 3
MBRL2:      ld b, 256
MBRL1:      ld a, (hl)
            cp aBRT+pGRN
            jr nz, MBRS1S
            ld (hl), pWHT
MBRS1S:     inc hl
            djnz MBRL1
            dec c
            jr nz, MBRL2             
            jr MouseDone
                        
MouseLeftButton:
            ld a, (BtnState)
            and a
            jr nz, MLBS1
            ld a, (HitRect)
            and a
            jr z, MouseDone
            call SaveScreen
            ld a, 1
            ld (BtnState), a
MLBS1:      ld bc, (CursorX)
            ld a, c
            and $F8
            ld c, a
            jr nz, MLBS2
            ld c, 8
MLBS2:      cp 232  
            jr c, MLBS3
            ld c, 232
MLBS3:      ld a, b
            and $F8
            ld b, a
            jr nz, MLBS4
            ld b, 8
MLBS4:      cp 169
            jr c, MLBS5
            ld b, 168
MLBS5:      and a
            ld hl, (LastPos)
            sbc hl, bc
            jr z, MouseDone
            ld (LastPos), bc
            dec b
            dec c
            push bc
            call ShowScreen
            ld a, aBRT+pGRN+iBLK
            ld b, pWHT
            xor b
            ld (IconColor), a
            pop bc
            ld a, (DragIcon)
            call DrawIcon
MouseDone:  call CursorSave
            call CursorDraw
            ret

MouseRightButton:
            ld a, (MouseCtr)
            and a
            jr z, MouseChange
            inc a
            ld (MouseCtr), a
            ret
MouseChange ld a, (Cursor)
            inc a
            cp 3
            jr c, MRBS1
            xor a
MRBS1:      ld (Cursor), a
            ;call CursorSave
            call CursorDraw
            ret                                        

BtnState:   defb 0
LastPos:    defw 0            
MouseCtr:   defb 0            
                
                                                
                
                
                                            