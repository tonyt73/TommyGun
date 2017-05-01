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
#include "fProblems.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KRegistry"
#pragma resource "*.dfm"
TfrmProblems *frmProblems;
//---------------------------------------------------------------------------
__fastcall TfrmProblems::TfrmProblems(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmProblems::lblViewLogClick(TObject *Sender)
{
    //shellexecute
    String sFile = ExtractFilePath(Application->ExeName) + "General.log";

	SHELLEXECUTEINFO shi;
	shi.cbSize       = sizeof( SHELLEXECUTEINFO );
    shi.hwnd         = NULL;
    shi.fMask        = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
    shi.lpFile       = sFile.c_str();
    shi.lpVerb       = NULL;
    shi.lpParameters = NULL;
    shi.lpDirectory  = NULL;
	shi.nShow        = SW_SHOWNORMAL;

	ShellExecuteEx( &shi );
}
//---------------------------------------------------------------------------
void __fastcall TfrmProblems::chkDonotShowClick(TObject *Sender)
{
    if (chkDonotShow->Checked)
    {
        regScorpio->Write("States", "DoNotShowProblems", true);
    }
}
//---------------------------------------------------------------------------

