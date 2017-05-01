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
#ifndef fVic20MultiColorPaletteH
#define fVic20MultiColorPaletteH
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
#include "ZXVic20MultiColorPalette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace Vic20Palette
    {
        //---------------------------------------------------------------------------
        class TfrmVic20MultiColorPalette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panPalette;
            TLabel *lblPalette;
            TImage *imgLogo;
            TLabel *lblResetPalette;
            TLabel *lblVicBackground;
            TLabel *lblVicBorder;
            TLabel *lblVicCharacter;
            TLabel *lblVicAuxiliary;
            TPanel *panVicBackground;
            TPanel *panVicBorder;
            TPanel *panVicCharacter;
            TPanel *panVicAuxiliary;
            void __fastcall lblVicBackgroundClick(TObject *Sender);
            void __fastcall panVicBackgroundClick(TObject *Sender);
            void __fastcall lblResetPaletteClick(TObject *Sender);
        private:	// User declarations
            ZXVic20MultiColorPalette m_Palette;
            ZXImageInterface        m_ImageEditor;
            TZX_HPLUGIN             m_PluginHandle;

            void        __fastcall  OnUpdatePaletteGUI(void);

        public:		// User declarations
                        __fastcall  TfrmVic20MultiColorPalette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
            void        __fastcall  RefreshPanels(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::Vic20Palette::TfrmVic20MultiColorPalette *frmVic20MultiColorPalette;
//---------------------------------------------------------------------------
#endif
