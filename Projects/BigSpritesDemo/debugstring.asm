;-----------------------------------------------------------------------------;
;                                                                             ;
;  DEBUG STRING OUTPUT MACROS                                                 ;
;  Programmed by Tony Thompson                                                ;
;  2 July 2017                                                                ;
;  Used by the TommyGun IDE application                                       ;
;                                                                             ;
;  These macros are used the TommyGun code editor and emulator to output      ;
;  debug information from a Spectrum game.                                    ;
;                                                                             ;
;  WARNING: These should NOT be used in a normal emulator!                    ;
;           It will probably just crash anyway.                               ;
;           Only compatible with TommyGun's internal debugger/emulator!       ;
;                                                                             ;
;  To Disable the macros use:                                                 ;
;    TOMMYGUN EQU 0                                                           ;
;  If assembler supports a command line define parameter (as Pasmo does)      ;
;    Pasmo --equ TOMMYGUN=0 ...                                               ;
;                                                                             ;
;-----------------------------------------------------------------------------;


;-----------------------------------------------------------------------------;
; DBG_SOURCE                                                                  ;
; Display the current file and line number in the editor output window        ;
;-----------------------------------------------------------------------------;
MACRO DBG_SOURCE
IF TOMMYGUN
push af
xor a
rst 0
pop af
ENDM

;-----------------------------------------------------------------------------;
; DBG_VAR_8                                                                   ;
; symbol: The symbol value to display                                         ;
; Display the 1 byte (8) bit value of a variable in the output window         ;
;-----------------------------------------------------------------------------;
MACRO DBG_VAR_8, symbol
IF TOMMYGUN
push af
push hl
ld a, 1
ld hl, symbol
rst 0
pop hl
pop af
ENDM

;-----------------------------------------------------------------------------;
; DBG_VAR_16                                                                  ;
; symbol: The symbol value to display                                         ;
; Display the 2 byte (16) bit value of a variable in the output window        ;
;-----------------------------------------------------------------------------;
MACRO DBG_VAR_16, symbol
IF TOMMYGUN
push af
push hl
ld a, 2
ld hl, symbol
rst 0
pop hl
pop af
ENDM

;-----------------------------------------------------------------------------;
; DBG_DUMP                                                                    ;
; location: The memory location to start dump from                            ;
; length  : The number of bytes to dump                                       ;
; columns : The number of columns to display the data in (default: 8)         ;
; Display the 2 byte (16) bit value of a variable in the output window        ;
;-----------------------------------------------------------------------------;
MACRO DBG_DUMP, location, length, columns
IF TOMMYGUN
push af
push bc
push de
push hl
ld hl, location
ld bc, length
IF NUL(columns)
ld de, 8
ELSE
ld de, columns
ENDIF
ld a, 3
rst 0
pop hl
pop de
pop bc
pop af
ENDM

;-----------------------------------------------------------------------------;
; DBG_MSG                                                                     ;
; message: The number of the user defined message.                            ;
; Outputs a user defined message (127) from within TommyGun's string editor.  ;
;                                                                             ;
; {symbol} displays the value of a symbol                                     ;
; [symbol] displays the location of a symbol                                  ;
;                                                                             ;
; From the String editor define messages as:                                  ;
; String Name : DBG_MSG_0, DBG_MSG_1, ..., DBG_MSG_126                        ;
; String Value: "Number of Lives is {lives} and is stored at [lives]"         ;
;                                                                             ;
; DO NOT EXPORT THESE INTO THE GAME CODE. THE CODE EDITOR WILL PICK THEM UP   ;
; FROM WITHIN THE TOMMYGUN PLUGIN ENVIRONMENT. THIS SAVES YOU VALUABLE MEMORY ;
;                                                                             ;
;-----------------------------------------------------------------------------;
MACRO DBG_MSG, message
IF TOMMYGUN
push af
ld a, 128 + message
rst 0
pop af
ENDM
