//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "fDisplayView.h"
#include "fCodeEditor.h"
#include "ZXSnapManager.h"
//#include "GlassManager.h"
#include "ZXDebugger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmDisplayView *frmDisplayView;
//---------------------------------------------------------------------------
__fastcall TfrmDisplayView::TfrmDisplayView(TComponent* Owner)
 : TForm(Owner)
 , m_Initializing(true)
{
//    WindowProc = SubClassWndProc;
}
//---------------------------------------------------------------------------
//void __fastcall TfrmDisplayView::SubClassWndProc(Messages::TMessage &Message)
//{
//    if (!SnapManager::ProcessMoving(Message, this))
//    {
//        WndProc(Message);
//    }
//}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::FormCreate(TObject *Sender)
{
    // register the window with the snap manager
//    SnapManager::RegisterSnapClient(frmDisplayView, frmCodeEditor, seLeft, 0, 32);
    // resize the bitmap in the image
    imgMainDisplay->Constraints->MinHeight = 192;
    imgMainDisplay->Constraints->MinWidth  = 256;
    imgMainDisplay->Picture->Bitmap->Width  = imgMainDisplay->Width;
    imgMainDisplay->Picture->Bitmap->Height = imgMainDisplay->Height;
    imgMainDisplay->Picture->Bitmap->PixelFormat = pf32bit;
    imgMainDisplay->Picture->Bitmap->Canvas->Brush->Color = clBlack;
    imgMainDisplay->Picture->Bitmap->Canvas->FillRect(TRect(0,0,256,192));

    popSVNormalSizeClick(NULL);

    if (imgMainDisplay->Width % 256 != 0)
    {
        int width = (imgMainDisplay->Width + 127) / 256;
        // adjust the window size to correct the image size
        Width += ((width * 256) - imgMainDisplay->Width);
    }
    if (imgMainDisplay->Height % 192 != 0)
    {
        int height = (imgMainDisplay->Height + 95) / 192;
        // adjust the window size to correct the image size
        Height += ((height * 192) - imgMainDisplay->Height);
    }
    m_Initializing = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::panMainDisplayWhiteResize(TObject *Sender)
{
    if (m_Initializing) return;
    imgMainDisplay->Picture->Bitmap->Width  = imgMainDisplay->Width;
    imgMainDisplay->Picture->Bitmap->Height = imgMainDisplay->Height;
    g_Debugger->UpdateDisplay();
    if (imgMainDisplay->Width % 256 != 0 || imgMainDisplay->Height % 192 != 0)
    {
        popSVNormalSize->Checked = false;
        popSVTripleSize->Checked = false;
        popSVTripleSize->Checked = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    g_Debugger->Machine.Keyboard.KeyDown(Key, Shift);
    if (Shift.Contains(ssAlt) && Key == VK_LEFT)
    {
        frmCodeEditor->actRewindExecute(NULL);
    }
    else if (Shift.Contains(ssAlt) && Key == VK_RIGHT)
    {
        frmCodeEditor->actForwardExecute(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    g_Debugger->Machine.Keyboard.KeyUp(Key, Shift);
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::popSVNormalSizeClick(TObject *Sender)
{
    Width  = 256 + (Width  - imgMainDisplay->Width );
    Height = 192 + (Height - imgMainDisplay->Height);
    popSVNormalSize->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::popSVDoubleSizeClick(TObject *Sender)
{
    Width  = 512 + (Width  - imgMainDisplay->Width );
    Height = 384 + (Height - imgMainDisplay->Height);
    popSVDoubleSize->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::popSVTripleSizeClick(TObject *Sender)
{
    Width  = 768 + (Width  - imgMainDisplay->Width );
    Height = 576 + (Height - imgMainDisplay->Height);
    popSVTripleSize->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::popSVShowAttributesClick(TObject *Sender)
{
    popSVShowAttributes->Checked = !popSVShowAttributes->Checked;
    g_Debugger->Machine.Display.SetAttributes(popSVShowAttributes->Checked, popBlackOnWhite->Checked);
    popBlackOnWhite->Enabled = !popSVShowAttributes->Checked;
    popWhiteOnBlack->Enabled = !popSVShowAttributes->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::FormMouseEnter(TObject *Sender)
{
    //AlphaBlend = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::FormMouseLeave(TObject *Sender)
{
    //AlphaBlend = popTranslucent->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::popTranslucentClick(TObject *Sender)
{
    popTranslucent->Checked = !popTranslucent->Checked;
    AlphaBlend = popTranslucent->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDisplayView::popBlackOnWhiteClick(TObject *Sender)
{
    static_cast<TMenuItem*>(Sender)->Checked = true; 
    g_Debugger->Machine.Display.SetAttributes(popSVShowAttributes->Checked, popBlackOnWhite->Checked);
}
//---------------------------------------------------------------------------

