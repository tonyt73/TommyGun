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
#ifndef ZXEventManagerH
#define ZXEventManagerH
//---------------------------------------------------------------------------
#include <map>
#include "..\..\Framework\FrameWorkInterface.h"
#include "ZXPlugin.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace Plugin
    {
        class ZXEventManager;
        typedef HRESULT(WINAPI *EventHandlerPtr)(ZXEventManager* EventManager, LPDATA Data, DWORD Param, DWORD Arg);
        //---------------------------------------------------------------------------
        __declspec ( dllexport ) class ZXEventManager
        {
        private:

            typedef std::map<TZX_EVENT, EventHandlerPtr>  ZXEventHandlers;
            typedef ZXEventHandlers::value_type ZXEventRelationship;
            typedef ZXEventHandlers::iterator ZXEventIterator;

            ZXEventHandlers     m_EventHandlers;
            //TZX_HPLUGIN         m_PluginHandle;

        protected:
            ZXPlugin*           m_pPlugin;

        public:
                                __fastcall  ZXEventManager();
            virtual             __fastcall ~ZXEventManager();

            virtual void        __fastcall  RegisterEvents(void) = 0;

                    void        __fastcall  InitialiseEvents(ZXPlugin* pPlugin);
                    void        __fastcall  ReleaseEvents(void);
                    TZX_HPLUGIN __fastcall  PluginHandle(void);
                    void        __fastcall  RegisterEvent(TZX_EVENT Event, EventHandlerPtr EventHandler);
                    void        __fastcall  UnRegisterEvent(TZX_EVENT Event);
                    void        __fastcall  UnRegisterEvents(void);
                    HRESULT     __fastcall  ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg);
                    HRESULT     __fastcall  NotifyEvent(TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg);
        };
    }
}
//---------------------------------------------------------------------------
#endif

