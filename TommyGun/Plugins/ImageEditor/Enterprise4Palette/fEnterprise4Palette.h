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
#ifndef fEnterprise4PaletteH
#define fEnterprise4PaletteH
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
#include "Enterprise4Palette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace EnterprisePalette
    {
        //---------------------------------------------------------------------------
        class TfrmEnterprise4Palette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panPalette;
            TLabel *lblPalette;
            TLabel *lblColour0;
            TLabel *lblColour2;
            TLabel *lblColour1;
            TLabel *lblColour3;
            TPanel *panColour0;
            TPanel *panColour2;
            TPanel *panColour1;
            TPanel *panColour3;
            TLabel *lblResetPalette;
    TImage *imgLogo;
            void __fastcall panColour0Click(TObject *Sender);
            void __fastcall lblColour0Click(TObject *Sender);
    void __fastcall lblResetPaletteClick(TObject *Sender);
        private:	// User declarations
                    Enterprise4Palette  m_Palette;
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;

            void        __fastcall  OnUpdatePaletteGUI(void);

        public:		// User declarations
                        __fastcall  TfrmEnterprise4Palette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
            void        __fastcall  RefreshPanels(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::EnterprisePalette::TfrmEnterprise4Palette *frmEnterprise4Palette;
//---------------------------------------------------------------------------
#endif
