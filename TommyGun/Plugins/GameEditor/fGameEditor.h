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
#ifndef fGameEditorH
#define fGameEditorH
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
#include <Menus.hpp>
#include <ActnList.hpp>
#include <Dialogs.hpp>
#include <AppEvnts.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <OleCtrls.hpp>
#include "shdocvw_ocx.h"
#include "KShadePanel.h"
#include "KSlider.h"
#include "KSpinEdit.h"
#include "KRegistry.h"
#include "pngimage.hpp"
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
#include "PropertyEditor.h"
#include "Keys.h"
#include "WindowArea.h"
#include "JumpTable.h"
#include "CollisionDistance.h"
#include "Sounds.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GameEditor
    {
        enum TVIcons
        {
            tviProperty,
            tviUnknown,
            tviSetting,
            tviKeyboard,
            tviSounds,
            tviWindow,
            tviJump,
            tviKeys,
            tviSprites,
            tviGroup,
            tviTextDoc,
            tviTextNew,
            tviBlocks,
            tviObjects
        };
        //---------------------------------------------------------------------------
        class TfrmGameEditor : public TForm
        {
        __published:    // IDE-managed Components
            TPanel *panTools;
            TPageControl *pgcTools;
            TTabSheet *tabOptions;
            TPanel *panContainer;
            TPanel *panTitle;
            TActionList *actMain;
            TAction *actZoomIn;
            TAction *actZoomOut;
            TAction *actMaskModeOff;
            TAction *actMaskModeOn;
            TAction *actMaskGenerate;
            TAction *actMaskInvert;
            TAction *actToggleCharGrid;
            TAction *actTogglePixelGrid;
            TAction *actToggleAnimationUnderlay;
            TAction *actToggleHotSpot;
            TPopupMenu *popImage;
            TMenuItem *popToggleGridChar;
            TMenuItem *popToggleGridPixel;
            TMenuItem *popZoomIn;
            TMenuItem *popZoomOut;
            KRegistry *regScorpio;
            TApplicationEvents *appEvents;
            TImageList *imgTabImages;
            TImage *imgLargeIcon;
            TImage *imgSmallIcon;
            TPageControl *pgcEditors;
            TTabSheet *tabWelcome;
            TTabSheet *tabWindowArea;
            TTabSheet *tabKeys;
            TTabSheet *tabJumpTable;
            TTabSheet *tabSounds;
            TTreeView *tvwPropertyView;
            TSplitter *Splitter1;
            TValueListEditor *vlePropertyEditor;
            TImage *imgKeyboard;
            TImage *imgKey1;
            TImage *imgKey2;
            TImage *imgKey3;
            TImage *imgKey4;
            TImage *imgKey5;
            TImage *imgKey6;
            TImage *imgKey7;
            TPanel *panImageKeysPanel;
            TLabel *Label2;
            TLabel *Label3;
            TPanel *panImageKeysBar;
            TLabel *lblKeysInstructions;
            TPanel *panScorePanel;
            TCheckBox *chkShowScorePanel;
            TLabel *lblScorePanelNote;
            TPanel *panLayoutContainer;
            TPanel *panWindowArea;
            TImage *imgLayout;
            TImage *imgScorePanel;
            TImage *imgCheckers;
            TImage *imgWindow;
            TLabel *lblWelcome;
            TRichEdit *rteWelcome;
            TPanel *panGameStyle;
            TBitBtn *btnArcade;
            TBitBtn *btnPlatform;
            TBitBtn *btnShootemUp;
            TLabel *lblGameStyle;
            TLabel *Label11;
            TPanel *panJumpTableContainer;
            TPanel *panJumpTable;
            TImage *imgJumpTable;
            TButton *btnReset;
            TLabel *lblCopyright;
            TButton *btnUpdate;
            TImage *Image1;
            TImage *Image2;
            TLabel *Label1;
            TImage *Image3;
            TImage *Image4;
            TLabel *Label4;
            TTabSheet *tabHelp;
            TRichEdit *rteHelp;
            TTimer *tmrUpdate;
            TPanel *Panel1;
            TLabel *Label5;
            TImage *Image5;
            TPanel *Panel2;
            TPanel *panSounds;
            TPanel *panLeft;
            TPanel *panRight;
            TPanel *panCenter;
            TLabel *Label6;
            TLabel *Label7;
            TListView *lstAvailableSfx;
            TListView *lstGameSfx;
            TBitBtn *cmdSndAdd;
            TBitBtn *cmdSndRemove;
            TBitBtn *cmdSndUp;
            TBitBtn *cmdSndDown;
            void __fastcall FormCreate(TObject *Sender);
            void __fastcall imgKeyboardMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
            void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
            void __fastcall tabWindowAreaResize(TObject *Sender);
            void __fastcall chkShowScorePanelClick(TObject *Sender);
            void __fastcall btnArcadeClick(TObject *Sender);
            void __fastcall btnPlatformClick(TObject *Sender);
            void __fastcall btnShootemUpClick(TObject *Sender);
            void __fastcall imgWindowMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
            void __fastcall imgWindowMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall tabJumpTableResize(TObject *Sender);
            void __fastcall imgJumpTableMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall imgJumpTableMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
            void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
            void __fastcall btnResetClick(TObject *Sender);
            void __fastcall tvwPropertyViewChange(TObject *Sender, TTreeNode *Node);
            void __fastcall btnUpdateClick(TObject *Sender);
            void __fastcall vlePropertyEditorKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
            void __fastcall vlePropertyEditorSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
            void __fastcall vlePropertyEditorExit(TObject *Sender);
            void __fastcall vlePropertyEditorSetEditText(TObject *Sender, int ACol, int ARow, const AnsiString Value);
            void __fastcall imgWindowMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall pgcEditorsChange(TObject *Sender);
            void __fastcall tmrUpdateTimer(TObject *Sender);
            void __fastcall tabSoundsResize(TObject *Sender);
            void __fastcall lstAvailableSfxSelectItem(TObject *Sender, TListItem *Item, bool Selected);
    void __fastcall lstGameSfxSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
    void __fastcall cmdSndAddClick(TObject *Sender);
    void __fastcall cmdSndRemoveClick(TObject *Sender);
    void __fastcall cmdSndUpClick(TObject *Sender);
    void __fastcall cmdSndDownClick(TObject *Sender);
        private:    // User declarations

            enum GameStyle { gsNone, gsArcade, gsPlatform, gsShootEmUp };

            TZX_HPLUGIN         m_PluginHandle;
            HWND                m_TabHandle;
            bool                m_bSaved;
            bool                m_bInitialized;
            bool                m_bScorePanelFound;
            GameStyle           m_GameStyle;

            typedef Graphics::TBitmap* ZXBitmap;
            std::vector<TToolBar*>  m_ToolBars;
            std::vector<TMenuItem*> m_ToolBarMenus;
            std::vector<String>     m_vTileNames;
            std::vector<ZXBitmap>   m_vTileBitmaps;

            PropertyEditor      m_PropertyEditor;
            WindowArea          m_WindowArea;
            JumpTable           m_JumpTable;
            Keys                m_Keys;
            CollisionDistance   m_CollisionDistance;
            Sounds              m_Sounds;
            
            int                 m_lastWindowWidth;
            int                 m_lastWindowHeight;

            void    __fastcall  OnMenuClick(TObject* Sender);
            void    __fastcall  TrapTabEvents(TWinControl* Control);
            void    __fastcall  OnTabHide(TObject *Sender);
            void    __fastcall  OnTabShow(TObject *Sender);
            String  __fastcall  ZeroPadInt(int iValue, int iSize);
            void    __fastcall  MenusAdd(void);
            void    __fastcall  MenusRemove(void);
            void    __fastcall  RefreshView(void);
            void    __fastcall  LoadSettings(void);
            void    __fastcall  SaveSettings(void);
            void    __fastcall  SetupWelcome();
            void    __fastcall  UpdateSndButtons();

        public:        // User declarations
                    __fastcall  TfrmGameEditor(TComponent* Owner);
                    __fastcall ~TfrmGameEditor();

            HRESULT __fastcall  Initialise(TZX_HPLUGIN PluginHandle);
            HRESULT __fastcall  ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
            HRESULT __fastcall  Release(void);
            void    __fastcall  Update();
            void    __fastcall  RefreshTiles();

            // file
            void    __fastcall  New();
            bool    __fastcall  Load(KXmlInfo& xmlInfo);
            void    __fastcall  Save(KXmlInfo& xmlInfo);
            bool    __fastcall  IsDirty();

            //bool    __fastcall  AddTab(const String& sCaption, Graphics::TBitmap* pBitmap, TTabSheet*& pTabSheet);
            void    __fastcall  EditCopy(void);
            void    __fastcall  EditCut(void);
            void    __fastcall  EditPaste(void);

            PropertyEditor& __fastcall  GetPropertyEditor() { return m_PropertyEditor; }
        };
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::GameEditor::TfrmGameEditor *frmGameEditor;
//---------------------------------------------------------------------------
#endif
