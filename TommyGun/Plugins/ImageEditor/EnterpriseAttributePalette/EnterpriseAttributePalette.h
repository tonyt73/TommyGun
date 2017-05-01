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
#ifndef EnterpriseAttributePaletteH
#define EnterpriseAttributePaletteH
//---------------------------------------------------------------------------
#include "..\ZXPalette.h"
#include "..\ZXImage.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace Enterprise64AttributePalette
    {
        //---------------------------------------------------------------------------
        class EnterpriseAttributePalette : public ZXPalette
        {
        private:
                    unsigned char       m_iInk;
                    unsigned char       m_iPaper;
                    unsigned char       m_iFixBias;
                    bool                m_bInkTransparent;
                    bool                m_bPaperTransparent;

                    void    __fastcall  Initialize(void);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char iInk, unsigned char iPaper, bool bSet, ZXImage& Image);
                    void    __fastcall  SetPixel(int iX, int iY, unsigned char PixelByte, ZXImage* Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char iInk, unsigned char iPaper, ZXImage& Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image);
            unsigned char   __fastcall  GetAttribute(int iX, int iY, ZXImage& Image);

                    void    __fastcall  SetInk  (unsigned char iInk);
                    void    __fastcall  SetPaper(unsigned char iPaper);
                    void    __fastcall  SetBias (unsigned char iFixBias);
                    bool    __fastcall  Convert(ZXImage* Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  FindColors(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Ink, unsigned char& Paper);
                    void    __fastcall  SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Ink, unsigned char Paper);
            unsigned char   __fastcall  GetColorIndex(TColor Color);
                    void    __fastcall  Loaded(void);

        public:
                            __fastcall  EnterpriseAttributePalette();

                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
                    void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
                    String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
                    void    __fastcall  Invert(ZXImage& Image, int X, int Y);
                    void    __fastcall  Swap(ZXImage& Image, int X, int Y);
                    TColor  __fastcall  Get256Color(int iIndex);
                    int     __fastcall  GetBiasColor(int iIndex);
                    void    __fastcall  Set256Color(unsigned char iColor, unsigned iIndex);
                    void    __fastcall  Reset(void);

            __property  unsigned char   Ink             = { read = m_iInk               , write = SetInk                };
            __property  unsigned char   Paper           = { read = m_iPaper             , write = SetPaper              };
            __property  unsigned char   FixBias         = { read = m_iFixBias           , write = SetBias               };
            __property  bool            InkTransparent  = { read = m_bInkTransparent    , write = m_bInkTransparent     };
            __property  bool            PaperTransparent= { read = m_bPaperTransparent  , write = m_bPaperTransparent   };
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
