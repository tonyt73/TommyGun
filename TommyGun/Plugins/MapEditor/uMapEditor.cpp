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
const String g_sPluginTitle = "Maps";
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
HRESULT __fastcall TfrmMapEditor::Initialise(TZX_HPLUGIN PluginHandle)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    // save the plugin handle
    m_PluginHandle = PluginHandle;
    m_MapEditor.PluginHandle = m_PluginHandle;
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
            m_bInitialized = true;

            bool bValue = true;
            if (regScorpio->Read("MapEditor", "MergeDupScreens", bValue))
            {
                chkMergeDuplicates->Checked = bValue;
                chkMergeDuplicatesClick(NULL);
            }

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
HRESULT __fastcall TfrmMapEditor::Release(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    SAFE_DELETE(m_MapTools);
    SAFE_DELETE(m_mnuMap);
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
void __fastcall TfrmMapEditor::AttachToolbars(void)
{
    /*for (int i = 0; i < Application->MainForm->ControlCount; ++i)
    {
        TControlBar* ControlBar = dynamic_cast<TControlBar*>(Application->MainForm->Controls[i]);
        if (true == SAFE_PTR(ControlBar))
        {
            // found the control so move our toolbars onto toolbar
            tbrMapTools->Visible    = true;//S_OK == IsActivePlugin(m_PluginHandle);
            tbrMapTools->Parent     = ControlBar;
            tbrMapTools->Left       = 200;
        }
    }*/
    TMenuItem* ViewMenu = Application->MainForm->Menu->Items->Find("View");
    if (ViewMenu)
    {
        TMenuItem* Toolbars = ViewMenu->Find("Toolbars");
        if (Toolbars)
        {
            m_MapTools              = new TMenuItem(NULL);
            m_MapTools->Caption     = "Map Tools";
            m_MapTools->Checked     = true;
            m_MapTools->Tag         = (int)tbrMapTools;
            m_MapTools->OnClick     = OnMenuClick;
            m_MapTools->Visible     = true;//S_OK == IsActivePlugin(m_PluginHandle);
            Toolbars->Add(m_MapTools);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::OnMenuClick(TObject* Sender)
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
void __fastcall TfrmMapEditor::TrapTabEvents(TWinControl* Control)
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
void __fastcall TfrmMapEditor::OnTabHide(TObject *Sender)
{
    //MenusRemove();
    m_MapTools->Visible = false;
    m_mnuMap->Visible = false;
    m_mnuMap->Enabled = false;
    mnuBringToFront->ShortCut = ShortCut(0, TShiftState());
    mnuSendToBack->ShortCut = ShortCut(0, TShiftState());
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::OnTabShow(TObject *Sender)
{
    m_MapTools->Visible = true;
    m_mnuMap->Visible = true;
    //tbrMapTools->Visible = m_MapTools->Checked;
    m_TileBrowser.Zoom(spnTilesZoom->Value);
    if (true == m_bImageChanged)
    {
        // refresh the images in the tile manager and browser
        m_TileBrowser.Refresh();
        m_SpriteBrowser.Refresh();
        m_ObjectBrowser.Refresh();
        m_ScorePanel.Refresh();
        m_ScorePanel.Update();
    }
    m_mnuMap->Enabled = true;
    mnuBringToFront->ShortCut = ShortCut(VK_HOME, TShiftState());
    mnuSendToBack->ShortCut = ShortCut(VK_END, TShiftState());
    UpdateScreenEditor();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmMapEditor::IsDirty(void)
{
    return m_Map.IsDirty;
}
//---------------------------------------------------------------------------
String __fastcall TfrmMapEditor::ZeroPadInt(int iValue, int iSize)
{
    String sValue = "000" + IntToStr(iValue);
    sValue = sValue.SubString(sValue.Length() - iSize + 1, iSize);
    return sValue;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::UndoRestore(KXmlInfo* xmlInfo)
{
    m_Map.UndoRestore(xmlInfo);
    m_MapEditor.UndoRestore(xmlInfo);
    m_MapEditor.Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::NewMap(int screenWidth, int screenHeight, int screensAcross, int screensDown, bool overwrite)
{
    float dx, dy;
    m_TileManager.GetScalar(dx, dy);
    edtMapScreenSizeWidth->Value = screenWidth;
    edtMapScreenSizeHeight->Value = screenHeight;
    m_MapEditor.SetScreenSize(edtMapScreenSizeWidth->Value, edtMapScreenSizeHeight->Value);
    //panTiles->Width  = m_Map.ScreenWidth  * edtMapEditorScreenLayoutMagnificationSize->Value * dx;
    //panTiles->Height = m_Map.ScreenHeight * edtMapEditorScreenLayoutMagnificationSize->Value * dy;
    //imgTiles->Picture->Bitmap->Width  = imgTiles->Width;
    //imgTiles->Picture->Bitmap->Height = imgTiles->Height;
    //imgScorePanel->Height = 16 * edtMapEditorScreenLayoutMagnificationSize->Value;
    edtMapMapSizeScreensAcross->Value = screensAcross;
    edtMapMapSizeScreensDown->Value = screensDown;
    m_MapEditor.SetScreenGrid(edtMapMapSizeScreensAcross->Value, edtMapMapSizeScreensDown->Value);
    UpdateScreenEditor();
    //m_MapEditor.Update();

    if (m_Map.New(screenWidth, screenHeight, screensAcross, screensDown, overwrite))
    {
        tbnMapScreenAddAllClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::MenusAdd(void)
{
    if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
    {
        popMap->Items->Remove(mnuSelectMode);
        popMap->Items->Remove(mnuPlaceMode);
        popMap->Items->Remove(mnuSnaptoGridToggle);
        popMap->Items->Remove(mnuAllowIntersect);
        popMap->Items->Remove(mnuToggleGrid);
        popMap->Items->Remove(mnuBringToFront);
        popMap->Items->Remove(mnuSendToBack);
        popMap->Items->Remove(mnuSaveMapBitmap);
        TMenuItem* mnuEdit = Application->MainForm->Menu->Items->Find("&Edit");
        if (true == SAFE_PTR(mnuEdit))
        {
            if (m_mnuMap == NULL)
            {
                AddMenu("&Map", m_mnuMap);
            }
            if (m_mnuMap)
            {
                m_mnuMap->Visible = false;
                m_mnuMap->Add(mnuSelectMode);
                m_mnuMap->Add(mnuPlaceMode);
                m_mnuMap->Add(mnuSnaptoGridToggle);
                m_mnuMap->Add(mnuAllowIntersect);
                m_mnuMap->Add(mnuToggleGrid);
                m_mnuMap->Add(mnuBringToFront);
                m_mnuMap->Add(mnuSendToBack);
                m_mnuMap->NewBottomLine();
                m_mnuMap->Add(mnuSaveMapBitmap);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::MenusRemove(void)
{
    if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
    {
        TMenuItem* mnuEdit = Application->MainForm->Menu->Items->Find("&Edit");
        if (true == SAFE_PTR(mnuEdit))
        {
            mnuEdit->Remove(mnuSelectMode);
            mnuEdit->Remove(mnuPlaceMode);
            mnuEdit->Remove(mnuSnaptoGridToggle);
            mnuEdit->Remove(mnuAllowIntersect);
            mnuEdit->Remove(mnuToggleGrid);
            mnuEdit->Remove(mnuBringToFront);
            mnuEdit->Remove(mnuSendToBack);
        }
        popMap->Items->Add(mnuSelectMode);
        popMap->Items->Add(mnuPlaceMode);
        popMap->Items->Add(mnuSnaptoGridToggle);
        popMap->Items->Add(mnuAllowIntersect);
        popMap->Items->Add(mnuToggleGrid);
        popMap->Items->Add(mnuBringToFront);
        popMap->Items->Add(mnuSendToBack);
    }
}
//---------------------------------------------------------------------------


