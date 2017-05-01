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
__fastcall ZXComments::ZXComments()
{
}
//---------------------------------------------------------------------------
__fastcall ZXComments::~ZXComments()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXComments::Draw(TCanvas* Canvas)
{
    TColor Color = Canvas->Brush->Color;
    for (int i = 0; i < (int)m_Comments.size(); i++)
    {
        const TRect& Rect = m_Comments[i].Rect;
        DrawFrame(Canvas, Rect, false);
        Canvas->TextRect(TRect(Rect.Left + 2, Rect.Top + 2, Rect.Right - 2, Rect.Bottom - 2), Rect.Left + 2, Rect.Top + 2, m_Comments[i].Text);
    }
    Canvas->Brush->Color = Color;
}
//---------------------------------------------------------------------------
void __fastcall ZXComments::DrawFrame(TCanvas* Canvas, const TRect& Rect, bool bGrabPoints)
{
    Canvas->Brush->Color = clWindowFrame;
    Canvas->Font->Name = "Terminal";
    Canvas->Font->Height = 6;
    Canvas->FrameRect(Rect);
    Canvas->FrameRect(TRect(Rect.Right + 1, Rect.Top    + 2, Rect.Right + 2, Rect.Bottom    ));
    Canvas->FrameRect(TRect(Rect.Left  + 2, Rect.Bottom + 1, Rect.Right + 2, Rect.Bottom + 2));

    Canvas->Brush->Color = clInfoBk;
    Canvas->FillRect (TRect(Rect.Left  + 1, Rect.Top    + 1, Rect.Right - 1, Rect.Bottom - 1));
}
//---------------------------------------------------------------------------
void __fastcall ZXComments::Add(const TRect& Rect, const String& Text)
{
    ZXComment Comment;
    Comment.Rect = Rect;
    Comment.Text = Text;

    m_Comments.push_back(Comment);    
}
//---------------------------------------------------------------------------
void __fastcall ZXComments::Select(const TRect& Rect)
{
    
}
//---------------------------------------------------------------------------
bool __fastcall ZXComments::Select(int X, int Y)
{
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXComments::Remove(void)
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXComments::HasSelection(void)
{
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXComments::SelectClear(void)
{
}
//---------------------------------------------------------------------------
void __fastcall ZXComments::Get(TRect& Rect, String& Text)
{
}
//---------------------------------------------------------------------------
void __fastcall ZXComments::Set(const TRect& Rect, const String& Text)
{
}
//---------------------------------------------------------------------------
void __fastcall ZXComments::Move(int dX, int dY)
{
}
//---------------------------------------------------------------------------

