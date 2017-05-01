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
#include <math.h>
//---------------------------------------------------------------------------
#include "..\..\..\SafeMacros.h"
#include "fImageTools.h"
#include "fImageRotate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageTools;
//---------------------------------------------------------------------------
#define SHOW_BITMAPS 0
//---------------------------------------------------------------------------
TfrmImageTools *frmImageTools = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmImageTools::TfrmImageTools(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmImageTools::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    m_ImageEditor.SystemAddToolBar(PluginHandle, tbrImageTools);
    //m_ImageEditor.ToolMergePaintToolBar(PluginHandle, tbrImageTools);
    m_ImageEditor.TypeGetImageManager(PluginHandle, m_pImageManager);
    m_pBitmap = new Graphics::TBitmap();
    m_pSelectionBitmap = new Graphics::TBitmap();
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmImageTools::Release(void)
{
    SAFE_DELETE(frmImageRotate);
    SAFE_DELETE(m_pSelectionBitmap);
    SAFE_DELETE(m_pBitmap);
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpPixelCharacterClick(TObject *Sender)
{
    tbnOpPixelCharacter->ImageIndex = tbnOpPixelCharacter->Down ? 9 : 8;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpWrapClick(TObject *Sender)
{
    tbnOpWrap->ImageIndex = tbnOpWrap->Down ? 11 : 10;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::GetImage(void)
{
    m_pImage = NULL;
    m_ImageEditor.ImageGetCurrent(NULL, m_pImage);
    if (true == SAFE_PTR(m_pImage))
    {
        m_pBitmap->Width  = m_pImage->Width;
        m_pBitmap->Height = m_pImage->Height;
        m_pBitmap->PixelFormat = m_pImage->Palette->PixelFormat;
        m_pSelectionBitmap->PixelFormat = m_pImage->Palette->PixelFormat;
        m_pImage->Draw(m_pBitmap->Canvas);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::ShiftImage(int dX, int dY)
{
    // adjust the delta to be character movement or pixel movement
    dX *= tbnOpPixelCharacter->Down ? 1 : 8;
    dY *= tbnOpPixelCharacter->Down ? 1 : 8;
    // get the current image is bitmap
    GetImage();
    if (true == SAFE_PTR(m_pImage))
    {
        PushUndo(m_pImage, utUndo, "Shift");
        // draw on screen for testing
#if SHOW_BITMAPS
        BitBlt(GetDC(NULL), 1280, 0, m_pImage->Width, m_pImage->Height, m_pBitmap->Canvas->Handle, 0, 0, SRCCOPY);
#endif//SHOW_BITMAPS
        // get the selection rect
        TRect SelectionRect(m_pImage->GetSelectionRect());
        // make the selection rect the full image if needed
        if (!SelectionRect.Left && !SelectionRect.Right && !SelectionRect.Top && !SelectionRect.Bottom)
        {
            SelectionRect.Right    = m_pImage->Width;
            SelectionRect.Bottom   = m_pImage->Height;
        }
        // setup the selection bitmap
        m_pSelectionBitmap->Width  = SelectionRect.Width();
        m_pSelectionBitmap->Height = SelectionRect.Height();
        // get the selection bitmap
        BitBlt
        (
            m_pSelectionBitmap->Canvas->Handle,
            0,
            0,
            SelectionRect.Width(),
            SelectionRect.Height(),
            m_pBitmap->Canvas->Handle,
            SelectionRect.Left,
            SelectionRect.Top,
            SRCCOPY
        );
        // calculate the start positions
        int X = std::max(SelectionRect.Left, SelectionRect.Left + dX);
        int Y = std::max(SelectionRect.Top , SelectionRect.Top  + dY);
        int W = SelectionRect.Width()  - std::abs(dX);
        int H = SelectionRect.Height() - std::abs(dY);
        int L = std::max(0, -dX);
        int T = std::max(0, -dY);
        // now place the bitmap back into the original image
        BitBlt(m_pBitmap->Canvas->Handle, X, Y, W, H, m_pSelectionBitmap->Canvas->Handle, L, T, SRCCOPY);
        // work out the blank shift area
        TRect FRect;
        L = 0;
        T = 0;
        if (dX > 0)
        {
            // right
            FRect = TRect(SelectionRect.Left, SelectionRect.Top, SelectionRect.Right - W, SelectionRect.Bottom);
            L = W;
        }
        if (dX < 0)
        {
            // left
            FRect = TRect(SelectionRect.Left + W, SelectionRect.Top, SelectionRect.Right, SelectionRect.Bottom);
        }
        if (dY > 0)
        {
            // down
            FRect = TRect(SelectionRect.Left, SelectionRect.Top, SelectionRect.Right, SelectionRect.Bottom - H);
            T = H;
        }
        if (dY < 0)
        {
            // up
            FRect = TRect(SelectionRect.Left, SelectionRect.Top + H, SelectionRect.Right, SelectionRect.Bottom);
        }
        if (!tbnOpWrap->Down)
        {
            // wrap the shift
            BitBlt
            (
                m_pBitmap->Canvas->Handle,
                FRect.Left,
                FRect.Top,
                FRect.Width(),
                FRect.Height(),
                m_pSelectionBitmap->Canvas->Handle,
                L,
                T,
                SRCCOPY
            );
        }
        else
        {
            // clear the shifted area
            m_pBitmap->Canvas->Brush->Color = m_pImage->Palette->BrushColor;
            m_pBitmap->Canvas->FillRect(FRect);
        }
        // draw the image on the screen
#if SHOW_BITMAPS
        BitBlt(GetDC(NULL), 1280, m_pImage->Height + 16, m_pImage->Width, m_pImage->Height, m_pBitmap->Canvas->Handle, 0, 0, SRCCOPY);
#endif//SHOW_BITMAPS
        // now get the image to convert the result
        if (false == m_pImage->ConvertBitmap(m_pBitmap))
        {
            // palette does not support bitmap conversion
            int iAnswer;
            m_ImageEditor.SystemMessageBox
            (
                mbtError,
                "Palette Error",
                "Failed to complete Shift or Scroll operation",
                "The palette plugin - " + m_pImage->Palette->Name + ", does not have the required support for this operation.",
                "Ok",
                "",
                "",
                iAnswer
            );
        }
        else
        {
            m_ImageEditor.SystemUpdateImage(NULL, m_pImage);
            m_ImageEditor.SystemRefreshView(NULL);
            m_ImageEditor.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
        }
        PushUndo(m_pImage, utRedo, "Shift");
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::MirrorOrFlip(bool bMirror)
{
    // get the current image is bitmap
    GetImage();
    if (true == SAFE_PTR(m_pImage))
    {
        PushUndo(m_pImage, utUndo, bMirror ? "Mirror" : "Flip");
#if SHOW_BITMAPS
        BitBlt(GetDC(NULL), 1280, 0, m_pImage->Width, m_pImage->Height, m_pBitmap->Canvas->Handle, 0, 0, SRCCOPY);
#endif//SHOW_BITMAPS
        // get the selection rect
        TRect SelectionRect(m_pImage->GetSelectionRect());
        // make the selection rect the full image if needed
        if (!SelectionRect.Left && !SelectionRect.Right && !SelectionRect.Top && !SelectionRect.Bottom)
        {
            SelectionRect.Right    = m_pImage->Width;
            SelectionRect.Bottom   = m_pImage->Height;
        }
        // setup the selection bitmap
        m_pSelectionBitmap->Width  = SelectionRect.Width();
        m_pSelectionBitmap->Height = SelectionRect.Height();
        // get the selection bitmap
        BitBlt
        (
            m_pSelectionBitmap->Canvas->Handle,
            0,
            0,
            SelectionRect.Width(),
            SelectionRect.Height(),
            m_pBitmap->Canvas->Handle,
            SelectionRect.Left,
            SelectionRect.Top,
            SRCCOPY
        );
#if SHOW_BITMAPS
        BitBlt(GetDC(NULL), 1280 + m_pImage->Width + 16, 0, m_pImage->Width, m_pImage->Height, m_pSelectionBitmap->Canvas->Handle, 0, 0, SRCCOPY);
#endif//SHOW_BITMAPS
        if (bMirror)
        {
            StretchBlt
            (
                m_pBitmap->Canvas->Handle,
                SelectionRect.Left,
                SelectionRect.Top,
                SelectionRect.Width(),
                SelectionRect.Height(),
                m_pSelectionBitmap->Canvas->Handle,
                SelectionRect.Width()-1,
                0,
               -SelectionRect.Width(),
                SelectionRect.Height(),
                SRCCOPY
            );
        }
        else
        {
            StretchBlt
            (
                m_pBitmap->Canvas->Handle,
                SelectionRect.Left,
                SelectionRect.Top,
                SelectionRect.Width(),
                SelectionRect.Height(),
                m_pSelectionBitmap->Canvas->Handle,
                0,
                SelectionRect.Height()-1,
                SelectionRect.Width(),
               -SelectionRect.Height(),
                SRCCOPY
            );
        }
#if SHOW_BITMAPS
        BitBlt(GetDC(NULL), 1280, m_pImage->Height + 16, m_pImage->Width, m_pImage->Height, m_pBitmap->Canvas->Handle, 0, 0, SRCCOPY);
#endif//SHOW_BITMAPS
        // now get the image to convert the result
        if (false == m_pImage->ConvertBitmap(m_pBitmap))
        {
            // palette does not support bitmap conversion
            int iAnswer;
            m_ImageEditor.SystemMessageBox
            (
                mbtError,
                "Palette Error",
                "Failed to complete Mirror or Flip operation",
                "The palette plugin - " + m_pImage->Palette->Name + ", does not have the required support for this operation.",
                "Ok",
                "",
                "",
                iAnswer
            );
        }
        else
        {
            m_ImageEditor.SystemUpdateImage(NULL, m_pImage);
            m_ImageEditor.SystemRefreshView(NULL);
            m_ImageEditor.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
        }
        PushUndo(m_pImage, utRedo, bMirror ? "Mirror" : "Flip");
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::Rotate(bool bRotateRight)
{
    // adjust the delta to be character movement or pixel movement
    int Step = tbnOpPixelCharacter->Down ? 1 : 8;
    // get the current image as a bitmap
    GetImage();
    if (true == SAFE_PTR(m_pImage))
    {
        PushUndo(m_pImage, utUndo, "Rotate " + bRotateRight ? "Right" : "Left");
        // draw on screen for testing
#if SHOW_BITMAPS
        BitBlt(GetDC(NULL), 1280, 0, m_pImage->Width, m_pImage->Height, m_pBitmap->Canvas->Handle, 0, 0, SRCCOPY);
#endif//SHOW_BITMAPS
        // get the selection rect
        TRect SelectionRect(m_pImage->GetSelectionRect());
        // make the selection rect the full image if needed
        if (!SelectionRect.Left && !SelectionRect.Right && !SelectionRect.Top && !SelectionRect.Bottom)
        {
            SelectionRect.Right    = m_pImage->Width;
            SelectionRect.Bottom   = m_pImage->Height;
        }
        // make the selection rect a square
        if (SelectionRect.Width() < SelectionRect.Height())
        {
            // make the width the major size of the selection rect
            SelectionRect.Bottom = SelectionRect.Top + SelectionRect.Width();
        }
        else if (SelectionRect.Width() > SelectionRect.Height())
        {
            // make the height the major size of the selection rect
            SelectionRect.Right = SelectionRect.Left + SelectionRect.Height();
        }
        // setup the selection bitmap
        m_pSelectionBitmap->Width  = SelectionRect.Width();
        m_pSelectionBitmap->Height = SelectionRect.Height();
        // get the selection bitmap
        BitBlt
        (
            m_pSelectionBitmap->Canvas->Handle,
            0,
            0,
            SelectionRect.Width(),
            SelectionRect.Height(),
            m_pBitmap->Canvas->Handle,
            SelectionRect.Left,
            SelectionRect.Top,
            SRCCOPY
        );
        // rotate the selection into the bitmap
        int iSize = SelectionRect.Width();
        for (int y = 0; y < iSize; ++y)
        {
            for (int x = 0; x < iSize; ++x)
            {
                if (bRotateRight)
                {
                    m_pBitmap->Canvas->Pixels[SelectionRect.Left + x][SelectionRect.Top + y] =
                        m_pSelectionBitmap->Canvas->Pixels[y][iSize - x - 1];
                }
                else
                {
                    m_pBitmap->Canvas->Pixels[SelectionRect.Left + x][SelectionRect.Top + y] =
                        m_pSelectionBitmap->Canvas->Pixels[iSize - y  - 1][x];
                }
            }
        }

        // draw the image on the screen
#if SHOW_BITMAPS
        BitBlt(GetDC(NULL), 1280, m_pImage->Height + 16, m_pImage->Width, m_pImage->Height, m_pBitmap->Canvas->Handle, 0, 0, SRCCOPY);
#endif//SHOW_BITMAPS
        // now get the image to convert the result
        if (false == m_pImage->ConvertBitmap(m_pBitmap))
        {
            // palette does not support bitmap conversion
            int iAnswer;
            m_ImageEditor.SystemMessageBox
            (
                mbtError,
                "Palette Error",
                "Failed to complete Rotate operation",
                "The palette plugin - " + m_pImage->Palette->Name + ", does not have the required support for this operation.",
                "Ok",
                "",
                "",
                iAnswer
            );
        }
        else
        {
            m_ImageEditor.SystemUpdateImage(NULL, m_pImage);
            m_ImageEditor.SystemRefreshView(NULL);
            m_ImageEditor.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
        }
        PushUndo(m_pImage, utRedo, "Rotate " + bRotateRight ? "Right" : "Left");
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::PushUndo(ZXImage* pImage, ZXUndoType UndoType, String sOperaton)
{
    KXmlInfo Undo;
    Undo.Add("Operation", "ImageChange");
    Undo.Add("Plugin", "Image Tools");
    Undo.Add("Description", sOperaton + " [" + pImage->Name + "]");
    KXmlInfo Image("Image");
    pImage->Save(Image, false);
    Undo.Add(Image);
    m_ImageEditor.Notify(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, UndoType, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tmrRepeatTimer(TObject *Sender)
{
    if (m_iRepeatTool == 0)
    {
        tbnOpShiftLeftClick(NULL);
    }
    else if (m_iRepeatTool == 1)
    {
        tbnOpShiftRightClick(NULL);
    }
    else if (m_iRepeatTool == 2)
    {
        tbnOpShiftUpClick(NULL);
    }
    else if (m_iRepeatTool == 3)
    {
        tbnOpShiftDownClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpShiftLeftMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    tmrRepeat->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpShiftLeftMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_iRepeatTool = 0;
    tmrRepeat->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpShiftRightMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_iRepeatTool = 1;
    tmrRepeat->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpShiftUpMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_iRepeatTool = 2;
    tmrRepeat->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpShiftDownMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_iRepeatTool = 3;
    tmrRepeat->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpShiftLeftClick(TObject *Sender)
{
    ShiftImage(-1,  0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpShiftRightClick(TObject *Sender)
{
    ShiftImage( 1,  0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpShiftUpClick(TObject *Sender)
{
    ShiftImage( 0, -1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpShiftDownClick(TObject *Sender)
{
    ShiftImage( 0,  1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpRotateRightClick(TObject *Sender)
{
    Rotate(true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpRotateLeftClick(TObject *Sender)
{
    Rotate(false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpMirrorClick(TObject *Sender)
{
    MirrorOrFlip(true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnOpFlipClick(TObject *Sender)
{
    MirrorOrFlip(false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageTools::tbnArbitaryRotateClick(TObject *Sender)
{
    if (false == SAFE_PTR(frmImageRotate))
    {
        frmImageRotate = new TfrmImageRotate(Application);
    }
    if (true == SAFE_PTR(frmImageRotate))
    {
        GetImage();
        if (frmImageRotate->Execute(m_pBitmap, m_pImage->Palette->GetColor(0)))
        {
            PushUndo(m_pImage, utUndo, "Arbitary Rotate");
            if (false == m_pImage->ConvertBitmap(m_pBitmap))
            {
                // palette does not support bitmap conversion
                int iAnswer;
                m_ImageEditor.SystemMessageBox
                (
                    mbtError,
                    "Palette Error",
                    "Failed to complete Rotate operation",
                    "The palette plugin - " + m_pImage->Palette->Name + ", does not have the required support for this operation.",
                    "Ok",
                    "",
                    "",
                    iAnswer
                );
            }
            else
            {
                m_ImageEditor.SystemUpdateImage(NULL, m_pImage);
                m_ImageEditor.SystemRefreshView(NULL);
                m_ImageEditor.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
            }
            PushUndo(m_pImage, utRedo, "Arbitary Rotate");
        }
    }
    //SAFE_DELETE(frmImageRotate);
}
//---------------------------------------------------------------------------

