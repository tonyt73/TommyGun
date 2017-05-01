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
__fastcall ZXToolDrawFree::ZXToolDrawFree()
: ZXToolInterface("Draw Free")
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawFree::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (mbLeft == Button || mbRight == Button)
    {
        Image->DrawInitialize();
        Image->DrawBegin();
        Image->DrawPoint(X, Y, mbLeft == Button);
        Image->DrawEnd();
        Image->DrawFinalize();
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawFree::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (Shift.Contains(ssLeft) || Shift.Contains(ssRight))
    {
        Image->DrawInitialize();
        Image->DrawBegin();
        Image->DrawPoint(X, Y, Shift.Contains(ssLeft));
        Image->DrawEnd();
        Image->DrawFinalize();
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------

