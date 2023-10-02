;MODIFIED version by Lee du-Caine
;Compiles with ZX Spin assembler

;20th May 2006
;MODIFIED version by Tony Thompson
;Compiles with Pasmo assembler

;Vortex Tracker II v1.0 PT3 player for ZX Spectrum
;(c)2004 S.V.Bulba <vorobey@mail.khstu.ru> http://bulba.at.kz

;Release number
Release EQU "6"

;Features
;--------
;-Can be compiled at any address (i.e. no need rounding ORG
; address).
;-Variables (VARS) can be located at any address (not only after
;code block).
;-INIT subroutine detects module version and rightly generates
; both note and volume tables outside of code block (in VARS).
;-Two portamento (spc. command 3xxx) algorithms (depending of
; module version).
;-Any Tempo value are accepted (including Tempo=1 and Tempo=2).
;-Fully compatible with Ay_Emul PT3 player codes.
;-See also notes at the end of this source code.

;Limitations
;-----------
;-Can run in RAM only (self-modified code is used).

;Warning!!! PLAY subroutine can crash if no module are loaded
;into RAM or INIT subroutine was not called before.

;Call MUTE or INIT one more time to mute sound after stopping
;playing 

;	ORG $8000

;Test codes (commented)
;	CALL START
;	EI
;_LP	HALT
;	CALL START+5
;	XOR A
;	IN A,($FE)
;	CPL
;	AND 15
;	JR Z,_LP

;Entry and other points
;START initialization
;START+3 initialization with module address in HL
;START+5 play one quark
;START+8 mute
;START+10 setup and status flags
;START+11 pointer to current position value in PT3 module;
;After INIT (START+11) points to Postion0-1 (optimization)

;***NEW SFX COMMANDS:
;START+13 - INITSFX 	Initialises SFX system with preset .SFX chunk (see the very end of this file). This only needs to be done once. You can use this to change between several effects banks.
;START+16 - INITSFX2	Same as above but allows you to specify .SFX address in HL
;START+19 - PLAYSFX 	Specify sound effect number in A (first effect is at 0). When this is called, the sound will be buffered for playback the next time PLAY is called
;			NB: Calling an unused sound effect may have unexpected effects!
;			Extra Codes: 	255=note off (silences any currently playing sounds)
;					254=repeat last played sound effect
;START+22 - PLAYSFX2	**NOT YET IMPLEMENTED** advanced mode - will allow you to specify pitch/volume/randomization parameters! Currently just calls PLAYSFX
;START+25 - SFXMODE - load A with sfxmode before calling - 0=Normal 3-channel music mode, 1=2-channel music, 1-channel SFX NB: May cause problems if you change mode mid-playback?

SND_START
SND_INIT    LD HL,MDLADDR
SND_INIT_HL JR INIT
SND_PLAY    JP PLAY
SND_MUTE    JR MUTE
SETUP       DB 0    ;set bit0 to 1, if you want to play without looping
                    ;bit7 is set each time, when loop point is passed
CrPsPtr     DW 0
SFX_INIT    JP INITSFX
SFX_INIT2   JP INITSFX2
SFX_PLAY    JP PLAYSFX	;LD A with desired sound effect first. Calling unused sound effects may cause a crash!
SFX_PLAY2   JP PLAYSFX2
SFX_MODE    JR SND_SETSFXM

SND_SETSFXM
            LD (SFXMode),A	;*** stores the mode specified by the user
            RET

;Identifier
;	DB "=VTII PT3 Player r.",Release,"="
;*** REMOVED ABOVE TO SAVE BYTES

CHECKLP	LD HL,SETUP
	SET 7,(HL) ;set loop bit - this happens every time loop point is passed
	BIT 0,(HL)
	RET Z
	POP HL
	LD HL,DelyCnt
	INC (HL)
	LD HL,ChanA+CHNPRM_NtSkCn
	INC (HL)
MUTE	XOR A	;A=0
	LD H,A	;H=A=0
	LD L,A	;L=A=0
	;now set all three AY channels to 0 amplitude
	LD (AYREGS+AR_AmplA),A
	LD (AYREGS+AR_AmplB),HL ;simple optimisation - AmplB and AmplC are adjacent bytes, so this is a simple way of loading them both with 0
	JP ROUT_A0


INIT
;HL - AddressOfModule

	LD (MODADDR),HL ;store passed module address (HL)
	LD (MDADDR2),HL ;in MODADDR and MDADDR2
	LD (MDADDR3),HL ;backup copy
	
	PUSH HL		;put that MODADDR value on the stack too
	LD DE,100	;DE=100
	ADD HL,DE	;HL=HL+DE = 100 (0x64) bytes into the module address, after the header
	LD A,(HL)	;Load 1st byte from module (after header) - this is the modules default speed/rate
	LD (Delay),A	;Load it into Delay
	PUSH HL		;Push post-header module address
	POP IX		;Pop post-header module address onto IX
			;
	ADD HL,DE	;Add another 100 (stored in DE) onto address... this takes us to 200 - sequence data starts at 201. CrPsPtr=Current Pattern
	LD (CrPsPtr),HL	;The pattern numbers (multiplied by 3) are stored in this "table" (actually at 201), terminating with 0xFF
	LD E,(IX+102-100);E=*post-header* module address + 2 = 102 = the loop point
	ADD HL,DE	;add the loop-point-pattern-pos (DE) onto 200...
	INC HL		;(...and add 1 because the table actually starts at 201)
	LD (LPosPtr),HL	;store the loop pointer in LPosPtr
	POP DE		;module address (MODADDR) popped onto DE
	LD L,(IX+103-100);retrieve the offset from the start of MODADDR to the start of pattern data
	LD H,(IX+104-100);we take off 100 because we are using the post-header MODADDR+100, which already has 100 added on.
	ADD HL,DE	;This puts the address of the pattern data into HL
	LD (PatsPtr),HL ;PatsPtr = Where the pattern data begins.
	LD (MODTPtr),HL	;backup of PatsPtr... SFXMode means PatsPtr will get repointed to our own data, etc
	LD HL,169	;169=where the Ornament pointers are
	ADD HL,DE	;HL=(modified)MODADDR+ORNAMENT POINTERS LOCATION
	LD (OrnPtrs),HL
	LD (MODOPtr),HL
	LD HL,105	;105=where the Sample pointers are...
	ADD HL,DE
	LD (SamPtrs),HL
	LD (MODSPtr),HL
	LD HL,SETUP	;looping bit
	RES 7,(HL)	;unsets the "loop has been done bit" - this bit is set every time the loop point is passed

;note table data depacker
	LD DE,T_PACK
	LD BC,T1_+(2*49)-1
TP_0	LD A,(DE)
	INC DE
	CP 15*2
	JR NC,TP_1
	LD H,A
	LD A,(DE)
	LD L,A
	INC DE
	JR TP_2
TP_1	PUSH DE
	LD D,0
	LD E,A
	ADD HL,DE
	ADD HL,DE
	POP DE
