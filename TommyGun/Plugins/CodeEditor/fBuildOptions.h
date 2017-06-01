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
#ifndef fBuildOptionsH
#define fBuildOptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
//-- APP --------------------------------------------------------------------
#include "ZXToolDefinition.h"
#include <Dialogs.hpp>
#include "KIconButton.h"
#include "cspin.h"
#include "KSpinEdit.h"
#include "KRegistry.h"
#include "SciLanguageManager.hpp"
#include "SciScintilla.hpp"
#include "SciScintillaBase.hpp"
#include "SciScintillaMemo.hpp"
#include "SciFileExtensionsManager.hpp"
#include "SciDocTabCtrl.hpp"
#include <vector>
//---------------------------------------------------------------------------
class TfrmBuildOptions : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TButton *cmdClose;
	TPanel *Panel2;
	TPageControl *pgcProperties;
    TTabSheet *tabGeneral;
    TTabSheet *tabHelp;
    TOpenDialog *dlgFindApp;
    TTabSheet *tabTools;
    TPanel *Panel4;
    KIconButton *btnGeneral;
    TImageList *imgBigIcons;
    KIconButton *btnTools;
    KIconButton *btnBuild;
    KIconButton *btnEmulator;
    KIconButton *btnHelp;
    TTabSheet *tabBuilders;
    TTabSheet *tabEmulator;
    KIconButton *btnEditor;
	TTabSheet *tabEditor;
    KRegistry *regScorpio;
    TImage *Image2;
    TPanel *Panel3;
    TImage *Image5;
    TGroupBox *FlatGroupBox2;
    TLabel *Label28;
    TLabel *Label35;
    TLabel *Label56;
    TLabel *Label57;
    TLabel *Label2;
    TLabel *Label12;
    TLabel *Label15;
    TGroupBox *GroupBox3;
    TMemo *Memo1;
    TGroupBox *GroupBox8;
	TMemo *Memo2;
    TPanel *Panel5;
    TImage *Image3;
    TImage *Image8;
    TImage *Image4;
    TGroupBox *FlatGroupBox3;
    TLabel *Label58;
    TLabel *Label59;
    TCheckBox *chkUpdateParserTags;
    TCheckBox *chkJumpToError;
    TCheckBox *chkClearConsole;
    TGroupBox *FlatGroupBox8;
    TLabel *Label27;
    TRadioButton *chkOptionsCodeEditorResourceOverwrite;
    TRadioButton *chkOptionsCodeEditorResourceSkip;
	TRadioButton *chkOptionsCodeEditorResourceAsk;
    TGroupBox *GroupBox7;
    TLabel *Label7;
    TComboBox *cmbTargetFile;
    TPanel *Panel6;
    TImage *Image11;
    TGroupBox *GroupBox2;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *lblMissingTool1;
    TSpeedButton *btnUpdateTool1;
    TLabel *lblTool1Defaults;
    TEdit *edtParameters1;
    TComboBox *cmbTool1;
    TGroupBox *grpTool2;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *lblMissingTool2;
    TSpeedButton *btnUpdateTool2;
    TLabel *lblTool2Defaults;
    TEdit *edtParameters2;
    TComboBox *cmbTool2;
    TCheckBox *chkTool2;
    TGroupBox *grpTool3;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *lblMissingTool3;
    TSpeedButton *btnUpdateTool3;
    TLabel *lblTool3Defaults;
    TEdit *edtParameters3;
    TComboBox *cmbTool3;
	TCheckBox *chkTool3;
    TPanel *Panel7;
    TImage *Image10;
    TGroupBox *GroupBox1;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *lblEmulatorNotFound;
    TSpeedButton *btnUpdateTool;
    TLabel *lblEmulatorDefaults;
    TEdit *edtEmulatorParameters;
    TComboBox *cmbEmulator;
    TPanel *Panel8;
    TImage *Image1;
    TImage *imgDisplayFontAttr;
    TGroupBox *GroupBox4;
	TLabel *Label4;
    TRadioButton *radTabsUse;
    TRadioButton *radTabUseSpaces;
    TCSpinEdit *edtTabWidth;
    TGroupBox *GroupBox6;
    TLabel *Label6;
    TCSpinEdit *edtGuideWidth;
    TCheckBox *chkAlignmentShow;
    TGroupBox *GroupBox5;
    TLabel *Label5;
    TCheckBox *chkAutoCloseBraces;
    TCheckBox *chkAutoCloseQuotes;
    TCheckBox *chkShowLineNumbers;
    TRadioButton *radWhitespaceNever;
    TRadioButton *radWhitespaceAlways;
    TRadioButton *radWhitespaceAfterIndent;
    TGroupBox *grpDisplayFontAttrs;
    TLabel *lblDisplayFontSample;
    TComboBox *cmbDisplayFonts;
    TPanel *panDisplayFontSample;
    KSpinEdit *edtDisplayFontSize;
    TCheckBox *chkDisplayFixedFontsOnly;
    TPanel *Panel9;
    TImage *Image9;
    TGroupBox *grpToolDefinition;
    TLabel *lblName;
    TLabel *lblExecutable;
    TLabel *lblType;
    TSpeedButton *btnToolAdd;
    TSpeedButton *btnToolUpdate;
    TSpeedButton *btnToolRemove;
	TSpeedButton *btnClear;
    TSpeedButton *btnFindExecutable;
    TLabel *Label1;
    TLabel *Label3;
    TEdit *edtName;
    TEdit *edtExecutable;
    TComboBox *cmbType;
    TGroupBox *grpPrefixes;
    TLabel *lblError;
    TLabel *lblFile;
    TLabel *lblLine;
    TEdit *edtPrefixError;
    TEdit *edtPrefixFile;
    TEdit *edtPrefixLineNo;
    TEdit *edtExtensions;
	TEdit *edtDefaultParameters;
	TCheckBox *chkAcceptsMultipleFiles;
	TGroupBox *grpTools;
	TListView *lstTools;
	KIconButton *KIconButton1;
	TTabSheet *tabColour;
	TImage *Image6;
	TGroupBox *GroupBox9;
	TComboBox *cmbLanguage;
	TLabel *Label18;
	TListBox *lstAttributes;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *lblBack;
	TSciLanguageManager *sciLangManager;
	TColorBox *clrBackGlobal;
	TColorBox *clrBack;
	TColorBox *clrFore;
	TSciDocumentTabControl *sciTabControl;
	TScintilla *sciEditor;
	TMemo *txtZ80;
	TMemo *txtText;
	TMemo *txtZXBasic;
	TMemo *txtCpp;
	TButton *btnReset;
	TButton *btnApply;
	TLabel *Label21;
	void __fastcall btnGeneralClick(TObject *Sender);
	void __fastcall cmbTypeChange(TObject *Sender);
	void __fastcall frmBuildChange(TObject *Sender);
	void __fastcall frmBuildEnter(TObject *Sender);
	void __fastcall frmBuildExit(TObject *Sender);
	void __fastcall btnToolAddClick(TObject *Sender);
	void __fastcall lstToolsSelectItem(TObject *Sender, TListItem *Item, bool Selected);
    void __fastcall btnToolUpdateClick(TObject *Sender);
    void __fastcall btnToolRemoveClick(TObject *Sender);
    void __fastcall btnClearClick(TObject *Sender);
    void __fastcall cmbEmulatorSelect(TObject *Sender);
    void __fastcall btnUpdateToolClick(TObject *Sender);
    void __fastcall btnUpdateTool1Click(TObject *Sender);
    void __fastcall btnUpdateTool2Click(TObject *Sender);
    void __fastcall btnUpdateTool3Click(TObject *Sender);
    void __fastcall cmbTool1Select(TObject *Sender);
    void __fastcall cmbTool2Select(TObject *Sender);
    void __fastcall cmbTool3Select(TObject *Sender);
    void __fastcall cmbTool1Change(TObject *Sender);
    void __fastcall chkTool2Click(TObject *Sender);
    void __fastcall btnFindExecutableClick(TObject *Sender);
    void __fastcall btnEmulatorDefaultsClick(TObject *Sender);
    void __fastcall lblTool1DefaultsClick(TObject *Sender);
    void __fastcall lblTool2DefaultsClick(TObject *Sender);
    void __fastcall lblTool3DefaultsClick(TObject *Sender);
	void __fastcall chkTool3Click(TObject *Sender);
    void __fastcall cmbTool2Change(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall tabBuildersEnter(TObject *Sender);
    void __fastcall btnToolsClick(TObject *Sender);
    void __fastcall cmbDisplayFontsChange(TObject *Sender);
    void __fastcall chkDisplayFixedFontsOnlyClick(TObject *Sender);
    void __fastcall cmdCloseClick(TObject *Sender);
	void __fastcall cmbLanguageChange(TObject *Sender);
	void __fastcall lstAttributesClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall clrForeChange(TObject *Sender);
	void __fastcall clrBackChange(TObject *Sender);
	void __fastcall clrBackGlobalChange(TObject *Sender);
	void __fastcall btnApplyClick(TObject *Sender);
	void __fastcall btnResetClick(TObject *Sender);
private:	// User declarations

	TCustomEdit*        m_Edit;
	bool                m_bDirty;
	int                 m_currentToolDefinition;
	ZXToolDefinitions   m_ToolDefinitions;
	bool				m_bChanging;

	int					m_LanguageIndex;
	String				m_Language;
	TExtensionMapper*   m_ExtMapper;
	TSciLangItem*		m_sciLang;
	std::vector<int>	m_AttributeMap;

    void    __fastcall  RefreshToolDefinitions();
    String  __fastcall  GUID();
    void    __fastcall  SaveIfDirty();
    void    __fastcall  GetFonts();
    void    __fastcall  Select(TComboBox* pComboBox, String sText);
	void    __fastcall  SetEditorOptions();
	void	__fastcall	FillStyles();
	int 	__fastcall 	GetLanguageIndex();

public:		// User declarations
            __fastcall  TfrmBuildOptions(TComponent* Owner);
            __fastcall ~TfrmBuildOptions();

    void    __fastcall  Load(void);
    void    __fastcall  EditCopy(void);
    void    __fastcall  EditCut(void);
    void    __fastcall  EditPaste(void);
    void    __fastcall  SetBuildTool(int tool, String name);
    void    __fastcall  SetBuildParameters(int tool, String parameters);
    void    __fastcall  SetEmulatorTool(String name);
    void    __fastcall  SetEmulatorParameters(String parameters);
    void    __fastcall  SetTargetFile(String file);
    String  __fastcall  GetEmulator();
    String  __fastcall  GetEmulatorParameters();
    bool    __fastcall  GetBuilder(int tool, ZXToolDefinition& builder);
    String  __fastcall  GetBuilderParameters(int tool);
    String  __fastcall  GetTargetFile();
    bool    __fastcall  DoesToolSupportExtension(int tool, String ext);
	bool    __fastcall  HasEmulator(void)   {   return GetEmulator().Trim() != ""; }
	void    __fastcall  GetPrefixes(int tool, String& error, String& file, String& lineNo);

	__property String Language = { read = m_Language, write = m_Language };
 };
//---------------------------------------------------------------------------
extern PACKAGE TfrmBuildOptions *frmBuildOptions;
//---------------------------------------------------------------------------
#endif

