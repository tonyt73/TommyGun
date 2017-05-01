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
const   String  g_sPaletteName = "ZX Spectrum Next (256 Color)";
//---------------------------------------------------------------------------
const unsigned int g_iRedMask = 0x000000FF;
const unsigned int g_iGrnMask = 0x0000FF00;
const unsigned int g_iBluMask = 0x00FF0000;
const unsigned int g_iRedShift = 0;
const unsigned int g_iGrnShift = 8;
const unsigned int g_iBluShift = 16;
//---------------------------------------------------------------------------
__fastcall ZXSpectrumNextPalette::ZXSpectrumNextPalette()
: ZXPalette(256, 256, 192, false),
  m_iPen(15),
  m_iBrush(0)
{
	m_bCanConvert = false;
	PalSignature(m_sSignature);
	Initialize();
	m_ColorPen    = ZXPalette::GetColor(m_iPen);
	m_ColorBrush  = ZXPalette::GetColor(m_iBrush);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::Initialize(void)
{
	m_PixelFormat               = pf32bit;
	// initialize our palette information
	m_iBitsPerPixel             = 8;
	m_iBitsPerAttribute         = 1;
	m_iPixelsWidePerAttribute   = 1;
	m_iPixelsHighPerAttribute   = 1;
	m_fPixelsPerByte            = 1.f;
    m_bSupportsPixelsOnly       = false;
    UseDefaultPalette();
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::UseImagePalette(void)
{
//    memcpy(m_Palette, m_LoadedPalette, sizeof(m_Palette));
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::UseDefaultPalette(void)
{
	static unsigned int defaultPalette[] = {
		0x000000, 0x800000, 0x008000, 0x808000, 0x000080, 0x800080, 0x008080, 0xc0c0c0, 0x808080, 0xff0000, 0x00ff00, 0xffff00, 0x0000ff, 0xff00ff, 0x00ffff, 0xffffff,
		0x000000, 0x00005f, 0x000087, 0x0000af, 0x0000d7, 0x0000ff, 0x005f00, 0x005f5f, 0x005f87, 0x005faf, 0x005fd7, 0x005fff, 0x008700, 0x00875f, 0x008787, 0x0087af,
		0x0087d7, 0x0087ff, 0x00af00, 0x00af5f, 0x00af87, 0x00afaf, 0x00afd7, 0x00afff, 0x00d700, 0x00d75f, 0x00d787, 0x00d7af, 0x00d7d7, 0x00d7ff, 0x00ff00, 0x00ff5f,
		0x00ff87, 0x00ffaf, 0x00ffd7, 0x00ffff, 0x5f0000, 0x5f005f, 0x5f0087, 0x5f00af, 0x5f00d7, 0x5f00ff, 0x5f5f00, 0x5f5f5f, 0x5f5f87, 0x5f5faf, 0x5f5fd7, 0x5f5fff,
		0x5f8700, 0x5f875f, 0x5f8787, 0x5f87af, 0x5f87d7, 0x5f87ff, 0x5faf00, 0x5faf5f, 0x5faf87, 0x5fafaf, 0x5fafd7, 0x5fafff, 0x5fd700, 0x5fd75f, 0x5fd787, 0x5fd7af,
		0x5fd7d7, 0x5fd7ff, 0x5fff00, 0x5fff5f, 0x5fff87, 0x5fffaf, 0x5fffd7, 0x5fffff, 0x870000, 0x87005f, 0x870087, 0x8700af, 0x8700d7, 0x8700ff, 0x875f00, 0x875f5f,
		0x875f87, 0x875faf, 0x875fd7, 0x875fff, 0x878700, 0x87875f, 0x878787, 0x8787af, 0x8787d7, 0x8787ff, 0x87af00, 0x87af5f, 0x87af87, 0x87afaf, 0x87afd7, 0x87afff,
		0x87d700, 0x87d75f, 0x87d787, 0x87d7af, 0x87d7d7, 0x87d7ff, 0x87ff00, 0x87ff5f, 0x87ff87, 0x87ffaf, 0x87ffd7, 0x87ffff, 0xaf0000, 0xaf005f, 0xaf0087, 0xaf00af,
		0xaf00d7, 0xaf00ff, 0xaf5f00, 0xaf5f5f, 0xaf5f87, 0xaf5faf, 0xaf5fd7, 0xaf5fff, 0xaf8700, 0xaf875f, 0xaf8787, 0xaf87af, 0xaf87d7, 0xaf87ff, 0xafaf00, 0xafaf5f,
		0xafaf87, 0xafafaf, 0xafafd7, 0xafafff, 0xafd700, 0xafd75f, 0xafd787, 0xafd7af, 0xafd7d7, 0xafd7ff, 0xafff00, 0xafff5f, 0xafff87, 0xafffaf, 0xafffd7, 0xafffff,
		0xd70000, 0xd7005f, 0xd70087, 0xd700af, 0xd700d7, 0xd700ff, 0xd75f00, 0xd75f5f, 0xd75f87, 0xd75faf, 0xd75fd7, 0xd75fff, 0xd78700, 0xd7875f, 0xd78787, 0xd787af,
		0xd787d7, 0xd787ff, 0xd7af00, 0xd7af5f, 0xd7af87, 0xd7afaf, 0xd7afd7, 0xd7afff, 0xd7d700, 0xd7d75f, 0xd7d787, 0xd7d7af, 0xd7d7d7, 0xd7d7ff, 0xd7ff00, 0xd7ff5f,
		0xd7ff87, 0xd7ffaf, 0xd7ffd7, 0xd7ffff, 0xff0000, 0xff005f, 0xff0087, 0xff00af, 0xff00d7, 0xff00ff, 0xff5f00, 0xff5f5f, 0xff5f87, 0xff5faf, 0xff5fd7, 0xff5fff,
		0xff8700, 0xff875f, 0xff8787, 0xff87af, 0xff87d7, 0xff87ff, 0xffaf00, 0xffaf5f, 0xffaf87, 0xffafaf, 0xffafd7, 0xffafff, 0xffd700, 0xffd75f, 0xffd787, 0xffd7af,
		0xffd7d7, 0xffd7ff, 0xffff00, 0xffff5f, 0xffff87, 0xffffaf, 0xffffd7, 0xffffff, 0x080808, 0x121212, 0x1c1c1c, 0x262626, 0x303030, 0x3a3a3a, 0x444444, 0x4e4e4e,
		0x585858, 0x626262, 0x6c6c6c, 0x767676, 0x808080, 0x8a8a8a, 0x949494, 0x9e9e9e, 0xa8a8a8, 0xb2b2b2, 0xbcbcbc, 0xc6c6c6, 0xd0d0d0, 0xdadada, 0xe4e4e4, 0xeeeeee
	};

	for (unsigned int i = 0; i < 256; i++)
	{
		// swap rgb to bgr
		unsigned bgr = ((defaultPalette[i] & 0x00FF0000) >> 16) | (defaultPalette[i] & 0x0000FF00) | ((defaultPalette[i] & 0x000000FF) << 16);
		m_Palette[i] = bgr;
		SetColor(i, TColor(bgr));
	}
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::UseZXSpectrumPalette(void)
{
//	unsigned char palette[64] =
//    {
//        0, 2, 24, 26, 192, 195, 216, 219, 0, 2, 24, 26, 192, 195, 216, 219,
//        0, 3, 28, 31, 224, 227, 252, 255, 0, 3, 28, 31, 224, 227, 252, 255,
//        0, 2, 24, 26, 192, 195, 216, 219, 0, 2, 24, 26, 192, 195, 216, 219,
//        0, 3, 28, 31, 224, 227, 252, 255, 0, 3, 28, 31, 224, 227, 252, 255
//    };
//
//    memcpy(m_Palette, palette, sizeof(palette));
//	UpdateColorTable();
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::UpdateLoadedPalette(void)
{
	// copy the current palette into the images loaded palette. aka: save the original palette
//    memcpy(m_LoadedPalette, m_Palette, sizeof(m_Palette));
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::UpdateColorTable(void)
{
//    for (int i = 0; i < 64; i++)
//    {
//        ZXPalette::SetColor(i, GetColor(i));
//    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::SetPen(unsigned char iPen)
{
	m_iPen       = iPen;
	m_ColorPen   = ZXPalette::GetColor(m_iPen);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::SetBrush(unsigned char iBrush)
{
	m_iBrush     = iBrush;
    m_ColorBrush = ZXPalette::GetColor(m_iBrush);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::SetColorAt(ZXImage& Image, int X, int Y)
{
    // sets the color in the palette to the color
    // dirty the character block
	int dX = X;
	int dY = Y;
    TRect Rect(dX, dY, dX + m_iPixelsWidePerAttribute, dY + m_iPixelsHighPerAttribute);
    Image.AddRect(Rect);
	m_ColorPen   = ZXPalette::GetColor(m_iPen);
    m_ColorBrush = ZXPalette::GetColor(m_iBrush);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::GetColorAt(ZXImage& Image, int X, int Y)
{
    if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = X / m_iPixelsWidePerAttribute;
		// assign any transparent attributes
		unsigned int Offset  = ((Y / m_iPixelsHighPerAttribute) * iCols) + iCX;
		unsigned char ColorIndex = Image.Pixels[Offset];
		m_iPen    = ColorIndex;
		//m_iBrush  = ColorIndex;
		if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::Invert(ZXImage& Image, int X, int Y)
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
void __fastcall ZXSpectrumNextPalette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // dirty the character block
	TRect Rect(X, Y, X + m_iPixelsWidePerAttribute, Y + m_iPixelsHighPerAttribute);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, m_iPen, m_iBrush, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
{
    //PERFORMANCE_PUSH
    // loop through the character block and set all the Pen and Brush values
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
                unsigned char ColorIndex = Image.Pixels[((y / m_iPixelsHighPerAttribute) * iCols) + (x / m_iPixelsWidePerAttribute)];
				Bitmap->Canvas->Pixels[x][y] = ZXPalette::GetColor(ColorIndex);
			}
        }
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::SetPixel(int iX, int iY, unsigned char iPen, unsigned char iBrush, bool bSet, ZXImage& Image)
{
	SetPixel(iX, iY, bSet ? iPen : iBrush, Image);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::SetPixel(int iX, int iY, unsigned char PixelByte, ZXImage& Image)
{
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        Image.Pixels[(iY * Image.Width) + iX] = PixelByte;
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXSpectrumNextPalette::Convert(ZXImage* Image, Graphics::TBitmap* Bitmap)
{
    bool bConverted = false;
    if (true == SAFE_PTR(Bitmap))
    {
		TRect Rect(0, 0, Image->Width, Image->Height);
        // convert the bitmap into a 256 color bitmap
        Bitmap->PixelFormat = pf8bit;
        // now convert each 8x8 character block into 2 colors only
        // rules:
        //  1. the most common color in the character block is the Pen color
        //  2. the second most common color is the Brush color
        //  3. any other color becomes an Pen color
        //  4. if other 1 color then Brush is black

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
                unsigned char Pen   = 0;    // black Pen
                unsigned char Brush = 0;    // black Brush
                // find the most common colors
                FindColors(Bitmap, cx, cy, Pen, Brush);
                // set pixels according to the most common pair of colors
                SetColors(Image, Bitmap, cx, cy, Pen, Brush);
            }
        }
        bConverted = true;
    }
    return bConverted;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::FindColors(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Pen, unsigned char& Brush)
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

    // find the most common Pen color (ie. not black!)
    unsigned char iPen = 1;
    for (int i = 1; i < 16; i++)
    {
        if (0 != iColorCounts[i] && iColorCounts[iPen] <= iColorCounts[i])
        {
            iPen = i;
            Pen  = i;
        }
    }
    unsigned char iBrush = Pen;
    iColorCounts[iPen] = 0;
    // find the most common other color (includes black)
    for (int i = 0; i < 16; i++)
    {
        if (iColorCounts[iBrush] < iColorCounts[i])
        {
            iBrush = i;
            Brush  = i;
        }
    }
#endif
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Pen, unsigned char Brush)
{
#if 0
    unsigned char Bright = Pen > 7 ? 0x40 : 0x00;
    for (int y = iY; y < iY + m_iPixelsHighPerAttribute; y++)
    {
        unsigned char Pixels = 0;
        for (int x = iX; x < iX + m_iPixelsWidePerAttribute; x++)
        {
            // change the non-Pen/Brush colors to the Pen color
            if (Bitmap->Canvas->Pixels[x][y] != g_ConvertColors[Pen] && Bitmap->Canvas->Pixels[x][y] != g_ConvertColors[Brush])
            {
                Bitmap->Canvas->Pixels[x][y] = g_ConvertColors[Pen];
            }
            int iBit = 0x80 >> (x % m_iPixelsWidePerAttribute);
            Pixels |= (Bitmap->Canvas->Pixels[x][y] == g_ConvertColors[Pen] && 0 != Pen ) ? iBit : 0;
        }
        SetPixel(iX, y, Pixels, Image);
	}
    Pen   = Pen   & 0x07;
    Brush = Brush & 0x07;
    unsigned char Attribute = Pen | (Brush << g_iBrushShift) | Bright;
    SetAttribute(iX, iY, Attribute, Image);
#endif
}
//---------------------------------------------------------------------------
unsigned char __fastcall ZXSpectrumNextPalette::GetColorIndex(TColor Color)
{
    unsigned char ColorIndex = 0;
    for (unsigned int i = 0; i < 256; i++)
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
String __fastcall ZXSpectrumNextPalette::GetName(void)
{
    return g_sPaletteName;
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall ZXSpectrumNextPalette::GetColorTable(void)
{
    KXmlInfo* colorTable = new KXmlInfo("Colors");
    for (unsigned int i = 0; i < 256; i++)
    {
        colorTable->Add("Color", m_Palette[i]);
    }

    return colorTable;
}
//---------------------------------------------------------------------------
bool __fastcall ZXSpectrumNextPalette::SetColorTable(KXmlInfo& xmlInfo)
{
    KXmlInfo* pColors = xmlInfo.GetNode("Colors");
    if (true == SAFE_PTR(pColors))
    {
        if (256 == pColors->size())
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
void __fastcall ZXSpectrumNextPalette::Loaded(void)
{
    // check if color table is blank
//    unsigned int blankCheck = 0;
//    for (int i = 0; i < 64; i++)
//    {
//        blankCheck += ZXPalette::GetColor(i);
//    }
//    if (blankCheck != 0)
//    {
//        // color table is not blank; so use it
//        for (int i = 0; i < 64; i++)
//        {
//            TColor color = ZXPalette::GetColor(i);
//            // convert TColor to 8 bit RGB (3R3G2B)
//            unsigned char R = (color & 0x000000E0) >>  5;
//            unsigned char G = (color & 0x0000E000) >> 13;
//            unsigned char B = (color & 0x00C00000) >> 22;
//            SetColor(i, R, G, B);
//        }
//    }
//    UpdateLoadedPalette();
//    // update color table anyway
//    UpdateColorTable();
}
//---------------------------------------------------------------------------
String __fastcall ZXSpectrumNextPalette::GetColorAsString(ZXImage& Image, int X, int Y)
{
	String sColor("None");
	if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
	{
		unsigned int Offset  = (X / m_iBitsPerPixel) + (Y * Image.Width);
		unsigned char ColorIndex = Image.Pixels[Offset];
		unsigned char R, G, B;
		GetColor(ColorIndex, R, G, B);

		sColor +=  "R:" + IntToStr(R);
		sColor += " G:" + IntToStr(G);
		sColor += " B:" + IntToStr(B);
	}
	return sColor;
}
//---------------------------------------------------------------------------
//unsigned char __fastcall ZXSpectrumNextPalette::GetColor(unsigned char R, unsigned char G, unsigned char B)
//{
//	//return (R << 16) | (G << 8) | B;
//	return 0;
//}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::GetColor(unsigned int index, unsigned char& R, unsigned char& G, unsigned char& B)
{
	R = 0;
	G = 0;
	B = 0;
	if (index < 256)
	{
		unsigned int color = m_Palette[index];
		R = (color & g_iRedMask) >> g_iRedShift;
		G = (color & g_iGrnMask) >> g_iGrnShift;
		B = (color & g_iBluMask) >> g_iBluShift;
	}
}
//---------------------------------------------------------------------------
//void __fastcall ZXSpectrumNextPalette::SetColor(unsigned int index, unsigned char R, unsigned char G, unsigned char B)
//{
//	if (index < 256)
//	{
//        m_Palette[index] = ((B << g_iBluShift) | ((G << g_iGrnShift) | (R << g_iRedShift);
//        ZXPalette::SetColor(index, GetColor(index));
//        UpdateLoadedPalette();
//    }
//}
//---------------------------------------------------------------------------

