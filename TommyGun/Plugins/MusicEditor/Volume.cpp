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
__fastcall ZXVolume::ZXVolume()
: ZXGridRender()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXVolume::Init()
{
    frmMusicEditor->imgVolumeCanvas->Picture->Bitmap->Width  = frmMusicEditor->imgVolumeCanvas->Width;
    frmMusicEditor->imgVolumeCanvas->Picture->Bitmap->Height = frmMusicEditor->imgVolumeCanvas->Height;
    frmMusicEditor->imgVolumeCanvas->Picture->Bitmap->Canvas->Brush->Color = TColor(0x443533);
    frmMusicEditor->panVolumeContainer->OnResize = OnResize;
}
//---------------------------------------------------------------------------
void __fastcall ZXVolume::DoRender()
{
    if (frmMusicEditor->panVolumeContainer->Visible)
    {
        RenderGrid(frmMusicEditor->imgVolumeCanvas->Picture->Bitmap->Canvas, frmMusicEditor->imgVolumeCanvas->Width, frmMusicEditor->imgVolumeCanvas->Height);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXVolume::OnResize(TObject *Sender)
{
    frmMusicEditor->imgVolumeCanvas->Picture->Bitmap->Width  = frmMusicEditor->imgVolumeCanvas->Width;
    frmMusicEditor->imgVolumeCanvas->Picture->Bitmap->Height = frmMusicEditor->imgVolumeCanvas->Height;
    Refresh();
}
//---------------------------------------------------------------------------


