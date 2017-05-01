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
using namespace Enterprise64AttributePalette;
//---------------------------------------------------------------------------
TfrmEnterpriseAttributePalette *frmEnterpriseAttributePalette = NULL;
TPanel* g_Panels[16];
//---------------------------------------------------------------------------
__fastcall TfrmEnterpriseAttributePalette::TfrmEnterpriseAttributePalette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterpriseAttributePalette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    g_Panels[ 0] = panColour0;
    g_Panels[ 1] = panColour1;
    g_Panels[ 2] = panColour2;
    g_Panels[ 3] = panColour3;
    g_Panels[ 4] = panColour4;
    g_Panels[ 5] = panColour5;
    g_Panels[ 6] = panColour6;
    g_Panels[ 7] = panColour7;
    g_Panels[ 8] = panColour8;
    g_Panels[ 9] = panColour9;
    g_Panels[10] = panColourA;
    g_Panels[11] = panColourB;
    g_Panels[12] = panColourC;
    g_Panels[13] = panColourD;
    g_Panels[14] = panColourE;
    g_Panels[15] = panColourF;
    lblResetPaletteClick(NULL);


    panInk->Color   = g_Panels[m_Palette.Ink  ]->Color;
    panPaper->Color = g_Panels[m_Palette.Paper]->Color;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterpriseAttributePalette::Release(void)
{
    RL_HRESULT(S_OK);
    panPalette->Parent->RemoveControl(panPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterpriseAttributePalette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterpriseAttributePalette::OnUpdatePaletteGUI(void)
{
    for (int i = 0; i < 16; i++)
    {
        g_Panels[i]->BevelOuter = (i == m_Palette.Ink || i == m_Palette.Paper ) ? bvLowered : bvRaised;
        g_Panels[i]->Caption = "";
        g_Panels[i]->Color = m_Palette.GetColor(i); 
    }
    if (m_Palette.Ink == m_Palette.Paper)
    {
        g_Panels[m_Palette.Ink  ]->Caption = "IP";
        g_Panels[m_Palette.Ink  ]->Font->Color = ZXPalette::Luminance(g_Panels[m_Palette.Ink  ]->Color) > 128 ? clBlack : clWhite;
    }
    else
    {
        g_Panels[m_Palette.Ink  ]->Caption = "I";
        g_Panels[m_Palette.Paper]->Caption = "P";
        g_Panels[m_Palette.Ink  ]->Font->Color = ZXPalette::Luminance(g_Panels[m_Palette.Ink  ]->Color) > 128 ? clBlack : clWhite;
        g_Panels[m_Palette.Paper]->Font->Color = ZXPalette::Luminance(g_Panels[m_Palette.Paper]->Color) > 128 ? clBlack : clWhite;
    }
    panInk->Color   = g_Panels[m_Palette.Ink  ]->Color;
    panPaper->Color = g_Panels[m_Palette.Paper]->Color;
    spdInkTransparent->Down = m_Palette.InkTransparent;
    spdPaperTransparent->Down = m_Palette.PaperTransparent;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterpriseAttributePalette::panColour0MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft || Button == mbRight)
    {
        for (int i = 0; i < 16; i++)
        {
            g_Panels[i]->BevelOuter = bvRaised;
        }

        TPanel* Panel = dynamic_cast<TPanel*>(Sender);

        if (true == SAFE_PTR(Panel))
        {
            if (Button == mbLeft)
            {
                m_Palette.Ink = Panel->Tag;
            }
            else
            {
                m_Palette.Paper = Panel->Tag;
            }
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterpriseAttributePalette::lblResetPaletteClick(TObject *Sender)
{
    m_Palette.Reset();
    for (int i = 0; i < 16; i++)
    {
        g_Panels[i]->Color = m_Palette.GetColor(i);
    }

    m_Palette.Ink   = 15;
    m_Palette.Paper = 0;
    m_Palette.InkTransparent = false;
    m_Palette.PaperTransparent = false;
    OnUpdatePaletteGUI();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterpriseAttributePalette::lblInkClick(TObject *Sender)
{
    if (dlgEnterpriseColors->Execute(m_Palette.Ink, true))
    {
        m_Palette.Set256Color(m_Palette.Ink, dlgEnterpriseColors->Index);
        OnUpdatePaletteGUI();
        m_ImageEditor.SystemRefreshView(m_PluginHandle);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterpriseAttributePalette::lblPaperClick(TObject *Sender)
{
    if (dlgEnterpriseColors->Execute(m_Palette.Paper, true))
    {
        m_Palette.Set256Color(m_Palette.Paper, dlgEnterpriseColors->Index);
        OnUpdatePaletteGUI();
        m_ImageEditor.SystemRefreshView(m_PluginHandle);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterpriseAttributePalette::spdInkTransparentClick(TObject *Sender)
{
    m_Palette.InkTransparent = spdInkTransparent->Down;
    m_Palette.PaperTransparent = spdPaperTransparent->Down;
}
//---------------------------------------------------------------------------


