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
    namespace EnterprisePalette
    {
        //---------------------------------------------------------------------------
        class Enterprise16Palette : public ZXPalette
        {
        private:
                    unsigned char       m_iColor;
                    unsigned char       m_iFixBias;

                    void    __fastcall  Initialize(void);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char iColor, bool bSet, ZXImage& Image);

                    void    __fastcall  SetColor(unsigned char iColor);
                    void    __fastcall  SetBias (unsigned char iFixBias);
            unsigned char   __fastcall  GetColorIndex(TColor Color);
                    void    __fastcall  Loaded(void);

        public:
                            __fastcall  Enterprise16Palette();

                    void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
                    void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
            unsigned char   __fastcall  GetColor(void);
                    TColor  __fastcall  GetColor(unsigned char iColor);
                    String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  Reset(void);

                    TColor  __fastcall  Get256Color(int iIndex);
                    int     __fastcall  GetBiasColor(int iIndex);
                    void    __fastcall  Set256Color(unsigned char iColor, unsigned iIndex);

            __property  unsigned char   Color           = { read = m_iColor     , write = SetColor  };
            __property  unsigned char   FixBias         = { read = m_iFixBias   , write = SetBias   };
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
