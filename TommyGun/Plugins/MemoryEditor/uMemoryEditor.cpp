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
const String g_sPluginTitle = "Memory";
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
HRESULT __fastcall TfrmMemoryEditor::Initialise(TZX_HPLUGIN PluginHandle)
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
            InitMemoryObjects();
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
HRESULT __fastcall TfrmMemoryEditor::Release(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    // Hide the form before releasing
    Visible = false;
    // Detach ourselves from the parent
    Parent->RemoveControl(this);
    // remove the tab we were allocated by shell
    RemovePage(m_PluginHandle, m_TabHandle);
    // reset our handle
    m_PluginHandle = 0;
    m_bInitialized = false;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::AttachToolbars(void)
{
    /*for (int i = 0; i < Application->MainForm->ControlCount; ++i)
    {
        TControlBar* ControlBar = dynamic_cast<TControlBar*>(Application->MainForm->Controls[i]);
        if (true == SAFE_PTR(ControlBar))
        {
            // found the control so move our toolbars onto toolbar
            tbrMemoryTools->Visible    = true;//S_OK == IsActivePlugin(m_PluginHandle);
            tbrMemoryTools->Parent     = ControlBar;
            tbrMemoryTools->Left       = 200;
        }
    }*/
    /*TMenuItem* ViewMenu = Application->MainForm->Menu->Items->Find("View");
    if (ViewMenu)
    {
        TMenuItem* Toolbars = ViewMenu->Find("Toolbars");
        if (Toolbars)
        {
            m_MemoryTools              = new TMenuItem(NULL);
            m_MemoryTools->Caption     = "Memory Tools";
            m_MemoryTools->Checked     = true;
            m_MemoryTools->Tag         = (int)tbrMemoryTools;
            m_MemoryTools->OnClick     = OnMenuClick;
            m_MemoryTools->Visible     = true;//S_OK == IsActivePlugin(m_PluginHandle);
            Toolbars->Add(m_MemoryTools);
        }
    }*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::OnMenuClick(TObject* Sender)
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
void __fastcall TfrmMemoryEditor::TrapTabEvents(TWinControl* Control)
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
void __fastcall TfrmMemoryEditor::OnTabHide(TObject *Sender)
{
    //tbrMemoryTools->Visible = false;
    //m_MemoryTools->Visible  = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::OnTabShow(TObject *Sender)
{
    //m_MemoryTools->Visible  = true;
    //tbrMemoryTools->Visible = m_MemoryTools->Checked;
}
//---------------------------------------------------------------------------


