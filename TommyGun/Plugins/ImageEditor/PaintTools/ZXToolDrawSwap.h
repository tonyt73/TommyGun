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
#ifndef ZXToolDrawSwapH
#define ZXToolDrawSwapH
//---------------------------------------------------------------------------
#include "ZXToolInterface.h"
//---------------------------------------------------------------------------
class ZXToolDrawSwap : public ZXToolInterface
{
private:
    bool*               m_SwapGrid;
    int                 m_iUnitsWide;
    int                 m_iUnitsHigh;

    void    __fastcall  AllocateSwapGrid(ZXImage* Image);
    bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y);

public:
            __fastcall  ZXToolDrawSwap();
};
//---------------------------------------------------------------------------
#endif

