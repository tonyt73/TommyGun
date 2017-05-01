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
#ifndef ZXPaletteH
#define ZXPaletteH
//- SYSTEM ------------------------------------------------------------------
#include <stdio.h>
#include <Graphics.hpp>
//- VCL ---------------------------------------------------------------------
#include <SyncObjs.hpp>
#include <ComCtrls.hpp>
#include <KXmlInfo.h>
//---------------------------------------------------------------------------
#include "ZXImageTypes.h"
//---------------------------------------------------------------------------
class ZXImage;
typedef void __fastcall (__closure *TEventUpdatePalette)(void);
//---------------------------------------------------------------------------
__declspec( dllexport ) class ZXPalette
{
private:
    TColor*                     m_pColorTable;              // a table of colors (ie. the palette)
    unsigned int                m_iColorsInTable;           // the number of entries in the color table
    std::vector<TColor>         m_ConvertColors;            // a table used during the bitmap conversion process

    TEventUpdatePalette         FOnUpdatePalette;
    int         __fastcall      ColorDifference(TColor C1, TColor C2);
    int         __fastcall      ConvertFindColor(int x, int y, Graphics::TBitmap* Bitmap);
    void        __fastcall      ConvertPalettized(ZXImage* Image, Graphics::TBitmap* Bitmap);
    void        __fastcall      BuildConvertColors(Graphics::TBitmap* Bitmap);

    __fastcall                  ZXPalette();                // don't allow creation of a blank palette

protected:
    String                      m_sSignature;               // the signature of the palette format (set by the specialization classes)
    TPixelFormat                m_PixelFormat;
    unsigned int                m_iBitsPerPixel;            // the number of bits used to store a pixel
    unsigned int                m_iBitsPerAttribute;        // the number of bits used to store an attribute
    unsigned int                m_iPixelsWidePerAttribute;  // the number of pixels wide an attribute represents
    unsigned int                m_iPixelsHighPerAttribute;  // the number of pixels high an attribute represents
    unsigned int                m_iDefaultScreenWidth;      // the default width of the screen for this palette
    unsigned int                m_iDefaultScreenHeight;     // the default height of the screen for this palette
    float                       m_fScalarX;                 // scaling factor for width
    float                       m_fScalarY;                 // scaling factor for height
    float                       m_fPixelsPerByte;           // the number of pixels per bytes
                                                            // eg. Spectrum has 8 pixels per byte
                                                            //     32bit Window Bitmap has 1/4 pixels per byte
    bool                        m_bSupportsPixelsOnly;      // flag: palette only supports pixels
                                                            // ie. Windows Bitmaps, Amiga, C64 etc
                                                            //     A ZX Spectrum, SamCoupe has separate pixel and attribute buffers
    bool                        m_bCanConvert;              // flag: says that the palette can convert a bitmap - needed by importers and some tools
    bool                        m_bShowAttributes;          // flag: says that attribute style images should draw in color - draws in monochrome if false
    bool                        m_bSaveColors;              // flag: save the colour table to the xml file
    bool                        m_bPenSet;                  // flag: the pen colour has been set
    bool                        m_bBrushSet;                // flag: the brush colour has been set
    bool                        m_bScreenResizeable;        // flag: the screen size is resizeable
    TColor                      m_ColorPen;                 // the current pen color
    TColor                      m_ColorBrush;               // the current brush color
    ZXImageTypes                m_SupportedImageTypes;      // the image types supported by the palette (all by default)

    virtual void    __fastcall  Initialize(void);           // overridden by a specialization class to set the color table up
    virtual bool    __fastcall  Convert(ZXImage* Image, Graphics::TBitmap* Bitmap);
    virtual String  __fastcall  GetName(void);
    virtual void    __fastcall  Loaded(void);
    virtual void    __fastcall  SetColor(unsigned char iColor);
    unsigned char   __fastcall  FlipBits(unsigned char iBits);

public:
                    __fastcall  ZXPalette(unsigned int iColors, unsigned int iScreenWidth, unsigned int iScreenHeight, bool bSaveColors = false, bool bScreenResizeable = false);
                    __fastcall  ZXPalette(const ZXPalette& Palette);
    virtual         __fastcall ~ZXPalette();

    ZXPalette                   operator=(const ZXPalette& Other);

            void    __fastcall  SetColor(unsigned int iColorIndex, TColor Color);
            TColor  __fastcall  GetColor(unsigned int iColorIndex);
    virtual String  __fastcall  GetColorAsString(ZXImage& Image, int X, int Y);
    virtual void    __fastcall  SetColorAt(ZXImage& Image, int X, int Y);
    virtual void    __fastcall  GetColorAt(ZXImage& Image, int X, int Y);
    virtual void    __fastcall  Draw(ZXImage& Image, Graphics::TBitmap* Bitmap);

    virtual void    __fastcall  Invert(ZXImage& Image, int X, int Y);
    virtual void    __fastcall  Swap(ZXImage& Image, int X, int Y);
            bool    __fastcall  ConvertBitmap(ZXImage* Image, Graphics::TBitmap* Bitmap);

    virtual void    __fastcall  Save(KXmlInfo& xmlInfo);
    virtual void    __fastcall  Load(KXmlInfo& xmlInfo);
  virtual KXmlInfo* __fastcall  GetColorTable(void);
    virtual bool    __fastcall  SetColorTable(KXmlInfo& xmlInfo);


    unsigned int    __fastcall  CalculateStride(unsigned int iWidth) const;
    unsigned int    __fastcall  CalculatePixelBufferSize(unsigned int iWidth, unsigned int iHeight) const;
    unsigned int    __fastcall  CalculateAttributeBufferSize(unsigned int iWidth, unsigned int iHeight) const;

            void    __fastcall  ApplyFix(const String& sVersion, ZXImage* pImage);

    static  DWORD   __fastcall  Luminance(TColor Color);
            bool    __fastcall  IsImageTypeSupported(ZXImageTypes imageType) const;

            // write a pixel into the image's buffers using the specialized Palette's knowledge of the Images buffer format.
            // also takes into consideration and special settings the palette may support like transparency
    virtual void    __fastcall  Write(int X, int Y, bool bSet, ZXImage& Image);

    __property  unsigned int    Colors                  = { read = m_iColorsInTable                             };
    __property  unsigned int    BitsPerPixel            = { read = m_iBitsPerPixel                              };
    __property  unsigned int    BitsPerAttribute        = { read = m_iBitsPerAttribute                          };
    __property  float           PixelsPerByte           = { read = m_fPixelsPerByte                             };
    __property  unsigned int    PixelsWidePerAttribute  = { read = m_iPixelsWidePerAttribute                    };
    __property  unsigned int    PixelsHighPerAttribute  = { read = m_iPixelsHighPerAttribute                    };
    __property  unsigned int    DefaultScreenWidth      = { read = m_iDefaultScreenWidth                        };
    __property  unsigned int    DefaultScreenHeight     = { read = m_iDefaultScreenHeight                       };
    __property  float           ScalarX                 = { read = m_fScalarX                                   };
    __property  float           ScalarY                 = { read = m_fScalarY                                   };
    __property  bool            SupportsPixelsOnly      = { read = m_bSupportsPixelsOnly                        };
    __property  bool            CanConvertBitmap        = { read = m_bCanConvert                                };
    __property  bool            ShowAttributes          = { read = m_bShowAttributes, write = m_bShowAttributes };
    __property  bool            ScreenResizeable        = { read = m_bScreenResizeable                          };
    __property  String          Signature               = { read = m_sSignature                                 };
    __property  TPixelFormat    PixelFormat             = { read = m_PixelFormat                                };
    __property  TColor          PenColor                = { read = m_ColorPen                                   };
    __property  TColor          BrushColor              = { read = m_ColorBrush                                 };
    __property  String          Name                    = { read = GetName                                      };

    // event fired when the GUI portion of a palette needs updating
    __property  TEventUpdatePalette OnUpdatePaletteGUI  = { read = FOnUpdatePalette , write = FOnUpdatePalette  };
};
//---------------------------------------------------------------------------
#endif
