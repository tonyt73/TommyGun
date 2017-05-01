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

    FrameworkInterface.h

    This file provides the interface prototypes for the Core.DLL.
    It provides access to all the Shell Interfaces, and the event definitions.

---------------------------------------------------------------------------*/
#ifndef __SHELL_INTERFACE_DLL__
#define __SHELL_INTERFACE_DLL__
/**
 * @file    Interface.h
 * @brief   Defines the Interfaces used to access the Core functions from within the KiwiWare Shell Environment.
 */
//---------------------------------------------------------------------------
//===========================================================================
// TommyGun Source Structure
//
//  Directory                   Comment
//===========================================================================
// +-[ ] TommyGun                KiwiWare project folder
//    |
//    +-[ ] Common              Common Source code and header files
//    |  |
//    |  +-[ ] Memory           Memory related source code
//    |  |
//    |  +-[ ] FileSystem       File system related source code
//    |  |
//    |  +-[ ] Utility          Utility source code
//    |
//    +-[ ] Scorpio6            The Scorpio VCL Component Suite
//    |
//    +-[ ] FrameWork           TommyGun Shell environment
//       |
//       +-[ ] Core             The Shells core functionality           (core.dll)
//       |
//       +-[ ] Helpers          Helper functions                        (helpers.lib)
//       |
//       +-[ ] Plugins          Plugin binaries are placed here.        (rpi and rpx files)
//          |
//          +-[ ] Include       BasePlugin.h and CustomEvents.h
//          |
//          +-[ ] Plugin 1      Plugin directory and associated files
//          |
//          +-[ ] Plugin 2
//          |
//          +-...
//          |
//          +-[ ] Plugin n
//
//
//===========================================================================
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <Unknwn.h>
#include <vector>
#include "fMessage.h"
#include <KXmlInfo.h>
//-- MACROS -----------------------------------------------------------------
// Macros for displaying exception information using the KiwiWare message dialog box

