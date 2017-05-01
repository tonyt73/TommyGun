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
 The KiwiWare Plugin Interface Definition
---------------------------------------------------------------------------*/
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
//-- APP --------------------------------------------------------------------
#include "ZXImage.h"
#include "ZXImageEditor.h"
#include "ZXImageManager.h"
#include "ZXPlugin.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Plugin;
//---------------------------------------------------------------------------
// Functions exposed from the DLL
extern "C"
{
    HRESULT __declspec(dllexport) WINAPI Initialise             (ZXPlugin* pPlugin);
    HRESULT __declspec(dllexport) WINAPI Release                (void);
    HRESULT __declspec(dllexport) WINAPI Notify                 (TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg);
    HRESULT __declspec(dllexport) WINAPI Flags                  (DWORD& dwFlags);

    // Plugin Interfaces for all Mini-Plugins
    HRESULT __declspec(dllexport) WINAPI IERegisterPluginEvent  (TZX_HPLUGIN PluginHandle, TZX_EVENT Event);
    HRESULT __declspec(dllexport) WINAPI IENotify               (TZX_HPLUGIN PluginHandle, TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg);
    // Interfaces for All Mini-Plugins
    HRESULT __declspec(dllexport) WINAPI SystemUpdateImage      (TZX_HPLUGIN PluginHandle, ZXImage* Image);    // refresh the selected image
    HRESULT __declspec(dllexport) WINAPI SystemRefreshView      (TZX_HPLUGIN PluginHandle);    // refresh the current image
    HRESULT __declspec(dllexport) WINAPI SystemAddToolBar       (TZX_HPLUGIN PluginHandle, TToolBar*  ToolBar);    // add a toolbar to the main toolbars show/hide when appropreiate
    HRESULT __declspec(dllexport) WINAPI SystemMessageBox       (ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3, int& iAnswer );
    // Interfaces for Tool Mini-Plugins
    HRESULT __declspec(dllexport) WINAPI ToolMergePaintToolBar  (TZX_HPLUGIN PluginHandle, TToolBar* ToolBar);
    // Interfaces for Type Mini-Plugins
    HRESULT __declspec(dllexport) WINAPI TypeAddTab             (TZX_HPLUGIN PluginHandle, const String& sCaption, Graphics::TBitmap* pBitmap, TTabSheet*& pTabSheet);
    HRESULT __declspec(dllexport) WINAPI TypeGetImageManager    (TZX_HPLUGIN PluginHandle, ZXImageManager*& pImageManager);
    HRESULT __declspec(dllexport) WINAPI TypeSelectImage        (TZX_HPLUGIN PluginHandle, const String& sOwner, int iIndex, int iFrame);
    // Interfaces for Image Mini-Plugins
    HRESULT __declspec(dllexport) WINAPI ImageGetCurrent        (TZX_HPLUGIN PluginHandle, ZXImage*& pImage);
};
//---------------------------------------------------------------------------
// I don't normally do this, but I'm doing it for ease of use at the moment
extern ZXImageEditor* g_Plugin;
//---------------------------------------------------------------------------

