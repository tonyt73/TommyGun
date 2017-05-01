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
#include "pch.h"
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
//using namespace Imaging;
using namespace EnterprisePalette;
//---------------------------------------------------------------------------
__fastcall Enterprise256Palette::Enterprise256Palette()
: ZXPalette(256, 80, 256, false)
, m_iPen(1)
, m_iBrush(0)
{
    PalSignature(m_sSignature);
    Initialize();
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::Initialize(void)
{
    m_PixelFormat               = pf32bit;
    // initialize our palette information
    m_iBitsPerPixel             = 8;
    m_iBitsPerAttribute         = 8;
    m_iPixelsWidePerAttribute   = 1;
    m_iPixelsHighPerAttribute   = 1;
    m_fScalarX                  = 4.f;
    m_fPixelsPerByte            = 1.f;
    m_bSupportsPixelsOnly       = true;
    // normally we would initialize the color table
    Reset();
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::SetColorAt(ZXImage& Image, int X, int Y)
{
    Write(X, Y, true, Image);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::SetPen(unsigned char iColor)
{
    m_iPen       = iColor;
    m_ColorPen   = GetColor(iColor);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::SetBrush(unsigned char iColor)
{
    m_iBrush     = iColor;
    m_ColorBrush = GetColor(iColor);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::GetColorAt(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iBytesWide            = CalculateStride(Image.Width);
        unsigned int PixelOffset  = (Y * iBytesWide) + X;
        // set the appropreiate pixel bits
        m_iPen                    = Image.Pixels[PixelOffset];
        if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    TRect Rect(X, Y, X + 1, Y + 1);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
{
    //PERFORMANCE_PUSH
    // loop through the character block and set all the ink and paper values
    Bitmap->PixelFormat = pf32bit;
    TRect UpdateRect;
    int iRects = Image.Rects();
    int iCols = CalculateStride(Image.Width);
    for (int rect = 0; rect < iRects; ++rect)
    {
        Image.GetRect(rect, UpdateRect);
        for (int y = UpdateRect.Top; y < UpdateRect.Bottom; ++y)
        {
            for (int x = UpdateRect.Left; x < UpdateRect.Right; x += m_fPixelsPerByte)
            {
                int iCX = x / m_fPixelsPerByte;
                unsigned char Pixels = Image.Pixels[(y * iCols) + iCX];
                Bitmap->Canvas->Pixels[x][y] = GetColor(Pixels);
            }
        }
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::SetPixel(int iX, int iY, bool bSet, ZXImage& Image)
{
    //PERFORMANCE_PUSH
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        unsigned int PixelOffset  = (iY * CalculateStride(Image.Width)) + iX;
        // set the appropreiate pixel bits
        Image.Pixels[PixelOffset] = bSet ? m_iPen : m_iBrush;
    }
    //PERFORMANCE_POP(__FUNC__)
}
//---------------------------------------------------------------------------
String __fastcall Enterprise256Palette::GetColorAsString(ZXImage& Image, int X, int Y)
{
    String sColor("None");
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        // assign any transparent attributes
        unsigned int PixelOffset    = (Y * CalculateStride(Image.Width)) + X;
        // get the appropreiate pixels and attribute
        sColor  = IntToStr(Image.Pixels[PixelOffset]);
    }
    return sColor;
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::Reset(void)
{
    for (int i = 0; i < 256; i++)
    {
        SetColor( i, dlgEnterpriseColors->GetColor(i));
    }

    m_ColorPen   = GetColor(m_iPen);
    m_ColorBrush = GetColor(m_iBrush);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise256Palette::Loaded(void)
{
    frmEnterprise256Palette->OnUpdatePaletteGUI();
}
//---------------------------------------------------------------------------

