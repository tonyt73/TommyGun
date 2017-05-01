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

-----------------------------------------------------------------------------

    FrameworkInterface.cpp

    This file implements the Framework API interfaces.
    Its main task is to provide pass through interfaces into the RWFramework object.

---------------------------------------------------------------------------*/
//-- VCL --------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma argsused
#include "FrameWorkInterface.h"
#include "StartUp.h"
#include "fMessage.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
//---------------------------------------------------------------------------
//
// All the following functions are used as Pass Through functions to the RWFramwork set of functions.
//
// They perform no logic, other than just the simple check on the fShell pointer.
//
// The HRESULT is done across lines so as to help with debugging requirements.
//  The hResult is assigned a known state.
//  The hResult is assigned the pass through functions return value.
//  And the hResult returned to the caller.
//
//---------------------------------------------------------------------------
// GENERAL FUNCTIONS
//---------------------------------------------------------------------------
HRESULT WINAPI PostNotifyEvent(TZX_HPLUGIN PluginHandle, TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg)
{
    HRESULT hResult = E_FAIL;
    hResult = g_PluginManager.Notify(PluginHandle, Event, lpData, Param, Arg);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI AddPage(TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Name)
{
    HRESULT hResult = S_OK;
    hResult = g_GuiManager.AddTab(PluginHandle, VCLParent, Name);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI RemovePage(TZX_HPLUGIN PluginHandle, HWND Handle)
{
    HRESULT hResult = S_OK;
    hResult = g_GuiManager.RemoveTab(PluginHandle, Handle);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI SetPageBitmap(TZX_HPLUGIN PluginHandle, HWND Handle, TImage* SmallImage, TImage* LargeImage)
{
    HRESULT hResult = S_OK;
    hResult = g_GuiManager.SetTabBitmap(PluginHandle, Handle, SmallImage, LargeImage);
    return hResult;
}
//---------------------------------------------------------------------------
FUNCTION_PREFIX Message(ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3, int& iAnswer)
{
    HRESULT hResult = S_OK;
    iAnswer = g_GuiManager.ShowMessage(eType, sTitle, sBrief, sDetails, sButton1, sButton2, sButton3);
    return hResult;
}
//---------------------------------------------------------------------------
FUNCTION_PREFIX SetStatusSlot( TZX_HPLUGIN PluginHandle, const String& sText, unsigned int iSlot )
{
    HRESULT hResult = S_OK;
    hResult = g_GuiManager.SetStatusSlot(PluginHandle, sText, iSlot);
    return hResult;
}
//---------------------------------------------------------------------------
// EVENT REGISTRATION FUNCTIONS
//---------------------------------------------------------------------------
FUNCTION_PREFIX RegisterPluginEvent(TZX_HPLUGIN PluginHandle, TZX_EVENT Event)
{
    HRESULT hResult = S_OK;
    hResult = g_PluginManager.RegisterPluginEvent(PluginHandle, Event);
    return hResult;
}
//---------------------------------------------------------------------------
FUNCTION_PREFIX UnRegisterPluginEvent(TZX_HPLUGIN PluginHandle, TZX_EVENT Event)
{
    HRESULT hResult = S_OK;
    hResult = g_PluginManager.UnRegisterPluginEvent(PluginHandle, Event);
    return hResult;
}
//---------------------------------------------------------------------------
FUNCTION_PREFIX AddOptionsPage(TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Name)
{
    HRESULT hResult = S_OK;
    hResult = g_GuiManager.AddOptionsTab(PluginHandle, VCLParent, Name);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI AddPluginIcon(TZX_HPLUGIN PluginHandle, TImage* Icon, const String& sDescription)
{
    g_GuiManager.AddPluginIcon(PluginHandle, Icon, sDescription);
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI RemovePluginIcon(TZX_HPLUGIN PluginHandle)
{
    g_GuiManager.RemovePluginIcon(PluginHandle);
    return S_OK;
}
//---------------------------------------------------------------------------
FUNCTION_PREFIX IsActivePlugin(TZX_HPLUGIN PluginHandle)
{
    return g_GuiManager.IsActivePlugin(PluginHandle);
}
//---------------------------------------------------------------------------
FUNCTION_PREFIX GetXmlInfo(KXmlInfo*& xmlInfo)
{
    xmlInfo = g_ProjectManager.GetXmlInfo();
    return S_OK;
}
//---------------------------------------------------------------------------
FUNCTION_PREFIX GetXmlVersion(DWORD &dwVersion)
{
    dwVersion = g_ProjectManager.ProjectVersion;
    return S_OK;
}
//---------------------------------------------------------------------------
FUNCTION_PREFIX AddMenu(const String& sCaption, TMenuItem*& pMenu)
{
    return g_GuiManager.AddMenu(sCaption, pMenu);
}
//---------------------------------------------------------------------------

