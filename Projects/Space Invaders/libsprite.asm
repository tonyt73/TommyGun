;---------------------------------------------------------------;
;                                                               ;
;  SPRITE.ASM                                                   ;
;                                                               ;
;  This file includes several useful sprite functions           ;
;                                                               ;
;---------------------------------------------------------------;

USE_DRWSPRNC            equ     ON
SUPPORT_ODD_WIDTH       equ     OFF

;---------------------------------------------------------------;
; DrwSprNC                                                      ;
;                                                               ;
;   Draws a sprite with no color ATTR onto the screen           ;
;   off screen buffer                                           ;
;   If the colour supplied is 0 then no colour is applied.      ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         3rd April 2004                              ;
;   Last Changed    3rd April 2004                              ;
;                                                               ;
;   Inputs                                                      ;
;       a  - the color of the sprite                            ;
;       b  - the y position of the sprite                       ;
;       c  - the x position of the sprite                       ;
;       hl - the address of the sprite data                     ;
;                                                               ;
; Outputs                                                       ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  de,  hl                                       ;
;---------------------------------------------------------------;
IF USE_DRWSPRNC
Scrolls:    defb 0                      ; the number of scrolls to do when drawing a sprite
DrwSprNC:   ex af, af'                  ; save the sprite color
            ld a, c                     ; do we need to scroll the sprite into position?
            and 7                       ; set z flag
            jr z, DSNCfast              ; if zero is set,  then we can draw the sprite the fast way
                                        ; need to draw the sprite the slow way
DSNCslow:   ;
            ; draw the pixels for the sprite
            ;
            ld (Scrolls), a             ; save the scroll count
            push bc                     ; save the sprite position (pos)
            push bc                     ; save the sprite position again (pos, pos)
            push hl                     ; save the sprite data address (pos, pos, spr)
            call Pix                    ; convert the position to an screen address
            ex de,  hl                  ; put the off screen address into de
            pop hl                      ; get the sprite data address into hl (pos, pos)
            pop bc                      ; get the sprite position (pos)
            ld c, (hl)                  ; put sprite width into c
            inc hl                      ; move to sprite height
            ld b, (hl)                  ; put the sprite height into b
            inc hl                      ; move to the sprite data
            push bc                     ; save the size of the sprite (pos, size)
            ;
            ; sprite width is even and we can draw this easier than an odd width
            ; hl - sprite data
            ; de - screen address
            ; bc - sprite size
            ;
DSNCslow0:  push bc                     ; save the size of the sprite (pos, size, size)
            push de                     ; save the screen (pos, size, scr)
DSNCslow1:  push bc                     ; save the size of the sprite (pos, size, size, scr, size)
            ld b, (hl)                  ; load b with sprite data
            inc hl                      ; move to next sprite data
            ld c, (hl)                  ; load c with sprite data
            inc hl                      ; move to next sprite data
            push hl                     ; save the sprite address (pos, size, size, scr, size, spr)
            ld a, (Scrolls)             ; put the number of scrolls into d
            ld l, 0
DSNCslow2:  srl b                       ; scroll b
            rr c                        ; scroll b into c
            rr l                        ; and scroll c into l
            dec a                       ; dec the counter
            jr nz, DSNCslow2            ; keep scrolling until complete
            ld a, (de)                  ; get pixels from screen
            xor b                       ; merge in some of left byte of sprite
            ld (de), a                  ; store result
            inc e                       ; next screen address
            ld a, (de)                  ; get pixels from screen
            xor c                       ; merge in some left and some right pixels of sprite
            ld (de), a                  ; store result
            inc e                       ; next screen address
            ld a, (de)                  ; get pixels from screen
            xor l                       ; merge in the last of the right pixels of sprite
            ld (de), a                  ; store result
            dec e                       ; move back 1 character
            pop hl                      ; get the sprite addr (pos, size, size, scr, size)
            pop bc                      ; get the sprite size (pos, size, size, scr)
            dec c                       ; completed 1st character
            dec c                       ; completed 2nd character
            jr nz, DSNCslow1            ; loop back and complete the sprite if we are not finished
            pop de                      ; restore the screen pointer (pos, size, size)
            ex de, hl                   ; hl = scr addr,  de = spr addr
            call Incy                   ; move down 1 line in the off screen buffer
            ex de, hl                   ; de = scr addr,  hl = spr addr
            pop bc                      ; get the size of the sprite (pos, size)
            djnz DSNCslow0              ; draw all lines
