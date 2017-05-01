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
TfrmEnterprise2Palette *frmEnterprise2Palette = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmEnterprise2Palette::TfrmEnterprise2Palette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterprise2Palette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    OnUpdatePaletteGUI();
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterprise2Palette::Release(void)
{
    RL_HRESULT(S_OK);
    panPalette->Parent->RemoveControl(panPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterprise2Palette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise2Palette::lblPenClick(TObject *Sender)
{
    if (true == dlgEnterpriseColors->Execute(dlgEnterpriseColors->GetIndex(panPen->Color)))
    {
        m_Palette.SetTableColor(1, dlgEnterpriseColors->Color);
        OnUpdatePaletteGUI();
    }
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise2Palette::lblBrushClick(TObject *Sender)
{
    if (true == dlgEnterpriseColors->Execute(dlgEnterpriseColors->GetIndex(panBrush->Color)))
    {
        m_Palette.SetTableColor(0, dlgEnterpriseColors->Color);
        OnUpdatePaletteGUI();
    }
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise2Palette::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    panPen->Color   = m_Palette.PenColor;
    panBrush->Color = m_Palette.BrushColor;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise2Palette::lblResetPaletteClick(TObject *Sender)
{
    m_Palette.Reset();
    OnUpdatePaletteGUI();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------


