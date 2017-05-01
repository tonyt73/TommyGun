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
#ifndef ZXToolDrawSprayH
#define ZXToolDrawSprayH
//---------------------------------------------------------------------------
#include "ZXToolInterface.h"
//---------------------------------------------------------------------------
class ZXToolDrawSpray : public ZXToolInterface
{
private:
    void    __fastcall  Spray(ZXImage* Image, int X, int Y, bool bSet);

    bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y);

public:
            __fastcall  ZXToolDrawSpray();
};
//---------------------------------------------------------------------------
#endif

