;---------------------------------------------------------------;
;                                                               ;
;   GamePlay.inc                                                ;
;                                                               ;
;   This file contains routines for dealing with playing the    ;
;   Game                                                        ;
;                                                               ;
;---------------------------------------------------------------;

GameStartNew:   call GenerateGems
                xor a
                ld (Level), a
                ld (MatchesSoFar), a
                call PrintLevel
                ld a, GF_START_GAME
                call ResetGameFlag
                ld a, GF_PLAYING
                call SetGameFlag
                call ResetScore
                call PrintScore
                ret

GameOver:       ld b, 24                ; show the hi score table
                ld c, 72
                ld d, 10
                ld e, 22
                call WindowOpen
                ld hl, GameOverTxt1
                call PrintLineAt
                ld hl, GameOverTxt2
                call PrintLineAt
                ld hl, GameOverTxt3
                call PrintLineAt
                ld hl, GameOverTxt4
                call PrintLineAt
                call WaitForSpace       ; wait for space to be pressed
                call WindowClose
                call TransferScore      ; transfer the player score
                call IsNewHighScore     ; check to see if its a hi score
                call c, GetHiscoreName  ; if so, get the players name
                ld b, 24                ; show the hi score table
                ld c, 72
                ld d, 16
                ld e, 21
                call WindowOpen         ; open a window 21x17 at 72,24
                call DisplayHiScore     ; display the hiscore table
                ld hl, GameOverTxt4
                ld a, 136
                ld (GameOverTxt4+1), a
                call PrintLineAt
                ld a, 88
                ld (GameOverTxt4+1), a
                call WaitForSpace       ; wait for space to be pressed
                call WindowClose        ; close the window
                ld a, GF_GAME_OVER + GF_PLAYING
                call ResetGameFlag      ; reset the game over and playing flags
                ld a, GF_MENU
                call SetGameFlag        ; enter the main menu
                ret

GamePlay:       call MoveGameCursor
                ;ld a, 255
                ;call IncrementScore
                ;ld a, GF_GAME_OVER
                ;call SetGameFlag
                ret


;---------------------------------------------------------------;
; GenerateGems                                                  ;
; Generates a clean board of gems with no matches on it         ;
;---------------------------------------------------------------;
GenerateGems:   call ClearBoard
                ld bc, (PointerPos)     ; get the mouse pointer position
                call ErasePointer       ; erase the pointer
                ld d, 8
                ld b, 0
                ld c, 64
DGlp2:          ld e, 8
DGlp1:          push de
                push bc
GG_Lp3:         push bc
                call ChooseGem
                pop bc
                xor a
                call DrwTile
                pop bc
                push bc
                call CheckGem
                jr c, GG_Lp3
                pop bc
                ld a, 24
                add a, c
                ld c, a
                pop de
                dec e
                jr nz, DGlp1
                ld a, c
                sub 192
                ld c, a
                ld a, 24
                add a, b
                ld b, a
                dec d
                jr nz, DGlp2
                ld bc, (PointerPos)     ; get the mouse pointer position
                call DrawPointer        ; draw the pointer
                ret

ChooseGem:      ld a, 15
                call RandomNumber
                and 7
                cp 7
                jr z, ChooseGem
GetGemAddr:     sla a
                ld c, a
                ld b, 0
                ld a, (GemTheme)
                ld hl, TileTheme1
                dec a
                jr z, GGA_Cont
                ld hl, TileTheme2
                dec a
                jr z, GGA_Cont
                ld hl, TileTheme3
GGA_Cont:       add hl, bc
                ld e, (hl)
                inc hl
                ld d, (hl)
                ex de, hl
                ret

NextTestGem     defb 0
ChooseGemTest:  ld hl, TestGemBoard
                ld a, (NextTestGem)
                ld c, a
                ld b, 0
                add hl, bc
                inc a
                and 63
                ld (NextTestGem), a
                ld a, (hl)
                jr GetGemAddr

TestGemBoard:   defb 0,1,2,3,4,5,6,0
                defb 1,2,3,5,5,6,0,1
                defb 2,1,5,3,3,0,1,2
                defb 3,4,5,6,0,1,2,3
                defb 4,5,6,0,1,2,3,4
                defb 5,6,0,1,2,3,4,5
                defb 6,0,1,2,3,4,5,6
                defb 0,1,2,3,4,5,6,0

;---------------------------------------------------------------;
; RandomNumber                                                  ;
;                                                               ;
; Chooses a random number from 0-a                              ;
;                                                               ;
;---------------------------------------------------------------;
RandomNumber:   push hl                 ; save registers
                push bc                 ; save registers
                ld c, a                 ; merge to C
                dec c                   ; computers does 0 n-1
                ld hl, (seed)           ; fetch RND pointer
                inc hl                  ; point to next number
                ld a, h
                and 63
                ld h, a                 ; but keep it in ROM
                ld a, r
                xor l
                ld l, a
                ld (seed), hl           ; store next RND-pointer
                ld a, (hl)              ; fetch RND number
RNmarge:        sub c                   ; calculate within marge
                jr nc, RNmarge
                adc a, c                ; 1 sub to much + range (1 - n) restore
                pop bc                  ; retrieve registers
                pop hl
                ret                     ; A holds RND value
seed            defw 0

;---------------------------------------------------------------;
; CheckGem                                                      ;
;                                                               ;
; Checks the current position of a new gem board being          ;
; generated. It only needs to check the past 3 position up and  ;
; to the left. This is so that the new board contains to        ;
; direct matches when it starts. This could be made even better ;
; by checking for possible matches and skipping a couple when   ;
; found to reduce the amount of matches available when the game ;
; starts.                                                       ;
;                                                               ;
; It uses the Check4GemMatch function buts supplies its own     ;
; pattern matches                                               ;
;---------------------------------------------------------------;
CheckGem:       ld hl, GemChecks
                call Check4GemMatch + 3
                ret
                ;   no   (l,   t)  (r,   b)  (x,   y)  (x,   y)  (x,   y)   (x,   y)
GemChecks:      defb 3,  112,   0,  0,   0,   0,   0, -24,   0, -48,   0, 255
                defb 3,   64,  48,  0,   0,   0,   0,   0, -24,   0, -48, 255
                defb 0


