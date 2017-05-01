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
__fastcall ZXToolDrawLine::ZXToolDrawLine()
: ZXToolInterface("Line")
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawLine::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (mbLeft == Button || mbRight == Button)
    {
        m_iStartX = X;
        m_iStartY = Y;
        Image->DrawInitialize();
        Image->DrawBegin();
        Image->DrawLine(TRect(X, Y, X, Y), mbLeft == Button);
        Image->DrawEnd();
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawLine::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (Shift.Contains(ssLeft) || Shift.Contains(ssRight))
    {
        Image->DrawBegin();
        Image->DrawLine(TRect(m_iStartX, m_iStartY, X, Y), Shift.Contains(ssLeft));
        Image->DrawEnd();
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawLine::DoMouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    Image->DrawFinalize();
    return false;
}
//---------------------------------------------------------------------------

