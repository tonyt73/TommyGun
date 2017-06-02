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
//-- CONSTANTS --------------------------------------------------------------
const   String  g_sPluginTitle      = "Code";
const   int     g_iSNAFileSize      = 49179;
const   int     g_iSNAHeaderSize    =    27;
//---------------------------------------------------------------------------
// Initialise
/**
 * Initialises the object, and integrates into the Shell evnironment
 * @param   PluginHandle the handle allocated to the plugin
 * @return  S_OK initialization successful, S_FALSE initalization failed
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCodeEditor::Initialise(TZX_HPLUGIN PluginHandle)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    // save the plugin handle
    m_PluginHandle = PluginHandle;
    // place the form onto the tab control
    TWinControl* tmpWindow = NULL;
    hResult = S_FALSE;
    if (S_OK == AddPage(PluginHandle, tmpWindow, g_sPluginTitle))
    {
        if (NULL != tmpWindow->Handle)
        {
            m_TabHandle = tmpWindow->Handle;
            hResult = SetPageBitmap( m_PluginHandle, m_TabHandle, imgSmallIcon, imgLargeIcon );
            Parent = tmpWindow;
            Visible = true;
            AddPluginIcon(m_PluginHandle, imgSmallIcon, "");
            TrapTabEvents(tmpWindow);
            AttachToolbars();
            OnTabHide(NULL);
            LoadSettings();
            m_bInitialized = true;
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
// Release
/**
 * Releases the resources associated with the Plugin
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCodeEditor::Release(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    SaveSettings();
    CloseDocuments();
    SAFE_DELETE(m_CodeTools);
    // Hide the form before releasing
    Visible = false;
    try
    {
        // Detach ourselves from the parent
        Parent->RemoveControl(this);
        // remove the tab we were allocated by shell
        RemovePage(m_PluginHandle, m_TabHandle);
    }
    catch(...)
    {
    }
    // reset our handle
    m_PluginHandle = 0;
    m_bInitialized = false;
    SAFE_DELETE(g_Debugger);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::AttachToolbars(void)
{
    TMenuItem* ViewMenu = Application->MainForm->Menu->Items->Find("View");
    if (ViewMenu)
    {
        TMenuItem* Toolbars = ViewMenu->Find("Toolbars");
        if (Toolbars)
        {
            m_CodeTools              = new TMenuItem(NULL);
            m_CodeTools->Caption     = "Code Tools";
            m_CodeTools->Checked     = true;
            m_CodeTools->Tag         = (int)tbrCodeTools;
            m_CodeTools->OnClick     = OnMenuClick;
            m_CodeTools->Visible     = S_OK == IsActivePlugin(m_PluginHandle);
            Toolbars->Add(m_CodeTools);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::OnMenuClick(TObject* Sender)
{
    TMenuItem* Menu = dynamic_cast<TMenuItem*>(Sender);
    if (true == SAFE_PTR(Menu))
    {
        Menu->Checked = !Menu->Checked;
        TToolBar* Toolbar = (TToolBar*)(Menu->Tag);
        if (true == SAFE_PTR(Toolbar))
        {
            Toolbar->Visible = Menu->Checked;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::TrapTabEvents(TWinControl* Control)
{
    if (true == SAFE_PTR(Control))
    {
        TTabSheet* TabSheet = dynamic_cast<TTabSheet*>(Control);
        if (true == SAFE_PTR(TabSheet))
        {
            TabSheet->OnHide = OnTabHide;
            TabSheet->OnShow = OnTabShow;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::OnTabHide(TObject *Sender)
{
    if (m_CodeTools != NULL)
    {
        actGotoLine->Enabled = false;
        actGotoLine->Visible = false;
        actBookmarkToggle->Enabled = false;
        actBookmarkToggle->Visible = false;
        actBookmarkNext->Enabled = false;
        actBookmarkNext->Visible = false;
        actBookmarkPrevious->Enabled = false;
        actBookmarkPrevious->Visible = false;
        actBookmarkClear->Enabled = false;
        actBookmarkClear->Visible = false;
        m_CodeTools->Visible = false;
        m_mnuBuild->Visible = false;
        MenusRemove();
        m_ParserManager.Hide();
        frmDisplayView->Visible = false;
        frmOSBView->Visible = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::OnTabShow(TObject *Sender)
{
    if (m_CodeTools != NULL)
    {
        MenusAdd();
        m_CodeTools->Visible = true;
        actGotoLine->Visible = true;
        actGotoLine->Enabled = true;
        actBookmarkToggle->Enabled = true;
        actBookmarkToggle->Visible = true;
        actBookmarkNext->Enabled = true;
        actBookmarkNext->Visible = true;
        actBookmarkPrevious->Enabled = true;
        actBookmarkPrevious->Visible = true;
        actBookmarkClear->Enabled = true;
        actBookmarkClear->Visible = true;
        mnuToggleSpecial->Enabled = true;
        m_mnuBuild->Visible = true;
        frmDisplayView->Visible = true;
        frmOSBView->Visible = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::BinToSna(const String& sBinFile, int iAddress)
{
    // get the sna buffer
    int i = 0;
    unsigned char* Snapshot = new unsigned char[g_iSNAFileSize];
    if (true == SAFE_PTR(Snapshot))
    {
        for (int y = 0; y < 129; y++)
        {
            unsigned char* sl = (unsigned char*)imgBlankSna->Picture->Bitmap->ScanLine[y];
            for (int x = 0; x < 192; x++)
            {
                if (i < g_iSNAFileSize)
                {
                    Snapshot[i++] = sl[x * 2 + 0];
                    Snapshot[i++] = sl[y * 2 + 1];
                }
            }
        }

        // load the bin file and merge it in
        FILE* fh = fopen(sBinFile.c_str(), "rb");
        if (fh)
        {
            fseek(fh, 0, SEEK_END);
            int iSize = ftell(fh);
            fseek(fh, 0, SEEK_SET);
            unsigned char* pBinBuffer = new unsigned char(iSize);
            fread(pBinBuffer, 1, iSize, fh);
            fclose(fh);
            // put the bin buffer into the snap shot
            iAddress -= 16384;
            CopyMemory(Snapshot + iAddress + g_iSNAHeaderSize, pBinBuffer, iSize);
            // write the snapshot memory to the snapshot file
            String sSnaFile = ChangeFileExt(sBinFile, ".sna");
            fh = fopen(sSnaFile.c_str(), "wb");
            if (NULL != fh)
            {
                fwrite(Snapshot, 1, g_iSNAFileSize, fh);
                fclose(fh);
            }
            else
            {
                ConsolePrint("Bin2Sna: Error - Failed to write SnapShot buffer to the file: " + sSnaFile);
            }
            SAFE_DELETE(pBinBuffer);
        }
        else
        {
            ConsolePrint("Bin2Sna: Error - Failed to open the file: " + sBinFile);
        }
        SAFE_ARRAY_DELETE(Snapshot);
    }
    else
    {
        ConsolePrint("Bin2Sna: Error - Failed to allocate memory for SnapShot buffer");
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::SaveSettings(void)
{
    //regScorpio->Write("CodeEditor", "TabAsSpaces", chkOptionsCodeEditorTabsAsSpace->Checked);
    //regScorpio->Write("CodeEditor", "TabWidth", spnOptionsCodeEditorTabWidth->Value);
    regScorpio->Write("CodeEditor", "BuildUpdateResources", frmBuildOptions->chkUpdateParserTags->Checked);
    if (frmBuildOptions->chkOptionsCodeEditorResourceOverwrite->Checked) regScorpio->Write("CodeEditor", "DuplicateResource", 0);
    if (frmBuildOptions->chkOptionsCodeEditorResourceSkip->Checked) regScorpio->Write("CodeEditor", "DuplicateResource", 1);
    if (frmBuildOptions->chkOptionsCodeEditorResourceAsk->Checked) regScorpio->Write("CodeEditor", "DuplicateResource", 2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::LoadSettings(void)
{
    bool bValue = false;
    int  iValue = 0;
    //if (regScorpio->Read("CodeEditor", "TabAsSpaces", bValue))   chkOptionsCodeEditorTabsAsSpace->Checked = bValue;
    //if (regScorpio->Read("CodeEditor", "TabWidth", iValue))    spnOptionsCodeEditorTabWidth->Value = iValue;
    if (regScorpio->Read("CodeEditor", "BuildUpdateResources", bValue)) frmBuildOptions->chkUpdateParserTags->Checked = bValue;
    if (regScorpio->Read("CodeEditor", "DuplicateResource", iValue))
    {
        frmBuildOptions->chkOptionsCodeEditorResourceOverwrite->Checked = iValue == 0;
        frmBuildOptions->chkOptionsCodeEditorResourceSkip->Checked = iValue == 1;
        frmBuildOptions->chkOptionsCodeEditorResourceAsk->Checked = iValue == 2;
    }
    // load the tools definitions
    frmBuildOptions->Load();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::DeleteKey(void)
{
    if (m_bEditting && true == SAFE_PTR(m_ActiveEditor->Editor))
    {
        SendMessage(m_ActiveEditor->Editor->Handle, WM_KEYDOWN, VK_DELETE, 0);
    }
    else
    {
        if (ActiveControl)
        {
            SendMessage(ActiveControl->Handle, WM_KEYDOWN, VK_DELETE, 0);
        }
        else if (m_bInFileList)
        {
            cmdFileRemoveClick(NULL);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::EditCopy(void)
{
    if (m_bEditting && true == SAFE_PTR(m_ActiveEditor->Editor))
    {
        SendMessage(m_ActiveEditor->Editor->Handle, WM_COPY, 0, 0);
    }
    else
    {
        if (frmBuildOptions->Visible)
        {
            frmBuildOptions->EditCopy();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::EditCut(void)
{
    if (m_bEditting && true == SAFE_PTR(m_ActiveEditor->Editor))
    {
        SendMessage(m_ActiveEditor->Editor->Handle, WM_CUT, 0, 0);
    }
    else
    {
        if (frmBuildOptions->Visible)
        {
            frmBuildOptions->EditCut();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::EditPaste(void)
{
    if (m_bEditting && true == SAFE_PTR(m_ActiveEditor->Editor))
    {
        SendMessage(m_ActiveEditor->Editor->Handle, WM_PASTE, 0, 0);
    }
    else
    {
        if (frmBuildOptions->Visible)
        {
            frmBuildOptions->EditPaste();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::MenusAdd(void)
{
    if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
    {
        popMenus->Items->Remove(mnuGotoLine);
        popMenus->Items->Remove(mnuToggleSpecial);
        popMenus->Items->Remove(mnuBookmarkToggle);
        popMenus->Items->Remove(mnuBookmarkNext);
        popMenus->Items->Remove(mnuBookmarkPrevious);
        popMenus->Items->Remove(mnuBookmarkClear);
        popBuild->Items->Remove(mnuRun);
        popBuild->Items->Remove(mnuOptions);
        popBuild->Items->Remove(mnuBuildSettings);
        popBuild->Items->Remove(mnuDebugRun);
        popBuild->Items->Remove(mnuDebugRunToCursor);
        popBuild->Items->Remove(mnuDebugStop);
        popBuild->Items->Remove(mnuDebugStepOver);
        popBuild->Items->Remove(mnuDebugStepInto);
        popBuild->Items->Remove(mnuDebugStepOut);
        popBuild->Items->Remove(mnuToggleBreakpoint);
        popBuild->Items->Remove(mnuToggleDisplay);
        popBuild->Items->Remove(mnuToggleOSB);
        TMenuItem* mnuEdit = Application->MainForm->Menu->Items->Find("&Edit");
        if (true == SAFE_PTR(mnuEdit))
        {
            mnuEdit->NewBottomLine();
            mnuEdit->Add(mnuGotoLine);
            mnuEdit->Add(mnuToggleSpecial);
            mnuEdit->NewBottomLine();
            mnuEdit->Add(mnuBookmarkToggle);
            mnuEdit->Add(mnuBookmarkNext);
            mnuEdit->Add(mnuBookmarkPrevious);
            mnuEdit->Add(mnuBookmarkClear);
            mnuToggleSpecial->Visible = false;
            mnuGotoLine->Visible = false;
            mnuGotoLine->ImageIndex = -1;
            mnuBookmarkToggle->Visible = false;
            mnuBookmarkNext->Visible = false;
            mnuBookmarkPrevious->Visible = false;
            mnuBookmarkClear->Visible = false;

            if (m_mnuBuild == NULL)
            {
                AddMenu("&Code", m_mnuBuild);
            }
            if (m_mnuBuild)
            {
                m_mnuBuild->Add(mnuRun);
                m_mnuBuild->NewBottomLine();
                m_mnuBuild->Add(mnuOptions);
                m_mnuBuild->Add(mnuBuildSettings);
                m_mnuBuild->NewBottomLine();
                m_mnuBuild->Add(mnuDebugRun);
                m_mnuBuild->Add(mnuDebugRunToCursor);
                m_mnuBuild->Add(mnuDebugStop);
                m_mnuBuild->Add(mnuDebugStepOver);
                m_mnuBuild->Add(mnuDebugStepInto);
                m_mnuBuild->Add(mnuDebugStepOut);
                m_mnuBuild->NewBottomLine();
                m_mnuBuild->Add(mnuToggleBreakpoint);
                m_mnuBuild->NewBottomLine();
                m_mnuBuild->Add(mnuToggleDisplay);
                m_mnuBuild->Add(mnuToggleOSB);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::MenusRemove(void)
{
    if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
    {
        TMenuItem* mnuEdit = Application->MainForm->Menu->Items->Find("&Edit");
        if (true == SAFE_PTR(mnuEdit))
        {
            mnuEdit->NewBottomLine();
            mnuEdit->Remove(mnuGotoLine);
            mnuEdit->Remove(mnuToggleSpecial);
            mnuEdit->Remove(mnuBookmarkToggle);
            mnuEdit->Remove(mnuBookmarkNext);
            mnuEdit->Remove(mnuBookmarkPrevious);
            mnuEdit->Remove(mnuBookmarkClear);
            mnuToggleSpecial->Visible = false;

            if (m_mnuBuild)
            {
                m_mnuBuild->Remove(mnuRun);
                m_mnuBuild->Remove(mnuOptions);
                m_mnuBuild->Remove(mnuBuildSettings);
                m_mnuBuild->Remove(mnuDebugRun);
                m_mnuBuild->Remove(mnuDebugRunToCursor);
                m_mnuBuild->Remove(mnuDebugStop);
                m_mnuBuild->Remove(mnuDebugStepOver);
                m_mnuBuild->Remove(mnuDebugStepInto);
                m_mnuBuild->Remove(mnuDebugStepOut);
                m_mnuBuild->Remove(mnuToggleBreakpoint);
                m_mnuBuild->Remove(mnuToggleDisplay);
                m_mnuBuild->Remove(mnuToggleOSB);
                m_mnuBuild->Clear();
            }
        }
        popMenus->Items->Add(mnuGotoLine);
        popMenus->Items->Add(mnuToggleSpecial);
        popMenus->Items->Add(mnuBookmarkToggle);
        popMenus->Items->Add(mnuBookmarkNext);
        popMenus->Items->Add(mnuBookmarkPrevious);
        popMenus->Items->Add(mnuBookmarkClear);
        popBuild->Items->Add(mnuRun);
        popBuild->Items->Add(mnuOptions);
        popBuild->Items->Add(mnuBuildSettings);
        popBuild->Items->Add(mnuDebugRun);
        popBuild->Items->Add(mnuDebugRunToCursor);
        popBuild->Items->Add(mnuDebugStop);
        popBuild->Items->Add(mnuDebugStepOver);
        popBuild->Items->Add(mnuDebugStepInto);
        popBuild->Items->Add(mnuDebugStepOut);
        popBuild->Items->Add(mnuToggleBreakpoint);
        popBuild->Items->Add(mnuToggleDisplay);
        popBuild->Items->Add(mnuToggleOSB);
    }
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCodeEditor::GotErrorInfo(const String& sLine, String& sFile, int& iLine)
{
    int ErrorsFound = 0;
    bool bErrorPrefixFound = false;

    // find the error prefix
    String sPrefixError;
    String sPrefixFile;
    String sPrefixLineNo;
    frmBuildOptions->GetPrefixes(m_currentBuildToolIndex, sPrefixError, sPrefixFile, sPrefixLineNo);
    std::vector<String> errorPrefixes;
    SplitString(sPrefixError, " ,;:\t", errorPrefixes);
    for (unsigned int i = 0; i < errorPrefixes.size(); ++i)
    {
        if (sLine.AnsiPos(errorPrefixes[i]) > 0)
        {
            bErrorPrefixFound = true;
            ErrorsFound++;
            break;
        }
    }

    if (ErrorsFound == 0)
    {
        return false;
    }

    // find the line number
    int iStart = 1;
    if (sPrefixLineNo != "")
    {
        iStart = sLine.Pos(sPrefixLineNo);
        if (iStart)
        {
            iStart += sPrefixLineNo.Length();
        }
        else
        {
            iStart = 1;
        }
    }
    int iFirstNum = 0;
    int iLastNum = 0;
    for (int i = iStart; i <= sLine.Length(); i++)
    {
        if (sLine.IsDelimiter("0123456789", i))
        {
            if (iFirstNum == 0)
            {
                iFirstNum = i;
            }
            iLastNum = i;
        }
        else if (iFirstNum != 0 && iLastNum != 0)
        {
            break;
        }
    }

    try
    {
        iLine = StrToInt(sLine.SubString(iFirstNum, iLastNum - iFirstNum + 1));
        ErrorsFound++;
    }
    catch(...)
    {
    }

    // find the filename
    iStart = 1;
    if (sPrefixFile != "")
    {
        iStart = sLine.AnsiPos(sPrefixFile);
        if (iStart)
        {
            iStart += sPrefixFile.Length();
        }
        else
        {
            iStart = 1;
        }
    }
    int iDot = 0;//sLine.LastDelimiter(".");
    if (sLine.Length())
    {
        iDot = sLine.AnsiPos(".");

        for (int i = iDot; i >= iStart; i--)
        {
            if (sLine[i] == ' ' || i == iStart)
            {
                int e = iDot + 1;
                for (; e <= sLine.Length(); e++)
                {
                    if (sLine.IsDelimiter(" .:[]-=+-\\/;,?{}|\"", e))
                    {
                        break;
                    }
                }
                ErrorsFound++;
                if (i == iStart)
                {
                    sFile = sLine.SubString(i, e - i);
                }
                else
                {
                    sFile = sLine.SubString(i + 1, e - i);
                }
                break;
            }
        }
    }

    return ErrorsFound >= 1 && bErrorPrefixFound;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmCodeEditor::FindErrorInfo(bool bLoadFile)
{
    bool bErrorFound = false;
    for (int i = m_iConsoleStart; i < memoConsole->Lines->Count && false == bErrorFound; i++)
    {
        try
        {
            bErrorFound = GotErrorInfo(memoConsole->Lines->Strings[i], m_sErrorFile, m_iErrorLine);
        }
        catch(...)
        {
        }
    }
    if (bErrorFound && frmBuildOptions->chkJumpToError->Checked && bLoadFile)
    {
        // jump to the error
        if (LoadFile(m_FileManager.FindFile(m_sErrorFile)) && m_ActiveEditor->Visible)
        {
            // TODO: Set caret
            m_ActiveEditor->Editor->SetFocus();
            m_ActiveEditor->Editor->GotoLineEnsureVisible(m_iErrorLine - 1);
            m_ActiveEditor->Editor->GotoPos(m_ActiveEditor->Editor->PositionFromLine(m_iErrorLine - 1));
        }
    }
    return bErrorFound;
}
//---------------------------------------------------------------------------
String __fastcall TfrmCodeEditor::Subst(const String& sString, char cFind, char cReplaceWith)
{
    String sNewString = sString;
    int iPos = sNewString.Pos(String(cFind));
    while (iPos)
    {
        sNewString[iPos] = cReplaceWith;
        iPos = sNewString.Pos(String(cFind));
    }
    return sNewString;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::FindText(void)
{
    if (!m_ActiveEditor->Visible)
        return;
    // TODO: Find text
    SetStatusSlot(m_PluginHandle, "", 2);
    String sFindText;
    String sReplaceText;
    int SearchOptions = 0;
    m_SearchReplaceConfirmation = rctReplace;
    m_bSearchReplace = false;

    if (true == m_bSearchOnly)
    {
        sFindText = frmSearch->FindText;
        sciSearchReplace->SearchCaseSensitive = frmSearch->CaseSensitive;
        sciSearchReplace->SearchWholeWords = frmSearch->WholeWordsOnly;
        sciSearchReplace->SearchFromCaret = frmSearch->FromCursor;
        sciSearchReplace->SearchBackwards = frmSearch->Backward;
        m_bSearchBackwards = frmSearch->Backward;
    }
    else
    {
        m_bSearchReplace = true;
        sFindText    = frmReplace->FindText;
        sReplaceText = frmReplace->ReplaceText;
        sciSearchReplace->SearchCaseSensitive = frmReplace->CaseSensitive;
        sciSearchReplace->SearchWholeWords = frmReplace->WholeWordsOnly;
        sciSearchReplace->SearchFromCaret = frmReplace->FromCursor;
        sciSearchReplace->SearchBackwards = frmReplace->Backward;
        m_bSearchBackwards = frmReplace->Backward;
        if (frmReplace->ReplaceAll)
        {
            m_SearchReplaceConfirmation = rctReplaceAll;
        }
        else if (frmReplace->PromptOnReplace)
        {
            m_SearchReplaceConfirmation = rctConfirm;
        }
    }
    if (sciSearchReplace->FoundText == sFindText && !sciSearchReplace->SearchBackwards)
    {
        int pos = m_ActiveEditor->Editor->GetCurrentPos();
        m_ActiveEditor->Editor->GotoPos(pos + sFindText.Length());
    }
    sciSearchReplace->SearchText = sFindText;
    sciSearchReplace->ReplaceText = sReplaceText;
    sciSearchReplace->DoSearchReplaceText(m_bSearchReplace, m_bSearchBackwards, m_SearchReplaceConfirmation);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::FindInFiles(void)
{
    lstSearchResults->Items->Clear();
    TFindInFiles FindInFiles;
    FindInFiles.Text = frmSearch->cmbFindText->Text;
    FindInFiles.CaseSensitive = frmSearch->chkCaseSensitive->Checked;
    FindInFiles.WholeWords = frmSearch->chkWholeWordsOnly->Checked;
    if (frmSearch->ProjectFiles)
    {
        FindInFiles.Find(m_FileManager);
    }
    if (FindInFiles.Strings->Count)
    {
        lstSearchResults->Items->AddStrings(FindInFiles.Strings);
        pgcTabs->ActivePage = tabSearchResults;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::SearchProjectFiles(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::SearchOpenFiles(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::SearchInFolders(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::Add(const String& file)
{
    m_bDirty = true;
    m_FileManager.Add(file, true);
    UpdateEditor();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::CloseDocuments()
{
    frmCodeEditor->Clear();
    m_FileManager.Clear();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCodeEditor::UpdateTargetFiles()
{
    String targetFile = frmBuildOptions->GetTargetFile();
    // load file names into the build options target files
    frmBuildOptions->cmbTargetFile->Items->Clear();
    for (int i = 0; i < m_FileManager.Files(); i++)
    {
        frmBuildOptions->cmbTargetFile->Items->Add(m_FileManager.GetFilename(i));
    }
    frmBuildOptions->SetTargetFile(targetFile);
}
//---------------------------------------------------------------------------

