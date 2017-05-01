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
#pragma resource "*.dfm"
#pragma link "KXmlInfo"
#pragma link "KShadePanel"
#pragma link "TScrollBox"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace TiledMapParser;
//---------------------------------------------------------------------------
TfrmTiledMapParserOptions *frmTiledMapParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmTiledMapParserOptions::TfrmTiledMapParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmTiledMapParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmTiledMapParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------

