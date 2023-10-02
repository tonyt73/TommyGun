;------------------------------------------------------------------------------;
;  Desktop.inc                                                                 ;
;  Contains routines for drawing and managing the desktop                      ;
;------------------------------------------------------------------------------;

; af - carry set - clear screen
DD_Flag:        defb 0
DrawDesktop:    ld (DD_Flag), a
                jr nc, DDNoClr
                ;call VSync
                ld a, (DesktopColour)
                call ClrScr
DDNoClr:        ;call VSync
                call DrawTopMenu
DDrawIcons:     ;call VSync                 
                ld ix, DesktopIcons     ; point to icon buffer
                ld b, (ix)              ; get the number of icons to display 
                inc ix                  ; move to first icon
DDL1:           push bc                 ; DP: BC        save no. of icons
                ld c, (ix+1)            ; get x pixel position
                ld b, (ix+2)            ; get y pixel position
                ld e, (ix+3)            ; get width
                ld d, (ix+4)            ; get height
                ld l, (ix+5)            ; get normal attr
                ld h, (ix+6)            ; get highlight attr
                push bc                 ; SP: BC BC     save position
                inc c                   ; move inside icon x positon
                inc b                   ; move inside icon y positon
                ld a, d                 ; get the height of the attr
                and $0F                 ; if its < 16
                add a, b                ; add it to the y position (icon is only 8 pixels high)
                ld b, a                 ; adjust y position (if height > 16, y is unchanged)
                xor a                   ; draw the rects using attributes (all flag bits off)
                ; TODO: load iy with the function to execute
                push ix                 ; SP: BC BC IX
                ld a, (DD_Flag)
                and a
                call nz, GuiRectAdd     ; add the icon rect to the rect buffer
                pop ix                  ; SP: BC BC
                pop bc                  ; SP: BC        get icon position
                push bc                 ; SP: BC BC     save position
                ld a, (ix+0)            ; get icon index
                push ix                 ; SP: BC BC IX  save ix
                call DrawIcon           
                pop ix                  ; SP: BC BC     restore ix
                pop bc                  ; SP: BC        get position
                push ix                 ; SP: BC IX     put ix
                pop hl                  ; SP: BC        in hl
                ld de, 7                ;
                add hl, de              ; move to label string
                ex de, hl               ; de = label string
                ld a, (DD_Flag)
                and a
                call nz, DrawIconLabel      ; draw label at BC
                ld bc, IconEntrySize    ; size of icon entry
                add ix, bc              ; next entry
                pop bc                  ; SP:           get no. of icons
                djnz DDL1
                ret                  

; bc = position of icon
; scf = found
; l = icon index
FindIcon:       push ix                 ; SP: IX    save ix
                ld a, c                 ; 
                and $F8                 ;
                ld c, a                 ; x = x - (x % 8)
                ld a, b
                and $F8 
                ld b, a                 ; y = y - (y % 8)
                ld a, (DesktopIcons)    ; get the number of icons
                ld h, a                 ; h = no of icons
                ld ix, DesktopIcons+1   ; set ix to start of icons 
FIL1:           ld a, (ix+1)            ; get the x position            
                inc a                   ; move it across 1 pixel
                and $F8                 ; remove lower 3 bits
                cp c                    ; cp to rect x position 
                jr nz, FIS1             ; if not same, go to next icon
                ld a, (ix+2)            ; get the icon y position
                inc a                   ; move it down 1 pixel
                and $F8                 ; remove lower 3 bits
                cp b                    ; cp to rect y position
                jr nz, FIS2             ; if not same, go to next icon
                ; found
FIF:            scf                     ; found, set carry flag
                ld l, (ix+0)            ; l = icon index
                pop ix                  ; restore ix
                ret                     ; done
FIS2:           ; check 8 pixels down
                add a, 8                ; move y down 8 pixels
                cp b                    ; compare to rect y
                jr z, FIF               ; if not found, continue to next icon                
FIS1:           ; next icon
                ld de, IconEntrySize    ; get icon entry size                            
                add ix, de              ; next record
                dec h                   ; loop 
                jr nz, FIL1             ; for all icons
                pop ix                  ; restore ix
                and a                   ; not found icon
                ret                

DesktopInfo:
DesktopColour:  defb pCYN + iBLK
 

IconEntrySize equ 20

DesktopIcons:
defb 4
; icon, x, y, attr width, attr height, normal attr, highlight attr, text[12], function(???)
; 18 bytes per entry (1K for 64 entries)

DI1:
defb 0, 215,  23, 16, 16, pWHT+iBLK, aBRT+pGRN+iBLK, " FLOPPY  A: ", 0
   
DI2:
defb 0, 215,  55, 16, 16, pWHT+iBLK, aBRT+pGRN+iBLK, " FLOPPY  B: ", 0

DI3:
defb 1, 215,  87, 16,  8, pWHT+iBLK, aBRT+pGRN+iBLK, " HARD  DISK ", 0

DI4:
defb 2, 215, 159, 16, 16, pWHT+iBLK, aBRT+pGRN+iBLK, "    TRASH   ", 0

; the other 60 entries
defs 960, 0
