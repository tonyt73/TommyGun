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
#ifndef fSpriteTypeH
#define fSpriteTypeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <Graphics.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "KSlider.h"
#include "KSpinEdit.h"
#include "..\ZXImageInterface.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace ImageTypes
    {
        //---------------------------------------------------------------------------
        class TfrmSpriteType : public TForm
        {
        __published:	// IDE-managed Components
            TImageList *imgIcons;
            TPanel *panSprites;
            TTimer *tmrAnimator;
            TImage *imgIcon;
            TLabel *lblSpriteWidth;
            TLabel *lblSpriteName;
            TLabel *lblSpriteHeight;
            TLabel *lblSpriteFormat;
            TComboBox *cmbSpriteFormat;
            KSpinEdit *edtSpriteWidth;
            TEdit *edtSpriteName;
            KSpinEdit *edtSpriteHeight;
            TBitBtn *cmdSpriteRename;
            TBitBtn *cmdSpriteRemove;
            TBitBtn *cmdSpriteClone;
            TBitBtn *cmdSpriteAdd;
            TListBox *lstSpriteList;
            TCheckBox *chkSpriteMasked;
            TGroupBox *grpFrames;
            TPanel *panFramesContainer;
            TToolBar *tbnSpriteFrames;
            TToolButton *tbnFramesFirst;
            TToolButton *tbnFramesPrevious;
            TToolButton *tbnFramePlay;
            TToolButton *tbnFrameStop;
            TToolButton *tbnFramesNext;
            TToolButton *tbnFramesLast;
            TToolButton *tbnSeparator07;
            TToolButton *tbnFramesRepeat;
            TToolButton *tbnSeparator08;
            TToolButton *tbnFramesInsert;
            TToolButton *tbnFramesRemove;
            TToolButton *tbnFramesClone;
            TPanel *panAnimationContainer;
            TPaintBox *pbxSpritesFramesAnimation;
            TPanel *panFramesInfo;
            TLabel *lblSpriteFrame;
            TLabel *lblFramesOf;
            KSpinEdit *edtFramesIndex;
            TCheckBox *chkSpriteShowInEditor;
            TPanel *panFrames;
            TScrollBox *sbxFrames;
            TPaintBox *pbxSpritePreview;
            TPanel *panFramesSpeed;
            TLabel *lblFramesSpeedLabel;
            KSlider *slrFramesSpeed;
            TLabel *lblFramesSpeed;
            TScrollBox *sbxContainer;
    TLabel *lblType;
    TComboBox *cmbType;
    TButton *btnType;
            void __fastcall edtSpriteNameChange(TObject *Sender);
            void __fastcall lstSpriteListClick(TObject *Sender);
            void __fastcall cmdSpriteAddClick(TObject *Sender);
            void __fastcall cmdSpriteRemoveClick(TObject *Sender);
            void __fastcall cmdSpriteCloneClick(TObject *Sender);
            void __fastcall cmdSpriteRenameClick(TObject *Sender);
            void __fastcall tbnFramesInsertClick(TObject *Sender);
            void __fastcall tbnFramesRemoveClick(TObject *Sender);
            void __fastcall tbnFramesCloneClick(TObject *Sender);
            void __fastcall tbnFramesFirstClick(TObject *Sender);
            void __fastcall tbnFramePlayClick(TObject *Sender);
            void __fastcall tbnFrameStopClick(TObject *Sender);
            void __fastcall tbnFramesNextClick(TObject *Sender);
            void __fastcall tbnFramesLastClick(TObject *Sender);
            void __fastcall pbxSpritePreviewPaint(TObject *Sender);
            void __fastcall pbxSpritePreviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall tbnFramesPreviousClick(TObject *Sender);
            void __fastcall tmrAnimatorTimer(TObject *Sender);
            void __fastcall slrFramesSpeedChange(TObject *Sender);
            void __fastcall cmbSpriteFormatChange(TObject *Sender);
    void __fastcall cmbTypeChange(TObject *Sender);
        private:	// User declarations
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;
                    std::vector<String> m_vPaletteSignatures;
                    ZXImageManager*     m_pImageManager;

                    //bool                m_bAnimating;       // flag: animating the sprite
                    bool                m_bSkipReorder;     // flag: skip the reordering of frame on the frame index change
                    int                 m_iLastFrameIndex;  // index of the last frame selected before the current frame change
                    float               m_fScalarX;
                    float               m_fScalarY;
                    int                 m_iPixelsHigh;

            void        __fastcall  OnTabHide(TObject *Sender);

        public:		// User declarations
                    TTabSheet*          m_pTabSheet;
                    
                        __fastcall  TfrmSpriteType(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);

            void        __fastcall  SetComboText(TComboBox* pComboBox, String sText);
            void        __fastcall  UpdatePreview(void);
            void        __fastcall  UpdateButtons(void);
            void        __fastcall  SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures);
            void        __fastcall  RefreshList(void);
            void        __fastcall  SelectFrame(int iFrame);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageTypes::TfrmSpriteType *frmSpriteType;
//---------------------------------------------------------------------------
#endif
