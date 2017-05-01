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
using namespace SpectrumPalette;
//---------------------------------------------------------------------------
const   String  g_sPaletteName = "ZX Spectrum ULAplus";
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
const unsigned char g_iTransparent  = 8; // attribute is transparent
const unsigned char g_iClutMask = 0xC0;
const unsigned char g_iPaperMask = 0x38;
const unsigned char g_iInkMask = 0x07;
const unsigned char g_iRedMask = 0x1C;
const unsigned char g_iGreenMask = 0xE0;
const unsigned char g_iBlueMask = 0x03;
const unsigned char g_iRedShift = 2;
const unsigned char g_iGreenShift = 5;
const unsigned char g_iBlueShift = 0;
const int g_iClutShift = 6;
const int g_iPaperShift = 3;
//---------------------------------------------------------------------------
__fastcall ZXSpectrumUlaPlusPalette::ZXSpectrumUlaPlusPalette()
: ZXPalette(64, 256, 192, true),
  m_iInk(0),
  m_iPaper(0),
  m_iClut(0)
{
    m_bCanConvert = false;
    PalSignature(m_sSignature);
    m_ColorPen    = GetColor(m_iClut, m_iInk);
    m_ColorBrush  = GetColor(m_iClut, 8 + m_iPaper);
    Initialize();
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::Initialize(void)
{
    m_PixelFormat               = pf32bit;
    // initialize our palette information
    m_iBitsPerPixel             = 1;
    m_iBitsPerAttribute         = 8;
    m_iPixelsWidePerAttribute   = 8;
    m_iPixelsHighPerAttribute   = 1;
    m_fPixelsPerByte            = 8.f;
    m_bSupportsPixelsOnly       = false;
    UseDefaultPalette();
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::UseImagePalette(void)
{
    memcpy(m_Palette, m_LoadedPalette, sizeof(m_Palette));
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::UseDefaultPalette(void)
{
    unsigned char color = 0;
    unsigned int i = 0;
    // normally we would initialize the color table
    for (int r = 1; r < 8; r += 2)
    {
        for (int g = 0; g < 8; g += 2)
        {
            for (int b = 0; b < 4; b++)
            {
                color = b | (r << g_iRedShift) | (g << g_iGreenShift);
                if (i < 64)
                {
                    m_Palette[i++] = color;
                }
            }
        }
    }
    m_Palette[0] = 0;
    m_Palette[63] = 255;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::UseZXSpectrumPalette(void)
{
    unsigned char palette[64] =
    {
        0, 2, 24, 26, 192, 195, 216, 219, 0, 2, 24, 26, 192, 195, 216, 219,
        0, 3, 28, 31, 224, 227, 252, 255, 0, 3, 28, 31, 224, 227, 252, 255,
        0, 2, 24, 26, 192, 195, 216, 219, 0, 2, 24, 26, 192, 195, 216, 219,
        0, 3, 28, 31, 224, 227, 252, 255, 0, 3, 28, 31, 224, 227, 252, 255
    };

    memcpy(m_Palette, palette, sizeof(palette));
    UpdateColorTable();
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::UpdateLoadedPalette(void)
{
    // copy the current palette into the images loaded palette. aka: save the original palette
    memcpy(m_LoadedPalette, m_Palette, sizeof(m_Palette));
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::UpdateColorTable(void)
{
    for (int i = 0; i < 64; i++)
    {
        ZXPalette::SetColor(i, GetColor(i));
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetInk(unsigned char iInk)
{
    m_iInk       = std::min((unsigned char)8, iInk);
    m_ColorPen   = GetColor(m_iClut, m_iInk);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetPaper(unsigned char iPaper)
{
    m_iPaper     = std::min((unsigned char)8, iPaper);
    m_ColorBrush = GetColor(m_iClut, 8 + m_iPaper);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetClut(unsigned char iClut)
{
    m_iClut      = iClut & 0x03;
    m_ColorPen   = GetColor(m_iClut, m_iInk);
    m_ColorBrush = GetColor(m_iClut, 8 + m_iPaper);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetColorAt(ZXImage& Image, int X, int Y)
{
    // sets the color in the palette to the color
    // dirty the character block
    int dX = X & ~0x07;
    int dY = Y;
    TRect Rect(dX, dY, dX + m_iPixelsWidePerAttribute, dY + m_iPixelsHighPerAttribute);
    Image.AddRect(Rect);
    SetAttribute(X, Y, m_iInk, m_iPaper, m_iClut, Image);
    m_ColorPen   = GetColor(m_iClut, m_iInk);
    m_ColorBrush = GetColor(m_iClut, 8 + m_iPaper);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::GetColorAt(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = X / m_iPixelsWidePerAttribute;
        // assign any transparent attributes
        unsigned int AttrOffset  = ((Y / m_iPixelsHighPerAttribute) * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        //         is attr transparent?          yes - read new attr             no - use supplied attr
        m_iInk    = (Attr & g_iInkMask   );
        m_iPaper  = (Attr & g_iPaperMask ) >> g_iPaperShift;
        m_iClut   = (Attr & g_iClutMask  ) >> g_iClutShift;
        if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::Invert(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        // swap the attributes
        Swap(Image, X, Y);
        // calculate the character position
        int dY = (int)(Y / m_iPixelsHighPerAttribute) * m_iPixelsHighPerAttribute;
        int iCols = CalculateStride(Image.Width);
        int iCX   = X / m_iPixelsWidePerAttribute;
        // calculate the offset into the pixel buffer
        unsigned int PixelOffset = ( dY * iCols) + iCX;
        // and then invert all 8 bytes of the character
        for (unsigned int i = 0; i < m_iPixelsHighPerAttribute; ++i)
        {
            Image.Pixels[PixelOffset] = Image.Pixels[PixelOffset] ^ 0x3F;
            PixelOffset += iCols;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::Swap(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        // swaps the attributes only
        // dirty the character block
        int dX = (X >> 3) << 3;
        int dY = Y;
        TRect Rect(dX, dY, dX + m_iPixelsWidePerAttribute, dY + m_iPixelsHighPerAttribute);
        Image.AddRect(Rect);
        unsigned char Attr = GetAttribute(X, Y, Image);
        unsigned char iInk    = (Attr & g_iInkMask   );
        unsigned char iPaper  = (Attr & g_iPaperMask ) >> g_iPaperShift;
        unsigned char iClut = (Attr & g_iClutMask);
        SetAttribute(X, Y, iPaper, iInk, iClut, Image);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // dirty the character block
    int dX = (X >> 3) << 3;
    int dY = Y;
    TRect Rect(dX, dY, dX + m_iPixelsWidePerAttribute, dY + m_iPixelsHighPerAttribute);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, m_iInk, m_iPaper, m_iClut, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
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
        for (int y = UpdateRect.Top; y < UpdateRect.Bottom; y += m_iPixelsHighPerAttribute)
        {
            for (int x = UpdateRect.Left; x < UpdateRect.Right; x += m_iPixelsWidePerAttribute)
            {
                unsigned char Attr   = Image.Attributes[((y / m_iPixelsHighPerAttribute) * iCols) + (x / m_iPixelsWidePerAttribute)];
                int iCX = x / m_iPixelsWidePerAttribute;
                int iInk   = (Attr & g_iInkMask);
                int iPaper = (Attr & g_iPaperMask ) >> g_iPaperShift;
                int iClut  = (Attr & g_iClutMask) >> g_iClutShift;
                TColor cInk = GetColor(iClut, iInk);
                TColor cPaper = GetColor(iClut, 8 + iPaper);
                for (unsigned int i = 0; i < m_iPixelsHighPerAttribute; ++i)
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
void __fastcall ZXSpectrumUlaPlusPalette::SetPixel(int iX, int iY, unsigned char iInk, unsigned char iPaper, unsigned char iClut, bool bSet, ZXImage& Image)
{
    //PERFORMANCE_PUSH
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX / m_iPixelsWidePerAttribute;
        // assign any transparent attributes
        unsigned int PixelOffset = (iY * iCols) + iCX;
        unsigned int AttrOffset  = (iY * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        //         is attr transparent?          yes - read new attr                      no - use supplied attr
        iInk   = (g_iTransparent == iInk   ) ?  (Attr & g_iInkMask   )                    : iInk;
        iPaper = (g_iTransparent == iPaper ) ? ((Attr & g_iPaperMask ) >> g_iPaperShift ) : iPaper;
        // set the appropreiate pixels and attribute
        unsigned char cPixelBit   = 128 >> (iX % m_iPixelsWidePerAttribute);
        unsigned char cAttribute  = (unsigned char)(iInk | (iPaper << g_iPaperShift) | (iClut << g_iClutShift));
        // set or reset the pixel
        Image.Pixels[PixelOffset] = bSet ? (Image.Pixels[PixelOffset] | cPixelBit) : (Image.Pixels[PixelOffset] & ~cPixelBit);
        // apply the attribute
        Image.Attributes[AttrOffset ] = cAttribute;
    }
    //PERFORMANCE_POP(__FUNC__)
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetPixel(int iX, int iY, unsigned char PixelByte, ZXImage* Image)
{
    if (0 <= iX && iX < Image->Width && 0 <= iY && iY < Image->Height)
    {
        int iCharWidth = CalculateStride(Image->Width);
        Image->Pixels[(iY * iCharWidth) + (iX / m_iPixelsWidePerAttribute)] = PixelByte;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetAttribute(int iX, int iY, unsigned char iInk, unsigned char iPaper, unsigned char iClut, ZXImage& Image)
{
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX / m_iPixelsWidePerAttribute;
        // assign any transparent attributes
        unsigned int AttrOffset  = (iY * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        //        is attr transparent?          yes - read new attr                        no - use supplied attr
        iInk   = (g_iTransparent == iInk   ) ?  (Attr & g_iInkMask   )                   : iInk;
        iPaper = (g_iTransparent == iPaper ) ? ((Attr & g_iPaperMask ) >> g_iPaperShift) : iPaper;
        // set the appropreiate pixels and attribute
        unsigned char cAttribute  = (unsigned char)(iInk | (iPaper << g_iPaperShift) | (iClut << g_iClutShift));
        // apply the attribute
        Image.Attributes[AttrOffset ] = cAttribute;
    }
}
//---------------------------------------------------------------------------
unsigned char __fastcall ZXSpectrumUlaPlusPalette::GetAttribute(int iX, int iY, ZXImage& Image)
{
    unsigned char Attr = 0;
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX / m_iPixelsWidePerAttribute;
        // assign any transparent attributes
        Attr = Image.Attributes[(iY * iCols) + iCX];
    }
    return Attr;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image)
{
    if (0 <= iX && iX < Image->Width && 0 <= iY && iY < Image->Height)
    {
        int iCharWidth = CalculateStride(Image->Width);
        Image->Attributes[((iY / m_iPixelsHighPerAttribute) * iCharWidth) + (iX / m_iPixelsWidePerAttribute)] = Attribute;
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXSpectrumUlaPlusPalette::Convert(ZXImage* Image, Graphics::TBitmap* Bitmap)
{
    bool bConverted = false;
    if (true == SAFE_PTR(Bitmap))
    {
        TRect Rect(0, 0, Image->Width, Image->Height);
        // convert the bitmap into a 16 color bitmap
        Bitmap->PixelFormat = pf4bit;
        // now convert each 8x8 character block into 2 colors only
        // rules:
        //  1. the most common color in the character block is the ink color
        //  2. the second most common color is the paper color
        //  3. any other color becomes an ink color
        //  4. if other 1 color then paper is black

        // loop through all the rows
        int iXS = 0;            
        int iXE = Image->Width;
        int iYS = 0;
        int iYE = Image->Height;

        for (int cy = iYS; cy < iYE; cy += m_iPixelsHighPerAttribute)
        {
            // loop through all the columns
            for (int cx = iXS; cx < iXE; cx += m_iPixelsWidePerAttribute)
            {
                unsigned char Ink   = 0;    // black ink
                unsigned char Paper = 0;    // black paper
                // find the most common colors
                FindColors(Bitmap, cx, cy, Ink, Paper);
                // set pixels according to the most common pair of colors
                SetColors(Image, Bitmap, cx, cy, Ink, Paper);
            }
        }
        bConverted = true;
    }
    return bConverted;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::FindColors(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Ink, unsigned char& Paper)
{
#if 0
    int iColorCounts[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (int y = iY; y < iY + m_iPixelsHighPerAttribute; y++)
    {
        for (int x = iX; x < iX + m_iPixelsWidePerAttribute; x++)
        {
            if (0 <= x && x < Bitmap->Width && 0 <= y && y < Bitmap->Height)
            {
                iColorCounts[GetColorIndex(Bitmap->Canvas->Pixels[x][y])]++;
            }
        }
    }

    // find the most common ink color (ie. not black!)
    unsigned char iInk = 1;
    for (int i = 1; i < 16; i++)
    {
        if (0 != iColorCounts[i] && iColorCounts[iInk] <= iColorCounts[i])
        {
            iInk = i;
            Ink  = i;
        }
    }
    unsigned char iPaper = Ink;
    iColorCounts[iInk] = 0;
    // find the most common other color (includes black)
    for (int i = 0; i < 16; i++)
    {
        if (iColorCounts[iPaper] < iColorCounts[i])
        {
            iPaper = i;
            Paper  = i;
        }
    }
#endif
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Ink, unsigned char Paper)
{
#if 0
    unsigned char Bright = Ink > 7 ? 0x40 : 0x00;
    for (int y = iY; y < iY + m_iPixelsHighPerAttribute; y++)
    {
        unsigned char Pixels = 0;
        for (int x = iX; x < iX + m_iPixelsWidePerAttribute; x++)
        {
            // change the non-ink/paper colors to the ink color
            if (Bitmap->Canvas->Pixels[x][y] != g_ConvertColors[Ink] && Bitmap->Canvas->Pixels[x][y] != g_ConvertColors[Paper])
            {
                Bitmap->Canvas->Pixels[x][y] = g_ConvertColors[Ink];
            }
            int iBit = 0x80 >> (x % m_iPixelsWidePerAttribute);
            Pixels |= (Bitmap->Canvas->Pixels[x][y] == g_ConvertColors[Ink] && 0 != Ink ) ? iBit : 0;
        }
        SetPixel(iX, y, Pixels, Image);
    }
    Ink   = Ink   & 0x07;
    Paper = Paper & 0x07;
    unsigned char Attribute = Ink | (Paper << g_iPaperShift) | Bright;
    SetAttribute(iX, iY, Attribute, Image);
#endif
}
//---------------------------------------------------------------------------
unsigned char __fastcall ZXSpectrumUlaPlusPalette::GetColorIndex(TColor Color)
{
    unsigned char ColorIndex = 0;
    for (unsigned int i = 0; i < 64; i++)
    {
        // TODO: Find color in palette
        /*if (Color == g_ConvertColors[i] || Color == g_ColorsSpectrum[i])
        {
            ColorIndex = i;
            break;
        }*/
    }
    return ColorIndex;
}
//---------------------------------------------------------------------------
String __fastcall ZXSpectrumUlaPlusPalette::GetName(void)
{
    return g_sPaletteName;
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall ZXSpectrumUlaPlusPalette::GetColorTable(void)
{
    KXmlInfo* colorTable = new KXmlInfo("Colors");
    for (unsigned int i = 0; i < 64; i++)
    {
        colorTable->Add("Color", m_Palette[i]);
    }

    return colorTable;
}
//---------------------------------------------------------------------------
bool __fastcall ZXSpectrumUlaPlusPalette::SetColorTable(KXmlInfo& xmlInfo)
{
    KXmlInfo* pColors = xmlInfo.GetNode("Colors");
    if (true == SAFE_PTR(pColors))
    {
        if (64 == pColors->size())
        {
            int i = 0;
            for (KXmlNodes::iterator it = pColors->begin(); it != pColors->end(); i++, it++)
            {
                m_Palette[i] = (*it)->GetInt();
            }
            UpdateLoadedPalette();
            UpdateColorTable();
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::Loaded(void)
{
    // check if color table is blank
    unsigned int blankCheck = 0;
    for (int i = 0; i < 64; i++)
    {
        blankCheck += ZXPalette::GetColor(i);
    }
    if (blankCheck != 0)
    {
        // color table is not blank; so use it
        for (int i = 0; i < 64; i++)
        {
            TColor color = ZXPalette::GetColor(i);
            // convert TColor to 8 bit RGB (3R3G2B)
            unsigned char R = (color & 0x000000E0) >>  5;
            unsigned char G = (color & 0x0000E000) >> 13;
            unsigned char B = (color & 0x00C00000) >> 22;
            SetColor(i, R, G, B);
        }
    }
    UpdateLoadedPalette();
    // update color table anyway
    UpdateColorTable();
}
//---------------------------------------------------------------------------
String __fastcall ZXSpectrumUlaPlusPalette::GetColorAsString(ZXImage& Image, int X, int Y)
{
    String sColor("None");
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        // assign any transparent attributes
        unsigned int AttrOffset  = ((Y / m_iPixelsHighPerAttribute) * iCols) + (X / m_iPixelsWidePerAttribute);
        unsigned char Attr = Image.Attributes[AttrOffset];
        sColor  = "C:" + IntToStr((Attr & g_iClutMask) >> g_iClutShift);
        sColor += ",P:" + IntToStr((Attr & g_iPaperMask) >> g_iPaperShift);
        sColor += ",I:" + IntToStr(Attr & g_iInkMask);
    }
    return sColor;
}
//---------------------------------------------------------------------------
TColor __fastcall ZXSpectrumUlaPlusPalette::GetColor(unsigned int index)
{
    TColor color = clFuchsia;
    if (index < 64)
    {
        unsigned char R, G, B;
        GetColor(index, R, G, B);
        color = (TColor)((B << 16) | (G << 8) | (R));
    }
    return color;
}
//---------------------------------------------------------------------------
TColor __fastcall ZXSpectrumUlaPlusPalette::GetColor(unsigned int clut, unsigned int index)
{
    return GetColor(clut * 16 + index);
}
//---------------------------------------------------------------------------
unsigned char __fastcall ZXSpectrumUlaPlusPalette::GetColor(unsigned char R, unsigned char G, unsigned char B)
{
    return (R << g_iRedShift) | (G << g_iGreenShift) | B;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::GetColor(unsigned int clut, unsigned int index, unsigned char& R, unsigned char& G, unsigned char& B)
{
    R = 0;
    G = 0;
    B = 0;
    index += clut * 16;
    if (index < 64)
    {
        unsigned char color = m_Palette[index];
        R = (color & g_iRedMask  ) >> g_iRedShift;
        G = (color & g_iGreenMask) >> g_iGreenShift;
        B = (color & g_iBlueMask );
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::GetColor(unsigned int index, unsigned char& R, unsigned char& G, unsigned char& B)
{
    R = 0;
    G = 0;
    B = 0;
    if (index < 64)
    {
        unsigned char color = m_Palette[index];
        R = (color & g_iRedMask) << 3;
        G = (color & g_iGreenMask);
        B = (color & g_iBlueMask) == 0 ? 0 : ((color & g_iBlueMask) << 1 | 1) << 5;

        R |= (R >> 3) | (R >> 6);
        G |= (G >> 3) | (G >> 6);
        B |= (B >> 3) | (B >> 6);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetColor(unsigned int index, unsigned char R, unsigned char G, unsigned char B)
{
    if (index < 64)
    {
        m_Palette[index] = ((G & 0x07) << g_iGreenShift) | ((R & 0x07) << g_iRedShift) | (B & 0x03);
        ZXPalette::SetColor(index, GetColor(index));
        UpdateLoadedPalette();
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::SetColor(unsigned int clut, unsigned int index, unsigned char R, unsigned char G, unsigned char B)
{
    SetColor(clut * 16 + index, R, G, B);
}
//---------------------------------------------------------------------------
TColor __fastcall ZXSpectrumUlaPlusPalette::DecodeColor(unsigned char RGB)
{
    unsigned char R = (RGB & g_iRedMask) << 3;
    unsigned char G = (RGB & g_iGreenMask);
    unsigned char B = (RGB & g_iBlueMask) == 0 ? 0 : ((RGB & g_iBlueMask) << 1 | 1) << 5;

    R |= (R >> 3) | (R >> 6);
    G |= (G >> 3) | (G >> 6);
    B |= (B >> 3) | (B >> 6);

    return (TColor)((B << 16) | (G << 8) | (R));
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumUlaPlusPalette::DecodeColor(unsigned char RGB, unsigned char& R, unsigned char& G, unsigned char& B)
{
    R = (RGB & g_iRedMask) >> g_iRedShift;
    G = (RGB & g_iGreenMask) >> g_iGreenShift;
    B = (RGB & g_iBlueMask);
}
//---------------------------------------------------------------------------