#ifdef _DEBUG
#ifndef CHECK_HRESULT
#define CHECK_HRESULT( a )\
if(FAILED(a))\
{\
    String sTitle = "hResult Error";\
    ShowWindowsErrorMessage( sTitle, a, __FILE__, __FUNC__, __LINE__ );\
}
#endif//CHECK_HRESULT
#else //_DEBUG
#ifndef CHECK_HRESULT
#define CHECK_HRESULT( a )
#endif//CHECK_HRESULT
#endif//_DEBUG
/**
 * @file    fShell.h
 * @brief   This file implements the Shell Environments GUI.
 * @verbatim

     Plugin Core Interface Versions

     00.01
        Initialize(TApplication*, TZX_HANDLE)         intializes the plugin
        Release   ()                                  releases the plugins resources
        Notify    (TZX_EVENT, LPDATA, DWORD, Arg)     message pump for the plugin
        Version   (DWORD)                             the version of the plugin
        Name      (String)                            name of the plugin

     00.02
        Initialize(TApplication*, TZX_HANDLE)         intializes the plugin
        Release   ()                                  releases the plugins resources
        Notify    (TZX_EVENT, LPDATA, DWORD, Arg)     message pump for the plugin
        Version   (DWORD)                             the version of the plugin
        Name      (String)                            name of the plugin
        Interface (DWORD)                             core.dll interface required to work
        Vendor    (String)                            vendor of the plugin
        Added the check for InterfaceVersionRequired

     00.03
        Initialize(TApplication*, TZX_HANDLE)         intializes the plugin
        Release   ()                                  releases the plugins resources
        Notify    (TZX_EVENT, LPDATA, DWORD, Arg)     message pump for the plugin
        Version   (DWORD)                             the version of the plugin
        Name      (String)                            name of the plugin
        Interface (DWORD)                             core.dll interface required to work
        Vendor    (String)                            vendor of the plugin
        Flags     (DWORD)[implementation is optional] flags for plugin control and access

        Added Status Bar and Options Page functions to the Core.dll interface

     00.04
        Initialize(TApplication*, TZX_HANDLE)         intializes the plugin
        Release   ()                                  releases the plugins resources
        Notify    (TZX_EVENT, LPDATA, DWORD, Arg)     message pump for the plugin
        Flags     (DWORD)[implementation is optional] flags for plugin control and access
        Removed:
            Version, Name, Vendor and Interface.
            All this information HAS to be in the file version information block for a plugin to load.

     00.05
        Initialize(TZX_HANDLE)                        intializes the plugin
        Release   ()                                  releases the plugins resources
        Notify    (TZX_EVENT, LPDATA, DWORD, Arg)     message pump for the plugin
        Flags     (DWORD)[implementation is optional] flags for plugin control and access
        Removed
            The TApplication pointer from the Initialize function.
            The Core is NO LONGER BACKWARDS COMPATIBLE with older versions.

     00.06
        Initialize(TZX_HANDLE)                        intializes the plugin
        Release   ()                                  releases the plugins resources
        Notify    (TZX_EVENT, LPDATA, DWORD, Arg)     message pump for the plugin
        Flags     (DWORD)[implementation is optional] flags for plugin control and access
        Added New Interfaces to Core
            TranslateString(ResID, String& sString)
            TranslateComponent(ResID, TComponent* Component)
            TranslateRTString(RTranslatableString& rtString)
            TranslateStringTable(RTStringTable& StringTable)
            TranslateIcon  (ResID, IUNKNOWN* pIcon)
            TranslateImage (ResID, IUNKNOWN* pImage)
            TranslateBitmap(ResID, HBITMAP* pBitmap)
        Moved the MessageBox code from Helpers to Code
            This was to help the translation of messages
        Added new Messagebox Intefaces to Core
            ShowExceptionMessage   ( ... )
            ShowWindowsErrorMessage( ... )
            MessageBox             ( ... )
            MessageBoxUser         ( ... )
            MessageBoxAdd          ( ... )
            MessageBoxAddUser      ( ... )
            MessagePost            ( ... )
            MessageRemove          ( ... )

     00.07
        Initialize(TZX_HANDLE)                        intializes the plugin
        Release   ()                                  releases the plugins resources
        Notify    (TZX_EVENT, LPDATA, DWORD, Arg)     message pump for the plugin
        Flags     (DWORD)[implementation is optional] flags for plugin control and access
        Added new Event registration

        Added new RWEventManager class
            Plugins can derive a new EventManager class from this base class, and register events they are interested in.

     00.08
        Initialize(TZX_HANDLE)                        intializes the plugin
        Release   ()                                  releases the plugins resources
        Notify    (TZX_EVENT, LPDATA, DWORD, Arg)     message pump for the plugin
        Flags     (DWORD)[implementation is optional] flags for plugin control and access
        Added new Options Panel to the patient browser panel
            AddOptionsPanel   (...)
            RemoveOptionsPanel(...)

     First major revision to the framework code (although the API is still very much the same) 
     01.00
        Initialize(TZX_HANDLE)                        intializes the plugin
        Release   ()                                  releases the plugins resources
        Notify    (TZX_EVENT, LPDATA, DWORD, Arg)     message pump for the plugin
        Flags     (DWORD)[implementation is optional] flags for plugin control and access
        Added new VCL AddBitmap functions
        Changed the AddOutlookButton()
        Changed AddOptionsPanel   (...) to AddDockPanel   (...)
        Changed RemoveOptionsPanel(...) to RemoveDockPanel(...)

     01.01
        Added GetXmlVersion(...)

 * @endverbatim
 */
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace Interface
    {
        //-- INTERFACE HANDLES ------------------------------------------------------
        //
        // All handles are either signed or unsigned int's.
        //
        // Handles are used to identify items with the shell environment.
        // They are NOT indexes into arrays, and you cannot assume they will be sequencial.
        // Handles are reallocated when they are freed back into the pool. So if you free
        // a handle, and keep a copy then the copy is invalid.
        //
        typedef          int TZX_EVENT;         /// Generic Event type
        typedef unsigned int TZX_HANDLE;        /// Generic Handle Type
        typedef HINSTANCE  TZX_HPLUGIN;         /// Plugin identification number
        //-- INTERFACE EVENTS -------------------------------------------------------
        //
        // The Shell environment passes information to the plugins through its Notify call.
        // The main parameter of the Notify function is the Event parameter.
        // Event is used to describe the reason of the call.
        // The Shell has a small set (at present) of known events it can generate.
        // These are described below.
        //
        // Verbs  - These are ACTION events. They are not normal Windows events as such.
        //          They represent call points from within the Shell's document logic framework.
        //
        // Notify - These are Windows Style events. They are called in response to mouse clicks etc.
        //
        // Query  - These are Queries as to the state of your document information. Mainly to do with
        //          whether data needs to be saved.
        //
        //! Common Shell Verbs
        enum TZX_SHELL_VERB
        {
          TZX_VERB_NONE             = 0x0000,
          TZX_VERB_MASK             = 0x0100,
          TZX_VERB_NEW              = 0x0101,
          TZX_VERB_OPEN             = 0x0102,
          TZX_VERB_LOAD             = 0x0103,
          TZX_VERB_SAVE             = 0x0104,
          TZX_VERB_CUT              = 0x0105,
          TZX_VERB_COPY             = 0x0106,
          TZX_VERB_PASTE            = 0x0107,
          TZX_VERB_UNDO             = 0x0108,   // these are sent for plugins that don't
          TZX_VERB_REDO             = 0x0109,   // support the built-in undo system
          TZX_VERB_DELETE           = 0x010a,
          TZX_VERB_SELECTALL        = 0x010b,
          TZX_VERB_DESELECTALL      = 0x010c,
          TZX_VERB_EXIT             = 0x0110,
          TZX_VERB_VIEWOPTIONS      = 0x0113,
          TZX_VERB_SWITCH_PLUGIN    = 0x0114,
        };

        //! Notification messages passed from the Shell
        enum TZX_NOTIFY_TYPE
        {
          /// menu on click events
          TZXN_NOTIFY_MASK          = 0x0600,
          TZXN_NOTIFY_MENU_MASK     = 0x0200,
          TZXN_FILE_NEW             = 0x0201,   // File New menu item click
          TZXN_FILE_OPEN            = 0x0202,   // File Open menu item click
          TZXN_FILE_SAVE            = 0x0203,   // File Save menu item click
          TZXN_FILE_EXIT            = 0x0208,   // File Exit menu item click
          TZXN_EDIT_UNDO            = 0x020A,   // Edit Undo menu item click
          TZXN_EDIT_REDO            = 0x020B,   // Edit Redo menu item click
          TZXN_EDIT_CUT             = 0x020C,   // Edit Cut menu item click
          TZXN_EDIT_COPY            = 0x020D,   // Edit Copy menu item click
          TZXN_EDIT_PASTE           = 0x020E,   // Edit Paste menu item click
          TZXN_EDIT_DELETE          = 0x020F,   // Edit Delete menu item click
          TZXN_EDIT_SELECTALL       = 0x0210,   // Edit SelectAll menu item click
          TZXN_EDIT_FIND            = 0x0220,   // Edit Find menu item click
          TZXN_EDIT_FIND_REPLACE    = 0x0221,   // Edit Find and Replace menu item click
          TZXN_EDIT_FIND_PREV       = 0x0222,   // Edit Find Previous menu item click
          TZXN_EDIT_FIND_NEXT       = 0x0223,   // Edit Find Next menu item click
          TZXN_VIEW_TOOLBARS        = 0x0230,   // View Toolbars menu item click
          TZXN_VIEW_OPTIONS         = 0x0231,   // View Options menu item click
          TZXN_VIEW_BROWSER         = 0x0232,   // View Browser menu item click
          /// Game events
          TZXN_GAME_PLAY            = 0x0300,   // Play the Game 
          /// application events
          /// Application Activate State change
          TZXN_ACTIVATE             = 0x0400,   // data - application
          TZXN_DEACTIVATE           = 0x0401,   // data - application
          /// Application Main Tab Show/Hide
          TZXN_TABSHOW              = 0x040A,   // data - application, Event, NULL, PluginHandle, TabHandle )
          TZXN_TABHIDE              = 0x040B,   // data - application, Event, NULL, PluginHandle, TabHandle )
          /// Application Quit (sent by plugins to request application terminate) (DOES NOT SAVE DATA)
          TZXN_QUIT                 = 0x040D,
          TZXN_OPTIONS_SAVE         = 0x040E,
          TZXN_OPTIONS_CANCELLED    = 0x040F,
          TZXN_OPTIONS_CHANGED      = 0x0410,
          TZXN_POST_LOAD            = 0x0411,
          TZXN_XML_NEW              = 0x0412,   // data - xml info object
          TZXN_XML_PRE_LOAD         = 0x0413,   // data - xml info object
          TZXN_XML_POST_LOAD        = 0x0414,   // data - xml info object
          TZXN_XML_PRE_SAVE         = 0x0415,   // data - xml info object
          TZXN_XML_POST_SAVE        = 0x0416,   // data - xml info object
          TZXN_XML_UPDATE           = 0x0417,   // data - xml info object (same as save but don't clear the dirty flag)
          TZXN_XML_CHANGED          = 0x0418,   // data - xml info object, String pointer to node changed
          TZXN_XML_UNDO_ADD         = 0x0419,   // data - xml undo object - plugins use this to save undo state
          TZXN_XML_UNDO_RESTORE     = 0x041A,   // data - xml undo object - plugins use this to restore undo state
        };

        /** Query events passed from the Shell

           All queries MUST be structured to take S_OK as the default answer of Yes.
           This way each plugin can actually set the No answer explicitly.
           Each plugin must reply to these events.
           By default each plugins Notify event processes these automatically if hResult is set to S_OK.
           The Plugin returns the answer in hResult
           S_OK     Question is TRUE
           S_FALSE  Question is FALSE
         */
        enum TZX_QUERY_TYPE
        {
          TZX_QUERY_MASK            = 0x0800,
          TZX_QUERY_DATASAVED       = 0x0801,
          TZX_QUERY_CANQUIT         = 0x0802,
          TZX_QUERY_SAVESIZE        = 0x0803,
          TZX_QUERY_COPYPASTE       = 0x0804,   // returns S_QUERY_YES if supported
          TZX_QUERY_FIND            = 0x0805,   // returns S_QUERY_YES if supported
          //TZX_QUERY_UNDO            = 0x0806,  // returns S_QUERY_YES if supported
          //TZX_QUERY_REDO            = 0x0807,  // returns S_QUERY_YES if supported
          TZX_QUERY_PROJECT_FOLDER  = 0x0808,   // returns S_QUERY_YES if retrieved - lpData is a string*
          TZX_QUERY_KEY_PANEL       = 0x0809,   // S_QUERY_YES if retrieved - asks a plugin for its key panel
        };

        // correct YES answer to most query messages
        enum TZX_RESPONSES
        {
            S_QUERY_YES             = 0x20000002
        };

        enum TZX_BUTTONSTYLE { tbsRWButton = 1, tbsRWCheck, tbsRWSeparator };

        //---------------------------------------------------------------------------
        enum ZXUndoType { utUndo, utRedo };
        enum TZX_UNDO_OPERATION { uoUndoSave, uoUndoRestore };

        /// Data pointer type ( Windows LPARAM data type )
        typedef LPARAM LPDATA;

        // Interface standard defines
        /// Standard Outlook Group Name<BR>
        /// Use this when you want to add a button the Outlook Bar
        #define TZXC_CUSTOM_EVENT_MASK  0xF000  // mask used to determine if an event is a custom event
        #define TZXC_SYSTEM_EVENT       0x0000
        #define TZXC_SYSTEM_EVENT_MASK  0xFF00
        #define STANDARD_OUTLOOK_GROUP  "Quick Links"


        /** Plugin Flags
         * @code
         *
         *  This shows all the bits currently assign to the flags
         *  Please update when you create more flags
         *
         * Bit  Taken
         * 00   [X] IsNotUnloadable
         * 01   [X] IsNotVisibleInOptionsPage
         * 02   [ ]
         * 03   [ ]
         * 04   [ ]
         * 05   [ ]
         * 06   [ ]
         * 07   [ ]
         * 08   [ ]
         * 09   [ ]
         * 10   [ ]
         * 11   [ ]
         * 12   [ ]
         * 13   [ ]
         * 14   [ ]
         * 15   [ ]
         * 16   [ ]
         * 17   [ ]
         * 18   [ ]
         * 19   [ ]
         * 20   [ ]
         * 21   [ ]
         * 22   [ ]
         * 23   [ ]
         * 24   [ ]
         * 25   [ ]
         * 26   [X] Lo bit of the Read  Security Level      0 - no privileges   1 - low
         * 27   [X] Hi bit of the Read  Security Level      2 - medium          4 - high
         * 28   [X] Lo bit of the Write Security Level      0 - no privileges   1 - low
         * 29   [X] Hi bit of the Write Security Level      2 - medium          4 - high
         * 30   [X] Lo bit of the Load  Priority value      0 - None            1 - Low
         * 31   [X] Hi bit of the Load  Priority value      2 - Medium          3 - High
         *
         * @endcode
         */

        #define FLAG_NotSet                     0x00000000
        #define FLAG_IsNotUnloadable            0x00000001
        #define FLAG_IsNotVisibleInOptionsPage  0x00000002
        #define FLAG_PluginLoadPriorityMask     0xC0000000
        #define FLAG_PluginLoadPriorityNone     0x00000000
        #define FLAG_PluginLoadPriorityLow      0x40000000
        #define FLAG_PluginLoadPriorityMedium   0x80000000
        #define FLAG_PluginLoadPriorityHigh     0xC0000000
        #define FLAG_PluginWriteSecurityMask    0x30000000
        #define FLAG_PluginWriteSecurityNone    0x00000000
        #define FLAG_PluginWriteSecurityLow     0x10000000
        #define FLAG_PluginWriteSecurityMedium  0x20000000
        #define FLAG_PluginWriteSecurityHigh    0x30000000
        #define FLAG_PluginReadSecurityMask     0x0C000000
        #define FLAG_PluginReadSecurityNone     0x00000000
        #define FLAG_PluginReadSecurityLow      0x04000000
        #define FLAG_PluginReadSecurityMedium   0x08000000
        #define FLAG_PluginReadSecurityHigh     0x0C000000

        #define SHIFTS_PluginLoadPriority       30
        #define SHIFTS_PluginWriteSecurity      28
        #define SHIFTS_PluginReadSecurity       26
    }
}

