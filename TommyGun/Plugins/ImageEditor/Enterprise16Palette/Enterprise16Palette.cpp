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
const   String  g_sPaletteName = "Enterprise 64/128 - 16 Colors";
//---------------------------------------------------------------------------
#define RED(x)   (((x & 1)<<2)+((x &  8)>>2)+((x &  64)>>6))
#define GREEN(x) (((x & 2)<<1)+((x & 16)>>3)+((x & 128)>>7))
#define BLUE(x)  (((x & 4)>>1)+((x & 32)>>5)               )
unsigned int Level_8[8] = { 0, 36,  73, 109, 146, 182, 218, 255 };
unsigned int Level_4[4] = { 0, 85, 170, 255                     };
//---------------------------------------------------------------------------
unsigned char g_iPixelMasks[] =
{
    0xF0,
    0x0F
};
//---------------------------------------------------------------------------
const TColor g_ConvertColors[16] =
{
            clBlack   ,
            clNavy    ,
            clMaroon  ,
            clPurple  ,
            clGreen   ,
            clTeal    ,
            clOlive   ,
            clSilver  ,
            clBlack   ,
            clBlue    ,
            clRed     ,
            clFuchsia ,
            clLime    ,
            clAqua    ,
            clYellow  ,
            clWhite
};
//---------------------------------------------------------------------------
const String g_sColors[16] =
{
    "$0",
    "$1",
    "$2",
    "$3",
    "$4",
    "$5",
    "$6",
    "$7",
    "$8",
    "$9",
    "$A",
    "$B",
    "$C",
    "$D",
    "$E",
    "$F"
};
//---------------------------------------------------------------------------
const   unsigned char   g_iInkMask      = 0x0F; // ink bits from attribute byte
const   unsigned char   g_iPaperMask    = 0xF0; // paper bits from attribute byte
//---------------------------------------------------------------------------
__fastcall Enterprise16Palette::Enterprise16Palette()
: ZXPalette(16, 320, 256),
  m_iColor(0)
{
    m_bCanConvert = true;
    PalSignature(m_sSignature);
    Initialize();
    m_ColorPen    = GetColor(m_iColor);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::Initialize(void)
{
    m_PixelFormat               = pf32bit;
    // initialize our palette information
    m_iBitsPerPixel             = 4;
    m_iBitsPerAttribute         = 8;
    m_iPixelsWidePerAttribute   = 8;
    m_iPixelsHighPerAttribute   = 1;
    m_fScalarX                  = 2.f;
    m_fPixelsPerByte            = 2.f;
    m_bSupportsPixelsOnly       = true;
    // normally we would initialize the color table
    Reset();
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::SetColor(unsigned char iColor)
{
    if (iColor < 16)
    {
        m_iColor = iColor;
        m_ColorPen = GetColor(iColor);
    }
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::SetBias(unsigned char iFixBias)
{
    iFixBias     = std::max((unsigned char)0, std::min((unsigned char)31, iFixBias));
    m_iFixBias   = iFixBias;
    for (int i = 0; i < 8; i++)
    {
        ZXPalette::SetColor(8 + i, Get256Color((iFixBias * 8) + i));
    }
}
//---------------------------------------------------------------------------
unsigned char __fastcall Enterprise16Palette::GetColor(void)
{
    return m_iColor;
}
//---------------------------------------------------------------------------
TColor __fastcall Enterprise16Palette::GetColor(unsigned char iColor)
{
    return ZXPalette::GetColor(iColor);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::SetColorAt(ZXImage& Image, int X, int Y)
{
    Write(X, Y, true, Image);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::GetColorAt(ZXImage& Image, int X, int Y)
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
        unsigned char cPixelShifts= cPixelPos << 2;
        m_iColor = (cPixels >> cPixelShifts) & 0x0F;
        if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // dirty the character block
    int dX = (X >> 3) << 3;
    //int dY = (Y >> 3) << 3;
    TRect Rect(dX, Y, dX + 8, Y + 1);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, m_iColor, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
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
void __fastcall Enterprise16Palette::SetPixel(int iX, int iY, unsigned char iColor, bool bSet, ZXImage& Image)
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
unsigned char __fastcall Enterprise16Palette::GetColorIndex(TColor Color)
{
    unsigned char ColorIndex = 0;
    for (int i = 0; i < 256; i++)
    {
        if (Color == GetColor(i))
        {
            ColorIndex = i;
            break;
        }
    }
    return ColorIndex;
}
//---------------------------------------------------------------------------
String __fastcall Enterprise16Palette::GetColorAsString(ZXImage& Image, int X, int Y)
{
    String sColor("None");
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iColX = X >> 3;
        unsigned int PixelOffset   = (Y * iCols) + iColX;
        unsigned char cPixelBit    = X % 2;
        unsigned char cPixels      = Image.Pixels[PixelOffset] & g_iPixelMasks[cPixelBit];
        unsigned char cPixelShifts = cPixelBit << 2;
        int iColor = (cPixels >> cPixelShifts) & 0x0F;
        sColor  = IntToStr(iColor);
    }
    return sColor;
}
//---------------------------------------------------------------------------
TColor __fastcall Enterprise16Palette::Get256Color(int iIndex)
{
    unsigned int R, G, B;

    R = Level_8[RED  (iIndex)] <<  0;
    G = Level_8[GREEN(iIndex)] <<  8;
    B = Level_4[BLUE (iIndex)] << 16;

    TColor Colour = (TColor)(R | G | B);
    return Colour;
}
//---------------------------------------------------------------------------
int __fastcall Enterprise16Palette::GetBiasColor(int iIndex)
{
    if (iIndex < 8)
        return iIndex;
    return (FixBias * 8) + (iIndex - 8);
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::Set256Color(unsigned char iColor, unsigned iIndex)
{
    if (iColor < 8)
    {
        ZXPalette::SetColor(iColor, Get256Color(iIndex));
    }
    else
    {
        FixBias = iIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::Reset(void)
{
    // reset 8-15
    FixBias = 31;
    // reset 0-7
    for (int i = 0; i < 8; i++)
    {
        ZXPalette::SetColor(i, Get256Color(i));
    }
    Color = 15;
}
//---------------------------------------------------------------------------
void __fastcall Enterprise16Palette::Loaded(void)
{
    frmEnterprise16Palette->OnUpdatePaletteGUI();
}
//---------------------------------------------------------------------------

