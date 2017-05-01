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
#ifndef fScreenTypeH
#define fScreenTypeH
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
        class TfrmScreenType : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panScreens;
            TImage *imgIcon;
            TLabel *lblScreenName;
            TLabel *lblScreenFormat;
            TLabel *lblScreensHeight;
            TLabel *lblScreensWidth;
            TEdit *edtScreenName;
            TComboBox *cmbScreenFormat;
            TBitBtn *cmdScreenAdd;
            TBitBtn *cmdScreenRemove;
            TPanel *panScreenPreview;
            TPaintBox *pbxScreenPreview;
            TBitBtn *cmdScreenRename;
            TBitBtn *cmdScreenClone;
            TListBox *lstScreenList;
            KSpinEdit *edtScreensWidth;
            KSpinEdit *edtScreensHeight;
            void __fastcall cmdScreenAddClick(TObject *Sender);
            void __fastcall cmdScreenRemoveClick(TObject *Sender);
            void __fastcall cmdScreenCloneClick(TObject *Sender);
            void __fastcall cmdScreenRenameClick(TObject *Sender);
            void __fastcall edtScreenNameChange(TObject *Sender);
            void __fastcall lstScreenListClick(TObject *Sender);
            void __fastcall pbxScreenPreviewPaint(TObject *Sender);
    		void __fastcall cmbScreenFormatChange(TObject *Sender);
        private:	// User declarations
                ZXImageInterface    m_ImageEditor;
                TZX_HPLUGIN         m_PluginHandle;
                std::vector<String> m_vPaletteSignatures;
                ZXImageManager*     m_pImageManager;

            void        __fastcall  UpdateButtons(void);
            void        __fastcall  SetComboText(TComboBox* pComboBox, String sText);

        public:		// User declarations
                        __fastcall  TfrmScreenType(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            void        __fastcall  SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures);
            void        __fastcall  UpdatePreview(void);
            void        __fastcall  RefreshList(void);
            void        __fastcall  AddScorePanel(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageTypes::TfrmScreenType *frmScreenType;
//---------------------------------------------------------------------------
#endif
