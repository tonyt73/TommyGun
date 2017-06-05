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
#include <iostream>
#include <fstream>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
//using namespace Imaging;
using namespace SpectrumPalette;
//---------------------------------------------------------------------------
const   String  g_sPaletteName = "Spectrum Next (256 Color)";
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
    m_bSupportsPixelsOnly       = true;
    m_iDefaultSpriteWidth       = 16;
    m_iDefaultSpriteHeight      = 16;
    m_iIncSpriteWidth           = 16;
    m_iIncSpriteHeight          = 16;
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
    //std::ofstream myfile;
    //myfile.open("D:\\SpecNext256.csv");
	for (unsigned int i = 0; i < 256; i++)
	{
		// convert rgb332 to rgb888
		unsigned char r = (i & 0xE0);
        unsigned char g = (i & 0x1C) << 3;
        unsigned char b = (i & 0x03) << 6;
        r = r | r >> 3 | r >> 6;
        g = g | g >> 3 | g >> 6;
        b = b | b >> 2 | b >> 4 | b >> 6;
        unsigned int rgb = b << 16 | g << 8 | r;
		SetColor(i, TColor(rgb));
        //myfile << IntToHex((int)rgb,6).c_str() << ", " << IntToStr(r).c_str() << ", " << IntToStr(g).c_str() << ", " << IntToStr(b).c_str() <<"\n";
	}
    //myfile.close();

    /*String file = "D:\\SpecNext256.hsb.dist.csv";
    myfile.open(file.c_str());
    for (int i = 0; i < 256; i++)
	{
        String line = "";
        myfile << line.c_str();
        for (unsigned int j = 0; j < 256; j++)
        {
            float hD = ZXPalette::HsbDistance(i, j);
            line += FloatToStrF(hD, ffFixed, 8, 8) + (j != 255 ? "," : "\n");
        }
        myfile << line.c_str();
    }
    myfile.close();*/
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::UseZXSpectrumPalette(void)
{
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::UpdateLoadedPalette(void)
{
    UseDefaultPalette();
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::UpdateColorTable(void)
{
    UseDefaultPalette();
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
    TRect Rect(X, Y, X + m_iPixelsWidePerAttribute, Y + m_iPixelsHighPerAttribute);
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
		if (OnUpdatePaletteGUI)
        {
            OnUpdatePaletteGUI();
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
        int iXS = 0;            
        int iXE = Image->Width;
        int iYS = 0;
        int iYE = Image->Height;
        unsigned char color = 0;

        for (int cy = iYS; cy < iYE; cy += m_iPixelsHighPerAttribute)
        {
            // loop through all the columns
            for (int cx = iXS; cx < iXE; cx += m_iPixelsWidePerAttribute)
            {
                // find the closet color
                color = GetClosestColor(Bitmap->Canvas->Pixels[cx][cy]);
                // set the pixel to the closest color
                SetPixel(cx, cy, color, *Image);
            }
        }
        bConverted = true;
    }
    return bConverted;
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
        //colorTable->Add("Color", m_Palette[i]);
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
                //m_Palette[i] = (*it)->GetInt();
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
}
//---------------------------------------------------------------------------
String __fastcall ZXSpectrumNextPalette::GetColorAsString(ZXImage& Image, int X, int Y)
{
	String sColor("None");
	if (0 <= X && X < Image.Width && 0 <= Y && Y < Image.Height)
	{
		unsigned int Offset  = (X / m_iBitsPerPixel) + (Y * Image.Width);
		int ColorIndex = Image.Pixels[Offset];
		unsigned char R, G, B;
		GetColor(ColorIndex, R, G, B);

        sColor  = IntToStr(ColorIndex) + ":";
		sColor += IntToHex(R,2) + ",";
		sColor += IntToHex(G,2) + ",";
		sColor += IntToHex(B,2);
	}
	return sColor;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrumNextPalette::GetColor(unsigned int index, unsigned char& R, unsigned char& G, unsigned char& B)
{
	R = 0;
	G = 0;
	B = 0;
	if (index < 256)
	{
		unsigned int color = ZXPalette::GetColor(index);
		R = (color & g_iRedMask) >> g_iRedShift;
		G = (color & g_iGrnMask) >> g_iGrnShift;
		B = (color & g_iBluMask) >> g_iBluShift;
	}
}
//---------------------------------------------------------------------------

