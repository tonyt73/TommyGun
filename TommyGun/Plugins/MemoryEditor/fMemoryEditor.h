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
#ifndef fMemoryEditorH
#define fMemoryEditorH
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
#include <ActnList.hpp>
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
#include "KSlider.h"
#include "KSpinEdit.h"
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
//---------------------------------------------------------------------------
enum eMemory    { memCustom, memROM, memSystem, memScreen, memStack, memSpriteTable, memSprites, memTileTable, memTiles, memCharacterSets, memMapTable, memMapScreens, memLast, memForceSize = 0xFFFFFFFF };
//---------------------------------------------------------------------------
typedef struct
{
    eMemory         eType;
    String          sName;
    String          sMessage;
    unsigned int    iAddress;
    unsigned int    iSize;
    bool            bEnabled;
    bool            bMoveable;
} ZXMemoryObject;
//---------------------------------------------------------------------------
class TfrmMemoryEditor : public TForm
{
__published:	// IDE-managed Components
    TPageControl *pgcMemoryMap;
    TTabSheet *tabMemoryObjects;
    TScrollBox *scpMemoryObjects;
    TTabSheet *tabMemorySettings;
    TImageList *imgTabImages;
    TPanel *panMemoryEditorMap;
    TPanel *panMemoryMapLegend;
    TLabel *Label7;
    TPanel *Panel1;
    TPanel *Panel5;
    TPanel *Panel6;
    TPanel *Panel7;
    TPanel *Panel8;
    TPanel *Panel9;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TPanel *Panel15;
    TPanel *Panel16;
    TPanel *Panel17;
    TPanel *Panel18;
    TScrollBox *sbxMemoryMap;
    TImage *imgMemoryMap;
    TPanel *panMemoryMap;
    TPanel *Panel14;
    TBitBtn *cmdMemoryMapDecrease;
    TBitBtn *cmdMemoryMapIncrease;
    TImage *imgLargeIcon;
    TImage *imgSmallIcon;
    TScrollBox *scpMemorySettings;
    TPanel *Panel2;
    TGroupBox *GroupBox2;
    TRadioButton *FlatRadioButton1;
    TRadioButton *FlatRadioButton2;
    TRadioButton *FlatRadioButton3;
    TPanel *Panel3;
    TGroupBox *GroupBox3;
    TLabel *lblMemoryMapName;
    TLabel *lblMemoryMapCustomObjects;
    TLabel *lblMemoryMapSystemObjects;
    TLabel *lblMemoryMapAddress;
    TLabel *lblMemoryMapSize;
    TEdit *edtMemoryMapName;
    TPanel *panMemoryMapCustomObjects;
    TCheckListBox *lstMemoryMapCustom;
    TPanel *panMemoryMapSystemObjects;
    TCheckListBox *lstMemoryMapSystem;
    TBitBtn *cmdMemoryMapAdd;
    TBitBtn *cmdMemoryMapRemove;
    KSpinEdit *edtMemoryMapAddress;
    KSpinEdit *edtMemoryMapSize;
    TGroupBox *GroupBox1;
    TLabel *lblMemoryMapStackAddress;
    TLabel *lblMemoryMapStackSize;
    KSpinEdit *edtMemoryMapStackAddress;
    KSpinEdit *edtMemoryMapStackSize;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall imgMemoryMapMouseMove(TObject *Sender,TShiftState Shift, int X, int Y);
    void __fastcall cmdMemoryMapDecreaseClick(TObject *Sender);
    void __fastcall cmdMemoryMapIncreaseClick(TObject *Sender);
    void __fastcall lstMemoryMapCustomClickCheck(TObject *Sender);
    void __fastcall lstMemoryMapSystemClickCheck(TObject *Sender);
    void __fastcall sbxMemoryMapResize(TObject *Sender);
    void __fastcall pgcMemoryMapDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active);
private:	// User declarations
    typedef struct
    {
        TRect                       Rect;
        ZXMemoryObject*             MemoryObject;
    } TMouseInfo;

    TZX_HPLUGIN                     m_PluginHandle;
    HWND                            m_TabHandle;
    bool                            m_bSaved;

    bool                            m_bInitialized;
    bool                            m_bProcessingData;

    TMenuItem*                      m_MemoryTools;

    std::vector<ZXMemoryObject*>    m_MemoryObjects;
    unsigned int                    m_iBlockSize;
    unsigned int                    m_iGameAddress;

    std::vector<TMouseInfo>         m_MouseRects;
    std::vector<ZXMemoryObject*>    m_SystemObjects;
    std::vector<ZXMemoryObject*>    m_CustomObjects;

    void            __fastcall  AttachToolbars(void);
    void            __fastcall  OnMenuClick(TObject* Sender);
    void            __fastcall  TrapTabEvents(TWinControl* Control);
    void            __fastcall  OnTabHide(TObject *Sender);
    void            __fastcall  OnTabShow(TObject *Sender);

    void            __fastcall  Setup(TImage* Image, TCheckListBox* SystemList, TCheckListBox* CustomList);
    void            __fastcall  OnMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void            __fastcall  OnSystemCheckClick(TObject *Sender);
    void            __fastcall  OnCustomCheckClick(TObject *Sender);
    void            __fastcall  Update(void);
    void            __fastcall  DrawMemoryObject(ZXMemoryObject* MemoryObject);
    void            __fastcall  Decrease(void);
    void            __fastcall  Increase(void);

    unsigned int    __fastcall MemoryObjects(void);
    ZXMemoryObject* __fastcall  MemoryObject(unsigned int iIndex);
    ZXMemoryObject* __fastcall  MemoryFind(String sName, eMemory Type, bool bMoveable);
    ZXMemoryObject* __fastcall  MemoryAdd(String sName, String sMessage, unsigned int iAddress, unsigned int iSize, eMemory Type, bool bMoveable);
    ZXMemoryObject* __fastcall  MemoryAdd(String sName, unsigned int iAddress, unsigned int iSize);
    bool            __fastcall  MemoryRemove(const String& sName);
    void            __fastcall  InitMemoryObjects(void);
    void            __fastcall  MemoryUpdate(void);


public:		// User declarations
                    __fastcall  TfrmMemoryEditor(TComponent* Owner);
                    __fastcall ~TfrmMemoryEditor();

    HRESULT         __fastcall  Initialise(TZX_HPLUGIN PluginHandle);
    HRESULT         __fastcall  ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
    HRESULT         __fastcall  Release(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemoryEditor *frmMemoryEditor;
//---------------------------------------------------------------------------
#endif
