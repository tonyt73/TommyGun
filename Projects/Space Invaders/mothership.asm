;---------------------------------------------------------------;
;                                                               ;
;  MOTHERSHIP.ASM                                               ;
;                                                               ;
;  This file contains functions to control the mothership       ;
;                                                               ;
;---------------------------------------------------------------;

MOTHERSHIP_Y        equ    28                   ; y position of the mothership
MOTHERSHIP_SPEED    equ     1                   ; the wait between mothership movement
SCORE_SPEED         equ    50                   ; the wait for score being displayed
MOTHERSHIP_STEP     equ     1                   ; the step between frames           
MOTHER_CHOOSE_TIME  equ     1                   ; state: choose next time
MOTHER_COUNTDOWN    equ     2                   ; state: count down to move
MOTHER_MOVE_SHIP    equ     3                   ; state: move ship across the screen
MOTHER_DESTROYED    equ     4                   ; state: ship destoryed


MotherState:        defw    MOTHER_CHOOSE_TIME
MotherCountDown:    defw    0                   ; countdown to when the mothership will appear
MotherX:            defb    0                   ; the position of mothership
MotherWait:         defw    0                   ; the wait(frames) between moving the ship

;---------------------------------------------------------------;
; MothershipFSM                                                 ;
;                                                               ;
; This is a finite state machine for running the mothership     ;
; Normal state transitions are:                                 ;
;    CHOOSE TIME=>COUNT DOWN=>MOVE SHIP=>(SHIP DESTROYED)=>+    ;
;    ^--------------------- back to start -----------------+    ;
;                                                               ;
; The player routines call KillMothership when a bullet         ;
; collision is detected with the mothership; this changes state ;
; to SHIP DESTROYED                                             ;
;                                                               ;
; Sure a vector jump table might be 'slightly' faster. But we   ;
; aren't too concern for speed here. What we need is easy state ;
; management and detection; as it is used elsewhere.            ;
; This is clean and simple.                                     ;
;---------------------------------------------------------------;
MothershipFSM:      ld a, (MotherState)         ; get the current finite state machine (FSM) state
                    cp MOTHER_COUNTDOWN         ; counting down to launch?
                    jr z, MotherCountdown       ; yes, goto countdown state
                    cp MOTHER_MOVE_SHIP         ; moving the mothership? 
                    jr z, MotherMoveShip        ; yes, goto move mothership state
                    cp MOTHER_DESTROYED         ; destorying the mothership?
                    jr z, MotherDestroyed       ; yes, move to destorying state
                                  
;---------------------------------------------------------------;
; MOTHER_CHOOSE_TIME state                                      ;
; This is the default state.                                    ;
; Choose a time when the mothersip will appear, once it matches ;
; or is less than the ISRCounter value.                         ;
; Exit state is always MOTHER_COUNTDOWN                         ;
;---------------------------------------------------------------;
MotherChooseTime:   call FastRNG                ; choose a RND number
                    ld c, a                     ; c = rnd number
                    call FastRNG                ; get another one
                    and 0x07                    ; reduce the number between to < 7
                    ld b, a                     ; b = 0 to 6
                    ld hl, (ISRCounter)         ; get the interrupt counter
                    add hl, bc                  ; add the rng 16 bit number
                    ld bc, 200
                    add hl, bc                  ; add 4 seconds as a minimum
                    ld (MotherCountDown), hl    ; store it
                    ld a, MOTHER_COUNTDOWN      ; change to countdown state
                    jr MoveToState

;---------------------------------------------------------------;
; MOTHER_COUNTDOWN state                                        ;
; Counts down the time until the mothership will appear.        ;
; Exit state is always MOTHER_MOVE_SHIP                         ;
;---------------------------------------------------------------;
MotherCountdown:    ld hl, (MotherCountDown)    ; get the countdown target
                    ld de, (ISRCounter)         ; get the interrupt counter
                    sbc hl, de                  ; have we gone over the value
                    ret nc                      ; no, then exit
                    ld hl, (ISRCounter)         ; get the interrupt counter 
                    ld de, MOTHERSHIP_SPEED     ; get the movement speed
                    add hl, de                  ; adjust new target
                    ld (MotherWait), hl         ; save the target value
                    xor a                       ; zero a
                    ld (MotherX), a             ; set mother x to 0
                    call DrawMother             ; draw the ship
                    ld a, MOTHER_MOVE_SHIP      ; change to moving the ship state
                    jr MoveToState

;---------------------------------------------------------------;
; MOTHER_MOVE_SHIP state                                        ;
; Moves the ship across the screen.                             ;
; Exit state is can be MOTHER_CHOOSE_TIME                       ;
; Player calls KillMothership changes state to MOTHER_DESTROYED ;
;---------------------------------------------------------------;
MotherMoveShip:     ld hl, (MotherWait)         ; get the movement speed target value
                    ld de, (ISRCounter)         ; get the interrupt counter
                    sbc hl, de                  ; is wait value > ISR counter?
                    ret nc                      ; no, then exit
                    ld hl, (ISRCounter)         ; yes, get the interrupt counter 
                    ld de, MOTHERSHIP_SPEED     ; get new speed
                    add hl, de                  ; adjust
                    ld (MotherWait), hl         ; save new target
                    ld a, (MotherX)             ; get the ship x position
                    push af                     ; save it
                    call EraseMother            ; erase the mothership from the old positon
                    pop af                      ; restore ship x position in a
                    add a, MOTHERSHIP_STEP      ; move the ship
                    ld (MotherX), a             ; save the new position
                    push af                     ; save it
                    call DrawMother             ; draw the mothership in the new position
                    pop af                      ; restore the ship position
                    cp 240                      ; it is at the end of the screen?
                    ret c                       ; no, then exit
                    ld a, (MotherX)             ; yes, then
                    call EraseMother            ; erase the mothership
                    ld a, MOTHER_CHOOSE_TIME    ; change to choose time state
                    jr MoveToState

