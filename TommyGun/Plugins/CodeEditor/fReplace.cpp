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
TfrmReplace *frmReplace = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmReplace::TfrmReplace(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TfrmReplace::Execute(void)
{
    m_bReplaceAll = false;
    ShowModal();
    return mrCancel != ModalResult;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmReplace::GetBool(int iIndex)
{
    bool bValue = false;
    switch(iIndex)
    {
        case eCaseSensitive:    bValue = chkCaseSensitive->Checked;     break;
        case eWholeWordsOnly:   bValue = chkWholeWordsOnly->Checked;    break;
        case ePromptOnReplace:  bValue = chkPromptOnReplace->Checked;   break;
        case eForward:          bValue = radForward->Checked;           break;
        case eBackward:         bValue = radBackwards->Checked;         break;
        case eGlobal:           bValue = radGlobal->Checked;            break;
        case eSelectedText:     bValue = radSelectedText->Checked;      break;
        case eFromCursor:       bValue = radFromCursor->Checked;        break;
        case eEntireScope:      bValue = radEntireScope->Checked;       break;
        case eReplaceAll:       bValue = m_bReplaceAll;                 break;
        default:                                                        break;
    }
    return bValue;
}
//---------------------------------------------------------------------------
void __fastcall TfrmReplace::SetBool(int iIndex, bool bValue)
{
    switch(iIndex)
    {
        case eCaseSensitive:    chkCaseSensitive->Checked   = bValue;   break;
        case eWholeWordsOnly:   chkWholeWordsOnly->Checked  = bValue;   break;
        case ePromptOnReplace:  chkPromptOnReplace->Checked = bValue;   break;
        case eForward:          radForward->Checked         = bValue;
                                radBackwards->Checked       =!bValue;   break;
        case eBackward:         radBackwards->Checked       = bValue;
                                radForward->Checked         =!bValue;   break;
        case eGlobal:           radGlobal->Checked          = bValue;
                                radSelectedText->Checked    =!bValue;   break;
        case eSelectedText:     radSelectedText->Checked    = bValue;
                                radGlobal->Checked          =!bValue;   break;
        case eFromCursor:       radFromCursor->Checked      = bValue;
                                radEntireScope->Checked     =!bValue;   break;
        case eEntireScope:      radEntireScope->Checked     = bValue;
                                radFromCursor->Checked      =!bValue;   break;
        default:                                                        break;
    }
}
//---------------------------------------------------------------------------
String __fastcall TfrmReplace::GetText(int iIndex)
{
    String sValue;
    switch(iIndex)
    {
        case eFindText:         sValue = cmbFindText->Text;             break;
        case eReplaceText:      sValue = cmbReplaceText->Text;          break;
        default:                                                        break;
    }
    return sValue;
}
//---------------------------------------------------------------------------
void __fastcall TfrmReplace::SetText(int iIndex, String sValue)
{
    switch(iIndex)
    {
        case eFindText:         cmbFindText->Text           = sValue;   break;
        case eReplaceText:      cmbReplaceText->Text        = sValue;   break;
        default:                                                        break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmReplace::cmdReplaceAllClick(TObject *Sender)
{
    m_bReplaceAll = true;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmReplace::FormShow(TObject *Sender)
{
    cmbFindText->SetFocus();    
}
//---------------------------------------------------------------------------

