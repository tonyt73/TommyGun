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
#ifndef ZXJupiterAcePaletteH
#define ZXJupiterAcePaletteH
//---------------------------------------------------------------------------
#include "..\ZXPalette.h"
#include "..\ZXImage.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace JupiterAcePalette
    {
        //---------------------------------------------------------------------------
        class ZXJupiterAcePalette : public ZXPalette
        {
        private:
                    void    __fastcall  Initialize(void);
                    void    __fastcall  SetPixel(int iX, int iY, bool bSet, ZXImage& Image);
                    void    __fastcall  DoSetPixel(int iX, int iY, bool bSet, ZXImage& Image);
                    String  __fastcall  GetName(void);
                    bool    __fastcall  Convert(ZXImage* Image, Graphics::TBitmap* Bitmap);

        public:
                            __fastcall  ZXJupiterAcePalette();
                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