;---------------------------------------------------------------;
; MoveToState                                                   ;
; Moves to a new state in the finite state machine              ;
;---------------------------------------------------------------;
MoveToState:        ld (MotherState), a         ; change the FSM state and exit
                    ret

;---------------------------------------------------------------;
; MOTHER_DESTROYED state                                        ;
; Wait for the score display to finish, then erases the score   ;
; and resets the mothership and restarts the FSM.               ;
; Exit state is always MOTHER_CHOOSE_TIME                       ;
;---------------------------------------------------------------;
MotherDestroyed:    ld hl, (MotherWait)         ; get score target value
                    ld de, (ISRCounter)         ; get the interrupt counter
                    sbc hl, de                  ; have we gone over the value
                    ret nc                      ; no, then exit
                    ld a, (MotherX)             ; yes, get ship x position
                    call EraseMother            ; erase the score
                    call ResetMothership        ; reset the ship
                    ld a, MOTHER_CHOOSE_TIME    ; change to choose time state
                    jr MoveToState

;---------------------------------------------------------------;
; ResetMothership                                               ;
; Resets the mothership position and state machine              ;
;---------------------------------------------------------------;
ResetMothership:    ld a, (MotherState)         ; get FSM state
                    cp MOTHER_MOVE_SHIP         ; are we in move ship state?
                    jr nz, RM1                  ; no, then skip to reset
                    ld a, (MotherX)             ; yes, get ship x position
                    call EraseMother            ; erase the ship
                    xor a                       ; a = 0
                    ld (MotherX), a             ; reset ship x position
RM1:                ld a, MOTHER_CHOOSE_TIME    ; jump back to choosing a time state
                    jr MoveToState                        

;---------------------------------------------------------------;
; KillMothership                                                ;
; Erases the mothership, shows the score for the hit.           ;
;                                                               ;
; Inputs                                                        ;
;   a - score                                                   ;
;       0 = 20                                                  ;
;       1 = 50                                                  ;
;       2 = 100                                                 ;
;                                                               ;
;---------------------------------------------------------------;
KillMothership:     ld b, a                     ; b = score to display
                    ld a, (MotherState)         ; get FSM state         
                    cp MOTHER_MOVE_SHIP         ; are we in move ship state?
                    ret nz                      ; no, then exit
                    ld a, b                     ; a = score                 
                    and a                       ; is it zero?
                    jr z, KMS20                 ; yes, then show 20
                    dec a                       ; is it 1?
                    jr z, KMS50                 ; yes, then show 50
                    ld hl, MS100                ; no, show 100
                    jr KMS1
KMS20:              ld hl, MS20                    
                    jr KMS1
KMS50:              ld hl, MS50                    
KMS1:               push hl                     ; save the score gfx data
                    ld a, (PlayerBulletY)       ; get the Bullet y position
                    call ErasePBullet           ; erase the bullet
                    ld a, (MotherX)             ; get ship x position
                    call EraseMother            ; erase the ship
                    pop hl                      ; restore the score gfx data
                    ld a, (MotherX)             ; get ship x position
                    ld c, a                     ; c = x position
                    ld b, MOTHERSHIP_Y          ; b = y position
                    call DrwSpr16               ; draw the score
                    ld hl, (ISRCounter)         ; get the interrupt counter 
                    ld de, SCORE_SPEED          ; get the time the score stays on the screen
                    add hl, de                  ; adjust new target
                    ld (MotherWait), hl         ; save the target value
                    ld a, MOTHER_DESTROYED      ; change destoryed the ship state
                    jr MoveToState         
                
;---------------------------------------------------------------;
; EraseMother                                                   ;
;                                                               ;
; Inputs                                                        ;
;   a - y position                                              ;
;---------------------------------------------------------------;
EraseMother:        ld hl, Mothership           ; point to ship graphic data          
                    ld c, a                     ; c = x position
                    ld b, MOTHERSHIP_Y          ; b = y position
                    call ErzSpr16               ; erase the sprite
                    ret
                                     
;---------------------------------------------------------------;
; DrawMother                                                    ;
;                                                               ;
; Inputs                                                        ;
;   a - y position                                              ;
;---------------------------------------------------------------;
DrawMother:         ld hl, Mothership           ; point to ship graphic data           
                    ld a, (MotherX)
                    ld c, a                     ; c = x position
                    ld b, MOTHERSHIP_Y          ; b = y position
                    call DrwSpr16               ; draw the sprite
                    ret
