;------------------------------------------------------------------------------;
;                                                                              ;
;  Buddy - UI for ZX Spectrum (compatibles)                                    ;
;                                                                              ;
;  Original graphic design (c) 1999-2000 Andrew Owen                           ;
;  I wrote a GEM windowing system when I was 12yo for the ZX Spectrum and this ;
;  is a following on for something to do. I really enjoyed making the original ;
;  GEM code.                                                                   ;
;  The original GEM code was written using ZEUS on the speccy. It took a long  ;
;  time to write; with all that loading, running, crashing, loading etc.       ;
;                                                                              ;
;  Hopefully this will be just as much fun and just as useless. :-)            ;
;                                                                              ;
;  I never got to making the Windows fully complete; with moving and resizing. ;
;  The menu's were complete and worked well. But at age 12 I didn't understand ;
;  what an event was so everything was hardcoded. It was difficult to create   ;
;  new dynamic windows and menus.                                              ;
;  Hopefully I can change that with this implementation.                       ;
;                                                                              ;
;  Thanks to Andrew Owen.                                                      ;
;  I always wanted to recreate my GEM system and when I saw his interpretation ;
;  of how a ZX GUI would look, I just had to use it and see it in action.      ;
;                                                                              ;
;  Date: October 2013                                                          ;
;                                                                              ;
;------------------------------------------------------------------------------;
 
                org 32768
Start:          scf
                ld a, iCYN
                out (0xFE), a
                ;call DrawBkGnd
                ;call TestFillRect
                ld a, 1
                scf
                call DrawDesktop
                call DDrawIcons
                call CursorSave
                call CursorDraw
                call InitKempstonMouse                
L1:             call KempstonMouse
                ld bc, (CursorX)
                call GuiRectUpdate
                jr L1                 

DrawBkGnd:      ld bc, 6144
                ld hl, 16384
                ld a, $55
                ld c, 192
SL2:            ld b, 32
                push af
                push hl
SL1:            ld (hl), a
                inc hl
                djnz SL1
                pop hl
                call Incy
                pop af
                xor 255
                dec c
                jr nz, SL2
                ld de, 22529
                ld (hl), pCYN
                ld bc, 767
                ldir
                and a 
                ret
                
                
TestFillRect:   ld bc, 1
                ld e, 16
                ld d, 4
TFRL1:          push de
                push bc
                call FillRect
                pop bc
                pop de
                push de
                push bc
                ;halt
                call FillRect
                pop bc
                pop de
                inc e
                ld a, c
                add a, e
                jr nz, TFRL1
                ld e, 16
                inc c
                ld a, 240
                cp c
                jr nz, TFRL1
                ret                 
                
Pause:          ld hl, 0
                ld de, 0
                ld bc, 100
                ldir
                ret
 

; Additional routines
include "display.inc"
include "caret_draw.inc"
include "icon_draw.inc"
include "memory.inc"
include "menus.inc"
include "print_64.inc"
include "print_pro.inc"
include "desktop.inc"
include "controls.inc"
include "gui_checkrect.inc" 
;include "icons.asm"
;include "menus.asm"
;include "controls.asm"
;include "windows.asm"
;include "text.asm"
 
 
; Gfx data
include "icons.inc"
include "font64.inc"
include "fontpro.inc"
include "caret_gfx.inc"
 
                nop
THEEND: defm "THE END" 
end 32768
