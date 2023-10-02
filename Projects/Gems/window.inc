;---------------------------------------------------------------;
;                                                               ;
;   Window.inc                                                  ;
;                                                               ;
;   This file contains routines for dealing with Opening and    ;
;   Closing Windows on the screen                               ;
;                                                               ;
;---------------------------------------------------------------;



;---------------------------------------------------------------;
; WindowDrwTile                                                 ;
;                                                               ;
;   Draws a window tile at the specified position               ;
;   Written by Tony Thompson                                    ;
;   Created         May 2006                                    ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;      de - the address of the tile to draw                     ;
;                                                               ;
;---------------------------------------------------------------;
WindowDrwTile:  push bc
                call Pix
                push hl
                ld b, 8
WDT_Lp1:        ld a, (de)
                ld (hl), a
                inc h
                inc de
                djnz WDT_Lp1
                pop hl
                call Attr
                ld a, (de)
                ld (hl), a
                pop bc
                ret

;---------------------------------------------------------------;
; WindowDrwRow                                                  ;
;                                                               ;
;   Draws a row of window tiles either the top line, a middle   ;
;   line or the bottom line                                     ;
;   Written by Tony Thompson                                    ;
;   Created         May 2006                                    ;
;                                                               ;
;---------------------------------------------------------------;
TileLeft:       defw 0      ; Left tile to draw
TileMiddle:     defw 0      ; Middle tile to draw
TileRight:      defw 0      ; Right tile to draw
WindowDrwRow:   push bc
                push de
                push de
                ld de, (TileLeft)
                call WindowDrwTile
                pop de
                dec e
WDR_Lp1:        push de
                ld a, c
                add a, 8
                ld c, a
                ld de, (TileMiddle)
                call WindowDrwTile
                pop de
                dec e
                ld a, e
                cp 1
                jr nz, WDR_Lp1
                ld a, c
                add a, 8
                ld c, a
                ld de, (TileRight)
                call WindowDrwTile
                pop de
                pop bc
                ret


;---------------------------------------------------------------;
; WindowDraw                                                    ;
;                                                               ;
;   Draws a complete window onto the screen                     ;
;   Written by Tony Thompson                                    ;
;   Created         May 2006                                    ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;       d - height of the window                                ;
;       e - width  of the window                                ;
;                                                               ;
;---------------------------------------------------------------;
WindowDraw:     push bc
                push de
                ld hl, CornerTL
                ld (TileLeft), hl
                ld hl, FrameT
                ld (TileMiddle), hl
                ld hl, CornerTR
                ld (TileRight), hl
                call WindowDrwRow
                ld hl, FrameL
                ld (TileLeft), hl
                ld hl, Blank
                ld (TileMiddle), hl
                ld hl, FrameR
                ld (TileRight), hl
WD_Lp1:         ld a, b
                add a, 8
                ld b, a
                call WindowDrwRow
                dec d
                ld a, d
                cp 1
                jr nz, WD_Lp1
                ld a, b
                add a, 8
                ld b, a
                ld hl, CornerBL
                ld (TileLeft), hl
                ld hl, FrameB
                ld (TileMiddle), hl
                ld hl, CornerBR
                ld (TileRight), hl
                call WindowDrwRow
                pop de
                pop bc
                ret


;---------------------------------------------------------------;
; WindowRestore                                                 ;
;                                                               ;
;   Erases a window by drawing the previous screen contents     ;
;   Written by Tony Thompson                                    ;
;   Created         May 2006                                    ;
;                                                               ;
;---------------------------------------------------------------;
WindowRestore:  ld ix, WinResTable
                ld a, (WindowsOpened)
                sla a
                ld d, 0
                ld e, a
                add ix, de
                add ix, de
                add ix, de
                add ix, de
                ld b, (ix+0)
                ld c, (ix+1)
                ld d, (ix+2)
                ld e, (ix+3)
                ld h, (ix+4)
                ld l, (ix+5)
                ld (NextSaveAddr), hl
                ld h, (ix+6)
                ld l, (ix+7)
                push hl
                pop ix
                push bc
                push de
                call Pix
WR_Lp1:         push bc
                ld b, 8
WR_Lp2:         push de
                push hl
WR_Lp3:         ld a, (ix+0)
                ld (hl), a
                inc hl
                inc ix
                dec e
                jr nz, WR_Lp3
                pop hl
                call Incy
                pop de
                djnz WR_Lp2
                pop bc
                dec d
                jr nz, WR_Lp1
                pop de
                pop bc
                call Pix
                call Attr
