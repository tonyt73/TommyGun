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
TfrmImageMask *frmImageMask = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmImageMask::TfrmImageMask(TComponent* Owner)
    : TForm(Owner)
    , m_bBorderStyle(mbsNone)
{
}
//---------------------------------------------------------------------------
bool __fastcall TfrmImageMask::Execute(ZXPalette* pPalette)
{
    m_bBorderStyle = mbsNone;
    radBorderStyleNone->Checked = true;
    /*cmbColors->Items->Clear();
    cmbColors->Sorted = false;
    cmbColors->AddColor("Colour " + IntToStr(pPalette->Colors - 1), pPalette->GetColor(pPalette->Colors - 1));
    for (unsigned int i = 0; i < pPalette->Colors - 1; i++)
    {
        cmbColors->AddColor("Colour " + IntToStr(i), pPalette->GetColor(i));
    }
    cmbColors->Sorted = false;
    cmbColors->ItemIndex = 0;*/
    ShowModal();
    return ModalResult == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageMask::radBorderStyleNoneClick(TObject *Sender)
{
    m_bBorderStyle = mbsNone;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageMask::radBorderStyleStarClick(TObject *Sender)
{
    m_bBorderStyle = mbsStar;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageMask::radBorderStyleSquareClick(TObject *Sender)
{
    m_bBorderStyle = mbsSquare;
}
//---------------------------------------------------------------------------

