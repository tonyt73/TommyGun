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
//- NAMESPACES --------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace Plugin;
using namespace Logging;
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Logging;
using namespace GameEditor;
//---------------------------------------------------------------------------
const String    g_sSignature    = "GameEditor";
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from GameEditor.cpp to create a new Plugin object. The GameEditor.cpp only uses the
 * Base class reference. So this function returns a Plugin object to use of type class ZXBasePlugin.
 * @return  ZXBasePlugin a ZXBasePlugin compatible object
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
ZXGameEditor* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXGameEditor();
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
__fastcall ZXGameEditor::ZXGameEditor()
{
    RL_METHOD
    Screen->Cursors[99] = LoadCursor(HInstance, "SELECT");
    // create the vcl form the plugin uses
    try
    {
        frmGameEditor = new TfrmGameEditor(NULL);
    }
    catch(...)
    {
        frmGameEditor = NULL;
    }
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
__fastcall ZXGameEditor::~ZXGameEditor()
{
    RL_METHOD
    // release our resources before dying
    Release();
    // destroy the vcl form the plugin used
    SAFE_DELETE(frmGameEditor);
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
HRESULT __fastcall ZXGameEditor::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_FAIL;
    if (true == SAFE_PTR(frmGameEditor))
    {
        hResult = frmGameEditor->Initialise(pPlugin->Handle);
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
HRESULT __fastcall ZXGameEditor::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmGameEditor))
    {
        hResult = frmGameEditor->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXGameEditor::RegisterEvents(void)
{
    // standard events
    RegisterEvent(TZX_QUERY_DATASAVED                   , EventSaveQuery        );
    // custom events
    RegisterEvent(TZXN_XML_NEW                          , EventXmlNew           );
    RegisterEvent(TZXN_XML_POST_LOAD                    , EventXmlPostLoad      );
    RegisterEvent(TZXN_XML_PRE_SAVE                     , EventXmlPreSave       );
    RegisterEvent(TZXN_XML_UPDATE                       , EventXmlUpdate        );
    RegisterEvent(TZXN_XML_UNDO_RESTORE                 , EventXmlUndoRestore   );
    RegisterEvent(TZX_QUERY_COPYPASTE                   , EventQueryEditFeatures);
    RegisterEvent(TZX_VERB_COPY                         , EventEditCopy         );
    RegisterEvent(TZX_VERB_CUT                          , EventEditCut          );
    RegisterEvent(TZX_VERB_PASTE                        , EventEditPaste        );
    RegisterEvent(TZX_VERB_DELETE                       , EventEditDelete       );
    RegisterEvent(TZX_QUERY_KEY_PANEL                   , EventKeyPanel         );
    RegisterEvent(TZXC_IMAGE_EDITOR_IMAGE_CHANGED       , EventImageChanged     );
    RegisterEvent(TZXC_IMAGE_EDITOR_IMAGE_RENAMED       , EventImageRenamed     );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventSaveQuery(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        bool* bNeedToSave = (bool*)lpData;
        *bNeedToSave |= frmGameEditor->IsDirty();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventXmlNew(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        frmGameEditor->New();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventXmlPostLoad(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            hResult = frmGameEditor->Load(*xmlInfo) ? S_OK : S_FALSE;
        }
        frmGameEditor->RefreshTiles();
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventXmlPreSave(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            frmGameEditor->Save(*xmlInfo);
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventXmlUpdate(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            frmGameEditor->Save(*xmlInfo);
            frmGameEditor->Update();
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventXmlUndoRestore(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            //_this->UndoRestore(xmlInfo);
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventImageChanged(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER)
    String sOwner(*((String*)dwParam));
    if (true == SAFE_PTR(frmGameEditor) && true == SAFE_PTR(lpData) && sOwner == "Tile")
    {
        frmGameEditor->Update();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventImageRenamed(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER)
    String sOwner = *(String*)dwParam;
    if (true == SAFE_PTR(frmGameEditor) && true == SAFE_PTR(lpData) && sOwner == "Tile")
    {
        frmGameEditor->Update();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventQueryEditFeatures(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    // we support finding, undo, redo and copy, cut and paste
    return S_FALSE;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventEditCopy(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        //frmGameEditor->EditCopy();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventEditCut(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        //frmGameEditor->EditCut();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventEditPaste(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        //frmGameEditor->EditPaste();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventEditDelete(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXGameEditor* _this = dynamic_cast<ZXGameEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        //frmGameEditor->EditCut();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXGameEditor::EventKeyPanel(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(lpData))
    {
        *((TPanel**)lpData) = frmGameEditor->panImageKeysPanel;
        hResult = S_QUERY_YES;
    }
    return hResult;
}
//---------------------------------------------------------------------------


