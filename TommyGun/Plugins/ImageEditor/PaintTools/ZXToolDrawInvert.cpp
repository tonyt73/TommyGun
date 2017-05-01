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
__fastcall ZXToolDrawInvert::ZXToolDrawInvert()
: ZXToolInterface("Invert Attributes"),
  m_InvertGrid(NULL)
{
}
//---------------------------------------------------------------------------
__fastcall ZXToolDrawInvert::~ZXToolDrawInvert()
{
    SAFE_ARRAY_DELETE(m_InvertGrid);
}
//---------------------------------------------------------------------------
void __fastcall ZXToolDrawInvert::AllocateInvertGrid(ZXImage* Image)
{
    SAFE_ARRAY_DELETE(m_InvertGrid);
    m_iUnitsWide = Image->Width  / Image->Palette->PixelsWidePerAttribute;
    m_iUnitsHigh = Image->Height / Image->Palette->PixelsHighPerAttribute;
    m_InvertGrid = new bool[m_iUnitsWide * m_iUnitsHigh];
    ZeroMemory(m_InvertGrid, m_iUnitsWide * m_iUnitsHigh * sizeof(bool));
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawInvert::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (true == Enabled && true == Shift.Contains(ssLeft))
    {
        AllocateInvertGrid(Image);
        bDrawn = MouseMove(Image, Shift, X, Y);
    }
    return bDrawn;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawInvert::DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (true == Enabled && true == Shift.Contains(ssLeft) && 0 <= X && X < Image->Width && 0 <= Y && Y < Image->Height)
    {
        int iPX = X / Image->Palette->PixelsWidePerAttribute;
        int iPY = Y / Image->Palette->PixelsHighPerAttribute;
        if (false == m_InvertGrid[m_iUnitsWide * iPY + iPX])
        {
            Image->DrawInitialize();
            Image->DrawBegin();
            // invert the grid position
            m_InvertGrid[m_iUnitsWide * iPY + iPX] = true;
            // now invert the pixels and the attributes
            Image->Palette->Invert(*Image, X, Y);
            Image->DrawEnd();
            Image->DrawFinalize();
            bDrawn = true;
        }
    }
    return bDrawn;
}
//---------------------------------------------------------------------------

