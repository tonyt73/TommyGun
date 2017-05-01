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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Plugin;
//---------------------------------------------------------------------------
__fastcall ZXEventManager::ZXEventManager()
: m_pPlugin(NULL)
{
    RL_METHOD
}
//---------------------------------------------------------------------------
__fastcall ZXEventManager::~ZXEventManager()
{
    RL_METHOD
    // clear the unregistered events
    UnRegisterEvents();
}
//---------------------------------------------------------------------------
void __fastcall ZXEventManager::InitialiseEvents(ZXPlugin* pPlugin)
{
    RL_METHOD
    m_pPlugin = pPlugin;
    RegisterEvents();
}
//---------------------------------------------------------------------------
void __fastcall ZXEventManager::ReleaseEvents(void)
{
    RL_METHOD
    // clear the unregistered events
    UnRegisterEvents();
}
//---------------------------------------------------------------------------
TZX_HPLUGIN __fastcall ZXEventManager::PluginHandle(void)
{
    RL_METHOD
    return m_pPlugin->Handle;
}
//---------------------------------------------------------------------------
void __fastcall ZXEventManager::RegisterEvent(TZX_EVENT Event, EventHandlerPtr EventHandler)
{
    RL_METHOD
    if (true == SAFE_PTR(m_pPlugin))
    {
        ZXEventIterator it = m_EventHandlers.find(Event);
        if (it == m_EventHandlers.end())
        {
            // add the new event handler
            m_EventHandlers.insert(ZXEventRelationship(Event, EventHandler));
            m_pPlugin->PluginManager->RegisterPluginEvent(m_pPlugin->Handle, Event);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXEventManager::UnRegisterEvent(TZX_EVENT Event)
{
    RL_METHOD
    if (true == SAFE_PTR(m_pPlugin))
    {
        ZXEventIterator it = m_EventHandlers.find(Event);
        if (it != m_EventHandlers.end())
        {
            // remove the event
            m_pPlugin->PluginManager->UnRegisterPluginEvent(m_pPlugin->Handle, it->first);
            m_EventHandlers.erase(it);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXEventManager::UnRegisterEvents(void)
{
    RL_METHOD
    // clear the registered events
    while(0 != m_EventHandlers.size())
    {
        m_pPlugin->PluginManager->UnRegisterPluginEvent(m_pPlugin->Handle, m_EventHandlers.begin()->first);
        m_EventHandlers.erase(m_EventHandlers.begin()->first);
    }
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXEventManager::ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_METHOD
    RL_HRESULT(S_FALSE);
    ZXEventIterator it = m_EventHandlers.find(Event);
    if (it != m_EventHandlers.end())
    {
        // process the event
        hResult = it->second(this, lpData, dwParam, dwArg);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXEventManager::NotifyEvent(TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_METHOD
    RL_HRESULT(S_FALSE);
    if (true == SAFE_PTR(m_pPlugin))
    {
        hResult = m_pPlugin->PluginManager->Notify(m_pPlugin->Handle, Event, lpData, dwParam, dwArg);
    }
    return hResult;
}
//---------------------------------------------------------------------------

