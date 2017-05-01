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
#pragma link "KRegistry"
//-- NAMESPACES -------------------------------------------------------------
using namespace Scorpio;
using namespace Logging;
using namespace GameEditor;
//-- VCL FORM OBJECT --------------------------------------------------------
TfrmGameEditor *frmGameEditor;
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the class and reset some member variables
 * @param   Owner the VCL owner of the form
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @date    Modified 3 May 2002 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
__fastcall TfrmGameEditor::TfrmGameEditor(TComponent* Owner)
: TForm(Owner)
, m_bInitialized(false)
{
    RL_METHOD
}
//---------------------------------------------------------------------------
// Destructor
/**
 * @brief   Frees allocated resources
 * @author  Tony Thompson
 * @date    Created 10 March 2003 by Tony Thompson
 * @remarks Copyright Scorpio Software 2003
 */
//---------------------------------------------------------------------------
__fastcall TfrmGameEditor::~TfrmGameEditor()
{
    RL_METHOD
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::FormCreate(TObject *Sender)
{
    //MenusAdd();
}
//-- CONSTANTS --------------------------------------------------------------
const String g_sPluginTitle = "Designer";
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
HRESULT __fastcall TfrmGameEditor::Initialise(TZX_HPLUGIN PluginHandle)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    // save the plugin handle
    m_PluginHandle = PluginHandle;
    // place the form onto the tab control
    TWinControl* tmpWindow = NULL;
    hResult = S_FALSE;
    tbrImageGridTools->CustomizeKeyName = "Software\\Scorpio\\TommyGun";
    tbrImageGridTools->CustomizeValueName = "ToolBars";
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
            //AddToolBar(tbrImagePaintTools);
            //AddToolBar(tbrImageGridTools);
            OnTabHide(NULL);
            //LoadSettings();
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
HRESULT __fastcall TfrmGameEditor::Release(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    //SaveSettings();
    for (unsigned int i = 0; i < m_ToolBarMenus.size(); i++)
    {
        SAFE_DELETE(m_ToolBarMenus[i]);
    }
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
void __fastcall TfrmGameEditor::OnMenuClick(TObject* Sender)
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
void __fastcall TfrmGameEditor::TrapTabEvents(TWinControl* Control)
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
void __fastcall TfrmGameEditor::OnTabHide(TObject *Sender)
{
    //MenusRemove();
    if (m_ToolBars.size() == m_ToolBarMenus.size())
    {
        for (unsigned int i = 0; i < m_ToolBars.size(); i++)
        {
            //m_ToolBars[i]->Visible = false;
            if (true == SAFE_PTR(m_ToolBarMenus[i]))
            {
                m_ToolBarMenus[i]->Visible  = false;
            }
            else
            {
                // why is the menu NULL?
                m_ToolBarMenus[i] = NULL;
            }
        }
    }
    else
    {
        //ZX_LOG_ERROR(lfGeneral, "The ToolBar list and the ToolbarMenu list sizes do not match!")
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::OnTabShow(TObject *Sender)
{
    if (m_ToolBars.size() == m_ToolBarMenus.size())
    {
        for (unsigned int i = 0; i < m_ToolBars.size(); i++)
        {
            m_ToolBarMenus[i]->Visible  = true;
            //m_ToolBars[i]->Visible = m_ToolBarMenus[i]->Checked;
        }
    }
    else
    {
        //ZX_LOG_ERROR(lfGeneral, "The ToolBar list and the ToolbarMenu list sizes do not match!")
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::RefreshView(void)
{
	// update stuff
}
//---------------------------------------------------------------------------
String __fastcall TfrmGameEditor::ZeroPadInt(int iValue, int iSize)
{
    String sValue = "000" + IntToStr(iValue);
    sValue = sValue.SubString(sValue.Length() - iSize + 1, iSize);
    return sValue;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::LoadSettings(void)
{
    bool bValue = false;
    int  iValue = 0;
    TColor cValue = clBlack;

    /*if (regScorpio->Read("GameEditor", "CenterImage"     , bValue)) chkCenterImage->Checked = bValue;
    if (regScorpio->Read("GameEditor", "BackgroundColor" , cValue)) panBackgroundColor->Color = cValue;
    if (regScorpio->Read("GameEditor", "ShowGridChar"    , bValue)) chkGridCharacter->Checked = bValue;
    if (regScorpio->Read("GameEditor", "ShowGridPixel"   , bValue)) chkGridPixel->Checked = bValue;
    if (regScorpio->Read("GameEditor", "AutoMagnify"     , bValue)) chkAutoMagnification->Checked = bValue;
    if (regScorpio->Read("GameEditor", "Magnification"   , iValue)) slrDisplayMagnification->Position = iValue;
    if (regScorpio->Read("GameEditor", "MaskTransparency", iValue)) slrMaskTransparency->Position = iValue;
    if (regScorpio->Read("GameEditor", "MaskColor"       , cValue)) panMaskColor->Color = cValue;
    if (regScorpio->Read("GameEditor", "ChrLineColor"    , cValue)) panChrLineColor->Color = cValue;
    if (regScorpio->Read("GameEditor", "PixelLineColor"  , cValue)) panPixelLineColor->Color = cValue;
    if (regScorpio->Read("GameEditor", "XScaleFacter"    , iValue)) slrCustomXScale->Position = iValue;
    if (regScorpio->Read("GameEditor", "YScaleFacter"    , iValue)) slrCustomYScale->Position = iValue;
    if (regScorpio->Read("GameEditor", "ScaleMode"       , iValue))
    {
        radModeScaleDefault->Checked = iValue == 0;
        radModeScaleRemove->Checked  = iValue == 1;
        radModeScaleCustom->Checked  = iValue == 2;
        UpdateModeScale();
    }
    sbxEditor->Color = panBackgroundColor->Color;
    */
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::SaveSettings(void)
{
    /*regScorpio->Write("GameEditor", "CenterImage"      , chkCenterImage->Checked           );
    regScorpio->Write("GameEditor", "BackgroundColor"  , panBackgroundColor->Color         );
    regScorpio->Write("GameEditor", "ShowGridChar"     , chkGridCharacter->Checked         );
    regScorpio->Write("GameEditor", "ShowGridPixel"    , chkGridPixel->Checked             );
    regScorpio->Write("GameEditor", "AutoMagnify"      , chkAutoMagnification->Checked     );
    regScorpio->Write("GameEditor", "Magnification"    , slrDisplayMagnification->Position );
    regScorpio->Write("GameEditor", "MaskTransparency" , slrMaskTransparency->Position     );
    regScorpio->Write("GameEditor", "MaskColor"        , panMaskColor->Color               );
    regScorpio->Write("GameEditor", "ChrLineColor"     , panChrLineColor->Color            );
    regScorpio->Write("GameEditor", "PixelLineColor"   , panPixelLineColor->Color          );
    regScorpio->Write("GameEditor", "XScaleFactor"     , slrCustomXScale->Position         );
    regScorpio->Write("GameEditor", "YScaleFactor"     , slrCustomYScale->Position         );
    if (radModeScaleDefault->Checked) regScorpio->Write("GameEditor", "ScaleMode" , 0);
    else if (radModeScaleRemove->Checked) regScorpio->Write("GameEditor", "ScaleMode" , 1);
    else regScorpio->Write("GameEditor", "ScaleMode" , 2);
    */
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::EditCopy(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::EditCut(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::EditPaste(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::MenusAdd(void)
{
    /*if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
    {
        popImage->Items->Remove(popToggleGridChar);
        popImage->Items->Remove(popToggleGridPixel);
        popImage->Items->Remove(popZoomIn);
        popImage->Items->Remove(popZoomOut);
        TMenuItem* mnuEdit = Application->MainForm->Menu->Items->Find("&Edit");
        if (true == SAFE_PTR(mnuEdit))
        {
            mnuEdit->NewBottomLine();
            mnuEdit->Add(popToggleGridChar);
            mnuEdit->Add(popToggleGridPixel);
            mnuEdit->Add(popZoomIn);
            mnuEdit->Add(popZoomOut);
        }
    }*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::MenusRemove(void)
{
    /*if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
    {
        TMenuItem* mnuEdit = Application->MainForm->Menu->Items->Find("&Edit");
        if (true == SAFE_PTR(mnuEdit))
        {
            mnuEdit->NewBottomLine();
            mnuEdit->Remove(popToggleGridChar);
            mnuEdit->Remove(popToggleGridPixel);
            mnuEdit->Remove(popZoomIn);
            mnuEdit->Remove(popZoomOut);
        }
        popImage->Items->Add(popToggleGridChar);
        popImage->Items->Add(popToggleGridPixel);
        popImage->Items->Add(popZoomIn);
        popImage->Items->Add(popZoomOut);
    }*/
}
//---------------------------------------------------------------------------

