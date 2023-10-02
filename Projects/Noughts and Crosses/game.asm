;---------------------------------------------------------------;
;                                                               ;
; NOUGHTS AND CROSSES                                           ;
;                                                               ;
; Author : Tony Thompson                                        ;
; Date   : 18 March 2006                                        ;
; Comment: Created for the TommyGun - Getting Started Guide     ;
;                                                               ;
;---------------------------------------------------------------;
SCREEN       equ 16384
ATTRIBUTES   equ 22528
MENU_OFF     equ 64 + 7               ; White Ink, Black Paper, Bright On, Flash Off
MENU_ON      equ 64 + 32 + 7          ; White Ink, Green Paper, Bright On, Flash Off
ICON_ON      equ 64 + 32
ICON_OFF     equ 64
NOUGHTS_WIN  equ 1
CROSSES_WIN  equ 2
DRAW_NO_WIN  equ 3
C1           equ  9
C2           equ 14
C3           equ 19
R1           equ  8
R2           equ 13
R3           equ 18
GRID_STEP    equ  5
INK_MASK     equ  7

             org 30000
;---------------------------------------------------------------;
; PlayGame                                                      ;
;   The games main loop                                         ;
;---------------------------------------------------------------;
PlayGame:    ld hl, GameBoard        ; display the title screen
             call DrawScr            ; draw the screen
PGLoop:      call Pause              ; pause between key presses
             call DrawPlayers        ; draw the current players
             call PosCursor          ; position the player marker
             call CheckForWin        ; check for player win
             cp NOUGHTS_WIN          ; Noughts WINS?
             jr z, N_WIN             ; if 0 then noughts won
             cp CROSSES_WIN          ; Crosses WINS?
             jr z, C_WIN             ; if 0 then crosses won
             cp DRAW_NO_WIN          ; was it a draw?
             jr z, D_WIN             ; if 0 then it was a draw
             ld a, (CurPlayer)       ; no winner yet
             xor 1                   ; so swap players
             ld (CurPlayer), a       ; store the next player
             jr PGLoop               ; keep going still the game is finished

;---------------------------------------------------------------;
; D_WIN, C_WIN, DRAW_NO_WIN, ShowWinner                         ;
;   Show the Winner of the game                                 ;
;---------------------------------------------------------------;
D_WIN:       ld l, 0                 ; x position
             ld h, 14                ; y position
             ld b, 2                 ; height
             call ShowWinner         ; shade the Nought zone in flashing green
             ld l, 26                ; x position
             ld h, 14                ; y position
             ld b, 2                 ; height
             call ShowWinner         ; sahde the Cross zone in flashing green
             call WaitForSpace       ; wait for space
             jr PlayGame             ; back to playing the game
N_WIN:       ld l, 0                 ; x position
             ld h, 6                 ; y position
             ld b, 8                 ; height
             call ShowWinner         ; shade the nought in flashing green
             call WaitForSpace       ; wait for space
             jr PlayGame             ; back to playing the game
C_WIN:       ld l, 26                ; x position
             ld h, 6                 ; y position
             ld b, 8                 ; height
             call ShowWinner         ; shade the cross in flashing green
             call WaitForSpace       ; wait for space
             jr PlayGame             ; back to playing the game
ShowWinner:  ld c, 6                 ; width
             ld d, 128 + MENU_ON     ; white ink, green paper, bright and flash on
             ld e, INK_MASK          ; keep the ink colour
             call ColBlock           ; highlight the required zone
             ret

;---------------------------------------------------------------;
; DrawPlayers                                                   ;
;   highlight the current player icon and reset the other icon  ;
;---------------------------------------------------------------;
DrawPlayers: ld a, (CurPlayer)       ; get the current player
             ld l, 0                 ; nought x position
             ld h, 6                 ; nought y position
             and a                   ; is the current player the nought?
             jr z, DrawCurrent       ; yes, then draw as the current player
             ld l, 26                ; no the cross is so change the x position
DrawCurrent: ld b, 6                 ; color 6 characters high
             ld c, 6                 ; and 6 wide
             ld d, ICON_ON           ; use the green paper
             ld e, INK_MASK          ; and make the ink transparent
             call ColBlock           ; do the color changes
             ld a, (CurPlayer)       ; get the current player again
             ld l, 0                 ; nought x position
             ld h, 6                 ; nought y position
             and a                   ; is the current player the nought?
             jr nz, DrawNext         ; no, so draw it as the next player
             ld l, 26                ; yes, so draw the cross as the next player
