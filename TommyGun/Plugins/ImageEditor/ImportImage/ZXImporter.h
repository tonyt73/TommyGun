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
#ifndef ZXImporterH
#define ZXImporterH
//---------------------------------------------------------------------------
#include "..\ZXImageInterface.h"
//---------------------------------------------------------------------------
class ZXImporter
{
private:

protected:
    ZXImageManager*             m_pImageManager;
    String                      m_sPaletteSignature;
    String                      m_sError;

            int     __fastcall  AddImage(const String& sType, const String& sName, int iWidth, int iHeight, bool bMasked, ZXImage** pImage = NULL);

public:
                    __fastcall  ZXImporter();
    virtual         __fastcall ~ZXImporter();

    virtual bool    __fastcall  ChoosePalette(TStrings* sFiles, TStrings* pPalettes) = 0;
    virtual bool    __fastcall  Import(TStrings* sFiles) = 0;

    __property  String          PaletteSignature    = { read = m_sPaletteSignature  , write = m_sPaletteSignature   };
    __property  ZXImageManager* ImageManager        = { read = m_pImageManager      , write = m_pImageManager       };
    __property  String          Error               = { read = m_sError                                             };
};
//---------------------------------------------------------------------------
#endif

