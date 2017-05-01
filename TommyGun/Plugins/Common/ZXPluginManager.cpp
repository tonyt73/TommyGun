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
#ifdef BUILDING_CORE
#include "core_pch.h"
#else
#include "pch.h"
#endif
#pragma hdrstop
//---------------------------------------------------------------------------
const String      g_sPluginsDirectory            = "Plugins";
const String      g_sSetPathError                = "Set Path Environment Error";
const String      g_sSetPathErrorMsg             = "Failed to add the Plugins directory to the PATH environment variable";
const int         g_iPathAddedSuccessfully       = 0;
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Plugin;
using namespace Logging;
//---------------------------------------------------------------------------
bool __fastcall PluginLessThan(ZXPlugin* left, ZXPlugin* right)
{
    DWORD dwPriority1 = left->Flags & FLAG_PluginLoadPriorityMask;
    DWORD dwPriority2 = right->Flags & FLAG_PluginLoadPriorityMask;
    if (dwPriority1 == dwPriority2)
    {
        return (left->LoadOrder < right->LoadOrder);
    }
    else
    {
        return (dwPriority1 > dwPriority2);
    }
}
//---------------------------------------------------------------------------
#ifdef USE_GUI_MANAGER
__fastcall ZXPluginManager::ZXPluginManager(ZXGUIManager* pGuiManager, const String& sPluginExtension)
: m_pGuiManager(pGuiManager)
#else
__fastcall ZXPluginManager::ZXPluginManager(const String& sPluginExtension)
: m_pGuiManager(NULL)
#endif
, FOnQuerySave(NULL)
, FOnQueryProjectFolder(NULL)
, m_ActivePlugin(NULL)
, m_hInst_PSAPI(NULL)
, m_bLoading(false)
, m_PluginsLoaded(0)
, m_iPluginGetNextIndex(0)
, m_sPluginExtension(sPluginExtension)
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXPluginManager::Initialize(HINSTANCE hInstance)
{
    m_Handle = hInstance;
    ZX_LOG_INFO(lfGeneral, "Initialized Plugin Manager")
    return true;
}
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::Release(void)
{
    ZX_LOG_INFO(lfGeneral, "Releasing Plugin Manager")
    UnloadPlugins();
    if (NULL != m_hInst_PSAPI)
    {
        if(FreeLibrary(m_hInst_PSAPI))
        {
            ZX_LOG_INFO(lfWindowsAPI, "Freed the PSAPI dll")
        }
        else
        {
            ZX_LOG_ERROR(lfWindowsAPI, "Failed to free the PSAPI dll")
        }
    }
}
//---------------------------------------------------------------------------
// LoadPlugins
/**
 * Loads all available plugins in order
 * @return          Number of plugins successfully loaded.
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 * @date            Last Modified 10 March 2003 - Add splash screen registry settings
 * @date            Last Modified 22 September 2003 - Simplified the code
 */
//---------------------------------------------------------------------------
#ifdef USE_GUI_MANAGER
int __fastcall ZXPluginManager::LoadPlugins(void)
{
    ZX_LOG_INFO(lfGeneral, "Loading plugins")
    DWORD dwStartTime = timeGetTime();
    // no events are to be processed while loading is in progress
    m_bLoading = true;
    // add plugins directory to path
    AddPluginsDirectoryToPath();
    // try to load the Window Process Helper dll
    LoadPSAPI();
    // search for the plugin files
    LocatePlugins();
    // order the plugin files with regard to the registry settings
    OrderPlugins();
    // load them in their load order
    LoadPluginsInOrder();
    // remove the plugins that failed to load
    RemoveUnloadedPlugins();
    // reorder the successfulled loaded plugins
    ReorderLoadedPlugins();
    // remove the do not load plugins
    RemoveDoNotLoadPlugins();
    m_bLoading = false;
    DWORD dwLoadTime = timeGetTime() - dwStartTime;
    ZX_LOG_INFO(lfPlugin, "Plugins took " + IntToStr(dwLoadTime) + "ms to load")
    ZX_LOG_INFO(lfGeneral, "Plugins took " + IntToStr(dwLoadTime) + "ms to load")
    // return the number of plugins loaded
    m_PluginsLoaded = m_Plugins.size();
    return m_PluginsLoaded;
}
#else
//---------------------------------------------------------------------------
// LoadPlugins
/**
 * Loads all available plugins in order
 * @return          Number of plugins successfully loaded.
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 * @date            Last Modified 10 March 2003 - Add splash screen registry settings
 * @date            Last Modified 22 September 2003 - Simplified the code
 */