;---------------------------------------------------------------;
; ActionSwap                                                    ;
;                                                               ;
; Swaps the gems at the old cursor position and the new cursor  ;
; positions.                                                    ;
; Validates the swap is allowed.                                ;
; If not, then reverts the gems back again.                     ;
; If so, then scores the gem matches and repeats until no more  ;
; gem matches occur.                                            ;
; Also inserts new gems as old gems are matched and removed.    ;
;                                                               ;
;---------------------------------------------------------------;
AS_Tile1Pos:    defw 0                  ; the position of the first tile being animated
AS_Tile2Pos:    defw 0                  ; the position of the second tile being animated
ActionSwap:     call EraseGameCursor    ; remove the game cursor
                call AS_BonusReset      ; reset the bonus counter
                ld bc, (CursorPos)      ; retrieve the current cursor position
                ld (AS_Tile1Pos), bc    ; and store it as the first tile position
                ld bc, (CursorPosOld)   ; retrieve the the previous cursor position
                ld (AS_Tile2Pos), bc    ; and use it as the second tile position
                ld bc, (PointerPos)     ; get the pointer position
                call ErasePointer       ; erase the pointer before swap animation
                call AnimateGemSwap     ; animate the gem swapping
                call AS_NotSame         ; check the swapped tiles aren't the same
                call c, AS_CheckMatch   ; check for any matching gem patterns
                jr nc, AS_Revert        ; if no matches revert the gems back
                ld bc, (CursorPos)
                ld (CursorPosOld), bc
                ;jr AS_Cont             ; jump to removing the gems
AS_Loop:        call AS_CheckAll        ; check all the board for any matching gem patterns
AS_Cont:        call c, ReplaceGems     ; remove and score the matching gems
                jr c, AS_Loop           ; keep going until no matches are left
                call AS_BonusAdd        ; add any bonus values
                call CheckLevelGO       ; check for next level and game over conditions
                ld bc, (PointerPos)     ; get the pointer position
                call SavePointer
                call DrawGemCursor      ; draw the gem board cursor
                jr AS_End               ; swap is complete

AS_NotSame:     ld bc, (AS_Tile1Pos)    ; get the first tile position
                call CoordAttr          ; get its attribute address
                push hl                 ; save it
                ld bc, (AS_Tile2Pos)    ; get the second tile position
                call CoordAttr          ; get its attribute address
                ld a, (hl)              ; get the tile colour
                and 7                   ; get the ink only
                ld c, a                 ; save ink in c
                pop hl                  ; get tile 1 address
                ld a, (hl)              ; get the tile colour
                and 7                   ; get the ink only
                cp c                    ; compare tile 1 ink to tile 2 ink
                scf                     ; set carry flag
                ret nz                  ; return is they aren't the same
                and a                   ; clear carry
                ret                     ; done

;---------------------------------------------------------------;
; AS_Revert                                                     ;
;   Reverts the swaps tiles back when the swap was illegal      ;
;   ie. no valid pattern matches                                ;
;---------------------------------------------------------------;
AS_Revert:      ld bc, (CursorPos)      ; retrieve the current cursor position
                ld (AS_Tile1Pos), bc    ; and store it as the first tile position
                ld bc, (CursorPosOld)   ; retrieve the the previous cursor position
                ld (AS_Tile2Pos), bc    ; and use it as the second tile position
                call AnimateGemSwap     ; animate the gem swapping
AS_End:         ld a, 1                 ;
                ld (CursorLive), a      ; set cursor as live
                ld bc, (CursorPosOld)   ; set cursor at old position
                call DrawCursorDo       ; draw the gem cursor
                ret
                
;---------------------------------------------------------------;
; AnimateGemSwap                                                ;
;  Animates the swapping of two Gems - no really it does ;-)    ;
;---------------------------------------------------------------;
SwapOne:        defw 0                  ; address of tile 1 to swap
SwapTwo:        defw 0                  ; address of tile 2 to swap
AnimateGemSwap: ld bc, (AS_Tile1Pos)
                call GetTileAt
                ld (SwapOne), hl
                ld bc, (AS_Tile2Pos)
                call GetTileAt
                ld (SwapTwo), hl
                ld b, 3
AGS_Lp1:        push bc
                halt
                ld bc, (AS_Tile1Pos)
                call AGS_ClearTile
                ld bc, (AS_Tile2Pos)
                call AGS_ClearTile
                call AGS_DrawTile1
                call AGS_DrawTile2
                halt
                call Pause
                halt
                pop bc
                djnz AGS_Lp1
                ret

AGS_DecPos:     ld a, (SwapFlags)
                srl a
                jr z, AGS_Down
                srl a
                jr z, AGS_Up
                srl a
                jr z, AGS_Right
                jr AGS_Left
                
AGS_IncPos:     ld a, (SwapFlags)
                srl a
                jr z, AGS_Up
                srl a
                jr z, AGS_Down
                srl a
                jr z, AGS_Left
AGS_Right:      ld a, c
                add a, 8
                ld c, a
                ret
AGS_Left:       ld a, c
                sub 8
                ld c, a
                ret
AGS_Down:       ld a, b
                add a, 8
                ld b, a
                ret
AGS_Up:         ld a, b
                sub 8
                ld b, a
                ret
                
AGS_DrawTile1:  ld bc, (AS_Tile1Pos)
                call AGS_DecPos
                ld (AS_Tile1Pos), bc
                ld hl, (SwapOne)
                xor a
                call DrwTile
                ret

AGS_DrawTile2:  ld bc, (AS_Tile2Pos)
                call AGS_IncPos
                ld (AS_Tile2Pos), bc
                ld hl, (SwapTwo)
                xor a
                call DrwTile
                ret

AGS_ClearTile:  push bc
                call CoordAttr
                ld de, 30
                ld b, 3
AGS_CP1:        ld (hl), 0
                inc hl
                ld (hl), 0
                inc hl
                ld (hl), 0
                add hl, de
                djnz AGS_CP1
                pop bc
                ret
                
;---------------------------------------------------------------;
; AS_CheckMatch                                                 ;
;  Checks the positions of the two tiles being swapped to see   ;
;  if any gem patterns match                                    ;
;  sets the carry flag if a match is found                      ;
;---------------------------------------------------------------;
AS_CheckMatch:  ld bc, (CursorPos)      ; get the current cursor position
                call ASCM_CheckPos      ; check the current position for a match
                jr c, ASCM_MF           ; match occurred so we test the other position too
                ld bc, (CursorPosOld)   ; get the old cursor position into bc
                call ASCM_CheckPos      ; check the old cursor position for a match
                call c, ReplaceGems     ; replace the matched gems
                ret
ASCM_MF:        ld hl, MatchSize
                ld de, MatchTemp
                ld bc, 7
                ldir                    ; copy the current matched variables
                ld bc, (CursorPosOld)   ; get the old cursor position into bc
                call ASCM_CheckPos      ; check the old cursor position for a match
                jr c, ASCM_2Matches     ; if carry set then both positions have a match
                ld de, MatchSize
                ld hl, MatchTemp
                ld bc, 7
                ldir                    ; copy the previous matched variables back into the matches variables
                call ReplaceGems        ; replace the matched gems from the previous check
                scf                     ; signal we had a match
                ret
                
