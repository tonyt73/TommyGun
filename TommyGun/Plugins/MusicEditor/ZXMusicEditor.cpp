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
//using namespace Logging;
//using namespace FileSystem;
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from Skeleton.cpp to create a new Plugin object. The Skeleton.cpp only uses the
 * Base class reference. So this function returns a Plugin object to use of type class ZXBasePlugin.
 * @return  ZXBasePlugin a ZXBasePlugin compatible object
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
ZXBasePlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXMusicEditor();
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
__fastcall ZXMusicEditor::ZXMusicEditor()
: m_bDirty(true)
{
    RL_METHOD
    // create the vcl form the plugin uses
    frmMusicEditor = new TfrmMusicEditor(NULL);
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
__fastcall ZXMusicEditor::~ZXMusicEditor()
{
    RL_METHOD
    // release our resources before dying
    Release();
    // destroy the vcl form the plugin used
    SAFE_DELETE(frmMusicEditor);
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
HRESULT __fastcall ZXMusicEditor::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_FAIL;
    if (true == SAFE_PTR(frmMusicEditor))
    {
        hResult = frmMusicEditor->Initialise(pPlugin->Handle);
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
HRESULT __fastcall ZXMusicEditor::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmMusicEditor))
    {
        hResult = frmMusicEditor->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXMusicEditor::RegisterEvents(void)
{
    RegisterEvent(TZX_QUERY_DATASAVED                   , EventSaveQuery        );
    RegisterEvent(TZX_VERB_NEW                          , EventNew              );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMusicEditor::EventSaveQuery(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    //TODO: Save Query
    /*ZXMusicEditor* _this = dynamic_cast<ZXMusicEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        bool* bNeedToSave = (bool*)lpData;
        *bNeedToSave |= _this->m_bDirty;
    } */
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMusicEditor::EventNew(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    //TODO: Clear data
    return S_OK;
}
//---------------------------------------------------------------------------
