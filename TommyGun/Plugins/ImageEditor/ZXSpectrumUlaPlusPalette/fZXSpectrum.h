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
#ifndef fZXSpectrumH
#define fZXSpectrumH
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
#include "SpectrumUlaPlusPalette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace SpectrumPalette
    {
        //---------------------------------------------------------------------------
        class TfrmZXSpectrum : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panZXSpectrumPalette;
            TImage *imgLogo;
            TPanel *Panel1;
            TImage *imgPalette;
            TLabel *Label1;
            TLabel *Label2;
            TLabel *Label3;
            TTrackBar *tbRed;
            TLabel *lblRed;
            TLabel *lblGreen;
            TLabel *lblBlue;
            TTrackBar *tbGreen;
            TTrackBar *tbBlue;
            TSpeedButton *btnLoadPalette;
            TSpeedButton *btnSavePalette;
            TLabel *Label4;
            TPanel *Panel2;
    TImage *imgColourPicker;
            TComboBox *cmbPalettes;
            TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
            void __fastcall tbRedChange(TObject *Sender);
            void __fastcall tbGreenChange(TObject *Sender);
            void __fastcall tbBlueChange(TObject *Sender);
            void __fastcall Panel1Resize(TObject *Sender);
            void __fastcall FormShow(TObject *Sender);
            void __fastcall imgPaletteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall imgPaletteMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
            void __fastcall cmbPalettesChange(TObject *Sender);
    void __fastcall Panel2Resize(TObject *Sender);
    void __fastcall imgColourPickerMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgColourPickerMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
        private:	// User declarations
            ZXSpectrumUlaPlusPalette    m_Palette;
            ZXImageInterface            m_ImageEditor;
            TZX_HPLUGIN                 m_PluginHandle;
            bool                        m_SelectionIsInk;
            bool                        m_ChangingPalettes;

            void        __fastcall      OnUpdatePaletteGUI(void);
            void        __fastcall      UpdatePaletteImage();
            void        __fastcall      UpdateRGB();
            void        __fastcall      UpdatePalettes();

        public:		// User declarations
                        __fastcall      TfrmZXSpectrum(TComponent* Owner);

            HRESULT     __fastcall      Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall      Release(void);
            HRESULT     __fastcall      Palette(ZXPalette*& Palette);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::SpectrumPalette::TfrmZXSpectrum *frmZXSpectrum;
//---------------------------------------------------------------------------
#endif