DrawNext:    ld b, 6                 ; color 6 characters high
             ld c, 6                 ; and 6 wide
             ld d, ICON_OFF          ; in a black paper and bright turn on
             ld e, INK_MASK          ; and ink is transparent
             call ColBlock           ; do the color change
             ret                     ; return back to main loop
             
;---------------------------------------------------------------;
; IsOccupied                                                    ;
;   return ink color of a grid to indicate if its occupied      ;
;   zero or black ink means the grid position is empty          ;
;---------------------------------------------------------------;
IsOccupied:  ld bc, (CurPos)         ; get the current position
             call Attr               ; convert it to an attr address
             ld a, (hl)              ; place the attr into a
             and INK_MASK            ; and get on the ink
             ret                     ; square is not occupied if its ink is black

;---------------------------------------------------------------;
; DrawCursor                                                    ;
;   draw the game cursor                                        ;
;   show a green background if a marker can be dropped          ;
;   show a red background if a marker cannot be dropped         ;
;---------------------------------------------------------------;
DrawCursor:  push af                 ; save the af registers
             call IsOccupied         ; is the square occupied?
             ld hl, (CurPos)         ; get the current cursor pos into hl
             jr z, NotOccupied       ; is the position occupied? if not goto NotOccupied
             ld d, 64 + 16           ; Red Paper, Black Ink, Bright On
             ld e, INK_MASK          ; transparent ink
             jr DrawCur
NotOccupied: ld d, 64 + 32           ; Green Paper, transparent Ink, Bright On
             ld e, INK_MASK          ; keep the current ink
DrawCur:     ld b, 4                 ; height
             ld c, 4                 ; width
             call ColBlock           ; highlight the sqaure
             pop af                  ; restore af registers
             ret                     ; return to caller
             
;---------------------------------------------------------------;
; EraseCursor                                                   ;
;   erase the game cursor                                       ;
;---------------------------------------------------------------;
EraseCursor: push af                 ; save af
             ld hl, (CurPos)
             ld d, 0
             ld e, 64 + INK_MASK     ; keep bright bit and ink
             ld b, 4
             ld c, 4
             call ColBlock           ; erase the game cursor
             pop af
             ret

;---------------------------------------------------------------;
; PosCursor                                                     ;
;   let the player move their marker and place it into a square ;
;---------------------------------------------------------------;
PosCursor:   call DrawCursor         ; draw the game cursor
             call MoveCursor         ; move the game cursor
             ret                     ; return to the main loop

;---------------------------------------------------------------;
; MoveCursor                                                    ;
;   move the game cursor around the grid                        ;
;---------------------------------------------------------------;
MoveCursor:  ld bc, 61438            ; check keys 0-6
             in a, (c)               ; get keys
             bit 2, a                ; test for right
             jr z, MoveRight         ; if pressed goto MoveRight
             bit 3, a                ; test for up
             jr z, MoveUp            ; if pressed goto MoveUp
             bit 4, a                ; test for down
             jr z, MoveDown          ; if pressed goto MoveDown
             bit 0, a                ; test for place marker
             jr z, MovePlace         ; if pressed goto MovePlace
             ld bc, 63486            ; check keys 1-5
             in a, (c)               ; get keys
             bit 4, a                ; test for left
             jr z, MoveLeft          ; if pressed goto MoveLeft
             ld bc, 49150            ; check keys enter-H
             in a, (c)               ; get keys
             bit 0, a                ; test for enter
             jr z, MovePlace         ; if pressed goto MovePlace
             ld bc, 32766            ; check keys Space-B
             in a, (c)               ; get keys
             bit 0, a                ; test for space
             jr z, MovePlace         ; if pressed goto MovePlace
             jr MoveCursor           ; check for keys again

MoveRight:   ld a, (CurPos)          ; get cursor x position
             cp C3                   ; test for end of grid
             jr z, MoveCursor        ; if at end goto back to checking keys
             call EraseCursor        ; erase the game cursor
             add a, GRID_STEP        ; move it right
             ld (CurPos), a          ; save the cursor x position
             call DrawCursor         ; draw the new cursor position
             call Pause              ; pause a little
             jr MoveCursor           ; back to checking keys
             
