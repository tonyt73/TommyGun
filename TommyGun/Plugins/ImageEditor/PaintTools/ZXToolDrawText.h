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
#ifndef ZXToolDrawTextH
#define ZXToolDrawTextH
//---------------------------------------------------------------------------
#include "ZXToolInterface.h"
//---------------------------------------------------------------------------
class ZXToolDrawText : public ZXToolInterface
{
private:
    bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);

public:
            __fastcall  ZXToolDrawText();
};
//---------------------------------------------------------------------------
#endif

