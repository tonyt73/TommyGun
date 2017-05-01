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
using namespace Scorpio;
using namespace Plugin;
using namespace Logging;
//---------------------------------------------------------------------------
const int   g_iNotFound    = -1;
//---------------------------------------------------------------------------
__fastcall ZXPlugin::ZXPlugin(const String& sFilename, ZXPluginManager* PluginManager)
: m_PluginManager(PluginManager)
, m_iLoadOrder(-1)
, m_sFileName(sFilename)
, m_sDescription("")
, m_sComments("")
, m_sProductVersion("Unknown")
, m_sFileVersion("Unknown")
, m_sInternalName("Unknown")
, m_sVendor("Unknown")
, m_sParentSignature("")
, m_bLoaded(false)
, m_bDoNotLoad(false)
, m_bUnloading(false)
, m_bInitialized(false)
, m_bExceptionCaught(false)
, m_hInstance(NULL)
, m_hParentInstance(NULL)
, m_NotifyFunc(NULL)
, m_ReleaseFunc(NULL)
, m_ModuleAddress(0)
, m_dwModuleSize(0)
, m_dwVersion(0)
, m_dwFlags(0)
, m_dwInterface(0)
, m_Icon(NULL)
{
}
//---------------------------------------------------------------------------
__fastcall ZXPlugin::~ZXPlugin()
{
    // unload the plugin if it hasn't already been done
    if (true == m_bLoaded)
    {
        Unload();
    }
    // reset some member variables just in case
    m_ModuleAddress = NULL;
    m_bInitialized  = false;
    m_bUnloading    = false;
    m_bLoaded       = false;
    m_sFileName     = "";
}
//---------------------------------------------------------------------------
// Load
/**
 * Loads a plugin into memory and initializes it if required
 * @param           GetModuleInformation the pointer to the GetModuleInformation function in PSAPI.dll
 * @return          S_OK if loaded successful, else E_FAIL if failed to load
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPlugin::Load(GetModuleInformationPtr GetModuleInformation)
{
    HRESULT hResult = E_FAIL;
    bool bFreeLibrary = false;
    // try to load the DLL
    String DllPath = ExtractFilePath(Application->ExeName) + String("Plugins\\") + m_sFileName;
    HINSTANCE hInstance = NULL;
    ZX_LOG_INFO(lfPlugin, "Loading Plugin: " + DllPath);
    DWORD dwStartTime = timeGetTime();

    try
    {
        hInstance = LoadLibrary(DllPath.c_str());
        // get the details of the module
        if (NULL != hInstance)
        {
            MODULEINFO ModuleInfo;
            ModuleInfo.lpBaseOfDll = hInstance;
            ModuleInfo.SizeOfImage = 0;
            ModuleInfo.EntryPoint  = 0;
            DWORD SizeOfModuleInfo = sizeof(ModuleInfo);
            HANDLE hProcess = GetCurrentProcess();
            if (true == SAFE_CODE_PTR(GetModuleInformation) && GetModuleInformation(hProcess, hInstance, &ModuleInfo, SizeOfModuleInfo))
            {
                m_dwModuleSize = ModuleInfo.SizeOfImage;
            }
            else
            {
                m_dwModuleSize = 0;
            }
            m_ModuleAddress = hInstance;
        }
        else
        {
            DWORD dwErrorCode = GetLastError();
            ZXMessageBox MessageBox;
            MessageBox.ShowWindowsErrorMessage("LoadLibrary Failed: " + DllPath, dwErrorCode, __FILE__, __FUNC__, __LINE__);
            ZX_LOG_ERROR(lfPlugin, "LoadLibrary Error: " + IntToStr(dwErrorCode));
        }
    }
    catch(...)
    {
        ZX_LOG_EXCEPTION(lfException, m_sFileName + "caused an exception while try to load the DLL");
        hInstance = NULL;
    }

    if (NULL != hInstance)
    {
        m_hInstance = hInstance;
        // Get Plugin file version details
        hResult = GetPluginVersionInfo();
        if (S_OK == hResult)
        {
            // We have version info in the file, so check the
            // interface version and initialise functions from the loaded DLL
            if ((m_sParentSignature == "" && S_OK == CheckInterfaceRequirements()) || (m_sParentSignature != "" && S_OK == CheckPluginSignature(m_sParentSignature)))
            {
                InitialisePtr InitialiseFunc = NULL;
                InitialiseFunc = reinterpret_cast<InitialisePtr>(GetProcAddress(hInstance, "Initialise"));
                // Do we have a valid initialise function to call?
                if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(InitialiseFunc)))
                {
                    // NOTE: It is not important that we check the LastError value if the GetProcAddresses fail. This maybe because
                    // the dll we are trying to load is not a valid plugin, there maybe other programs out there that use the same
                    // extension we do. Thus we can only assume a valid plugin, if all functions are satisfied.
					m_NotifyFunc  = reinterpret_cast<NotifyPtr> (GetProcAddress(hInstance, "Notify"));
                    m_ReleaseFunc = reinterpret_cast<ReleasePtr>(GetProcAddress(hInstance, "Release"));
                    // Are all the functions required, present?
                    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_NotifyFunc )) &&
                        FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_ReleaseFunc)))
                    {
                        // yes, the DLL is valid.
                        m_bLoaded = true;
                        hResult = S_OK;
                        // does the plugin have a flags function?
                        FlagsPtr FlagsFunc = reinterpret_cast<FlagsPtr> (GetProcAddress(hInstance, "Flags"));
                        DWORD Flags = 0L;
                        if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(FlagsFunc)))
                        {
                            if (S_FALSE == FlagsFunc(Flags))
                            {
                                Flags = 0L;
                            }
                            if (FLAG_IsNotUnloadable == (Flags & FLAG_IsNotUnloadable))
                            {
                                // must always load this plugin
                                m_bDoNotLoad = false;
                            }
                        }
                        m_dwFlags = Flags;
                        // Does the user want us to load the plugin, or do we have to load it because it has to be loaded
                        if (false == m_bDoNotLoad)
                        {
                            bool bExceptionCaught = false;
                            try
                            {
                                m_bLoaded = false;
                                hResult   = S_FALSE;
                                // initialize the loaded DLL
                                if (S_OK != InitialiseFunc(this))
                                {
                                    // failed to initialize do not load next time
                                    ZX_LOG_ERROR(lfPlugin, "Failed to Initialize Plugin: " + m_sFileName);
                                    m_bExceptionCaught = true;
                                    m_bDoNotLoad = true;
                                    bFreeLibrary = true;
                                }
                                else
                                {
                                    m_bLoaded = true;
                                    hResult = S_OK;
                                    // set the default icon for the plugin if the plugin hasn't already done so in initialize
                                    #ifdef USE_GUI_MANAGER
                                    if (true == SAFE_PTR(m_PluginManager->GuiManager))
                                    {
                                        m_PluginManager->GuiManager->AddPluginIcon(m_hInstance, NULL, m_sDescription);
                                    }
                                    #endif
                                    ZX_LOG_INFO(lfPlugin, "Initialized Plugin: " + m_sFileName);
                                    m_bInitialized = true;
                                }
                            }
                            catch(...)
                            {
                                bExceptionCaught = true;
                                ZX_LOG_EXCEPTION(lfException, m_sFileName + " caused an exception during Initialization")
                            }
                            if (true == bExceptionCaught)
                            {
                                // plugin caused an exception during initialization, so unload it
                                m_bExceptionCaught = true;
                                m_bDoNotLoad = true;
                                bFreeLibrary = true;
                                hResult = S_FALSE;
                            }
                        }
                        else
                        {
                            ZX_LOG_WARNING(lfPlugin, "Instructed not to load Plugin: " + m_sFileName);
                            m_bLoaded = true;
                            bFreeLibrary = false;
                        }
                    }
                    else
                    {
                        ZX_LOG_WARNING(lfPlugin, "The File " + m_sFileName + " may not be a TommyGun Plugin");
                    }
                }
                else
                {
                    ZX_LOG_WARNING(lfPlugin, "The File " + m_sFileName + " may not be a TommyGun Plugin");
                }
            }
            else
            {
                ZX_LOG_ERROR(lfPlugin, "The File " + m_sFileName + " is incompatible with this version of the Framework");
                // report that we tried to load a plugin but its interface requirements where incorrect!
                String Msg = "Failed to Load Plugin: " + m_sFileName;
                #ifdef USE_GUI_MANAGER
                if (true == SAFE_PTR(m_PluginManager->GuiManager))
                {
                    m_PluginManager->GuiManager->ShowGeneralMessage(Msg, "Incompatible Interface Requirements", __FILE__, __FUNC__, __LINE__);
                }
                #endif
                m_bLoaded = true;
                Unload();
                m_bDoNotLoad = true;
                bFreeLibrary = false;
                hResult = S_FALSE;
            }
        }
        else
        {
            ZX_LOG_ERROR(lfPlugin, "Plugin " + m_sFileName + " has no Version Info and its interface requirements cannot be validated");
        }
        if (S_FALSE == hResult || true == bFreeLibrary)
        {
            ZX_LOG_INFO(lfPlugin, "Unloading " + m_sFileName + " due to error while Loading and Initializing")
            m_ReleaseFunc = NULL;
            m_NotifyFunc  = NULL;
            Unload();
        }
    }
    else
    {
        // we failed to load a suspected plugin.
        ZX_LOG_ERROR(lfPlugin, "LoadLibrary FAILED on the file " + m_sFileName);
    }
    DWORD dwEndTime = timeGetTime();
    ZX_LOG_INFO(lfPlugin, "Loading took " + IntToStr(dwEndTime - dwStartTime) + "ms for " + m_sFileName);
    return hResult;
}
//---------------------------------------------------------------------------
// Unload
/**
 * Unloads a plugin its resources and the dll
 * @param           GetModuleInformation the pointer to the GetModuleInformation function in PSAPI.dll
 * @return          S_OK if loaded successful, else E_FAIL if failed to load
 * @author          Tony Thompson
 * @date            Last Modified 30 October 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPlugin::Unload(bool bFreeOptions)
{
    RL_HRESULT(E_FAIL);
    // clear the events
    m_Events.clear();
    if (true == m_bLoaded)
    {
        DWORD dwStartTime = timeGetTime();
        try
        {
            ZX_LOG_WARNING(lfPlugin, "Unloading Plugin " + m_sFileName);
            m_bUnloading = true;
            // release the plugin resources
            if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_ReleaseFunc)) && true == m_bInitialized)
            {
                try
                {
                     m_ReleaseFunc();
                }
                catch(...)
                {
                    ZX_LOG_EXCEPTION(lfException, m_sFileName + " caused an exception during Release()")
                    ZX_LOG_ERROR(lfPlugin, "Unable to Release Plugin: " + m_sFileName + " due to an exception");
                    m_bExceptionCaught = true;
                    m_ReleaseFunc = NULL;
                }
            }
            else
            {
                ZX_LOG_ERROR(lfPlugin, "No Release function or Plugin is not initialized [" + m_sFileName + "]");
            }
        }
        __finally
        {
            // free the DLL
            if (NULL != m_hInstance)
            {
                #ifdef USE_GUI_MANAGER
                if (true == SAFE_PTR(m_PluginManager->GuiManager))
                {
                    m_PluginManager->GuiManager->Free(m_hInstance, bFreeOptions);
                }
                #endif
                if (FALSE == FreeLibrary(m_hInstance))
                {
                    // failed to free the DLL
                    ZX_LOG_ERROR(lfPlugin, "Failed to Unload the DLL of the Plugin: " + m_sFileName);
                }
                else
                {
                    ZX_LOG_INFO(lfPlugin, "Successfully Unloaded the DLL of the Plugin: " + m_sFileName);
                    hResult = S_OK;
                }
                m_hInstance = NULL;
                m_bLoaded = false;
            }
        }
        DWORD dwEndTime = timeGetTime();
        ZX_LOG_INFO(lfPlugin, "Unloading took " + IntToStr(dwEndTime - dwStartTime) + "ms for " + m_sFileName);
    }
    return hResult;
}
//---------------------------------------------------------------------------
// GetPluginVersionInfo
/**
 * Gets the File Version information for the plugin file
 * @param           PluginIt The plugin iterator
 * @return          HRESULT     S_OK information retrieved, else failed
 * @author          Tony Thompson
 * @date            Created 12 March 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPlugin::GetPluginVersionInfo(void)
{
    HRESULT hResult = E_FAIL;
    // get the detals of the plugin
    String DllPath = ExtractFilePath(Application->ExeName) + "Plugins\\" + m_sFileName;
    KFileInfo* FileInfo = NULL;
    try
    {
        FileInfo = new KFileInfo(NULL);
    }
    catch(EOutOfMemory&)
    {
        ZX_LOG_EXCEPTION(lfException, "Failed to create the FileInfo object")
        FileInfo = NULL;
    }
    if (true == SAFE_PTR(FileInfo))
    {
        FileInfo->FileName = DllPath;
        if (true == FileInfo->FileInfoValid)
        {
            m_sDescription      = FileInfo->FileDescription;
            m_sComments         = FileInfo->Comments;
            m_sVendor           = FileInfo->CompanyName;
            m_sFileVersion      = FileInfo->FileVersion;
            m_sProductVersion   = FileInfo->ProductVersion;
            m_sInternalName     = FileInfo->InternalName;
            hResult = S_OK;
        }
        SAFE_DELETE(FileInfo);
    }
    return hResult;
}
//---------------------------------------------------------------------------
// CheckInterfaceRequirements
/**
 * Checks the Plugin Interface Requirements can be met by Core.dll
 * @param           PluginIt The plugin iterator
 * @return          HRESULT     S_OK Requirements can be met
 * @author          Tony Thompson
 * @date            Created 12 March 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPlugin::CheckInterfaceRequirements(void)
{
    HRESULT hResult = E_FAIL;
    // convert the product version string to a major and minor number
    int iDotPos = m_sProductVersion.Pos('.');
    ZX_LOG_INFO(lfPlugin, m_sFileName + ", Version: " + m_sProductVersion);
    if (0 != iDotPos)
    {
        AnsiString sMajor = m_sProductVersion.SubString(1, iDotPos - 1);
        String sProductVersion = m_sProductVersion.SubString(iDotPos + 1, m_sProductVersion.Length());
        iDotPos = sProductVersion.Pos('.');
        if (0 != iDotPos)
        {
            AnsiString sMinor = sProductVersion.SubString(1, iDotPos - 1);
            int iMajor = 0;
            int iMinor = 0;
            iMajor = StrToInt(sMajor);
            iMinor = StrToInt(sMinor);
            WORD iVersion = (iMajor << 8) | iMinor;
            // check the requirements of the plugin against the cores functionality
            if (g_dwCoreInterfaceVersion >= iVersion && iVersion >= g_dwCompatibleBaseVersion)
            {
                hResult = S_OK;
            }
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
// ReadLoadOrder
/**
 * Reads a plugin loading information from the registry
 * @param           NextAvailableLoadOrder the next available load order id to use
 * @author          Tony Thompson
 * @date            Created 22 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall ZXPlugin::ReadLoadOrder(unsigned int& NextAvailableLoadOrder)
{
    // assume the plugin has no load order defined
    int iLoadOrder = g_iNotFound;
    // reset the plugin flags to zero
    m_dwFlags = 0L;
    // try to read a load order from the registry
    #ifdef USE_GUI_MANAGER
	if (true == SAFE_PTR(m_PluginManager->GuiManager) && true == m_PluginManager->GuiManager->Registry()->Read("Plugins", m_sFileName, iLoadOrder))
    {
        // plugin is known, and an order has been given
        bool bDoNotLoad;
        m_iLoadOrder = iLoadOrder;
        // does it have a DoNotLoad entry
        if (true == m_PluginManager->GuiManager->Registry()->Read("Plugins", "DNL_" + m_sFileName, bDoNotLoad))
        {
            // yes, assign the DNL value
            m_bDoNotLoad = bDoNotLoad;
            if (true == bDoNotLoad) ZX_LOG_INFO(lfPlugin, m_sFileName + " is set NOT to load")
        }
        else
        {
            // DNL is false by default
            m_bDoNotLoad = false;
        }
    }
    else
    {
        // this is a new plugin, make it welcome and give it a load order
        m_iLoadOrder = NextAvailableLoadOrder;
        m_bDoNotLoad = false;
        ++NextAvailableLoadOrder;
    }
    #endif
}
//---------------------------------------------------------------------------
// AddToOptions
/**
 * Adds a plugin to the options dialog
 * @param           iNewLoadOrder the new load order of the plugin
 * @author          Tony Thompson
 * @date            Created 22 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall ZXPlugin::AddToOptions(int iNewLoadOrder)
{
    m_iLoadOrder = iNewLoadOrder;
    #ifdef USE_GUI_MANAGER
    if (true == SAFE_PTR(m_PluginManager->GuiManager))
    {
		m_PluginManager->GuiManager->Registry()->Write("Plugins", m_sFileName, (int)m_iLoadOrder);
        m_PluginManager->GuiManager->Registry()->Write("Plugins", "DNL_" + m_sFileName, m_bDoNotLoad);
        m_PluginManager->GuiManager->OptionsPluginsAdd(m_hInstance,
                                       m_sDescription,
                                       m_sFileName,
                                       m_sVendor,
                                       m_sProductVersion,
                                       m_sFileVersion,
                                       (FLAG_IsNotUnloadable != (m_dwFlags & FLAG_IsNotUnloadable)),
                                       m_bDoNotLoad,
                                       FLAG_IsNotVisibleInOptionsPage == (m_dwFlags & FLAG_IsNotVisibleInOptionsPage),
                                       m_dwFlags & FLAG_PluginLoadPriorityMask,
                                       m_iLoadOrder,
                                       m_Icon
                                       );
    }
    #endif
}
//---------------------------------------------------------------------------
bool __fastcall ZXPlugin::InterestedInEvent(TZX_EVENT Event)
{
    return std::find(m_Events.begin(), m_Events.end(), Event) != m_Events.end();
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPlugin::NotifyEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg)
{
    RL_HRESULT(S_FALSE);
    if (true == InterestedInEvent(Event))
    {
        try
        {
            if (true == SAFE_CODE_PTR(m_NotifyFunc))
            {
                hResult = m_NotifyFunc(Event, lpData, Param, Arg);
            }
            else
            {
                ZX_LOG_ERROR(lfPlugin, m_sFileName + " has an invalid NotifyFunc pointer")
            }
        }
        catch(...)
        {
            // plugin caused an exception
            m_bExceptionCaught = true;
            ZX_LOG_EXCEPTION(lfException, m_sFileName + " caused an exception while processing NotifyEvent with message 0x" + IntToHex(Event, 8))
            // unload the plugin due to exception
            Unload();
            #ifdef USE_GUI_MANAGER
            if (true == SAFE_PTR(m_PluginManager->GuiManager))
            {
                m_PluginManager->GuiManager->ShowMessage(mbtError,
                                         "Plugin has caused an Exception",
                                         "A plugin has exploded in a heap and crashed",
                                         "Plugin: " + m_sDescription + "\n\nThis plugin has caused a fault and as such has been booted out of the TommyGun environment for being a naughty little plugin.\n\nPlease send the exception.log and plugin.log files to KiwiWare.",
                                         "OK", "", ""
                                         );
            }
            #endif
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPlugin::RegisterEvent(TZX_EVENT Event)
{
    RL_HRESULT(E_FAIL);
    // find the event (or lack of it)
    if (m_Events.end() == std::find(m_Events.begin(), m_Events.end(), Event))
    {
        // register the event
        m_Events.push_back(Event);
        hResult = S_OK;
    }
    else
    {
        // event already registered
        hResult = S_FALSE;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPlugin::UnRegisterEvent(TZX_EVENT Event)
{
    RL_HRESULT(E_FAIL);
    ZXEventsIterator EventsIt = std::find(m_Events.begin(), m_Events.end(), Event);
    if (m_Events.end() != EventsIt)
    {
        // unregister the event
        m_Events.erase(EventsIt);
        hResult = S_OK;
    }
    else
    {
        // event already unregistered
        hResult = S_FALSE;
    }
    return hResult;
}
//---------------------------------------------------------------------------
bool __fastcall ZXPlugin::OwnsMemory(void *Address)
{
    DWORD dwAddress = (DWORD)Address;
    DWORD dwModule  = (DWORD)m_ModuleAddress;
    return (dwModule <= dwAddress && dwAddress <= dwModule + m_dwModuleSize);
}
//---------------------------------------------------------------------------
// CheckPluginSignature
/**
 * Checks the Plugin Interface Requirements can be met by Core.dll
 * @param           PluginIt The plugin iterator
 * @return          HRESULT     S_OK Requirements can be met
 * @author          Tony Thompson
 * @date            Created 12 March 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPlugin::CheckPluginSignature(String sRequiredSignature)
{
    HRESULT hResult = E_FAIL;
    String sSignature = "";
    SignaturePtr SignatureFunc = reinterpret_cast<SignaturePtr>(GetProcAddress(Handle, "Signature"));
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(SignatureFunc)))
    {
        if (S_OK != SignatureFunc(sSignature))
        {
            sSignature = "";
        }
        if (sRequiredSignature == sSignature)
        {
            hResult = S_OK;
        }
    }
    m_sParentSignature = sSignature;
    // convert the product version string to a major and minor number
    /*int iDotPos = m_sProductVersion.Pos('.');
    ZX_LOG_INFO(lfPlugin, m_sFileName + ", Version: " + m_sProductVersion);
    if (0 != iDotPos)
    {
        AnsiString sMajor = m_sProductVersion.SubString(1, iDotPos - 1);
        String sProductVersion = m_sProductVersion.SubString(iDotPos + 1, m_sProductVersion.Length());
        iDotPos = sProductVersion.Pos('.');
        if (0 != iDotPos)
        {
            AnsiString sMinor = sProductVersion.SubString(1, iDotPos - 1);
            int iMajor = 0;
            int iMinor = 0;
            iMajor = StrToInt(sMajor);
            iMinor = StrToInt(sMinor);
            WORD iVersion = (iMajor << 8) | iMinor;
            // check the requirements of the plugin against the cores functionality
            if (g_dwCoreInterfaceVersion >= iVersion && iVersion >= g_dwCompatibleBaseVersion)
            {
                hResult = S_OK;
            }
        }
    }*/
    return hResult;
}
//---------------------------------------------------------------------------


