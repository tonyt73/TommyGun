#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Definitions. */

#define LF						0x0a
#define CR						0x0d

#define NUM_EVENTS				15							/* number of separate events to compile. */
#define MAX_EVENT_SIZE			32768						/* maximum size of compiled event routines. */
#define NUM_NESTING_LEVELS		12
#define SNDSIZ					41							/* size of each AY sound. */

#define NO_ARGUMENT				255
#define SPRITE_PARAMETER		0
#define NUMERIC					1

/* Game engine labels. */

#define PAM1ST					5							/* ix+5 is first sprite parameter. */
#define X						8							/* ix+8 is x coordinate of sprite. */
#define Y						9							/* ix+9 is y coordinate of sprite. */
#define GLOBALS					( VAR_EDGET - SPR_X + X )	/* global variables. */
#define IDIFF					( SPR_TYP - PAM1ST )		/* diff between type and first sprite param. */
#define ASMLABEL_DUMMY			1366


/* Here's the vocabulary. */

enum
{
	INS_IF = 1,
	INS_SPRITEUP,
	INS_SPRITEDOWN,
	INS_SPRITELEFT,
	INS_SPRITERIGHT,
	INS_ENDIF,
	INS_CANGOUP,
	INS_CANGODOWN,
	INS_CANGOLEFT,
	INS_CANGORIGHT,
	INS_LADDERABOVE,
	INS_LADDERBELOW,
	INS_DEADLY,
	INS_CUSTOM,
	INS_TO,
	INS_FROM,

	FIRST_PARAMETER,
	SPR_TYP = FIRST_PARAMETER,
	SPR_IMG,
	SPR_FRM,
	SPR_X,
	SPR_Y,
	SPR_DIR,
	SPR_PMA,
	SPR_PMB,

	FIRST_VARIABLE,
	VAR_EDGET = FIRST_VARIABLE,
	VAR_EDGEB,
	VAR_EDGEL,
	VAR_EDGER,
	VAR_SCREEN,
	VAR_LIV,
	VAR_A,
	VAR_B,
	VAR_C,
	VAR_D,
	VAR_E,
	VAR_F,
	VAR_G,
	VAR_H,
	VAR_I,
	VAR_J,
	VAR_K,
	VAR_L,
	VAR_M,
	VAR_N,
	VAR_O,
	VAR_P,
	VAR_LINE,
	VAR_COLUMN,
	VAR_RND,
	VAR_OBJ,
	LAST_PARAMETER = VAR_OBJ,

	INS_GOT,
	INS_KEY,
	INS_COLLISION,
	INS_NUM,												/* number follows this marker. */
	OPE_EQU,												/* operators. */
	OPE_GRT,
	OPE_NOT,
	OPE_LES,
	INS_LET,
	INS_ANIM,
	INS_ANIMBACK,
	INS_DIGUP,
	INS_DIGDOWN,
	INS_DIGLEFT,
	INS_DIGRIGHT,
	INS_FILLUP,
	INS_FILLDOWN,
	INS_FILLLEFT,
	INS_FILLRIGHT,
	INS_NEXTLEVEL,
	INS_RESTART,
	INS_SPAWN,
	INS_REMOVE,
	INS_GETRANDOM,
	INS_ELSE,
	INS_DISPLAYSCORE,
	INS_SCORE,
	INS_SOUND,
	INS_BEEP,
	INS_CLS,
	INS_BORDER,
	INS_COLOUR,
	INS_DELAY,
	INS_MESSAGE,
	INS_KILL,
	INS_ADD,
	INS_SUB,
	INS_DISPLAY,
	INS_SCREENUP,
	INS_SCREENDOWN,
	INS_SCREENLEFT,
	INS_SCREENRIGHT,
	INS_WAITKEY,
	INS_JUMP,
	INS_FALL,
	INS_OTHER,
	INS_SPAWNED,
	INS_ORIGINAL,
	INS_ENDGAME,
	INS_GET,
	INS_PUT,
	INS_DETECTOBJ,
	INS_ASM,
	INS_EXIT,
	INS_REPEAT,
	INS_ENDREPEAT,
	FINAL_INSTRUCTION
};

/* Function prototypes. */

void StartEvent( unsigned short int nEvent );
void BuildFile( void );
void EndEvent( void );
unsigned short int NextKeyword( void );
unsigned short int GetNum( void );
void Compile( unsigned short int nInstruction );
void ResetIf( void );
void CR_If( void );
void CR_SpriteUp( void );
void CR_SpriteDown( void );
void CR_SpriteLeft( void );
void CR_SpriteRight( void );
void CR_EndIf( void );
void CR_CanGoUp( void );
void CR_CanGoDown( void );
void CR_CanGoLeft( void );
void CR_CanGoRight( void );
void CR_LadderAbove( void );
void CR_LadderBelow( void );
void CR_Deadly( void );
void CR_Custom( void );
void CR_To( void );
void CR_Cls( void );
void CR_Got( void );
void CR_Key( void );
void CR_Collision( void );
void CR_Anim( void );
void CR_AnimBack( void );
void CR_DigUp( void );
void CR_DigDown( void );
void CR_DigLeft( void );
void CR_DigRight( void );
void CR_FillUp( void );
void CR_FillDown( void );
void CR_FillLeft( void );
void CR_FillRight( void );
void CR_NextLevel( void );
void CR_Restart( void );
void CR_Spawn( void );
void CR_Remove( void );
void CR_GetRandom( void );
void CR_DisplayScore( void );
void CR_Score( void );
void CR_Sound( void );
void CR_Beep( void );
void CR_Border( void );
void CR_Colour( void );
void CR_Delay( void );
void CR_Message( void );
void CR_Kill( void );
void CR_Add( void );
void CR_Subtract( void );
void CR_Display( void );
void CR_ScreenUp( void );
void CR_ScreenDown( void );
void CR_ScreenLeft( void );
void CR_ScreenRight( void );
void CR_WaitKey( void );
void CR_Jump( void );
void CR_Fall( void );
void CR_Other( void );
void CR_Spawned( void );
void CR_Original( void );
void CR_EndGame( void );
void CR_Get( void );
void CR_Put( void );
void CR_DetectObject( void );
void CR_Asm( void );
void CR_Exit( void );
void CR_Repeat( void );
void CR_EndRepeat( void );

