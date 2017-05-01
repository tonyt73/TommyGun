#pragma link "TComboBoxUnit"
#pragma link "TEditUnit"
#pragma link "TRadioButtonUnit"
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
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageParser;
//---------------------------------------------------------------------------
TfrmImageParserOptions *frmImageParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmImageParserOptions::TfrmImageParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmImageParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    //m_ImageEditor.GetInterfaces(hParentInstance);
    //m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmImageParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    //panZXSpectrumPalette->Parent->RemoveControl(panZXSpectrumPalette);
    return hResult;
}
//---------------------------------------------------------------------------
/*HRESULT __fastcall TfrmImageParser::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}*/
//---------------------------------------------------------------------------

