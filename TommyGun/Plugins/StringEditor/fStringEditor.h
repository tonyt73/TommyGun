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
#ifndef fStringEditorH
#define fStringEditorH
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
#include <CheckLst.hpp>
#include <ActnList.hpp>
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
#include "ZXTableManager.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
//---------------------------------------------------------------------------
class TfrmStringEditor : public TForm
{
__published:	// IDE-managed Components
    TPageControl *pgcStringMap;
    TTabSheet *tabStringTables;
    TScrollBox *scpStringObjects;
    TImageList *imgTabImages;
    TPanel *panStringEditorMap;
    TPanel *panStringEditor;
    TImageList *imgIcons;
    TToolBar *tbrStrings;
    TToolButton *tbnAddString;
    TToolButton *tbnRemoveString;
    TListView *lstStrings;
    TToolButton *ToolButton1;
    TActionList *actList;
    TAction *actAddString;
    TAction *actRemoveString;
    TToolButton *tbnCloneString;
    TAction *actCloneString;
    TToolButton *tbnEditString;
    TAction *actEditString;
    TToolButton *ToolButton2;
    TToolButton *tbnUpString;
    TToolButton *tbnDownString;
    TAction *actUpString;
    TAction *actDownString;
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
    TImage *Image6;
    TLabel *Label52;
    TLabel *Label53;
    TPanel *panImageKeysBar;
    TImage *imgLargeIcon;
    TImage *imgSmallIcon;
    TPanel *panTables;
    TLabel *lblName;
    TLabel *lblTables;
    TEdit *edtTableName;
    TBitBtn *cmdTableAdd;
    TBitBtn *cmdTableRemove;
    TBitBtn *cmdTableRename;
    TPanel *panFileList;
    TListBox *lstTables;
    TBitBtn *cmdTableClone;
    TBitBtn *cmdTableMoveUp;
    TBitBtn *cmdTableMoveDown;
    void __fastcall actAddStringExecute(TObject *Sender);
    void __fastcall actRemoveStringExecute(TObject *Sender);
    void __fastcall actCloneStringExecute(TObject *Sender);
    void __fastcall lstStringsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall actEditStringExecute(TObject *Sender);
    void __fastcall actUpStringExecute(TObject *Sender);
    void __fastcall actDownStringExecute(TObject *Sender);
    void __fastcall edtTableNameChange(TObject *Sender);
    void __fastcall cmdTableAddClick(TObject *Sender);
    void __fastcall cmdTableRemoveClick(TObject *Sender);
    void __fastcall cmdTableCloneClick(TObject *Sender);
    void __fastcall cmdTableRenameClick(TObject *Sender);
    void __fastcall lstTablesClick(TObject *Sender);
    void __fastcall lstStringsClick(TObject *Sender);
    void __fastcall cmdTableMoveUpClick(TObject *Sender);
    void __fastcall cmdTableMoveDownClick(TObject *Sender);
    void __fastcall lstStringsChange(TObject *Sender, TListItem *Item, TItemChange Change);
    void __fastcall pgcStringMapDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active);
private:	// User declarations
    TZX_HPLUGIN                     m_PluginHandle;
    HWND                            m_TabHandle;
    bool                            m_bSaved;

    bool                            m_bInitialized;
    bool                            m_bProcessingData;

    ZXTableManager                  m_TableManager;

    void            __fastcall  UpdateControls(void);
    void            __fastcall  UpdateTableList(void);
    void            __fastcall  UpdateStringsList(void);

public:		// User declarations
                    __fastcall  TfrmStringEditor(TComponent* Owner);
                    __fastcall ~TfrmStringEditor();

    HRESULT         __fastcall  Initialise(TZX_HPLUGIN PluginHandle);
    HRESULT         __fastcall  ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
    HRESULT         __fastcall  Release(void);
    bool            __fastcall  IsDirty(void) { return m_TableManager.IsDirty;  }
    void            __fastcall  Clear(void);
    bool            __fastcall  Load(KXmlInfo* xmlInfo);
    bool            __fastcall  Save(KXmlInfo* xmlInfo);
    void            __fastcall  NewTable(const String& name) { m_TableManager.AddTable(name); UpdateTableList(); }
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStringEditor *frmStringEditor;
//---------------------------------------------------------------------------
#endif
