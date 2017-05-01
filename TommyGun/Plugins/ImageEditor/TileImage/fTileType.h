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
#ifndef fTileTypeH
#define fTileTypeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "..\ZXImageInterface.h"
#include "KSpinEdit.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace ImageTypes
    {
        //---------------------------------------------------------------------------
        class TfrmTileType : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panTiles;
            TImage *imgIcon;
            TLabel *lblTileName;
            TLabel *lblTileFormat;
            TLabel *lblTileWidth;
            TLabel *lblTileHeight;
            TComboBox *cmbTileFormat;
            TBitBtn *cmdTileAdd;
            TBitBtn *cmdTileRemove;
            TPanel *panTilePreview;
            TPaintBox *pbxTilePreview;
            TBitBtn *cmdTileRename;
            TBitBtn *cmdTileClone;
            KSpinEdit *edtTileWidth;
            KSpinEdit *edtTileHeight;
            TListBox *lstTileList;
            TEdit *edtTileName;
            TCheckBox *chkTileMasked;
            TComboBox *cmbType;
            TLabel *lblType;
            TButton *btnType;
            void __fastcall cmdTileAddClick(TObject *Sender);
            void __fastcall lstTileListClick(TObject *Sender);
            void __fastcall pbxTilePreviewPaint(TObject *Sender);
            void __fastcall edtTileNameChange(TObject *Sender);
            void __fastcall cmdTileRemoveClick(TObject *Sender);
            void __fastcall cmdTileCloneClick(TObject *Sender);
            void __fastcall cmdTileRenameClick(TObject *Sender);
            void __fastcall cmbTileFormatChange(TObject *Sender);
            void __fastcall cmbTypeChange(TObject *Sender);
        private:	// User declarations
                    ZXImageInterface    m_ImageEditor;
                    TZX_HPLUGIN         m_PluginHandle;
                    std::vector<String> m_vPaletteSignatures;
                    ZXImageManager*     m_pImageManager;
                    int                 m_iPixelsHigh;

            void        __fastcall  UpdateButtons(void);

        public:		// User declarations
                    bool            m_bSizeEnabled;
                        __fastcall  TfrmTileType(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            void        __fastcall  SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures);
            void        __fastcall  SetComboText(TComboBox* pComboBox, String sText);
            void        __fastcall  UpdatePreview(void);
            void        __fastcall  RefreshList(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageTypes::TfrmTileType *frmTileType;
//---------------------------------------------------------------------------
#endif
