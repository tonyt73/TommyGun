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
#ifndef fMSX16PaletteH
#define fMSX16PaletteH
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
#include "MSX16Palette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace MSXPalette
    {
        //---------------------------------------------------------------------------
        class TfrmMSX16Palette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panMSX16Palette;
            TLabel *lblMSXPalette;
            TLabel *lblPaletteInk;
            TLabel *lblPalettePaper;
            TSpeedButton *spdInkBlack;
            TSpeedButton *spdInkBlue;
            TSpeedButton *spdInkRed;
            TSpeedButton *spdInkPurple;
            TSpeedButton *spdInkGreen;
            TSpeedButton *spdInkCyan;
            TSpeedButton *spdInkYellow;
            TSpeedButton *spdInkWhite;
            TSpeedButton *spdInkTransparent;
            TSpeedButton *spdPaperBlack;
            TSpeedButton *spdPaperBlue;
            TSpeedButton *spdPaperRed;
            TSpeedButton *spdPaperPurple;
            TSpeedButton *spdPaperGreen;
            TSpeedButton *spdPaperCyan;
            TSpeedButton *spdPaperYellow;
            TSpeedButton *spdPaperWhite;
            TSpeedButton *spdPaperTransparent;
            TImage *imgPaletteTransparent;
            TLabel *lblPaletteTransparent;
            TImage *imgLogo;
            void __fastcall spdInkBlackClick(TObject *Sender);
            void __fastcall spdPaperBlackClick(TObject *Sender);
        private:	// User declarations
                    MSX16Palette     m_Palette;
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;

            void        __fastcall  OnUpdatePaletteGUI(void);

        public:		// User declarations
                        __fastcall  TfrmMSX16Palette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::MSXPalette::TfrmMSX16Palette *frmMSX16Palette;
//---------------------------------------------------------------------------
#endif
