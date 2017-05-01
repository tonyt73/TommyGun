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
inline int __fastcall ZXPalette::ColorDifference(TColor C1, TColor C2)
{
    int iDifference  = abs(( C1        & 0xFF) - ( C2        & 0xFF));
        iDifference += abs(((C1 >>  8) & 0xFF) - ((C2 >>  8) & 0xFF));
        iDifference += abs(((C1 >> 16) & 0xFF) - ((C2 >> 16) & 0xFF));
    return iDifference;
}
//---------------------------------------------------------------------------
int __fastcall ZXPalette::ConvertFindColor(int x, int y, Graphics::TBitmap* Bitmap)
{
    // by default use the first ink/pen color
    int iColorIndex = -1;
    // get the bitmaps pixel color
    TColor Color = Bitmap->Canvas->Pixels[x][y];
    iColorIndex = 1;
    int iClosestDifference = ColorDifference(Color, m_pColorTable[1]);
    // search the color table for the closest matching color entry
    for (unsigned int i = 0; i < m_iColorsInTable && iClosestDifference; ++i)
    {
        int iDifference = ColorDifference(Color, m_pColorTable[i]);
        if (iDifference < iClosestDifference)
        {
            iClosestDifference = iDifference;
            iColorIndex = i;
        }
    }
    if (iClosestDifference > 32)
    {
        iColorIndex = -1;
        // use the convert colour table
        for (unsigned int i = 0; i < m_ConvertColors.size(); i++)
        {
            if (Color == m_ConvertColors[i])
            {
                iColorIndex = i;
                break;
            }
        }
        if (iColorIndex == -1)
        {
            iColorIndex = 0;
            int iClosestDifference = ColorDifference(Color, m_ConvertColors[0]);
            // search the color table for the closest matching color entry
            for (unsigned int i = 1; i < m_iColorsInTable && iClosestDifference; ++i)
            {
                int iDifference = ColorDifference(Color, m_ConvertColors[i]);
                if (iDifference < iClosestDifference)
                {
                    iClosestDifference = iDifference;
                    iColorIndex = i;
                }
            }
        }
    }
    return iColorIndex;
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
    float fStride = (float)iWidth / PixelsPerByte;
    int   iStride = fStride;
    if ((float)iStride != fStride)
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
    float fStride = (float)iWidth / PixelsPerByte;
    int   iStride = fStride;
    if ((float)iStride != fStride)
        iStride++;
    //int iStride = iWidth / m_iPixelsWidePerAttribute;
    //iStride += (iWidth % 8) ? 1 : 0;
    float fStryde = (float)iHeight / (float)m_iPixelsHighPerAttribute;
    int   iStryde = fStryde;
    if ((float)iStryde != fStryde)
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
    DWORD dwLuminance = (0.299f * (float)dwRed + 0.587f * (float)dwGreen + 0.114f * (float)dwBlue);
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

