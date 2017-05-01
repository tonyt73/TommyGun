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
#include "ZXVic20MultiColorDHPalette.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
//using namespace Imaging;
using namespace Vic20MultiColorDHPalette;
//---------------------------------------------------------------------------
const   String  g_sPaletteName = "VIC-20 MultiColor (Double Height)";
//---------------------------------------------------------------------------
unsigned char g_cPixelMasks[4] =
{
    0xC0,
    0x30,
    0x0C,
    0x03
};
//---------------------------------------------------------------------------
const TColor g_ColorsVIC20[16] =
{
    (TColor)0x00000000, // Black
    (TColor)0x00FFFFFF, // White
    (TColor)0x001818B4, // Red
    (TColor)0x00D8E64C, // Cyan
    (TColor)0x00CA29BC, // Purple
    (TColor)0x0036E442, // Green
    (TColor)0x00C82A32, // Blue
    (TColor)0x0026E1D2, // Yellow
    (TColor)0x00025ACA, // Orange
    (TColor)0x0080ACDE, // Light Orange
    (TColor)0x009494DC, // Pink
    (TColor)0x00ECF4A5, // Light Cyan
    (TColor)0x00E49AE0, // Light Purple
    (TColor)0x009AF2A0, // Light Green
    (TColor)0x00E4929C, // Light Blue
    (TColor)0x009AF8EF, // Light Yellow
};
//---------------------------------------------------------------------------
const String g_sColors[16] =
{
    "Black",
    "White",
    "Red",
    "Cyan",
    "Purple",
    "Green",
    "Blue",
    "Yellow",
    "Orange",
    "Lt Orange",
    "Pink",
    "Lt Cyan",
    "Lt Purple",
    "Lt Green",
    "Lt Blue",
    "Lt Yellow"
};
//---------------------------------------------------------------------------
const   unsigned char   g_iInkMask      = 0x07; // ink bits from attribute byte
const   unsigned char   g_iMultiColorDH = 0x08; // the multicolor bit
//---------------------------------------------------------------------------
__fastcall ZXVic20MultiColorDHPalette::ZXVic20MultiColorDHPalette()
: ZXPalette(16, 160, 192, false, true)
, m_iInk(1)
, m_iPaper(0)
, m_iBorder(2)
, m_iAux(3)
, m_eColor(vcCharacter)
{
    m_bCanConvert = true;
    PalSignature(m_sSignature);
    m_ColorPen    = g_ColorsVIC20[m_iInk];
    m_ColorBrush  = g_ColorsVIC20[m_iPaper];
    Initialize();
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::Initialize(void)
{
    m_PixelFormat               = pf32bit;
    // initialize our palette information
    m_iBitsPerPixel             = 2;
    m_iBitsPerAttribute         = 8;
    m_iPixelsWidePerAttribute   = 4;
    m_iPixelsHighPerAttribute   = 16;
    m_fPixelsPerByte            = 4.0f;
    m_fScalarX                  = 3.0f;
    m_bSupportsPixelsOnly       = false;
    // normally we would initialize the color table
    for (int i = 0; i < 16; i++)
    {
        SetColor(i, g_ColorsVIC20[i]);
    }
    m_ColorBrush = clBlack;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::SetInk(unsigned char iInk)
{
    m_iInk       = iInk;
    m_ColorPen   = g_ColorsVIC20[m_iInk];
    m_eColor     = vcCharacter;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::SetPaper(unsigned char iPaper)
{
    m_iPaper     = iPaper;
    m_ColorPen   = g_ColorsVIC20[m_iPaper];
    m_ColorBrush = g_ColorsVIC20[m_iPaper];
    m_eColor     = vcBackground;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::SetAux(unsigned char iAux)
{
    m_iAux       = iAux;
    m_ColorPen   = g_ColorsVIC20[m_iAux];
    m_eColor     = vcAuxiliary;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::SetBorder(unsigned char iBorder)
{
    m_iBorder    = iBorder;
    m_ColorPen   = g_ColorsVIC20[m_iBorder];
    m_eColor     = vcBorder;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::SeteColor(TMultiColorDH eColor)
{
    m_eColor     = eColor;
    if (eColor == vcBackground)
        m_ColorPen   = g_ColorsVIC20[m_iPaper];
    else if (eColor == vcBorder)
        m_ColorPen   = g_ColorsVIC20[m_iBorder];
    else if (eColor == vcAuxiliary)
        m_ColorPen   = g_ColorsVIC20[m_iAux];
    else
        m_ColorPen   = g_ColorsVIC20[m_iInk];
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::SetColorAt(ZXImage& Image, int X, int Y)
{
    // sets the color in the palette to the color
    // dirty the character block
    int dX = (X >> 2) << 2;
    int dY = (Y >> 4) << 4;
    TRect Rect(dX, dY, dX + 4, dY + 16);
    Image.AddRect(Rect);
    SetPixel(X, Y, vcCharacter, true, Image);
    SetAttribute(X, Y, m_iInk, &Image);
    m_ColorPen   = g_ColorsVIC20[m_iInk   ];
    m_ColorBrush = g_ColorsVIC20[m_iPaper ];
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::GetColorAt(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = X >> 2; // / 4
        // assign any transparent attributes
        unsigned int AttrOffset  = ((Y >> 4) * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        m_iInk = (Attr & g_iInkMask);
        if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // dirty the character block
    int dX = (X >> 2) << 2;
    int dY = (Y >> 4) << 4;
    TRect Rect(dX, dY, dX + 4, dY + 16);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, m_eColor, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
{
    //PERFORMANCE_PUSH
    // loop through the character block and set all the ink and paper values
    Bitmap->PixelFormat = pf32bit;
    int iCols = CalculateStride(Image.Width);
    TRect UpdateRect;
    int iRects = Image.Rects();
    for (int rect = 0; rect < iRects; ++rect)
    {
        Image.GetRect(rect, UpdateRect);
        for (int y = UpdateRect.Top; y < UpdateRect.Bottom; y++)
        {
            for (int x = UpdateRect.Left; x < UpdateRect.Right; x++)
            {
                int           Bit   = x % 4;
                unsigned char Attr  = Image.Attributes[((y >> 4) * iCols) + (x >> 2)];
                unsigned char Pixel = Image.Pixels[(y * iCols) + (x >> 2)];
                unsigned char CType = Pixel & g_cPixelMasks[Bit];
                TColor        Color = clBlack;
                CType >>= (3 - Bit) * 2;
                if      (CType == vcCharacter ) Color = g_ColorsVIC20[Attr & 0x07];
                else if (CType == vcBackground) Color = g_ColorsVIC20[m_iPaper   ];
                else if (CType == vcBorder    ) Color = g_ColorsVIC20[m_iBorder  ];
                else                            Color = g_ColorsVIC20[m_iAux     ];
                Bitmap->Canvas->Pixels[x][y]  = Color;
            }
        }
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::SetPixel(int iX, int iY, TMultiColorDH eColor, bool bSet, ZXImage& Image)
{
    //PERFORMANCE_PUSH
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX >> 2; // / 4
        // assign any transparent attributes
        unsigned int PixelOffset = ( iY       * iCols) + iCX;
        unsigned int AttrOffset  = ((iY >> 4) * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        // set the appropreiate pixels and attribute
        unsigned char Color = ((unsigned char)eColor) << 6;
        int Shifts = (iX % 4) * 2;
        unsigned char cPixelBits = (unsigned char)(Color >> Shifts) & 0xFF;
        // reset the pixel
        Image.Pixels[PixelOffset] &= ~g_cPixelMasks[iX % 4];
        // set it if necessary
        if (bSet)
            Image.Pixels[PixelOffset] |= cPixelBits;
        // apply the attribute
        Image.Attributes[AttrOffset] |= g_iMultiColorDH;
        if (eColor == vcCharacter)
            Image.Attributes[AttrOffset] = m_iInk | g_iMultiColorDH;
    }
    //PERFORMANCE_POP(__FUNC__)
}
//---------------------------------------------------------------------------
unsigned char __fastcall ZXVic20MultiColorDHPalette::GetAttribute(int iX, int iY, ZXImage& Image)
{
    unsigned char Attr = 0;
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX >> 2; // / 4
        // assign any transparent attributes
        Attr = Image.Attributes[((iY >> 4) * iCols) + iCX];
    }
    return Attr;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image)
{
    if (0 <= iX && iX < Image->Width && 0 <= iY && iY < Image->Height)
    {
        int iCharWidth = CalculateStride(Image->Width);
        int iCX   = iX >> 2; // / 4
        // assign any transparent attributes
        unsigned int AttrOffset  = ((iY >> 4) * iCharWidth) + iCX;
        unsigned char Attr = Image->Attributes[AttrOffset];
        Image->Attributes[((iY >> 4) * iCharWidth) + (iX >> 2)] = Attribute | g_iMultiColorDH;
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXVic20MultiColorDHPalette::Convert(ZXImage* Image, Graphics::TBitmap* Bitmap)
{
    bool bConverted = false;
    if (true == SAFE_PTR(Bitmap))
    {
        TColorStack ColorStack(*this);
        // now convert each 4x8 character block
        // rules:
        //  1. The most common 2 colours > 7 are the background and auxiliary colours
        //  2. the most common non bright color in the character block is the ink color
        //  3. any other color(s) <= 7 becomes the border color
        //
        FindBrightColors(Bitmap);

        // loop through all the rows
        int iXS = 0;
        int iXE = Image->Width;
        int iYS = 0;
        int iYE = Image->Height;

        for (int cy = iYS; cy < iYE; cy += 16)
        {
            // loop through all the columns
            for (int cx = iXS; cx < iXE; cx += 4)
            {
                unsigned char Ink = 0;        // black ink
                // find the most common ink color
                FindInk(Bitmap, cx, cy, Ink);
                // set pixels according to the most common set of colors
                SetColors(Image, Bitmap, cx, cy, Ink, ColorStack);
            }
        }
        bConverted = true;
    }
    return bConverted;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::FindBrightColors(Graphics::TBitmap* Bitmap)
{
    int iColorCounts[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    // count the colours
    for (int y = 0; y < Bitmap->Height; y++)
    {
        for (int x = 0; x < Bitmap->Width; x++)
        {
            iColorCounts[GetColorIndex(Bitmap->Canvas->Pixels[x][y])]++;
        }
    }

    // find the most common color bright color
    // lets assume the current colors are in the image
    unsigned char iBkg = m_iPaper;
    unsigned char iAux = m_iAux;
    unsigned char iBdr = m_iBorder;
    if (iColorCounts[iBkg] == 0)
    {
        for (int i = 8; i < 16; i++)
        {
            if (0 != iColorCounts[i] && iColorCounts[iBkg] < iColorCounts[i])
            {
                iBkg = i;
            }
        }
    }
    if (iColorCounts[iBkg] == 0)
    {
        // no bright background color, so find most common color
        for (int i = 0; i < 8; i++)
        {
            if (0 != iColorCounts[i] && iColorCounts[iBkg] < iColorCounts[i])
            {
                iBkg = i;
            }
        }
    }
    // find an auxiliary color
    if (iBkg > 7 && iColorCounts[iAux] == 0)
    {
        // find a bright auxiliary color
        for (int i = 8; i < 16; i++)
        {
            if (0 != iColorCounts[i] && i != iBkg && iColorCounts[iAux] < iColorCounts[i])
            {
                iAux = i;
            }
        }
    }
    if (iColorCounts[iAux] == 0)
    {
        // no auxiliary color found so, find next most common color
        for (int i = 0; i < 8; i++)
        {
            if (0 != iColorCounts[i] && i != iBkg && iColorCounts[iAux] < iColorCounts[i])
            {
                iAux = i;
            }
        }
    }
    // find border color
    if (iColorCounts[iBdr] == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            if (0 != iColorCounts[i] && i != iBkg && i != iAux && iColorCounts[iBdr] < iColorCounts[i])
            {
                iBdr = i;
            }
        }
    }
    
    m_iPaper  = iBkg;
    m_iAux    = iAux;
    m_iBorder = iBdr;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::FindInk(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& iInk)
{
    int iColorCounts[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (int y = iY; y < iY + 16; y++)
    {
        for (int x = iX; x < iX + 4; x++)
        {
            if (0 <= x && x < Bitmap->Width && 0 <= y && y < Bitmap->Height)
            {
                iColorCounts[GetColorIndex(Bitmap->Canvas->Pixels[x][y])]++;
            }
        }
    }

    // find the most common ink color
    iInk = 0;
    for (int i = 0; i < 8; i++)
    {
        if (0 != iColorCounts[i] && iColorCounts[iInk] <= iColorCounts[i] && i != m_iPaper && i != m_iBorder && i != m_iAux)
        {
            iInk = i;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Ink, const TColorStack& ColorStack)
{
    for (int y = iY; y < iY + 16; y++)
    {
        unsigned char Pixels = 0;
        for (int x = iX; x < iX + 4; x++)
        {
            unsigned char ColorIndex = 0;
            TColor BmpColor = GetClosestColor(Bitmap->Canvas->Pixels[x][y], &ColorIndex);
            TColor ImgColor = GetImageColor(*Image, x, y, ColorStack);
            if (BmpColor != ImgColor)
            {
                if (BmpColor == g_ColorsVIC20[m_iPaper])
                {
                    SetPixel(x, y, vcBackground, true, *Image);
                }
                else if (BmpColor == g_ColorsVIC20[m_iAux])
                {
                    SetPixel(x, y, vcAuxiliary, true, *Image);
                }
                else if (BmpColor == g_ColorsVIC20[m_iBorder])
                {
                    SetPixel(x, y, vcBorder, true, *Image);
                }
                else
                {
                    m_iInk = ColorIndex;
                    SetPixel(x, y, vcCharacter, true, *Image);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
unsigned char __fastcall ZXVic20MultiColorDHPalette::GetColorIndex(TColor Color)
{
    unsigned char ColorIndex = 0;
    GetClosestColor(Color, &ColorIndex);
    return ColorIndex;
}
//---------------------------------------------------------------------------
String __fastcall ZXVic20MultiColorDHPalette::GetName(void)
{
    return g_sPaletteName;
}
//---------------------------------------------------------------------------
String __fastcall ZXVic20MultiColorDHPalette::GetColorAsString(ZXImage& Image, int X, int Y)
{
    String sColor("None");
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = X >> 2; // / 4
        // assign any transparent attributes
        unsigned int AttrOffset  = ((Y >> 4) * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        unsigned int PixelOffset = (Y * iCols) + iCX;
        unsigned char Pixels = Image.Pixels[PixelOffset];
        Pixels = Pixels & g_cPixelMasks[X % 4];
        Pixels >>= (X % 4) * 2;
        if (Pixels == vcBackground)
            sColor = "Bg: " + g_sColors[m_iPaper];
        else if (Pixels == vcBorder)
            sColor = "Bd: " + g_sColors[m_iBorder];
        else if (Pixels == vcAuxiliary)
            sColor = "Ax: " + g_sColors[m_iAux];
        else
            sColor = "Ch:" + g_sColors[Attr];
    }
    return sColor;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20MultiColorDHPalette::Reset()
{
    m_iInk    = 1;
    m_iPaper  = 0;
    m_iBorder = 2;
    m_iAux    = 3;
}
//---------------------------------------------------------------------------
TColor __fastcall ZXVic20MultiColorDHPalette::GetClosestColor(TColor SrcColor, unsigned char* ColorIndex)
{
    float CP = 0.1f;
    std::vector<float> Colors;
    TColor Color = clBlack;

    int SR = (SrcColor & 0x000000FF)      ;
    int SG = (SrcColor & 0x0000FF00) >>  8;
    int SB = (SrcColor & 0x00FF0000) >> 16;

    for (int i = 0; i < 16; i++)
    {
        TColor TgtColor = g_ColorsVIC20[i];

        if (TgtColor == SrcColor)
        {
            if (ColorIndex)
                *ColorIndex = i;
            return SrcColor;
        }

        int TR = (TgtColor & 0x000000FF)      ;
        int TG = (TgtColor & 0x0000FF00) >>  8;
        int TB = (TgtColor & 0x00FF0000) >> 16;

        int CD = 25;

        if ((TR - CD < SR && SR < TR + CD) &&
            (TG - CD < SG && SG < TG + CD) &&
            (TB - CD < SB && SB < TB + CD))
        {
            // work out the percentage delta
            float PD = 0.0f;
            PD += (float)(abs(TR - SR)) / (float)TR;
            PD += (float)(abs(TG - SG)) / (float)TG;
            PD += (float)(abs(TB - SB)) / (float)TB;
            Colors.push_back(PD);
        }
        else
        {
            Colors.push_back(100.0f);
        }
    }

    // find the lowest percentage difference color
    int MinColor = 0;
    float Lowest = 100.f;
    for (int i = 0; i < 16; i++)
    {
        if (Colors[i] < Lowest)
        {
            Lowest = Colors[i];
            MinColor = i;
        }
    }

    if (ColorIndex != NULL)
    {
        *ColorIndex = MinColor;
    }

    return g_ColorsVIC20[MinColor];
}
//---------------------------------------------------------------------------
TColor __fastcall ZXVic20MultiColorDHPalette::GetImageColor(ZXImage& Image, int iX, int iY, const TColorStack& ColorStack)
{
    TColor Color = clBlack;
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX >> 2; // / 4
        // assign any transparent attributes
        unsigned int PixelOffset = ( iY       * iCols) + iCX;
        unsigned int AttrOffset  = ((iY >> 4) * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        // get the appropreiate pixels and attribute
        int Shifts = (iX % 4) * 2;
        // reset the pixel
        TMultiColorDH PixColor = (TMultiColorDH)((Image.Pixels[PixelOffset] & g_cPixelMasks[iX % 4]) >> Shifts);
        if (PixColor == vcBackground)
        {
            Color = g_ColorsVIC20[ColorStack.m_iPaper];
        }
        else if (PixColor == vcAuxiliary)
        {
            Color = g_ColorsVIC20[ColorStack.m_iAux];
        }
        else if (PixColor == vcBorder)
        {
            Color = g_ColorsVIC20[ColorStack.m_iBorder];
        }
        else
        {
            Color = g_ColorsVIC20[Image.Attributes[AttrOffset] & 0x07];
        }
    }
    return Color;
}
//---------------------------------------------------------------------------

