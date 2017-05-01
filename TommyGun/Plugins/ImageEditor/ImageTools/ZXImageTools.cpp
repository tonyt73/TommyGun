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
using namespace ImageTools;
using namespace Interface;
using namespace Plugin;
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
ZXImageTools* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXImageTools();
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
__fastcall ZXImageTools::ZXImageTools()
{
    RL_METHOD
    frmImageTools = new TfrmImageTools(NULL);
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
__fastcall ZXImageTools::~ZXImageTools()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmImageTools);
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
HRESULT __fastcall ZXImageTools::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    // use the hInstanceParent to get the Parent Interfaces using GetProcAddress
    // if the interfaces do not exist then fail the Initialization
    // if it passes then
    //   TODO: create the paint tool buttons
    //   and add them the parent plugin
    if (true == SAFE_PTR(frmImageTools))
    {
        hResult = frmImageTools->Initialize(pPlugin->Handle, pPlugin->ParentInstance);
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
HRESULT __fastcall ZXImageTools::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmImageTools))
    {
        hResult = frmImageTools->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageTools::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageTools::MouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    RL_METHOD
    return E_FAIL;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageTools::MouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    RL_METHOD
    return E_FAIL;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageTools::MouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    RL_METHOD
    return E_FAIL;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageTools::Cursor(TCursor& Cursor)
{
    RL_METHOD
    return E_FAIL;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageTools::ImageChange(ZXImage* Image)
{
    RL_METHOD
    return S_OK;
}
//---------------------------------------------------------------------------

