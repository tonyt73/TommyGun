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
using namespace Enterprise64AttributePalette;
//---------------------------------------------------------------------------
#define RED(x)   (((x & 1)<<2)+((x &  8)>>2)+((x &  64)>>6))
#define GREEN(x) (((x & 2)<<1)+((x & 16)>>3)+((x & 128)>>7))
#define BLUE(x)  (((x & 4)>>1)+((x & 32)>>5)               )
unsigned int Level_8[8] = { 0, 36,  73, 109, 146, 182, 218, 255 };
unsigned int Level_4[4] = { 0, 85, 170, 255                     };
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
    0x01,
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
__fastcall EnterpriseAttributePalette::EnterpriseAttributePalette()
: ZXPalette(16, 320, 256),
  m_iInk(15),
  m_iPaper(0),
  m_bInkTransparent(false),
  m_bPaperTransparent(false)
{
    m_bCanConvert = true;
    PalSignature(m_sSignature);
    Initialize();
    m_ColorPen    = GetColor(m_iInk  );
    m_ColorBrush  = GetColor(m_iPaper);
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::Initialize(void)
{
    m_PixelFormat               = pf32bit;
    // initialize our palette information
    m_iBitsPerPixel             = 1;
    m_iBitsPerAttribute         = 8;
    m_iPixelsWidePerAttribute   = 8;
    m_iPixelsHighPerAttribute   = 1;
    m_fPixelsPerByte            = 8.f;
    m_bSupportsPixelsOnly       = false;
    // normally we would initialize the color table
    Reset();
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::SetInk(unsigned char iInk)
{
    m_iInk = iInk;
    m_ColorPen = GetColor(m_iInk);
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::SetPaper(unsigned char iPaper)
{
    m_iPaper = iPaper;
    m_ColorBrush = GetColor(m_iPaper);
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::SetBias(unsigned char iFixBias)
{
    iFixBias     = std::max((unsigned char)0, std::min((unsigned char)31, iFixBias));
    m_iFixBias   = iFixBias;
    for (int i = 0; i < 8; i++)
    {
        SetColor( 8 + i, Get256Color((iFixBias * 8) + i));
    }
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::SetColorAt(ZXImage& Image, int X, int Y)
{
    // sets the color in the palette to the color
    // dirty the character block
    int dX = (X >> 3) << 3;
    //int dY = Y;//(Y >> 3) << 3;
    TRect Rect(dX, Y, dX + 1, Y + 1);
    Image.AddRect(Rect);
    SetAttribute(X, Y, m_iInk, m_iPaper, Image);
    m_ColorPen   = GetColor(m_iInk  );
    m_ColorBrush = GetColor(m_iPaper);
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::GetColorAt(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = X >> 3;
        // assign any transparent attributes
        unsigned int AttrOffset  = (Y * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        //         is attr transparent?          yes - read new attr             no - use supplied attr
        m_iInk        = (Attr & g_iInkMask   )        ;
        m_iPaper      = (Attr & g_iPaperMask ) >> 4   ;
        if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::Invert(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        // swap the attributes
        Swap(Image, X, Y);
        // calculate the character position
        int iCols = CalculateStride(Image.Width);
        int iCX   = X >> 3;
        // calculate the offset into the pixel buffer
        unsigned int PixelOffset = (Y * iCols) + iCX;
        // and then invert all 8 bytes of the character
        //for (int i = 0; i < 1; ++i)
        {
            Image.Pixels[PixelOffset] = Image.Pixels[PixelOffset] ^ 0xFF;
            //PixelOffset += iCols;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::Swap(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        // swaps the attributes only
        // dirty the character block
        int dX = (X >> 3) << 3;
        //int dY = (Y >> 3) << 3;
        TRect Rect(dX, Y, dX + 8, Y + 1);
        Image.AddRect(Rect);
        unsigned char Attr        = GetAttribute(X, Y, Image);
        unsigned char iInk        = (Attr & g_iInkMask   )        ;
        unsigned char iPaper      = (Attr & g_iPaperMask ) >> 4   ;
        SetAttribute(X, Y, iPaper, iInk, Image);
    }
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // dirty the character block
    int dX = (X >> 3) << 3;
    //int dY = (Y >> 3) << 3;
    TRect Rect(dX, Y, dX + 8, Y + 1);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, m_iInk, m_iPaper, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
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
            for (int x = UpdateRect.Left; x < UpdateRect.Right; x += 8)
            {
                unsigned char Attr   = Image.Attributes[(y * iCols) + (x >> 3)];
                int iCX = x >> 3;
                int iInk        = (Attr & g_iInkMask   );
                int iPaper      = (Attr & g_iPaperMask ) >> 4;
                TColor cPaper = ShowAttributes ? GetColor(iPaper) : clBlack;
                TColor cInk   = ShowAttributes ? GetColor(iInk  ) : clWhite;
                //for (int i = 0; i < 8; ++i)
                {
                    unsigned char Pixels = Image.Pixels[(y * iCols) + iCX];
                    Bitmap->Canvas->Pixels[x+0][y] = (Pixels & g_cPixelMasks[0]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+1][y] = (Pixels & g_cPixelMasks[1]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+2][y] = (Pixels & g_cPixelMasks[2]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+3][y] = (Pixels & g_cPixelMasks[3]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+4][y] = (Pixels & g_cPixelMasks[4]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+5][y] = (Pixels & g_cPixelMasks[5]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+6][y] = (Pixels & g_cPixelMasks[6]) ? cInk : cPaper;
                    Bitmap->Canvas->Pixels[x+7][y] = (Pixels & g_cPixelMasks[7]) ? cInk : cPaper;
                }
            }
        }
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::SetPixel(int iX, int iY, unsigned char iInk, unsigned char iPaper, bool bSet, ZXImage& Image)
{
    //PERFORMANCE_PUSH
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX >> 3;
        // assign any transparent attributes
        unsigned int Offset = (iY * iCols) + iCX;
        unsigned char Attr = Image.Attributes[Offset];
        //         is attr transparent?          yes - read new attr             no - use supplied attr
        iInk        = (m_bInkTransparent  ) ?  (Attr & g_iInkMask   )          : iInk;
        iPaper      = (m_bPaperTransparent) ? ((Attr & g_iPaperMask ) >> 4   ) : iPaper;
        // set the appropreiate pixels and attribute
        unsigned char cPixelBit   = 128 >> (iX % 8);
        unsigned char cAttribute  = (unsigned char)(iInk | (iPaper << 4));
        // set or reset the pixel
        Image.Pixels[Offset] = bSet ? (Image.Pixels[Offset] | cPixelBit) : (Image.Pixels[Offset] & ~cPixelBit);
        // apply the attribute
        Image.Attributes[Offset ] = cAttribute;
    }
    //PERFORMANCE_POP(__FUNC__)
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::SetPixel(int iX, int iY, unsigned char PixelByte, ZXImage* Image)
{
    if (0 <= iX && iX < Image->Width && 0 <= iY && iY < Image->Height)
    {
        int iCharWidth = CalculateStride(Image->Width);
        Image->Pixels[(iY * iCharWidth) + (iX / 8)] = PixelByte;
    }
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::SetAttribute(int iX, int iY, unsigned char iInk, unsigned char iPaper, ZXImage& Image)
{
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX >> 3;
        // assign any transparent attributes
        unsigned int AttrOffset  = (iY * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        //         is attr transparent?          yes - read new attr             no - use supplied attr
        iInk        = (m_bInkTransparent  ) ?  (Attr & g_iInkMask   )          : iInk;
        iPaper      = (m_bPaperTransparent) ? ((Attr & g_iPaperMask ) >> 4   ) : iPaper;
        // set the appropreiate pixels and attribute
        unsigned char cAttribute  = (unsigned char)(iInk | (iPaper << 4));
        // apply the attribute
        Image.Attributes[AttrOffset ] = cAttribute;
    }
}
//---------------------------------------------------------------------------
unsigned char __fastcall EnterpriseAttributePalette::GetAttribute(int iX, int iY, ZXImage& Image)
{
    unsigned char Attr = 0;
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX >> 3;
        // assign any transparent attributes
        Attr = Image.Attributes[(iY * iCols) + iCX];
    }
    return Attr;
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image)
{
    if (0 <= iX && iX < Image->Width && 0 <= iY && iY < Image->Height)
    {
        int iCharWidth = CalculateStride(Image->Width);
        Image->Attributes[(iY * iCharWidth) + (iX / 8)] = Attribute;
    }
}
//---------------------------------------------------------------------------
bool __fastcall EnterpriseAttributePalette::Convert(ZXImage* Image, Graphics::TBitmap* Bitmap)
{
    bool bConverted = false;
    if (true == SAFE_PTR(Bitmap))
    {
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

        for (int cy = iYS; cy < iYE; cy++)
        {
            // loop through all the columns
            for (int cx = iXS; cx < iXE; cx += 8)
            {
                unsigned char Ink   = 0;    // black ink
                unsigned char Paper = 0;    // black paper
                // find the most common colors
                FindColors(Bitmap, cx, cy, Ink, Paper);
                // set pixels according to the most common pair of colors
                SetColors (Image, Bitmap, cx, cy, Ink, Paper);
            }
        }
        bConverted = true;
    }
    return bConverted;
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::FindColors(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Ink, unsigned char& Paper)
{
    int iColorCounts[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //for (int y = iY; y < iY + 1; y++)
    {
        for (int x = iX; x < iX + 8; x++)
        {
            if (0 <= x && x < Bitmap->Width && 0 <= iY && iY < Bitmap->Height)
            {
                iColorCounts[GetColorIndex(Bitmap->Canvas->Pixels[x][iY])]++;
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
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Ink, unsigned char Paper)
{
    //for (int y = iY; y < iY + 8; y++)
    {
        unsigned char Pixels = 0;
        for (int x = iX; x < iX + 8; x++)
        {
            // change the non-ink/paper colors to the ink color
            if (Bitmap->Canvas->Pixels[x][iY] != g_ConvertColors[Ink] && Bitmap->Canvas->Pixels[x][iY] != g_ConvertColors[Paper])
            {
                Bitmap->Canvas->Pixels[x][iY] = g_ConvertColors[Ink];
            }
            int iBit = 0x80 >> (x % 8);
            Pixels |= (Bitmap->Canvas->Pixels[x][iY] == g_ConvertColors[Ink] && 0 != Ink ) ? iBit : 0;
        }
        SetPixel(iX, iY, Pixels, Image);
    }

    Ink   &= 0x0F;
    Paper &= 0x0F;
    unsigned char Attribute = Ink | (Paper << 4);
    SetAttribute(iX, iY, Attribute, Image);
}
//---------------------------------------------------------------------------
unsigned char __fastcall EnterpriseAttributePalette::GetColorIndex(TColor Color)
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
String __fastcall EnterpriseAttributePalette::GetColorAsString(ZXImage& Image, int X, int Y)
{
    String sColor("None");
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = X >> 3;
        // assign any transparent attributes
        unsigned int AttrOffset  = (Y * iCols) + iCX;
        unsigned char Attr = Image.Attributes[AttrOffset];
        sColor  = g_sColors[(Attr & 0x0F)     ] + " ";
        sColor += g_sColors[(Attr & 0xF0) >> 4];
    }
    return sColor;
}
//---------------------------------------------------------------------------
TColor __fastcall EnterpriseAttributePalette::Get256Color(int iIndex)
{
    unsigned int R, G, B;

    R = Level_8[RED  (iIndex)] <<  0;
    G = Level_8[GREEN(iIndex)] <<  8;
    B = Level_4[BLUE (iIndex)] << 16;

    TColor Colour = (TColor)(R | G | B);
    return Colour;
}
//---------------------------------------------------------------------------
int __fastcall EnterpriseAttributePalette::GetBiasColor(int iIndex)
{
    if (iIndex < 8)
        return iIndex;
    return (FixBias * 8) + (iIndex - 8);
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::Set256Color(unsigned char iColor, unsigned iIndex)
{
    if (iColor < 8)
    {
        SetColor(iColor, Get256Color(iIndex));
    }
    else
    {
        FixBias = iIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::Reset(void)
{
    // reset 8-15
    FixBias = 31;
    // reset 0-7
    for (int i = 0; i < 8; i++)
    {
        SetColor(i, Get256Color(i));
    }
}
//---------------------------------------------------------------------------
void __fastcall EnterpriseAttributePalette::Loaded(void)
{
    frmEnterpriseAttributePalette->OnUpdatePaletteGUI();
}
//---------------------------------------------------------------------------

