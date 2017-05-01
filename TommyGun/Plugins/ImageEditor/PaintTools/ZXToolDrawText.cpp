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
__fastcall ZXToolDrawText::ZXToolDrawText()
: ZXToolInterface("Text")
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawText::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (mbLeft == Button || mbRight == Button)
    {
        if (true == frmTextDialog->Execute(X, Y, Image))
        {
            Image->DrawInitialize();
            Image->DrawBegin();
            Image->DrawText(X, Y, frmTextDialog->edtText->Text, frmTextDialog->dlgFont->Font);
            Image->DrawEnd();
            Image->DrawFinalize();
        }
        bDrawn = true;
    }
    return bDrawn;
}
//---------------------------------------------------------------------------

