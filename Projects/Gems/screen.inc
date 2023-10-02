;---------------------------------------------------------------;
;                                                               ;
;   Screen.inc                                                  ;
;                                                               ;
;   This file contains routines for dealing with the            ;
;   ZX Spectrum screen                                          ;
;                                                               ;
;---------------------------------------------------------------;
;                                                               ;
;   Routines                                                    ;
;                                                               ;
;=== CoordAttr =================================================;
; Converts a screen pixel coordinate into a screen attr address ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;   Outputs                                                     ;
;      hl - the attribute address for the screen location       ;
;                                                               ;
;=== Attr ======================================================;
; Converts a screen pixel address into a screen attr address    ;
;   Inputs                                                      ;
;      hl - screen pixel address                                ;
;   Outputs                                                     ;
;      hl - the attribute address for the screen location       ;
;                                                               ;
;=== Pix =======================================================;
;   Converts a screen pixel coord into a screen address and     ;
;   pixel position                                              ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;   Outputs                                                     ;
;      hl - the screen address for the screen location          ;
;      a  - contains the bit position of the pixel              ;
;                                                               ;
;=== ClrScr ====================================================;
;   Clears the screen to black paper and black ink              ;
;                                                               ;
;=== PlotPoint =================================================;
;   Plots a pixel on the screen                                 ;
;   Inputs                                                      ;
;       b - y position                                          ;
;       c - x position                                          ;
;                                                               ;
;=== Incy ======================================================;
;   Moves the screen address down 1 line                        ;
;   Inputs                                                      ;
;       hl - the address of a screen location                   ;
;   Outputs                                                     ;
;       hl - the address of the line below                      ;
;                                                               ;
;=== DrwTile ===================================================;
;   Draws a tile object on the screen                           ;
;   Inputs                                                      ;
;       hl - the address of the tile to draw                    ;
;       b  - the y position of the tile on the screen           ;
;       c  - the x position of the tile on the screen           ;
;       a  - 0 - draw attributes, non-zero don't draw           ;
;                                                               ;
;=== DrwSprNC ==================================================;
;   Draws a sprite with no color ATTR onto the screen           ;
;   off screen buffer                                           ;
;   Inputs                                                      ;
;       a  - the color of the sprite                            ;
;            if zero, then no attributes drawn                  ;
;       b  - the y position of the sprite                       ;
;       c  - the x position of the sprite                       ;
;       hl - the address of the sprite data                     ;
;                                                               ;
;=== ErasePointer ==============================================;
;   Erases the arrow mouse pointer on the screen by restoring   ;
;   the contents under the pointer                              ;
;   Inputs                                                      ;
;       b  - the y position of the pointer                      ;
;       c  - the x position of the pointer                      ;
;                                                               ;
;=== SavePointer ===============================================;
;   Saves the contents of the screen under the pointer          ;
;   This allows the ErasePointer function to restore the screen ;
;   contents later                                              ;
;   Inputs                                                      ;
;       b  - the y position of the pointer                      ;
;       c  - the x position of the pointer                      ;
;                                                               ;
;=== DrawPointer ===============================================;
;   Draws the masked mouse pointer onto the screen              ;
;   This is a specialized version of the generic sprite code    ;
;   from DrwSprNC above.                                        ;
;   Inputs                                                      ;
;       b  - the y position of the pointer                      ;
;       c  - the x position of the pointer                      ;
;                                                               ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
;                                                               ;
; DEFINES                                                       ;
;                                                               ;
;---------------------------------------------------------------;
SCREEN:         equ 16384               ; spectrum display memory address
ATTR:           equ 22528               ; address of the attributes
PAUSETIME:      equ 10000               ; time of pause
SCRLEN:         equ 6144                ; size of the screen pixels in bytes
ATTRLEN:        equ 768                 ; size of the ATTR in bytes
SCRWIDTH:       equ 32                  ; number of character the offscreen buffer is wide

