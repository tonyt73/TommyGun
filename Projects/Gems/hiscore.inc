;---------------------------------------------------------------;
;                                                               ;
;   HiScore.inc                                                 ;
;                                                               ;
;   This file contains routines for dealing with the Hi Score   ;
;   Table and entering of hi score names                        ;
;                                                               ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; DisplayHiScore                                                ;
;                                                               ;
;   Displays the hi-score table                                 ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         4th May 2006                                ;
;   Last Changed    4th July 2006 - Ian Munro                   ;
;       Removed the title and press space code as this is now   ;
;       handled by the high score menu routine                  ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
;                                                               ;
;   Outputs                                                     ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af, bc, de, hl                                          ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, bc, de, hl                                          ;
;---------------------------------------------------------------;
DisplayHiScore: ld a, 10                ; 10 score items to loop through
                ld b, 48                ; start y at 48
                ld c, 88                ; x = 88
                ld hl, ScoreTable       ; point hl to the hi score table text
DS_Lp1:         push af                 ; save the loop count
                push bc                 ; save the current coordinates
                push hl                 ; save the hi score text address
                call Pix                ; get the screen addr for coords
                ex de, hl               ; put the result into de
                pop hl                  ; get the text pointer back
                push hl                 ; save it again
                call PrintLine          ; display the hi score text
                pop hl                  ; get the text pointer back
                ld bc, 19               ; each score element is 19 bytes
                add hl, bc              ; so move to the next hi score item
                pop bc                  ; get the coordinates
                ld a, b                 ; get y into a
                add a, 8                ; move to next line
                ld b, a                 ; put a into b (y)
                pop af                  ; get the loop counter
                dec a                   ; decrement the loop
                jr nz, DS_Lp1           ; keep going if we are not finished
                ret                     ; all done

;---------------------------------------------------------------;
; IsNewHighScore                                                ;
;                                                               ;
;   Checks to see if the new score can be added to the high     ;
;   score table. If it can the carry flag will be set           ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         4st May 2006                                ;
;   Last Changed    4st May 2006                                ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
;                                                               ;
;   Outputs                                                     ;
;       carry will be set if the new score can be added to the  ;
;       table                                                   ;
;       de = start address of where the users name goes         ;
;                                                               ;
;   Regs Used                                                   ;
;       af, bc, de, hl                                          ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, bc, de, hl                                          ;
;---------------------------------------------------------------;

IsNewHighScore: ld de, ScoreTable
                ld c, 10                ; number of scores in hi-table

NextTableItem:  ld hl, NewScore
                ld b, 6                 ; number of bytes holding the score
                push de
                
                inc de
ParseScoreByte: ld a, (de)
                cp (hl)
                jp c, Bigger
                inc de
                inc hl
                jp nz, Smaller
                djnz ParseScoreByte

Bigger:         pop de                  ; equal and higher values are inserted above
                push de
                ld hl, ScoreTableEnd

                xor a
                sbc hl, de
                ld b, h
                ld c, l

                ld hl, ScoreTableEnd-19
                ld de, ScoreTableEnd
                lddr
                pop de
                ld hl, NewScore-1
                ld bc, 8                ; only insert the score here, don't add the name
                ldir
                scf                     ; set the carry flag so that we know we have a high score
                ret                     ; exit

Smaller:        pop de
                ld hl, 19
                add hl, de
                ex de, hl

                dec c
                jp nz, NextTableItem
                ret                     ; exit, no hi-score

;---------------------------------------------------------------;
; PrintLine                                                     ;
;                                                               ;
;   Prints a line of text and applies a colour                  ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         4st May 2006                                ;
;   Last Changed    10th July 2006                              ;
;       Stopped using the af' register                          ;
;                                                               ;
;   Inputs                                                      ;
;       hl = the data string to display                         ;
;       de = the screen address of where the string will start  ;
;                                                               ;
;   Outputs                                                     ;
;       coloured text is drawn on the screen                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af, b, de, hl                                           ;
;                                                               ;
;   Regs destroyed                                              ;
;       b, de, hl                                               ;
;---------------------------------------------------------------;

PrintLine:      push af
                ld a, (hl)
PrintLineLoop:  ld b,a               ; store colour
                inc hl
                ld a, (hl)
                cp $ff
                jp z, PrintLineExit
                push hl
                push de
                ld h, 0
                sub 32
                ld l, a
                add hl, hl
                add hl, hl
                add hl, hl
                ld de, font
                add hl, de
                pop de
                push de
                ld a,b
                push af
                call Print8x8Char
                pop af
                pop de
                call AddCharColour
                pop hl
                inc de
                jp PrintLineLoop
