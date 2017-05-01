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
#ifndef fEnterprise256PaletteH
#define fEnterprise256PaletteH
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
#include "Enterprise256Palette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace EnterprisePalette
    {
        //---------------------------------------------------------------------------
        class TfrmEnterprise256Palette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panPalette;
            TLabel *lblPalette;
            TLabel *lblPen;
            TLabel *lblBrush;
            TPanel *panPen;
            TPanel *panBrush;
            TLabel *lblResetPalette;
            TImage *imgLogo;
            void __fastcall lblPenClick(TObject *Sender);
            void __fastcall lblResetPaletteClick(TObject *Sender);
            void __fastcall lblBrushClick(TObject *Sender);
        private:	// User declarations
                    Enterprise256Palette m_Palette;
                    ZXImageInterface     m_ImageEditor;
                    TZX_HPLUGIN          m_PluginHandle;

        public:		// User declarations
                        __fastcall  TfrmEnterprise256Palette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);
            void        __fastcall  OnUpdatePaletteGUI(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::EnterprisePalette::TfrmEnterprise256Palette *frmEnterprise256Palette;
//---------------------------------------------------------------------------
#endif
