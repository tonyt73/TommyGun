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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXMusic::ZXMusic()
: ZXGridRender()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXMusic::Init()
{
    frmMusicEditor->imgMusicCanvas->Picture->Bitmap->Width  = frmMusicEditor->imgMusicCanvas->Width;
    frmMusicEditor->imgMusicCanvas->Picture->Bitmap->Height = frmMusicEditor->imgMusicCanvas->Height;
    frmMusicEditor->imgMusicCanvas->Picture->Bitmap->Canvas->Brush->Color = TColor(0x443533);
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall ZXMusic::DoRender()
{
    int width  = frmMusicEditor->imgMusicCanvas->Picture->Bitmap->Width;
    int height = frmMusicEditor->imgMusicCanvas->Picture->Bitmap->Height;

    RenderGrid(frmMusicEditor->imgMusicCanvas->Picture->Bitmap->Canvas, width, height);
}
//---------------------------------------------------------------------------
