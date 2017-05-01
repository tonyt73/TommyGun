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
unsigned char g_iPixelMasks[] =
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
//---------------------------------------------------------------------------
__fastcall Enterprise2Palette::Enterprise2Palette()
: ZXPalette(2, 640, 256, true)
, m_iPen(1)
, m_iBrush(0)
{
    PalSignature(m_sSignature);
    Initialize();
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::Initialize(void)
{
    m_PixelFormat               = pf32bit;
    // initialize our palette information
    m_iBitsPerPixel             = 1;
    m_iBitsPerAttribute         = 1;
    m_iPixelsWidePerAttribute   = 1;
    m_iPixelsHighPerAttribute   = 1;
    m_fScalarX                  = 0.5f;
    m_fPixelsPerByte            = 8.f;
    m_bSupportsPixelsOnly       = true;
    // normally we would initialize the color table
    Reset();
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::SetPen(unsigned char iColor)
{
    m_iPen       = iColor;
    m_ColorPen   = GetColor(iColor);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::SetBrush(unsigned char iColor)
{
    m_iBrush     = iColor;
    m_ColorBrush = GetColor(iColor);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::SetTableColor(unsigned char iColor, TColor Color)
{
    if (iColor < 2)
    {
        ZXPalette::SetColor(iColor, Color);
    }
    m_ColorPen   = GetColor(m_iPen  );
    m_ColorBrush = GetColor(m_iBrush);
}
//---------------------------------------------------------------------------
TColor __fastcall Enterprise2Palette::GetColor(unsigned char iColor)
{
    return ZXPalette::GetColor(iColor);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::SetColorAt(ZXImage& Image, int X, int Y)
{
    Write(X, Y, true, Image);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::GetColorAt(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iPixelsPerByte        = 8;
        int iBytesWide            = CalculateStride(Image.Width);
        int iByteX                = X / iPixelsPerByte;
        unsigned int PixelOffset  = (Y * iBytesWide) + iByteX;
        // set the appropreiate pixel bits
        unsigned char cPixelPos   = X % iPixelsPerByte;
        unsigned char cPixels     = Image.Pixels[PixelOffset] & g_iPixelMasks[cPixelPos];
        m_iPen = (cPixels >> (7 - cPixelPos)) & 0x01;
        if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // dirty the character block
    int dX = X & 0xF8;
    TRect Rect(dX, Y, dX + 8, Y + 1);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
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
                Bitmap->Canvas->Pixels[x+0][y] = GetColor((Pixels >> 7) & 0x01);
                Bitmap->Canvas->Pixels[x+1][y] = GetColor((Pixels >> 6) & 0x01);
                Bitmap->Canvas->Pixels[x+2][y] = GetColor((Pixels >> 5) & 0x01);
                Bitmap->Canvas->Pixels[x+3][y] = GetColor((Pixels >> 4) & 0x01);
                Bitmap->Canvas->Pixels[x+4][y] = GetColor((Pixels >> 3) & 0x01);
                Bitmap->Canvas->Pixels[x+5][y] = GetColor((Pixels >> 2) & 0x01);
                Bitmap->Canvas->Pixels[x+6][y] = GetColor((Pixels >> 1) & 0x01);
                Bitmap->Canvas->Pixels[x+7][y] = GetColor((Pixels     ) & 0x01);
            }
        }
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::SetPixel(int iX, int iY, bool bSet, ZXImage& Image)
{
    //PERFORMANCE_PUSH
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iPixelsPerByte        = 8;
        int iBytesWide            = CalculateStride(Image.Width);
        int iByteX                = iX / iPixelsPerByte;
        unsigned int PixelOffset  = (iY * iBytesWide) + iByteX;
        // set the appropreiate pixel bits
        unsigned char cPixelPos   = iX % iPixelsPerByte;
        unsigned char cColorValue = ((bSet ? 1 : 0) & 0x01) << (7 - cPixelPos);
        //cColorValue >>= cPixelPos;
        // reset the pixel
        Image.Pixels[PixelOffset] &= ~g_iPixelMasks[cPixelPos];
        if (true == bSet && cColorValue)
        {
            Image.Pixels[PixelOffset] |= cColorValue;
        }
    }
    //PERFORMANCE_POP(__FUNC__)
}
//---------------------------------------------------------------------------
String __fastcall Enterprise2Palette::GetColorAsString(ZXImage& Image, int X, int Y)
{
    String sColor("None");
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iColX = X >> 3;
        // assign any transparent attributes
        unsigned int PixelOffset   = (Y * iCols) + iColX;
        // set the appropreiate pixels and attribute
        unsigned char cPixelBit    = X % 8;
        unsigned char cPixels      = Image.Pixels[PixelOffset] & g_iPixelMasks[cPixelBit];
        unsigned char cPixelShifts = cPixelBit;
        int iColor = (cPixels >> cPixelShifts) & 0x01;
        sColor  = IntToStr(iColor);
    }
    return sColor;
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::Reset(void)
{
    SetColor( m_iPen  , dlgEnterpriseColors->GetColor(1));
    SetColor( m_iBrush, dlgEnterpriseColors->GetColor(0));

    m_ColorPen   = GetColor(m_iPen  );
    m_ColorBrush = GetColor(m_iBrush);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise2Palette::Loaded(void)
{
    m_ColorPen   = GetColor(m_iPen  );
    m_ColorBrush = GetColor(m_iBrush);
    frmEnterprise2Palette->OnUpdatePaletteGUI();
}
//---------------------------------------------------------------------------

