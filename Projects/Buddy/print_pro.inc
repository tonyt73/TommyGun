;------------------------------------------------------------------------------;
;  Print_Pro.inc                                                               ;
;  Contains routines for drawing and managing text usingt he fonts.asm data.   ;
;------------------------------------------------------------------------------;

; b  - y pixel
; c  - x pixel
; de - string
; ret: a = length in pixels

PrintPro:   push bc                 ; save original position
PrintProL1: ld a, (de)              ; get character from string
            and a                   ; is it zero?
            jr z, PrintProEnd       ; terminated
            push de                 ; save string address 
            push bc                 ; save the location
            call PrintProCh         ; print the character
            pop bc                  ; get the location
            add a, c                ; add the size of the character to x position
            ld c, a                 ; set new x position
            pop de                  ; get string address
            inc de                  ; next character
            jr PrintProL1           ; keep printing
PrintProEnd:ld a, c                 ; get current x position
            pop bc                  ; get original x position
            sub c                   ; calculate length of string in pixels
            sub 3                   ; remove space
            ret
            

; a  - character
; b  - y pixel
; c  - x pixel
; ret: a character width
PrintProCh: ld hl, FontPro - 192
            ld e, a
            ld d, 0
REPT 6
            add hl, de          ; * 6
ENDM
            ex de, hl           ; de = font chr gfx
            push de             ; save font address (width)
            inc de              ; move to first gfx
            call Pix            ; get screen address and pixel rotation
            ld c, 5             ; 5 lines to draw
            ld b, a             ; put shifts into b
            and a
            jr nz, PPCshift
            ; no shifting required
PPCnoShift: push bc
            ld a, (de)
            ld b, (hl)
            or b
            ld (hl), a
            inc de
            inc h
            pop bc
            dec c
            jr nz, PPCnoShift 
            jr PPCend            
            ; shifting required
PPCshift:   push bc             ; save counters
            push hl
            ld a, (de)          ; get chr gfx
            ld c, 0             ; clear c to shift into
PPC2:       srl a               ; rotate a
            rr c                ; through to c
            djnz PPC2           ; move the gfx into position
            ld b, (hl)          ; place gfx on screen
            or b
            ld (hl), a
            ld a, c
            and a
            jr z, PPC3          ; can we skip the next character?
            inc l
            ld c, (hl)
            or c
            ld (hl), a
PPC3:       inc de              ; next gfx
            pop hl
            inc h
            pop bc
            dec c
            jr nz, PPCshift
PPCend:     pop de
            ld a, (de)          ; get the width of the character
            ret
                
                                        
    