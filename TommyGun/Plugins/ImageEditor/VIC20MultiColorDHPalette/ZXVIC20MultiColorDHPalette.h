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
#ifndef ZXVic20MultiColorDHPaletteH
#define ZXVic20MultiColorDHPaletteH
//---------------------------------------------------------------------------
#include "..\ZXPalette.h"
#include "..\ZXImage.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace Vic20MultiColorDHPalette
    {
        enum TMultiColorDH { vcBackground, vcBorder, vcCharacter, vcAuxiliary };
        //---------------------------------------------------------------------------
        class ZXVic20MultiColorDHPalette : public ZXPalette
        {
        private:
                    class TColorStack
                    {
                    private:
                        TMultiColorDH               m_eColor;
                        unsigned char               m_iInk;
                        ZXVic20MultiColorDHPalette& m_Palette;

                        __fastcall TColorStack();
                        __fastcall operator=(TColorStack&);

                    public:
                        __fastcall TColorStack(ZXVic20MultiColorDHPalette& Palette)
                        : m_iInk   (Palette.Character )
                        , m_iPaper (Palette.Background)
                        , m_iAux   (Palette.Auxiliary )
                        , m_iBorder(Palette.Border    )
                        , m_eColor (Palette.Color     )
                        , m_Palette(Palette           )
                        {
                        }

                        __fastcall ~TColorStack()
                        {
                            m_Palette.Character  = m_iInk;
                            m_Palette.Background = m_iPaper;
                            m_Palette.Auxiliary  = m_iAux;
                            m_Palette.Border     = m_iBorder;
                            m_Palette.Color      = m_eColor;
                        }

                        unsigned char       m_iPaper;
                        unsigned char       m_iAux;
                        unsigned char       m_iBorder;
                    };

                    unsigned char       m_iInk;
                    unsigned char       m_iPaper;
                    unsigned char       m_iAux;
                    unsigned char       m_iBorder;
                    TMultiColorDH       m_eColor;

                    void    __fastcall  Initialize(void);
                    void    __fastcall  SetPixel(int iX, int iY, TMultiColorDH eColor, bool bSet, ZXImage& Image);
                    void    __fastcall  SetAttribute(int iX, int iY, unsigned char Attribute, ZXImage* Image);
            unsigned char   __fastcall  GetAttribute(int iX, int iY, ZXImage& Image);
                    void    __fastcall  SetInk   (unsigned char iInk);
                    void    __fastcall  SetPaper (unsigned char iPaper);
                    void    __fastcall  SetAux   (unsigned char iAux);
                    void    __fastcall  SetBorder(unsigned char iBorder);
                    void    __fastcall  SeteColor(TMultiColorDH eColor);
                    bool    __fastcall  Convert(ZXImage* Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  FindBrightColors(Graphics::TBitmap* Bitmap);
                    void    __fastcall  FindInk(Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char& Ink);
                    void    __fastcall  SetColors(ZXImage* Image, Graphics::TBitmap* Bitmap, int iX, int iY, unsigned char Ink, const TColorStack& ColorStack);
            unsigned char   __fastcall  GetColorIndex(TColor Color);
                    TColor  __fastcall  GetImageColor(ZXImage& Image, int X, int Y, const TColorStack& ColorStack);
                    String  __fastcall  GetName(void);
                    TColor  __fastcall  GetClosestColor(TColor SrcColor, unsigned char* ColorIndex = NULL);


        public:
                            __fastcall  ZXVic20MultiColorDHPalette();
                    void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);
                    void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);
                    void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
                    void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
                    String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
                    void    __fastcall  Reset();

            __property  unsigned char   Character       = { read = m_iInk           , write = SetInk            };
            __property  unsigned char   Background      = { read = m_iPaper         , write = SetPaper          };
            __property  unsigned char   Auxiliary       = { read = m_iAux           , write = SetAux            };
            __property  unsigned char   Border          = { read = m_iBorder        , write = SetBorder         };
            __property  TMultiColorDH   Color           = { read = m_eColor         , write = SeteColor         };
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
#endif