DSNCattr:   pop de                      ; put the size into de	(pos)
            pop bc                      ; put the position into bc ()
            srl d                       ; div d by 2
            srl d                       ; div d by 4
            srl d                       ; div d by 8
            inc d                       ; add a extra character block to the height
            inc e                       ; and the width
            jr DSNCAttrs                ; set the ATTR

DSNCfast:   ;
            ; draw the pixels for the sprite
            ;
            push bc                     ; save the sprite position (pos)
            push bc                     ; save the sprite position again (pos, pos)
            push hl                     ; save the sprite data address (pos, pos, spr)
            call Pix                    ; convert the position to an off screen address
            ex de,  hl                  ; put the off screen address into de
            pop hl                      ; get the sprite data address into hl (pos, pos)
            pop bc                      ; get the sprite position (pos)
            ld c, (hl)                  ; put sprite width into c
            inc hl                      ; move to sprite height
            ld b, (hl)                  ; put the sprite height into b
            inc hl                      ; move to the sprite data
            push bc                     ; save the size of the sprite (pos, size)
DSNCfast1:  push bc                     ; save the size of the sprite	(pos, size, size)
            push de                     ; save the off screen address (pos, size, size, scr)
            ld b, c                     ; place the sprite width into b
DSNCfast2:  
IF 0        
            ld a, (de)                  ; get the screen contents
            xor (hl)                    ; merge the sprite data
            ld (de), a                  ; place data onto the screen
            inc e                       ; move to next screen position
            inc hl                      ; move to next sprite data
ELSE
            ldi
ENDIF            
            djnz DSNCfast2              ; draw the entire line onto the screen
            ex de, hl                   ; put the sprite address into de
            pop hl                      ; restore the off screen address into hl (pos, size, size)
            call Incy                   ; move the screen buffer address to the next line
            ex de, hl                   ; place the screen addr into de,  and the sprite addr into hl
            pop bc                      ; get the sprite size into bc (pos, size)
            djnz DSNCfast1              ; draw all lines of the sprite
            pop de                      ; put the sprite size into de (pos)
            srl d                       ; div d by 2
            srl d                       ; div d by 4
            srl d                       ; div d by 8
            inc d
            pop bc                      ; put the sprite position into bc ()
            ;
            ; draw the ATTR for the sprite
            ;
            ; bc - position of sprite in pixels
            ; de - the size of the sprite in characters
            ;
DSNCAttrs:  ex af, af'                  ; get the color of the sprite
            and a                       ; is it zero?
            ret z                       ; if so,  no need to draw ATTR
IF USE_MATTR2
            ex af, af'                  ; save the color
            push bc                     ; save the sprite position (pos)
            call MAttr2                 ; get the offscreen attribute address of the position
            pop bc                      ; restore the sprite position into bc ()
            push hl                     ; save the attr addr (attr)
            call Pix                    ; convert bc to a screen addr
            call Attr                   ; convert hl to a screen attr address
            ld b, d                     ; put the sprite height into b
            ld c, e                     ; put the sprite width  into c
            pop de                      ; put the off screen attr addr into de ()
DSNCAttrs1: push de                     ; save the off screen attr addr (osattr)
            push bc                     ; save the sprite size (osattr, size)
            ld b, c                     ; put the sprite width into b
            push hl                     ; save the attr address (osattr, size, attr)
DSNCAttrs2: ld a, (de)                  ; get the off screen attribute
            inc de                      ; move the attr pointer
            and a                       ; check for zero
            jr nz, DSNCSkip             ; if its zero,  we can set the screen attr
            ex af, af'                  ; get the color of the sprite
            ld (hl), a                  ; replace the attr with the new sprite color
            ex af, af'                  ; save the color of the sprite
DSNCSkip:   inc hl                      ; move to next attr
            djnz DSNCAttrs2             ; do all the ATTR in the row
            pop hl                      ; restore the attr address (osattr, size)
            ld bc,  SCRWIDTH            ; place the off screen buffer width into bc
            add hl, bc                  ; move down 1 line of ATTR
            ex de, hl                   ; de = scr attr
            pop bc                      ; restore the sprite size (osattr)
            pop hl                      ; load hl with the off screen attr addr
            push bc                     ; save the sprite size (size)
            ld bc,  SCRWIDTH            ; place the off screen buffer width into bc
            add hl, bc                  ; move to the next line in the off screen attrs
            ex de, hl                   ; de = off screen attr,  hl = scr attr
            pop bc                      ; get the sprite size into bc
            djnz DSNCAttrs1             ; draw all the lines of ATTR
