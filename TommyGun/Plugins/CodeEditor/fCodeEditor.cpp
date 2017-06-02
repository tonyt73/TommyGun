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
#include "fCodeEditor.h"
#include <Clipbrd.hpp>
#include <UxTheme.h>
#include "ZXDebugger.h"
#include "Pasmo.h"
//---------------------------------------------------------------------------
#pragma link "DosCommand"
#pragma link "KSlider"
#pragma link "KRegistry"
#pragma link "SciDocTabCtrl"
#pragma link "SciLanguageManager"
#pragma link "SciScintilla"
#pragma link "SciScintillaBase"
#pragma link "SciScintillaMemo"
#pragma link "SciSearchReplace"
#pragma link "SciSearchReplaceBase"
#pragma link "SciDocTabCtrl"
#pragma link "SciLanguageManager"
#pragma link "SciScintilla"
#pragma link "SciScintillaBase"
#pragma link "SciScintillaMemo"
#pragma link "SciSearchReplace"
#pragma link "SciSearchReplaceBase"
#pragma resource "*.dfm"
//-- VCL FORM OBJECT --------------------------------------------------------
TfrmCodeEditor *frmCodeEditor;
const String g_sInvalidChars = "\\ / : * ? \" < > | & ^\n\n";
const String g_sBlank        = "";
//---------------------------------------------------------------------------
const int BOOKMARKER = 2;
const int DEBUG_BREAKPOINT = 3;
const int DEBUG_HIGHLIGHTER_MARKER = 4;
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the class and reset some member variables
 * @param   Owner the VCL owner of the form
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @date    Modified 3 May 2002 by Tony Thompson
 * @remarks Copyright KiwiWare 2004
 */
//---------------------------------------------------------------------------
__fastcall TfrmCodeEditor::TfrmCodeEditor(TComponent* Owner, ZXFileManager& FileManager, ZXParserManager& ParserManager)
: TForm(Owner)
, m_bInitialized(false)
, m_bDirty(false)
, m_bDosAborted(false)
, m_bSearchOnly(true)
, m_bUpdating(false)
, m_bEditting(false)
, m_bInFileList(false)
, m_iFilesOpen(0)
, m_PluginHandle(NULL)
, m_FileManager(FileManager)
, m_ParserManager(ParserManager)
, m_mnuBuild(NULL)
, m_currentBuildToolIndex(0)
, m_ExtMapper(new TExtensionMapper())
, m_bTrace(false)
, m_BreakpointMarker(NULL)
, m_BreakpointHighlighter(NULL)
, m_BookMarker(NULL)
, m_DebugMode(dmStopped)
, m_TimelapseMode(tmStopped)
, m_ActiveEditor(NULL)
{
    RL_METHOD
    // setup the editor defaults
    dosCommand->OutputLines = memoConsole->Lines;
}
//---------------------------------------------------------------------------
// Destructor
/**
 * @brief   Frees allocated resources
 * @author  Tony Thompson
 * @date    Created 10 March 2003 by Tony Thompson
 * @remarks Copyright KiwiWare 2004
 */
