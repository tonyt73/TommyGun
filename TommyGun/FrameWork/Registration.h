//---------------------------------------------------------------------------
#ifndef RegistrationH
#define RegistrationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "IdExplicitTLSClientServerBase.hpp"
#include "IdSMTPBase.hpp"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdMessageClient.hpp>
#include <IdSMTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdMessage.hpp>
#include "IdSSL.hpp"
#include <IdServerIOHandler.hpp>
#include <IdSSLOpenSSL.hpp>
#include "IdIOHandlerStack.hpp"
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include "IdSASL.hpp"
#include "IdSASLLogin.hpp"
#include "IdSASLPlain.hpp"
#include "IdSASLUserPass.hpp"
#include "IdUserPassProvider.hpp"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class TRegistrationThread : public TThread
{
    private:
        TIdSMTP* m_Smtp;
        TIdMessage* m_Message;

    protected:
        void __fastcall Execute();

    public:
        __fastcall TRegistrationThread(TIdSMTP* smtp, TIdMessage* message);
        __fastcall ~TRegistrationThread();
};
//---------------------------------------------------------------------------
#endif