;---------------------------------------------------------------;
; Check the value in BC if it contains a match. But first make  ;
; sure the values are snapped to a 24 pixel boundary            ;
;---------------------------------------------------------------;
ASCM_CheckPos:  ld a, c                 ; get x position
                sub 64                  ; x = x - 64
                call Snap24             ; snap the x pixel position to a 24 pixel boundary
                add a, 64               ; x = x + 64
                ld c, a                 ; put x into c
                ld a, b                 ; get y position
                call Snap24             ; snap it to a 24 pixel boundary
                ld b, a                 ; put y into b
                call Check4GemMatch     ; check the position for a match
                ret

;---------------------------------------------------------------;
; Both positions have a match so we need to be carefull how we  ;
; scroll the new gems into view.                                ;
;                                                               ;
; Basically if a position is shared between the 2 matches then  ;
; we need to only scroll that column once for that position.    ;
;---------------------------------------------------------------;
ASCM_2Matches:  ld a, (MatchDelta)
                ld b, a
                ld a, (MatchTemp)
                and a
                jr nz, ASCM_2MChkNZ
                ld a, b
                and a
                jr z, ASCM_NoCommonTile
                jr ASCM_CommonTile
ASCM_2MChkNZ:   ld a, b
                and a
                jr nz, ASCM_CommonTile
                
ASCM_NoCommonTile:
                call ReplaceGems        ; replace the matched gems from the current check
                ld de, MatchSize
                ld hl, MatchTemp
                ld bc, 7
                ldir                    ; copy the previous matched variables back into the matches variables
                call ReplaceGems        ; replace the matched gems from the previous check
                scf                     ; signal we had a match
                ret
                
ASCM_CommonTile:
                ;
                ; TODO: need to replace the current tiles
                ; then copy the current match info in another temp space
                ; then go through each position in the new temp space
                ; and check if its in the old temp space, if its no
                ; then setup the matches variables to do 1 scroll
                ; eg. set Matches to 1 and
                ;     the start position to the current position being checked
                ;     the do the scroll and replace
                ; and repeat for all positions
                ;
                ret
                
                

;---------------------------------------------------------------;
; AS_CheckAll                                                   ;
;  Goes through ALL positions on the gem board and checks for   ;
;  and gem matching gem patterns                                ;
;  sets the carry flag if a match is found                      ;
;---------------------------------------------------------------;
AS_CheckAll:    ld b, 0
                ld c, 64
AS_CA_Lp1:      push bc
                call Check4GemMatch
                pop bc
                ret c
                ld a, c
                add a, 24
                ld c, a
                jr nz, AS_CA_Lp1
                ld c, 64
                ld a, b
                add a, 24
                ld b, a
                cp 192
                jr nz, AS_CA_Lp1
                and a
                ret
                
;---------------------------------------------------------------;
; BonusCount                                                    ;
;---------------------------------------------------------------;
BonusCount:     defb 0
AS_BonusReset:  xor a
                ld (BonusCount), a
                ret
                
;---------------------------------------------------------------;
; AS_BonusAdd                                                   ;
;---------------------------------------------------------------;
AS_BonusAdd:    ret
                
;---------------------------------------------------------------;
; AS_AddScore                                                   ;
;  Adds the score for a set of matching gems                    ;
;---------------------------------------------------------------;
MatchScores:    defb 0, 0, 3, 5, 10
AS_ScoreAdd:    push af
                ld a, (MatchSize)
                ld hl, MatchScores
                ld c, a
                ld b, 0
                add hl, bc
                ld a, (hl)
                call IncrementScore
                call PrintScore
                call DrawLevelBar
                pop af
                ret

;---------------------------------------------------------------;
; Check4GemMatch                                                ;
;                                                               ;
; Checks the surrounding tiles of a given position to see if a  ;
; gem pattern match has occurred                                ;
;                                                               ;
; Inputs                                                        ;
;   b  - y position to check from                               ;
;   c  - x position to check from                               ;
;                                                               ;
; Outputs                                                       ;
;   carry flag set - a match was found and stored in the match  ;
;                    global parameters                          ;
;                                                               ;
;---------------------------------------------------------------;
MatchTemp:      defw 0, 0, 0, 0             ; used to backup the variables below
MatchSize:      defb 0                      ; the number of gems matched
MatchStartPos:  defb 0, 0                   ; the x, y position of the first gem
MatchEndPos:    defb 0, 0                   ; the x, y position of the last  gem
MatchDelta:     defb 0, 0                   ; the dx, dy values relative to the start of the 1st matched tile
MatchNewGems:   defb 0, 0, 0, 0, 0          ; the list of new gems to replace the matched gems
Check4GemMatch: ld hl, MatchesTable         ; hl points to the first row of patterns
CGM_Loop:       ld a, (hl)                  ; get the number of x, y pairs
                ld (MatchSize), a           ; save the number of matches in case it passes
                and a                       ; is it zero? (note how it also resets the carry flag :-)
                ret z                       ; if yes, then finished
                inc hl                      ; move to left bounds
                call CGM_ChkPatternRow      ; check the current pattern row
                jr nc, CGM_Loop             ; keep going until a match is found or the end of the table is reached
                ld hl, MatchesSoFar         ; point hl to the matches so far variable
                inc (hl)                    ; increment the counter
                ret                         ; a match was found, carry will be set automagically

CGM_ChkPatternRow:
                push af                     ; save the number of coords
                ld a, c                     ; get the min x bounds
                sub (hl)                    ; subtract the x position
                jr c, CGM_C4MFail           ; if nc then x is < min x
                inc hl                      ; move to min y bounds
                ld a, b                     ; get min y bounds
                sub (hl)                    ; subtract y position
                jr c, CGM_C4MFail           ; if nc then y < min y
                inc hl                      ; move to max x
                ld a, c                     ; get x
                add a, (hl)                 ; add max x position
                jr c, CGM_C4MFail           ; if c then x >= max x
                inc hl                      ; move to max y
                ld a, b                     ; get y
                add a, (hl)                 ; add max y position
                jr c, CGM_C4MFail           ; if c then y >= max y
                inc hl                      ; move to 1st dx, dy pair
                ;
                ; Check pattern row
                ;
                pop af                      ; restore the number of coords
                push af                     ; save the number of dx, dy coords
                ld e, (hl)                  ; e = dx coord
                inc hl                      ; move to dy coord
                ld d, (hl)                  ; d = dy coord
                inc hl                      ; move to next dx, dy pair
                push bc                     ; save the tile check position
                push hl                     ; save the pattern row position
                ld a, c                     ; a = x
                add a, e                    ; a = a + dx
                ld c, a                     ; c = a
                ld a, b                     ; a = y
                add a, d                    ; a = a + dy
                ld b, a                     ; b = a
                ld (MatchStartPos), bc      ; save the start position of the match
                call Pix                    ; convert bc to hl pixel address
                call Attr                   ; convert hl to attr address
                ld a, (hl)                  ; get the tile colour
                and 7                       ; get the ink colour only
                ld (TileCheck), a           ; store the tile index
                pop hl                      ; restore the pattern row
                pop bc                      ; restore the tile position
                pop af                      ; restore the x,y pair count
                dec a                       ; decrement the pair count
                ;
                ; first pair has set the tile
                ; to match for the test to pass
                ;