//---------------------------------------------------------------------------
__fastcall TfrmCodeEditor::~TfrmCodeEditor()
{
    RL_METHOD
    frmDebuggerStateView->Parent = NULL;
    SAFE_DELETE(m_BreakpointMarker);
    SAFE_DELETE(m_BreakpointHighlighter);
    SAFE_DELETE(m_BookMarker);
    SAFE_DELETE(frmDebuggerStateView);
    SAFE_DELETE(frmDisplayView);
    SAFE_DELETE(frmOSBView);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::FormCreate(TObject *Sender)
{
    sciEditor->StreamClass = __classid(TSciStreamDefault);
    sciEditorOther->StreamClass = __classid(TSciStreamDefault);
	m_ExtMapper->Add(".c;.h;.cpp;.cxx;.hpp", "C++/C");
    m_ExtMapper->Add(".bas", "ZX Basic");
    m_ExtMapper->Add(".asm;.z80;.inc", "Z80");

    m_FileManager.SetSciTabControls(sciTabControl, sciTabControlOther);

    MenusAdd();
    pgcCodeEditor->DoubleBuffered = true;
    // state view
    frmDebuggerStateView = new TfrmDebuggerStateView(Application);
    frmDebuggerStateView->Parent = tabStateView;
    frmDebuggerStateView->Visible = true;
    // display
    frmDisplayView = new TfrmDisplayView(NULL);
    frmDisplayView->Visible = false;
    // osb view
    frmOSBView = new TfrmOSBView(NULL);
    frmOSBView->Visible = false;
    UpdateControls();

    g_Debugger->OnBreakpointHit = OnBreakpointHit;

    m_BreakpointMarker = new TSciMarker(sciEditor, DEBUG_BREAKPOINT, sciMCircle);
    m_BreakpointHighlighter = new TSciMarker(sciEditor, DEBUG_HIGHLIGHTER_MARKER, sciMBackground);
    m_BookMarker = new TSciMarker(sciEditor, BOOKMARKER, sciMFullRect);
    m_BreakpointMarkerOther = new TSciMarker(sciEditorOther, DEBUG_BREAKPOINT, sciMCircle);
    m_BreakpointHighlighterOther = new TSciMarker(sciEditorOther, DEBUG_HIGHLIGHTER_MARKER, sciMBackground);
    m_BookMarkerOther = new TSciMarker(sciEditorOther, BOOKMARKER, sciMFullRect);
    m_ActiveEditor = sciTabControl;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::FormShow(TObject *Sender)
{
    m_BreakpointMarker->ForeColor = clWhite;
    m_BreakpointMarker->BackColor = clRed;
    m_BreakpointMarker->MarkerType = sciMCircle;
    m_BookMarker->ForeColor = clAqua;
    m_BookMarker->BackColor = clBlue;
    m_BookMarker->MarkerType = sciMFullRect;
    m_BreakpointHighlighter->ForeColor = clBlack;   // white
    m_BreakpointHighlighter->BackColor = clNavy;  // red
	m_BreakpointHighlighterOther->MarkerType = sciMBackground;
    
    m_BreakpointMarkerOther->ForeColor = clWhite;
    m_BreakpointMarkerOther->BackColor = clRed;
    m_BreakpointMarkerOther->MarkerType = sciMCircle;
    m_BookMarkerOther->ForeColor = clAqua;
    m_BookMarkerOther->BackColor = clBlue;
    m_BookMarkerOther->MarkerType = sciMFullRect;
    m_BreakpointHighlighterOther->ForeColor = clBlack;   // white
    m_BreakpointHighlighterOther->BackColor = clNavy;  // red
	m_BreakpointHighlighterOther->MarkerType = sciMBackground;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdFileLoadClick(TObject *Sender)
{
    if (true == dlgLoadCode->Execute())
    {
        m_bDirty = true;
        int iIndex = m_FileManager.Add(dlgLoadCode->FileName);
        LoadFile(iIndex);
        m_FileManager.Rename(iIndex, Subst(m_FileManager.GetFilename(iIndex), ' ', '_'));
        UpdateEditor();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::lstFilesDblClick(TObject *Sender)
{
    m_bDirty = false;
    if (lstFiles->ItemIndex >= 0)
    {
        LoadFile(lstFiles->ItemIndex);
        sciEditor->Refresh();
        sciEditor->Update();
		sciEditorOther->Refresh();
		sciEditorOther->Update();
		UpdateEditorSlots();
        UpdateBreakpoints();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::lstFilesClick(TObject *Sender)
{
    edtFilename->Text = m_FileManager.GetFilename(lstFiles->ItemIndex);
    lstFiles->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::edtFilenameChange(TObject *Sender)
{
    UpdateControls(false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdFileAddClick(TObject *Sender)
{
    m_bDirty = true;
    m_FileManager.Add(Subst(edtFilename->Text, ' ', '_'));
    UpdateEditor();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdFileRemoveClick(TObject *Sender)
{
    int iAnswer = 1;
    if (m_FileManager.IsFileDirty(lstFiles->ItemIndex))
    {
        // ask to save file first?
        Message
        (
            mbtWarning,
            "The file has changed, would you like to save it?",
			"The file has changed and is unsaved",
            "The file has changes that are not saved.\n\nClick\n\tYes\tto Save the file and then Remove it.\n\tNo\tto not save the file and Remove it.\n\tCancel\tto Cancel the operation and not Remove it.",
            "Cancel",
            "No",
            "Yes",
            iAnswer
        );
        if (iAnswer == 2)
        {
            // save the file being removed
            m_FileManager.Save();
        }
    }
    if (iAnswer != 0)
    {
        String file = lstFiles->Items->Strings[lstFiles->ItemIndex];
        m_bDirty = true;
        m_FileManager.Remove(lstFiles->ItemIndex);
        edtFilename->Text = "";
        UpdateEditor();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdFileRenameClick(TObject *Sender)
{
    String file = lstFiles->Items->Strings[lstFiles->ItemIndex];
    m_bDirty = true;
    int iIndex = lstFiles->ItemIndex;
    m_FileManager.Rename(iIndex, Subst(edtFilename->Text, ' ', '_'));
    UpdateEditor();
    lstFiles->ItemIndex = iIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::UpdateControls(bool bChangeName)
{
    bool bFileExists       = m_FileManager.FileNameExists(edtFilename->Text);
    cmdFileAdd->Enabled    = edtFilename->Text.Trim() != "" && !bFileExists;
    cmdFileRename->Enabled = edtFilename->Text.Trim() != "" && !bFileExists;
    cmdFileRemove->Enabled = -1 != lstFiles->ItemIndex;
    cmdFileMoveUp->Enabled = -1 != lstFiles->ItemIndex;
    cmdFileMoveDown->Enabled = -1 != lstFiles->ItemIndex;

    switch (m_DebugMode)
    {
        case dmPaused:
            tbnDebugPause->Down = true;
            tbnDebugRun->Down = false;
            tbnDebugStop->Down = false;
            break;
        case dmRunning:
            actDebugPause->Enabled = true;
            tbnDebugRun->Down = true;
            tbnDebugStop->Down = false;
            tbnDebugPause->Down = false;
            break;
        //case dmStopped:
        default:
            tbnDebugStop->Down = true;
            tbnDebugRun->Down = false;
            tbnDebugPause->Down = false;
            actDebugPause->Enabled = false;
            break;
    }

    // update internal tools
    tmrDebugger->Enabled = m_DebugMode == dmRunning;
    bool debugEnabled = m_DebugMode == dmPaused;
    actDebugStepOver->Enabled = debugEnabled;
    actDebugStepInto->Enabled = debugEnabled;
    actDebugStepOut->Enabled = debugEnabled;
    actDebugStepBack->Enabled = debugEnabled;
    actDebugRewind->Enabled = debugEnabled;
    actDebugRunToCursor->Enabled = debugEnabled;
    actRewinder->Enabled = debugEnabled;
    actRewindStop->Enabled = debugEnabled;
    actForwarder->Enabled = debugEnabled;

    sciEditor->ReadOnly = debugEnabled;
    sciEditor->HideSelect = sciEditor->ReadOnly;
	sciEditorOther->ReadOnly = debugEnabled;
	sciEditorOther->HideSelect = sciEditorOther->ReadOnly;

    tmrRewind->Enabled = m_TimelapseMode != tmStopped;

    switch (m_TimelapseMode)
    {
        case tmBack:
            tbnRewinder->Down = true;
            tbnRewindStop->Down = false;
            tbnForwarder->Down = false;
            break;
        case tmForward:
            tbnForwarder->Down = true;
            tbnRewindStop->Down = false;
            tbnRewinder->Down = false;
            break;
        default:
            tbnRewindStop->Down = true;
            tbnRewinder->Down = false;
            tbnForwarder->Down = false;
            break;
    }

    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::OnTabMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Shift.Contains(ssMiddle))
    {
        actClosePageExecute(NULL);
    }
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCodeEditor::LoadFile(int iIndex)
{
    m_FileManager.Open(iIndex, false);
    //actToggleSpecialExecute(NULL);
    //g_EditorSettings.Apply();*/
    UpdateEditorSlots();
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::UpdateEditor(void)
{
    UpdateTargetFiles();
    UpdateList();
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::popCutClick(TObject *Sender)
{
    m_ActiveEditor->Editor->Cut();
    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::popCopyClick(TObject *Sender)
{
    m_ActiveEditor->Editor->Copy();
    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::popPasteClick(TObject *Sender)
{
    m_ActiveEditor->Editor->Paste();
    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::popUndoClick(TObject *Sender)
{
    m_ActiveEditor->Editor->Undo();
    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::popRedoClick(TObject *Sender)
{
    m_ActiveEditor->Editor->Redo();
    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actFindExecute(TObject *Sender)
{
    if (m_ActiveEditor->Editor->SelText == "")
    {
        m_ActiveEditor->Editor->SelectWordAtCaret();
    }
    frmSearch->cmbFindText->Text = m_ActiveEditor->Editor->SelText;
    if (true == frmSearch->Execute())
    {
        if (!frmSearch->ProjectFiles)
        {
            // find in active editor
            m_bSearchOnly = true;
            FindText();
        }
        else
        {
            // do find in files
            FindInFiles();
        }
    }
    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actReplaceExecute(TObject *Sender)
{
    if (m_ActiveEditor->Editor->SelText == "")
    {
        m_ActiveEditor->Editor->SelectWordAtCaret();
    }
    frmReplace->cmbFindText->Text = m_ActiveEditor->Editor->SelText;

    if (true == frmReplace->Execute())
    {
        m_bSearchOnly = false;
        FindText();
    }
    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cbrCodeEditorDblClick(TObject *Sender)
{
    tbrCodeTools->Visible = !tbrCodeTools->Visible;
    m_CodeTools->Checked  =  tbrCodeTools->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::UpdateEditorSlots(void)
{
    if (!m_FileManager.IsOpeningFile)
    {
        sciTabControl->Visible = sciTabControl->Count > 0 && !sciTabControl->ActiveDocument->IsUntitled();
        sciTabControlOther->Visible = sciTabControlOther->Count > 0 && !sciTabControlOther->ActiveDocument->IsUntitled();
        String sMsg = IntToStr(m_ActiveEditor->Editor->GetCaretInLine() + 1) + ": " + IntToStr(m_ActiveEditor->Editor->GetCurrentLineNumber() + 1);
        SetStatusSlot(m_PluginHandle, sMsg, 0);
        sMsg = m_ActiveEditor->Editor->GetOvertype() ? "Overwrite" : "Insert";
        SetStatusSlot(m_PluginHandle, sMsg, 1);
        lblFileLines->Caption = "?";
        lblFileCharacters->Caption = "?";
        if (SAFE_PTR(((TScintilla*)m_ActiveEditor->Editor)->Lines))
        {
            lblFileLines->Caption = IntToStr(m_ActiveEditor->Editor->GetLineCount());
            lblFileCharacters->Caption = IntToStr(m_ActiveEditor->Editor->GetLength());
        }
        lblFileDirty->Caption = m_ActiveEditor->Editor->Modified ? String("Yes") : String("No");
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actFindForwardExecute(TObject *Sender)
{
    if (frmSearch->FindText != "")
    {
        frmSearch->Forward  = true;
        frmSearch->FromCursor = true;
        frmSearch->Global = true;
        FindText();
    }
    else
    {
        actFindExecute(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actFindBackwardExecute(TObject *Sender)
{
    if (frmSearch->FindText != "")
    {
        frmSearch->Backward = true;
        frmSearch->FromCursor = true;
        frmSearch->Global = true;
        FindText();
    }
    else
    {
        actFindExecute(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciEditorKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (((TScintilla*)Sender)->ReadOnly)
	{
        g_Debugger->Machine.Keyboard.KeyDown(Key, Shift);
        if (Shift.Contains(ssAlt) && Key == VK_LEFT)
        {
            actRewindExecute(NULL);
        }
        else if (Shift.Contains(ssAlt) && Key == VK_RIGHT)
        {
            actForwardExecute(NULL);
        }
        else if (Shift.Contains(ssAlt) && Key == VK_SPACE)
        {
            actRewindStopExecute(NULL);
        }
    }
    else
    {
        if (Shift.Contains(ssCtrl) && Key == VK_TAB)
        {
            if (Shift.Contains(ssShift))
                actFilePreviousExecute(NULL);
            else
                actFileNextExecute(NULL);
        }
        if (VK_F3 == Key)
        {
            if (false == Shift.Contains(ssShift))
            {
                actFindForwardExecute(Sender);
            }
            else
            {
                actFindBackwardExecute(Sender);
            }
        }
        UpdateEditorSlots();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciEditorKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (((TScintilla*)Sender)->ReadOnly)
    {
        g_Debugger->Machine.Keyboard.KeyUp(Key, Shift);
        if (Shift.Contains(ssAlt) && (Key == VK_LEFT || Key == VK_RIGHT))
        {
            tbnRewindStop->Down = true;
            tbnForwarder->Down = false;
            tbnRewinder->Down = false;
        }
    }
}
//---------------------------------------------------------------------------
/*void __fastcall TfrmCodeEditor::sciEditorReplaceText(TObject *Sender, const AnsiString ASearch, const AnsiString AReplace, int Line, int Column, TSynReplaceAction &Action)
{
    if (ASearch == AReplace)
    {
        Action = raSkip;
    }
    else
    {
        Synedittypes::TDisplayCoord APos;
        APos.Column     = Column;
        APos.Row        = Line;
        TPoint BPos     = sciEditor->ClientToScreen(sciEditor->RowColumnToPixels(APos));
        TRect EditRect  = ClientRect;
        TPoint pt       = ClientToScreen(TPoint(EditRect.Left, EditRect.Top));
        EditRect.Left   = pt.x;
        EditRect.Top    = pt.y;
        pt              = ClientToScreen(TPoint(EditRect.Right, EditRect.Bottom));
        EditRect.Right  = pt.x;
        EditRect.Bottom = pt.y;

        if (false == SAFE_PTR(frmConfirmReplace))
        {
            frmConfirmReplace = new TfrmConfirmReplace(Application);
        }
        if (true == SAFE_PTR(frmConfirmReplace))
        {
            frmConfirmReplace->Execute(EditRect, BPos.x, BPos.y, BPos.y + sciEditor->LineHeight, ASearch);
            switch(frmConfirmReplace->ModalResult)
            {
                case mrYes:         Action = raReplace;     break;
                case mrYesToAll:    Action = raReplaceAll;  break;
                case mrNo:          Action = raSkip;        break;
                default:            Action = raCancel;      break;
            }
        }
    }
}*/
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::Clear(void)
{
    // clear the list and the editor
    lstFiles->Items->Clear();
    // update the gui
    UpdateControls();
    m_bDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actInsertItemExecute(TObject *Sender)
{
    int index = m_FileManager.FindFile(m_ActiveEditor->ActiveDocument->FileName);
    if (index != -1)
    {
        TStrings* pLines = new TStringList();
        if (m_FileManager.GetLines(index, pLines))
        {
            if (m_ParserManager.Execute(pLines, m_FileManager.IsCFile(index)))
            {
                m_FileManager.PutLines(index, pLines);
            }
        }
        SAFE_DELETE(pLines);
    }
    else
    {
        int iAnswer;
        Message
        (
            mbtError,
            "There is no Active Source Code File",
            "There needs to be an active file to insert source code into.",
            "You need to activate a file. If you have not created any source code files.\nPlease Add a file so "
            "your resources can be converted into source code.\n\nGo to the Files Tab, Enter a Name, and Click "
            "the Add Button.\n\nThen simply double click the file in the "
            "Project File List to load it into the Text Editor and Activate it.\n\nThen try to insert a resource.",
            "Ok",
            "",
            "",
            iAnswer
        );
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actUpdateAllResourcesExecute(TObject *Sender)
{
    m_FileManager.Save();
    // update all the resources from all the files
    int i = 0;
    TStrings* pLines = new TStringList();
    while(m_FileManager.GetLines(i, pLines))
    {
        // parse them for resources, and if its the current file then update it in the editor
        if (m_ParserManager.Update(pLines, m_FileManager.GetFilename(i), m_FileManager.IsCFile(i)))
        {
            // update the file if it is not in an active editor
            m_FileManager.PutLines(i, pLines);
        }
        pLines->Clear();
        m_FileManager.GetLines(++i, pLines);
    }
    SAFE_DELETE(pLines);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actToggleSpecialExecute(TObject *Sender)
{
    g_EditorSettings.Apply(sciEditor);
    g_EditorSettings.Apply(sciEditorOther);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdTextMaximizeClick(TObject *Sender)
{
    if (0 != panConsoleContainer->Height && 0 != panEditorMain->Height)
    {
        m_iWindowRestore        = panConsoleContainer->Height;
    }
    panConsoleContainer->Height = 0;//panConsoleHeader->Height/* + 4*/;
    cmdTextMinimize->Enabled    = true;
    cmdTextRestore->Enabled     = true;
    cmdTextMaximize->Enabled    = false;
    //cmdConsoleMinimize->Enabled = false;
    //cmdConsoleRestore->Enabled  = true;
    //cmdConsoleMaximize->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdTextRestoreClick(TObject *Sender)
{
    panConsoleContainer->Height = m_iWindowRestore;
    cmdTextMinimize->Enabled    = true;
    cmdTextRestore->Enabled     = false;
    cmdTextMaximize->Enabled    = true;
    //cmdConsoleMinimize->Enabled = true;
    //cmdConsoleRestore->Enabled  = false;
    //cmdConsoleMaximize->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdTextMinimizeClick(TObject *Sender)
{
    if (0 != panConsoleContainer->Height && 0 != panEditorMain->Height)
    {
        m_iWindowRestore        = panConsoleContainer->Height;
    }
    panConsoleContainer->Height = panEditorContainer->Height - panEditorHeader->Height;
    cmdTextMinimize->Enabled    = false;
    cmdTextRestore->Enabled     = true;
    cmdTextMaximize->Enabled    = true;
    //cmdConsoleMinimize->Enabled = true;
    //cmdConsoleRestore->Enabled  = true;
    //cmdConsoleMaximize->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdTextCloseClick(TObject *Sender)
{
    // 
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::splEditorMoved(TObject *Sender)
{
    m_iWindowRestore            = panConsoleContainer->Height;
    cmdTextMinimize->Enabled    = true;
    cmdTextRestore->Enabled     = false;
    cmdTextMaximize->Enabled    = true;
    //cmdConsoleMinimize->Enabled = true;
    //cmdConsoleRestore->Enabled  = false;
    //cmdConsoleMaximize->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::spnOptionsCodeEditorTabWidthChange(TObject *Sender)
{
    if (true == SAFE_PTR(sciEditor))
    {
        //sciEditor->TabWidth = spnOptionsCodeEditorTabWidth->Value;
    }
    //m_bDirty = true;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCodeEditor::Save(KXmlInfo& xmlInfo, bool bCleanDirty)
{
    m_bWasDirty |= m_FileManager.IsDirty;
    KXmlInfo& Settings = xmlInfo.AddTag("Settings");
    KXmlInfo& BuildTools = Settings.AddTag("BuildTools");
    BuildTools.Add("Tool1", frmBuildOptions->cmbTool1->Text);
    BuildTools.Add("Parameters1", frmBuildOptions->edtParameters1->Text);
    if (frmBuildOptions->cmbTool2->ItemIndex != -1)
    {
        BuildTools.Add("Tool2", frmBuildOptions->cmbTool2->Text);
        BuildTools.Add("Parameters2", frmBuildOptions->edtParameters2->Text);
        if (frmBuildOptions->cmbTool3->ItemIndex != -1)
        {
            BuildTools.Add("Tool3", frmBuildOptions->cmbTool3->Text);
            BuildTools.Add("Parameters3", frmBuildOptions->edtParameters3->Text);
        }
    }
    KXmlInfo& Emulator = Settings.AddTag("Emulator");
    Emulator.Add("Tool", frmBuildOptions->cmbEmulator->Text);
    Emulator.Add("Parameters", frmBuildOptions->edtEmulatorParameters->Text);

    KXmlInfo& Internal = Settings.AddTag("Internal");
    Internal.Add("TargetFile", frmBuildOptions->GetTargetFile());

    m_FileManager.Save(xmlInfo);
    g_Debugger->Breakpoints.Save(xmlInfo);
    frmOSBView->Save(xmlInfo);
    if (bCleanDirty)
    {
        m_bDirty = false;
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCodeEditor::Load(KXmlInfo& xmlInfo)
{
    HRESULT hResult(S_OK);
    KXmlInfo* Settings;
    // clear the gui
    //Clear();
    UpdateTargetFiles();
    g_Debugger->Breakpoints.Load(xmlInfo);
    frmOSBView->Load(xmlInfo);
    // find the settings node
    if (xmlInfo.Find(Settings, "Settings", 0))
    {
        KXmlInfo* SubNode;
        KXmlInfo* Node;
        // get the build tools node
        KXmlInfo* BuildTools;
        if (Settings->Find(BuildTools, "BuildTools", 0))
        {
            if (BuildTools->Find(SubNode, "Tool1", 0))
            {
                frmBuildOptions->SetBuildTool(0, SubNode->GetText());
                if (BuildTools->Find(SubNode, "Parameters1", 0))
                {
                    frmBuildOptions->SetBuildParameters(0, SubNode->GetText());
                }
                if (BuildTools->Find(SubNode, "Tool2", 0))
                {
                    frmBuildOptions->SetBuildTool(1, SubNode->GetText());
                    if (BuildTools->Find(SubNode, "Parameters2", 0))
                    {
                        frmBuildOptions->SetBuildParameters(1, SubNode->GetText());
                    }
                    if (BuildTools->Find(SubNode, "Tool3", 0))
                    {
                        frmBuildOptions->SetBuildTool(2, SubNode->GetText());
                        if (BuildTools->Find(SubNode, "Parameters3", 0))
                        {
                            frmBuildOptions->SetBuildParameters(2, SubNode->GetText());
                        }
                    }
                }
            }
            KXmlInfo* Emulator;
            if (Settings->Find(Emulator, "Emulator", 0))
            {
                if (Emulator->Find(SubNode, "Tool", 0))
                {
                    frmBuildOptions->SetEmulatorTool(SubNode->GetText());
                }
                if (Emulator->Find(SubNode, "Parameters", 0))
                {
                    frmBuildOptions->SetEmulatorParameters(SubNode->GetText());
                }
            }
            KXmlInfo* Internal;
            if (Settings->Find(Internal, "Internal", 0))
            {
                if (Internal->Find(Node, "TargetFile", 0))
                {
                    String sFile = Node->GetText();
                    frmBuildOptions->SetTargetFile(sFile);
                    // load symbols and debug files if they exist
                    String sFolder;
                    PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);
                    // load the map(symbols) file into the debugger
                    sFile = sFolder + sFile;
                    AnsiString mapFile = sFile.SubString(1, sFile.Pos(".")) + "map";
                    g_Debugger->LoadMap(mapFile);
                    // load the debug file
                    AnsiString dbgFile = sFile.SubString(1, sFile.Pos(".")) + "dbg";
                    g_Debugger->Debug.LoadDebugFile(dbgFile);
                    frmOSBView->Update();
                }
            }
        }
        else
        {
            // get the old compilation node and convert to the new build tools
            KXmlInfo* Compilation;
            if (Settings->Find(Compilation, "Compilation", 0))
            {
                // if the build tool node exists then load the settigs
                if (Compilation->Find(Node, "BuildTool", 0))
                {
                    if (Node->Find(SubNode, "Application", 0))
                    {
                        frmBuildOptions->SetBuildTool(0, SubNode->GetText());
                        if (Node->Find(SubNode, "Parameters", 0))
                        {
                            frmBuildOptions->SetBuildParameters(0, SubNode->GetText());
                        }
                    }
                    if (Node->Find(SubNode, "Compiler", 0))
                    {
                        String app = SubNode->GetText();
                        String params;
                        if (app.Length() > 0)
                        {
                            if (Node->Find(SubNode, "CParameters", 0))
                            {
                                params = SubNode->GetText();
                            }
                            if (frmBuildOptions->cmbTool1->ItemIndex == -1)
                            {
                                frmBuildOptions->SetBuildTool(0, app);
                                frmBuildOptions->SetBuildParameters(0, params);
                            }
                            else
                            {
                                frmBuildOptions->SetBuildTool(1, app);
                                frmBuildOptions->SetBuildParameters(1, params);
                            }
                            // if the linking node exists then load the settigs
                            if (Compilation->Find(Node, "Linking", 0))
                            {
                                String app;
                                String params;
                                if (Node->Find(SubNode, "Application", 0))
                                {
                                    app = SubNode->GetText();
                                }
                                if (app.Length() > 0)
                                {
                                    if (Node->Find(SubNode, "Parameters", 0))
                                    {
                                        params = SubNode->GetText();
                                    }
                                    if (frmBuildOptions->cmbTool2->ItemIndex == -1)
                                    {
                                        frmBuildOptions->SetBuildTool(1, app);
                                        frmBuildOptions->SetBuildParameters(1, params);
                                    }
                                    else
                                    {
                                        frmBuildOptions->SetBuildTool(2, app);
                                        frmBuildOptions->SetBuildParameters(2, params);
                                    }
                                }
                            }
                        }
                    }
                }
                // if the emulation node exists then load the settigs
                if (Compilation->Find(Node, "Emulation", 0))
                {
                    if (Node->Find(SubNode, "Applicaton", 0))
                    {
                        frmBuildOptions->SetEmulatorTool(SubNode->GetText());
                    }
                    if (Node->Find(SubNode, "Parameters", 0))
                    {
                        frmBuildOptions->SetEmulatorParameters(SubNode->GetText());
                    }
                }
            }
        }
    }
    m_bDirty = false;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::RunApplication(String sApp, String sParams)
{
    if (FileExists(sApp))
    {
        String sFolder;
        PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);
        if (sFolder.Trim() != "")
        {
            String sOperation("open");
            //String sParameters = edtOptionsBuildToolsEmulatorParameters->Text.Trim();
            DoSubstitutes(sParams);
            ConsolePrint("Launching emulator: " + sApp + " " + sParams);
            if (32 > (int)ShellExecute(NULL, "open", sApp.c_str(), sParams.c_str(), sFolder.c_str(), SW_SHOWNORMAL))
            {
                ConsolePrint("FAILED to launch emulator");
                ShowMessage("Failed to launch Application!");
            }
            else
            {
                ConsolePrint("Emulator launched");
            }
            ConsolePrint("");
        }
    }
    else
    {
        ConsolePrint("Cannot find Emulator executeable. Please check the applications path!");
    }
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCodeEditor::DoSubstitutes(String& sParameters)
{
    bool bChanged = true;
    // get the folder location
    String sFolder;
    PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);
    sFolder = sFolder.Trim();
    if (sFolder.IsEmpty())
        return false;
    // get the projects name from the folder
    String sGame = sFolder;
    if (sGame[sGame.Length()] == '\\')
    {
        sGame = sGame.SubString(1, sGame.Length()-1);
    }
    sGame = sGame.SubString(sGame.LastDelimiter("\\") + 1, 65535);
    // do substitutions
    while (bChanged)
    {
        bChanged = false;
        String sNewParameters = Substitute(sParameters, "%Pfolder%\\", sFolder);
        bChanged = sParameters != sNewParameters;
        sParameters = sNewParameters;
        //sNewParameters = Substitute(sParameters, "%infile%", sInfile);
        //bChanged |= sParameters != sNewParameters;
        //sParameters = sNewParameters;
        sNewParameters = Substitute(sParameters, "%game%", sGame);
        bChanged |= sParameters != sNewParameters;
        sParameters = sNewParameters;
        if (sNewParameters.Pos("%ask%") > 0 && m_FileManager.Files() > 0)
        {
            frmChooseBuildFile = new TfrmChooseBuildFile(NULL);
            frmChooseBuildFile->cmbFiles->Clear();
            for (int i = 0; i < m_FileManager.Files(); ++i)
            {
                frmChooseBuildFile->cmbFiles->Items->Add(m_FileManager.GetFilename(i));
            }
            frmChooseBuildFile->cmbFiles->ItemIndex = 0;
            frmChooseBuildFile->ShowModal();
            sNewParameters = Substitute(sParameters, "%ask%", m_FileManager.GetFilename(frmChooseBuildFile->cmbFiles->ItemIndex));
            sParameters = sNewParameters;
            SAFE_DELETE(frmChooseBuildFile);
        }
    }

    int iDblQuotes = sParameters.Pos("\"\"");
    while (iDblQuotes)
    {
        sParameters = sParameters.SubString(1, iDblQuotes - 1) + sParameters.SubString(iDblQuotes + 1, 10000);
        iDblQuotes = sParameters.Pos("\"\"");
    }

    if (sParameters[1] == '"' && sParameters[sParameters.Length()] == '"')
    {
        for (int i = 2; i < sParameters.Length(); ++i)
        {
            if (sParameters[i] == '"')
            {
                sParameters = sParameters.SubString(1, i - 1) + sParameters.SubString(i + 1, sParameters.Length() - i);
                i = 1;
            }
        }
    }

    return sParameters.AnsiPos("%") <= 0;
}
//---------------------------------------------------------------------------
String __fastcall TfrmCodeEditor::Substitute(const String& sParameters, const String& sFind, const String& sReplace)
{
    String sResult = sParameters;
    if (sFind.Trim() != "" && sReplace.Trim() != "")
    {
        bool bNeedsQuotes = (0 != sReplace.Pos(" "));
        int iLen = sFind.Length();
        int iPos = sParameters.LowerCase().Pos(sFind.LowerCase());
        if (iPos)
        {
            if (bNeedsQuotes)
            {
                int iSpace = sParameters.Length() + 1;
                // find the space after the sFind
                for (int i = iPos + 1; i < iSpace; i++)
                {
                    if (sParameters[i] == ' ')
                    {
                        iSpace = i;
                        break;
                    }
                }
                sResult = sParameters.SubString(1, iPos - 1) +
                          "\"" +
                          sReplace +
                          sParameters.SubString(iPos + iLen, iSpace - (iPos + iLen)) +
                          "\"" +
                          sParameters.SubString(iSpace, 65535);
            }
            else
            {
                sResult = sParameters.SubString(1, iPos - 1) +
                          sReplace +
                          sParameters.SubString(iPos + iLen, 65535);
            }
        }
    }
    return sResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::ConsolePrint(String sMessage)
{
    memoConsole->Lines->Add(sMessage);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actGotoLineExecute(TObject *Sender)
{
    TfrmGotoLine* frmGotoLine = new TfrmGotoLine(NULL);
    if (true == SAFE_PTR(frmGotoLine))
    {
        int iLine = frmGotoLine->Execute();
        if (iLine >= 0)
        {
            // goto the new line
            m_ActiveEditor->Editor->GotoLineEnsureVisible(iLine - 1);
        }
        SAFE_DELETE(frmGotoLine);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::UpdateList(void)
{
    lstFiles->Items->Clear();
    int i = 0;
    String sFile = m_FileManager.GetFilename(i++);
    int iSelected = lstFiles->ItemIndex;
    while (sFile != "")
    {
        lstFiles->Items->Add(sFile);
        sFile = m_FileManager.GetFilename(i++);
    };
    lstFiles->ItemIndex = iSelected;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCodeEditor::ExecuteTool(const String& commandLine)
{
    m_bDosRunning = true;
    m_bDosAborted = false;
    dosCommand->CommandLine = commandLine;
    dosCommand->Execute();
    ConsolePrint("DOS: " + dosCommand->CommandLine);
    //actBuildStop->Enabled = true;
    do
    {
        Application->ProcessMessages();
    }
    while(m_bDosRunning);
    m_bDosRunning = false;

    return !FindErrorInfo();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCodeEditor::Build(ZXToolDefinition builder, TStringList* buildFiles, AnsiString sParameters)
{
    String sTool = builder.m_Executable;
    DoSubstitutes(sTool);
    if (FileExists(sTool))
    {
        bool result = false;
        if (builder.m_AcceptsMultipleInputFiles)
        {
            String filesList;
            // collect all the files and issue 1 build command
            for (int i = 0; i < buildFiles->Count; ++i)
            {
                filesList += buildFiles->Strings[i] + " ";
            }
            sParameters = ReplaceSubString(sParameters, "%files%", filesList);
            result = ExecuteTool(sTool + " " + sParameters);
        }
        else
        {
            // loop through each input file and build it
            for (int i = 0; i < buildFiles->Count; ++i)
            {
                String sParams = ReplaceSubString(sParameters, "%files%", buildFiles->Strings[i]);
                result = ExecuteTool(sTool + " " + sParams);
            }
        }
        return result;
    }
    ConsolePrint("Build Error: Tool is missing! [" + sTool + "]");
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCodeEditor::Pasmo(const String& File)
{
    String pasmo = ExtractFilePath(Application->ExeName) + "\\pasmo\\pasmo.exe";
    if (FileExists(pasmo))
    {
        String params = " -v --debug --sna --equ TOMMYGUN " + File + " " + ChangeFileExt(File, ".sna") + " " + ChangeFileExt(File, ".map");
        return ExecuteTool(pasmo + params);
    }
    ConsolePrint("Build Error: Pasmo.exe is missing! Please re-install TommyGun to restore it. The internal debugger tools require it.");
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCodeEditor::Build(eBuildTypes BuildType, bool useInternalCompiler)
{
    String sFolder;
    PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);

    m_FileManager.ChangeDirectoryAttribute(sFolder.c_str());

    pgcTabs->ActivePage = tabConsole;
    if (frmBuildOptions->chkClearConsole->Checked)
    {
        memoConsole->Lines->Clear();
        Update();
    }
    m_iConsoleStart = memoConsole->Lines->Count;
    if (frmBuildOptions->chkUpdateParserTags->Checked)
    {
        ConsolePrint("Updating Resources...");
        actUpdateAllResourcesExecute(NULL);
        ConsolePrint("Resources Updated.");
    }
    ConsolePrint("Saving Project...");
    m_FileManager.Save();
    ConsolePrint("Project Saved.");

    ConsolePrint("Building Project...");
    if (btBuildAll == BuildType)
    {
        if (sFolder.Trim() != "")
        {
            SetCurrentDir(sFolder);
            ChDir(sFolder);
        }

        if (useInternalCompiler)
        {
            String sFile = frmBuildOptions->GetTargetFile();
            if (sFile.Trim().IsEmpty())
            {
                ConsolePrint("ERROR: Target file is not set. Please set Target file in Build Options.");
                return false;
            }
            if (!FileExists(sFile))
            {
                ConsolePrint("ERROR: Target file was not found. Please set a valid target file in the Build Options.");
                return false;
            }
//            std::string output;
//            if (Pasmo::Compile(sFile.c_str(), output))
            if (Pasmo(sFile))
            {
                // load the .sna file into the emulator
                AnsiString snaFile = sFile.SubString(1, sFile.Pos(".")) + "sna";
                g_Debugger->LoadSNA(snaFile);
                // load the map(symbols) file into the debugger
                AnsiString mapFile = sFile.SubString(1, sFile.Pos(".")) + "map";
                g_Debugger->LoadMap(mapFile);
                // load the debug file
                AnsiString dbgFile = sFile.SubString(1, sFile.Pos(".")) + "dbg";
                g_Debugger->Debug.LoadDebugFile(dbgFile);
            }
            else
            {
                ConsolePrint("Build Error: Failed to build file(s)");
                return false;
            }
        }
        else
        {
            TStringList* ProjectFiles = new TStringList();
            TStringList* BuildFiles = new TStringList();
            try
            {
                // get the list of files to build
                String sTool;
                String sExts;
                String sParameters;
                String sBuildExt;
                ProjectFiles->AddStrings(lstFiles->Items);

                bool built = true;
                for (int i = 0; i < 3; ++i)
                {
                    m_currentBuildToolIndex = i;
                    ZXToolDefinition builder;
                    if (frmBuildOptions->GetBuilder(i, builder))
                    {
                        sExts = builder.m_Extensions;
                        // we add a Space to take care when checking *.asm vs *.a
                        sParameters = frmBuildOptions->GetBuilderParameters(i) + " ";
                        if (!DoSubstitutes(sParameters))
                        {
                            ConsolePrint("Build Warning: Issue encountered during variable substitution. Parameters: [" + sParameters + "]");
                        }

                        std::vector<String> supportedExts;
                        SplitString(sExts, " ,;:\t", supportedExts);
                        for (unsigned int e = 0; e < supportedExts.size(); e++)
                        {
                            String ext = supportedExts[e];
                            if (ext[1] != '.')
                            {
                                ext = "." + ext;
                            }
                            ext += " ";
                        }

                        if (supportedExts.size() == 0)
                        {
                            ConsolePrint("Build tool does not have any supported extensions defined. Tool: " + builder.m_Name);
                            ConsolePrint("   Define the supported file extensions and rebuild.");
                            return false;
                        }

                        if (i == 0)
                        {
                            // find the files to build for the first tool
                            // for assemblers and basic; this is only *.asm, *.bas etc
                            // but for C compilers it means the 2nd tool is a linker so the *.c needs to be changed to *.o

                            // build the list of build files
                            for (unsigned int e = 0; e < supportedExts.size(); e++)
                            {
                                String ext = supportedExts[e].LowerCase();
                                // does *.ext exist in parameters
                                bool acceptAll = sParameters.AnsiPos("*" + ext) > 0;
                                sParameters = ReplaceSubString(sParameters, "*" + ext, "%files%");
                                // file affected files
                                for (int i = 0; i < ProjectFiles->Count; i++)
                                {
                                    String file = ProjectFiles->Strings[i] + " ";
                                    String fext = ExtractFileExt(file).LowerCase().Trim();
                                    if ((fext == ext && sParameters.AnsiPos(file) > 0) || (acceptAll && fext == ext))
                                    {
                                        sBuildExt = ext;
                                        BuildFiles->Add(ProjectFiles->Strings[i]);
                                    }
                                }
                            }
                        }
                        else
                        {
                            // we take the original build files and convert the extensions to the new tool requirement
                            for (unsigned int e = 0; e < supportedExts.size(); e++)
                            {
                                String ext = supportedExts[e];
                                if (sParameters.AnsiPos(ext) > 0)
                                {
                                    sParameters = ReplaceSubString(sParameters, "*" + ext, "%files%");
                                    // found the extension we need, so replace all the previous exts with the new one
                                    for (int i = 0; i < BuildFiles->Count; ++i)
                                    {
                                        ReplaceSubString(BuildFiles->Strings[i], sBuildExt, supportedExts[e]);
                                    }
                                    sBuildExt = ext;
                                    break;
                                }
                            }
                        }

                        built &= Build(builder, BuildFiles, sParameters);
                        if (!built)
                        {
                            ConsolePrint("Build Error: Failed to build file(s)");
                        }
                    }

                    m_currentBuildToolIndex = 0;
                }
            }
            __finally
            {
                SAFE_DELETE(ProjectFiles);
                SAFE_DELETE(BuildFiles);
            }
        }
    }
    else
    {
        BuildMakefile();
    }
    ConsolePrint("Build Process Completed.");

    FindErrorInfo();
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::BuildMakefile(void)
{
    //ConsolePrint("Building project using Makefile...");
    ConsolePrint("Sorry, Makefile support is not implemented yet!");
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdFileMoveUpClick(TObject *Sender)
{
    int iIndex = lstFiles->ItemIndex;
    if (m_FileManager.MoveUp(iIndex))
    {
        UpdateList();
        lstFiles->ItemIndex = iIndex - 1;
        UpdateControls();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::cmdFileMoveDownClick(TObject *Sender)
{
    int iIndex = lstFiles->ItemIndex;
    if (m_FileManager.MoveDown(iIndex))
    {
        UpdateList();
        lstFiles->ItemIndex = iIndex + 1;
        UpdateControls();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actFileNextExecute(TObject *Sender)
{
    if (m_ActiveEditor->TabIndex != -1)
    {
        int index = (m_ActiveEditor->TabIndex + 1) % m_ActiveEditor->Count;
        m_ActiveEditor->Activate(index);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actFilePreviousExecute(TObject *Sender)
{
    if (m_ActiveEditor->TabIndex != -1)
    {
        int index = (m_ActiveEditor->Count + m_ActiveEditor->TabIndex - 1) % m_ActiveEditor->Count;
        m_ActiveEditor->Activate(index);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::pgcEditorChange(TObject *Sender)
{
    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::mnuConsoleGotoErrorinSourceClick(TObject *Sender)
{
    if (pgcTabs->ActivePage == tabConsole)
    {
        String sLine = memoConsole->Lines->Strings[memoConsole->CaretPos.y];
        String sFile;
        int iLineNo = -1;

        if (GotErrorInfo(sLine, sFile, iLineNo) && m_FileManager.FileNameExists(sFile))
        {
            // show the file and position the caret
            LoadFile(m_FileManager.Add(sFile, true));
            UpdateList();
            //sciEditor->CaretY = iLineNo;
            //sciEditor->CaretX = 0;
            Update();
            //sciEditor->SetFocus();
        }
    }
    else
    {
        lstSearchResultsDblClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::mnuConsoleSaveToFileClick(TObject *Sender)
{
    if (pgcTabs->ActivePage == tabConsole)
    {
        dlgSaveCode->FilterIndex = 3;
        dlgSaveCode->FileName = "console.txt";
        if (dlgSaveCode->Execute())
        {
            memoConsole->Lines->SaveToFile(dlgSaveCode->FileName);
        }
        dlgSaveCode->FileName = "";
        dlgSaveCode->FilterIndex = 1;
    }
    else
    {
        dlgSaveCode->FilterIndex = 3;
        dlgSaveCode->FileName = "searchresults.txt";
        if (dlgSaveCode->Execute())
        {
            lstSearchResults->Items->SaveToFile(dlgSaveCode->FileName);
        }
        dlgSaveCode->FileName = "";
        dlgSaveCode->FilterIndex = 1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::memoConsoleDblClick(TObject *Sender)
{
    mnuConsoleGotoErrorinSourceClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actClosePageExecute(TObject *Sender)
{
	if (m_ActiveEditor->ActiveDocument->Modified)
	{
		int iAnswer = 0;
		Message
		(
			mbtWarning,
			"The file has changed, would you like to save it?",
			"The file has been changed is unsaved",
			"The file has changes that are not saved.\n\nClick\n\tYes\tto Save the file and then Remove it.\n\tNo\tto not save the file and Remove it.\n\tCancel\tto Cancel the operation and not Remove it.",
			"Cancel",
			"No",
			"Yes",
			iAnswer
		);
		if (iAnswer == 2)
		{
			// save the file being removed
			m_FileManager.Save();
		}
	}
	m_FileManager.Close(m_ActiveEditor->ActiveDocument->FileName);
	cmdTextClose->Enabled = m_FileManager.OpenedDocuments() > 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::popConsoleClearClick(TObject *Sender)
{
    if (pgcTabs->ActivePage == tabConsole)
    {
        memoConsole->Lines->Clear();
    }
    else
    {
        lstSearchResults->Items->Clear();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actBuildSettingsExecute(TObject *Sender)
{
	frmBuildOptions->Language = ((TScintilla*)m_ActiveEditor->Editor)->SelectedLanguage;
	frmBuildOptions->ShowModal();
	if (m_FileManager.HasOpenDocument())
	{
		g_EditorSettings.Apply(sciTabControl->ActiveDocument);
		g_EditorSettings.Apply((TScintillaMemo*)sciEditor);
		g_EditorSettings.Apply(sciTabControlOther->ActiveDocument);
		g_EditorSettings.Apply((TScintillaMemo*)sciEditorOther);
    }
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::SetDirty(void)
{
    m_bDirty = true;
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::lstFilesEnter(TObject *Sender)
{
    m_bInFileList = true;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::lstFilesExit(TObject *Sender)
{
    m_bInFileList = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actBuildRunExecute(TObject *Sender)
{
    bool result = Build(btBuildAll);
    if (result && !FindErrorInfo() && !m_bDosAborted)
    {
        String executable = frmBuildOptions->GetEmulator();
        if (FileExists(executable))
        {
            RunApplication(executable, frmBuildOptions->GetEmulatorParameters());
        }
        else
        {
            memoConsole->Lines->Add("Emulator executable not found. [" + executable + "]");
        }
    }
    m_bWasDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actHardResetExecute(TObject *Sender)
{
    g_Debugger->Reset();
    actDebugRunExecute(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::popConsoleCopyClick(TObject *Sender)
{
    if (pgcTabs->ActivePage == tabConsole)
    {
        if (memoConsole->SelText.Trim() != "")
        {
            Clipboard()->AsText = memoConsole->SelText;
        }
        else
        {
            Clipboard()->AsText = memoConsole->Lines->Text;
        }
    }
    else
    {
        if (lstSearchResults->ItemIndex != -1)
        {
            Clipboard()->AsText = lstSearchResults->Items->Strings[lstSearchResults->ItemIndex];
        }
        else
        {
            Clipboard()->AsText = lstSearchResults->Items->Text;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::dosCommandTerminated(TObject *Sender, int ExitCode)
{
    //actBuildStop->Enabled = false;
    if (m_bDosAborted)
    {
        ConsolePrint("Build Aborted!");
    }
    else if (ExitCode == 0 && !FindErrorInfo(false))
    {
        ConsolePrint("Build Completed Successfully");
    }
    else
    {
        ConsolePrint("Build Failed!");
        m_bDosAborted = true;
    }
    ConsolePrint("");
    m_bDosRunning = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::lstSearchResultsDblClick(TObject *Sender)
{
    // find the file and line
    if (lstSearchResults->ItemIndex >= 0)
    {
        String sLine = lstSearchResults->Items->Strings[lstSearchResults->ItemIndex];
        int LB = sLine.Pos("(");
        int MB = sLine.Pos(", ");
        int RB = sLine.Pos("):");
        String sFile = sLine.SubString(1, LB - 1);
        int iLine = StrToInt(sLine.SubString(LB + 1, MB - LB - 1));
        int iPos  = StrToInt(sLine.SubString(MB + 2, RB - MB - 2));
        int index = m_FileManager.FindFile(sFile);
        if (index != -1)
        {
            m_FileManager.Open(index, false);
        }
        else
        {
            m_FileManager.Add(sFile, true);
        }
        UpdateList();
        m_ActiveEditor->Editor->SetFocus();
        m_ActiveEditor->Editor->GotoLineEnsureVisible(iLine - 1);
        m_ActiveEditor->Editor->GotoLine(iLine - 1);
        int pos = m_ActiveEditor->Editor->GetCurrentPos();
        m_ActiveEditor->Editor->SetCurrentPos(pos + iPos - 1);
        m_ActiveEditor->Editor->SetAnchor(pos + iPos - 1);
        Update();
    }
}
//---------------------------------------------------------------------------
String __fastcall TfrmCodeEditor::ReplaceSubString(const String& text, const String& find, const String& replace)
{
    String newText = text;
    int pos = text.LowerCase().AnsiPos(find.LowerCase());
    while (pos > 0)
    {
        String tmpText = newText.SubString(1, pos - 1) + replace + (newText.SubString(pos + find.Length(), newText.Length() - find.Length()));
        newText = tmpText;
        pos = newText.LowerCase().AnsiPos(find.LowerCase());
    }
    return newText;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::SplitString(const String& text, const String& seps, std::vector<String>& list)
{
    list.clear();
    String split;
    for (int i = 1; i <= text.Length(); ++i)
    {
        if (text.IsDelimiter(seps, i))
        {
            if (!split.IsEmpty())
            {
                list.push_back(split);
                split = "";
            }
        }
        else
        {
            split += text[i];
        }
    }
    if (!split.IsEmpty())
    {
        list.push_back(split);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciTabControlDetectHighlighter(TObject *Sender, const AnsiString Extension, AnsiString &Language)
{
    if (m_ExtMapper != NULL)
    {
        Language = m_ExtMapper->DetectLanguage(Extension);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciTabControlMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TSciDocumentTabControl* tabControl = (TSciDocumentTabControl*)Sender;
	if (Shift.Contains(ssMiddle))
	{
		int index = tabControl->IndexOfTabAt(X,Y);
		if (index == -1)
			return;

		if (tabControl->Document[index]->Modified)
		{
			int iAnswer = 0;
			Message
			(
				mbtWarning,
				"The file has changed, would you like to save it?",
				"The file has been changed is unsaved",
				"The file has changes that are not saved.\n\nClick\n\tYes\tto Save the file and then Remove it.\n\tNo\tto not save the file and Remove it.\n\tCancel\tto Cancel the operation and not Remove it.",
				"Cancel",
				"No",
				"Yes",
				iAnswer
			);
			if (iAnswer == 2)
			{
				// save the file being removed
				m_FileManager.Save();
			}
		}
		if (!m_FileManager.Close(tabControl->Document[index]->FileName))
		{
			tabControl->Close(index);
		}
        cmdTextClose->Enabled = tabControl->Count > 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciEditorEnter(TObject *Sender)
{
    m_bEditting = true;
	TScintilla* editor = (TScintilla*)Sender;
    m_ActiveEditor = sciTabControl->Editor == editor ? sciTabControl : sciTabControlOther;
    sciSearchReplace->Editor = editor;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciEditorExit(TObject *Sender)
{
    m_bEditting = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciEditorModified(TObject *Sender, const int position, const int modificationType, PChar text, const int len, const int linesAdded, const int line, const int foldLevelNow, const int foldLevelPrev)
{
	if (Sender == sciEditor && !sciEditor->ReadOnly)
	{
		m_FileManager.sciEditorModified(Sender, position, modificationType, text, len, linesAdded, line, foldLevelNow, foldLevelPrev);
        sciEditor->Modified = false;
	}
	if (Sender == sciEditorOther && !sciEditorOther->ReadOnly)
	{
		m_FileManager.sciEditorModifiedOther(Sender, position, modificationType, text, len, linesAdded, line, foldLevelNow, foldLevelPrev);
        sciEditorOther->Modified = false;
	}
	UpdateEditorSlots();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciTabControlClosing(TObject *Sender, const int TabIndex, bool &AllowClose)
{
    m_FileManager.AdjustTabIndexes(TabIndex);
    AllowClose = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciTabControlChange(TObject *Sender)
{
	TSciDocumentTabControl* tabControl = (TSciDocumentTabControl*)Sender;
	tabControl->Visible = tabControl->Count > 1 || !tabControl->ActiveDocument->IsUntitled();
    UpdateEditorSlots();
    UpdateBreakpoints();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciSearchReplaceTextNotFound(TObject *Sender)
{
    if (frmSearch->Global)
    {
        if (!m_bSearchBackwards)
        {
            m_ActiveEditor->Activate((m_ActiveEditor->TabIndex + 1) % sciTabControl->Count);
            sciSearchReplace->Editor->GotoLineEnsureVisible(0);
            sciSearchReplace->DoSearchReplaceText(m_bSearchReplace, m_bSearchBackwards, m_SearchReplaceConfirmation);
        }
        else
        {
            m_ActiveEditor->Activate((m_ActiveEditor->Count + m_ActiveEditor->TabIndex - 1) % m_ActiveEditor->Count);
            m_ActiveEditor->Editor->GotoLineEnsureVisible(((TScintilla*)m_ActiveEditor->Editor)->Lines->Count - 1);
            sciSearchReplace->DoSearchReplaceText(m_bSearchReplace, m_bSearchBackwards, m_SearchReplaceConfirmation);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciEditorUpdateUI(TObject *Sender)
{
    UpdateEditorSlots();
}
//---------------------------------------------------------------------------
// STATE VIEW
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actToggleDisplayExecute(TObject *Sender)
{
    frmDisplayView->Visible = !frmDisplayView->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actToggleOSBExecute(TObject *Sender)
{
    frmOSBView->Visible = !frmOSBView->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::tmrDebuggerTimer(TObject *Sender)
{
    if (!m_bTrace)
    {
        g_Debugger->Run();
    }
    else
    {
        g_Debugger->StepInto();
        HighlightCurrentLine();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugRunExecute(TObject *Sender)
{
    if (m_DebugMode == dmStopped)
    {
        m_DebugMode = dmRunning;
        g_Debugger->Breakpoints.Reset();
        if (Build(btBuildAll, true))
        {
            frmOSBView->Update();
            actDebugPause->Enabled = true;
            tmrDebugger->Enabled = true;
            UpdateControls();
        }
        else
        {
            actDebugStopExecute(NULL);
        }
    }
    else
    {
        m_DebugMode = dmRunning;
        UpdateControls();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugPauseExecute(TObject *Sender)
{
    m_DebugMode = dmPaused;
    tmrDebugger->Enabled = false;
    UpdateControls();
    // get current address from emulator
    HighlightCurrentLine();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugStopExecute(TObject *Sender)
{
    m_DebugMode = dmStopped;
    g_Debugger->Machine.SnapshotReset();
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugStepOverExecute(TObject *Sender)
{
    g_Debugger->StepOver();
    HighlightCurrentLine();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugStepIntoExecute(TObject *Sender)
{
    g_Debugger->StepInto();
    HighlightCurrentLine();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugStepOutExecute(TObject *Sender)
{
    g_Debugger->StepOut();
    HighlightCurrentLine();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugRunToCursorExecute(TObject *Sender)
{
    HighlightCurrentLine();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugToggleBreakpointExecute(TObject *Sender)
{
    String File;
    int Line;
    TSciMarker* marker = m_ActiveEditor == sciTabControl ? m_BreakpointMarker : m_BreakpointMarkerOther;
    if (m_FileManager.ActiveDocument(m_ActiveEditor, File, Line))
    {
        if (marker->Present(Line))
        {
            g_Debugger->Breakpoints.Remove(File, Line + 1);
            marker->Delete(Line);
        }
        else
        {
            g_Debugger->Breakpoints.Add(File, Line + 1);
            marker->Add(Line);
        }
        UpdateBreakpoints();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugStepBackExecute(TObject *Sender)
{
    HighlightCurrentLine();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugRewindExecute(TObject *Sender)
{
    HighlightCurrentLine();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::HighlightCurrentLine()
{
    Z80 context;
    g_Debugger->Machine.GetContext(context);
    int line;
    String file;
    g_Debugger->Debug.GetLocation(context.PC.W, file, line);
    if (line != -1 && file != "")
    {
        HighlightLine(file, line);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::HighlightLine(const String& File, int Line)
{
    int iFile = m_FileManager.FindFile(ExtractFileName(File));
    if (iFile != -1)
    {
        TScintilla* editor = m_FileManager.InOtherView(iFile) ? sciEditorOther : sciEditor;

        if (!m_FileManager.IsFileOpen(iFile))
        {
            m_FileManager.Open(iFile, false);
        }
        else
        {
            m_FileManager.SelectFile(iFile);
        }
        editor->MarkerDeleteAll(DEBUG_HIGHLIGHTER_MARKER);
        if (editor->ReadOnly)
        {
            editor->MarkerAdd(Line - 1, DEBUG_HIGHLIGHTER_MARKER);
        }
        editor->GotoLineEnsureVisible(Line - 1);
        UpdateControls();
        editor->Update();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::pgcCodeEditorDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    static Graphics::TBitmap* bm = NULL;
    Control->Canvas->Brush->Color = clWhite;
    Control->Canvas->FillRect(Rect);
    TTabSheet* sheet = pgcCodeEditor->Pages[TabIndex];
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
    pgcCodeEditor->Images->Draw(Control->Canvas, rl + 10 + cx - cw - 20, rt + cy - 8, sheet->ImageIndex, true);

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
void __fastcall TfrmCodeEditor::actDebugTraceExecute(TObject *Sender)
{
    m_bTrace = actDebugTrace->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::OnBreakpointHit(const String& File, int Line)
{
    actDebugPauseExecute(NULL);
    tbnDebugPause->Down = true;
    tbnDebugRun->Down = false;
    HighlightLine(File, Line);
    ConsolePrint("Breakpoint Hit: " + File + "@" + IntToStr(Line));
    UpdateBreakpoints();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciEditorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft && Shift.Contains(ssCtrl))
	{
		TScintilla* editor = (TScintilla*)Sender;
		editor->SelectWordAtCaret();
		String word = editor->SelText;
		editor->SelLength = 0;
		editor->SelStart = 0;
		unsigned int address = g_Debugger->Symbols.GetSymbol(word);
		if (address != 0)
		{
			String file;
			int line;
            g_Debugger->Debug.GetLocation(address, file, line);
            HighlightLine(file, line);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::pgcTabsDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    static Graphics::TBitmap* bm = NULL;
    Control->Canvas->Brush->Color = clWhite;
    Control->Canvas->FillRect(Rect);
    TTabSheet* sheet = pgcTabs->Pages[TabIndex];
    int cw = Control->Canvas->TextWidth(sheet->Caption) / 2;
    int ch = Control->Canvas->TextHeight(sheet->Caption) / 2;
    int rl = Rect.Left;
    int rt = Rect.Top;
    int cx = Rect.Width() / 2;
    int cy = Rect.Height() / 2;
    Control->Canvas->Font->Color = clBlack;
    Control->Canvas->Font->Height = 12;
    Control->Canvas->Font->Style = Active ? TFontStyles() << fsBold : TFontStyles();
    Control->Canvas->TextRect(Rect, rl + 10 + cx - cw, rt + cy - ch, sheet->Caption);
    pgcTabs->Images->Draw(Control->Canvas, rl + 10 + cx - cw - 20, rt + cy - 8, sheet->ImageIndex, true);

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
        TRect tr(Rect.left, Rect.top, Rect.right, Rect.top + 3);
        Control->Canvas->StretchDraw(tr, bm);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugAddBreakpointExecute(TObject *Sender)
{
    //    
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugDeleteBreakpointExecute(TObject *Sender)
{
    if (lstBreakpoints->ItemIndex != -1)
    {
        TListItem* lvi = lstBreakpoints->Items->Item[lstBreakpoints->ItemIndex];
        String file = lvi->SubItems->Strings[0];
        int line = StrToInt(lvi->SubItems->Strings[1]);
        g_Debugger->Breakpoints.Remove(file, line);
        UpdateBreakpoints();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugDeleteAllBreakpointsExecute(TObject *Sender)
{
    g_Debugger->Breakpoints.RemoveAll();
    UpdateBreakpoints();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugEnableAllBreakpointsExecute(TObject *Sender)
{
    g_Debugger->Breakpoints.EnableAll();
    UpdateBreakpoints();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugDisableAllBreakpointsExecute(TObject *Sender)
{
    g_Debugger->Breakpoints.DisableAll();
    UpdateBreakpoints();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actDebugBreakpointPropertiesExecute(TObject *Sender)
{
    if (lstBreakpoints->ItemIndex != -1)
    {
        TListItem* lvi = lstBreakpoints->Items->Item[lstBreakpoints->ItemIndex];
        String file = lvi->SubItems->Strings[0];
        int line = StrToInt(lvi->SubItems->Strings[1]);
        TBreakpoint bp = g_Debugger->Breakpoints.Get(file, line);
        if (bp.file != "")
        {
            TfrmBreakpointProperties* fBp = new TfrmBreakpointProperties(NULL);
            if (fBp->Execute(true, bp, m_FileManager))
            {
                // update breakpoint
                g_Debugger->Breakpoints.PassCount(file, line, bp.passCountReset);
                UpdateBreakpoints();
            }
            SAFE_DELETE(fBp);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::tabBreakpointsShow(TObject *Sender)
{
    UpdateBreakpoints();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::UpdateBreakpoints()
{
    if (m_BreakpointMarker == NULL || m_BreakpointMarkerOther == NULL)
        return;
    try
    {
        // refresh the breakpoint list
        TBreakpointList breakpoints;
        g_Debugger->Breakpoints.Get(breakpoints);
        if (lstBreakpoints->Items->Count != (int)breakpoints.size())
        {
            lstBreakpoints->Items->Clear();
            m_BreakpointMarker->ClearAll();
            m_BreakpointMarkerOther->ClearAll();
            for (TBreakpointListIt it = breakpoints.begin(); it != breakpoints.end(); ++it)
            {
                TListItem* lvi = lstBreakpoints->Items->Add();
                lvi->Checked = it->enabled;
                lvi->SubItems->Add(it->file);
                lvi->SubItems->Add(IntToStr(it->line));
                lvi->SubItems->Add(IntToStr(it->passCountReset));
                if (it->enabled && m_FileManager.IsActiveDocument(sciTabControl, it->file))
                {
                    m_BreakpointMarker->Add(it->line - 1);
                }
                if (it->enabled && m_FileManager.IsActiveDocument(sciTabControlOther, it->file))
                {
                    m_BreakpointMarkerOther->Add(it->line - 1);
                }
            }
            lstBreakpoints->Update();
        }
        else
        {
            // update the items already there
            int i = 0;
            m_BreakpointMarker->ClearAll();
            m_BreakpointMarkerOther->ClearAll();
            for (TBreakpointListIt it = breakpoints.begin(); it != breakpoints.end(); ++it, ++i)
            {
                TListItem* lvi = lstBreakpoints->Items->Item[i];
                lvi->Checked = it->enabled;
                lvi->SubItems->Strings[0] = it->file;
                lvi->SubItems->Strings[1] = IntToStr(it->line);
                lvi->SubItems->Strings[2] = IntToStr(it->passCountReset);
                if (it->enabled)
                {
                    if (m_FileManager.IsActiveDocument(sciTabControl, it->file))
                        m_BreakpointMarker->Add(it->line - 1);
                    if (m_FileManager.IsActiveDocument(sciTabControlOther, it->file))
                        m_BreakpointMarkerOther->Add(it->line - 1);
                }
            }
            lstBreakpoints->Update();
        }
    }
    catch(...)
    {
        // ummm, scintilla is not quite ready
    }
    actDebugAddBreakpoint->Enabled = false;
    actDebugDeleteBreakpoint->Enabled = lstBreakpoints->ItemIndex != -1;
    actDebugDeleteAllBreakpoints->Enabled = lstBreakpoints->Items->Count > 0;
    actDebugDisableAllBreakpoints->Enabled = lstBreakpoints->Items->Count > 0;
    actDebugEnableAllBreakpoints->Enabled = lstBreakpoints->Items->Count > 0;
    actDebugBreakpointProperties->Enabled = lstBreakpoints->ItemIndex != -1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::lstBreakpointsChanging(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange)
{
    AllowChange = Change == ctState;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::lstBreakpointsChange(TObject *Sender, TListItem *Item, TItemChange Change)
{
    if (lstBreakpoints->Items->Count > 0 && Item->SubItems->Count == 2)
    {
        bool enabled = Item->Checked;
        String file = Item->SubItems->Strings[0];
        int line = StrToInt(Item->SubItems->Strings[1]);

        if (enabled)
        {
            g_Debugger->Breakpoints.Enable(file, line);
        }
        else
        {
            g_Debugger->Breakpoints.Disable(file, line);
        }
        if (m_FileManager.IsActiveDocument(m_ActiveEditor, file))
        {
            TSciMarker* marker = m_ActiveEditor == sciTabControl ? m_BreakpointMarker : m_BreakpointMarkerOther;
            marker->Delete(line - 1);
            if (enabled)
            {
                marker->Add(line - 1);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::lstBreakpointsSelectItem(TObject *Sender, TListItem *Item, bool Selected)
{
    actDebugDeleteBreakpoint->Enabled = lstBreakpoints->ItemIndex != -1;
    actDebugBreakpointProperties->Enabled = lstBreakpoints->ItemIndex != -1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::lstBreakpointsDblClick(TObject *Sender)
{
    if (lstBreakpoints->ItemIndex != -1)
    {
        actDebugBreakpointPropertiesExecute(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actBookmarkToggleExecute(TObject *Sender)
{
    String File;
    int Line;
    TSciMarker* bookMarker = m_ActiveEditor == sciTabControl ? m_BookMarker : m_BookMarkerOther;
    if (m_FileManager.ActiveDocument(m_ActiveEditor, File, Line))
    {
        if (bookMarker->Present(Line))
        {
            bookMarker->Delete(Line);
        }
        else
        {
            bookMarker->Add(Line);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actBookmarkNextExecute(TObject *Sender)
{
    TSciMarker* bookMarker = m_ActiveEditor == sciTabControl ? m_BookMarker : m_BookMarkerOther;
    bookMarker->Next();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actBookmarkPreviousExecute(TObject *Sender)
{
    TSciMarker* bookMarker = m_ActiveEditor == sciTabControl ? m_BookMarker : m_BookMarkerOther;
    bookMarker->Next(false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actBookmarkClearExecute(TObject *Sender)
{
    m_BookMarker->ClearAll();
    m_BookMarkerOther->ClearAll();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::sciEditorMarginClick(TObject *Sender, const int modifiers, const int position, const int margin)
{
	((TScintilla*)Sender)->GotoPos(position);
    actDebugToggleBreakpointExecute(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actRewindExecute(TObject *Sender)
{
    if (tbnDebugPause->Down)
    {
        bool canRun = g_Debugger->Machine.SnapshotRewind();
        g_Debugger->UpdateDisplay();
        UpdateControls();
        if (!tbnRewinder->Down)
        {
            HighlightCurrentLine();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actForwardExecute(TObject *Sender)
{
    if (tbnDebugPause->Down)
    {
        bool canRun = g_Debugger->Machine.SnapshotForward();
        g_Debugger->UpdateDisplay();
        UpdateControls();
        if (!tbnForwarder->Down)
        {
            HighlightCurrentLine();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::tmrRewindTimer(TObject *Sender)
{
    if (m_TimelapseMode == tmBack)
    {
        actRewindExecute(NULL);
    }
    else if (m_TimelapseMode == tmForward)
    {
        actForwardExecute(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actRewinderExecute(TObject *Sender)
{
    m_TimelapseMode = tmBack;
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actForwarderExecute(TObject *Sender)
{
    m_TimelapseMode = tmForward;
    UpdateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actRewindStopExecute(TObject *Sender)
{
    m_TimelapseMode = tmStopped;
    UpdateControls();
    HighlightCurrentLine();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::actMoveViewExecute(TObject *Sender)
{
	String file = m_ActiveEditor->ActiveDocument->FileName;
	m_FileManager.Save();
	m_FileManager.Close(file);
	m_FileManager.Open(m_FileManager.FindFile(file), m_ActiveEditor == sciTabControl);
    UpdateBreakpoints();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::popCodeEditorPopup(TObject *Sender)
{
    actMoveView->Enabled = m_FileManager.OpenedDocuments() >= 2;
    m_ActiveEditor = popCodeEditor->PopupComponent == sciEditor ? sciTabControl : sciTabControlOther;
}
//---------------------------------------------------------------------------


