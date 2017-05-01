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
#ifndef fImageToolsH
#define fImageToolsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
#include "..\ZXImageInterface.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace ImageTools
    {
        //---------------------------------------------------------------------------
        class TfrmImageTools : public TForm
        {
        __published:	// IDE-managed Components
            TImageList *imgImageTools;
            TTimer *tmrRepeat;
    TToolBar *tbrImageTools;
    TToolButton *tbnOpPixelCharacter;
    TToolButton *tbnOpWrap;
    TToolButton *tbnSeparator01;
    TToolButton *tbnOpShiftLeft;
    TToolButton *tbnOpShiftRight;
    TToolButton *tbnOpShiftUp;
    TToolButton *tbnOpShiftDown;
    TToolButton *tbnSeparator02;
    TToolButton *tbnOpRotateRight;
    TToolButton *tbnOpRotateLeft;
    TToolButton *tbnArbitaryRotate;
    TToolButton *tbnSeparator03;
    TToolButton *tbnOpMirror;
    TToolButton *tbnOpFlip;
            void __fastcall tbnOpPixelCharacterClick(TObject *Sender);
            void __fastcall tbnOpWrapClick(TObject *Sender);
            void __fastcall tmrRepeatTimer(TObject *Sender);
            void __fastcall tbnOpShiftDownMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall tbnOpShiftLeftMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall tbnOpShiftRightMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall tbnOpShiftUpMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall tbnOpShiftLeftClick(TObject *Sender);
            void __fastcall tbnOpShiftRightClick(TObject *Sender);
            void __fastcall tbnOpShiftUpClick(TObject *Sender);
            void __fastcall tbnOpShiftDownClick(TObject *Sender);
            void __fastcall tbnOpRotateRightClick(TObject *Sender);
            void __fastcall tbnOpRotateLeftClick(TObject *Sender);
            void __fastcall tbnOpMirrorClick(TObject *Sender);
            void __fastcall tbnOpFlipClick(TObject *Sender);
            void __fastcall tbnOpShiftLeftMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall tbnArbitaryRotateClick(TObject *Sender);
        private:	// User declarations
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;
                    ZXImageManager*     m_pImageManager;
                    ZXImage*            m_pImage;
                    Graphics::TBitmap*  m_pBitmap;
                    Graphics::TBitmap*  m_pSelectionBitmap;
                    int                 m_iRepeatTool;

            void        __fastcall  GetImage(void);
            void        __fastcall  ShiftImage(int dX, int dY);
            void        __fastcall  MirrorOrFlip(bool bMirror);
            void        __fastcall  Rotate(bool bRotateRight);
            void        __fastcall  PushUndo(ZXImage* pImage, ZXUndoType UndoType, String sOperaton);

        public:		// User declarations
                        __fastcall  TfrmImageTools(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageTools::TfrmImageTools *frmImageTools;
//---------------------------------------------------------------------------
#endif
