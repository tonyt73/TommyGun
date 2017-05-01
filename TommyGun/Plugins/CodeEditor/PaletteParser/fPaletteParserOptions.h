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
#ifndef fPaletteParserOptionsH
#define fPaletteParserOptionsH
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
    namespace PaletteParser
    {
        //---------------------------------------------------------------------------
        class TfrmPaletteParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panPaletteParser;
            TScrollBox *scpZXPaletteParser;
            TPanel *panTitle;
            TLabel *lblZXImagesParser;
            TLabel *lblZXPaletteParserDescription;
            KRegistry *regScorpio;
            TPanel *panOptions;
            TGroupBox *grpSourceCode;
            TLabel *lblPrefix;
            TLabel *lblLabelPrefix;
            TLabel *lblLabelPostfix;
            TLabel *lblExample;
            TRadioButton *radSourceCodeAsm;
            TRadioButton *radSourceCodeC;
            TCheckBox *chkSourceCodeUseLabel;
            TEdit *edtPrefix;
            TEdit *edtLabelPrefix;
            TEdit *edtLabelPostfix;
            TGroupBox *grpNumberBase;
            TLabel *lblNumerialPrefix;
            TRadioButton *radZXPaletteParserDecimal;
            TRadioButton *radZXPaletteParserHexidecimal;
            TRadioButton *radZXPaletteParserBinary;
            TEdit *edtNumericalPrefix;
            void __fastcall radZXPaletteParserDecimalClick(TObject *Sender);
            void __fastcall radZXPaletteParserHexidecimalClick(TObject *Sender);
            void __fastcall radZXPaletteParserBinaryClick(TObject *Sender);
            void __fastcall edtLabelPrefixChange(TObject *Sender);
            void __fastcall edtNumericalPrefixChange(TObject *Sender);
            void __fastcall radSourceCodeAsmClick(TObject *Sender);

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;

        public:		// User declarations
                        __fastcall  TfrmPaletteParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);

            String      __fastcall  NumToStr(unsigned char iNum);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::PaletteParser::TfrmPaletteParserOptions *frmPaletteParserOptions;
//---------------------------------------------------------------------------
#endif
