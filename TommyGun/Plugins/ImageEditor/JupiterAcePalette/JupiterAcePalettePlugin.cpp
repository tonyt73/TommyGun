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
RL_MESSAGE_LOGGER_OBJECT
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace Plugin;
using namespace Logging;
//- GLOBAL LOG FILE ---------------------------------------------------------
ZXLogFile g_LogFile;
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace JupiterAcePalette;
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
JupiterAcePalettePlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new JupiterAcePalettePlugin();
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
__fastcall JupiterAcePalettePlugin::JupiterAcePalettePlugin()
{
    RL_METHOD
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
__fastcall JupiterAcePalettePlugin::~JupiterAcePalettePlugin()
{
    RL_METHOD
    // release our resources before dying
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
HRESULT __fastcall JupiterAcePalettePlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = S_OK;
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
HRESULT __fastcall JupiterAcePalettePlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall JupiterAcePalettePlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall JupiterAcePalettePlugin::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall JupiterAcePalettePlugin::GetPalettePanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Panel = NULL;
    return hResult;
}
//---------------------------------------------------------------------------