;---------------------------------------------------------------;
; CoordAttr                                                     ;
;                                                               ;
;   Converts a screen pixel coord into a screen attr address    ;
;   Written by Tony Thompson                                    ;
;   Created         1984                                        ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;                                                               ;
;   Outputs                                                     ;
;       hl - the attribute address for the screen location      ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  hl                                            ;
;---------------------------------------------------------------;
CoordAttr:      push de
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
                ld de,  ATTR
                add hl, de
                pop de
                ret

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
Attr:       ld a, h                 ; get the high byte of screen address
            rra                     ; divide h by 8
            rra                     ;
            rra                     ;
            and 3                   ; keep lower 3 bits,  these mimick the lower 4 bits of the attribute address
            or 0x58                 ; set the high order byte to the start of the attribute block
            ld h, a                 ; load the result into h
            ret                     ; hl now contains the attribute address

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
;       hl - the screen address for the screen location         ;
;       a  - contains the bit position of the pixel             ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  hl                                            ;
;                                                               ;
;   Regs destoryed                                              ;
;       af                                                      ;
;---------------------------------------------------------------;
Pix:            ld a, b
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

;---------------------------------------------------------------;
; PlotPoint                                                     ;
;                                                               ;
;   Plots a pixel on the screen                                 ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         29th April 2006                             ;
;   Last Changed    29th April 2006                             ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position                                          ;
;       c - x position                                          ;
;                                                               ;
;   Regs Used                                                   ;
;       af, e, bc,  hl                                          ;
;                                                               ;
;   Regs destoryed                                              ;
;       af, bc,  e,  hl                                         ;
;---------------------------------------------------------------;
PlotPoint:      call Pix
                ld e, a
                and a
                ld a, 128
                jr z, PPSkip
                ld b, e
PP1Loop:        rr a
                djnz PP1Loop
PPSkip:         xor (hl)
                ld (hl), a
                ret


ClearBoard:     push bc
                push de
                push hl
                ;
                ; clear the attributes
                ;
                ld b, 24
                ld hl, 22528 + 8
CB_Lp3:         push bc
                ld b, 24
CB_Lp4:         ld (hl), 0
                inc hl
                djnz CB_Lp4
                ld bc, 8
                add hl, bc
                pop bc
                djnz CB_Lp3
                pop hl
                pop de
                pop bc
                ret

;---------------------------------------------------------------;
; ClrScr                                                        ;
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
ClrScr:     push bc                     ; save bc
            push de                     ; save de
            push hl                     ; save hl
                                        ; clear the ATTR first - makes for a smoother clear
            ld hl,  ATTR                ; point hl to screen address
            ld de,  ATTR+1              ; point de to screen address + 1
            ld bc,  ATTRLEN-1           ; load bc with the size of the screen - 1
            ld (hl), 71                 ; clear the first element of the screen
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

;---------------------------------------------------------------;
; DrwTile                                                       ;
;                                                               ;
;   Draws a tile object on the screen                           ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         24th April 2003                             ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       hl - the address of the tile to draw                    ;
;       b  - the y position of the tile on the screen           ;
;       c  - the x position of the tile on the screen           ;
;       a  - 0 - draw attributes, non-zero don't draw           ;
;                                                               ;
;Outputs                                                        ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       hl,  de,  bc,  af                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  de,  hl                                       ;
;---------------------------------------------------------------;
DrwTile:    push af
            ld e, (hl)                  ; read the width of the tile
            inc hl                      ; move to height
            ld d, (hl)                  ; read the height of the tile
            inc hl                      ; hl now points to the tile data,  and de contains the size of the tile
            push bc                     ; save the position of the tiles
            push hl                     ; save tile address
            call Pix                    ; convert bc position into screen address
            push de                     ; push size onto stack
            pop bc                      ; and put size into bc
            pop de                      ; put tile address into de
            push hl                     ; save the screen address
            push bc                     ; save the size
            sla b                       ; convert character height to
            sla b                       ; pixel height by muliplying the
            sla b                       ; character height by 8
dt1:        push bc                     ; save the size
            push hl                     ; save the screen address
            ex de, hl                   ; swap screen addr and tile addr (hl - tile)
            ld b, 0                     ; load b with zero,  now bc contains width
            ldir                        ; block transfer the tile to the screen
            ex de, hl                   ; swap screen addr and tile addr back again (de - tile)
            pop hl                      ; get the 1st column screen address
            call Incy
            pop bc                      ; get the size
            djnz dt1                    ; draw all lines of the tile
            pop bc                      ; get the size
            pop hl                      ; get the top/left screen address
            pop af                      ; put position into af
            push bc                     ; save size
            push af                     ; save position
            pop bc                      ; put position back into bc
            call Attr                   ; convert tile pos to attribute address
            pop bc                      ; put size back into bc
            pop af                      ; get attribute draw flag
            and a                       ; set zero flag
            ret nz                      ; return if we are NOT to draw attributes