unsigned short int CompileArgument( void );
unsigned short int NumberOnly( void );
void CR_Operator( unsigned short int nOperator );
void CR_Else( void );
void CR_Arg( void );
void CR_Pam( unsigned short int nParam );
void CR_ArgA( short int nNum );
void CR_ArgB( short int nNum );
void CR_PamA( short int nNum );
void CR_PamB( short int nNum );
void CR_PamC( short int nNum );
void CR_StackIf( void );
void CompileCondition( void );
void WriteJPNZ( void );
void WriteNumber( short int nInteger );
void WriteInstruction( unsigned char *cCommand );
void WriteInstructionArg( unsigned char *cCommand, unsigned short int nNum );
void WriteLabel( unsigned short int nWhere );
void NewLine( void );
void Error( unsigned char *cMsg );

/* Constants. */

unsigned const char *keywrd =
{
	/* Some keywords. */

	"IF."				// if.
	"SPRITEUP."			// move sprite up.
	"SPRITEDOWN."		// move sprite down.
	"SPRITELEFT."		// move sprite left.
	"SPRITERIGHT."		// move sprite right.
	"ENDIF."			// end-if.
	"CANGOUP."			// sprite can go up test.
	"CANGODOWN."		// sprite can go down test.
	"CANGOLEFT."		// sprite can go left test.
	"CANGORIGHT."		// sprite can go right test.
	"LADDERABOVE."		// ladder above test.
	"LADDERBELOW."		// ladder below test.
	"DEADLY."			// check if touching deadly block.
	"CUSTOM."    		// check if touching custom block.
	"TO."           	// variable to increment.
	"FROM."          	// variable to decrement.

	/* Sprite variables. */

	"TYPE."				// 17 - first parameter.
	"IMAGE."			// 18.
	"FRAME."			// 19.
	"X."				// 20.
	"Y."				// 21.
	"DIRECTION."		// 22.
	"PARAMA."			// sprite parameter a.
	"PARAMB."			// sprite parameter b.

	/* Global variables. */

	"EDGET."			// screen edge.
	"EDGEB."			// screen edge.
	"EDGEL."			// screen edge.
	"EDGER."			// screen edge.
	"SCREEN."			// screen number.
	"LIVES."			// lives.
	"A."				// variable.
	"B."				// variable.
	"C."				// variable.
	"D."				// variable.
	"E."				// variable.
	"F."				// variable.
	"G."				// variable.
	"H."				// variable.
	"I."				// variable.
	"J."				// variable.
	"K."				// variable.
	"L."				// variable.
	"M."				// variable.
	"N."				// variable.
	"O."				// variable.
	"P."				// variable.
	"LINE."				// x coordinate.
	"COLUMN."			// y coordinate.
	"RND."				// last random number variable.
	"OBJ."				// last object variable.
	"GOT."				// function.
	"KEY."				// function.

	/* Commands. */

	"COLLISION."		// collision with sprite.
	" ."				// number to follow.
	"=."				// equals, ignored.
	">."				// greater than, ignored.
	"<>."				// not equal to, ignored.
	"<=."				// less than or equal to, ignored.
	"LET."				// x=y.
	"ANIMATE."			// animate sprite.
	"ANIMBACK."			// animate sprite backwards.
	"DIGUP."			// dig up.
	"DIGDOWN."			// dig down.
	"DIGLEFT."			// dig left.
	"DIGRIGHT."			// dig right.
	"FILLUP."			// fill up.
	"FILLDOWN."			// fill down.
	"FILLLEFT."			// fill left.
	"FILLRIGHT."		// fill right.
	"NEXTLEVEL."		// next level.
	"RESTART."			// restart game.
	"SPAWN."			// spawn new sprite.
	"REMOVE."			// remove this sprite.
	"GETRANDOM."		// variable.
	"ELSE."				// else.
	"SHOWSCORE."		// show score.
	"SCORE."			// increase score.
	"SOUND."			// play sound.
	"BEEP."				// play beeper sound.
	"CLS."				// clear screen.
	"BORDER."			// set border.
	"COLOUR."			// set attributes.
	"DELAY."			// pause for a while.
	"MESSAGE."			// display message.
	"KILL."				// kill the player.
	"ADD."				// add to variable.
	"SUBTRACT."			// subtract from variable.
	"DISPLAY."			// display number.
	"SCREENUP."			// up a screen.
	"SCREENDOWN."		// down a screen.
	"SCREENLEFT."		// left a screen.
	"SCREENRIGHT."		// right a screen.
	"WAITKEY."			// wait for keypress.
	"JUMP."				// jump.
	"FALL."				// fall.
	"OTHER."			// select second collision sprite.
	"SPAWNED."			// select spawned sprite.
	"ORIGINAL."			// select original sprite.
	"ENDGAME."			// end game with victory.
	"GET."				// get object.
	"PUT."				// drop object.
	"DETECTOBJ."		// detect object.
	"ASM."				// encode.
	"EXIT."				// exit.
	"REPEAT."			// repeat.
	"ENDREPEAT."		// endrepeat.
};

const unsigned char cVariables[][ 7 ] =
{
	"edget",			// top edge.
	"edgeb",			// top edge.
	"edgel",			// top edge.
	"edger",			// top edge.
	"scno",				// screen number.
	"numlif",			// lives.
	"vara",				// variable.
	"varb",				// variable.
	"varc",				// variable.
	"vard",				// variable.
	"vare",				// variable.
	"varf",				// variable.
	"varg",				// variable.
	"varh",				// variable.
	"vari",				// variable.
	"varj",				// variable.
	"vark",				// variable.
	"varl",				// variable.
	"varm",				// variable.
	"varn",				// variable.
	"varo",				// variable.
	"varp",				// variable.
	"dispx",			// x coordinate.
	"dispy",			// y coordinate.
	"varrnd",			// last random number variable.
	"varobj"			// last object variable.
};

