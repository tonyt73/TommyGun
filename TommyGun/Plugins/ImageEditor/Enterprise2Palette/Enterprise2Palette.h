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
#ifndef Enterprise2PaletteH
#define Enterprise2PaletteH
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
        class Enterprise2Palette : public ZXPalette
        {
        private:
                    unsigned char       m_iPen;
                    unsigned char       m_iBrush;

                    void    __fastcall  Initialize(void);
                    void    __fastcall  SetPen(unsigned char iColor);
                    void    __fastcall  SetBrush(unsigned char iColor);
                    void    __fastcall  SetPixel(int iX, int iY, bool bSet, ZXImage& Image);
                    void    __fastcall  Loaded(void);

        public:
                            __fastcall  Enterprise2Palette();

                    void    __fastcall  SetTableColor(unsigned char iColor, TColor Color);
                    void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
                    void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
                    TColor  __fastcall  GetColor(unsigned char iColor);
                    String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  Reset(void);

            unsigned char   __property  Pen   = { read = m_iPen  , write = SetPen   };
            unsigned char   __property  Brush = { read = m_iBrush, write = SetBrush };
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
