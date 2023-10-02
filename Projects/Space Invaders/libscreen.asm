;---------------------------------------------------------------;
;                                                               ;
;  SCREEN.ASM                                                   ;
;                                                               ;
;  This file includes several useful screen functions           ;
;                                                               ;
;---------------------------------------------------------------;

SCREEN      equ     16384               ; spectrum display memory address
SCREEN2     equ     SCREEN+64           ; address to draw the offset screen buffer
ATTR        equ     22528               ; spectrum attribute memory address
SCRLEN      equ     6144                ; size of the screen pixels in bytes
ATTRLEN     equ     768                 ; size of the ATTR in bytes
MEMSCRLEN   equ     6335                ; size of the offscreen buffer
SCRWIDTH    equ     32                  ; number of character the offscreen buffer is wide

;
; COLORS
;
INK_BLK     equ     0
INK_BLU     equ     1
INK_RED     equ     2
INK_MAG     equ     3
INK_GRN     equ     4
INK_CYN     equ     5
INK_YEL     equ     6
INK_WHT     equ     7

PAP_BLK     equ     0
PAP_BLU     equ     8
PAP_RED     equ     16
PAP_MAG     equ     24
PAP_GRN     equ     32     
PAP_CYN     equ     40
PAP_YEL     equ     48
PAP_WHT     equ     56

BRIGHT      equ     64
FLASH       equ     128

;
; Defines to control what functions to compile into the program
;
ON              equ 1
OFF             equ 0

USE_INCY        equ ON
USE_DECY        equ ON
USE_PIX         equ ON
USE_ATTR        equ ON
IF !USE_OSB
; Don't use the Off Screen Buffer
USE_MPIX        equ OFF
USE_MATTR       equ OFF
USE_MATTR2      equ OFF
USE_CLRMEMSCR   equ OFF
USE_BLTMEMSCR   equ OFF
ELSE  ; USE_OSB
; Use the Off Screen Buffer and its associated off screen routines 
USE_MPIX        equ ON
USE_MATTR       equ ON
USE_MATTR2      equ ON
USE_CLRMEMSCR   equ ON
USE_BLTMEMSCR   equ ON
ENDIF ; USE_OSB
USE_CLEARSCR    equ ON
USE_CLRATTR     equ ON

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
IF USE_INCY
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
ENDIF ; USE_INCY

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
IF USE_DECY
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
ENDIF ; USE_DECY            

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
;       hl - the address for the pixels location on the screen  ;
;       a  - contains the bit position of the pixel             ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  hl                                            ;
;                                                               ;
;   Regs destoryed                                              ;
;       af                                                      ;
;---------------------------------------------------------------;
IF USE_PIX
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
ENDIF ; USE_PIX

;---------------------------------------------------------------;
; MPix                                                          ;
;                                                               ;
;   Converts a screen pixel coord into an off screen address    ;
;   Written by Tony Thompson                                    ;
;   Created         1984                                        ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;                                                               ;
;   Outputs                                                     ;
;       hl - the buffer address for the off screen location     ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  de                                            ;
;---------------------------------------------------------------;
IF USE_MPIX
MPix:       push de
            srl c
            srl c
            srl c                   ; div x pos by 8 into col
            ld l, b                 ; multiply y pos * 32
            ld h, 0
            add hl, hl
            add hl, hl
            add hl, hl
            add hl, hl
            add hl, hl
            ld a, l
            or c                    ; add c to de
            ld l, a
            ld de, MemScr
            add hl, de              ; add de to hl to get MemScr to offset
            pop de
            ret
ENDIF ; USE_MPIX

;---------------------------------------------------------------;
; MAttr                                                         ;
;                                                               ;
;   Converts a screen pixel coord into a off screen attr address;
;   Written by Tony Thompson                                    ;
;   Created         1984                                        ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;                                                               ;
;   Outputs                                                     ;
;       hl - the attribute address for the off screen location  ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  hl                                            ;
;---------------------------------------------------------------;
IF USE_MATTR
MAttr:      push de
            srl c
            srl c
            srl c                   ; div x pos by 8 into col
            ld l, b                 ; put row into hl
            ld h, 0
            add hl, hl
            add hl, hl
            ld a, l
            or c                    ; add c to hl
            ld l, a
            ld de,  MemAttr
            add hl, de
            pop de
            ret
