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
__fastcall ZXKeyboard::ZXKeyboard()
: ZXImageRender()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXKeyboard::Init()
{
    frmMusicEditor->imgKeysCanvas->Picture->Bitmap->Width  = frmMusicEditor->imgKeysCanvas->Width;
    frmMusicEditor->imgKeysCanvas->Picture->Bitmap->Height = frmMusicEditor->imgKeysCanvas->Height;
    Refresh();
}
//---------------------------------------------------------------------------
void __fastcall ZXKeyboard::DoRender()
{
    int RollHeight = frmMusicEditor->imgKeyRoll->Height;
    TCanvas* pCanvas = frmMusicEditor->imgKeysCanvas->Picture->Bitmap->Canvas;
    for (int i = 0; i < 10; i++)
    {
        pCanvas->Draw(0, i * RollHeight, frmMusicEditor->imgKeyRoll->Picture->Bitmap);
    }
}
//---------------------------------------------------------------------------
