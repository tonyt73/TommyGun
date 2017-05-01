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
#ifndef ZXImporterSpectrumH
#define ZXImporterSpectrumH
//---------------------------------------------------------------------------
#include "ZXImporter.h"
//---------------------------------------------------------------------------
class ZXImporterSpectrum : public ZXImporter
{
protected:
    //void    __fastcall  FlipBits(unsigned char* Pixels, unsigned int iSize);

public:
            __fastcall  ZXImporterSpectrum();
    virtual __fastcall ~ZXImporterSpectrum();

    bool    __fastcall  ChoosePalette(TStrings* sFiles, TStrings* pPalettes);
};
//---------------------------------------------------------------------------
#endif

