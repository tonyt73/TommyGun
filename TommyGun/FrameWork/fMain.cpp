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
#include "..\SafeMacros.h"
#include "..\Logging\MessageLogger.h"
//---------------------------------------------------------------------------
#include <shfolder.h>
//---------------------------------------------------------------------------
#include "FrameWorkInterface.h"
#include "ZXLogFile.h"
#include "ZXPluginManager.h"
#include "ZXProjectManager.h"
#include "ZXGuiManager.h"
#include "fMain.h"
#include "fAbout.h"
#include "fRenameProject.h"
#include "fCopyProject.h"
//-- PRAGMA'S ---------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KRegistry"
#pragma link "pngimage"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GUI;
using namespace Logging;
using namespace Interface;
using namespace Plugin;
using namespace Project;
//---------------------------------------------------------------------------
TMRUProjectsVector g_mruList;
const TColor    g_Colors[] = { clRed, clYellow, clLime, clAqua };
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the main form
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner),
      m_bClosing(false),
      m_iTopOfButtons(8)
{
    RL_METHOD
}
//---------------------------------------------------------------------------
// Denstructor
/**
 * Checks all allocate memory is freed
 * @author  Tony Thompson
 * @date    Created 23 April 2005
 */
//---------------------------------------------------------------------------
__fastcall TfrmMain::~TfrmMain()
{
    if (NULL != frmAbout)
    {
        ZX_LOG_ERROR(lfGeneral, "frmAbout is not freed");
    }
    if (0 != m_SwitcherButtons.size())
    {
        ZX_LOG_ERROR(lfGeneral, "Not all the Switcher Buttons have been freed");
    }
}
//---------------------------------------------------------------------------
// FormCreate
/**
 * Event handler for the when the form is created
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    RestoreStates();
    panTitle->DoubleBuffered = true;
//    panMRUList->DoubleBuffered = true;
    panPluginButtons->DoubleBuffered = true;
    GetLocation();
    GetMachines();
    UpdateGUI();
    edtNewProjectLocation->Text = GetMyDocumentsFolder() + "\\TommyGun\\";
    //pgcPlugins->DoubleBuffered = true;
    Registration();
    PROTECT_END
}
//---------------------------------------------------------------------------
// FormActivate
/**
 * Repositions the form when it is activate (only once though)
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormActivate(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    static bool bRepositioned = false;
    if (false == bRepositioned)
    {
        bRepositioned = true;
        int iValue = 0;
        bool bState = false;
        if (regScorpio->Read("States", "Top"        , iValue))              Top         = iValue;
        if (regScorpio->Read("States", "Left"       , iValue))              Left        = iValue;
        if (regScorpio->Read("States", "Maximized"  , bState) && bState)    WindowState = wsMaximized;
    }
    FormResize(NULL);
    PROTECT_END
}
//---------------------------------------------------------------------------
// FormCloseQuery
/**
 * Queries the form to see if its OK to close
 * @param   Sender the VCL object that called the method
 * @param   CanClose true if canclose, false if not
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    RL_METHOD
    PROTECT_BEGIN
    CanClose = false;
    if (S_OK == g_PluginManager.Notify(g_PluginManager.Handle, TZX_VERB_NEW, NULL, 0, 0))
    {
        // notify of closing
        g_PluginManager.Notify(g_PluginManager.Handle, TZX_VERB_EXIT, NULL, 0, 0);
        m_bClosing = true;
        // can close application
        CanClose = true;
    }
    PROTECT_END
}
//---------------------------------------------------------------------------
// FormClose
/**
 * Event handler for the when the form is created
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    RL_METHOD
    PROTECT_BEGIN
    if (WindowState != wsMaximized)
    {
        regScorpio->Write("States", "Top"       , Top                       );
        regScorpio->Write("States", "Left"      , Left                      );
        regScorpio->Write("States", "Width"     , Width                     );
        regScorpio->Write("States", "Height"    , Height                    );
    }
    regScorpio->Write("States", "Maximized" , WindowState == wsMaximized);
    PROTECT_END
}
//---------------------------------------------------------------------------
// FormResize
/**
 * Event handler for the when the form is resized
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormResize(TObject *Sender)
{
    stsStatus->Panels->Items[0]->Width = stsStatus->ClientWidth - 260 - stsStatus->Panels->Items[1]->Width;
    stsStatus->Update();
    if (pgcPlugins->Width != panPageContainer->Width  + 8)
    {
        pgcPlugins->Width  = panPageContainer->Width  + 8;
        pgcPlugins->Left   = -4;
    }
    if (pgcPlugins->Height!= panPageContainer->Height + 9)
    {
        pgcPlugins->Height = panPageContainer->Height + 9;
        pgcPlugins->Top    = -8;
    }
    pgcPlugins->Update();
}
//---------------------------------------------------------------------------
// appEventsException
/**
 * Event handler for when an exception occurs
 * @param   Sender  the vcl object that caused the event
 * @param   E       the exception object
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::appEventsException(TObject *Sender, Exception *E)
{
    RL_METHOD
    ZXPlugin* Plugin = g_PluginManager.CheckException();
    if (true == SAFE_PTR(Plugin))
    {
        m_MessageBox.ShowExceptionMessage(Plugin->Description, Plugin->Vendor, (DWORD)Plugin->ModuleAddress, (DWORD)ExceptAddr(), E->Message, true);
        Plugin->Unload();
    }
    else
    {
        if (0 < g_Exceptions.size())
        {
            for (unsigned int i = 0; i < g_Exceptions.size(); ++i)
            {
                m_MessageBox.ShowExceptionMessage(g_Exceptions[i].sMessage, g_Exceptions[i].sFile, g_Exceptions[i].sFunc, g_Exceptions[i].iLine);
            }
            g_Exceptions.clear();
        }
        else
        {
            m_MessageBox.ShowExceptionMessage(E->Message, __FILE__, __FUNC__, __LINE__);
        }
    }
}
//---------------------------------------------------------------------------
// appEventsHint
/**
 * Event handler for when a hint occurs
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::appEventsHint(TObject *Sender)
{
    stsStatus->Panels->Items[0]->Text = Application->Hint;
}
//---------------------------------------------------------------------------
// mnuHelpAboutClick
/**
 * Event handler for the about menu
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuHelpAboutClick(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    frmAbout = new TfrmAbout(Application);
    frmAbout->Execute();
    SAFE_DELETE(frmAbout);
    PROTECT_END
}
//---------------------------------------------------------------------------
// mnuViewPluginSwitcherClick
/**
 * Toggles the visibility of the plugin switcher
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuViewPluginSwitcherClick(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    mnuViewPluginSwitcher->Checked = !mnuViewPluginSwitcher->Checked;
    panPluginSwitcher->Visible = mnuViewPluginSwitcher->Checked;
    regScorpio->Write("States", "Switcher", mnuViewPluginSwitcher->Checked);
    PROTECT_END
}
//---------------------------------------------------------------------------
// mnuViewStandardClick
/**
 * Toggles the visibility of the standard toolbar
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuViewStandardClick(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    mnuViewStandard->Checked = !mnuViewStandard->Checked;
    //tbrStandard->Visible = mnuViewStandard->Checked;
    panToolbars->Visible = mnuViewStandard->Checked;
    regScorpio->Write("States", "Standard", mnuViewStandard->Checked);
    PROTECT_END
}
//---------------------------------------------------------------------------
// spdPluginsUpClick
/**
 * Scrolls the plugin buttons down into view within the browser
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::spdPluginsUpClick(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    panPluginButtons->Top = std::min(0, panPluginButtons->Top + 76);
    PROTECT_END
}
//---------------------------------------------------------------------------
// spdPluginsDownClick
/**
 * Scrolls the plugin buttons up into view within the browser
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::spdPluginsDownClick(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    panPluginButtons->Height = std::max(m_iTopOfButtons, panPluginButtonsContainer->Height);
    panPluginButtons->Top = std::min(0, std::max(panPluginButtonsContainer->Height - m_iTopOfButtons + 64, panPluginButtons->Top - 76));
    PROTECT_END
}
//---------------------------------------------------------------------------
// panPluginButtonsContainerResize
/**
 * Resizes the plugin browser panels
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::panPluginButtonsContainerResize(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    panPluginButtons->Height = std::max(m_iTopOfButtons, panPluginButtonsContainer->Height);
    panPluginButtons->Top = 0;
    PROTECT_END
}
//---------------------------------------------------------------------------
// actSwitch01Execute
/**
 * Switches to plugin using the Ctrl+Fn keys
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actSwitch01Execute(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    int iPluginIndex = ((TAction*)Sender)->Tag;
    if (0 <= iPluginIndex && iPluginIndex < (int)m_SwitcherButtons.size())
    {
        PostNotifyEvent(m_SwitcherButtons[iPluginIndex].PluginHandle, TZX_VERB_SWITCH_PLUGIN, NULL, 0, 0);
        UpdateGUI();
    }
    PROTECT_END
}
//---------------------------------------------------------------------------
// OnPluginButtonClick
/**
 * Event handler for when a plugin buttons is pressed
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::OnPluginButtonClick(TObject *Sender)
{
    RL_METHOD
    PROTECT_BEGIN
    //ClearStatusSlots();
    //pgcPlugins->ActivePageIndex = ((TComponent*)Sender)->Tag;
    PostNotifyEvent(m_SwitcherButtons[((TComponent*)Sender)->Tag].PluginHandle, TZX_VERB_SWITCH_PLUGIN, NULL, 0, 0);
    UpdateGUI();
    PROTECT_END
}
//---------------------------------------------------------------------------
// RestoreStates
/**
 * Restores the states of some form objects
 * @param   Sender  the vcl object that caused the event
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall TfrmMain::RestoreStates(void)
{
    RL_METHOD
    PROTECT_BEGIN
    bool bState = true;
    int  iValue = 0;
        regScorpio->Read("States", "Switcher"   , bState);
    if (bState)                                                                 mnuViewPluginSwitcherClick(NULL);
    if (regScorpio->Read("States", "Standard"   , bState) && false == bState)   mnuViewStandardClick(NULL);
    if (regScorpio->Read("States", "Width"      , iValue) && false == bState)   Width       = iValue;
    if (regScorpio->Read("States", "Height"     , iValue) && false == bState)   Height      = iValue;
    PROTECT_END
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mnuViewOptionsClick(TObject *Sender)
{
    PROTECT_BEGIN

    g_GuiManager.OptionsShow();
    tbrStandard->AutoSize = false;
    tbrStandard->AutoSize = true;

    String sFolder;
    if (regScorpio->Read("ProjectFolder", sFolder))
    {
        edtNewProjectLocation->Text = sFolder;
    }
    PROTECT_END
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::UpdateOptions(void)
{
    bool bValue = true;
    regScorpio->Read("ShowPluginIcons", bValue);
    stsStatus->Panels->Items[1]->Width = bValue ? 200 : 0;
    FormResize(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::AddSwitcherButton(TZX_HPLUGIN PluginHandle, const String& sCaption)
{
    TSwitcherButton Button;
    Button.PluginHandle = PluginHandle;
    Button.IconButton = new KIconButton(NULL);
    Button.IconButton->Name = "Button" + IntToStr(PluginHandle);
    Button.IconButton->Caption = sCaption;
    Button.IconButton->Parent = panPluginButtons;
    Button.IconButton->Left = 4;
    Button.IconButton->Top = 8 + (m_SwitcherButtons.size() * 76);
    Button.IconButton->Height = 68;
    Button.IconButton->Width = 68;
    Button.IconButton->Tag = m_SwitcherButtons.size();
    Button.IconButton->IconsCold = imgLarge;
    Button.IconButton->IconsHot  = imgLarge;
    Button.IconButton->IconIndex = -1;
    Button.IconButton->Grouped = true;
    Button.IconButton->ColorHighlight = (TColor)0x00F6E8E0;//clInfoBk;
    Button.IconButton->ColorSelected = (TColor)0x00EED2C1;//clWhite;
    Button.IconButton->Color = (TColor)0x00846142;//panPluginButtons->Color; //clBtnFace;
    Button.IconButton->ColorBorder = (TColor)0x00846142;
    Button.IconButton->ColorBackground = panPluginButtons->Color;
    //Button.IconButton->Color = clBtnShadow;
    //Button.IconButton->ColorBorderSelected = clWhite;
    //Button.IconButton->ColorHighlight = 0x00F6E8E0;
    //Button.IconButton->ColorSelected = 0x00EED2C1;
    Button.IconButton->Font->Name = "Octin Stencil Rg";
    Button.IconButton->Font->Size = 8;
    Button.IconButton->CornerWidth = 10;
    Button.IconButton->CornerHeight = 10;
    Button.IconButton->OnClick = OnPluginButtonClick;
    m_SwitcherButtons.push_back(Button);
    m_SwitcherButtons[0].IconButton->Selected = true;
    m_iTopOfButtons = 4 + ((m_SwitcherButtons.size()) * 84);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::RemoveSwitcherButton(TZX_HPLUGIN PluginHandle)
{
    // remove the button
    TSwitcherButtonIterator it = m_SwitcherButtons.begin();
    for (it = m_SwitcherButtons.begin(); it != m_SwitcherButtons.end(); it++)
    {
        if ((*it).PluginHandle == PluginHandle)
        {
            SAFE_DELETE((*it).IconButton);
            //SAFE_DELETE((*it).Panel);
            m_SwitcherButtons.erase(it);
            break;
        }
    }
    // reposition the remaining buttons
    for (unsigned int i = 0; i < m_SwitcherButtons.size(); ++i)
    {
        m_SwitcherButtons[i].IconButton->Top = 4 + (i * 84);
        m_SwitcherButtons[i].IconButton->Tag = i;
    }
    // resize the panel
    m_iTopOfButtons = 4 + (m_SwitcherButtons.size() * 84);
    panPluginButtons->Height = std::max(m_iTopOfButtons, panPluginButtonsContainer->Height);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SetSwitcherBitmap(TZX_HPLUGIN PluginHandle, TImage* Image)
{
    TSwitcherButtonIterator it = m_SwitcherButtons.begin();
    for (it = m_SwitcherButtons.begin(); it != m_SwitcherButtons.end(); it++)
    {
        if ((*it).PluginHandle == PluginHandle)
        {
            int iIndex = imgLarge->AddMasked(Image->Picture->Bitmap, Image->Picture->Bitmap->Canvas->Pixels[0][0]);
            (*it).IconButton->IconIndex = iIndex;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ClearStatusSlots(void)
{
    // clear the status bar slots for the next plugin
    stsStatus->Panels->Items[2]->Text = "";
    stsStatus->Panels->Items[3]->Text = "";
    stsStatus->Panels->Items[4]->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actFileNewProjectExecute(TObject *Sender)
{
    if (g_ProjectManager.Close())
    {
        ActiveControl = edtNewProjectName;
    }
    FillProjectList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actFileOpenProjectAccept(TObject *Sender)
{
    g_ProjectManager.Load(actFileOpenProject->Dialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actFileSaveProjectExecute(TObject *Sender)
{
    g_ProjectManager.Save();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actFileCloseProjectExecute(TObject *Sender)
{
    g_ProjectManager.Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SwitchToPlugin(TZX_HPLUGIN PluginHandle)
{
    int iPluginIndex = -1;
    for (int i = 0; i < (int)m_SwitcherButtons.size(); i++)
    {
        if (m_SwitcherButtons[i].PluginHandle == PluginHandle)
        {
            iPluginIndex = i;
            break;
        }
    }
    if (0 <= iPluginIndex && iPluginIndex < pgcPlugins->PageCount)
    {
        ClearStatusSlots();
        m_SwitcherButtons[iPluginIndex].IconButton->Selected = true;
        pgcPlugins->ActivePageIndex = iPluginIndex;
        UpdateGUI();
    }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TfrmMain::GetMyDocumentsFolder()
{
    CHAR my_documents[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, my_documents);
    if (SUCCEEDED(result))
    {
        AnsiString folder = AnsiString(my_documents);
        AnsiString myDocFolder = StringReplace(folder, "Documents", "My Documents", TReplaceFlags() << rfReplaceAll);
        if (DirectoryExists(folder))
        {
            return folder;
        }
        if (DirectoryExists(myDocFolder))
        {
            return myDocFolder;
        }
    }
    return "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cmdOpenProjectClick(TObject *Sender)
{
    if (DirectoryExists(edtNewProjectLocation->Text))
    {
        actFileOpenProject->Dialog->InitialDir = edtNewProjectLocation->Text;
    }
    else
    {
        actFileOpenProject->Dialog->InitialDir = GetMyDocumentsFolder() + "\\TommyGun\\";
    }
    actFileOpenProject->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::edtNewProjectNameChange(TObject *Sender)
{
    lblMessage->Visible = false;
    UpdateOk();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cmdCreateProjectClick(TObject *Sender)
{
    String sBaseFolder = edtNewProjectLocation->Text;
    if (sBaseFolder[sBaseFolder.Length()] != '\\')
    {
        sBaseFolder += "\\";
    }
    String sProjectFolder = sBaseFolder + edtNewProjectName->Text + "\\";

    if (ForceDirectories(sBaseFolder))
    {
        regScorpio->Write("Plugins", "MachineFolder", cmbNewProjectMachine->Text);
        regScorpio->Write("ProjectFolder", sBaseFolder);
        String sProjectFile = sProjectFolder + "project.xml" ;
        //sProjectFile = ChangeFileExt(sProjectFile, ".xml");
        if (false == DirectoryExists(sProjectFolder))
        {
            if (ForceDirectories(sProjectFolder))
            {
                // add the file name to the projects list
                g_ProjectManager.New(sProjectFile, cmbNewProjectMachine->Text);
            }
            else
            {
                lblMessage->Caption = "Location is not valid please select a new Location";
                lblMessage->Visible = true;
            }
        }
        else
        {
            lblMessage->Caption = "A Project file with that Name already exists at the Location";
            lblMessage->Visible = true;
        }
    }
    else
    {
        lblMessage->Caption = "Location is not valid please select a new Location";
        lblMessage->Visible = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::UpdateOk(void)
{
    cmdCreateProject->Enabled = !edtNewProjectName->Text.Trim().IsEmpty() && !edtNewProjectLocation->Text.Trim().IsEmpty() && -1 != cmbNewProjectMachine->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::GetMachines(void)
{
    cmbNewProjectMachine->Items->Clear();
    // read the registry setting and set it to the appropreiate folder
    String sRegFolder;
    regScorpio->Read("Plugins", "MachineFolder", sRegFolder);
    cmbNewProjectMachine->Clear();
    cmbNewProjectMachine->ItemIndex = -1;
    String sPluginsFolder = ExtractFilePath(Application->ExeName) + "Plugins\\_*";
    // find the machine specific plugin folders
    TSearchRec sr;
    if (0 == FindFirst(sPluginsFolder, faAnyFile, sr))
    {
        do
        {
            if ((sr.Attr & faDirectory) == faDirectory)
            {
                String sFolder = sr.Name.SubString(2, sr.Name.Length());
                cmbNewProjectMachine->Items->Add(sFolder);
                if (sFolder.LowerCase() == sRegFolder.LowerCase())
                {
                    cmbNewProjectMachine->ItemIndex = cmbNewProjectMachine->Items->Count - 1;
                }
            }
        }
        while(0 == FindNext(sr));
        FindClose(sr);
    }
    if (cmbNewProjectMachine->ItemIndex == -1 && cmbNewProjectMachine->Items->Count > 0)
    {
        cmbNewProjectMachine->ItemIndex = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::GetLocation(void)
{
    String sProjectFolder;
    if (regScorpio->Read("ProjectFolder", sProjectFolder))
    {
        edtNewProjectLocation->Text = sProjectFolder;
    }
    else
    {
        edtNewProjectLocation->Text = ExtractFilePath(Application->ExeName) + "Projects\\";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FillProjectList(void)
{
    lstProjects->Items->Clear();
    g_ProjectManager.GetMRUList(g_mruList, true);
    if (g_mruList.size())
    {
        // fill the projects list view with the time stamp sorted items
        for (int i = 0; i < (int)g_mruList.size(); ++i)
        {
            TListItem  *item = lstProjects->Items->Add();
            String sProjectFolder = ExtractFilePath(g_mruList[i].File);
            sProjectFolder.SetLength(sProjectFolder.Length() - 1);
            String sFolder = ExtractFileName(sProjectFolder);
            if (g_mruList[i].Exists)
            {
                item->Caption = sFolder;
                // set the machine name
                //item->SubItems->Add(g_mruList[i].Machine);
                item->SubItems->Add(sProjectFolder);
                item->ImageIndex = -1;
                int iDate = Now();
                if ((int)g_mruList[i].TimeStamp == iDate)
                {
                    item->SubItems->Add("Today");
                }
                else if ((int)g_mruList[i].TimeStamp == iDate - 1)
                {
                    item->SubItems->Add("Yesterday");
                }
                else
                {
                    item->SubItems->Add(g_mruList[i].TimeStamp.FormatString("dddddd"));
                }
            }
            else
            {
                item->Caption = sFolder + " (missing)";
                // set the machine name
                item->SubItems->Add("Unknown");
                item->SubItems->Add("Unknown");
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lstProjectsChange(TObject *Sender, TListItem *Item, TItemChange Change)
{
    cmdProjectRemove->Visible = lstProjects->ItemIndex != -1;
    cmdProjectRestore->Visible = lstProjects->ItemIndex != -1;
    cmdProjectCopy->Visible = lstProjects->ItemIndex != -1;
    // load the selected file
    if (lstProjects->ItemIndex != -1 && lstProjects->ItemIndex < (int)g_mruList.size())
    {
        cmdProjectRemove->Top = 47 + ((lstProjects->Selected->Index - lstProjects->TopItem->Index) * 17/*cmdProjectRemove->Height*/);
        cmdProjectRestore->Top = cmdProjectRemove->Top;
        cmdProjectCopy->Top = cmdProjectRemove->Top;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lstProjectsClick(TObject *Sender)
{
    lstProjectsChange(NULL, NULL, TItemChange());
    // load the selected file
    if (lstProjects->ItemIndex != -1 && lstProjects->ItemIndex < (int)g_mruList.size())
    {
        g_ProjectManager.Load(g_mruList[lstProjects->ItemIndex].File);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cmdBrowseClick(TObject *Sender)
{
	dlgBrowse->DefaultFolder = edtNewProjectLocation->Text;
	dlgBrowse->Title = "Select Project Folder";
	if (dlgBrowse->Execute())
    {
		edtNewProjectLocation->Text = dlgBrowse->FileName;
	}
    UpdateOk();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cmdCleanMissingProjectsClick(TObject *Sender)
{
    g_ProjectManager.GetMRUList(g_mruList, true);
    if (g_mruList.size())
    {
        // fill the projects list view with the time stamp sorted items
        for (int i = 0; i < (int)g_mruList.size(); ++i)
        {
            String sFile = ExtractFileName(g_mruList[i].File);
            sFile = ChangeFileExt(sFile, "");
            if (false == g_mruList[i].Exists || g_mruList[i].Machine.LowerCase() == "unknown")
            {
                regScorpio->ClearValue("MRU", IntToStr(i));
            }
        }
    }
    FillProjectList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actFindExecute(TObject *Sender)
{
    TAction* action = dynamic_cast<TAction*>(Sender);
    if (true == SAFE_PTR(action))
    {
        // send the find message to the active plugin
        g_PluginManager.NotifyPlugin(TZXN_EDIT_FIND + action->Tag, NULL, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::UpdateGUI(void)
{
    // query the active plugin to see what it supports and update the gui
    bool bEnableFind            = S_QUERY_YES == g_PluginManager.NotifyPlugin(TZX_QUERY_FIND, NULL, 0, 0);
    actFind->Enabled            = bEnableFind;
    actFindReplace->Enabled     = bEnableFind;
    actFindNext->Enabled        = bEnableFind;
    actFindPrev->Enabled        = bEnableFind;
    mnuEditFindReplace->Enabled = bEnableFind;

    bool bEnableCopyCutPaste    = S_QUERY_YES == g_PluginManager.NotifyPlugin(TZX_QUERY_COPYPASTE, NULL, 0, 0);
    actEditCopy2->Enabled       = bEnableCopyCutPaste;
    actEditCut2->Enabled        = bEnableCopyCutPaste;
    actEditPaste2->Enabled      = bEnableCopyCutPaste;

    //actEditUndo->Enabled        = S_QUERY_YES == g_PluginManager.NotifyPlugin(TZX_QUERY_UNDO, NULL, 0, 0);
    //actEditRedo->Enabled        = S_QUERY_YES == g_PluginManager.NotifyPlugin(TZX_QUERY_REDO, NULL, 0, 0);
    //actEditUndoList->Enabled    = actEditUndo->Enabled && actEditRedo->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::pgcPluginsChange(TObject *Sender)
{
    PostNotifyEvent(m_SwitcherButtons[pgcPlugins->ActivePageIndex].PluginHandle, TZX_VERB_SWITCH_PLUGIN, NULL, 0, 0);
    UpdateGUI();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actEditDeleteExecute(TObject *Sender)
{
    bool bSendDelToControl = false;
    String sClass = ActiveControl->ClassName();
    TCustomEdit* pEdit = dynamic_cast<TCustomEdit*>(ActiveControl);
    bSendDelToControl = (true == SAFE_PTR(pEdit) && true == pEdit->Enabled);
    if (bSendDelToControl)
    {
        SendMessage(ActiveControl->Handle, WM_KEYDOWN, VK_DELETE, 0); 
    }
    else
    {
        g_PluginManager.NotifyPlugin(TZX_VERB_DELETE, NULL, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::popRemoveProjectClick(TObject *Sender)
{
    int iAnswer = 0;
    Message
    (
        mbtError,
        "Remove or Delete the project?",
        "You can choose to Remove or Delete the project from the list",
        "You can choose to either just Remove the project from the list, "
        "Delete the project folder entirely or "
        "Cancel this operation and leave the list unchanged.\n\n"
        "Click,\n\tDelete\tto Delete the project permanently.\n"
        "\tRemove\tto just Remove the entry from the list.\n"
        "\tCancel\tto Cancel this operation and leave the entry in the list.",
        "Cancel", "Remove", "Delete", iAnswer
    );
    if (iAnswer != 0)
    {
        g_ProjectManager.Remove(lstProjects->Items->Item[lstProjects->ItemIndex]->Caption, iAnswer == 2);
        FillProjectList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::popRenameProjectClick(TObject *Sender)
{
    if (false == SAFE_PTR(frmRenameProject))
    {
        frmRenameProject = new TfrmRenameProject(NULL);
    }
    if (true == SAFE_PTR(frmRenameProject) && lstProjects->ItemIndex != -1)
    {
        String sOldName = lstProjects->Items->Item[lstProjects->ItemIndex]->Caption;
        if (frmRenameProject->Execute(sOldName))
        {
            // rename the project
            g_ProjectManager.Rename(sOldName, frmRenameProject->edtNewName->Text.Trim());
        }
        SAFE_DELETE(frmRenameProject);
        FillProjectList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::popMRUListPopup(TObject *Sender)
{
    popRemoveProject->Enabled = lstProjects->ItemIndex != -1;
    popRenameProject->Enabled = lstProjects->ItemIndex != -1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lstProjectsColumnClick(TObject *Sender, TListColumn *Column)
{
    static TListColumn *LastColumn = NULL;
    if (lstProjects->Items->Count)
    {
        if (LastColumn)
        {
            //LastColumn->ImageIndex = 0;
        }

        bool bAscending = g_ProjectManager.SortProjects(Column->Index);
        //Column->ImageIndex = bAscending ? 2 : 1;
        LastColumn = Column;
        FillProjectList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lstProjectsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    if (ActiveControl != Sender)
    {
        ActiveControl = dynamic_cast<TWinControl*>(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actEditCopyExecute(TObject *Sender)
{
    g_PluginManager.NotifyPlugin(TZX_VERB_COPY, NULL, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actEditCutExecute(TObject *Sender)
{
    g_PluginManager.NotifyPlugin(TZX_VERB_CUT, NULL, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actEditPasteExecute(TObject *Sender)
{
    g_PluginManager.NotifyPlugin(TZX_VERB_PASTE, NULL, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::popRestoreProjectClick(TObject *Sender)
{
    String sProject = lstProjects->Items->Item[lstProjects->ItemIndex]->Caption;
    if (sProject.SubString(sProject.Length() - 9, 10) == " (missing)")
    {
        sProject = sProject.SubString(1, sProject.Length() - 10);
    }
    g_ProjectManager.Restore(sProject);
    FillProjectList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::popCopyProjectClick(TObject *Sender)
{
    if (false == SAFE_PTR(frmCopyProject))
    {
        frmCopyProject = new TfrmCopyProject(NULL);
    }
    if (true == SAFE_PTR(frmCopyProject) && lstProjects->ItemIndex != -1)
    {
        String sOldName = lstProjects->Items->Item[lstProjects->ItemIndex]->Caption;
        if (frmCopyProject->Execute(sOldName))
        {
            // rename the project
            g_ProjectManager.Copy(sOldName, frmCopyProject->edtNewName->Text.Trim());
        }
        SAFE_DELETE(frmCopyProject);
        FillProjectList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lstProjectsKeyPress(TObject *Sender, char &Key)
{
    if (Key == VK_RETURN && lstProjects->ItemIndex != -1)
    {
        lstProjectsClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actRunExecute(TObject *Sender)
{
    // send play message
    g_PluginManager.Notify(NULL, TZXN_GAME_PLAY, NULL, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Registration(void)
{
    /*const int cVersion = 0x1350;
    int iVersion = cVersion;
    bool bState = false;
    regScorpio->Read("States", "Registered"  , bState);
    regScorpio->Read("States", "RegisteredVersion"  , iVersion);
    if (!bState || iVersion != cVersion)
    {
        regScorpio->Write("States", "Registered", true);
        regScorpio->Write("States", "RegisteredVersion", cVersion);
        new TRegistrationThread(IdSMTP1, IdMessage1);
    }*/
}
//---------------------------------------------------------------------------

