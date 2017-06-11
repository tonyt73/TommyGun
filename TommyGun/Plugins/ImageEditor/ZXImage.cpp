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
#pragma hdrstop
//---------------------------------------------------------------------------
#include "..\..\SafeMacros.h"
#include "ZXImage.h"
#include "ZXPalette.h"
//---------------------------------------------------------------------------
#include <mmsystem.h>
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const char g_cHex[16] = "0123456789ABCDEF";
//---------------------------------------------------------------------------
TColor ZXImage::g_BackgroundColor = clBlack;
TColor ZXImage::g_TransparentColor = clFuchsia;
bool ZXImage::g_bTransparentMode = false;
//---------------------------------------------------------------------------
__fastcall ZXImage::ZXImage(int iWidth, int iHeight, bool bMasked, ZXPalette* Palette, bool bCanResize)
: m_sName("Unnamed"),
  m_pPalette(Palette),
  m_pPixelBuffer(NULL),
  m_pBackupPixelBuffer(NULL),
  m_pAttributeBuffer(NULL),
  m_pBackupAttributeBuffer(NULL),
  m_pMaskBuffer(NULL),
  m_pBackupMaskBuffer(NULL),
  m_fMaskAlpha(0.75f),
  m_bCanResize(bCanResize),
  m_bMaskMode(false),
  m_bHotSpotMode(false),
  m_bIsDirty(true),
  m_MaskColor(clRed),
  m_bIsMasked(bMasked),
  m_pImage(NULL),
  m_pMaskImage(NULL),
  m_pBackupImage(NULL),
  m_iPixelBufferSize(0),
  m_iMaskBufferSize(0),
  m_iAttributeBufferSize(0),
  m_iDrawInitializeCount(0),
  m_fModeScaleX(1.f),
  m_fModeScaleY(1.f),
  m_iSubType(0),
  m_iWidth(iWidth),
  m_iHeight(iHeight),
  m_iHotSpotX(-1),
  m_iHotSpotY(-1)
{
    ResizeBuffers(iWidth, iHeight);
}
//---------------------------------------------------------------------------
__fastcall ZXImage::ZXImage(ZXImage& Image)
{
    *this = Image;
    m_bIsDirty = true;
}
//---------------------------------------------------------------------------
__fastcall ZXImage::~ZXImage()
{
    FreeBuffers();
}
//---------------------------------------------------------------------------
ZXImage& ZXImage::operator=(ZXImage& Image)
{
    SAFE_DELETE(m_pPixelBuffer);
    SAFE_DELETE(m_pBackupPixelBuffer);
    SAFE_DELETE(m_pAttributeBuffer);
    SAFE_DELETE(m_pBackupAttributeBuffer);
    SAFE_DELETE(m_pMaskBuffer);
    SAFE_DELETE(m_pBackupMaskBuffer);
    // copy the images' properties
    m_sName                 = Image.m_sName;
    m_iWidth                = Image.m_iWidth;
    m_iHeight               = Image.m_iHeight;
    m_iDrawInitializeCount  = 0;
    m_iDrawBeginCount       = 0;
    m_bMaskMode             = Image.m_bMaskMode;
    m_fMaskAlpha            = Image.m_fMaskAlpha;
    m_MaskColor             = Image.m_MaskColor;
    m_bIsMasked             = Image.m_bIsMasked;
    m_bCanResize            = Image.m_bCanResize;
    m_iPixelBufferSize      = Image.m_iPixelBufferSize;
    m_iMaskBufferSize       = Image.m_iMaskBufferSize;
    m_iAttributeBufferSize  = Image.m_iAttributeBufferSize;
    m_pPalette              = Image.m_pPalette;
    // copy the buffers and the images
    m_pImage->PixelFormat   = SAFE_PTR(m_pPalette) ? m_pPalette->PixelFormat : pf1bit;
    m_pImage->Width         = m_iWidth;
    m_pImage->Height        = m_iHeight;
    m_pImage->Assign(Image.m_pImage);
    if (true == SAFE_PTR(m_pMaskImage))
    {
      m_pMaskImage->PixelFormat= m_pImage->PixelFormat;
      m_pMaskImage->Width     = m_iWidth;
      m_pMaskImage->Height    = m_iHeight;
      m_pMaskImage->Assign(Image.m_pMaskImage);
    }
    if (true == SAFE_PTR(m_pBackupImage))
    {
      m_pBackupImage->PixelFormat = SAFE_PTR(m_pPalette) ? m_pPalette->PixelFormat : pf1bit;
      m_pBackupImage->Width   = m_iWidth;
      m_pBackupImage->Height  = m_iHeight;
    }
    m_pPixelBuffer          = new unsigned char[m_iPixelBufferSize];
    m_pBackupPixelBuffer    = new unsigned char[m_iPixelBufferSize];
    CopyMemory(m_pPixelBuffer, Image.m_pPixelBuffer, m_iPixelBufferSize);
    if (true == m_bIsMasked)
    {
        m_pMaskBuffer       = new unsigned char[m_iMaskBufferSize];
        m_pBackupMaskBuffer = new unsigned char[m_iMaskBufferSize];
        CopyMemory(m_pMaskBuffer, Image.m_pMaskBuffer, m_iMaskBufferSize);
    }
    if (0 != m_iAttributeBufferSize)
    {
        m_pAttributeBuffer  = new unsigned char[m_iAttributeBufferSize];
        m_pBackupAttributeBuffer = new unsigned char[m_iAttributeBufferSize];
        CopyMemory(m_pAttributeBuffer, Image.m_pAttributeBuffer, m_iAttributeBufferSize);
    }
    m_bIsDirty = true;
    Invalidate();
    return *this;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawInitialize(void)
{
    while (0 < m_iDrawInitializeCount)
    {
        DrawCancel();
    }
    m_iDrawInitializeCount = 0;
    //if (0 == m_iDrawInitializeCount)
    {
        // backup the original buffers
        if (false == m_bMaskMode)
        {
            CopyMemory(m_pBackupPixelBuffer, m_pPixelBuffer, m_iPixelBufferSize);
        }
        else
        {
            CopyMemory(m_pBackupMaskBuffer, m_pMaskBuffer, m_iMaskBufferSize);
        }
        if (NULL != m_pAttributeBuffer)
        {
            CopyMemory(m_pBackupAttributeBuffer, m_pAttributeBuffer, m_iAttributeBufferSize);
        }
        // backup the bitmap
        BitBlt(m_pBackupImage->Canvas->Handle,
               0, 0,
               m_iWidth,
               m_iHeight,
               m_pImage->Canvas->Handle,
               0, 0,
               SRCCOPY);
        m_rBlitRect.Left   = m_iWidth;
        m_rBlitRect.Top    = m_iHeight;
        m_rBlitRect.Right  = 0;
        m_rBlitRect.Bottom = 0;
        m_rLastBlitRect    = m_rBlitRect;
    }
    ++m_iDrawInitializeCount;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawCancel(void)
{
    // Restore the image to the original
    --m_iDrawInitializeCount;
    if (0 == m_iDrawInitializeCount)
    {
        // restore the buffers
        if (false == m_bMaskMode)
        {
            CopyMemory(m_pPixelBuffer, m_pBackupPixelBuffer, m_iPixelBufferSize);
            if (NULL != m_pAttributeBuffer)
            {
                CopyMemory(m_pAttributeBuffer, m_pBackupAttributeBuffer, m_iAttributeBufferSize);
            }
        }
        else
        {
            CopyMemory(m_pMaskBuffer, m_pBackupMaskBuffer, m_iMaskBufferSize);
        }
        // Restore the image to the original
        BitBlt(m_pImage->Canvas->Handle,
               0, 0,
               m_iWidth,
               m_iHeight,
               m_pBackupImage->Canvas->Handle,
               0, 0,
               SRCCOPY);
        // reset the blit rects
        m_rBlitRect.Left   = m_iWidth;
        m_rBlitRect.Top    = m_iHeight;
        m_rBlitRect.Right  = 0;
        m_rBlitRect.Bottom = 0;
        m_rLastBlitRect    = m_rBlitRect;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawFinalize(void)
{
    --m_iDrawInitializeCount;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawBegin(void)
{
    // restore the buffers (before the operation takes place)
    if (false == m_bMaskMode)
    {
        CopyMemory(m_pPixelBuffer, m_pBackupPixelBuffer, m_iPixelBufferSize);
        if (NULL != m_pAttributeBuffer)
        {
            CopyMemory(m_pAttributeBuffer, m_pBackupAttributeBuffer, m_iAttributeBufferSize);
        }
    }
    else
    {
        CopyMemory(m_pMaskBuffer, m_pBackupMaskBuffer, m_iMaskBufferSize);
    }

    // copy the original bitmap if required
    if (m_rLastBlitRect.Left < m_rLastBlitRect.Right)
    {
        BitBlt(m_pImage->Canvas->Handle,
               m_rLastBlitRect.Left  , m_rLastBlitRect.Top,
               m_rLastBlitRect.Right - m_rLastBlitRect.Left,
               m_rLastBlitRect.Bottom - m_rLastBlitRect.Top,
               m_pBackupImage->Canvas->Handle,
               m_rLastBlitRect.Left, m_rLastBlitRect.Top,
               SRCCOPY);
    }
    /*m_rBlitRect.Left   = m_iWidth;
    m_rBlitRect.Top    = m_iHeight;
    m_rBlitRect.Right  = 0;
    m_rBlitRect.Bottom = 0;
    m_rLastBlitRect    = m_rBlitRect;*/
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawEnd(void)
{
    if (m_vDirtyRects.size() || (m_rBlitRect.Left < m_rBlitRect.Right && m_rBlitRect.Top < m_rBlitRect.Bottom))
    {
        DrawImage();
        m_vDirtyRects.clear();
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawImage(void)
{
    if (true == SAFE_PTR(m_pPalette))
    {
        // get the palette object to draw the changes to the dirty regions of the image
        m_pPalette->Draw(*this, m_pImage);
        // replace transparent color
        if (g_bTransparentMode)
        {
            for (int y = 0; y < m_iHeight; y++)
            {
                for (int x = 0; x < m_iWidth; x++)
                {
                    if (m_pImage->Canvas->Pixels[x][y] == g_TransparentColor)
                    {
                        m_pImage->Canvas->Pixels[x][y] = g_BackgroundColor;
                    }
                }
            }
        }
        // apply the mask if needed
        if (true == m_bMaskMode && true == SAFE_PTR(m_pMaskImage))
        {
            // copy the image onto the mask bitmap
            BitBlt(m_pMaskImage->Canvas->Handle, 0, 0, m_iWidth, m_iHeight, m_pImage->Canvas->Handle, 0, 0, SRCCOPY);
            if (0.25f < m_fMaskAlpha)
            {
                // draw the mask
                DrawMask(m_fMaskAlpha < 0.95f);
            }
        }
        if (UsesHotSpot && m_bHotSpotMode)
        {
            if (0.25f < m_fMaskAlpha)
            {
                // TODO: Draw the Hot Spot
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawMask(bool bBlendMask)
{
    TRect UpdateRect;
    int iRects = Rects();
    //int iPixelsPerByte = m_pPalette->PixelsPerByte;
    int iMaskWidth = m_iWidth % 8 == 0 ? (m_iWidth / 8) : ((m_iWidth / 8) + 1);
    if (false == bBlendMask)
    {
        for (int y = 0; y < m_iHeight; y++)
        {
            for (int x = 0; x < m_iWidth; x++)
            {
                int iByteOffset = (x >> 3) + (iMaskWidth * y);
                unsigned char iBit = 0x80 >> (x & 0x07);
                m_pMaskImage->Canvas->Pixels[x][y] = m_pMaskBuffer[iByteOffset] & iBit ? m_MaskColor : clBlack;
            }
        }
    }
    else
    {
        // get the masks RGB colors as floats
        int MaskColor = ColorToRGB(m_MaskColor);
        float MaskR = (float)((MaskColor & 0x000000FF)      ) * m_fMaskAlpha;
        float MaskG = (float)((MaskColor & 0x0000FF00) >>  8) * m_fMaskAlpha;
        float MaskB = (float)((MaskColor & 0x00FF0000) >> 16) * m_fMaskAlpha;
        float fAlpha = 1.f - m_fMaskAlpha;
        unsigned int R = 0;
        unsigned int G = 0;
        unsigned int B = 0;
        unsigned int C = 0;
        for (int y = 0; y < m_iHeight; y++)
        {
            for (int x = 0; x < m_iWidth; x++)
            {
                int iByteOffset = (x >> 3) + (iMaskWidth * y);
                unsigned char iBit = 0x80 >> (x & 0x07);
                if (m_pMaskBuffer[iByteOffset] & iBit)
                {
                    // blend the colors
                    int Color = ColorToRGB(m_pImage->Canvas->Pixels[x][y]);
                    float PixR = (float)((Color & 0x000000FF)      ) * fAlpha;
                    float PixG = (float)((Color & 0x0000FF00) >>  8) * fAlpha;
                    float PixB = (float)((Color & 0x00FF0000) >> 16) * fAlpha;
                    R = PixR + MaskR;
                    G = PixG + MaskG;
                    B = PixB + MaskB;
                    C = R + (G << 8) + (B << 16);
                    m_pMaskImage->Canvas->Pixels[x][y] = (TColor)C;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawPoint(int X, int Y, bool bSet)
{
    if (0 <= X && X < m_iWidth && 0 <= Y && Y < m_iHeight && (PtInRect(X, Y)))
    {
        if (false == m_bMaskMode)
        {
            if (true == SAFE_PTR(m_pPalette))
            {
                m_pPalette->Write(X, Y, bSet, *this);
            }
        }
        else
        {
            int iStride = (m_iWidth % 8) ? (m_iWidth / 8) + 1 : (m_iWidth / 8);
            // set the mask pixel
            int iByteOffset = (X >> 3) + (iStride * Y);
            unsigned char iBit = 0x80 >> (X & 0x07);
            m_pMaskBuffer[iByteOffset] = bSet ? (m_pMaskBuffer[iByteOffset] | iBit) : (m_pMaskBuffer[iByteOffset] & ~iBit);
            // dirty the pixel
            Invalidate();
            AddRect(m_rBlitRect);
        }
        m_bIsDirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawLine(const TRect& Rect, bool bSet)
{
    //PERFORMANCE_PUSH
    // draws a line from (m_iStartX, m_iStartY) to (iPX, iPX)

    int iDX = 1;
    int iDY = 1;
    int iPX = Rect.Left;
    int iPY = Rect.Top;

    int iYDiff = Rect.Bottom - Rect.Top;
    if (iYDiff < 0)
    {
        iYDiff = -iYDiff;
        iDY = -1;
    }

    int iXDiff = Rect.Right - Rect.Left;
    if (iXDiff < 0)
    {
        iXDiff = -iXDiff;
        iDX = -1;
    }

    int iError = 0;
    if (iXDiff > iYDiff)
    {
        for (int i = 0; i <= iXDiff; ++i)
        {
            DrawPoint(iPX, iPY, bSet);
            iPX += iDX;
            if (iPX > m_iWidth) break;
            iError += iYDiff;
            if (iError >= iXDiff)
            {
                iError -= iXDiff;
                iPY += iDY;
            }
        }
    }
    else
    {
        for (int i = 0; i <= iYDiff; ++i)
        {
            DrawPoint(iPX, iPY, bSet);
            iPY += iDY;
            if (iPY > m_iHeight) break;
            iError += iXDiff;
            if (iError >= iYDiff)
            {
                iError -= iYDiff;
                iPX += iDX;
            }
        }
    }
    m_bIsDirty = true;
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawHorizontalLine(int SX, int SY, int EX, bool bSet)
{
    for (int x = SX; x <= EX; ++x)
    {
        DrawPoint(x, SY, bSet);
    }
    m_bIsDirty = true;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::DrawText(int X, int Y, const String& sText, TFont* Font)
{
    Graphics::TBitmap* Bitmap = new Graphics::TBitmap();
    if (true == SAFE_PTR(Bitmap))
    {
        Bitmap->Canvas->Font->Assign(Font);
        int iWidth  = Bitmap->Canvas->TextWidth(sText);
        int iHeight = Bitmap->Canvas->TextHeight(sText);
        Bitmap->Width                = iWidth;
        Bitmap->Height               = iHeight;
        Bitmap->PixelFormat          = pf8bit;
        Bitmap->Canvas->Font->Color  = clWhite;
        Bitmap->Canvas->Pen->Color   = clWhite;
        Bitmap->Canvas->Brush->Color = clBlack;
        Bitmap->Canvas->FillRect(Rect(0, 0, iWidth, iHeight));
        Bitmap->Canvas->TextOut(0, 0, sText);
        for (int y = 0; y < iHeight; ++y)
        {
            unsigned char* ScanLine = (unsigned char*)Bitmap->ScanLine[y];
            for (int x = 0; x < iWidth; ++x)
            {
                if (ScanLine[x])
                {
                    DrawPoint(X + x, Y + y);
                }
            }
        }
        SAFE_DELETE(Bitmap);
    }
    m_bIsDirty = true;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::ReDraw(void)
{
    Invalidate();
    AddRect(m_rBlitRect);
    DrawImage();
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::Draw(TCanvas* Canvas, int iMagnification)
{
    bool bDrawn = false;
    TRect BlitRect;
    if (m_rBlitRect.Left < m_rBlitRect.Right && m_rBlitRect.Top < m_rBlitRect.Bottom)
    {
        BlitRect.Left   = std::max(0L             , std::min(m_rBlitRect.Left  , m_rLastBlitRect.Left  ));
        BlitRect.Top    = std::max(0L             , std::min(m_rBlitRect.Top   , m_rLastBlitRect.Top   ));
        BlitRect.Right  = std::min((long)m_iWidth , std::max(m_rBlitRect.Right , m_rLastBlitRect.Right ));
        BlitRect.Bottom = std::min((long)m_iHeight, std::max(m_rBlitRect.Bottom, m_rLastBlitRect.Bottom));
        //RL_DEBUG("Drawing Blit Rect: " + AnsiString(BlitRect.Left) + ", " + AnsiString(BlitRect.Top) + ", " + AnsiString(BlitRect.Right) + ", " + AnsiString(BlitRect.Bottom))
        //RL_DEBUG("Last    Blit Rect: " + AnsiString(m_rLastBlitRect.Left) + ", " + AnsiString(m_rLastBlitRect.Top) + ", " + AnsiString(m_rLastBlitRect.Right) + ", " + AnsiString(m_rLastBlitRect.Bottom))

        int iBlitWidth  = BlitRect.Right  - BlitRect.Left;
        int iBlitHeight = BlitRect.Bottom - BlitRect.Top;

        //PERFORMANCE_PUSH
        // stretch blit the image onto the larger canvas
        StretchBlt
        (
            Canvas->Handle,
            (BlitRect.Left) * iMagnification * (m_pPalette->ScalarX / m_fModeScaleX),
            (BlitRect.Top ) * iMagnification * (m_pPalette->ScalarY / m_fModeScaleY),
            (iBlitWidth   ) * iMagnification * (m_pPalette->ScalarX / m_fModeScaleX),
            (iBlitHeight  ) * iMagnification * (m_pPalette->ScalarY / m_fModeScaleY),
            m_bMaskMode ? m_pMaskImage->Canvas->Handle : m_pImage->Canvas->Handle,
            //m_pImage->Canvas->Handle,
            BlitRect.Left,
            BlitRect.Top ,
            iBlitWidth   ,
            iBlitHeight  ,
            SRCCOPY
        );
        //PERFORMANCE_POP("TZXImage::Show - Blit")
        m_rLastBlitRect    = BlitRect;
        // reset the dirty rect
        m_rBlitRect.Left   = m_iWidth;
        m_rBlitRect.Top    = m_iHeight;
        m_rBlitRect.Right  = 0;
        m_rBlitRect.Bottom = 0;
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::Draw(TCanvas* Canvas, int iMagnification, const TRect& UpdateRect)
{
    bool bDrawn = false;
    if (UpdateRect.Left < UpdateRect.Right && UpdateRect.Top < UpdateRect.Bottom)
    {
        int iBlitWidth  = UpdateRect.Right  - UpdateRect.Left;
        int iBlitHeight = UpdateRect.Bottom - UpdateRect.Top;
        //PERFORMANCE_PUSH
        // stretch blit the image onto the larger canvas
        StretchBlt
        (
            Canvas->Handle,
            (UpdateRect.Left) * iMagnification * (m_pPalette->ScalarX / m_fModeScaleX),
            (UpdateRect.Top ) * iMagnification * (m_pPalette->ScalarY / m_fModeScaleY),
            (iBlitWidth     ) * iMagnification * (m_pPalette->ScalarX / m_fModeScaleX),
            (iBlitHeight    ) * iMagnification * (m_pPalette->ScalarY / m_fModeScaleY),
            m_bMaskMode ? m_pMaskImage->Canvas->Handle : m_pImage->Canvas->Handle,
            //m_pImage->Canvas->Handle,
            UpdateRect.Left,
            UpdateRect.Top ,
            iBlitWidth     ,
            iBlitHeight    ,
            SRCCOPY
        );
        //PERFORMANCE_POP("TZXImage::Show - Blit")
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::Draw(TCanvas* Canvas, int iMagnification, int X, int Y)
{
    bool bDrawn = false;
    TRect BlitRect;
    if (m_rBlitRect.Left < m_rBlitRect.Right && m_rBlitRect.Top < m_rBlitRect.Bottom)
    {
        BlitRect.Left   = std::max(0L             , std::min(m_rBlitRect.Left  , m_rLastBlitRect.Left  ));
        BlitRect.Top    = std::max(0L             , std::min(m_rBlitRect.Top   , m_rLastBlitRect.Top   ));
        BlitRect.Right  = std::min((long)m_iWidth , std::max(m_rBlitRect.Right , m_rLastBlitRect.Right ));
        BlitRect.Bottom = std::min((long)m_iHeight, std::max(m_rBlitRect.Bottom, m_rLastBlitRect.Bottom));
        //RL_DEBUG("Drawing Blit Rect: " + AnsiString(BlitRect.Left) + ", " + AnsiString(BlitRect.Top) + ", " + AnsiString(BlitRect.Right) + ", " + AnsiString(BlitRect.Bottom))
        //RL_DEBUG("Last    Blit Rect: " + AnsiString(m_rLastBlitRect.Left) + ", " + AnsiString(m_rLastBlitRect.Top) + ", " + AnsiString(m_rLastBlitRect.Right) + ", " + AnsiString(m_rLastBlitRect.Bottom))

        int iBlitWidth  = BlitRect.Right  - BlitRect.Left;
        int iBlitHeight = BlitRect.Bottom - BlitRect.Top;
        //PERFORMANCE_PUSH
        // stretch blit the image onto the larger canvas
        StretchBlt
        (
            Canvas->Handle,
            X,
            Y,
            iBlitWidth  * iMagnification * (m_pPalette->ScalarX / m_fModeScaleX),
            iBlitHeight * iMagnification * (m_pPalette->ScalarY / m_fModeScaleY),
            m_pImage->Canvas->Handle,
            BlitRect.Left,
            BlitRect.Top ,
            iBlitWidth   ,
            iBlitHeight  ,
            SRCCOPY
        );
        //PERFORMANCE_POP("TZXImage::Show - Blit")
        m_rLastBlitRect    = BlitRect;
        // reset the dirty rect
        m_rBlitRect.Left   = m_iWidth;
        m_rBlitRect.Top    = m_iHeight;
        m_rBlitRect.Right  = 0;
        m_rBlitRect.Bottom = 0;
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::DrawMask(TCanvas* Canvas, int X, int Y, TColor MaskColor)
{
    bool bDrawn = false;
    if (IsMasked)
    {
        unsigned char masks[8] =
        {
            0x80,
            0x40,
            0x20,
            0x10,
            0x08,
            0x04,
            0x02,
            0x01
        };
        for (int y = 0; y < Height; y++)
        {
            int row = y * (Width >> 3); 
            for (int x = 0; x < Width; x++)
            {
                int mx = x >> 3;
                if (!(m_pMaskBuffer[row + mx] & masks[x % 8]))
                {
                    Canvas->Pixels[x][y] = MaskColor;
                }
            }
        }
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::Draw(TCanvas* Canvas)
{
    //PERFORMANCE_PUSH
    // stretch blit the image onto the larger canvas
    BitBlt
    (
        Canvas->Handle,
        0,
        0,
        Width,
        Height,
        m_bMaskMode ? m_pMaskImage->Canvas->Handle : m_pImage->Canvas->Handle,
        //m_pImage->Canvas->Handle,
        0,
        0,
        SRCCOPY
    );
    return true;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::Delete(const TRect& Rect)
{
    m_bIsDirty = true;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::Invalidate(void)
{
    // invalidates the update rect, so it updates the entire image next time
    m_rBlitRect.Left   = 0;
    m_rBlitRect.Top    = 0;
    m_rBlitRect.Right  = m_iWidth;
    m_rBlitRect.Bottom = m_iHeight;
    m_vDirtyRects.clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::Invalidate(const TRect& Rect)
{
    // merges the update rects together
    m_rBlitRect.Left   = std::min(std::min(m_rBlitRect.Left  , Rect.Left  ), Rect.Right );
    m_rBlitRect.Right  = std::max(std::max(m_rBlitRect.Right , Rect.Right ), Rect.Left  );
    m_rBlitRect.Top    = std::min(std::min(m_rBlitRect.Top   , Rect.Top   ), Rect.Bottom);
    m_rBlitRect.Bottom = std::max(std::max(m_rBlitRect.Bottom, Rect.Bottom), Rect.Top   );
    //RL_DEBUG("Blit Rect: " + AnsiString(m_rBlitRect.Left) + ", " + AnsiString(m_rBlitRect.Top) + ", " + AnsiString(m_rBlitRect.Right) + ", " + AnsiString(m_rBlitRect.Bottom))
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::GetMaskMode(void) const
{
    return m_bMaskMode;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::SetMaskMode(bool bNewMaskMode)
{
    // can only change the mask mode if the image is masked and when no drawing is occurring
    if (true == m_bIsMasked && 0 == m_iDrawInitializeCount)
    {
        m_bMaskMode = bNewMaskMode & m_bIsMasked;
        Invalidate();
        m_bIsDirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::SetHotSpotMode(bool bNewMode)
{
    // can only change the mask mode if the image is masked and when no drawing is occurring
    if (UsesHotSpot && 0 == m_iDrawInitializeCount && m_bHotSpotMode != bNewMode)
    {
        m_bHotSpotMode = bNewMode;
        Invalidate();
        m_bIsDirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::SetMaskAlpha(float fAlpha)
{
    m_fMaskAlpha = fAlpha;
    if (true == m_bIsMasked && 0 == m_iDrawInitializeCount)
    {
        Invalidate();
        m_bIsDirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::SetMaskColor(TColor Color)
{
    m_MaskColor = Color;
    if (true == m_bIsMasked && 0 == m_iDrawInitializeCount)
    {
        Invalidate();
        m_bIsDirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::AllocateBuffers(void)
{
    // free the old buffers
    SAFE_DELETE(m_pImage);
    SAFE_DELETE(m_pBackupImage);
    SAFE_DELETE(m_pPixelBuffer);
    SAFE_DELETE(m_pBackupPixelBuffer);
    SAFE_DELETE(m_pMaskBuffer);
    SAFE_DELETE(m_pAttributeBuffer);
    // allocate new buffers
    m_pImage = new Graphics::TBitmap();
    if (true == m_bIsMasked)
    {
        m_pMaskImage = new Graphics::TBitmap();
    }
    if (true == SAFE_PTR(m_pPalette))
    {
        m_pImage->PixelFormat = m_pPalette->PixelFormat;
    }
    m_pImage->Width  = m_iWidth;
    m_pImage->Height = m_iHeight;
    if (true == SAFE_PTR(m_pMaskImage))
    {
        m_pMaskImage->PixelFormat = m_pPalette->PixelFormat;
        m_pMaskImage->Width       = m_iWidth;
        m_pMaskImage->Height      = m_iHeight;
    }
    m_pImage->Canvas->Brush->Color = clBlack;   //(TColor)m_pPalette;
    m_pImage->Canvas->FillRect(TRect(0, 0, m_iWidth, m_iHeight));
    m_pBackupImage = new Graphics::TBitmap();
    m_pBackupImage->PixelFormat = SAFE_PTR(m_pPalette) ? m_pPalette->PixelFormat : pf1bit;
    m_pBackupImage->Width  = m_iWidth;
    m_pBackupImage->Height = m_iHeight;
    //m_pImage->PixelFormat = pfDevice;
    m_pPixelBuffer = new unsigned char[m_iPixelBufferSize];
    ZeroMemory(m_pPixelBuffer, m_iPixelBufferSize);
    m_pBackupPixelBuffer = new unsigned char[m_iPixelBufferSize];
    if (true == m_bIsMasked)
    {
        m_pBackupMaskBuffer = new unsigned char[m_iMaskBufferSize];
        m_pMaskBuffer = new unsigned char[m_iMaskBufferSize];
        ZeroMemory(m_pMaskBuffer, m_iMaskBufferSize);
    }
    if (0 != m_iAttributeBufferSize)
    {
        m_pBackupAttributeBuffer = new unsigned char[m_iAttributeBufferSize];
        m_pAttributeBuffer = new unsigned char[m_iAttributeBufferSize];
        ZeroMemory(m_pAttributeBuffer, m_iAttributeBufferSize);
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::Save(KXmlInfo& xmlInfo, bool bClearDirty)
{
    String xmlString;
    xmlInfo.Add("Name", Name);
    xmlInfo.Add("Palette", Palette->Name);
    xmlInfo.Add("SubType", SubType);
    xmlInfo.Add("Width", Width);
    xmlInfo.Add("Height", Height);
    xmlInfo.Add("IsMasked", IsMasked);
    xmlInfo.Add("MaskMode", MaskMode);
    xmlInfo.Add("MaskAlpha", MaskAlpha);
    xmlInfo.Add("MaskColor", MaskColor);
    xmlInfo.Add("HotSpotX", HotSpotX);
    xmlInfo.Add("HotSpotY", HotSpotY);
    GetXmlData(xmlString);
    xmlInfo.Add("Pixels", xmlString);
    if (Attributes)
    {
        GetXmlData(xmlString, xmlAttributes);
        xmlInfo.Add("Attributes", xmlString);
    }
    if (IsMasked)
    {
        GetXmlData(xmlString, xmlMasks);
        xmlInfo.Add("Masks", xmlString);
    }
    if (bClearDirty)
    {
        m_bIsDirty = false;
    }
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::Load(KXmlInfo& xmlInfo, bool bClearDirty, const String& sVersion)
{
    String xmlString;
    KXmlInfo* node = xmlInfo.GetNode("Name");
    if (SAFE_PTR(node)) Name = node->GetText();
    node = xmlInfo.GetNode("MaskMode");
    if (SAFE_PTR(node)) MaskMode = node->GetBool();
    node = xmlInfo.GetNode("MaskAlpha");
    if (SAFE_PTR(node)) MaskAlpha = node->GetDouble();
    node = xmlInfo.GetNode("MaskColor");
    if (SAFE_PTR(node)) MaskColor = (TColor)node->GetUInt();
    node = xmlInfo.GetNode("HotSpotX");
    if (SAFE_PTR(node)) HotSpotX = node->GetInt();
    node = xmlInfo.GetNode("HotSpotY");
    if (SAFE_PTR(node)) HotSpotY = node->GetInt();
    node = xmlInfo.GetNode("SubType");
    if (SAFE_PTR(node)) SubType = node->GetInt();

    m_iPixelBufferSize = Palette->CalculatePixelBufferSize(Width, Height);
    if (true == IsMasked)
    {
        //int iPixelsPerByte = m_pPalette->PixelsPerByte;
        m_iMaskBufferSize = (Width % 8 == 0 ? (Width / 8) : (Width / 8) + 1) * Height;
        //m_iMaskBufferSize = Width % iPixelsPerByte == 0 ? (Width / iPixelsPerByte) * Height : ((Width / iPixelsPerByte) + 1) * Height;
    }
    if (false == Palette->SupportsPixelsOnly)
    {
        m_iAttributeBufferSize = Palette->CalculateAttributeBufferSize(Width, Height);
    }
    AllocateBuffers();

    node = xmlInfo.GetNode("Pixels");
    if (SAFE_PTR(node)) SetXmlData(node->GetText());
    if (Attributes)
    {
        node = xmlInfo.GetNode("Attributes");
        if (SAFE_PTR(node)) SetXmlData(node->GetText(), xmlAttributes);
    }
    if (IsMasked)
    {
        node = xmlInfo.GetNode("Masks");
        if (SAFE_PTR(node)) SetXmlData(node->GetText(), xmlMasks);
    }

    if (bClearDirty)
    {
        m_bIsDirty = false;
    }
    // apply any palette bug fixes
    Palette->ApplyFix(sVersion, this);
    // todo: apply any image bug fixes here
    return true;
}
//---------------------------------------------------------------------------
String __fastcall ZXImage::Signature(void) const
{
    String sSignature = "";
    if (true == SAFE_PTR(m_pPalette))
    {
        sSignature = m_pPalette->Signature;
    }
    return sSignature;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::AddRect(const TRect& DirtyRect)
{
    //RL_DEBUG("Add Rect: " + AnsiString(DirtyRect.Left) + ", " + AnsiString(DirtyRect.Top) + ", " + AnsiString(DirtyRect.Right) + ", " + AnsiString(DirtyRect.Bottom))
    int iLastRect = m_vDirtyRects.size() - 1;
    Invalidate(DirtyRect);
    for (unsigned int i = iLastRect; i < m_vDirtyRects.size(); --i)
    {
        if (m_vDirtyRects[i] == DirtyRect)
        {
            // this is naughty, but its faster than waiting to exit through the end of function
            return;
        }
    }
    m_vDirtyRects.push_back(DirtyRect);
}
//---------------------------------------------------------------------------
int __fastcall ZXImage::Rects(void)
{
    return m_vDirtyRects.size();
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::GetRect(unsigned int iIndex, TRect& Rect)
{
    if (iIndex < m_vDirtyRects.size())
    {
        Rect = m_vDirtyRects[iIndex];
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::SetSelectionRect(const TRect& Rect)
{
    m_rSelectionRect.Left   = std::max(0L          , Rect.Left  );
    m_rSelectionRect.Top    = std::max(0L          , Rect.Top   );
    m_rSelectionRect.Right  = std::min((long)Width , Rect.Right );
    m_rSelectionRect.Bottom = std::min((long)Height, Rect.Bottom);
}
//---------------------------------------------------------------------------
TRect __fastcall ZXImage::GetSelectionRect(void)
{
    return m_rSelectionRect;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::PtInRect(int iX, int iY)
{
    bool bPtInRect = true;
    if (m_rSelectionRect.Top != m_rSelectionRect.Bottom || m_rSelectionRect.Left != m_rSelectionRect.Bottom)
    {
        bPtInRect = (m_rSelectionRect.Left <= iX && iX < m_rSelectionRect.Right && m_rSelectionRect.Top <= iY && iY < m_rSelectionRect.Bottom);
    }
    return bPtInRect;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::PaletteGetColor(int X, int Y)
{
    Palette->GetColorAt(*this, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::PaletteSetColor(int X, int Y)
{
    Palette->SetColorAt(*this, X, Y);
}
//---------------------------------------------------------------------------
TRect __fastcall ZXImage::GetDirtyRect(void)
{
    TRect Rect;
    Rect.Left   = std::max(0L             , std::min(m_rBlitRect.Left  , m_rLastBlitRect.Left  ));
    Rect.Top    = std::max(0L             , std::min(m_rBlitRect.Top   , m_rLastBlitRect.Top   ));
    Rect.Right  = std::min((long)m_iWidth , std::max(m_rBlitRect.Right , m_rLastBlitRect.Right ));
    Rect.Bottom = std::min((long)m_iHeight, std::max(m_rBlitRect.Bottom, m_rLastBlitRect.Bottom));
    TRect DirtyRect;
    DirtyRect.Left   = std::min(Rect.Left, Rect.Right );
    DirtyRect.Right  = std::max(Rect.Left, Rect.Right );
    DirtyRect.Top    = std::min(Rect.Top , Rect.Bottom);
    DirtyRect.Bottom = std::max(Rect.Top , Rect.Bottom);
    return DirtyRect;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::GetXmlData(String& xmlString, XmlData xmlData)
{
    unsigned char* data = m_pPixelBuffer;
    unsigned long  size = m_iPixelBufferSize;
    if (xmlAttributes == xmlData)
    {
        data = m_pAttributeBuffer;
        size = m_iAttributeBufferSize;
    }
    else if (xmlMasks == xmlData)
    {
        data = m_pMaskBuffer;
        size = m_iMaskBufferSize;
    }

    xmlString = "";
    for (unsigned int i = 0; i < size; i++)
    {
        xmlString += (char)('A' + (data[i] >>   4));
        xmlString += (char)('A' + (data[i] & 0x0F));
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::SetXmlData(const String& xmlString, XmlData xmlData)
{
    bool bSet = false;
    unsigned char* data = m_pPixelBuffer;
    unsigned long  size = m_iPixelBufferSize;
    if (xmlAttributes == xmlData)
    {
        data = m_pAttributeBuffer;
        size = m_iAttributeBufferSize;
    }
    else if (xmlMasks == xmlData)
    {
        data = m_pMaskBuffer;
        size = m_iMaskBufferSize;
    }

    if ((unsigned int)xmlString.Length() / 2 == size)
    {
        // ok, the string is the correct size to fit the buffer
        for (unsigned int i = 0; i < size; i++)
        {
            data[i] = ((xmlString[i * 2 + 1] - 'A') << 4) | (xmlString[i * 2 + 2] - 'A');
        }
        bSet = true;
    }
    return bSet;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::ConvertBitmap(Graphics::TBitmap* Bitmap)
{
    bool bResult = false;
    if (true == SAFE_PTR(m_pPalette))
    {
        bResult = m_pPalette->ConvertBitmap(this, Bitmap);
        ReDraw();
        m_bIsDirty = true;
    }
    return bResult;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::ConvertBitmapMask(Graphics::TBitmap* Bitmap, TColor MaskColor)
{
    bool bResult = true;
    if (m_bIsMasked)
    {
        bool MaskMode = m_bMaskMode;
        for (int y = 0; y < m_iHeight; ++y)
        {
            for (int x = 0; x < m_iWidth; ++x)
            {
                m_bMaskMode = true;
                DrawPoint(x, y, Bitmap->Canvas->Pixels[x][y] == MaskColor);
                m_bMaskMode = false;
                if (Bitmap->Canvas->Pixels[x][y] == MaskColor)
                {
                    DrawPoint(x, y, false);
                }
            }
        }
        m_bMaskMode = MaskMode;
        ReDraw();
        m_bIsDirty = true;
        bResult = true;
    }
    return bResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::Resize(int iLeft, int iTop, int iNewWidth, int iNewHeight)
{
    if (m_bCanResize)
    {
        bool bOldMaskMode = m_bMaskMode;
        m_bMaskMode = false;
        ReDraw();
        Graphics::TBitmap* curBmp = new Graphics::TBitmap();    // current bitmap
        Graphics::TBitmap* newBmp = new Graphics::TBitmap();    // new resized bitmap
        Graphics::TBitmap* nmkBmp = NULL;                       // new resized mask bitmap
        if (m_bIsMasked)
        {
            // draw the mask image and copy it into the new mask bitmap in the resized position
            DrawMask(false);
            nmkBmp = new Graphics::TBitmap();
            nmkBmp->Width  = iNewWidth;
            nmkBmp->Height = iNewHeight;
            newBmp->PixelFormat = m_pMaskImage->PixelFormat;
            nmkBmp->Canvas->Brush->Color = clBlack;
            nmkBmp->Canvas->FillRect(TRect(0, 0, iNewWidth, iNewHeight));
            BitBlt
            (
                nmkBmp->Canvas->Handle,
                iLeft,
                iTop,
                Width,
                Height,
                m_pMaskImage->Canvas->Handle,
                0,
                0,
                SRCCOPY
            );
        }
        if (true == SAFE_PTR(curBmp) && true == SAFE_PTR(newBmp))
        {
            // get the image into a tmp bitmap
            curBmp->PixelFormat = Palette->PixelFormat;
            curBmp->Width  = Width;
            curBmp->Height = Height;
            Draw(curBmp->Canvas);
            newBmp->PixelFormat = Palette->PixelFormat;
            newBmp->Width  = iNewWidth;
            newBmp->Height = iNewHeight;
            newBmp->Canvas->Brush->Color = Palette->BrushColor;
            newBmp->Canvas->FillRect(TRect(0, 0, iNewWidth, iNewHeight));
            // paste the paste object into the tmp bitmap
            BitBlt
            (
                newBmp->Canvas->Handle,
                iLeft,
                iTop,
                Width,
                Height,
                curBmp->Canvas->Handle,
                0,
                0,
                SRCCOPY
            );
            // make the image convert the new pasted image
            ResizeBuffers(iNewWidth, iNewHeight);
            if (m_bIsMasked)
            {
                ConvertBitmapMask(nmkBmp, MaskColor);
                SAFE_DELETE(nmkBmp);
            }
            ConvertBitmap(newBmp);
            SAFE_DELETE(curBmp);
            SAFE_DELETE(newBmp);
            Invalidate();
        }
        m_bMaskMode = bOldMaskMode;
        ReDraw();
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::ResizeBuffers(int iWidth, int iHeight)
{
    FreeBuffers();
    int iMinWidth = 8;      // 8 pixels
    if (m_pPalette->PixelsPerByte > 0)
    {
        // 8 pixels or less
        iMinWidth = (int)(8.0f / m_pPalette->PixelsPerByte);
    }
    else
    {
        // larger than 8 bits per pixel
        iMinWidth = (int)(1.0f / m_pPalette->PixelsPerByte);
    }
    
    m_iWidth  = std::max(iMinWidth, std::min(1024, iWidth ));
    m_iHeight = std::max(4        , std::min(1024, iHeight));

    m_rSelectionRect = TRect(0 ,0 ,0 ,0);
    m_rLastBlitRect  = TRect(32,32,0 ,0);
    m_iPixelBufferSize = Palette->CalculatePixelBufferSize(iWidth, iHeight);
    if (true == m_bIsMasked)
    {
        m_iMaskBufferSize = (Width % 8 == 0 ? (Width / 8) : (Width / 8) + 1) * Height;
        //m_iMaskBufferSize = iWidth % iPixelsPerByte == 0 ? (m_iWidth / iPixelsPerByte) * iHeight : ((m_iWidth / iPixelsPerByte) + 1) * iHeight;
    }
    if (false == Palette->SupportsPixelsOnly)
    {
        m_iAttributeBufferSize = Palette->CalculateAttributeBufferSize(iWidth, iHeight);
    }
    AllocateBuffers();
    ReDraw();
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::FreeBuffers(void)
{
    SAFE_DELETE(m_pPixelBuffer);
    SAFE_DELETE(m_pBackupPixelBuffer);
    SAFE_DELETE(m_pAttributeBuffer);
    SAFE_DELETE(m_pBackupAttributeBuffer);
    SAFE_DELETE(m_pMaskBuffer);
    SAFE_DELETE(m_pBackupMaskBuffer);
    SAFE_DELETE(m_pMaskImage);
    SAFE_DELETE(m_pImage);
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::InvertMask(void)
{
    if (IsMasked)
    {
        for (unsigned int i = 0; i < m_iMaskBufferSize; i++)
        {
            m_pMaskBuffer[i] = ~m_pMaskBuffer[i];
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::GenerateMask(int BorderStyle, int iPaletteIndex)
{
    if (IsMasked)
    {
        bool MaskMode = m_bMaskMode;
        m_bMaskMode = false;
        DrawImage();
        m_bMaskMode = true;
        // clear the mask
        ZeroMemory(m_pMaskBuffer, m_iMaskBufferSize);
        // create the masks
        TColor BackColor = m_pPalette->GetColor(iPaletteIndex);
        for (int y = 0; y < m_iHeight; y++)
        {
            for (int x = 0; x < m_iWidth; x++)
            {
                TColor ForeColor = m_pImage->Canvas->Pixels[x][y];
                if (ForeColor != BackColor)
                {
                    DrawPoint(x, y, true);
                    if (BorderStyle)
                    {
                        DrawPoint(x+0, y-1, true);
                        DrawPoint(x-1, y+0, true);
                        DrawPoint(x+1, y+0, true);
                        DrawPoint(x+0, y+1, true);
                    }
                    if (BorderStyle == 2)
                    {
                        DrawPoint(x-1, y-1, true);
                        DrawPoint(x+1, y-1, true);
                        DrawPoint(x-1, y+1, true);
                        DrawPoint(x+1, y+1, true);
                    }
                }
            }
        }
        m_bMaskMode = MaskMode;
        DrawImage();
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXImage::GetUsesHotSpot(void)
{
    return m_iHotSpotX >= 0 || m_iHotSpotY >= 0;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::SetBackgroundColor(TColor color)
{
    g_BackgroundColor = color;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::SetTransparentColor(TColor color)
{
    g_TransparentColor = color;
}
//---------------------------------------------------------------------------
void __fastcall ZXImage::SetTransparentMode(bool mode)
{
    g_bTransparentMode = mode;
}
//---------------------------------------------------------------------------