//-- SHELL INTERFACE EXPOSURE -----------------------------------------------
//
// These interfaces are available to any plugin that links to the CorePlugin.lib static link library.
//
//  ALL Functions return the same error codes
//      S_OK    function successful
//      S_FALSE function failure
//
#define FUNCTION_PREFIX HRESULT __declspec(dllexport) WINAPI
using namespace Scorpio;
using namespace Interface;

extern "C"
{
    /// Tab Interfaces
    //  The tab interfaces provide access to a tab for a plugin.
    //  Tabs are not shareable across plugins.
    //  You can add many Tabs from a single plugin.
    //  The handle parameter returns the Windows Handle of the newly create Tab control within the Shell environment
    //  As the onwer of a Tab you will receive OnResize, OnHide, OnShow events specifically targetted to you the Tab Owner.
    FUNCTION_PREFIX AddPage                 ( TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Name );
    FUNCTION_PREFIX RemovePage              ( TZX_HPLUGIN PluginHandle, HWND  Handle );
    FUNCTION_PREFIX SetPageBitmap           ( TZX_HPLUGIN PluginHandle, HWND Handle, TImage* SmallImage, TImage* LargeImage );

    FUNCTION_PREFIX AddMenu                 ( const String& sCaption, TMenuItem*& pMenu );

    /// Options Page Interfaces
    FUNCTION_PREFIX AddOptionsPage          ( TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Name );

    FUNCTION_PREFIX SetStatusSlot           ( TZX_HPLUGIN PluginHandle, const String& sText, unsigned int iSlot );

    FUNCTION_PREFIX IsActivePlugin          ( TZX_HPLUGIN PluginHandle );

    /// General Interfaces
    //  PostNotifyEvent - this function allows a plugin to send an event to the Shell, and other Plugins.
    //  Currently only the TZX_QUIT message is trapped within the Shell environment. All other messages are simply
    //  forwarded to all other plugins.
    FUNCTION_PREFIX PostNotifyEvent         ( TZX_HPLUGIN PluginHandle, TZX_EVENT Event, LPDATA Data, DWORD Param, DWORD Arg );

    // Message Box functions
    FUNCTION_PREFIX Message                 ( ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3, int& iAnswer );

    // Event registration functions
    FUNCTION_PREFIX RegisterPluginEvent     ( TZX_HPLUGIN PluginHandle, TZX_EVENT Event );
    FUNCTION_PREFIX UnRegisterPluginEvent   ( TZX_HPLUGIN PluginHandle, TZX_EVENT Event );

    // Error/Exception logging
    FUNCTION_PREFIX LogPluginException      ( TZX_HPLUGIN PluginHandle );
    FUNCTION_PREFIX LogWindowsError         ( const String& MsgTitle, const DWORD ErrorCode, const String& File, const String& Function, int Line );

    FUNCTION_PREFIX AddPluginIcon           ( TZX_HPLUGIN PluginHandle, TImage* Icon, const String& sDescription);
    FUNCTION_PREFIX RemovePluginIcon        ( TZX_HPLUGIN PluginHandle);

    FUNCTION_PREFIX GetXmlInfo              ( KXmlInfo*& xmlInfo );
    FUNCTION_PREFIX GetXmlVersion           ( DWORD &dwVersion );
};
#endif // __SHELL_INTERFACE_DLL__
