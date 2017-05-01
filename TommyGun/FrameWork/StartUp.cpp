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
//-- VCL --------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------
#include <mmsystem.h>
#include "..\SafeMacros.h"
#include "StartUp.h"
#include "ZXLogFile.h"
//---------------------------------------------------------------------------
//TODO:RL_MESSAGE_LOGGER_OBJECT
//---------------------------------------------------------------------------
const String g_sBlank = "";
//-- DLL INTERFACES ---------------------------------------------------------
extern "C"
{
    FUNCTION_PREFIX InitializeCore           (void);
    FUNCTION_PREFIX FreeCore                 (void);
};
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Logging;
using namespace GUI;
using namespace Plugin;
using namespace Project;
//-- GLOBAL MANAGER OBJECTS -------------------------------------------------
ZXGUIManager        g_GuiManager;
ZXPluginManager     g_PluginManager(&g_GuiManager, ".tpi");
ZXProjectManager    g_ProjectManager;
ZXUndoManager       g_UndoManager;
//ZXExceptionManager  g_ExceptionManager;
//- GLOBAL LOG FILE ---------------------------------------------------------
ZXLogFile           g_LogFile(true);
//---------------------------------------------------------------------------
std::vector<TZXExceptionInfo>   g_Exceptions;
//---------------------------------------------------------------------------
HINSTANCE g_hInstance = NULL;
//---------------------------------------------------------------------------
/** DllEntryPoint
 *
 * @brief   Main Windows Entry point for all dll's
 * @return  TRUE dll entered
 * @author  Tony Thompson
 * @date    Created 29 October 2001
 * @date    Last Modified 19 September 2003
 */
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    if (DLL_PROCESS_ATTACH != reason && NULL == g_hInstance)
    {
        g_hInstance = hinst;
    }
    return TRUE;
}
//---------------------------------------------------------------------------
/** InitializeManagers
 * @brief   Initializes the global manager objects
 * @return  true if successful, false if not
 * @author  Tony Thompson
 * @date    Created 19 September 2003
 */
//---------------------------------------------------------------------------
bool __fastcall InitializeManagers(void)
{
    bool bInitialized = true;
    try
    {
        // everything uses the exception manager so initialize it first
        //bInitialized &= g_ExceptionManager.Initialize();
        // then the gui manager because the plugin manager needs it,
        bInitialized &= g_GuiManager.Initialize();
        // and the plugin manager
        bInitialized &= g_PluginManager.Initialize(g_hInstance);
        // and lastly the project manager
        bInitialized &= g_ProjectManager.Initialize(g_hInstance);
        ZX_LOG_INFO(lfGeneral, "All managers initialized")
    }
    catch(...)
    {
        // oh my, an evil troll has us by the goolies...errrrr...ahhhhh!!!!!!!
        bInitialized = false;
        ZX_LOG_EXCEPTION(lfGeneral, "Exception caught during InitializeManagers");
    }
    return bInitialized;
}
//---------------------------------------------------------------------------
/** ReleaseManagers
 * @brief   Releases the global managers
 * @return  true if successful, false if not
 * @author  Tony Thompson
 * @date    Created 19 September 2003
 */
//---------------------------------------------------------------------------
bool __fastcall ReleaseManagers(void)
{
    bool bReleased = false;
    try
    {
        // and of course we release in the reverse order to initialization
        g_ProjectManager.Release();
        g_PluginManager.Release();
        g_GuiManager.Release();
        //bReleased &= g_ExceptionManager.Release();
        bReleased = true;
    }
    catch(...)
    {
        // oh my, we have failed in our quest to release ourselves from the evil troll and it has punished us!
        bReleased = false;
        ZX_LOG_EXCEPTION(lfGeneral, "Exception caught during ReleaseManagers");
    }
    return bReleased;
}
//---------------------------------------------------------------------------
/** InitializeCore
 * @brief   Initializes the core engine. Loads all the plugins.
 * @return  S_OK initialization successful, S_FALSE already initialized, E_FAIL failed to initialize
 * @author  Tony Thompson
 * @date    Created 29 October 2001
 * @date    Last Modified 19 September 2003
 */
//---------------------------------------------------------------------------
HRESULT WINAPI InitializeCore(void)
{
    RL_HRESULT(S_FALSE);
    PROTECT_BEGIN
    static bool bInitialized = false;
    // if the application is valid
    if (false == bInitialized)
    {
        // create the main manager objects
        if (true == InitializeManagers())
        {
            hResult = S_OK;
            ZX_LOG_INFO(lfGeneral, "Framework Object Initialized")
            // show the splash screen if required
            g_GuiManager.ShowSplash();
            // update the options form
            g_GuiManager.OptionsUpdate();
            // update the resources for the loaded plugins
            g_PluginManager.InitiatePlugins();
            // finished loading, events can be processed
            g_GuiManager.HideSplash();
            // TODO: check the command line and see if a file was opened
            // core is now initialized. Cannot be affected by calls from other dll's or exe's.
            bInitialized = true;
        }
        else
        {
            ZX_LOG_ERROR(lfGeneral, "Failed to create and initialize the Manager objects")
            hResult = E_FAIL;
        }
    }
    else
    {
        ZX_LOG_WARNING(lfGeneral, "Framework is already Initialized")
    }
    PROTECT_END
    return hResult;
}
//---------------------------------------------------------------------------
/** FreeCore
 * @brief   Frees the resources associated with the framework
 * @return  S_OK successful
 * @author  Tony Thompson
 * @date    Created 29 October 2001
 * @date    Last Modified 19 September 2003
 */
//---------------------------------------------------------------------------
HRESULT WINAPI FreeCore(void)
{
    bool bReleased = false;
    PROTECT_BEGIN
    // relase the manager objects
    bReleased = ReleaseManagers();
    if (true == bReleased)
    {
        ZX_LOG_INFO(lfGeneral, "Framework Released")
    }
    else
    {
        ZX_LOG_ERROR(lfGeneral, "Framework FAILED to release correctly")
    }
    PROTECT_END
    return bReleased ? S_OK : E_FAIL;
}
//---------------------------------------------------------------------------
/** PushException
 * @brief   Pushes an exception onto a global exception list
 * @author  Tony Thompson
 * @date    Created 9 April 2004
 */
//---------------------------------------------------------------------------
void __fastcall PushException(const String sMessage, const String sFile, const String sFunc, int iLine)
{
    TZXExceptionInfo Info;
    Info.sMessage = sMessage;
    Info.sFile    = sFile;
    Info.sFunc    = sFunc;
    Info.iLine    = iLine;
    g_Exceptions.push_back(Info);
}
//---------------------------------------------------------------------------

