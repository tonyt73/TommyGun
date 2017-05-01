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
#ifndef fMessageH
#define fMessageH
//-- SYSTEM -----------------------------------------------------------------
#include <stdio.h>
#include <dos.h>
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
//#include "pngimage.hpp"
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
typedef enum { mbbOk   , mbbOkCancel, mbbYesNoCancel              } ZXMessageBoxButtons;
#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES
typedef enum { mbtError, mbtWarning , mbtInformation, mbtQuestion } ZXMessageBoxType;
#endif
//---------------------------------------------------------------------------
__declspec (dllexport) class TfrmMessage : public TForm
{
__published:	// IDE-managed Components
    TPanel *panMessageHeader;
    TLabel *lblMessageTitle;
    TLabel *lblShortMessage;
    TBevel *bvlMessageTop;
    TImage *imgError;
    TImage *imgWarning;
    TImage *imgQuestion;
    TImage *imgInformation;
    TLabel *lblLongMessage;
    TBevel *bvlMessageBottom;
    TButton *cmdButton1;
    TButton *cmdButton2;
    TButton *cmdButton3;
    TButton *cmdHelp;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TImage *imgMessageIcon;

    void __fastcall cmdButton1Click(TObject *Sender);

private:	// User declarations

    int                         m_iResponse;
    int                         m_iNextMessageID;

    void            __fastcall  CheckButton(TButton* Button);

public:		// User declarations

    int             __fastcall  Show(unsigned int      Type,
                                     const AnsiString& Title,
                                     const AnsiString& ShortMsg,
                                     const AnsiString& LongMsg,
                                     const AnsiString& Button1,
                                     const AnsiString& Button2,
                                     const AnsiString& Button3);

    void            __fastcall  Remove(unsigned int MessageID);

    void            __fastcall  ShowException(
                                    const AnsiString& OwnerOfException,
                                    const AnsiString& Vendor,
                                    DWORD AddressBase,
                                    DWORD Address,
                                    const AnsiString& Message,
                                    bool  bIsAPlugin = true );

    void            __fastcall  ShowException(
                                    const AnsiString& ExceptionMessage,
                                    const String& File,
                                    const String& Function,
                                    int   Line);

    void            __fastcall  ShowWindowsMessage(
                                    const AnsiString& Title,
                                    const DWORD ErrorCode,
                                    const String& File,
                                    const String& Function,
                                    int   Line);

    void            __fastcall  ShowGeneralMessage(
                                    const AnsiString& Title,
                                    const AnsiString& Problem,
                                    const String& File,
                                    const String& Function,
                                    int   Line);

    int             __fastcall  Post(unsigned int MessageID);

                    __fastcall  TfrmMessage(TComponent* Owner);
                    __fastcall ~TfrmMessage();
};
//---------------------------------------------------------------------------
//extern PACKAGE TfrmMessage *frmMessage;
//---------------------------------------------------------------------------
#endif
