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
TfrmMSX16Palette *frmMSX16Palette = NULL;
TSpeedButton* g_ButtonsInk[8];
TSpeedButton* g_ButtonsPaper[8];
TSpeedButton* g_ButtonsBright[2];
TSpeedButton* g_ButtonsFlash[2];
//---------------------------------------------------------------------------
__fastcall TfrmMSX16Palette::TfrmMSX16Palette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmMSX16Palette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    g_ButtonsInk[0]     = spdInkBlack;
    g_ButtonsInk[1]     = spdInkBlue;
    g_ButtonsInk[2]     = spdInkRed;
    g_ButtonsInk[3]     = spdInkPurple;
    g_ButtonsInk[4]     = spdInkGreen;
    g_ButtonsInk[5]     = spdInkCyan;
    g_ButtonsInk[6]     = spdInkYellow;
    g_ButtonsInk[7]     = spdInkWhite;
    g_ButtonsPaper[0]   = spdPaperBlack;
    g_ButtonsPaper[1]   = spdPaperBlue;
    g_ButtonsPaper[2]   = spdPaperRed;
    g_ButtonsPaper[3]   = spdPaperPurple;
    g_ButtonsPaper[4]   = spdPaperGreen;
    g_ButtonsPaper[5]   = spdPaperCyan;
    g_ButtonsPaper[6]   = spdPaperYellow;
    g_ButtonsPaper[7]   = spdPaperWhite;
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmMSX16Palette::Release(void)
{
    RL_HRESULT(S_OK);
    panMSX16Palette->Parent->RemoveControl(panMSX16Palette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmMSX16Palette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMSX16Palette::spdInkBlackClick(TObject *Sender)
{
    TComponent* Button = dynamic_cast<TComponent*>(Sender);
    if (true == SAFE_PTR(Button))
    {
        static_cast<TSpeedButton*>(Button)->Down = true;
        m_Palette.Ink = Button->Tag;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMSX16Palette::spdPaperBlackClick(TObject *Sender)
{
    TComponent* Button = dynamic_cast<TComponent*>(Sender);
    if (true == SAFE_PTR(Button))
    {
        static_cast<TSpeedButton*>(Button)->Down = true;
        m_Palette.Paper = Button->Tag;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMSX16Palette::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    spdInkBlackClick  (g_ButtonsInk   [m_Palette.Ink   ]);
    spdPaperBlackClick(g_ButtonsPaper [m_Palette.Paper ]);
}
//---------------------------------------------------------------------------