CGM_C4M_Lp:     push af                     ; save the dx, dy pair count
                ld e, (hl)                  ; e = dx
                inc hl                      ; move to dy
                ld d, (hl)                  ; d = dy
                inc hl                      ; move to next pair
                push bc                     ; save the tile position
                push hl                     ; save the pattern row position
                ld a, c                     ; a = tile x
                add a, e                    ; a = tile x + dx
                ld c, a                     ; c = a
                ld a, b                     ; a = tile y
                add a, d                    ; a = tile y + dy
                ld b, a                     ; b = a
                ld (MatchEndPos), bc        ; save the end position of the match (so far)
                call CoordAttr              ; get attribute address of position x, y
                ld a, (hl)                  ; get the tile colour
                and 7                       ; get the ink colour only
                ld e, a                     ; save a in e
                pop hl                      ; restore the pattern row position
                pop bc                      ; restore the tile position
                ld a, (TileCheck)           ; a with the first tile colour
                cp e                        ; cp to current tile colour
                jr nz, CGM_C4MFail          ; if not the same failed
                pop af                      ; so far so good, restore the pair count
                dec a                       ; decrement pair count
                jr nz, CGM_C4M_Lp           ; keep going for all pairs
                scf                         ; wow! a pass so set carry to indicate success
                ret
                
TileCheck:      defb 0                      ; the tile colour to match

;
; position is not valid to do a pattern check
; so skip over all the x,y coords to the end of the pattern run
;
CGM_C4MFail:    pop af                      ; restore the number of x, y coords
CGM_C4M_Skp:    ld a, (hl)                  ; get pattern byte
                cp 255                      ; is it the end of pattern marker?
                inc hl                      ; move over the pattern byte
                jr nz, CGM_C4M_Skp          ; keep moving if it is not the end of pattern marker
                and a                       ; reset carry flag
                ret                         ; hl points to the next pattern row

;
; Matches table
;
; number of matches, left, top, right, bottom
;   offset 1 x, offset 1 y, offset 2 x, offset 2 y... offset x n, offset y n, (255) end of pair marker
;

MatchesTable:   ; matches for 5 of a kind
                ;   no   (l,   t)  (r,   b)  (x,   y)  (x,   y)  (x,   y)  (x,   y)  (x,   y)
                defb 5,  64,   0,  96,   0,   0,   0,  24,   0,  48,   0,  72,   0,  96,   0, 255    ; (  0,  0) ( 24,  0) ( 48,  0) ( 72,  0) ( 96,  0)
                defb 5,  88,   0,  72,   0, -24,   0,   0,   0,  24,   0,  48,   0,  72,   0, 255    ; (-24,  0) (  0,  0) ( 24,  0) ( 48,  0) ( 72,  0)
                defb 5, 112,   0,  48,   0, -48,   0, -24,   0,   0,   0,  24,   0,  48,   0, 255    ; (-48,  0) (-24,  0) (  0,  0) ( 24,  0) ( 48,  0)
                defb 5, 136,   0,  24,   0, -72,   0, -48,   0, -24,   0,   0,   0,  24,   0, 255    ; (-72,  0) (-48,  0) (-24,  0) ( 0,   0) ( 24,  0)
                defb 5, 160,   0,   0,   0, -96,   0, -72,   0, -48,   0, -24,   0,   0,   0, 255    ; (-96,  0) (-72,  0) (-48,  0) (-24,  0) (  0,  0)
                defb 5,  64,   0,   0, 160,   0,   0,   0,  24,   0,  48,   0,  72,   0,  96, 255    ; (  0,  0) (  0, 24) (  0, 48) (  0, 72) (  0, 96)
                defb 5,  64,  24,   0, 136,   0, -24,   0,   0,   0,  24,   0,  48,   0,  72, 255    ; (  0,-24) (  0,  0) (  0, 24) (  0, 48) (  0, 72)
                defb 5,  64,  48,   0, 112,   0, -48,   0, -24,   0,   0,   0,  24,   0,  48, 255    ; (  0,-48) (  0,-24) (  0,  0) (  0, 24) (  0, 48)
                defb 5,  64,  72,   0,  88,   0, -72,   0, -48,   0, -24,   0,   0,   0,  24, 255    ; (  0,-72) (  0,-48) (  0,-24) (  0,  0) (  0, 24)
                defb 5,  64,  96,   0,  64,   0, -96,   0, -72,   0, -48,   0, -24,   0,   0, 255    ; (  0,-96) (  0,-72) (  0,-48) (  0,-24) (  0,  0)

                ; matches for 4 of a kind
                ;   no   (l,   t)  (r,   b)  (x,   y)  (x,   y)  (x,   y)   (x,   y)
                defb 4,  64,   0,  72,   0,   0,   0,  24,   0,  48,   0,   72,   0, 255             ; (  0,  0) ( 24,  0) ( 48,  0) ( 72,  0)
                defb 4,  88,   0,  48,   0, -24,   0,   0,   0,  24,   0,   48,   0, 255             ; (-24,  0) (  0,  0) ( 24,  0) ( 48,  0)
                defb 4, 112,   0,  24,   0, -48,   0, -24,   0,   0,   0,   24,   0, 255             ; (-48,  0) (-24,  0) (  0,  0) ( 24,  0)
                defb 4, 136,   0,   0,   0, -72,   0, -48,   0, -24,   0,    0,   0, 255             ; (-72,  0) (-48,  0) (-24,  0) (  0,  0)
                defb 4,  64,   0,   0, 136,   0,   0,   0,  24,   0,  48,    0,  72, 255             ; (  0,  0) (  0, 24) (  0, 48) (  0, 72)
                defb 4,  64,  24,   0, 112,   0, -24,   0,   0,   0,  24,    0,  48, 255             ; (  0,-24) (  0,  0) (  0, 24) (  0, 48)
                defb 4,  64,  48,   0,  88,   0, -48,   0, -24,   0,   0,    0,  24, 255             ; (  0,-48) (  0,-24) (  0,  0) (  0, 24)
                defb 4,  64,  72,   0,  64,   0, -72,   0, -48,   0, -24,    0,   0, 255             ; (  0,-72) (  0,-48) (  0,-24) (  0,  0)

                ; matches to 3 of a kind
                ;   no   (l,   t)  (r,   b) ( x,   y) ( x,   y) ( x,   y)
                defb 3,  64,   0,  48,   0,   0,   0,  24,   0,  48,   0, 255                        ; (  0,  0) ( 24,  0) ( 48,  0)
                defb 3,  88,   0,  24,   0, -24,   0,   0,   0,  24,   0, 255                        ; (-24,  0) (  0,  0) ( 24,  0)
                defb 3, 112,   0,   0,   0, -48,   0, -24,   0,   0,   0, 255                        ; (-48,  0) (-24,  0) (  0,  0)
                defb 3,  64,   0,   0, 112,   0,   0,   0,  24,   0,  48, 255                        ; (  0,  0) (  0, 24) (  0, 48)
                defb 3,  64,  24,   0,  88,   0, -24,   0,   0,   0,  24, 255                        ; (  0,-24) (  0,  0) (  0, 24)
                defb 3,  64,  48,   0,  64,   0, -48,   0, -24,   0,   0, 255                        ; (  0,-48) (  0,-24) (  0,  0)
                
                ; end of table
                defb 0

