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
#ifndef fUDGTypeH
#define fUDGTypeH
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
#include "cspin.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace ImageTypes
    {
        //---------------------------------------------------------------------------
        class TfrmUDGType : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panUDGs;
            TImage *imgIcon;
            TLabel *lblUserDefinedGraphicsName;
            TLabel *lblPaletteWarning;
            TEdit *edtUDGName;
            TBitBtn *cmdUserDefinedGraphicsSetAdd;
            TBitBtn *cmdUserDefinedGraphicsSetRemove;
            TBitBtn *cmdUserDefinedGraphicsSetRename;
            TBitBtn *cmdUserDefinedGraphicsSetClone;
            TPanel *panUserDefinedGraphics;
            TScrollBox *sbxUserDefinedGraphics;
            TPaintBox *pbxUserDefinedGraphics;
            TListBox *lstUDGList;
            TPanel *panUserDefinedGraphicsButtons;
            TSpeedButton *spdUserDefinedGraphicsA;
            TSpeedButton *spdUserDefinedGraphicsU;
            TSpeedButton *spdUserDefinedGraphicsT;
            TSpeedButton *spdUserDefinedGraphicsS;
            TSpeedButton *spdUserDefinedGraphicsR;
            TSpeedButton *spdUserDefinedGraphicsQ;
            TSpeedButton *spdUserDefinedGraphicsP;
            TSpeedButton *spdUserDefinedGraphicsO;
            TSpeedButton *spdUserDefinedGraphicsN;
            TSpeedButton *spdUserDefinedGraphicsM;
            TSpeedButton *spdUserDefinedGraphicsL;
            TSpeedButton *spdUserDefinedGraphicsK;
            TSpeedButton *spdUserDefinedGraphicsJ;
            TSpeedButton *spdUserDefinedGraphicsI;
            TSpeedButton *spdUserDefinedGraphicsH;
            TSpeedButton *spdUserDefinedGraphicsG;
            TSpeedButton *spdUserDefinedGraphicsF;
            TSpeedButton *spdUserDefinedGraphicsE;
            TSpeedButton *spdUserDefinedGraphicsD;
            TSpeedButton *spdUserDefinedGraphicsC;
            TSpeedButton *spdUserDefinedGraphicsB;
    TLabel *Label1;
    TCSpinEdit *spnScale;
            void __fastcall cmdUserDefinedGraphicsSetAddClick(TObject *Sender);
            void __fastcall edtUDGNameChange(TObject *Sender);
            void __fastcall cmdUserDefinedGraphicsSetRemoveClick(TObject *Sender);
            void __fastcall cmdUserDefinedGraphicsSetCloneClick(TObject *Sender);
            void __fastcall cmdUserDefinedGraphicsSetRenameClick(TObject *Sender);
            void __fastcall spdUserDefinedGraphicsAClick(TObject *Sender);
            void __fastcall pbxUserDefinedGraphicsPaint(TObject *Sender);
            void __fastcall lstUDGListClick(TObject *Sender);
            void __fastcall pbxUserDefinedGraphicsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall spnScaleChange(TObject *Sender);
        private:	// User declarations
            ZXImageInterface        m_ImageEditor;
            TZX_HPLUGIN             m_PluginHandle;
            ZXImageManager*         m_pImageManager;
            std::vector<String>     m_vPaletteSignatures;
            int                     m_iActiveCharacter;

            void        __fastcall  UpdateButtons(void);

        public:		// User declarations
                        __fastcall  TfrmUDGType(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            void        __fastcall  SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures);
            void        __fastcall  RefreshList(void);
            void        __fastcall  UpdatePreview(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageTypes::TfrmUDGType *frmUDGType;
//---------------------------------------------------------------------------
#endif
