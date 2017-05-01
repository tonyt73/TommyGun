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
#ifndef fMapEditorH
#define fMapEditorH
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
#include <Menus.hpp>
#include <Dialogs.hpp>
#include "KSlider.h"
#include "KRegistry.h"
#include "KSpinEdit.h"
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
//---------------------------------------------------------------------------
#include "TZXMap.h"
#include "TZXMapEditor.h"
#include "ZXTileManager.h"
#include "TZXTileBrowser.h"
#include "ZXSpriteManager.h"
#include "TZXSpriteBrowser.h"
#include "ZXObjectManager.h"
#include "TZXObjectBrowser.h"
#include "ZXScorePanel.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
//---------------------------------------------------------------------------
class TfrmMapEditor : public TForm
{
__published:	// IDE-managed Components
    TPanel *panBrowser;
    TPageControl *pgcBrowsers;
    TTabSheet *tabMapInfo;
    TScrollBox *TScrollBox2;
    TTabSheet *tabMapTiles;
    TScrollBox *scpMapTiles;
    TPanel *panMapBitmapPanels;
    TPanel *panTilesBrowser;
    TStatusBar *stsMapBitmapsStatus;
    TTabSheet *tabMapSettings;
    TScrollBox *scpProject;
    TImageList *imgIcons;
    TImageList *imgTabImages;
    TPanel *panEditor;
    TSplitter *splEditors;
    TScrollBox *sbxTiles;
    TScrollBox *sbxScreens;
    TImage *imgLayout;
    TPanel *panMapMap;
    TPanel *panMapButtons;
    TBitBtn *cmdMapMinimize;
    TBitBtn *cmdMapRestore;
    TBitBtn *cmdMapMaximize;
    TBitBtn *cmdMapIncrease;
    TBitBtn *cmdMapDecrease;
    TPanel *Panel2;
    TPanel *panMapTiles;
    TPanel *panTilesButtons;
    TBitBtn *cmdTileMinimize;
    TBitBtn *cmdTileRestore;
    TBitBtn *cmdTileMaximize;
    TControlBar *cbrMapEditor;
    TToolBar *tbrMapTools;
    TToolButton *tbnMapTileSelect;
    TToolButton *tbnMapScreenAddAll;
    TToolButton *tbnMapScreenAdd;
    TToolButton *tbnMapScreenRemove;
    TToolButton *tbnMapScreenClone;
    TToolButton *tbnMapSnapToGrid;
    TToolButton *tbnMapAllowIntersections;
    KRegistry *regScorpio;
    TBitBtn *cmdTileIncrease;
    TBitBtn *cmdTileDecrease;
    TImage *imgLargeIcon;
    TImage *imgSmallIcon;
    TToolButton *tbnShowGrid;
    TToolButton *tbnBringToFront;
    TToolButton *tbnSendToBack;
    TLabel *lblTilesZoom;
    KSpinEdit *spnTilesZoom;
    TPopupMenu *popMap;
    TMenuItem *mnuSelectMode;
    TMenuItem *mnuPlaceMode;
    TMenuItem *mnuSnaptoGridToggle;
    TMenuItem *mnuAllowIntersect;
    TMenuItem *mnuToggleGrid;
    TMenuItem *mnuBringToFront;
    TMenuItem *mnuSendToBack;
    TPanel *panMapKeysPanel;
    TLabel *lblKeysImage;
    TImage *Image1;
    TLabel *Label4;
    TLabel *Label6;
    TImage *Image2;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TPanel *panImageKeysBar;
    TImage *Image3;
    TImage *Image4;
    TImage *Image5;
    TLabel *Label13;
    TLabel *Label14;
    TImage *Image6;
    TLabel *Label15;
    TLabel *Label16;
    TImage *Image7;
    TLabel *Label17;
    TLabel *Label18;
    TMenuItem *mnuSaveMapBitmap;
    TSaveDialog *dlgSave;
    TToolButton *tbnMapTileFree;
    TToolButton *tbnMapTileLine;
    TToolButton *tbnMapTileRect;
    TToolButton *tbnMapTileRectFill;
    TToolButton *tbnMapTileCircle;
    TToolButton *tbnMapTileCircleFill;
    TToolBar *tbrMapScreens;
    TToolBar *tbrMapOptions;
    TToolButton *tbnTilesGroup;
    TToolBar *tbrMapOperations;
    TToolButton *tbnSeparator01;
    TToolButton *tbnTilesUngroup;
    TToolButton *tbnMapCommentShowHide;
    TImage *Image9;
    TLabel *Label20;
    TLabel *Label21;
    TImage *Image10;
    TLabel *Label22;
    TLabel *Label23;
    TImage *Image11;
    TLabel *Label24;
    TLabel *Label25;
    TImage *Image12;
    TLabel *Label26;
    TLabel *Label27;
    TImage *Image13;
    TLabel *Label28;
    TLabel *Label29;
    TImage *Image14;
    TLabel *Label30;
    TLabel *Label31;
    TImage *Image15;
    TLabel *Label32;
    TLabel *Label33;
    TImage *Image16;
    TLabel *Label34;
    TLabel *Label35;
    TMenuItem *popToggleComments;
    TMenuItem *mnuPreviousTileTool;
    TToolButton *tbnOverwriteTiles;
    TPanel *panMapInfo;
    TButton *cmdMapApplyChanges;
    TGroupBox *grpMapScreenSize;
    TLabel *lblMapScreenSizeWidth;
    KSlider *slrMapScreenSizeWidth;
    TLabel *lblMapScreenSizeHeight;
    KSlider *slrMapScreenSizeHeight;
    KSpinEdit *edtMapScreenSizeWidth;
    KSpinEdit *edtMapScreenSizeHeight;
    TGroupBox *grpMapMapSize;
    TLabel *lblMapMapSizeScreensAcross;
    KSlider *slrMapMapSizeScreensAcross;
    TLabel *lblMapMapSizeScreenDown;
    KSlider *slrMapMapSizeScreensDown;
    KSpinEdit *edtMapMapSizeScreensAcross;
    KSpinEdit *edtMapMapSizeScreensDown;
    TGroupBox *grpMapType;
    TRadioButton *radMapTypeTileFlip;
    TRadioButton *radMapTypeIsometricFlip;
    TRadioButton *radMapTypeTileScrolling;
    TPanel *panSettings;
    TGroupBox *GroupBox1;
    TLabel *lblScorePanelNote;
    TLabel *lblXOverlap;
    TLabel *lblYOverlap;
    TCheckBox *chkShowScorePanel;
    KSpinEdit *edtMapEditorXOverlap;
    KSpinEdit *edtMapEditorYOverlap;
    TGroupBox *grpMapEditorScreenLayout;
    TGroupBox *grpMapEditorScreenLayoutTiling;
    TLabel *lblMapEditorScreenLayoutTilingWidth;
    KSlider *slrMapEditorScreenLayoutTilingWidth;
    TLabel *lblMapEditorScreenLayoutTilingHeight;
    KSlider *slrMapEditorScreenLayoutTilingHeight;
    TCheckBox *chkMapEditorScreenLayoutTilingSnapToGrid;
    TCheckBox *chkMapEditorScreenLayoutTilingDoNotIntersect;
    KSpinEdit *edtMapEditorScreenLayoutTilingWidth;
    KSpinEdit *edtMapEditorScreenLayoutTilingHeight;
    TCheckBox *chkMapEditorScreenLayoutTilingOverwriteOverlap;
    TGroupBox *grpMapEditorScreenLayoutMagnification;
    TLabel *lblMapEditorScreenLayoutMagnificationSize;
    KSlider *slrMapEditorScreenLayoutMagnificationSize;
    KSpinEdit *edtMapEditorScreenLayoutMagnificationSize;
    TGroupBox *grpMapEditorMapLayout;
    TGroupBox *grpMapEditorMapLayoutGap;
    TLabel *lblMapEditorMapLayoutGapSize;
    KSpinEdit *edtMapEditorMapLayoutGapSize;
    TGroupBox *grpMapEditorMapLayoutScreenScale;
    TRadioButton *radMapEditorMapLayoutScreenScale100;
    TRadioButton *radMapEditorMapLayoutScreenScale75;
    TRadioButton *radMapEditorMapLayoutScreenScale50;
    TRadioButton *radMapEditorMapLayoutScreenScale25;
    TRadioButton *radMapEditorMapLayoutScreenScale10;
    TGroupBox *grpRemoveDuplicateScreens;
    TLabel *Label5;
    TLabel *Label2;
    TCheckBox *chkMergeDuplicates;
    TTabSheet *tabMapSprites;
    TTabSheet *tabMapObjects;
    TPanel *Panel3;
    TImageList *imgObjects;
    TPanel *panSpritesBrowser;
    TLabel *lblSpritesZoom;
    KSpinEdit *spnSpritesZoom;
    TStatusBar *stsMapSpriteStatus;
    TScrollBox *scpMapSprites;
    TPanel *panMapSpritePanels;
    TStatusBar *stsMapObjectStatus;
    TListView *lstObjects;
    TPopupMenu *popObjects;
    TMenuItem *mnuAssignInventory;
    TMenuItem *mnuAssignScreen;
    TMenuItem *mnuAssignNoScreen;
    TImage *imgTiles;
    TSplitter *splSprites;
    TListView *lstSprites;
    TImageList *imgSprites;
    TToolBar *tbrSprites;
    TToolButton *tbnSpriteAdd;
    TToolButton *tbnSpriteRemove;
    TToolButton *tbnSpriteAssign;
    TToolButton *tbnSpriteSep01;
    TToolButton *tbnSpriteSep02;
    TToolButton *tbnSpriteSep03;
    TToolButton *tbnSpriteTypeInc;
    TToolButton *tbnSpriteTypeDec;
    TToolBar *ToolBar1;
    TToolButton *tbnObjectsInventory;
    TToolButton *ToolButton2;
    TToolButton *tbnObjectsScreen;
    TToolButton *ToolButton4;
    TToolButton *tbnObjectsNoScreen;
    TPanel *Panel1;
    TLabel *Label1;
    TImage *Image8;
    TPanel *Panel4;
    TLabel *Label3;
    TImage *Image17;
    TPanel *Panel5;
    TLabel *Label19;
    TImage *Image18;
    TGroupBox *GroupBox2;
    TLabel *lblStartScreen;
    TButton *cmdStartScreen;
    void __fastcall cbrMapEditorDblClick(TObject *Sender);
    void __fastcall cmdTileMinimizeClick(TObject *Sender);
    void __fastcall cmdTileRestoreClick(TObject *Sender);
    void __fastcall cmdTileMaximizeClick(TObject *Sender);
    void __fastcall splEditorsMoved(TObject *Sender);
    void __fastcall cmdMapDecreaseClick(TObject *Sender);
    void __fastcall cmdMapIncreaseClick(TObject *Sender);
    void __fastcall chkMapEditorScreenLayoutTilingDoNotIntersectClick(TObject *Sender);
    void __fastcall tbnMapSnapToGridClick(TObject *Sender);
    void __fastcall chkMapEditorScreenLayoutTilingSnapToGridClick(TObject *Sender);
    void __fastcall tbnMapAllowIntersectionsClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall tbnMapScreenAddAllClick(TObject *Sender);
    void __fastcall tbnMapScreenAddClick(TObject *Sender);
    void __fastcall tbnMapScreenRemoveClick(TObject *Sender);
    void __fastcall tbnMapScreenCloneClick(TObject *Sender);
    void __fastcall tbnMapTileSelectClick(TObject *Sender);
    void __fastcall tbnMapTilePlaceClick(TObject *Sender);
    void __fastcall imgLayoutMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgLayoutMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgLayoutMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgTilesMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgTilesMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgTilesMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall cmdMapApplyChangesClick(TObject *Sender);
    void __fastcall radMapEditorMapLayoutScreenScale100Click(TObject *Sender);
    void __fastcall edtMapEditorMapLayoutGapSizeChange(TObject *Sender);
    void __fastcall edtMapEditorScreenLayoutMagnificationSizeChange(TObject *Sender);
    void __fastcall edtMapScreenSizeWidthChange(TObject *Sender);
    void __fastcall edtMapMapSizeScreensAcrossChange(TObject *Sender);
    void __fastcall cmdTileDecreaseClick(TObject *Sender);
    void __fastcall cmdTileIncreaseClick(TObject *Sender);
    void __fastcall chkShowScorePanelClick(TObject *Sender);
    void __fastcall tbnShowGridClick(TObject *Sender);
    void __fastcall edtMapEditorScreenLayoutTilingWidthChange(TObject *Sender);
    void __fastcall tbnBringToFrontClick(TObject *Sender);
    void __fastcall tbnSendToBackClick(TObject *Sender);
    void __fastcall chkMergeDuplicatesClick(TObject *Sender);
    void __fastcall spnTilesZoomChange(TObject *Sender);
    void __fastcall mnuSelectModeClick(TObject *Sender);
    void __fastcall mnuPlaceModeClick(TObject *Sender);
    void __fastcall mnuSnaptoGridToggleClick(TObject *Sender);
    void __fastcall mnuAllowIntersectClick(TObject *Sender);
    void __fastcall mnuToggleGridClick(TObject *Sender);
    void __fastcall mnuSaveMapBitmapClick(TObject *Sender);
    void __fastcall tbnMapCommentShowHideClick(TObject *Sender);
    void __fastcall tbnMapCommentAddClick(TObject *Sender);
    void __fastcall popToggleCommentsClick(TObject *Sender);
    void __fastcall mnuPreviousTileToolClick(TObject *Sender);
    void __fastcall tbnOverwriteTilesClick(TObject *Sender);
    void __fastcall chkMapEditorScreenLayoutTilingOverwriteOverlapClick(TObject *Sender);
    void __fastcall slrMapScreenSizeHeightChange(TObject *Sender);
    void __fastcall slrMapMapSizeScreensAcrossChange(TObject *Sender);
    void __fastcall spnSpritesZoomChanged(TObject *Sender);
    void __fastcall edtMapEditorXOverlapChanged(TObject *Sender);
    void __fastcall edtMapEditorYOverlapChanged(TObject *Sender);
    void __fastcall tbnSpriteAddClick(TObject *Sender);
    void __fastcall tbnSpriteRemoveClick(TObject *Sender);
    void __fastcall tbnSpriteAssignClick(TObject *Sender);
    void __fastcall tbnSpriteTypeIncClick(TObject *Sender);
    void __fastcall tbnSpriteTypeDecClick(TObject *Sender);
    void __fastcall mnuAssignInventoryClick(TObject *Sender);
    void __fastcall mnuAssignScreenClick(TObject *Sender);
    void __fastcall mnuAssignNoScreenClick(TObject *Sender);
    void __fastcall pgcBrowsersChange(TObject *Sender);
    void __fastcall cmdStartScreenClick(TObject *Sender);
    void __fastcall pgcBrowsersDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active);