;---------------------------------------------------------------;
; RemoveGems                                                    ;
;  Removes the matched gems from the board, and then scrolls    ;
;  existing gems down onto the blank space left. Then inserts   ;
;  inserts new gems for all the blank gems                      ;
;---------------------------------------------------------------;
ReplaceGems:    push af                     ; save the carry flag
                call ChooseNewGems          ; choose the gems to replace the matched gems
                call ClearGems              ; clear the gems that were matched
                call Pause
                call Pause
                call Pause
                call Pause
                call Pause
                ;call Pause
                ;call Pause
                ;call Pause
                ;call Pause
                ;call Pause
                ;call Pause
                ;call Pause
                ;call Pause
                call ScrollGems             ; scroll the existing gems to the space
                call AS_ScoreAdd            ; add the score for the matched gems
                pop af                      ; restore the carry flag
                ret

;---------------------------------------------------------------;
; ClearGems                                                     ;
;  Removes the matched gems from the board                      ;
;---------------------------------------------------------------;
ClearGems:      ld a, (MatchSize)           ; get the number of tiles to remove
                ld h, a                     ; use h as the tile counter
                ld bc, (MatchStartPos)      ; get the position of the first tile
                ld de, (MatchEndPos)        ; get the position of the second tile
                ld a, d                     ; get 2nd y in a
                cp b                        ; compare to 1st y
                ld d, 0                     ; reset d to zero
                jr z, CGs_Nxt               ; if y's are equal start on x comparsions
                ld d, 24                    ; set dy to +24
                jr nc, CGs_Nxt              ; is the 1st y < 2nd y?
                ld d, -24                   ; no, so offset is -24
CGs_Nxt:        ld a, e                     ; get 2nd x in a
                cp c                        ; compare to 1st x
                ld e, 0                     ; set dx to zero
                jr z, CGs_Cont              ; if x's are equal start clearing the tiles
                ld e, 24                    ; no, set dy to 24
                jr nc, CGs_Cont             ; is the 1st x < 2nd y?
                ld e, -24                   ; no, so offset is -24
CGs_Cont:       ld (MatchDelta), de         ; save the match deltas relative to the start position
CGs_Lp:         push de                     ; save dx/dy
                push hl                     ; save the tile counter
                call AGS_ClearTile          ; clear the tile
                pop hl                      ; restore the tile counter
                pop de                      ; restore dx/dy
                ld a, b                     ; add dy
                add a, d                    ; to y
                ld b, a                     ; y = y + dx
                ld a, c                     ; add dx
                add a, e                    ; to x
                ld c, a                     ; x = x + dy
                dec h                       ; dec the tile counter
                jr nz, CGs_Lp               ; loop until all tiles are cleared
                ret

;---------------------------------------------------------------;
; ScrollGems                                                    ;
; Scrolls the existing gems into the slots of the removed gems  ;
;---------------------------------------------------------------;
ScrollGems:     ld bc, (MatchStartPos)      ; get tile 1 position in bc
                ld a, 16                    ; add 16
                add a, b                    ; to the y value
                ld b, a                     ; y1 = y1 + 16
                ld de, (MatchDelta)         ; get the matched deltas
                ld a, e                     ; get the x delta
                and a                       ; is it zero?
                jr z, SG_Vertical           ; if yes, we need to do a vertical scroll
                                            ; ok, we're doing a horizontal scroll
                ld h, 3                     ; need to scroll 3 rows of characters
SG_Lp2:         push bc                     ; save the start position of the scrolling
                ld a, (MatchSize)           ; get the match count
                ld l, a                     ; use l as the match count
SG_Lp1:         push hl                     ; save it
                push bc                     ; save the current column scroll position
                push de                     ; save the destination column position
                call SG_ScrollColumn        ; scroll the current column
                pop de                      ; restore the destination column position
                pop bc                      ; restore the current scroll column
                pop hl                      ; get the match count
                push hl                     ; save scroll column
                push de                     ; save the dst column
                push bc                     ; save match count
                call DrawNewGem             ; draw part of the new gem
                pop bc                      ; restore match count
                pop de                      ; restore the dst column
                pop hl                      ; restore the scroll column
                ld a, c                     ; get current x
                add a, e                    ; move to next column (if needed)
                ld c, a                     ; put x into c again
                dec l                       ; decrement the match count
                jr nz, SG_Lp1               ; keep going until all tiles are scrolled
                pop bc                      ; get the original scroll start position
                dec h                       ; decrement the row count
                jr nz, SG_Lp2               ; if not all rows done then continue
                ret

SG_Vertical:    ld a, (MatchSize)           ; get the match count
                ld l, a                     ; use l as the match count
                push hl                     ; save the match count
                dec l                       ; dec the match count
                ld h, 24                    ; 24 pixels per gem block
                ld a, b                     ; get y position in a
SGV_Lp1:        add a, h                    ; add 24 to y for each gem we need to scroll over
                dec l                       ; dec the match count
                jr nz, SGV_Lp1              ; keep counting all the gems
                ld b, a                     ; store the new y position in b
                pop hl                      ; restore the match count
