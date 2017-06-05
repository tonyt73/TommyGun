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
#include <math.h>
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
, m_ColorPicker(new Graphics::TBitmap())
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXSpectrum::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    m_ColorPicker = new Graphics::TBitmap();
    m_ColorPicker->Width = 132;  // 2 + 384. 384 / 6 = 64
    m_ColorPicker->Height = 100;
    m_ColorPicker->PixelFormat = pf32bit;
    DrawColorPicker();    
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
    UpdatePaletteImage();
	return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::OnUpdatePaletteGUI(void)
{
    // the palette colors and update the palette form
    UpdatePaletteImage();
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
	panPen->Color = m_Palette.ZXPalette::GetColor(m_Palette.Pen);
	panPen->Font->Color = (ZXPalette::Luminance(panPen->Color) < 128) ? clWhite : clBlack;
    lblPenRGB->Caption = IntToHex(panPen->Color & 0x000000FF,2) + "," + IntToHex((panPen->Color & 0x0000FF00)>>8,2) + "," +IntToHex((panPen->Color & 0x00FF0000)>>16,2);
    lblPenIndex->Caption = IntToStr(m_Palette.Pen) + " (" + IntToHex(m_Palette.Pen,2) + ")";
	panBrush->Color = m_Palette.ZXPalette::GetColor(m_Palette.Brush);
	panBrush->Font->Color = (ZXPalette::Luminance(panBrush->Color) < 128) ? clWhite : clBlack;
    lblBrushRGB->Caption = IntToHex(panBrush->Color & 0x000000FF,2) + "," + IntToHex((panBrush->Color & 0x0000FF00)>>8,2) + "," +IntToHex((panBrush->Color & 0x00FF0000)>>16,2);
    lblBrushIndex->Caption = IntToStr(m_Palette.Brush) + " (" + IntToHex(m_Palette.Brush,2) + ")";
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

    UpdatePaletteImage();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
    m_ChangingPalettes = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::imgColourPickerMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    m_ColorCursor.x = X;
    m_ColorCursor.y = Y;

    FormResize(NULL);

	if (Shift.Contains(ssLeft))
	{
		imgColourPickerMouseDown(Sender, mbLeft, Shift, X, Y);
	}
	if (Shift.Contains(ssRight))
	{
		imgColourPickerMouseDown(Sender, mbRight, Shift, X, Y);
	}
	UpdatePaletteImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::imgColourPickerMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    TColor color = imgColourPicker->Picture->Bitmap->Canvas->Pixels[X][Y];
    if (Button == mbLeft)
    {
        // set Pen
        m_Palette.Pen = m_Palette.ZXPalette::GetColor(color);
    }
    else if (Button == mbRight)
    {
        // set Brush
        m_Palette.Brush = m_Palette.ZXPalette::GetColor(color);
    }

    UpdatePaletteImage();
    m_ImageEditor.SystemRefreshView(m_PluginHandle);
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::DrawColorPicker()
{
    int greyWidth = 4;
    m_ColorPicker->Canvas->Brush->Color = clBlack;
    m_ColorPicker->Canvas->FillRect(Rect(0, 0, imgColourPicker->Picture->Bitmap->Width, imgColourPicker->Picture->Bitmap->Height));
    // draw the greys on the left
    m_ColorPicker->Canvas->Brush->Color = m_Palette.ZXPalette::GetColor(0xff);
    m_ColorPicker->Canvas->FillRect(Rect(0, 0, greyWidth, 20));
    m_ColorPicker->Canvas->Brush->Color = m_Palette.ZXPalette::GetColor(0x92);
    m_ColorPicker->Canvas->FillRect(Rect(0, 20, greyWidth, 40));
    m_ColorPicker->Canvas->Brush->Color = m_Palette.ZXPalette::GetColor(0x49);
    m_ColorPicker->Canvas->FillRect(Rect(0, 40, greyWidth, 60));
    m_ColorPicker->Canvas->Brush->Color = m_Palette.ZXPalette::GetColor(0x00);
    m_ColorPicker->Canvas->FillRect(Rect(0, 60, greyWidth, 80));
    m_ColorPicker->Canvas->Brush->Color = m_Palette.ZXPalette::GetColor(m_Palette.ZXPalette::GetClosestColor(clFuchsia));
    m_ColorPicker->Canvas->FillRect(Rect(0, 80, greyWidth, 100));

    float w = m_ColorPicker->Width - greyWidth;
    THsl hsl;
    float h = m_ColorPicker->Height;
    for (int y = 0; y < m_ColorPicker->Height; y++)
    {
        for (int x = 0; x < w; x++)
        {
            hsl.h = ((float)x / w);
            hsl.s = 1.0f;
            hsl.l = 1.0f - ((float)y / h);
            m_ColorPicker->Canvas->Pixels[greyWidth + x][y] = m_Palette.ZXPalette::GetColor(m_Palette.ZXPalette::GetClosestColor(hsl));
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::FormResize(TObject *Sender)
{
    if (imgColourPicker->Picture->Bitmap == NULL)
    {
        imgColourPicker->Picture->Bitmap = new Graphics::TBitmap();
        imgColourPicker->Picture->Bitmap->PixelFormat = pf32bit;
    }
    imgColourPicker->Picture->Bitmap->Width = imgColourPicker->Width;
    imgColourPicker->Picture->Bitmap->Height = imgColourPicker->Height;
    StretchBlt(imgColourPicker->Picture->Bitmap->Canvas->Handle,
        0, 0, imgColourPicker->Picture->Bitmap->Width, imgColourPicker->Picture->Bitmap->Height,
        m_ColorPicker->Canvas->Handle, 0, 0, m_ColorPicker->Width, m_ColorPicker->Height,
        SRCCOPY);
    // draw the cursor
    imgColourPicker->Picture->Bitmap->Canvas->Brush->Color = clBlack;
    int size = 8;
    TRect rect(m_ColorCursor.x - size, m_ColorCursor.y - size, m_ColorCursor.x + size, m_ColorCursor.y + size);
    imgColourPicker->Picture->Bitmap->Canvas->FrameRect(rect);
    rect.left++;
    rect.top++;
    rect.right -= 2;
    rect.bottom -= 2;
    imgColourPicker->Picture->Bitmap->Canvas->Brush->Color = clWhite;
    imgColourPicker->Picture->Bitmap->Canvas->FrameRect(rect);
}
//---------------------------------------------------------------------------