PrintLineExit:  pop af
                ret


;---------------------------------------------------------------;
; PrintLineAt                                                   ;
;                                                               ;
;   Use PrintLine to print a line of text, except that the      ;
;   first 2 bytes store the x,y coordinates of where to print   ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created        20th May 2006                                ;
;   Last Changed   20th May 2006                                ;
;                                                               ;
;---------------------------------------------------------------;
PrintLineAt:    ld c, (hl)              ; get x pixel position
                inc hl                  ; move to y value
                ld b, (hl)              ; get y pixel position
                inc hl                  ; move to string data
                push hl                 ; save string data
                call Pix                ; get screen addr for x, y into hl
                ex de, hl               ; put screen addr in de
                pop hl                  ; get string data
                call PrintLine          ; display it
                ret

;---------------------------------------------------------------;
; AddCharColour                                                 ;
;                                                               ;
;   Applies a colour to a character cell                        ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         4st May 2006                                ;
;   Last Changed    4st May 2006                                ;
;                                                               ;
;   Inputs                                                      ;
;        a = attribute colour                                   ;
;       de = the screen address of where the character was      ;
;            printed                                            ;
;                                                               ;
;   Outputs                                                     ;
;       sets the character cell attribute                       ;
;                                                               ;
;   Regs Used                                                   ;
;       af, b, de, hl                                           ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, b, de, hl                                           ;
;---------------------------------------------------------------;

AddCharColour:  ld b, a
                ld l, e
                ld a, d
                or $07
                xor $85
                rrca
                rrca
                rrca
                ld h, a
                ld a, b
                ld (hl), a
                ret
                
;---------------------------------------------------------------;
; Print8x8Char                                                  ;
;                                                               ;
;   Prints an 8 x 8 character at a given screen address         ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         4st May 2006                                ;
;   Last Changed    4st May 2006                                ;
;                                                               ;
;   Inputs                                                      ;
;       hl = the start address of the required character data   ;
;       de = the screen address of where the character should   ;
;            be printed                                         ;
;                                                               ;
;   Outputs                                                     ;
;       draws a single character                                ;
;                                                               ;
;   Regs Used                                                   ;
;       af, b, de, hl                                           ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, b, de, hl                                           ;
;---------------------------------------------------------------;

Print8x8Char:   ld b, 8
PrtCharLoop:    ld a, (hl)
                ld (de), a
                inc d                   ; NB: IncY could be used here is printing across boundaries is required.
                inc hl                  ;     If using IncY, HL and DE should be swapped.
                djnz PrtCharLoop
                ret

;---------------------------------------------------------------;
; Print8x16Char                                                 ;
;                                                               ;
;   Prints an 8 x 16 character at a given screen address        ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         17t May 2006                                ;
;   Last Changed    17t May 2006                                ;
;                                                               ;
;   Inputs                                                      ;
;       hl = the start address of the required character data   ;
;       de = the screen address of where the character should   ;
;            be printed                                         ;
;                                                               ;
;   Outputs                                                     ;
;       draws a single character 1 byte wide by 16 high         ;
;                                                               ;
;   Regs Used                                                   ;
;       af, b, de, hl                                           ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, b, de, hl                                           ;
;---------------------------------------------------------------;

Print8x16Char:  ld b, 16
PrtLargeCharLp: ld a, (hl)
                ld (de), a
                inc hl
                inc d
                ld a, d
                and 7
                jp nz, PrtLrgChrLpEnd
                ld a, e
                add a, 32
                ld e, a
                jp c, PrtLrgChrLpEnd
                ld a, d
                sub 8
                ld d, a
PrtLrgChrLpEnd: djnz PrtLargeCharLp
                ret
                
;---------------------------------------------------------------;
; GetHiscoreName                                                ;
;                                                               ;
;   Allows the user to type in there name when they get a       ;
;   new High Score                                              ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         17th May 2006                               ;
;   Last Changed    17th May 2006                               ;
;   Last Changed    21st May 2006 - Tony Thompson               ;
;                   Added this header                           ;
;                   Added a Window to enter the name into       ;
;                   Added some more comments                    ;
;                   Fixed some non 256 byte aligned increments  ;
;                                                               ;
;   Inputs                                                      ;
;       hl = the start address of the required character data   ;
;       de = the screen address of where the character should   ;
;            be printed                                         ;
;                                                               ;
;   Outputs                                                     ;
;       draws a single character 1 byte wide by 16 high         ;
;                                                               ;
;   Regs Used                                                   ;
;       af, b, de, hl                                           ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, b, de, hl                                           ;
;---------------------------------------------------------------;

