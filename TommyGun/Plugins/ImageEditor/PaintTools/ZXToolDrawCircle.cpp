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
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXToolDrawCircle::ZXToolDrawCircle()
: ZXToolInterface("Circle")
{
}
//---------------------------------------------------------------------------
void __fastcall ZXToolDrawCircle::DrawEllipsePoints(ZXImage* Image, int X, int Y, bool bSet)
{
    Image->DrawPoint(m_iStartX + X, m_iStartY + Y, bSet);
    Image->DrawPoint(m_iStartX - X, m_iStartY + Y, bSet);
    Image->DrawPoint(m_iStartX - X, m_iStartY - Y, bSet);
    Image->DrawPoint(m_iStartX + X, m_iStartY - Y, bSet);
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawCircle::DrawEllipse(ZXImage* Image, TShiftState Shift, int iX, int iY)
{
    int XRadius = std::max(1, abs(iX - m_iStartX));
    int YRadius = std::max(1, abs(iY - m_iStartY));

    int TwoASquare = 2 * XRadius * XRadius;
    int TwoBSquare = 2 * YRadius * YRadius;
    int X = XRadius;
    int Y = 0;
    int XChange = YRadius * YRadius * (1 - 2 * XRadius);
    int YChange = XRadius * XRadius;
    int EllipseError = 0;
    int StoppingX = TwoBSquare * XRadius;
    int StoppingY = 0;

    while ( StoppingX >= StoppingY )
    {
        DrawEllipsePoints(Image, X, Y, Shift.Contains(ssLeft));
        ++Y;
        StoppingY += TwoASquare;
        EllipseError += YChange;
        YChange += TwoASquare;

        if (( 2 * EllipseError + XChange) > 0 )
        {
            --X;
            StoppingX -= TwoBSquare;
            EllipseError += XChange;
            XChange += TwoBSquare;
        }
    }
    X = 0;
    Y = YRadius;
    XChange = YRadius * YRadius;
    YChange = XRadius * XRadius * (1 - 2 * YRadius);
    EllipseError = 0;
    StoppingX = 0;
    StoppingY = TwoASquare * YRadius;
    while ( StoppingX <= StoppingY )
    {
        DrawEllipsePoints(Image, X, Y, Shift.Contains(ssLeft));
        ++X;
        StoppingX += TwoBSquare;
        EllipseError += XChange;
        XChange += TwoBSquare;
        if (( 2 * EllipseError + YChange) > 0 )
        {
            --Y;
            StoppingY -= TwoASquare;
            EllipseError += YChange;
            YChange += TwoASquare;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawCircle::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
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
bool __fastcall ZXToolDrawCircle::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (Shift.Contains(ssLeft) || Shift.Contains(ssRight))
    {
        Image->DrawBegin();
        DrawEllipse(Image, Shift, X, Y);
        Image->DrawEnd();
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawCircle::DoMouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    Image->DrawFinalize();
    return false;
}
//---------------------------------------------------------------------------
__fastcall ZXToolDrawCircleFill::ZXToolDrawCircleFill()
: ZXToolDrawCircle()
{
    m_sName = "Circle (Fill)";
}
//---------------------------------------------------------------------------
void __fastcall ZXToolDrawCircleFill::DrawEllipsePoints(ZXImage* Image, int X, int Y, bool bSet)
{
    Image->DrawHorizontalLine(m_iStartX - X, m_iStartY + Y, m_iStartX + X, bSet);
    Image->DrawHorizontalLine(m_iStartX - X, m_iStartY - Y, m_iStartX + X, bSet);
}
//---------------------------------------------------------------------------

