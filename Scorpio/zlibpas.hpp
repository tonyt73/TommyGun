// CodeGear C++Builder
// Copyright (c) 1995, 2007 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Zlibpas.pas' rev: 11.00

#ifndef ZlibpasHPP
#define ZlibpasHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Zlibpas
{
//-- type declarations -------------------------------------------------------
typedef void * __fastcall (*TAlloc)(void * AppData, int Items, int Size);

typedef void __fastcall (*TFree)(void * AppData, void * Block);

#pragma pack(push,1)
struct TZStreamRec
{
	
public:
	char *next_in;
	int avail_in;
	int total_in;
	char *next_out;
	int avail_out;
	int total_out;
	char *msg;
	void *internal;
	TAlloc zalloc;
	TFree zfree;
	void *AppData;
	int data_type;
	int adler;
	int reserved;
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
#define zlib_version "1.2.3"
static const Shortint Z_NO_FLUSH = 0x0;
static const Shortint Z_PARTIAL_FLUSH = 0x1;
static const Shortint Z_SYNC_FLUSH = 0x2;
static const Shortint Z_FULL_FLUSH = 0x3;
static const Shortint Z_FINISH = 0x4;
static const Shortint Z_OK = 0x0;
static const Shortint Z_STREAM_END = 0x1;
static const Shortint Z_NEED_DICT = 0x2;
static const Shortint Z_ERRNO = -1;
static const Shortint Z_STREAM_ERROR = -2;
static const Shortint Z_DATA_ERROR = -3;
static const Shortint Z_MEM_ERROR = -4;
static const Shortint Z_BUF_ERROR = -5;
static const Shortint Z_VERSION_ERROR = -6;
static const Shortint Z_NO_COMPRESSION = 0x0;
static const Shortint Z_BEST_SPEED = 0x1;
static const Shortint Z_BEST_COMPRESSION = 0x9;
static const Shortint Z_DEFAULT_COMPRESSION = -1;
static const Shortint Z_FILTERED = 0x1;
static const Shortint Z_HUFFMAN_ONLY = 0x2;
static const Shortint Z_DEFAULT_STRATEGY = 0x0;
static const Shortint Z_BINARY = 0x0;
static const Shortint Z_ASCII = 0x1;
static const Shortint Z_UNKNOWN = 0x2;
static const Shortint Z_DEFLATED = 0x8;
extern PACKAGE char *_z_errmsg[10];
extern PACKAGE int __fastcall deflateInit_(TZStreamRec &strm, int level, char * version, int recsize);
extern PACKAGE int __fastcall deflate(TZStreamRec &strm, int flush);
extern PACKAGE int __fastcall deflateEnd(TZStreamRec &strm);
extern PACKAGE int __fastcall inflateInit_(TZStreamRec &strm, char * version, int recsize);
extern PACKAGE int __fastcall inflate(TZStreamRec &strm, int flush);
extern PACKAGE int __fastcall inflateEnd(TZStreamRec &strm);

}	/* namespace Zlibpas */
using namespace Zlibpas;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Zlibpas
