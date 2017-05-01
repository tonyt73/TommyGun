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
#include "ZXGameEditor.h"
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
};
//---------------------------------------------------------------------------
// I don't normally do this, but I'm doing it for ease of use at the moment
extern ZXGameEditor* g_Plugin;
//---------------------------------------------------------------------------

