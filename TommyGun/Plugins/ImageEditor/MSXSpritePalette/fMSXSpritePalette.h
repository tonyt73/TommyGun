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
#ifndef fMSXSpritePaletteH
#define fMSXSpritePaletteH
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
#include "ZXMSXSpritePalette.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace MSXPalette
    {
        //---------------------------------------------------------------------------
        class TfrmMSXSpritePalette : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panPalette;
            TLabel *lblPalette;
            TLabel *lblPen;
            TPanel *panPen;
            TImage *imgLogo;
            TPanel *panColor01;
            TPanel *panColor02;
            TPanel *panColor04;
            TPanel *panColor03;
            TPanel *panColor06;
            TPanel *panColor05;
            TPanel *panColor08;
            TPanel *panColor07;
            TPanel *panColor10;
            TPanel *panColor09;
            TPanel *panColor12;
            TPanel *panColor11;
            TPanel *panColor14;
            TPanel *panColor13;
            TPanel *panColor15;
    void __fastcall panColor01Click(TObject *Sender);
        private:	// User declarations
                    ZXMSXSpritePalette  m_Palette;
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;
                    TPanel*             m_LastPanel;


        public:		// User declarations
                        __fastcall  TfrmMSXSpritePalette(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            HRESULT     __fastcall  GetPalette(ZXPalette*& Palette);

            void        __fastcall  OnUpdatePaletteGUI(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::MSXPalette::TfrmMSXSpritePalette *frmMSXSpritePalette;
//---------------------------------------------------------------------------
#endif
