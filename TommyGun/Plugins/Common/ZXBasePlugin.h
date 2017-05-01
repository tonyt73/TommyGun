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
#ifndef BasePluginH
#define BasePluginH
#include "..\..\Framework\FrameWorkInterface.h"
#include "ZXEventManager.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace Plugin
    {
        //---------------------------------------------------------------------------
        /**
         * @class ZXBasePlugin
         * @brief This is a base class for all plugins, that wish to use the core event manager.
         * This class presents a plugin interface for all KiwiWare plugins. There are only
         * 2 virtual interfaces that must be implemented, Initialise() and Release(), all
         * the other interfaces are optional and have a default implementation.
         * @remarks I have placed the code in the header file so that it can be easily maintained
         * and I won't have to copy a cpp file into all plugin directories.
         */
        //---------------------------------------------------------------------------
        __declspec ( dllexport ) class ZXBasePlugin : public ZXEventManager
        {
        protected:
            bool    m_bReleased;

        public:
                                __fastcall  ZXBasePlugin();
            virtual             __fastcall ~ZXBasePlugin();

                     //HRESULT    __fastcall  Initialise          (TZX_HPLUGIN PluginHandle);
                     HRESULT    __fastcall  Initialise          (ZXPlugin* pPlugin);
                     HRESULT    __fastcall  Release             (void);
            virtual  HRESULT    __fastcall  InitialisePlugin    (ZXPlugin* pPlugin) = 0;
            virtual  HRESULT    __fastcall  ReleasePlugin       (void) = 0;
        };
    }
}
//---------------------------------------------------------------------------
#endif
