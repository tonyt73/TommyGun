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
#pragma link "KSpinEdit"
#pragma link "DirDialog"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace AGDParser;
//---------------------------------------------------------------------------
TfrmAGDParserOptions *frmAGDParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmAGDParserOptions::TfrmAGDParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
, m_Initialized(false)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmAGDParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    m_Initialized = true;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmAGDParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------


