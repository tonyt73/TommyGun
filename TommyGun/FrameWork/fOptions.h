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
#ifndef fOptionsH
#define fOptionsH
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include "KRegistry.h"
#include "KIconButton.h"
#include <Buttons.hpp>
#include "KSpinEdit.h"
#include "pngimage.hpp"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <map>
#include "..\Helpers\BandManager.h"
//#include "ZXPlugin.h"
//---------------------------------------------------------------------------
//using namespace Scorpio;
//using namespace Plugin;
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GUI
    {
        struct TPluginInfo
        {
            DWORD       Handle;
            String      Name;
            String      RegName;
            String      Vendor;
            String      PluginVersion;
            String      FileVersion;
            bool        IsUnloadable;
            bool        DoNotLoad;
            bool        DoNotShow;
            DWORD       Priority;
            int         LoadOrder;
            TPanel*     Panel;
            TShape*     Shape;
            TCheckBox*  CheckBox;
            TLabel*     Label;
            TImage*     Image;
            TImage*     Icon;
        };

        //---------------------------------------------------------------------------
        class TfrmOptions : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panOptionsButtons;
            TButton *cmdClose;
            TButton *cmdApply;
            TBevel *bvlBevel00;
            TImage *imgArrowUpDown;
            TImageList *imgPriorityIcons;
            TImage *imgDefaultIcon;
            KRegistry *regScorpio;
            TPanel *panButtonsContainer;
            TPanel *panButtons;
            TPanel *panPluginsContainer;
            TPageControl *pgcOptions;
            TTabSheet *tabGeneral;
            TTabSheet *tabOptionsPlugins;
            TPanel *panGeneral;
            TPanel *panPlugins;
            TPanel *panPluginsRed;
            TPanel *panPluginsYellow;
            TPanel *panPluginsGreen;
            TPanel *panPluginsAqua;
            TPanel *panGeneralRed;
            TPanel *panGeneralYellow;
            TPanel *panGeneralGreen;
            TPanel *panGeneralAqua;
            TImageList *imgBigIcons;
            TTabSheet *tabProject;
            TPanel *panProject;
            TPanel *panProjectRed;
            TPanel *panProjectYellow;
            TPanel *panProjectGreen;
            TPanel *panProjectAqua;
            TGroupBox *grpSplashScreen;
            TCheckBox *chkShowSplashScreen;
            TGroupBox *grpPluginDirectory;
            TLabel *lblOptionsPluginMachineSpecific;
            TPanel *panPluginsMachine;
            TGroupBox *grpProjectDialog;
            TEdit *edtProjectFolder;
            TButton *spdProjectFolderBrowse;
            TTabSheet *tabOptionsUndo;
            TPanel *panUndo;
            TPanel *panUndoRed;
            TPanel *panUndoYellow;
            TPanel *panUndoGreen;
            TPanel *panUndoAqua;
            TGroupBox *grpUndo;
            TCheckBox *chkUndoEnableUndo;
            TCheckBox *chkUndoMemoryLimit;
            TLabel *lblUndoMB;
            TCheckBox *chkUndoEnabledRedo;
            TCheckBox *chkUndoClear;
            TLabel *lblUndoMessage;
            TLabel *lblUndoWarning;
            TImage *imgWarning;
            TPanel *panIconsUp;
            TPanel *panButtonsDown;
            TSpeedButton *spdPluginsUp;
            TSpeedButton *spdPluginsDown;
            TPanel *panButtonContainer;
            TPanel *panIconScroller;
            KIconButton *cmdGeneral;
            KIconButton *cmdPlugins;
            KIconButton *cmdProject;
            KIconButton *cmdUndo;
            TTabSheet *tabKeys;
            TPanel *panKeys;
            TPanel *panKeysRed;
            TPanel *panKeysYellow;
            TPanel *panKeysGreen;
            TPanel *panKeysAqua;
            TGroupBox *grpKeys;
            KIconButton *cmdKeys;
            TScrollBox *scpKeys;
            TPanel *panKeysGeneral;
            TTimer *tmrScrollTimer;
            TCheckBox *chkUndoEnableDialog;
            TRadioButton *radUndoAutoSwitchTo;
            TRadioButton *radUndoGroupByPlugin;
            TPanel *panCommonKeys;
            TLabel *lblKeysGeneral;
            TImage *Image1;
            TLabel *Label2;
            TLabel *Label3;
            TImage *Image2;
            TLabel *Label4;
            TLabel *Label5;
            TImage *Image4;
            TLabel *Label8;
            TLabel *Label9;
            TImage *Image5;
            TLabel *Label10;
            TLabel *Label11;
            TImage *Image6;
            TLabel *Label12;
            TLabel *Label13;
            TImage *Image7;
            TLabel *Label14;
            TLabel *Label15;
            TImage *Image8;
            TLabel *Label16;
            TLabel *Label17;
            TImage *Image9;
            TLabel *Label18;
            TLabel *Label19;
            TImage *Image10;
            TLabel *Label20;
            TLabel *Label21;
            TLabel *Label22;
            TLabel *Label23;
            TLabel *Label24;
            TLabel *Label25;
            TLabel *Label26;
            TLabel *Label27;
            TLabel *Label28;
            TImage *Image11;
            TLabel *Label29;
            TLabel *Label30;
            TImage *Image12;
            TLabel *Label31;
            TLabel *Label32;
            TImage *Image13;
            TLabel *Label33;
            TLabel *Label34;
            TImage *Image14;
            TLabel *Label35;
            TLabel *Label36;
            TLabel *Label37;
            TLabel *Label38;
            TLabel *Label39;
            TLabel *Label40;
            TLabel *Label41;
            TLabel *Label42;
            TLabel *Label43;
            TPanel *panKeysGeneralBar;
            TTabSheet *tabBackup;
            TPanel *panBackup;
            TPanel *Panel2;
            TPanel *Panel3;
            TPanel *Panel4;
            TPanel *Panel5;
            TGroupBox *grpBackup;
            KIconButton *cmdBackup;
            TCheckBox *chkBackupEnabled;
            TLabel *lblBackupFolders;
            TCheckBox *chkLimitBackupUsage;
            TRadioButton *radBackupOnSave;
            TRadioButton *radBackupOnClose;
            TLabel *lblBackupWhen;
            TLabel *lblBackupOnClose;
            TLabel *lblBackupOnSave;
            TCheckBox *chkRemoveWhitespaceFromXML;
            TLabel *lblRemoveWhitespace;
            TBevel *Bevel1;
            TLabel *Label6;
            TLabel *Label7;
            TBevel *Bevel2;
            TCheckBox *chkShowPluginIcons;
            TBevel *Bevel3;
            TLabel *Label44;
            TCheckBox *chkLoggingProduceFiles;
            TLabel *lblDebugging;
            TLabel *lblOptionsPluginsLoad;
            TLabel *lblOptionsPluginsPluginName;
            TLabel *lblReorderMessage;
            TPanel *panOptionsLoadOrderContainer;
            TPanel *panOptionsPluginsFramer;
            TScrollBox *sbxPlugins;
            TPanel *panOptionsPluginContainerBody;
            TPanel *panOptionsPluginContainer;
            TPanel *panOptionsPlugin;
            TShape *shpOptionsPluginName;
            TLabel *lblOptionsPluginsName;
            TImage *imgOptionsPluginsPriority;
            TImage *imgPluginIcon;
            TCheckBox *chkOptionsPluginName;
            TLabel *Label45;
            TBevel *Bevel4;
            KSpinEdit *edtBackupFolders;
            KSpinEdit *edtUndoMemory;
    TLabel *lblAppDataFolder;
    TLabel *Label1;
    TLabel *Label46;
    TLabel *Label47;
    TLabel *Label48;
    TLabel *Label49;
    TLabel *Label50;
	TFileOpenDialog *dlgBrowse;
            void __fastcall cmdCloseClick(TObject *Sender);
            void __fastcall chkOptionsPluginNameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall chkOptionsPluginNameMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
            void __fastcall chkOptionsPluginNameMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall cmdApplyClick(TObject *Sender);
            void __fastcall FormShow(TObject *Sender);
            void __fastcall chkOptionsPluginNameClick(TObject *Sender);
            void __fastcall cmbOptionsPluginMachineSpecificChange(TObject *Sender);
            void __fastcall cmdGeneralClick(TObject *Sender);
            void __fastcall spdProjectFolderBrowseClick(TObject *Sender);
            void __fastcall edtProjectFolder2Change(TObject *Sender);
            void __fastcall spdPluginsUpClick(TObject *Sender);
            void __fastcall spdPluginsDownClick(TObject *Sender);
            void __fastcall chkUndoEnableUndoClick(TObject *Sender);
            void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
            void __fastcall tmrScrollTimerTimer(TObject *Sender);
    void __fastcall chkBackupEnabledClick(TObject *Sender);
    void __fastcall lblAppDataFolderClick(TObject *Sender);
        private:	// User declarations

            std::vector<TPluginInfo>    m_Plugins;
            ZXBandManager*              m_BandManager;
            int                         m_BandPosition;
            bool                        m_bPluginsChanged;
            bool                        m_bPluginChangesApplied;
            int                         m_iTopOfButtons;
            int                         m_iKeyPanelHeights;

            TPanel*     __fastcall      FindPanel(TObject *Sender);
            void        __fastcall      AddPlugin(TPluginInfo& PluginInfo);
            void        __fastcall      SortPlugins(void);
            void        __fastcall      FindMachineSpecificFolders(void);
            void        __fastcall      DonotLoadChanged(TObject *Sender);

        public:		// User declarations
                        __fastcall      TfrmOptions(TComponent* Owner);
                        __fastcall     ~TfrmOptions();

            String      __fastcall      ReadMachineFolder(void);
            void        __fastcall      WriteMachineFolder(const String& sMachineFolder);

            void        __fastcall      ClearPlugins(void);
            void        __fastcall      AddPlugin(DWORD Handle,
                                                  String sName,
                                                  String sRegName,
                                                  String sVendor,
                                                  String sPluginVersion,
                                                  String sFileVersion,
                                                  bool   bIsUnloadable,
                                                  bool   bDoNotLoad,
                                                  bool   bDoNotShow,
                                                  DWORD  dwPriority,
                                                  int    iLoadOrder,
                                                  TImage* Icon);
            void        __fastcall      RemovePlugin(DWORD Handle);
            bool        __fastcall      Execute(void);
            void        __fastcall      Changed(void);
        };
    }
}
//---------------------------------------------------------------------------
#endif
