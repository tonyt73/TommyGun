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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXImporter::ZXImporter()
: m_pImageManager(NULL)
, m_sError("Importer module failed to supply an error message")
{
}
//---------------------------------------------------------------------------
__fastcall ZXImporter::~ZXImporter()
{
}
//---------------------------------------------------------------------------
int __fastcall ZXImporter::AddImage(const String& sType, const String& sName, int iWidth, int iHeight, bool bMasked, ZXImage** pImage)
{
    int iImage = -1;
    if (true == SAFE_PTR(m_pImageManager))
    {
        iImage = m_pImageManager->AddImage(sType, m_sPaletteSignature, sName, iWidth, iHeight, bMasked, pImage);
    }
    return iImage;
}
//---------------------------------------------------------------------------

