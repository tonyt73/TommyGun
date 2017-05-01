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
#ifndef ZXSpectrumPaletteH
#define ZXSpectrumPaletteH
//---------------------------------------------------------------------------
#include "..\ZXPalette.h"
#include "..\ZXImage.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace C64SpritePalette
    {
        //---------------------------------------------------------------------------
        class SpritePalette : public ZXPalette
        {
        private:
                    unsigned char       m_iColor;

                    void    __fastcall  Initialize(void);
                    void    __fastcall  SetColor(unsigned char iColor);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char iColor, bool bSet, ZXImage& Image);
                    void    __fastcall  Loaded(void);

        public:
                            __fastcall  SpritePalette();

                    void    __fastcall  SetTableColor(unsigned char iColor, TColor Color);
                    void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
                    void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
            unsigned char   __fastcall  GetColor(void);
                    TColor  __fastcall  GetColor(unsigned char iColor);
                    String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  Reset(void);

            unsigned char   __property  Color   = { read = m_iColor, write = SetColor   }; 
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