MoveLeft:    ld a, (CurPos)          ; get cursor x position
             cp C1                   ; test for start of grid
             jr z, MoveCursor        ; if at start goto back to checking keys
             call EraseCursor        ; erase the game cursor
             sub GRID_STEP           ; move it left
             ld (CurPos), a          ; save the cursor x position
             call DrawCursor         ; draw the new cursor position
             call Pause              ; pause a little
             jr MoveCursor           ; back to checking keys

MoveUp:      ld a, (CurPos+1)        ; get cursor y position
             cp R1                   ; test for top of grid
             jr z, MoveCursor        ; if at top goto back to checking keys
             call EraseCursor        ; erase the game cursor
             sub GRID_STEP           ; move it up
             ld (CurPos+1), a        ; save the cursor x position
             call DrawCursor         ; draw the new cursor position
             call Pause              ; pause a little
             jr MoveCursor           ; back to checking keys

MoveDown:    ld a, (CurPos+1)        ; get cursor y position
             cp R3                   ; test for bottom of grid
             jr z, MoveCursor        ; if at bottom goto back to checking keys
             call EraseCursor        ; erase the game cursor
             add a, GRID_STEP        ; move it down
             ld (CurPos+1), a        ; save the cursor x position
             call DrawCursor         ; draw the new cursor position
             call Pause              ; pause a little
             jp MoveCursor           ; back to checking keys

MovePlace:   call IsOccupied         ; is the square occupied?
             jp nz, MoveCursor       ; if yes, then back to checking keys
             ld a, (CurPos)          ; no, draw a marker here
             sla a                   ; x * 2
             sla a                   ; x * 4
             sla a                   ; x * 8
             ld c, a                 ; store the char -> pixel x value in c
             ld a, (CurPos+1)        ; get the y position
             sla a                   ; y * 2
             sla a                   ; y * 4
             sla a                   ; y * 8
             ld b, a                 ; store the char -> pixel y value in b
             ld a, (CurPlayer)       ; get the current player
             and a                   ; is it the nought?
             jr nz, DrawCross        ; if not draw the cross
             ld hl, Nought           ; yes, get nought tile
             jr MoveDoDraw           ; draw the tile
DrawCross:   ld hl, Cross            ; no, its the cross
MoveDoDraw:  call DrwTile            ; draw the player marker
             ret                     ; return to main loop

;---------------------------------------------------------------;
; CheckForWin                                                   ;
;   check for a winner                                          ;
;---------------------------------------------------------------;
CheckForWin:  ld b, 8                ; 8 entries in the wintable
              ld hl, WinTable        ; hl points to wintable
CFWloop:      push bc                ; save b counter
              call CheckEntry        ; check the current entry
              pop bc                 ; restore the b counter
              and a                  ; check the entry result
              ret nz                 ; return to main loop if it has a result
              djnz CFWloop           ; check next table entry
              ld b, 9                ; no winners yet, so do we have a draw
              ld hl, WinTable        ; back to the wintable
CheckForDraw: push bc                ; save counter
              ld c, (hl)             ; get x position from table into c
              inc hl                 ; move to y position
              ld b, (hl)             ; get y position into b
              inc hl                 ; move to y position
              push hl                ; save hl
              call Attr              ; convert bc to a attr addr
              ld a, (hl)             ; get the attr
              and INK_MASK           ; get the ink color
              pop hl                 ; restore hl (wintable pointer)
              pop bc                 ; restore the table counter
              and a                  ; is the ink black?
              ret z                  ; yes, then the grid is not fill yet
              djnz CheckForDraw      ; chech the next grid position
              ld a, DRAW_NO_WIN      ; no empty squares, so its a draw
              ret                    ; return to the main loop

