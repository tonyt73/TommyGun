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
__fastcall ZXToolDrawDropper::ZXToolDrawDropper()
: ZXToolInterface("Dropper")
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawDropper::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    return MouseMove(Image, Shift, X, Y);
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawDropper::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (true == Shift.Contains(ssLeft) && true == Image->PtInRect(X, Y))
    {
        Image->DrawInitialize();
        Image->DrawBegin();
        Image->Palette->SetColorAt(*Image, X, Y);
        Image->DrawEnd();
        Image->DrawFinalize();
        bDrawn = true;
    }
    else if (Shift.Contains(ssRight))
    {
        Image->Palette->GetColorAt(*Image, X, Y);
    }
    return bDrawn;
}
//---------------------------------------------------------------------------

