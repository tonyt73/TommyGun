;------------------------------------------------------------------------------;
;  Gui_CheckRect.inc                                                           ;
;  Contains routines for creating and checking the hit rects for objects       ;
;------------------------------------------------------------------------------;

; format
; x position in pixels      1(+RtPx)
; y position in pixels      1(+RtPy)
; width in pixels           1(+RtWdh) 
; height in pixels          1(+RtHgt) 
; normal attribute          1(+RtNA)
; hit attribute             1(+RtHA)
; flags                     1(+RtFlg)   0: mouse over, 1: highlighted 2: down, 3: Attr(0) Pixel(1)
; click function            2(+RtFunc)
; total                     9

Flag_Over   equ 1
Flag_HighLt equ 2
Flag_On     equ 3
Flag_Down   equ 4
Flag_Pixel  equ 8
Flag_AddRt  equ 16

RtPx        equ 0   ; x pixel pos
RtPy        equ 1   ; y pixel pos
RtWdth      equ 2   ; width in pixels
RtHght      equ 3   ; height in pixels
RtNA        equ 4   ; normal attribute
RtHA        equ 5   ; highlight attribute
RtFlg       equ 6   ; flags
RtFunc      equ 7   ; func
RtSize      equ 8   ; size of rect structure         

; bc = position
; de = width/height in pixels
; a  = flags
; l  = normal attribute
; h  = hit attribute
; iy = click function
GuiRectAdd: push de
            ld ix, (NextRect)
            ld (ix+RtFlg), a    ; save flags
            ld (ix+RtPy), b     ; save y pixel position
            ld (ix+RtPx), c     ; save x pixel position
            ld (ix+RtHght), d   ; save height in pixels
            ld (ix+RtWdth), e   ; save width in pixels
            ld (ix+RtHA), h     ; save hit attr
            ld (ix+RtNA), l     ; save normal attr
            push iy     
            pop hl
            ld (ix+RtFunc), l
            ld (ix+RtFunc+1), h ; save click function
            ld hl, (NextRect)
            ld de, RtSize
            add hl, de
            ld (NextRect), hl
            ld a, (Rects)
            inc a
            ld (Rects), a
            pop de   
            ret

; bc = mouse position            
GuiRectUpdate:
            ld d, b
            ld e, c             ; de = mouse pixel position
            ld a, (Rects)
            ld b, a             ; b = no. of rects to traverse
            xor a
            ld (HitRect), a
            ld ix, RectBuffer   ; rect buffer
            ; check the rects for a hit
            push bc             ; SP:BC save no. of rects
GRUL1:      push de             ; SP:BC DE save mouse pixel position
            push bc             ; SP:BC DE BC number of rects 
            call GuiCheckHit    
            ld a, (ix+RtFlg)    ; get flags
            and $FE             ; reset mouse over bit
            or b                ; set mouse over bit (if required)
            ld (ix+RtFlg), a    ; update rect flags
            pop bc              ; SP: BC DE
            and Flag_Over       ; is mouse over set?
            jr z, GRUS2         ; if not skip
            ld a, b             ; get the hit rect (count down) index
            ld (HitRect), a     ; set the hit rect index
            push bc             ; SP: BC DE BC
            ld c, (ix+RtPx)     ; get x position of the rect
            ld b, (ix+RtPy)     ; get y position of the rect
            call FindIcon       ; find an matching icon
            jr nc, GRUS3        ; if not found skip
            ld a, l             ; get the index found
            ld (DragIcon), a    ; save to drag icon 
GRUS3:      pop bc              ; SP: BC DE
            ; move to next rect record  
GRUS2:      ld de, RtSize       ; get rect struct size
            add ix, de          ; move to next rect
            pop de              ; SP:BC
            djnz GRUL1          ; loop for all rects
            ld ix, RectBuffer   ; go back to start of rect buffer
            pop bc              ; get number of rects
            ; draw the state of the rects
GRUL2:      push bc             ; SP:BC     save no. of rects
            ld a, (ix+RtFlg)    ; get rect flags
            and Flag_On
            jr z, GRUS1         ; no mouse over and no highlight = no change, skip
            cp Flag_On          ; mouse over and highlighted = no change, skip 
            jr z, GRUS1
            ld a, (ix+RtFlg)    ; get the flags
            xor Flag_HighLt     ; toggle the highlight bit
            ld (ix+RtFlg), a    ; set the flags
            call GRUDrawRect    ; draw the change of the rect
            pop bc              ; technically only 1 rect can change at a time
            ret                 ; so we are done
GRUS1:      ld bc, RtSize
            add ix, bc          ; move to next rect
            pop bc              ; SP:   get no. of rects
            djnz GRUL2          ; loop for all rects
            ret

; ix=rect
; 
GRUDrawRect:ld c, (ix+RtPx)
            ld b, (ix+RtPy)
            ld e, (ix+RtWdth)
            ld d, (ix+RtHght)
            ld a, (ix+RtFlg)
            and Flag_Pixel
            jr nz, GRUpixs
            ; draw the rect using attributes            
            srl c
            srl c
            srl c               ; x / 8
            srl b
            srl b
            srl b               ; y / 8
            srl d
            srl d
            srl d               ; h / 8
            srl e
            srl e
            srl e               ; w / 8
            ld a, (ix+RtFlg)
            and Flag_HighLt                
            ld a, (ix+RtNA)     ; assume it is normal
            jr z, GRUDRHL       ; is it highlighted?      
            ld a, (ix+RtHA)     ; use highlighted
            ; set the rect attributes
            ; hl = attr
GRUDRHL:    jp AttrRect
            ; draw the rect using pixels
GRUpixs:    call CursorHide
            call FillRect       ; draw rect using pixels
            call CursorSave
            call CursorDraw
            ret                                                      

; de = mouse pixel positions
; ix = rect
; ret b = 0 not hit, 1 = hit
GuiCheckHit:ld b, 0
            ld a, (ix+RtPx)
            cp e
            jr z, GCHY 
            ret nc
            add a, (ix+RtWdth)
            cp e
            ret c
GCHY:       ld a, (ix+RtPy)
            cp d
            jr z, GCHhit 
            ret nc
            add a, (ix+RtHght)
            cp d
            ret c
GCHhit:     ld b, Flag_Over
            ret


           
            
            
DragIcon    defb 0           
HitRect     defb 0              ; the index of the rect currently hit            
Rects       defb 0              ; number of rects in buffer
NextRect    defw RectBuffer     
RectBuffer  defs RtSize * 32, 55      
            