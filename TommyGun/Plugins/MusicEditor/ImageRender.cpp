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
__fastcall ZXImageRender::ZXImageRender()
: m_bDirty(true)
{
}
//---------------------------------------------------------------------------
void __fastcall ZXImageRender::Render()
{
    if (m_bDirty)
    {
        DoRender();
        m_bDirty = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageRender::Refresh()
{
    m_bDirty = true;
    Render();
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
__fastcall ZXGridRender::ZXGridRender()
: ZXImageRender()
, m_iGridWidth(12)
, m_iGridHeight(12)
, m_iSectionWidth(8)
, m_iHighlightColumn(-1)
, m_bStretch(false)
, m_LightSection(TColor(0x443533))
, m_DarkSection(TColor(0x3E2F2D))
, m_LightLine(TColor(0x524341))
, m_MediumLine(TColor(0x625352))
, m_BrightLine(TColor(0x7E6F6D))
, m_Highlight(TColor(0x544543))
{
}
//---------------------------------------------------------------------------
void __fastcall ZXGridRender::RenderGrid(TCanvas* pCanvas, int Width, int Height)
{
    if (Height == 0)
        return;
        
    int ws     = m_iGridWidth * 32;
    int ws2    = ws * 2;
    // draw the light section
    pCanvas->Brush->Color = m_LightSection;
    for (int w = 0; w < Width; w += ws2)
    {
        TRect Rect(w, 0, w + ws, Height);
        pCanvas->FillRect(Rect);
    }
    // draw the dark section
    pCanvas->Brush->Color = m_DarkSection;
    for (int w = ws; w < Width; w += ws2)
    {
        TRect Rect(w, 0, w + ws, Height);
        pCanvas->FillRect(Rect);
    }
    if (m_iHighlightColumn >= 0 && m_iHighlightColumn < Width / m_iGridWidth)
    {
        // draw the highlight section
        pCanvas->Brush->Color = m_Highlight;
        TRect Rect(ws * m_iGridWidth, 0, (ws + 1) * m_iGridWidth, Height);
        pCanvas->FillRect(Rect);
    }
    // draw the light grid lines
    pCanvas->Pen->Color = m_LightLine;
    ws = m_iGridWidth * 2;
    for (int w = m_iGridWidth; w < Width; w += ws)
    {
        pCanvas->MoveTo(w, 0);
        pCanvas->LineTo(w, Height);
    }
    for (int h = m_iGridHeight; h < Height; h += ws)
    {
        pCanvas->MoveTo(0, h);
        pCanvas->LineTo(Width, h);
    }
    // draw the medium grid lines
    pCanvas->Pen->Color = m_MediumLine;
    ws = m_iGridWidth * 2;
    int gp = 1;
    for (int w = ws; w < Width; w += ws, ++gp)
    {
        if (gp % 4)
        {
            pCanvas->MoveTo(w, 0);
            pCanvas->LineTo(w, Height);
        }
    }
    ws = m_iGridHeight * 2;
    gp = 1;
    for (int h = ws; h < Height; h += ws, ++gp)
    {
        if (gp % 4)
        {
            pCanvas->MoveTo(0, h);
            pCanvas->LineTo(Width, h);
        }
    }
    // draw the dark grid lines
    pCanvas->Pen->Color = m_BrightLine;
    ws = m_iGridWidth * 8;
    for (int w = 0; w < Width; w += ws)
    {
        pCanvas->MoveTo(w, 0);
        pCanvas->LineTo(w, Height);
    }
    for (int h = 0; h < Height; h += ws)
    {
        pCanvas->MoveTo(0, h);
        pCanvas->LineTo(Width, h);
    }
}
//---------------------------------------------------------------------------

