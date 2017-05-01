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
TfrmSearch *frmSearch = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmSearch::TfrmSearch(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::FormShow(TObject *Sender)
{
    cmbFindText->SetFocus();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmSearch::Execute(void)
{
    ShowModal();
    return mrCancel != ModalResult;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmSearch::GetBool(int iIndex)
{
    bool bValue = false;
    switch(iIndex)
    {
        case eCaseSensitive:    bValue = chkCaseSensitive->Checked;     break;
        case eWholeWordsOnly:   bValue = chkWholeWordsOnly->Checked;    break;
        case eForward:          bValue = radForward->Checked;           break;
        case eBackward:         bValue = radBackwards->Checked;         break;
        case eGlobal:           bValue = radGlobal->Checked;            break;
        case eProjectFiles:     bValue = radProjectFiles->Checked;      break;
        case eFromCursor:       bValue = radFromCursor->Checked;        break;
        case eEntireScope:      bValue = radEntireScope->Checked;       break;
        default:                                                        break;
    }
    return bValue;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::SetBool(int iIndex, bool bValue)
{
    switch(iIndex)
    {
        case eCaseSensitive:    chkCaseSensitive->Checked   = bValue;   break;
        case eWholeWordsOnly:   chkWholeWordsOnly->Checked  = bValue;   break;
        case eForward:          radForward->Checked         = bValue;   break;
        case eBackward:         radBackwards->Checked       = bValue;   break;
        case eGlobal:           radGlobal->Checked          = bValue;   break;
        case eProjectFiles:     radProjectFiles->Checked    = bValue;   break;
        case eFromCursor:       radFromCursor->Checked      = bValue;   break;
        case eEntireScope:      radEntireScope->Checked     = bValue;   break;
        default:                                                        break;
    }
}
//---------------------------------------------------------------------------
String __fastcall TfrmSearch::GetText(int iIndex)
{
    return cmbFindText->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::SetText(int iIndex, String sValue)
{
    cmbFindText->Text = sValue;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::cmdOKClick(TObject *Sender)
{
    if (cmbFindText->Text.Trim() == "")
    {
        int iAnswer = 0;
        Message(mbtError, "Search Error", "The search text cannot be blank", "The search text is blank, please include a valid text string to search for.", "OK", "", "", iAnswer );
    }
    else
    {
        ModalResult = mrOk;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = ModalResult != mrNone;
}
//---------------------------------------------------------------------------


