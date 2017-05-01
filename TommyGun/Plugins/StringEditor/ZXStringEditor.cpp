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
const String    g_sSignature    = "String";
const DWORD     g_dwVersion     = 0x00000100;   // 0.0.1.0
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from StringEditor.cpp to create a new Plugin object. The StringEditor.cpp only uses the
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
    return new ZXStringEditor();
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
__fastcall ZXStringEditor::ZXStringEditor()
: m_bDirty(false)
{
    RL_METHOD
    // create the vcl form the plugin uses
    frmStringEditor = new TfrmStringEditor(NULL);
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
__fastcall ZXStringEditor::~ZXStringEditor()
{
    RL_METHOD
    // release our resources before dying
    Release();
    // destroy the vcl form the plugin used
    SAFE_DELETE(frmStringEditor);
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
HRESULT __fastcall ZXStringEditor::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = S_FALSE;
    if (true == SAFE_PTR(frmStringEditor))
    {
        hResult = frmStringEditor->Initialise(pPlugin->Handle);
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
HRESULT __fastcall ZXStringEditor::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmStringEditor))
    {
        hResult = frmStringEditor->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXStringEditor::RegisterEvents(void)
{
    RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery);
    RegisterEvent(TZX_VERB_NEW          , EventNew      );
    RegisterEvent(TZX_VERB_LOAD         , EventLoad     );
    RegisterEvent(TZXN_XML_PRE_SAVE     , EventSave     );
    RegisterEvent(TZXN_XML_POST_LOAD    , EventLoad     );
    RegisterEvent(TZXN_XML_UPDATE       , EventXmlUpdate);
    RegisterEvent(TZX_QUERY_KEY_PANEL   , EventKeyPanel );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXStringEditor::EventSaveQuery(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (true == SAFE_PTR(lpData))
    {
        bool* bNeedToSave = (bool*)lpData;
        *bNeedToSave |= frmStringEditor->IsDirty();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXStringEditor::EventNew(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    frmStringEditor->Clear();
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXStringEditor::EventLoad(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    HRESULT hResult = S_FALSE;
    if (true == SAFE_PTR(lpData))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            hResult = frmStringEditor->Load(xmlInfo) ? S_OK : S_FALSE;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXStringEditor::EventSave(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    HRESULT hResult = S_FALSE;
    if (true == SAFE_PTR(lpData))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            hResult = frmStringEditor->Save(xmlInfo) ? S_OK : S_FALSE;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXStringEditor::EventXmlUpdate(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmStringEditor))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            frmStringEditor->Save(xmlInfo);
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXStringEditor::EventKeyPanel(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(lpData))
    {
        *((TPanel**)lpData) = frmStringEditor->panCodeKeysPanel;
        hResult = S_QUERY_YES;
    }
    return hResult;
}
//---------------------------------------------------------------------------
