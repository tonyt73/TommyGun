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
#ifndef ZXCodeInterfaceH
#define ZXCodeInterfaceH
//-- VCL --------------------------------------------------------------------
//#include <Classes.hpp>
//#include <Controls.hpp>
//#include <StdCtrls.hpp>
//#include <ComCtrls.hpp>
#include <Unknwn.h>
//---------------------------------------------------------------------------
#include "..\Common\ZXTypes.h"
#include "ZXImage.h"
#include "ZXImageManager.h"
#include "ZXImageNotifications.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Imaging;
using namespace Interface;
//---------------------------------------------------------------------------
#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES
typedef enum { mbtError, mbtWarning , mbtInformation, mbtQuestion } ZXMessageBoxType;
#endif
//---------------------------------------------------------------------------
typedef int    (WINAPI *StdCallPtr              )(void              );
// image plugin interfaces
typedef HRESULT(WINAPI *RegisterPluginEventPtr  )(TZX_HPLUGIN PluginHandle, TZX_EVENT Event);
typedef HRESULT(WINAPI *NotifyPtr               )(TZX_HPLUGIN PluginHandle, TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg);
// codeparser interfaces
typedef HRESULT(WINAPI *SystemRefreshViewPtr    )(TZX_HPLUGIN PluginHandle);
typedef HRESULT(WINAPI *SystemUpdateImagePtr    )(TZX_HPLUGIN PluginHandle, ZXImage*   Image  );
typedef HRESULT(WINAPI *SystemAddToolBarPtr     )(TZX_HPLUGIN PluginHandle, TToolBar*  ToolBar);
typedef HRESULT(WINAPI *SystemMessageBoxPtr     )(ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3, int& iAnswer );
// other interfaces
typedef HRESULT(WINAPI *ToolMergePaintToolBarPtr)(TZX_HPLUGIN PluginHandle, TToolBar*  ToolBar);
// imagetype interfaces
typedef HRESULT(WINAPI *TypeAddTabPtr           )(TZX_HPLUGIN PluginHandle, const String& sCaption, Graphics::TBitmap* pBitmap, TTabSheet*& pTabSheet);
typedef HRESULT(WINAPI *TypeGetImageManagerPtr  )(TZX_HPLUGIN PluginHandle, ZXImageManager*& pImageManager);
typedef HRESULT(WINAPI *TypeSelectImagePtr      )(TZX_HPLUGIN PluginHandle, const String& sOwner, int iIndex, int iFrame);
// imagepalette interfaces
// imageimport interfaces
// imageexport interfaces
//---------------------------------------------------------------------------
// Obtains the ImageEditor interfaces
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace ImageEditor
    {
        class ZXImageInterface
        {
        private:
            // plugin interfaces
            RegisterPluginEventPtr      m_RegisterPluginEventFunc;
            NotifyPtr                   m_NotifyFunc;
            // system interfaces
            SystemUpdateImagePtr        m_SystemUpdateImageFunc;
            SystemRefreshViewPtr        m_SystemRefreshViewFunc;
            SystemAddToolBarPtr         m_SystemAddToolBarFunc;
            SystemMessageBoxPtr         m_SystemMessageBoxFunc;
            // tools interfaces
            ToolMergePaintToolBarPtr    m_ToolMergePaintToolBarFunc;
            // type interfaces
            TypeAddTabPtr               m_TypeAddTabFunc;
            TypeGetImageManagerPtr      m_TypeGetImageManagerFunc;
            TypeSelectImagePtr          m_TypeSelectImageFunc;

        public:
                    __fastcall  ZXImageInterface();

            void    __fastcall  GetInterfaces(HINSTANCE hInstance);
            // plugin interface methods
            HRESULT __fastcall RegisterPluginEvent  (TZX_HPLUGIN PluginHandle, TZX_EVENT Event);
            HRESULT __fastcall Notify               (TZX_HPLUGIN PluginHandle, TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg);
            // system interface methods
            HRESULT __fastcall SystemRefreshView    (TZX_HPLUGIN PluginHandle);
            HRESULT __fastcall SystemUpdateImage    (TZX_HPLUGIN PluginHandle, ZXImage*   Image  );
            HRESULT __fastcall SystemAddToolBar     (TZX_HPLUGIN PluginHandle, TToolBar*  ToolBar);
            HRESULT __fastcall SystemMessageBox     (ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3, int& iAnswer );
            // tool interface methods
            HRESULT __fastcall ToolMergePaintToolBar(TZX_HPLUGIN PluginHandle, TToolBar* ToolBar);
            // type interface methods
            HRESULT __fastcall TypeAddTab           (TZX_HPLUGIN PluginHandle, const String& sCaption, Graphics::TBitmap* pBitmap, TTabSheet*& pTabSheet);
            HRESULT __fastcall TypeGetImageManager  (TZX_HPLUGIN PluginHandle, ZXImageManager*& pImageManager);
            HRESULT __fastcall TypeSelectImage      (TZX_HPLUGIN PluginHandle, const String& sOwner, int iIndex, int iFrame);
        };
    }
}
//---------------------------------------------------------------------------
#endif
