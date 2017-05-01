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
#ifndef fPaletteImageParserOptionsH
#define fPaletteImageParserOptionsH
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
#include "KRegistry.h"
#include "KSpinEdit.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace ImageParser
    {
        //---------------------------------------------------------------------------
        class TfrmPaletteImageParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panPaletteImageParser;
            TScrollBox *scpZXImageParser;
            TPanel *panTitle;
            TLabel *lblZXImagesParser;
            TLabel *lblZXImageParserDescription;
            KRegistry *regScorpio;
    TPanel *panOptions;
    TGroupBox *grpSourceCode;
    TLabel *lblPrefix;
    TLabel *lblLabelPrefix;
    TLabel *lblLabelPostfix;
    TLabel *lblExample;
    TImage *imgZXImageParserZigZag;
    TImage *imgZXImageParserClassic;
    TRadioButton *radSourceCodeAsm;
    TRadioButton *radSourceCodeC;
    TCheckBox *chkSourceCodeUseLabel;
    TEdit *edtPrefix;
    TEdit *edtLabelPrefix;
    TEdit *edtLabelPostfix;
    TRadioButton *radZXImageParserRowOrderClassic;
    TRadioButton *radZXImageParserRowOrderZigZag;
    TGroupBox *grpZXImageParserMaskOrder;
    TRadioButton *radZXImageParserPixelMaskBytePairs;
    TRadioButton *radZXImageParserAfterPixels;
    TRadioButton *radZXImageParserMaskPixelBytePairs;
    TRadioButton *radZXImageParserBeforePixels;
    TGroupBox *grpZXImageParserMaskType;
    TImage *imgZXImageParserMaskCovers;
    TImage *imgZXImageParserMaskOutlines;
    TRadioButton *radZXImageParserMaskCovers;
    TRadioButton *radZXImageParserMaskOutlines;
    TGroupBox *grpImageSize;
    TLabel *lblSizeOrder;
    TCheckBox *chkPlaceSize;
    TCheckBox *chkConvertX;
    TCheckBox *chkConvertY;
    TRadioButton *radSizeWidthHeight;
    TRadioButton *radSizeHeightWidth;
    TGroupBox *grpNumberBase;
    TLabel *lblNumerialPrefix;
    TRadioButton *radZXImageParserDecimal;
    TRadioButton *radZXImageParserHexidecimal;
    TRadioButton *radZXImageParserBinary;
    TEdit *edtNumericalPrefix;
    TGroupBox *grpPixelBitRemapping;
    TLabel *lblBit7;
    TLabel *lblBit6;
    TLabel *lblBit5;
    TLabel *lblBit4;
    TLabel *lblBit3;
    TLabel *lblBit2;
    TLabel *lblBit1;
    TLabel *lblBit0;
    TLabel *lblTestValue;
    TLabel *lblResult;
    TLabel *lblRemapResult;
    TSpeedButton *spdRemapPresetSave;
    TSpeedButton *spdRemapPresetDelete;
    TLabel *lblRemappingPresets;
    TLabel *lblValue;
    TLabel *lblRemapValue;
    TCheckBox *chkEnabledRemap;
    KSpinEdit *edtBit7;
    KSpinEdit *edtBit6;
    KSpinEdit *edtBit5;
    KSpinEdit *edtBit4;
    KSpinEdit *edtBit3;
    KSpinEdit *edtBit2;
    KSpinEdit *edtBit1;
    KSpinEdit *edtBit0;
    KSpinEdit *edtTestValue;
    TComboBox *cmbRemapPreset;
    TRadioButton *radZXImageParserPixelMaskNone;
            void __fastcall radZXImageParserDecimalClick(TObject *Sender);
            void __fastcall radZXImageParserHexidecimalClick(TObject *Sender);
            void __fastcall radZXImageParserBinaryClick(TObject *Sender);
            void __fastcall edtBit7Change(TObject *Sender);
            void __fastcall chkEnabledRemapClick(TObject *Sender);
            void __fastcall edtLabelPrefixChange(TObject *Sender);
            void __fastcall edtNumericalPrefixChange(TObject *Sender);
            void __fastcall radSourceCodeAsmClick(TObject *Sender);
			void __fastcall chkPlaceSizeClick(TObject *Sender);

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;

        unsigned char   __fastcall  RemapValue(unsigned char iNum);

        public:		// User declarations
                        __fastcall  TfrmPaletteImageParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);

            String      __fastcall  NumToStr(unsigned char iNum);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageParser::TfrmPaletteImageParserOptions *frmPaletteImageParserOptions;
//---------------------------------------------------------------------------
#endif