TP_2	LD A,H
	LD (BC),A
	DEC BC
	LD A,L
	LD (BC),A
	DEC BC
	SUB $F0
	JR NZ,TP_0
	;NB: A must now be 0, otherwise the loop would still be going on

	LD HL,VARS		;source
	LD (HL),A		;(HL) = 
	LD DE,VARS+1		;target
	LD BC,VAR0END-VARS-1 	;counter
	LDIR			;fill the VARS with 0
	INC A			;A=1

	LD (DelyCnt),A		;DelyCnt=1
	LD HL,$F001 ;H - CHNPRM_Volume, L - CHNPRM_NtSkCn
	LD (ChanA+CHNPRM_NtSkCn),HL
	LD (ChanB+CHNPRM_NtSkCn),HL
	LD (ChanC+CHNPRM_NtSkCn),HL

	LD HL,EMPTYSAMORN
	LD (AdInPtA),HL ;ptr to zero
	LD (ChanA+CHNPRM_OrnPtr),HL ;ornament 0 is "0,1,0"
	LD (ChanB+CHNPRM_OrnPtr),HL ;in all versions from
	LD (ChanC+CHNPRM_OrnPtr),HL ;3.xx to 3.6x and VTII

	LD (ChanA+CHNPRM_SamPtr),HL ;S1 There is no default
	LD (ChanB+CHNPRM_SamPtr),HL ;S2 sample in PT3, so, you
	LD (ChanC+CHNPRM_SamPtr),HL ;S3 can comment S1,2,3; see
				    ;also EMPTYSAMORN comment

	LD A,(IX-87) ;EXTRACT VERSION NUMBER
	SUB $30
	JR C,L20
	CP 10
	JR C,L21
L20	LD A,6
L21	LD (Version),A
	PUSH AF
	CP 4
	LD A,(IX-1) ;TONE TABLE NUMBER
	RLA
	AND 7

;NoteTableCreator (c) Ivan Roshin
;A - NoteTableNumber*2+VersionForNoteTable
;(xx1b - 3.xx..3.4r, xx0b - 3.4x..3.6x..VTII1.0)

	LD HL,NT_DATA
	PUSH DE
	LD D,B
	ADD A,A
	LD E,A
	ADD HL,DE
	LD E,(HL)
	INC HL
	SRL E
	SBC A,A
	AND $A7 ;$00 (NOP) or $A7 (AND A)
	LD (L3),A
	EX DE,HL
	POP BC ;BC=T1_
	ADD HL,BC

	LD A,(DE)

	ADD A,T_ & 255
	LD C,A
	ADC A,T_/256 ;Z80ASM by AIG cannot to assemble it

;other variant (temporary, 1 byte longer...)
	;LD BC,T_
	;ADD A,C
	;LD C,A
	;ADC A,B

	SUB C
	LD B,A
	PUSH BC
	LD DE,NT_
	PUSH DE

	LD B,12
L1	PUSH BC
	LD C,(HL)
	INC HL
	PUSH HL
	LD B,(HL)

	PUSH DE
	EX DE,HL
	LD DE,23
	LD IXH,8

L2	SRL B
	RR C
L3	DB $19	;AND A or NOP
	LD A,C
	ADC A,D	;=ADC 0
	LD (HL),A
	INC HL
	LD A,B
	ADC A,D
	LD (HL),A
	ADD HL,DE
	DEC IXH
	JR NZ,L2

	POP DE
	INC DE
	INC DE
	POP HL
	INC HL
	POP BC
	DJNZ L1

	POP HL
	POP DE

	LD A,E
	CP TCOLD_1 & 255
	JR NZ,CORR_1
	LD A,$FD
	LD (NT_+$2E),A

CORR_1	LD A,(DE)
	AND A
	JR Z,TC_EXIT
	RRA
	PUSH AF
	ADD A,A
	LD C,A
	ADD HL,BC
	POP AF
	JR NC,CORR_2
	DEC (HL)
	DEC (HL)
CORR_2	INC (HL)
	AND A
	SBC HL,BC
	INC DE
	JR CORR_1

TC_EXIT

	POP AF

;VolTableCreator (c) Ivan Roshin
;A - VersionForVolumeTable (0..4 - 3.xx..3.4x;
			   ;5.. - 3.5x..3.6x..VTII1.0)

	CP 5
	LD HL,$11
	LD D,H
	LD E,H
	LD A,$17
	JR NC,M1
	DEC L
	LD E,L
	XOR A
M1      LD (M2),A

	LD IX,VT_+16
	LD C,$10

INITV2  PUSH HL

	ADD HL,DE
	EX DE,HL
	SBC HL,HL

INITV1  LD A,L
M2      DB $7D
	LD A,H
	ADC A,0
	LD (IX+$00),A
	INC IX
	ADD HL,DE
	INC C
	LD A,C
	AND 15
	JR NZ,INITV1

	POP HL
	LD A,E
	CP $77
	JR NZ,M3
	INC E
M3      LD A,C
	AND A
	JR NZ,INITV2

	JP ROUT_A0

;pattern decoder
PD_OrSm	LD (IX+8),0
	CALL SETORN
	LD A,(BC)	;loads next piece of pattern data (because BC has already been incremented to point to it)
	INC BC		;increment BC to point to the next piece of data after that...
	RRCA

PD_SAM	ADD A,A
PD_SAM_	LD E,A
	LD D,0
SamPtrs EQU $+1
	LD HL,$2121
	ADD HL,DE
	LD E,(HL)
	INC HL
	LD D,(HL)
MODADDR EQU $+1
	LD HL,$2121
	ADD HL,DE
	LD (IX+CHNPRM_SamPtr12),L
	LD (IX+CHNPRM_SamPtr13),H
	JR PD_LOOP

PD_VOL	RLCA
	RLCA
	RLCA
	RLCA
	LD (IX+CHNPRM_Volume12),A
	JR PD_LP2
	
PD_EOff	LD (IX+CHNPRM_Env_En12),A
	LD (IX-CHNPRM_PsInOr12),A
	JR PD_LP2

PD_SorE	DEC A
	JR NZ,PD_ENV
	LD A,(BC)
	INC BC
	LD (IX+CHNPRM_NNtSkp12),A
	JR PD_LP2

PD_ENV	CALL SETENV
	JR PD_LP2

PD_ORN	CALL SETORN
	JR PD_LOOP

PD_ESAM	LD (IX+CHNPRM_Env_En12),A
	LD (IX-CHNPRM_PsInOr12),A
	CALL NZ,SETENV
	LD A,(BC)
	INC BC
	JR PD_SAM_

	;when PTDECOD is called...
	;IX will have been set to ChanA+12,ChanB+12 or ChanC+12
	;BC will contain pointer to the relevant pattern data
PTDECOD LD A,(IX+CHNPRM_Note12)	;A=current note
	LD (PrNote+1),A			;this alters a LD $xxxx later on
	LD L,(IX-CHNPRM_CrTnSl12)	;loads L with low-byte of Current Tone Slide
	LD H,(IX-CHNPRM_CrTnSl13)	;loads H with high-byte of Current Tone Slide
	LD (PrSlide+1),HL		;loads the Current Tone Slide into PrSlide (self-modifying LD $xxxx)




;PT3:
;F0-FF - ornament number
;D0 - empty location?
;

