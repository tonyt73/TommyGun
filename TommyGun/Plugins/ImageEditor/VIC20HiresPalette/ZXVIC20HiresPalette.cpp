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
#include "ZXVic20HiresPalette.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
//using namespace Imaging;
using namespace Vic20HiresPalette;
//---------------------------------------------------------------------------
const   String  g_sPaletteName = "VIC-20 Hi-Res";
//---------------------------------------------------------------------------
unsigned char g_cPixelMasks[8] =
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
const String g_sColors[8] =
{
    "Black",
    "White",
    "Red",
    "Cyan",
    "Purple",
    "Green",
    "Blue",
    "Yellow"
};
//---------------------------------------------------------------------------
const   unsigned char   g_iTransparent  =    8; // attribute is transparent
const   unsigned char   g_iInkMask      = 0x07; // ink bits from attribute byte
//---------------------------------------------------------------------------
__fastcall ZXVic20HiresPalette::ZXVic20HiresPalette()
: ZXPalette(2, 160, 192, false, true)
, m_iInk(1)
, m_iPaper(0)
{
    m_bCanConvert = true;
    PalSignature(m_sSignature);
    m_ColorPen    = g_ColorsVIC20[m_iInk];
    m_ColorBrush  = g_ColorsVIC20[m_iPaper];
    Initialize();
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::Initialize(void)
{
    m_PixelFormat               = pf32bit;
    // initialize our palette information
    m_iBitsPerPixel             = 1;
    m_iBitsPerAttribute         = 8;
    m_iPixelsWidePerAttribute   = 8;
    m_iPixelsHighPerAttribute   = 8;
    m_fPixelsPerByte            = 8.f;
    m_bSupportsPixelsOnly       = false;
    m_fScalarX                  = 1.5f;
    // normally we would initialize the color table
    for (int i = 0; i < 16; i++)
    {
        SetColor(i, g_ColorsVIC20[i]);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::SetInk(unsigned char iInk)
{
    m_iInk       = iInk;
    m_ColorPen   = g_ColorsVIC20[m_iInk];
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::SetPaper(unsigned char iPaper)
{
    m_iPaper     = iPaper;
    m_ColorBrush = g_ColorsVIC20[m_iPaper];
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::SetColorAt(ZXImage& Image, int X, int Y)
{
    // sets the color in the palette to the color
    // dirty the character block
    int dX = (X >> 3) << 3;
    int dY = (Y >> 3) << 3;
    TRect Rect(dX, dY, dX + 8, dY + 8);
    Image.AddRect(Rect);
    SetAttribute(X, Y, m_iInk, &Image);
    m_ColorPen   = g_ColorsVIC20[m_iInk   ];
    m_ColorBrush = g_ColorsVIC20[m_iPaper ];
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::GetColorAt(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = X >> 3; // / 8
        // assign any transparent attributes
        unsigned int AttrOffset  = ((Y >> 3) * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        m_iInk    = (Attr & g_iInkMask);
        if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::Invert(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        // calculate the character position
        int dY = Y & 0xFFFFFFF8;
        int iCols = CalculateStride(Image.Width);
        int iCX   = X >> 3; // / 8
        // calculate the offset into the pixel buffer
        unsigned int PixelOffset = ( dY       * iCols) + iCX;
        // and then invert all 8 bytes of the character
        for (int i = 0; i < 8; ++i)
        {
            Image.Pixels[PixelOffset] = Image.Pixels[PixelOffset] ^ 0xFF;
            PixelOffset += iCols;
        }
        // dirty the character block
        int dX = (X >> 3) << 3;
        dY = (Y >> 3) << 3;
        TRect Rect(dX, dY, dX + 8, dY + 8);
        Image.AddRect(Rect);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // dirty the character block
    int dX = (X >> 3) << 3;
    int dY = (Y >> 3) << 3;
    TRect Rect(dX, dY, dX + 8, dY + 8);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, m_iInk, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
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
        for (int y = UpdateRect.Top; y < UpdateRect.Bottom; y += 8)
        {
            for (int x = UpdateRect.Left; x < UpdateRect.Right; x += 8)
            {
                unsigned char Attr = Image.Attributes[((y >> 3) * iCols) + (x >> 3)];
                int iCX = x >> 3;
                TColor cPaper = ShowAttributes ? g_ColorsVIC20[m_iPaper] : clBlack;
                TColor cInk   = ShowAttributes ? g_ColorsVIC20[Attr    ] : clWhite;
                for (int i = 0; i < 8; ++i)
                {
                    unsigned char Pixels = Image.Pixels[((y+i) * iCols) + iCX];
                    Bitmap->Canvas->Pixels[x+0][y+i] = (Pixels & g_cPixelMasks[0]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+1][y+i] = (Pixels & g_cPixelMasks[1]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+2][y+i] = (Pixels & g_cPixelMasks[2]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+3][y+i] = (Pixels & g_cPixelMasks[3]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+4][y+i] = (Pixels & g_cPixelMasks[4]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+5][y+i] = (Pixels & g_cPixelMasks[5]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+6][y+i] = (Pixels & g_cPixelMasks[6]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+7][y+i] = (Pixels & g_cPixelMasks[7]) ? cInk : cPaper;
                }
            }
        }
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::SetPixel(int iX, int iY, unsigned char iInk, bool bSet, ZXImage& Image)
{
    //PERFORMANCE_PUSH
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX >> 3; // / 8
        // assign any transparent attributes
        unsigned int PixelOffset = ( iY       * iCols) + iCX;
        unsigned int AttrOffset  = ((iY >> 3) * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        //         is attr transparent?          yes - read new attr             no - use supplied attr
        iInk    = (g_iTransparent == iInk   ) ?  (Attr & g_iInkMask) : iInk;
        // set the appropreiate pixels and attribute
        unsigned char cPixelBit   = 128 >> (iX % 8);
        // set or reset the pixel
        Image.Pixels[PixelOffset] = bSet ? (Image.Pixels[PixelOffset] | cPixelBit) : (Image.Pixels[PixelOffset] & ~cPixelBit);
        // apply the attribute
        Image.Attributes[AttrOffset ] = iInk;
    }
    //PERFORMANCE_POP(__FUNC__)
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::SetPixel(int iX, int iY, unsigned char PixelByte, ZXImage* Image)
{
    if (0 <= iX && iX < Image->Width && 0 <= iY && iY < Image->Height)
    {
        int iCharWidth = CalculateStride(Image->Width);
        Image->Pixels[(iY * iCharWidth) + (iX / 8)] = PixelByte;
    }
}
//---------------------------------------------------------------------------
unsigned char __fastcall ZXVic20HiresPalette::GetAttribute(int iX, int iY, ZXImage& Image)
{
    unsigned char Attr = 0;
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX >> 3; // / 8
        // assign any transparent attributes
        Attr = Image.Attributes[((iY >> 3) * iCols) + iCX];
    }
    return Attr;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image)
{
    if (0 <= iX && iX < Image->Width && 0 <= iY && iY < Image->Height)
    {
        int iCharWidth = CalculateStride(Image->Width);
        int iCX   = iX >> 3; // / 8
        // assign any transparent attributes
        unsigned int AttrOffset  = ((iY >> 3) * iCharWidth) + iCX;
        unsigned char Attr = Image->Attributes[AttrOffset];
        //         is attr transparent?          yes - read new attr             no - use supplied attr
        Attribute = (g_iTransparent == Attribute) ?  (Attr & g_iInkMask) : Attribute;
        Image->Attributes[((iY >> 3) * iCharWidth) + (iX >> 3)] = Attribute;
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXVic20HiresPalette::Convert(ZXImage* Image, Graphics::TBitmap* Bitmap)
{
    bool bConverted = false;
    if (true == SAFE_PTR(Bitmap))
    {
        // convert the bitmap into a 16 color bitmap
        // find the most common color in the image and use it as the background color
        unsigned int Paper = FindPaperColor(Bitmap);
        // now convert each 8x8 character block into 2 colors only
        // rules:
        //  1. the most common non bright color in the character block is the ink color
        //  2. any other color(s) becomes the background color

        // loop through all the rows
        int iXS = 0;
        int iXE = Image->Width;
        int iYS = 0;
        int iYE = Image->Height;

        for (int cy = iYS; cy < iYE; cy += 8)
        {
            // loop through all the columns
            for (int cx = iXS; cx < iXE; cx += 8)
            {
                unsigned char Ink = 0;    // black ink
                // find the most common colors
                FindInkColor(Bitmap, cx, cy, Ink, Paper);
                // set pixels according to the most common pair of colors
                SetColors(Image, Bitmap, cx, cy, Ink, Paper);
            }
        }
        bConverted = true;
    }
    return bConverted;
}
//---------------------------------------------------------------------------
int __fastcall ZXVic20HiresPalette::FindPaperColor(Graphics::TBitmap* Bitmap)
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
    int iPaper = m_iPaper;
    if (iColorCounts[iPaper] == 0)
    {
        for (int i = 8; i < 16; i++)
        {
            if (0 != iColorCounts[i] && iColorCounts[iPaper] < iColorCounts[i])
            {
                iPaper = i;
            }
        }
    }
    // if no bright colours then find the most common dull colour
    if (iColorCounts[iPaper] == 0)
    {
        // no bright background color, so find most common color
        for (int i = 0; i < 8; i++)
        {
            if (0 != iColorCounts[i] && iColorCounts[iPaper] < iColorCounts[i])
            {
                iPaper = i;
            }
        }
    }
    
    return iPaper;
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::FindInkColor(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Ink, unsigned char Paper)
{
    int iColorCounts[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (int y = iY; y < iY + 8; y++)
    {
        for (int x = iX; x < iX + 8; x++)
        {
            if (0 <= x && x < Bitmap->Width && 0 <= y && y < Bitmap->Height)
            {
                iColorCounts[GetColorIndex(Bitmap->Canvas->Pixels[x][y])]++;
            }
        }
    }

    // find the most common ink color (ie. not a bright color - can include black!)
    Ink = (Paper + 1) % 8;
    for (int i = 0; i < 8; i++)
    {
        if (0 != iColorCounts[i] && iColorCounts[Ink] <= iColorCounts[i] && i != Paper)
        {
            Ink  = i;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXVic20HiresPalette::SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Ink, unsigned char Paper)
{
    Ink = Ink & 0x07;
    for (int y = iY; y < iY + 8; y++)
    {
        unsigned char Pixels = 0;
        for (int x = iX; x < iX + 8; x++)
        {
            // change the non-ink/paper colors to the ink color
            unsigned char ColorIndex = 0;
            TColor BmpColor = GetClosestColor(Bitmap->Canvas->Pixels[x][y], &ColorIndex);
            int iBit = 0x80 >> (x % 8);
            Pixels |= (ColorIndex == Ink && 0 != Ink ) ? iBit : 0;
        }
        SetPixel(iX, y, Pixels, Image);
    }
    SetAttribute(iX, iY, Ink, Image);
}
//---------------------------------------------------------------------------
unsigned char __fastcall ZXVic20HiresPalette::GetColorIndex(TColor Color)
{
    unsigned char ColorIndex = 0;
    GetClosestColor(Color, &ColorIndex);
    return ColorIndex;
}
//---------------------------------------------------------------------------
String __fastcall ZXVic20HiresPalette::GetName(void)
{
    return g_sPaletteName;
}
//---------------------------------------------------------------------------
String __fastcall ZXVic20HiresPalette::GetColorAsString(ZXImage& Image, int X, int Y)
{
    String sColor("None");
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = X >> 3; // / 8
        // assign any transparent attributes
        unsigned int AttrOffset  = ((Y >> 3) * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset] & 0x07;
        sColor = g_sColors[Attr];
    }
    return sColor;
}
//---------------------------------------------------------------------------
TColor __fastcall ZXVic20HiresPalette::GetClosestColor(TColor SrcColor, unsigned char* ColorIndex)
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