/* Variables. */

unsigned long int nErrors = 0;
unsigned short int nSourceLength = 0;
unsigned short int nSize;									/* source file length. */
unsigned short int nLine;
unsigned short int nAddress = 0;							/* compilation start address. */
unsigned short int nCurrent;								/* current compilation address. */
unsigned char *cBufPos;
unsigned char *cBuff;
unsigned char *cObjt;
unsigned char *cStart;
unsigned short int nIfBuff[ NUM_NESTING_LEVELS ];			/* nested IF addresses. */
unsigned short int nNumIfs;									/* number of Ifs. */
unsigned short int nIfSet;
unsigned short int nPamType;								/* parameter type. */
unsigned short int nPamNum;									/* parameter number. */
unsigned short int nLastOperator;							/* last operator. */
unsigned short int nOpType;									/* operation type, eg add or subtract. */
unsigned short int nRepeatAddress;							/* address ENDREPEAT jumps back to. */
unsigned short int nNextLabel;								/* label to write. */
unsigned short int nEvent;									/* event number passed to compiler */

FILE *pObject;												/* output file. */

/* Functions */

int main( int argc, const char* argv[] )
{
	short int nChr = 0;
	short int nTmp;
	FILE *pSource;

    if (argc != 4)
    {
		fputs( "AgdCompile {event number} {source file} {target file}\n\teg: AgdCompile test.agd test.asm\n", stderr );
        // invalid number of command line arguments
		exit ( 1 );
    }

	/* Open target file. */
	pObject = fopen( argv[3], "wb" );

	/* Open source file. */
	pSource = fopen( argv[2], "r" );

    nEvent = atoi(argv[1]);

	if ( !pSource )
	{
        fprintf( stderr, "Source file not found:  %s\n", argv[2]);
		exit ( 1 );
	}

	if ( !pObject )
	{
        fprintf( stderr, "Unable to create target file: %s\n", argv[3]);
		exit ( 1 );
	}

	/* Allocate buffer for the target code. */
	cObjt = ( char* )malloc( MAX_EVENT_SIZE );
	cStart = cObjt;
	if ( !cObjt )
	{
		fputs( "Out of memory\n", stderr );
		exit ( 1 );
	}

    /* Only build the command line event when using the TG compiler */
#ifndef BUILD_TG_COMPILER
	/* Else now process each of the event scripts in turn. */
    for ( nEvent = 0; nEvent < NUM_EVENTS; nEvent++ )
#endif
	{
		StartEvent( nEvent );								/* write event label and header. */

		if ( pSource )
		{
			/* Establish its size, 64K is more than generous. */
			fseek( pSource, 0, SEEK_END );
			nSize = ( short int )ftell( pSource );
			rewind( pSource );

			/* Allocate buffer for the script source code. */
			cBuff = ( char* )malloc( sizeof( char )*nSize );
			if ( !cBuff )
			{
				fputs( "Out of memory\n", stderr );
				exit ( 1 );
			}

			/* Read source file into the buffer. */
			nSize = fread( cBuff, 1, nSize, pSource );

			/* Compile our target */
			cBufPos = cBuff;								/* start of buffer */
			nLine = 1;										/* line number */

			BuildFile();

			/* Close source file and free up the memory. */
			fclose( pSource );
			free( cBuff );
		}

		EndEvent();											/* always put a ret at the end. */

		fwrite( cStart, 1, nCurrent - nAddress, pObject );	/* write output to file. */
	}

	/* Close target file and free up the memory. */
	fclose( pObject );
	free( cStart );

	return ( nErrors );
}

/* Sets up the label at the start of each event. */
void StartEvent( unsigned short int nEvent )
{
	unsigned char cLine[ 14 ];
	unsigned char *cChar = cLine;

	/* reset compilation address. */
	nCurrent = nAddress;
	nOpType = 0;
	nRepeatAddress = ASMLABEL_DUMMY;
	nNextLabel = 0;

	cObjt = cStart + ( nCurrent - nAddress );
	sprintf( cLine, "\nevnt%02d equ $", nEvent );

	while ( *cChar )
	{
		*cObjt = *cChar++;
		cObjt++;
		nCurrent++;
	}
}

/* Build our object file */
void BuildFile( void )
{
	unsigned short int nCount;
	unsigned short int nKeyword;

	/* Reset the IF address stack. */
	nNumIfs = 0;
	nIfSet = 0;
	ResetIf();

	for ( nCount = 0; nCount < NUM_NESTING_LEVELS; nCount++ )
	{
		nIfBuff[ nCount ] = 0;
	}

	do
	{
		nKeyword = NextKeyword();
		if ( nKeyword < FINAL_INSTRUCTION &&
			 nKeyword > 0 )
		{
			Compile( nKeyword );
		}
	}
	while ( cBufPos < ( cBuff + nSize ) );
}

void EndEvent( void )
{
	WriteInstruction( "ret" );								/* always put a ret at the end. */
	if ( nNumIfs > 0 )
	{
		Error( "Missing ENDIF" );
	}
}

