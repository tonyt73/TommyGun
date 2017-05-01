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
#ifndef MessageLoggerH
#define MessageLoggerH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <vcl.h>
#include <Registry.hpp>
#ifdef USE_REMOTE_LOGGING
#ifdef RL_LOG_METHODS
    #define RL_LOG_DEBUGS
#endif
//---------------------------------------------------------------------------
enum TZXLogType   { ltNone = 0, ltInformation, ltDebug, ltWarning, ltError, ltException };
//---------------------------------------------------------------------------
enum TZXLogLevel  { llNone = 0, llLow, llMedium, llHigh, llSevere };
//---------------------------------------------------------------------------
/**
 * @class   TZXMessageLogger
 * @brief   Helper class that gives access to the Remote Logger application
 * @author  Tony Thompson
 * @date    Created 23 October 2002
 */
//---------------------------------------------------------------------------
class TZXMessageLogger
{
private:
    String      m_sComputerName;        // Name of Computer, the messages are being generated on
    String      m_sUserName;            // Name of the User logged into the computer
    String      m_sMessages;            // group of messages to be sent to the Remote Logger
    HWND        m_LoggerHWND;           // the Window Handle of the Remote Logger Application
    TZXLogType  m_MinType;              // the minimum level of Message Type  to log
    TZXLogLevel m_MinLevel;             // the minimum level of Message Level to log
    int         m_iGroupSize;           // the size of the group before we send the messages
    int         m_iGroupCount;          // the current size of the group
    TRegistry*  m_Registry;             // the system registry

    // adds message to the group to do sent
    void        Log             (TZXLogType eType, TZXLogLevel eLevel, const String& sSource, const String& sDescription);
    // sends all queued messages to the remote logger application
    void        MailLog         (void);
    bool        ReadBool        (String sKey, bool& bValue);
    bool        ReadInt         (String sKey, int& iValue);

public:

    char        m_sLine[16];

                TZXMessageLogger();
               ~TZXMessageLogger();

    void        LogInformation(const String& sDescription, TZXLogLevel eLevel, const String& sSource);
    void        LogWarning    (const String& sDescription, TZXLogLevel eLevel, const String& sSource);
    void        LogError      (const String& sDescription, TZXLogLevel eLevel, const String& sSource);
    void        LogException  (const String& sDescription, TZXLogLevel eLevel, const String& sSource);
    void        LogDebug      (const String& sDescription, TZXLogLevel eLevel, const String& sSource);
    void        FlushLog      (void);

    void        SetMinType    (TZXLogType eType)      { m_MinType    = eType;      }
    void        SetMaxLevel   (TZXLogLevel eLevel)    { m_MinLevel   = eLevel;     }
    void        SetGroupSize  (int iGroupSize)      { m_iGroupSize = iGroupSize; m_iGroupCount = 0; FlushLog(); }
};
//---------------------------------------------------------------------------
#endif//USE_REMOTE_LOGGING
//---------------------------------------------------------------------------
// LOGGING MACROS
//---------------------------------------------------------------------------
#ifndef USE_REMOTE_LOGGING
    #pragma message ("*** Not using Remote Logger ***")
    #define RL_MESSAGE_LOGGER_OBJECT
    #define RL_LOG_TYPE (t)         
    #define RL_LOG_LEVEL(l)         
    #define RL_GROUP_SIZE(s)        
    #define RL_FLUSH                
    #define RL_EXCEPTION(d)         
    #define RL_EXCEPTION_USER(d,l)  
    #define RL_EXCEPTION_NONE(d)    
    #define RL_EXCEPTION_LOW(d)     
    #define RL_EXCEPTION_MEDIUM(d)  
    #define RL_EXCEPTION_HIGH(d)    
    #define RL_EXCEPTION_SEVERE(d)  
    #define RL_ERROR(d)             
    #define RL_ERROR_USER(d,l)      
    #define RL_ERROR_NONE(d)        
    #define RL_ERROR_LOW(d)         
    #define RL_ERROR_MEDIUM(d)
    #define RL_ERROR_HIGH(d)        
    #define RL_ERROR_SEVERE(d)      
    #define RL_WARNING(d)           
    #define RL_WARNING_USER(d,l)    
    #define RL_WARNING_NONE(d)      
    #define RL_WARNING_LOW(d)       
    #define RL_WARNING_MEDIUM(d)    
    #define RL_WARNING_HIGH(d)      
    #define RL_WARNING_SEVERE(d)    
    #define RL_DEBUG(d)             
    #define RL_DEBUG_USER(d,l)      
    #define RL_DEBUG_NONE(d)        
    #define RL_DEBUG_LOW(d)         
    #define RL_DEBUG_MEDIUM(d)      
    #define RL_DEBUG_HIGH(d)        
    #define RL_DEBUG_SEVERE(d)      
    #define RL_INFO(d)              
    #define RL_INFO_USER(d,l)       
    #define RL_INFO_NONE(d)         
    #define RL_INFO_LOW(d)          
    #define RL_INFO_MEDIUM(d)       
    #define RL_INFO_HIGH(d)         
    #define RL_INFO_SEVERE(d)       
    #ifdef __BORLANDC__
        #define RL_METHOD
        #define RL_HRESULT(hr)  HRESULT hResult = hr;
    #else
        #define RL_METHOD(d)
        #define RL_HRESULT(hr)  HRESULT hResult = hr;      
    #endif//__BORLANDC__