PD_LOOP	LD DE,$2010	;DE=$2010
PD_LP2	LD A,(BC)	;Load A with the next piece of relevant pattern data (pointed to by BC)
;***			;NB: INJECT DATA HERE?!
	INC BC		;increment BC - pattern ptr+1
	ADD A,E		;A+$10 ... Adds $10 onto A, which holds the piece of pattern data
	JR C,PD_OrSm	;If Carry has been set, there must be an ornament/sample on this line, so jump to relevant part...
	ADD A,D		;A+$20
	JR Z,PD_FIN	;END OF TRACK DATA
	JR C,PD_SAM
	ADD A,E		;A+$10
	JR Z,PD_REL
	JR C,PD_VOL
	ADD A,E		;A+$10
	JR Z,PD_EOff
	JR C,PD_SorE
	ADD A,96	;A+$60
	JR C,PD_NOTE
	ADD A,E		;A+$10
	JR C,PD_ORN
	ADD A,D		;A+$20
	JR C,PD_NOIS
	ADD A,E		;A+$10
	JR C,PD_ESAM
	ADD A,A		;A+A...
	LD E,A
	;LD HL,SPCCOMS+$FF20-$2000
	LD HL,SPCCOMS-$20E0; 
	ADD HL,DE
	LD E,(HL)
	INC HL
	LD D,(HL)
	PUSH DE
	JR PD_LOOP

PD_NOIS	LD (Ns_Base),A
	JR PD_LP2

PD_REL	RES 0,(IX+CHNPRM_Flags12)
	JR PD_RES
	
PD_NOTE	LD (IX+CHNPRM_Note12),A
	SET 0,(IX+CHNPRM_Flags12)
	XOR A

PD_RES	LD (PDSP_+1),SP
	LD SP,IX
	LD H,A
	LD L,A
	PUSH HL
	PUSH HL
	PUSH HL
	PUSH HL
	PUSH HL
	PUSH HL
PDSP_	LD SP,$3131

PD_FIN	LD A,(IX+CHNPRM_NNtSkp12)	;load up note skip data
	LD (IX+CHNPRM_NtSkCn12),A
	RET

C_PORTM RES 2,(IX+CHNPRM_Flags12)
	LD A,(BC)
	INC BC
;SKIP PRECALCULATED TONE DELTA (BECAUSE
;CANNOT BE RIGHT AFTER PT3 COMPILATION)
	INC BC
	INC BC
	LD (IX+CHNPRM_TnSlDl12),A
	LD (IX-CHNPRM_TSlCnt12),A
	LD DE,NT_
	LD A,(IX+CHNPRM_Note12)
	LD (IX+CHNPRM_SlToNt12),A
	ADD A,A
	LD L,A
	LD H,0
	ADD HL,DE
	LD A,(HL)
	INC HL
	LD H,(HL)
	LD L,A
	PUSH HL
PrNote	LD A,$3E
	LD (IX+CHNPRM_Note12),A
	ADD A,A
	LD L,A
	LD H,0
	ADD HL,DE
	LD E,(HL)
	INC HL
	LD D,(HL)
	POP HL
	SBC HL,DE
	LD (IX+CHNPRM_TnDelt12),L
	LD (IX+CHNPRM_TnDelt13),H
	LD E,(IX-CHNPRM_CrTnSl12)
	LD D,(IX-CHNPRM_CrTnSl13)
Version EQU $+1
	LD A,$3E
	CP 6
	JR C,OLDPRTM ;Old 3xxx for PT v3.5-
PrSlide	LD DE,$1111
	LD (IX-CHNPRM_CrTnSl12),E
	LD (IX-CHNPRM_CrTnSl13),D
OLDPRTM	LD A,(BC) ;SIGNED TONE STEP
	INC BC
	EX AF,AF'
	LD A,(BC)
	INC BC
	AND A
	JR Z,NOSIG
	EX DE,HL
NOSIG	SBC HL,DE
	JP P,SET_STP
	CPL
	EX AF,AF'
	NEG
	EX AF,AF'
SET_STP	LD (IX+CHNPRM_TSlStp13),A
	EX AF,AF'
	LD (IX+CHNPRM_TSlStp12),A
	LD (IX-CHNPRM_COnOff12),0
	RET

C_GLISS	SET 2,(IX+CHNPRM_Flags12)
	LD A,(BC)
	INC BC
	LD (IX+CHNPRM_TnSlDl12),A
	LD (IX-CHNPRM_TSlCnt12),A
	LD A,(BC)
	INC BC
	EX AF,AF'
	LD A,(BC)
	INC BC
	JR SET_STP

C_SMPOS	LD A,(BC)
	INC BC
	LD (IX-CHNPRM_PsInSm12),A
	RET

C_ORPOS	LD A,(BC)
	INC BC
	LD (IX-CHNPRM_PsInOr12),A
	RET

C_VIBRT	LD A,(BC)
	INC BC
	LD (IX-CHNPRM_OnOffD12),A
	LD (IX-CHNPRM_COnOff12),A
	LD A,(BC)
	INC BC
	LD (IX+CHNPRM_OffOnD12),A
	XOR A
	LD (IX-CHNPRM_TSlCnt12),A
	LD (IX-CHNPRM_CrTnSl12),A
	LD (IX-CHNPRM_CrTnSl13),A
	RET

C_ENGLS	LD A,(BC)
	INC BC
	LD (Env_Del),A
	LD (CurEDel),A
	LD A,(BC)
	INC BC
	LD L,A
	LD A,(BC)
	INC BC
	LD H,A
	LD (ESldAdd),HL
	RET

C_DELAY	LD A,(BC)
	INC BC
	LD (Delay),A
	RET
	
SETENV	LD (IX+CHNPRM_Env_En12),E
	LD (AYREGS+AR_EnvTp),A
	LD A,(BC)
	INC BC
	LD H,A
	LD A,(BC)
	INC BC
	LD L,A
	LD (EnvBase),HL
	XOR A
	LD (IX-CHNPRM_PsInOr12),A
	LD (CurEDel),A
	LD H,A
	LD L,A
	LD (CurESld),HL
C_NOP	RET

SETORN	ADD A,A	;double A... so ornament data began as 1111xxxx, where xxxx is the data, and ends up as xxxx0000
	LD E,A	;load it into E
	LD D,0	;D=0
	LD (IX-CHNPRM_PsInOr12),D ;set Position In Ornament to 0, because we're starting to play a new ornament
OrnPtrs	EQU $+1		;self-modifying pointer
	LD HL,$2121	;...pointer to ornament data
	ADD HL,DE	;add the ornament pointer to the ornament number - now we have a pointer to the correct ornament index
	LD E,(HL)	;load the high byte of the index into E
	INC HL		;inc HL to point at low byte of index
	LD D,(HL)	;load the low byte of the index into D
MDADDR2	EQU $+1		;
	LD HL,$2121
	ADD HL,DE	;add the module pointer to the ornament offset
	LD (IX+CHNPRM_OrnPtr12),L	;now we can load a memory pointer to the ornament into the OrnPtr struct
	LD (IX+CHNPRM_OrnPtr13),H	;...
	RET

;ALL 16 ADDRESSES TO PROTECT FROM BROKEN PT3 MODULES
SPCCOMS DW C_NOP
	DW C_GLISS
	DW C_PORTM
	DW C_SMPOS
	DW C_ORPOS
	DW C_VIBRT
	DW C_NOP
	DW C_NOP
	DW C_ENGLS
	DW C_DELAY
	DW C_NOP
	DW C_NOP
	DW C_NOP
	DW C_NOP
	DW C_NOP
	DW C_NOP

