;------------------------------------------------------------------------------;
;  Menus.inc                                                                   ;
;  Contains routines for drawing and managing menus                            ;
;------------------------------------------------------------------------------;

DrawTopMenu:    ld bc, 0
                ld a, 56
                ld d, 31
                call ClrChrLine
                ld hl, MenuDesk
                call DrawStrAt
                ld hl, MenuFile
                call DrawStrAt
                ld hl, MenuView
                call DrawStrAt
                ld hl, MenuOpts
                call DrawStrAt
                ld b, 7
                ld c, 0
                ld d, 31
                call DrawHLine
                ret

DrawStrAt:      ld c, (hl)
                inc hl
                ld b, (hl)
                inc hl
                ld d, h
                ld e, l
                push bc
                call PrintPro
                pop bc                  ; a = len pixels, c = x, b = y
                dec c                   
                dec c
                dec c
                dec c                   ; x = x - 4
                dec b                   ; y = y - 1
                add a, 8                ; fatten the width 4 pixels each side
                ld e, a                 ; e = width in pixels
                ld d, 7                 ; d = height in pixels
                ld l, pWHT+iBLK         ; l = normal attr
                ld h, aBRT+pWHT+iBLK    ; h = hit attr
                ld iy, 0                ; hit function
                ld a, Flag_Pixel
                call GuiRectAdd                                 
                ret                
                
                

MenuDesk: defb 12, 1, "DESK", 0
MenuFile: defb 44, 1, "FILE", 0
MenuView: defb 76, 1, "VIEW", 0
MenuOpts: defb 108, 1, "OPTIONS", 0


