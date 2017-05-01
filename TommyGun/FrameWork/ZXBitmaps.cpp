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
#include <vcl.h>
#pragma hdrstop
#include "ZXBitmaps.h"
#include "SafeMacros.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace GUI;
//---------------------------------------------------------------------------
const int g_iNotFound = -1;
//---------------------------------------------------------------------------
__fastcall ZXBitmaps::ZXBitmaps()
: m_Images(NULL)
{
}
//---------------------------------------------------------------------------
__fastcall ZXBitmaps::~ZXBitmaps()
{
    Free();
    m_Images = NULL;
}
//---------------------------------------------------------------------------
// Add
/**
 * Adds a bitmap to the list
 * @param   BitmapHandle the Windows Bitmap handle of the bitmap to add to the list
 * @return  Returns the index into the ImageList of the bitmap
 * @author  Tony Thompson
 * @date    Last Modified 30 October 2001
 * @date    Last Modified 22 September 2003
 * @remarks
 */
//---------------------------------------------------------------------------
int __fastcall ZXBitmaps::Add(TZX_HPLUGIN PluginHandle, TImage* Image)
{
    int ImageListIndex = -1;
    // try to add the new bitmap to the image list
    ImageListIndex = m_Images->AddMasked(Image->Picture->Bitmap, Image->Canvas->Pixels[0][0]);
    if (g_iNotFound != ImageListIndex)
    {
        // save the data
        TZXBitmapInfo BitmapInfo;
        // add the bitmap to the image list
        BitmapInfo.iIndex = ImageListIndex;
        BitmapInfo.hOwner = PluginHandle;
        // add the bitmap information to our bitmap list
        m_Bitmaps.push_back(BitmapInfo);
    }
    return ImageListIndex;
}
//---------------------------------------------------------------------------
void __fastcall ZXBitmaps::Setup(TImageList* ImageList)
{
    m_Images = ImageList;
}
//---------------------------------------------------------------------------
void __fastcall ZXBitmaps::Free(void)
{
    m_Bitmaps.clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXBitmaps::Free(TZX_HPLUGIN PluginHandle)
{
    TZXBitmapInfoIterator BitmapIt = m_Bitmaps.begin();
    while(BitmapIt != m_Bitmaps.end())
    {
        if ((*BitmapIt).hOwner == PluginHandle)
        {
            BitmapIt = m_Bitmaps.erase(BitmapIt);
        }
        else
        {
            BitmapIt++;
        }
    }
}
//---------------------------------------------------------------------------
