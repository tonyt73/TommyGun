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
#include "vcl.h"
#pragma hdrstop
#include "fSamCoupeColors.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TdlgSamCoupeColors *dlgSamCoupeColors;
//---------------------------------------------------------------------------
__fastcall TdlgSamCoupeColors::TdlgSamCoupeColors(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TdlgSamCoupeColors::Execute(int iColor)
{
    for (int i = 0; i < ControlCount; i++)
    {
        TPanel* Panel = dynamic_cast<TPanel*>(Controls[i]);
        if (Panel != NULL && 0 < Panel->Tag)
        {
            Panel->BevelOuter = /*Panel->Tag == iColor + 1 ? bvLowered :*/ bvRaised;
        }
    }
    ShowModal();
    return ModalResult == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TdlgSamCoupeColors::panC64BlackClick(TObject *Sender)
{
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    if (Panel != NULL)
    {
        m_Color = Panel->Color;
        for (int i = 0; i < ComponentCount; i++)
        {
            TPanel* Panel = dynamic_cast<TPanel*>(Components[i]);
            if (Panel != NULL && 0 < Panel->Tag)
            {
                Panel->BevelOuter = (Panel == Sender) ? bvLowered : bvRaised;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TdlgSamCoupeColors::imgSamPaletteMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    // update the colour index and the rgb colour value
    if (64 <= X && X < 320 && 32 < Y && Y < 160)
    {
        TColor color = imgSamPalette->Canvas->Pixels[X >> 1][Y >> 1];
        unsigned char R = (color >>  0) & 0x000000FF;
        unsigned char G = (color >>  8) & 0x000000FF;
        unsigned char B = (color >> 16) & 0x000000FF;
        lblColourRGB->Caption = "RGB: " + IntToStr(R) + ", " + IntToStr(G) + ", " + IntToStr(B);

        int iIndex = (((Y - 32) & 0xF0)) + ((X - 64) >> 4);
        lblColourIndexValue->Caption = IntToStr(iIndex) + " (0x" + IntToHex(iIndex, 2) + ")";
    }
}
//---------------------------------------------------------------------------
void __fastcall TdlgSamCoupeColors::imgSamPaletteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (64 <= X && X < 320 && 32 < Y && Y < 160)
    {
        panColour->Color = imgSamPalette->Canvas->Pixels[X >> 1][Y >> 1];
        m_Color = panColour->Color;
        panColour->Left = 64 + (((X - 64) >> 4) << 4);
        panColour->Top  = 80 + (((Y - 32) >> 4) << 4);
        int iIndex = (((Y - 32) & 0xF0)) + ((X - 64) >> 4);
        lblSelectedColourIndex->Caption = IntToStr(iIndex) + " (0x" + IntToHex(iIndex, 2) + ")";
    }
}
//---------------------------------------------------------------------------

