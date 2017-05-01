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
using namespace MSXPalette;
//---------------------------------------------------------------------------
TfrmMSXSpritePalette *frmMSXSpritePalette = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmMSXSpritePalette::TfrmMSXSpritePalette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmMSXSpritePalette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    OnUpdatePaletteGUI();
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    m_LastPanel = panColor15;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmMSXSpritePalette::Release(void)
{
    RL_HRESULT(S_OK);
    panPalette->Parent->RemoveControl(panPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmMSXSpritePalette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMSXSpritePalette::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    panPen->Color   = m_Palette.GetColor(1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMSXSpritePalette::panColor01Click(TObject *Sender)
{
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    m_LastPanel->BevelOuter = bvRaised;
    Panel->BevelOuter = bvLowered;
    m_LastPanel = Panel;
    m_Palette.SetColor(1, Panel->Color);
    OnUpdatePaletteGUI();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------


