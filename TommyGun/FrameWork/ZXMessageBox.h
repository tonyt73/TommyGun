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
#ifndef ZXMessageBoxH
#define ZXMessageBoxH
//---------------------------------------------------------------------------
#include "fMessage.h"
//---------------------------------------------------------------------------
/**
 * @class ZXMessageBox
 * TommyGun Message box class. Displays more informative and user friendly messages. 
 */
//---------------------------------------------------------------------------
__declspec ( dllexport ) class ZXMessageBox
{
public:
            __fastcall  ZXMessageBox();
            __fastcall ~ZXMessageBox();

    void    __fastcall  ShowWindowsErrorMessage (const String& MsgTitle, const DWORD ErrorCode,    const String& File, const String& Function, int Line);
    void    __fastcall  ShowExceptionMessage    (const String& ExceptionMessage,                   const String& File, const String& Function, int Line);
    void    __fastcall  ShowLastExceptionMessage(const String& ExceptionMessagePrefix,             const String& File, const String& Function, int Line);
    void    __fastcall  ShowGeneralMessage      (const String& MsgTitle, const String& MsgProblem, const String& File, const String& Function, int Line);
    void    __fastcall  ShowExceptionMessage    (const AnsiString& OwnerOfException,const AnsiString& Vendor,DWORD AddressBase,DWORD Address,const AnsiString& Message,bool  bIsAPlugin = true);
    int     __fastcall  ShowMessage             (ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3);
};
extern bool bApplicationIsClosing;
//---------------------------------------------------------------------------
#endif//MessageBoxH