GetHiscoreName: push de                 ; save where the name is to be inserted
                ld b, 80                ; lets draw a window for editing in
                ld c, 80                ; x,y = 80, 80
                ld d, 5                 ; h = 5
                ld e, 20                ; w = 20
                call WindowOpen         ; open the window
                ld hl, Text_HSName_1    ; 1st line of text
                call PrintLineAt        ; draw it
                ld hl, Text_HSName_2    ; 2nd line of text
                call PrintLineAt        ; draw it
                ld hl, Text_HSName_3    ; 3rd row of text
                call PrintLineAt        ; draw it
                xor a                   ; clear a
                ld (HS_CursorPos), a    ; reset cursor position
                ld hl, NewName          ; clear name buffer
                ld de, NewName+1        ;
                ld bc, 9                ; 10 chars
                ld (hl), 32             ; place spaces
                ldir                    ; reset it all
                call GetTheName         ; get the players name
                ld hl, NewName          ; put player name into hl
                pop de                  ; get the location where to copy to
                ld bc, 11               ; copy all the name + $ff
                ldir                    ; do the copy
                call WindowClose        ; close the editing window
                ret

HS_CursorPos    defb 0                  ; the position of the name edit cursor

GetTheName:     call ShowName           ; draw the player name being edited

KeyReadLoop:    call GetKey             ; get a key
                jp nc, KeyReadLoop      ; keep reading until a key is pressed
                cp 250                  ; is it enter?
                ret z                   ; yes, finished
                cp 254                  ; is the delete key?
                jp z, ChkAndDel         ; then delete the current character
                cp 95                   ; No printable characters above 95
                jp c, ChkAndAdd         ; < 95 then add the character

ChkIfKeyUp:     xor a                   ; wait for key up
                in a, (254)             ; read key
                cpl                     ; invert result
                and 31                  ; and masked out top bits - lower 5 bits available
                jr nz, ChkIfKeyUp       ; if not zero then keep reading until it is
                jr KeyReadLoop          ; key is up, now read next key

ChkAndDel:      ld a, (HS_CursorPos)
                and a
                jp z, ChkIfKeyUp
                dec a
                ld (HS_CursorPos), a
                ld hl, NewName
                ld e, a
                ld d, 0
                add hl, de
                ld (hl), 32
                call ShowName
                jp ChkIfKeyUp

ChkAndAdd:      add a, 32               ; return key code to ascii code
                ld b, a
                ld a, (HS_CursorPos)
                cp 10
                jp z, ChkIfKeyUp
                inc a
                ld (HS_CursorPos), a
                ld hl, NewName
                ld e, a
                ld d, 0
                add hl, de
                dec hl
                ld (hl), b
                call ShowName
                jp ChkIfKeyUp

ShowName:       ld b, 112
                ld c, 146
                call Pix
                push hl
                ex de, hl
                ld hl, NewName-1
                call PrintLine
                pop hl
                ld a, (HS_CursorPos)
                cp 10
                ret z
                call Attr
                ld a, (HS_CursorPos)
                ld c, a
                ld b, 0
                add hl, bc
                ld (hl), 45             ; set the cursor colour
                ret

;---------------------------------------------------------------;
; GetKey                                                        ;
;                                                               ;
;   Scans the keyboard and returns the key code only if a       ;
;   single key is pressed (with the exception of Caps and       ;
;   Symbol shift keys)                                          ;
;                                                               ;
;   Original code by Alcoholics Anonymous                       ;
;   Modified by Ian Munro                                       ;
;   Created         12th May 2006                               ;
;   Last Changed    12th May 2006                               ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
;                                                               ;
;   Outputs                                                     ;
;       when carry is set, 'a' will hold the key code           ;
;                                                               ;
;   Regs Used                                                   ;
;       af, af', bc, de, hl                                     ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, af', bc, de, hl                                     ;
;---------------------------------------------------------------;

GetKey:         ld bc, $fefe            ; get ready to scan all rows on keyboard
                ld d, $fe               ; d = max 1 keypress
                xor a                   ; a = current key index
                ld h, a                 ; index of last keypress

ScanLoop:       in e, (c)               ; read status of key row
                ld l, 5                 ; 5 keys in row

