;---------------------------------------------------------------;
;                                                               ;
;   Interrupt Service Routines                                  ;
;                                                               ;
; This file adds an interrupt service routine to call the AY    ;
; sound player.                                                 ;
;                                                               ;
;---------------------------------------------------------------;


org 24317
start:          jp main
;
; Interrupt Mode 2 - Interrupt Vector Table
;
; ISR routine is at 96 * 256 + 96 = 24672
;
ISR_VEC_TABLE:  defs 257, 96
; The original value of the i register
ISR_I           defb 0
;---------------------------------------------------------------;
; ISR_Start                                                     ;
;   Save the original ISR and start the IM 2 interrupts         ;
;---------------------------------------------------------------;
ISR_Start:      di
                ld a, i
                ld (ISR_I), a
                ld hl, ISR_VEC_TABLE
                ld a, h
                ld i, a
                im 2
                ei
                ret

;---------------------------------------------------------------;
; ISR_Stop                                                      ;
;   Restore the original ISR and stop the IM 2 interrupts       ;
;---------------------------------------------------------------;
ISR_Stop:       di
                ld a, (ISR_I)
                ld i, a
                im 1
                ei
                ret
;---------------------------------------------------------------;
; ISR                                                           ;
;   Interrupt Service Routine                                   ;
;                                                               ;
; Saves all the registers                                       ;
; calls the AY Player                                           ;
; Restores all the registers                                    ;
;                                                               ;
;---------------------------------------------------------------;
                defs 73
                ;org 24929
ISR:            di                  ; disable interrupts
                push af             ; save all std regs
                push bc
                push de
                push hl
                push ix             ; save ix & iy
                push iy
                ex af, af'          ; and shadow af
                push af
                call SND_PLAY       ; play the current tune
                pop af
                ex af, af'          ; restore af
                pop iy
                pop ix              ; restore ix & iy
                pop hl
                pop de
                pop bc
                pop af              ; restore all std regs
                ei                  ; enable interrupts
                ret                 ; done

            