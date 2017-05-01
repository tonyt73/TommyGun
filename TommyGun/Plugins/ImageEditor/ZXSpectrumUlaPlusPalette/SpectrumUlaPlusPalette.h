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
#ifndef ZXSpectrumUlaPlusPaletteH
#define ZXSpectrumUlaPlusPaletteH
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
        class ZXSpectrumUlaPlusPalette : public ZXPalette
        {
        private:
                    unsigned char       m_Palette[64];
                    unsigned char       m_LoadedPalette[64];

                    unsigned char       m_iInk;
                    unsigned char       m_iPaper;
                    unsigned char       m_iClut;

                    void    __fastcall  Initialize(void);
                    void    __fastcall  UpdateLoadedPalette(void);
                    void    __fastcall  UpdateColorTable(void);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char iInk, unsigned char iPaper, unsigned char iClut, bool bSet, ZXImage& Image);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char PixelByte, ZXImage* Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char iInk, unsigned char iPaper, unsigned char iClut, ZXImage& Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image);
            unsigned char   __fastcall  GetAttribute(int iX, int iY, ZXImage& Image);
                    void    __fastcall  SetInk   (unsigned char iInk);
                    void    __fastcall  SetPaper (unsigned char iPaper);
                    void    __fastcall  SetClut  (unsigned char iClut);
                    bool    __fastcall  Convert(ZXImage* Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  FindColors(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Ink, unsigned char& Paper);
                    void    __fastcall  SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Ink, unsigned char Paper);
            unsigned char   __fastcall  GetColorIndex(TColor Color);
                    String  __fastcall  GetName(void);
                    void    __fastcall  Loaded(void);
                KXmlInfo*   __fastcall  GetColorTable(void);
                    bool    __fastcall  SetColorTable(KXmlInfo& xmlInfo);

        public:
                            __fastcall  ZXSpectrumUlaPlusPalette();

                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
                    void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
                    String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
                    void    __fastcall  Invert(ZXImage& Image, int X, int Y);
                    void    __fastcall  Swap(ZXImage& Image, int X, int Y);
                    TColor  __fastcall  DecodeColor(unsigned char RGB);
                    void    __fastcall  DecodeColor(unsigned char RGB, unsigned char& R, unsigned char& G, unsigned char& B);
                    TColor  __fastcall  GetColor(unsigned int index);
                    TColor  __fastcall  GetColor(unsigned int clut, unsigned int index);
                    unsigned char __fastcall GetColor(unsigned char R, unsigned char G, unsigned char B);
                    void    __fastcall  GetColor(unsigned int clut, unsigned int index, unsigned char& R, unsigned char& G, unsigned char& B);
                    void    __fastcall  GetColor(unsigned int index, unsigned char& R, unsigned char& G, unsigned char& B);
                    void    __fastcall  SetColor(unsigned int index, unsigned char R, unsigned char G, unsigned char B);
                    void    __fastcall  SetColor(unsigned int clut, unsigned int index, unsigned char R, unsigned char G, unsigned char B);
                    void    __fastcall  UseImagePalette(void);
                    void    __fastcall  UseDefaultPalette(void);
                    void    __fastcall  UseZXSpectrumPalette(void);

            __property  unsigned char   Ink             = { read = m_iInk           , write = SetInk            };
            __property  unsigned char   Paper           = { read = m_iPaper         , write = SetPaper          };
            __property  unsigned char   Clut            = { read = m_iClut          , write = SetClut           };
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