/* Return next keyword number */
unsigned short int NextKeyword( void )
{
	unsigned short int nFound;
	unsigned short int nSrc = 0;
	unsigned short int nResWord = INS_IF;					/* ID of reserved word we're checking. */
	unsigned short int nWord = 0;
	const unsigned char *cRes;								/* reserved word pointer. */
	unsigned char *cSrcSt;									/* source pointer, word start. */
	unsigned char *cSrc;									/* source pointer. */

	/* Set up source address. */
	cSrc = cBufPos;
	nFound = 0;

	/* Skip spaces, newlines, comments etc. */
	do
	{
		if ( *cSrc == ';' )									/* comment marker? */
		{
			do												/* skip to next line */
			{
				cSrc++;
			}
			while ( *cSrc != LF && *cSrc != CR );
			nLine++;
		}
		else
		{
			if ( isdigit( *cSrc ) ||						/* valid character? */
				 isalpha( *cSrc ) ||
				 ( *cSrc >= '<' && *cSrc <= '>' ) )
			{
				nFound++;									/* flag as legitimate. */
			}
			else											/* treat as space. */
			{
				if ( *cSrc == LF )
				{
					nLine++;								/* count lines */
				}
				cSrc++;										/* skip character */
			}
		}
	}
	while ( !nFound && ( ( cSrc - cBuff ) < nSize ) );

	if ( !nFound )											/* end of file */
	{
		cBufPos = cBuff + nSize + 1;
		return( 0 );
	}

	if ( isdigit( *cSrc ) )									/* encountered a number. */
	{
		cBufPos = cSrc;
		return( INS_NUM );
	}

	/* Point to the reserved words and off we go */
	cSrcSt = cSrc;
	cRes = keywrd;
	nFound = 0;

	do
	{
		if ( toupper( *cSrc ) == *cRes )
		{
			cSrc++;
			cRes++;
		}
		else
		{
			if ( *cRes == '.' &&							/* end marker for reserved word? */
//				 ( *cSrc <= '<' || *cSrc >= '>' ) &&
				 ( toupper( *cSrc ) < 'A' ||				/* no more of source word? */
				   toupper( *cSrc ) > 'Z' ) )
			{
				nFound++;									/* great, matched a reserved word. */
			}
			else
			{
				nResWord++;									/* keep tally of words we've skipped. */
				if ( nResWord < FINAL_INSTRUCTION )
				{
					while ( *cRes++ != '.' );				/* find next reserved word. */
					cSrc = cSrcSt;							/* back to start of source word. */
				}
				else
				{
					while ( isalpha( *cSrc ) ||				/* find end of unrecognised word. */
						 ( *cSrc >= '<' && *cSrc <= '>' ) )
					{
						cSrc++;
					}
				}
			}
		}
	}
	while ( !nFound && nResWord < FINAL_INSTRUCTION );

	if ( !nFound )
	{
		Error( "Unrecognised instruction" );
	}

	cBufPos = cSrc;

	return ( nResWord );
}

/* Return number. */
unsigned short int GetNum( void )
{
	unsigned short int nNum = 0;
	unsigned char *cSrc;									/* source pointer. */

	cSrc = cBufPos;

	while( isdigit( *cSrc ) )
	{
		nNum = 10 * nNum + ( *cSrc - '0' );
		cSrc++;
	}

	if ( nNum > 255 )
	{
		Error( "Number out of range" );
	}

	cBufPos = cSrc;

	return ( nNum );
}


/* Parsed an instruction, this routine deals with it. */

void Compile( unsigned short int nInstruction )
{
	switch( nInstruction )
	{
		case INS_IF:
			CR_If();
			break;
		case INS_SPRITEUP:
			CR_SpriteUp();
			break;
		case INS_SPRITEDOWN:
			CR_SpriteDown();
			break;
		case INS_SPRITELEFT:
			CR_SpriteLeft();
			break;
		case INS_SPRITERIGHT:
			CR_SpriteRight();
			break;
		case INS_ENDIF:
			CR_EndIf();
			break;
		case INS_CANGOUP:
			CR_CanGoUp();
			break;
		case INS_CANGODOWN:
			CR_CanGoDown();
			break;
		case INS_CANGOLEFT:
			CR_CanGoLeft();
			break;
		case INS_CANGORIGHT:
			CR_CanGoRight();
			break;
		case INS_LADDERABOVE:
			CR_LadderAbove();
			break;
		case INS_LADDERBELOW:
			CR_LadderBelow();
			break;
		case INS_DEADLY:
			CR_Deadly();
			break;
		case INS_CUSTOM:
			CR_Custom();
			break;
		case INS_TO:
		case INS_FROM:
			CR_To();
			break;
		case INS_NUM:
			CR_Arg();
			break;
		case OPE_EQU:
		case OPE_GRT:
		case OPE_NOT:
		case OPE_LES:
			CR_Operator( nInstruction );
			break;
		case INS_LET:
			ResetIf();
			break;
		case INS_ELSE:
			CR_Else();
			break;
		case VAR_EDGET:
		case VAR_EDGEB:
		case VAR_EDGEL:
		case VAR_EDGER:
		case VAR_SCREEN:
		case VAR_LIV:
		case VAR_A:
		case VAR_B:
		case VAR_C:
		case VAR_D:
		case VAR_E:
		case VAR_F:
		case VAR_G:
		case VAR_H:
		case VAR_I:
		case VAR_J:
		case VAR_K:
		case VAR_L:
		case VAR_M:
		case VAR_N:
		case VAR_O:
		case VAR_P:
		case VAR_LINE:
		case VAR_COLUMN:
		case VAR_RND:
		case VAR_OBJ:
		case SPR_TYP:
		case SPR_IMG:
		case SPR_FRM:
		case SPR_X:
		case SPR_Y:
		case SPR_DIR:
		case SPR_PMA:
		case SPR_PMB:
			CR_Pam( nInstruction );
			break;
		case INS_GOT:
			CR_Got();
			break;
		case INS_KEY:
			CR_Key();
			break;
		case INS_COLLISION:
			CR_Collision();
			break;
		case INS_ANIM:
			CR_Anim();
			break;
		case INS_ANIMBACK:
			CR_AnimBack();
			break;
		case INS_DIGUP:
			CR_DigUp();
			break;
		case INS_DIGDOWN:
			CR_DigDown();
			break;
		case INS_DIGLEFT:
			CR_DigLeft();
			break;
		case INS_DIGRIGHT:
			CR_DigRight();
			break;
		case INS_FILLUP:
			CR_FillUp();
			break;
		case INS_FILLDOWN:
			CR_FillDown();
			break;
		case INS_FILLLEFT:
			CR_FillLeft();
			break;
		case INS_FILLRIGHT:
			CR_FillRight();
			break;
		case INS_NEXTLEVEL:
			CR_NextLevel();
			break;
		case INS_RESTART:
			CR_Restart();
			break;
		case INS_SPAWN:
			CR_Spawn();
			break;
		case INS_REMOVE:
			CR_Remove();
			break;
		case INS_GETRANDOM:
			CR_GetRandom();
			break;
		case INS_DISPLAYSCORE:
			CR_DisplayScore();
			break;
		case INS_SCORE:
			CR_Score();
			break;
		case INS_SOUND:
			CR_Sound();
			break;
		case INS_BEEP:
			CR_Beep();
			break;
		case INS_CLS:
			CR_Cls();
			break;
		case INS_BORDER:
			CR_Border();
			break;
		case INS_COLOUR:
			CR_Colour();
			break;
		case INS_DELAY:
			CR_Delay();
			break;
		case INS_MESSAGE:
			CR_Message();
			break;
		case INS_KILL:
			CR_Kill();
			break;
		case INS_ADD:
			CR_Add();
			break;
		case INS_SUB:
			CR_Subtract();
			break;
		case INS_DISPLAY:
			CR_Display();
			break;
		case INS_SCREENUP:
			CR_ScreenUp();
			break;
		case INS_SCREENDOWN:
			CR_ScreenDown();
			break;
		case INS_SCREENLEFT:
			CR_ScreenLeft();
			break;
		case INS_SCREENRIGHT:
			CR_ScreenRight();
			break;
		case INS_WAITKEY:
			CR_WaitKey();
			break;
		case INS_JUMP:
			CR_Jump();
			break;
		case INS_FALL:
			CR_Fall();
			break;
		case INS_OTHER:
			CR_Other();
			break;
		case INS_SPAWNED:
			CR_Spawned();
			break;
		case INS_ORIGINAL:
			CR_Original();
			break;
		case INS_ENDGAME:
			CR_EndGame();
			break;
		case INS_GET:
			CR_Get();
			break;
		case INS_PUT:
			CR_Put();
			break;
		case INS_DETECTOBJ:
			CR_DetectObject();
			break;
		case INS_ASM:
			CR_Asm();
			break;
		case INS_EXIT:
			CR_Exit();
			break;
		case INS_REPEAT:
			CR_Repeat();
			break;
		case INS_ENDREPEAT:
			CR_EndRepeat();
			break;

		default:
			printf( "Instruction %d not handled\n", nInstruction );
			break;
	}
}

