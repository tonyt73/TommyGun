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
//---------------------------------------------------------------------------
const String    g_sSignature    = "Memory";
const DWORD     g_dwVersion     = 0x00000100;   // 0.0.1.0
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from MemoryEditor.cpp to create a new Plugin object. The MemoryEditor.cpp only uses the
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
    return new ZXMemoryEditor();
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
__fastcall ZXMemoryEditor::ZXMemoryEditor()
: m_bDirty(false)
{
    RL_METHOD
    // create the vcl form the plugin uses
    frmMemoryEditor = new TfrmMemoryEditor(NULL);
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
__fastcall ZXMemoryEditor::~ZXMemoryEditor()
{
    RL_METHOD
    // release our resources before dying
    Release();
    // destroy the vcl form the plugin used
    SAFE_DELETE(frmMemoryEditor);
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
HRESULT __fastcall ZXMemoryEditor::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = S_FALSE;
    if (true == SAFE_PTR(frmMemoryEditor))
    {
        hResult = frmMemoryEditor->Initialise(pPlugin->Handle);
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
HRESULT __fastcall ZXMemoryEditor::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmMemoryEditor))
    {
        hResult = frmMemoryEditor->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXMemoryEditor::RegisterEvents(void)
{
    RegisterEvent(TZX_QUERY_DATASAVED                   , EventSaveQuery);
    RegisterEvent(TZX_VERB_NEW                          , EventNew      );
    RegisterEvent(TZX_VERB_LOAD                         , EventLoad     );
    RegisterEvent(TZXN_XML_PRE_SAVE                     , EventSave     );
    RegisterEvent(TZXN_XML_POST_LOAD                    , EventLoad     );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMemoryEditor::EventSaveQuery(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    //TODO: Save Query
    /*ZXMemoryEditor* _this = dynamic_cast<ZXMemoryEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        bool* bNeedToSave = (bool*)lpData;
        *bNeedToSave |= _this->m_bDirty;
    }*/
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMemoryEditor::EventNew(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    //TODO: Clear data
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMemoryEditor::EventLoad(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    HRESULT hResult = S_FALSE;
    ZXMemoryEditor* _this = dynamic_cast<ZXMemoryEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        /* TODO: XML ME!
        ZXFile zxFile((FILE*)lpData);
        ZXFileHeader Header;
        if (zxFile.ReadHeader(Header))
        {
            if (g_dwSignature == Header.dwSignature && g_dwVersion == Header.dwVersion)
            {
                String sMessage;
                if (zxFile.ReadString(sMessage))
                {
                    _this->m_bDirty = false;
                    hResult = S_OK;
                }
            }
        }*/
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMemoryEditor::EventSave(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    HRESULT hResult = S_FALSE;
    ZXMemoryEditor* _this = dynamic_cast<ZXMemoryEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        /* TODO: XML ME!
        ZXFile zxFile((FILE*)lpData);
        ZXFileHeader Header;
        Header.dwSignature = g_dwSignature;
        Header.dwVersion   = g_dwVersion;
        if (zxFile.WriteHeader(Header))
        {
            String sHello = "Hello from the Memory editor";
            if (zxFile.WriteString(sHello))
            {
                hResult = S_OK;
                _this->m_bDirty = false;
            }
        }*/
    }
    return hResult;
}
//---------------------------------------------------------------------------
