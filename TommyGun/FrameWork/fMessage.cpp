#pragma link "pngimage"
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
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
//TfrmMessage *frmMessage = NULL;
//---------------------------------------------------------------------------
static bool g_bShowingMessage = false;

const String sNewLine               = "\n";
const String sSlash                 = "/";
const String sColon                 = ":";
const String sFileMode              = "a+";
const String g_sMsgBoxBLANK         = "";

const String sVendorScorpio         = "KiwiWare";
const String sShellOwner            = "TommyGun Shell Environment";

const String sExceptionLog          = "Exception.log";
const String sScorpioLog            = "Errors.log";
const String sWindowsLog            = "WindowsAPI.log";

const int iNoResponse = -1;
//-- Message Box Strings ----------------------------------------------------
const String g_sMsgBoxOK            = "OK";
const String g_sMsgBoxCANCEL        = "Cancel";
const String g_sMsgBoxYES           = "Yes";
const String g_sMsgBoxNO            = "No";
//-- Messages ---------------------------------------------------------------
const String g_sTrappedException    = "TommyGun has Trapped an Exception";
const String g_sTrappedExceptionBrief="TommyGun has caused an Exception";
const String g_sTrappedExceptionLong= "TommyGun has caused an Exception and has trapped the Exception properly.\n"
                                      "A log file has been created in the applications directory [exception.log], that has the details of the exception.\n"
                                      "Please send the Exception.Log file to TommyGun.IDE@gmail.com\n"
                                      "\nClick,\n\tOK\t\tto Continue\n\tTerminate\tto Quit TommyGun";


const String g_sExceptionTitle      = "TommyGun caught an unhandled exception form within a Plugin";
const String g_sExceptionLong1      = "TommyGun has caught an exception from within ";
const String g_sExceptionLong2      = ". The Plugin will now be unloaded.\nThe Vendor of the component is ";
const String g_sExceptionLong3      = "\nA log file has been created in the applications directory [exception.log], that has the details of the exception.\n"
                                      "Please send the Exception.Log file to TommyGun.IDE@gmail.com\n"
                                      "\nClick,\n\tOK\t\tto Unload the Plugin and Continue\n\tTerminate\tto Quit TommyGun";

const String g_sExceptionTitle2     = "TommyGun has caused an Unhandled Exception";
const String g_sExceptionLong4      = "TommyGun has caused an Exception and has failed to handle the Exception properly.\n"
                                      "A log file has been created in the applications directory [exception.log], that has the details of the exception.\n"
                                      "Please send the Exception.Log file to TommyGun.IDE@gmail.com\n"
                                      "\nClick,\n\tOK\t\tto Continue\n\tTerminate\tto Quit TommyGun";

const String g_sUntrappedException  = "TommyGun has caught an Unhandled Exception";
const String g_sWindowLong1         = "A Windows API call returned a failed error code [0x";
const String g_sWindowLong2         = "].\nThis translates to:\n";
const String g_sWindowLong3         = "A log file has been produced [windowsapi.log]\n\nClick\n\tOK to continue";
const String g_sWindowLong4         = ".\nSorry, TommyGun was unable to translate the message.\n\n"
                                      "A log file has been produced [windowsapi.log]\n\n"
                                      "Click\n\tOK to continue";

const String g_sGeneralMsg          = "\n\nA log file was produced [General.log]\nPlease send the file to TommyGun.IDE@gmail.com.\n\nClick,\n\tOK\tto Continue";

const String g_sScorpioError         = "TommyGun Error Message";
const String g_sWindowsAPIFailure   = "Windows API Failure";
const String g_sNoConvert           = "Unable to convert Windows Code to Message.\n";
//-- Log File Strings -------------------------------------------------------
const String g_sTypeError           = "Error:";
const String g_sTypeWarning         = "Warning: ";
const String g_sTypeInformation     = "Information: ";
const String g_sTypeQuestion        = "Question: ";