SG_Lp4:         push bc                     ; save the start position of the scrolling
                ld h, 3                     ; need to scroll 3 rows of characters
SG_Lp3:         push hl                     ; save it
                push bc                     ; save the current column scroll position
                push de                     ; save the destination column position
                call SG_ScrollColumn        ; scroll the current column
                pop de                      ; restore the destination column position
                pop bc                      ; restore the current scroll column
                pop hl                      ; get the match count
                push hl                     ; save scroll column
                push de                     ; save the dst column
                push bc                     ; save match count
                call DrawNewGem             ; draw part of the new gem
                pop bc                      ; restore match count
                pop de                      ; restore the dst column
                pop hl                      ; restore the scroll column
                dec h                       ; decrement the match count
                jr nz, SG_Lp3               ; keep going until all tiles are scrolled
                pop bc                      ; get the original scroll start position
                dec l                       ; decrement the row count
                jr nz, SG_Lp4               ; if not all rows done then continue
                ret


;---------------------------------------------------------------;
; SG_ScrollColumn                                               ;
; Scrolls a gem column 1 row at a time                          ;
;---------------------------------------------------------------;
SG_ScrollColumn:
                ld a, 8                     ; add 8
                add a, b                    ; to the y value
                ld d, a                     ; save in d
                ld e, c                     ; put x in e
                push de                     ; save destintation x,y
                call Pix                    ; get screen addr of current x,y
                call Decy                   ; move to the line above it
                pop bc                      ; get destination x,y in bc
                ex de, hl                   ; save the source screen addr in de
                call Pix                    ; get screen addr of destination x,y
                call Decy                   ; and then move to the line above it
                ex de, hl                   ; de = destination addr and hl in source addr
                ld c, 3                     ; need to scroll 3 columns
SG_SP_Lp1:      push hl                     ; save the src addr
                push de                     ; save the dst addr
SG_SP_Lp5:      ld b, 8                     ; do 8 lines at once
SG_SP_Lp2:      ld a, (hl)                  ; get src byte
                ld (de), a                  ; put into dst byte
                call Decy                   ; move up src 1 line
                ex de, hl                   ; exchange src and dst addr's
                call Decy                   ; move up 1 dst line
                ex de, hl                   ; exchange src and dst addr's
                djnz SG_SP_Lp2              ; do for all 8 lines of a character block
                ld a, h                     ; get the high byte of the src address
                cp 63                       ; is it in ROM?
                jp nz, SG_SP_Lp5            ; if not then keep scrolling the column
                pop de                      ; get the dst addr
                pop hl                      ; get the src addr
                inc hl                      ; move to next src column
                inc de                      ; move to next dst column
                dec c                       ; decrement the column counter
                jp nz, SG_SP_Lp1            ; keep scrolling if not done 3 columns
;
; scroll the attributes
;
                dec hl                      ; dec to previous src column
                call Attr                   ; convert to attribute address
                ld bc, 32                   ; 32 columns on the screen
                push hl                     ; save src attr address
                add hl, bc                  ; move down 1 attr line
                ex de, hl                   ; put dst attr address in de
                pop hl                      ; get src attr address in hl
                ld bc, 30                   ; 30 characters to next start column
SG_SP_Lp3:      ld a, (hl)                  ; get the src attr
                ld (de), a                  ; put into dst attr
                dec hl                      ; move to previous src column
                dec de                      ; move to previous dst column
                ld a, (hl)                  ; get the src attr
                ld (de), a                  ; put into dst attr
                dec hl                      ; move to previous src column
                dec de                      ; move to previous dst column
                ld a, (hl)                  ; get the src attr
                ld (de), a                  ; put into dst attr
                sbc hl, bc                  ; move to next src start column
                ld a, h                     ; get high byte of hl
                cp 87                       ; is it in the pixel buffer?
                jp z, SG_SP_NxtCol2         ; no (nz), so continue scrolling attr's
                ex de, hl                   ; get the dst attr
                sbc hl, bc                  ; move to start of next dst column
                ex de, hl                   ; get src attr in hl
                jp SG_SP_Lp3                ; continue scrolling
SG_SP_NxtCol2:  ret                          ; finished scrolling attr columns

;---------------------------------------------------------------;
; DrawNewGem                                                    ;
;  Draws part of the new gems being scrolled down               ;
;                                                               ;
;  c - x position of new gem                                    ;
;  l - the gem to draw from the MatchNewGems table              ;
;  h - the row to draw 3, 2 or 1                                ;
;                                                               ;
;---------------------------------------------------------------;
DNG_GemAddr:    defw 0
DrawNewGem:     push hl                     ; save the gem info
                push bc                     ; save x position
                ld b, 0                     ; reset b
                ld c, l                     ; bc = gem offset into MatchNewGems table
                dec c                       ; we need 0-4, not 1 - 5
                ld hl, MatchNewGems         ; hl = MatchNewGems table
                add hl, bc                  ; add the offset
                ld a, (hl)                  ; put gem to draw from the table into a
                call GetGemAddr             ; get the address of the tile to draw
                inc hl                      ; skip width
                inc hl                      ; skip height
                ld (DNG_GemAddr), hl        ; save the gem address
                ex de, hl                   ; de = gem graphics address, hl = gem info
                pop bc                      ; get x position
                ld b, 0                     ; top line of display
                call Pix                    ; hl = screen address of new gem
                pop bc                      ; get the gem info (from push hl into bc)
                ld a, b                     ; get the row no. to draw
                ld bc, 0                    ; draw top row of gem
                dec a                       ; decrement the row count
                jr z, DNG_Cont              ; if 0 then continue to draw
DNG_Nxt1:       ld bc, 24                   ; draw middle row of gem
                dec a                       ; decrement the row count
                jr z, DNG_Cont              ; if 0 then continue to draw
                ld bc, 48                   ; drawing bottom row
DNG_Cont:       ex de, hl                   ; de = scr addr, hl = gem addr
                add hl, bc                  ; move to correct gem graphic offset
                ex de, hl                   ; de = gem addr, hl = scr addr
                ld b, 8                     ; draw 8 lines of graphics
DNG_Lp1:        push hl                     ; save the screen address
                ld a, (de)                  ; get the gem graphics
                ld (hl), a                  ; put on screen
                inc hl                      ; next column
                inc de                      ; next graphics
                ld a, (de)                  ; repeat for next 2 columns/characters
                ld (hl), a
                inc hl
                inc de
                ld a, (de)
                ld (hl), a
                inc de
                pop hl                      ; restore the screen address
                inc h                       ; move down 1 line
                djnz DNG_Lp1                ; repeat for all 8 lines
                dec h                       ; move up a line
                call Attr                   ; convert to attribute address
                ex de, hl                   ; de = attr address
                ld hl, (DNG_GemAddr)        ; get the gem graphics address
                ld bc, 72                   ; 3 * 24 = 72 bytes of pixel data
                add hl, bc                  ; point to colour info
                ld a, (hl)                  ; get tile colour
                ld (de), a                  ; put gem colour into next 3 attr characters
                inc de
                ld (de), a
                inc de
                ld (de), a
                ret
                
