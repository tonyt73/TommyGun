;---------------------------------------------------------------;
;                                                               ;
;  INPUT.ASM                                                    ;
;                                                               ;
;  This file includes several useful keyboard input functions   ;
;                                                               ;
;---------------------------------------------------------------;

;
;   KEYBOARD and JOYSTICK PORTS
;
SpaceToB            equ 32766       ; $7FFE
EnterToH            equ 49150       ; $BFFE   
PToSeven            equ 57342       ; $DFFE
ZeroToSix           equ 61438       ; $EFFE
OneToFive           equ 63486       ; $7FFE
QToT                equ 64510       ; $FBFE
AToG                equ 65022       ; $FDFE
CapsToV             equ 65278       ; $FEFE
InterfaceII_P1      equ OneToFive   ; $7FFE 
InterfaceII_P2      equ ZeroToSix   ; $EFFE
CursorKeys          equ ZeroToSix   ; $EFFE
KempstonJoystick    equ 31          ; $001F

;
; KEY BITS
;
KEY_D0              equ $01
KEY_D1              equ $02
KEY_D2              equ $04
KEY_D3              equ $08
KEY_D4              equ $10
KEY_MASK            equ $1F

;
; KEMPSTON BITS
;
KEMPSTON_RIGHT      equ $01 
KEMPSTON_LEFT       equ $02 
KEMPSTON_DOWN       equ $04
KEMPSTON_UP         equ $08 
KEMPSTON_BUTTON1    equ $10 
KEMPSTON_MASK       equ $1F

;
; KEMPTSON FLAGS
;
KEMPSTON_NOT_FOUND  equ $00
KEMPSTON_AVAILABLE  equ $01 

;
; ACTION KEY BITS
;
ACTION_NONE         equ $00
ACTION_LEFT         equ $01
ACTION_RIGHT        equ $02   
ACTION_UP           equ $04
ACTION_DOWN         equ $08
ACTION_FIRE         equ $10

;
;   INPUT TYPE
;
KEYBOARD            equ  $00
CURSOR_KEYS         equ  $01
INTERFACE_II_P1     equ  $02
INTERFACE_II_P2     equ  $03
KEMPSTON            equ  $04
InputType           defw CursorKeys_Interface_II_2

;
;   INPUT PORTS TABLE
;       Left port, bit mask, toggle bit mask, active bit, action bit
;       Right port, bit mask, toggle bit mask, active bit, action bit
;       Fire port, bit mask, toggle bit mask, active bit, action bit
;       0 end of keys entry
InputsTable:        defw KeyBoard, CursorKeys_Interface_II_2, InterfaceII_1, CursorKeys_Interface_II_2, Kempston
KeyBoard:           ;   KEYBOARD
                    ;   Left (Z)
                    defw CapsToV
                    defb KEY_MASK, KEY_D1, ACTION_LEFT
                    ;   Right (X)
                    defw CapsToV
                    defb KEY_MASK, KEY_D2, ACTION_RIGHT
                    ;   Fire (Space)
                    defw SpaceToB 
                    defb KEY_MASK, KEY_D0, ACTION_FIRE
                    defw 0

CursorKeys_Interface_II_2:  ; CURSOR KEYS and INTERFACE II Port 2
                    ;   Left (5)
                    defw OneToFive
                    defb KEY_MASK, KEY_D4, ACTION_LEFT
                    ;   Right (X)
                    defw ZeroToSix
                    defb KEY_MASK, KEY_D2, ACTION_RIGHT
                    ; INTERFACE II - Port 2 (right)
                    ;   Left (1)
                    defw ZeroToSix
                    defb KEY_MASK, KEY_D4, ACTION_LEFT
                    ;   Right (2)
                    defw ZeroToSix
                    defb KEY_MASK, KEY_D3, ACTION_RIGHT
                    ;   Fire (0)
                    defw ZeroToSix 
                    defb KEY_MASK, KEY_D0, ACTION_FIRE
                    defw 0

InterfaceII_1:      ;   Left (1)
                    defw OneToFive
                    defb KEY_MASK, KEY_D0, ACTION_LEFT
                    ;   Right (2)
                    defw OneToFive
                    defb KEY_MASK, KEY_D1, ACTION_RIGHT
                    ;   Fire (5)
                    defw OneToFive 
                    defb KEY_MASK, KEY_D4, ACTION_FIRE
                    defw 0

Kempston:           ;   Left (1)
                    defw KempstonJoystick
                    defb 0, KEMPSTON_LEFT, ACTION_LEFT
                    ;   Right (2)
                    defw KempstonJoystick
                    defb 0, KEMPSTON_RIGHT, ACTION_RIGHT
                    ;   Fire (5)
                    defw KempstonJoystick 
                    defb 0, KEMPSTON_BUTTON1, ACTION_FIRE
                    defw 0


;---------------------------------------------------------------;
; ReadKeys                                                      ;
;                                                               ;
;   Reads the control keys and set the A register with the      ;
;   actions for each key pressed                                ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         6th September 2015                          ;
;   Last Changed    6th September 2015                          ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
;                                                               ;
;   Outputs                                                     ;
;       a - the game keys currently pressed                     ;
;   bit 0 - LEFT pressed                                        ;
;   bit 1 - RIGHT pressed                                       ;
;   bit 4 - FIRE pressed                                        ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc                                                 ;
;                                                               ;
;   Regs destoryed                                              ;
;       af, bc, hl, ix                                          ;
;---------------------------------------------------------------;
ReadKeys:       ld l, 0                 ; reset actions
                ld ix, (InputType)      ; get the current input definition
