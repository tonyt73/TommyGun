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
#ifndef ZXPluginManagerH
#define ZXPluginManagerH
//---------------------------------------------------------------------------
#include "ZXPlugin.h"
#include <KXmlInfo.h>
//---------------------------------------------------------------------------
namespace Scorpio
{
    #ifdef USE_GUI_MANAGER
    namespace GUI
    {
        class ZXGUIManager;
    }
    #endif
    namespace Plugin
    {
        #ifdef USE_GUI_MANAGER
        using namespace GUI;
        #endif
        class ZXPlugin;
        //---------------------------------------------------------------------------
        typedef std::vector<ZXPlugin*>      ZXPluginsVector;
        typedef ZXPluginsVector::iterator   ZXPluginsIterator;
        typedef void __fastcall (__closure *ZXQuerySaveEvent)(bool& bSaved);
        typedef void __fastcall (__closure *ZXQueryProjectFolderEvent)(String& sFolder);
        //---------------------------------------------------------------------------
        #ifndef USE_GUI_MANAGER
        __declspec( dllexport)
        #endif
        class ZXPluginManager
        {
        private:
            typedef BOOL   (WINAPI *GetModuleInformationPtr)(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb);
            // GetModuleInformation Pointer
            ZXQuerySaveEvent                    FOnQuerySave;
            ZXQueryProjectFolderEvent           FOnQueryProjectFolder;
            
            GetModuleInformationPtr             m_GetModuleInformation;
            /// Loaded Plugins list
            #ifdef USE_GUI_MANAGER
            ZXGUIManager*                       m_pGuiManager;          // The gui manager to use
            #else
            void*                               m_pGuiManager;          // dummy gui manager pointe
            #endif
            ZXPluginsVector                     m_Plugins;              // list of the plugins loaded
            TZX_HPLUGIN                         m_Handle;
            TZX_HPLUGIN                         m_ActivePlugin;
            HINSTANCE                           m_hInst_PSAPI;
            bool                                m_bLoading;
            int                                 m_PluginsLoaded;
            unsigned int                        m_iPluginGetNextIndex;
            String                              m_sPluginExtension;

            void                    __fastcall  LocatePlugins               (void);
            void                    __fastcall  OrderPlugins                (void);
            void                    __fastcall  LoadPluginsInOrder          (void);
            void                    __fastcall  RemoveUnloadedPlugins       (void);
            void                    __fastcall  ReorderLoadedPlugins        (void);
            void                    __fastcall  RemoveDoNotLoadPlugins      (void);
            HRESULT                 __fastcall  GetPluginVersionInfo        (ZXPluginsIterator& PluginIt);
            HRESULT                 __fastcall  CheckInterfaceRequirements  (ZXPluginsIterator& PluginIt);
            void                    __fastcall  AddPluginsDirectoryToPath   (void);
            void                    __fastcall  LoadPSAPI                   (void);
            void                    __fastcall  PerformVerbCommand          (TZX_EVENT Event);
            ZXPluginsIterator       __fastcall  FindPlugin                  (TZX_HPLUGIN PluginHandle);
            ZXPluginsIterator       __fastcall  FindPlugin                  (const String& sFilename);
            void                    __fastcall  SortPlugins                 (void);

        public:
                                    #ifdef USE_GUI_MANAGER
                                    __fastcall  ZXPluginManager             (ZXGUIManager* pGuiManager, const String& sPluginExtension);
                                    #else
                                    __fastcall  ZXPluginManager             (const String& sPluginExtension);
                                    #endif

            bool                    __fastcall  Initialize                  (HINSTANCE hInstance);
            void                    __fastcall  Release                     (void);

                                    #ifdef USE_GUI_MANAGER
            int                     __fastcall  LoadPlugins                 (void);
                                    #else
            int                     __fastcall  LoadPlugins                 (HINSTANCE hParentInstance, const String& sSignature);
            void                    __fastcall  LoadPluginsFound            (HINSTANCE hParentInstance, const String& sSignature);
                                    #endif
            void                    __fastcall  UnloadPlugins               (void);
            ZXPlugin*               __fastcall  CheckException              (void);
            void                    __fastcall  InitiatePlugins             (void);
            ZXPluginsIterator       __fastcall  UnloadPlugin                (const ZXPluginsIterator& PluginIt, bool bFreeOptions = true);
            bool                    __fastcall  IsPluginValid               (TZX_HPLUGIN PluginHandle);
            void                    __fastcall  SetPluginIcon               (TZX_HPLUGIN PluginHandle, TImage* Icon);

            ZXPlugin*               __fastcall  GetFirstPlugin              (void);
            ZXPlugin*               __fastcall  GetNextPlugin               (void);


            // broadcast to all plugins except the transmitter
            HRESULT                 __fastcall  Notify                      (TZX_HPLUGIN Plugin, TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
            HRESULT                 __fastcall  NotifyPlugin                (TZX_HPLUGIN Plugin, TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
            HRESULT                 __fastcall  NotifyPlugin                (TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);

            HRESULT                 __fastcall  RegisterPluginEvent         (TZX_HPLUGIN PluginHandle, TZX_EVENT Event);
            HRESULT                 __fastcall  UnRegisterPluginEvent       (TZX_HPLUGIN PluginHandle, TZX_EVENT Event);

            void                    __fastcall  XmlNotify                   (TZX_EVENT XmlEvent, const String& sNode = String(), KXmlInfo* xmlInfo = NULL);

            __property bool                     IsLoading                   = { read = m_bLoading       };
            __property TZX_HPLUGIN              Handle                      = { read = m_Handle         };
            __property int                      PluginsLoaded               = { read = m_PluginsLoaded  };
            #ifdef USE_GUI_MANAGER
            __property ZXGUIManager*            GuiManager                  = { read = m_pGuiManager    };
            #else
            __property void*                    GuiManager                  = { read = m_pGuiManager    };
            #endif

        	__property ZXQuerySaveEvent             OnQuerySave             = { read = FOnQuerySave, write = FOnQuerySave                    };
            __property ZXQueryProjectFolderEvent    OnQueryProjectFolder   = { read = FOnQueryProjectFolder, write = FOnQueryProjectFolder  };
        };
    }
}
//---------------------------------------------------------------------------
extern Scorpio::Plugin::ZXPluginManager g_PluginManager;
//---------------------------------------------------------------------------
#endif
