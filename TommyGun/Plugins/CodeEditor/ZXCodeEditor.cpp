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
//---------------------------------------------------------------------------
const String    g_sSignature    = "CodeEditor";
//- MINI-PLUGIN MANAGER -----------------------------------------------------
ZXPluginManager g_MiniPluginManager(".cpi");
//- GLOBAL LOG FILE ---------------------------------------------------------
ZXLogFile g_LogFile;
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from CodeEditor.cpp to create a new Plugin object. The CodeEditor.cpp only uses the
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
    return new ZXCodeEditor();
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
__fastcall ZXCodeEditor::ZXCodeEditor()
: m_bDirty(true)
{
    RL_METHOD
    // create the vcl form the plugin uses
    frmCodeEditor       = new TfrmCodeEditor(Application, m_FileManager, m_ParserManager);
    frmBuildOptions     = new TfrmBuildOptions(Application);
    frmSearch           = new TfrmSearch(Application);
    frmReplace          = new TfrmReplace(Application);
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
__fastcall ZXCodeEditor::~ZXCodeEditor()
{
    RL_METHOD
    // release our resources before dying
    Release();
    // destroy the vcl form the plugin used
    SAFE_DELETE(frmReplace         );
    SAFE_DELETE(frmSearch          );
    SAFE_DELETE(frmBuildOptions    );
    SAFE_DELETE(frmCodeEditor      );
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
HRESULT __fastcall ZXCodeEditor::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_FAIL;
    if (true == SAFE_PTR(frmCodeEditor))
    {
        g_MiniPluginManager.Initialize(pPlugin->Handle);
        hResult = frmCodeEditor->Initialise(pPlugin->Handle);
        ZX_LOG_INFO(lfPlugin, "Loading CodeEditor Mini-Plugins")
        int iPluginsLoaded = g_MiniPluginManager.LoadPlugins(pPlugin->Handle, g_sSignature);
        if (0 < iPluginsLoaded)
        {
            OrganisePlugins();
            m_ParserManager.Initialize(&m_ParserPlugins);
        }
        ZX_LOG_INFO(lfPlugin, "Loaded " + IntToStr(iPluginsLoaded) + " CodeEditor Mini-Plugin(s)")
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
HRESULT __fastcall ZXCodeEditor::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    g_MiniPluginManager.UnloadPlugins();
    g_MiniPluginManager.Release();
    if (true == SAFE_PTR(frmCodeEditor))
    {
        hResult = frmCodeEditor->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXCodeEditor::RegisterEvents(void)
{
    RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery        );
    RegisterEvent(TZXN_XML_NEW          , EventXmlNew           );
    RegisterEvent(TZXN_XML_POST_LOAD    , EventXmlPostLoad      );
    RegisterEvent(TZXN_XML_PRE_SAVE     , EventXmlPreSave       );
    RegisterEvent(TZXN_XML_UPDATE       , EventXmlUpdate        );
    RegisterEvent(TZX_QUERY_COPYPASTE   , EventQueryEditFeatures);
    RegisterEvent(TZX_QUERY_FIND        , EventQueryEditFeatures);
    RegisterEvent(TZX_VERB_COPY         , EventEditCopy         );
    RegisterEvent(TZX_VERB_CUT          , EventEditCut          );
    RegisterEvent(TZX_VERB_PASTE        , EventEditPaste        );
    //RegisterEvent(TZX_QUERY_UNDO        , EventQueryEditFeatures);
    //RegisterEvent(TZX_QUERY_REDO        , EventQueryEditFeatures);
    RegisterEvent(TZXN_EDIT_FIND        , EventFind             );
    RegisterEvent(TZXN_EDIT_FIND_REPLACE, EventFindReplace      );
    RegisterEvent(TZXN_EDIT_FIND_NEXT   , EventFindNext         );
    RegisterEvent(TZXN_EDIT_FIND_PREV   , EventFindPrevious     );
    RegisterEvent(TZX_VERB_DELETE       , EventDelete           );
    RegisterEvent(TZX_QUERY_KEY_PANEL   , EventKeyPanel         );
    RegisterEvent(TZXN_GAME_PLAY        , EventPlayGame         );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventDelete(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (true == SAFE_PTR(frmCodeEditor))
    {
        frmCodeEditor->DeleteKey();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventEditCopy(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (true == SAFE_PTR(frmCodeEditor))
    {
        frmCodeEditor->EditCopy();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventEditCut(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (true == SAFE_PTR(frmCodeEditor))
    {
        frmCodeEditor->EditCut();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventEditPaste(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (true == SAFE_PTR(frmCodeEditor))
    {
        frmCodeEditor->EditPaste();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventSaveQuery(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    //TODO: Save Query
    ZXCodeEditor* _this = dynamic_cast<ZXCodeEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        bool* bNeedToSave = (bool*)lpData;
        *bNeedToSave |= frmCodeEditor->IsDirty;
        *bNeedToSave |= _this->m_FileManager.IsDirty;
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventXmlNew(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    frmCodeEditor->Clear();
    ZXCodeEditor* _this = dynamic_cast<ZXCodeEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        _this->m_FileManager.Clear();
        frmCodeEditor->Clear();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventXmlPostLoad(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_FAIL);
    ZXCodeEditor* _this = dynamic_cast<ZXCodeEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            // remove the old code editor node
            KXmlInfo* node;
            if (xmlInfo->Find(node, "CodeEditor", 0))
            {
                hResult |= _this->m_FileManager.Load(*node);
                hResult  = frmCodeEditor->Load(*node);
                //_this->NotifyPluginEvent(NULL, TZXN_XML_POST_LOAD, (LPDATA)node, dwParam, dwArg);
            }
        }
        frmCodeEditor->UpdateEditor();
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventXmlPreSave(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_FAIL);
    ZXCodeEditor* _this = dynamic_cast<ZXCodeEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            // remove the old code editor node
            KXmlInfo* node;
            if (xmlInfo->Find(node, "CodeEditor", 0))
            {
                xmlInfo->Remove(node);
            }
            // create a new code editor node
            KXmlInfo CodeEditor("CodeEditor");
            hResult  = frmCodeEditor->Save(CodeEditor);
            // TODO: implement xml parser mini-plugins
            //_this->NotifyPluginEvent(NULL, TZXN_XML_POST_LOAD, (LPDATA)&CodeEditor, dwParam, dwArg);
            xmlInfo->Add(CodeEditor);
            frmCodeEditor->UpdateEditorSlots();
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventXmlUpdate(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_FAIL);
    ZXCodeEditor* _this = dynamic_cast<ZXCodeEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            // remove the old code editor node
            KXmlInfo* node;
            if (xmlInfo->Find(node, "CodeEditor", 0))
            {
                xmlInfo->Remove(node);
            }
            // create a new code editor node
            KXmlInfo CodeEditor("CodeEditor");
            hResult  = frmCodeEditor->Save(CodeEditor, false);
            // TODO: implement xml parser mini-plugins
            //_this->NotifyPluginEvent(NULL, TZXN_XML_POST_LOAD, (LPDATA)&CodeEditor, dwParam, dwArg);
            xmlInfo->Add(CodeEditor);
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventQueryEditFeatures(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    // we support finding, undo, redo and copy, cut and paste
    return S_QUERY_YES;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventFind(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    frmCodeEditor->actFindExecute(NULL);
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventFindReplace(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    frmCodeEditor->actReplaceExecute(NULL);
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventFindNext(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    frmCodeEditor->actFindForwardExecute(NULL);
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventFindPrevious(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    frmCodeEditor->actFindBackwardExecute(NULL);
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventKeyPanel(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(lpData))
    {
        *((TPanel**)lpData) = frmCodeEditor->panCodeKeysPanel;
        hResult = S_QUERY_YES;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXCodeEditor::EventPlayGame(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (frmCodeEditor->tbnBuildRun->Down)
        frmCodeEditor->actBuildRunExecute(NULL);
    else
        frmCodeEditor->actDebugRunExecute(NULL);
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall ZXCodeEditor::GetParserInterfaces(ZXPlugin* Plugin)
{
    ZXParserPluginInfo* PPi = new ZXParserPluginInfo();
    if (true == SAFE_PTR(PPi))
    {
        PPi->pPlugin  = Plugin;
        int iInterfaces = 0;
        PPi->pGetOptionsPanelFunc = reinterpret_cast<GetOptionsPanelPtr>(GetProcAddress(Plugin->Handle, "GetOptionsPanel"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(PPi->pGetOptionsPanelFunc))) ? 1 : 0;
        PPi->pGetResourceTypesFunc = reinterpret_cast<GetResourceTypesPtr>(GetProcAddress(Plugin->Handle, "GetResourceTypes"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(PPi->pGetResourceTypesFunc))) ? 1 : 0;
        PPi->pGetResourcesListFunc = reinterpret_cast<GetResourcesListPtr>(GetProcAddress(Plugin->Handle, "GetListOfResources"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(PPi->pGetResourcesListFunc))) ? 1 : 0;
        PPi->pParseResourceFunc = reinterpret_cast<ParseResourcesPtr>(GetProcAddress(Plugin->Handle, "ParseResources"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(PPi->pParseResourceFunc))) ? 1 : 0;
        PPi->pDescriptionFunc = reinterpret_cast<GetDescriptionPtr>(GetProcAddress(Plugin->Handle, "GetDescription"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(PPi->pDescriptionFunc))) ? 1 : 0;
        if (5 == iInterfaces)
        {
            ZX_LOG_INFO(lfPlugin, "Found all 5 required Code Parser Plugin interfaces");
            m_ParserPlugins.push_back(PPi);
        }
        else
        {
            ZX_LOG_ERROR(lfPlugin, "Failed to find all 5 required Code Parser Interfaces from mini-plugin + " + Plugin->Description);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXCodeEditor::OrganisePlugins(void)
{
    m_ParserPlugins.clear();
    m_ToolPlugins.clear();
    ZXPlugin* Plugin = g_MiniPluginManager.GetFirstPlugin();
    while (true == SAFE_PTR(Plugin))
    {
        String sDescription = Plugin->Description;
        if (0 != sDescription.Pos("Parser Plugin"))
        {
            GetParserInterfaces(Plugin);
        }
        else if (0 != sDescription.Pos("Tool Plugin"))
        {
            //GetToolInterfaces(Plugin);
        }
        else
        {
            ZX_LOG_ERROR(lfPlugin, "Invalid Code Editor plugin [" + sDescription + "]");
        }
        Plugin = g_MiniPluginManager.GetNextPlugin();
    };
    //GetParserDescriptions();
    //AssignPalettes();
}
//---------------------------------------------------------------------------
