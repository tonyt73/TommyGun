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
__fastcall ZXToolDrawFill::ZXToolDrawFill()
: ZXToolInterface("Fill")
{
    m_Bitmap = new Graphics::TBitmap();
    m_Bitmap->PixelFormat = pf32bit;
}
//---------------------------------------------------------------------------
__fastcall ZXToolDrawFill::~ZXToolDrawFill()
{
    SAFE_DELETE(m_Bitmap);
}
//---------------------------------------------------------------------------
void __fastcall ZXToolDrawFill::FloodFill(ZXImage* Image, int X, int Y, bool bSet)
{
    if (m_MatchColor == m_Bitmap->Canvas->Pixels[X][Y])
    {
        // add the start position to fill queue
        m_FillQueue.push(TPoint(X, Y));

        // process all points in the queue
        while (!m_FillQueue.empty())
        {
            // get the current point in the queue
            TPoint pt = m_FillQueue.front();
            m_FillQueue.pop();
            // does it match the color?
            if (m_MatchColor == m_Bitmap->Canvas->Pixels[pt.x][pt.y])
            {
                // yep, so fill the point
                m_Bitmap->Canvas->Pixels[pt.x][pt.y] = m_FillColor;
                Image->DrawPoint(pt.x, pt.y, bSet);
                // now check West
                if (m_MatchColor == m_Bitmap->Canvas->Pixels[pt.x-1][pt.y])
                {
                    // add the West point to queue
                    m_FillQueue.push(TPoint(pt.x-1, pt.y));
                }
                // check East
                if (m_MatchColor == m_Bitmap->Canvas->Pixels[pt.x+1][pt.y])
                {
                    // add the East point to queue
                    m_FillQueue.push(TPoint(pt.x+1, pt.y));
                }
                // check South
                if (m_MatchColor == m_Bitmap->Canvas->Pixels[pt.x][pt.y-1])
                {
                    // add the South point to queue
                    m_FillQueue.push(TPoint(pt.x, pt.y-1));
                }
                // check North
                if (m_MatchColor == m_Bitmap->Canvas->Pixels[pt.x][pt.y+1])
                {
                    // add the North point to queue
                    m_FillQueue.push(TPoint(pt.x, pt.y+1));
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDrawFill::DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDrawn = false;
    if (Shift.Contains(ssLeft) || Shift.Contains(ssRight) && true == SAFE_PTR(m_Bitmap))
    {
        // copy the images bitmap
        m_Bitmap->Width  = Image->Width;
        m_Bitmap->Height = Image->Height;
        Image->Invalidate();
        Image->Draw(m_Bitmap->Canvas);
        // set the brush color from the images palette and based on whether the users pressed the left or right mouse button
        m_FillColor  = Shift.Contains(ssLeft) ? Image->Palette->PenColor : Image->Palette->BrushColor;
        m_MatchColor = m_Bitmap->Canvas->Pixels[X][Y];
        if (m_FillColor != m_MatchColor)
        {
            // do the fill
            Image->DrawInitialize();
            Image->DrawBegin();
            FloodFill(Image, X, Y, Shift.Contains(ssLeft));
            Image->DrawEnd();
            Image->DrawFinalize();
            Image->ReDraw();
            bDrawn = true;
        }
    }
    return bDrawn;
}
//---------------------------------------------------------------------------

