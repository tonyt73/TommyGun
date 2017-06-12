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
//---------------------------------------------------------------------------
#include "fAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "pngimage"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmAbout *frmAbout = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::Execute(void)
{
    ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::OpenLink(char* sLink)
{
    SHELLEXECUTEINFO shi;
    shi.cbSize       = sizeof( SHELLEXECUTEINFO );
    shi.hwnd         = NULL;
    shi.fMask        = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
    shi.lpFile       = sLink;
    shi.lpVerb       = NULL;
    shi.lpParameters = NULL;
    shi.lpDirectory  = NULL;
    shi.nShow        = SW_SHOWNORMAL;
    ShellExecuteEx( &shi );
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::lblGotoLinkClick(TObject *Sender)
{
    OpenLink(((TLabel*)Sender)->Hint.c_str());
}
//---------------------------------------------------------------------------

