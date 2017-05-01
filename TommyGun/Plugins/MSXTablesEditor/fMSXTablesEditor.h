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
#ifndef fMSXTablesEditorH
#define fMSXTablesEditorH
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
#include "KShadePanel.h"
#include "KSlider.h"
#include "KSpinEdit.h"
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
#include <CheckLst.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
using namespace Scorpio;
//---------------------------------------------------------------------------
class TfrmMSXTablesEditor : public TForm
{
__published:	// IDE-managed Components
    TPageControl *pgcMSXTablesMap;
    TTabSheet *tabMSXTablesObjects;
    TScrollBox *scpMSXTablesObjects;
    TImageList *imgTabImages;
    TPanel *panMSXTablesEditorMap;
    TTabSheet *tabTiles;
    TPanel *panTilesBrowser;
    TLabel *lblTilesZoom;
    KSpinEdit *spnTilesZoom;
    TStatusBar *stsMapBitmapsStatus;
    TScrollBox *scpMapTiles;
    TPanel *panMapBitmapPanels;
    TTabSheet *tabSprites;
    TTabSheet *tabFonts;
    TPanel *Panel1;
    TLabel *Label8;
    KSpinEdit *FlatSpinEditInteger1;
    TStatusBar *StatusBar1;
    TStatusBar *StatusBar2;
    TPanel *Panel2;
    TLabel *Label9;
    KSpinEdit *FlatSpinEditInteger2;
    TPanel *Panel3;
    TPanel *Panel4;
    TLabel *Label13;
    TBitBtn *FlatButton5;
    TLabel *Label14;
    TLabel *Label15;
    TBitBtn *FlatButton6;
    TBitBtn *FlatButton7;
    TPanel *panNameDesigner;
    TPanel *panTilesButtons;
    TBitBtn *cmdTileMinimize;
    TBitBtn *cmdTileRestore;
    TBitBtn *cmdTileMaximize;
    TBitBtn *cmdTileIncrease;
    TBitBtn *cmdTileDecrease;
    TSplitter *splEditors;
    TPanel *panPatternNameDesignerContainer;
    TScrollBox *sbxPatternNameDesigner;
    TImage *imgPatternNameGrid;
    TPanel *panPatternNameContainer;
    TPanel *panPatternNameDesigner;
    TPanel *panMapButtons;
    TBitBtn *cmdMapMinimize;
    TBitBtn *cmdMapRestore;
    TBitBtn *cmdMapMaximize;
    TBitBtn *cmdMapIncrease;
    TBitBtn *cmdMapDecrease;
    TToolBar *ToolBar1;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TPanel *panPatterColorDesigner;
    TScrollBox *sbxPatternColourDesigner;
    TImage *imgPatternColorGrid;
    TPanel *panOptions;
    TListBox *lstSpriteList;
    TBitBtn *cmdSpriteRename;
    TBitBtn *cmdSpriteClone;
    TBitBtn *cmdMSXTablesMapRemove;
    TBitBtn *cmdMSXTablesMapAdd;
    TEdit *edtMSXTablesMapName;
    TLabel *Label4;
    TLabel *Label3;
    TLabel *Label2;
    TLabel *lblPatternsType;
    TImage *imgSmallIcon;
    TImage *imgLargeIcon;
    TLabel *lblMSXTablesMapName;
    TPanel *panPatternInfo;
    TLabel *Label1;
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
    TZX_HPLUGIN                     m_PluginHandle;
    HWND                            m_TabHandle;
    bool                            m_bSaved;

    bool                            m_bInitialized;
    bool                            m_bProcessingData;

    void            __fastcall  AttachToolbars(void);
    void            __fastcall  OnMenuClick(TObject* Sender);
    void            __fastcall  TrapTabEvents(TWinControl* Control);
    void            __fastcall  OnTabHide(TObject *Sender);
    void            __fastcall  OnTabShow(TObject *Sender);

public:		// User declarations
                    __fastcall  TfrmMSXTablesEditor(TComponent* Owner);
                    __fastcall ~TfrmMSXTablesEditor();

    HRESULT         __fastcall  Initialise(TZX_HPLUGIN PluginHandle);
    HRESULT         __fastcall  ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
    HRESULT         __fastcall  Release(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMSXTablesEditor *frmMSXTablesEditor;
//---------------------------------------------------------------------------
#endif
