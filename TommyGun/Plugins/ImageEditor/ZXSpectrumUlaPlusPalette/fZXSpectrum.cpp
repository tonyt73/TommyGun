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
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace SpectrumPalette;
//---------------------------------------------------------------------------
TfrmZXSpectrum *frmZXSpectrum = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmZXSpectrum::TfrmZXSpectrum(TComponent* Owner)
: TForm(Owner)
, m_SelectionIsInk(true)
, m_ChangingPalettes(false)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXSpectrum::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    imgPalette->Picture->Bitmap = new Graphics::TBitmap();
    if (true == SAFE_PTR(imgPalette->Picture))
    {
        imgPalette->Picture->Bitmap->Width = imgPalette->Width;
        imgPalette->Picture->Bitmap->Height = imgPalette->Height;
        imgPalette->Picture->Bitmap->PixelFormat = pf32bit;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXSpectrum::Release(void)
{
    RL_HRESULT(S_OK);
    panZXSpectrumPalette->Parent->RemoveControl(panZXSpectrumPalette);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXSpectrum::Palette(ZXPalette*& Palette)
{
    RL_METHOD
    RL_HRESULT(S_OK);
    Palette = NULL;
    Palette = &m_Palette;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    UpdatePaletteImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::tbRedChange(TObject *Sender)
{
    lblRed->Caption = IntToStr(tbRed->Position);
    if (!m_ChangingPalettes)
    {
        unsigned int index = m_SelectionIsInk ? m_Palette.Clut * 16 + m_Palette.Ink : m_Palette.Clut * 16 + 8 + m_Palette.Paper;
        m_Palette.SetColor(index, tbRed->Position, tbGreen->Position, tbBlue->Position);
        UpdatePaletteImage();
        UpdateRGB();
        m_ImageEditor.SystemRefreshView(m_PluginHandle);
        cmbPalettes->ItemIndex = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::tbGreenChange(TObject *Sender)
{
    lblGreen->Caption = IntToStr(tbGreen->Position);
    if (!m_ChangingPalettes)
    {
        unsigned int index = m_SelectionIsInk ? m_Palette.Clut * 16 + m_Palette.Ink : m_Palette.Clut * 16 + 8 + m_Palette.Paper;
        m_Palette.SetColor(index, tbRed->Position, tbGreen->Position, tbBlue->Position);
        UpdatePaletteImage();
        UpdateRGB();
        m_ImageEditor.SystemRefreshView(m_PluginHandle);
        cmbPalettes->ItemIndex = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::tbBlueChange(TObject *Sender)
{
    lblBlue->Caption = IntToStr(tbBlue->Position);
    if (!m_ChangingPalettes)
    {
        unsigned int index = m_SelectionIsInk ? m_Palette.Clut * 16 + m_Palette.Ink : m_Palette.Clut * 16 + 8 + m_Palette.Paper;
        m_Palette.SetColor(index, tbRed->Position, tbGreen->Position, tbBlue->Position);
        UpdatePaletteImage();
        UpdateRGB();
        m_ImageEditor.SystemRefreshView(m_PluginHandle);
        cmbPalettes->ItemIndex = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::Panel1Resize(TObject *Sender)
{
    UpdatePaletteImage();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::FormShow(TObject *Sender)
{
    // redraw the palette image
    UpdatePaletteImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::UpdatePaletteImage()
{
    int dX = imgPalette->Width / 18;
    int dY = (imgPalette->Height - 16) / 4;
    // clear the control
    imgPalette->Picture->Bitmap->Canvas->Brush->Color = clBlack;
    imgPalette->Picture->Bitmap->Canvas->FillRect(Rect(0, 0, imgPalette->Width, imgPalette->Height));
    imgPalette->Picture->Bitmap->Canvas->Brush->Color = clBlack;
    imgPalette->Picture->Bitmap->Canvas->Pen->Color = clWhite;
    imgPalette->Picture->Bitmap->Canvas->MoveTo((dX *  0) + (dX/2), 14);
    imgPalette->Picture->Bitmap->Canvas->LineTo((dX *  0) + (dX/2),  8);
    imgPalette->Picture->Bitmap->Canvas->LineTo((dX *  9) - (dX/2),  8);
    imgPalette->Picture->Bitmap->Canvas->LineTo((dX *  9) - (dX/2), 14);
    imgPalette->Picture->Bitmap->Canvas->MoveTo((dX *  9) + (dX/2), 14);
    imgPalette->Picture->Bitmap->Canvas->LineTo((dX *  9) + (dX/2),  8);
    imgPalette->Picture->Bitmap->Canvas->LineTo((dX * 18) - (dX/2),  8);
    imgPalette->Picture->Bitmap->Canvas->LineTo((dX * 18) - (dX/2), 14);
    TFont* oldFont = imgPalette->Picture->Bitmap->Canvas->Font;
    TFont* newFont = new TFont();
    newFont->Color = clWhite;
    newFont->Height = 8;
    newFont->Name = "Courier";
    imgPalette->Picture->Bitmap->Canvas->Font = newFont;
    imgPalette->Picture->Bitmap->Canvas->TextOut(dX * 3 + 2, 2, "INK");
    imgPalette->Picture->Bitmap->Canvas->TextOut(dX * 11 + 2, 2, "PAPER");
    newFont->Name = "Arial";
    newFont->Size = 6;
    imgPalette->Picture->Bitmap->Canvas->Font = newFont;
    // draw the palettes
    // INK
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            imgPalette->Picture->Bitmap->Canvas->Brush->Color = m_Palette.GetColor( (y * 16) + x);
            imgPalette->Picture->Bitmap->Canvas->FillRect(Rect((x * dX) + 2, 16 + (y * dY) + 2, (x * dX) + dX - 4, 16 + (y * dY) + dY - 4));
        }
        // Transparent
        imgPalette->Picture->Bitmap->Canvas->Brush->Color = clBlack;
        imgPalette->Picture->Bitmap->Canvas->TextOut((8 * dX) + 4, 16 + (y * dY), "T");
    }
    // PAPER
    for (int y = 0; y < 4; y++)
    {
        for (int x = 8; x < 16; x++)
        {
            imgPalette->Picture->Bitmap->Canvas->Brush->Color = m_Palette.GetColor( (y * 16) + x);
            imgPalette->Picture->Bitmap->Canvas->FillRect(Rect(((x + 1) * dX) + 2, 16 + (y * dY) + 2, ((x + 1) * dX) + dX - 4, 16 + (y * dY) + dY - 4));
        }
        // Transparent
        imgPalette->Picture->Bitmap->Canvas->Brush->Color = clBlack;
        imgPalette->Picture->Bitmap->Canvas->TextOut((17 * dX) + 4, 16 + (y * dY), "T");
    }
    imgPalette->Picture->Bitmap->Canvas->Font = oldFont;

    // draw the ink and paper indicators
    imgPalette->Picture->Bitmap->Canvas->Brush->Color = clWhite;
    int y = 16 + m_Palette.Clut * dY;
    int x = m_Palette.Ink * dX;
    TRect rI(x - 1, y - 1, x + dX - 1, y + dY - 1);
    imgPalette->Picture->Bitmap->Canvas->FrameRect(rI);
    x = (9 + m_Palette.Paper) * dX;
    TRect rP(x - 1, y - 1, x + dX - 1, y + dY - 1);
    imgPalette->Picture->Bitmap->Canvas->FrameRect(rP);
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::UpdateRGB()
{
    if ((m_SelectionIsInk && m_Palette.Ink == 8) || (!m_SelectionIsInk && m_Palette.Paper == 8))
    {
        tbRed->Enabled = false;
        tbGreen->Enabled = false;
        tbBlue->Enabled = false;
        return;
    }
    tbRed->Enabled = true;
    tbGreen->Enabled = true;
    tbBlue->Enabled = true;

    unsigned char R, G, B;
    if (m_SelectionIsInk)
    {
        m_Palette.GetColor(m_Palette.Clut, m_Palette.Ink, R, G, B);
    }
    else
    {
        m_Palette.GetColor(m_Palette.Clut, 8 + m_Palette.Paper, R, G, B);
    }
    tbRed->Position = R;
    tbGreen->Position = G;
    tbBlue->Position = B;
    Label5->Caption = m_Palette.GetColor(R, G, B);
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::imgPaletteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Y >= 16)
    {
        int dX = imgPalette->Width / 18;
        int dY = (imgPalette->Height - 16) / 4;
        Y -= 16;
        m_Palette.Clut = Y / dY;
        if (X / dX < 9)
        {
            m_Palette.Ink = X / dX;
            m_SelectionIsInk = true;
        }
        else
        {
            m_Palette.Paper = (X - (dX * 9)) / dX;
            m_SelectionIsInk = false;
        }
        UpdateRGB();
        UpdatePaletteImage();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::imgPaletteMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    if (Shift.Contains(ssLeft))
    {
        imgPaletteMouseDown(Sender, mbLeft, Shift, X, Y);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::UpdatePalettes()
{
    cmbPalettes->Items->Clear();
    cmbPalettes->Items->Add("Default");
    cmbPalettes->Items->Add("ZX Spectrum");
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::cmbPalettesChange(TObject *Sender)
{
    m_ChangingPalettes = true;
    switch (cmbPalettes->ItemIndex)
    {
        case 0:
            m_Palette.UseImagePalette();
            break;
        case 1:
            m_Palette.UseDefaultPalette();
            break;
        case 2:
            m_Palette.UseZXSpectrumPalette();
            break;
    }

    UpdateRGB();
    UpdatePaletteImage();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
    m_ChangingPalettes = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::Panel2Resize(TObject *Sender)
{
    imgColourPicker->Picture->Bitmap->Width = imgColourPicker->Width;
    imgColourPicker->Picture->Bitmap->Height = imgColourPicker->Height;
    imgColourPicker->Picture->Bitmap->PixelFormat = pf32bit;
    imgColourPicker->Picture->Bitmap->Canvas->Brush->Color = clBlack;
    imgColourPicker->Picture->Bitmap->Canvas->FillRect(imgColourPicker->ClientRect);

    int dX = std::max(8, (int)(imgColourPicker->Width / 64));
    int dY = imgColourPicker->Height / 4;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            imgColourPicker->Picture->Bitmap->Canvas->Brush->Color = m_Palette.DecodeColor(y * 64 + x);
            imgColourPicker->Picture->Bitmap->Canvas->FillRect(Rect((x * dX) + 1, (y * dY) + 1, (x * dX) + (dX - 2), (y * dY) + (dY - 2)));
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::imgColourPickerMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    unsigned int dX = std::max(8, (int)(imgColourPicker->Width / 64));
    unsigned int dY = imgColourPicker->Height / 4;
    unsigned int x = X / dX;
    unsigned int y = Y / dY;

    Panel2Resize(NULL);

    if (x < 64 && y < 4)
    {
        imgColourPicker->Picture->Bitmap->Canvas->Brush->Color = clSilver;
        imgColourPicker->Picture->Bitmap->Canvas->FrameRect(Rect((x * dX), (y * dY), (x * dX) + (dX - 1), (y * dY) + (dY - 1)));
        imgColourPicker->Picture->Bitmap->Canvas->FrameRect(Rect((x * dX) - 1, (y * dY) - 1, (x * dX) + (dX), (y * dY) + (dY)));
    }

    if (Shift.Contains(ssLeft))
    {
        imgColourPickerMouseDown(Sender, mbLeft, Shift, X, Y);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::imgColourPickerMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    unsigned int dX = std::max(8, (int)(imgColourPicker->Width / 64));
    unsigned int dY = imgColourPicker->Height / 4;
    unsigned int x = X / dX;
    unsigned int y = Y / dY;

    if (x < 64 && y < 4)
    {
        unsigned char R, G, B;
        unsigned char index = y * 64 + x;
        m_Palette.DecodeColor(index, R, G, B);

        m_ChangingPalettes = true;
        tbRed->Position = R;
        tbGreen->Position = G;
        tbBlue->Position = B;

        index = m_SelectionIsInk ? m_Palette.Clut * 16 + m_Palette.Ink : m_Palette.Clut * 16 + 8 + m_Palette.Paper;
        m_Palette.SetColor(index, R, G, B);
        UpdatePaletteImage();
        UpdateRGB();
        m_ImageEditor.SystemRefreshView(m_PluginHandle);
        cmbPalettes->ItemIndex = 0;

        m_ChangingPalettes = false;
    }
}
//---------------------------------------------------------------------------

