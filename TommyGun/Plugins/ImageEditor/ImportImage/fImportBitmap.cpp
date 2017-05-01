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
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "fImportBitmap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "pngimage"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmImportBitmap::TfrmImportBitmap(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TfrmImportBitmap::Execute(TStrings* sFiles)
{
    bool bScreenSized   = (256 == imgBitmap->Picture->Bitmap->Width && 192 == imgBitmap->Picture->Bitmap->Height);
    bool bSpriteTooWide = (imgBitmap->Picture->Bitmap->Width  > 256);
    bool bSpriteTooHigh = (imgBitmap->Picture->Bitmap->Height > 256);
    m_sFiles = sFiles;
    edtBitmap->Max = sFiles->Count - 1;
    edtBitmap->Value = 0;
    edtBitmap->Enabled = sFiles->Count > 1;
    lblNewName->Visible = sFiles->Count > 1;
    edtNewName->Visible = sFiles->Count > 1;
    edtNewName->Text = ChangeFileExt(ExtractFileName(sFiles->Strings[0]), "");
    edtName->Enabled = sFiles->Count == 1;
    lblSpriteMultiMessage->Visible = sFiles->Count == 1;
    lblSpriteMultiFrameWidth->Visible = sFiles->Count == 1;
    edtSpriteMultiFrameWidth->Visible = sFiles->Count == 1;
    imgBitmap->Picture->Bitmap->LoadFromFile(sFiles->Strings[0]);
    lblBitmapSize->Caption = IntToStr(imgBitmap->Picture->Bitmap->Width) + " x " + IntToStr(imgBitmap->Picture->Bitmap->Height);
    m_bSpriteToWide = bSpriteTooWide;
    radImportAsSprite->Enabled = !bSpriteTooHigh;
    radImportAsScreen->Checked =  bScreenSized ||  bSpriteTooHigh;
    radImportAsSprite->Checked = !bScreenSized && !bSpriteTooHigh;
    radSpriteSingle->Enabled   =  !bSpriteTooWide;
    edtSpriteMultiFrameWidth->Max = imgBitmap->Picture->Bitmap->Width;
    panMaskColour->Color = imgBitmap->Picture->Bitmap->Canvas->Pixels[0][imgBitmap->Picture->Bitmap->Height-1];
    //radSpriteMulti->Enabled = sFiles->Count == 1;
    if (true == radImportAsScreen->Checked)
    {
        radImportAsScreenClick(NULL);
    }
    else
    {
        radImportAsSpriteClick(NULL);
    }
    edtBitmapChange(NULL);
    return ShowModal() == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::radImportAsScreenClick(TObject *Sender)
{
    imgBitmap->AutoSize = false;
    imgBitmap->Width    = 256;
    imgBitmap->Height   = 192;
    imgBitmap->Stretch  = true;

    cmdImport->Enabled = true;
    radSpriteSingle->Enabled = false;
    radSpriteMulti->Enabled = false;
    lblSpriteMultiMessage->Enabled = false;
    edtSpriteMultiFrameWidth->Enabled = false;
    lblSpriteMultiFrameWidth->Enabled = false;
    lblNewName->Enabled = false;
    edtNewName->Enabled = false;

    chkMaskEmptyClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::radImportAsTileClick(TObject *Sender)
{
    imgBitmap->Stretch  = false;
    imgBitmap->AutoSize = true;

    cmdImport->Enabled = true;
    radSpriteSingle->Enabled = false;
    radSpriteMulti->Enabled = false;
    lblSpriteMultiMessage->Enabled = false;
    edtSpriteMultiFrameWidth->Enabled = false;
    lblSpriteMultiFrameWidth->Enabled = false;
    lblNewName->Enabled = false;
    edtNewName->Enabled = false;

    chkMaskEmptyClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::radImportAsSpriteClick(TObject *Sender)
{
    imgBitmap->Stretch  = false;
    imgBitmap->AutoSize = true;

    cmdImport->Enabled = true;
    radSpriteSingle->Enabled = true;
    radSpriteMulti->Enabled = true;//m_sFiles->Count == 1;
    lblSpriteMultiMessage->Enabled = radSpriteMulti->Enabled;
    edtSpriteMultiFrameWidth->Enabled = radSpriteMulti->Enabled;
    lblSpriteMultiFrameWidth->Enabled = radSpriteMulti->Enabled;
    lblNewName->Enabled = true;
    edtNewName->Enabled = true;

    if (true == m_bSpriteToWide && radSpriteMulti->Enabled)
    {
        radSpriteSingle->Enabled        = false;
        radSpriteMulti->Checked         = true;
    }

    chkMaskEmptyClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::edtSpriteMultiFrameWidthChange(TObject *Sender)
{
    radSpriteMulti->Checked = true;
    cmdImport->Enabled = (float)((float)imgBitmap->Width / (float)edtSpriteMultiFrameWidth->Value) == (float)((int)(imgBitmap->Width / edtSpriteMultiFrameWidth->Value)) ||
                         edtNewName->Visible;
    int iFrames = edtNewName->Visible ? m_sFiles->Count : imgBitmap->Width / edtSpriteMultiFrameWidth->Value;
    lblFrames->Caption = IntToStr(iFrames) + (iFrames == 1 ? " Frame" : " Frames");
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::radSpriteMultiClick(TObject *Sender)
{
    edtSpriteMultiFrameWidthChange(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::radSpriteSingleClick(TObject *Sender)
{
    cmdImport->Enabled = true;
    lblFrames->Caption = "1 Frame";
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::edtNameChange(TObject *Sender)
{
    cmdImport->Enabled = edtName->Text.Trim() != "";
    m_sFiles->Strings[edtBitmap->Value] = ExtractFilePath(m_sFiles->Strings[edtBitmap->Value]) + edtName->Text + ExtractFileExt(m_sFiles->Strings[edtBitmap->Value]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::edtBitmapChange(TObject *Sender)
{
    imgBitmap->Picture->Bitmap->LoadFromFile(m_sFiles->Strings[edtBitmap->Value]);
    edtName->Text = ChangeFileExt(ExtractFileName(m_sFiles->Strings[edtBitmap->Value]), "");
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::panMaskColourClick(TObject *Sender)
{
    if (dlgColour->Execute())
    {
        panMaskColour->Color = dlgColour->Color;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImportBitmap::chkMaskEmptyClick(TObject *Sender)
{
    chkImageIsMasked->Enabled  = !radImportAsScreen->Checked;
    chkMaskEmpty->Enabled      = !radImportAsScreen->Checked && chkImageIsMasked->Checked;
    chkMaskBackground->Enabled = !radImportAsScreen->Checked && chkImageIsMasked->Checked;
    panMaskColour->Enabled     = !radImportAsScreen->Checked && chkImageIsMasked->Checked && chkMaskBackground->Checked;
    lblMaskColour->Enabled     = !radImportAsScreen->Checked && chkImageIsMasked->Checked && chkMaskBackground->Checked;
    panMaskColour->Caption     = lblMaskColour->Enabled ? "click to change" : "";
}
//---------------------------------------------------------------------------

