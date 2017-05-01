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
#ifndef fMusicEditorH
#define fMusicEditorH
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
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include "TButtonUnit.hpp"
#include "TPanelUnit.hpp"
#include "TEditUnit.hpp"
#include "TScrollbarUnit.hpp"
#include "TSpeedButtonUnit.hpp"
#include "TSpinEditUnit.hpp"
#include "KRegistry.h"
#include "KIconButton.h"
#include "TScrollBox.h"
#include "KShadePanel.h"
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
#include "Keyboard.h"
#include "Timeline.h"
#include "Music.h"
#include "Volume.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
//---------------------------------------------------------------------------
class TfrmMusicEditor : public TForm
{
__published:	// IDE-managed Components
    TPanel *panMusicContainer;
    TPanel *panMusic;
    TImageList *imgTabImages;
    KRegistry *regScorpio;
    TControlBar *cbrMusic;
    TToolBar *tbrMusic;
    TPanel *panComposer;
    TPanel *panTB1;
    TSpeedButton *spdPlay;
    TSpeedButton *spdStop;
    TSpinEditInteger *edtTempo;
    TSpinEditInteger *edtPattern;
    TImage *imgTempo;
    TImage *imgPattern;
    TPanel *panPianoPatternContainer;
    TImage *imgSmallIcon;
    TImage *imgLargeIcon;
    TImage *imgKeyRoll;
    TImage *imgKeyTopDown;
    TImage *imgKeyMidDown;
    TImage *imgKeyBotDown;
    TImage *imgKeyBlkDown;
    TSplitter *Splitter1;
    TPanel *panVolumeContainer;
    TImage *imgVolumeCanvas;
    TPanel *panVolumePaddingLeft;
    TPanel *panPianoToolbarContainer;
    TPanel *panPianoContainer;
    TScrollbar *scbKeyboard;
    TImage *imgKeysCanvas;
    TImage *imgMusicCanvas;
    TSpeedButton *spdKeyboardLarge;
    TSpeedButton *spdKeyboardSmall;
    TSpeedButton *spdKeyboardABC;
    TSpeedButton *spdMusicMenu;
    TPanel *panChannelColour;
    TPanel *panHScroll;
    TScrollbar *scbTimeline;
    TSpeedButton *spdDraw;
    TSpeedButton *spdPaint;
    TSpeedButton *spdDelete;
    TSpeedButton *spdSelect;
    TPanel *panVScroll;
    TImage *imgTimelineCanvas;
    TPanel *panTools;
    TPageControl *pgcTools;
    TTabSheet *tabOptions;
    TScrollBox *scpOptions;
    KShadePanel *shpImageEditor;
    TTabSheet *tabMusic;
    TScrollBox *TScrollBox1;
    KShadePanel *KShadePanel1;
    TSpinEditInteger *edtChannel;
    TImage *imgChannel;
    TPanel *panVolumePaddingRight;
    TPanel *panKeyboardScroller;
    TPanel *panMusicScroller;
    TPanel *panVolumeScroller;
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall panPianoPatternContainerResize(TObject *Sender);
    void __fastcall scbTimelineScroll(TObject *Sender, int ScrollPos);
    void __fastcall scbKeyboardScroll(TObject *Sender, int ScrollPos);
    void __fastcall FormResize(TObject *Sender);
private:	// User declarations
    TZX_HPLUGIN             m_PluginHandle;
    HWND                    m_TabHandle;
    bool                    m_bSaved;
    int                     m_iNotesWidth;

    bool                    m_bInitialized;
    bool                    m_bProcessingData;

    ZXKeyboard              m_Keyboard;
    ZXTimeline              m_Timeline;
    ZXMusic                 m_Music;
    ZXVolume                m_Volume;

public:		// User declarations
            __fastcall      TfrmMusicEditor(TComponent* Owner);
            __fastcall     ~TfrmMusicEditor();

    HRESULT __fastcall      Initialise(TZX_HPLUGIN PluginHandle);
    HRESULT __fastcall      ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
    HRESULT __fastcall      Release(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMusicEditor *frmMusicEditor;
//---------------------------------------------------------------------------
#endif
