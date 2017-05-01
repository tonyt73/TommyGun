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
#include "MessageLogger.h"
#include <mmsystem.h>
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma package(smart_init)
#endif
//---------------------------------------------------------------------------
#ifdef USE_REMOTE_LOGGING
//---------------------------------------------------------------------------
static char* g_sMailSlot = "\\\\.\\mailslot\\Scorpio\\RemoteLogger\\LogSlot";
const String g_sRootKeyString = "\\Software\\Scorpio\\RemoteLogger\\";
//---------------------------------------------------------------------------
/** Constructor
 * @brief   Initializes the class, and retrieves the computer and user names
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
TZXMessageLogger::TZXMessageLogger()
: m_LoggerHWND(NULL),
  m_MinType(ltNone),
  m_MinLevel(llNone),
  m_iGroupSize(10),
  m_sComputerName(""),
  m_sUserName(""),
  m_sMessages(""),
  m_Registry(NULL)
{
	// create a character buffer
    DWORD dwSize = 4096;
    char  cName[4096];
    // find computers the name
    GetComputerName(cName, &dwSize);
    String sComputerName(cName);
    m_sComputerName = sComputerName;
    // find users the name
    GetUserName(cName, &dwSize);
    String sUserName(cName);
    m_sUserName = sUserName;

    try
    {
        //m_Registry = new RRegistry(NULL);
        m_Registry = new TRegistry;
        if (NULL != m_Registry)
        {
            m_Registry->RootKey = HKEY_LOCAL_MACHINE;
            //m_Registry->RootKey = HKEY_CURRENT_USER;
            m_Registry->OpenKey(NULL, false);
            m_Registry->OpenKey(g_sRootKeyString, true);
        }
    }
    catch(...)
    {
        delete m_Registry;
    }
}
//---------------------------------------------------------------------------
/** Destructor
 * @brief   Flushs the log cache
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
TZXMessageLogger::~TZXMessageLogger()
{
    FlushLog();
    if (NULL != m_Registry)
    {
        m_Registry->CloseKey();
    }
    delete m_Registry;
}
//---------------------------------------------------------------------------
/** Log
 * @brief   Logs a message. Sends the message to the Remote Logger application
 * @param   eType           type of log message
 * @param   eLevel          level of the log message
 * @param   sSource         the source of the log message
 * @param   sDescription    message descripton
 * @author  Tony Thompson
 * @date    Created 23 October 2002     original version
 * @date    Modified 29 October 2002    fixed time stamps
 * @date    Modified 1 November 2002    added Grouping
 */
//---------------------------------------------------------------------------
void TZXMessageLogger::Log(TZXLogType eType, TZXLogLevel eLevel, const String& sSource, const String& sDescription)
{
    static char cTime[] = "00:00:00.000";
    static char cDate[] = "00/00/00";

    // determine if the RemoteLogger has enabled Application Filtering?
    if (NULL != m_Registry)
    {
        bool bApplicationFiltering = false;
        if (true == ReadBool("ApplicationFiltering", bApplicationFiltering))
        {
            if (false == bApplicationFiltering)
            {
                // override the applications minimum type and level filtering
                int Min;
                if (true == ReadInt("MinimumType", Min))
                {
                    m_MinType = static_cast<TZXLogType>(Min);
                }
                if (true == ReadInt("MinimumLevel", Min))
                {
                    // failed to read keys so set minimum
                    m_MinLevel = static_cast<TZXLogLevel>(Min);
                }
            }
            else
            {
                m_MinType  = ltNone;
                m_MinLevel = llNone;
            }
        }
    }
    TZXLogType  MinType  = m_MinType;
    TZXLogLevel MinLevel = m_MinLevel;
    // check the application/remote logger wants us to log the message
    if (MinType <= eType && MinLevel <= eLevel)
    {
        // yep, so get the current date/time
        SYSTEMTIME sysTime;
        GetLocalTime(&sysTime);
        // convert to a string  (as fast and compiler compatible as possible thanks)
        cTime[ 0] = '0' + ( sysTime.wHour                / 10);
        cTime[ 1] = '0' + ( sysTime.wHour                % 10);
        cTime[ 3] = '0' + ( sysTime.wMinute              / 10);
        cTime[ 4] = '0' + ( sysTime.wMinute              % 10);
        cTime[ 6] = '0' + ( sysTime.wSecond              / 10);
        cTime[ 7] = '0' + ( sysTime.wSecond              % 10);
        cTime[ 9] = '0' + ((sysTime.wMilliseconds / 100) % 10);
        cTime[10] = '0' + ((sysTime.wMilliseconds /  10) % 10);
        cTime[11] = '0' + ((sysTime.wMilliseconds /   1) % 10);

        cDate[ 0] = '0' + ( sysTime.wDay                 / 10);
        cDate[ 1] = '0' + ( sysTime.wDay                 % 10);
        cDate[ 3] = '0' + ( sysTime.wMonth               / 10);
        cDate[ 4] = '0' + ( sysTime.wMonth               % 10);
        cDate[ 6] = '0' + ((sysTime.wYear         / 10)  % 10);
        cDate[ 7] = '0' + ( sysTime.wYear                % 10);

        // build the message
        // TLDD:DD:DDTT:TT:TT:TTT{User}|{Computer}|{Source}|{Descripton}
        // 1234567890123456789012345678901234567890
        //          1         2         3         4
        String sMessage("");
        String sDate(cDate);
        String sTime(cTime);

        char cType  = '0' + eType;
        char cLevel = '0' + eLevel;
        sMessage += String(cType);
        sMessage += String(cLevel);
        sMessage += sDate + sTime + m_sUserName + "|" + m_sComputerName + "|" + sSource + "|" + sDescription + "|\0";
        m_sMessages = m_sMessages + "[" + sMessage + "]";

        if (++m_iGroupCount >= m_iGroupSize)
        {
            MailLog();
        }
    }
}
//---------------------------------------------------------------------------
/** FlushLog
 * @brief   Flushs the current logged messages to the Remote Logger application
 * @author  Tony Thompson
 * @date    Created 1 November 2002
 */