void ResetIf( void )
{
	nIfSet = 0;
	nPamType = NO_ARGUMENT;
	nPamNum = 255;
}

/****************************************************************************************************************/
/* Individual compilation routines.                                                                             */
/****************************************************************************************************************/

void CR_If( void )
{
	nLastOperator = OPE_EQU;
	ResetIf();
	nIfSet = 1;
}

void CR_SpriteUp( void )
{
	WriteInstruction( "dec (ix+8)" );
}

void CR_SpriteDown( void )
{
	WriteInstruction( "inc (ix+8)" );
}

void CR_SpriteLeft( void )
{
	WriteInstruction( "dec (ix+9)" );
}

void CR_SpriteRight( void )
{
	WriteInstruction( "inc (ix+9)" );
}

void CR_EndIf( void )
{
	unsigned short int nAddr1;
	unsigned short int nAddr2;
	unsigned short int nAddr3;

	if ( nNumIfs > 0 )
	{
		nAddr1 = nIfBuff[ --nNumIfs ];						/* where to put label after conditional jump. */
		nAddr2 = nCurrent;									/* where we are is ENDIF address. */
//		WriteLabel( nAddr2 );								/* set jump address for unsuccessful IF. */
		nCurrent = nAddr1;									/* go back to end of original condition. */
		WriteLabel( nAddr2 );								/* set jump address for unsuccessful IF. */
		nNextLabel = nCurrent;
		nCurrent = nAddr2;

		nNextLabel = nAddr2;
	}
}

void CR_CanGoUp( void )
{
	WriteInstruction( "call cangu" );
	WriteInstruction( "jp nz,      " );
	CompileCondition();
	ResetIf();
}

void CR_CanGoDown( void )
{
	WriteInstruction( "call cangd" );
	WriteInstruction( "jp nz,      " );
	CompileCondition();
	ResetIf();
}

void CR_CanGoLeft( void )
{
	WriteInstruction( "call cangl" );
	WriteInstruction( "jp nz,      " );
	CompileCondition();
	ResetIf();
}

void CR_CanGoRight( void )
{
	WriteInstruction( "call cangr" );
	WriteInstruction( "jp nz,      " );
	CompileCondition();
	ResetIf();
}

void CR_LadderAbove( void )
{
	WriteInstruction( "call laddu" );
	WriteInstruction( "jp nz,      " );
	CompileCondition();
	ResetIf();
}

void CR_LadderBelow( void )
{
	WriteInstruction( "call laddd" );
	WriteInstruction( "jp nz,      " );
	CompileCondition();
	ResetIf();
}

void CR_Deadly( void )
{
	WriteInstruction( "ld b,DEADLY" );
	WriteInstruction( "call tded" );
	WriteInstruction( "cp b" );
	WriteInstruction( "jp nz,      " );
	CompileCondition();
	ResetIf();
}

void CR_Custom( void )
{
	WriteInstruction( "ld b,CUSTOM" );
	WriteInstruction( "call tded" );
	WriteInstruction( "cp b" );
	WriteInstruction( "jp nz,      " );
	CompileCondition();
	ResetIf();
}

