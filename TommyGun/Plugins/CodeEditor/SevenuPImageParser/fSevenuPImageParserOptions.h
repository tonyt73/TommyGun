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
#ifndef fSevenuPImageParserOptionsH
#define fSevenuPImageParserOptionsH
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
#include "SevenuPImageParser.h"
#include "SevenuPImageParserPlugin.h"
#include "KRegistry.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace ImageParser
    {
        //---------------------------------------------------------------------------
        class TfrmSevenuPImageParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panSevenuPImageParser;
            TScrollBox *scpSevenuPImageParser;
            TPanel *panTitle;
            TLabel *lblZXImagesParser;
            TLabel *lblSevenuPImageParserDescription;
    TPanel *panOptions;
    TGroupBox *grpSourceCode;
    TLabel *lblPrefix;
    TLabel *lblLabelPrefix;
    TLabel *lblLabelPostfix;
    TLabel *lblExample;
    TImage *imgZXImageParserZigZag;
    TRadioButton *radSourceCodeAsm;
    TRadioButton *radSourceCodeC;
    TCheckBox *chkSourceCodeUseLabel;
    TEdit *edtPrefix;
    TEdit *edtLabelPrefix;
    TEdit *edtLabelPostfix;
    TCheckBox *chkSourceCodeZ88DK;
    TCheckBox *chkMiscZigZag;
    TGroupBox *grpDataOutputted;
    TRadioButton *radDataGraphicsAttributes;
    TRadioButton *radDataAttributesGraphics;
    TRadioButton *radDataGraphics;
    TRadioButton *radDataAttributes;
    TGroupBox *grpMasking;
    TImage *imgSevenuPImageParserMaskOutlines;
    TImage *imgSevenuPImageParserMaskCovers;
    TRadioButton *radMaskingMaskCovers;
    TCheckBox *chkMaskingBeforeGraphics;
    TCheckBox *chkMaskingAttributeMask;
    TCheckBox *chkMaskingAttributeInk;
    TCheckBox *chkMaskingAttributePaper;
    TCheckBox *chkMaskingAttributeBright;
    TCheckBox *chkMaskingAttributeFlash;
    TRadioButton *radMaskingMaskOutlines;
    TGroupBox *grpInterleave;
    TRadioButton *radInterleaveLine;
    TRadioButton *radInterleaveCharacter;
    TRadioButton *radInterleaveColumn;
    TRadioButton *radInterleaveFrames;
    TRadioButton *radInterleaveSprite;
    TGroupBox *grpByteSortPriority;
    TListBox *lstByteSortPriority;
    TBitBtn *cmdSortListMoveUp;
    TBitBtn *cmdSortListMoveDown;
    TButton *cmdListDefault;
    TGroupBox *grpNumberBase;
    TLabel *lblNumberBasePrefix;
    TLabel *lblNumberBasePostfix;
    TLabel *lblExampleIs;
    TLabel *lblExampleValue;
    TRadioButton *radDecimal;
    TRadioButton *radBinary;
    TRadioButton *radOctal;
    TEdit *edtNumberBasePrefix;
    TEdit *edtNumberBasePostfix;
    TRadioButton *radHexidecimal;
            void __fastcall radSourceCodeAsmClick(TObject *Sender);
            void __fastcall chkMaskingAttributeMaskClick(TObject *Sender);
            void __fastcall edtNumberBasePrefixChange(TObject *Sender);
            void __fastcall edtNumberBasePostfixChange(TObject *Sender);
            void __fastcall radDecimalClick(TObject *Sender);
            void __fastcall radInterleaveLineClick(TObject *Sender);
            void __fastcall lstByteSortPriorityClick(TObject *Sender);
            void __fastcall cmdSortListMoveUpClick(TObject *Sender);
            void __fastcall cmdSortListMoveDownClick(TObject *Sender);
            void __fastcall cmdListDefaultClick(TObject *Sender);
            void __fastcall radAssemblerGenericClick(TObject *Sender);
            void __fastcall radDataGraphicsAttributesClick(TObject *Sender);
            void __fastcall chkMaskingAttributeInkClick(TObject *Sender);
            void __fastcall chkMaskingBeforeGraphicsClick(TObject *Sender);
            void __fastcall edtLabelPostfixChange(TObject *Sender);

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;
                    String          m_Prefixes[4];
                    String          m_Postfixes[4];
                    eDataOutputted  m_DataOutputted;
                    eCompiler       m_Compiler;
                    eNumberBase     m_NumberBase;
                    eInterleave     m_Interleave;
                    bool            m_MaskBefore;            
                    unsigned char   m_AttributeMask;

            void        __fastcall  UpdateExample(void);
            void        __fastcall  UpdateAttributeMask(void);


        public:		// User declarations
                        __fastcall  TfrmSevenuPImageParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);

            String      __fastcall  GetPrefix(int NumberBase);
            String      __fastcall  GetPostfix(int NumberBase);
            String      __fastcall  GetAsmPrefix();

            __property  eDataOutputted  DataOutputted   = { read = m_DataOutputted  };
            __property  eCompiler       Compiler        = { read = m_Compiler       };
            __property  eInterleave     Interleave      = { read = m_Interleave     };
            __property  eNumberBase     NumberBase      = { read = m_NumberBase     };
            __property  bool            MaskBefore      = { read = m_MaskBefore     };
            __property  unsigned char   AttributeMask   = { read = m_AttributeMask  };
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageParser::TfrmSevenuPImageParserOptions *frmSevenuPImageParserOptions;
//---------------------------------------------------------------------------
#endif
