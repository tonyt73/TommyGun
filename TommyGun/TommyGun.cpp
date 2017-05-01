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

-----------------------------------------------------------------------------

	TommyGun.cpp
	This is the main VCL application cpp. It handles the task of loading the main core.dll.
	Core.dll contains all the logic for the application.
	TommyGun.cpp processes all the Windows messages from within the Run() call.

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
#pragma warn -8004  // Turn OFF Warning W8004: Identifier is assigned a value that is not used.
//#include <mmsystem.h>
//---------------------------------------------------------------------------
typedef HRESULT(WINAPI *InitializePtr)(void);
typedef HRESULT(WINAPI *FreeCorePtr  )(void);
typedef int    (WINAPI *StdCallPtr   )(void);
///-- CORE.DLL HINSTANCE -----------------------------------------------------
HINSTANCE g_hInst = NULL;
///-- STRING CONSTANTS -------------------------------------------------------
const String      g_sApplicationTitle            = "TommyGun";
const String      g_sCorePluginPath              = "Core_R6.dll";
const char* const g_sInitializeFunctionName      = "InitializeCore";
const char* const g_sFreeCoreFunctionName        = "FreeCore";
const char* const g_sFailedToLoadCoreTitle       = "Failed to Load Core.DLL";
const char* const g_sFailedToInitalizeCoreMsg    = "Core.DLL Initialize Function not accessable";
const char* const g_sFailedToInitalizeCoreTitle  = "Failed to Initialize KiwiWare.DLL";
const char* const g_sFailedFreeCoreMsg           = "Core.DLL is seems to be invalid";
const char* const g_sFailedFreeCoreTitle         = "Failed to Free KiwiWare.DLL";
//---------------------------------------------------------------------------
/** @file TommyGun.cpp
 *  @method         LoadCorePlugin
 *  @brief          Loads the Core.DLL and initializes it.
 *  @return         bool true if successful, false if unsucessful
 *  @author         Tony Thompson
 *  @date           29 October 2001
 */
//---------------------------------------------------------------------------
bool __fastcall LoadCorePlugin(void)
{
    bool bResult = false;
    // get the core.dll full path
    String CoreDLL = ExtractFilePath(Application->ExeName) + g_sCorePluginPath;
    // try to load the DLL
    g_hInst = LoadLibrary(CoreDLL.c_str());
    // check the DLL loaded
    if (NULL != g_hInst)
    {
        // get the initalize function pointer
        InitializePtr InitializeFunc = NULL;
        InitializeFunc = reinterpret_cast<InitializePtr>(GetProcAddress(g_hInst, g_sInitializeFunctionName));
        // did we get an initialize function pointer? and is it valid?
        if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(InitializeFunc)))
        {
            // yep, call the initialize function
            try
            {
                if (SUCCEEDED(InitializeFunc()))
                {
                    // excellent, we initialized the framework.
                    bResult = true;
                }
            }
            catch (...)
            {
                bResult = false;
            }
        }
        else
        {
            // Display the error string from GetProcAddress
            ShowMessage(g_sFailedToInitalizeCoreTitle);
            // free the DLL
            try
            {
				if (FALSE == FreeLibrary(g_hInst))
                {
                    // failed to free the DLL
                    ShowMessage(g_sFailedFreeCoreTitle);
                }
            }
            __finally
            {
                g_hInst = NULL;
            }
        }
    }
    else
    {
        // The Dll failed to load for some reason, so lets tell the user
        // why it failed be giving them a good old Windows cryptic message!
        ShowMessage(g_sFailedToLoadCoreTitle);
    }
    return bResult;
}
//---------------------------------------------------------------------------
/** @file TommyGun.cpp
 *  @method          FreeCorePlugin
 *  @brief           Frees the Core.DLL
 *  @return          void
 *  @author          Tony Thompson
 *  @date            29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall FreeCorePlugin(void)
{
    // if we loaded the core.dll then we should free it
    if (NULL != g_hInst)
    {
        // get the free core function pointer
        FreeCorePtr FreeCoreFunc = NULL;
        FreeCoreFunc = reinterpret_cast<FreeCorePtr>(GetProcAddress(g_hInst, g_sFreeCoreFunctionName));
        if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(FreeCoreFunc)))
        {
            // ok, call the free core function
			try
            {
                FreeCoreFunc();
            }
            catch (...)
            {
            }
        }
        else
        {
            // Display the string.
            ShowMessage(g_sFailedFreeCoreTitle);
        }
        try
        {
            // free the DLL
            if (FALSE == FreeLibrary(g_hInst))
            {
                // failed to free the DLL
                ShowMessage(g_sFailedFreeCoreTitle);
            }
        }
        __finally
        {
            g_hInst = NULL;
        }
    }
}
//---------------------------------------------------------------------------
/** @file TommyGun.cpp
 *  @method          WinMain
 *  @brief           Main Entry point into the Application. Is the main window loop of the Application
 *  @author          Tony Thompson
 *  @date            29 October 2001
 */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		// initialize the VCL application, and set its title
		Application->Initialize();
		SetApplicationMainFormOnTaskBar(Application, true);
		// try, to load the core.dll
		if (Screen->Width >= 800 && Screen->Height >= 600)
		{
			//DWORD st = timeGetTime();
			if (true == LoadCorePlugin())
			{
				//ShowMessage("Load Core took: " + IntToStr(timeGetTime() - st) + "ms");
				// success, run the application
				//Application->HelpFile = "";
                Application->Title = "TommyGun";
                Application->Run();
				// free the framework
				//st = timeGetTime();
				FreeCorePlugin();
				//String sMsg = "Unloading Core took: " + IntToStr(timeGetTime() - st) + "ms";
				//Application->MessageBox(sMsg.c_str(), "Close down");
			}
		}
        else
        {
            Application->MessageBox
            (
                "TommyGun requires a Resolution of 800x600 or greater.\n"
                "Please Increase your Screen Resolution and try again\n"
                "The application will now exit.",
                "Screen Resolution Problem",
                MB_OK
            );
        }
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
    // HACK: To kill ourselves, so the CC3280MT.DLL will exit.
    HANDLE hHandle;
    DWORD dwExitCode = 0;
    hHandle = ::OpenProcess(PROCESS_ALL_ACCESS, 0, GetCurrentProcessId());
    ::GetExitCodeProcess(hHandle, &dwExitCode);
    ::TerminateProcess(hHandle, dwExitCode);
	return 0;
}
//---------------------------------------------------------------------------