//---------------------------------------------------------------------------
int __fastcall ZXPluginManager::LoadPlugins(HINSTANCE hParentInstance, const String& sSignature)
{
    DWORD dwStartTime = timeGetTime();
    // no events are to be processed while loading is in progress
    m_bLoading = true;
    // try to load the Window Process Helper dll
    LoadPSAPI();
    // search for the plugin files
    LocatePlugins();
    // load the ones we found
    LoadPluginsFound(hParentInstance, sSignature);
    // remove the plugins that failed to load
    RemoveUnloadedPlugins();
    // finished loading, events can be processed
    m_bLoading = false;
    DWORD dwUnloadTime = timeGetTime() - dwStartTime;
    ZX_LOG_INFO(lfPlugin, "Plugins took " + IntToStr(dwUnloadTime) + "ms to load")
    // return the number of plugins loaded
    return m_Plugins.size();
}
//---------------------------------------------------------------------------
// LoadPluginsFound
/**
 * Loads all the plugins in their load order
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::LoadPluginsFound(HINSTANCE hParentInstance, const String& sSignature)
{
    // load the plugins
    ZXPluginsIterator PluginIt = m_Plugins.begin();
    while(PluginIt != m_Plugins.end())
    {
        (*PluginIt)->ParentInstance  = hParentInstance;
        (*PluginIt)->ParentSignature = sSignature;
        (*PluginIt)->Load(m_GetModuleInformation);
        PluginIt++;
    }
}
#endif
//---------------------------------------------------------------------------
// InitiatePlugins
/**
 * Initiates the resources of all loaded plugins
 * @author          Tony Thompson
 * @date            Last Modified 22 September 2003 - Extracted form LoadPlugins
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::InitiatePlugins(void)
{
    // notify all plugins we are activated
    Notify(NULL, TZXN_ACTIVATE, NULL, 0, 0);
}
//---------------------------------------------------------------------------
// UnloadPlugins
/**
 * Unloads all the plugins
 * @author          Tony Thompson
 * @date            Created 22 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::UnloadPlugins(void)
{
    ZX_LOG_INFO(lfGeneral, "Unloading the plugins")
    DWORD dwStartTime = timeGetTime();
    // unload the plugins
    while(m_Plugins.size() > 0)
    {
        ZXPluginsIterator PluginIt = m_Plugins.end();
        PluginIt--;
        (*PluginIt)->Unload();
        SAFE_DELETE((*PluginIt));
        m_Plugins.erase(PluginIt);
    }
    DWORD dwUnloadTime = timeGetTime() - dwStartTime;
    ZX_LOG_INFO(lfPlugin , "Plugins took " + IntToStr(dwUnloadTime) + "ms to unload")
    ZX_LOG_INFO(lfGeneral, "Plugins took " + IntToStr(dwUnloadTime) + "ms to unload")
    #ifdef USE_GUI_MANAGER
    if (true == SAFE_PTR(m_pGuiManager))
    {
        m_pGuiManager->ResetActivePlugin();
        m_pGuiManager->FreeOptions();
    }
    #endif
}
//---------------------------------------------------------------------------
// OrderPlugins
/**
 * Orders the plugins based on their LoadOrder value
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 * @date            Last Modified 22 September 2003 - Simplifed the code
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::OrderPlugins(void)
{
    unsigned int NextAvailableLoadOrder = m_Plugins.size();
    // loop thru all plugins, and check to see if it has a load order in the registry
    ZXPluginsIterator PluginIt = m_Plugins.begin();
    while(PluginIt != m_Plugins.end())
    {
        (*PluginIt)->ReadLoadOrder(NextAvailableLoadOrder);
        PluginIt++;
    }
    // now, order the plugins
    //std::sort(m_Plugins.begin(), m_Plugins.end());
    SortPlugins();
}
//---------------------------------------------------------------------------
// UnloadPlugin
/**
 * Unloads a specific plugin
 * @param           PluginIt the iterator of the plugin to remove
 * @return          The iterator of the next plugin in the list
 * @author          Tony Thompson
 * @date            Last Modified 15 November 2001
 * @date            Last Modified 22 September 2003
 */
