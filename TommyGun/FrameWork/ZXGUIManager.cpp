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
#include <clipbrd.hpp>
#include "mmsystem.h"
#include "..\SafeMacros.h"
#include "ZXGUIManager.h"
#include "ZXUndoManager.h"
#include "ZXPluginManager.h"
#include "ZXProjectManager.h"
#include "ZXLogFile.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GUI;
using namespace Logging;
using namespace Project;
//---------------------------------------------------------------------------
__fastcall ZXGUIManager::ZXGUIManager()
: m_frmMain(NULL),
  m_frmOptions(NULL),
  m_frmSplash(NULL)
{
}
//---------------------------------------------------------------------------
__fastcall ZXGUIManager::~ZXGUIManager()
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXGUIManager::Initialize(void)
{
    bool bInitialized = false;
    try
    {
        Application->CreateForm(__classid(TfrmMain), &m_frmMain);
        if (true == SAFE_PTR(m_frmMain))
        {
            // create the options form
            m_frmOptions = new TfrmOptions(NULL);
            if (true == SAFE_PTR(m_frmOptions))
            {
                // setup the component handlers
                m_Tabs.Setup(m_frmMain->pgcPlugins, m_frmOptions->pgcOptions, m_frmMain->imgSmall);
                // show and draw the form
                m_StatusBar.Setup(m_frmMain->stsStatus, m_frmMain->imgPluginIcons);
                ProjectActive(false);
                // update the undo manager
                g_UndoManager.Initialize(m_frmMain->actEditUndo, m_frmMain->actEditRedo, m_frmMain->actEditUndoList);
                m_frmMain->Show();
                m_frmMain->Update();
                bInitialized = true;
                ZX_LOG_INFO(lfGeneral, "Initialized GUI Manager")
            }
        }
        if (false == bInitialized)
        {
            ZX_LOG_ERROR(lfGeneral, "Failed to Create forms for the GUI Manager")
        }
    }
    catch(...)
    {
        ZX_LOG_EXCEPTION(lfGeneral, "Failed to Initialize GUI Manager")
        bInitialized = false;
        m_frmMain = NULL;
    }
    return bInitialized;
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::Release(void)
{
    ZX_LOG_INFO(lfGeneral, "Releasing the GUI Manager")
    // free the component handlers
    m_Tabs.Free();
    // free the forms we allocated
    SAFE_DELETE(m_frmSplash);
    SAFE_DELETE(m_frmOptions);
    SAFE_DELETE(m_frmMain);
    // clear the clipboard
    Clipboard()->Clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::Free(TZX_HPLUGIN PluginHandle, bool bFreeOptions)
{
    RemovePluginIcon(PluginHandle);
    // setup the component handlers
    if (bFreeOptions)
    {
        m_frmOptions->RemovePlugin((DWORD)PluginHandle);
    }
    m_Tabs.Free(PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::FreeOptions(void)
{
    if (true == SAFE_PTR(m_frmOptions))
    {
        m_frmOptions->ClearPlugins();
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXGUIManager::ShowSplash(void)
{
    m_dwSplashStartTime = 0;
    bool bShowSplashScreen = true;
    m_frmMain->regScorpio->Read("ShowSplashScreen", bShowSplashScreen);
    if (true == bShowSplashScreen)
    {
        // create the splash screen
        try
        {
            m_frmSplash = new TfrmSplash(NULL);
        }
        catch(...)
        {
            m_frmSplash = NULL;
        }
        // show the splash screen
        if (true == SAFE_PTR(m_frmSplash))
        {
            m_dwSplashStartTime = timeGetTime();
            m_frmSplash->Show();
            m_frmSplash->Update();
        }
    }
    return bShowSplashScreen;
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::HideSplash(void)
{
    // remove the splash screen
    if (true == SAFE_PTR(m_frmSplash))
    {
        // wait for at least 2 seconds for the splash screen
        while(timeGetTime() - m_dwSplashStartTime < 2000)
        {
            Application->ProcessMessages();
            ::Sleep(10);
        }
        // hide the splash form
        m_frmSplash->Hide();
        SAFE_DELETE(m_frmSplash);
        // update the main form
        m_frmMain->Update();
    }
}
//---------------------------------------------------------------------------
KRegistry* __fastcall ZXGUIManager::Registry(void)
{
    return m_frmMain->regScorpio;
}
//---------------------------------------------------------------------------
bool __fastcall ZXGUIManager::IsClosing(void)
{
    return m_frmMain->IsClosing;
}
//---------------------------------------------------------------------------
// PerformVerbCommand
/**
 * Executes a verb command on behalf of a plugin
 * @param           TZX_EVENT   the event/message
 * @author          Tony Thompson
 * @date            Created 7 Feburary 2002
 */
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::PerformVerbCommand(TZX_EVENT Event)
{
    bool bExecuted = false;
    for (int i = 0; i < m_frmMain->actMain->ActionCount && false == bExecuted; i++)
    {
        if (m_frmMain->actMain->Actions[i]->Tag == Event)
        {
            bExecuted = m_frmMain->actMain->Actions[i]->Execute();
        }
    }
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXGUIManager::AddTab(TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Caption)
{
    HRESULT hResult = m_Tabs.AddTab(PluginHandle, VCLParent, Caption);
    if (S_OK == hResult)
    {
        // add the tab switching button
        m_frmMain->AddSwitcherButton(PluginHandle, Caption);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXGUIManager::RemoveTab(TZX_HPLUGIN PluginHandle, HWND  Handle)
{
    m_frmMain->RemoveSwitcherButton(PluginHandle);
    return m_Tabs.RemoveTab(PluginHandle, Handle);
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXGUIManager::SetTabBitmap(TZX_HPLUGIN PluginHandle, HWND  Handle, TImage* SmallImage, TImage* LargeImage)
{
    HRESULT hResult = m_Tabs.SetTabBitmap(PluginHandle, Handle, SmallImage);
    if (S_OK == hResult)
    {
        // set the tab switching buttons bitmap
        m_frmMain->SetSwitcherBitmap(PluginHandle, LargeImage);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXGUIManager::AddOptionsTab(TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Name)
{
    return m_Tabs.AddOptionsTab(PluginHandle, VCLParent, Name);
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXGUIManager::SetStatusSlot(TZX_HPLUGIN PluginHandle, const String& sText, unsigned int iSlot)
{
    RL_HRESULT(S_FALSE);
    if (true == m_Tabs.IsActivePlugin(PluginHandle) && iSlot < 3)
    {
        m_frmMain->stsStatus->Panels->Items[2 + iSlot]->Text = sText;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::ResetStatusSlots(void)
{
    m_frmMain->stsStatus->Panels->Items[2]->Text = "";
    m_frmMain->stsStatus->Panels->Items[3]->Text = "";
    m_frmMain->stsStatus->Panels->Items[4]->Text = "";
}
//---------------------------------------------------------------------------
// Message
/**
 * Shows a message dialog, with user defined buttons
 * @param   eType type of message dialog (rmbError, rmbWarning, rmbInforamation, rmbQuestion)
 * @param   sTitle of the message dialog
 * @param   sBrief brief line describing the message
 * @param   sDetails the details in full of the message
 * @param   sButton1 the caption of the 1st button
 * @param   sButton2 the caption of the 2nd button
 * @param   sButton3 the caption of the 3rd button
 * @param   iAnswer
 * @return  the answer to the message
 * @author  Tony Thompson
 * @date    Created 19 April 2002
 */
//---------------------------------------------------------------------------
int __fastcall ZXGUIManager::ShowMessage(ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3)
{
    int iAnswer = -1;
    PROTECT_BEGIN
    ZXMessageBox MessageBox;
    iAnswer = MessageBox.ShowMessage(eType, sTitle, sBrief, sDetails, sButton1, sButton2, sButton3);
    PROTECT_END
    return iAnswer;
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::ShowGeneralMessage(const AnsiString& Title, const AnsiString& Problem, const String& File, const String& Function, int Line)
{
    PROTECT_BEGIN
    ZXMessageBox MessageBox;
    MessageBox.ShowGeneralMessage(Title, Problem, File, Function, Line);
    PROTECT_END
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::OptionsUpdate(void)
{
    m_frmMain->UpdateOptions();
    g_UndoManager.UpdateSettings();
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::OptionsPluginsClear(void)
{
    m_frmOptions->ClearPlugins();
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::OptionsPluginsAdd(TZX_HPLUGIN PluginHandle, String sName, String sRegName, String sVendor, String sPluginVersion, String sFileVersion, bool bIsUnloadable, bool bDoNotLoad, bool dDoNotShow, DWORD dwPriority, int iLoadOrder, TImage* Icon)
{
    m_frmOptions->AddPlugin((DWORD)PluginHandle, sName, sRegName, sVendor, sPluginVersion, sFileVersion, bIsUnloadable, bDoNotLoad, dDoNotShow, dwPriority, iLoadOrder, Icon);
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::OptionsChanged(void)
{
    m_frmOptions->Changed();
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::OptionsShow(void)
{
    if (true == SAFE_PTR(m_frmOptions))
    {
        if (m_frmOptions->Execute())
        {
            // plugins changed, ask user if they want to reload the project to make the change stick
            int iResponse = ShowMessage(mbtInformation,
                        "Plugin properties have changed",
                        "The project will need to be reloaded",
                        "Properties of the projects plugins have changed. "
                        "For these changes to take effect the project needs to be reloaded.\n\n"
                        "Click,\n"
                        "\tReload\tto Save your changes and reload or\n"
                        "\tIgnore\tto continue working without saving and no plugin changes",
                        "Ignore", "Reload", ""
                        );
            if (iResponse)
            {
                // reload the project
                g_ProjectManager.Reload();
            }
        }
        // update the undo settings
        g_UndoManager.UpdateSettings();
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::AddPluginIcon(TZX_HPLUGIN PluginHandle, TImage* Icon, const String& sDescription)
{
    m_StatusBar.AddPluginIcon(PluginHandle, Icon, sDescription);
    g_PluginManager.SetPluginIcon(PluginHandle, Icon);
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::RemovePluginIcon(TZX_HPLUGIN PluginHandle)
{
    m_StatusBar.RemovePluginIcon(PluginHandle);
    g_PluginManager.SetPluginIcon(PluginHandle, NULL);
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXGUIManager::IsActivePlugin(TZX_HPLUGIN PluginHandle)
{
    return m_Tabs.IsActivePlugin(PluginHandle) ? S_OK : E_FAIL;
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::SwitchToPlugin(TZX_HPLUGIN PluginHandle)
{
    m_frmMain->SwitchToPlugin(PluginHandle);
    m_StatusBar.ActivePlugin(PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::ResetActivePlugin(void)
{
    m_StatusBar.ActivePlugin(NULL);
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::ProjectActive(bool bProjectOpened)
{
    g_GuiManager.m_frmMain->actFileNewProject->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actFileMergeProject->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actFileSaveProject->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actFileCloseProject->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actFileImport->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actFileExport->Enabled = bProjectOpened;
    //g_GuiManager.m_frmMain->actEditUndoList->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actEditCopy2->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actEditCut2->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actEditPaste2->Enabled = bProjectOpened;
    //g_GuiManager.m_frmMain->actEditUndo->Enabled = bProjectOpened;
    //g_GuiManager.m_frmMain->actEditRedo->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actEditDelete->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->actEditSelectAll->Enabled = bProjectOpened;
    g_GuiManager.m_frmMain->mnuViewPluginSwitcher->Visible = bProjectOpened;
    g_GuiManager.m_frmMain->panToolbars->Visible = bProjectOpened && g_GuiManager.m_frmMain->mnuViewStandard->Checked;
    //g_GuiManager.m_frmMain->mnuViewToolbars->Visible = bProjectOpened;
    // show/hide the switcher
    bool bVisible = false;
    g_GuiManager.m_frmMain->regScorpio->Read("States", "Switcher", bVisible);
    g_GuiManager.m_frmMain->panPluginSwitcher->Visible = bProjectOpened && bVisible;
    g_GuiManager.m_frmMain->mnuGame->Visible = bProjectOpened && bVisible;
    // clear the status slots
    ResetStatusSlots();
    g_GuiManager.m_frmMain->tabStartPage->TabVisible = !bProjectOpened;
    g_GuiManager.m_frmMain->edtNewProjectName->Text = "";
    g_GuiManager.m_frmMain->panPageContainer->Color = bProjectOpened ? clBtnFace : clWhite;
    if (!bProjectOpened)
    {
        g_GuiManager.m_frmMain->FillProjectList();
        g_GuiManager.m_frmMain->pgcPlugins->ActivePage = g_GuiManager.m_frmMain->tabStartPage;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::ProjectTitle(const String& Title)
{
    m_frmMain->Caption = "TommyGun [" + Title + "]";
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::Refresh(void)
{
    m_frmMain->Refresh();
}
//---------------------------------------------------------------------------
String __fastcall ZXGUIManager::ReadMachineFolder(void)
{
    return m_frmOptions->ReadMachineFolder();
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::WriteMachineFolder(const String& sMachineFolder)
{
    m_frmOptions->WriteMachineFolder(sMachineFolder);
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::XmlInitialize(KXmlInfo* xmlInfo)
{
    // initialize the xml object
    // TODO: Setup GUI XML
    /*
    KXmlInfo& System = xmlInfo.AddTag("System");
    KXmlInfo& UndoSys = System.AddTag("UndoSystem");
    KXmlInfo& Undo = UndoSys.AddTag("Undo");
    Undo.Add("Data", "00 00 00 00");
    KXmlInfo& Redo = UndoSys.AddTag("Redo");
    Redo.Add("Data", "11 11 11 11");
    */
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXGUIManager::AddMenu(const String& sCaption, TMenuItem*& pMenu)
{
    static int i = 1000;
    //pMenu = NewSubMenu(sCaption, 0, "NewMenu" + IntToStr(i++), NULL, -1, true);
    //pMenu->Visible = false;
    //m_frmMain->mnuMain->Items->Insert(m_frmMain->mnuHelp->MenuIndex, pMenu);

    try
    {
        pMenu = new TMenuItem(m_frmMain);
    }
    catch(EOutOfMemory&)
    {
        pMenu = NULL;
    }

    if (true == SAFE_PTR(pMenu))
    {
        pMenu->Caption = sCaption;
        pMenu->OnClick = OnMenuClick;
        // add the new menu the to the main menu
        m_frmMain->mnuMain->Items[0].Add(pMenu);
        // make sure the help menu stays last
        pMenu->MenuIndex = pMenu->MenuIndex - 1;
        pMenu->Visible = false;
    }
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::OnMenuClick(TObject* Sender)
{
}
//---------------------------------------------------------------------------
void __fastcall ZXGUIManager::AddUndo(KXmlInfo* xmlInfo, DWORD UndoType)
{
    g_UndoManager.Add(xmlInfo, (ZXUndoType)UndoType);
}
//---------------------------------------------------------------------------


