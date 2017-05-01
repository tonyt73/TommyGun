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
#ifndef ZXImporterSNASCRH
#define ZXImporterSNASCRH
//---------------------------------------------------------------------------
#include "ZXImporterSpectrum.h"
//---------------------------------------------------------------------------
class ZXImporterZXScreen : public ZXImporterSpectrum
{
private:
            __fastcall  ZXImporterZXScreen();
            
protected:
    int                 m_iFileHeaderOffset;    // size of any file headers
    int                 m_iFileSize;            // size of file to load

public:
            __fastcall  ZXImporterZXScreen(int iFileHeaderOffset, int iFileSize);

    bool    __fastcall  Import(TStrings* sFiles);
};
//---------------------------------------------------------------------------
class ZXImporterSNA : public ZXImporterZXScreen
{
public:
            __fastcall  ZXImporterSNA();
};
//---------------------------------------------------------------------------
class ZXImporterSCR : public ZXImporterZXScreen
{
public:
            __fastcall  ZXImporterSCR();
};
//---------------------------------------------------------------------------
#endif

