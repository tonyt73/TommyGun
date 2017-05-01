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
#ifndef ZXTypesH
#define ZXTypesH
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace Interface
    {
        //-- INTERFACE HANDLES ------------------------------------------------------
        //
        // All handles are either signed or unsigned int's.
        //
        // Handles are used to identify items with the plugin environment.
        // They are NOT indexes into arrays, and you cannot assume they will be sequencial.
        // Handles are reallocated when they are freed back into the pool. So if you free
        // a handle, and keep a copy then the copy is invalid.
        //
        typedef          int TZX_EVENT;         /// Generic Event type
        typedef unsigned int TZX_HANDLE;        /// Generic Handle Type
        typedef HINSTANCE  TZX_HPLUGIN;         /// Plugin identification number

        /// Data pointer type ( Windows LPARAM data type )
        typedef LPARAM LPDATA;
    }
}
//---------------------------------------------------------------------------
#define FUNCTION_PREFIX HRESULT __declspec(dllexport) WINAPI
//---------------------------------------------------------------------------
#endif//ZXTypesH 
