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
#ifndef ZXToolHotSpotH
#define ZXToolHotSpotH
//---------------------------------------------------------------------------
#include "ZXToolInterface.h"
//---------------------------------------------------------------------------
class ZXToolHotSpot : public ZXToolInterface
{
private:
    bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y);

public:
            __fastcall  ZXToolHotSpot();
};
//---------------------------------------------------------------------------
#endif
