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
#ifndef SamMode2PaletteH
#define SamMode2PaletteH
//---------------------------------------------------------------------------
#include "..\ZXPalette.h"
#include "..\ZXImage.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace SamCoupeMode2Palette
    {
        //---------------------------------------------------------------------------
        class SamMode2Palette : public ZXPalette
        {
        private:
                    unsigned char       m_iInk;
                    unsigned char       m_iPaper;
                    unsigned char       m_iBright;
                    unsigned char       m_iFlash;

                    void    __fastcall  Initialize(void);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char iInk, unsigned char iPaper, unsigned char iBright, unsigned char iFlash, bool bSet, ZXImage& Image);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char PixelByte, ZXImage* Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char iInk, unsigned char iPaper, unsigned char iBright, unsigned char iFlash, ZXImage& Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image);
            unsigned char   __fastcall  GetAttribute(int iX, int iY, ZXImage& Image);

                    void    __fastcall  SetInk   (unsigned char iInk);
                    void    __fastcall  SetPaper (unsigned char iPaper);
                    void    __fastcall  SetFlash (unsigned char iFlash);
                    void    __fastcall  SetBright(unsigned char iBright);
                    bool    __fastcall  Convert(ZXImage* Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  FindColors(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Ink, unsigned char& Paper);
                    void    __fastcall  SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Ink, unsigned char Paper);
            unsigned char   __fastcall  GetColorIndex(TColor Color);
                    String  __fastcall  GetName(void);

        public:
                            __fastcall  SamMode2Palette();

                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
                    void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
                    String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
                    void    __fastcall  Invert(ZXImage& Image, int X, int Y);
                    void    __fastcall  Swap(ZXImage& Image, int X, int Y);

            __property  unsigned char   Ink             = { read = m_iInk           , write = SetInk            };
            __property  unsigned char   Paper           = { read = m_iPaper         , write = SetPaper          };
            __property  unsigned char   Bright          = { read = m_iBright        , write = SetBright         };
            __property  unsigned char   Flash           = { read = m_iFlash         , write = SetFlash          };
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