dt2:        push bc                     ; save the size
            push hl                     ; save the attr address
            ld b, 0                     ; make bc contain only the width
            ex de, hl                   ; swap attr addr and tile addr
            ldir                        ; block transfert the attr data
            ex de, hl                   ; swap attr addr and tile addr back again
            pop hl                      ; get 1st column attr address
            ld c, 32                    ; ld bc with width of screen
            add hl, bc                  ; goto the next line down
            pop bc                      ; put currently drawn size into bc
            djnz dt2                    ; do all the lines of attr's
            ret                         ; finished drawing tile

;---------------------------------------------------------------;
; DrwSprNC                                                      ;
;                                                               ;
;   Draws a sprite with no color ATTR onto the screen           ;
;   screen buffer                                               ;
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
Scrolls:        defb 0                      ; the number of scrolls to do when drawing a sprite
DrwSprNC:       ex af, af'                  ; save the sprite color
                ld a,  c                    ; do we need to scroll the sprite into position?
                and 7                       ; set z flags
                jr z, DSNCfast              ; if zero if set,  then we can draw the sprite the fast way
                                            ; need to draw the sprite the slow way
DSNCslow:       ;
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
                srl c                       ; div c by 2
                srl c                       ; div c by 4
                srl c                       ; div c by 8 into total
                inc hl                      ; move to sprite height
                ld b, (hl)                  ; put the sprite height into b
                inc hl                      ; move to the sprite data
                push bc                     ; save the size of the sprite (pos, size)
                bit 0,  c
                jr nz,  DSNCodd
                ;
                ; sprite width is even and we can draw this easier than an odd width
                ; hl - sprite data
                ; de - screen address
                ; bc - sprite size
                ;
DSNCslow0:      push bc                     ; save the size of the sprite (pos, size, size)
                push de                     ; save the screen (pos, size, scr)
DSNCslow1:      push bc                     ; save the size of the sprite (pos, size, size, scr, size)
                ld b, (hl)                  ; load b with sprite data
                inc hl                      ; move to next sprite data
                ld c, (hl)                  ; load c with sprite data
                inc hl                      ; move to next sprite data
                push hl                     ; save the sprite address (pos, size, size, scr, size, spr)
                ld a, (Scrolls)             ; put the number of scrolls into d
                ld l, 0
DSNCslow2:      srl b                       ; scroll b
                rr c                        ; scroll b into c
                rr l                        ; and scroll c into l
                dec a                       ; dec the counter
                jr nz, DSNCslow2            ; keep scrolling until complete
                ld a, (de)                  ; get pixels from screen
                xor b                       ; merge in some of left byte of sprite
                ld (de),  a                 ; store result
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
                jr DSNCattr

DSNCodd:        ;
                ; draw a sprite what has an odd width
                ; hl - sprite data
                ; de - screen address
                ; bc - sprite size
                ;

DSNCattr:       pop de                      ; put the size into de	(pos)
                pop bc                      ; put the position into bc ()
                srl d                       ; div d by 2
                srl d                       ; div d by 4
                srl d                       ; div d by 8
                inc d                       ; add a extra character block to the height
                inc e                       ; and the width
                jr DSNCAttrs                ; set the ATTR

DSNCfast:       ;
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
                srl c                       ; div c by 2
                srl c                       ; div c by 4
                srl c                       ; div c by 8 into total
                inc hl                      ; move to sprite height
                ld b, (hl)                  ; put the sprite height into b
                inc hl                      ; move to the sprite data
                push bc                     ; save the size of the sprite (pos, size)
DSNCfast1:      push bc                     ; save the size of the sprite	(pos, size, size)
                push de                     ; save the off screen address (pos, size, size, scr)
                ld b, c                     ; place the sprite width into b