;---------------------------------------------------------------;
; CheckEntry                                                    ;
;   check the WinTable entry positions for a winner             ;
;---------------------------------------------------------------;
CheckEntry:   ld c, (hl)             ; get x into c
              inc hl                 ; move to y
              ld b, (hl)             ; get y into b
              inc hl                 ; move to x
              push hl                ; save hl
              call Attr              ; convert bc to attr addr
              ld a, (hl)             ; get attr
              and INK_MASK           ; get the ink color
              ld e, a                ; save ink in e
              pop hl                 ; restore hl
              ld c, (hl)             ; get x in c
              inc hl                 ; move to y
              ld b, (hl)             ; get y in b
              inc hl                 ; move to x
              push hl                ; save hl
              call Attr              ; convert bc to attr addr
              ld a, (hl)             ; get attr
              and INK_MASK           ; get the ink color
              ld d, a                ; save ink in e
              pop hl                 ; restore hl
              ld c, (hl)             ; get x in c
              inc hl                 ; move to y
              ld b, (hl)             ; get y in b
              inc hl                 ; move to x
              push hl                ; save hl
              call Attr              ; convert bc to attr addr
              ld a, (hl)             ; get attr
              and INK_MASK           ; get the ink color
              pop hl                 ; restore hl
              add a, d               ; add all the inks together
              add a, e               ;
              jr nz, FindWinner      ; are their any colors set?
CheckNoWin:   xor a                  ; no, so return 0 - no winner yet
              ret                    ; return to main loop
FindWinner:   cp 18                  ; is it 3 noughts in a row then 3*6 is 18
              jr z, NoughtWins       ; yes, goto NoughtWins
              cp 3                   ; is it 3 crosses in a row then 3*1 is 3
              jr nz, CheckNoWin      ; no, goto CheckNoWin
              ld a, CROSSES_WIN      ; yes, crosses won
              ret                    ; return in the main loop
NoughtWins:   ld a, NOUGHTS_WIN      ; noughts won
              ret                    ; return to the main loop

;---------------------------------------------------------------;
; Pause                                                         ;
;   pause briefly                                               ;
;---------------------------------------------------------------;
Pause:       push bc                 ; save bc
             push de                 ; save de
             push hl                 ; hl
             ld bc, 50000            ; define the pause length
             ld de, 0                ; define block transfer destination
             ld hl, 0                ; define block transfer source
             ldir                    ; do a block transfer (takes a little while)
             pop hl                  ; restore hl
             pop de                  ; restore de
             pop bc                  ; restore bc
             ret                     ; pause complete

;---------------------------------------------------------------;
; WaitForSpace                                                  ;
;   wait for space key to be pressed                            ;
;---------------------------------------------------------------;
WaitForSpace: ld bc, 32766           ; check keys from Space-B
              in a, (c)              ; get keys
              bit 0, a               ; if space pressed
              jr nz, WaitForSpace    ; no, then check again
              ret                    ; yes, return to caller

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
; DrawScr                                                       ;
;                                                               ;
;   Draws a screen object onto the display                      ;
;   Written by Tony Thompson                                    ;
;   Created         2006                                        ;
;   Last Changed    18 March 2006                               ;
;                                                               ;
;   Inputs                                                      ;
;       hl - the address of a screen to draw                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc, de, hl                                         ;
;                                                               ;
;   Regs destoryed                                              ;
;       none                                                    ;
;---------------------------------------------------------------;
DrawScr:    push af
            push bc
            push de
            push hl            ; save all the registers
            push bc
            push hl
            ld bc, 768        ; clear the attributes to black
            ld hl, ATTRIBUTES
DrwScrClr:  ld (hl), 0
            inc hl
            dec bc
            ld a, c
            or b
            jr nz, DrwScrClr
            pop hl
            pop bc
            ld b, 192          ; transfer 192 lines
            ld de, SCREEN      ; point de at the screen address
