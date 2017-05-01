/*---------------------------------------------------------------------------

    (c) 2004 Scorpio Software
        19 Wittama Drive
        Glenmore Park
        Sydney NSW 2745
        Australia

-----------------------------------------------------------------------------

    $Workfile::                                                           $
    $Revision::                                                           $
        $Date::                                                           $
      $Author::                                                           $

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef ZXImporterSevenuPH
#define ZXImporterSevenuPH
//---------------------------------------------------------------------------
#include "ZXImporterSpectrum.h"
//---------------------------------------------------------------------------
class ZXImporterSevenuP : public ZXImporterSpectrum
{
private:
#pragma pack(push, 1);
    typedef struct
    {
        char            Signature[4];
        unsigned char   MajorVersion;
        unsigned char   MinorVersion;
        unsigned short  Property1;
        unsigned short  Frames;
        unsigned short  Width;
        unsigned short  Height;
    } TSevenuPHeader;
#pragma pack(pop);
    bool    __fastcall  Load(const String& sFilename);
    
public:
            __fastcall  ZXImporterSevenuP();

    bool    __fastcall  Import(TStrings* sFiles);
};
//---------------------------------------------------------------------------
#endif