//---------------------------------------------------------------------------
void TZXMessageLogger::FlushLog(void)
{
    MailLog();
}
//---------------------------------------------------------------------------
/** MailLog
 * @brief   Sends the log messages to the Remote Application using a Windows Mail Slot
 * @author  Tony Thompson
 * @date    Created 1 November 2002
 */
//---------------------------------------------------------------------------
void TZXMessageLogger::MailLog(void)
{
    if (m_sMessages != "")
    {
        // open the log messages mail slot
        HANDLE hSlot = ::CreateFile(
            g_sMailSlot,
            GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (INVALID_HANDLE_VALUE != hSlot)
        {
            // Mail the message to the logger
            DWORD dwWritten(0);
            ::WriteFile(hSlot, static_cast<void*>(const_cast<char*>(m_sMessages.c_str())), m_sMessages.Length(), &dwWritten, NULL);
            ::CloseHandle(hSlot);
        }
        // Clear queued messages and counter
        m_sMessages = "";
        m_iGroupCount = 0;
    }
}
//---------------------------------------------------------------------------
/** LogInformation
 * @brief   Logs a Informative message
 * @param   sDescription    message descripton
 * @param   eLevel          level of the log message
 * @param   sSource         the source of the log message
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
void TZXMessageLogger::LogInformation(const String& sDescription, TZXLogLevel eLevel, const String& sSource)
{
    Log(ltInformation, eLevel, sSource, sDescription);
}
//---------------------------------------------------------------------------
/** LogWarning
 * @brief   Logs a warning message
 * @param   sDescription    message descripton
 * @param   eLevel          level of the log message
 * @param   sSource         the source of the log message
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
void TZXMessageLogger::LogWarning(const String& sDescription, TZXLogLevel eLevel, const String& sSource)
{
    Log(ltWarning, eLevel, sSource, sDescription);
}
//---------------------------------------------------------------------------
/** LogError
 *
 * @brief   Logs an Error message
 * @param   sDescription    message descripton
 * @param   eLevel          level of the log message
 * @param   sSource         the source of the log message
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
void TZXMessageLogger::LogError(const String& sDescription, TZXLogLevel eLevel, const String& sSource)
{
    Log(ltError, eLevel, sSource, sDescription);
}
//---------------------------------------------------------------------------
/** LogException
 * @brief   Logs an Exception message
 * @param   sDescription    message descripton
 * @param   eLevel          level of the log message
 * @param   sSource         the source of the log message
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
void TZXMessageLogger::LogException(const String& sDescription, TZXLogLevel eLevel, const String& sSource)
{
    Log(ltException, eLevel, sSource, sDescription);
}
//---------------------------------------------------------------------------
/** LogDebug
 * @brief   Log a Debug message
 * @param   sDescription    message descripton
 * @param   eLevel          level of the log message
 * @param   sSource         the source of the log message
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
void TZXMessageLogger::LogDebug(const String& sDescription, TZXLogLevel eLevel, const String& sSource)
{
    Log(ltDebug, eLevel, sSource, sDescription);
}
//---------------------------------------------------------------------------
/**
 * @brief
 * @param
 * @param
 * @author  Tony Thompson
 * @date    Created 7 May 2003
 */
//---------------------------------------------------------------------------
bool TZXMessageLogger::ReadBool(String sKey, bool& bValue)
{
    bool bResult = true;
    bValue = false;
    try
    {
        bValue = m_Registry->ReadBool(sKey);
    }
    catch(...)
    {
        bResult = false;
    }
    return bResult;
}
//---------------------------------------------------------------------------
/**
 * @brief
 * @param
 * @param
 * @author  Tony Thompson
 * @date    Created 7 May 2003
 */
//---------------------------------------------------------------------------
bool TZXMessageLogger::ReadInt(String sKey, int& iValue)
{
    bool bResult = true;
    iValue = 0;
    try
    {
        iValue = m_Registry->ReadInteger(sKey);
    }
    catch(...)
    {
        bResult = false;
    }
    return bResult;
}
//---------------------------------------------------------------------------
/** Constructor
 * @brief   Logs the entering of a function/method
 * @param   sMethodName The name of the method to trace
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
__fastcall TZXMethodLogger::TZXMethodLogger(String sMethodName)
{
    m_sMethodName = sMethodName;
    RL_DEBUG_HIGH("Enter: " + m_sMethodName);
}
//---------------------------------------------------------------------------
/** Destructor
 * @brief   Logs the exiting of a function/method
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
__fastcall TZXMethodLogger::~TZXMethodLogger()
{
    RL_DEBUG_HIGH("Exit : " + m_sMethodName);
    RL_FLUSH;
}
//---------------------------------------------------------------------------
/** Constructor
 * @brief   Setups a local HRESULT variable that we can use and trace 
 * @param   sMethodName The name of the method to trace
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
__fastcall TZXhResultLogger::TZXhResultLogger(String sMethodName, HRESULT* hResult)
{
    m_sMethodName = sMethodName;
    m_hResult     = hResult;
}
//---------------------------------------------------------------------------
/** Destructor
 * @brief   Logs the hResult value as we exit a function/method
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
__fastcall TZXhResultLogger::~TZXhResultLogger()
{
    String sMsg = "Function " + m_sMethodName + ", Exited with HRESULT: ";
    String sResult = "0x00000000";
    char*    cHex = "00000000";

    switch(*m_hResult)
    {
        case S_OK:                      sResult = "S_OK";                                       break;
        case S_FALSE:                   sResult = "S_FALSE";                                    break;
        case E_NOTIMPL:                 sResult = "E_NOTIMPL";                                  break;
        case E_OUTOFMEMORY:             sResult = "E_OUTOFMEMORY";                              break;
        case E_INVALIDARG:              sResult = "E_INVALIDARG";                               break;
        case E_NOINTERFACE:             sResult = "E_NOINTERFACE";                              break;
        case E_POINTER:                 sResult = "E_POINTER";                                  break;
        case E_HANDLE:                  sResult = "E_HANDLE";                                   break;
        case E_ABORT:                   sResult = "E_ABORT";                                    break;
        case E_FAIL:                    sResult = "E_FAIL";                                     break;
        case E_ACCESSDENIED:            sResult = "E_ACCESSDENIED";                             break;
        case E_PENDING:                 sResult = "E_PENDING";                                  break;
        case ERROR_FILE_NOT_FOUND:      sResult = "ERROR_FILE_NOT_FOUND";                       break;
        case ERROR_ALREADY_EXISTS:      sResult = "ERROR_ALREADY_EXISTS";                       break;
        case ERROR_NOT_FOUND:           sResult = "ERROR_NOT_FOUND";                            break;
        case ERROR_OPEN_FAILED:         sResult = "ERROR_OPEN_FAILED";                          break;
        case ERROR_BAD_FORMAT:          sResult = "ERROR_BAD_FORMAT";                           break;
        case ERROR_INVALID_DATA:        sResult = "ERROR_INVALID_DATA";                         break;
        case ERROR_INVALID_NAME:        sResult = "ERROR_INVALID_NAME";                         break;
        case ERROR_INVALID_HANDLE:      sResult = "ERROR_INVALID_HANDLE";                       break;
        case ERROR_FILE_EXISTS:         sResult = "ERROR_FILE_EXISTS";                          break;
        case ERROR_INVALID_PARAMETER:   sResult = "ERROR_INVALID_PARAMETER";                    break;
        case STG_E_PATHNOTFOUND:        sResult = "STG_E_PATHNOTFOUND";                         break;
        case STG_E_WRITEFAULT:          sResult = "STG_E_WRITEFAULT";                           break;
        case STG_E_READFAULT:           sResult = "STG_E_READFAULT";                            break;
        case STG_E_INVALIDHANDLE:       sResult = "STG_E_INVALIDHANDLE";                        break;
        case STG_E_OLDFORMAT:           sResult = "STG_E_OLDFORMAT";                            break;
        case STG_E_SEEKERROR:           sResult = "STG_E_SEEKERROR";                            break;
        default:                        sprintf(cHex, "%0.8X");sResult = "0x" + String(cHex); break;
    }
    RL_DEBUG_HIGH(sMsg + sResult);
    RL_FLUSH;
}
//---------------------------------------------------------------------------
#endif//USE_REMOTE_LOGGING
//---------------------------------------------------------------------------



