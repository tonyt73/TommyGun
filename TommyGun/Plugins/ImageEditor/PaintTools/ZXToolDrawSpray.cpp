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
__fastcall ZXToolDrawSpray::ZXToolDrawSpray()
: ZXToolInterface("Spray Can")
{
}
//---------------------------------------------------------------------------
void __fastcall ZXToolDrawSpray::Spray(ZXImage* Image, int X, int Y, bool bSet)
{
    int iDX = 0;
    int iDY = 0;
    Image->DrawInitialize();
    Image->DrawBegin();
    for (int i = 0; i < 5; i++)
    {
        iDX = (rand() % 8) - 4;
        iDY = (rand() % 8) - 4;
        Image->DrawPoint(X + iDX, Y + iDY, bSet);
    }
    Image->DrawEnd();
    Image->DrawFinalize();
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawSpray::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    return MouseMove(Image, Shift, X, Y);
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawSpray::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (Shift.Contains(ssLeft) || Shift.Contains(ssRight))
    {
        Spray(Image, X, Y, Shift.Contains(ssLeft));
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------