private:	// User declarations
    TZX_HPLUGIN         m_PluginHandle;
    HWND                m_TabHandle;
    bool                m_bSaved;
    bool                m_bInitialized;
    bool                m_bProcessingData;
    bool                m_bImageChanged;
    TMenuItem*          m_MapTools;
    TMenuItem*          m_mnuMap;
    int                 m_iWindowRestore;   // the size of the top window to restore to
    int                 m_iScrollX;         // start coordinates when scrolling the scrollbox using the middle mouse button
    int                 m_iScrollY;
    TAlign              m_ScorePanelAlign;
    TTextLayout         m_ScorePanelLayout;
    TZXScorePanel       m_ScorePanel;
    TRadioButton*       m_LastRadioButton;

    TZXMap              m_Map;
    TZXMapEditor        m_MapEditor;
    ZXTileManager       m_TileManager;
    TZXTileBrowser      m_TileBrowser;
    ZXSpriteManager     m_SpriteManager;
    TZXSpriteBrowser    m_SpriteBrowser;
    ZXObjectManager     m_ObjectManager;
    TZXObjectBrowser    m_ObjectBrowser;

    void    __fastcall  AttachToolbars(void);
    void    __fastcall  OnMenuClick(TObject* Sender);
    void    __fastcall  TrapTabEvents(TWinControl* Control);
    void    __fastcall  OnTabHide(TObject *Sender);
    void    __fastcall  OnTabShow(TObject *Sender);
    String  __fastcall  ZeroPadInt(int iValue, int iSize);
    void    __fastcall  UpdateButtons(void);
    void    __fastcall  MenusAdd(void);
    void    __fastcall  MenusRemove(void);
    void    __fastcall  UpdateScreenEditor();
    void    __fastcall  RefreshSpritesList();
    void    __fastcall  UpdateControlStates();
    void    __fastcall  UpdateStartScreen();

