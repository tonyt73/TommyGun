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
#include "..\..\..\Framework\FrameworkInterface.h"
//-- APP --------------------------------------------------------------------
#include "ZXTileType.h"
#include "ZXPlugin.h"
//---------------------------------------------------------------------------
// Functions exposed from the DLL
extern "C"
{
    HRESULT __declspec(dllexport) WINAPI Initialise     (ZXPlugin* pPlugin);
    HRESULT __declspec(dllexport) WINAPI Release        (void);
    HRESULT __declspec(dllexport) WINAPI Notify         (TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
    HRESULT __declspec(dllexport) WINAPI Flags          (DWORD& dwFlags);
    HRESULT __declspec(dllexport) WINAPI Signature      (String& sSignature);
    HRESULT __declspec(dllexport) WINAPI TypeSignature  (String& sSignature);
    HRESULT __declspec(dllexport) WINAPI SetPalettes    (TStrings* pPalettes, std::vector<String>& vSignatures);
};
//---------------------------------------------------------------------------
extern const String g_sTypeSignature;
//---------------------------------------------------------------------------

