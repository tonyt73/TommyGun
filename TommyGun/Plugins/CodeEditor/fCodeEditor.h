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
#ifndef fCodeEditorH
#define fCodeEditorH
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
#include <ActnList.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <StdActns.hpp>
#include <AppEvnts.hpp>
//-- SCINTILLA --------------------------------------------------------------
#include "SciDocTabCtrl.hpp"
#include "SciLanguageManager.hpp"
#include "SciScintilla.hpp"
#include "SciScintillaBase.hpp"
#include "SciScintillaMemo.hpp"
#include "SciStreamDefault.hpp"
#include "SciSearchReplace.hpp"
#include "SciSearchReplaceBase.hpp"
#include "SciFileExtensionsManager.hpp"
//-- SCORPIO ----------------------------------------------------------------
#include "KSlider.h"
#include "KRegistry.h"
#include "DosCommand.hpp"
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
#include "ZXFileManager.h"
#include "ZXBreakpointManager.h"
#include "ZXSymbolsManager.h"
#include "ZXDebugFileManager.h"
#include "ZXParserManager.h"
#include "ZXToolDefinition.h"
#include "ZXDebugger.h"
#include "fDebuggerStateView.h"
#include "fDisplayView.h"
#include "fOSBView.h"
#include "fBreakpointProperties.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
//---------------------------------------------------------------------------
class TfrmCodeEditor : public TForm
{
__published:	// IDE-managed Components
    TImageList *imgIcons;
    TImageList *imgTabImages;
    TControlBar *cbrCodeEditor;
    TToolBar *tbrCodeTools;
    TToolButton *tbnCodeEditorSearch;
    TToolButton *tbnCodeEditorReplace;
    TPanel *panEditorContainer;
    TSplitter *splEditor;
    TPanel *panEditorHeader;
    TPanel *panEditorButtons;
    TBitBtn *cmdTextMinimize;
    TBitBtn *cmdTextRestore;
    TBitBtn *cmdTextMaximize;
    TPopupMenu *popCodeEditor;
    TMenuItem *popCut;
    TMenuItem *popCopy;
    TMenuItem *popPaste;
    TMenuItem *mnuLine02;
    TMenuItem *popUndo;
    TMenuItem *popRedo;
    TMenuItem *mnuLine03;
    TMenuItem *popFind;
    TMenuItem *popReplace;
    TSaveDialog *dlgSaveCode;
    TOpenDialog *dlgLoadCode;
    TActionList *actCodeEditor;
    TAction *actFind;
    TAction *actReplace;
    TToolButton *tbnCodeEditorFindBackward;
    TToolButton *tbnCodeEditorFindForward;
    TAction *actFindForward;
    TAction *actFindBackward;
    TMenuItem *popInsertItem;
    TMenuItem *mnuLine01;
    TAction *actInsertItem;
    TToolButton *tbnInsertItem;
    TToolButton *tbnSeparator04;
    TToolBar *tbrBuildTools;
    TToolButton *tbnDebugRun;
    TToolButton *tbnSeparator02;
    TAction *actToggleSpecial;
    TToolButton *tbnCodeEditorToggleSpecial;
    TDosCommand *dosCommand;
    TPopupMenu *popConsole;
    TMenuItem *mnuConsoleGotoErrorinSource;
    TMenuItem *mnuConsoleLine01;
    TMenuItem *mnuConsoleSaveToFile;
    TAction *actGotoLine;
    TToolButton *tbnCodeEditorGotoLine;
    TPopupMenu *popMenus;
    TMenuItem *mnuGotoLine;
    TMenuItem *mnuToggleSpecial;
    TPanel *panShowHide;
    TSpeedButton *spdShowHide;
    TPanel *panTabsContainer;
    TPanel *panMainContainer;
    TPanel *panEditContainer;
    TPopupMenu *popBuild;
    TMenuItem *mnuRun;
    TImage *imgBlankSna;
    TPanel *panEditorMain;
    TToolButton *tbnUpdateResources;
    TAction *actUpdateAllResources;
    TMenuItem *mnuUpdateAllResources;
    KRegistry *regScorpio;
    TImageList *imgProjectIcons;
    TPopupMenu *popGroup;
    TMenuItem *popAdd;
    TMenuItem *popNew;
    TMenuItem *popRemoveFile;
    TMenuItem *popOptions;
    TMenuItem *popLine01;
    TMenuItem *popActivate;
    TMenuItem *popLine02;
    TMenuItem *popSave;
    TPopupMenu *popFile;
    TMenuItem *popOpen;
    TMenuItem *popRemoveFromProject;
    TMenuItem *popSaveProject;
    TMenuItem *popSaveAsProject;
    TMenuItem *popCompile;
    TMenuItem *popBuildRules;
    TAction *actFileNext;
    TAction *actFilePrevious;
    TMenuItem *popClosePage;
    TAction *actClosePage;
    TImageList *imgOldIcons;
    TMenuItem *popConsoleClear;
    TMenuItem *mnuOptions;
    TAction *actOptions;
    TMenuItem *mnuBuildSettings;
    TAction *actBuildSettings;
    TAction *actBuildRun;
    TMenuItem *popConsoleCopy;
    TBitBtn *cmdTextClose;
    TPopupMenu *popTabs;
    TMenuItem *popTabsClosePage;
    TPanel *panConsoleContainer;
    TPageControl *pgcTabs;
    TTabSheet *tabConsole;
    TTabSheet *tabSearchResults;
    TPanel *panConsoleAligner;
    TMemo *memoConsole;
    TPanel *panConsoleMargin;
    TListBox *lstSearchResults;
    TPanel *panCodeKeysPanel;
    TLabel *lblKeysImage;
    TImage *Image1;
    TLabel *Label36;
    TLabel *Label37;
    TImage *Image2;
    TLabel *Label38;
    TLabel *Label39;
    TLabel *Label40;
    TLabel *Label41;
    TLabel *Label42;
    TLabel *Label43;
    TImage *Image3;
    TImage *Image4;
    TImage *Image5;
    TLabel *Label44;
    TLabel *Label45;
    TLabel *Label46;
    TLabel *Label47;
    TImage *Image7;
    TLabel *Label54;
    TLabel *Label55;
    TPanel *panImageKeysBar;
    TSciDocumentTabControl *sciTabControl;
    TScintilla *sciEditor;
    TSciLanguageManager *sciLangManager;
    TSciSearchReplace *sciSearchReplace;
    TToolButton *tbnBuildRun;
    TToolButton *tbnProjectOptions;
    TToolButton *ToolButton3;
    TAction *actHardReset;
    TAction *actDebugStop;
    TAction *actDebugPause;
    TAction *actDebugStepOver;
    TAction *actDebugStepInto;
    TAction *actDebugStepOut;
    TToolButton *tbnDebugStepOver;
    TToolButton *tbnDebugStepInto;
    TToolButton *tbnDebugStepOut;
    TToolButton *tbnDebugRunToCursor;
    TAction *actDebugRunToCursor;
    TAction *actDebugToggleBreakpoint;
    TToolButton *ToolButton9;
    TToolButton *tbnDebugToggleBreakpoint;
    TAction *actDebugRewind;
    TAction *actDebugStepBack;
    TToolButton *ToolButton12;
    TMenuItem *N1;
    TAction *actToggleDisplay;
    TAction *actToggleOSB;
    TMenuItem *mnuToggleDisplay;
    TMenuItem *mnuToggleOSB;
    TTimer *tmrDebugger;
    TToolButton *ToolButton2;
    TToolButton *tbnToggleDisplay;
    TToolButton *tbnToggleOSB;
    TAction *actDebugRun;
    TMenuItem *N2;
    TMenuItem *mnuDebugRun;
    TMenuItem *mnuDebugStop;
    TMenuItem *mnuDebugStepOver;
    TMenuItem *mnuDebugStepInto;
    TMenuItem *mnuDebugStepOut;
    TMenuItem *mnuDebugRunToCursor;
    TMenuItem *mnuToggleBreakpoint;
    TToolButton *tbnDebugPause;
    TToolButton *tbnDebugStop;
    TToolButton *tbnDebugTrace;
    TAction *actDebugTrace;
    TTabSheet *tabBreakpoints;
    TListView *lstBreakpoints;
    TToolBar *tbrBreakpoints;
    TToolButton *ToolButton1;
    TToolButton *ToolButton4;
    TToolButton *ToolButton5;
    TToolButton *ToolButton6;
    TToolButton *ToolButton7;
    TAction *actDebugAddBreakpoint;
    TAction *actDebugDeleteBreakpoint;
    TAction *actDebugDeleteAllBreakpoints;
    TAction *actDebugEnableAllBreakpoints;
    TAction *actDebugDisableAllBreakpoints;
    TAction *actDebugBreakpointProperties;
    TToolButton *ToolButton8;
    TAction *actBookmarkToggle;
    TAction *actBookmarkNext;
    TAction *actBookmarkPrevious;
    TAction *actBookmarkClear;
    TMenuItem *mnuBookmarkToggle;
    TMenuItem *mnuBookmarkNext;
    TMenuItem *mnuBookmarkPrevious;
    TMenuItem *mnuBookmarkClear;
    TToolButton *ToolButton10;
    TAction *actRewind;
    TAction *actForward;
    TTimer *tmrRewind;
    TToolButton *ToolButton11;
    TToolButton *tbnRewinder;
    TToolButton *tbnForwarder;
    TAction *actRewinder;
    TAction *actForwarder;
    TToolButton *tbnRewindStop;
    TAction *actRewindStop;
	TMenuItem *N3;
	TAction *actCloneView;
	TAction *actMoveView;
	TMenuItem *Clonetootherview1;
	TMenuItem *Clonetootherview2;
	TPanel *panSciEditors;
	TSplitter *splOtherView;
	TSciDocumentTabControl *sciTabControlOther;
	TScintilla *sciEditorOther;
	TPageControl *pgcCodeEditor;
	TTabSheet *tabFiles;
	TScrollBox *scpSourceFiles;
	TPanel *panProjectFiles;
	TLabel *Label1;
	TImage *imgSmallIcon;
	TImage *imgLargeIcon;
	TLabel *Label5;
	TBitBtn *cmdFileRemove;
	TBitBtn *cmdFileMoveDown;
	TBitBtn *cmdFileMoveUp;
	TBitBtn *cmdFileLoad;
	TPanel *panFileList;
	TListBox *lstFiles;
	TBitBtn *cmdFileRename;
	TBitBtn *cmdFileAdd;
	TEdit *edtFilename;
	TGroupBox *grpFileStats;
	TLabel *lblLines;
	TLabel *lblCharacters;
	TLabel *lblFileIsModified;
	TLabel *lblFileLines;
	TLabel *lblFileCharacters;
	TLabel *lblFileDirty;
	TTabSheet *tabStateView;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall cmdFileLoadClick(TObject *Sender);
    void __fastcall lstFilesDblClick(TObject *Sender);
    void __fastcall lstFilesClick(TObject *Sender);
    void __fastcall edtFilenameChange(TObject *Sender);
    void __fastcall cmdFileAddClick(TObject *Sender);
    void __fastcall cmdFileRemoveClick(TObject *Sender);
    void __fastcall cmdFileRenameClick(TObject *Sender);
    void __fastcall popCutClick(TObject *Sender);
    void __fastcall popCopyClick(TObject *Sender);
    void __fastcall popPasteClick(TObject *Sender);
    void __fastcall popUndoClick(TObject *Sender);
    void __fastcall popRedoClick(TObject *Sender);
    void __fastcall actFindExecute(TObject *Sender);
    void __fastcall cbrCodeEditorDblClick(TObject *Sender);
    void __fastcall actFindForwardExecute(TObject *Sender);
    void __fastcall actFindBackwardExecute(TObject *Sender);
    void __fastcall actReplaceExecute(TObject *Sender);
    void __fastcall actInsertItemExecute(TObject *Sender);
    void __fastcall actToggleSpecialExecute(TObject *Sender);
    void __fastcall cmdTextMaximizeClick(TObject *Sender);
    void __fastcall cmdTextRestoreClick(TObject *Sender);
    void __fastcall cmdTextMinimizeClick(TObject *Sender);
    void __fastcall splEditorMoved(TObject *Sender);
    void __fastcall spnOptionsCodeEditorTabWidthChange(TObject *Sender);
    void __fastcall actGotoLineExecute(TObject *Sender);
    void __fastcall cmdFileMoveUpClick(TObject *Sender);
    void __fastcall cmdFileMoveDownClick(TObject *Sender);
    void __fastcall actUpdateAllResourcesExecute(TObject *Sender);
    void __fastcall actFileNextExecute(TObject *Sender);
    void __fastcall actFilePreviousExecute(TObject *Sender);
    void __fastcall pgcEditorChange(TObject *Sender);
    void __fastcall mnuConsoleGotoErrorinSourceClick(TObject *Sender);
    void __fastcall mnuConsoleSaveToFileClick(TObject *Sender);
    void __fastcall memoConsoleDblClick(TObject *Sender);
    void __fastcall actClosePageExecute(TObject *Sender);
    void __fastcall popConsoleClearClick(TObject *Sender);
    void __fastcall actBuildSettingsExecute(TObject *Sender);
    void __fastcall lstFilesEnter(TObject *Sender);
    void __fastcall lstFilesExit(TObject *Sender);
    void __fastcall actBuildRunExecute(TObject *Sender);
    void __fastcall popConsoleCopyClick(TObject *Sender);
    void __fastcall dosCommandTerminated(TObject *Sender, int ExitCode);
    void __fastcall cmdTextCloseClick(TObject *Sender);
    void __fastcall lstSearchResultsDblClick(TObject *Sender);
    void __fastcall sciTabControlDetectHighlighter(TObject *Sender, const AnsiString Extension, AnsiString &Language);
    void __fastcall sciTabControlMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall sciEditorEnter(TObject *Sender);
    void __fastcall sciEditorExit(TObject *Sender);
    void __fastcall sciEditorModified(TObject *Sender, const int position, const int modificationType, PChar text, const int len,const int linesAdded, const int line, const int foldLevelNow, const int foldLevelPrev);
    void __fastcall sciTabControlClosing(TObject *Sender, const int TabIndex, bool &AllowClose);
    void __fastcall sciEditorKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall sciTabControlChange(TObject *Sender);
    void __fastcall sciSearchReplaceTextNotFound(TObject *Sender);
    void __fastcall sciEditorUpdateUI(TObject *Sender);
    void __fastcall actToggleDisplayExecute(TObject *Sender);
    void __fastcall actToggleOSBExecute(TObject *Sender);
    void __fastcall tmrDebuggerTimer(TObject *Sender);
    void __fastcall actHardResetExecute(TObject *Sender);
    void __fastcall actDebugPauseExecute(TObject *Sender);
    void __fastcall actDebugStepOutExecute(TObject *Sender);
    void __fastcall actDebugStepIntoExecute(TObject *Sender);
    void __fastcall actDebugStepOverExecute(TObject *Sender);
    void __fastcall actDebugRunToCursorExecute(TObject *Sender);
    void __fastcall actDebugToggleBreakpointExecute(TObject *Sender);
    void __fastcall actDebugRewindExecute(TObject *Sender);
    void __fastcall actDebugStopExecute(TObject *Sender);
    void __fastcall pgcCodeEditorDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active);
    void __fastcall actDebugRunExecute(TObject *Sender);
    void __fastcall actDebugTraceExecute(TObject *Sender);
    void __fastcall sciEditorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall actDebugStepBackExecute(TObject *Sender);
    void __fastcall pgcTabsDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active);
    void __fastcall actDebugAddBreakpointExecute(TObject *Sender);
    void __fastcall actDebugDeleteBreakpointExecute(TObject *Sender);
    void __fastcall actDebugDeleteAllBreakpointsExecute(TObject *Sender);
    void __fastcall actDebugEnableAllBreakpointsExecute(TObject *Sender);
    void __fastcall actDebugDisableAllBreakpointsExecute(TObject *Sender);
    void __fastcall actDebugBreakpointPropertiesExecute(TObject *Sender);
    void __fastcall tabBreakpointsShow(TObject *Sender);
    void __fastcall lstBreakpointsChanging(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange);
    void __fastcall lstBreakpointsChange(TObject *Sender, TListItem *Item, TItemChange Change);
    void __fastcall lstBreakpointsSelectItem(TObject *Sender, TListItem *Item, bool Selected);
    void __fastcall lstBreakpointsDblClick(TObject *Sender);
    void __fastcall actBookmarkToggleExecute(TObject *Sender);
    void __fastcall actBookmarkNextExecute(TObject *Sender);
    void __fastcall actBookmarkPreviousExecute(TObject *Sender);
    void __fastcall actBookmarkClearExecute(TObject *Sender);
    void __fastcall sciEditorMarginClick(TObject *Sender, const int modifiers, const int position, const int margin);
    void __fastcall sciEditorKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall actRewindExecute(TObject *Sender);
    void __fastcall actForwardExecute(TObject *Sender);
    void __fastcall tmrRewindTimer(TObject *Sender);
    void __fastcall actRewinderExecute(TObject *Sender);
    void __fastcall actForwarderExecute(TObject *Sender);
    void __fastcall actRewindStopExecute(TObject *Sender);
	void __fastcall actCloneViewExecute(TObject *Sender);
	void __fastcall actMoveViewExecute(TObject *Sender);
