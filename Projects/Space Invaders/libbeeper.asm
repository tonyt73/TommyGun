; MT Engine MK2
; Copyleft 2014 the Mojon Twins

; Beeper.h
; Original routines by Shiru

;
;	SoundFX Table
;
;	n	sfx
;	----------
;	0	Enemy destroyed
;	1	Enemy hit
;	2	Something
;	3	Jump
;	4	Player hit
;	5	Enemy destroyed 2
;	6	Shot
;	7	Item #1		(item)
;	8	Item #2		(key)
;	9	Item #3		(life)
;	10  Item #4     (???)
                    defb 255
snd_queue:          defb 255
                    defb 255
next_snd:           defw snd_queue 

playsfx:            ld b, a
                    and 128
                    jr nz, PlaySoundNow
                    ; queue sound
                    ld hl, (next_snd)
                    ld a, (hl)
                    cp 255
                    jr nz, PSn1
                    ld (hl), b
                    ret
PSn1:               ld a, l
                    xor 1
                    ld l, a
                    ld (hl), b  
                    ret

PlaySound:          ld hl, (next_snd)
                    ld a, (hl)
                    ld b, a
                    cp 255
                    ld (hl), 255
                    jr nz, PlaySoundNow
                    ld a, l
                    xor 1
                    ld l, a
                    ld (next_snd), hl
                    ld a, (hl)
                    ld b, a
                    cp 255
                    ret z
                    ld (hl), 255
PlaySoundNow:       ld a, b
                    and 127
                    ld l,a
            		ld h,0
            		add hl,hl
            		ld de,proclist
            		add hl,de
            		ld a,(hl)
            		inc hl
            		ld h,(hl)
            		ld l,a
            		ld de,0
            		jp (hl)
	
sound1:	;enemy destroyed
            		ex de,hl
            		ld bc,250
sound1l0:
            		ld a,(hl)
            		and 16
            		out ($FE),a
            		ld e,a
            		inc a
            		sla a
            		sla a
sound1l1:
            		dec a
            		jr nz,sound1l1
            		out ($FE),a
            		ld a,e
            		inc a
            		add a,a
            		add a,a
            		add a,a
sound1l2:
            		dec a
            		jr nz,sound1l2
            		ld a,b
            		inc hl
            		dec bc
            		ld a,b
            		or c
            		jr nz,sound1l0
                    ret
	
sound2:	;enemy hit
            		ex de,hl
            		ld bc,40*256+100
sound2l0:
            		ld a,(hl)
            		and 16
            		out ($FE),a
            		inc hl
            		ld a,c
sound2l1:
            		dec a
            		jr nz,sound2l1
            		out ($FE),a
            		ld a,c
sound2l2:
            		dec a
            		jr nz,sound2l2
            		djnz sound2l0
                    ret
	
sound3:	;something
            		ex de,hl
            		ld b,100
            		ld de,$1020
sound3l0:
            		ld a,(hl)
            		and d
            		out ($FE),a
            		inc hl
            		ld a,e
sound3l0a:
            		dec a
            		jr nz,sound3l0a
            		djnz sound3l0
            		ld b,250
sound3l1:
            		ld a,(hl)
            		and d
            		out ($FE),a
            		inc hl
            		ld a,2
sound3l2:
            		dec a
            		jr nz,sound3l2
            		xor a
            		out ($FE),a
            		ld a,e
sound3l3:
            		dec a
            		jr nz,sound3l3
            		djnz sound3l1
                    ret
	
sound4:	;jump
            		ld bc,20*256+250
sound4l0:
            		ld a,16
            		out ($FE),a
            		ld a,4
sound4l1:
            		dec a
            		jr nz,sound4l1
            		out ($FE),a
            		ld a,c
sound4l2:
            		dec a
            		jr nz,sound4l2
            		dec c
            		dec c
            		djnz sound4l0
                    ret
	
sound5:	;player hit
            		ex de,hl
            		ld bc,100*256+16
sound5l0:
            		ld a,(hl)
            		and c
            		out ($FE),a
            		inc hl
            		ld a,110
            		sub b
            		ld e,a
            		and c
            		out ($FE),a
sound5l1:
            		dec e
            		jr nz,sound5l1
            		djnz sound5l0
                    ret
	
sound6:	;enemy destroyed 2
            		ex de,hl
            		ld bc,20*256+16
sound6l0:
            		ld a,(hl)
            		inc hl
            		and c
            		out ($FE),a
            		xor a
sound6l0a:
            		dec a
            		jr nz,sound6l0a
            		djnz sound6l0
sound6l1:
            		ld a,(hl)
            		inc hl
            		and c
            		out ($FE),a
sound6l2:
            		dec a
            		jr nz,sound6l2
            		djnz sound6l1
                    ret
		
sound7:	;shot
            		ex de,hl
            		ld bc,50*256
sound7l0:
            		ld a,(hl)
            		inc hl
            		or c
            		and 16
            		out ($FE),a
            		ld a,(hl)
            		srl a
            		srl a
sound7l1:
            		dec a
            		jr nz,sound7l1
            		ld a,c
            		add a,4
            		ld c,a
            		djnz sound7l0
                    ret
	
sound8:	;take item
            		ld a,200
            		jr soundItem
sound9:
            		ld a,175
            		jr soundItem
sound10:
            		ld a,100
soundItem:
            		ld (frq),a
            		ld b,4
            		ld d,128
sound8l2:
            		push bc
            	   ;.frq=$+1
            	   ;	ld bc,2*256+200
            		defb #01	;ld bc
frq:
            		defb 200	;+200
            		defb 2	;2*256
sound8l0:
            		push bc
            		ld b,50
sound8l1:
            		xor 16
            		and 16
            		out ($FE),a
            		ld e,a
            		ld a,d
sound8l2b:
            		dec a
            		jr nz,sound8l2b
            		out ($FE),a
            		ld a,129
            		sub d
sound8l3:
            		dec a
            		jr nz,sound8l3
            		ld a,e
            		ld e,c
sound8l4:
            		dec e
            		jr nz,sound8l4
            		djnz sound8l1
            		pop bc
            		ld a,c
            		sub 16
            		ld c,a
            		djnz sound8l0
            		pop bc
            		srl d
            		srl d
            		djnz sound8l2
                    ret
	
;
;	SoundFX Table
;
;	n	sfx
;	----------
;	0	Enemy destroyed
;	1	Enemy hit
;	2	Something
;	3	Jump
;	4	Player hit
;	5	Enemy destroyed 2
;	6	Shot
;	7	Item #1		(item)
;	8	Item #2		(key)
;	9	Item #3		(life)
;	10  Item #4     (???)

proclist:
            		defw sound1
            		defw sound2
            		defw sound3
            		defw sound4
            		defw sound5
            		defw sound6
            		defw sound7
            		defw sound8
            		defw sound9
            		defw sound10

FIRE_SFX            equ     6
ALIEN_HIT_SFX       equ     1
SPACE_SFX           equ     2 + 128
MOTHERSHIP_HIT_SFX  equ     0
BULLET_HIT_SFX      equ     1
