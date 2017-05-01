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
using namespace Scorpio;
using namespace ImageTypes;
using namespace Interface;
using namespace Plugin;
//---------------------------------------------------------------------------
const String    g_sSignature    = "UDG";
const DWORD     g_dwVersion     = 0x00000100;   // 0.0.1.0
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from ImageEditor.cpp to create a new Plugin object. The ImageEditor.cpp only uses the
 * Base class reference. So this function returns a Plugin object to use of type class ZXBasePlugin.
 * @return  ZXBasePlugin a ZXBasePlugin compatible object
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
ZXUDGType* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXUDGType();
}
//---------------------------------------------------------------------------
// Constructor
/**
 * Allocates resource for use by the Plugin class
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
__fastcall ZXUDGType::ZXUDGType()
{
    RL_METHOD
    frmUDGType = new TfrmUDGType(NULL);
}
//---------------------------------------------------------------------------
// Destructor
/**
 * Frees the resources of the Plugin class
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
__fastcall ZXUDGType::~ZXUDGType()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmUDGType);
    Release();
}
//---------------------------------------------------------------------------
// InitialisePlugin
/**
 * Initialises the plugin for use
 * @param   PluginHandle the handle allocated to the plugin
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXUDGType::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    // use the hInstanceParent to get the Parent Interfaces using GetProcAddress
    // if the interfaces do not exist then fail the Initialization
    // if it passes then
    //   TODO: create the paint tool buttons
    //   and add them the parent plugin
    if (true == SAFE_PTR(frmUDGType))
    {
        hResult = frmUDGType->Initialize(pPlugin->Handle, pPlugin->ParentInstance);
    }
    return hResult;
}
//---------------------------------------------------------------------------
// ReleasePlugin
/**
 * Releases the resources associated with the Plugin
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXUDGType::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmUDGType))
    {
        hResult = frmUDGType->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXUDGType::RegisterEvents(void)
{
    RegisterEvent(IMAGE_EDITOR_IMAGE_CHANGED    , EventImageChanged     );
    RegisterEvent(IMAGE_EDITOR_REFRESH_LIST     , EventImageListRefresh );
    RegisterEvent(TZXN_XML_POST_LOAD            , EventImageListRefresh );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXUDGType::EventImageChanged(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmUDGType))
    {
        frmUDGType->UpdatePreview();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXUDGType::EventImageListRefresh(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmUDGType))
    {
        frmUDGType->RefreshList();
    }
    return S_OK;
}
//---------------------------------------------------------------------------

