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
using namespace CPCMode0Palette;
//---------------------------------------------------------------------------
unsigned char g_iPixelMasks[] =
{
    0xF0,
    0x0F,
};
//---------------------------------------------------------------------------
const TColor g_Colors[27] =
{
            clBlack   ,
            clNavy    ,
            clBlue    ,
            clMaroon  ,
            clPurple  ,
    (TColor)0x00FF0080,
            clRed     ,
    (TColor)0x008000FF,
            clFuchsia ,
            clGreen   ,
            clTeal    ,
    (TColor)0x00FF8000,
            clOlive   ,
            clGray    ,
    (TColor)0x00FF8080,
    (TColor)0x000080FF,
    (TColor)0x008080FF,
    (TColor)0x00FF80FF,
            clLime    ,
    (TColor)0x0080FF00,
            clAqua    ,
    (TColor)0x0000FF80,
    (TColor)0x0080FF80,
    (TColor)0x00FFFF80,
            clYellow  ,
    (TColor)0x0080FFFF,
            clWhite
};
//---------------------------------------------------------------------------
__fastcall Mode0Palette::Mode0Palette()
: ZXPalette(16, 160, 200, true),
  m_iColor(1)
{
    PalSignature(m_sSignature);
    Initialize();
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::Initialize(void)
{
    m_PixelFormat               = pf32bit;
    // initialize our palette information
    m_iBitsPerPixel             = 4;
    m_iBitsPerAttribute         = 1;
    m_iPixelsWidePerAttribute   = 1;
    m_iPixelsHighPerAttribute   = 1;
    m_fScalarX                  = 2.f;
    m_fPixelsPerByte            = 2.f;
    m_bSupportsPixelsOnly       = true;
    // normally we would initialize the color table
    Reset();
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::SetColor(unsigned char iColor)
{
    if (iColor < 16)
    {
        m_iColor = iColor;
        m_ColorPen = GetColor(iColor);
    }
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::SetTableColor(unsigned char iColor, TColor Color)
{
    if (iColor < 16)
    {
        ZXPalette::SetColor(iColor, Color);
    }
}
//---------------------------------------------------------------------------
unsigned char __fastcall Mode0Palette::GetColor(void)
{
    return m_iColor;
}
//---------------------------------------------------------------------------
TColor __fastcall Mode0Palette::GetColor(unsigned char iColor)
{
    return ZXPalette::GetColor(iColor);
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::SetColorAt(ZXImage& Image, int X, int Y)
{
    Write(X, Y, true, Image);
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::GetColorAt(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iPixelsPerByte        = 2;
        int iBytesWide            = CalculateStride(Image.Width);
        int iByteX                = X / iPixelsPerByte;
        unsigned int PixelOffset  = (Y * iBytesWide) + iByteX;
        // set the appropreiate pixel bits
        unsigned char cPixelPos   = X % iPixelsPerByte;
        unsigned char cPixels     = Image.Pixels[PixelOffset] & g_iPixelMasks[cPixelPos];
        unsigned char cPixelShifts= 4 - (cPixelPos << 2);
        m_iColor = (cPixels >> cPixelShifts) & 0x0F;
        if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // dirty the character block
    int dX = X & 0xFE;
    TRect Rect(dX, Y, dX + 2, Y + 1);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, m_iColor, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
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
                Bitmap->Canvas->Pixels[x+0][y] = GetColor((Pixels >> 4) & 0x0F);
                Bitmap->Canvas->Pixels[x+1][y] = GetColor((Pixels     ) & 0x0F);
            }
        }
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::SetPixel(int iX, int iY, unsigned char iColor, bool bSet, ZXImage& Image)
{
    //PERFORMANCE_PUSH
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iPixelsPerByte        = 2;
        int iBytesWide            = CalculateStride(Image.Width);
        int iByteX                = iX / iPixelsPerByte;
        unsigned int PixelOffset  = (iY * iBytesWide) + iByteX;
        // set the appropreiate pixel bits
        unsigned char cPixelPos   = iX % iPixelsPerByte;
        unsigned char cColorValue = (iColor & 0x0F) << 4;
        cColorValue >>= (cPixelPos * 4);
        // reset the pixel bits
        Image.Pixels[PixelOffset] &= ~g_iPixelMasks[cPixelPos];
        if (true == bSet && cColorValue)
        {
            Image.Pixels[PixelOffset] |= cColorValue;
        }
    }
    //PERFORMANCE_POP(__FUNC__)
}
//---------------------------------------------------------------------------
String __fastcall Mode0Palette::GetColorAsString(ZXImage& Image, int X, int Y)
{
    String sColor("None");
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iColX = X >> 3;
        // assign any transparent attributes
        unsigned int PixelOffset   = (Y * iCols) + iColX;
        // set the appropreiate pixels and attribute
        unsigned char cPixelBit    = ((X % 8) >> 2);
        unsigned char cPixels      = Image.Pixels[PixelOffset] & g_iPixelMasks[cPixelBit];
        unsigned char cPixelShifts = cPixelBit << 2;
        int iColor = (cPixels >> cPixelShifts) & 0x0F;
        sColor  = IntToStr(iColor);
    }
    return sColor;
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::Reset(void)
{
    ZXPalette::SetColor( 0, g_Colors[ 1]);
    ZXPalette::SetColor( 1, g_Colors[24]);
    ZXPalette::SetColor( 2, g_Colors[20]);
    ZXPalette::SetColor( 3, g_Colors[ 6]);
    ZXPalette::SetColor( 4, g_Colors[26]);
    ZXPalette::SetColor( 5, g_Colors[ 0]);
    ZXPalette::SetColor( 6, g_Colors[ 2]);
    ZXPalette::SetColor( 7, g_Colors[ 8]);
    ZXPalette::SetColor( 8, g_Colors[10]);
    ZXPalette::SetColor( 9, g_Colors[12]);
    ZXPalette::SetColor(10, g_Colors[14]);
    ZXPalette::SetColor(11, g_Colors[16]);
    ZXPalette::SetColor(12, g_Colors[18]);
    ZXPalette::SetColor(13, g_Colors[22]);
    ZXPalette::SetColor(14, g_Colors[ 1]);
    ZXPalette::SetColor(15, g_Colors[16]);
    SetColor(1);
}
//---------------------------------------------------------------------------
void __fastcall Mode0Palette::Loaded(void)
{
    frmCPCMode0Palette->RefreshPanels();
}
//---------------------------------------------------------------------------

