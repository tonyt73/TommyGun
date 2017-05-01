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
#ifndef fCPCMode2PaletteH
#define fCPCMode2PaletteH
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
#include "CPCMode2Palette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace CPCMode2Palette
    {
        //---------------------------------------------------------------------------
        class TfrmCPCMode2Palette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panCPCPalette;
            TLabel *lblCPCPalette;
    TLabel *lblColour0;
    TLabel *lblColour1;
            TPanel *panColour0;
            TPanel *panColour1;
    TLabel *lblResetPalette;
    TImage *imgLogo;
            void __fastcall panColour0Click(TObject *Sender);
            void __fastcall lblColour0Click(TObject *Sender);
            void __fastcall lblResetPaletteClick(TObject *Sender);
        private:	// User declarations
                    Mode2Palette        m_Palette;
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;

            void        __fastcall  OnUpdatePaletteGUI(void);

        public:		// User declarations
                        __fastcall  TfrmCPCMode2Palette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);

            void        __fastcall  RefreshPanels(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::CPCMode2Palette::TfrmCPCMode2Palette *frmCPCMode2Palette;
//---------------------------------------------------------------------------
#endif