void CR_To( void )
{
	unsigned short int nWhere;								/* where to put the result. */

	if ( nOpType > 0 )
	{
		nWhere = CompileArgument();
		if ( nOpType == 129 )
		{
			WriteInstruction( "add a,c" );
		}
		else
		{
			WriteInstruction( "sub c" );
		}
		if ( nWhere >= FIRST_PARAMETER &&
			 nWhere <= LAST_PARAMETER )
		{
			CR_PamC( nWhere );								/* put accumulator in variable or sprite parameter. */
		}
		nOpType = 0;
	}
	else
	{
		Error( "ADD or SUBTRACT missing" );
	}
}

void CR_Got( void )
{
	CompileArgument();
	WriteInstruction( "call gotob" );
	WriteInstruction( "jp c,      " );
	CompileCondition();
	ResetIf();
}

void CR_Key( void )
{
	unsigned short int nNum = NumberOnly();

	WriteInstruction( "ld a,(joyval)" );
	WriteInstruction( "and " );
	WriteNumber( 1 << nNum );
	WriteInstruction( "jp nz,      " );
	CompileCondition();
	ResetIf();
}

void CR_Collision( void )
{
	unsigned short int nNum = NumberOnly();

	WriteInstruction( "ld b," );
	WriteNumber( nNum );									/* sprite type to find. */
	WriteInstruction( "call sktyp" );
	WriteInstruction( "jp nc,      " );
	CompileCondition();
	ResetIf();
}

void CR_Anim( void )
{
	WriteInstruction( "call animsp" );
}

void CR_AnimBack( void )
{
	WriteInstruction( "call animbk" );
}

void CR_DigUp( void )
{
	WriteInstruction( "call digu" );
}

void CR_DigDown( void )
{
	WriteInstruction( "call digd" );
}

void CR_DigLeft( void )
{
	WriteInstruction( "call digl" );
}

void CR_DigRight( void )
{
	WriteInstruction( "call digr" );
}

void CR_FillUp( void )
{
	unsigned short int nNum = NumberOnly();

	WriteInstruction( "ld b," );
	WriteNumber( nNum );
	WriteInstruction( "call fillu" );
}

void CR_FillDown( void )
{
	unsigned short int nNum = NumberOnly();

	WriteInstruction( "ld b," );
	WriteNumber( nNum );
	WriteInstruction( "call filld" );
}

void CR_FillLeft( void )
{
	unsigned short int nNum = NumberOnly();

	WriteInstruction( "ld b," );
	WriteNumber( nNum );
	WriteInstruction( "call filll" );
}

void CR_FillRight( void )
{
	unsigned short int nNum = NumberOnly();

	WriteInstruction( "ld b," );
	WriteNumber( nNum );
	WriteInstruction( "call fillr" );
}

void CR_NextLevel( void )
{
	WriteInstruction( "ld hl,nexlev" );
	WriteInstruction( "ld (hl),h" );
}

void CR_Restart( void )
{
	WriteInstruction( "ld hl,restfl" );
	WriteInstruction( "ld (hl),h" );
}

void CR_Spawn( void )
{
	unsigned short int nNum = NumberOnly();

	WriteInstruction( "ld bc," );
	nNum = 256 * NumberOnly() + nNum;
	WriteNumber( nNum );									/* pass both parameters as 16-bit argument. */
	WriteInstruction( "call spawn" );
}

void CR_Remove( void )
{
	WriteInstruction( "ld (ix+5),255" );
}

void CR_GetRandom( void )
{
	WriteInstruction( "call random" );
}

void CR_DisplayScore( void )
{
	WriteInstruction( "call dscore" );
}

void CR_Score( void )
{
	CompileArgument();
	WriteInstruction( "call addsc" );
}

void CR_Sound( void )
{
	unsigned short int nNum = NumberOnly();

	nNum = SNDSIZ;
	WriteInstruction( "ld hl,(sndptr)" );
	WriteInstruction( "ld de," );
	WriteNumber( nNum );
	WriteInstruction( "add hl,de" );
	WriteInstruction( "call isnd" );
}

void CR_Beep( void )
{
	CompileArgument();
	WriteInstruction( "ld (sndtyp),a" );
}

void CR_Cls( void )
{
	WriteInstruction( "call 3503" );
}

void CR_Border( void )
{
	CompileArgument();
	WriteInstruction( "call 8859" );						/* address of ROM BORDER routine. */
}

void CR_Colour( void )
{
	CompileArgument();
	WriteInstruction( "ld (23693),a" );						/* permanent attributes. */
	WriteInstruction( "ld (23695),a" );						/* temporary attributes. */
}

void CR_Delay( void )
{
	CompileArgument();
	WriteInstruction( "ld b,a" );
	WriteInstruction( "call delay" );
}

void CR_Message( void )
{
	CompileArgument();
	WriteInstruction( "call dmsg" );
}

void CR_Kill( void )
{
	WriteInstruction( "ld hl,deadf" );
	WriteInstruction( "ld (hl),h" );
}

void CR_Add( void )
{
	nOpType = 129;											/* code for ADD A,C (needed by CR_To). */
	CompileArgument();
	WriteInstruction( "ld c,a" );
}

void CR_Subtract( void )
{
	nOpType = 145;											/* code for SUB C (needed by CR_To). */
	CompileArgument();
	WriteInstruction( "ld c,a" );
}

void CR_Display( void )
{
	CompileArgument();
	WriteInstruction( "call disply" );
}

void CR_ScreenUp( void )
{
	WriteInstruction( "call scru" );
}

void CR_ScreenDown( void )
{
	WriteInstruction( "call scrd" );
}

void CR_ScreenLeft( void )
{
	WriteInstruction( "call scrl" );
}

void CR_ScreenRight( void )
{
	WriteInstruction( "call scrr" );
}

void CR_WaitKey( void )
{
	WriteInstruction( "call prskey" );
}

void CR_Jump( void )
{
	WriteInstruction( "call jump" );
}

void CR_Fall( void )
{
	WriteInstruction( "call ifall" );
}

void CR_Other( void )
{
	WriteInstruction( "ld ix,(skptr)" );
}

void CR_Spawned( void )
{
	WriteInstruction( "ld ix,(spptr)" );
}