KeyRowLoop:     rrc e                   ; is this key pressed?
                jp c, NoPress
                or a
                jp z, NoPress           ; ignore CAPS
                cp 36
                jp z, NoPress           ; ignore SYM SHIFT
                inc d                   ; another key pressed
                jp z, ExitNoKeySet      ; exit if more than one
                ld h, a                 ; remember which key

NoPress:        inc a                   ; on to the next key index
                dec l
                jp nz, KeyRowLoop

NextScanRow:    rlc b                   ; on to the next key row
                jp c, ScanLoop

                inc d                   ; check if a single key was pressed
                jp nz, ExitNoKeySet

                ld e, h
                ld d, 0                 ; de = index of key pressed
                ld hl, KeyTransTables
                add hl, de

                ld a, $fe               ; check on CAPS key
                in a, ($fe)
                and 1
                jp nz, NoCaps
                ld e, 40
                add hl, de

NoCaps:         ld a, $7f               ; check on SYM SHIFT
                in a, ($fe)
                and 2
                jp nz, NoSym
                ld e, 80
                add hl, de

NoSym:          ld a, (hl)              ; a = key code from translation table
                scf                     ; indicate key was registered
                ret

ExitNoKeySet:   xor a
                ret

;---------------------------------------------------------------;
; IncrementScore                                                ;
;                                                               ;
;   Increments the score by a user defined value                ;
;                                                               ;
;   Written by Ian Munro                                        ;
;   Created         17th May 2006                               ;
;   Last Changed    17th May 2006                               ;
;                                                               ;
;   Inputs                                                      ;
;       a = the amount to increase the score by                 ;
;           1 = '10' 2 = '20' 20 = '200' etc                    ;
;                                                               ;
;   Outputs                                                     ;
;       the score will be incremented                           ;
;                                                               ;
;   Regs Used                                                   ;
;       af, b, hl                                               ;
;                                                               ;
;   Regs destroyed                                              ;
;       af, b, hl                                               ;
;---------------------------------------------------------------;

IncrementScore:                         ; NB: 'a' must be set by caller
                ld hl, ScoreData5       ; the 'tens' column
AddNumbersLoop: ld b, 0
                add a, (hl)
                ld (hl), a
                cp 10
                ret c
DoDecTen:       inc b
                sub 10
                cp 10
                jp nc, DoDecTen
                ld (hl), a
                dec hl
                ld a, b
                jp AddNumbersLoop

PrintScore:     ld b, 56
                ld c, 8
                call Pix
                ex de, hl
                ld c, 6
                ld hl, ScoreData1
PrtScoreMainLp: push hl
                push de
                ld d, 0
                ld a, (hl)
                add a, a
                add a, a
                add a, a
                add a, a
                ld e, a
                ld hl, Number0
                add hl, de
                pop de
                push de
                call Print8x16Char
                pop de
                pop hl
                inc e
                inc hl
                dec c
                jp nz, PrtScoreMainLp
                ret

;---------------------------------------------------------------;
; Set the score back to zero                                    ;
;---------------------------------------------------------------;

ResetScore:     ld hl, ScoreData1
                ld de, ScoreData2
                ld bc, 5
                ld (hl), 0
                ldir
                ret
                
;---------------------------------------------------------------;
; Move the 'live' score to the temp high score location         ;
; Call this once the game has ended and before calling the high ;
; score functions                                               ;
;---------------------------------------------------------------;

TransferScore:  ld b, 6
                ld hl, ScoreData1
                ld de, NewScore
TransScoreLoop: ld a, (hl)
                add a, 48               ; add 48 to the score value so that it points
                ld (de), a              ; to the correct font character
                inc hl
                inc de
                djnz TransScoreLoop
                ret
                

PrintLevel:     ld b, 120
                ld c, 24
                call Pix
                ex de, hl
                ld bc, 0
                ld a, (Level)
                inc a
PL_Lp:          cp 10
                jr c, PL_Cont
                sub 10
                inc b
                jr PL_Lp
PL_Cont:        push de
                ld c, a
                ld a, b
                add a, a
                add a, a
                add a, a
                add a, a
                ld d, 0
                ld e, a
                ld hl, Number0
                add hl, de
                pop de
                push de
                push bc
                call Print8x16Char
                pop bc
                ld d, 0
                ld a, c
                add a, a
                add a, a
                add a, a
                add a, a
                ld e, a
                ld hl, Number0
                add hl, de
                pop de
                inc de
                call Print8x16Char
                ret
