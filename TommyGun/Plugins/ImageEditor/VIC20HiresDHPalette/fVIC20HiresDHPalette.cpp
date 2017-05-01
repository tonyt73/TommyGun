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
TfrmVic20HiresDHPalette *frmVic20HiresDHPalette = NULL;
TSpeedButton* g_ButtonsInk[8];
TSpeedButton* g_ButtonsPaper[16];
//---------------------------------------------------------------------------
__fastcall TfrmVic20HiresDHPalette::TfrmVic20HiresDHPalette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmVic20HiresDHPalette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    g_ButtonsInk[0]     = spdInk00;
    g_ButtonsInk[1]     = spdInk01;
    g_ButtonsInk[2]     = spdInk02;
    g_ButtonsInk[3]     = spdInk03;
    g_ButtonsInk[4]     = spdInk04;
    g_ButtonsInk[5]     = spdInk05;
    g_ButtonsInk[6]     = spdInk06;
    g_ButtonsInk[7]     = spdInk07;
    g_ButtonsPaper[ 0]  = spdPaper00;
    g_ButtonsPaper[ 1]  = spdPaper01;
    g_ButtonsPaper[ 2]  = spdPaper02;
    g_ButtonsPaper[ 3]  = spdPaper03;
    g_ButtonsPaper[ 4]  = spdPaper04;
    g_ButtonsPaper[ 5]  = spdPaper05;
    g_ButtonsPaper[ 6]  = spdPaper06;
    g_ButtonsPaper[ 7]  = spdPaper07;
    g_ButtonsPaper[ 8]  = spdPaper08;
    g_ButtonsPaper[ 9]  = spdPaper09;
    g_ButtonsPaper[10]  = spdPaper10;
    g_ButtonsPaper[11]  = spdPaper11;
    g_ButtonsPaper[12]  = spdPaper12;
    g_ButtonsPaper[13]  = spdPaper13;
    g_ButtonsPaper[14]  = spdPaper14;
    g_ButtonsPaper[15]  = spdPaper15;

    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    OnUpdatePaletteGUI();
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmVic20HiresDHPalette::Release(void)
{
    RL_HRESULT(S_OK);
    panPalette->Parent->RemoveControl(panPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmVic20HiresDHPalette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmVic20HiresDHPalette::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    spdInk00Click  (g_ButtonsInk   [m_Palette.Ink   ]);
    spdPaper00Click(g_ButtonsPaper [m_Palette.Paper ]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmVic20HiresDHPalette::spdInk00Click(TObject *Sender)
{
    TComponent* Button = dynamic_cast<TComponent*>(Sender);
    if (true == SAFE_PTR(Button))
    {
        static_cast<TSpeedButton*>(Button)->Down = true;
        m_Palette.Ink = Button->Tag;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmVic20HiresDHPalette::spdPaper00Click(TObject *Sender)
{
    TComponent* Button = dynamic_cast<TComponent*>(Sender);
    if (true == SAFE_PTR(Button))
    {
        static_cast<TSpeedButton*>(Button)->Down = true;
        m_Palette.Paper = Button->Tag;
    }
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------

