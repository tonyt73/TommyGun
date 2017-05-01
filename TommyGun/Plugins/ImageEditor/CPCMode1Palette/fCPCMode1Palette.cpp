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
using namespace CPCMode1Palette;
//---------------------------------------------------------------------------
TfrmCPCMode1Palette *frmCPCMode1Palette = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmCPCMode1Palette::TfrmCPCMode1Palette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCPCMode1Palette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    RefreshPanels();
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCPCMode1Palette::Release(void)
{
    RL_HRESULT(S_OK);
    panCPCPalette->Parent->RemoveControl(panCPCPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCPCMode1Palette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode1Palette::panColour0Click(TObject *Sender)
{
    panColour0->BevelOuter = bvRaised;
    panColour1->BevelOuter = bvRaised;
    panColour2->BevelOuter = bvRaised;
    panColour3->BevelOuter = bvRaised;
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    if (true == SAFE_PTR(Panel))
    {
        m_Palette.Color = Panel->Tag;
        Panel->BevelOuter = bvLowered;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode1Palette::lblColour0Click(TObject *Sender)
{
    TLabel* Label = dynamic_cast<TLabel*>(Sender);
    if (true == SAFE_PTR(Label) && true == dlgAmstradColors->Execute(Label->Tag))
    {
        m_Palette.SetTableColor(Label->Tag, dlgAmstradColors->Color);
        for (int i = 0; i < panCPCPalette->ControlCount; i++)
        {
            TPanel* Panel = dynamic_cast<TPanel*>(panCPCPalette->Controls[i]);
            if (true == SAFE_PTR(Panel) && Label->Tag == Panel->Tag)
            {
                Panel->Color = dlgAmstradColors->Color;
            }
        }
    }
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode1Palette::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    panColour0->BevelOuter = panColour0->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour1->BevelOuter = panColour1->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour2->BevelOuter = panColour2->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour3->BevelOuter = panColour3->Tag == m_Palette.Color ? bvLowered : bvRaised;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode1Palette::lblResetPaletteClick(TObject *Sender)
{
    m_Palette.Reset();
    RefreshPanels();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode1Palette::RefreshPanels(void)
{
    panColour0->Color = m_Palette.GetColor(0);
    panColour1->Color = m_Palette.GetColor(1);
    panColour2->Color = m_Palette.GetColor(2);
    panColour3->Color = m_Palette.GetColor(3);
    panColour0Click(panColour1);
}
//---------------------------------------------------------------------------

