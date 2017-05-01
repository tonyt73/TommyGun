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
#ifndef fCPCMode0PaletteH
#define fCPCMode0PaletteH
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
#include "CPCMode0Palette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace CPCMode0Palette
    {
        //---------------------------------------------------------------------------
        class TfrmCPCMode0Palette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panCPCPalette;
            TLabel *lblCPCPalette;
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
                    Mode0Palette        m_Palette;
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;

            void        __fastcall  OnUpdatePaletteGUI(void);

        public:		// User declarations
                        __fastcall  TfrmCPCMode0Palette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
            void        __fastcall  RefreshPanels(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::CPCMode0Palette::TfrmCPCMode0Palette *frmCPCMode0Palette;
//---------------------------------------------------------------------------
#endif
