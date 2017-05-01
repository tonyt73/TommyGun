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
#include "ZXStatusBar.h"
#include "ZXGUIManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GUI;
//---------------------------------------------------------------------------
__fastcall ZXStatusBar::ZXStatusBar()
: m_StatusBar(NULL)
, m_ActivePlugin(NULL)
, m_IconList(NULL)
{
}
//---------------------------------------------------------------------------
__fastcall ZXStatusBar::~ZXStatusBar()
{
    Free();
}
//---------------------------------------------------------------------------
void __fastcall ZXStatusBar::Setup(TStatusBar* StatusBar, TImageList* IconList)
{
    m_StatusBar = StatusBar;
    m_IconList  = IconList;
    StatusBar->OnDrawPanel = DrawPanel;
    StatusBar->OnMouseMove = MouseMove;
    StatusBar->OnMouseDown = MouseDown;
}
//---------------------------------------------------------------------------
void __fastcall ZXStatusBar::Free()
{
    m_StatusBar    = NULL;
    m_ActivePlugin = NULL;
    m_IconList     = NULL;
}
//---------------------------------------------------------------------------
void __fastcall ZXStatusBar::MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (mbLeft == Button)
    {
        for (unsigned int i = 0; i < m_Icons.size(); i++)
        {
            if (m_Icons[i].iPosition < X && X < m_Icons[i].iPosition + 16)
            {
                // switch to the plugin clicked on
                PostNotifyEvent(m_Icons[i].hPlugin, TZX_VERB_SWITCH_PLUGIN, NULL, 0, 0);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXStatusBar::MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    m_StatusBar->Hint = "";
    for (unsigned int i = 0; i < m_Icons.size(); i++)
    {
        if (m_Icons[i].iPosition < X && X < m_Icons[i].iPosition + 16)
        {
            Application->Hint = m_Icons[i].sDescription;
            if (i < 12)
            {
                Application->Hint += "\nCtrl + F" + IntToStr(i + 1) + " to switch";
            }
            m_StatusBar->Hint = Application->Hint;
            Application->ActivateHint(m_StatusBar->ClientToScreen(TPoint(X, Y)));
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXStatusBar::DrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect)
{
    DrawPluginIcons(Panel, Rect);
}
//---------------------------------------------------------------------------
void __fastcall ZXStatusBar::DrawPluginIcons(TStatusPanel *Panel, const TRect &Rect)
{
    int iX = 0;
    m_StatusBar->Canvas->Brush->Color = clWhite;
    m_StatusBar->Canvas->FillRect(Rect);
    for (unsigned int i = 0; i < m_Icons.size(); i++)
    {
        if (m_ActivePlugin == m_Icons[i].hPlugin)
        {
            TRect NewRect(Rect.Left + iX, Rect.Top, Rect.Left + iX + 17, Rect.Bottom);
            m_StatusBar->Canvas->Brush->Color = clLime; //clHighlight;
            m_StatusBar->Canvas->FillRect(NewRect);
            m_StatusBar->Canvas->Brush->Color = clWhite;
        }
        m_IconList->Draw(m_StatusBar->Canvas, Rect.Left + iX, Rect.Top + 1, m_Icons[i].iIcon, true);
        m_Icons[i].iPosition = Rect.Left + iX;
        iX += 18;
    }
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXStatusBar::AddStatusPanel(TZX_HPLUGIN PluginHandle, unsigned int PanelIndex)
{
    return E_FAIL;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXStatusBar::RemoveStatusPanel(TZX_HPLUGIN PluginHandle, unsigned int PanelIndex)
{
    return E_FAIL;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXStatusBar::SetStatusPanelCaption(TZX_HPLUGIN PluginHandle, unsigned int PanelIndex, const String& Caption)
{
    return E_FAIL;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXStatusBar::SetStatusPanelSize(TZX_HPLUGIN PluginHandle, unsigned int PanelIndex, unsigned int Size)
{
    return E_FAIL;
}
//---------------------------------------------------------------------------
void __fastcall ZXStatusBar::AddPluginIcon(TZX_HPLUGIN PluginHandle, TImage* Icon, const String& sDescription)
{
    // if plugin exists then
    //      modify the plugin icon
    //      if Icon is null then
    //          remove the icon and plugin
    //          redraw the icons
    //      else
    //          change the plugins icon
    //      endif
    // else
    //      make a new icon for the plugin
    // endif
    IconIterator IconIt = FindIcon(PluginHandle);
    if (IconIt != m_Icons.end())
    {
        // plugin exists
        if (sDescription != "")
        {
            IconIt->sDescription = sDescription;
        }
        if (NULL != Icon)
        {
            IconIt->iIcon = m_IconList->AddMasked(Icon->Picture->Bitmap, clFuchsia);
        }
    }
    else
    {
        if (NULL == m_ActivePlugin)
        {
            m_ActivePlugin = PluginHandle;
        }
        // new plugin entry
        TIconInfo IconInfo;
        IconInfo.hPlugin = PluginHandle;
        IconInfo.sDescription = sDescription;
        IconInfo.iIcon = 0; // use the default index
        if (NULL != Icon)
        {
            IconInfo.iIcon = m_IconList->AddMasked(Icon->Picture->Bitmap, clFuchsia);
        }
        m_Icons.push_back(IconInfo);
    }
    // redraw the status bar
    m_StatusBar->Refresh();
    m_StatusBar->Update();
}
//---------------------------------------------------------------------------
void __fastcall ZXStatusBar::RemovePluginIcon(TZX_HPLUGIN PluginHandle)
{
    IconIterator IconIt = FindIcon(PluginHandle);
    if (IconIt != m_Icons.end())
    {
        // plugin exists
        m_Icons.erase(IconIt);
        m_StatusBar->Refresh();
        m_StatusBar->Update();
    }
}
//---------------------------------------------------------------------------
IconIterator __fastcall ZXStatusBar::FindIcon(TZX_HPLUGIN PluginHandle)
{
    IconIterator it = m_Icons.begin();
    for (unsigned int i = 0; i < m_Icons.size(); i++)
    {
        if (m_Icons[i].hPlugin == PluginHandle)
        {
            break;
        }
        it++;
    }
    return it;
}
//---------------------------------------------------------------------------
void __fastcall ZXStatusBar::ActivePlugin(TZX_HPLUGIN PluginHandle)
{
    m_ActivePlugin = PluginHandle;
    m_StatusBar->Refresh();
}
//---------------------------------------------------------------------------

