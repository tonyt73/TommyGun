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
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXToolInterface::ZXToolInterface(const String sName)
: m_bEnabled(false)
, m_sName(sName)
{
}
//---------------------------------------------------------------------------
__fastcall ZXToolInterface::~ZXToolInterface()
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolInterface::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolInterface::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolInterface::DoMouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolInterface::MouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    return DoMouseDown(Image, Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolInterface::MouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    return DoMouseMove(Image, Shift, X, Y);
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolInterface::MouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    return DoMouseUp(Image, Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
