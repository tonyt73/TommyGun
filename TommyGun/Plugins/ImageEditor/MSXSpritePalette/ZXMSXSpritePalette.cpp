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
#include "ZXMSXSpritePalette.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
//using namespace Imaging;
using namespace MSXSpritePalette;
//---------------------------------------------------------------------------
const   String  g_sPaletteName = "MSX Monochrome Sprite";
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
__fastcall ZXMSXSpritePalette::ZXMSXSpritePalette()
: ZXPalette(2, 256, 192)
{
    PalSignature(m_sSignature);
    Initialize();
}
//---------------------------------------------------------------------------
#define RGB(r,g,b) (TColor)(((int)r) | ((int)g << 8) | ((int)b << 16) 
//---------------------------------------------------------------------------
void __fastcall ZXMSXSpritePalette::Initialize(void)
{
    m_PixelFormat               = pf32bit;
    m_SupportedImageTypes       = itSprite;
    // initialize our palette information
    m_iBitsPerPixel             = 1;
    m_iBitsPerAttribute         = 1;
    m_iPixelsWidePerAttribute   = 1;
    m_iPixelsHighPerAttribute   = 1;
    m_fPixelsPerByte            = 8.f;
    m_bSupportsPixelsOnly       = true;
    // normally we would initialize the color table
    SetColor( 0, clBlack);
    SetColor( 1, clWhite);

    /*
    SetColor( 0, RGB(  0,   0,   0));
    SetColor( 1, RGB(  0,   0,   0));
    SetColor( 2, RGB( 33, 200,  66));
    SetColor( 3, RGB( 94, 220, 120));
    SetColor( 4, RGB( 84,  85, 237));
    SetColor( 5, RGB(125, 118, 252));
    SetColor( 6, RGB(212,  82,  77));
    SetColor( 7, RGB( 66, 235, 245));
    SetColor( 8, RGB(252,  85,  84));
    SetColor( 9, RGB(255, 121, 120));
    SetColor(10, RGB(212, 193,  84));
    SetColor(11, RGB(230, 206, 128));
    SetColor(12, RGB(33, 176,  59 ));
    SetColor(13, RGB(201,  91, 186));
    SetColor(14, RGB(204, 204, 204));
    SetColor(15, RGB(255, 255, 255));
    */
}
//---------------------------------------------------------------------------
void __fastcall ZXMSXSpritePalette::Write(int X, int Y, bool bSet, ZXImage& Image)
{
    // dirty the character block
    int dX = (X >> 3) << 3;
    int dY = (Y >> 3) << 3;
    TRect Rect(dX, dY, dX + 8, dY + 8);
    Image.AddRect(Rect);
    // write the pixel to the image
    SetPixel(X, Y, bSet, Image);
}
//---------------------------------------------------------------------------
void __fastcall ZXMSXSpritePalette::Draw(ZXImage& Image, Graphics::TBitmap* Bitmap)
{
    //PERFORMANCE_PUSH
    // loop through the character block and set all the ink and paper values
    Bitmap->PixelFormat = pf32bit;
    int iCols = CalculateStride(Image.Width);
    TRect UpdateRect;
    int iRects = Image.Rects();
    TColor Pen = GetColor(1);
    for (int rect = 0; rect < iRects; ++rect)
    {
        Image.GetRect(rect, UpdateRect);
        for (int y = UpdateRect.Top; y < UpdateRect.Bottom; ++y)
        {
            for (int x = UpdateRect.Left; x < UpdateRect.Right; x += 8)
            {
                int iCX = x >> 3;
                unsigned char Pixels = Image.Pixels[(y * iCols) + iCX];
                Bitmap->Canvas->Pixels[x+0][y] = (Pixels & g_cPixelMasks[0]) ? Pen : clBlack;
                Bitmap->Canvas->Pixels[x+1][y] = (Pixels & g_cPixelMasks[1]) ? Pen : clBlack;
                Bitmap->Canvas->Pixels[x+2][y] = (Pixels & g_cPixelMasks[2]) ? Pen : clBlack;
                Bitmap->Canvas->Pixels[x+3][y] = (Pixels & g_cPixelMasks[3]) ? Pen : clBlack;
                Bitmap->Canvas->Pixels[x+4][y] = (Pixels & g_cPixelMasks[4]) ? Pen : clBlack;
                Bitmap->Canvas->Pixels[x+5][y] = (Pixels & g_cPixelMasks[5]) ? Pen : clBlack;
                Bitmap->Canvas->Pixels[x+6][y] = (Pixels & g_cPixelMasks[6]) ? Pen : clBlack;
                Bitmap->Canvas->Pixels[x+7][y] = (Pixels & g_cPixelMasks[7]) ? Pen : clBlack;
            }
        }
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall ZXMSXSpritePalette::SetPixel(int iX, int iY, bool bSet, ZXImage& Image)
{
    //PERFORMANCE_PUSH
    if (0 <= iX && iX < Image.Width && 0 <= iY && iY < Image.Height)
    {
        int iCols = CalculateStride(Image.Width);
        int iCX   = iX >> 3; 
        // assign any transparent attributes
        unsigned int PixelOffset = ( iY * iCols) + iCX;
        // set the appropreiate pixels and attribute
        unsigned char cPixelBit   = 128 >> (iX % 8);
        // set or reset the pixel
        Image.Pixels[PixelOffset] = bSet ? (Image.Pixels[PixelOffset] | cPixelBit) : (Image.Pixels[PixelOffset] & ~cPixelBit);
    }
    //PERFORMANCE_POP(__FUNC__)
}
//---------------------------------------------------------------------------
String __fastcall ZXMSXSpritePalette::GetName(void)
{
    return g_sPaletteName;
}
//---------------------------------------------------------------------------
bool __fastcall ZXMSXSpritePalette::Convert(ZXImage* Image, Graphics::TBitmap* Bitmap)
{
    bool bConverted = false;
    if (true == SAFE_PTR(Bitmap))
    {
        TRect Rect(0, 0, Image->Width, Image->Height);
        int iXS = 0;
        int iXE = Image->Width;
        int iYS = 0;
        int iYE = Image->Height;

        for (int cy = iYS; cy < iYE; cy++)
        {
            // loop through all the columns
            for (int cx = iXS; cx < iXE; cx++)
            {
                // set pixels according to the most common pair of colors
                SetPixel(cx, cy, Bitmap->Canvas->Pixels[cx][cy] != clBlack, *Image);
            }
        }
        bConverted = true;
    }
    return bConverted;
}
//---------------------------------------------------------------------------

