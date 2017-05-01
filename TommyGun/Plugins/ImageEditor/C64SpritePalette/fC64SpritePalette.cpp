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
using namespace C64SpritePalette;
//---------------------------------------------------------------------------
TfrmC64SpritePalette *frmC64SpritePalette = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmC64SpritePalette::TfrmC64SpritePalette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmC64SpritePalette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    RefreshPanels();
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmC64SpritePalette::Release(void)
{
    RL_HRESULT(S_OK);
    panC64Palette->Parent->RemoveControl(panC64Palette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmC64SpritePalette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmC64SpritePalette::panC64ScreenColorClick(TObject *Sender)
{
    panC64ScreenColor->BevelOuter = bvRaised;
    panC64NormalColor->BevelOuter = bvRaised;
    panC64MultiColor1->BevelOuter = bvRaised;
    panC64MultiColor2->BevelOuter = bvRaised;
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    if (true == SAFE_PTR(Panel))
    {
        m_Palette.Color = Panel->Tag;
        Panel->BevelOuter = bvLowered;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmC64SpritePalette::lblC64ScreenColorClick(TObject *Sender)
{
    TLabel* Label = dynamic_cast<TLabel*>(Sender);
    if (true == SAFE_PTR(Label) && true == dlgCommodoreColors->Execute(Label->Tag))
    {
        m_Palette.SetTableColor(Label->Tag, dlgCommodoreColors->Color);
        for (int i = 0; i < panC64Palette->ControlCount; i++)
        {
            TPanel* Panel = dynamic_cast<TPanel*>(panC64Palette->Controls[i]);
            if (true == SAFE_PTR(Panel) && Label->Tag == Panel->Tag)
            {
                Panel->Color = dlgCommodoreColors->Color;
            }
        }
    }
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmC64SpritePalette::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    panC64ScreenColor->BevelOuter = panC64ScreenColor->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panC64NormalColor->BevelOuter = panC64NormalColor->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panC64MultiColor1->BevelOuter = panC64MultiColor1->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panC64MultiColor2->BevelOuter = panC64MultiColor2->Tag == m_Palette.Color ? bvLowered : bvRaised;
}
//---------------------------------------------------------------------------
void __fastcall TfrmC64SpritePalette::lblResetPaletteClick(TObject *Sender)
{
    m_Palette.Reset();
    panC64ScreenColorClick(panC64NormalColor);
    RefreshPanels();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmC64SpritePalette::RefreshPanels(void)
{
    panC64ScreenColor->Color = m_Palette.GetColor(0);
    panC64NormalColor->Color = m_Palette.GetColor(1);
    panC64MultiColor1->Color = m_Palette.GetColor(2);
    panC64MultiColor2->Color = m_Palette.GetColor(3);
}
//---------------------------------------------------------------------------

