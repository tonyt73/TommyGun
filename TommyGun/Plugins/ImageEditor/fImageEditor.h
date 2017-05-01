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
#ifndef fImageEditorH
#define fImageEditorH
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
#include "KSlider.h"
#include "KSpinEdit.h"
//-- APP --------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
#include "ZXImage.h"
#include <Dialogs.hpp>
#include "KRegistry.h"
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace ImageEditor
    {
        //---------------------------------------------------------------------------
        class TfrmImageEditor : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panTools;
            TPageControl *pgcTools;
            TTabSheet *tabOptions;
            TScrollBox *scpOptions;
            TPanel *panContainer;
            TScrollBox *sbxEditor;
            TImage *imgCanvas;
            TImageList *imgTabImages;
            TImageList *imgIcons;
            TControlBar *cbrImageEditor;
            TToolBar *tbrImageGridTools;
            TToolButton *tbnGridCharacter;
            TToolButton *tbnGridPixel;
            TToolBar *tbrImagePaintTools;
            TToolButton *tbnToolSelect;
            TPanel *panMapTiles;
            TPanel *panTilesButtons;
            TPanel *panPaletteContainer;
            TBevel *bvlBevel00;
            TActionList *actMain;
            TAction *actZoomIn;
            TAction *actZoomOut;
            TImageList *imgPaintToolBar;
            TToolBar *tbrPaletteAttributes;
            TToolButton *tbnPaletteShowAttributes;
            TToolButton *tbnPaletteHideAttributes;
            TImageList *imgSpectrumIcons;
            TBitBtn *cmdZoomOut;
            TBitBtn *cmdZoomIn;
            TToolBar *tbrMaskTools;
            TToolButton *tbnMaskModeOff;
            TToolButton *tbnMaskModeOn;
            TAction *actMaskModeOff;
            TAction *actMaskModeOn;
            TToolButton *tbnSeparator01;
            TToolButton *tbnMaskGenerate;
            TAction *actMaskGenerate;
            TColorDialog *dlgColor;
            TImage *imgLargeIcon;
            TImage *imgSmallIcon;
            KRegistry *regScorpio;
            TAction *actToggleCharGrid;
            TAction *actTogglePixelGrid;
            TPanel *panImageKeysPanel;
            TPanel *panImageKeysBar;
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
            TPopupMenu *popImage;
            TMenuItem *popToggleGridChar;
            TMenuItem *popToggleGridPixel;
            TMenuItem *popZoomIn;
            TMenuItem *popZoomOut;
            TApplicationEvents *appEvents;
            TLabel *Label9;
            TLabel *Label10;
            TToolBar *tbnImageTools;
            TToolButton *tbnImageResize;
            TToolButton *tbnImageChangePalette;
            TToolButton *tbnMaskInvert;
            TToolButton *ToolButton1;
            TAction *actMaskInvert;
            TToolBar *tbrAnimationTools;
            TToolButton *tbnAnimationUnderlay;
            TAction *actToggleAnimationUnderlay;
			TToolButton *tbnShowHotSpot;
			TAction *actToggleHotSpot;
            TPanel *panOptions;
            TGroupBox *grpEditorGridLines;
            TLabel *lblChrLineColor;
            TLabel *lblPixelLineColor;
            TCheckBox *chkGridPixel;
            TCheckBox *chkGridCharacter;
            TPanel *panChrLineColor;
            TPanel *panPixelLineColor;
            TGroupBox *grpEditorMagnification;
            TLabel *lblDisplayScreenMagnification;
            KSlider *slrDisplayMagnification;
            TLabel *lblAutoMagnification;
            KSpinEdit *edtDisplayScreenMagnification;
            TCheckBox *chkAutoMagnification;
            TGroupBox *grpMasking;
            TLabel *lblMaskTransparency;
            KSlider *slrMaskTransparency;
            TLabel *lblMaskColor;
            KSpinEdit *edtMaskTransparency;
            TPanel *panMaskColor;
            TGroupBox *grpImageWindow;
            TLabel *lblEditorBackgroundColor;
            TCheckBox *chkCenterImage;
            TPanel *panBackgroundColor;
            TButton *cmdRestoreDefaults;
            TGroupBox *grpModeScaleAdjust;
            TLabel *lblCustomX25;
            KSlider *slrCustomXScale;
            TLabel *lblCustomX50;
            TLabel *lblCustomX100;
            TLabel *lblCustomX200;
            TLabel *lblCustomXAxis;
            TLabel *lblCustomY25;
            KSlider *slrCustomYScale;
            TLabel *lblCustomY50;
            TLabel *lblCustomY100;
            TLabel *lblCustomY200;
            TLabel *lblCustomYAxis;
            TLabel *lblModeScaleDescription;
            TRadioButton *radModeScaleDefault;
            TRadioButton *radModeScaleCustom;
            TRadioButton *radModeScaleRemove;
            void __fastcall FormCreate(TObject *Sender);
            void __fastcall slrDisplayMagnificationChange(TObject *Sender);
            void __fastcall actZoomInExecute(TObject *Sender);
            void __fastcall actZoomOutExecute(TObject *Sender);
            void __fastcall imgCanvasMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall imgCanvasMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
            void __fastcall imgCanvasMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall sbxEditorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
            void __fastcall tbnToolSelectClick(TObject *Sender);
            void __fastcall cbrImageEditorDblClick(TObject *Sender);
            void __fastcall tbnPaletteShowAttributesClick(TObject *Sender);
            void __fastcall edtDisplayScreenMagnificationChange(TObject *Sender);
            void __fastcall actMaskGenerateExecute(TObject *Sender);
            void __fastcall actMaskModeOffExecute(TObject *Sender);
            void __fastcall actMaskModeOnExecute(TObject *Sender);
            void __fastcall edtMaskTransparencyChange(TObject *Sender);
            void __fastcall chkAutoMagnificationClick(TObject *Sender);
            void __fastcall sbxEditorResize(TObject *Sender);
            void __fastcall panMaskColorClick(TObject *Sender);
            void __fastcall slrMaskTransparencyChange(TObject *Sender);
            void __fastcall panBackgroundColorClick(TObject *Sender);
            void __fastcall panChrLineColorClick(TObject *Sender);
            void __fastcall panPixelLineColorClick(TObject *Sender);
            void __fastcall cmdRestoreDefaultsClick(TObject *Sender);
            void __fastcall actTogglePixelGridExecute(TObject *Sender);
            void __fastcall actToggleCharGridExecute(TObject *Sender);
            void __fastcall chkCenterImageClick(TObject *Sender);
            void __fastcall radModeScaleDefaultClick(TObject *Sender);
            void __fastcall appEventsMessage(tagMSG &Msg, bool &Handled);
            void __fastcall tbnImageResizeClick(TObject *Sender);
            void __fastcall actMaskInvertExecute(TObject *Sender);
            void __fastcall actToggleAnimationUnderlayExecute(TObject *Sender);
            void __fastcall tbnImageChangePaletteClick(TObject *Sender);
			void __fastcall actToggleHotSpotExecute(TObject *Sender);
            void __fastcall edtDisplayScreenMagnificationChanged(TObject *Sender, int value);
            void __fastcall edtMaskTransparencyChanged(TObject *Sender, int value);
            void __fastcall pgcToolsDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active);
        private:	// User declarations

            typedef struct
            {
                TRect           Rect;
                TRect           RectLast;
                bool            Active;
                bool            Dragging;
                int             X;
                int             Y;
            } TSelectionInfo;

            TZX_HPLUGIN         m_PluginHandle;
            HWND                m_TabHandle;
            bool                m_bSaved;
            bool                m_bInitialized;
            int                 m_iMagnification;
            TSelectionInfo      m_Selection;
            TRect               m_rPaste;
            TPoint              m_PasteOffset;
            bool                m_bSnapToChar;
            bool                m_bPasting;
            bool                m_bToolbarVisible;
            float               m_fModeScaleX;
            float               m_fModeScaleY;
            Graphics::TBitmap*  m_pCanvas;
            Graphics::TBitmap*  m_pPasteObject;
            Graphics::TBitmap*  m_pUnderlay1;
            Graphics::TBitmap*  m_pUnderlay2;
            //ZXImageManager*     m_pImageManager;

            TMenuItem*          m_PaintTools;
            TMenuItem*          m_GridTools;

            std::vector<TToolBar*>  m_ToolBars;
            std::vector<TMenuItem*> m_ToolBarMenus;

            ZXImage*            m_pImage;
            String              m_sOwner;

            void    __fastcall  OnMenuClick(TObject* Sender);
            void    __fastcall  TrapTabEvents(TWinControl* Control);
            void    __fastcall  OnTabHide(TObject *Sender);
            void    __fastcall  OnTabShow(TObject *Sender);
            String  __fastcall  ZeroPadInt(int iValue, int iSize);
            void    __fastcall  PasteObject(void);
            void    __fastcall  DrawPasteObject(void);
            void    __fastcall  DrawPreviousFrame(void);
            void    __fastcall  DrawGridLines(TRect& UpdateRect);
            void    __fastcall  DrawSelection(void);
            void    __fastcall  DrawHotSpot(void);
            void    __fastcall  UpdateImage(void);
            void    __fastcall  UpdateMagnification(void);
            void    __fastcall  SaveSettings(void);
            void    __fastcall  LoadSettings(void);
            void    __fastcall  PushUndo(ZXImage* pImage, ZXUndoType UndoType, String sTool);
            void    __fastcall  SaveToClipboard(Graphics::TBitmap* Bitmap, TRect Rect);
            void    __fastcall  UpdateModeScale(void);
            void    __fastcall  MenusAdd(void);
            void    __fastcall  MenusRemove(void);
            void    __fastcall  ResizeImage(int iLeft, int iTop, int iWidth, int iHeight);
            void    __fastcall  UpdateCanvasMagnification();

        public:		// User declarations
                    __fastcall  TfrmImageEditor(TComponent* Owner);
                    __fastcall ~TfrmImageEditor();

            HRESULT __fastcall  Initialise(TZX_HPLUGIN PluginHandle);
            HRESULT __fastcall  ProcessEvent(TZX_EVENT Event, LPDATA lpData, DWORD Param, DWORD Arg);
            HRESULT __fastcall  Release(void);

            //void    __fastcall  SetImageManager(ZXImageManager* pImageManager);
            void    __fastcall  SetImage(ZXImage* Image, const String& sOwner);
            bool    __fastcall  AddToolBar(TToolBar* ToolBar);
            void    __fastcall  UpdateImage(ZXImage* Image, bool bIsATypePlugin);
            void    __fastcall  CenterImage(void);
            void    __fastcall  RefreshView(void);
            bool    __fastcall  MergePaintToolBar(TToolBar* ToolBar);
            bool    __fastcall  AddTab(const String& sCaption, Graphics::TBitmap* pBitmap, TTabSheet*& pTabSheet);
        ZXImage*    __fastcall  GetCurrentImage(void) { return m_pImage; }
            void    __fastcall  EditCopy(void);
            void    __fastcall  EditCut(void);
            void    __fastcall  EditPaste(void);
        };
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageEditor::TfrmImageEditor *frmImageEditor;
//---------------------------------------------------------------------------
#endif
