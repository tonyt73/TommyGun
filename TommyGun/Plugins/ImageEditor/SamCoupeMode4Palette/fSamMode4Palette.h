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
#ifndef fSamMode4PaletteH
#define fSamMode4PaletteH
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
#include "SamMode4Palette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace SamMode4Palette
    {
        //---------------------------------------------------------------------------
        class TfrmSamMode4Palette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panSamPalette;
            TLabel *lblSamPalette;
            TLabel *lblColours0to7;
            TLabel *lblColours8to15;
            TPanel *panColour0;
            TPanel *panColour8;
            TPanel *panColour1;
            TPanel *panColour9;
            TPanel *panColour2;
            TPanel *panColour10;
            TPanel *panColour3;
            TPanel *panColour11;
            TPanel *panColour4;
            TPanel *panColour12;
            TPanel *panColour5;
            TPanel *panColour13;
            TPanel *panColour6;
            TPanel *panColour14;
            TPanel *panColour7;
            TPanel *panColour15;
            TLabel *lblResetPalette;
    TImage *imgLogo;
            void __fastcall panColour0Click(TObject *Sender);
            void __fastcall lblColours0to7Click(TObject *Sender);
            void __fastcall lblResetPaletteClick(TObject *Sender);
        private:	// User declarations
                    Mode4Palette        m_Palette;
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;

            void        __fastcall  OnUpdatePaletteGUI(void);

        public:		// User declarations
                        __fastcall  TfrmSamMode4Palette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
            void        __fastcall  RefreshPanels(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::SamMode4Palette::TfrmSamMode4Palette *frmSamMode4Palette;
//---------------------------------------------------------------------------
#endif
