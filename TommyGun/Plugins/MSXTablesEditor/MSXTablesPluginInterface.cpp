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
 The KiwiWare Plugin Interface Implementation
 There is no need to modify this file.
---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
//-- PLUGIN -----------------------------------------------------------------
ZXBasePlugin* g_Plugin = NULL;
// Plugin Class Factory function
extern ZXBasePlugin* NewPluginClass(void);
//-- PLUGIN FLAG INFORMATION ------------------------------------------------
DWORD  g_dwFlags = 0x0000;
//---------------------------------------------------------------------------
// Flags
/**
 * Returns the Interface Version the plugin adheres to.
 * @param   version returns the version number
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT WINAPI Flags(DWORD& dwFlags)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    // see. Interface.h for possible flag values
    dwFlags = g_dwFlags;
    return hResult;
}
//---------------------------------------------------------------------------
// Initialise
/**
 * Initialises the plugin for use
 * @param   PluginHandle the handle allocated to the plugin
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT WINAPI Initialise(ZXPlugin* pPlugin)
{
    RL_METHOD
    RL_HRESULT(S_FALSE)
    // check plugin is uninitialized
    if (false == SAFE_PTR(g_Plugin))
    {
        // create a new plugin
        g_Plugin = NewPluginClass();
    }
    // check plugin object was created correct
    if (true == SAFE_PTR(g_Plugin))
    {
        // plugin is valid, intialise it
        hResult = g_Plugin->Initialise(pPlugin);
    }
    return hResult;
}
//---------------------------------------------------------------------------
// Notify
/**
 * Message pump for the plugin
 * @param   Event the event that occurred
 * @param   Data  depends on the event
 * @param   Param depends on the event
 * @param   Arg   depends on the event
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT WINAPI Notify(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(g_Plugin))
    {
        hResult = g_Plugin->ProcessEvent(Event, lpData, Param, Arg);
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
HRESULT WINAPI Release(void)
{
    RL_METHOD
    // default: resources are released OK
    RL_HRESULT(S_OK)
    // check the form pointer is valid
    if (true == SAFE_PTR(g_Plugin))
    {
        // release the forms resources
        hResult = g_Plugin->Release();
        // delete the form
        SAFE_DELETE(g_Plugin);
    }

    // return the result of the resource release
    return hResult;
}
//---------------------------------------------------------------------------
