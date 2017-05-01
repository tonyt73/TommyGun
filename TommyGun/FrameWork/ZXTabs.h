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
#ifndef ZXTabsH
#define ZXTabsH
//---------------------------------------------------------------------------
#include "ZXBitmaps.h"
#include "FrameWorkInterface.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace GUI;
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GUI
    {
        typedef struct
        {
            TTabSheet*                  Control;           // the control reference we created for the plugin
            TZX_HPLUGIN                 hOwner;
            // used by std::find to search for tab by handle
            bool operator==(const HWND Handle)
            {
              return this->Control->Handle == Handle;
            }
            // used by std::find to search for tab by control reference
            bool operator==(const TTabSheet* Control)
            {
              return this->Control == Control;
            }
        } TZXTabInfo;
        // vector and vector iterator typedefs
        typedef std::vector<TZXTabInfo>         TZXTabInfoVector;
        typedef TZXTabInfoVector::iterator      TZXTabInfoIterator;
        //---------------------------------------------------------------------------
        class ZXTabs
        {
        private:
            TPageControl*           m_ViewPage;
            TPageControl*           m_OptionsPage;
            TTabSheet*              m_TabSheet;
            TTabSheet*              m_StartPage;

            TZXTabInfoVector        m_Tabs;
            ZXBitmaps               m_Bitmaps;

            TTabSheet*  __fastcall  FindTabControl(TZX_HPLUGIN PluginHandle, HWND Handle, bool Access, HRESULT& hResult);
            void        __fastcall  TabOnShow(TObject *Sender);
            void        __fastcall  TabOnHide(TObject *Sender);

        public:
                        __fastcall  ZXTabs();
                        __fastcall ~ZXTabs();

            void        __fastcall  Setup           (TPageControl* ViewPage,
                                                     TPageControl* OptionsPage,
                                                     TImageList*   Images);
            void        __fastcall  Free            (void);
            void        __fastcall  Free            (TZX_HPLUGIN PluginHandle);
            void        __fastcall  ActivatePlugin  (TZX_HPLUGIN PluginHandle);
            bool        __fastcall  IsActivePlugin  (TZX_HPLUGIN PluginHandle);

            HRESULT     __fastcall  AddTab          (TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Caption);
            HRESULT     __fastcall  RemoveTab       (TZX_HPLUGIN PluginHandle, HWND  Handle);
            HRESULT     __fastcall  SetTabBitmap    (TZX_HPLUGIN PluginHandle, HWND  Handle, TImage* Bitmap);

            HRESULT     __fastcall  AddOptionsTab   (TZX_HPLUGIN PluginHandle, TWinControl*& VCLParent, const String& Name);
        };
    }
}
//---------------------------------------------------------------------------
#endif
