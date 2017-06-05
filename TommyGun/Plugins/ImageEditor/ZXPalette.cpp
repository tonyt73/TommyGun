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
#include "ZXPalette.h"
#include "ZXImage.h"
#include <map>
#include <math.h>
#include <iostream>
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXPalette::ZXPalette(unsigned int iColors, unsigned int iScreenWidth, unsigned int iScreenHeight, bool bSaveColors, bool bScreenResizeable)
: m_iColorsInTable(iColors),
  m_pColorTable(NULL),
  m_PixelFormat(pfDevice),
  m_bCanConvert(false),
  m_bShowAttributes(true),
  m_bPenSet(false),
  m_bBrushSet(false),
  m_bSaveColors(bSaveColors),
  m_bScreenResizeable(bScreenResizeable),
  m_ColorPen(clWhite),
  m_ColorBrush(clBlack),
  m_iDefaultScreenWidth(iScreenWidth),
  m_iDefaultScreenHeight(iScreenHeight),
  m_iDefaultSpriteWidth(16),
  m_iDefaultSpriteHeight(16),
  m_iIncSpriteWidth(8),
  m_iIncSpriteHeight(1),
  m_fScalarX(1.f),
  m_fScalarY(1.f),
  m_SupportedImageTypes(itAny),
  FOnUpdatePalette(NULL)
{
    m_pColorTable = new TColor[iColors];
    ZeroMemory(m_pColorTable, sizeof(TColor) * iColors);
    Initialize();
}
//---------------------------------------------------------------------------
__fastcall ZXPalette::ZXPalette(const ZXPalette& Palette)
{
    *this = Palette;
}
//---------------------------------------------------------------------------
__fastcall ZXPalette::~ZXPalette()
{
    delete[] m_pColorTable;
}
//---------------------------------------------------------------------------
ZXPalette ZXPalette::operator=(const ZXPalette& Other)
{
    // copy the palette information
    m_iBitsPerPixel             = Other.m_iBitsPerPixel;
    m_iBitsPerAttribute         = Other.m_iBitsPerAttribute;
    m_iPixelsWidePerAttribute   = Other.m_iPixelsWidePerAttribute;
    m_iPixelsHighPerAttribute   = Other.m_iPixelsHighPerAttribute;
    m_bSupportsPixelsOnly       = Other.m_bSupportsPixelsOnly;
    // free the existing color table
    if (NULL == m_pColorTable)
    {
        delete[] m_pColorTable;
    }
    // allocate another color table
    m_iColorsInTable = Other.m_iColorsInTable;
    m_pColorTable = new TColor[m_iColorsInTable];
    // and copy the other color table into it
    CopyMemory(m_pColorTable, Other.m_pColorTable, m_iColorsInTable * sizeof(TColor));
    return *this;
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::Initialize(void)
{
    // default initialization of the palette information
    // default palette is blank
    ZeroMemory(m_pColorTable, sizeof(TColor) * m_iColorsInTable);
    m_iBitsPerPixel             = 1;
    m_iBitsPerAttribute         = 1;
    m_iPixelsWidePerAttribute   = 1;
    m_iPixelsHighPerAttribute   = 1;
    m_fPixelsPerByte            = 1.f;
    m_bSupportsPixelsOnly       = true;
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::SetColor(unsigned int iColorIndex, TColor Color)
{
    if (iColorIndex < m_iColorsInTable)
    {
        m_pColorTable[iColorIndex] = Color;
    }
    // set default pen color
    if (!m_bPenSet && iColorIndex == 1)
    {
        m_ColorPen = Color;
        m_bPenSet  = true;
    }
    // set default brush color
    if (!m_bBrushSet && iColorIndex == 0)
    {
        m_ColorBrush = Color;
        m_bBrushSet  = true;
    }
}
//---------------------------------------------------------------------------
TColor __fastcall ZXPalette::GetColor(unsigned int iColorIndex)
{
    TColor Color(clBlack);
    if (iColorIndex < m_iColorsInTable)
    {
        Color = m_pColorTable[iColorIndex];
    }
    return Color;
}
//---------------------------------------------------------------------------
int __fastcall ZXPalette::GetColor(TColor Color)
{
    for (unsigned int i = 0; i < m_iColorsInTable; i++)
    {
        if (m_pColorTable[i] == Color)
            return i;
    }
    return clBlack;//GetClosestColor(Color);
}
//---------------------------------------------------------------------------
double __fastcall ZXPalette::HsbDistance(int c1, int c2)
{
    const double wHue = 0.8;
    const double wSat = 0.1;
    const double wVal = 0.5;

    TRgb sRgb(m_pColorTable[c1]);
    THsb hsb = RgbToHsb(sRgb);

    TRgb cRgb(m_pColorTable[c2]);
    THsb cHSB = RgbToHsb(cRgb);

    double dH = cHSB.h - hsb.h;
    double dS = cHSB.s - hsb.s;
    double dV = cHSB.b - hsb.b;

    return sqrt(wHue * pow(dH, 2) + wSat * pow(dS, 2) + wVal * pow(dV, 2));
}
//---------------------------------------------------------------------------
unsigned int __fastcall ZXPalette::GetClosestColor(THsb hsb, const double wHue, const double wSat, const double wVal)
{
    double minDistance = 1000000000.0;
    int minIndex = 0;

    for (unsigned int i = 0; i < m_iColorsInTable; i++)
    {
        int idx = i;//m_iColorsInTable - i - 1;
        TRgb rgb(m_pColorTable[idx]);
        THsb cHSB = RgbToHsb(rgb);

        double dH = cHSB.h - hsb.h;
        double dS = cHSB.s - hsb.s;
        double dV = cHSB.b - hsb.b;

        double distance = wHue * pow(dH, 2) + wSat * pow(dS, 2) + wVal * pow(dV, 2);
        if (distance < minDistance)
        {
            minDistance = distance;
            minIndex = idx;
        }
    }
    return minIndex;
}
//---------------------------------------------------------------------------
unsigned int __fastcall ZXPalette::GetClosestColor(THsl hsl)
{
    const double wHue = 0.5;
    const double wSat = 0.1;
    const double wVal = 0.8;
    double minDistance = 1000000000.0;
    int minIndex = 0;

    for (unsigned int i = 0; i < m_iColorsInTable; i++)
    {
        int idx = i;//m_iColorsInTable - i - 1;
        THsl cHSL = RgbToHsl(m_pColorTable[idx]);

        double dH = cHSL.h - hsl.h;
        double dS = cHSL.s - hsl.s;
        double dV = cHSL.l - hsl.l;

        double distance = sqrt(wHue * pow(dH, 2) + wSat * pow(dS, 2) + wVal * pow(dV, 2));
        if (distance < minDistance)
        {
            minDistance = distance;
            minIndex = idx;
        }
    }
    return minIndex;
}
//---------------------------------------------------------------------------
unsigned int __fastcall ZXPalette::GetClosestColor(TColor Color)
{
    return GetClosestColor(RgbToHsl(Color));
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::SetColorAt(ZXImage& Image, int X, int Y)
{
    // default function for the derived classes to override
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::GetColorAt(ZXImage& Image, int X, int Y)
{
    // default function for the derived classes to override
}
//---------------------------------------------------------------------------
String __fastcall ZXPalette::GetColorAsString(ZXImage& Image, int X, int Y)
{
    return String("n/a");
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::Invert(ZXImage& Image, int X, int Y)
{
    // default function for the derived classes attribute classes to override
    // ie. not applicable to pixel only palettes
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::Swap(ZXImage& Image, int X, int Y)
{
    // default function for the derived classes attribute classes to override
    // ie. not applicable to pixel only palettes
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // default write function does nothing
    // its upto the specialized palette classes to write color information to the image
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::SetColor(unsigned char iColor)
{
}
//---------------------------------------------------------------------------
int __fastcall ZXPalette::Distance(TColor color1, TColor color2)
{
    return 0;//Difference(RgbToHsv(color1), RgbToHsv(color2));
}
//---------------------------------------------------------------------------
inline int __fastcall ZXPalette::Difference(TColor C1, TColor C2)
{
    return abs(( C1        & 0xFF) - ( C2        & 0xFF)) +
           abs(((C1 >>  8) & 0xFF) - ((C2 >>  8) & 0xFF)) +
           abs(((C1 >> 16) & 0xFF) - ((C2 >> 16) & 0xFF));
}
//---------------------------------------------------------------------------
unsigned int __fastcall ZXPalette::ConvertFindColor(int x, int y, Graphics::TBitmap* Bitmap)
{
    return GetClosestColor(Bitmap->Canvas->Pixels[x][y]);
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::BuildConvertColors(Graphics::TBitmap* Bitmap)
{
    int iColors = 0;
    m_ConvertColors.clear();
    m_ConvertColors.push_back(Bitmap->Canvas->Pixels[0][0]);
    for (int y = 0; y < Bitmap->Height; ++y)
    {
        for (int x = 0; x < Bitmap->Width; ++x)
        {
            TColor color = Bitmap->Canvas->Pixels[x][y];
            bool bFound = false;
            for (unsigned int i = 0; i < m_ConvertColors.size() && !bFound; i++)
            {
                bFound = (color == m_ConvertColors[i]);
            }
            if (!bFound)
            {
                m_ConvertColors.push_back(color);
                if (m_ConvertColors.size() == m_iColorsInTable)
                {
                    // found enough colours
                    return;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::ConvertPalettized(ZXImage* Image, Graphics::TBitmap* Bitmap)
{
    // find the number of colours in the
    BuildConvertColors(Bitmap);
    for (int y = 0; y < Image->Height; ++y)
    {
        for (int x = 0; x < Image->Width; ++x)
        {
            SetColor(ConvertFindColor(x, y, Bitmap));
            Write(x, y, true, *Image);
        }
    }
    m_ConvertColors.clear();
}
//---------------------------------------------------------------------------
bool __fastcall ZXPalette::Convert(ZXImage* Image, Graphics::TBitmap* Bitmap)
{
    // needs to be overridden by the derived classes so a bitmap can be converted to the native palette
    if (m_bSupportsPixelsOnly)
    {
        if (m_fPixelsPerByte > 0.f)
        {
            // this is a colour table style palette
            // eg 2 colour (1 bit)
            //    4 colour (2 bit)
            //   16 colour (4 bit)
            //  256 colour (8 bit)
            ConvertPalettized(Image, Bitmap);
            return true;
        }
        else
        {
            // this is either 16, 24 or 32 bit palette
        }
    }
    else
    {
        // this is a ZX Spectrum style palette
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXPalette::ConvertBitmap(ZXImage* Image, Graphics::TBitmap* Bitmap)
{
    bool bConverted = false;
    if (true == SAFE_PTR(Bitmap) && Bitmap->Width == Image->Width && Bitmap->Height == Image->Height)
    {
        bConverted = Convert(Image, Bitmap);
        if (true == bConverted)
        {
            Image->Invalidate();
        }
    }
    return bConverted;
}
//---------------------------------------------------------------------------
unsigned int __fastcall ZXPalette::CalculateStride(unsigned int iWidth) const
{
    double fStride = (double)iWidth / PixelsPerByte;
    int   iStride = fStride;
    if ((double)iStride != fStride)
        iStride++;
    //iStride += (iWidth % 8) ? 1 : 0;
    return iStride;
}
//---------------------------------------------------------------------------
unsigned int __fastcall ZXPalette::CalculatePixelBufferSize(unsigned int iWidth, unsigned int iHeight) const
{
    return iHeight * CalculateStride(iWidth);
}
//---------------------------------------------------------------------------
unsigned int __fastcall ZXPalette::CalculateAttributeBufferSize(unsigned int iWidth, unsigned int iHeight) const
{
    double fStride = (double)iWidth / PixelsPerByte;
    int   iStride = fStride;
    if ((double)iStride != fStride)
        iStride++;
    //int iStride = iWidth / m_iPixelsWidePerAttribute;
    //iStride += (iWidth % 8) ? 1 : 0;
    double fStryde = (double)iHeight / (double)m_iPixelsHighPerAttribute;
    int   iStryde = fStryde;
    if ((double)iStryde != fStryde)
        iStryde++;
    //int iStryde = iHeight / m_iPixelsHighPerAttribute;
    //iStryde += (iHeight % 8) ? 1 : 0;
    return iStride * iStryde;
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
{
    // dummy function for the specialization class to override and handle
}
//---------------------------------------------------------------------------
String __fastcall ZXPalette::GetName(void)
{
    return m_sSignature;
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall ZXPalette::GetColorTable(void)
{
    // override to return your own color table
    return NULL;
}
//---------------------------------------------------------------------------
bool __fastcall ZXPalette::SetColorTable(KXmlInfo& xmlInfo)
{
    // override to load your own color table
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo Palette("Palette");

    Palette.Add("Name"                  , m_sSignature              );
    Palette.Add("BitsPerPixel"          , m_iBitsPerPixel           );
    Palette.Add("BitPerAttribute"       , m_iBitsPerAttribute       );
    Palette.Add("PixelsWidePerAttribute", m_iPixelsWidePerAttribute );
    Palette.Add("PixelsHighPerAttribute", m_iPixelsHighPerAttribute );
    Palette.Add("PixelsPerByte"         , m_fPixelsPerByte          );
    Palette.Add("SupportsPixelsOnly"    , m_bSupportsPixelsOnly     );

    if (m_bSaveColors)
    {
        KXmlInfo* colorTable = GetColorTable();
        if (colorTable == NULL)
        {
            // save the colour table
            KXmlInfo ColorTable("Colors");

            for (unsigned int i = 0; i < m_iColorsInTable; i++)
            {
                ColorTable.Add("Color", ColorToString(m_pColorTable[i]));
            }
            Palette.Add(ColorTable);
        }
        else
        {
            Palette.Add(*colorTable);
        }
    }

    xmlInfo.Add(Palette);
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::Load(KXmlInfo& xmlInfo)
{
    if (xmlInfo.GetNode("Name")->GetText() == Name)
    {
        if (m_bSaveColors && !SetColorTable(xmlInfo))
        {
            KXmlInfo* pColors = xmlInfo.GetNode("Colors");
            if (true == SAFE_PTR(pColors))
            {
                if (m_iColorsInTable == pColors->size())
                {
                    int i = 0;
                    for (KXmlNodes::iterator it = pColors->begin(); it != pColors->end(); i++, it++)
                    {
                        m_pColorTable[i] = StringToColor((*it)->GetText());
                    }
                }
                // signal to the palette we have loaded the color table
                Loaded();
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::Loaded(void)
{
}
//---------------------------------------------------------------------------
void __fastcall ZXPalette::ApplyFix(const String& sVersion, ZXImage* pImage)
{
    if (sVersion == "1.0")
    {
        for (unsigned int i = 0; i < pImage->PixelBufSize; ++i)
        {
            switch (m_iBitsPerPixel)
            {
                case 1:
                {
                    // bit flip the pixels (most common problem
                    pImage->Pixels[i] = FlipBits(pImage->Pixels[i]);
                    break;
                }
                case 2:
                {
                    pImage->Pixels[i] = ((pImage->Pixels[i] & 0xC0) >> 6)
                                        |
                                        ((pImage->Pixels[i] & 0x30) >> 2)
                                        |
                                        ((pImage->Pixels[i] & 0x0C) << 2)
                                        |
                                        ((pImage->Pixels[i] & 0x03) << 6);
                    break;
                }
                case 4:
                {
                    pImage->Pixels[i] = ((pImage->Pixels[i] & 0xF0) >> 4)
                                        |
                                        ((pImage->Pixels[i] & 0x0F) << 4);
                    break;
                }
                default:
                    break;
            }
        }
    }
}
//---------------------------------------------------------------------------
unsigned char __fastcall ZXPalette::FlipBits(unsigned char iBits)
{
    unsigned char iResult = 0;
    unsigned char iBit = 128;
    for (int i = 0; i < 8; i++)
    {
        if (iBits & 0x01)
        {
            iResult |= iBit;
        }
        iBit >>= 1;
        iBits >>= 1;
    }
    return iResult;
}
//---------------------------------------------------------------------------
DWORD __fastcall ZXPalette::Luminance(TColor Color)
{
    // get the luminance of the color
    DWORD dwRed       = (Color & 0x000000FF) >>  0;
    DWORD dwGreen     = (Color & 0x0000FF00) >>  8;
    DWORD dwBlue      = (Color & 0x00FF0000) >> 16;
    DWORD dwLuminance = (0.299f * (double)dwRed + 0.587f * (double)dwGreen + 0.114f * (double)dwBlue);
    return dwLuminance;
}
//---------------------------------------------------------------------------
bool __fastcall ZXPalette::IsImageTypeSupported(ZXImageTypes imageType) const
{
    bool supported = true;
    if (m_SupportedImageTypes != itAny)
    {
        supported = (m_SupportedImageTypes & imageType) != 0;
    }
    return supported;
}
//---------------------------------------------------------------------------
TRgb __fastcall ZXPalette::HsbToRgb(THsb hsb)
{
    TRgb rgb;
    return rgb;
}
//---------------------------------------------------------------------------
THsb __fastcall ZXPalette::RgbToHsb(TRgb rgb)
{
#if 1
    // normalize red, green and blue values
    double r = (rgb.r / 255.0);
    double g = (rgb.g / 255.0);
    double b = (rgb.b / 255.0);
    // conversion start
    double max = std::max(r, std::max(g, b));
    double min = std::min(r, std::min(g, b));
    double h = 0.0;
    if (max == min)
    {
        h = 0.0;
    }
    else if (max == r && g >= b)
    {
        h = 60.0 * (g - b) / (max - min);
    }
    else if (max == r && g < b)
    {
        h = 60.0 * (g - b) / (max - min) + 360.0;
    }
    else if (max == g)
    {
        h = 60.0 * (b - r) / (max - min) + 120.0;
    }
    else if (max == b)
    {
        h = 60.0 * (r - g) / (max - min) + 240.0;
    }
    double s = (max == 0) ? 0.0 : (1.0 - (min / max));
    THsb hsb = { h, s, max };
    return hsb;
#else
    double r = rgb.r / 255.0;
    double g = rgb.g / 255.0;
    double b = rgb.b / 255.0;
    double max = std::max(std::max(r, g), b);
    double min = std::min(std::min(r, g), b);
    double delta = max - min;
    THsb hsb;

    if (delta != 0.0)
    {
        double hue;
        if (r == max)
        {
            hue = (g - b) / delta;
        }
        else
        {
            if (g == max)
            {
                hue = 2.0 + (b - r) / delta;
            }
            else
            {
                hue = 4.0 + (r - g) / delta;
            }
        }
        hue *= 60.0;
        if (hue < 0.0) hue += 360.0;
        hsb.h = hue;
    }
    else
    {
        hsb.h = 0.0;
    }
    hsb.s = max == 0 ? 0 : (max - min) / max;
    hsb.b = max;
    return hsb;
#endif
}
//---------------------------------------------------------------------------
// RGB = TColor => xBGR
// HSV = TColor => xVSH
THsv __fastcall ZXPalette::RgbToHsv(TRgb in)
{
    THsv        out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, v is undefined
        out.s = 0.0;
        out.h = 0.0;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}
//---------------------------------------------------------------------------
// RGB = TColor => xBGR
// HSV = TColor => xVSH
TRgb __fastcall ZXPalette::HsvToRgb(THsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    TRgb        out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}
//---------------------------------------------------------------------------
THsl __fastcall ZXPalette::RgbToHsl(TRgb rgb)
{
    THsl hsl;
    // R, G, B input  range = 0 ÷ 255
    // H, S, L output range = 0 ÷ 1.0

    double R = rgb.r / 255.0;
    double G = rgb.g / 255.0;
    double B = rgb.b / 255.0;

    double Min = std::min( R, std::min(G, B ));      // Min. value of RGB
    double Max = std::max( R, std::max(G, B ));      // Max. value of RGB
    double dMax = Max - Min;                         // Delta RGB value

    hsl.l = (Max + Min) / 2.0;

    if (dMax == 0.0)                                // This is a gray, no chroma...
        hsl.s = hsl.h = 0.0;
    else                                            // Chromatic data...
    {
        if (hsl.l < 0.5)
            hsl.s = dMax / ( Max + Min );
        else
            hsl.s = dMax / ( 2.0 - Max - Min );

        double dR = (((Max - R ) / 6.0) + (dMax / 2.0)) / dMax;
        double dG = (((Max - G ) / 6.0) + (dMax / 2.0)) / dMax;
        double dB = (((Max - B ) / 6.0) + (dMax / 2.0)) / dMax;

        if      ( R == Max ) hsl.h = dB - dG;
        else if ( G == Max ) hsl.h = ( 1.0 / 3.0 ) + dR - dB;
        else if ( B == Max ) hsl.h = ( 2.0 / 3.0 ) + dG - dR;

        if ( hsl.h < 0.0 ) hsl.h += 1.0;
        if ( hsl.h > 1.0 ) hsl.h -= 1.0;
    }
    return hsl;
}
//---------------------------------------------------------------------------
TRgb __fastcall ZXPalette::HslToRgb(THsl hsl)
{
    double r, g, b;

    if(hsl.s == 0.0)
    {
        r = g = b = hsl.l; // achromatic
    }
    else
    {
        double q = hsl.l < 0.5 ? hsl.l * (1.0 + hsl.s) : (hsl.l + hsl.s) - (hsl.l * hsl.s);
        double p = 2.0 * hsl.l - q;
        r = Hue2Rgb(p, q, hsl.h + 1.0/3.0);
        g = Hue2Rgb(p, q, hsl.h);
        b = Hue2Rgb(p, q, hsl.h - 1.0/3.0);
    }

    TRgb rgb;
    rgb.r = r * 255.0;
    rgb.g = g * 255.0;
    rgb.b = b * 255.0;
    return rgb;
}
//---------------------------------------------------------------------------
double __fastcall ZXPalette::Hue2Rgb(double p, double q, double t)
{
    if (t < 0.0) t += 1.0;
    if (t > 1.0) t -= 1.0;
    if (t < 1.0/6.0) return p + (q - p) * 6.0 * t;
    if (t < 1.0/2.0) return q;
    if (t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6.0;
    return p;
}
//---------------------------------------------------------------------------
double __fastcall ZXPalette::Lerp(double a, double b, double f)
{
     return a + f * (b - a);
}
//---------------------------------------------------------------------------

