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
#ifndef fZXImageParserOptionsH
#define fZXImageParserOptionsH
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
#include "ZXImageParser.h"
#include "KRegistry.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace ImageParser
    {
        //---------------------------------------------------------------------------
        class TfrmZXImageParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panZXImageParser;
            TScrollBox *scpZXImageParser;
            TPanel *panTitle;
            TLabel *lblZXImagesParser;
            TLabel *lblZXImageParserDescription;
    TPanel *panOptions;
    TGroupBox *grpZXImageParserPixelOrder;
    TRadioButton *radZXImageParserPixelsRowColumn;
    TRadioButton *radZXImageParserPixelCharacterBlock;
    TGroupBox *grpZXImageParserPixelRowOrder;
    TImage *imgZXImageParserClassic;
    TImage *imgZXImageParserZigZag;
    TRadioButton *radZXImageParserRowOrderClassic;
    TRadioButton *radZXImageParserRowOrderZigZag;
    TGroupBox *grpZXImageParserAttributeOrder;
    TRadioButton *radZXImageParserAttributesEnd;
    TRadioButton *radZXImageParserAttributesInterleaved;
    TCheckBox *chkUseAttributes;
    TGroupBox *grpZXImageParserMaskOrder;
    TRadioButton *radZXImageParserMaskBytePairs;
    TRadioButton *radZXImageParserAfterPixels;
    TPanel *panMaskOrder;
    TRadioButton *radZXImageParserMaskAfter;
    TRadioButton *radZXImageParserMaskBefore;
    TGroupBox *grpZXImageParserMaskType;
    TImage *imgZXImageParserMaskCovers;
    TImage *imgZXImageParserMaskOutlines;
    TRadioButton *radZXImageParserMaskCovers;
    TRadioButton *radZXImageParserMaskOutlines;
    TGroupBox *grpZXImageParserImageSize;
    TCheckBox *chkPlaceSize;
    TCheckBox *chkConvertX;
    TCheckBox *chkConvertY;
    TGroupBox *grpNumberBase;
    TRadioButton *radZXImageParserDecimal;
    TRadioButton *radZXImageParserHexidecimal;
    TRadioButton *radZXImageParserBinary;
    TRadioButton *radZXImageParserOctal;
    TGroupBox *GroupBox1;
    TImage *imgZXImageParserPreview;
    TRichEdit *rdtZXImageParserPreview;
            void __fastcall radZXImageParserPixelsRowColumnClick(TObject *Sender);

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;
                    int             m_iCharacters;

                void    __fastcall  Preview1(void);
                void    __fastcall  Preview2(void);
                void    __fastcall  Preview3(void);
                void    __fastcall  Preview4(void);
                void    __fastcall  AddText(String sText, TColor cColor, bool bBold, bool bItalic);
                void    __fastcall  SetAttr(int iStart, int iLen, TColor cColor);

        public:		// User declarations
                        __fastcall  TfrmZXImageParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageParser::TfrmZXImageParserOptions *frmZXImageParserOptions;
//---------------------------------------------------------------------------
#endif
