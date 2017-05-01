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
__fastcall ZXTimeline::ZXTimeline()
: ZXImageRender()
, m_iGridWidth(12)
, m_iGridHeight(12)
{
}
//---------------------------------------------------------------------------
void __fastcall ZXTimeline::Init()
{
    frmMusicEditor->imgTimelineCanvas->Picture->Bitmap->Width  = frmMusicEditor->imgTimelineCanvas->Width;
    frmMusicEditor->imgTimelineCanvas->Picture->Bitmap->Height = frmMusicEditor->imgTimelineCanvas->Height;
    frmMusicEditor->panHScroll->OnResize = OnResize;
}
//---------------------------------------------------------------------------
void __fastcall ZXTimeline::DoRender()
{
    frmMusicEditor->imgTimelineCanvas->Picture->Bitmap->Canvas->Brush->Color = TColor(0x1C0D0B);
    frmMusicEditor->imgTimelineCanvas->Picture->Bitmap->Canvas->FillRect(frmMusicEditor->imgTimelineCanvas->ClientRect);
}
//---------------------------------------------------------------------------
void __fastcall ZXTimeline::Scroll(int delta)
{
    Dirty();
}
//---------------------------------------------------------------------------
void __fastcall ZXTimeline::Zoom(int delta)
{
    Dirty();
}
//---------------------------------------------------------------------------
void __fastcall ZXTimeline::OnResize(TObject *Sender)
{
    frmMusicEditor->imgTimelineCanvas->Picture->Bitmap->Width  = frmMusicEditor->imgTimelineCanvas->Width;
    Refresh();
}
//---------------------------------------------------------------------------