void CR_Original( void )
{
	WriteInstruction( "ld ix,(ogptr)" );
}

void CR_EndGame( void )
{
	WriteInstruction( "ld hl,gamwon" );
	WriteInstruction( "ld (hl),h" );
}

void CR_Get( void )
{
	WriteInstruction( "call getobj" );
}

void CR_Put( void )
{
	CompileArgument();
	WriteInstruction( "call drpobj" );
}

void CR_DetectObject( void )
{
	WriteInstruction( "call skobj" );
	WriteInstruction( "ld (varobj),a" );
}

void CR_Asm( void )											/* this is undocumented as it's dangerous! */
{
	unsigned short int nNum = NumberOnly();

	WriteNumber( nNum );									/* write opcode straight to code. */
}

void CR_Exit( void )
{
	WriteInstruction( "ret" );								/* finish event. */
}

void CR_Repeat( void )
{
	if ( nRepeatAddress == ASMLABEL_DUMMY )
	{
		CompileArgument();
		WriteInstruction( "ld (loopc),a" );
		nRepeatAddress = nCurrent;							/* store current address. */
		nNextLabel = nRepeatAddress;
	}
	else
	{
		Error( "Nested REPEAT" );
	}
}

void CR_EndRepeat( void )
{
	if ( nRepeatAddress == ASMLABEL_DUMMY )
	{
		Error( "ENDREPEAT without REPEAT" );
	}
	else
	{
		WriteInstruction( "ld hl,loopc" );
		WriteInstruction( "dec (hl)" );
		WriteInstruction( "jp nz," );
		WriteLabel( nRepeatAddress );
		nRepeatAddress = ASMLABEL_DUMMY;
	}
}


/****************************************************************************************************************/
/* command requires a number, variable or sprite parameter as an argument.                                      */
/****************************************************************************************************************/
unsigned short int CompileArgument( void )
{
	unsigned short int nArg = NextKeyword();

	if ( nArg == INS_NUM )
	{
		CR_ArgA( GetNum() );
	}
	else
	{
		if ( nArg >= FIRST_PARAMETER &&
			 nArg <= LAST_PARAMETER )
		{
			CR_PamA( nArg );
		}
		else
		{
			Error( "Invalid argument" );
		}
	}

	return ( nArg );
}

unsigned short int NumberOnly( void )
{
	unsigned short int nArg = NextKeyword();

	if ( nArg == INS_NUM )
	{
		nArg = GetNum();
	}
	else
	{
		Error( "Number expected" );
		nArg = 0;
	}

	return ( nArg );
}

void CR_Operator( unsigned short int nOperator )
{
	nLastOperator = nOperator;
}

void CR_Else( void )
{
	unsigned short int nAddr1;
	unsigned short int nAddr2;
	unsigned short int nAddr3;

	if ( nNumIfs > 0 )
	{
		WriteInstruction( "jp " );							/* jump over the ELSE to the ENDIF. */
		nAddr2 = nCurrent;									/* store where we are. */
		nAddr1 = nIfBuff[ nNumIfs - 1 ];					/* original conditional jump. */
		nIfBuff[ nNumIfs - 1 ] = nAddr2;					/* store ELSE address so we can write it later. */
		nCurrent = nAddr2;
		WriteLabel( nAddr2 );								/* set jump address before ELSE. */

		nAddr3 = nCurrent;									/* where to resume after the ELSE. */
		nCurrent = nAddr1;
		WriteLabel( nAddr3 );								/* set jump address before ELSE. */
		nCurrent = nAddr3;
		nNextLabel = nCurrent;

		ResetIf();											/* no longer in an IF clause. */
	}
}

/****************************************************************************************************************/
/* We've hit a loose numeric value, so it's an argument for something.                                          */
/* We need to establish how it fits in to the code.                                                             */
/****************************************************************************************************************/
void CR_Arg( void )
{
	if ( nPamType == 255 )									/* this is the first argument we've found. */
	{
		nPamType = NUMERIC;									/* set flag to say we've found a number. */
		nPamNum = GetNum();
	}
	else													/* this is the second argument. */
	{
		if ( nIfSet > 0 )									/* we're in an IF. */
		{
			CR_ArgA( GetNum() );							/* compile code to set up this argument. */

			if ( nPamType == NUMERIC )
			{
				CR_ArgB( nPamNum );							/* compile second argument: numeric. */
				CR_StackIf();
			}

			if ( nPamType == SPRITE_PARAMETER )
			{
				CR_PamB( nPamNum );							/* compile second argument: variable or sprite parameter. */
				CR_StackIf();
			}
		}
		else												/* not a comparison, so we're setting a sprite parameter. */
		{
			if ( nPamType == SPRITE_PARAMETER )
			{
				CR_ArgA( GetNum() );						/* compile second argument: variable or sprite parameter. */
				CR_PamC( nPamNum );							/* compile code to set variable or sprite parameter. */
			}
			else											/* trying to assign a number to another number. */
			{
				GetNum();									/* ignore the number. */
			}
			ResetIf();
		}
	}
}

/****************************************************************************************************************/
/* We've hit a loose variable or sprite parameter, so it's an argument for something.                           */
/* We need to establish how it fits in to the code.                                                             */
/****************************************************************************************************************/
void CR_Pam( unsigned short int nParam )
{
	if ( nPamType == 255 )									/* this is the first argument we've found. */
	{
		nPamType = SPRITE_PARAMETER;
		nPamNum = nParam;
	}
	else													/* this is the second argument. */
	{
		if ( nIfSet > 0 )									/* we're in an IF. */
		{
			CR_PamA( nParam );								/* compile second argument: variable or sprite parameter. */
			if ( nPamType == SPRITE_PARAMETER )
			{
				CR_PamB( nPamNum );							/* compare with first argument. */
			}
			else
			{
				CR_ArgB( nPamNum );							/* compare with first argument. */
			}
			CompileCondition();
			ResetIf();
		}
		else												/* not an IF, we must be assigning a value. */
		{
			if ( nPamType == SPRITE_PARAMETER )
			{
				CR_PamA( nParam );							/* set up the value. */
				CR_PamC( nPamNum );
			}
			else
			{
				ResetIf();
			}
		}
	}
}


