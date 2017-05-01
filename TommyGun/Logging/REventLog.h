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

-----------------------------------------------------------------------------

    This class provides simple access to the Window Event Log under the MMC.

	Use these compiler defines to use this class
        USE_EVENT_LOG           define to enable logging of events	(undefine to remove all logging)
        LOG_ERROR_EVENTS        define to enable logging of error events
        LOG_WARNING_EVENTS      define to enable logging of warning events
        LOG_INFORMATION_EVENTS  define to enable logging of information events

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef REventLogH
#define REventLogH
//- SYS ---------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
/**
 * @class   REventLog
 * @brief   A simple class to log events to the Windows Event Log in the MMC.
 * @author  Tony Thompson
 * @date    26 August 2003
 * @remarks Copyright KiwiWare 2004
 */
//---------------------------------------------------------------------------
class REventLog
{
private:
    HANDLE m_hEventLog;             // Handle to an Event Log

	//-----------------------------------------------------------------------
    /** Deregister
     * @brief   Deregisters the event log source
     * @author  Tony Thompson
     * @date    26 August 2003
     * @remarks Copyright KiwiWare 2004
     */
	//-----------------------------------------------------------------------
    void Deregister(void)
    {
#ifdef USE_EVENT_LOG
        // do we have a valid event log handle
        if (NULL != m_hEventLog)
        {
            // yes, then release the handle
            ::DeregisterEventSource(m_hEventLog);
            // erase the handle
            m_hEventLog = NULL;
        }
#endif//USE_EVENT_LOG
    }

public:
	//-----------------------------------------------------------------------
    /** Constructor
     * @brief   Initializes the object
     * @author  Tony Thompson
     * @date    26 August 2003
     * @remarks Copyright KiwiWare 2004
     */
	//-----------------------------------------------------------------------
    REventLog()
    : m_hEventLog(NULL)
    {
#ifdef USE_EVENT_LOG
        // register a default source id
        Source("KiwiWare");
#endif//USE_EVENT_LOG
    }

	//-----------------------------------------------------------------------
    /** Destructor
     * @brief   Frees allocated resouces
     * @author  Tony Thompson
     * @date    26 August 2003
     * @remarks Copyright KiwiWare 2004
     */
	//-----------------------------------------------------------------------
   ~REventLog()
    {
#ifdef USE_EVENT_LOG
        // deregister the event source
        Deregister();
#endif//USE_EVENT_LOG
    }

	//-----------------------------------------------------------------------
    /** Source
     * @brief   Changes the source for an event log
     * @author  Tony Thompson
     * @date    26 August 2003
     * @remarks Copyright KiwiWare 2004
     */
	//-----------------------------------------------------------------------
    void Source(const char* const szEventSource)
    {
#ifdef USE_EVENT_LOG
        // deregister any previous event log used
        Deregister();
        // create a new event log using the new source id
        m_hEventLog = ::RegisterEventSource
                        (
                            NULL,           // no machine name, just use the local name
                            szEventSource   // name of source application
                        );
#endif//USE_EVENT_LOG
    }

	//-----------------------------------------------------------------------
    /** Error
     * @brief   Logs an error message to the EventLog
     * @author  Tony Thompson
     * @date    26 August 2003
     * @remarks Copyright KiwiWare 2004
     */
	//-----------------------------------------------------------------------
    void Error(const char* const szMessage) const
    {
#if defined(USE_EVENT_LOG) && defined(LOG_ERROR_EVENTS)
        // do we have a valid event log handle?
        if (NULL != m_hEventLog)
        {
            // yes, then log the message
            LPCTSTR arMessages[2] = {szMessage, NULL};
            ::ReportEvent(m_hEventLog, EVENTLOG_ERROR_TYPE, 0, 0, NULL, 1, 0, arMessages, NULL);
        }
#endif//LOG_ERROR_EVENTS
    }

	//-----------------------------------------------------------------------
    /** Warning
     * @brief   Logs a warning message to the EventLog
     * @author  Tony Thompson
     * @date    26 August 2003
     * @remarks Copyright KiwiWare 2004
     */
	//-----------------------------------------------------------------------
    void Warning(const char* const szMessage) const
    {
#if defined(USE_EVENT_LOG) && defined(LOG_WARNING_EVENTS)
        // do we have a valid event log handle?
        if (NULL != m_hEventLog)
        {
            // yes, then log the message
            LPCTSTR arMessages[2] = {szMessage, NULL};
            ::ReportEvent(m_hEventLog, EVENTLOG_WARNING_TYPE, 0, 0, NULL, 1, 0, arMessages, NULL);
        }
#endif//LOG_WARNING_EVENTS
    }

	//-----------------------------------------------------------------------
    /** Information
     * @brief   Logs an information message to the EventLog
     * @author  Tony Thompson
     * @date    26 August 2003
     * @remarks Copyright KiwiWare 2004
     */
	//-----------------------------------------------------------------------
    void Information(const char* const szMessage) const
    {
#if defined(USE_EVENT_LOG) && defined(LOG_INFORMATION_EVENTS)
        // do we have a valid event log handle?
        if (NULL != m_hEventLog)
        {
            // yes, then log the message
            LPCTSTR arMessages[2] = {szMessage, NULL};
            ::ReportEvent(m_hEventLog, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, arMessages, NULL);
        }
#endif//LOG_INFORMATION_EVENTS
    }
};
//---------------------------------------------------------------------------
#endif//REventLogH