RKL1:           ld c, (ix+0)            ; get the lower port byte
                ld b, (ix+1)            ; get the high port byte 
                ld a, c                 ; c = port
                or b                    ; is the port zero?
                jr z, RK_F              ; yes, finished reading keys
                in a, (c)               ; read the joystick/keys
                and (ix+3)              ; mask out only the key bit we need
                xor (ix+2)              ; invert it so as no keys pressed is 0
                and (ix+3)              ; test if its set
                jr z, RK_N1             ; no, then read next key bit
                ld a, l                 ; get actions
                or (ix+4)               ; yes, so set the action
                ld l ,a                 ; save new actions
RK_N1:          ld bc, 5                ; offset to next key entry
                add ix, bc              ; move to next key to read
                jr RKL1                 ; read all the keys
RK_F:           ld a, l                 ; get actions
                ret                     


;---------------------------------------------------------------;
; DetectInput                                                   ;
;                                                               ;
; Detects the desire controller to be used by the player.       ;
;                                                               ;
;   fire buttons used                                           ;
;    Space         - Keyboard                                   ;
;                       Z left                                  ;
;                       X right                                 ;
;    5             - Interface II port 1                        ;
;                       1 left                                  ;
;                       2 right                                 ;
;    0             - Cursor keys or Interface II port 2         ;
;                    Cursor keys                                ; 
;                       5 left                                  ;
;                       8 right                                 ;
;                    Interface II port 2                        ;
;                       6 left                                  ;
;                       7 right                                 ;
;    Kempston fire - Kempston joystick                          ;
;                                                               ;
;---------------------------------------------------------------;
DetectInput:    ld bc, SpaceToB         ; is space pressed?
                ld e, KEYBOARD          ; set keyboard as detected
                in a, (c)               ; read the keys 
                and KEY_D0              ; mask space key bit
                jr z, SIT_Store         ; yes, use keyboard
                ld bc, InterfaceII_P1   ; is interface II port 1 fire pressed?
                ld e, INTERFACE_II_P1   ; set interface II port 1 as detected
                in a, (c)               ; read the joystick port
                and KEY_D4              ; is fire pressed
                jr z, SIT_Store         ; yes, use interface II
                ld bc, CursorKeys       ; set cursor keys/interface II port 2 as detected
                ld e, CURSOR_KEYS       ; read fire button port
                in a, (c)               ; read the joystick port
                and KEY_D0              ; is fire pressed
                jr z, SIT_Store         ; yes, use cursor keys/interface II port 2
                ld a, (KempstonFlags)   ; get the kempston flags
                and KEMPSTON_AVAILABLE  ; is the joystick available?
                jr z, SIT_NoFire        ; no, then no fire pressed                
                ld bc, KempstonJoystick ; is kempston fire pressed?
                ld e, KEMPSTON          ; set kempston as detected
                in a, (c)               ; read the port
                and KEMPSTON_BUTTON1    ; is fire pressed 
                jr nz, SIT_Store        ; yes, use Kempston joystick        
                
SIT_NoFire:     and a                   ; no fire button pressed
                ret                     ; done
SIT_Store:      sla e                   ; get detected input * 2
                ld d, 0                 ; de = offset into InputsTable                 
                ld ix, InputsTable      ; ix = Inputs table
                add ix, de              ; index into table
                ld d, (ix+1)            ; de = input entry
                ld e, (ix+0)                
                ld (InputType), de      ; set the input type entry to use
                scf                     ; fire pressed
                ret

;---------------------------------------------------------------;
; DetectKempston                                                ;
;                                                               ;
;   Checks if a kempston joystick is attached                   ;
;---------------------------------------------------------------;
KempstonFlags:  defb 0                
DetectKempston: halt
                ld c, KEMPSTON_NOT_FOUND
                in a, (KempstonJoystick)
                ld b, a
                and 0x03
                cp 0x03                 ; are both left and right on?
                jr z, NoKempston        ; yes, then no joystick found
                ld a, b
                and 0x0C                ; are both up and down on?
                cp 0x0C
                jr z, NoKempston        ; yes, then no joystick found    
                ld c, KEMPSTON_AVAILABLE 
NoKempston:     ld a, c
                ld (KempstonFlags), a
                ret 

;---------------------------------------------------------------;
; IsSpacePressed                                                ;
;                                                               ;
;   Checks if space is pressed                                  ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         12th November 2007                          ;
;   Last Changed    12th November 2007                          ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
;                                                               ;
;   Outputs                                                     ;
;       set carry flag if space key is pressed                  ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc                                                 ;
;                                                               ;
;   Regs destoryed                                              ;
;       af, bc                                                  ;
;---------------------------------------------------------------;
IsSpacePressed: ld bc, SpaceToB         ; get space to b row port
                in a, (c)               ; read the keys
                and KEY_D0              ; mask off unwanted bits
                xor KEY_D0              ; toggle the bits
                rrca                    ; put space bit into carry flag
                ret

;---------------------------------------------------------------;
; WaitForSpace                                                  ;
;                                                               ;
;   Wait for the space key to be pressed and released           ;
;                                                               ;
;   Written by Tony Thompson                                    ;
;   Created         12th November 2007                          ;
;   Last Changed    12th November 2007                          ;
;                                                               ;
;   Inputs                                                      ;
;       none                                                    ;
;                                                               ;
;   Outputs                                                     ;
;       none                                                    ;
;                                                               ;
;   Regs Used                                                   ;
;       af,  bc                                                 ;
;                                                               ;
;   Regs destoryed                                              ;
;       af, bc                                                  ;
;---------------------------------------------------------------;
WaitForSpace:   call IsSpacePressed     ; check for space being pressed
                jr nc, WaitForSpace     ; pressed? no, repeat 
WFS1:           call IsSpacePressed     ; check for space being pressed
                jr c, WFS1              ; pressed? yes, repeat
                ld a, SPACE_SFX
                call playsfx                
                ret                     ; done                