#else//USE_REMOTE_LOGGING
    #pragma message ("*** Using Remote Logger ***")
    extern TZXMessageLogger g_MessageLogger;
    #define RL_MESSAGE_LOGGER_OBJECT TZXMessageLogger g_MessageLogger;
    #define RL_LOG_TYPE (t)  g_MessageLogger.SetMinType  (t);
    #define RL_LOG_LEVEL(l)  g_MessageLogger.SetMinLevel (l);
    #define RL_GROUP_SIZE(s) g_MessageLogger.SetGroupSize(s);
    #define RL_FLUSH         g_MessageLogger.FlushLog();
    //---------------------------------------------------------------------------
    // EXCEPTION LOGGING MACROS
    //---------------------------------------------------------------------------
    #ifdef RL_LOG_EXCEPTIONS
      #pragma message ("*** Logging Exception Messages")
      #define RL_EXCEPTION(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogException(sDesc, llSevere, sSource);\
      }

      #define RL_EXCEPTION_USER(d,l) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogException(sDesc, (TZXLogLevel)l, sSource);\
      }

      #define RL_EXCEPTION_NONE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogException(sDesc, llNone, sSource);\
      }

      #define RL_EXCEPTION_LOW(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogException(sDesc, llLow, sSource);\
      }

      #define RL_EXCEPTION_MEDIUM(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogException(sDesc, llMedium, sSource);\
      }

      #define RL_EXCEPTION_HIGH(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogException(sDesc, llHigh, sSource);\
      }

      #define RL_EXCEPTION_SEVERE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogException(sDesc, llSevere, sSource);\
      }
    #else//RL_LOG_EXCEPTIONS
      #define RL_EXCEPTION(d)         
      #define RL_EXCEPTION_USER(d,l)  
      #define RL_EXCEPTION_NONE(d)    
      #define RL_EXCEPTION_LOW(d)     
      #define RL_EXCEPTION_MEDIUM(d)  
      #define RL_EXCEPTION_HIGH(d)    
      #define RL_EXCEPTION_SEVERE(d)  
    #endif//RL_LOG_EXCEPTIONS

    //---------------------------------------------------------------------------
    // ERROR LOGGING MACROS
    //---------------------------------------------------------------------------
    #ifdef RL_LOG_ERRORS
      #pragma message ("*** Logging Error Messages")
      #define RL_ERROR(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogError(sDesc, llHigh, sSource);\
      }

      #define RL_ERROR_USER(d,l) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogError(sDesc, (TZXLogLevel)l, sSource);\
      }

      #define RL_ERROR_NONE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogError(sDesc, llNone, sSource);\
      }

      #define RL_ERROR_LOW(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogError(sDesc, llLow, sSource);\
      }

      #define RL_ERROR_MEDIUM(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogError(sDesc, llMedium, sSource);\
      }

      #define RL_ERROR_HIGH(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogError(sDesc, llHigh, sSource);\
      }

      #define RL_ERROR_SEVERE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogError(sDesc, llSevere, sSource);\
      }
    #else//RL_LOG_ERRORS
      #define RL_ERROR(d)             
      #define RL_ERROR_USER(d,l)      
      #define RL_ERROR_NONE(d)        
      #define RL_ERROR_LOW(d)         
      #define RL_ERROR_MEDIUM(d)      
      #define RL_ERROR_HIGH(d)        
      #define RL_ERROR_SEVERE(d)      
    #endif//RL_LOG_ERRORS
    //---------------------------------------------------------------------------
    // WARNING LOGGING MACROS
    //---------------------------------------------------------------------------
    #ifdef RL_LOG_WARNINGS
      #pragma message ("*** Logging Warning Messages")
      #define RL_WARNING(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogWarning(sDesc, llMedium, sSource);\
      }

      #define RL_WARNING_USER(d,l) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogWarning(sDesc, (TZXLogLevel)l, sSource);\
      }

      #define RL_WARNING_NONE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogWarning(sDesc, llNone, sSource);\
      }

      #define RL_WARNING_LOW(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogWarning(sDesc, llLow, sSource);\
      }

      #define RL_WARNING_MEDIUM(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogWarning(sDesc, llMedium, sSource);\
      }

      #define RL_WARNING_HIGH(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogWarning(sDesc, llHigh, sSource);\
      }

      #define RL_WARNING_SEVERE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogWarning(sDesc, llSevere, sSource);\
      }
    #else//RL_LOG_WARNINGS
      #define RL_WARNING(d)           
      #define RL_WARNING_USER(d,l)    
      #define RL_WARNING_NONE(d)      
      #define RL_WARNING_LOW(d)       
      #define RL_WARNING_MEDIUM(d)    
      #define RL_WARNING_HIGH(d)      
      #define RL_WARNING_SEVERE(d)    
    #endif//RL_LOG_WARNINGS
    //---------------------------------------------------------------------------
    // DEBUG LOGGING MACROS
    //---------------------------------------------------------------------------
    #ifdef RL_LOG_DEBUGS
      #pragma message ("*** Logging Debug Messages")
      #define RL_DEBUG(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogDebug(sDesc, llLow, sSource);\
      }

      #define RL_DEBUG_USER(d,l) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogDebug(sDesc, (TZXLogLevel)l, sSource);\
      }

      #define RL_DEBUG_NONE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogDebug(sDesc, llNone, sSource);\
      }

      #define RL_DEBUG_LOW(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogDebug(sDesc, llLow, sSource);\
      }

      #define RL_DEBUG_MEDIUM(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogDebug(sDesc, llMedium, sSource);\
      }

      #define RL_DEBUG_HIGH(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogDebug(sDesc, llHigh, sSource);\
      }

      #define RL_DEBUG_SEVERE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogDebug(sDesc, llSevere, sSource);\
      }
    #else//RL_LOG_DEBUGS
      #define RL_DEBUG(d)             
      #define RL_DEBUG_USER(d,l)      
      #define RL_DEBUG_NONE(d)        
      #define RL_DEBUG_LOW(d)         
      #define RL_DEBUG_MEDIUM(d)      
      #define RL_DEBUG_HIGH(d)        
      #define RL_DEBUG_SEVERE(d)      
    #endif//RL_LOG_DEBUGS

    //---------------------------------------------------------------------------
    // INFORMATION LOGGING MACROS
    //---------------------------------------------------------------------------
    #ifdef RL_LOG_INFOS
      #pragma message ("*** Logging Information Messages")
      #define RL_INFO(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogInformation(sDesc, llNone, sSource);\
      }

      #define RL_INFO_USER(d,l) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogInformation(sDesc, (TZXLogLevel)l, sSource);\
      }

      #define RL_INFO_NONE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogInformation(sDesc, llNone, sSource);\
      }

      #define RL_INFO_LOW(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogInformation(sDesc, llLow, sSource);\
      }

      #define RL_INFO_MEDIUM(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.Instance()->LogInformation(sDesc, llMedium, sSource);\
      }

      #define RL_INFO_HIGH(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogInformation(sDesc, llHigh, sSource);\
      }

      #define RL_INFO_SEVERE(d) \
      {\
          itoa(__LINE__, g_MessageLogger.m_sLine, 10);\
          String sDesc(d);\
          String sSource = "Line: " + String(g_MessageLogger.m_sLine) + ", Function: " + String(__FUNC__) + ", File: " + String(__FILE__);\
          g_MessageLogger.LogInformation(sDesc, llSevere, sSource);\
      }
    #else//RL_LOG_INFOS
      #define RL_INFO(d)              
      #define RL_INFO_USER(d,l)       
      #define RL_INFO_NONE(d)         
      #define RL_INFO_LOW(d)          
      #define RL_INFO_MEDIUM(d)       
      #define RL_INFO_HIGH(d)         
      #define RL_INFO_SEVERE(d)       
    #endif//RL_LOG_INFOS
    //---------------------------------------------------------------------------
    // Redefine the DEBUG_STRING macros to use the Remote Logger
    //---------------------------------------------------------------------------
   /* #ifdef DEBUG_STRING
    #undef DEBUG_STRING
    #pragma message("***   DEBUG_STRING Redefined   ***")
    #define DEBUG_STRING(s) RL_DEBUG(s)
    #endif//DEBUG_STRING
    */
