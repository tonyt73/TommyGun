;---------------------------------------------------------------;
;                                                               ;
;  LIBSPRITEXOR.ASM                                             ;
;  Programmed by Tony Thompson (aka Kiwi)                       ;
;                                                               ;
;  This code show how to draw a large character based sprite    ;
;  using xor to draw and erase the sprite on the screen.        ;
;                                                               ;
;  Pros:                                                        ;
;   * Probably the simpliest way to draw an image               ;
;   * Easily the fastest way to draw an image                   ;
;   * Easily optimized for more speed                           ;
;                                                               ;
;  Cons:                                                        ;
;   * FLICKER, as we are drawing directly to the screen         ;
;     it will flicker quite badly                               ;
;   * Doesn't merge well with the background                    ;
;   * Doesn't work for attributes                               ;
;                                                               ;
;---------------------------------------------------------------;


DemoXor:        ld hl, nmwalker1        ; sprite frame to draw
                ld b, XORSPRY           ; y character position
                xor a
                ld c, a                 ; x character position
                ld (XorLX), a           ; reset all variables
                ld (XorLF), a
                ld (XorEX), a
                ld (XorEF), a           
                call DrawSpriteXor      ; draw first frame of sprite
DX1:            call IsSpacePressed     ; check for space key
                ret c
                call XorPause           ; pause between frames
                call AnimateSprite      ; animate to the next frame
                jr DX1                  ; keep moving the sprite
            
XorLX:          defb 0                  ; the last position of the sprite
XorLF:          defb 0                  ; the last frame we drew
XorEX:          defb 0                  ; the position to erase from
XorEF:          defb 0                  ; the frame to erase

XORSPRY         equ  4                  ; the y character position to draw the sprite

; draw next frame
; erase last frame

AnimateSprite:  ld hl, (XorLX)          ; get last X and last frame
                ld (XorEX), hl          ; copy them into erase X and erase frame
                ld a, (XorLF)           ; get the last frame we drew
                inc a                   ; go to next frame
                and 7                   ; limit to 0-7 frame (loops around at 8)
                ld (XorLF), a           ; store the frame we are drawing
                ld c, a                 ; c = last frame
                ld a, (XorLX)           ; get the last x position
                ld e, a                 ; e = last x position                
                ld b, 0                 ; bc = offset into the position offset table
                ld hl, NCXorPosOffsets  ; get the offsets table
                add hl, bc              ; move to position offset
                ld a, (hl)              ; get the position offset
                add a, e                ; move the sprite (if needed)
                cp 25
                jr c, AS1
                xor a
AS1:            ld (XorLX), a           ; store the new x position
                ld ix, XorLX
                call DrawXorFrame       ; draw the next/new frame
                ld ix, XorEX
                call DrawXorFrame       ; erase the previous/old frame
                ret

            
DrawXorFrame:   ld c, (ix+1)            ; get the frame to draw
                sla c                   ; 2 bytes per entry (*2)
                ld b, 0                 ; bc = offset into sprite frame table
                ld hl, WalkerSprite     ; hl = sprite table
                add hl, bc              ; hl = points to frame address
                ld e, (hl)              ; e = frame address low byte
                inc hl                  ; move to high byte
                ld d, (hl)              ; de = sprite frame address
                ex de, hl               ; hl = sprite frame address
                ld c, (ix+0)            ; c = x character positon
                ld b, XORSPRY           ; b = y characters down
                call DrawSpriteXor      ; draw/erase the sprite
                ret
                
                
XorPause:       ld hl, 0
                ld de, 0
                ld bc, 20000
                ldir
                ret

; Sprites table (NC = No Clip) Xor Sprite Table
; Points to the addresses of each frame for the walker sprite
WalkerSprite:       defw nmwalker1
                    defw nmwalker2
                    defw nmwalker3
                    defw nmwalker4
                    defw nmwalker5
                    defw nmwalker6
                    defw nmwalker7
                    defw nmwalker8

;
; Sprite offsets
; These are the character offsets to move each frame when it is to be drawn
;
NCXorPosOffsets:    defb 1
                    defb 0
                    defb 0
                    defb 3
                    defb 0
                    defb 1
                    defb 0
                    defb 2

;---------------------------------------------------------------;
;                                                               ;
; DrawSpriteXor                                                 ;
; Draws a sprite using XOR directly to the screen               ;
;                                                               ;
; Written by Tony Thompson                                      ;
;                                                               ;
; Limitations                                                   ;
; * No clipping performed and so sprite must always be entirely ;
;   on the screen                                               ;
;                                                               ;
; Inputs                                                        ;
;  b  - the y character position of sprite                      ;
;  c  - the x character position of sprite                      ;
;  hl - the address of the sprite data                          ;
;                                                               ;
;---------------------------------------------------------------;
DrawSpriteXor:  halt
                ex de, hl           ; save sprite data address in de
                sla b               ; b * 8
                sla b
                sla b               ; y position in pixels
                sla c               ; c * 8
                sla c
                sla c               ; x position in pixels
                call Pix            ; convert the pixel position into a screen address
                ld a, (de)          ; get width of sprite
                ld c, a             ; c = width of sprite (in characters/bytes)
                inc de              ; move to sprite height
                ld a, (de)          ; get sprite height
                ld b, a             ; b = sprite height (in pixels)
                inc de              ; move to sprite data
DSX2:           push bc             ; save size
                push hl             ; save screen address
                ld b, c
DSX1:           ld a, (de)          ; get sprite data
                xor (hl)            ; merge with screen data
                ld (hl), a          ; store result on screen
                inc l               ; move to next screen address
                inc de              ; move to next sprite data
                djnz DSX1           ; draw entire line of sprite
                pop hl              ; get screen address (start of line)
                call Incy           ; move down 1 screen line
                pop bc              ; get size of sprite
                djnz DSX2           ; decrement height count and keep drawing until all lines drawn
                ret                 ; done
                
                
                