CHREGS	XOR A			;A=0
	LD (Ampl),A		;Ampl=0
	BIT 0,(IX+CHNPRM_Flags)	;test bit 0 of the flags - the "enabled flag"
	PUSH HL			
	JP Z,CH_EXIT		;if channel not enabled, jump to CH_EXIT
	LD (CSP_+1),SP
	LD L,(IX+CHNPRM_OrnPtr)
	LD H,(IX+CHNPRM_OrnPtr+1)
	LD SP,HL
	POP DE
	LD H,A
	LD A,(IX+CHNPRM_PsInOr)
	LD L,A
	ADD HL,SP
	INC A
	CP D
	JR C,CH_ORPS
	LD A,E
CH_ORPS	LD (IX+CHNPRM_PsInOr),A
	LD A,(IX+CHNPRM_Note)
	ADD A,(HL)
	JP P,CH_NTP
	XOR A
CH_NTP	CP 96
	JR C,CH_NOK
	LD A,95
CH_NOK	ADD A,A
	EX AF,AF'
	LD L,(IX+CHNPRM_SamPtr)
	LD H,(IX+CHNPRM_SamPtr+1)
	LD SP,HL
	POP DE
	LD H,0
	LD A,(IX+CHNPRM_PsInSm)
	LD B,A
	ADD A,A
	ADD A,A
	LD L,A
	ADD HL,SP
	LD SP,HL
	LD A,B
	INC A
	CP D
	JR C,CH_SMPS
	LD A,E
CH_SMPS	LD (IX+CHNPRM_PsInSm),A
	POP BC
	POP HL
	LD E,(IX+CHNPRM_TnAcc)
	LD D,(IX+CHNPRM_TnAcc+1)
	ADD HL,DE
	BIT 6,B
	JR Z,CH_NOAC
	LD (IX+CHNPRM_TnAcc),L
	LD (IX+CHNPRM_TnAcc+1),H
CH_NOAC EX DE,HL
	EX AF,AF'
	LD L,A
	LD H,0
	LD SP,NT_
	ADD HL,SP
	LD SP,HL
	POP HL
	ADD HL,DE
	LD E,(IX+CHNPRM_CrTnSl)
	LD D,(IX+CHNPRM_CrTnSl+1)
	ADD HL,DE
CSP_	LD SP,$3131
	EX (SP),HL
	XOR A
	OR (IX+CHNPRM_TSlCnt)
	JR Z,CH_AMP
	DEC (IX+CHNPRM_TSlCnt)
	JR NZ,CH_AMP
	LD A,(IX+CHNPRM_TnSlDl)
	LD (IX+CHNPRM_TSlCnt),A
	LD L,(IX+CHNPRM_TSlStp)
	LD H,(IX+CHNPRM_TSlStp+1)
	LD A,H
	ADD HL,DE
	LD (IX+CHNPRM_CrTnSl),L
	LD (IX+CHNPRM_CrTnSl+1),H
	BIT 2,(IX+CHNPRM_Flags)
	JR NZ,CH_AMP
	LD E,(IX+CHNPRM_TnDelt)
	LD D,(IX+CHNPRM_TnDelt+1)
	AND A
	JR Z,CH_STPP
	EX DE,HL
CH_STPP SBC HL,DE
	JP M,CH_AMP
	LD A,(IX+CHNPRM_SlToNt)
	LD (IX+CHNPRM_Note),A
	XOR A
	LD (IX+CHNPRM_TSlCnt),A
	LD (IX+CHNPRM_CrTnSl),A
	LD (IX+CHNPRM_CrTnSl+1),A
CH_AMP	LD A,(IX+CHNPRM_CrAmSl)
	BIT 7,C
	JR Z,CH_NOAM
	BIT 6,C
	JR Z,CH_AMIN
	CP 15
	JR Z,CH_NOAM
	INC A
	JR CH_SVAM
CH_AMIN	CP -15
	JR Z,CH_NOAM
	DEC A
CH_SVAM	LD (IX+CHNPRM_CrAmSl),A
CH_NOAM	LD L,A
	LD A,B
	AND 15
	ADD A,L
	JP P,CH_APOS
	XOR A
CH_APOS	CP 16
	JR C,CH_VOL
	LD A,15
CH_VOL	OR (IX+CHNPRM_Volume)
	LD L,A
	LD H,0
	LD DE,VT_
	ADD HL,DE
	LD A,(HL)
CH_ENV	BIT 0,C
	JR NZ,CH_NOEN
	OR (IX+CHNPRM_Env_En)
CH_NOEN	LD (Ampl),A
	BIT 7,B
	LD A,C
	JR Z,NO_ENSL
	RLA
	RLA
	SRA A
	SRA A
	SRA A
	ADD A,(IX+CHNPRM_CrEnSl) ;SEE COMMENT BELOW
	BIT 5,B
	JR Z,NO_ENAC
	LD (IX+CHNPRM_CrEnSl),A
NO_ENAC	LD HL,AddToEn
	ADD A,(HL) ;BUG IN PT3 - NEED WORD HERE.
		   ;FIX IT IN NEXT VERSION?
	LD (HL),A
	JR CH_MIX
NO_ENSL RRA
	ADD A,(IX+CHNPRM_CrNsSl)
	LD (AddToNs),A
	BIT 5,B
	JR Z,CH_MIX
	LD (IX+CHNPRM_CrNsSl),A
CH_MIX	LD A,B
	RRA
	AND $48
