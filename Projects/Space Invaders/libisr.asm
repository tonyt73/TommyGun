;---------------------------------------------------------------;
;                                                               ;
;   Interrupt Service Routines                                  ;
;                                                               ;
; This file adds an interrupt service routine.                  ;
;                                                               ;
;---------------------------------------------------------------;

                org 24317
start:          jp GameStart
;
; Interrupt Mode 2 - Interrupt Vector Table
;
; ISR routine is at 96 * 256 + 96 = 0x6060 = 24672 (ISR)
;
ISR_VEC_TABLE:  defs 257, 96

;---------------------------------------------------------------;
; ISR_Start                                                     ;
;   Save the original ISR and start the IM 2 interrupts         ;
;---------------------------------------------------------------;
ISR_Start:      di                  ; disable interrupts
                ld a, i             ; a = i
                ld (ISR_I), a       ; save i in ISR_I
                ld hl, ISR_VEC_TABLE; hl = ISR_VEC_TABLE
                ld a, h             ; a = high byte
                ld i, a             ; set i = h
                im 2                ; interrupt mode 2
                ei                  ; enable interrupts
                ret

;---------------------------------------------------------------;
; ISR_Stop                                                      ;
;   Restore the original ISR and stop the IM 2 interrupts       ;
;---------------------------------------------------------------;
ISR_Stop:       di                  ; disble interrupts
                ld a, (ISR_I)       ; get original ISR_I (i) value
                ld i, a             ; load i with original value
                im 1                ; interrupt mode 1
                ei                  ; enable interrupts
                ret

;---------------------------------------------------------------;
; Interrupt service routine variables                           ;
;---------------------------------------------------------------;
ISR_I           defb 0              ; The original value of the i register
ISRCounter:     defw 0              ; the number of interrupts processed
                
                ; decrease this by the size of any new variables added above
                ; so the ISR routine is always at 0x6060 (96,96)
                defs 66
;---------------------------------------------------------------;
; ISR                                                           ;
;   Interrupt Service Routine                                   ;
;                                                               ;
; Saves all the registers                                       ;
; calls Move the Player                                         ;
; Restores all the registers                                    ;
;                                                               ;
;---------------------------------------------------------------;
                ; This should be at address 0x6060 (96 * 256 + 96) 24672
                ; !!! Check the game.map file !!!
ISR:            di                  ; disable interrupts
                push af             ; save all std regs
                push bc
                push de
                push hl
                push ix             ; save ix & iy
                push iy
                ex af, af'          ; and shadow af
                push af
                call MovePlayer     ; move the player
                ld hl, (ISRCounter) ; get the value of ISR Counter
                inc hl              ; increment it - 50 per second, 250 = 5 secs
                ld (ISRCounter), hl ; save the counter
                call PlaySound      ; play next sound                
ISR1:           pop af
                ex af, af'          ; restore af
                pop iy
                pop ix              ; restore ix & iy
                pop hl 
                pop de
                pop bc
                pop af              ; restore all std regs
                ei                  ; enable interrupts
                reti                ; done

            