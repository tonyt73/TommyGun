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
//-- VCL FORM OBJECT --------------------------------------------------------
TfrmStringEditor *frmStringEditor = NULL;
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the class and reset some member variables
 * @param   Owner the VCL owner of the form
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @date    Modified 3 May 2002 by Tony Thompson
 * @remarks Copyright KiwiWare 2001
 */
//---------------------------------------------------------------------------
__fastcall TfrmStringEditor::TfrmStringEditor(TComponent* Owner)
    : TForm(Owner),
      m_bInitialized(false),
      m_PluginHandle(NULL)
{
    RL_METHOD
    frmStringDlg = new TfrmStringDlg(NULL);
    UpdateControls();
}
//---------------------------------------------------------------------------
// Destructor
/**
 * @brief   Frees allocated resources
 * @author  Tony Thompson
 * @date    Created 10 March 2003 by Tony Thompson
 * @remarks Copyright KiwiWare 2003
 */
//---------------------------------------------------------------------------
__fastcall TfrmStringEditor::~TfrmStringEditor()
{
    RL_METHOD
    SAFE_DELETE(frmStringDlg);
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::actAddStringExecute(TObject *Sender)
{
    if (frmStringDlg->Execute(true, "", ""))
    {
        m_TableManager.AddString(lstTables->ItemIndex, frmStringDlg->edtID->Text, frmStringDlg->memoValue->Text);
        UpdateStringsList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::actRemoveStringExecute(TObject *Sender)
{
    m_TableManager.RemoveString(lstTables->ItemIndex, lstStrings->ItemIndex);
    UpdateStringsList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::actCloneStringExecute(TObject *Sender)
{
    m_TableManager.CloneString(lstTables->ItemIndex, lstStrings->ItemIndex);
    UpdateStringsList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::actEditStringExecute(TObject *Sender)
{
    TListItem* item = lstStrings->Selected;
    if (SAFE_PTR(item))
    {
        if (frmStringDlg->Execute(false, item->SubItems->Strings[0], item->SubItems->Strings[1]))
        {
            m_TableManager.SetString(lstTables->ItemIndex, lstStrings->ItemIndex, frmStringDlg->memoValue->Text);
            m_TableManager.SetID(lstTables->ItemIndex, lstStrings->ItemIndex, frmStringDlg->edtID->Text);
            UpdateStringsList();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::actUpStringExecute(TObject *Sender)
{
    lstStrings->ItemIndex = m_TableManager.UpString(lstTables->ItemIndex, lstStrings->ItemIndex);
    UpdateStringsList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::actDownStringExecute(TObject *Sender)
{
    lstStrings->ItemIndex = m_TableManager.DownString(lstTables->ItemIndex, lstStrings->ItemIndex);
    UpdateStringsList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::lstStringsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == 'A' || Key == 'a')
    {
        actAddStringExecute(NULL);
    }
    else if (Key == 'C' || Key == 'c')
    {
        actCloneStringExecute(NULL);
    }
    else if (Key == 'R' || Key == 'r')
    {
        actRemoveStringExecute(NULL);
    }
    else if (Key == 'U' || Key == 'u')
    {
        actUpStringExecute(NULL);
    }
    else if (Key == 'D' || Key == 'd')
    {
        actDownStringExecute(NULL);
    }
    else if (Key == VK_RETURN)
    {
        actEditStringExecute(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::edtTableNameChange(TObject *Sender)
{
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::UpdateControls(void)
{
    bool bTables = m_TableManager.Tables > 0;
    bool bEmpty = edtTableName->Text.Trim() == "";
    bool bTableExists = !bEmpty && m_TableManager.TableExists(edtTableName->Text);

    cmdTableAdd->Enabled = !bTableExists && !bEmpty;
    cmdTableRemove->Enabled = bTableExists;
    cmdTableClone->Enabled = !bTableExists && lstTables->ItemIndex != -1;
    cmdTableRename->Enabled = !bTableExists && lstTables->ItemIndex != -1;
    cmdTableMoveUp->Enabled = lstTables->ItemIndex > 0;
    cmdTableMoveDown->Enabled = lstTables->ItemIndex != -1 && lstTables->ItemIndex < (lstTables->Items->Count - 1);

    actAddString->Enabled = bTables && lstTables >= 0;
    actRemoveString->Enabled = bTables && lstStrings->ItemIndex != -1;
    actCloneString->Enabled = bTables && lstStrings->ItemIndex != -1;
    actEditString->Enabled = bTables && lstStrings->ItemIndex != -1;
    actUpString->Enabled = bTables && lstStrings->ItemIndex > 0;
    actDownString->Enabled = bTables && lstStrings->ItemIndex != -1 && lstStrings->ItemIndex < (lstStrings->Items->Count - 1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::cmdTableAddClick(TObject *Sender)
{
    m_TableManager.AddTable(edtTableName->Text);
    UpdateTableList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::cmdTableRemoveClick(TObject *Sender)
{
    m_TableManager.RemoveTable(edtTableName->Text);
    UpdateTableList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::cmdTableCloneClick(TObject *Sender)
{
    m_TableManager.CloneTable(lstTables->ItemIndex, edtTableName->Text);
    UpdateTableList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::cmdTableRenameClick(TObject *Sender)
{
    m_TableManager.RenameTable(lstTables->ItemIndex, edtTableName->Text);
    UpdateTableList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::lstTablesClick(TObject *Sender)
{
    if (lstTables->ItemIndex >= 0)
    {
        edtTableName->Text = lstTables->Items->Strings[lstTables->ItemIndex];
        UpdateStringsList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::UpdateTableList(void)
{
    int iIndex = lstTables->ItemIndex;
    lstTables->Items->Clear();
    for (int i = 0; i < m_TableManager.Tables; i++)
    {
        lstTables->Items->Add(m_TableManager.GetName(i));
    }
    if (iIndex == -1 && lstTables->Items->Count > 0)
    {
        lstTables->ItemIndex = 0;
    }
    else
    {
        lstTables->ItemIndex = iIndex;
    }
    UpdateStringsList();
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::UpdateStringsList(void)
{
    int iIndex = lstStrings->ItemIndex;
    lstStrings->Items->Clear();
    if (lstTables->ItemIndex >= 0)
    {
        for (int i = 0; i < m_TableManager.Strings(lstTables->ItemIndex); i++)
        {
            TListItem* item = lstStrings->Items->Add();
            if (SAFE_PTR(item))
            {
                item->Caption = StrToInt(i);
                item->SubItems->Add(m_TableManager.GetID(lstTables->ItemIndex, i));
                item->SubItems->Add(m_TableManager.GetString(lstTables->ItemIndex, i));
            }
        }
    }
    if (iIndex != -1 && iIndex < lstStrings->Items->Count)
    {
        lstStrings->ItemIndex = iIndex;
    }
    if (iIndex == -1 && lstStrings->Items->Count)
    {
        lstStrings->ItemIndex = 0;
    }
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::lstStringsClick(TObject *Sender)
{
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::cmdTableMoveUpClick(TObject *Sender)
{
    lstTables->ItemIndex = m_TableManager.UpTable(lstTables->ItemIndex);
    UpdateTableList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::cmdTableMoveDownClick(TObject *Sender)
{
    lstTables->ItemIndex = m_TableManager.DownTable(lstTables->ItemIndex);
    UpdateTableList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::lstStringsChange(TObject *Sender, TListItem *Item, TItemChange Change)
{
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::Clear(void)
{
    m_TableManager.Clear();
    UpdateTableList();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmStringEditor::Load(KXmlInfo* xmlInfo)
{
    m_TableManager.Load(xmlInfo);
    UpdateTableList();
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmStringEditor::Save(KXmlInfo* xmlInfo)
{
    return m_TableManager.Save(xmlInfo);
}
//---------------------------------------------------------------------------
void __fastcall TfrmStringEditor::pgcStringMapDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    static Graphics::TBitmap* bm = NULL;
    Control->Canvas->Brush->Color = clWhite;
    Control->Canvas->FillRect(Rect);
    TTabSheet* sheet = pgcStringMap->Pages[TabIndex];
    int cw = Control->Canvas->TextWidth(sheet->Caption) / 2;
    int ch = Control->Canvas->TextHeight(sheet->Caption) / 2;
    int rl = Rect.Left;
    int rt = Rect.Top;
    int cx = Rect.Width() / 2;
    int cy = Rect.Height() / 2;
    Control->Canvas->Font->Color = clBlack;
    Control->Canvas->Font->Height = 15;
    Control->Canvas->Font->Style = Active ? TFontStyles() << fsBold : TFontStyles();
    Control->Canvas->TextRect(Rect, rl + 10 + cx - cw, rt + cy - ch, sheet->Caption);
    pgcStringMap->Images->Draw(Control->Canvas, rl + 10 + cx - cw - 20, rt + cy - 8, sheet->ImageIndex, true);

    if (Active)
    {
        if (bm == NULL)
        {
            bm = new Graphics::TBitmap();
            bm->Width = 1;
            bm->Height = 1;
            bm->PixelFormat = pf32bit;
            bm->Canvas->Pixels[0][0] = (TColor)0x00846142;
        }
        TRect tr(Rect.left, Rect.top, Rect.right, Rect.top + 5);
        Control->Canvas->StretchDraw(tr, bm);
    }
}
//---------------------------------------------------------------------------

