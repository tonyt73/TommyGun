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
using namespace EnterprisePalette;
//---------------------------------------------------------------------------
TfrmEnterprise16Palette *frmEnterprise16Palette = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmEnterprise16Palette::TfrmEnterprise16Palette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterprise16Palette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    lblResetPaletteClick(NULL);
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterprise16Palette::Release(void)
{
    RL_HRESULT(S_OK);
    panPalette->Parent->RemoveControl(panPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterprise16Palette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise16Palette::lblResetPaletteClick(TObject *Sender)
{
    m_Palette.Reset();
    OnUpdatePaletteGUI();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise16Palette::lblColours0to7Click(TObject *Sender)
{
    if (dlgEnterpriseColors->Execute(m_Palette.Color, true))
    {
        m_Palette.Set256Color(m_Palette.Color, dlgEnterpriseColors->Index);
        OnUpdatePaletteGUI();
        m_ImageEditor.SystemRefreshView(m_PluginHandle);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise16Palette::panColour0Click(TObject *Sender)
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
    panColourA->BevelOuter = bvRaised;
    panColourB->BevelOuter = bvRaised;
    panColourC->BevelOuter = bvRaised;
    panColourD->BevelOuter = bvRaised;
    panColourE->BevelOuter = bvRaised;
    panColourF->BevelOuter = bvRaised;
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    if (true == SAFE_PTR(Panel))
    {
        m_Palette.Color = Panel->Tag;
        Panel->BevelOuter = bvLowered;
    }

}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise16Palette::OnUpdatePaletteGUI(void)
{
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
    panColourA->BevelOuter = panColourA->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColourB->BevelOuter = panColourB->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColourC->BevelOuter = panColourC->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColourD->BevelOuter = panColourD->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColourE->BevelOuter = panColourE->Tag == m_Palette.Color ? bvLowered : bvRaised;
    panColourF->BevelOuter = panColourF->Tag == m_Palette.Color ? bvLowered : bvRaised;
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
    panColourA->Color = m_Palette.GetColor(10);
    panColourB->Color = m_Palette.GetColor(11);
    panColourC->Color = m_Palette.GetColor(12);
    panColourD->Color = m_Palette.GetColor(13);
    panColourE->Color = m_Palette.GetColor(14);
    panColourF->Color = m_Palette.GetColor(15);
}
//---------------------------------------------------------------------------

