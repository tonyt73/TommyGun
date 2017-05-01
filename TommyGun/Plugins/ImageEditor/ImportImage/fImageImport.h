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
#ifndef fImageImportH
#define fImageImportH
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
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
#include "..\ZXImageInterface.h"
//---------------------------------------------------------------------------
class TGenericGraphic : public TPicture
{
public:
            __fastcall  TGenericGraphic() : TPicture() {};

    void    __fastcall  LoadFromClipboardFormat(Word AFormat, int AData, HPALETTE APalette) {};
    void    __fastcall  LoadFromFile(const AnsiString FileName) {};
    void    __fastcall  LoadFromStream(Classes::TStream* Stream) {};
    void    __fastcall  SaveToClipboardFormat(Word &AFormat, int &AData, HPALETTE &APalette) {};
    void    __fastcall  SaveToFile(const AnsiString Filename) {};
    void    __fastcall  SaveToStream(Classes::TStream* Stream) {};
};

//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace ImageImport
    {
        //---------------------------------------------------------------------------
        class TfrmImageImport : public TForm
        {
        __published:	// IDE-managed Components
            TPopupMenu *mnuImportImage;
            TMenuItem *mnuImportImages;
            TOpenPictureDialog *dlgImport;
            TMenuItem *mnuImportImageSheet;
            TOpenPictureDialog *dlgImportSheet;
            void __fastcall mnuImportImagesClick(TObject *Sender);
            void __fastcall mnuImportImageSheetClick(TObject *Sender);

        private:	// User declarations
                ZXImageInterface    m_ImageEditor;
                TZX_HPLUGIN         m_PluginHandle;
                std::vector<String> m_vPaletteSignatures;
                TStrings*           m_pPalettes;
                ZXImageManager*     m_pImageManager;

            void        __fastcall  UpdateButtons(void);
            void        __fastcall  SetComboText(TComboBox* pComboBox, String sText);

        public:		// User declarations
                        __fastcall  TfrmImageImport(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            void        __fastcall  SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageImport::TfrmImageImport *frmImageImport;
//---------------------------------------------------------------------------
#endif
