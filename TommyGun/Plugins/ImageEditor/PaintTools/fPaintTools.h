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
#ifndef fPaintToolsH
#define fPaintToolsH
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
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace PaintTools
    {
        //---------------------------------------------------------------------------
        class TfrmPaintTools : public TForm
        {
        __published:	// IDE-managed Components
            TImageList *imgPaintTools;
            TToolBar *tbrPaintTools;
            TToolButton *tbnToolSwapAttributes;
            TToolButton *tbnToolInvert;
            TToolButton *tbnToolCircleFill;
            TToolButton *tbnToolCircle;
            TToolButton *tbnToolRectangleFill;
            TToolButton *tbnToolRectangle;
            TToolButton *tbnToolText;
            TToolButton *tbnToolFill;
            TToolButton *tbnToolSpray;
            TToolButton *tbnToolAttribute;
            TToolButton *tbnToolLine;
            TToolButton *tbnToolFreeHand;
    TToolButton *tbnToolHotSpot;
        private:	// User declarations
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;
        public:		// User declarations
                        __fastcall  TfrmPaintTools(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::PaintTools::TfrmPaintTools *frmPaintTools;
//---------------------------------------------------------------------------
#endif
