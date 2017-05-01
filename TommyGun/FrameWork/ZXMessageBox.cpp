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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const int g_iExceptionBufferSize = 1024;
const String g_sVCLExceptionMsg  = "VCL Exception: ";
const String g_sCppExceptionMsg  = "Windows/C++ Exception caught";
const String g_sDash             = " - ";
const String g_sNewLine          = "\n";
const String g_sNoResources1     = "Exception Caught and no resources available to report it\nFile:";
const String g_sErrorCode        = "ErrorCode: ";
const String g_sFile             = "\nFile:";
const String g_sFunction         = "\nFunction:";
const String g_sLine             = "\Line:";
//---------------------------------------------------------------------------
extern bool bApplicationIsClosing = false;
//---------------------------------------------------------------------------
__fastcall ZXMessageBox::ZXMessageBox()
{
}
//---------------------------------------------------------------------------
__fastcall ZXMessageBox::~ZXMessageBox()
{
}
//---------------------------------------------------------------------------
// ShowWindowsErrorMessage
/**
 * Displays a Windows Error message for the LastError() function
 * @param   MsgTitle    The title of the message window
 * @author  Tony Thompson
 * @date    Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXMessageBox::ShowWindowsErrorMessage( const String& MsgTitle, const DWORD ErrorCode, const String& File, const String& Function, int Line )
{
    if (bApplicationIsClosing) return;
    TfrmMessage* frmMessage = new TfrmMessage(NULL);
    if (true == SAFE_PTR(frmMessage))
    {
        frmMessage->ShowWindowsMessage( MsgTitle, ErrorCode, File, Function, Line );
        SAFE_DELETE(frmMessage);
    }
    else
    {
        // show a windows message box, that already has resources allocated
        ::ShowMessage( MsgTitle + g_sNewLine + g_sErrorCode + IntToStr(ErrorCode) + g_sFile + File + g_sFunction + Function + g_sLine + IntToStr(Line));
    }
}
//---------------------------------------------------------------------------
// ShowExceptionMessage
/**
 * Displays a Windows Error message for the LastError() function
 * @param   MsgTitle    The title of the message window
 * @author  Tony Thompson
 * @date    Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXMessageBox::ShowExceptionMessage( const String& ExceptionMessage, const String& File, const String& Function, int Line )
{
    /*
    TODO: Investigate this function. It causes exception handling to stop working.
    Maybe this library should be integrated into the shell core.dll*/
    TfrmMessage* frmMessage = new TfrmMessage(NULL);
    if (true == SAFE_PTR(frmMessage))
    {
        frmMessage->ShowException( ExceptionMessage, File, Function, Line );
        SAFE_DELETE(frmMessage);
    }
    else
    {
        ShowException(ExceptObject(), ExceptAddr());
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXMessageBox::ShowExceptionMessage(const AnsiString& OwnerOfException,const AnsiString& Vendor,DWORD AddressBase,DWORD Address,const AnsiString& Message,bool  bIsAPlugin)
{
    if (bApplicationIsClosing) return;
    TfrmMessage* frmMessage = new TfrmMessage(NULL);
    //TfrmMessage* frmMessage = new TfrmMessage(NULL);
    if (true == SAFE_PTR(frmMessage))
    {
        frmMessage->ShowException(OwnerOfException, Vendor, AddressBase, Address, Message, bIsAPlugin);
        SAFE_DELETE(frmMessage);
    }
}
//---------------------------------------------------------------------------
// ShowGeneralMessage
/**
 * Displays a General Error message
 * @param   MsgTitle    The title of the message window
 * @param   MsgTitle    The title of the message window
 * @author  Tony Thompson
 * @date    Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXMessageBox::ShowGeneralMessage( const String& MsgTitle, const String& MsgProblem, const String& File, const String& Function, int Line )
{
    if (bApplicationIsClosing) return;
    TfrmMessage* frmMessage = new TfrmMessage(NULL);
    if (true == SAFE_PTR(frmMessage))
    {
        frmMessage->ShowGeneralMessage( MsgTitle, MsgProblem, File, Function, Line );
        SAFE_DELETE(frmMessage);
    }
    else
    {
        // show a windows message box, that already has resources allocated
        ::ShowMessage( MsgTitle + g_sNewLine + MsgProblem + g_sFile + File + g_sFunction + Function + g_sLine + IntToStr(Line));
    }
}
//---------------------------------------------------------------------------
// ShowLastExceptionMessage
/**
 * Displays a Windows Error message for the last exception that occurred
 * @param   MsgTitle    The title of the message window
 * @author  Tony Thompson
 * @date    Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXMessageBox::ShowLastExceptionMessage( const String& ExceptionMessagePrefix, const String& File, const String& Function, int Line )
{
    if (bApplicationIsClosing) return;
    AnsiString Msg;
    char* charBuffer = (char*)malloc( g_iExceptionBufferSize + 1 );

    if (true == SAFE_PTR(charBuffer))
    {
        ZeroMemory( charBuffer, g_iExceptionBufferSize + 1 );

        // construct a message of the last exception
        TObject* exceptObj  = ExceptObject();
        void*    exceptAddr = ExceptAddr();

        if (true == SAFE_PTR(exceptObj))
        {
            ExceptionErrorMessage( exceptObj, exceptAddr, charBuffer, g_iExceptionBufferSize );
            Msg = charBuffer;
            Msg = g_sVCLExceptionMsg + Msg;
        }
        else
        {
            Msg = g_sCppExceptionMsg;
        }

        //TfrmMessage* frmMessage = new TfrmMessage(Application);
        TfrmMessage* frmMessage = new TfrmMessage(NULL);
        if (true == SAFE_PTR(frmMessage))
        {
            frmMessage->ShowException( ExceptionMessagePrefix + g_sDash + Msg, File, Function, Line );
            SAFE_DELETE(frmMessage);
        }
        else
        {
            // show a windows message box, that already has resources allocated
            ::ShowMessage( g_sNoResources1 + File + g_sFunction + Function + g_sLine + IntToStr(Line));
        }
        free(charBuffer);
    }
    else
    {
        ::ShowMessage( g_sNoResources1 + File + g_sFunction + Function + g_sLine + IntToStr(Line));
    }
}
//---------------------------------------------------------------------------
int __fastcall ZXMessageBox::ShowMessage(ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3)
{
    if (bApplicationIsClosing) return 0;
    int iResult = -1;

    //TfrmMessage* frmMessage = new TfrmMessage(Application);
    TfrmMessage* frmMessage = new TfrmMessage(NULL);
    if (true == SAFE_PTR(frmMessage))
    {
        iResult = frmMessage->Show(eType, sTitle, sBrief, sDetails, sButton1, sButton2, sButton3);
        SAFE_DELETE(frmMessage);
    }
    return iResult;
}
//---------------------------------------------------------------------------

