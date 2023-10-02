;------------------------------------------------------------------------------;
;  Display.inc                                                                 ;
;  Contains routines for using the display                                     ;
;------------------------------------------------------------------------------;

iBLK equ 0
iBLU equ 1
iRED equ 2
iPUR equ 3
iGRN equ 4
iCYN equ 5
iYLW equ 6
iWHT equ 7
pBLK equ 0
pBLU equ 1*8
pRED equ 2*8
pPUR equ 3*8
pGRN equ 4*8
pCYN equ 5*8
pYLW equ 6*8
pWHT equ 7*8
aBRT equ 64
aFLH equ 128

;---------------------------------------------------------------;
; Incy                                                          ;
;                                                               ;
;   Moves the screen address down 1 line                        ;
;   Written by Tony Thompson                                    ;
;   Written by Nick Fleming                                     ;
;   Both versions where identical                               ;
;   Created         1984                                        ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       hl - the address of a screen location                   ;
;                                                               ;
;   Outputs                                                     ;
;       hl - the address of the line below                      ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  hl                                                 ;
;                                                               ;
;   Regs destoryed                                              ;
;       af                                                      ;
;---------------------------------------------------------------;
Incy:       inc h                       ; try to move down 1 line in a character                1M  4T
            ld a, h                     ; get h into a                                          1M  4T
            and 7                       ; test if still inside character                        2M  7T
            ret nz                      ; ret if in character square                            1M  5T  3M  5T  7M  20T
            ld a, l                     ; no,  get lower byte of address                        1M  4T
            add a, 32                   ; and move it to the next character block               2M  7T
            ld l, a                     ; store the result                                      1M  4T
            ret c                       ; return if we are still in the same segment?           1M  5T  3M  5T  13M 40T
            ld a, h                     ; no,  so need to adjust high order byte of address     1M  4T
            sub 8                       ; adjust screen segment                                 2M  7T
            ld h, a                     ; store the correction                                  1M  4T
            ret                         ;                                                       3M 10T          18M 60T

;---------------------------------------------------------------;
; Decy                                                          ;
;                                                               ;
;   Moves the screen address up 1 line                          ;
;   Written by Nick Fleming                                     ;
;                                                               ;
;   Inputs                                                      ;
;       hl - the address of a screen location                   ;
;                                                               ;
;   Outputs                                                     ;
;       hl - the address of the line above                      ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  hl                                                 ;
;                                                               ;
;   Regs destoryed                                              ;
;       af                                                      ;
;---------------------------------------------------------------;

Decy:       dec h                       ; try to move up 1 line in a character
            ld a, h                     ; test high order of address
            and 7                       ; mask off top 5 bits,  keep lower 3
            cp 7                        ; is the result 7?,  if yes we are at the bottom of a character square
            ret nz                      ; yes,
            ld a, l                     ; so get lower order byte of screen address
            sub 32                      ; and try to move up by 1 character to next line
            ld l, a                     ; store resul in lower order byte screen address
            ret c                       ; are we still in the correct segment?
            ld a, h                     ; no,  so need to adjust screen segemnt
            add a, 8                    ; correct the segment we are in
            ld h, a                     ; store the correction
            ret

;---------------------------------------------------------------;
; Pix                                                           ;
;                                                               ;
;   Converts a screen pixel coord into a screen address and     ;
;   pixel position                                              ;
;   Written by Tony Thompson                                    ;
;   Created         1984                                        ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;                                                               ;
;   Outputs                                                     ;
;       hl - the attribute address for the screen location      ;
;       a  - contains the bit position of the pixel             ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  hl                                            ;
;                                                               ;
;   Regs destoryed                                              ;
;       af                                                      ;
;---------------------------------------------------------------;
Pix:        ld a, b
            rra
            scf
            rra
            rra
            and 88
            ld h, a
            ld a, b
            and 7
            add a, h
            ld h, a
            ld a, c
            rrca
            rrca
            rrca
            and 31
            ld l, a
            ld a, b
            and 56
            add a, a
            add a, a
            or l
            ld l, a
            ld a, c
            and 7
            ret 
            
            
;---------------------------------------------------------------;
; Attr                                                          ;
;                                                               ;
;   Converts a screen addr into an attribute address            ;
;   Written by Nick Fleming                                     ;
;                                                               ;
;   Inputs                                                      ;
;       hl - the address of a screen location                   ;
;                                                               ;
;   Outputs                                                     ;
;       hl - the attribute address for the screen location      ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  h                                                  ;
;                                                               ;
;   Regs destoryed                                              ;
;       af                                                      ;
;---------------------------------------------------------------;
Attr:       ld a, h                 ; get the high byte of screen address
            rra                     ; divide h by 8
            rra                     ;
            rra                     ;
            and 3                   ; keep lower 3 bits,  these mimick the lower 4 bits of the attribute address
            or 0x58                 ; set the high order byte to the start of the attribute block
            ld h, a                 ; load the result into h
            ret                     ; hl now contains the attribute address

; b = y character pos
; c = x character pos
; hl = attribute address
PosAttr:    xor a                   ; shift y pos down 3 into a
            srl b
            rra
            srl b
            rra
            srl b
            rra                     ; = y * 32
            or c                    ; add c
            ld c, a                 ; bc = attribute offset
            ld hl, 22528
            add hl, bc              ; hl = attribute address
            ret    


