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
#ifndef ZXToolDrawLineH
#define ZXToolDrawLineH
//---------------------------------------------------------------------------
#include "ZXToolInterface.h"
//---------------------------------------------------------------------------
class ZXToolDrawLine : public ZXToolInterface
{
private:
    int                 m_iStartX;
    int                 m_iStartY;

    bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);

public:
            __fastcall  ZXToolDrawLine();
};
//---------------------------------------------------------------------------
#endif