public:		// User declarations
            __fastcall  TfrmMapEditor(TComponent* Owner);
            __fastcall ~TfrmMapEditor();

    HRESULT __fastcall  Initialise(TZX_HPLUGIN PluginHandle);
    HRESULT __fastcall  ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
    HRESULT __fastcall  Release(void);

    void    __fastcall  TileRemove(const String& sName);
    void    __fastcall  TileRename(const String& sOldName, const String& sNewName);
    void    __fastcall  SpriteRemove(const String& sName);
    void    __fastcall  SpriteRename(const String& sOldName, const String& sNewName);

    void    __fastcall  Clear(void);
    void    __fastcall  Save(KXmlInfo& xmlInfo, bool bCleanDirty = true);
    bool    __fastcall  Load(KXmlInfo& xmlInfo);
    bool    __fastcall  IsDirty(void);
    void    __fastcall  RefreshView(void);
    void    __fastcall  Copy(void)      { m_MapEditor.Copy();   }
    void    __fastcall  Cut(void)       { m_MapEditor.Cut();    }
    void    __fastcall  Paste(void)     { m_MapEditor.Paste();  }
    void    __fastcall  Delete(void)    { m_MapEditor.Delete(); UpdateButtons(); }
    void    __fastcall  UndoRestore(KXmlInfo* xmlInfo);
    void    __fastcall  NewMap(int screenWidth, int screenHeight, int screensAcross, int screensDown, bool overwrite);

    __property  bool    ImageChanged    = { read = m_bImageChanged, write = m_bImageChanged };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMapEditor *frmMapEditor;
//---------------------------------------------------------------------------
#endif
