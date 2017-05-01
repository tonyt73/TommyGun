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
TfrmStringDlg *frmStringDlg = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmStringDlg::TfrmStringDlg(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringDlg::edtIDChange(TObject *Sender)
{
    cmdOk->Enabled = memoValue->Text.Trim() != "";
}
//---------------------------------------------------------------------------
bool __fastcall TfrmStringDlg::Execute(bool bAdd, const String& sID, const String& sValue)
{
    ActiveControl = edtID;
    Caption = bAdd ? "Add String" : "Edit String";

    edtID->Text = sID;
    memoValue->Text = sValue;
        
    ShowModal();
    return ModalResult == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringDlg::memoValueKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Shift.Contains(ssCtrl) && Key == VK_RETURN && cmdOk->Enabled)
    {
        ModalResult = mrOk;
    }
}
//---------------------------------------------------------------------------

