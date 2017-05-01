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
#ifndef fTiledMapParserOptionsH
#define fTiledMapParserOptionsH
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
#include "TiledMapParser.h"
#include "KRegistry.h"
#include "TScrollBox.h"
#include "KShadePanel.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace TiledMapParser
    {
        //---------------------------------------------------------------------------
        class TfrmTiledMapParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panTiledMapParser;
            TScrollBox *scpTiledMapParser;
            KShadePanel *shpMapOptions;
            TGroupBox *FlatGroupBox1;
            TLabel *Label4;
            TCheckBox *chkBuildTilesTable;
            TGroupBox *grpCoordinates;
            TLabel *Label3;
            TCheckBox *chkUseDefw;
            TGroupBox *grpScreenPrefix;
            TLabel *Label2;
            TEdit *edtPrefix;
            TGroupBox *grpMapName;
            TLabel *Label1;
            TEdit *edtTableName;
            TPanel *panTitle;
            TLabel *lblTiledMapParserDescription;
            TLabel *lblTiledMapParser;
            TLabel *lblDefaultTileIndex;
            KSpinEdit *edtDefaultTileIndex;
            TLabel *lblDefaultMessage;

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;

        public:		// User declarations
                        __fastcall  TfrmTiledMapParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::TiledMapParser::TfrmTiledMapParserOptions *frmTiledMapParserOptions;
//---------------------------------------------------------------------------
#endif