//---------------------------------------------------------------------------
ZXPluginsIterator __fastcall ZXPluginManager::UnloadPlugin(const ZXPluginsIterator& PluginIt, bool bFreeOptions)
{
    (*PluginIt)->Unload(bFreeOptions);
    SAFE_DELETE((*PluginIt));
    return m_Plugins.erase(PluginIt);
}
//---------------------------------------------------------------------------
// LocatePlugins
/**
 * Locates all the plugin files within the plugin directory
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
#if 0
void __fastcall ZXPluginManager::LocatePlugins(void)
{
	AnsiString sDLLPath = ExtractFilePath(Application->ExeName) + AnsiString("Plugins\\");
    TSearchRec sr;
    int attr = faAnyFile;
    m_Plugins.clear();
    // find all files in the plugin directory
    if (0 == FindFirst(sDLLPath + "*" + m_sPluginExtension, attr, sr))
    {
        do
        {
            int MaskedAttributtes = (sr.Attr & (faVolumeID | faDirectory));
            // is the file found, really a file? We don't want VolumeIDs or Directories
            if (0 == MaskedAttributtes)
            {
                // found a plugin capable file, add it to our load list
                ZXPlugin* Plugin = new ZXPlugin(sr.Name, this);
                m_Plugins.push_back(Plugin);
            }
        // find the next file
        } while(0 == FindNext(sr));
    }
}
#endif
//---------------------------------------------------------------------------
// LocatePlugins
/**
 * Locates all the plugin files within the plugin directory
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::LocatePlugins(void)
{
	AnsiString sAppPath = Application->ExeName;
	AnsiString sPluginPath = "Plugins\\";
	AnsiString sDLLPath = ExtractFilePath(sAppPath) + sPluginPath;
    TSearchRec sr;
    // find all files in the plugin directory
    if (0 == FindFirst(sDLLPath + "*" + m_sPluginExtension, faAnyFile, sr))
    {
        do
        {
            int MaskedAttributtes = (sr.Attr & (faVolumeID | faDirectory));
            // is the file found, really a file? We don't want VolumeIDs or Directories
            if (0 == MaskedAttributtes)
            {
                // found a plugin capable file, add it to our load list
                ZXPlugin* Plugin = new ZXPlugin(sr.Name, this);
                m_Plugins.push_back(Plugin);
            }
        }
        // find the next file
        while(0 == FindNext(sr));
    }
    KRegistry* Registry = NULL;
    try
    {
        Registry = new KRegistry(NULL);
        String sMachineFolder;
        Registry->Section = "TommyGun";
        Registry->SoftwareKey = "\\Software\\Scorpio\\";
        Registry->RootKey = rkHKEY_CURRENT_USER;
        Registry->Read("Plugins", "MachineFolder", sMachineFolder);
        if (sMachineFolder.Trim() != "" && true == DirectoryExists(sDLLPath + "_" + sMachineFolder + "\\"))
        {
            sDLLPath += "_" + sMachineFolder + "\\";
            // find all files in the machine specific plugin directory
            if (0 == FindFirst(sDLLPath + "*" + m_sPluginExtension, faAnyFile, sr))
            {
                do
                {
                    int MaskedAttributtes = (sr.Attr & (faVolumeID | faDirectory));
                    // is the file found, really a file? We don't want VolumeIDs or Directories
                    if (0 == MaskedAttributtes)
                    {
                        // found a plugin capable file, add it to our load list
                        String sFile = "_" + sMachineFolder + "\\" + sr.Name;
                        ZXPlugin* Plugin = new ZXPlugin(sFile, this);
                        m_Plugins.push_back(Plugin);
                    }
                }
                // find the next file
                while(0 == FindNext(sr));
            }
        }
    }
    __finally
    {
        SAFE_DELETE(Registry);
    }
}
//---------------------------------------------------------------------------
// LoadPluginsInOrder
/**
 * Loads all the plugins in their load order
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::LoadPluginsInOrder(void)
{
    // load the plugins
    ZXPluginsIterator PluginIt = m_Plugins.begin();
    while(PluginIt != m_Plugins.end())
    {
        (*PluginIt)->Load(m_GetModuleInformation);
        if (m_ActivePlugin == NULL)
        {
            m_ActivePlugin = (*PluginIt)->Handle;
        }
        if (PluginIt == m_Plugins.begin())
        {
            #ifdef USE_GUI_MANAGER
            if (true == SAFE_PTR(m_pGuiManager))
            {
                m_pGuiManager->Refresh();
            }
            #endif
        }
        PluginIt++;
    }
}
//---------------------------------------------------------------------------
// RemoveUnloadedPlugins
/**
 * Removes all the plugins that failed to load
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::RemoveUnloadedPlugins(void)
{
    // remove the unloaded plugins
    ZXPluginsIterator PluginIt = m_Plugins.begin();
    while (PluginIt != m_Plugins.end())
    {
        if (false == (*PluginIt)->Loaded || true == (*PluginIt)->ExceptionCaught)
        {
            (*PluginIt)->Unload();
            PluginIt = m_Plugins.erase(PluginIt);
        }
        else
        {
            PluginIt++;
        }
    }
}
//---------------------------------------------------------------------------
// RemoveDoNotLoadPlugins
/**
 * Removes the plugins flagged as Donot Load
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::RemoveDoNotLoadPlugins(void)
{
    ZXPluginsIterator PluginIt = m_Plugins.begin();
    // remove the 'donot load' plugins
    while (PluginIt != m_Plugins.end())
    {
        if (true == (*PluginIt)->DoNotLoad && false == (*PluginIt)->ExceptionCaught)
        {
            PluginIt = UnloadPlugin(PluginIt, false);
        }
        else
        {
            PluginIt++;
        }
    }
}
//---------------------------------------------------------------------------
// ReorderLoadedPlugins
/**
 * Reorders the loaded plugins and saves their new order to the registry
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::ReorderLoadedPlugins(void)
{
    int iLoadOrder = 0;
    // reorder the plugins and save their orders, and add them to the options dialog
    //std::sort(m_Plugins.begin(), m_Plugins.end());
    SortPlugins();
    // clear the options plugin list
    #ifdef USE_GUI_MANAGER
    if (true == SAFE_PTR(m_pGuiManager))
    {
        m_pGuiManager->OptionsPluginsClear();
    }
    #endif
    // add the sorted plugins to the options list
    ZXPluginsIterator PluginIt = m_Plugins.begin();
    while (PluginIt != m_Plugins.end())
    {
        // add the plugin to the options dialog
        (*PluginIt)->AddToOptions(iLoadOrder);
        iLoadOrder++;
        PluginIt++;
    }
}
//---------------------------------------------------------------------------
// AddPluginsDirectoryToPath
/**
 * Adds the Plugins directory to the processes environment path variable to assist DLL loading
 * @author  Tony Thompson
 * @date    23 Janury 2002
 */
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::AddPluginsDirectoryToPath(void)
{
    // extract the old path variable
    char* cpPathVar = getenv("PATH");
    // failed to add to path variable
    int iResult = -1;
    if (true == SAFE_PTR(cpPathVar))
    {
        // construct a new path variable
        String sNewPathVar(cpPathVar);
        sNewPathVar = "PATH=" + sNewPathVar;
        // by adding the plugins directory
        sNewPathVar += ";" + ExtractFilePath(Application->ExeName) + g_sPluginsDirectory;
        // make the change to the new path variable
        iResult = putenv(sNewPathVar.c_str());
    }
}
//---------------------------------------------------------------------------
// Notify
/**
 * Broadcast a message to all plugins except the transmitter (Plugin parameter)
 * @param           TZX_HPLUGIN the Handle to the plugin who is transmitting the message
 * @param           TZX_EVENT   the event/message
 * @param           LPDATA      depends on message
 * @param           DWORD       depends on message
 * @param           DWORD       depends on message
 * @return          HRESULT     message response (depends on message type)
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPluginManager::Notify(TZX_HPLUGIN Plugin, TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg)
{
    HRESULT hResult = S_OK;
    TRY_ALL
    {
        bool bIsClosing = false;
        #ifdef USE_GUI_MANAGER
        if (true == SAFE_PTR(m_pGuiManager))
        {
            bIsClosing = m_pGuiManager->IsClosing();
        }
        #endif
        if (false == bIsClosing && false == IsLoading)
        {
            bool bKeepingProcessing = false;
            // process the new and open commands
            switch(Event)
            {
                case TZX_VERB_NEW:
                case TZX_VERB_OPEN:
                {
                    bool bDataSaved = true;

                    if (FOnQuerySave)
                    {
                        FOnQuerySave(bDataSaved);
                    }

                    if (true == bDataSaved)
                    {
                        // keep processing the message
                        bKeepingProcessing = true;
                    }
                    else
                    {
                        // don't process the message
                        bKeepingProcessing = false;
                        // cancel was pressed
                        hResult = S_FALSE;
                    }
                    break;
                }
                case TZXN_OPTIONS_SAVE:
                {
                    #ifdef USE_GUI_MANAGER
                    if (true == SAFE_PTR(m_pGuiManager))
                    {
                        m_pGuiManager->OptionsUpdate();
                    }
                    #endif
                    bKeepingProcessing = true;
                    break;
                }
                case TZX_VERB_SWITCH_PLUGIN:
                {
                    m_ActivePlugin = Plugin;
                    #ifdef USE_GUI_MANAGER
                    if (true == SAFE_PTR(m_pGuiManager))
                    {
                        m_pGuiManager->SwitchToPlugin(Plugin);
                    }
                    #endif
                    bKeepingProcessing = true;
                    break;
                }
                case TZX_QUERY_PROJECT_FOLDER:
                {
                    String sFolder;

                    if (FOnQueryProjectFolder)
                    {
                        FOnQueryProjectFolder(sFolder);
                    }
                    sFolder = ExtractFilePath(sFolder);
                    String* sProjectFolder = (String*)lpData;
                    if (true == SAFE_PTR(sProjectFolder))
                    {
                        *sProjectFolder = sFolder;
                    }
                    bKeepingProcessing = false;
                    break;
                }
                case TZXN_XML_UNDO_ADD:
                {
                    #ifdef USE_GUI_MANAGER
                    if (true == SAFE_PTR(m_pGuiManager))
                    {
                        m_pGuiManager->AddUndo((KXmlInfo*)lpData, (ZXUndoType)Param);
                    }
                    #endif
                    bKeepingProcessing = false;
                    break;
                }
                default:
                {
                    bKeepingProcessing = true;
                    break;
                }
            }
            // can we continue processing the notification?
            if (true == bKeepingProcessing)
            {
                switch(Event)
                {
                    case TZXN_QUIT:
                    {
                        // close the main form, and thus the application
                        //m_bClosing = true;
                        Application->Terminate();
                        break;
                    }
                    case TZXN_OPTIONS_CHANGED:
                    {
                        // a plugin has changed their options tab, so allow the user to apply the changes
                        #ifdef USE_GUI_MANAGER
                        if (true == SAFE_PTR(m_pGuiManager))
                        {
                            m_pGuiManager->OptionsChanged();
                        }
                        #endif
                        break;
                    }
                    default:
                    {
                        // broadcast the message to all plugins
                        if (Plugin != m_Handle && TZX_VERB_MASK == (Event & TZX_VERB_MASK))
                        {
                            // we have been sent a verb command. use the shells version of the verb to process the event for all plugins
                            #ifdef USE_GUI_MANAGER
                            if (true == SAFE_PTR(m_pGuiManager))
                            {
                                m_pGuiManager->PerformVerbCommand(Event);
                            }
                            #endif
                        }
                        else
                        {
                            // find the plugin that posted the event
                            ZXPluginsIterator PostPIIt = FindPlugin(Plugin);
                            // start at the beginning of the plugins
                            ZXPluginsIterator PluginIt = m_Plugins.begin();
                            // send event to all, but the plugin that sent the event.
                            // exit the loop if the application is closing
                            bool bIsClosing = false;
                            #ifdef USE_GUI_MANAGER
                            if (true == SAFE_PTR(m_pGuiManager))
                            {
                                bIsClosing = m_pGuiManager->IsClosing();
                            }
                            #endif
                            while(PluginIt != m_Plugins.end() && false == bIsClosing && false == (*PluginIt)->Unloading && false == (*PluginIt)->ExceptionCaught)
                            {
                                // only send the event to plugins that are loaded
                                if (PluginIt != PostPIIt)
                                {
                                    // get the plugins response to the message
                                    HRESULT Response = (*PluginIt)->NotifyEvent(Event, lpData, Param, Arg);
                                    // ignore S_OK as it means message posted, and S_FALSE as it means message ignored
                                    if (FAILED(Response))
                                    {
                                        // anything else if very relavent
                                        // the delimer here is do we assign or merge all the hresults?
                                        // assigning means we only get the last failed response
                                        // merging means that several plugins had some major problems
                                        // 99% of the time the failed response will probably be the same thus merging is like assigning 
                                        hResult |= Response;
                                    }
                                    if (true == (*PluginIt)->ExceptionCaught)
                                    {
                                        // plugin caused an exception so unload it
                                        PluginIt = UnloadPlugin(PluginIt);
                                    }
                                    else
                                    {
                                        PluginIt++;
                                    }
                                }
                                else
                                {
                                    PluginIt++;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    CATCH_ALL(hResult = S_FALSE)
    return hResult;
}
//---------------------------------------------------------------------------
// NotifyPlugin
/**
 * Sends a message to a specific plugin
 * @param           TZX_HPLUGIN the Handle to the plugin to receive the message
 * @param           TZX_EVENT   the event/message
 * @param           LPDATA      depends on message
 * @param           DWORD       depends on message
 * @param           DWORD       depends on message
 * @return          HRESULT     message response (depends on message type)
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPluginManager::NotifyPlugin(TZX_HPLUGIN Plugin, TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg)
{
    HRESULT hResult = S_OK;
    bool bIsClosing = false;
    #ifdef USE_GUI_MANAGER
    if (true == SAFE_PTR(m_pGuiManager))
    {
        bIsClosing = m_pGuiManager->IsClosing();
    }
    #endif
    if (TZXN_QUIT != Event && false == bIsClosing && (false == IsLoading || TZX_QUERY_KEY_PANEL == Event))
    {
        ZXPluginsIterator PluginIt = FindPlugin(Plugin);
        if (PluginIt != m_Plugins.end())
        {
            if (false == (*PluginIt)->Unloading && false == (*PluginIt)->ExceptionCaught)
            {
                hResult = (*PluginIt)->NotifyEvent(Event, lpData, Param, Arg);
                if (true == (*PluginIt)->ExceptionCaught)
                {
                    // plugin caused an exception so unload it
                    UnloadPlugin(PluginIt);
                }
            }
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
// Notify
/**
 * Sends a message to the active plugin only
 * @param           TZX_EVENT   the event/message
 * @param           LPDATA      depends on message
 * @param           DWORD       depends on message
 * @param           DWORD       depends on message
 * @return          HRESULT     message response (depends on message type)
 * @author          Tony Thompson
 * @date            Created 10 September 2005
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPluginManager::NotifyPlugin(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg)
{
    return NotifyPlugin(m_ActivePlugin, Event, lpData, Param, Arg);
}
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::LoadPSAPI(void)
{
    // what version of Windows are we running?
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    // try to load the PSAPI.DLL from the current directory
    if (VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
    {
        // We can use the PSAPI.DLL
        ZX_LOG_INFO(lfWindowsAPI, "Trying to Load PSAPI.DLL");
        m_hInst_PSAPI = LoadLibrary("PSAPI.DLL");
        // did we load the dll?
        if (NULL != m_hInst_PSAPI)
        {
            ZX_LOG_INFO(lfWindowsAPI, "PSAPI: Loaded PSAPI.DLL");
            m_GetModuleInformation = reinterpret_cast<GetModuleInformationPtr>(GetProcAddress(m_hInst_PSAPI, "GetModuleInformation"));
            if (true == SAFE_CODE_PTR(m_GetModuleInformation))
            {
                ZX_LOG_INFO(lfWindowsAPI, "PSAPI: Found - GetModuleInformation()");
            }
            else
            {
                ZX_LOG_INFO(lfWindowsAPI, "PSAPI: Failed to Find - GetModuleInformation()");
            }
        }
        else
        {
            ZX_LOG_INFO(lfWindowsAPI, "FAILED to Load PSAPI.DLL");
        }
    }
    else
    {
        ZX_LOG_INFO(lfWindowsAPI, "Cannot use PSAPI.DLL");
    }
}
//---------------------------------------------------------------------------
ZXPluginsIterator __fastcall ZXPluginManager::FindPlugin(TZX_HPLUGIN PluginHandle)
{
    RL_METHOD
    ZXPluginsIterator PluginIt = m_Plugins.begin();
    while(PluginIt != m_Plugins.end())
    {
        if ((*PluginIt)->Handle == PluginHandle)
        {
            break;
        }
        PluginIt++;
    }
    return PluginIt;
}
//---------------------------------------------------------------------------
ZXPluginsIterator __fastcall ZXPluginManager::FindPlugin(const String& sFilename)
{
    RL_METHOD
    String sFileName = ChangeFileExt(sFilename, m_sPluginExtension);
    ZXPluginsIterator PluginIt = m_Plugins.begin();
    while(PluginIt != m_Plugins.end())
    {
        if ((*PluginIt)->Filename == sFileName)
        {
            break;
        }
        PluginIt++;
    }
    return PluginIt;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPluginManager::RegisterPluginEvent(TZX_HPLUGIN PluginHandle, TZX_EVENT Event)
{
    RL_HRESULT(E_FAIL);
    ZXPluginsIterator PluginIt = FindPlugin(PluginHandle);
    if (PluginIt != m_Plugins.end())
    {
        hResult = (*PluginIt)->RegisterEvent(Event);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPluginManager::UnRegisterPluginEvent(TZX_HPLUGIN PluginHandle, TZX_EVENT Event)
{
    RL_HRESULT(E_FAIL);
    ZXPluginsIterator PluginIt = FindPlugin(PluginHandle);
    if (PluginIt != m_Plugins.end())
    {
        hResult = (*PluginIt)->UnRegisterEvent(Event);
    }
    return hResult;
}
//---------------------------------------------------------------------------
bool __fastcall ZXPluginManager::IsPluginValid(TZX_HPLUGIN PluginHandle)
{
    ZXPluginsIterator PluginIt = FindPlugin(PluginHandle);
    return PluginIt != m_Plugins.end();
}
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::SortPlugins(void)
{
    bool bSwapped = false;
    if (0 < m_Plugins.size())
    {
        do
        {
            bSwapped = false;
            for (unsigned int i = 0; i < m_Plugins.size() - 1; i++)
            {
                ZXPlugin* Plugin1 = m_Plugins[i  ];
                ZXPlugin* Plugin2 = m_Plugins[i+1];
                if (true == PluginLessThan(Plugin2, Plugin1))
                {
                    m_Plugins[i  ] = Plugin2;
                    m_Plugins[i+1] = Plugin1;
                    bSwapped = true;
                }
            }
        } while(true == bSwapped);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::SetPluginIcon(TZX_HPLUGIN PluginHandle, TImage* Icon)
{
    ZXPluginsIterator PluginIt = FindPlugin(PluginHandle);
    if (PluginIt != m_Plugins.end())
    {
        (*PluginIt)->Icon(Icon);
    }
}
//---------------------------------------------------------------------------
ZXPlugin* __fastcall ZXPluginManager::CheckException(void)
{
    ZXPlugin* Plugin = NULL;
    ZXPluginsIterator PluginIt = m_Plugins.begin();
    while (PluginIt != m_Plugins.end() && NULL == Plugin)
    {
        if (true == (*PluginIt)->OwnsMemory(ExceptAddr()))
        {
            Plugin = (*PluginIt);
        }
        PluginIt++;
    }
    return Plugin;
}
//---------------------------------------------------------------------------
void __fastcall ZXPluginManager::XmlNotify(TZX_EVENT XmlMessage, const String& sNode, KXmlInfo* xmlInfo)
{
    #ifdef USE_GUI_MANAGER
    if (false == SAFE_PTR(xmlInfo))
    {
        GetXmlInfo(xmlInfo);
    }
    PostNotifyEvent(NULL, XmlMessage, (LPDATA)xmlInfo, (LPARAM)&sNode, 0);
    #endif    
}
//---------------------------------------------------------------------------
ZXPlugin* __fastcall ZXPluginManager::GetFirstPlugin(void)
{
    m_iPluginGetNextIndex = 0;
    return GetNextPlugin();
}
//---------------------------------------------------------------------------
ZXPlugin* __fastcall ZXPluginManager::GetNextPlugin(void)
{
    ZXPlugin* Plugin = NULL;
    if (m_iPluginGetNextIndex < m_Plugins.size())
    {
        Plugin = m_Plugins[m_iPluginGetNextIndex++];
    }
    return Plugin;
}
//---------------------------------------------------------------------------


