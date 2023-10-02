;------------------------------------------------------------------------------;
;  Print_64.inc                                                                ;
;  Contains routines for drawing and managing text using the fonts.inc data.   ;
;------------------------------------------------------------------------------;

;------------------------------------------------------------------------------;
; Print64                                                                      ;
;   Prints a null terminated screen to the screen.                             ;
;   No checking. No wrap-around. Short strings only.                           ;
;   Use PrintNice to draw the nice, but much slower portional font.            ;
;                                                                              ;
; Inputs                                                                       ;
; b  - y pixel                                                                 ;
; c  - x pixel                                                                 ;
; de - address of string to draw                                               ;
;                                                                              ;
; Regs Used                                                                    ;
;  af, af', bc, de, hl                                                         ;
;                                                                              ;
;------------------------------------------------------------------------------;
Print64:    call Pix                ; get the screen address for the text
            and a                   ; reset carry
            bit 2, c                ; check the character nibble position
            jr z, Print64L1         ; start on high nibble if ZF is set
            scf                     ; start on low nibble            
Print64L1:  ex af, af'              ; save carry flag
            ld a, (de)              ; get character
            and a                   ; check for zero
            ret z                   ; done if string terminator found
            ld c, a                 ; c = character to draw
            ex af, af'              ; restore carry flag
            push af                 ; save carry flag (which side to draw)
            push de                 ; save string position
            call Print64Chr         ; draw the character
            pop de                  ; restore string position
            inc de                  ; next character
            pop af                  ; get carry flag
            ccf                     ; swap carry flag
            jr c, Print64L1         ; if low nibble keep printing        
            inc l                   ; high nibble, move to next screen position
            jr Print64L1            ; keep printing

;------------------------------------------------------------------------------;
; Print64Chr                                                                   ;
;   Draws a character onto the screen using the 64 column font (4x5).          ;
;   Designed to be drawn as fast as possible to allow for a lot of use.        ;
;                                                                              ;
; Inputs                                                                       ;
;   c  - character to draw                                                     ;
;   f  - zero flag set to draw low nibble, not set draws the high nibble       ;
;   hl - screen address                                                        ;
;                                                                              ;
; Regs Used                                                                    ;
;  af, bc, de, hl                                                              ;
;                                                                              ;
; Regs Destroyed                                                               ;
;  af, bc, de                                                                  ;
;                                                                              ;
;------------------------------------------------------------------------------;

Print64Chr: push hl
            push af                 ; save carry
            ex de, hl               ; save hl in de
            ld hl, Font64Column-160 ; get character gfx - minus first 32 chars     
            ld b, 0
REPT 5
            add hl, bc              ; character gfx offset = character * 5 bytes
ENDM
            ex de, hl               ; de = character gfx, hl back to screen
            pop af                  ; get carry (which nibble to draw into)
            ld b, 5                 ; each character is 5 bytes
            jr c, Prt64Low          ; carry = print right side of character
            ; draw the character on the high nibble  [XXXX....]
Prt64High:  ld a, (hl)              ; get the screen contents
            and 0x0F                ; mask off where we want to draw to
            ld c, a                 ; save the masked value
            ld a, (de)              ; get the character font gfx
            and 0xF0                ; mask off the left side (printing right)
            or c                    ; combine with screen 
            ld (hl), a              ; store on screen
            inc h                   ; move down 1 line on screen
            inc de                  ; move to next character gfx
            djnz Prt64High          ; do for all lines
            pop hl                  ; restore original screen location
            ret                     ; all done
            ; draw the character on the low nibble  [....XXXX]
Prt64Low:   ld a, (hl)
            and 0xF0
            ld c, a
            ld a, (de)
            and 0x0F
            or c
            ld (hl), a
            inc h
            inc de
            djnz Prt64Low
            pop hl
            ret
                                          