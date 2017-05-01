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
#ifndef ZXLogFileH
#define ZXLogFileH
//-- SYSTEM -----------------------------------------------------------------
#include <stdio.h>
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
//- INCLUDES ----------------------------------------------------------------
#include <vector>
//- NAMESPACE ---------------------------------------------------------------
namespace Scorpio
{
    namespace Logging
    {
        //- LOG FILE TYPES ----------------------------------------------------------
        enum eLogFile { lfNone = 0, lfGeneral, lfPlugin , lfException, lfWindowsAPI,              lfLast, lfForceEnumSize = 0xFFFFFFFF };
        enum eMsgType { mtNone = 0, mtInfo   , mtDebug  , mtWarning  , mtError     , mtException, mtLast, mtForceEnumSize = 0xFFFFFFFF };
        //---------------------------------------------------------------------------
        // TODO: This should be a singleton class
        //---------------------------------------------------------------------------
        __declspec ( dllexport) class ZXLogFile
        {
        private:
            bool                m_bErasedFiles;
            String              m_LogFiles[lfLast];
            String              m_MsgTypes[mtLast];
        public:
                    __fastcall  ZXLogFile(bool bEraseFiles = false);
                    __fastcall ~ZXLogFile();

            void    __fastcall  Message(eLogFile LogFile, eMsgType MsgType, String sFunc, String sMessage);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
void __declspec(dllexport) WINAPI ZX_MESSAGE(Scorpio::Logging::eLogFile LogFile, Scorpio::Logging::eMsgType MsgType, String sFunc, String sMessage);
//---------------------------------------------------------------------------
#define ZX_LOG(a, b, c)         ZX_MESSAGE(a, b                   , __FUNC__, String(c));
#define ZX_LOG_INFO(a, c)       ZX_MESSAGE(a, Logging::mtInfo     , __FUNC__, String(c));
#define ZX_LOG_DEBUG(a, c)      ZX_MESSAGE(a, Logging::mtDebug    , __FUNC__, String(c));
#define ZX_LOG_WARNING(a, c)    ZX_MESSAGE(a, Logging::mtWarning  , __FUNC__, String(c));
#define ZX_LOG_ERROR(a, c)      ZX_MESSAGE(a, Logging::mtError    , __FUNC__, String(c));
#define ZX_LOG_EXCEPTION(a, c)  ZX_MESSAGE(a, Logging::mtException, __FUNC__, String(c));
//---------------------------------------------------------------------------
//__declspec ( dllexport) extern Scorpio::Logging::ZXLogFile g_LogFile;
//---------------------------------------------------------------------------
#endif
