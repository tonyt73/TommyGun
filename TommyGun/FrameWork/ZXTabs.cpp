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
#include "..\SafeMacros.h"
#include "ZXTabs.h"
#include "ZXLogFile.h"
#include "ZXGUIManager.h"
#include "ZXPluginManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace Logging;
using namespace GUI;
//---------------------------------------------------------------------------
const int   g_iNoImage     = -1;
//---------------------------------------------------------------------------
__fastcall ZXTabs::ZXTabs()
: m_ViewPage(NULL),
  m_OptionsPage(NULL),
  m_TabSheet(NULL)
{
}
//---------------------------------------------------------------------------
__fastcall ZXTabs::~ZXTabs()
{
    Free();
    if (0 != m_Tabs.size())
    {
        ZX_LOG_ERROR(lfGeneral, "Not all Tabs freed");
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXTabs::Setup(TPageControl* ViewPage, TPageControl* OptionsPage, TImageList* Images)
{
    m_ViewPage      = ViewPage;
    m_OptionsPage   = OptionsPage;
    m_StartPage     = ViewPage->ActivePage;
    m_Bitmaps.Setup(Images);

    if (false == SAFE_PTR(m_TabSheet))
    {
        m_TabSheet = new TTabSheet(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXTabs::Free(void)
{
    TZXTabInfoIterator TabIt = m_Tabs.begin();
    while(TabIt != m_Tabs.end())
    {
        if (S_FALSE != RemoveTab(TabIt->hOwner, TabIt->Control->Handle))
        {
            TabIt = m_Tabs.begin();
        }
        else
        {
            TabIt++;
        }
    }
    m_Tabs.clear();
    SAFE_DELETE(m_TabSheet);
}
//---------------------------------------------------------------------------
// Free
/**
 * Removes all tabs owned by a plugin
 * @param   PluginHandle the plugin handle to remove all the tabs for
 * @author  Tony Thompson
 * @date    Last Modified 15 November 2001
 * @date    Last Modified 22 September 2003
 * @remarks
 */
//---------------------------------------------------------------------------
void __fastcall ZXTabs::Free(TZX_HPLUGIN PluginHandle)
{
    TZXTabInfoIterator TabIt = m_Tabs.begin();
    while(TabIt != m_Tabs.end())
    {
        if (TabIt->hOwner == PluginHandle && S_OK == RemoveTab(PluginHandle, TabIt->Control->Handle))
        {
            TabIt = m_Tabs.begin();
        }
        else
        {
            TabIt++;
        }
    }
}
//---------------------------------------------------------------------------
// FindTabControl
/**
 * Finds a tab control based on a HWND handle
 * @param   PluginHandle owner of the tab
 * @param   Handle the unique HWND Handle for the TabSheet
 * @param   Access allows a caller to change the property if the plugin is the owner, else they get the dummy control
 * @param   hResult returns the successful or failure of the operation
 * @return  Returns a valid TabSheet item to change
 * @author  Tony Thompson
 * @date    Last Modified 30 October 2001
 * @date    Last Modified 22 September 2003
 */
//---------------------------------------------------------------------------
TTabSheet* __fastcall ZXTabs::FindTabControl(TZX_HPLUGIN PluginHandle, HWND Handle, bool Access, HRESULT& hResult)
{
    // set the default failure for the operation
    hResult = S_FALSE;
    TTabSheet* TabSheet = NULL;
    // find the tab item from the lists
    TZXTabInfoIterator TabIt = std::find(m_Tabs.begin(), m_Tabs.end(), Handle);
    // check for search success
    if (TabIt != m_Tabs.end())
    {
        // found a real tab, so return our success
        TabSheet = TabIt->Control;
        hResult = S_OK;
    }
    else
    {
        // failed to find the tab, so return the dummy tab item as a valid tab item to change
        TabSheet = m_TabSheet;
        // reset the dummy tab item
		m_TabSheet->Caption    = "";
        m_TabSheet->Hint       = "";
        m_TabSheet->Enabled    = false;
        m_TabSheet->Visible    = false;
        m_TabSheet->TabVisible = false;
        m_TabSheet->Tag        = 0;
    }
    return TabSheet;
}
//---------------------------------------------------------------------------
// TabOnShow
/**
 * OnShow event that generates OnShow messages for a tab sheet and its plugin
 *
 * @param           Sender the tab sheet that generated the event
 * @return          none
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 * @date            Last Modified 22 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall ZXTabs::TabOnShow(TObject *Sender)
{
    if (true == SAFE_PTR(Sender) && true == Sender->InheritsFrom(__classid(TTabSheet)))
    {
        TTabSheet* TabSheet = static_cast<TTabSheet*>(Sender);
        g_PluginManager.NotifyPlugin((TZX_HPLUGIN)TabSheet->Tag, TZXN_TABSHOW, NULL, 0, (DWORD)(TabSheet->Handle));
        //g_GuiManager.UpdateBrowserCaption();
    }
}
//---------------------------------------------------------------------------
// TabOnHide
/**
 * OnHide event that generates OnShow messages for a tab sheet and its plugin
 * @param           Sender the tab sheet that generated the event
 * @return          none
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 * @date            Last Modified 22 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall ZXTabs::TabOnHide(TObject *Sender)
{
    if (true == SAFE_PTR(Sender) && true == Sender->InheritsFrom(__classid(TTabSheet)))
    {
        TTabSheet* TabSheet = static_cast<TTabSheet*>(Sender);
        g_PluginManager.NotifyPlugin((TZX_HPLUGIN)TabSheet->Tag, TZXN_TABHIDE, NULL, 0, (DWORD)(TabSheet->Handle));
    }
}
//---------------------------------------------------------------------------
// AddTab
/**
 * Adds a new TabSheet to 1 of 2 page controls
 * @param   PluginHandle handle of the plugin to own the TabSheet
 * @param   VCLParent the parent vcl control of the Tab (PageControl)
 * @param   Caption the name displayed on the Tab
 * @param   AddToViewTab flag to indicate adding the tab to the view page control
 * @return  S_OK if successful, else S_FALSE
 * @author  Tony Thompson
 * @date    Last Modified 30 October 2001
 * @date    Last Modified 22 September 2003
 * @remarks
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXTabs::AddTab(TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Caption)
{
    HRESULT hResult = S_FALSE;
    if (true == g_PluginManager.IsPluginValid(PluginHandle))
    {
        TTabSheet* TabSheet = NULL;
        try
        {
            // ok, make a new TabSheet sheet
            TabSheet = new TTabSheet(this);
        }
        catch(EOutOfMemory&)
        {
            TabSheet = NULL;
            // operation successful
            hResult = S_FALSE;
        }
        if (true == SAFE_PTR(TabSheet))
        {
            // give it a name
            TabSheet->Name = "TabSheet" + IntToStr(PluginHandle) + IntToStr(m_Tabs.size());
            // set the TabSheets caption
            TabSheet->Caption = Caption;
            // no bitmap
            TabSheet->ImageIndex = g_iNoImage;
            // no hint
            TabSheet->Hint = "";
            // no showing the hint
            TabSheet->ShowHint = false;
            // set up the show/hide event handlers
            TabSheet->OnShow = TabOnShow;
            TabSheet->OnHide = TabOnHide;
            TabSheet->Tag    = (int)PluginHandle;
            // double buffer the control
            //TabSheet->DoubleBuffered = true;
            TabSheet->PageControl = m_ViewPage;
            m_ViewPage->ActivePageIndex = 0;
            m_StartPage->PageIndex = m_ViewPage->PageCount - 1;
            // return the newly acquired handle to the plugin
            VCLParent = TabSheet;
            // save the TabSheet info in the plugins information struct
            TZXTabInfo TabInfo;
            TabInfo.hOwner = PluginHandle;
            TabInfo.Control = TabSheet;
            m_Tabs.push_back(TabInfo);
            // operation successful
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
// RemoveTab
/**
 * Removes a tab from a page control
 * @param   PluginHandle handle of the plugin who owns the TabSheet
 * @param   Handle the Windows HWND of the tab control
 * @return  S_OK if successful, else S_FALSE
 * @author  Tony Thompson
 * @date    Last Modified 30 October 2001
 * @date    Last Modified 22 September 2003
 * @remarks
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXTabs::RemoveTab(TZX_HPLUGIN PluginHandle, HWND Handle)
{
    HRESULT hResult = S_FALSE;
    if (true == g_PluginManager.IsPluginValid(PluginHandle))
    {
        // ok, does the HWND belong to them?
        TZXTabInfoIterator TabIt = std::find(m_Tabs.begin(), m_Tabs.end(), Handle);
        // did we find the HWND
        if (TabIt != m_Tabs.end() && true == SAFE_PTR(TabIt->Control))
        {
            // yes, they own it, so remove the tab entry
            TPageControl* PageControl = dynamic_cast<TPageControl*>(TabIt->Control->Parent);
            if (true == SAFE_PTR(PageControl))
            {
                TabIt->Control->Visible = false;
                TabIt->Control->TabVisible = false;
                SAFE_DELETE(TabIt->Control);
            }
            m_Tabs.erase(TabIt);
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
// SetTabBitmap
/**
 * Sets the bitmap of the TabSheet
 * @param   PluginHandle handle of the plugin who owns the TabSheet
 * @param   Handle the Windows HWND of the tab control
 * @param   BitmapHandle the HBITMAP of a bitmap to set
 * @return  S_OK if successful, else S_FALSE
 * @author  Tony Thompson
 * @date    Last Modified 30 October 2001
 * @date    Last Modified 22 September 2003
 * @remarks
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXTabs::SetTabBitmap(TZX_HPLUGIN PluginHandle, HWND  Handle, TImage* Bitmap)
{
    HRESULT hResult = S_FALSE;
    FindTabControl(PluginHandle, Handle, false, hResult)->ImageIndex = m_Bitmaps.Add(PluginHandle, Bitmap);
    return hResult;
}
//---------------------------------------------------------------------------
// AddOptionsTab
/**
 * Adds an options page tab to the options dialog
 * @param           PluginHandle the Handle to the plugin that requested the service
 * @param           Handle the HWND handle of the tab control - See AddTab for more details
 * @param           Name the caption of the Tab
 * @return          HRESULT S_OK successful, S_FALSE failed
 * @author          Tony Thompson
 * @date            Last Modified 29 November 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXTabs::AddOptionsTab(TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Name)
{
    HRESULT hResult = S_FALSE;
    if (true == g_PluginManager.IsPluginValid(PluginHandle))
    {
        // ok, make a new tab sheet
        TTabSheet* tab = NULL;
        try
        {
            tab = new TTabSheet(this);
        }
        catch(EOutOfMemory&)
        {
            tab = NULL;
            hResult = S_FALSE;
        }

        if (true == SAFE_PTR(tab))
        {
            // give it a name
            tab->Name = "TabSheet" + IntToStr(PluginHandle) + IntToStr(m_Tabs.size())  + "OptionsPanel";
            // set the tabs caption
            tab->Caption = Name;
            // no bitmap
            tab->ImageIndex = g_iNoImage;
            // no hint
            tab->Hint = "";
            // no showing the hint
            tab->ShowHint = false;
            // tab is visible to user
            //tab->TabVisible = true;
            //tab->Visible = true;
            tab->Tag = (int)PluginHandle;
            // double buffer the control
            tab->DoubleBuffered = true;
            // add the tab to options page control
            tab->PageControl = m_OptionsPage;
            //m_OptionsPage->ActivePage = tab;
            m_OptionsPage->ActivePageIndex = 0;
            // return the newly acquired handle to the plugin
            VCLParent = tab;
            // save the TabSheet info in the plugins information struct
            TZXTabInfo TabInfo;
            TabInfo.hOwner = PluginHandle;
            TabInfo.Control = tab;
            m_Tabs.push_back(TabInfo);
            // operation successful
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXTabs::ActivatePlugin(TZX_HPLUGIN PluginHandle)
{
    // find the plugins tab and set to be the active tab on the page control
    for (unsigned int i = 0; i < m_Tabs.size(); i++)
    {
        if (PluginHandle == m_Tabs[i].hOwner && true == SAFE_PTR(m_Tabs[i].Control))
        {
            // make the tab sheet the active tab sheet
            m_Tabs[i].Control->PageControl->ActivePage = m_Tabs[i].Control;
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXTabs::IsActivePlugin(TZX_HPLUGIN PluginHandle)
{
    bool bActivePlugin = false;
    for (unsigned int i = 0; i < m_Tabs.size() && false == bActivePlugin; i++)
    {
        if (PluginHandle == m_Tabs[i].hOwner && true == SAFE_PTR(m_Tabs[i].Control))
        {
            bActivePlugin = m_Tabs[i].Control->PageControl->ActivePage == m_Tabs[i].Control;
        }
    }
    return bActivePlugin;
}
//---------------------------------------------------------------------------

