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
#ifndef ZXPluginH
#define ZXPluginH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
#include "psapi.h"
#ifdef USE_GUI_MANAGER
#include "FrameWorkInterface.h"
#else
#include "ZXTypes.h"
#endif
#ifdef Version
#undef Version
#endif
//---------------------------------------------------------------------------
const WORD  g_dwCompatibleBaseVersion = 0x0100; // 02.00
const WORD  g_dwCoreInterfaceVersion  = 0x0102; // 02.00
using namespace Scorpio;
#ifdef USE_GUI_MANAGER
using namespace Interface;
#endif
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace Plugin
    {
        class ZXPlugin;
    }
}
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
//-- DLL FUNCTION POINTER TYPES ---------------------------------------------
typedef BOOL   (WINAPI *GetModuleInformationPtr )(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb);
typedef int    (WINAPI *StdCallPtr              )(void);
typedef HRESULT(WINAPI *InitialisePtr           )(Scorpio::Plugin::ZXPlugin* pPlugin);
typedef HRESULT(WINAPI *ReleasePtr              )(void);
typedef HRESULT(WINAPI *NotifyPtr               )(TZX_EVENT Event, LPDATA Data, DWORD Param, DWORD Arg);
typedef HRESULT(WINAPI *FlagsPtr                )(DWORD& PluginVersion);
typedef HRESULT(WINAPI *SignaturePtr            )(String& Signature);
//---------------------------------------------------------------------------
typedef std::vector<TZX_EVENT>      ZXEvents;
typedef ZXEvents::iterator          ZXEventsIterator;
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace Plugin
    {
        class ZXPluginManager;
        //---------------------------------------------------------------------------
        __declspec( dllexport) class ZXPlugin
        {
        private:
            ZXPluginManager*        m_PluginManager;    // The manager of this plugin
            ZXEvents                m_Events;           // The events that the plugin is registered to recieve
            unsigned int            m_iLoadOrder;       // Order to in which to load the plugin
            String                  m_sFileName;        // FileName of the DLL
            String                  m_sDescription;     // Description from the DLL (Plugin long display Name)
            String                  m_sComments;        // Comment from the DLL
            String                  m_sProductVersion;  // The version number of the product (GUI shell interface required)
            String                  m_sFileVersion;     // The version number of the plugin
            String                  m_sInternalName;    // The internal name of the plugin
            String                  m_sVendor;          // Vendor(CompanyName) of the plugin
            bool                    m_bLoaded;          // Whether the DLL was loaded
            bool                    m_bDoNotLoad;       // DoNot load the DLL request from the registry
            bool                    m_bUnloading;       // Unloading the plugin
            bool                    m_bInitialized;     // Plugin was Initialized
            bool                    m_bExceptionCaught; // Exception has being caught for this plugin DO NOT use it
            HINSTANCE               m_hInstance;        // DLL instance Handle
            HINSTANCE               m_hParentInstance;  // DLL instance of the plugins parent
            NotifyPtr               m_NotifyFunc;       // Notify function from the DLL
            ReleasePtr              m_ReleaseFunc;      // Release function from the DLL
            void*                   m_ModuleAddress;    // Address the module loaded at
            DWORD                   m_dwModuleSize;     // Size of the loaded module
            DWORD                   m_dwVersion;        // Version of the plugin
            DWORD                   m_dwFlags;          // Flags of the plugin
            DWORD                   m_dwInterface;      // Interface the plugin requires to work
            String                  m_sDLLPath;         // full path to the dll's
            String                  m_sParentSignature; // If we are a mini-plugin, we have a parent to be a sub-plugin of
            TImage*                 m_Icon;             // the icon belonging to a plugin

            HRESULT __fastcall      GetPluginVersionInfo(void);
            HRESULT __fastcall      CheckInterfaceRequirements(void);
            HRESULT __fastcall      CheckPluginSignature(String sRequiredSignature);
            bool    __fastcall      InterestedInEvent(TZX_EVENT Event);

                    __fastcall      ZXPlugin();

        public:

                    __fastcall      ZXPlugin(const String& sFilename, ZXPluginManager* PluginManager);
                    __fastcall     ~ZXPlugin();

            void    __fastcall      ReadLoadOrder(unsigned int& NextAvailableLoadOrder);
            void    __fastcall      AddToOptions(int iNewLoadOrder);
            void    __fastcall      Icon(TImage* Icon)  { if (Icon) m_Icon = Icon; }
            bool    __fastcall      OwnsMemory(void *Address);

            HRESULT __fastcall      Load(GetModuleInformationPtr GetModuleInformation);
            HRESULT __fastcall      Unload(bool bFreeOptions = true);
            HRESULT __fastcall      NotifyEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
            HRESULT __fastcall      RegisterEvent(TZX_EVENT Event);
            HRESULT __fastcall      UnRegisterEvent(TZX_EVENT Event);

            __property unsigned int LoadOrder       = {read = m_iLoadOrder      };
            __property  String      Filename        = {read = m_sFileName       };
            __property  String      Description     = {read = m_sDescription    };
            __property  String      Comments        = {read = m_sComments       };
            __property  String      ProductVersion  = {read = m_sProductVersion };
            __property  String      FileVersion     = {read = m_sFileVersion    };
            __property  String      InternalName    = {read = m_sInternalName   };
            __property  String      Vendor          = {read = m_sVendor         };
            __property  bool        Loaded          = {read = m_bLoaded         };
            __property  bool        DoNotLoad       = {read = m_bDoNotLoad      };
            __property  bool        Unloading       = {read = m_bUnloading      };
            __property  bool        ExceptionCaught = {read = m_bExceptionCaught};
            __property  HINSTANCE   Handle          = {read = m_hInstance       };
            __property  DWORD       Version         = {read = m_dwVersion       };
            __property  DWORD       Flags           = {read = m_dwFlags         };
            __property  DWORD       Interface       = {read = m_dwInterface     };
            __property  DWORD       ModuleSize      = {read = m_dwModuleSize    };
            __property  void*       ModuleAddress   = {read = m_ModuleAddress   };
            __property  String      ParentSignature = {read = m_sParentSignature, write = m_sParentSignature };
            __property  HINSTANCE   ParentInstance  = {read = m_hParentInstance , write = m_hParentInstance  };

            __property ZXPluginManager* PluginManager={read = m_PluginManager };
        };
    }
}
//---------------------------------------------------------------------------
//bool operator<(const ZXPlugin& info1, const ZXPlugin& info2);
//---------------------------------------------------------------------------
#endif
