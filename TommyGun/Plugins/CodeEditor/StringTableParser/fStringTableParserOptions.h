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
#ifndef fStringTableParserOptionsH
#define fStringTableParserOptionsH
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
#include "StringTableParser.h"
#include "KRegistry.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace StringTableParser
    {
        //---------------------------------------------------------------------------
        class TfrmStringTableParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panStringTableParser;
            TPanel *panTitle;
            TLabel *lblStringTableParserDescription;
            TLabel *lblStringTableParser;

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;

        public:		// User declarations
                        __fastcall  TfrmStringTableParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::StringTableParser::TfrmStringTableParserOptions *frmStringTableParserOptions;
//---------------------------------------------------------------------------
#endif
