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
TfrmEnterprise256Palette *frmEnterprise256Palette = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmEnterprise256Palette::TfrmEnterprise256Palette(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterprise256Palette::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    OnUpdatePaletteGUI();
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterprise256Palette::Release(void)
{
    RL_HRESULT(S_OK);
    panPalette->Parent->RemoveControl(panPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmEnterprise256Palette::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise256Palette::lblPenClick(TObject *Sender)
{
    if (true == dlgEnterpriseColors->Execute(m_Palette.Pen))
    {
        m_Palette.Pen = dlgEnterpriseColors->Index;
        panPen->Color = dlgEnterpriseColors->Color;
    }
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise256Palette::lblBrushClick(TObject *Sender)
{
    if (true == dlgEnterpriseColors->Execute(m_Palette.Brush))
    {
        m_Palette.Brush = dlgEnterpriseColors->Index;
        panBrush->Color = dlgEnterpriseColors->Color;
    }
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise256Palette::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    panPen->Color   = m_Palette.GetColor(m_Palette.Pen  );
    panBrush->Color = m_Palette.GetColor(m_Palette.Brush);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEnterprise256Palette::lblResetPaletteClick(TObject *Sender)
{
    m_Palette.Reset();
    OnUpdatePaletteGUI();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------

