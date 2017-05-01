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
#ifndef fEnterprise16PaletteH
#define fEnterprise16PaletteH
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
#include "Enterprise16Palette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace EnterprisePalette
    {
        //---------------------------------------------------------------------------
        class TfrmEnterprise16Palette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panPalette;
            TLabel *lblPalette;
            TLabel *lblColours0to7;
            TLabel *lblColours8to15;
            TPanel *panColour0;
            TPanel *panColour8;
            TPanel *panColour1;
            TPanel *panColour9;
            TPanel *panColour2;
            TPanel *panColourA;
            TPanel *panColour3;
            TPanel *panColourB;
            TPanel *panColour4;
            TPanel *panColourC;
            TPanel *panColour5;
            TPanel *panColourD;
            TPanel *panColour6;
            TPanel *panColourE;
            TPanel *panColour7;
            TPanel *panColourF;
            TLabel *lblResetPalette;
            TImage *imgLogo;
            void __fastcall lblResetPaletteClick(TObject *Sender);
            void __fastcall lblColours0to7Click(TObject *Sender);
            void __fastcall panColour0Click(TObject *Sender);
        private:	// User declarations
                    Enterprise16Palette m_Palette;
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;


        public:		// User declarations
                        __fastcall  TfrmEnterprise16Palette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
            void        __fastcall  RefreshPanels(void);
            void        __fastcall  OnUpdatePaletteGUI(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::EnterprisePalette::TfrmEnterprise16Palette *frmEnterprise16Palette;
//---------------------------------------------------------------------------
#endif
