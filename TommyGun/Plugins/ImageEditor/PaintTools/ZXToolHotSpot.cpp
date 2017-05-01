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
__fastcall ZXToolHotSpot::ZXToolHotSpot()
: ZXToolInterface("Set Hot Spot")
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolHotSpot::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (mbLeft == Button)
    {
        Image->HotSpotX = X;
        Image->HotSpotY = Y;
        Image->Invalidate();
        bDrawn = true;
    }
    else if (mbRight == Button)
    {
        Image->HotSpotX = -1;
        Image->HotSpotY = -1;
        Image->Invalidate();
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolHotSpot::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (Shift.Contains(ssLeft))
    {
        Image->HotSpotX = X;
        Image->HotSpotY = Y;
        Image->Invalidate();
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------

