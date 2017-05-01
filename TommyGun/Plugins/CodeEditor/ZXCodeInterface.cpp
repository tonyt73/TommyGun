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
#pragma hdrstop
//---------------------------------------------------------------------------
#include "..\..\SafeMacros.h"
//---------------------------------------------------------------------------
#include "ZXLogFile.h"
#include "ZXImageInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Logging;
using namespace ImageEditor;
//---------------------------------------------------------------------------
__fastcall ZXImageInterface::ZXImageInterface()
: m_SystemUpdateImageFunc(NULL),
  m_SystemRefreshViewFunc(NULL),
  m_SystemAddToolBarFunc(NULL)
{
}
//---------------------------------------------------------------------------
void __fastcall ZXImageInterface::GetInterfaces(HINSTANCE hInstance)
{
    // PLUGIN INTERFACES
    m_RegisterPluginEventFunc   = reinterpret_cast<RegisterPluginEventPtr   >(GetProcAddress(hInstance, "IERegisterPluginEvent"   ));
    if(m_RegisterPluginEventFunc)   ZX_LOG_INFO(lfPlugin, "RegisterPluginEvent() found") else ZX_LOG_ERROR(lfPlugin, "IERegisterPluginEvent() NOT found");
    m_NotifyFunc                = reinterpret_cast<NotifyPtr                >(GetProcAddress(hInstance, "IENotify"   ));
    if(m_NotifyFunc)   ZX_LOG_INFO(lfPlugin, "IENotify() found") else ZX_LOG_ERROR(lfPlugin, "IENotify() NOT found");
    // SYSTEM INTERFACES
    m_SystemUpdateImageFunc     = reinterpret_cast<SystemUpdateImagePtr     >(GetProcAddress(hInstance, "SystemUpdateImage"         ));
    if(m_SystemUpdateImageFunc)     ZX_LOG_INFO(lfPlugin, "SystemUpdateImage() found") else ZX_LOG_ERROR(lfPlugin, "SystemUpdateImage() NOT found");
    m_SystemRefreshViewFunc     = reinterpret_cast<SystemRefreshViewPtr     >(GetProcAddress(hInstance, "SystemRefreshView"         ));
    if(m_SystemRefreshViewFunc)     ZX_LOG_INFO(lfPlugin, "SystemRefreshView() found") else ZX_LOG_ERROR(lfPlugin, "SystemRefreshView() NOT found");
    m_SystemAddToolBarFunc      = reinterpret_cast<SystemAddToolBarPtr      >(GetProcAddress(hInstance, "SystemAddToolBar"          ));
    if(m_SystemAddToolBarFunc)      ZX_LOG_INFO(lfPlugin, "SystemAddToolBar() found") else ZX_LOG_ERROR(lfPlugin, "SystemAddToolBar() NOT found");
    m_SystemMessageBoxFunc      = reinterpret_cast<SystemMessageBoxPtr      >(GetProcAddress(hInstance, "SystemMessageBox"          ));
    if(m_SystemMessageBoxFunc)      ZX_LOG_INFO(lfPlugin, "SystemMessageBox() found") else ZX_LOG_ERROR(lfPlugin, "SystemMessageBox() NOT found");
    // IMAGETOOL INTERFACES
    m_ToolMergePaintToolBarFunc = reinterpret_cast<ToolMergePaintToolBarPtr >(GetProcAddress(hInstance, "ToolMergePaintToolBar"     ));
    if(m_ToolMergePaintToolBarFunc) ZX_LOG_INFO(lfPlugin, "ToolMergePaintToolBar() found") else ZX_LOG_ERROR(lfPlugin, "ToolMergePaintToolBar() NOT found");
    // IMAGETYPE INTERFACES
    m_TypeAddTabFunc            = reinterpret_cast<TypeAddTabPtr            >(GetProcAddress(hInstance, "TypeAddTab"                ));
    if(m_TypeAddTabFunc)            ZX_LOG_INFO(lfPlugin, "TypeAddTab() found") else ZX_LOG_ERROR(lfPlugin, "TypeAddTab() NOT found");
    m_TypeGetImageManagerFunc   = reinterpret_cast<TypeGetImageManagerPtr   >(GetProcAddress(hInstance, "TypeGetImageManager"       ));
    if(m_TypeGetImageManagerFunc)   ZX_LOG_INFO(lfPlugin, "TypeGetImageManager() found") else ZX_LOG_ERROR(lfPlugin, "TypeGetImageManager() NOT found");
    m_TypeSelectImageFunc       = reinterpret_cast<TypeSelectImagePtr       >(GetProcAddress(hInstance, "TypeSelectImage"           ));
    if(m_TypeSelectImageFunc)       ZX_LOG_INFO(lfPlugin, "TypeSelectImage() found") else ZX_LOG_ERROR(lfPlugin, "TypeSelectImage() NOT found");
    // IMAGEIMPORT INTERFACE

    // IMAGEEXPORT IMTERFACES

    // IMAGEPALETTE INTERFACES
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::SystemUpdateImage(TZX_HPLUGIN PluginHandle, ZXImage* Image)
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_SystemUpdateImageFunc)))
    {
        hResult = m_SystemUpdateImageFunc(PluginHandle, Image);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::SystemRefreshView(TZX_HPLUGIN PluginHandle)
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_SystemRefreshViewFunc)))
    {
        hResult = m_SystemRefreshViewFunc(PluginHandle);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::SystemAddToolBar(TZX_HPLUGIN PluginHandle, TToolBar* ToolBar)
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_SystemAddToolBarFunc)))
    {
        hResult = m_SystemAddToolBarFunc(PluginHandle, ToolBar);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::ToolMergePaintToolBar(TZX_HPLUGIN PluginHandle, TToolBar* ToolBar)
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_ToolMergePaintToolBarFunc)))
    {
        hResult = m_ToolMergePaintToolBarFunc(PluginHandle, ToolBar);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::TypeAddTab(TZX_HPLUGIN PluginHandle, const String& sCaption, Graphics::TBitmap* pBitmap, TTabSheet*& pTabSheet)
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_TypeAddTabFunc)))
    {
        hResult = m_TypeAddTabFunc(PluginHandle, sCaption, pBitmap, pTabSheet);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::TypeGetImageManager(TZX_HPLUGIN PluginHandle, ZXImageManager*& pImageManager)
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_TypeGetImageManagerFunc)))
    {
        hResult = m_TypeGetImageManagerFunc(PluginHandle, pImageManager);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::TypeSelectImage(TZX_HPLUGIN PluginHandle, const String& sOwner, int iIndex, int iFrame)
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_TypeSelectImageFunc)))
    {
        hResult = m_TypeSelectImageFunc(PluginHandle, sOwner, iIndex, iFrame);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::SystemMessageBox(ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3, int& iAnswer )
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_SystemMessageBoxFunc)))
    {
        hResult = m_SystemMessageBoxFunc(eType, sTitle, sBrief, sDetails, sButton1, sButton2, sButton3, iAnswer);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::RegisterPluginEvent(TZX_HPLUGIN PluginHandle, TZX_EVENT Event)
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_RegisterPluginEventFunc)))
    {
        hResult = m_RegisterPluginEventFunc(PluginHandle, Event);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageInterface::Notify(TZX_HPLUGIN PluginHandle, TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(m_NotifyFunc)))
    {
        hResult = m_NotifyFunc(PluginHandle, Event, lpData, dwParam, dwArg);
    }
    return hResult;
}
//---------------------------------------------------------------------------

