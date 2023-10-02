;---------------------------------------------------------------;
;                                                               ;
;  LIBSPRITEMASKED.ASM                                          ;
;  Programmed by Tony Thompson (aka Kiwi)                       ;
;                                                               ;
;  This code show how to draw a large character based sprite    ;
;  using masking to an off screen buffer, which is then copied  ;
;  to the screen.                                               ;
;                                                               ;
;  Pros:                                                        ;
;   * Probably the hardest way to draw an image                 ;
;   * The smoothest way to animate a sprite                     ;
;   * The nicest way to display a sprite against a background   ;
;                                                               ;
;  Cons:                                                        ;
;   * Easily the slowest way to draw an image                   ;
;   * Not easily optimised for speed                            ;
;   * Requires additional memory for a buffer                   ;
;   * Requires a lot of reading/writing memory to do the masking;
;                                                               ;
;---------------------------------------------------------------;


DemoMasked:     ld b, XORSPRY
                sla b
                sla b
                sla b
                ld c, 0
                call Pix
                ld (ScreenTop), hl
                call CopyScrToBuf       ; copy the screen to our buffer
                xor a
                ld (MaskLX), a          ; reset the last x position
                ld (MaskLF), a          ; reset the last frame
                call SaveSpriteBack     ; copy the background to restore later
DM1:            call IsSpacePressed     ; check for space key
                ret c
                call MAnimateSprite     ; animate to the next frame
                call MaskPause          ; pause between frames
                jr DM1                  ; keep moving the sprite
            
MaskLX:         defb 0                  ; the last position of the sprite
MaskLF:         defb 0                  ; the last position of the sprite
ScreenTop:      defw 0                  ; the address of the line of the screen when the OSB/sprite is drawn to

; draw next frame
; erase last frame

MAnimateSprite: DBG_VAR_8 MaskLX
                call RestoreSpriteBack  ; restore the background where the sprite was drawn
                ld a, (MaskLF)          ; get the last frame we drew
                inc a                   ; go to next frame
                and 7                   ; limit to 0-7 frame (loops around at 8)
                ld (MaskLF), a          ; save last frame
                ld c, a                 ; c = last frame
                ld b, 0                 ; bc = offset into the position offset table
                ld hl, NCXorPosOffsets  ; get the offsets table
                add hl, bc              ; move to position offset
                ld a, (MaskLX)          ; get last X and last frame
                ld e, a                 ; e = last x position                
                ld a, (hl)              ; get the position offset
                add a, e                ; move the sprite (if needed)
                cp 39                   ; is the sprite now off the screen
                jr c, MAS1              ; no, skip reset
                xor a                   ; yes reset sprite position
MAS1:           ld (MaskLX), a          ; store the new x position
                call SaveSpriteBack     ; save the background where the sprite is to going to be drawn
                ld ix, MaskLX
                call DrawMaskedFrame    ; draw the sprite
                ;halt
                call CopyBufToScr       ; show result of the screen
                ret

            
DrawMaskedFrame:ld c, (ix+1)            ; get the frame to draw
                sla c                   ; 2 bytes per entry (*2)
                ld b, 0                 ; bc = offset into sprite frame table
                ld hl, MaskWalkerSprite ; hl = sprite table
                add hl, bc              ; hl = points to frame address
                ld e, (hl)              ; e = frame address low byte
                inc hl                  ; move to high byte
                ld d, (hl)              ; de = sprite frame address
                ex de, hl               ; hl = sprite frame address
                ld c, (ix+0)            ; c = x character positon
                call DrawSpriteMasked   ; draw/erase the sprite
                ret
                
                
MaskPause:      ld hl, 0
                ld de, 0
                ld bc, 20000
                ldir
                ret

; Sprites table (NC = No Clip) Xor Sprite Table
; Points to the addresses of each frame for the walker sprite
MaskWalkerSprite:   defw walker1
                    defw walker2
                    defw walker3
                    defw walker4
                    defw walker5
                    defw walker6
                    defw walker7
                    defw walker8

;---------------------------------------------------------------;
;                                                               ;
; DrawSpriteMasked                                              ;
; Draws a sprite using Masks to the off screen buffer           ;
;                                                               ;
; Written by Tony Thompson                                      ;
;                                                               ;
; Inputs                                                        ;
;  c  - the x character position of sprite                      ;
;  hl - the address of the sprite data                          ;
;                                                               ;
;---------------------------------------------------------------;
DrawSpriteMasked:
                ex de, hl           ; de = sprite data address
                ld b, 0             ; 
                ld hl, OSBuf        ;
                add hl, bc          ; hl = OSB address to draw into
                ld a, (de)          ; get width of sprite
                ld c, a             ; c = width of sprite (in characters/bytes)
                inc de              ; move to sprite height
                ld a, (de)          ; get sprite height
                ld b, a             ; b = sprite height (in pixels)
                inc de              ; move to sprite data
