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
#ifndef ZXImporterZXGH
#define ZXImporterZXGH
//---------------------------------------------------------------------------
#include "ZXImporterSpectrum.h"
//---------------------------------------------------------------------------
class ZXImporterZXG : public ZXImporterSpectrum
{
public:
            __fastcall  ZXImporterZXG();
            __fastcall ~ZXImporterZXG();

    bool    __fastcall  Import(TStrings* sFiles);
};
//---------------------------------------------------------------------------
#endif

