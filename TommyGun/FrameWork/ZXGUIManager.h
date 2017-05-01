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
#ifndef ZXGUIManagerH
#define ZXGUIManagerH
//- VCL ---------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//- APP ---------------------------------------------------------------------
#include "fMain.h"
#include "fOptions.h"
#include "fSplash.h"
#include "ZXTabs.h"
#include "ZXStatusBar.h"
#include "ZXMessageBox.h"
#include <KXmlInfo.h>
//-- CONSTANTS --------------------------------------------------------------
const int   g_msgCancel    = 0;
const int   g_msgQueryNo   = 1;
const int   g_msgQueryYes  = 2;
const int   g_iOutlookTab  = 128;
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GUI
    {
        class ZXGUIManager
        {
        private:
            // the VCL form objects
            TfrmMain*                           m_frmMain;
            TfrmOptions*                        m_frmOptions;
            TfrmSplash*                         m_frmSplash;
            ZXStatusBar                         m_StatusBar;
            // the handlers for items on the main form
            ZXTabs                              m_Tabs;
            // the PSAPI dll hInstance reference
            HINSTANCE                           m_hInst_PSAPI;          // hInstance for PSAPI.DLL
            DWORD                               m_dwSplashStartTime;

            void        __fastcall  ResetStatusSlots        (void);
            void        __fastcall  OnMenuClick             (TObject* Sender);

        public:
                        __fastcall  ZXGUIManager();
                        __fastcall ~ZXGUIManager();

            bool        __fastcall  Initialize(void);
            void        __fastcall  Release(void);
            void        __fastcall  Free                    (TZX_HPLUGIN PluginHandle, bool bFreeOptions = true);
            void        __fastcall  FreeOptions             (void);
            void        __fastcall  AddPluginIcon           (TZX_HPLUGIN PluginHandle, TImage* Icon, const String& sDescription);
            void        __fastcall  RemovePluginIcon        (TZX_HPLUGIN PluginHandle);
            void        __fastcall  OptionsPluginsClear     (void);
            void        __fastcall  OptionsPluginsAdd       (TZX_HPLUGIN PluginHandle, String sName, String sRegName, String sVendor, String sPluginVersion, String sFileVersion, bool bIsUnloadable, bool bDoNotLoad, bool dDoNotShow, DWORD dwPriority, int iLoadOrder, TImage* Icon);
            void        __fastcall  OptionsChanged          (void);
            void        __fastcall  OptionsUpdate           (void);
            void        __fastcall  OptionsShow             (void);
            bool        __fastcall  ShowSplash              (void);
            void        __fastcall  HideSplash              (void);
            KRegistry*  __fastcall  Registry                (void);
            bool        __fastcall  IsClosing               (void);
            void        __fastcall  PerformVerbCommand      (TZX_EVENT Event);
            void        __fastcall  SwitchToPlugin          (TZX_HPLUGIN PluginHandle);
            int         __fastcall  ShowMessage             (ZXMessageBoxType eType, const String& sTitle, const String& sBrief, const String& sDetails, const String& sButton1, const String& sButton2, const String& sButton3);
            void        __fastcall  ShowGeneralMessage      (const AnsiString& Title, const AnsiString& Problem, const String& File, const String& Function, int Line);
            void        __fastcall  Refresh                 (void);
            String      __fastcall  ReadMachineFolder       (void);
            void        __fastcall  WriteMachineFolder      (const String& sMachineFolder);

            //
            // TAB INTERFACES
            //
            HRESULT     __fastcall AddTab                   (TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Caption);
            HRESULT     __fastcall RemoveTab                (TZX_HPLUGIN PluginHandle, HWND  Handle);
            HRESULT     __fastcall SetTabBitmap             (TZX_HPLUGIN PluginHandle, HWND  Handle, TImage* SmallImage, TImage* LargeImage);

            //
            // MENU INTERFACES
            //
            HRESULT     __fastcall  AddMenu                 (const String& sCaption, TMenuItem*& pMenu);

            //
            // STATUS BAR INTERFACES
            //
            HRESULT     __fastcall SetStatusSlot            (TZX_HPLUGIN PluginHandle, const String& sText, unsigned int iSlot);

            HRESULT     __fastcall IsActivePlugin           (TZX_HPLUGIN PluginHandle);
            void        __fastcall ResetActivePlugin        (void);
            
            //
            // OPTIONS PAGE INTERFACES
            //
            HRESULT     __fastcall  AddOptionsTab           (TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Name);

            //
            // PROJECT INTERFACES
            //
            void        __fastcall  ProjectActive           (bool bProjectOpened);
            void        __fastcall  ProjectTitle            (const String& Title);

            //
            // XML INTERFACES
            //
            void        __fastcall  XmlInitialize           (KXmlInfo* xmlInfo);
            void        __fastcall  AddUndo                 (KXmlInfo* xmlInfo, DWORD UndoType);
        };
    }
}
//---------------------------------------------------------------------------
extern Scorpio::GUI::ZXGUIManager g_GuiManager;
//---------------------------------------------------------------------------
#endif
