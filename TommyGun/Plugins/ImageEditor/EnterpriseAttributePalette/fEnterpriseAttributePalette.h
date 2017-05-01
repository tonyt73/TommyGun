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
#ifndef fEnterpriseAttributePaletteH
#define fEnterpriseAttributePaletteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "..\ZXImageInterface.h"
#include "EnterpriseAttributePalette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace Enterprise64AttributePalette
    {
        //---------------------------------------------------------------------------
        class TfrmEnterpriseAttributePalette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panPalette;
            TLabel *lblPalette;
            TLabel *lblColours0to7;
            TLabel *lblColours8to15;
            TSpeedButton *spdInkTransparent;
            TSpeedButton *spdPaperTransparent;
            TLabel *lblInk;
            TImage *imgPaletteTransparent;
            TLabel *lblPaletteTransparent;
            TLabel *lblPaper;
            TImage *imgLogo;
            TPanel *panColour0;
            TPanel *panColour8;
            TPanel *panColour1;
            TPanel *panColour9;
            TPanel *panColour2;
            TPanel *panColourA;
            TPanel *panColour3;
            TPanel *panColourB;
            TPanel *panColour4;
            TPanel *panColourC;
            TPanel *panColour5;
            TPanel *panColourD;
            TPanel *panColour6;
            TPanel *panColourE;
            TPanel *panColour7;
            TPanel *panColourF;
            TPanel *panInk;
            TPanel *panPaper;
            TLabel *lblResetPalette;
            void __fastcall panColour0MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall lblResetPaletteClick(TObject *Sender);
            void __fastcall lblInkClick(TObject *Sender);
            void __fastcall lblPaperClick(TObject *Sender);
            void __fastcall spdInkTransparentClick(TObject *Sender);
        private:	// User declarations
                    EnterpriseAttributePalette  m_Palette;
                    ZXImageInterface            m_ImageEditor;
                    TZX_HPLUGIN                 m_PluginHandle;

        public:		// User declarations
                        __fastcall  TfrmEnterpriseAttributePalette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
            void        __fastcall  OnUpdatePaletteGUI(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::Enterprise64AttributePalette::TfrmEnterpriseAttributePalette *frmEnterpriseAttributePalette;
//---------------------------------------------------------------------------
#endif
