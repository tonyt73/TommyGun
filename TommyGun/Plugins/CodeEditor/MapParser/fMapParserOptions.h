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
#ifndef fMapParserOptionsH
#define fMapParserOptionsH
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
#include "MapParser.h"
#include "KRegistry.h"
#include <Dialogs.hpp>
#include "KSpinEdit.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace MapParser
    {
        //---------------------------------------------------------------------------
        class TfrmMapParserOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panMapParser;
            TScrollBox *scpMapParser;
            TPanel *panTitle;
            TLabel *lblMapParserDescription;
            TLabel *lblMapParser;
            TOpenDialog *dlgBrowse;
            KRegistry *regScorpio;
    TPanel *panOptions;
    TGroupBox *grpScreenPrefix;
    TLabel *Label2;
    TEdit *edtPrefix;
    TGroupBox *grpMapOutputInformation;
    TLabel *lblTileWidth;
    TLabel *lblTileHeight;
    TLabel *lblDefaultTileIndex;
    TLabel *lblDefaultMessage;
    TLabel *lblIndexOnlyMessage;
    TLabel *lblCoordIndexMessage;
    TRadioButton *radUseCoordIndex;
    TRadioButton *radUseIndexOnly;
    KSpinEdit *edtTileWidth;
    KSpinEdit *edtTileHeight;
    TCheckBox *chkOverrideTileSize;
    KSpinEdit *edtDefaultTileIndex;
    TCheckBox *chkIndexUseDefw;
    TCheckBox *chkConvertX;
    TCheckBox *chkConvertY;
    TCheckBox *chkCoordUseDefw;
    TGroupBox *FlatGroupBox2;
    TLabel *lblApplication;
    TLabel *lblParameters;
    TLabel *lblConvertToSourceCode;
    TLabel *lblUseOutputBinary;
    TLabel *Label3;
    TEdit *edtApplication;
    TEdit *edtParameters;
    TRadioButton *radConvertToSourceCode;
    TRadioButton *radUseOutputBinary;
    TButton *cmdApplication;
    TCheckBox *chkUsePostProcessor;
    TGroupBox *grpMapName;
    TLabel *lblDefaultTableName;
    TLabel *lblMapSortOrder;
    TLabel *Label5;
    TEdit *edtTableName;
    TRadioButton *radMapColRow;
    TRadioButton *radMapRowCol;
    TGroupBox *grpTilesTable;
    TLabel *lblBuildTheTilesTable;
    TCheckBox *chkBuildTilesTable;
    TGroupBox *FlatGroupBox4;
    TLabel *Label1;
    TLabel *Label4;
    TRadioButton *FlatRadioButton1;
    TRadioButton *FlatRadioButton2;
    TGroupBox *grpTilesTableFormat;
    TBitBtn *cmdTilesTableFormatUp;
    TBitBtn *cmdTilesTableFormatDown;
    TBitBtn *cmdTilesTableFormatAdd;
    TBitBtn *cmdTilesTableFormatRemove;
    TPanel *panTilesTableFormat;
    TListView *lstTileTableFormat;
    TPanel *panItemsAvailable;
    TListView *lstItemsAvailable;
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
    TGroupBox *grpEndianess;
    TRadioButton *radLittleEndian;
    TRadioButton *radBigEndian;
            void __fastcall edtNumberBasePrefixChange(TObject *Sender);
            void __fastcall edtNumberBasePostfixChange(TObject *Sender);
            void __fastcall radDecimalClick(TObject *Sender);
            void __fastcall radUseCoordIndexClick(TObject *Sender);
            void __fastcall chkUsePostProcessorClick(TObject *Sender);
            void __fastcall cmdApplicationClick(TObject *Sender);
            void __fastcall edtApplicationChange(TObject *Sender);
            void __fastcall lstTileTableFormatChange(TObject *Sender, TListItem *Item, TItemChange Change);
            void __fastcall lstItemsAvailableChange(TObject *Sender, TListItem *Item, TItemChange Change);
            void __fastcall cmdTilesTableFormatAddClick(TObject *Sender);
            void __fastcall cmdTilesTableFormatRemoveClick(TObject *Sender);
            void __fastcall cmdTilesTableFormatUpClick(TObject *Sender);
            void __fastcall cmdTilesTableFormatDownClick(TObject *Sender);

        private:	// User declarations
                    //ZXCodeInterface    m_CodeEditor;
                    ZXPlugin*       m_pPlugin;
                    String          m_Prefixes[4];
                    String          m_Postfixes[4];
                    eNumberBase     m_NumberBase;
                    bool            m_Initialized;

            void        __fastcall  UpdateExample(void);

        public:		// User declarations
                        __fastcall  TfrmMapParserOptions(TComponent* Owner);

            String      __fastcall  GetPrefix(int NumberBase);
            String      __fastcall  GetPostfix(int NumberBase);
            
            HRESULT     __fastcall  Initialize(ZXPlugin* pPlugin);
            HRESULT     __fastcall  Release(void);

            __property  eNumberBase NumberBase  = { read = m_NumberBase };
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::MapParser::TfrmMapParserOptions *frmMapParserOptions;
//---------------------------------------------------------------------------
#endif
