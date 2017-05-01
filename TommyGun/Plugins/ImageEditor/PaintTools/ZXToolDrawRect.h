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
#ifndef ZXToolDrawRectH
#define ZXToolDrawRectH
//---------------------------------------------------------------------------
#include "ZXToolInterface.h"
//---------------------------------------------------------------------------
class ZXToolDrawRect : public ZXToolInterface
{
private:
    bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);

protected:
    int                 m_iStartX;
    int                 m_iStartY;

    virtual void    __fastcall  DrawRect(ZXImage* Image, TShiftState Shift, int X, int Y);

public:
            __fastcall  ZXToolDrawRect();
};
//---------------------------------------------------------------------------
class ZXToolDrawRectFill : public ZXToolDrawRect
{
private:
    void    __fastcall  DrawRect(ZXImage* Image, TShiftState Shift, int X, int Y);
    
public:
            __fastcall  ZXToolDrawRectFill();
};
//---------------------------------------------------------------------------
#endif

