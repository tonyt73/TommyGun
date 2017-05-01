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
#ifndef fAGDParserOptionsH
#define fAGDParserOptionsH
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
#include "AGDParser.h"
#include "KRegistry.h"
#include "KShadePanel.h"
#include "DirDialog.hpp"
#include <Dialogs.hpp>
#include "KSpinEdit.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace AGDParser
    {
        //---------------------------------------------------------------------------
        class TfrmAGDParserOptions : public TForm
        {
        __published:	// IDE-managed Components
    TPanel *panAGDParser;
    TPanel *panTitle;
    TLabel *lblAGDParser;
    TPanel *Panel1;
    TLabel *lblAGDParserDescription;
    TLabel *Label1;

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;
                    bool            m_Initialized;

        public:		// User declarations
                        __fastcall  TfrmAGDParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::AGDParser::TfrmAGDParserOptions *frmAGDParserOptions;
//---------------------------------------------------------------------------
#endif
