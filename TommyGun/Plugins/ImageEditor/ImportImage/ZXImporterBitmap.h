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
#ifndef ZXImporterBitmapH
#define ZXImporterBitmapH
//---------------------------------------------------------------------------
#include "ZXImporter.h"
//---------------------------------------------------------------------------
class ZXImporterBitmap : public ZXImporter
{
private:
    bool    __fastcall  AddSprites(TStrings* sFiles);
    bool    __fastcall  AddScreen(TStrings* sFiles);
    bool    __fastcall  AddTile(TStrings* sFiles);

public:
            __fastcall  ZXImporterBitmap();
            __fastcall ~ZXImporterBitmap();

    bool    __fastcall  ChoosePalette(TStrings* sFiles, TStrings* pPalettes);
    bool    __fastcall  Import(TStrings* sFiles);
};
//---------------------------------------------------------------------------
#endif

