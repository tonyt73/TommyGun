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
#ifndef ZXToolDrawInvertH
#define ZXToolDrawInvertH
//---------------------------------------------------------------------------
#include "ZXToolInterface.h"
//---------------------------------------------------------------------------
class ZXToolDrawInvert : public ZXToolInterface
{
private:
    bool*               m_InvertGrid;
    int                 m_iUnitsWide;
    int                 m_iUnitsHigh;

    void    __fastcall  AllocateInvertGrid(ZXImage* Image);
    bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);
    bool    __fastcall  DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y);

public:
            __fastcall  ZXToolDrawInvert();
            __fastcall ~ZXToolDrawInvert();
};
//---------------------------------------------------------------------------
#endif

