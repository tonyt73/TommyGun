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
#ifndef fZXScreenParserOptionsH
#define fZXScreenParserOptionsH
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
#include "ZXScreenParser.h"
#include "KRegistry.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace ScreenParser
    {
        //---------------------------------------------------------------------------
        class TfrmZXScreenParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panZXScreenParser;
            TScrollBox *scpZXImageParser;
            TPanel *panTitle;
            TLabel *lblZXImagesParser;
            TLabel *lblZXImageParserDescription;
    TPanel *Panel1;
    TGroupBox *grpZXScreenParserAddress;
    TRadioButton *radZXScreenParserOrgDefault;
    TRadioButton *radZXScreenParserOrgNone;
    TRadioButton *radZXScreenParserOrgUser;
    TEdit *edtZXScreenParserOrgValue;
    TGroupBox *grpZXScreensParserAttributes;
    TRadioButton *radZXScreenParserInclude;
    TRadioButton *radZXScreenParserExclude;
    void __fastcall radZXScreenParserOrgDefaultClick(TObject *Sender);
    void __fastcall edtZXScreenParserOrgValueKeyPress(TObject *Sender,
          char &Key);

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;

        public:		// User declarations
                        __fastcall  TfrmZXScreenParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ScreenParser::TfrmZXScreenParserOptions *frmZXScreenParserOptions;
//---------------------------------------------------------------------------
#endif
