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
__fastcall ZXToolDrawSwap::ZXToolDrawSwap()
: ZXToolInterface("Pixel Invert")
{
}
//---------------------------------------------------------------------------
void __fastcall ZXToolDrawSwap::AllocateSwapGrid(ZXImage* Image)
{
    SAFE_ARRAY_DELETE(m_SwapGrid);
    m_iUnitsWide = Image->Width  / Image->Palette->PixelsWidePerAttribute;
    m_iUnitsHigh = Image->Height / Image->Palette->PixelsHighPerAttribute;
    m_SwapGrid = new bool[m_iUnitsWide * m_iUnitsHigh];
    ZeroMemory(m_SwapGrid, m_iUnitsWide * m_iUnitsHigh * sizeof(bool));
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawSwap::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (true == Enabled && true == Shift.Contains(ssLeft))
    {
        AllocateSwapGrid(Image);
        bDrawn = MouseMove(Image, Shift, X, Y);
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawSwap::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (true == Enabled && true == Shift.Contains(ssLeft) && 0 <= X && X < Image->Width && 0 <= Y && Y < Image->Height)
    {
        int iPX = X / Image->Palette->PixelsWidePerAttribute;
        int iPY = Y / Image->Palette->PixelsHighPerAttribute;
        if (false == m_SwapGrid[m_iUnitsWide * iPY + iPX])
        {
            Image->DrawInitialize();
            Image->DrawBegin();
            // invert the grid position
            m_SwapGrid[m_iUnitsWide * iPY + iPX] = true;
            // now invert the pixels and the attributes
            Image->Palette->Swap(*Image, X, Y);
            Image->DrawEnd();
            Image->DrawFinalize();
            bDrawn = true;
        }
    }
    return bDrawn;
}
//---------------------------------------------------------------------------

