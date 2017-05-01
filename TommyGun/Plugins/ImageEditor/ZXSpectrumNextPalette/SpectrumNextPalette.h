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
#ifndef ZXSpectrumNextPaletteH
#define ZXSpectrumNextPaletteH
//---------------------------------------------------------------------------
#include "..\ZXPalette.h"
#include "..\ZXImage.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace SpectrumPalette
    {
        //---------------------------------------------------------------------------
        class ZXSpectrumNextPalette : public ZXPalette
        {
        private:
					unsigned int        m_Palette[256];
                    unsigned int        m_LoadedPalette[256];

                    unsigned char       m_iPen;
                    unsigned char       m_iBrush;

                    void    __fastcall  Initialize(void);
                    void    __fastcall  UpdateLoadedPalette(void);
                    void    __fastcall  UpdateColorTable(void);
					void    __fastcall  SetPixel(int iX, int iY, unsigned char iPen, unsigned char iBrush, bool bSet, ZXImage& Image);
					void    __fastcall  SetPixel(int iX, int iY, unsigned char PixelByte, ZXImage& Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char iPen, unsigned char iBrush, ZXImage& Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image);
            unsigned char   __fastcall  GetAttribute(int iX, int iY, ZXImage& Image);
                    void    __fastcall  SetPen   (unsigned char iPen);
                    void    __fastcall  SetBrush (unsigned char iBrush);
                    bool    __fastcall  Convert(ZXImage* Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  FindColors(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Pen, unsigned char& Brush);
                    void    __fastcall  SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Pen, unsigned char Brush);
					void 	__fastcall 	GetColor(unsigned int index, unsigned char& R, unsigned char& G, unsigned char& B);
			unsigned char   __fastcall  GetColorIndex(TColor Color);
                    String  __fastcall  GetName(void);
                    void    __fastcall  Loaded(void);
                KXmlInfo*   __fastcall  GetColorTable(void);
                    bool    __fastcall  SetColorTable(KXmlInfo& xmlInfo);
					//void 	__fastcall 	SetColor(unsigned int index, unsigned char R, unsigned char G, unsigned char B);

        public:
                            __fastcall  ZXSpectrumNextPalette();

                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
                    void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
                    String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
                    void    __fastcall  Invert(ZXImage& Image, int X, int Y);
                    //void    __fastcall  Swap(ZXImage& Image, int X, int Y);
					void    __fastcall  UseImagePalette(void);
                    void    __fastcall  UseDefaultPalette(void);
                    void    __fastcall  UseZXSpectrumPalette(void);

            __property  unsigned char   Pen             = { read = m_iPen           , write = SetPen            };
            __property  unsigned char   Brush           = { read = m_iBrush         , write = SetBrush          };
		};
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