const String g_sTrappedExceptMsg    = "Trapped Exception  ";
const String g_sUntrappedExceptMsg  = "Untrapped Exception";
const String g_sMsgDateTime         = "Error Date/Time  : ";
const String g_sProgramMessage      = "Program Message  : ";
const String g_sErrorMessage        = "ErrorMessage     : ";
const String g_sErrorCode           = "ErrorCode        : ";
const String g_sFile                = "File             : ";
const String g_sFunction            = "Function         : ";
const String g_sLine                = "Line             : ";
const String g_sVendor              = "Vendor           : ";
const String g_sOwner               = "Owner            : ";
const String g_sExceptionMessage    = "Exception Message: ";
const String g_sBaseAddress         = "Base Address     : ";
const String g_sExceptionAddress    = "Exception Address: ";
const String g_sExceptionOffset     = "Exception Offset : ";
//---------------------------------------------------------------------------
__fastcall TfrmMessage::TfrmMessage(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TfrmMessage::~TfrmMessage()
{
}
//---------------------------------------------------------------------------
int __fastcall TfrmMessage::Show(unsigned int Type, const AnsiString& Title, const AnsiString& ShortMsg, const AnsiString& LongMsg, const AnsiString& Button1, const AnsiString& Button2, const AnsiString& Button3)
{
    lblMessageTitle->Caption = Title;
    lblShortMessage->Caption = ShortMsg;
    lblLongMessage->Caption  = LongMsg;

    cmdButton1->Caption = "&" + Button1;
    cmdButton2->Caption = "&" + Button2;
    cmdButton3->Caption = "&" + Button3;
    cmdButton2->Visible = Button2 != g_sMsgBoxBLANK;
    cmdButton3->Visible = Button3 != g_sMsgBoxBLANK;

    CheckButton( cmdButton3 );
    CheckButton( cmdButton2 );
    CheckButton( cmdButton1 );

    imgError->Visible = false;
    imgWarning->Visible = false;
    imgInformation->Visible = false;
    imgQuestion->Visible = false;

    imgError->Visible = ( mbtError == Type );
    imgWarning->Visible = ( mbtWarning == Type );
    imgInformation->Visible = ( mbtInformation == Type );
    imgQuestion->Visible = ( mbtQuestion == Type );

    if (false == Visible && false == g_bShowingMessage)
    {
        g_bShowingMessage = true;
        ShowModal( );
        g_bShowingMessage = false;
    }

    return m_iResponse;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::ShowException( const AnsiString& ExceptionMessage, const String& File, const String& Function, int Line )
{
    lblMessageTitle->Caption = g_sTrappedException;

    lblShortMessage->Caption = g_sTrappedExceptionBrief;
    lblLongMessage->Caption  = g_sTrappedExceptionLong;

    String vendor = sVendorScorpio;

    // log the exception to Exception.log
    AnsiString LogFile = AnsiString(getenv("APPDATA")) + "\\TommyGun\\" + sExceptionLog;

    FILE* fhFile = fopen( LogFile.c_str(), sFileMode.c_str() );

    if ( NULL != fhFile )
    {
        struct date d;
        struct time t;

        getdate( &d );
        gettime( &t );

        String sDateTime = IntToStr( d.da_day ) + sSlash + IntToStr( d.da_mon ) + sSlash + IntToStr( d.da_year ) + "  " +
                           IntToStr( t.ti_hour) + sColon + IntToStr( t.ti_min ) + sColon + IntToStr( t.ti_sec  );

        String Msg =  g_sTrappedExceptMsg     +
                      g_sMsgDateTime          + sDateTime        + sNewLine +
                      g_sVendor               + vendor           + sNewLine +
                      g_sExceptionMessage     + ExceptionMessage + sNewLine +
                      g_sFile                 + File             + sNewLine +
                      g_sFunction             + Function         + sNewLine +
                      g_sLine                 + Line             + sNewLine + sNewLine;

        fprintf(fhFile, Msg.c_str());
        fclose(fhFile);
    }

    cmdButton1->Caption = g_sMsgBoxOK;
    cmdButton2->Caption = g_sMsgBoxBLANK;
    cmdButton3->Caption = g_sMsgBoxBLANK;
    cmdButton2->Caption = "Terminate";
    //cmdButton3->Caption = "Help";
    cmdButton2->Visible = true;
    cmdButton3->Visible = false;

    CheckButton( cmdButton3 );
    CheckButton( cmdButton2 );
    CheckButton( cmdButton1 );

    imgError->Visible = true;
    imgWarning->Visible = false;
    imgInformation->Visible = false;
    imgQuestion->Visible = false;

    if (false == Visible && false == g_bShowingMessage)
    {
        g_bShowingMessage = true;
        ShowModal( );
        if (m_iResponse == 1)
        {
            Application->Terminate();
        }
        g_bShowingMessage = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::ShowException( const AnsiString& OwnerOfException, const AnsiString& Vendor, DWORD AddressBase, DWORD Address, const AnsiString& Message, bool bIsAPlugin )
{
    lblMessageTitle->Caption = g_sUntrappedException;

    String owner  = OwnerOfException;
    String vendor = Vendor;

    if ( true == bIsAPlugin )
    {
        lblShortMessage->Caption = g_sExceptionTitle;
        lblLongMessage->Caption  = g_sExceptionLong1 + owner +
                                   g_sExceptionLong2 + vendor + sNewLine +
                                   g_sExceptionLong3;
    }
    else
    {
        lblShortMessage->Caption = g_sExceptionTitle2;
        lblLongMessage->Caption  = g_sExceptionLong4;

        owner  = sShellOwner;
        vendor = sVendorScorpio;
    }

    // log the exception to Exception.log
    AnsiString LogFile = AnsiString(getenv("APPDATA")) + "\\TommyGun\\" + sExceptionLog;

    FILE* fhFile = fopen( LogFile.c_str(), sFileMode.c_str() );

    if ( NULL != fhFile )
    {
        struct date d;
        struct time t;

        getdate( &d );
        gettime( &t );

        String sDateTime = IntToStr( d.da_day ) + sSlash + IntToStr( d.da_mon ) + sSlash + IntToStr( d.da_year ) + "  " +
                           IntToStr( t.ti_hour) + sColon + IntToStr( t.ti_min ) + sColon + IntToStr( t.ti_sec  );

        DWORD Offset = Address - AddressBase;

        String Msg =  g_sUntrappedExceptMsg   +
                      g_sMsgDateTime          + sDateTime                                   + sNewLine +
                      g_sOwner                + owner                                       + sNewLine +
                      g_sVendor               + vendor                                      + sNewLine +
                      g_sExceptionMessage     + Message                                     + sNewLine +
                      g_sBaseAddress          + IntToHex( static_cast<int>(AddressBase),8 ) + sNewLine +
                      g_sExceptionAddress     + IntToHex( static_cast<int>(Address    ),8 ) + sNewLine +
                      g_sExceptionOffset      + IntToHex( static_cast<int>(Offset     ),8 ) + sNewLine + sNewLine;

        fprintf( fhFile, Msg.c_str( ) );
        fclose( fhFile );
    }

    cmdButton1->Caption = g_sMsgBoxOK;
    cmdButton2->Caption = g_sMsgBoxBLANK;
    cmdButton3->Caption = g_sMsgBoxBLANK;
    cmdButton2->Caption = "Terminate";
    //cmdButton3->Caption = "Help";
    cmdButton2->Visible = true;
    cmdButton3->Visible = false;

    CheckButton( cmdButton3 );
    CheckButton( cmdButton2 );
    CheckButton( cmdButton1 );

    imgError->Visible = true;
    imgWarning->Visible = false;
    imgInformation->Visible = false;
    imgQuestion->Visible = false;

    if (false == Visible && false == g_bShowingMessage)
    {
        g_bShowingMessage = true;
        ShowModal( );
        if (m_iResponse == 1)
        {
            Application->Terminate();
        }
        g_bShowingMessage = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::ShowWindowsMessage( const AnsiString& Title, const DWORD ErrorCode, const String& File, const String& Function, int Line )
{
    bool bValidWindowsMessage = true;
    LPVOID lpMsgBuf = NULL;
    AnsiString WindowsMessage = g_sNoConvert;

    try
    {
        DWORD MsgLength = 0;

        // convert the message to Window MessageID to Window Speak!
        MsgLength = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            ErrorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            reinterpret_cast<LPTSTR>(&lpMsgBuf),
            0,
            NULL
        );

        if ( 0 == MsgLength )
        {
            bValidWindowsMessage = false;
        }
    }
    catch(...)
    {
        bValidWindowsMessage = false;
    }

    if ( true == bValidWindowsMessage )
    {
        // move the message to an AnsiString
        WindowsMessage = ( reinterpret_cast<char*>(lpMsgBuf) );

        // Free the buffer.
        LocalFree( lpMsgBuf );
    }

    lblMessageTitle->Caption = Title;
    lblShortMessage->Caption = g_sWindowsAPIFailure;

    if ( true == bValidWindowsMessage )
    {
        lblLongMessage->Caption = g_sWindowLong1 + IntToHex( static_cast<int>(ErrorCode),4 ) +
                                  g_sWindowLong2 + WindowsMessage + sNewLine + sNewLine +
                                  g_sWindowLong3;
    }
    else
    {
        lblLongMessage->Caption = g_sWindowLong1 + IntToHex( static_cast<int>(ErrorCode),4 ) +
                                  g_sWindowLong4;
    }

    // log the message to WindowsAPI.log
    AnsiString WindowsLogFile = AnsiString(getenv("APPDATA")) + "\\TommyGun\\" + sWindowsLog;

    FILE* fhFile = fopen( WindowsLogFile.c_str(), sFileMode.c_str() );

    if ( NULL != fhFile )
    {
        struct date d;
        struct time t;

        getdate( &d );
        gettime( &t );

        String sDateTime = IntToStr( d.da_day ) + sSlash + IntToStr( d.da_mon ) + sSlash + IntToStr( d.da_year ) + "  " +
                           IntToStr( t.ti_hour) + sColon + IntToStr( t.ti_min ) + sColon + IntToStr( t.ti_sec  );

        String Msg =  g_sMsgDateTime          + sDateTime                                 + sNewLine +
                      g_sErrorCode            + IntToHex( static_cast<int>(ErrorCode),4 ) + sNewLine +
                      g_sErrorMessage         + WindowsMessage                            +
                      g_sProgramMessage       + Title                                     + sNewLine +
                      g_sFile                 + File                                      + sNewLine +
                      g_sFunction             + Function                                  + sNewLine +
                      g_sLine                 + IntToStr( Line )                          + sNewLine + sNewLine;

        fprintf( fhFile, Msg.c_str( ) );
        fclose( fhFile );
    }

    cmdButton1->Caption = g_sMsgBoxOK;
    cmdButton2->Caption = g_sMsgBoxBLANK;
    cmdButton3->Caption = g_sMsgBoxBLANK;
    cmdButton2->Visible = false;
    cmdButton3->Visible = false;

    CheckButton( cmdButton3 );
    CheckButton( cmdButton2 );
    CheckButton( cmdButton1 );

    imgError->Visible = true;
    imgWarning->Visible = false;
    imgInformation->Visible = false;
    imgQuestion->Visible = false;

#ifdef _DEBUG   // only show the message dislog if we are in debug mode
    if (false == Visible && false == g_bShowingMessage)
    {
        g_bShowingMessage = true;
        ShowModal( );
        if (m_iResponse == 1)
        {
            Application->Terminate();
        }
        g_bShowingMessage = false;
    }
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::ShowGeneralMessage(const AnsiString& Title,const AnsiString& Problem,const String& File,const String& Function,int   Line )
{
    lblMessageTitle->Caption = Title;
    lblShortMessage->Caption = g_sScorpioError;

    lblLongMessage->Caption = Problem + g_sGeneralMsg;

    // log the message to WindowsAPI.log
    AnsiString WindowsLogFile = AnsiString(getenv("APPDATA")) + "\\TommyGun\\" + sScorpioLog;

    FILE* fhFile = fopen( WindowsLogFile.c_str(), sFileMode.c_str() );

    if ( NULL != fhFile )
    {
        struct date d;
        struct time t;

        getdate( &d );
        gettime( &t );

        String sDateTime = IntToStr( d.da_day ) + sSlash + IntToStr( d.da_mon ) + sSlash + IntToStr( d.da_year ) + "  " +
                           IntToStr( t.ti_hour) + sColon + IntToStr( t.ti_min ) + sColon + IntToStr( t.ti_sec  );

        String Msg =  g_sMsgDateTime          + sDateTime        + sNewLine +
                      g_sProgramMessage       + Title            + sNewLine +
                      g_sErrorMessage         + Problem          + sNewLine +
                      g_sFile                 + File             + sNewLine +
                      g_sFunction             + Function         + sNewLine +
                      g_sLine                 + IntToStr( Line ) + sNewLine + sNewLine;

        fprintf( fhFile, Msg.c_str( ) );
        fclose( fhFile );
    }

    cmdButton1->Caption = g_sMsgBoxOK;
    cmdButton2->Caption = g_sMsgBoxBLANK;
    cmdButton3->Caption = g_sMsgBoxBLANK;
    cmdButton2->Visible = false;
    cmdButton3->Visible = false;

    CheckButton( cmdButton3 );
    CheckButton( cmdButton2 );
    CheckButton( cmdButton1 );

    imgError->Visible = true;
    imgWarning->Visible = false;
    imgInformation->Visible = false;
    imgQuestion->Visible = false;

    if (false == Visible && false == g_bShowingMessage)
    {
        g_bShowingMessage = true;
        ShowModal( );
        g_bShowingMessage = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::CheckButton(TButton* Button)
{
    AnsiString sCaption = Button->Caption;
    sCaption = sCaption.LowerCase( );

    Button->Default  = ( sCaption == g_sMsgBoxOK.LowerCase()     ) | ( sCaption == g_sMsgBoxYES.LowerCase() );
    Button->Cancel   = ( sCaption == g_sMsgBoxCANCEL.LowerCase() ) | ( sCaption == g_sMsgBoxNO.LowerCase()  );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMessage::cmdButton1Click(TObject *Sender)
{
    m_iResponse = static_cast<TSpeedButton*>(Sender)->Tag;
    ModalResult = mrOk;
    Close( );
}
//---------------------------------------------------------------------------



