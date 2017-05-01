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
#ifndef fEditorPropertiesH
#define fEditorPropertiesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include "KRegistry.h"
#include "KSpinEdit.h"
#include "KIconButton.h"
//---------------------------------------------------------------------------
class TfrmEditorProperties : public TForm
{
__published:	// IDE-managed Components
    TPanel *panButtons;
    TButton *cmdApply;
    TButton *cmdClose;
    TPanel *panProperties;
    TPageControl *pgcProperties;
    TTabSheet *tabGeneral;
    TTabSheet *tabDisplay;
    TTabSheet *tabColours;
    TGroupBox *grpColoursFontAttrs;
    TGroupBox *grpColourSettings;
    TCheckBox *chkColoursFontBold;
    TCheckBox *chkColoursFontItalic;
    TCheckBox *chkColoursFontUnderline;
    TComboBox *cmbColoursSpeedSettings;
    TLabel *lblColoursSpeedSettings;
    TLabel *lblColoursElement;
    TPanel *panColoursBlack;
    TPanel *panColoursMaroon;
    TPanel *panColoursGreen;
    TPanel *panColoursOlive;
    TPanel *panColoursNavy;
    TPanel *panColoursPurple;
    TPanel *panColoursTeal;
    TPanel *panColoursSilver;
    TPanel *panColoursGray;
    TPanel *panColoursRed;
    TPanel *panColoursLime;
    TPanel *panColoursYellow;
    TPanel *panColoursBlue;
    TPanel *panColoursFuchsia;
    TPanel *panColoursAqua;
    TPanel *panColoursWhite;
    TLabel *lblColoursColour;
    TGroupBox *grpGeneralEditorSettings;
    TLabel *lblGeneralTabWidth;
    TGroupBox *grpDisplayGutterMargin;
    TGroupBox *grpDisplayFontAttrs;
    TComboBox *cmbDisplayFonts;
    TLabel *lblDisplayFont;
    TLabel *lblDisplayFontSize;
    TLabel *lblDisplayFontSample;
    TPanel *panDisplayFontSample;
    TCheckBox *chkDisplayLineNumbers;
    TImage *imgDisplayGutter;
    TImage *imgDisplayFontAttr;
    TImage *imgGeneralSettings;
    TImage *imgColoursSettings;
    TImage *imgColoursSyntaxExample;
    TGroupBox *grpColoursSyntaxHighlighting;
    TImage *imgColoursFontAttrs;
    KSpinEdit *edtDisplayFontSize;
    KSpinEdit *edtGeneralTabWidth;
    TColorDialog *dlgColor;
    TCheckBox *chkDisplayFixedFontsOnly;
    KRegistry *regScorpio;
    TButton *cmdRestoreDefaults;
    TPanel *panColoursElements;
    TListBox *lstColoursElements;
    TPanel *Panel4;
    KIconButton *btnGeneral;
    KIconButton *btnDisplay;
    KIconButton *btnColours;
    TImageList *imgBigIcons;
    TCheckBox *chkGeneralTabsToSpaces;
    void __fastcall cmdApplyClick(TObject *Sender);
    void __fastcall cmbColoursSpeedSettingsChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall panDisplayGutterStartColourClick(TObject *Sender);
    void __fastcall cmbDisplayFontsChange(TObject *Sender);
    void __fastcall chkDisplayFixedFontsOnlyClick(TObject *Sender);
    void __fastcall lstColoursElementsClick(TObject *Sender);
    void __fastcall panColoursBlackMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall chkColoursFontBoldClick(TObject *Sender);
    void __fastcall cmdRestoreDefaultsClick(TObject *Sender);
    void __fastcall btnGeneralClick(TObject *Sender);
    void __fastcall pgcPropertiesChange(TObject *Sender);
private:	// User declarations
    ZXFileManager&      m_FileManager;
    TColor              m_ForeColor;
    TColor              m_BackColor;
    TPanel*             m_ForePanel;
    TPanel*             m_BackPanel;

    void __fastcall     ApplyGeneral(void);
    void __fastcall     ApplyDisplay(void);
    void __fastcall     ApplyKeyMappings(void);
    void __fastcall     ApplyColours(void);

    void __fastcall     ReadGeneral(void);
    void __fastcall     ReadDisplay(void);
    void __fastcall     ReadKeyMappings(void);
    void __fastcall     ReadColours(void);

    void __fastcall     Select(TComboBox* pComboBox, String sText);
    void __fastcall     GetFonts(void);
    void __fastcall     UpdateColors(TColor ForeColor, TColor BackColor);
    void __fastcall     UpdateFontStyles(const TColorSetting& ColorSetting);
    TPanel* __fastcall FindColor(TColor Color);

public:		// User declarations
    __fastcall TfrmEditorProperties(TComponent* Owner, ZXFileManager& FileManager);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEditorProperties *frmEditorProperties;
//---------------------------------------------------------------------------
#endif

