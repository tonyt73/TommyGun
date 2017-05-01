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
#ifndef ZXStatusBarH
#define ZXStatusBarH
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//- APP ---------------------------------------------------------------------
#include "FrameWorkInterface.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GUI
    {
        typedef struct
        {
            TZX_HPLUGIN         hPlugin;
            String              sDescription;
            int                 iIcon;
            int                 iPosition;
        } TIconInfo;
        typedef std::vector<TIconInfo>  IconVector;
        typedef IconVector::iterator    IconIterator;
        
        class ZXStatusBar
        {
        private:
            TStatusBar*             m_StatusBar;
            TImageList*             m_IconList;
            IconVector              m_Icons;
            TZX_HPLUGIN             m_ActivePlugin;

            void    __fastcall  MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void    __fastcall  MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
            void    __fastcall  DrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel, const TRect &Rect);
            void    __fastcall  DrawPluginIcons(TStatusPanel *Panel, const TRect &Rect);

            IconIterator    __fastcall  FindIcon(TZX_HPLUGIN PluginHandle);

        public:
                    __fastcall  ZXStatusBar();
                    __fastcall ~ZXStatusBar();

            void    __fastcall  Setup(TStatusBar* StatusBar, TImageList* IconList);
            void    __fastcall  Free();
            void    __fastcall  AddPluginIcon           (TZX_HPLUGIN PluginHandle, TImage* Icon, const String& sDescription);
            void    __fastcall  RemovePluginIcon        (TZX_HPLUGIN PluginHandle);
            void    __fastcall  ActivePlugin            (TZX_HPLUGIN PluginHandle);

            HRESULT __fastcall  AddStatusPanel          (TZX_HPLUGIN PluginHandle, unsigned int PanelIndex);
            HRESULT __fastcall  RemoveStatusPanel       (TZX_HPLUGIN PluginHandle, unsigned int PanelIndex);
            HRESULT __fastcall  SetStatusPanelCaption   (TZX_HPLUGIN PluginHandle, unsigned int PanelIndex, const String& Caption);
            HRESULT __fastcall  SetStatusPanelSize      (TZX_HPLUGIN PluginHandle, unsigned int PanelIndex, unsigned int Size);
        };
    }
}
//---------------------------------------------------------------------------
#endif
