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
#include <algorithm>
#include "fOptions.h"
#include "fMain.h"
#include "ZXPluginManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KRegistry"
#pragma link "KIconButton"
#pragma link "KSpinEdit"
#pragma link "pngimage"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GUI;
//---------------------------------------------------------------------------
// used by std::sort for the comparsion of 2 TZXPlugInfo objects
bool operator<(const TPluginInfo& info1, const TPluginInfo& info2 )
{
    bool bLessThan = false;
    if ( info1.Priority == info2.Priority )
    {
        bLessThan = ( info1.LoadOrder < info2.LoadOrder );
    }
    else
    {
        bLessThan = ( info1.Priority > info2.Priority );
    }
    return bLessThan;
}
//---------------------------------------------------------------------------
const String Priorities[4] =
{
    "None",
    "Low",
    "Normal",
    "High"
};
//---------------------------------------------------------------------------
// Constructor
/**
 * creates the BandManager object
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
__fastcall TfrmOptions::TfrmOptions(TComponent* Owner)
: TForm(Owner)
, m_iTopOfButtons(0)
{
    m_BandManager = new ZXBandManager;
    m_iKeyPanelHeights = panCommonKeys->Height;
}
//---------------------------------------------------------------------------
// Destructor
/**
 * Clears the list of plugins, and destroys the BandManager
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
__fastcall TfrmOptions::~TfrmOptions()
{
    ClearPlugins();
    SAFE_DELETE(m_BandManager);
}
//---------------------------------------------------------------------------
// cmdCloseClick
/**
 * Event handler for the Close button. Closes the dialog box
 * @param           Sender the vcl object that called the event
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::cmdCloseClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
// FormShow
/**
 * OnFormShow event handler
 * @param           Sender the vcl object that called the event
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 * @date            Last Modified 10 March 2003 - Add splash screen registry settings
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormShow(TObject *Sender)
{
    String path = getenv("APPDATA");
    path += "\\TommyGun\\";
    lblAppDataFolder->Caption = "%APPDATA% = " + path;
    bool bValue = true;
    int  iValue = 0;
    chkShowSplashScreen->Checked = true;
    if (true == regScorpio->Read("ShowSplashScreen", bValue))
    {
        chkShowSplashScreen->Checked = bValue;
    }
    chkShowPluginIcons->Checked = true;
    if (true == regScorpio->Read("ShowPluginIcons", bValue))
    {
        chkShowPluginIcons->Checked = bValue;
    }
    chkLoggingProduceFiles->Checked = false;
    if (true == regScorpio->Read("States", "UseLogFiles", bValue))
    {
        chkLoggingProduceFiles->Checked = bValue;
    }
    /*chkShowProblemDialog->Checked = true;
    if (true == regScorpio->Read("States", "DoNotShowProblems", bValue))
    {
        chkShowProblemDialog->Checked = !bValue;
    }*/
    String sProjectFolder;
    if (regScorpio->Read("ProjectFolder", sProjectFolder))
    {
        edtProjectFolder->Text = sProjectFolder;
    }
    else
    {
        edtProjectFolder->Text = ExtractFilePath(Application->ExeName) + "Projects\\";
    }
    chkRemoveWhitespaceFromXML->Checked = false;
    if (true == regScorpio->Read("States", "RemoveXmlWhitespace", bValue))
    {
        chkRemoveWhitespaceFromXML->Checked = bValue;
    }

    chkUndoEnableUndo->Checked = true;
    if (true == regScorpio->Read("Undo", "EnableUndo", bValue))
    {
        chkUndoEnableUndo->Checked = bValue;
    }
    chkUndoEnabledRedo->Checked = true;
    if (true == regScorpio->Read("Undo", "EnabledRedo", bValue))
    {
        chkUndoEnabledRedo->Checked = bValue;
    }
    chkUndoMemoryLimit->Checked = true;
    if (true == regScorpio->Read("Undo", "EnableMemoryLimit", bValue))
    {
        chkUndoMemoryLimit->Checked = bValue;
    }
    chkUndoClear->Checked = true;
    if (true == regScorpio->Read("Undo", "ClearAfterSave", bValue))
    {
        chkUndoClear->Checked = bValue;
	}
	edtUndoMemory->Value = 16;
	if (true == regScorpio->Read("Undo", "MemoryLimit", iValue))
	{
		edtUndoMemory->Value = iValue;
	}

    chkBackupEnabled->Checked = true;
    if (true == regScorpio->Read("Backup", "EnableBackup", bValue))
    {
        chkBackupEnabled->Checked = bValue;
    }
    chkLimitBackupUsage->Checked = true;
    if (true == regScorpio->Read("Backup", "EnableFolderLimit", bValue))
    {
        chkLimitBackupUsage->Checked = bValue;
    }
	edtBackupFolders->Value = 32;
	if (true == regScorpio->Read("Backup", "FolderLimit", iValue))
	{
		edtBackupFolders->Value = iValue;
	}
	radBackupOnSave->Checked = true;
    if (true == regScorpio->Read("Backup", "BackOnSave", bValue))
    {
        if (false == bValue)
            radBackupOnClose->Checked = true;
    }

    cmdApply->Enabled = false;
}
//---------------------------------------------------------------------------
//  Execute
/**
 * called by the application to show the dialog
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
bool __fastcall TfrmOptions::Execute(void)
{
    m_bPluginsChanged = false;
    m_bPluginChangesApplied = false;
    FindMachineSpecificFolders();
    ShowModal();
    return m_bPluginChangesApplied;
}
//---------------------------------------------------------------------------
// Changed
/**
 * Options have changed, so enables the apply button
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::Changed(void)
{
    cmdApply->Enabled = true;
}
//---------------------------------------------------------------------------
// ClearPlugins
/**
 * Clears the list of plugins that are displayed
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::ClearPlugins(void)
{
    if (true == SAFE_PTR(m_BandManager))
    {
        m_BandManager->SetArrowImage(imgArrowUpDown);
    }
    // remove all the plugins
    for (unsigned int i = 0; i < m_Plugins.size(); i++)
    {
        // remove the control from the bandmanager
        m_BandManager->UnRegisterControl(m_Plugins[i].Panel);
        // remove the control form the form
        SAFE_DELETE(m_Plugins[i].Label);
        SAFE_DELETE(m_Plugins[i].Icon);
        SAFE_DELETE(m_Plugins[i].Image);
        SAFE_DELETE(m_Plugins[i].CheckBox);
        SAFE_DELETE(m_Plugins[i].Shape);
        m_Plugins[i].Panel->Parent->RemoveControl(m_Plugins[i].Panel);
        SAFE_DELETE(m_Plugins[i].Panel);
    }
    m_Plugins.clear();
    panKeysGeneral->Height = panCommonKeys->Height;
    m_iKeyPanelHeights = panCommonKeys->Height;
    panCommonKeys->Align = alTop;
    scpKeys->VertScrollBar->Position = 0;
    scpKeys->Invalidate();
}
//---------------------------------------------------------------------------
// AddPlugin
/**
 * Converts a ZXPlugin object to a TPluginInfo 
 * @param           Plugin the plugin to retrieve information from
 * @author          Tony Thompson
 * @date            Last Modified 22 September 2003
 */
