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
#ifndef fC64SpritePaletteH
#define fC64SpritePaletteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "..\ZXImageInterface.h"
#include "SpritePalette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace C64SpritePalette
    {
        //---------------------------------------------------------------------------
        class TfrmC64SpritePalette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panC64Palette;
            TLabel *lblC64Palette;
            TLabel *lblC64ScreenColor;
            TLabel *lblC64NormalColor;
            TLabel *lblC64MultiColor1;
            TLabel *lblC64MultiColor2;
            TPanel *panC64ScreenColor;
            TPanel *panC64NormalColor;
            TPanel *panC64MultiColor1;
            TPanel *panC64MultiColor2;
            TLabel *lblResetPalette;
            TImage *imgLogo;
            void __fastcall panC64ScreenColorClick(TObject *Sender);
            void __fastcall lblC64ScreenColorClick(TObject *Sender);
            void __fastcall lblResetPaletteClick(TObject *Sender);
        private:	// User declarations
            SpritePalette           m_Palette;
            ZXImageInterface        m_ImageEditor;
            TZX_HPLUGIN             m_PluginHandle;

            void        __fastcall  OnUpdatePaletteGUI(void);

        public:		// User declarations
                        __fastcall  TfrmC64SpritePalette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
            void        __fastcall  RefreshPanels(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::C64SpritePalette::TfrmC64SpritePalette *frmC64SpritePalette;
//---------------------------------------------------------------------------
#endif
