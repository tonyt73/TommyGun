;---------------------------------------------------------------;
;                                                               ;
;  TEXT.ASM                                                     ;
;                                                               ;
;  This file includes several useful text drawing functions     ;
;                                                               ;
;---------------------------------------------------------------;
ROM_CHRSET:     equ     15616               ; address of the spectrum ROM characters
NEW_CHRSET:     equ     Invader_ascii_032

;---------------------------------------------------------------;
; DrwChr                                                        ;
;                                                               ;
;   Draws a character on the screen                             ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         24th April 2003                             ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       a  - the character to draw                              ;
;       hl - the screen address to draw the character           ;
;                                                               ;
; Outputs                                                       ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  b,  de,  hl                                        ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  b,  de,  hl                                        ;
;---------------------------------------------------------------;
DrwChr:     sub 32                      ; character set starts at space
            push hl                     ; save screen address
            ld h, 0                     ; use hl to calculate character address
            ld l, a                     ;
            add hl, hl                  ; multiply by 2
            add hl, hl                  ; multiply by 4
            add hl, hl                  ; multiply by 8
            ld de, NEW_CHRSET               ; de has character set address
            add hl, de                  ; hl contains address of character data
            ex de, hl                   ; now put it into de
            pop hl                      ; get screen address
            ld b, 8                     ; characters are 8 pixels high
dc1:        ld a, (de)                  ; get character data
            ld (hl), a                  ; put it on screen
            inc h                       ; move down 1 line within a character on screen
            inc de                      ; move to next character data
            djnz dc1                    ; count the lines drawn
            ret                         ; done

;---------------------------------------------------------------;
; DrwStr                                                        ;
;                                                               ;
;   Draws a string of characters on the screen                  ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         24th April 2003                             ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       de - the address of the string                          ;
;       hl - the screen address to draw the string              ;
;                                                               ;
; Outputs                                                       ;
;       c  - the number of characters drawn                     ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  de,  hl                                            ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  de,  hl                                            ;
;---------------------------------------------------------------;
DrwStr:     ld c, 0
DrwStrLp1:  ld a, (de)                  ; get character from string
            or a                        ; check character is not end of string
            ret z                       ; return if string is finished
            push de                     ; save string address
            push hl                     ; save screen address
            call DrwChr                 ; draw the character
            pop hl                      ; get the screen address
            pop de                      ; get the string address
            inc de                      ; move to next character in the string
            inc hl                      ; move to next screen position
            inc c
            jr DrwStrLp1

;---------------------------------------------------------------;
; DrwStrP                                                       ;
;                                                               ;
;   Draws a string of characters on the screen at the position  ;
;   stored at the start of the string.                          ;
;   Format: color byte                                          ;
;           column byte                                         ;
;           row bytes                                           ;
;           string bytes                                        ;
;           zero string terminator                              ;
;                                                               ;
;   Restriction: Can only print strings of 2 characters or more ;
;                in length.                                     ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         10th November 2007                          ;
;   Last Changed    10th November 2007                          ;
;                                                               ;
;   Inputs                                                      ;
;       de - the address of the string                          ;
;                                                               ;
; Outputs                                                       ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       de                                                      ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  de,  hl                                            ;
;---------------------------------------------------------------;
DrwStrP:    ld a, (de)                  ; get the color
            inc de
            push af                     ; save the color
            call DrwStrN
            call Attr                   ; convert the screen address to attribute address
            dec c                       ; remove 1 less string character
            ld b, 0                     ; make bc store the length of the string
            pop af                      ; get the string colour
            ld (hl), a                  ; store it at the attribute address
            push hl                     ; save hl
            pop de                      ; and put it into de
            inc de                      ; move to next attribute
            ldir                        ; make all string characters have the same colour                                                 
            ret

;---------------------------------------------------------------;
; DrwStrN                                                       ;
;                                                               ;
;   Draws a string of characters on the screen at the position  ;
;   stored at the start of the string. No color.                ;
;   Format: column byte                                         ;
;           row bytes                                           ;
;           string bytes                                        ;
;           zero string terminator                              ;
;                                                               ;
;   Restriction: Can only print strings of 2 characters or more ;
;                in length.                                     ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         10th November 2007                          ;
;   Last Changed    10th November 2007                          ;
;                                                               ;
;   Inputs                                                      ;
;       de - the address of the string                          ;
;                                                               ;
; Outputs                                                       ;
;       hl - screen address of string                           ;
;                                                               ;
;   Regs Used                                                   ;
;       de                                                      ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  de,  hl                                            ;
;---------------------------------------------------------------;
DrwStrN:    ld a, (de)                  ; get the column position
            sla a                   
            sla a
            sla a                       ; x8 to convert from character position 
            ld c, a                     ; store the pixel X position in c
            inc de                      ; move to the row position                      
            ld a, (de)                  ; get the row position 
            sla a   
            sla a
            sla a                       ; x8 to convert from character position
            ld b, a                     ; store the pixel Y position in b
            inc de                      ; move to start of the string
            call Pix                    ; convert the pixel x,y position into a screen address
            push hl
            call DrwStr                 ; draw the string
            pop hl
            ret



