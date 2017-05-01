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
#ifndef fZXImageTableParserOptionsH
#define fZXImageTableParserOptionsH
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
#include "ZXImageTableParser.h"
#include "KRegistry.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace ImageTableParser
    {
        //---------------------------------------------------------------------------
        class TfrmZXImageTableParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panZXImageTableParser;
            TScrollBox *scpZXImageTableParser;
            TPanel *panTitle;
            TLabel *lblZXImagesParser;
            TLabel *lblZXImageTableParserDescription;
    TPanel *panOptions;
    TGroupBox *FlatGroupBox1;
    TLabel *Label1;
    TEdit *edtTableName;
    TGroupBox *grpZXImageTableParserPixelOrder;
    TCheckBox *chkTableAddNumber;
    TGroupBox *grpPreview;
    TRichEdit *rdtZXImageTableParserPreview;
    void __fastcall chkTableAddNumberClick(TObject *Sender);

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;
                    int             m_iCharacters;

                void    __fastcall  Preview(void);
                void    __fastcall  AddText(String sText, TColor cColor, bool bBold, bool bItalic);
                void    __fastcall  SetAttr(int iStart, int iLen, TColor cColor);

        public:		// User declarations
                        __fastcall  TfrmZXImageTableParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageTableParser::TfrmZXImageTableParserOptions *frmZXImageTableParserOptions;
//---------------------------------------------------------------------------
#endif
