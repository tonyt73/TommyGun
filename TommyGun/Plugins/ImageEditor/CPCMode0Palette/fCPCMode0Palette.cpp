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
using namespace CPCMode0Palette;
//---------------------------------------------------------------------------
TfrmCPCMode0Palette *frmCPCMode0Palette = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmCPCMode0Palette::TfrmCPCMode0Palette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCPCMode0Palette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    RefreshPanels();
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCPCMode0Palette::Release(void)
{
    RL_HRESULT(S_OK);
    panCPCPalette->Parent->RemoveControl(panCPCPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCPCMode0Palette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode0Palette::panColour0Click(TObject *Sender)
{
    panColour0->BevelOuter = bvRaised;
    panColour1->BevelOuter = bvRaised;
    panColour2->BevelOuter = bvRaised;
    panColour3->BevelOuter = bvRaised;
    panColour4->BevelOuter = bvRaised;
    panColour5->BevelOuter = bvRaised;
    panColour6->BevelOuter = bvRaised;
    panColour7->BevelOuter = bvRaised;
    panColour8->BevelOuter = bvRaised;
    panColour9->BevelOuter = bvRaised;
    panColour10->BevelOuter = bvRaised;
    panColour11->BevelOuter = bvRaised;
    panColour12->BevelOuter = bvRaised;
    panColour13->BevelOuter = bvRaised;
    panColour14->BevelOuter = bvRaised;
    panColour15->BevelOuter = bvRaised;
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    if (true == SAFE_PTR(Panel))
    {
        m_Palette.Color = Panel->Tag;
        Panel->BevelOuter = bvLowered;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode0Palette::lblColours0to7Click(TObject *Sender)
{
    TLabel* Label = dynamic_cast<TLabel*>(Sender);
    if (true == SAFE_PTR(Label) && true == dlgAmstradColors->Execute(m_Palette.Color))
    {
        m_Palette.SetTableColor(m_Palette.Color, dlgAmstradColors->Color);
        for (int i = 0; i < panCPCPalette->ControlCount; i++)
        {
            TPanel* Panel = dynamic_cast<TPanel*>(panCPCPalette->Controls[i]);
            if (true == SAFE_PTR(Panel) && Panel->Tag >= 0 && Panel->BevelOuter == bvLowered)
            {
                Panel->Color = dlgAmstradColors->Color;
            }
        }
    }
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode0Palette::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    panColour0->BevelOuter = panColour0->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour1->BevelOuter = panColour1->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour2->BevelOuter = panColour2->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour3->BevelOuter = panColour3->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour4->BevelOuter = panColour4->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour5->BevelOuter = panColour5->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour6->BevelOuter = panColour6->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour7->BevelOuter = panColour7->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour8->BevelOuter = panColour8->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour9->BevelOuter = panColour9->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour10->BevelOuter = panColour10->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour11->BevelOuter = panColour11->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour12->BevelOuter = panColour12->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour13->BevelOuter = panColour13->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour14->BevelOuter = panColour14->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColour15->BevelOuter = panColour15->Tag == m_Palette.Color ? bvLowered : bvRaised;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode0Palette::lblResetPaletteClick(TObject *Sender)
{
    m_Palette.Reset();
    RefreshPanels();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCPCMode0Palette::RefreshPanels(void)
{
    panColour0->Color = m_Palette.GetColor(0);
    panColour1->Color = m_Palette.GetColor(1);
    panColour2->Color = m_Palette.GetColor(2);
    panColour3->Color = m_Palette.GetColor(3);
    panColour4->Color = m_Palette.GetColor(4);
    panColour5->Color = m_Palette.GetColor(5);
    panColour6->Color = m_Palette.GetColor(6);
    panColour7->Color = m_Palette.GetColor(7);
    panColour8->Color = m_Palette.GetColor(8);
    panColour9->Color = m_Palette.GetColor(9);
    panColour10->Color = m_Palette.GetColor(10);
    panColour11->Color = m_Palette.GetColor(11);
    panColour12->Color = m_Palette.GetColor(12);
    panColour13->Color = m_Palette.GetColor(13);
    panColour14->Color = m_Palette.GetColor(14);
    panColour15->Color = m_Palette.GetColor(15);
    panColour0Click(panColour1);
}
//---------------------------------------------------------------------------

