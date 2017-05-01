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
using namespace ImageImport;
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
ZXImageImport* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXImageImport();
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
__fastcall ZXImageImport::ZXImageImport()
{
    RL_METHOD
    frmImageImport = new TfrmImageImport(NULL);
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
__fastcall ZXImageImport::~ZXImageImport()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmImageImport);
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
HRESULT __fastcall ZXImageImport::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    // use the hInstanceParent to get the Parent Interfaces using GetProcAddress
    // if the interfaces do not exist then fail the Initialization
    // if it passes then
    //   TODO: create the paint tool buttons
    //   and add them the parent plugin
    if (true == SAFE_PTR(frmImageImport))
    {
        hResult = frmImageImport->Initialize(pPlugin->Handle, pPlugin->ParentInstance);
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
HRESULT __fastcall ZXImageImport::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmImageImport))
    {
        hResult = frmImageImport->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageImport::RegisterEvents(void)
{
    RegisterEvent(IMAGE_EDITOR_IMAGE_CHANGED    , EventImageChanged );
    RegisterEvent(TZXN_XML_POST_LOAD            , EventXmlPostLoad  );
    RegisterEvent(TZXN_XML_PRE_SAVE             , EventXmlPreSave   );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageImport::EventImageChanged(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmImageImport))
    {
        //frmImageImport->UpdatePreview();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageImport::EventXmlPostLoad(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmImageImport))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            //frmImageImport->RefreshList();
            //frmImageImport->UpdatePreview();
        }
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageImport::EventXmlPreSave(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmImageImport))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
        }
    }
    return S_OK;
}
//---------------------------------------------------------------------------

