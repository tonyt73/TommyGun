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
using namespace Interface;
using namespace Plugin;
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace MSXPalette;
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
MSXSpritePalettePlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new MSXSpritePalettePlugin();
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
__fastcall MSXSpritePalettePlugin::MSXSpritePalettePlugin()
{
    RL_METHOD
    frmMSXSpritePalette = new TfrmMSXSpritePalette(NULL);
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
__fastcall MSXSpritePalettePlugin::~MSXSpritePalettePlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmMSXSpritePalette);
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
HRESULT __fastcall MSXSpritePalettePlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = S_OK;
    if (true == SAFE_PTR(frmMSXSpritePalette))
    {
        hResult = frmMSXSpritePalette->Initialize(pPlugin->Handle, pPlugin->ParentInstance);
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
HRESULT __fastcall MSXSpritePalettePlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmMSXSpritePalette))
    {
        hResult = frmMSXSpritePalette->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall MSXSpritePalettePlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall MSXSpritePalettePlugin::GetPalette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmMSXSpritePalette))
    {
        hResult = frmMSXSpritePalette->GetPalette(Palette);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall MSXSpritePalettePlugin::GetPalettePanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmMSXSpritePalette))
    {
        Panel = frmMSXSpritePalette->panPalette;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------

