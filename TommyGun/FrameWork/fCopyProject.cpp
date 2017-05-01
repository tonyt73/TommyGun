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
#include <vcl.h>
#pragma hdrstop
#include "fCopyProject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "pngimage"
#pragma resource "*.dfm"
TfrmCopyProject *frmCopyProject;
//---------------------------------------------------------------------------
__fastcall TfrmCopyProject::TfrmCopyProject(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCopyProject::Execute(String sOldName)
{
    lblOldName->Caption = sOldName;
    return ShowModal() == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCopyProject::edtNewNameChange(TObject *Sender)
{
    cmdOK->Enabled = edtNewName->Text.Trim() != "" && edtNewName->Text.Trim().LowerCase() != lblOldName->Caption.LowerCase();
}
//---------------------------------------------------------------------------

