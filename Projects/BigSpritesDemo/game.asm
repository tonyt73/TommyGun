;---------------------------------------------------------------;
;                                                               ;
;  GAME.ASM                                                     ;
;  Programmed by Tony Thompson (aka Kiwi)                       ;
;                                                               ;
;  Big Sprite Demo                                              ;
;  This code demostrates several ways to draw very big sprites. ;
;                                                               ;
;---------------------------------------------------------------;

; include debug string macros
include "debugstring.asm"

org 0x8000

DemoStart:      call DrawBackground
                
DS1:            call Read1to5Keys
                jr z, DS1
                bit 0, a               ; is '1' pressed
                jr nz, DoDemoXor
                bit 1, a               ; is '2' pressed
                jr nz, DoDemoMasked
                jr DemoStart

DoDemoXor:      call DemoXor
                jr DemoStart
DoDemoMasked:   call DemoMasked
                jr DemoStart

;---------------------------------------------------------------;
; ShowLoadingScreen                                             ;  
; Show a loading screen$ for 5 seconds                          ;
;---------------------------------------------------------------;
DrawBackground: ld hl, background + SCRLEN + ATTRLEN
                ld de, SCREEN + SCRLEN + ATTRLEN
                ld bc, SCRLEN + ATTRLEN
                lddr                        ; draw screen backwards
                ret

; Include libraries
include "libspritexor.asm"
include "libspritemasked.asm"
include "libscreen.asm"
include "libinput.asm"

; Include graphics
org 0xA000
include "background.inc"
include "spritesxor.inc"
include "spritesmasked.inc"

end 0x8000
