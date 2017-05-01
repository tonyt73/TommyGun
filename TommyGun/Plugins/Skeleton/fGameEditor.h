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
#include "KShadePanel.h"
#include "KSlider.h"
#include "KSpinEdit.h"
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
#include <Dialogs.hpp>
#include "KRegistry.h"
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace GameEditor
    {
        //---------------------------------------------------------------------------
        class TfrmGameEditor : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panTools;
            TPageControl *pgcTools;
            TTabSheet *tabOptions;
            TPanel *panContainer;
            TControlBar *cbrGameEditor;
            TToolBar *tbrImageGridTools;
            TPanel *panTitle;
            TPanel *panTilesButtons;
            TBitBtn *cmdZoomOut;
            TBitBtn *cmdZoomIn;
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
    TPanel *panImageKeysPanel;
    TLabel *lblKeysImage;
    TImage *Image1;
    TLabel *Label2;
    TLabel *Label3;
    TImage *Image2;
    TLabel *Label5;
    TLabel *Label4;
    TLabel *Label1;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TPanel *panImageKeysBar;
    TImage *imgLargeIcon;
    TImage *imgSmallIcon;
            void __fastcall FormCreate(TObject *Sender);
        private:	// User declarations

            TZX_HPLUGIN         m_PluginHandle;
            HWND                m_TabHandle;
            bool                m_bSaved;
            bool                m_bInitialized;

            std::vector<TToolBar*>  m_ToolBars;
            std::vector<TMenuItem*> m_ToolBarMenus;


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

        public:		// User declarations
                    __fastcall  TfrmGameEditor(TComponent* Owner);
                    __fastcall ~TfrmGameEditor();

            HRESULT __fastcall  Initialise(TZX_HPLUGIN PluginHandle);
            HRESULT __fastcall  ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
            HRESULT __fastcall  Release(void);

            //bool    __fastcall  AddTab(const String& sCaption, Graphics::TBitmap* pBitmap, TTabSheet*& pTabSheet);
            void    __fastcall  EditCopy(void);
            void    __fastcall  EditCut(void);
            void    __fastcall  EditPaste(void);
        };
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::GameEditor::TfrmGameEditor *frmGameEditor;
//---------------------------------------------------------------------------
#endif