;---------------------------------------------------------------;
; ChooseNewGems                                                 ;
;  Chooses the new gems to replace the gems matched             ;
;---------------------------------------------------------------;
ChooseNewGems:  ld a, (MatchSize)           ; get the number of gems matched
                ld b, a                     ; b contains the gems matched
                ld hl, MatchNewGems         ; hl points to the new gems table
                ld c, 0                     ; c stores the previously gem generated
CNG_Lp1:        ld a, 15                    ; random number seed
                call RandomNumber           ; get a random number
                and 7                       ; we need 0 - 6
                cp 7                        ; make sure its not 7
                jr z, CNG_Lp1               ; if so, get another number
                cp c                        ; compare to the last number generated
                jr z, CNG_Lp1               ; if the same then get another number
                ld c, a                     ; save the chosen gem
                ld (hl), a                  ; put the number in the table
                inc hl                      ; move to the next new gem entry in the table
                djnz CNG_Lp1                ; choose all required new gems
                ret

;---------------------------------------------------------------;
; GetTileAt                                                     ;
;                                                               ;
; Retrieves the tile address at the position specified in bc    ;
;                                                               ;
; Inputs                                                        ;
;   b  - y position                                             ;
;   c  - x position                                             ;
;                                                               ;
; Outputs                                                       ;
;   hl - the address for the tile at the position               ;
;                                                               ;
;---------------------------------------------------------------;
GetTileAt:      call CoordAttr              ; convert x,y to attribute address
                ld a, (hl)                  ; get colour at x, y
                and 7                       ; only want the ink colour
                jr nz, GTA_Cont             ; if ink is not zero, then goto continue
                ld a, (hl)                  ; need the paper colour then
                srl a                       ; shift the paper colour into the ink position
                srl a
                srl a                       ; paper is now ink
                and 7                       ; mask the ink
GTA_Cont:       dec a                       ; decrement the ink colour
                jp GetGemAddr               ; get the address for the selected tile index


;---------------------------------------------------------------;
; CheckLevelAndGO                                               ;
;                                                               ;
; Checks for when the next level is to be incremented and also  ;
; for Game Over conditions such as time out or no more moves.   ;
;                                                               ;
;---------------------------------------------------------------;
CheckLevelGO:   call CheckForGameOver
                ret nc
                call CheckLevelUp
                call DrawLevelBar
                ret
                
;---------------------------------------------------------------;
; LevelUp                                                       ;
;                                                               ;
;  Checks to see if the player has levelled up, if so it also   ;
; adds a level bonus and changes the level the player is on.    ;
;---------------------------------------------------------------;
CheckLevelUp:   ld hl, LevelTable
                ld a, (Level)
                ld c, a
                ld b, 0
                add hl, bc
                ld a, (MatchesSoFar)
                cp (hl)
                ret c
                ;ld a, (hl)
                ld a, 10                    ; add 100 to score
                call IncrementScore
                call PrintScore
                ld hl, Level
                inc (hl)                    ; move to the next level
                call PrintLevel
                xor a
                ld (MatchesSoFar), a        ; reset the matches so far
                ret

;---------------------------------------------------------------;
; LevelTable                                                    ;
;                                                               ;
;  This table doubles as the level match count for levelling up ;
; and also the bonus points awarded for levelling up            ;
;---------------------------------------------------------------;
LevelTable:     defb 10     ; to level  1
                defb 10     ; to level  2
                defb 16     ; to level  3
                defb 16     ; to level  4
                defb 16     ; to level  5
                defb 20     ; to level  6
                defb 20     ; to level  7
                defb 20     ; to level  8
                defb 20     ; to level  9
                defb 24     ; to level 10
                defb 24     ; to level 11
                defb 24     ; to level 12
                defb 24     ; to level 13
                defb 24     ; to level 14
                defb 32     ; to level 15
                defb 32     ; to level 16
                defb 32     ; to level 17
                defb 32     ; to level 18
                defb 32     ; to level 19
                defb 32     ; to level 20
                defb 40     ; to level 21
                defb 40     ; to level 22
                defb 40     ; to level 23
                defb 40     ; to level 24
                defb 40     ; to level 25
                defb 40     ; to level 26
                defb 40     ; to level 27
                defb 48     ; to level 28
                defb 48     ; to level 29
                defb 48     ; to level 30
                defb 48     ; to level 31
                defb 48     ; to level 32
                defb 48     ; to level 33
                defb 48     ; to level 34
                defb 48     ; to level 35

                ;
                ; 40 pixel wide bar
                ;
                
Level10:        defb 10,  0,  4,  8, 12, 16, 20, 24, 28, 32, 36, 40
Level16:        defb 16,  0,  2,  5,  7, 10, 12, 15, 17, 20, 22
                defb     25, 27, 30, 32, 35, 37, 40
Level20:        defb 20,  0,  2,  4,  6,  8, 10, 12, 14, 16, 18
                defb     20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40
Level24:        defb 24,  0,  1,  3,  5,  6,  8, 10, 11, 13, 15
                defb     16, 18, 20, 21, 23, 25, 26, 38, 30, 31
                defb     33, 35, 36, 38, 40
Level32:        defb 32,  0,  1,  2,  3,  5,  6,  7,  8, 10, 11
                defb     12, 13, 15, 16, 17, 18, 20, 21, 22, 23
                defb     25, 26, 27, 28, 30, 31, 32, 33, 35, 36
                defb     37, 38, 40
Level40:        defb 40,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9
                defb     10, 11, 12, 13, 14, 15, 16, 17, 18, 19
                defb     20, 21, 22, 23, 24, 25, 26, 27, 28, 29
                defb     30, 31, 32, 33, 34, 35, 36, 37, 38, 39
                defb     40
Level48:        defb 48,  0,  0,  1,  2,  3,  4,  5,  5,  6,  7
                defb      8,  9, 10, 10, 11, 12, 13, 14, 15, 15
                defb     16, 17, 18, 19, 20, 20, 21, 22, 23, 24
                defb     25, 25, 26, 27, 28, 29, 30, 30, 31, 32
                defb     33, 34, 35, 35, 36, 37, 38, 39, 40

