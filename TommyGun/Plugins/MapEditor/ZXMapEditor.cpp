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
const String    g_sSignature    = "Map";
const DWORD     g_dwVersion     = 0x00000100;   // 0.0.1.0
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from MapEditor.cpp to create a new Plugin object. The MapEditor.cpp only uses the
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
    return new ZXMapEditor();
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
__fastcall ZXMapEditor::ZXMapEditor()
//: m_bDirty(true)
{
    RL_METHOD
    // create the vcl form the plugin uses
    frmMapEditor = new TfrmMapEditor(NULL);
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
__fastcall ZXMapEditor::~ZXMapEditor()
{
    RL_METHOD
    // release our resources before dying
    Release();
    // destroy the vcl form the plugin used
    SAFE_DELETE(frmMapEditor);
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
HRESULT __fastcall ZXMapEditor::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = S_FALSE;
    if (true == SAFE_PTR(frmMapEditor))
    {
        hResult = frmMapEditor->Initialise(pPlugin->Handle);
        //frmMapEditor->tabMapSprites->TabVisible = false;
        //frmMapEditor->tabMapObjects->TabVisible = false;
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
HRESULT __fastcall ZXMapEditor::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmMapEditor))
    {
        hResult = frmMapEditor->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXMapEditor::RegisterEvents(void)
{
    // standard events
    RegisterEvent(TZX_QUERY_DATASAVED                   , EventSaveQuery        );
    RegisterEvent(TZX_QUERY_COPYPASTE                   , EventEditQuery        );
    RegisterEvent(TZXN_XML_NEW                          , EventXmlNew           );
    RegisterEvent(TZXN_XML_POST_LOAD                    , EventXmlPostLoad      );
    RegisterEvent(TZXN_XML_PRE_SAVE                     , EventXmlPreSave       );
    RegisterEvent(TZXN_XML_UPDATE                       , EventXmlUpdate        );
    RegisterEvent(TZX_VERB_COPY                         , EventEditCopy         );
    RegisterEvent(TZX_VERB_CUT                          , EventEditCut          );
    RegisterEvent(TZX_VERB_PASTE                        , EventEditPaste        );
    RegisterEvent(TZX_VERB_DELETE                       , EventDelete           );
    // custom events
    RegisterEvent(TZXC_IMAGE_EDITOR_IMAGE_CHANGED       , EventImageChanged     );
    RegisterEvent(TZXC_IMAGE_EDITOR_IMAGE_RENAMED       , EventImageRenamed     );
    RegisterEvent(TZXN_XML_UNDO_RESTORE                 , EventXmlUndoRestore   );
    RegisterEvent(TZX_QUERY_KEY_PANEL                   , EventKeyPanel         );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventSaveQuery(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    //TODO: Save Query
    if (true == SAFE_PTR(frmMapEditor))
    {
        bool* bNeedToSave = (bool*)lpData;
        *bNeedToSave |= frmMapEditor->IsDirty();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventEditQuery(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    return S_QUERY_YES;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventXmlNew(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmMapEditor))
    {
        frmMapEditor->Clear();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventXmlPostLoad(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmMapEditor))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            hResult = frmMapEditor->Load(*xmlInfo) ? S_OK : S_FALSE;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventXmlPreSave(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmMapEditor))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            frmMapEditor->Save(*xmlInfo);
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventXmlUpdate(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmMapEditor))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            frmMapEditor->Save(*xmlInfo, false);
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventXmlUndoRestore(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmMapEditor) && true == SAFE_PTR(lpData))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            frmMapEditor->UndoRestore(xmlInfo);
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventImageChanged(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER)
    String sOwner(*((String*)dwParam));
    if (true == SAFE_PTR(frmMapEditor) && true == SAFE_PTR(lpData) && sOwner == "Tile")
    {
        if (2 == dwArg)
        {
            String sName(*((String*)lpData));
            frmMapEditor->TileRemove(sName);
        }
        else
        {
            frmMapEditor->ImageChanged = true;
        }
        hResult = S_OK;
    }
    else if (true == SAFE_PTR(frmMapEditor) && true == SAFE_PTR(lpData) && sOwner == "Sprite")
    {
        if (2 == dwArg)
        {
            String sName(*((String*)lpData));
            frmMapEditor->SpriteRemove(sName);
        }
        else
        {
            frmMapEditor->ImageChanged = true;
        }
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventImageRenamed(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER)
    String sOwner = *(String*)dwParam;
    if (true == SAFE_PTR(frmMapEditor) && true == SAFE_PTR(lpData) && sOwner == "Tile")
    {
        String sOldName(*((String*)lpData));
        String sNewName(*((String*)dwArg ));
        frmMapEditor->TileRename(sOldName, sNewName);
        hResult = S_OK;
    }
    else if (true == SAFE_PTR(frmMapEditor) && true == SAFE_PTR(lpData) && sOwner == "Sprite")
    {
        String sOldName(*((String*)lpData));
        String sNewName(*((String*)dwArg ));
        frmMapEditor->SpriteRename(sOldName, sNewName);
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventEditCopy(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (true == SAFE_PTR(frmMapEditor))
    {
        frmMapEditor->Copy();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventEditCut(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (true == SAFE_PTR(frmMapEditor))
    {
        frmMapEditor->Cut();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventEditPaste(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (true == SAFE_PTR(frmMapEditor))
    {
        frmMapEditor->Paste();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventDelete(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (true == SAFE_PTR(frmMapEditor))
    {
        frmMapEditor->Delete();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXMapEditor::EventKeyPanel(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(lpData))
    {
        *((TPanel**)lpData) = frmMapEditor->panMapKeysPanel;
        hResult = S_QUERY_YES;
    }
    return hResult;
}
//---------------------------------------------------------------------------