//---------------------------------------------------------------------------
/*void __fastcall TfrmOptions::AddPlugin(ZXPlugin* Plugin)
{
    TPluginInfo PluginInfo;
    PluginInfo.Name             = Plugin->Description;
    PluginInfo.RegName          = Plugin->Filename;
    PluginInfo.Vendor           = Plugin->Vendor;
    PluginInfo.FileVersion      = Plugin->FileVersion;
    PluginInfo.PluginVersion    = Plugin->FileVersion;
    PluginInfo.LoadOrder        = Plugin->LoadOrder;
    PluginInfo.Priority         = Plugin->Flags & FLAG_PluginLoadPriorityMask;
    PluginInfo.IsUnloadable     = (FLAG_IsNotUnloadable != (Plugin->Flags & FLAG_IsNotUnloadable));
    PluginInfo.DoNotLoad        = Plugin->DoNotLoad;
    PluginInfo.DoNotShow        = FLAG_IsNotVisibleInOptionsPage == (Plugin->Flags & FLAG_IsNotVisibleInOptionsPage);
    AddPlugin(PluginInfo);
}*/
//---------------------------------------------------------------------------
// AddPlugin
/**
 * Adds a plugins information to the list of plugins
 * @param           pi the information about the plugin
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::AddPlugin(DWORD Handle, String sName, String sRegName, String sVendor, String sPluginVersion, String sFileVersion, bool bIsUnloadable, bool bDoNotLoad, bool bDoNotShow, DWORD dwPriority, int iLoadOrder, TImage* Icon)
{
    static int nextID = 0;
    TPluginInfo pi;
    pi.Handle           = Handle;
    pi.Name             = sName;
    pi.RegName          = sRegName;
    pi.Vendor           = sVendor;
    pi.PluginVersion    = sPluginVersion;
    pi.FileVersion      = sFileVersion;
    pi.IsUnloadable     = bIsUnloadable;
    pi.DoNotLoad        = bDoNotLoad;
    pi.DoNotShow        = bDoNotShow;
    pi.Priority         = dwPriority;
    pi.LoadOrder        = iLoadOrder;

    panOptionsPluginContainerBody->Top = 0;
    //pi.Panel = new TPanel(panOptionsPluginContainerBody);
    pi.Panel = new TPanel((void*)NULL);
    pi.Panel->Name = "PluginPanel" + IntToStr(nextID);
    panOptionsPluginContainerBody->InsertControl(pi.Panel);
    pi.Panel->Color = clWhite;
    pi.Panel->Align = alTop;
    pi.Panel->Width = panOptionsPluginContainer->Width;
    pi.Panel->Height = panOptionsPluginContainer->Height;
    pi.Panel->BevelOuter = bvNone;
    pi.Panel->ShowHint = true;
    pi.Panel->Hint = "Plugin Vendor: " + pi.Vendor + "\nPlugin Version: " + pi.PluginVersion + "\nPlugin File: " + pi.RegName + "\nFile Version: " + pi.FileVersion;
    pi.Panel->Left = 0;
    pi.Panel->Top = 0;
    pi.Panel->Visible = true;
    pi.Shape = new TShape(pi.Panel);
    pi.Shape->Name = "PluginShape" + IntToStr(nextID);
    pi.Shape->Parent = pi.Panel;
    pi.Shape->Align = alClient;
    pi.Shape->Shape = stRectangle;
    pi.Shape->Pen->Color = clWindowFrame;
    pi.Shape->Visible = true;
    pi.Shape->OnMouseDown = chkOptionsPluginNameMouseDown;
    pi.Shape->OnMouseMove = chkOptionsPluginNameMouseMove;
    pi.Shape->OnMouseUp   = chkOptionsPluginNameMouseUp;
    pi.Shape->Brush->Color = clWhite;

    //pi.Panel->Visible = !pi.DoNotShow;

    DWORD PriorityImageIndex = pi.Priority >> SHIFTS_PluginLoadPriority;

    pi.Image = new TImage(pi.Shape);
    pi.Image->Name = "PluginImage" + IntToStr(nextID);
    pi.Image->Width   = 12;
    pi.Image->Height  = 16;
    pi.Image->Visible = true;
    pi.Image->Left    = imgOptionsPluginsPriority->Left;
    pi.Image->Top     = imgOptionsPluginsPriority->Top;
    pi.Image->Parent  = pi.Panel;
    pi.Image->Hint    = Priorities[PriorityImageIndex];
    pi.Image->Transparent = true;

    imgPriorityIcons->GetBitmap(PriorityImageIndex, pi.Image->Picture->Bitmap);

    pi.CheckBox = new TCheckBox(pi.Panel);
    pi.CheckBox->Name = "PluginCheckBox" + IntToStr(nextID);
    pi.CheckBox->Left = 4;
    pi.CheckBox->Top  = 4;
    pi.CheckBox->Width = chkOptionsPluginName->Width;
    pi.CheckBox->Height = chkOptionsPluginName->Height;
    pi.CheckBox->Caption = "";
    pi.CheckBox->Checked = !pi.DoNotLoad;
    pi.CheckBox->Parent = pi.Panel;
    pi.CheckBox->Color = clWhite;
    pi.CheckBox->Visible = true;

    if (pi.IsUnloadable)
    {
        pi.CheckBox->OnClick = DonotLoadChanged;
    }
    else
    {
        pi.CheckBox->Enabled = false;
        pi.CheckBox->Checked = true;
        pi.CheckBox->Visible = false;
    }

    pi.Icon = new TImage(pi.Shape);
    pi.Icon->Name = "PluginIcon" + IntToStr(nextID);
    pi.Icon->Width   = 16;
    pi.Icon->Height  = 16;
    pi.Icon->Visible = true;
    pi.Icon->Left    = imgPluginIcon->Left;
    pi.Icon->Top     = imgPluginIcon->Top;
    pi.Icon->Parent  = pi.Panel;
    pi.Icon->Transparent = true;
    if (true == SAFE_PTR(Icon))
    {
        pi.Icon->Canvas->Draw(0,0, Icon->Picture->Bitmap);
    }
    else
    {
        pi.Icon->Canvas->Draw(0,0, imgDefaultIcon->Picture->Bitmap);
    }

    pi.Label = new TLabel(pi.Panel);
    pi.Label->Name = "PluginLabel" + IntToStr(nextID);
    pi.Label->Parent = pi.Panel;
    pi.Label->AutoSize = false;
    pi.Label->Left = lblOptionsPluginsName->Left;
    pi.Label->Top  = lblOptionsPluginsName->Top;
    pi.Label->Width = lblOptionsPluginsName->Width;
    pi.Label->Caption = pi.Name;
    pi.Label->Visible = true;
    pi.Label->Color = clWhite;
    pi.Label->Transparent = true;
    pi.Label->ShowHint = true;
    pi.Label->Hint = pi.Panel->Hint;
    pi.Label->OnMouseDown = chkOptionsPluginNameMouseDown;
    pi.Label->OnMouseMove = chkOptionsPluginNameMouseMove;
    pi.Label->OnMouseUp   = chkOptionsPluginNameMouseUp;
    ++nextID;

    m_BandManager->RegisterControl(pi.Panel, Name);
    m_Plugins.push_back(pi);
    panOptionsPluginContainerBody->Height = m_Plugins.size() * panOptionsPluginContainer->Height + 2;
    SortPlugins();

    TPanel* pKeysPanel = NULL;
    if (S_QUERY_YES == g_PluginManager.NotifyPlugin((TZX_HPLUGIN)Handle, TZX_QUERY_KEY_PANEL, (LPDATA)&pKeysPanel, 0, 0) && true == SAFE_PTR(pKeysPanel))
    {
        m_iKeyPanelHeights      += pKeysPanel->Height;
        panKeysGeneral->AutoSize = false;
        panKeysGeneral->Height   = m_iKeyPanelHeights;
        pKeysPanel->Parent       = panKeysGeneral;
        pKeysPanel->Top          = m_iKeyPanelHeights - 10;
        pKeysPanel->Align        = alTop;
        pKeysPanel->Visible      = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::RemovePlugin(DWORD Handle)
{
    bool bRemoved = false;
    for (unsigned int i = 0; i < m_Plugins.size() && false == bRemoved; i++)
    {
        if (m_Plugins[i].Handle == Handle)
        {
            // remove the control from the bandmanager
            m_BandManager->UnRegisterControl(m_Plugins[i].Panel);
            // remove the control form the form
            if (true == SAFE_PTR(m_Plugins[i].Panel))
            {
                m_Plugins[i].Panel->Parent->RemoveControl(m_Plugins[i].Panel);
                SAFE_DELETE(m_Plugins[i].Panel);
                m_Plugins.erase(m_Plugins.begin() + i);
                bRemoved = true;
            }
        }
    }
}
//---------------------------------------------------------------------------
// chkOptionsPluginNameMouseDown
/**
 * Mouse down event handler for the checkbox to load/unload a plugin
 * @param           Sender the vcl object that called the event
 * @param           Button the button pressed on the checkbox
 * @param           State the state of the shift keys
 * @param           X the x position of the cursor
 * @param           Y the y position of the cursor
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::chkOptionsPluginNameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        m_BandPosition = FindPanel(Sender)->Top;
        m_BandManager->MouseDown(Sender, X, Y);
    }
}
//---------------------------------------------------------------------------
// chkOptionsPluginNameMouseMove
/**
 * Mouse move event handler for the checkbox
 * @param           Sender the vcl object that called the event
 * @param           Button the button pressed on the checkbox
 * @param           State the state of the shift keys
 * @param           X the x position of the cursor
 * @param           Y the y position of the cursor
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::chkOptionsPluginNameMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    if (Shift.Contains(ssLeft))
    {
        m_BandManager->MouseMove(Sender, X, Y);
    }
}
//---------------------------------------------------------------------------
// chkOptionsPluginNameMouseUp
/**
 * Mouse up event handler for the checkbox
 * @param           Sender the vcl object that called the event
 * @return          HRESULT S_OK successful, S_FALSE failed
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::chkOptionsPluginNameMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        m_bPluginsChanged = true;
        m_BandManager->MouseUp(Sender, X, Y);
        cmdApply->Enabled |= (m_BandPosition != FindPanel(Sender)->Top);
        // apply the plugin settings
        for (unsigned int i = 0; i < m_Plugins.size(); i++)
        {
            int Pos = m_Plugins[i].Panel->Top / panOptionsPluginContainer->Height;
            m_Plugins[i].LoadOrder = Pos;
        }
        SortPlugins();
    }
}
//---------------------------------------------------------------------------
// FindPanel
/**
 * Finds a panel based on the VCL sender informatin
 * @param           Sender the vcl object that called the event
 * @return          TPanel* the pointer to the panel
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
TPanel* __fastcall TfrmOptions::FindPanel(TObject *Sender)
{
    for (unsigned int i = 0; i < m_Plugins.size(); i++)
    {
        if (m_Plugins[i].Label == Sender || m_Plugins[i].Shape == Sender)
        {
            return m_Plugins[i].Panel;
        }
    }
    return NULL;
}
//---------------------------------------------------------------------------
// cmdApplyClick
/**
 * Applys the changes to the options dialog
 * @param           Sender the vcl object that called the event
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 * @date            Last Modified 10 March 2003 - Add splash screen registry settings
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::cmdApplyClick(TObject *Sender)
{
    // save the plugin load order
    for (unsigned int i = 0; i < m_Plugins.size(); i++)
    {
        regScorpio->Write("Plugins", m_Plugins[i].RegName, m_Plugins[i].LoadOrder);
        regScorpio->Write("Plugins", "DNL_" + m_Plugins[i].RegName, !m_Plugins[i].CheckBox->Checked);
    }
    // update the registry
    regScorpio->Write("ShowSplashScreen", chkShowSplashScreen->Checked);
    regScorpio->Write("ShowPluginIcons" , chkShowPluginIcons->Checked );
    regScorpio->Write("States", "UseLogFiles", chkLoggingProduceFiles->Checked);
    //regScorpio->Write("States", "DoNotShowProblems", !chkShowProblemDialog->Checked);
    regScorpio->Write("ProjectFolder", edtProjectFolder->Text);
    regScorpio->Write("States", "RemoveXmlWhitespace", chkRemoveWhitespaceFromXML->Checked);
    regScorpio->Write("Undo", "EnableUndo", chkUndoEnableUndo->Checked);
    regScorpio->Write("Undo", "EnabledRedo", chkUndoEnabledRedo->Checked);
    regScorpio->Write("Undo", "EnableMemoryLimit", chkUndoMemoryLimit->Checked);
    regScorpio->Write("Undo", "ClearAfterSave", chkUndoClear->Checked);
    regScorpio->Write("Undo", "MemoryLimit", (int)edtUndoMemory->Value);
    regScorpio->Write("Undo", "GroupByPlugin", radUndoGroupByPlugin->Checked);
    regScorpio->Write("Undo", "AutoSwitchToPlugin", radUndoAutoSwitchTo->Checked);
    regScorpio->Write("Undo", "EnableStackDialog", chkUndoEnableDialog->Checked);
    regScorpio->Write("Backup", "EnableBackup", chkBackupEnabled->Checked);
    regScorpio->Write("Backup", "EnableFolderLimit", chkLimitBackupUsage->Checked);
    regScorpio->Write("Backup", "FolderLimit", (int)edtBackupFolders->Value);
    regScorpio->Write("Backup", "BackOnSave", radBackupOnSave->Checked);
    // call PostNotifyEvent from frmShell to inform the plugins of a property change
    g_PluginManager.Notify(NULL, TZXN_OPTIONS_SAVE, NULL, 0L, 0L);
    m_bPluginChangesApplied = m_bPluginsChanged;
    cmdApply->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::DonotLoadChanged(TObject *Sender)
{
    m_bPluginsChanged = true;
    chkOptionsPluginNameClick(Sender);
}
//---------------------------------------------------------------------------
// chkOptionsPluginNameClick
/**
 * Click event handler for the checkbox
 * @param           Sender the vcl object that called the event
 * @return          HRESULT S_OK successful, S_FALSE failed
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::chkOptionsPluginNameClick(TObject *Sender)
{
    cmdApply->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::SortPlugins(void)
{
    // sort the plugin order
    std::sort(m_Plugins.begin(), m_Plugins.end());
    // reorder the list to show the correct order
    for (unsigned int i = 0; i < m_Plugins.size(); i++)
    {
        m_Plugins[i].Panel->Top = i * panOptionsPluginContainer->Height;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::FindMachineSpecificFolders(void)
{
    // read the registry setting and set it to the appropreiate folder
    String sRegFolder;
    regScorpio->Read("Plugins", "MachineFolder", sRegFolder);
    panPluginsMachine->Caption = "  " + sRegFolder;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::cmbOptionsPluginMachineSpecificChange(TObject *Sender)
{
    cmdApply->Enabled = true;
}
//---------------------------------------------------------------------------
String __fastcall TfrmOptions::ReadMachineFolder(void)
{
    String sRegFolder;
    regScorpio->Read("Plugins", "MachineFolder", sRegFolder);
    return sRegFolder;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::WriteMachineFolder(const String& sMachineFolder)
{
    regScorpio->Write("Plugins", "MachineFolder", sMachineFolder);
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::cmdGeneralClick(TObject *Sender)
{
    TComponent* Button = dynamic_cast<TComponent*>(Sender);
    if (true == SAFE_PTR(Button))
    {
        pgcOptions->ActivePageIndex = Button->Tag;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::spdProjectFolderBrowseClick(TObject *Sender)
{
	dlgBrowse->DefaultFolder = edtProjectFolder->Text;
	if (dlgBrowse->Execute())
    {
        edtProjectFolder->Text = dlgBrowse->FileName;
        cmdApply->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::edtProjectFolder2Change(TObject *Sender)
{
    cmdApply->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::spdPluginsUpClick(TObject *Sender)
{
    panIconScroller->Top = std::min(0, panIconScroller->Top + 80);
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::spdPluginsDownClick(TObject *Sender)
{
    panIconScroller->Top = std::max(panButtonContainer->Height - panIconScroller->Height, panIconScroller->Top - 80);
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::chkUndoEnableUndoClick(TObject *Sender)
{
    cmdApply->Enabled = true;
    chkUndoMemoryLimit->Enabled = chkUndoEnableUndo->Checked;
	edtUndoMemory->Enabled = chkUndoEnableUndo->Checked;
	lblUndoMB->Enabled = chkUndoEnableUndo->Checked;
	chkUndoEnabledRedo->Enabled = chkUndoEnableUndo->Checked;
	chkUndoClear->Enabled = chkUndoEnableUndo->Checked;
    chkUndoEnableDialog->Enabled = chkUndoEnableUndo->Checked;
    radUndoAutoSwitchTo->Enabled = chkUndoEnableUndo->Checked;
    radUndoGroupByPlugin->Enabled = chkUndoEnableUndo->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    if (false == tmrScrollTimer->Enabled)
    {
        tmrScrollTimer->Enabled = true;

        if (WheelDelta > 0)
        {
            spdPluginsUpClick(NULL);
        }
        else if (WheelDelta < 0)
        {
            spdPluginsDownClick(NULL);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::tmrScrollTimerTimer(TObject *Sender)
{
    tmrScrollTimer->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::chkBackupEnabledClick(TObject *Sender)
{
    cmdApply->Enabled = true;
    chkLimitBackupUsage->Enabled = chkBackupEnabled->Checked;
    edtBackupFolders->Enabled = chkBackupEnabled->Checked;
    lblBackupFolders->Enabled = chkBackupEnabled->Checked;
    lblBackupWhen->Enabled = chkBackupEnabled->Checked;
    radBackupOnSave->Enabled = chkBackupEnabled->Checked;
    lblBackupOnSave->Enabled = chkBackupEnabled->Checked;
    radBackupOnClose->Enabled = chkBackupEnabled->Checked;
    lblBackupOnClose->Enabled = chkBackupEnabled->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::lblAppDataFolderClick(TObject *Sender)
{
    String path = getenv("APPDATA");
    path += "\\TommyGun\\";
    ShellExecute(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

