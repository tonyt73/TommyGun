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
#ifndef ZXVic20HiresPaletteH
#define ZXVic20HiresPaletteH
//---------------------------------------------------------------------------
#include "..\ZXPalette.h"
#include "..\ZXImage.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace Vic20HiresPalette
    {
        //---------------------------------------------------------------------------
        class ZXVic20HiresPalette : public ZXPalette
        {
        private:
                    unsigned char       m_iInk;
                    unsigned char       m_iPaper;

                    void    __fastcall  Initialize(void);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char iInk, bool bSet, ZXImage& Image);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char PixelByte, ZXImage* Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image);
            unsigned char   __fastcall  GetAttribute(int iX, int iY, ZXImage& Image);
                    void    __fastcall  SetInk   (unsigned char iInk);
                    void    __fastcall  SetPaper (unsigned char iPaper);
                    bool    __fastcall  Convert(ZXImage* Image, Graphics::TBitmap* Bitmap);
                    int     __fastcall  FindPaperColor(Graphics::TBitmap* Bitmap);
                    void    __fastcall  FindInkColor(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Ink, unsigned char Paper);
                    void    __fastcall  SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Ink, unsigned char Paper);
            unsigned char   __fastcall  GetColorIndex(TColor Color);
                    String  __fastcall  GetName(void);
                    TColor  __fastcall  GetClosestColor(TColor SrcColor, unsigned char* ColorIndex);


        public:
                            __fastcall  ZXVic20HiresPalette();
                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
                    void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
                    String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
                    void    __fastcall  Invert(ZXImage& Image, int X, int Y);

            __property  unsigned char   Ink             = { read = m_iInk           , write = SetInk            };
            __property  unsigned char   Paper           = { read = m_iPaper         , write = SetPaper          };
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
