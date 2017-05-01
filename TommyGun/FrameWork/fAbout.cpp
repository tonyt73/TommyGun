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
void __fastcall TfrmAbout::lblEmailClick(TObject *Sender)
{
    char sWebLink[] = "mailto:tommygun.ide@gmail.com\0";
    OpenLink(sWebLink);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::lblWebsiteClick(TObject *Sender)
{
    char sWebLink[] = "https://sourceforge.net/projects/tommygun/\0";
    OpenLink(sWebLink);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::lblSynEditClick(TObject *Sender)
{
    char sWebLink[] = "http://www.scintilla.org/\0";
    OpenLink(sWebLink);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::lblFooodWebSiteClick(TObject *Sender)
{
    char sWebLink[] = "http://www.iconaholic.com/\0";
    OpenLink(sWebLink);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::Label2Click(TObject *Sender)
{
    char sWebLink[] = "http://pasmo.speccy.org/\0";
    OpenLink(sWebLink);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::Label4Click(TObject *Sender)
{
    char sWebLink[] = "http://fms.komkon.org/EMUL8/\0";
    OpenLink(sWebLink);
}
//---------------------------------------------------------------------------