//---------------------------------------------------------------------------
    /**
     * @class   TZXMethodLogger
     * @brief   Provides a mechanism to log entry and exit points to a method/function
     * @date    11 February 2003
     * @author  Tony Thompson
     */
    class TZXMethodLogger
    {
    private:
        String    m_sMethodName;
    public:

        __fastcall TZXMethodLogger(String sMethodName);
        __fastcall ~TZXMethodLogger();
    };
//---------------------------------------------------------------------------
    /**
     * @class   TZXMethodLogger
     * @brief   Provides a mechanism to log a hResult exit value from a method/function
     * @date    28 February 2003
     * @author  Tony Thompson
     */
    class TZXhResultLogger
    {
    private:
        String    m_sMethodName;
        HRESULT*    m_hResult;
    public:
        __fastcall TZXhResultLogger(String sMethodName, HRESULT* hResult);
        __fastcall ~TZXhResultLogger();
    };
//---------------------------------------------------------------------------
    #ifdef __BORLANDC__
      #ifdef RL_LOG_METHODS
        #pragma message ("*** Logging Methods")
        #define RL_METHOD                             TZXMethodLogger  MethodLogger (__FUNC__);
      #else
        #define RL_METHOD
      #endif
      #ifdef RL_LOG_HRESULTS
        #pragma message ("*** Logging HResults")
        #define RL_HRESULT(hr)  HRESULT hResult = hr; TZXhResultLogger hResultLogger(__FUNC__, &hResult);
      #else
        #define RL_HRESULT(hr)  HRESULT hResult = hr;
      #endif
    #else
      #pragma message ("*** Logging Methods")
      #define RL_METHOD(f)                            TZXMethodLogger   MethodLogger (f                );
      #define RL_HRESULT(f,hr) HRESULT hResult = hr;  TZXhResultLogger  hResultLogger(f, &hResult      );
    #endif//__BORLANDC__
//---------------------------------------------------------------------------
#endif//USE_REMOTE_LOGGING
//---------------------------------------------------------------------------
#endif

