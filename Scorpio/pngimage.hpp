// CodeGear C++Builder
// Copyright (c) 1995, 2007 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Pngimage.pas' rev: 11.00

#ifndef PngimageHPP
#define PngimageHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Zlibpas.hpp>	// Pascal unit
#include <Pnglang.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Pngimage
{
//-- type declarations -------------------------------------------------------
typedef AnsiString pngimage__1[9];

class DELPHICLASS EPNGOutMemory;
class PASCALIMPLEMENTATION EPNGOutMemory : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGOutMemory(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGOutMemory(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGOutMemory(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGOutMemory(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGOutMemory(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGOutMemory(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGOutMemory(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGOutMemory(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGOutMemory(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPngError;
class PASCALIMPLEMENTATION EPngError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPngError(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPngError(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPngError(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPngError(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPngError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPngError(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPngError(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPngError(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPngError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPngUnexpectedEnd;
class PASCALIMPLEMENTATION EPngUnexpectedEnd : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPngUnexpectedEnd(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPngUnexpectedEnd(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPngUnexpectedEnd(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPngUnexpectedEnd(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPngUnexpectedEnd(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPngUnexpectedEnd(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPngUnexpectedEnd(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPngUnexpectedEnd(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPngUnexpectedEnd(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPngInvalidCRC;
class PASCALIMPLEMENTATION EPngInvalidCRC : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPngInvalidCRC(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPngInvalidCRC(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPngInvalidCRC(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPngInvalidCRC(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPngInvalidCRC(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPngInvalidCRC(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPngInvalidCRC(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPngInvalidCRC(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPngInvalidCRC(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPngInvalidIHDR;
class PASCALIMPLEMENTATION EPngInvalidIHDR : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPngInvalidIHDR(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPngInvalidIHDR(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPngInvalidIHDR(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPngInvalidIHDR(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPngInvalidIHDR(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPngInvalidIHDR(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPngInvalidIHDR(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPngInvalidIHDR(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPngInvalidIHDR(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGMissingMultipleIDAT;
class PASCALIMPLEMENTATION EPNGMissingMultipleIDAT : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGMissingMultipleIDAT(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGMissingMultipleIDAT(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGMissingMultipleIDAT(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGMissingMultipleIDAT(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGMissingMultipleIDAT(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGMissingMultipleIDAT(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGMissingMultipleIDAT(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGMissingMultipleIDAT(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGMissingMultipleIDAT(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGZLIBError;
class PASCALIMPLEMENTATION EPNGZLIBError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGZLIBError(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGZLIBError(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGZLIBError(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGZLIBError(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGZLIBError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGZLIBError(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGZLIBError(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGZLIBError(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGZLIBError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGInvalidPalette;
class PASCALIMPLEMENTATION EPNGInvalidPalette : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGInvalidPalette(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGInvalidPalette(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGInvalidPalette(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGInvalidPalette(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGInvalidPalette(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGInvalidPalette(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGInvalidPalette(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGInvalidPalette(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGInvalidPalette(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGInvalidFileHeader;
class PASCALIMPLEMENTATION EPNGInvalidFileHeader : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGInvalidFileHeader(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGInvalidFileHeader(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGInvalidFileHeader(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGInvalidFileHeader(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGInvalidFileHeader(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGInvalidFileHeader(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGInvalidFileHeader(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGInvalidFileHeader(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGInvalidFileHeader(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGIHDRNotFirst;
class PASCALIMPLEMENTATION EPNGIHDRNotFirst : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGIHDRNotFirst(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGIHDRNotFirst(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGIHDRNotFirst(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGIHDRNotFirst(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGIHDRNotFirst(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGIHDRNotFirst(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGIHDRNotFirst(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGIHDRNotFirst(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGIHDRNotFirst(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGNotExists;
class PASCALIMPLEMENTATION EPNGNotExists : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGNotExists(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGNotExists(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGNotExists(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGNotExists(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGNotExists(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGNotExists(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGNotExists(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGNotExists(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGNotExists(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGSizeExceeds;
class PASCALIMPLEMENTATION EPNGSizeExceeds : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGSizeExceeds(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGSizeExceeds(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGSizeExceeds(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGSizeExceeds(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGSizeExceeds(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGSizeExceeds(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGSizeExceeds(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGSizeExceeds(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGSizeExceeds(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGMissingPalette;
class PASCALIMPLEMENTATION EPNGMissingPalette : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGMissingPalette(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGMissingPalette(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGMissingPalette(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGMissingPalette(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGMissingPalette(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGMissingPalette(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGMissingPalette(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGMissingPalette(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGMissingPalette(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGUnknownCriticalChunk;
class PASCALIMPLEMENTATION EPNGUnknownCriticalChunk : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGUnknownCriticalChunk(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGUnknownCriticalChunk(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGUnknownCriticalChunk(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGUnknownCriticalChunk(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGUnknownCriticalChunk(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGUnknownCriticalChunk(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGUnknownCriticalChunk(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGUnknownCriticalChunk(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGUnknownCriticalChunk(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGUnknownCompression;
class PASCALIMPLEMENTATION EPNGUnknownCompression : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGUnknownCompression(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGUnknownCompression(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGUnknownCompression(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGUnknownCompression(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGUnknownCompression(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGUnknownCompression(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGUnknownCompression(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGUnknownCompression(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGUnknownCompression(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGUnknownInterlace;
class PASCALIMPLEMENTATION EPNGUnknownInterlace : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGUnknownInterlace(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGUnknownInterlace(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGUnknownInterlace(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGUnknownInterlace(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGUnknownInterlace(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGUnknownInterlace(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGUnknownInterlace(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGUnknownInterlace(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGUnknownInterlace(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGNoImageData;
class PASCALIMPLEMENTATION EPNGNoImageData : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGNoImageData(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGNoImageData(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGNoImageData(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGNoImageData(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGNoImageData(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGNoImageData(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGNoImageData(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGNoImageData(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGNoImageData(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGCouldNotLoadResource;
class PASCALIMPLEMENTATION EPNGCouldNotLoadResource : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGCouldNotLoadResource(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGCouldNotLoadResource(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGCouldNotLoadResource(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGCouldNotLoadResource(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGCouldNotLoadResource(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGCouldNotLoadResource(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGCouldNotLoadResource(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGCouldNotLoadResource(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGCouldNotLoadResource(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGCannotChangeTransparent;
class PASCALIMPLEMENTATION EPNGCannotChangeTransparent : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGCannotChangeTransparent(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGCannotChangeTransparent(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGCannotChangeTransparent(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGCannotChangeTransparent(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGCannotChangeTransparent(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGCannotChangeTransparent(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGCannotChangeTransparent(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGCannotChangeTransparent(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGCannotChangeTransparent(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGHeaderNotPresent;
class PASCALIMPLEMENTATION EPNGHeaderNotPresent : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGHeaderNotPresent(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGHeaderNotPresent(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGHeaderNotPresent(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGHeaderNotPresent(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGHeaderNotPresent(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGHeaderNotPresent(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGHeaderNotPresent(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGHeaderNotPresent(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGHeaderNotPresent(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGInvalidNewSize;
class PASCALIMPLEMENTATION EPNGInvalidNewSize : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGInvalidNewSize(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGInvalidNewSize(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGInvalidNewSize(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGInvalidNewSize(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGInvalidNewSize(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGInvalidNewSize(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGInvalidNewSize(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGInvalidNewSize(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGInvalidNewSize(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPNGInvalidSpec;
class PASCALIMPLEMENTATION EPNGInvalidSpec : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EPNGInvalidSpec(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPNGInvalidSpec(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPNGInvalidSpec(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPNGInvalidSpec(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPNGInvalidSpec(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPNGInvalidSpec(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPNGInvalidSpec(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPNGInvalidSpec(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPNGInvalidSpec(void) { }
	#pragma option pop
	
};


typedef tagRGBTRIPLE TRGBLine[65536];

typedef TRGBLine *pRGBLine;

#pragma pack(push,1)
struct TMAXBITMAPINFO
{
	
public:
	tagBITMAPINFOHEADER bmiHeader;
	tagRGBQUAD bmiColors[256];
} ;
#pragma pack(pop)

#pragma option push -b-
enum TPNGTransparencyMode { ptmNone, ptmBit, ptmPartial };
#pragma option pop

typedef unsigned *pCardinal;

struct TRGBPixel;
typedef TRGBPixel *pRGBPixel;

#pragma pack(push,1)
struct TRGBPixel
{
	
public:
	Byte B;
	Byte G;
	Byte R;
} ;
#pragma pack(pop)

typedef Byte TByteArray[65536];

typedef TByteArray *pByteArray;

typedef void *TPointerArray[65536];

typedef TPointerArray *pPointerArray;

class DELPHICLASS TPNGPointerList;
class DELPHICLASS TPNGObject;
#pragma option push -b-
enum TFilter { pfNone, pfSub, pfUp, pfAverage, pfPaeth };
#pragma option pop

typedef Set<TFilter, pfNone, pfPaeth>  TFilters;

typedef Shortint TCompressionLevel;

#pragma option push -b-
enum TInterlaceMethod { imNone, imAdam7 };
#pragma option pop

class DELPHICLASS TPNGList;
class PASCALIMPLEMENTATION TPNGPointerList : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	TPNGObject* fOwner;
	unsigned fCount;
	TPointerArray *fMemory;
	void * __fastcall GetItem(unsigned Index);
	void __fastcall SetItem(unsigned Index, const void * Value);
	
protected:
	virtual void * __fastcall Remove(void * Value);
	void __fastcall Insert(void * Value, unsigned Position);
	void __fastcall Add(void * Value);
	__property void * Item[unsigned Index] = {read=GetItem, write=SetItem};
	void __fastcall SetSize(const unsigned Size);
	__property TPNGObject* Owner = {read=fOwner};
	
public:
	__property unsigned Count = {read=fCount, write=SetSize, nodefault};
	__fastcall TPNGPointerList(TPNGObject* AOwner);
	__fastcall virtual ~TPNGPointerList(void);
};


class DELPHICLASS TChunk;
typedef TMetaClass* TChunkClass;

class PASCALIMPLEMENTATION TPNGList : public TPNGPointerList 
{
	typedef TPNGPointerList inherited;
	
private:
	HIDESBASE TChunk* __fastcall GetItem(unsigned Index);
	
public:
	TChunk* __fastcall FindChunk(TMetaClass* ChunkClass);
	void __fastcall RemoveChunk(TChunk* Chunk)/* overload */;
	HIDESBASE TChunk* __fastcall Add(TMetaClass* ChunkClass);
	TChunk* __fastcall ItemFromClass(TMetaClass* ChunkClass);
	__property TChunk* Item[unsigned Index] = {read=GetItem};
public:
	#pragma option push -w-inl
	/* TPNGPointerList.Create */ inline __fastcall TPNGList(TPNGObject* AOwner) : TPNGPointerList(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPNGPointerList.Destroy */ inline __fastcall virtual ~TPNGList(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkpHYs;
class DELPHICLASS TChunkIHDR;
class PASCALIMPLEMENTATION TPNGObject : public Graphics::TGraphic 
{
	typedef Graphics::TGraphic inherited;
	
protected:
	Byte InverseGamma[256];
	void __fastcall InitializeGamma(void);
	
private:
	Graphics::TCanvas* fCanvas;
	TFilters fFilters;
	TCompressionLevel fCompressionLevel;
	int fMaxIdatSize;
	TInterlaceMethod fInterlaceMethod;
	TPNGList* fChunkList;
	void __fastcall ClearChunks(void);
	bool __fastcall HeaderPresent(void);
	void __fastcall GetPixelInfo(unsigned &LineSize, unsigned &Offset);
	void __fastcall SetMaxIdatSize(const int Value);
	pByteArray __fastcall GetAlphaScanline(const int LineIndex);
	void * __fastcall GetScanline(const int LineIndex);
	void * __fastcall GetExtraScanline(const int LineIndex);
	TChunkpHYs* __fastcall GetPixelInformation(void);
	TPNGTransparencyMode __fastcall GetTransparencyMode(void);
	Graphics::TColor __fastcall GetTransparentColor(void);
	void __fastcall SetTransparentColor(const Graphics::TColor Value);
	AnsiString __fastcall GetLibraryVersion();
	
protected:
	bool BeingCreated;
	virtual HPALETTE __fastcall GetPalette(void);
	virtual void __fastcall SetPalette(HPALETTE Value);
	void __fastcall DoSetPalette(HPALETTE Value, const bool UpdateColors);
	virtual int __fastcall GetWidth(void);
	virtual int __fastcall GetHeight(void);
	virtual void __fastcall SetWidth(int Value);
	virtual void __fastcall SetHeight(int Value);
	void __fastcall AssignPNG(TPNGObject* Source);
	virtual bool __fastcall GetEmpty(void);
	TChunkIHDR* __fastcall GetHeader(void);
	void __fastcall DrawPartialTrans(HDC DC, const Types::TRect &Rect);
	virtual bool __fastcall GetTransparent(void);
	virtual Graphics::TColor __fastcall GetPixels(const int X, const int Y);
	virtual void __fastcall SetPixels(const int X, const int Y, const Graphics::TColor Value);
	
public:
	Byte GammaTable[256];
	void __fastcall Resize(const int CX, const int CY);
	void __fastcall CreateAlpha(void);
	void __fastcall RemoveTransparency(void);
	__property Graphics::TColor TransparentColor = {read=GetTransparentColor, write=SetTransparentColor, nodefault};
	void __fastcall AddtEXt(const AnsiString Keyword, const AnsiString Text);
	void __fastcall AddzTXt(const AnsiString Keyword, const AnsiString Text);
	virtual void __fastcall SaveToClipboardFormat(Word &AFormat, unsigned &AData, HPALETTE &APalette);
	virtual void __fastcall LoadFromClipboardFormat(Word AFormat, unsigned AData, HPALETTE APalette);
	void __fastcall RaiseError(TMetaClass* ExceptionClass, AnsiString Text);
	__property void * Scanline[int Index] = {read=GetScanline};
	__property void * ExtraScanline[int Index] = {read=GetExtraScanline};
	bool __fastcall HasPixelInformation(void);
	__property TChunkpHYs* PixelInformation = {read=GetPixelInformation};
	__property pByteArray AlphaScanline[int Index] = {read=GetAlphaScanline};
	void __fastcall DrawUsingPixelInformation(Graphics::TCanvas* Canvas, const Types::TPoint &Point);
	__property Graphics::TCanvas* Canvas = {read=fCanvas};
	__property TChunkIHDR* Header = {read=GetHeader};
	__property TPNGTransparencyMode TransparencyMode = {read=GetTransparencyMode, nodefault};
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	void __fastcall AssignHandle(HBITMAP Handle, bool Transparent, unsigned TransparentColor);
	virtual void __fastcall Draw(Graphics::TCanvas* ACanvas, const Types::TRect &Rect);
	__property int Width = {read=GetWidth, nodefault};
	__property int Height = {read=GetHeight, nodefault};
	__property TInterlaceMethod InterlaceMethod = {read=fInterlaceMethod, write=fInterlaceMethod, nodefault};
	__property TFilters Filters = {read=fFilters, write=fFilters, nodefault};
	__property int MaxIdatSize = {read=fMaxIdatSize, write=SetMaxIdatSize, nodefault};
	__property bool Empty = {read=GetEmpty, nodefault};
	__property TCompressionLevel CompressionLevel = {read=fCompressionLevel, write=fCompressionLevel, nodefault};
	__property TPNGList* Chunks = {read=fChunkList};
	__fastcall virtual TPNGObject(void);
	__fastcall TPNGObject(unsigned ColorType, unsigned Bitdepth, int cx, int cy);
	__fastcall virtual ~TPNGObject(void);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall LoadFromResourceName(unsigned Instance, const AnsiString Name);
	void __fastcall LoadFromResourceID(unsigned Instance, int ResID);
	__property Graphics::TColor Pixels[int X][int Y] = {read=GetPixels, write=SetPixels};
	__property AnsiString Version = {read=GetLibraryVersion};
};



typedef char TChunkName[4];

class PASCALIMPLEMENTATION TChunk : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	void *fData;
	unsigned fDataSize;
	TPNGObject* fOwner;
	char fName[4];
	TChunkIHDR* __fastcall GetHeader(void);
	int __fastcall GetIndex(void);
	/* virtual class method */ virtual AnsiString __fastcall GetName(TMetaClass* vmt);
	AnsiString __fastcall GetChunkName();
	
public:
	__property int Index = {read=GetIndex, nodefault};
	__property TChunkIHDR* Header = {read=GetHeader};
	void __fastcall ResizeData(const unsigned NewSize);
	__property void * Data = {read=fData};
	__property unsigned DataSize = {read=fDataSize, nodefault};
	virtual void __fastcall Assign(TChunk* Source);
	__property TPNGObject* Owner = {read=fOwner};
	__fastcall virtual TChunk(TPNGObject* Owner);
	__fastcall virtual ~TChunk(void);
	__property AnsiString Name = {read=GetChunkName};
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	bool __fastcall SaveData(Classes::TStream* Stream);
	virtual bool __fastcall SaveToStream(Classes::TStream* Stream);
};


class DELPHICLASS TChunkIEND;
class PASCALIMPLEMENTATION TChunkIEND : public TChunk 
{
	typedef TChunk inherited;
	
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkIEND(TPNGObject* Owner) : TChunk(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkIEND(void) { }
	#pragma option pop
	
};


struct TIHDRData;
typedef TIHDRData *pIHDRData;

#pragma pack(push,1)
struct TIHDRData
{
	
public:
	unsigned Width;
	unsigned Height;
	Byte BitDepth;
	Byte ColorType;
	Byte CompressionMethod;
	Byte FilterMethod;
	Byte InterlaceMethod;
} ;
#pragma pack(pop)

class PASCALIMPLEMENTATION TChunkIHDR : public TChunk 
{
	typedef TChunk inherited;
	
private:
	HBITMAP ImageHandle;
	HDC ImageDC;
	HPALETTE ImagePalette;
	bool HasPalette;
	TMAXBITMAPINFO BitmapInfo;
	void *ExtraImageData;
	void *ImageData;
	void *ImageAlpha;
	TIHDRData IHDRData;
	
protected:
	int BytesPerRow;
	HPALETTE __fastcall CreateGrayscalePalette(int Bitdepth);
	void __fastcall PaletteToDIB(HPALETTE Palette);
	void __fastcall PrepareImageData(void);
	void __fastcall FreeImageData(void);
	
public:
	__property HBITMAP ImageHandleValue = {read=ImageHandle, nodefault};
	__property unsigned Width = {read=IHDRData.Width, write=IHDRData.Width, nodefault};
	__property unsigned Height = {read=IHDRData.Height, write=IHDRData.Height, nodefault};
	__property Byte BitDepth = {read=IHDRData.BitDepth, write=IHDRData.BitDepth, nodefault};
	__property Byte ColorType = {read=IHDRData.ColorType, write=IHDRData.ColorType, nodefault};
	__property Byte CompressionMethod = {read=IHDRData.CompressionMethod, write=IHDRData.CompressionMethod, nodefault};
	__property Byte FilterMethod = {read=IHDRData.FilterMethod, write=IHDRData.FilterMethod, nodefault};
	__property Byte InterlaceMethod = {read=IHDRData.InterlaceMethod, write=IHDRData.InterlaceMethod, nodefault};
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	virtual bool __fastcall SaveToStream(Classes::TStream* Stream);
	__fastcall virtual TChunkIHDR(TPNGObject* Owner);
	__fastcall virtual ~TChunkIHDR(void);
	virtual void __fastcall Assign(TChunk* Source);
};


#pragma option push -b-
enum TUnitType { utUnknown, utMeter };
#pragma option pop

typedef TUnitType *pUnitType;

class PASCALIMPLEMENTATION TChunkpHYs : public TChunk 
{
	typedef TChunk inherited;
	
private:
	unsigned fPPUnitX;
	unsigned fPPUnitY;
	TUnitType fUnit;
	
public:
	__property unsigned PPUnitX = {read=fPPUnitX, write=fPPUnitX, nodefault};
	__property unsigned PPUnitY = {read=fPPUnitY, write=fPPUnitY, nodefault};
	__property TUnitType UnitType = {read=fUnit, write=fUnit, nodefault};
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	virtual bool __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall Assign(TChunk* Source);
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkpHYs(TPNGObject* Owner) : TChunk(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkpHYs(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkgAMA;
class PASCALIMPLEMENTATION TChunkgAMA : public TChunk 
{
	typedef TChunk inherited;
	
private:
	unsigned __fastcall GetValue(void);
	void __fastcall SetValue(const unsigned Value);
	
public:
	__property unsigned Gamma = {read=GetValue, write=SetValue, nodefault};
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	__fastcall virtual TChunkgAMA(TPNGObject* Owner);
	virtual void __fastcall Assign(TChunk* Source);
public:
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkgAMA(void) { }
	#pragma option pop
	
};


#pragma pack(push,1)
struct TZStreamRec2
{
	
public:
	Zlibpas::TZStreamRec ZLIB;
	void *Data;
	Classes::TStream* fStream;
} ;
#pragma pack(pop)

class DELPHICLASS TChunkPLTE;
class PASCALIMPLEMENTATION TChunkPLTE : public TChunk 
{
	typedef TChunk inherited;
	
protected:
	int fCount;
	
private:
	tagRGBQUAD __fastcall GetPaletteItem(Byte Index);
	
public:
	__property tagRGBQUAD Item[Byte Index] = {read=GetPaletteItem};
	__property int Count = {read=fCount, nodefault};
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	virtual bool __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall Assign(TChunk* Source);
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkPLTE(TPNGObject* Owner) : TChunk(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkPLTE(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunktRNS;
class PASCALIMPLEMENTATION TChunktRNS : public TChunk 
{
	typedef TChunk inherited;
	
private:
	bool fBitTransparency;
	unsigned __fastcall GetTransparentColor(void);
	void __fastcall SetTransparentColor(const unsigned Value);
	
public:
	Byte PaletteValues[256];
	__property bool BitTransparency = {read=fBitTransparency, nodefault};
	__property unsigned TransparentColor = {read=GetTransparentColor, write=SetTransparentColor, nodefault};
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	virtual bool __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall Assign(TChunk* Source);
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunktRNS(TPNGObject* Owner) : TChunk(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunktRNS(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkIDAT;
class PASCALIMPLEMENTATION TChunkIDAT : public TChunk 
{
	typedef TChunk inherited;
	
private:
	TChunkIHDR* Header;
	int ImageWidth;
	int ImageHeight;
	unsigned Row_Bytes;
	unsigned Offset;
	TByteArray *Encode_Buffer[6];
	TByteArray *Row_Buffer[2];
	bool RowUsed;
	int EndPos;
	void __fastcall FilterRow(void);
	Byte __fastcall FilterToEncode(void);
	int __fastcall IDATZlibRead(TZStreamRec2 &ZLIBStream, void * Buffer, int Count, int &EndPos, unsigned &crcfile);
	void __fastcall IDATZlibWrite(TZStreamRec2 &ZLIBStream, void * Buffer, const unsigned Length);
	void __fastcall FinishIDATZlib(TZStreamRec2 &ZLIBStream);
	void __fastcall PreparePalette(void);
	
protected:
	void __fastcall DecodeInterlacedAdam7(Classes::TStream* Stream, TZStreamRec2 &ZLIBStream, const int Size, unsigned &crcfile);
	void __fastcall DecodeNonInterlaced(Classes::TStream* Stream, TZStreamRec2 &ZLIBStream, const int Size, unsigned &crcfile);
	void __fastcall EncodeNonInterlaced(Classes::TStream* Stream, TZStreamRec2 &ZLIBStream);
	void __fastcall EncodeInterlacedAdam7(Classes::TStream* Stream, TZStreamRec2 &ZLIBStream);
	void __fastcall CopyNonInterlacedRGB8(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyNonInterlacedRGB16(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyNonInterlacedPalette148(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyNonInterlacedPalette2(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyNonInterlacedGray2(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyNonInterlacedGrayscale16(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyNonInterlacedRGBAlpha8(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyNonInterlacedRGBAlpha16(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyNonInterlacedGrayscaleAlpha8(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyNonInterlacedGrayscaleAlpha16(char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedRGB8(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedRGB16(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedPalette148(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedPalette2(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedGray2(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedGrayscale16(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedRGBAlpha8(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedRGBAlpha16(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedGrayscaleAlpha8(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall CopyInterlacedGrayscaleAlpha16(const Byte Pass, char * Src, char * Dest, char * Trans, char * Extra);
	void __fastcall EncodeNonInterlacedRGB8(char * Src, char * Dest, char * Trans);
	void __fastcall EncodeNonInterlacedRGB16(char * Src, char * Dest, char * Trans);
	void __fastcall EncodeNonInterlacedGrayscale16(char * Src, char * Dest, char * Trans);
	void __fastcall EncodeNonInterlacedPalette148(char * Src, char * Dest, char * Trans);
	void __fastcall EncodeNonInterlacedRGBAlpha8(char * Src, char * Dest, char * Trans);
	void __fastcall EncodeNonInterlacedRGBAlpha16(char * Src, char * Dest, char * Trans);
	void __fastcall EncodeNonInterlacedGrayscaleAlpha8(char * Src, char * Dest, char * Trans);
	void __fastcall EncodeNonInterlacedGrayscaleAlpha16(char * Src, char * Dest, char * Trans);
	void __fastcall EncodeInterlacedRGB8(const Byte Pass, char * Src, char * Dest, char * Trans);
	void __fastcall EncodeInterlacedRGB16(const Byte Pass, char * Src, char * Dest, char * Trans);
	void __fastcall EncodeInterlacedPalette148(const Byte Pass, char * Src, char * Dest, char * Trans);
	void __fastcall EncodeInterlacedGrayscale16(const Byte Pass, char * Src, char * Dest, char * Trans);
	void __fastcall EncodeInterlacedRGBAlpha8(const Byte Pass, char * Src, char * Dest, char * Trans);
	void __fastcall EncodeInterlacedRGBAlpha16(const Byte Pass, char * Src, char * Dest, char * Trans);
	void __fastcall EncodeInterlacedGrayscaleAlpha8(const Byte Pass, char * Src, char * Dest, char * Trans);
	void __fastcall EncodeInterlacedGrayscaleAlpha16(const Byte Pass, char * Src, char * Dest, char * Trans);
	
public:
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	virtual bool __fastcall SaveToStream(Classes::TStream* Stream);
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkIDAT(TPNGObject* Owner) : TChunk(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkIDAT(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunktIME;
class PASCALIMPLEMENTATION TChunktIME : public TChunk 
{
	typedef TChunk inherited;
	
private:
	Word fYear;
	Byte fMonth;
	Byte fDay;
	Byte fHour;
	Byte fMinute;
	Byte fSecond;
	
public:
	__property Word Year = {read=fYear, write=fYear, nodefault};
	__property Byte Month = {read=fMonth, write=fMonth, nodefault};
	__property Byte Day = {read=fDay, write=fDay, nodefault};
	__property Byte Hour = {read=fHour, write=fHour, nodefault};
	__property Byte Minute = {read=fMinute, write=fMinute, nodefault};
	__property Byte Second = {read=fSecond, write=fSecond, nodefault};
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	virtual bool __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall Assign(TChunk* Source);
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunktIME(TPNGObject* Owner) : TChunk(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunktIME(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunktEXt;
class PASCALIMPLEMENTATION TChunktEXt : public TChunk 
{
	typedef TChunk inherited;
	
private:
	AnsiString fKeyword;
	AnsiString fText;
	
public:
	__property AnsiString Keyword = {read=fKeyword, write=fKeyword};
	__property AnsiString Text = {read=fText, write=fText};
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	virtual bool __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall Assign(TChunk* Source);
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunktEXt(TPNGObject* Owner) : TChunk(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunktEXt(void) { }
	#pragma option pop
	
};


class DELPHICLASS TChunkzTXt;
class PASCALIMPLEMENTATION TChunkzTXt : public TChunktEXt 
{
	typedef TChunktEXt inherited;
	
public:
	virtual bool __fastcall LoadFromStream(Classes::TStream* Stream, char const * ChunkName, int Size);
	virtual bool __fastcall SaveToStream(Classes::TStream* Stream);
public:
	#pragma option push -w-inl
	/* TChunk.Create */ inline __fastcall virtual TChunkzTXt(TPNGObject* Owner) : TChunktEXt(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TChunk.Destroy */ inline __fastcall virtual ~TChunkzTXt(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define LibraryVersion "1.564"
extern PACKAGE AnsiString ZLIBErrors[9];
static const Shortint Z_NO_FLUSH = 0x0;
static const Shortint Z_FINISH = 0x4;
static const Shortint Z_STREAM_END = 0x1;
static const Shortint FILTER_NONE = 0x0;
static const Shortint FILTER_SUB = 0x1;
static const Shortint FILTER_UP = 0x2;
static const Shortint FILTER_AVERAGE = 0x3;
static const Shortint FILTER_PAETH = 0x4;
static const Shortint COLOR_GRAYSCALE = 0x0;
static const Shortint COLOR_RGB = 0x2;
static const Shortint COLOR_PALETTE = 0x3;
static const Shortint COLOR_GRAYSCALEALPHA = 0x4;
static const Shortint COLOR_RGBALPHA = 0x6;
extern PACKAGE unsigned __fastcall update_crc(unsigned crc, pByteArray buf, int len);
extern PACKAGE int __fastcall ByteSwap(const int a);
extern PACKAGE void __fastcall RegisterChunk(TMetaClass* ChunkClass);

}	/* namespace Pngimage */
using namespace Pngimage;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Pngimage