DSM2:           push bc             ; save size
                ld b, c
DSM1:           ld a, (de)          ; get sprite mask 
                ld c, a             ; c = mask
                inc de              ; move to sprite data
                and (hl)            ; mask out sprite area of screen
                ld c, a             ; c = masked screen data
                ld a, (de)          ; a = sprite data
                or c                ; merge masked screen with sprite graphic data
                ld (hl), a          ; store masked sprite on screen
                inc hl              ; move to next OSB address
                inc de              ; move to next sprite data
                djnz DSM1           ; draw entire line of sprite
                ld bc, 44 - 7
                add hl, bc          ; move to next line in OSB
                pop bc              ; get size of sprite
                djnz DSM2           ; decrement height count and keep drawing until all lines drawn
                ret                 ; done
                
;
; OSB
; 32 + 6 + 6 = 44 characters wide.
; 32 is the screen width
;  6 is the width of the sprite - 1
;  2 x 6 is so that the sprite can exist partial off screen.
;        if it was completely off screen at 7 characters then we wouldn't need to draw it ;-)
; 86 pixels high 
; So buffer is 44 bytes * 86 lines = 3,784 bytes in size
;
OSBuf:            defs    3784
; SpriteBack is a buffer to store the sprite background that we will be overwriting when we draw the sprite
; sprite is 7 characters * 86 = 602 bytes
SpriteBackBuf:     defs    602

; Copy the original screen background to our off screen buffer
; The screen is only 32 bytes wide and our buffer is 44 bytes wide
CopyScrToBuf:   ld hl, (ScreenTop)  ; source data is the screen
                ld de, OSBuf + 6    ; destination is the OSB + 6 bytes
                ld b, 86            ; copying 86 lines
                ld c, 32            ; and 32 bytes per line
CSTB1:          push bc             ; save the counters
                push hl             ; save start of the line on the screen
                ld b, 0
                ldir                ; copy the line on the screen to the buffer
                ld hl, 12
                add hl, de
                ex de, hl           ; move de to next line
                pop hl              ; restore the screen line start address
                call Incy           ; move down to next line
                pop bc              ; restore the counter
                djnz CSTB1          ; loop for all lines
                ret                 ; and done

; Copy the OSB to the screen
; This is the dumb version; as it copies the entire screen portion of the OSB
; to the screen. The smart version would only copy the part of the OSB that
; has changed. This would result in at most a buffer transfer of 10 bytes *
; 86 lines and not 32 bytes * 86 lines and at best 7 bytes * 86 lines.
CopyBufToScr:   ld de, (ScreenTop)  ; get screen address to start copying to
                ld hl, OSBuf + 6    ; get start of
                ld b, 86
                ld c, 32
CBTS1:          push bc             ; save counters
                push de             ; save screen address
                ld b, 0
                ldir                ; copy OSB to screen
                ld bc, 12
                add hl, bc          ; hl = OSB next line
                pop de              ; restore screen address
                ex de, hl           ; swap de/hl
                call Incy           ; move down 1 screen line
                ex de, hl           ; de = screen address
                pop bc              ; restore counters
                djnz CBTS1          ; loop for all lines
                ret
                

                
; Save the background where the sprite is to be drawn
; So we can restore it to erase the sprite
; c = x
SaveSpriteBack: ld hl, OSBuf
                ;ld a, (MaskLX)
                ld b, 0
                ld c, a
                add hl, bc          ; hl = address to start copying OSB from
                ld de, SpriteBackBuf
                ld b, 86            ; 86 lines
                ld c, 7             ; 7 bytes per line
SSB1:           push bc             ; save counters
                ld b, 0             ; only copy 7 bytes
                ldir                ; copy OSB to SpriteBack
                ld c, 37            ; span of buffer - SpriteBack buffer width
                add hl, bc          ; hl = next line in OSB
                pop bc              ; restore counters
                djnz SSB1
                ret
                
RestoreSpriteBack:
                ld hl, OSBuf
                ld a, (MaskLX)
                ld b, 0
                ld c, a
                add hl, bc          ; hl = OSB    
                ld de, SpriteBackBuf; de = SB
                ld b, 86
                ld c, 7
RSB1:           push bc
                ld b, 0
                ex de, hl           ; de = OSB, hl = SB
                ldir                ; copy SB to OSB
                ld c, 37
                ex de, hl           ; hl = SB, de = OSB
                add hl, bc          ; hl = next line in OSB
                pop bc
                djnz RSB1
                ret
                
                