DSNCfast2:      ld a, (de)                  ; get the screen contents
                xor (hl)                    ; merge the sprite data
                ld (de), a                  ; place data onto the screen
                inc e                       ; move to next screen position
                inc hl                      ; move to next sprite data
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
DSNCAttrs:      ex af, af'                  ; get the color of the sprite
                and a                       ; is it zero?
                ret z                       ; if so,  no need to draw ATTR
                ex af, af'                  ; save the color
                push hl                     ; save the attr addr (attr)
                call Pix                    ; convert bc to a screen addr
                call Attr                   ; convert hl to a screen attr address
                ld b, d                     ; put the sprite height into b
                ld c, e                     ; put the sprite width  into c
                pop de                      ; put the off screen attr addr into de ()
DSNCAttrs1:     push de                     ; save the off screen attr addr (osattr)
                push bc                     ; save the sprite size (osattr, size)
                ld b, c                     ; put the sprite width into b
                push hl                     ; save the attr address (osattr, size, attr)
DSNCAttrs2:     ld a, (de)                  ; get the off screen attribute
                inc de                      ; move the attr pointer
                and a                       ; check for zero
                jr nz, DSNCSkip             ; if its zero,  we can set the screen attr
                ex af, af'                  ; get the color of the sprite
                ld (hl), a                  ; replace the attr with the new sprite color
                ex af, af'                  ; save the color of the sprite
DSNCSkip:       inc hl                      ; move to next attr
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
                ret


;---------------------------------------------------------------;
; ErasePointer                                                  ;
;                                                               ;
;   Erases the arrow mouse pointer on the screen by restoring   ;
;   the contents under the pointer                              ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created        29th April 2006                              ;
;   Last Changed   29th April 2006                              ;
;                                                               ;
;   Inputs                                                      ;
;       b  - the y position of the pointer                      ;
;       c  - the x position of the pointer                      ;
;                                                               ;
; Outputs                                                       ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,       de,  hl                                       ;
;---------------------------------------------------------------;
MouseBG:        defw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
ErasePointer:   call Pix            ; convert coords to screen address
                ld de, MouseBG      ; point de to saved screen data
                ld b, 11            ; pointer is 11 pixels high
EP_Lp1:         ld a, (de)          ; get the saved screen data
                ld (hl), a          ; restore the screen
                inc hl              ; next screen address
                inc de              ; next saved screen data address
                ld a, (de)          ; get the saved screen data
                ld (hl), a          ; restore the screen
                dec hl              ; previous screen address
                inc de              ; next saved screen data address
                call Incy           ; move down 1 screen line
                djnz EP_Lp1         ; repeat for all 11 rows
                ret                 ; done

;---------------------------------------------------------------;
; SavePointer                                                   ;
;                                                               ;
;   Saves the contents of the screen under the pointer          ;
;   This allows the ErasePointer function to restore the screen ;
;   contents later                                              ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created        29th April 2006                              ;
;   Last Changed   29th April 2006                              ;
;                                                               ;
;   Inputs                                                      ;
;       b  - the y position of the pointer                      ;
;       c  - the x position of the pointer                      ;
;                                                               ;
; Outputs                                                       ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,       de,  hl                                       ;
;---------------------------------------------------------------;
SavePointer:    push bc             ; save the coordinates
                call Pix            ; convert coords to screen address
                ld de, MouseBG      ; do pointers to saved screen data address
                ld b, 11            ; pointer is 11 pixels high
SP_Lp1:         ld a, (hl)          ; get contents of screen
                ld (de), a          ; save screen data
                inc hl              ; next screen address
                inc de              ; next save data address
                ld a, (hl)          ; get contents of screen
                ld (de), a          ; save screen data
                dec hl              ; go back 1 screen address
                inc de              ; next save data address
                call Incy           ; move down 1 screen line
                djnz SP_Lp1         ; repeat for all 11 rows
                pop bc              ; restore the original coordinates
                ret                 ; done


;---------------------------------------------------------------;
; DrawPointer                                                   ;
;                                                               ;
;   Draws the masked mouse pointer onto the screen              ;
;   This is a specialized version of the generic sprite code    ;
;   from DrwSprNC above.                                        ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created        29th April 2006                              ;
;   Last Changed   29th April 2006                              ;
;                                                               ;
;   Inputs                                                      ;
;       b  - the y position of the pointer                      ;
;       c  - the x position of the pointer                      ;
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
DrawPointer:    call SavePointer    ; save the pixels under the cursor
                call Pix            ; get the screen address of the position
                ld de, MousePointer ; point de to the mouse pointer data
                ex af, af'          ; save the bit position from the screen address calculation
                ld a,  c            ; do we need to scroll the sprite into position?
                ld b, 11            ; mouse cursor is 11 pixels high
                and 7               ; set z flag
                ld c, a             ; store the bit shift counter in c reg
                jr nz, DP_Slow      ; if zero is set, then we can draw the sprite the fast way
                ex af, af'          ; get the pixel position (amount to scroll the data)
