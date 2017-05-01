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
#ifndef fImageParserOptionsH
#define fImageParserOptionsH
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
//#include "..\CodePluginInterface.h"
#include "ImageParser.h"
#include "TComboBoxUnit.hpp"
#include "TEditUnit.hpp"
#include "TRadioButtonUnit.hpp"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace ImageParser
    {
        //---------------------------------------------------------------------------
        class TfrmImageParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panImageParser;
    TLabel *lblImagesParser;
    TLabel *lblImageParserDescription;
    TPageControl *pgcImageParserOptions;
    TTabSheet *tabImageParserDataFormat;
    TTabSheet *tabImageParserLanguage;
    TTabSheet *tabImageParserFileOutput;
    TRadioButton *radImageParserCurrentFile;
    TRadioButton *radImageParserExistingOrNewFile;
    TComboBox *cmbImageParserFile;
    TLabel *lblImageParserFile;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TComboBox *FlatComboBox1;
    TLabel *Label4;
    TBevel *Bevel1;
    TEdit *FlatEdit1;
    TLabel *Label5;
    TEdit *FlatEdit2;
            
        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;


        public:		// User declarations
                        __fastcall  TfrmImageParserOptions(TComponent* Owner);

            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);
            //HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageParser::TfrmImageParserOptions *frmImageParserOptions;
//---------------------------------------------------------------------------
#endif