CH_EXIT	LD HL,AYREGS+AR_Mixer 	;load up mixer settings into HL
	OR (HL)			;A would be 0 as default (channel not enabled)... so no change.
	RRCA			;???
	LD (HL),A		;load it back into AY regs mixer setting
	POP HL			;pops off the HL we pushed on at the start of CHREGS
	XOR A			;A=0
	OR (IX+CHNPRM_COnOff)	;...puts COnOff in A
	RET Z			;if COnOff is 0 then return
	DEC (IX+CHNPRM_COnOff)	;decrement the on/off value
	RET NZ			;and return if its not 0
				;...and if it is 0... (
	XOR (IX+CHNPRM_Flags)	;A = A XOR Flags = 0 XOR Flags... this toggles it? so the On/Off command just enables and disables the channel repeatedly
	LD (IX+CHNPRM_Flags),A	;put A back into the Flags...
	RRA			;rotate A right - only affects carry flag. so if it was enabled, the carry flag is set
	LD A,(IX+CHNPRM_OnOffD)	;put the time/delay value for ONoff into A
	JR C,CH_ONDL		;if enabled, jump to CH_ONDL and store the ONoff value...
	LD A,(IX+CHNPRM_OffOnD) ;else use the OFFon delay time value.
CH_ONDL	LD (IX+CHNPRM_COnOff),A ;store it in the counter.
	RET

PLAY    XOR A 			;A=0
	LD (AddToEn),A		;(AddToEn)=0
	LD (AYREGS+AR_Mixer),A	;AYREGS.Mixer=0
	DEC A			;A=255
	LD (AYREGS+AR_EnvTp),A  ;(AYREGS.EnvTp)=255
	LD HL,DelyCnt		;...
	DEC (HL)		;DelyCnt=DelyCnt-1
	JP NZ,PL2 		;JUMP to PL2 if we are still part way through a row, and don't have a new pattern row to process yet
Delay	EQU $+1		;speed of the song in frames
	LD A,$3E
	LD (DelyCnt),A	;...since we just played a row, the counter needs resetting

	LD HL,ChanA+CHNPRM_NtSkCn ;(Note Skip Count) - for when there are no notes to play on this row, this tells us how many empty rows till the next
	DEC (HL)		  ;DEC ChanA+CHNPRM_NtSkCn
	JR NZ,PL1B		;if NtSkCn !=0, we are waiting for the next note in that row, so jump to PL1B and process channel B instead

;"Address In Pattern for Channel A"
AdInPtA	EQU $+1		;pointer to the $0101 below
	LD BC,$0101	;BC= address of pattern pointer for channel A
	LD A,(BC)	;A= next value from pattern for channel A
	AND A
	JR NZ,PL1A	;if not 0, we have a note or something... so jump to PL1A
	LD D,A		;D=A (=next value from pattern)
	LD (Ns_Base),A	;Ns_Base=A - Noise Base? For Noise column in tracker? (probably not - noise column is stored in channel B)
	LD HL,(CrPsPtr) ;HL=Current Pos Pointer?
	INC HL		;HL+1
	LD A,(HL)	;A=HL (Current Pos Ptr +1)
	INC A		;A=HL+1
	JR NZ,PLNLP
	CALL CHECKLP
LPosPtr	EQU $+1		;pointer to the $2121 below
	LD HL,$2121	;load the loop position pointer into HL
	LD A,(HL)	;load contents of pointer into A
	INC A		;increase pointer
PLNLP	LD (CrPsPtr),HL	;set the CurrentPattPositionPtr to the start of the loop
	DEC A		;dec pointer
	ADD A,A		;double it
	LD E,A		;load it into E
	RL D		;rotate D left (possibly "double it"?)
PatsPtr	EQU $+1		;pointer to the $2121 below
	LD HL,$2121	;load HL with pointer to the pattern data
	ADD HL,DE	;...
	LD DE,(MODADDR) ;...
	LD (PSP_+1),SP  ;i think this section is something to do with moving onto a new pattern in the sequence
	LD SP,HL	;...
	POP HL		;...
	ADD HL,DE	;...
	LD B,H		;...
	LD C,L		;...
	POP HL		;i think this section is something to do with moving onto a new pattern in the sequence, loading up the pointers for it, etc
	ADD HL,DE	;...
	LD (AdInPtB),HL	;...
	POP HL		;...
	ADD HL,DE	;...
	;LD A,(SFXMode)	;***
	;OR A		;***
	;JR NZ,PSP_	;***skips over next line if we are in SFXmode 1 or 2
	LD (AdInPtC),HL	;
PSP_	LD SP,$3131	;...
PL1A	LD IX,ChanA+12	;load the address+12 of channel A params into IX...
	CALL PTDECOD
	LD (AdInPtA),BC	;put BC in the address for PtA

;PROCESS CHANNEL B
PL1B	LD HL,ChanB+CHNPRM_NtSkCn ;Note Skip Count - the CHNPRM_NtSkCn needs adding on because we haven't checked B or C channels like we have the A one's pattern data
	DEC (HL)	;decrease it by 1
	JR NZ,PL1C	;if its still not 0, we have no note/data for this channel...
	LD IX,ChanB+12
AdInPtB	EQU $+1
	LD BC,$0101
	CALL PTDECOD
	LD (AdInPtB),BC

;PROCESS CHANNEL C
PL1C
	LD A,(SFXMode) 	;***
	OR 0		;***
	JR NZ,SFXH	;***If we are in SFX mode, jump over the usual processing
	LD HL,ChanC+CHNPRM_NtSkCn ;Note Skip Count
	DEC (HL)
	JP NZ,PL2B
	LD IX,ChanC+12
AdInPtC	EQU $+1
	LD BC,$0101
	CALL PTDECOD
	LD (AdInPtC),BC
	JP PL2B



PL2	
	LD A,(SFXMode) 	;***
	OR A		;***
	JP Z,PL2B	;***If we're not in SFX mode, jump out of this part and into the final part of the player

SFXH	;***SFX handler goes here!
	;check to see if the trigger has been set
	LD A,(FXTrig)	;***
	OR A		;***
	JP Z,SFXH3	;*** if FXTrig=0, jump over the triggering routine
			;*** else...set up vars according to selected preset

	
SFXH2	;***this entire section SFXH2-SFXH3 has been added
	;when PTDECOD is called...
	;IX will have been set to ChanA+12,ChanB+12 or ChanC+12
	;BC will contain pointer to the relevant pattern data
	LD HL,ChanC+CHNPRM_NtSkCn ;***Note Skip Count
	DEC (HL)	;***decrease NtSkCn
	JR NZ,PL2B	;***if it's still not 0, we are waiting for the next row
	LD BC,(FXNext);***actually this is more like the "current" pattern data address
;*******NB: we need to patch in the correct SOT pointers before calling PTDECOD
	LD HL,(FXSmPtr)	;SamPtrs=FXSmPtr
	LD (SamPtrs),HL	;...
	LD HL,(FXOrnPtr);OrnPtrs=FXOrnPtr
	LD (OrnPtrs),HL	;
	LD HL,(FXAddr)	;MODADDR=MDADDR2=FXAddr
	LD (MODADDR),HL
	LD (MDADDR2),HL
	LD IX,ChanC+12
	CALL PTDECOD	;***this routine also updates NtSkCn
	LD (FXNext),BC	;***
	LD HL,(MODSPtr);restore the original pointers so the music can play as normal
	LD (SamPtrs),HL
	LD HL,(MODOPtr)
	LD (OrnPtrs),HL
	LD HL,(MDADDR3)
	LD (MODADDR),HL
	LD (MDADDR2),HL
	XOR A
	LD (FXTrig),A

SFXH3


		

PL2B	
	LD IX,ChanA
	LD HL,(AYREGS+AR_TonA)
	CALL CHREGS
	LD (AYREGS+AR_TonA),HL
	LD A,(Ampl)
	LD (AYREGS+AR_AmplA),A
	LD IX,ChanB
	LD HL,(AYREGS+AR_TonB)
	CALL CHREGS
	LD (AYREGS+AR_TonB),HL
	LD A,(Ampl)
	LD (AYREGS+AR_AmplB),A
	LD IX,ChanC
	LD HL,(AYREGS+AR_TonC)
	CALL CHREGS
	;LD A,(Ampl) ;Ampl = AYREGS+AR.AmplC
	;LD (AYREGS+AR.AmplC),A
	LD (AYREGS+AR_TonC),HL

	LD HL,(Ns_Base_AddToNs)
	LD A,H
	ADD A,L
	LD (AYREGS+AR_Noise),A

AddToEn EQU $+1
	LD A,$3E
	LD E,A
	ADD A,A
	SBC A,A
	LD D,A
	LD HL,(EnvBase)
	ADD HL,DE
	LD DE,(CurESld)
	ADD HL,DE
	LD (AYREGS+AR_Env),HL

	XOR A
	LD HL,CurEDel
	OR (HL)
	JR Z,ROUT_A0
	DEC (HL)
	JR NZ,ROUT
Env_Del	EQU $+1
	LD A,$3E
	LD (HL),A
ESldAdd	EQU $+1
	LD HL,$2121
	ADD HL,DE
	LD (CurESld),HL

ROUT	XOR A		;this section outputs data to the AY chip
ROUT_A0	LD DE,$FFBF
	LD BC,$FFFD
	LD HL,AYREGS
LOUT	OUT (C),A
	LD B,E
	OUTI 
	LD B,D
	INC A
	CP 13		;we only need to send data to the lower 13 bits - 14/15 are i/o bits
	JR NZ,LOUT
	OUT (C),A
	LD A,(HL)
	AND A
	RET M
	LD B,E
	OUT (C),A
	RET

INITSFX	
	LD HL,FXCHUNKBIN ;HL=FXCHUNK
INITSFX2 ;***pass pointer to fx chunk in HL
	LD (FXAddr),HL;
	;store FXSmPtr, FXOrnPtr, FXPrsPtr
	LD D,H
	LD E,L ;DE=HL=FXCHUNK
	LD IX,(FXAddr) ;Load chunk address into index reg
	LD L,(IX+0);get sample table offset
	LD H,(IX+1);...
	ADD HL,DE;add the chunk address onto it
	LD (FXSmPtr),HL;FXSamPtr=(HL)(=6 byte offset)
	LD L,(IX+2);
	LD H,(IX+3)
	ADD HL,DE;add the chunk address onto it
	LD (FXOrnPtr),HL;FXSamPtr=(HL)(=6 byte offset)
	LD L,(IX+4);
	LD H,(IX+5)
	ADD HL,DE;add the chunk address onto it
	LD (FXPrsPtr),HL;FXSamPtr=(HL)(=6 byte offset)	
	LD HL,FXNtOff
	LD (FXNext),HL ;point to default note data - the note off note
	XOR A
	LD (FXTrig),A
INITSFX3 ;we can jump here to init these params on the fly
	;e.g. we can have modes where these values are held, or reset every time a note is played
	XOR A
	LD (FXVol),A
	LD (FXRand),A
	LD (FXPitch),A
	RET


PLAYSFX	;***SIMPLE SFX player. Specify sound in A
	;if highest bit of A is set - NOTE OFF
	EX AF,AF' ;because otherwise A will get trashed by the following line
	CALL INITSFX3 ;reset vol/rand/pitch to 0
	EX AF,AF'
	CP 255;=note off code
	JR Z,PSFXNO ;if Note Off selected...
	CP 254;=repeat last note code
	JR Z,PSFXREP
	;***set up vars to play sound
	;FXNext
	LD HL,(FXPrsPtr)
	ADD A,A ;double preset number because the table is in words, not bytes
	LD C,A	;put it in the lower byte of BC
	LD B,0	;put 0 in high byte
	ADD HL,BC ;Add offset onto table start... now HL points to the correct table entry
	LD C,(HL);load data offset into BC
	INC HL
	LD B,(HL)
	LD HL,(FXAddr);load fx chunk address into HL
	ADD HL,BC ;add data offset onto chunk start
	LD (FXNext),HL

	;set ChannelC params
	LD IX,ChanC
	XOR A
	INC A
	LD (IX+CHNPRM_NtSkCn),A
	XOR A
	INC A
	LD (FXTrig),A

	RET
	
PSFXNO	LD HL,FXNtOff
	LD (FXNext),HL
PSFXREP	XOR A
	INC A
	LD (FXTrig),A
	RET



PLAYSFX2;***ADVANCED SFX player.
	JR PLAYSFX
	RET

	DB "NT_DATA"
NT_DATA	DB (T_NEW_0-T1_)*2
	DB TCNEW_0-T_
	DB (T_OLD_0-T1_)*2+1
	DB TCOLD_0-T_
	DB (T_NEW_1-T1_)*2+1
	DB TCNEW_1-T_
	DB (T_OLD_1-T1_)*2+1
	DB TCOLD_1-T_
	DB (T_NEW_2-T1_)*2
	DB TCNEW_2-T_
	DB (T_OLD_2-T1_)*2
	DB TCOLD_2-T_
	DB (T_NEW_3-T1_)*2
	DB TCNEW_3-T_
	DB (T_OLD_3-T1_)*2
	DB TCOLD_3-T_

T_

TCOLD_0	DB $00+1,$04+1,$08+1,$0A+1,$0C+1,$0E+1,$12+1,$14+1
	DB $18+1,$24+1,$3C+1,0
TCOLD_1	DB $5C+1,0
TCOLD_2	DB $30+1,$36+1,$4C+1,$52+1,$5E+1,$70+1,$82,$8C,$9C
	DB $9E,$A0,$A6,$A8,$AA,$AC,$AE,$AE,0
TCNEW_3	DB $56+1
TCOLD_3	DB $1E+1,$22+1,$24+1,$28+1,$2C+1,$2E+1,$32+1,$BE+1,0
TCNEW_0	DB $1C+1,$20+1,$22+1,$26+1,$2A+1,$2C+1,$30+1,$54+1
	DB $BC+1,$BE+1,0
TCNEW_1 EQU TCOLD_1
TCNEW_2	DB $1A+1,$20+1,$24+1,$28+1,$2A+1,$3A+1,$4C+1,$5E+1
	DB $BA+1,$BC+1,$BE+1,0

EMPTYSAMORN EQU $-1
	DB 1,0,$90 ;delete $90 if you don't need default sample

;first 12 values of tone tables (packed)

	DB "T_PACK"

T_PACK	DB $0D,$D8         ;$06EC*2/256,$06EC*2
	DB $0755-$06EC ;$69
	DB $07C5-$0755 ;70
	DB $083B-$07C5
	DB $08B8-$083B
	DB $093D-$08B8
	DB $09CA-$093D
	DB $0A5F-$09CA
	DB $0AFC-$0A5F
	DB $0BA4-$0AFC
	DB $0C55-$0BA4
	DB $0D10-$0C55 ;BB
	DB $0C,$DA         ;$066D*2/256,$066D*2
	DB $06CF-$066D ;62
	DB $0737-$06CF
	DB $07A4-$0737
	DB $0819-$07A4
	DB $0894-$0819
	DB $0917-$0894
	DB $09A1-$0917
	DB $0A33-$09A1
	DB $0ACF-$0A33
	DB $0B73-$0ACF
	DB $0C22-$0B73
	DB $0CDA-$0C22
	DB $0E,$08         ;$0704*2/256,$0704*2
	DB $076E-$0704
	DB $07E0-$076E
	DB $0858-$07E0
	DB $08D6-$0858
	DB $095C-$08D6
	DB $09EC-$095C
	DB $0A82-$09EC
	DB $0B22-$0A82
	DB $0BCC-$0B22
	DB $0C80-$0BCC
	DB $0D3E-$0C80
	DB $0F,$C0         ;$07E0*2/256,$07E0*2
	DB $0858-$07E0
	DB $08E0-$0858
	DB $0960-$08E0
	DB $09F0-$0960
	DB $0A88-$09F0
	DB $0B28-$0A88
	DB $0BD8-$0B28
	DB $0C80-$0BD8
	DB $0D60-$0C80
	DB $0E10-$0D60
	DB $0EF8-$0E10

;vars from here can be stripped
;you can move VARS to any other address

	;resb 512
VARS
	DB "VARS"
;ChannelsVars
IF 0
CHNPRM ;struct
;reset group
.PsInOr     defs 1      ;Position in Ornament
.PsInSm     defs 1      ;Position in Sample
.CrAmSl     defs 1      ;Current Amplitude (Slide?)
.CrNsSl     defs 1      ;Current Noise (Slide?)
.CrEnSl     defs 1      ;Current Envelope (Slide?)
.TSlCnt     defs 1      ;Tone Slide Count?
.CrTnSl     defsw 1     ;Current Tone Slide?
.TnAcc      defsw 1     ;Tone Accumulator
.COnOff     defs 1      ;a counter for the OnOff command. It counts down the number of frames ON or OFF, then flips.
;reset group
.OnOffD     defs 1      ;on/off tremolo command?
;IX for PTDECOD here (+12)
.OffOnD     defs 1      ;on/off tremolo command?
.OrnPtr     defsw 1     ;ornament pointer
.SamPtr     defsw 1     ;sample pointer
.NNtSkp     defs 1      ;next note skip - empty rows till next note (or data?)
.Note       defs 1      ;...
.SlToNt     defs 1      ;Slide To Note (- note to slide to?)
.Env_En     defs 1      ;Envelope enabled
.Flags      defs 1      ;Enabled - 0,SimpleGliss - 2
.TnSlDl     defs 1      ;Tone Slide Delay
.TSlStp     defsw 1     ;Tone Slide Step
.TnDelt     defsw 1     ;Tone Delta - calc'ed from Delay/Step?
.NtSkCn     defs 1      ;Note Skip Count. Number of rows until next note
.Volume     defs 1
.Size       defs 1
	endstruct
ELSE
;reset group
CHNPRM_PsInOr   equ 0   ;Position in Ornament
CHNPRM_PsInSm   equ 1   ;Position in Sample
CHNPRM_CrAmSl   equ 2   ;Current Amplitude (Slide?)
CHNPRM_CrNsSl   equ 3   ;Current Noise (Slide?)
CHNPRM_CrEnSl   equ 4   ;Current Envelope (Slide?)
CHNPRM_TSlCnt   equ 5   ;Tone Slide Count?
CHNPRM_CrTnSl   equ 6   ;Current Tone Slide?
CHNPRM_CrTnSl1  equ 7   ;Current Tone Slide?
CHNPRM_TnAcc    equ 8   ;Tone Accumulator
CHNPRM_TnAcc1   equ 9   ;Tone Accumulator
CHNPRM_COnOff   equ 10  ;a counter for the OnOff commandCHNPRM_ It counts down the number of frames ON or OFF, then flipsCHNPRM_
CHNPRM_OnOffD   equ 11  ;on/off tremolo command?
CHNPRM_OffOnD   equ 12  ;on/off tremolo command?
CHNPRM_OrnPtr   equ 13  ;ornament pointer
CHNPRM_OrnPtr1  equ 14  ;ornament pointer
CHNPRM_SamPtr   equ 15  ;sample pointer
CHNPRM_SamPtr1  equ 16  ;sample pointer
CHNPRM_NNtSkp   equ 17  ;next note skip - empty rows till next note (or data?)
CHNPRM_Note     equ 18  ;CHNPRM_CHNPRM_CHNPRM_
CHNPRM_SlToNt   equ 19  ;Slide To Note (- note to slide to?)
CHNPRM_Env_En   equ 20  ;Envelope enabled
CHNPRM_Flags    equ 21  ;Enabled - 0,SimpleGliss - 2
CHNPRM_TnSlDl   equ 22  ;Tone Slide Delay
CHNPRM_TSlStp   equ 23  ;Tone Slide Step
CHNPRM_TnDelt   equ 25  ;Tone Delta - calc'ed from Delay/Step?
CHNPRM_NtSkCn   equ 27  ;Note Skip CountCHNPRM_ Number of rows until next note
CHNPRM_Volume   equ 28
CHNPRM_Size     equ 29

; - 12
CHNPRM_PsInOr12 equ    12   ;Position in Ornament
CHNPRM_PsInSm12 equ    11   ;Position in Sample
CHNPRM_CrAmSl12 equ   -10   ;Current Amplitude (Slide?)
CHNPRM_CrNsSl12 equ    -9   ;Current Noise (Slide?)
CHNPRM_CrEnSl12 equ    -8   ;Current Envelope (Slide?)
CHNPRM_TSlCnt12 equ     7   ;Tone Slide Count?
CHNPRM_CrTnSl12 equ     6   ;Current Tone Slide?
CHNPRM_CrTnSl13 equ     5   ;Current Tone Slide?
CHNPRM_TnAcc12  equ    -4   ;Tone Accumulator
CHNPRM_TnAcc13  equ    -3   ;Tone Accumulator
CHNPRM_COnOff12 equ     2  ;a counter for the OnOff commandCHNPRM_ It counts down the number of frames ON or OFF, then flipsCHNPRM_
CHNPRM_OnOffD12 equ     1  ;on/off tremolo command?
CHNPRM_OffOnD12 equ     0  ;on/off tremolo command?
CHNPRM_OrnPtr12 equ     1  ;ornament pointer
CHNPRM_OrnPtr13 equ     2  ;ornament pointer
CHNPRM_SamPtr12 equ     3  ;sample pointer
CHNPRM_SamPtr13 equ     4  ;sample pointer
CHNPRM_NNtSkp12 equ     5  ;next note skip - empty rows till next note (or data?)
CHNPRM_Note12   equ     6  ;CHNPRM_CHNPRM_CHNPRM_
CHNPRM_SlToNt12 equ     7  ;Slide To Note (- note to slide to?)
CHNPRM_Env_En12 equ     8  ;Envelope enabled
CHNPRM_Flags12  equ     9  ;Enabled - 0,SimpleGliss - 2
CHNPRM_TnSlDl12 equ    10  ;Tone Slide Delay
CHNPRM_TSlStp12 equ    11  ;Tone Slide Step
CHNPRM_TSlStp13 equ    12  ;Tone Slide Step
CHNPRM_TnDelt12 equ    13  ;Tone Delta - calc'ed from Delay/Step?
CHNPRM_TnDelt13 equ    14  ;Tone Delta - calc'ed from Delay/Step?
CHNPRM_NtSkCn12 equ    15  ;Note Skip CountCHNPRM_ Number of rows until next note
CHNPRM_Volume12 equ    16
ENDIF


IF 0
ChanA	resb CHNPRM.Size
ChanB	resb CHNPRM.Size
ChanC	resb CHNPRM.Size
ELSE
ChanA   defs CHNPRM_Size, 0
ChanB   defs CHNPRM_Size, 0
ChanC   defs CHNPRM_Size, 0
ENDIF

	DB "ARStruct"
IF 0
AR struct
.TonA       defsw 1
.TonB       defsw 1
.TonC       defsw 1
.Noise      defs  1
.Mixer      defs  1
.AmplA      defs  1
.AmplB      defs  1
.AmplC      defs  1
.Env        defsw 1
.EnvTp      defs  1
.Size       defs  1
	endstruct
ELSE
AR_TonA     equ    0
AR_TonB     equ    2
AR_TonC     equ    4
AR_Noise    equ    6
AR_Mixer    equ    7
AR_AmplA    equ    8
AR_AmplB    equ    9
AR_AmplC    equ    10
AR_Env      equ    11
AR_EnvTp    equ    13
AR_Size     equ    14
ENDIF

	DB "GlobalVars"
;GlobalVars
DelyCnt     DB 0
CurESld     DW 0
CurEDel     DB 0
Ns_Base_AddToNs
Ns_Base	    DB 0
AddToNs	    DB 0




IF 0
AYREGS defs AR.Size
ELSE
AYREGS defs AR_Size
ENDIF

IF 0
VT_         resb 256 ;CreatedVolumeTableAddress
ELSE
VT_         defs 256, 0
ENDIF

EnvBase	    EQU VT_+14
T1_	        EQU VT_+16 ;Tone tables data depacked here

T_OLD_1	    EQU T1_
T_OLD_2	    EQU T_OLD_1+24
T_OLD_3	    EQU T_OLD_2+24
T_OLD_0	    EQU T_OLD_3+2
T_NEW_0	    EQU T_OLD_0
T_NEW_1	    EQU T_OLD_1
T_NEW_2	    EQU T_NEW_0+24
T_NEW_3	    EQU T_OLD_3

IF 0
NT_	        resb 192 ;CreatedNoteTableAddress
ELSE
NT_         defs 192, 0
ENDIF

;local var
Ampl        EQU AYREGS + AR_AmplC

VAR0END	    EQU VT_+16 ;INIT zeroes from VARS to VAR0END-1

VARSEND     EQU $

MDLADDR     EQU $9000

;***SFXVars - maybe make this into a struct later
	DB "SFXVars"
MODSPtr     DW 0
MODOPtr     DW 0
MODTPtr     DW 0
MDADDR3     DW 0
SFXMode     DB 1 ;***
FXAddr      DW 0

FXNext      DW FXNtOff      ;pointer to the "next" piece of note data, ie, the sound we are going to trigger - default points to "note off"
                            ;NB: we don't have to store which preset is being played, as FXNEXT will be loaded up with the correct data as soon as the user makes the relevant PLAYSFX call
FXTrig      DB 0	;trigger - set this to non-zero to play FXNEXT
FXVol       DB 0	;Volume. 0 = USE PRESET VOLUME
FXRand      DB 0	;SFX random byte: low nibble=volume variation (0 means none), high nibble=pitch variation (0 means none)
FXPitch     DW 0	;SFX pitch modifier? two bytes, fine and coarse (notes)
FXNtOff     DB $B1,$40,$D0,$00	;"note off" - 4 bytes - point to this to turn off sound fx - this is the default sound - "b1,40,d0,00"
FXSmPtr     DW 0	;pointer to sample table
FXOrnPtr    DW 0	;pointer to ornament table
FXPrsPtr    DW 0	;pointer to preset/track table

;PLAYSFX call parameters:
;A --> Preset to play --> 255=note off, 254=repeat last note

;PLAYSFX2 - with advanced parameters
;A --> Preset to play --> 255=note off, 254=repeat last note
;B --> Volume --> 0=use preset volume
;C --> Randbyte --> low nibble=volume variation (0 means none), high nibble=pitch variation (0 means none)
;DE -->Pitch mod byte

;PLAYSFX3 - "full control"
;A --> Preset to play --> 255=note off, 254=repeat last note
;B --> Volume --> 0=use preset volume
;C --> Randbyte --> low nibble=volume variation (0 means none), high nibble=pitch variation (0 means none)
;DE -->Absolute pitch byte
;D'E'-->Sample and Ornament number

;Release 0 steps:
;11.Sep.2004 - Note tables creator
;12.Sep.2004 - Volume tables creator; INIT subroutine
;13.Sep.2004 - Play counters, position counters
;14.Sep.2004 - Patterns decoder subroutine
;15.Sep.2004 - Resting (no code)
;16.Sep.2004 - CHREGS subroutine; global debugging; 1st stable
;version was born
;17.Sep.2004 - Debugging and optimization. First release!
;Release 1 steps:
;20.Sep.2004 - local vars moved to code (selfmodified code
;smaller and faster)
;22.Sep.2004 - added mute sound entry at START+8; position
;pointer moved to START+11; added setup and status byte at
;START+10 noloop mode and loop passed flags added
;Release 2 steps:
;28.Sep.2004 - Optimization: code around CHREGS's volume and
;vibrato faster now; zeroing PD_RES through stack; Ton and Ampl
;moved from channel vars to global ones; first position selector
;removed from INIT; optimization for packers(Ivan Roshin method)
;Release 3 steps:
;2.Oct.2004 - optimization in INIT and PD_LOOP (thanks to Ivan
;Roshin)
;4.Oct.2004 - load delay from (hl) in INIT (2 bytes shorter)
;5.Oct.2004 - optimization in PD_LOOP (->PD_LP2)
;7.Oct.2004 - swaping some commands for better packing
;Release 4 steps:
;9.Oct.2004 - optimization around LD HL,SPCCOMS (thanks to Ivan
;Roshin); in PTDECOD swapped BC and DE to optimize C_PORTM;
;removed sam and orn len and loop channel vars; CHREGS totally
;optimized
;Release 5 steps:
;11.Oct.2004 - PD_OrSm and C_PORTM optimized; Ivan Roshin's
;volume tables creator algorithm (51 bytes shorter than mine)
;12.Oct.2004 - Ivan Roshin's note tables creator algorithm (74
;bytes shorter than mine)
;Release 6 steps:
;14.Oct.2004 - loop and next position calculations moved to INIT
;15.Oct.2004 - AdInPt moved to code
;19.Oct.2004 - Env_Del moved to code
;20.Oct.2004 - Version PUSH and POP (1 byte shorter, thanks to
;Ivan Roshin)
;22.Oct.2004 - Env_En moved from Flags' bit to byte (shorter and
;faster code)
;25.Oct.2004 - SETENV optimized
;29.Oct.2004 - Optimized around AddToEn (SBC A,A, thanks to Ivan
;Roshin)
;3.Nov.2004 - Note tables data was compressed; with depacker it
;is 9 bytes shorter than uncompressed (thanks to Ivan Roshin)
;4.Nov.2004 - default sample and ornament both are fixed now
;and placed into code block (6 bytes shorter)
;7.Nov.2004 - LD A,(Ns_Base):LD L,A changed to LD HL,(Ns_Base)
;(thanks to Dima Bystrov)
;9.Nov.2004 - Ns_Base and AddToNs are merged to Ns_Base_AddToNs;
;LD A,255 changed to DEC A (at start of PLAY); added ROUT_A0
;12.Nov.2004 - NtSkCn&Volume are merged (8 bytes smaller init);
;LD BC,T1_ changed to PUSH DE...POP BC in note table creator
;19.Dec.2004 - NT_DATA reorganized (6 bytes shorter, thanks to
;Ivan Roshin); C_PORTM and C_GLISS are merged via SET_STP (48
;tacts slower, but 8 bytes smaller, thanks to Ivan Roshin)

;Tests in IMMATION TESTER V1.0 by Andy Man/POS (thanks to
;Himik's ZxZ for help):
;Module name/author	Min tacts	Max tacts	Average
;Spleen/Nik-O		1720		9256		5500
;Chuta/Miguel		1720		9496		5500
;Zhara/Macros		4536		8744		5500

;Size:
;Code block $647 bytes
;Variables $21D bytes (can be stripped)
;Size in RAM $647+$21D=$864 (2148) bytes

;Not so bad for the most universal PT3 player, I think ;)

;Notes:
;Pro Tracker 3.4r can not be detected by header, so PT3.4r tone
;tables realy used only for modules of 3.3 and older versions.

FXCHUNKBIN
	incbin "SoundFX.SFX"

TITLE_TUNE:
    incbin "TitleTune.pt3"
    
TUNE_A:
    incbin "TuneA.pt3"

TUNE_B:
    incbin "TuneB.pt3"
    
TUNE_C:
    incbin "TuneC.pt3"