/****************************************************************************************************************/
/* CR_ArgA, CR_PamA compile code to put the number or parameter in the accumulator.                             */
/* CR_ArgB, CR_PamB compile code to compare the number or parameter with the number already in the accumulator. */
/****************************************************************************************************************/
void CR_ArgA( short int nNum )
{
	WriteInstruction( "ld a," );
	WriteNumber( nNum );
}

void CR_ArgB( short int nNum )
{
	WriteInstruction( "cp " );
	WriteNumber( nNum );
	WriteJPNZ();											/* write conditional jump at end of if. */
}

void CR_PamA( short int nNum )
{
	char cVar[ 14 ];

	if ( nNum >= FIRST_VARIABLE )							/* load accumulator with global variable. */
	{
		sprintf( cVar, "ld a,(%s)", cVariables[ nNum - FIRST_VARIABLE ] );
		WriteInstruction( cVar );
	}
	else													/* load accumulator with sprite parameter. */
	{
		WriteInstructionArg( "ld a,(ix+?)", nNum - IDIFF );
	}
}

void CR_PamB( short int nNum )
{
	char cVar[ 13 ];

	if ( nNum >= FIRST_VARIABLE )							/* compare accumulator with global variable. */
	{
		sprintf( cVar, "ld hl,%s", cVariables[ nNum - FIRST_VARIABLE ] );
		WriteInstruction( cVar );
		WriteInstruction( "cp (hl)" );
	}
	else													/* compare accumulator with sprite parameter. */
	{
		WriteInstructionArg( "cp (ix+?)", nNum );
	}

	WriteJPNZ();											/* write conditional jump at end of if. */
}

void CR_PamC( short int nNum )
{
	char cVar[ 14 ];

	if ( nNum >= FIRST_VARIABLE )							/* compare accumulator with global variable. */
	{
		sprintf( cVar, "ld (%s),a", cVariables[ nNum - FIRST_VARIABLE ] );
		WriteInstruction( cVar );

		if ( nNum == VAR_SCREEN )							/* is this code changing the screen? */
		{
			WriteInstruction( "call nwscr" );				/* address of routine to display the new screen. */
		}
	}
	else													/* compare accumulator with sprite parameter. */
	{
		WriteInstructionArg( "ld (ix+?),a", nNum - IDIFF );
	}
}


void CR_StackIf( void )
{
	CompileCondition();
	ResetIf();
}

/****************************************************************************************************************/
/* We don't yet know where we want to jump following the condition, so remember address where label will be     */
/* written when we have that address.                                                                           */
/****************************************************************************************************************/
void CompileCondition( void )
{
	if ( nNumIfs < NUM_NESTING_LEVELS )
	{
		nIfBuff[ nNumIfs ] = nCurrent - 6;					/* minus 6 for label after contional jump. */
		nNumIfs++;
	}
	else
	{
		fputs( "Nesting too deep\n", stderr );
	}
}

/****************************************************************************************************************/
/* Writes the conditional jump at the end of an IF.                                                             */
/****************************************************************************************************************/
void WriteJPNZ( void )
{
	switch ( nLastOperator )
	{
		case OPE_NOT:
			WriteInstruction( "jp z,xxxxxx" );
			break;
		case OPE_GRT:
			WriteInstruction( "jp nc,xxxxxx" );
			break;
		case OPE_LES:
			WriteInstruction( "jp c,xxxxxx" );
			break;
		case OPE_EQU:
		default:
			WriteInstruction( "jp nz,xxxxxx" );
			break;
	}
}

void WriteNumber( short int nInteger )
{
	unsigned char cNum[ 6 ];
	unsigned char *cChar = cNum;

	sprintf( cNum, "%d", nInteger );
	cObjt = cStart + ( nCurrent - nAddress );

	while ( *cChar )
	{
		*cObjt = *cChar++;
		cObjt++;
		nCurrent++;
	}
}

void WriteInstruction( unsigned char *cCommand )
{
	NewLine();
	cObjt = cStart + ( nCurrent - nAddress );

	while ( *cCommand )
	{
		*cObjt = *cCommand++;
		cObjt++;
		nCurrent++;
	}
}

void WriteInstructionArg( unsigned char *cCommand, unsigned short int nNum )
{
	NewLine();
	cObjt = cStart + ( nCurrent - nAddress );

	while ( *cCommand )
	{
		if ( *cCommand == '?' )
		{
			WriteNumber( nNum );
			cCommand++;
		}
		else
		{
			*cObjt = *cCommand++;
			cObjt++;
			nCurrent++;
		}
	}
}

void WriteLabel( unsigned short int nWhere )
{
	unsigned char cLabel[ 7 ];
	unsigned char *cChar = cLabel;

	sprintf( cLabel, "%c%05d", nEvent + 'a', nWhere >> 2 );
	cObjt = cStart + ( nCurrent - nAddress );

	while ( *cChar )
	{
		*cObjt = *cChar++;
		cObjt++;
		nCurrent++;
	}
}

void NewLine( void )
{
	unsigned char cLine[ 9 ] = "\n       ";
	unsigned char *cChar = cLine;

	cObjt = cStart + ( nCurrent - nAddress );

	if ( nNextLabel > 0 )
	{
		sprintf( cLine, "\n%c%05d ", nEvent + 'a', nNextLabel >> 2 );
		nNextLabel = 0;
	}
	else
	{
		strcpy( cLine, "\n       " );
	}

	while ( *cChar )
	{
		*cObjt = *cChar++;
		cObjt++;
		nCurrent++;
	}
}

void Error( unsigned char *cMsg )
{
	fprintf( stderr, "%s on line %d\n", cMsg, nLine );
	nErrors++;
}
