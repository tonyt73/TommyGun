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
__fastcall ZXToolDrawRect::ZXToolDrawRect()
: ZXToolInterface("Rectangle")
{
}
//---------------------------------------------------------------------------
void __fastcall ZXToolDrawRect::DrawRect(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    Image->DrawLine(TRect(m_iStartX, m_iStartY, X, m_iStartY), Shift.Contains(ssLeft));
    Image->DrawLine(TRect(        X, m_iStartY, X,         Y), Shift.Contains(ssLeft));
    Image->DrawLine(TRect(m_iStartX,         Y, X,         Y), Shift.Contains(ssLeft));
    Image->DrawLine(TRect(m_iStartX, m_iStartY, m_iStartX, Y), Shift.Contains(ssLeft));
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawRect::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (mbLeft == Button || mbRight == Button)
    {
        m_iStartX = X;
        m_iStartY = Y;
        Image->DrawInitialize();
        Image->DrawBegin();
        Image->DrawPoint(X, Y, mbLeft == Button);
        Image->DrawEnd();
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawRect::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (Shift.Contains(ssLeft) || Shift.Contains(ssRight))
    {
        Image->DrawBegin();
        DrawRect(Image, Shift, X, Y);
        Image->DrawEnd();
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawRect::DoMouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    Image->DrawFinalize();
    return false;
}
//---------------------------------------------------------------------------
__fastcall ZXToolDrawRectFill::ZXToolDrawRectFill()
: ZXToolDrawRect()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXToolDrawRectFill::DrawRect(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    int iYS = std::min(m_iStartY, Y);
    int iYE = std::max(m_iStartY, Y);
    for (int y = iYS; y <= iYE; y++)
    {
        Image->DrawLine(TRect(m_iStartX, y, X, y), Shift.Contains(ssLeft));
    }
}
//---------------------------------------------------------------------------

