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
__fastcall ZXBasePlugin::ZXBasePlugin()
: m_bReleased(false)
{
    RL_METHOD
}
//---------------------------------------------------------------------------
__fastcall ZXBasePlugin::~ZXBasePlugin()
{
    RL_METHOD
    Release();
}
//---------------------------------------------------------------------------
/*HRESULT __fastcall ZXBasePlugin::Initialise(TZX_HPLUGIN PluginHandle)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    InitialisePlugin(PluginHandle);
    InitialiseEvents(PluginHandle);
    return hResult;
}*/
//---------------------------------------------------------------------------
HRESULT __fastcall ZXBasePlugin::Initialise(ZXPlugin* pPlugin)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    m_pPlugin = pPlugin;
    hResult = InitialisePlugin(pPlugin);
    if (SUCCEEDED(hResult))
    {
        InitialiseEvents(pPlugin);
    }
    return hResult;
}
//---------------------------------------------------------------------------
/*HRESULT __fastcall ZXBasePlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    return E_FAIL;
}*/
//---------------------------------------------------------------------------
HRESULT __fastcall ZXBasePlugin::Release(void)
{
    RL_METHOD
    RL_HRESULT(S_FALSE)
    if (false == m_bReleased)
    {
        m_bReleased = true;
        ReleaseEvents();
        ReleasePlugin();
    }
    return hResult;
}
//---------------------------------------------------------------------------