;---------------------------------------------------------------;
; ClrScr                                                        ;
;                                                               ;
;   Clears the screen                                           ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         1st May 2003                                ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       a - attribute colour                                    ;
;                                                               ;
;   Outputs                                                     ;
;       screen is cleared                                       ;
;                                                               ;
;   Regs Used                                                   ;
;       bc,  hl                                                 ;
;                                                               ;
;   Regs destoryed                                              ;
;       bc,  de,  hl                                            ;
;---------------------------------------------------------------;
ClrScr:     push bc                     ; save bc
            push de                     ; save de
            push hl                     ; save hl
                                        ; clear the ATTR first - makes for a smoother clear
            ld hl,  ATTRS               ; point hl to screen address
            ld de,  ATTRS+1             ; point de to screen address + 1
            ld bc,  ATTRLEN-1           ; load bc with the size of the screen - 1
            ld (hl),  a                 ; clear the first element of the screen
            ldir                        ; block transfer zeroes to all of the screen
                                        ; clear the screen data
            ld hl,  SCREEN              ; point hl to screen address + 1
            ld de,  SCREEN+1            ; point de to screen address
            ld bc,  SCRLEN-1            ; load bc with the size of the screen - 1
            ld (hl),  0                 ; clear the first element of the screen
            ldir                        ; block transfer zeroes to all of the screen
            pop hl                      ; restore hl
            pop de                      ; restore de
            pop bc                      ; restore bc
            ret                         ; screen cleared

; draw a filled rect
; c - x pixel position
; b - y pixel position
; e - width in pixels (must > 16 pixels)
; d - height in pixels
FillRect:   call Pix                    ; get screen address and pixel position
            push hl                     ; SP: HL
            xor 7                       ; a = 7 - a
            ld l, a                     ; get left start pixel position
            ld a, e
            sub l
            ld e, a                     ; width - left pixels
            push de                     ; SP: HL DE
            ld h, 0
            ld bc, LEdgeLut
            add hl, bc
            ld c, (hl)                  ; c = left edge pixels to set
            ld a, e                     ; a = width
            and 7                       ; a = remaining right pixels
            ld e, a
            ld d, 0
            ld hl, REdgeLut
            add hl, de
            ld b, (hl)                  ; b = right pixels, c = left pixels
            pop de                      ; SP: HL    d = height, e = width
            pop hl                      ; SP:    hl = screen address
            srl e
            srl e
            srl e
FRL1:       push de                     ; SP: DE
            push hl                     ; SP: DE HL
            ld a, c                     ; draw left edge
            xor (hl)                    ; blend pixels with screen
            ld (hl), a                  ; set the result
            inc hl                      ; middle section
FRL2:       ld a, $FF                   ; all bits set
            xor (hl)                    ; blend with screen
            ld (hl), a                  ; set result
            inc hl                      ; next screen pos
            dec e
            jr nz, FRL2                 ; if not zero, repeat
            ld a, b                     ; get right edge pixels
            xor (hl)                    ; blend with screen
            ld (hl), a                  ; set result
            pop hl                      ; SP: DE  restore start screen address
            call Incy                   ; move down 1 line                       
            pop de                      ; SP:  get width/height
            dec d                       ; down 1 line
            jr nz, FRL1                 ; repeat until all lines done
            ret
            
;
; a = attribute
; b = y char position
; c = x char position
; d = char height
; e = char width            
AttrRect:   push af                     ; save attribute
            call PosAttr                ; get attribute address of char position
            ld b, e
            pop af                      ; get attribute
ARL2:       push de                     ; SP:BC     save width/height
            push hl                     ; SP:BC HL  save attr address
            ld b, e
ARL1:       ld (hl), a                  ; set attribute
            inc l                       ; next attribute
            djnz ARL1
            pop hl                      ; SP:BC     get start attr address
            ld bc, 32                   ; 
            add hl, bc                  ; down 1 line 
            pop de                      ; SP:       get width/height
            dec d                       ; down 1 line
            jr nz, ARL2     
            ret
            
LEdgeLut:   defb $01    ; +7 
            defb $03    ; +6            
            defb $07    ; +5            
            defb $0F    ; +4            
            defb $1F    ; +3            
            defb $3F    ; +2            
            defb $7F    ; +1            
            defb $FF    ; +0
            
REdgeLut:   defb $80    ; +0
            defb $C0    ; +1            
            defb $E0    ; +2            
            defb $F0    ; +3            
            defb $F8    ; +4            
            defb $FC    ; +5            
            defb $FE    ; +6            
            defb $FF    ; +7            
            
; a - attribute 
; b - y pixel
; c - x pixel
; d - width (bytes)
ClrChrLine: ex af, af'
            ld a, b
            and 0xF8
            call Pix
            ld c, d
            ld b, 8
            push hl
CCCL1:      push bc
            push hl
            ld d, h
            ld e, l
            inc de
            ld b, 0
            ld (hl), 0
            ldir
            pop hl
            inc h
            pop bc
            djnz CCCL1
            pop hl
            call Attr
            ex af, af'
            ld (hl), a
            ld d, h
            ld e, l
            inc de
            ldir
            ret 
                        

; b - y pixel
; c - x pixel
; d - width (bytes)
DrawHLine:  call Pix
            ld b, 0
            ld c, d
            ld (hl), 255
            ld d, h
            ld e, l
            inc de
            ldir
            ret             


SaveScreen: ld hl, 16384
            ld de, 25600
            ld bc, 6912
            ldir
            ret
            
ShowScreen: ld hl, 25600
            ld de, 16384 
            ld bc, 6912
            ldir
            ret            


; synchronize with the raster beam
VSync:      ld      bc, $3805
            ld      a, 14
            jr      sync_raster
delay_128k: ld      b, $3b

sync_raster:
            nop                             ; extra delay
sync_raster_loop:
            djnz    sync_raster_loop
            ld      b, a
            ld      hl, ($4000)             ; synchronize
            dec     c
            jr      nz, sync_raster

; wait for the raster beam
            ld      a, (bc)                 ; extra delay
            ld      b, 4
wait_raster:
            djnz    wait_raster
            ret            
                                    
