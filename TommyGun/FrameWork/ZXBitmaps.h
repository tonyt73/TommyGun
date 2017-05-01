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
#ifndef ZXBitmapsH
#define ZXBitmapsH
//---------------------------------------------------------------------------
#include "FrameWorkInterface.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GUI
    {
        class ZXBitmaps
        {
        private:
            typedef struct
            {
                int                           iIndex;          // index into the image list of the bitmap
                bool                          bLargeList;      // true if in Large list, false if in SmallList
                TZX_HPLUGIN                   hOwner;          // the plugin handle owns the bitmap
            } TZXBitmapInfo;
            // vector and vector iterator typedefs
            typedef std::vector<TZXBitmapInfo>      TZXBitmapInfoVector;
            typedef TZXBitmapInfoVector::iterator   TZXBitmapInfoIterator;

            TImageList*         m_Images;   // image list we add the bitmaps to
            TZXBitmapInfoVector m_Bitmaps;  // list of bitmaps added by plugins

        public:
                    __fastcall  ZXBitmaps();
                    __fastcall ~ZXBitmaps();

            void    __fastcall  Setup(TImageList* ImageList);
            void    __fastcall  Free(void);
            void    __fastcall  Free(TZX_HPLUGIN PluginHandle);
            int     __fastcall  Add (TZX_HPLUGIN PluginHandle, TImage* Image);
        };
    }
}
//---------------------------------------------------------------------------
#endif