ENDIF ; USE_MATTR

IF USE_MATTR2
MAttr2:     push de
            srl c
            srl c
            srl c                   ; div x pos by 8 into col
            srl b
            srl b
            srl b
            dec b
            dec b
            ld l, b                 ; multiply y pos * 32
            ld h, 0
            add hl, hl
            add hl, hl
            add hl, hl
            add hl, hl
            add hl, hl
            ld a, l
            or c                    ; add c to de
            ld l, a
            ld de, MemAttr
            add hl, de              ; add de to hl to get MemScr to offset
            pop de
            ret
ENDIF ; USE_MATTR2            

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
IF USE_ATTR
Attr:       ld a, h                 ; get the high byte of screen address
            rra                     ; divide h by 8
            rra                     ;
            rra                     ;
            and 3                   ; keep lower 3 bits,  these mimick the lower 4 bits of the attribute address
            or 0x58                 ; set the high order byte to the start of the attribute block
            ld h, a                 ; load the result into h
            ret                     ; hl now contains the attribute address
ENDIF ; USE_ATTR

;---------------------------------------------------------------;
; ClearScr                                                      ;
;                                                               ;
;   Clears the screen                                           ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         1st May 2003                                ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
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
IF USE_CLEARSCR
ClearScr:   push bc                     ; save bc
            push de                     ; save de
            push hl                     ; save hl
                                        ; clear the ATTR first - makes for a smoother clear
            ld hl,  ATTR                ; point hl to screen address
            ld de,  ATTR+1              ; point de to screen address + 1
            ld bc,  ATTRLEN-1           ; load bc with the size of the screen - 1
            ld (hl),  7                 ; clear the first element of the screen
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
ENDIF ; USE_CLEARSCR

;---------------------------------------------------------------;
; ClrMemScr                                                     ;
;                                                               ;
;   Clears the off screen memory buffer                         ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         1st May 2003                                ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
;                                                               ;
;   Outputs                                                     ;
;       off screen is cleared                                   ;
;                                                               ;
;   Regs Used                                                   ;
;       bc,  hl                                                 ;
;                                                               ;
;   Regs destoryed                                              ;
;       none                                                    ;
;---------------------------------------------------------------;
IF USE_CLRMEMSCR
ClrMemScr:  push bc                     ; save bc
            push de                     ; save de
            push hl                     ; save hl
            ld hl,  MemScr              ; point hl to the offscreen buffer
            ld de,  MemScr              ; point de to the offscreen buffer
            inc de
            ld bc,  MEMSCRLEN           ; set bc to the size of the buffer
            ld (hl), 0                  ; clear the first byte of the buffer
            ldir                        ; clear all of the buffer
            pop hl                      ; restore hl
            pop de                      ; restore de
            pop bc                      ; restore bc
            ret                         ; done
ENDIF ; USE_CLRMEMSCR
;---------------------------------------------------------------;
; BltMemScr                                                     ;
;                                                               ;
;   Blits the off screen memory buffer to the screen            ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         1st May 2003                                ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
;                                                               ;
;   Outputs                                                     ;
;       off screen is copied to the screen                      ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  de,  hl                                       ;
;---------------------------------------------------------------;
IF USE_BLTMEMSCR
BltMemScr:  ;di
            ld hl,  MemAttr             ; copy the ATTR first
            ld de,  ATTR + 64           ; this makes for a smoother copy
            ld bc,  704                 ; onto the screen
            ldir                        ; copy attribute in 1 block transfer
                                        ; copy the screen data
            ld b, 176                   ; lines to copy
            ld hl, MemScr               ; off screen buffer
            ld de, SCREEN2              ; destination on screen
