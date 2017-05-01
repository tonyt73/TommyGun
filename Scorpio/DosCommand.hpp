// CodeGear C++Builder
// Copyright (c) 1995, 2007 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Doscommand.pas' rev: 11.00

#ifndef DoscommandHPP
#define DoscommandHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Extctrls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Doscommand
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TCreatePipeError;
class PASCALIMPLEMENTATION TCreatePipeError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall TCreatePipeError(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall TCreatePipeError(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall TCreatePipeError(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall TCreatePipeError(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall TCreatePipeError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall TCreatePipeError(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall TCreatePipeError(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall TCreatePipeError(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TCreatePipeError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TCreateProcessError;
class PASCALIMPLEMENTATION TCreateProcessError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall TCreateProcessError(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall TCreateProcessError(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall TCreateProcessError(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall TCreateProcessError(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall TCreateProcessError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall TCreateProcessError(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall TCreateProcessError(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall TCreateProcessError(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TCreateProcessError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TOutputType { otEntireLine, otBeginningOfLine };
#pragma option pop

class DELPHICLASS TProcessTimer;
class PASCALIMPLEMENTATION TProcessTimer : public Extctrls::TTimer 
{
	typedef Extctrls::TTimer inherited;
	
private:
	int FSinceBeginning;
	int FSinceLastOutput;
	void __fastcall MyTimer(System::TObject* Sender);
	
public:
	__fastcall virtual TProcessTimer(Classes::TComponent* AOwner);
	void __fastcall Beginning(void);
	void __fastcall NewOutput(void);
	void __fastcall Ending(void);
	__property int SinceBeginning = {read=FSinceBeginning, nodefault};
	__property int SinceLastOutput = {read=FSinceLastOutput, nodefault};
public:
	#pragma option push -w-inl
	/* TTimer.Destroy */ inline __fastcall virtual ~TProcessTimer(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TNewLineEvent)(System::TObject* Sender, AnsiString NewLine, TOutputType OutputType);

typedef void __fastcall (__closure *TTerminatedEvent)(System::TObject* Sender, int ExitCode);

class DELPHICLASS TDosThread;
class PASCALIMPLEMENTATION TDosThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	System::TObject* FOwner;
	AnsiString FCommandLine;
	Classes::TStringList* FLines;
	Classes::TStrings* FOutputLines;
	bool FInputToOutput;
	TProcessTimer* FTimer;
	int FMaxTimeAfterBeginning;
	int FMaxTimeAfterLastOutput;
	TNewLineEvent FOnNewLine;
	TTerminatedEvent FOnTerminated;
	TCreatePipeError* FCreatePipeError;
	TCreateProcessError* FCreateProcessError;
	int FPriority;
	int FExitCode;
	void __fastcall FExecute(void);
	
protected:
	virtual void __fastcall Execute(void);
	
public:
	Classes::TStringList* InputLines;
	__fastcall TDosThread(System::TObject* AOwner, AnsiString Cl, Classes::TStringList* L, Classes::TStrings* Ol, TProcessTimer* t, int mtab, int mtalo, TNewLineEvent Onl, TTerminatedEvent Ot, int p, bool ito);
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TDosThread(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDosCommand;
class PASCALIMPLEMENTATION TDosCommand : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Classes::TComponent* FOwner;
	AnsiString FCommandLine;
	Classes::TStringList* FLines;
	Classes::TStrings* FOutputLines;
	bool FInputToOutput;
	TNewLineEvent FOnNewLine;
	TTerminatedEvent FOnTerminated;
	TDosThread* FThread;
	TProcessTimer* FTimer;
	int FMaxTimeAfterBeginning;
	int FMaxTimeAfterLastOutput;
	int FPriority;
	int FExitCode;
	void __fastcall SetOutputLines(Classes::TStrings* Value);
	
public:
	__fastcall virtual TDosCommand(Classes::TComponent* AOwner);
	void __fastcall Execute(void);
	void __fastcall Stop(void);
	void __fastcall SendLine(AnsiString Value, bool Eol);
	__property Classes::TStrings* OutputLines = {read=FOutputLines, write=SetOutputLines};
	__property Classes::TStringList* Lines = {read=FLines};
	__property int Priority = {read=FPriority, write=FPriority, nodefault};
	__property int ExitCode = {read=FExitCode, nodefault};
	
__published:
	__property AnsiString CommandLine = {read=FCommandLine, write=FCommandLine};
	__property TNewLineEvent OnNewLine = {read=FOnNewLine, write=FOnNewLine};
	__property TTerminatedEvent OnTerminated = {read=FOnTerminated, write=FOnTerminated};
	__property bool InputToOutput = {read=FInputToOutput, write=FInputToOutput, nodefault};
	__property int MaxTimeAfterBeginning = {read=FMaxTimeAfterBeginning, write=FMaxTimeAfterBeginning, nodefault};
	__property int MaxTimeAfterLastOutput = {read=FMaxTimeAfterLastOutput, write=FMaxTimeAfterLastOutput, nodefault};
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TDosCommand(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Doscommand */
using namespace Doscommand;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Doscommand
