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
#include "fTextTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KSlider"
#pragma link "KSpinEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace PaintTools;
//---------------------------------------------------------------------------
TfrmTextDialog *frmTextDialog = NULL;
static bool bChanging = false;
//---------------------------------------------------------------------------
__fastcall TfrmTextDialog::TfrmTextDialog(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmTextDialog::cmdFontClick(TObject *Sender)
{
    if (true == dlgFont->Execute())
    {
        UpdatePreview();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTextDialog::dlgFontApply(TObject *Sender, HWND Wnd)
{
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTextDialog::slrMagnificationChange(TObject *Sender)
{
    if (!bChanging)
    {
        bChanging = true;
        UpdatePreview();
        bChanging = false;
        slrMagnification->Update();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTextDialog::edtMagnificationChange(TObject *Sender)
{
    if (!bChanging)
    {
        bChanging = true;
        slrMagnification->Position = edtMagnification->Value;
        UpdatePreview();
        bChanging = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTextDialog::chkAutoUpdateClick(TObject *Sender)
{
    if (chkAutoUpdate->Checked)
    {
        UpdatePreview();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTextDialog::UpdatePreview(void)
{
    lblFontName->Caption = dlgFont->Font->Name;
    lblFontSize->Caption = dlgFont->Font->Size;
    lblFontSample->Font->Assign(dlgFont->Font);
    // update the preview image
    imgPreview->Width  = m_Image->Width  * slrMagnification->Position;
    imgPreview->Height = m_Image->Height * slrMagnification->Position;
    imgPreview->Picture->Bitmap->Width  = std::max(imgPreview->Picture->Bitmap->Width , m_Image->Width  * slrMagnification->Position);
    imgPreview->Picture->Bitmap->Height = std::max(imgPreview->Picture->Bitmap->Height, m_Image->Height * slrMagnification->Position);
    if (true == chkAutoUpdate->Checked)
    {
        // draw the image onto the preview image
        m_Image->DrawInitialize();
        m_Image->DrawBegin();
        m_Image->ReDraw();
        m_Image->DrawText(m_iX, m_iY, edtText->Text, dlgFont->Font);
        m_Image->DrawEnd();
        m_Image->Draw(imgPreview->Picture->Bitmap->Canvas, slrMagnification->Position);
        m_Image->DrawCancel();
        imgPreview->Refresh();
    }
}
//---------------------------------------------------------------------------
bool __fastcall TfrmTextDialog::Execute(int X, int Y, ZXImage* Image)
{
    m_iX = X;
    m_iY = Y;
    m_Image = Image;
    imgPreview->Picture->Bitmap->PixelFormat = pf32bit;
    sbxImagePreview->DoubleBuffered = true;
    UpdatePreview();
    ShowModal();
    return ModalResult == mrOk;
}
//---------------------------------------------------------------------------