ENDIF ; USE_MATTR2
            ret
ENDIF ; USE_DRWSPRNC

;---------------------------------------------------------------;
; DrwSpr16                                                      ;
;                                                               ;
;   Draws a 16 pixel wide sprite with no color onto the screen  ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         21st March 2015                             ;
;   Last Changed    21st March 2015                             ;
;                                                               ;
;   Inputs                                                      ;
;       b  - the y position of the sprite                       ;
;       c  - the x position of the sprite                       ;
;       hl - the address of the sprite data                     ;
;                                                               ;
; Outputs                                                       ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  de,  hl                                       ;
;---------------------------------------------------------------;
EraseEdge:  defb 0
SetErase:   ld a, 1
            ld (EraseEdge), a
            ret

DrwSpr16:   ld a, c                     ; do we need to scroll the sprite into position?
            and 7                       ; set z flag
            jr z, DS16fast              ; if zero is set,  then we can draw the sprite the fast way
DS16slow:   ld (Scrolls), a             ; save the scroll count
            push hl                     ; save the sprite data address                      (spr)
            call Pix                    ; convert the position to an screen address
            ex de,  hl                  ; put the off screen address into de
            pop hl                      ; get the sprite data address into hl               ()
            inc hl                      ; move to sprite height
            ld b, (hl)                  ; put the sprite height into b
            inc hl                      ; move to the sprite data
DS16slow0:  push bc                     ; save the size of the sprite                       (size)
            push de                     ; save the screen                                   (size, scr)
            ; scroll 16 bits of sprite data into 3 bytes 
            ld b, (hl)                  ; load b with sprite data
            inc hl                      ; move to next sprite data
            ld c, (hl)                  ; load c with sprite data
            inc hl                      ; move to next sprite data
            push hl                     ; save the sprite address                           (size, scr, spr)
            ld a, (Scrolls)             ; put the number of scrolls into a
            ld l, 0
DS16slow2:  srl b                       ; scroll b
            rr c                        ; scroll b into c
            rr l                        ; and scroll c into l
            dec a                       ; dec the counter
            jr nz, DS16slow2            ; keep scrolling until complete
            ; put sprite data onto screen
            ld a, (EraseEdge)           ; are we erasing an edge?
            and a                       ; test if erasing
            jr nz, DS16s1               ; if erasing goto DS16s1
            ld a, (de)                  ; get pixels from screen
            xor b                       ; merge in some of left byte of sprite
            jr DS16s2                   ; jump to drawing the sprite
DS16s1:     ld a, b                     ; get left edge pixels
DS16s2:     ex de, hl                   ; hl = scr addr, de = spr addr
            ld (hl), a                  ; store result
            inc l                       ; next screen address
            ld (hl), c                  ; store result
            inc l                       ; next screen address
            ld (hl), e                  ; store result
            ex de, hl                   ; de = scr addr,  hl = spr addr
            pop hl                      ; get the sprite addr                               (size, scr)
            pop de                      ; restore the screen pointer                        (size)
            ex de, hl                   ; hl = scr addr,  de = spr addr
            call Incy                   ; move down 1 line in the off screen buffer
            ex de, hl                   ; de = scr addr,  hl = spr addr
            pop bc                      ; get the size of the sprite                        ()
            djnz DS16slow0              ; draw all lines
            xor a
            ld (EraseEdge), a
            ret
            
DS16fast:   ;
            ; draw the pixels for the sprite
            ;
            push hl                     ; save the sprite data address (spr)
            call Pix                    ; convert the position to an off screen address
            ex de,  hl                  ; put the off screen address into de
            pop hl                      ; get the sprite data address into hl               ()
            inc hl                      ; move to sprite height
            ld b, (hl)                  ; put the sprite height into b
            inc hl                      ; move to the sprite data
DS16fast1:  push de                     ; save the screen address                           (scr)
            ldi                         ; copy the sprite data to the screen
            ldi
            ex de, hl                   ; put the sprite address into de
            pop hl                      ; restore the screen address into hl                ()
            call Incy                   ; move the screen buffer address to the next line
            ex de, hl                   ; place the screen addr into de, and the sprite addr into hl
            djnz DS16fast1              ; draw all lines of the sprite
            ret

