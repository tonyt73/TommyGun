;---------------------------------------------------------------;
;                                                               ;
;   Math.inc                                                    ;
;                                                               ;
;   This file contains routines for dealing with arithmetic     ;
;   math routines                                               ;
;                                                               ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; Table used for fast division by 24                            ;
;---------------------------------------------------------------;
Div24Table:     defb 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                defb 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                defb 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                defb 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                defb 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
                defb 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
                defb 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
                defb 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
                defb 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
                defb 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
                defb 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
                defb 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
                defb 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
                defb 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
                defb 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
                defb 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
                defb 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
                defb 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7

;---------------------------------------------------------------;
; Snap24                                                        ;
;                                                               ;
;   This function snaps a value to the nearest pixel on a 24    ;
;   pixel boundary                                              ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         1984                                        ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;                                                               ;
;   Outputs                                                     ;
;       a - the value snapped to the 24 grid value              ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af, hl                                                  ;
;---------------------------------------------------------------;
Snap24:         push bc             ; save the bc reg
                ld c, a             ; get value to snap into c reg
                ld b , 0            ; reset b reg
                ld hl, Div24Table   ; point hl to the div24 table
                add hl, bc          ; point hl to the value / 24
                ld a, (hl)          ; get the value / 24 from the table
                sla a               ; a * 2
                sla a               ; a * 4
                sla a               ; a * 8
                ld e, a             ; e = a * 8
                sla a               ; a * 16
                add a, e            ; a = a + e [a * 24] (or a = (a * 8) + (a * 16))
                pop bc              ; restore bc
                ret
