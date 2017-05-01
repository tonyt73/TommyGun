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
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace StringTableParser;
//---------------------------------------------------------------------------
TfrmStringTableParserOptions *frmStringTableParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmStringTableParserOptions::TfrmStringTableParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmStringTableParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmStringTableParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------

