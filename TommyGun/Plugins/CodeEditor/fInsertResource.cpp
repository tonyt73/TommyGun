#pragma link "pngimage"
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
__fastcall TfrmInsertResource::TfrmInsertResource(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmInsertResource::cmdCloseClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------
void __fastcall TfrmInsertResource::actEditSelectAllExecute(TObject *Sender)
{
    for (int i = 0; i < lstResources->Items->Count; i++)
    {
        lstResources->Checked[i] = true;
    }
    lstResourcesClickCheck(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmInsertResource::actEditDeselectAllExecute(TObject *Sender)
{
    for (int i = 0; i < lstResources->Items->Count; i++)
    {
        lstResources->Checked[i] = false;
    }
    lstResourcesClickCheck(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmInsertResource::lstResourcesClickCheck(TObject *Sender)
{
    cmdInsert->Enabled = true;

    if (lstResources->Items->Count > 0)
    {
        int checked = 0;
        for (int i = 0; i < lstResources->Items->Count; ++i)
        {
            if (lstResources->Checked[i])
                checked++;
        }
        cmdInsert->Enabled = checked > 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmInsertResource::splSplitterMoved(TObject *Sender)
{
    lstResourceParser->Width = grpResourceType->Width - lstResourceParser->Left - 6;
    cmbResourceType->Width   = lstResourceParser->Width;
}
//---------------------------------------------------------------------------
void __fastcall TfrmInsertResource::cmbResourceTypeChange(TObject *Sender)
{
    if (lstResources->Items->Count > 0)
    {
        for (int i = 0; i < lstResources->Items->Count; ++i)
        {
            lstResources->Checked[i] = true;
        }
        cmdInsert->Enabled = true;
    }
}
//---------------------------------------------------------------------------



