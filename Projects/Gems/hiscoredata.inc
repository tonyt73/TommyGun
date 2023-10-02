;---------------------------------------------------------------;
;                                                               ;
;   HiScoreData.inc                                             ;
;                                                               ;
;   This file contains data used by the HiScore.inc file        ;
;                                                               ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; Hi-Score Table                                                ;
; Table holds 10 scores and names.                              ;
; Each entry is stored as follows:                              ;
; Colour = 1 byte                                               ;
; Score = 6 bytes                                               ;
; Space = 1 byte                                                ;
; Names = 10 bytes                                              ;
; EOL char = 1 byte                                             ;
; Total is 19 bytes per score element                           ;
;---------------------------------------------------------------;

ScoreTable      defb $47 + 8                            ; colour
                defm "010000 KIWI......"                ; score and name
                defb $ff                                ; end of line
                
scoretablepos1  defb $7 + 8
                defm "009000 RETROCODER"
                defb $ff
                
scoretablepos2  defb $47 + 8
                defm "008000 LEE_DC...."
                defb $ff
                
scoretablepos3  defb $7 + 8
                defm "007000 SADAKO...."
                defb $ff
                
scoretablepos4  defb $47 + 8
                defm "006000 JOHN......"
                defb $ff
                
scoretablepos5  defb $7 + 8
                defm "005000 MARY......"
                defb $ff
                
scoretablepos6  defb $47 + 8
                defm "004000 PETER....."
                defb $ff
                
scoretablepos7  defb $7 + 8
                defm "003000 BOB......."
                defb $ff
                
scoretablepos8  defb $47 + 8
                defm "002000 BARRY....."
                defb $ff
                
scoretablepos9  defb $7 + 8
                defm "001000 HARRY....."
ScoreTableEnd   defb $ff


                defb $43 + 8
NewScore        defm "000000"                       ; temp score store
                defb 32
                defb $47 + 8                           ; font colour as user types in their name
NewName         defm "          "                   ; temp name store
                defb $FF
                defb $FF


Text_HiScore    defb 71 + 8                        ; colour
                defm "HI SCORE TABLE"
                defb $ff                            ; end of line

Text_Space      defb 87 + 8                         ; colour
                defm "   PRESS SPACE   "
                defb $ff                            ; end of line
                
Text_HSName_1   defb 96, 88
                defb 71 + 8
                defm "CONGRADULATIONS!"
                defb $ff
Text_HSName_2   defb 88, 96
                defb 71 + 8
                defm "YOU GOT A HI-SCORE"
                defb $ff
Text_HSName_3   defb 88, 112
                defb 71 + 8
                defm "NAME  [          ]"
                defb $ff


;---------------------------------------------------------------;
; Look up table to convert key presses                          ;
;---------------------------------------------------------------;

                ; normal key press table
                
KeyTransTables  defb 253,90,88,67,86     ; CAPS SHIFT z x c v
                defb 65,83,68,70,71      ; a s d f g
                defb 81,87,69,82,84      ; q w e r t
                defb 17,18,19,20,21      ; 1 2 3 4 5
                defb 16,25,24,23,22      ; 0 9 8 7 6
                defb 80,79,73,85,89      ; p o i u y
                defb 250,76,75,74,72     ; ENTER l k j h
                defb 0,252,77,78,66      ; SPACE SYM SHIFT m n b

                ; key press with CAPS SHIFT
                
                defb 253,58,56,35,54     ; CAPS SHIFT Z X C V
                defb 33,51,36,38,39      ; A S D F G
                defb 49,55,37,50,52      ; Q W E R T
                defb 17,18,19,20,21      ; 1 2 3 4 5
                defb 254,25,24,23,22     ; 0 9 8 7 6
                defb 48,47,41,53,57      ; P O I U Y
                defb 250,44,43,42,40     ; ENTER L K J H
                defb 0,252,45,46,34      ; SPACE SYM SHIFT M N B

                ; key press with SYMBOL SHIFT

                defb 253,26,64,31,15     ; CAPS SHIFT : £ ? /
                defb 251,251,251,251,251 ;
                defb 251,251,251,28,30   ;       < >
                defb 1,32,3,4,5          ; ! @ # $ %
                defb 63,9,8,7,6          ; _ ) ( ' &
                defb 2,27,251,251,251    ; " ;
                defb 250,29,11,13,62     ; ENTER = + - ^
                defb 0,252,14,12,10      ; SPACE SYM SHIFT . , *

                ; key press with CAPS SHIFT and SYMBOL SHIFT

                defb 253,251,251,251,251 ; CAPS SHIFT
                defb 94,92,60,91,93      ; ~ | \ { }
                defb 251,251,251,251,251 ;
                defb 251,251,251,251,251 ;
                defb 251,251,251,251,251 ;
                defb 95,251,251,61,59    ; ©     ] [
                defb 250,251,251,251,251 ; ENTER
                defb 0,252,251,251,251   ; SPACE SYM SHIFT

;---------------------------------------------------------------;
; This is where the current 'live' score is held                ;
;---------------------------------------------------------------;

ScoreData1      defb 0
ScoreData2      defb 0
ScoreData3      defb 0
ScoreData4      defb 0
ScoreData5      defb 0
ScoreData6      defb 0