private:	// User declarations

    enum eBuildTypes    { btBuildMakefile, btBuildAll };
    enum eDebugMode     { dmStopped, dmRunning, dmPaused };
    enum eTimelapseMode { tmBack, tmStopped, tmForward };

    TZX_HPLUGIN         m_PluginHandle;
    HWND                m_TabHandle;
    bool                m_bDirty;
    bool                m_bDosRunning;
    bool                m_bDosAborted;
    bool                m_bInitialized;
    bool                m_bProcessingData;
    bool                m_bSearchOnly;
    bool                m_bUpdating;
    bool                m_bEditting;
    bool                m_bWasDirty;
    bool                m_bInFileList;
    bool                m_bSearchReplace;
    bool                m_bSearchBackwards;
    TReplaceConfirmType m_SearchReplaceConfirmation;
    int                 m_iWindowRestore;   // the size of the top window to restore to
    int                 m_iErrorLine;
    String              m_sErrorFile;
    int                 m_currentBuildToolIndex;
    ZXParserManager&    m_ParserManager;
    ZXFileManager&      m_FileManager;
    TExtensionMapper*   m_ExtMapper;
    TSciMarker*         m_BreakpointMarker;
    TSciMarker*         m_BreakpointHighlighter;
    TSciMarker*         m_BookMarker;
    eDebugMode          m_DebugMode;
    eTimelapseMode      m_TimelapseMode;

    TMenuItem*          m_CodeTools;
    TMenuItem*          m_mnuBuild;
    int                 m_iFilesOpen;
    int                 m_iConsoleStart;
    std::list<TRect>    m_CloseButtonRects;
    bool                m_bTrace;

    void    __fastcall  AttachToolbars(void);
    void    __fastcall  OnMenuClick(TObject* Sender);
    void    __fastcall  TrapTabEvents(TWinControl* Control);
    void    __fastcall  OnTabHide(TObject *Sender);
    void    __fastcall  OnTabShow(TObject *Sender);
    void    __fastcall  OnTabMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void    __fastcall  UpdateList(void);
    void    __fastcall  FindText(void);
    void    __fastcall  FindInFiles(void);
    void    __fastcall  SearchProjectFiles(void);
    void    __fastcall  SearchOpenFiles(void);
    void    __fastcall  SearchInFolders(void);
    void    __fastcall  RunApplication(String sApp, String sParams);
    String  __fastcall  Substitute(const String& sParameters, const String& sFind, const String& sReplace);
    bool    __fastcall  ExecuteTool(const String& commandLine);
    bool    __fastcall  Build(ZXToolDefinition builder, TStringList* buildFiles, AnsiString sParameters);
    bool    __fastcall  Build(eBuildTypes BuildType, bool useInternalCompiler = false);
    void    __fastcall  BuildMakefile(void);
    void    __fastcall  BinToSna(const String& sBinFile, int iAddress);
    void    __fastcall  SaveSettings(void);
    void    __fastcall  LoadSettings(void);
    bool    __fastcall  LoadFile(int iIndex);
    void    __fastcall  MenusAdd(void);
    void    __fastcall  MenusRemove(void);
    bool    __fastcall  GotErrorInfo(const String& sLine, String& sFile, int& iLine);
    bool    __fastcall  FindErrorInfo(bool bLoadFile = true);
    String  __fastcall  Subst(const String& sString, char cFind, char cReplaceWith);
    String  __fastcall  ReplaceSubString(const String& text, const String& find, const String& replace);
    void    __fastcall  CloseDocuments();
    void    __fastcall  UpdateTargetFiles();
    void    __fastcall  HighlightCurrentLine();
    void    __fastcall  HighlightLine(const String& File, int Line);
    bool    __fastcall  Pasmo(const String& File);
    void    __fastcall  OnBreakpointHit(const String& File, int Line);
    void    __fastcall  UpdateBreakpoints();

