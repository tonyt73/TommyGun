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
ZXSpriteType* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXSpriteType();
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
__fastcall ZXSpriteType::ZXSpriteType()
{
    RL_METHOD
    frmSpriteType = new TfrmSpriteType(NULL);
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
__fastcall ZXSpriteType::~ZXSpriteType()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmSpriteType);
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
HRESULT __fastcall ZXSpriteType::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    // use the hInstanceParent to get the Parent Interfaces using GetProcAddress
    // if the interfaces do not exist then fail the Initialization
    // if it passes then
    if (true == SAFE_PTR(frmSpriteType))
    {
        hResult = frmSpriteType->Initialize(pPlugin->Handle, pPlugin->ParentInstance);
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
HRESULT __fastcall ZXSpriteType::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmSpriteType))
    {
        hResult = frmSpriteType->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpriteType::RegisterEvents(void)
{
    RegisterEvent(IMAGE_EDITOR_IMAGE_CHANGED    , EventImageChanged     );
    RegisterEvent(IMAGE_EDITOR_REFRESH_LIST     , EventImageListRefresh );
    RegisterEvent(IMAGE_EDITOR_IMAGE_SELECT     , EventImageSelect      );
    RegisterEvent(TZXN_XML_NEW                  , EventXmlNew           );
    RegisterEvent(TZXN_XML_POST_LOAD            , EventXmlPostLoad      );
    RegisterEvent(TZXN_XML_PRE_SAVE             , EventXmlPreSave       );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXSpriteType::EventImageChanged(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmSpriteType))
    {
        frmSpriteType->UpdatePreview();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXSpriteType::EventImageListRefresh(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmSpriteType))
    {
        frmSpriteType->RefreshList();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXSpriteType::EventImageSelect(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmSpriteType))
    {
        frmSpriteType->SelectFrame(Arg);
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXSpriteType::EventXmlNew(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmSpriteType))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            xmlInfo->Add("Sprites", "1.0");
        }
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXSpriteType::EventXmlPostLoad(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmSpriteType))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            frmSpriteType->RefreshList();
            frmSpriteType->UpdatePreview();
            frmSpriteType->UpdateButtons();
        }
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXSpriteType::EventXmlPreSave(ZXEventManager* EventManager, LPDATA lpData, DWORD Param, DWORD Arg)
{
    if (true == SAFE_PTR(frmSpriteType))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
        }
    }
    return S_OK;
}
//---------------------------------------------------------------------------

