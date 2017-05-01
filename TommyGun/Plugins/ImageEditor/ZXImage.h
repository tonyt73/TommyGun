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
#ifndef ZXImageH
#define ZXImageH
//- SYSTEM ------------------------------------------------------------------
#include <stdio.h>
#include <vector>
//- VCL ---------------------------------------------------------------------
#include <ComCtrls.hpp>
#include <KXmlInfo.h>
//---------------------------------------------------------------------------
class ZXPalette;
typedef std::vector<TRect>      TRectVector;
typedef TRectVector::iterator   TRectVectorIterator;
enum XmlData  { xmlPixels, xmlAttributes, xmlMasks  };
//---------------------------------------------------------------------------
__declspec( dllexport ) class ZXImage
{
private:
    String                      m_sName;                    // the name of the image
    ZXPalette*                  m_pPalette;                 // the palette to be used for the image
    unsigned char*              m_pPixelBuffer;             // the pixel buffer
    unsigned char*              m_pAttributeBuffer;         // the attributes buffer
    unsigned char*              m_pMaskBuffer;              // the mask buffer
    unsigned char*              m_pBackupPixelBuffer;       // the pixel buffer
    unsigned char*              m_pBackupAttributeBuffer;   // the attributes buffer
    unsigned char*              m_pBackupMaskBuffer;        // the mask buffer
    unsigned long               m_iPixelBufferSize;         // the size of the pixel buffer
    unsigned long               m_iAttributeBufferSize;     // the size of the attribute buffer
    unsigned long               m_iMaskBufferSize;          // the size of the mask buffer
    Graphics::TBitmap*          m_pImage;                   // the image as a Windows bitmap
    Graphics::TBitmap*          m_pBackupImage;             // the original image bitmap before a set of draw operations
    Graphics::TBitmap*          m_pMaskImage;               // the mask as a Windows bitmap
    TRect                       m_rBlitRect;                // the rect that needs to be redrawn after a DrawBegin and DrawEnd have completed
    TRect                       m_rLastBlitRect;            // the last rect we used to blit an image
    TRect                       m_rSelectionRect;           // the rect that is used to constraint drawing/cuting/copying operations
    int                         m_iSubType;                 // the user defined sub-type of the image
    int                         m_iWidth;                   // the width of the image in pixels
    int                         m_iHeight;                  // the height of the image in pixels
    int                         m_iHotSpotX;                // the X position of the hot spot
    int                         m_iHotSpotY;                // the Y position of the hot spot
    unsigned int                m_iBitsPerPixel;            // bits per pixel
    int                         m_iDrawInitializeCount;     // draw initialization/finalization counter
    int                         m_iDrawBeginCount;          // draw begin/end counter
    float                       m_fMaskAlpha;               // the value of the mask alpha (transparency, see through-ness)
    TColor                      m_MaskColor;                // the color to render the mask
    bool                        m_bMaskMode;                // flag: true is editing the mask, and false is editing the image
    bool                        m_bIsMasked;                // flag: true - there is a mask image attached to this image (masks have no attributes)
    bool                        m_bIsDirty;                 // flag: true the image has been changed
    bool                        m_bCanResize;               // flag: indicates if you can resize the image
    bool                        m_bHotSpotMode;             // flag: true is show the hot spot and false if not
    TRectVector                 m_vDirtyRects;              // a list of dirty rects
    float                       m_fModeScaleX;              // the mode scale X adjust value
    float                       m_fModeScaleY;              // the mode scale Y adjust value


                    __fastcall  ZXImage();                  // don't allow a blank image with no palette to be created
            void    __fastcall  AllocateBuffers(void);      // allocates the buffers needed
            TRect   __fastcall  GetDirtyRect(void);
            void    __fastcall  DrawImage(void);
            void    __fastcall  DrawMask(bool bBlendMask);
            void    __fastcall  SetMaskAlpha(float fAlpha);
            void    __fastcall  SetMaskColor(TColor Color);
            void    __fastcall  GetXmlData(String& xmlString, XmlData xmlData = xmlPixels);
            bool    __fastcall  SetXmlData(const String& xmlString, XmlData xmlData = xmlPixels);
            void    __fastcall  ResizeBuffers(int iWidth, int iHeight);
            void    __fastcall  FreeBuffers(void);
            bool    __fastcall  GetUsesHotSpot(void);

public:
            // normal creation constructor
                    __fastcall  ZXImage(int iWidth, int iHeight, bool bMasked, ZXPalette* Palette, bool bCanResize = false);
            // copy operator
                    __fastcall  ZXImage(ZXImage& Image);
            // destructor
                    __fastcall ~ZXImage();
            // assignment operator
            ZXImage&            operator=(ZXImage& Image);

            // drawing functions
            void    __fastcall  DrawInitialize(void);       // saves the current image - all drawing appears on this until drawing finalized
            void    __fastcall  DrawCancel(void);           // the drawing was cancelled so restore the original image
            void    __fastcall  DrawFinalize(void);         // drawing is final so make the update the image to the changed image
            void    __fastcall  DrawBegin(void);            // used by a tools plugin to begin drawing
            void    __fastcall  DrawEnd(void);              // updates are complete the image can be re-drawn
    virtual void    __fastcall  DrawPoint(int X, int Y, bool bSet = true);
    virtual void    __fastcall  DrawLine(const TRect& Rect, bool bSet = true);
    virtual void    __fastcall  DrawHorizontalLine(int SX, int SY, int EX, bool bSet = true);
            bool    __fastcall  Draw(TCanvas* Canvas);
            bool    __fastcall  Draw(TCanvas* Canvas, int iMagnification);
            bool    __fastcall  Draw(TCanvas* Canvas, int iMagnification, const TRect& UpdateRect);
            bool    __fastcall  Draw(TCanvas* Canvas, int iMagnification, int X, int Y);
            bool    __fastcall  DrawMask(TCanvas* Canvas, int X, int Y, TColor MaskColor);
            void    __fastcall  DrawText(int X, int Y, const String& sText, TFont* Font);
            void    __fastcall  ReDraw(void);

            // misc functions
            void    __fastcall  Delete(const TRect& Rect);
            //bool    __fastcall  Copy(const TRect& Rect);
            //bool    __fastcall  Cut(const TRect& Rect);
            //bool    __fastcall  Paste(int iX, int iy, const TRect& Rect);
            void    __fastcall  Invalidate(void);
            void    __fastcall  Invalidate(const TRect& Rect);
            bool    __fastcall  GetMaskMode(void) const;
            void    __fastcall  SetMaskMode(bool bNewMaskMode);
            void    __fastcall  SetHotSpotMode(bool bNewMode);
            bool    __fastcall  Save(KXmlInfo& xmlInfo, bool bClearDirty);
            bool    __fastcall  Load(KXmlInfo& xmlInfo, bool bClearDirty, const String& sVersion = "");
            String  __fastcall  Signature(void) const;
            void    __fastcall  AddRect(const TRect& DirtyRect);
            int     __fastcall  Rects(void);
            void    __fastcall  GetRect(unsigned int iIndex, TRect& Rect);
            bool    __fastcall  PtInRect(int iX, int iY);
            void    __fastcall  SetSelectionRect(const TRect& Rect);
            TRect   __fastcall  GetSelectionRect(void);
            void    __fastcall  PaletteGetColor(int X, int Y);
            void    __fastcall  PaletteSetColor(int X, int Y);
            bool    __fastcall  ConvertBitmap(Graphics::TBitmap* Bitmap);
            bool    __fastcall  ConvertBitmapMask(Graphics::TBitmap* Bitmap, TColor MaskColor);
            void    __fastcall  Resize(int iLeft, int iTop, int iNewWidth, int iNewHeight);
            void    __fastcall  InvertMask(void);
            void    __fastcall  GenerateMask(int BorderStyle, int iPaletteIndex);


    // access functions
    __property  String          Name        = { read = m_sName      , write = m_sName       };
    __property  ZXPalette*      Palette     = { read = m_pPalette                           };
    __property  int             SubType     = { read = m_iSubType   , write = m_iSubType    };
    __property  int             Width       = { read = m_iWidth                             };
    __property  int             Height      = { read = m_iHeight                            };
    __property  int             HotSpotX    = { read = m_iHotSpotX  , write = m_iHotSpotX   };
    __property  int             HotSpotY    = { read = m_iHotSpotY  , write = m_iHotSpotY   };
    __property  bool            IsMasked    = { read = m_bIsMasked                          };
    __property  bool            MaskMode    = { read = m_bMaskMode  , write = SetMaskMode   };
    __property  bool            IsDirty     = { read = m_bIsDirty                           };
    __property  bool            CanResize   = { read = m_bCanResize , write = m_bCanResize  };
    __property  bool            UsesHotSpot = { read = GetUsesHotSpot                       };
    __property  bool            HotSpotMode = { read = m_bHotSpotMode,write = SetHotSpotMode};
    __property  float           MaskAlpha   = { read = m_fMaskAlpha , write = SetMaskAlpha  };
    __property  TColor          MaskColor   = { read = m_MaskColor  , write = SetMaskColor  };
    __property  unsigned char*  Pixels      = { read = m_pPixelBuffer                       };
    __property  unsigned char*  Attributes  = { read = m_pAttributeBuffer                   };
    __property  unsigned char*  Masks       = { read = m_pMaskBuffer                        };
    __property  TRect           DirtyRect   = { read = GetDirtyRect                         };
    __property  float           ModeScaleX  = { read = m_fModeScaleX, write = m_fModeScaleX };
    __property  float           ModeScaleY  = { read = m_fModeScaleY, write = m_fModeScaleY };
    __property  unsigned long   PixelBufSize= { read = m_iPixelBufferSize                   };
    __property  unsigned long   AttrBufSize = { read = m_iAttributeBufferSize               };
    __property  unsigned long   MaskBufSize = { read = m_iMaskBufferSize                    };
};
//---------------------------------------------------------------------------
#endif