LevelAdjustTable:
                defw Level10
                defw Level10
                defw Level16
                defw Level16
                defw Level16
                defw Level20
                defw Level20
                defw Level20
                defw Level20
                defw Level24
                defw Level24
                defw Level24
                defw Level24
                defw Level24
                defw Level32
                defw Level32
                defw Level32
                defw Level32
                defw Level32
                defw Level32
                defw Level40
                defw Level40
                defw Level40
                defw Level40
                defw Level40
                defw Level40
                defw Level40
                defw Level48
                defw Level48
                defw Level48
                defw Level48
                defw Level48
                defw Level48
                defw Level48
                defw Level48

LastBarSize:    defb 0

DrawLevelBar:   ld a, (Level)               ; get the current level
                add a, a
                ld c, a                     ; put level into bc
                ld b, 0                     ;
                ld hl, LevelAdjustTable     ; point hl to level table
                add hl, bc                  ; move to correct level offset
                ld e, (hl)                  ; get the levels difficulty value
                inc hl
                ld d, (hl)
                ex de, hl
                ld d, (hl)
DLB_Cont:       ld a, (MatchesSoFar)        ; get the number of matches so far
                cp d                        ; have we exceeded the level value?
                jr c, DLB_Cont2             ; if no then goto continue 2
                ld a, d                     ; yes so restrict it back to the max level value
DLB_Cont2:      ld c, a                     ; put into bc
                ld b, 0                     ;
                inc hl                      ; move past the level value
                add hl, bc                  ; to point correct level offset
                ld a, (hl)                  ; get the number of pixels to draw
DrawBar:        ld hl, LastBarSize          ; point hl to the last pixel postition we plotted to
                cp (hl)                     ; is it the same as the current position?
                ret z                       ; return if it is
                ld e, a                     ; put end position into e
                ld a, (hl)                  ; get last plot position
                ld d, a                     ; put start position into d
                ld (hl), e                  ; store the end position
                cp e                        ; cp start to end (carry set if end > start)
                jr c, DB_Cont               ; continue if end > start
                ld a, d                     ; swap start and end
                ld d, e                     ; d is min position (start)
                ld e, a                     ; e is max position (end)
DB_Cont:        ld c, 12                    ; x = 12
                ld a, d                     ; get current dx
                add a, c                    ; dx += x
                ld c, a                     ; x = x + dx
DB_Lp1:         ld b, 93                    ; y = 98
                push de                     ; save the start and end positions
                ld e, 7                     ; drawing 6 pixels
DB_Lp2:         push bc                     ; save the pixel positions
                call XorPixel               ; plot/unplot the pixel
                pop bc                      ; restore the pixel position
                inc b                       ; y = y + 1
                dec e                       ; dec y counter
                jr nz, DB_Lp2               ; keep going until all 6 pixels are done
                pop de                      ; restore the start and end positions
                inc c                       ; x = x + 1
                inc d                       ; start = start + 1
                ld a, d                     ; get start position
                cp e                        ; is start equal to the end position?
                jr nz, DB_Lp1               ; if not then contine plotting
                ret

;---------------------------------------------------------------;
; CheckForGameOver                                              ;
;  Goes through ALL positions on the gem board and checks for   ;
;  the possible moves left and if none are left then sets       ;
;  the game over flag and resets the carry set                  ;
;---------------------------------------------------------------;
CheckForGameOver:
                ld b, 0
                ld c, 64
GFGO_Lp:        push bc
                ld hl, PossiblesTable
                call Check4GemMatch + 3
                pop bc
                ret c
                ld a, c
                add a, 24
                ld c, a
                jr nz, GFGO_Lp
                ld c, 64
                ld a, b
                add a, 24
                ld b, a
                cp 192
                jr nz, GFGO_Lp
                and a
                ld a, GF_GAME_OVER
                call SetGameFlag
                ret

PossiblesTable: ;
                ; This table represents the gem patterns of possible swaps
                ; available to the player so their next move
                ;
                ; It works exactly the same way as the MatchesTable but it finds
                ; next possible move not the completed gem matches
                ;
                ;   no   (l,   t)  (r,   b)  (x,   y)  (x,   y)  (x,   y) end of marker
                ;
                ;     XX
                ;       X
                defb 3,  64,   0,  48,  88,   0,   0,  24,   0,  48,  24, 255
                ;       X
                ;     XX
                defb 3,  64,   0,  48,  88,   0,  24,  24,  24,  48,   0, 255
                ;      XX
                ;     X
                defb 3,  64,   0,  48,  88,   0,  24,  24,   0,  48,   0, 255
                ;     X
                ;      XX
                defb 3,  64,   0,  48,  88,   0,   0,  24,  24,  48,  24, 255
                ;      X
                ;     X X
                defb 3,  64,   0,  48,  88,   0,  24,  24,   0,  48,  24, 255
                ;     X X
                ;      X
                defb 3,  64,   0,  48,  88,   0,   0,  24,  24,  48,   0, 255

                ;   no   (l,   t)  (r,   b)  (x,   y)  (x,   y)  (x,   y) end of marker
                ;     X
                ;      X
                ;      X
                defb 3,  64,   0,  48,  88,   0,   0,  24,  24,  24,  48, 255
                ;      X
                ;     X
                ;     X
                defb 3,  64,   0,  48,  88,  24,   0,   0,  24,   0,  48, 255
                ;     X
                ;      X
                ;     X
                defb 3,  64,   0,  48,  88,   0,   0,  24,  24,   0,  48, 255
                ;      X
                ;     X
                ;      X
                defb 3,  64,   0,  48,  88,  24,   0,   0,  24,  24,  48, 255
                ;     X
                ;     X
                ;      X
                defb 3,  64,   0,  48,  88,   0,   0,   0,  24,  24,  48, 255
                ;      X
                ;     X
                ;     X
                defb 3,  64,   0,  48,  88,  24,   0,  24,  24,   0,  48, 255

                ;   no   (l,   t)  (r,   b)  (x,   y)  (x,   y)  (x,   y) end of marker
                ;     XX_X
                defb 3,  64,   0,  72,  64,   0,   0,  24,   0,  72,   0, 255
                ;     X_XX
                defb 3,  64,   0,  72,  64,   0,   0,  48,   0,  72,   0, 255

                ;   no   (l,   t)  (r,   b)  (x,   y)  (x,   y)  (x,   y) end of marker
                ;     X
                ;     _
                ;     X
                ;     X
                defb 3,  64,   0,  24, 136,   0,   0,   0,  48,   0,  72, 255
                ;     X
                ;     X
                ;     _
                ;     X
                defb 3,  64,   0,  24, 136,   0,   0,   0,  24,   0,  72, 255

                defb 0
                
