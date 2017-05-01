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
#include <vcl.h>
#include <windows.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <fstream>
#include "..\Logging\MessageLogger.h"
#include "ZXLogFile.h"
#include <Registry.hpp>
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Logging;
//- GLOBAL LOG FILE ---------------------------------------------------------
static ZXLogFile g_LogFile;
static int       g_bOpened = 0;
static bool      g_bOpenFiles = false;
static FILE*     g_Files[lfLast];
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the log files and message types
 * @author  Tony Thompson
 * @date    Created 13 June 2003
 */
//---------------------------------------------------------------------------
__fastcall ZXLogFile::ZXLogFile(bool bEraseFiles)
{
    g_bOpened++;
    if (g_bOpened == 1)
    {
        g_Files   [lfNone      ] = NULL;
        g_Files   [lfGeneral   ] = NULL;
        g_Files   [lfPlugin    ] = NULL;
        g_Files   [lfException ] = NULL;
        g_Files   [lfWindowsAPI] = NULL;

        m_LogFiles[lfNone      ] = "Failed Logs.log";
        m_LogFiles[lfGeneral   ] = "General.log";
        m_LogFiles[lfPlugin    ] = "Plugin.log";
        m_LogFiles[lfException ] = "Exception.log";
        m_LogFiles[lfWindowsAPI] = "WindowsAPI.log";

        m_MsgTypes[mtNone      ] = "          ";
        m_MsgTypes[mtInfo      ] = "Info      ";
        m_MsgTypes[mtDebug     ] = "Debug     ";
        m_MsgTypes[mtWarning   ] = "Warning   ";
        m_MsgTypes[mtError     ] = "Error     ";
        m_MsgTypes[mtException ] = "Exception ";

        String path = getenv("APPDATA");
        path += "\\TommyGun\\";

        if (true == bEraseFiles)
        {
            DeleteFile(path + m_LogFiles[lfGeneral   ]);
            DeleteFile(path + m_LogFiles[lfPlugin    ]);
            DeleteFile(path + m_LogFiles[lfException ]);
            DeleteFile(path + m_LogFiles[lfWindowsAPI]);
        }

        TRegistry *pRegistry = NULL;
        try
        {
            pRegistry = new TRegistry(KEY_READ);
            try
            {
                pRegistry->RootKey = HKEY_CURRENT_USER;
                pRegistry->OpenKey(NULL, false);
                if (true == pRegistry->OpenKey("\\Software\\Scorpio\\TommyGun\\States", false))
                {
                    try
                    {
                        if (pRegistry->ValueExists("UseLogFiles"))
                        {
                            g_bOpenFiles = pRegistry->ReadBool("UseLogFiles");
                        }
                    }
                    catch(ERegistryException&)
                    {
                    }
                }
            }
            __finally
            {
                pRegistry->CloseKey();
                delete pRegistry;
            }
        }
        catch(EOutOfMemory&)
        {
            pRegistry = NULL;
        }
        if (true == g_bOpenFiles)
        {
            if (g_bOpened == 1)
            {
                if (!DirectoryExists(path))
                {
                    CreateDir(path);
                }
                // open the log files
                AnsiString sFile;
                sFile = path + m_LogFiles[lfGeneral];
                g_Files[lfGeneral   ] = fopen(sFile.c_str(), "a");
                sFile = path + m_LogFiles[lfPlugin];
                g_Files[lfPlugin    ] = fopen(sFile.c_str(), "a");
                sFile = path + m_LogFiles[lfException];
                g_Files[lfException ] = fopen(sFile.c_str(), "a");
                sFile = path + m_LogFiles[lfWindowsAPI];
                g_Files[lfWindowsAPI] = fopen(sFile.c_str(), "a");
            }
        }
    }
}
//---------------------------------------------------------------------------
__fastcall ZXLogFile::~ZXLogFile()
{
    // we erased the log files, then we can close the log files too else skip closing them
    g_bOpened--;
    if (true == g_bOpenFiles && g_bOpened == 0)
    {
        if (g_Files[lfGeneral   ]) fclose(g_Files[lfGeneral   ]);
        if (g_Files[lfPlugin    ]) fclose(g_Files[lfPlugin    ]);
        if (g_Files[lfException ]) fclose(g_Files[lfException ]);
        if (g_Files[lfWindowsAPI]) fclose(g_Files[lfWindowsAPI]);
    }
}
//---------------------------------------------------------------------------
// Message
/**
 * Logs a message to a log file (and remote logger if its active)
 * @param   LogFile the log file to write the message to
 * @param   sMsg the message to log
 * @author  Tony Thompson
 * @date    Created 11 April 2002
 * @date    Modified 13 June 2003
            Moved into own class, from fShellHelpers.cpp
            Added support for different log files
            Added Message types
            Added Remote Logger support
 */
//---------------------------------------------------------------------------
void __fastcall ZXLogFile::Message(eLogFile LogFile, eMsgType MsgType, String sFunc, String sMessage)
{
    // is it a valid log file type?
    if (lfNone >= LogFile || LogFile >= lfLast)
    {
        // nope, so use the failed logs files
        LogFile = lfNone;
    }
    if (mtNone >= MsgType || MsgType >= mtLast)
    {
        // nope, so use the failed logs files
        MsgType = mtInfo;
    }
    if (mtInfo == MsgType)
    {
        RL_INFO(sMessage)
    }
    if (mtDebug == MsgType)
    {
        RL_DEBUG(sMessage)
    }
    if (mtWarning == MsgType)
    {
        RL_WARNING(sMessage)
    }
    if (mtError == MsgType)
    {
        RL_ERROR(sMessage)
    }
    if (mtException == MsgType)
    {
        RL_EXCEPTION(sMessage)
    }
    // get the current file handle
    FILE* fh = g_Files[LogFile];
    if (NULL != fh && lfNone != LogFile)
    {
        sFunc = sFunc + AnsiString::StringOfChar(' ', 32);
        sFunc = sFunc.SubString(1, 32);
        // output to the file
        String sMsg = TDateTime::CurrentDateTime().DateTimeString() + "|" + m_MsgTypes[MsgType] + "|" + sFunc + "|" + sMessage;
        fprintf(fh, "%s\n", sMsg.c_str());
        fflush(fh);
    }
}
//---------------------------------------------------------------------------
void WINAPI ZX_MESSAGE(Scorpio::Logging::eLogFile LogFile, Scorpio::Logging::eMsgType MsgType, String sFunc, String sMessage)
{
    g_LogFile.Message(LogFile, MsgType, sFunc, sMessage);    
}
//---------------------------------------------------------------------------

