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
#include "SevenuPImageParserPlugin.h"
//---------------------------------------------------------------------------
// Functions exposed from the DLL
extern "C"
{
    HRESULT __declspec(dllexport) WINAPI Initialise     (ZXPlugin* pPlugin);
    HRESULT __declspec(dllexport) WINAPI Release        (void);
    HRESULT __declspec(dllexport) WINAPI Notify         (TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
    HRESULT __declspec(dllexport) WINAPI Flags          (DWORD& dwFlags);
    HRESULT __declspec(dllexport) WINAPI Signature      (String& sSignature);

    // ImageFormat Plugin interfaces
    HRESULT __declspec(dllexport) WINAPI GetOptionsPanel (TPanel*& Panel);
    HRESULT __declspec(dllexport) WINAPI GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types);
    HRESULT __declspec(dllexport) WINAPI GetListOfResources(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources);
    HRESULT __declspec(dllexport) WINAPI ParseResources  (KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData);
    HRESULT __declspec(dllexport) WINAPI GetDescription  (String& sSignature);
};
//---------------------------------------------------------------------------

