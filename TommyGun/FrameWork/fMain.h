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
#ifndef fMainH
#define fMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <AppEvnts.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ActnList.hpp>
#include <StdActns.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>
#include "KRegistry.h"
#include "KIconButton.h"
#include "pngimage.hpp"
#include <ActnColorMaps.hpp>
#include <ActnMan.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
#include "FrameWorkInterface.h"
#include "ZXMessageBox.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GUI
    {
        class TfrmMain : public TForm
        {
        __published:	// IDE-managed Components
            TMainMenu *mnuMain;
            TMenuItem *mnuFile;
            TMenuItem *mnuEdit;
            TMenuItem *mnuView;
            TMenuItem *mnuHelp;
            TPanel *panPluginSwitcher;
            TActionList *actMain;
            TAction *actFileNewProject;
            TFileOpen *actFileOpenProject;
            TAction *actFileMergeProject;
            TAction *actFileSaveProject;
            TAction *actFileImport;
            TEditCopy *actEditCopy;
            TAction *actFileExport;
            TAction *actEditRedo;
            TAction *actEditUndoList;
            TFileExit *actFileExit;
            TEditPaste *actEditPaste;
            TEditCut *actEditCut;
            TEditSelectAll *actEditSelectAll;
            TAction *actSwitchTo1;
            TAction *actSwitchTo2;
            TAction *actSwitchTo3;
            TAction *actSwitchTo4;
            TAction *actSwitchTo5;
            TAction *actSwitchTo6;
            TAction *actSwitchTo7;
            TAction *actSwitchTo8;
            TAction *actSwitchTo9;
            TAction *actSwitchTo10;
            TAction *actSwitchTo11;
            TAction *actSwitchTo12;
            TMenuItem *mnuFileNewProject;
            TMenuItem *mnuFileOpenProject;
            TMenuItem *mnuFileSaveProject;
            TMenuItem *mnuFileLine01;
            TMenuItem *mnuFileLine02;
            TMenuItem *mnuFileExit;
            TMenuItem *mnuEditUndo;
            TMenuItem *mnuEditRedo;
            TMenuItem *mnuEditUndoList;
            TMenuItem *mnuEditLine01;
            TMenuItem *mnuEditCut;
            TMenuItem *mnuEditCopy;
            TMenuItem *mnuEditPaste;
            TMenuItem *mnuEditDelete;
            TMenuItem *mnuEditSelectAll;
            TMenuItem *mnuViewStandard;
            TMenuItem *mnuViewLine01;
            TMenuItem *mnuViewOptions;
            TMenuItem *mnuHelpAbout;
            KRegistry *regScorpio;
            TMenuItem *mnuViewToolbars;
            TMenuItem *mnuViewPluginSwitcher;
            TApplicationEvents *appEvents;
            TImageList *imgSmall;
            TImageList *imgLarge;
            TImageList *imgPluginIcons;
            TStatusBar *stsStatus;
            TControlBar *cbrToolbars;
            TToolBar *tbrStandard;
            TToolButton *tbnFileProjectNew;
            TToolButton *tbnFileProjectOpen;
            TToolButton *tbnFileProjectSave;
            TToolButton *tbnSeparator01;
            TToolButton *tbnEditCut;
            TToolButton *tbnEditCopy;
            TToolButton *tbnEditPaste;
            TToolButton *tbnEditDelete;
            TPanel *panToolbars;
            TPanel *panTitle;
            TPanel *panTools;
            TImage *imgTommyGun;
            TAction *actFileCloseProject;
            TMenuItem *mnuFileCloseProject;
            TToolButton *tbnEditUndo;
            TToolButton *tbnEditRedo;
            TAction *actFind;
            TAction *actFindNext;
            TAction *actFindReplace;
            TAction *actFindPrev;
            TMenuItem *mnuEditLine02;
            TMenuItem *mnuEditFindReplace;
            TMenuItem *mnuEditFind;
            TMenuItem *mnuFindAndReplace;
            TMenuItem *mnuFindPrevious;
            TMenuItem *mnuFindNext;
            TMenuItem *mnuFileImport;
            TAction *actEditDelete;
            TPopupMenu *popMRUList;
            TMenuItem *popRemoveProject;
            TMenuItem *popRenameProject;
            TImageList *imgArrows;
            TImageList *imgIconsClassic;
            TAction *actEditUndo;
            TAction *actEditCopy2;
            TAction *actEditCut2;
            TAction *actEditPaste2;
            TMenuItem *popRestoreProject;
            TImageList *imgWinXP;
            TMenuItem *popCopyProject;
            TPanel *Panel3;
            TPanel *panPluginButtonsContainer;
            TPanel *panPluginButtons;
            TPanel *panPluginsDown;
            TSpeedButton *spdPluginsDown;
            TPanel *panPluginsUp;
            TSpeedButton *spdPluginsUp;
            TAction *actRun;
            TMenuItem *mnuGame;
            TMenuItem *mnuRun;
            TToolButton *ToolButton1;
            TToolButton *ToolButton2;
    TPanel *panPageContainer;
    TPageControl *pgcPlugins;
    TTabSheet *tabStartPage;
    TPanel *panTommyGunTitle;
    TImage *Image1;
    TPanel *Panel1;
    TGroupBox *GroupBox1;
    TSpeedButton *cmdProjectRemove;
    TSpeedButton *cmdProjectRestore;
    TSpeedButton *cmdProjectCopy;
    TPanel *panOpenProject;
    TButton *cmdOpenProject;
    TButton *cmdCleanMissingProjects;
    TPanel *panMRUContainer;
    TPanel *panList;
    TListView *lstProjects;
    TGroupBox *GroupBox2;
    TLabel *lblName;
    TLabel *lblMachine;
    TLabel *lblLocation;
    TLabel *lblMessage;
    TEdit *edtNewProjectName;
    TEdit *edtNewProjectLocation;
    TComboBox *cmbNewProjectMachine;
    TButton *cmdBrowse;
    TButton *cmdCreateProject;
	TOpenDialog *dlgOpen;
	TFileOpenDialog *dlgBrowse;
            void __fastcall spdPluginsUpClick(TObject *Sender);
            void __fastcall spdPluginsDownClick(TObject *Sender);
            void __fastcall panPluginButtonsContainerResize(TObject *Sender);
            void __fastcall actSwitch01Execute(TObject *Sender);
            void __fastcall mnuViewStandardClick(TObject *Sender);
            void __fastcall mnuViewPluginSwitcherClick(TObject *Sender);
            void __fastcall FormCreate(TObject *Sender);
            void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
            void __fastcall FormActivate(TObject *Sender);
            void __fastcall appEventsException(TObject *Sender, Exception *E);
            void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
            void __fastcall appEventsHint(TObject *Sender);
            void __fastcall mnuViewOptionsClick(TObject *Sender);
            void __fastcall actFileNewProjectExecute(TObject *Sender);
            void __fastcall actFileOpenProjectAccept(TObject *Sender);
            void __fastcall actFileSaveProjectExecute(TObject *Sender);
            void __fastcall FormResize(TObject *Sender);
            void __fastcall actFileCloseProjectExecute(TObject *Sender);
            void __fastcall cmdOpenProjectClick(TObject *Sender);
            void __fastcall edtNewProjectNameChange(TObject *Sender);
            void __fastcall cmdCreateProjectClick(TObject *Sender);
            void __fastcall lstProjectsClick(TObject *Sender);
            void __fastcall cmdBrowseClick(TObject *Sender);
            void __fastcall cmdCleanMissingProjectsClick(TObject *Sender);
            void __fastcall actFindExecute(TObject *Sender);
            void __fastcall pgcPluginsChange(TObject *Sender);
            void __fastcall actEditDeleteExecute(TObject *Sender);
            void __fastcall popRemoveProjectClick(TObject *Sender);
            void __fastcall popRenameProjectClick(TObject *Sender);
            void __fastcall popMRUListPopup(TObject *Sender);
            void __fastcall lstProjectsColumnClick(TObject *Sender, TListColumn *Column);
            void __fastcall lstProjectsChange(TObject *Sender, TListItem *Item, TItemChange Change);
            void __fastcall lstProjectsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
            void __fastcall actEditCopyExecute(TObject *Sender);
            void __fastcall actEditCutExecute(TObject *Sender);
            void __fastcall actEditPasteExecute(TObject *Sender);
            void __fastcall popRestoreProjectClick(TObject *Sender);
            void __fastcall popCopyProjectClick(TObject *Sender);
            void __fastcall mnuHelpAboutClick(TObject *Sender);
            void __fastcall lstProjectsKeyPress(TObject *Sender, char &Key);
    void __fastcall actRunExecute(TObject *Sender);

        private:    // User declarations
            typedef struct
            {
                TZX_HPLUGIN     PluginHandle;
                KIconButton*    IconButton;
            } TSwitcherButton;
            typedef std::vector<TSwitcherButton>    TSwitcherButtonVector;
            typedef TSwitcherButtonVector::iterator TSwitcherButtonIterator;

            TSwitcherButtonVector   m_SwitcherButtons;      // the buttons use to switch the plugin pages
            ZXMessageBox            m_MessageBox;
            bool                    m_bClosing;
            int                     m_iTopOfButtons;

            void    __fastcall  OnPluginButtonClick(TObject *Sender);
            void    __fastcall  RestoreStates(void);
            void    __fastcall  ClearStatusSlots(void);
            void    __fastcall  GetLocation(void);
            void    __fastcall  GetMachines(void);
            void    __fastcall  UpdateOk(void);
            AnsiString __fastcall GetMyDocumentsFolder();
            void    __fastcall  Registration(void);

        public:     // User declarations
                    __fastcall  TfrmMain(TComponent* Owner);
                    __fastcall ~TfrmMain();

            void    __fastcall  AddSwitcherButton(TZX_HPLUGIN PluginHandle, const String& sCaption);
            void    __fastcall  RemoveSwitcherButton(TZX_HPLUGIN PluginHandle);
            void    __fastcall  SetSwitcherBitmap(TZX_HPLUGIN PluginHandle, TImage* Image);
            void    __fastcall  UpdateOptions(void);
            void    __fastcall  UpdateGUI(void);
            void    __fastcall  SwitchToPlugin(TZX_HPLUGIN PluginHandle);
            void    __fastcall  FillProjectList(void);

            __property  bool    IsClosing   = { read = m_bClosing   };
        };
    }
}
//---------------------------------------------------------------------------
#endif
