#pragma link "TButtonUnit"
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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TdlgEnterpriseColors *dlgEnterpriseColors;
Graphics::TBitmap* Bitmap = NULL;
//---------------------------------------------------------------------------
#define RED(x)   (((x & 1)<<2)+((x &  8)>>2)+((x &  64)>>6))
#define GREEN(x) (((x & 2)<<1)+((x & 16)>>3)+((x & 128)>>7))
#define BLUE(x)  (((x & 4)>>1)+((x & 32)>>5)               )
unsigned int Level_8[8] = { 0, 36,  73, 109, 146, 182, 218, 255 };
unsigned int Level_4[4] = { 0, 85, 170, 255                     };
//---------------------------------------------------------------------------
__fastcall TdlgEnterpriseColors::TdlgEnterpriseColors(TComponent* Owner)
: TForm(Owner)
, m_Index(0)
, m_Color(clBlack)
, m_RedIndex(0)
, m_GreenIndex(0)
, m_BlueIndex(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TdlgEnterpriseColors::FormCreate(TObject *Sender)
{
    Bitmap = new Graphics::TBitmap();
    Bitmap->Width  = 16;
    Bitmap->Height = 16;
    Bitmap->PixelFormat = pf32bit;
    int Colour = 0;

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            Bitmap->Canvas->Pixels[x][y] = GetColor(Colour++);
        }
    }
    imgPalette->Picture->Assign(Bitmap);
    imgPalette->Stretch = true;
}
//---------------------------------------------------------------------------
bool __fastcall TdlgEnterpriseColors::Execute(int iColor, bool bUseBias)
{
    m_BiasMode = bUseBias && (iColor > 7);
    m_Index = iColor;
    m_Color = GetColor(m_Index);
    bvlBias->Visible = m_BiasMode;
    panBias->Visible = m_BiasMode;
    panColorInfo->Visible = !m_BiasMode;
    UpdateGUI();
    ShowModal();
    return ModalResult == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TdlgEnterpriseColors::imgPaletteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_BiasMode)
    {
        X /= 128;
        Y /= 12;
        bvlBias->Left =  4 + (X * 128);
        bvlBias->Top  = 48 + (Y *  12);

        m_Index = (Y * 2) + X;
        lblFixBias->Caption = IntToStr(m_Index);
    }
    else
    {
        X /= 16;
        Y /= 12;

        m_Index = Y * 16 + X;
        m_Color = GetColor(m_Index);
    }
    UpdateGUI();
}
//---------------------------------------------------------------------------
void __fastcall TdlgEnterpriseColors::spdR1Click(TObject *Sender)
{
    m_RedIndex = dynamic_cast<TSpeedButton*>(Sender)->Tag - 1;
    UpdateColor();
}
//---------------------------------------------------------------------------
void __fastcall TdlgEnterpriseColors::spdG1Click(TObject *Sender)
{
    m_GreenIndex = dynamic_cast<TSpeedButton*>(Sender)->Tag - 1;
    UpdateColor();
}
//---------------------------------------------------------------------------
void __fastcall TdlgEnterpriseColors::spdB1Click(TObject *Sender)
{
    m_BlueIndex = dynamic_cast<TSpeedButton*>(Sender)->Tag - 1;
    UpdateColor();
}
//---------------------------------------------------------------------------
void __fastcall TdlgEnterpriseColors::UpdateColor()
{
    unsigned int R = Level_8[m_RedIndex  ] <<  0;
    unsigned int G = Level_8[m_GreenIndex] <<  8;
    unsigned int B = Level_4[m_BlueIndex ] << 16;

    TColor NewColor = (TColor)(R | G | B);

    panColour->Color = NewColor;

    R = (NewColor & 0x000000FF) >>  0;
    G = (NewColor & 0x0000FF00) >>  8;
    B = (NewColor & 0x00FF0000) >> 16;

    lblRGB->Caption = IntToStr(R) + ", " + IntToStr(G) + ", " + IntToStr(B);

    m_Index = GetIndex(NewColor);
    m_Color = GetColor(m_Index);
    lblIndex->Caption = IntToStr(m_Index);
}
//---------------------------------------------------------------------------
void __fastcall TdlgEnterpriseColors::UpdateGUI()
{
    panColour->Color = m_Color;
    lblIndex->Caption = m_Index;
    unsigned char R = (panColour->Color & 0x000000FF) >>  0;
    unsigned char G = (panColour->Color & 0x0000FF00) >>  8;
    unsigned char B = (panColour->Color & 0x00FF0000) >> 16;

    lblRGB->Caption = IntToStr(R) + ", " + IntToStr(G) + ", " + IntToStr(B);
}
//---------------------------------------------------------------------------
TColor __fastcall TdlgEnterpriseColors::GetColor(int iIndex)
{
    unsigned int R, G, B;

    R = Level_8[RED  (iIndex)] <<  0;
    G = Level_8[GREEN(iIndex)] <<  8;
    B = Level_4[BLUE (iIndex)] << 16;

    TColor Colour = (TColor)(R | G | B);
    return Colour;
}
//---------------------------------------------------------------------------
int __fastcall TdlgEnterpriseColors::GetIndex(TColor Colour)
{
    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            if (Colour == imgPalette->Picture->Bitmap->Canvas->Pixels[x][y])
            {
                return y * 16 + x;
            }
        }
    }
    return 0;
}
//---------------------------------------------------------------------------

