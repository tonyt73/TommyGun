;---------------------------------------------------------------;
;                                                               ;
;  MATH.ASM                                                     ;
;                                                               ;
;  This file includes several useful math functions             ;
;                                                               ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; IntDiv                                                        ;
;                                                               ;
;   Returns the integer division of 2 16 bit integer numbers    ;
;   Written by Tony Thompson                                    ;
;   Created         10th November 2007                          ;
;   Last Changed    10th November 2007                          ;
;                                                               ;
;   Inputs                                                      ;
;       hl - the numerator (the number to be divide into)       ;
;       de - the divisor   (the number to be divided by )       ;
;                                                               ;
;   Outputs                                                     ;
;        a - the division of hl / de                            ;
;       hl - the remainder of the division                      ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  de, hl                                             ;
;                                                               ;
;   Regs destoryed                                              ;
;       af, hl                                                  ;
;---------------------------------------------------------------;
IntDiv:     xor a                       ; clear A and the carry flag
ID_Lp1:     sbc hl, de                  ; subtract divisor from numerator
            jr c, ID_End                ; if negative then finished
            inc a                       ; count the substraction
            jr ID_Lp1                   ; repeat until negative 
ID_End:     add hl, de                  ; add the divisor back to the numerator
            and a                       ; set/reset the zero flag 
            ret                         ; to make it positive
            
            
;---------------------------------------------------------------;
; Fast RND                                                      ;
;                                                               ;
; An 8-bit pseudo-random number generator,                      ;
; using a similar method to the Spectrum ROM,                   ;
; - without the overhead of the Spectrum ROM.                   ;
;                                                               ;
; R = random number seed                                        ;
; an integer in the range [1, 256]                              ;
;                                                               ;
; R -> (33*R) mod 257                                           ;
;                                                               ;
; S = R - 1                                                     ;
; an 8-bit unsigned integer                                     ;
;                                                               ;
;   Outputs                                                     ;
;       a - random value                                        ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc, r                                              ;
;                                                               ;
;   Regs destoryed                                              ;
;       af, bc                                                  ;
;---------------------------------------------------------------;
seed        defb    0
FastRNG:    ld a, r                     ; get r (ram refresh) register
            ld c, a                     ; c = r
            ld a, (seed)                ; get seed value
            ld b, a                     ; b = seed
            rrca                        ; rotate seed through carry
            rrca
            rrca
            xor 0x1f                    ; toggle bits 0 - 5
            add a, b                    ; add the seed value
            xor c                       ; toggle using the ram refresh value                       
            sbc a, 255                  ; adjust with carry
            ld (seed), a                ; store rnd number as next seed
            ret