bms1:       push bc                     ; save lines to copy
            ld bc,  32                  ; set size of line to block transfer
            push de                     ; save screen address
            ldir                        ; block transfer the line
            ex de, hl                   ; put new buffer address into de
            pop hl                      ; get screen address
            inc h                       ; try to move down 1 line in a character                1M  4T
            ld a, h                     ; get h into a                                          1M  4T
            and 7                       ; test if still inside character                        2M  7T
            jr nz, bms2                 ; ret if in character square                            1M  5T  3M  5T  7M  20T
            ld a, l                     ; no,  get lower byte of address                         1M  4T
            add a, 32                   ; and move it to the next character block               2M  7T
            ld l, a                     ; store the result                                      1M  4T
            jr c, bms2                  ; return if we are still in the same segment?           1M  5T  3M  5T  13M 40T
            ld a, h                     ; no,  so need to adjust high order byte of address      1M  4T
            sub 8                       ; adjust screen segment                                 2M  7T
            ld h, a                     ; store the correction                                  1M  4T
bms2:       ex de, hl                   ; swap addresses
            pop bc                      ; get the lines to copy
            djnz bms1                  ; dec and repeat until all lines are copied
            ;ei
            ret
ENDIF ; USE_BLTMEMSCR

;---------------------------------------------------------------;
; ClrAttr                                                       ;
;                                                               ;
;   Colors an area of attributes                                ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         10th Nov 2007                               ;
;   Last Changed    10th Nov 2007                               ;
;                                                               ;
;   Inputs                                                      ;
;       a  - color to clear to                                  ;
;       c  - x start position (pixels)                          ;
;       b  - y start position (pixels)                          ;
;       e  - width of area    (characters)                      ;
;       d  - height of area   (characters)                      ;
;                                                               ;
;   Outputs                                                     ;
;       area of attribute screen is colored                     ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  de,  hl                                       ;
;---------------------------------------------------------------;
IF USE_CLRATTR
ClrAttr:    push af                 ; save the colour
            push de                 ; save the width and height of the area
            call Pix                ; convert x,y positin to screen address
            call Attr               ; convert screen address into attribute address
            pop bc                  ; restore the width and height into bc (b-height, c-width)
            pop af                  ; restore the colour
CA_LP1:     push af                 ; save the colour
            push bc                 ; save loop counters (width and height)
            push hl                 ; save the attribute address
            ld b, c                 ; get only width in b
CA_LP2:     ld (hl), a              ; place the colour into attribute address
            inc l                   ; and move hl on 1
            djnz CA_LP2 
            pop hl                  ; restore the attribute address
            ld bc, 32
            add hl, bc
            pop bc                  ; restore the width and height into bc            
            pop af                  ; restore the colour
            djnz CA_LP1             ; loop for height of area
            ret                         
ENDIF ; USE_CLRATTR                

;---------------------------------------------------------------;
; ClrBlock                                                      ;
;                                                               ;
;   Clears a block of screen pixels                             ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         22nd Mar 2015                               ;
;   Last Changed    22nd Mar 2015                               ;
;                                                               ;
;   Inputs                                                      ;
;       b  - y pixel start position                             ;
;       c  - x pixel start position                             ;
;       d  - pixel height of area                               ;
;       e  - character width of area                            ;
;                                                               ;
;   Outputs                                                     ;
;       area of pixel screen is clear                           ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  de,  hl                                       ;
;---------------------------------------------------------------;
ClrBlock:   push de                 ; save the size                             (size)
            call Pix                ; calculate screen address from pixels pos
            pop bc                  ; get size into bc                          ()
CB_LP1:     push bc                 ; save the size                             (size)
            push hl                 ; save screen address                       (size, scr)
            ld b, c                 ; get width into b
CB_LP2:     ld (hl), 0              ; reset the character block pixels
            inc l                   ; next character block
            djnz CB_LP2             ; do for all width
            pop hl                  ; get start of line screen address          (size)
            call Incy               ; move down a line
            pop bc                  ; get size                                  ()
            djnz CB_LP1             ; loop for all lines
            ret

;****************************************
; WAIT FOR FLYBACK...
;****************************************
IF 0
WaitVBlank:	xor		a
			ld		r,a
			ei

			ld		a,(FXNumber)
			or		a
			jr		nz,Beeper

WaitInt:	ld		a,r
			jp		p,WaitInt
			di
			ret
ENDIF			