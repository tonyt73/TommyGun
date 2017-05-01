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
using namespace Vic20Palette;
//---------------------------------------------------------------------------
TfrmVic20MultiColorDHPalette *frmVic20MultiColorDHPalette = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmVic20MultiColorDHPalette::TfrmVic20MultiColorDHPalette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmVic20MultiColorDHPalette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);

    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    OnUpdatePaletteGUI();
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    RefreshPanels();
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmVic20MultiColorDHPalette::Release(void)
{
    RL_HRESULT(S_OK);
    panPalette->Parent->RemoveControl(panPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmVic20MultiColorDHPalette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmVic20MultiColorDHPalette::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    panVicBackground->BevelOuter = panVicBackground->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panVicBorder->BevelOuter     = panVicBorder->Tag     == m_Palette.Color ? bvLowered : bvRaised;
    panVicCharacter->BevelOuter  = panVicCharacter->Tag  == m_Palette.Color ? bvLowered : bvRaised;
    panVicAuxiliary->BevelOuter  = panVicAuxiliary->Tag  == m_Palette.Color ? bvLowered : bvRaised;
}
//---------------------------------------------------------------------------
void __fastcall TfrmVic20MultiColorDHPalette::lblVicBackgroundClick(TObject *Sender)
{
    TLabel* Label = dynamic_cast<TLabel*>(Sender);
    if (true == SAFE_PTR(Label) && true == dlgCommodoreColors->Execute(Label->Tag))
    {
        switch(Label->Tag)
        {
            case vcBackground:
            m_Palette.Background = dlgCommodoreColors->Color;
            panVicBackground->Color = m_Palette.GetColor(dlgCommodoreColors->Color);
            break;
            case vcBorder:
            m_Palette.Border = dlgCommodoreColors->Color;
            panVicBorder->Color = m_Palette.GetColor(dlgCommodoreColors->Color);
            break;
            case vcCharacter:
            m_Palette.Character = dlgCommodoreColors->Color;
            panVicCharacter->Color = m_Palette.GetColor(dlgCommodoreColors->Color);
            break;
            case vcAuxiliary:
            m_Palette.Auxiliary = dlgCommodoreColors->Color;
            panVicAuxiliary->Color = m_Palette.GetColor(dlgCommodoreColors->Color);
            break;
            default:
                break;
        }
    }
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmVic20MultiColorDHPalette::panVicBackgroundClick(TObject *Sender)
{
    panVicBackground->BevelOuter = bvRaised;
    panVicBorder->BevelOuter     = bvRaised;
    panVicCharacter->BevelOuter  = bvRaised;
    panVicAuxiliary->BevelOuter  = bvRaised;
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    if (true == SAFE_PTR(Panel))
    {
        m_Palette.Color = (TMultiColorDH)Panel->Tag;
        Panel->BevelOuter = bvLowered;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmVic20MultiColorDHPalette::lblResetPaletteClick(TObject *Sender)
{
    m_Palette.Reset();
    panVicBackgroundClick(panVicCharacter);
    RefreshPanels();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmVic20MultiColorDHPalette::RefreshPanels(void)
{
    panVicBackground->Color = m_Palette.GetColor(m_Palette.Background);
    panVicBorder->Color     = m_Palette.GetColor(m_Palette.Border    );
    panVicCharacter->Color  = m_Palette.GetColor(m_Palette.Character );
    panVicAuxiliary->Color  = m_Palette.GetColor(m_Palette.Auxiliary );
}
//---------------------------------------------------------------------------