EraseMasks: defb $00, $ff                
            defb $80, $7f                 
            defb $c0, $3f                
            defb $e0, $1f                 
            defb $f0, $0f                 
            defb $f8, $07                
            defb $fc, $03
            defb $fe, $01
            defb $ff, $00
;
; Erase a 16x8 sprite (aka, alien)
;            
ErzSpr16:   ld a, c                     ; do we need to scroll the sprite into position?
            and 7                       ; set z flag
            jr z, ES16fast              ; if zero is set,  then we can erase the sprite the fast way
            ;
            ; erase the sprite 3 bytes x 8 lines at a time
            ;
ES16L1:     ex af, af'
            call Pix                    ; convert the position into a screen address
            ex af, af'
            ld c, a
            ld b, 0
            ld ix, EraseMasks
            add ix, bc
            add ix, bc
            ld e, (ix + 0)              ; e = left mask
            ld d, (ix + 1)              ; d = right mask
            ld b, 8                     ; put the sprite height into b
            ; erase sprite from screen
ES16L2:     ld a, (hl)                  ; get pixels from screen
            and e                       ; mask left of sprite
            ld (hl), a                  ; put result on screen
            inc l                       ; next screen address
            ld (hl), 0                  ; erase the middle of the sprite
            inc l                       ; next screen address
            ld a, (hl)                  ; get pixels from screen
            and d                       ; mask right of sprie
            ld (hl), a                  ; put result on screen
            dec l                       ; restore screen address
            dec l                       ; to start of sprite
            call Incy                   ; move down 1 line in the screen buffer
            djnz ES16L2                 ; erase all lines
            ret
            
ES16fast:   ;
            ; erase the pixels for the sprite
            ; within a 2x1 character block
            ;
            call Pix                    ; convert the position to an off screen address
            ld b, 8                     ; put the sprite height into b
ES16fast1:  ld (hl), 0
            inc l
            ld (hl), 0
            dec l
            call Incy                   ; move the screen buffer address to the next line
            djnz ES16fast1              ; draw all lines of the sprite
            ret

;---------------------------------------------------------------;
; DrwSpr8                                                       ;
;                                                               ;
;   Draws a 8 pixel wide sprite with no color onto the screen   ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         18th Feburary 2016                          ;
;   Created         18th Feburary 2016                          ;
;                                                               ;
;   Inputs                                                      ;
;       b  - the y position of the sprite                       ;
;       c  - the x position of the sprite                       ;
;       hl - the address of the sprite data                     ;
;                                                               ;
; Outputs                                                       ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  de,  hl                                       ;
;---------------------------------------------------------------;
DrwSpr8:    inc hl                      ; skip width
            ld a, c                     ; do we need to scroll the sprite into position?
            and 7                       ; set z flag
            jr z, DS8fast               ; if zero is set,  then we can draw the sprite the fast way
            ex de, hl                   ; de = sprite data
            call Pix                    ; hl = screen                    
            ld c, a                     ; save the number of rotations needed. c = rotations
            ld a, (de)                  ; get height
            ld b, a                     ; b = height            
DS8s1:      push bc                     ; save height count, rotations
            ld a, (de)                  ; get sprite data
            inc de                      ; point to next sprite data
            ld b, c                     ; get scroll count
            ld c, 0                     ; reset c to 0
DS8s2:      srl a                       ; scroll a
            rr c                        ; scroll a into c
            djnz DS8s2                  ; scroll all bits                  
            ld (hl), a                  ; store result on screen
            inc l                       ; move forward 1 character
            ld a, c                     ; get scrolled sprite data 
            ld (hl), a                  ; store result on screen
            dec l                       ; move back 1 character
            call Incy                   ; move down 1 line
            pop bc                      ; get height count, get scroll count 
            djnz DS8s1                  ; loop for all sprite height
            ret                        
            
DS8fast:    ex de, hl
            call Pix
            ld a, (de)                  ; get height
            ld b, a                     ; b = height
            inc de                      ; point to sprite data
DS8f1:      ld a, (de)                  ; get sprite data
            ld (hl), a                  ; save to screen
            call Incy                   ; down 1 line
            inc de                      ; next sprite data
            djnz DS8f1                  ; repeat all lines
            ret

; hl = sprite                       
ErzSpr8:    inc hl
            ld d, (hl)
            call Pix
            ld b, d
ES8f1:      ld (hl), 0
            inc l
            ld (hl), 0
            dec l
            call Incy
            djnz ES8f1
            ret
            