public:		// User declarations
            __fastcall  TfrmCodeEditor(TComponent* Owner, ZXFileManager& FileManager, ZXParserManager& ParserManager);
            __fastcall ~TfrmCodeEditor();

    void    __fastcall  Clear(void);
    void    __fastcall  UpdateEditor(void);
    void    __fastcall  DeleteKey(void);
    void    __fastcall  EditCopy(void);
    void    __fastcall  EditCut(void);
    void    __fastcall  EditPaste(void);

    HRESULT __fastcall  Initialise(TZX_HPLUGIN PluginHandle);
    HRESULT __fastcall  ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
    HRESULT __fastcall  Release(void);
    HRESULT __fastcall  Save(KXmlInfo& xmlInfo, bool bCleanDirty = true);
    HRESULT __fastcall  Load(KXmlInfo& xmlInfo);
    void    __fastcall  Add(const String& file);
    void    __fastcall  UpdateEditorSlots(void);
    void    __fastcall  UpdateControls(bool bChangeName = false);
    void    __fastcall  SetDirty(void);
    bool    __fastcall  DoSubstitutes(String& sParameters);
    void    __fastcall  SetContext(const Z80& Context);
    void    __fastcall  SplitString(const String& text, const String& seps, std::vector<String>& list);
    void    __fastcall  ConsolePrint(String sMessage);

    __property bool     IsDirty = { read = m_bDirty };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCodeEditor *frmCodeEditor;
//---------------------------------------------------------------------------
#endif
