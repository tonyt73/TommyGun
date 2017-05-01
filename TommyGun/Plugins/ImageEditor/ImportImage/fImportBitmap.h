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
#ifndef fImportBitmapH
#define fImportBitmapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Menus.hpp>
#include "KSpinEdit.h"
#include "pngimage.hpp"
//---------------------------------------------------------------------------
class TfrmImportBitmap : public TForm
{
__published:	// IDE-managed Components
    TPanel *panMessageHeader;
    TLabel *lblMessageTitle;
    TLabel *lblShortMessage;
    TBevel *bvlMessageTop;
    TScrollBox *sbxBitmap;
    TImage *imgBitmap;
    TPanel *panButtons;
    TButton *cmdCancel;
    TButton *cmdImport;
    TLabel *lblBitmapPreview;
    TLabel *lblBitmap_Size;
    TLabel *lblBitmap_Format;
    TLabel *lblBitmapSize;
    TLabel *lblBitmapFormat;
    TRadioButton *radImportAsScreen;
    TLabel *lblImportBitmapAs;
    TLabel *lblImageFormat;
    TComboBox *cmbImageFormat;
    TRadioButton *radImportAsSprite;
    TPanel *panSprite;
    TLabel *lblSpriteMultiFrameWidth;
    KSpinEdit *edtSpriteMultiFrameWidth;
    TRadioButton *radSpriteMulti;
    TRadioButton *radSpriteSingle;
    TLabel *lblSpriteMultiMessage;
    TLabel *lblFrames;
    TRadioButton *radImportAsTile;
    TLabel *Label1;
    TLabel *lblName;
    TEdit *edtName;
    KSpinEdit *edtBitmap;
    TEdit *edtNewName;
    TLabel *lblNewName;
    TCheckBox *chkImageIsMasked;
    TPanel *panImageIsMasked;
    TRadioButton *chkMaskEmpty;
    TRadioButton *chkMaskBackground;
    TPanel *panMaskColour;
    TColorDialog *dlgColour;
    TLabel *lblMaskColour;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TImage *imgInformation;
    TImage *Image1;
    void __fastcall radImportAsScreenClick(TObject *Sender);
    void __fastcall radImportAsSpriteClick(TObject *Sender);
    void __fastcall edtSpriteMultiFrameWidthChange(TObject *Sender);
    void __fastcall radSpriteMultiClick(TObject *Sender);
    void __fastcall radSpriteSingleClick(TObject *Sender);
    void __fastcall radImportAsTileClick(TObject *Sender);
    void __fastcall edtNameChange(TObject *Sender);
    void __fastcall edtBitmapChange(TObject *Sender);
    void __fastcall panMaskColourClick(TObject *Sender);
    void __fastcall chkMaskEmptyClick(TObject *Sender);
private:    // User declarations
    bool                m_bSpriteToWide;
    TStrings*           m_sFiles;
    
public:     // User declarations
            __fastcall TfrmImportBitmap(TComponent* Owner);

    bool    __fastcall  Execute(TStrings* sFiles);
};
//---------------------------------------------------------------------------
#endif
