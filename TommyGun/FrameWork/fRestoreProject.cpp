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
#include "fRestoreProject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "pngimage"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmRestoreProject::TfrmRestoreProject(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int __fastcall TfrmRestoreProject::Execute(const String& sName, ZXRestoreItems& vItems)
{
    panProjectName->Caption = "  " + sName.SubString(2, 1024);
    for (int i = 1; i < (int)vItems.size(); i++)
    {
        if (vItems[i].dtDate > vItems[i-1].dtDate)
        {
            ZXRestoreItem ri = vItems[i];
            vItems[i] = vItems[i-1];
            vItems[i-1] = ri;
            i = 0;
        }
    }
    for (int i = 0; i < (int)vItems.size(); i++)
    {
        TListItem  *Item = lstBackups->Items->Add();
        Item->Caption = vItems[i].dtDate.FormatString("ddddd");
        Item->SubItems->Add(vItems[i].dtDate.FormatString("tt"));
        Item->SubItems->Add(IntToStr(vItems[i].iFiles));
        if (vItems[i].iSize < 1024)
            Item->SubItems->Add(IntToStr(vItems[i].iSize) + " bytes");
        else if (vItems[i].iSize < 1024*1024)
            Item->SubItems->Add(FloatToStrF((float)vItems[i].iSize / 1024.0, ffFixed, 7, 1) + " KB");
        else
            Item->SubItems->Add(FloatToStrF((float)vItems[i].iSize / (1024.0 * 1024.0), ffFixed, 7, 1) + " MB");
    }
    lstBackupsClick(NULL);
    ShowModal();
    return lstBackups->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRestoreProject::lstBackupsClick(TObject *Sender)
{
    cmdOK->Enabled = lstBackups->Items->Count > 0 && lstBackups->ItemIndex != -1;
}
//---------------------------------------------------------------------------

