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
#ifndef fVic20HiresDHPaletteH
#define fVic20HiresDHPaletteH
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
#include "ZXVic20HiresDHPalette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace Vic20Palette
    {
        //---------------------------------------------------------------------------
        class TfrmVic20HiresDHPalette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panPalette;
            TLabel *lblPalette;
            TLabel *lblCharacter;
            TImage *imgLogo;
            TLabel *lblBackground;
            TSpeedButton *spdInk00;
            TSpeedButton *spdInk01;
            TSpeedButton *spdInk02;
            TSpeedButton *spdInk03;
            TSpeedButton *spdInk04;
            TSpeedButton *spdInk05;
            TSpeedButton *spdInk06;
            TSpeedButton *spdInk07;
            TSpeedButton *spdPaper00;
            TSpeedButton *spdPaper01;
            TSpeedButton *spdPaper02;
            TSpeedButton *spdPaper03;
            TSpeedButton *spdPaper04;
            TSpeedButton *spdPaper05;
            TSpeedButton *spdPaper06;
            TSpeedButton *spdPaper07;
            TSpeedButton *spdPaper08;
            TSpeedButton *spdPaper09;
            TSpeedButton *spdPaper10;
            TSpeedButton *spdPaper11;
            TSpeedButton *spdPaper12;
            TSpeedButton *spdPaper13;
            TSpeedButton *spdPaper14;
            TSpeedButton *spdPaper15;
    TSpeedButton *spdInkTransparent;
            void __fastcall spdInk00Click(TObject *Sender);
            void __fastcall spdPaper00Click(TObject *Sender);
        private:	// User declarations
                    ZXVic20HiresDHPalette m_Palette;
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;
                    TPanel*             m_LastChrPanel;
                    TPanel*             m_LastBkgPanel;


        public:		// User declarations
                        __fastcall  TfrmVic20HiresDHPalette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);

            void        __fastcall  OnUpdatePaletteGUI(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::Vic20Palette::TfrmVic20HiresDHPalette *frmVic20HiresDHPalette;
//---------------------------------------------------------------------------
#endif
