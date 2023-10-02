;------------------------------------------------------------------------------;
;  Icon_draw.inc                                                               ;
;  Contains routines to draw icons                                             ;
;------------------------------------------------------------------------------;

;------------------------------------------------------------------------------;
;  DrawIcon                                                                    ;
;                                                                              ;
;  Draws an Icon. Icons are 32x18.                                             ;
;  There is an extra line around a standard 16x16 bitmap graphic.              ;
;  Only the 16x16 area contains color. The out side area does not.             ;
;                                                                              ;
;  Inputs                                                                      ;
;       A - contains the icon index to draw (see IconsInfoTable)               ;
;       B - Y pixel position (should be (y % 8) - 1)                           ;
;       C - X pixel position (should be (x % 8) - 1)                           ;
;                                                                              ;
;  Regs Used                                                                   ;
;   af, bc, de, hl, ix, iy                                                     ;
;                                                                              ;
;  Regs Destroyed                                                              ;
;   af, de, hl, ix, iy                                                         ;
;                                                                              ;
;------------------------------------------------------------------------------;
DrawIcon:       push bc                 ; SP: BC save the icon position
                ld ix, IconsInfoTable   ; 
                ld e, a                 ; calculate the icon entry
                ld d, 0                 
                sla e
                rl d
                sla e
                rl d                    ; de * 4
                add ix, de              ; IX = icon info entry
                call Pix                ; get screen address to draw to
                push hl                 ; SP: BC HL save screen address
                ld l, (ix+2)
                ld h, (ix+3)            ; get icon info structure into IY
                push hl                 ; SP: BC HL HL
                pop iy                  ; SP: BC HL                      
                ld c, (iy+0)            ; width in c
                ld b, (iy+1)            ; lines in b
                ld e, (ix+0)
                ld d, (ix+1)            ; de = icon gfx
                pop hl                  ; SP: BC    get screen address
                push bc                 ; SP: BC BC
                push hl                 ; SP: BC BC HL
                
                ; draw the graphics
DrawIconGfx:    push bc                 ; SP: BC BC HL BC       save the gfx size
                push hl                 ; SP: BC BC HL BC HL    save the screen address
                ld a, (hl)
                ld b, a
                ld a, (de)
                or b                    ; blend left side of icon
                ld (hl), a              ; with the screen
                inc hl
                inc de
                ld a, (de)              ; copy middle gfx
                ld (hl), a              ; to screen
                inc hl
                inc de
                ld a, (de)              ; copy middle gfx
                ld (hl), a              ; to screen
                inc hl
                inc de
                ld a, (hl)
                ld b, a
                ld a, (de)
                or b                    ; blend right side gfx
                ld (hl), a              ; with screen
                inc de  
                pop hl                  ; SP: BC BC HL BC   restore the start of line address
                call Incy               ; move down 1 line
                pop bc                  ; SP: BC BC HL      restore the gfx size
                djnz DrawIconGfx        ; draw all lines
                
                ; move to drawing the attributes
                pop hl                  ; SP: BC BC     get screen address
                call Attr               ; convert to attribute address
                ld de, 33               ; move down to attribute location
                add hl, de              ; move attribute address
                pop bc                  ; SP: BC        get the gfx size
                rr b
                rr b
                rr b                    ; div height by 8
                push iy                 ; SP: BC IY
                pop de                  ; SP: BC        put iy into de
                inc de
                inc de                  ; point to icon attributes
                
                ; colour the icon
DrawIconAttr:   ld a, (de)              ; get the icon attribute
                and a                   ; is it zero?
                jr z, DIA1              ; yes, skip it then
                ld c, a                 ; c = icon color
                ld a, (IconColor)       ; get the icon color override value
                xor c                   ; blend together to change color (0=no change) 
                ld (hl), a              ; no, set the colour
DIA1:           inc de                  ; get next attribute
                inc hl                  ; move to next screen address
                ld a, (de)              ; get the icon attribute 
                and a                   ; is it zero?
                jr z, DIA2              ; yes, skip it
                ld c, a
                ld a, (IconColor)
                xor c                   ; blend override color
                ld (hl), a              ; no, set the colour
DIA2:           ld bc, 31               ; move to line below
                add hl, bc              
                inc de                  ; get next attribute 
                ld a, (de)              ; get the icon attribute
                and a                   ; is it zero?
                jr z, DIA3              ; yes, skip it then
                ld c, a
                ld a, (IconColor)
                xor c                   ; blend override color
                ld (hl), a              ; no, set the colour
DIA3:           inc de                  ; get next attribute
                inc hl                  ; move to next screen address
                ld a, (de)              ; get the icon attribute 
                and a                   ; is it zero?
                jr z, DIA4              ; yes, skip it
                ld c, a
                ld a, (IconColor)
                xor c                   ; blend override color 
                ld (hl), a              ; no, set the colour
                
DIA4:           pop bc                  ; SP:   restore the icon position
                ret 
                
IconColor:      defb 0                
                
;------------------------------------------------------------------------------;
;  DrawIconLabel                                                               ;
;                                                                              ;
;  Draws an icons label using the icons original pixel positions.              ;
;  Uses the small portional font.                                              ;
;                                                                              ;
;  Inputs                                                                      ;
;       DE - the address of the label text to draw                             ;
;       B - Y pixel position (should be (y % 8) - 1)                           ;
;       C - X pixel position (should be (x % 8) - 1)                           ;
;                                                                              ;
;------------------------------------------------------------------------------;
DrawIconLabel:  ld a, 19
                add a, b
                ld b, a
                ld a, c
                sub 14
                ld c, a
                push bc
                ; draw the label
                call Print64
                pop bc
                call Pix
                ; set the attributes
                call Attr
                ld (hl), 120                                                  
                ld d, h
                ld e, l
                inc de
                ldi 
                ldi 
                ldi 
                ldi 
                ldi 
                ret                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                                                        
                        