WR_Lp4:         push bc
                push de
                push hl
WR_Lp5:         ld a, (ix+0)
                ld (hl), a
                inc hl
                inc ix
                dec e
                jr nz, WR_Lp5
                pop hl
                ld bc, 32
                add hl, bc
                pop de
                pop bc
                dec d
                jr nz, WR_Lp4
                ret
        
        
        
;---------------------------------------------------------------;
; WindowSave                                                    ;
;                                                               ;
;   Saves the contents that a window is about to overwrite      ;
;   Written by Tony Thompson                                    ;
;   Created         May 2006                                    ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;       d - height of the window                                ;
;       e - width  of the window                                ;
;                                                               ;
;---------------------------------------------------------------;
WindowSave:     push bc
                inc d
                push de
                push de
                ld ix, WinResTable
                dec a
                sla a
                ld d, 0
                ld e, a
                add ix, de
                add ix, de
                add ix, de
                add ix, de
                pop de
                ld hl, (NextSaveAddr)
                ld (ix+0), b
                ld (ix+1), c
                ld (ix+2), d
                ld (ix+3), e
                ld (ix+4), h
                ld (ix+5), l
                ld b, d
                ld d, 0
                ld hl, 0
WS_Lp1:         add hl, de
                djnz WS_Lp1
                push hl
                sla l
                rl h
                sla l
                rl h
                sla l
                rl h
                pop de
                add hl, de
                ex de, hl
                ld hl, (NextSaveAddr)
                sbc hl, de
                ld (NextSaveAddr), hl
                ld (ix+6), h
                ld (ix+7), l
                push hl
                pop ix
                pop de
                pop bc
                push bc
                push de
                call Pix
WS_Lp2:         push bc
                ld b, 8
WS_Lp3:         push de
                push hl
WS_Lp4:         ld a, (hl)
                ld (ix+0), a
                inc hl
                inc ix
                dec e
                jr nz, WS_Lp4
                pop hl
                call Incy
                pop de
                djnz WS_Lp3
                pop bc
                dec d
                jr nz, WS_Lp2
                pop de
                pop bc
                call Pix
                call Attr
                push bc
                push de
WS_Lp5:         push bc
                push de
                push hl
WS_Lp6:         ld a, (hl)
                ld (ix+0), a
                inc hl
                inc ix
                dec e
                jr nz, WS_Lp6
                pop hl
                ld bc, 32
                add hl, bc
                pop de
                pop bc
                dec d
                jr nz, WS_Lp5
                pop de
                dec d
                pop bc
                ret


        
        
;---------------------------------------------------------------;
; WindowOpen                                                    ;
;                                                               ;
;   Opens a window for drawing to                               ;
;   Written by Tony Thompson                                    ;
;   Created         May 2006                                    ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;       d - height of the window                                ;
;       e - width  of the window                                ;
;                                                               ;
;---------------------------------------------------------------;
WindowOpen:     ld a, (WindowsOpened)
                cp 4
                ret z
                inc a
                ld (WindowsOpened), a
                call WindowSave
                ld h, 3
                ld l, 3
WO_Lp1:         push de
                ld a, e
                cp l
                jr z, WO_Skp2
                inc l
WO_Skp2:        ld a, d
                cp h
                jr z, WO_Skp3
                inc h
WO_Skp3:        ex de, hl
                call WindowDraw
                ex de, hl
                pop de
                ld a, l
                cp e
                jr nz, WO_Lp1
                ld a, d
                cp h
                jr nz, WO_Lp1
                ret
        
        
        
;---------------------------------------------------------------;
; WindowClose                                                   ;
;                                                               ;
;   Closes the currently open window                            ;
;   Written by Tony Thompson                                    ;
;   Created         May 2006                                    ;
;                                                               ;
;---------------------------------------------------------------;
WindowClose:    ld a, (WindowsOpened)
                and a
                ret z
                dec a
                ld (WindowsOpened), a
                call WindowRestore
                ret

WindowSetColor: ld (Blank + 8), a
                ret

WindowsOpened:  defb 0                  ; the number of windows open
NextSaveAddr:   defw 65400              ; the next available address to save screen data
WinResTable:    defw 0,0,0,0,0,0,0,0    ; the windows restore table
                defw 0,0,0,0,0,0,0,0    ; saves the windows position (x, y), its size
                defw 0,0,0,0,0,0,0,0    ; of width and height, the address where
                defw 0,0,0,0,0,0,0,0    ; its saved screen contents are and the
                defw 0,0,0,0,0,0,0,0    ; address of the previous NextSaveAddr
                
