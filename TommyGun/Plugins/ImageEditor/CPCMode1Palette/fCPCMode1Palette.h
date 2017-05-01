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
#ifndef fCPCMode1PaletteH
#define fCPCMode1PaletteH
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
#include "CPCMode1Palette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace CPCMode1Palette
    {
        //---------------------------------------------------------------------------
        class TfrmCPCMode1Palette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panCPCPalette;
            TLabel *lblCPCPalette;
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
                    Mode1Palette        m_Palette;
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;

            void        __fastcall  OnUpdatePaletteGUI(void);

        public:		// User declarations
                        __fastcall  TfrmCPCMode1Palette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
            void        __fastcall  RefreshPanels(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::CPCMode1Palette::TfrmCPCMode1Palette *frmCPCMode1Palette;
//---------------------------------------------------------------------------
#endif
