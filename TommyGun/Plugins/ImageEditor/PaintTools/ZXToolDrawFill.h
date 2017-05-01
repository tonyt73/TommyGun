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
#ifndef ZXToolDrawFillH
#define ZXToolDrawFillH
//---------------------------------------------------------------------------
#include "ZXToolInterface.h"
#include <queue>
//---------------------------------------------------------------------------
class ZXToolDrawFill : public ZXToolInterface
{
private:
    Graphics::TBitmap*  m_Bitmap;
    TColor              m_FillColor;
    TColor              m_MatchColor;
    std::queue<TPoint>  m_FillQueue;


    void    __fastcall  FloodFill(ZXImage* Image, int X, int Y, bool bSet);
    bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);

public:
            __fastcall  ZXToolDrawFill();
            __fastcall ~ZXToolDrawFill();
};
//---------------------------------------------------------------------------
#endif

