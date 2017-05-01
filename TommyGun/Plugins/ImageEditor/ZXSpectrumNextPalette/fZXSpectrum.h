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
#include "SpectrumNextPalette.h"
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
            TSpeedButton *btnLoadPalette;
            TSpeedButton *btnSavePalette;
            TPanel *Panel2;
    TImage *imgColourPicker;
            TComboBox *cmbPalettes;
    TLabel *Label6;
	TPanel *panPen;
	TPanel *panBrush;
            void __fastcall Panel1Resize(TObject *Sender);
            void __fastcall FormShow(TObject *Sender);
            void __fastcall cmbPalettesChange(TObject *Sender);
    void __fastcall Panel2Resize(TObject *Sender);
    void __fastcall imgColourPickerMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgColourPickerMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
        private:	// User declarations
            ZXSpectrumNextPalette    m_Palette;
            ZXImageInterface            m_ImageEditor;
            TZX_HPLUGIN                 m_PluginHandle;
            bool                        m_SelectionIsInk;
            bool                        m_ChangingPalettes;

            void        __fastcall      OnUpdatePaletteGUI(void);
            void        __fastcall      UpdatePaletteImage();
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
