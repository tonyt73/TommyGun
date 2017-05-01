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
#ifndef ZXToolDrawCircleH
#define ZXToolDrawCircleH
//---------------------------------------------------------------------------
#include "ZXToolInterface.h"
//---------------------------------------------------------------------------
class ZXToolDrawCircle : public ZXToolInterface
{
private:
    bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);

protected:
    int                 m_iStartX;
    int                 m_iStartY;

    virtual void    __fastcall  DrawEllipsePoints(ZXImage* Image, int X, int Y, bool bSet);
            bool    __fastcall  DrawEllipse(ZXImage* Image, TShiftState Shift, int X, int Y);

public:
            __fastcall  ZXToolDrawCircle();
};
//---------------------------------------------------------------------------
class ZXToolDrawCircleFill : public ZXToolDrawCircle
{
public:
            __fastcall  ZXToolDrawCircleFill();

    void    __fastcall  DrawEllipsePoints(ZXImage* Image, int X, int Y, bool bSet);
};
//---------------------------------------------------------------------------
#endif