DrwScrLp:   push bc            ; save bc
            ld bc, 32          ; transfer 1 line of pixels
            push de            ; save the screen position
            ldir               ; do the transfer
            pop de             ; restore the screen position
            ex de, hl          ; swap screen address for off screen address
            call Incy          ; get next line of the physical screen
            ex de, hl          ; put screen address back into de
            pop bc             ; get the line count
            djnz DrwScrLp      ; decrement it and keep draw lines if not zero
            ld bc, 768         ; transfer the attributes to the screen
            ldir               ; do the transfer
            pop hl             ; restore all the registers
            pop de
            pop bc
            pop af
            ret                ; return to caller

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
;       hl - the attribute address for the screen location      ;
;       a  - contains the bit position of the pixel             ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  hl                                            ;
;                                                               ;
;   Regs destoryed                                              ;
;       af                                                      ;
;---------------------------------------------------------------;
Pix:        ld a, b
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
; MAttr                                                         ;
;                                                               ;
;   Converts a screen pixel coord into a off screen attr address;
;   Written by Tony Thompson                                    ;
;   Created         1984                                        ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in pixels                                ;
;       c - x position in pixels                                ;
;                                                               ;
;   Outputs                                                     ;
;       hl - the attribute address for the off screen location  ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       af,  bc,  hl                                            ;
;---------------------------------------------------------------;
MAttr:      push de
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
            ld de,  ATTRIBUTES
            add hl, de
            pop de
            ret

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
DrwTile:    ld e, (hl)                  ; read the width of the tile
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
            call Incy                   ; move down 1 line in the screen buffer
            pop bc                      ; get the size
            djnz dt1                    ; draw all lines of the tile
            pop bc                      ; get the size
            pop hl                      ; get the top/left screen address
            pop af                      ; put position into af
            push bc                     ; save size
            push af                     ; save position
            pop bc                      ; put position back into bc
            call MAttr                  ; convert tile pos to attribute address
            pop bc                      ; put size back into bc
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
; Attr                                                          ;
;                                                               ;
;   Converts a screen char coord into a screen attr address     ;
;   Written by Tony Thompson                                    ;
;   Created         1984                                        ;
;   Last Changed    1st May 2003                                ;
;                                                               ;
;   Inputs                                                      ;
;       b - y position in characters                            ;
;       c - x position in characters                            ;
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
Attr:       ld l, b                ; get y position into l
            ld h, 0                ; reset h to 0
            add hl, hl             ; hl * 2
            add hl, hl             ; hl * 4
            add hl, hl             ; hl * 8
            add hl, hl             ; hl * 16
            add hl, hl             ; hl * 32
            ld a, c                ; get the x position
            or l                   ; merge l and c
            ld l, a                ; put a into l (ie. (y*32) + x position
            ld bc,  ATTRIBUTES     ; get the attributes address into bc
            add hl, bc             ; make the address relative to the attrs
            ret                    ; hl contains the attribute address of bc


;---------------------------------------------------------------;
; ColBlock                                                      ;
;                                                               ;
;   Colours a block of attributes to a desired set of colours   ;
;   Written by Tony Thompson                                    ;
;   Created         2006                                        ;
;   Last Changed    18 March 2006                               ;
;                                                               ;
;   Inputs                                                      ;
;       b - y height in characters                              ;
;       c - x width in characters                               ;
;       d - attribute colour                                    ;
;       e - attribute mask                                      ;
;       h - y position in characters                            ;
;       l - x position in characters                            ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc,  de,  hl                                       ;
;                                                               ;
;   Regs destoryed                                              ;
;       none                                                    ;
;---------------------------------------------------------------;
ColBlock:     push af
              push bc
              push de
              push hl             ; all regs saved
              push bc             ; save bc - the size
              push hl
              pop bc              ; put hl into bc -bc has screen pos
              call Attr           ; hl now has the attribute address
              pop bc              ; bc now has the size again
ColBlock1:    push bc             ; save the size
              push hl             ; save the attribute screen address
              ld b, c             ; put the width into b
ColBlock2:    ld a, (hl)          ; get the current attribute
              and e               ; mask off the attributes we don't want
              or d                ; and set the new attributes we do want
              ld (hl), a          ; store the result
              inc hl
              djnz ColBlock2      ; do the width of the block
              ld bc, 32
              pop hl
              add hl, bc          ; move to next attribute line
              pop bc              ; get the current width and height
              djnz ColBlock1      ; do all the lines of the block
              pop hl
              pop de
              pop bc
              pop af              ; all regs restored
              ret


CurPos:       defb 9, 8           ; the current position of the board cursor
CurPlayer:    defb 0              ; current player is nought, next is cross

WinTable:
     defb C1, R1, C2, R1, C3, R1  ; top row
     defb C1, R2, C2, R2, C3, R2  ; middle row
     defb C1, R3, C2, R3, C3, R3  ; bottom row
     defb C1, R1, C1, R2, C1, R3  ; left column
     defb C2, R1, C2, R2, C2, R3  ; middle column
     defb C3, R1, C3, R2, C3, R3  ; right column
     defb C1, R1, C2, R2, C3, R3  ; left to right, top to bottom
     defb C3, R1, C2, R2, C1, R3  ; right to left, top to bottom

org 32768                         ; place the screens and tiles from RAM address 32768
include "images.inc"              ; include the screens and tiles

end 30000                         ; the execution start address (pc) of the .tap file