;---------------------------------------------------------------;
; Fast draw                                                     ;
;  This code draws the pointer when it is aligned to pixel 0    ;
;  i.e. It does not require shifting into position              ;
;  Note how much easier and faster it is to draw an aligned     ;
;  sprite. Also if the sprite was preshifted use could ALMOST   ;
;  use this code as well.                                       ;
;  But with preshifted sprites we would need to take the width  ;
;  into consideration as well. So we would need another         ;
;  internal loop to do this.                                    ;
;---------------------------------------------------------------;
DP_Lp1:         push bc             ; save the loop counters
                ld a, (hl)          ; get the screen contents
                ex de, hl           ; swap screen addr and sprite addr, hl - spr, de - scr
                ld b, (hl)          ; b has sprite data
                inc hl              ; move sprite data
                ld c, (hl)          ; c has mask data
                inc hl              ; move sprite data
                ex de, hl           ; swap screen and sprite data, de - spr, hl - scr
                and c               ; mask out unwanted screen bits
                or b                ; or in the sprite data
                ld (hl), a          ; store masked sprite on the screen
                call Incy           ; move down 1 line on the screen
                pop bc              ; restore the loop counters
                djnz DP_Lp1         ; loop until all rows done
                ret                 ; done

;---------------------------------------------------------------;
; Slow draw                                                     ;
;  This code draws the pointer when it is not on pixel 0        ;
;  The pointer and its mask must be scrolled into position      ;
;  and then drawn                                               ;
;---------------------------------------------------------------;
DP_Slow:        ex af, af'          ; get the pixel position (amount to scroll the data)
DP_Lp2:         push bc             ; save the counters
                ld a, c             ; get the bit shift counter and place it into accum
                ex af, af'          ; save the bit shift counter
                ld a, (de)          ; get the sprite data
                ld b, a             ; b contains sprite data
                ld c, 0             ; reset c reg
                inc de              ; move to mask
                push de             ; save sprite position
                push hl             ; save the screen address
                ex de, hl           ; swap screen address and sprite data, hl - spr, de - scr
                ld d, (hl)          ; load e with mask value
                ld e, 255           ; reset d
                ex de, hl           ; hl contains sprite mask, de contains sprite address
                ex af, af'          ; get the bit shift counter
DP_Lp3:         and a               ; clear the carry flag - ie. shift 0 into sprite data
                srl b               ; shift right logical b reg (into carry)
                rr c                ; rotate right from carry into c reg
                scf                 ; set the carry flag - ie. shift 1 into the mask data
                rr h                ; shift mask in hl
                rr l                ;
                dec a               ; dec bit shift counter
                jr nz, DP_Lp3       ; continue rotating the sprite and mask
                ex de, hl           ; de contains shifted mask, hl contains screen
                pop hl              ; restore the screen address
                ld a, (hl)          ; get screen contents
                and d               ; mask off unwanted bits
                or b                ; or in the sprite data
                ld (hl), a          ; save the masked sprite to the screen
                inc hl              ; move to next screen address
                ld a, (hl)          ; get screen contents
                and e               ; mask off unwanted bits
                or c                ; or in the sprite data
                ld (hl), a          ; save the masked sprite to the screen
                dec hl              ; move back 1 screen address
                call Incy           ; move down 1 line
                pop de              ; restore sprite position
                inc de              ; move to sprite data
                pop bc              ; restore the loop counters
                djnz DP_Lp2         ; loop until all rows done
                ret                 ; done

GetPixel:       call Pix
                ld b, a
                inc b
                xor a
                scf
GP_Lp:          rr a
                djnz GP_Lp
                ret

SetPixel:       call GetPixel
                or (hl)
                ld (hl), a
                ret
                
UnsetPixel:     call GetPixel
                xor 255
                and (hl)
                ld (hl), a
                ret

XorPixel:       call GetPixel
                xor (hl)
                ld (hl), a
                ret