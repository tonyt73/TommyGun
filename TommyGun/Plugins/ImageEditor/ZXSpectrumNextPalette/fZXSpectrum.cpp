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
#include "..\ZXPalette.h"
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
, m_PaletteChanged(true)
, m_QuickColorPicker(new Graphics::TBitmap())
, m_SpectrumColorPicker(new Graphics::TBitmap())
, m_GridColorPicker(new Graphics::TBitmap())
, m_HueColorPicker(new Graphics::TBitmap())
, m_LuminanceColorPicker(new Graphics::TBitmap())
, m_CurrentPicker(ptGrid)
, m_NextPicker(ptSpectrum)
, m_QuickPickerWidth(24)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXSpectrum::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    m_Palette.OnUpdatePaletteGUI = OnUpdatePaletteGUI;
    m_QuickColorPicker = new Graphics::TBitmap();
    m_QuickColorPicker->Width = 1;
    m_QuickColorPicker->Height = 5;
    m_QuickColorPicker->PixelFormat = pf32bit;
    m_SpectrumColorPicker = new Graphics::TBitmap();
    m_SpectrumColorPicker->Width = 100;
    m_SpectrumColorPicker->Height = 180;
    m_SpectrumColorPicker->PixelFormat = pf32bit;
    m_GridColorPicker = new Graphics::TBitmap();
    m_GridColorPicker->Width = 32;
    m_GridColorPicker->Height = 8;
    m_GridColorPicker->PixelFormat = pf32bit;
    m_HueColorPicker = new Graphics::TBitmap();
    m_HueColorPicker->Width = 32;
    m_HueColorPicker->Height = 8;
    m_HueColorPicker->PixelFormat = pf32bit;
    m_LuminanceColorPicker = new Graphics::TBitmap();
    m_LuminanceColorPicker->Width = 32;
    m_LuminanceColorPicker->Height = 8;
    m_LuminanceColorPicker->PixelFormat = pf32bit;
    DrawPicker(); 
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
void __fastcall TfrmZXSpectrum::FormResize(TObject *Sender)
{
    DrawPicker();
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::actPickerSpectrumExecute(TObject *Sender)
{
    m_NextPicker = ptSpectrum;
    DrawPicker();
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::actPickerGridExecute(TObject *Sender)
{
    m_NextPicker = ptGrid;
    DrawPicker();
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::actPickerHeatExecute(TObject *Sender)
{
    m_NextPicker = ptHeatMap;
    DrawPicker();
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::actPickerHueExecute(TObject *Sender)
{
    m_NextPicker = ptHueSorted;
    DrawPicker();
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::actPickerLuminanceExecute(TObject *Sender)
{
    m_NextPicker = ptLuminanceSorted;
    DrawPicker();
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::DrawPicker()
{
    bool resized = false;
    if (imgColourPicker->Picture->Bitmap == NULL)
    {
        imgColourPicker->Picture->Bitmap = new Graphics::TBitmap();
        imgColourPicker->Picture->Bitmap->PixelFormat = pf32bit;
    }
    if (imgColourPicker->Picture->Bitmap->Width != imgColourPicker->Width || imgColourPicker->Picture->Bitmap->Height != imgColourPicker->Height)
    {
        imgColourPicker->Picture->Bitmap->Width = imgColourPicker->Width;
        imgColourPicker->Picture->Bitmap->Height = imgColourPicker->Height;
        resized = true;
    }

    if (m_CurrentPicker != m_NextPicker || resized)
    {
        m_CurrentPicker = m_NextPicker;
        if (m_PaletteChanged)
        {
            m_PaletteChanged = false;
            DrawQuickPicker();
            DrawSpectrumPicker();
            DrawGridPicker();
            DrawLuminancePicker();
            DrawHuePicker();
        }
    }

    Graphics::TBitmap* picker = NULL;
    switch (m_NextPicker)
    {
        case ptSpectrum:        picker = m_SpectrumColorPicker;             break;
        case ptGrid:            picker = m_GridColorPicker;                 break;
        case ptHeatMap:         picker = imgHeatMapPick->Picture->Bitmap;   break;
        case ptHueSorted:       picker = m_HueColorPicker;                  break;
        case ptLuminanceSorted: picker = m_LuminanceColorPicker;            break;
    }

    // show the quick picker
    if (m_QuickPickerWidth)
    {
        StretchBlt(imgColourPicker->Picture->Bitmap->Canvas->Handle,
            0, 0, m_QuickPickerWidth, imgColourPicker->Picture->Bitmap->Height,
            m_QuickColorPicker->Canvas->Handle, 0, 0, m_QuickColorPicker->Width, m_QuickColorPicker->Height,
            SRCCOPY);
    }

    // show the picker bitmap
    StretchBlt(imgColourPicker->Picture->Bitmap->Canvas->Handle,
        m_QuickPickerWidth, 0, imgColourPicker->Picture->Bitmap->Width - m_QuickPickerWidth, imgColourPicker->Picture->Bitmap->Height,
        picker->Canvas->Handle, 0, 0, picker->Width, picker->Height,
        SRCCOPY);

    // draw the cursor
    imgColourPicker->Picture->Bitmap->Canvas->Pen->Color = clBlack;
    imgColourPicker->Picture->Bitmap->Canvas->Brush->Style = bsClear;
    int size = 5;
    TRect rect(m_ColorCursor.x - size, m_ColorCursor.y - size, m_ColorCursor.x + size, m_ColorCursor.y + size);
    imgColourPicker->Picture->Bitmap->Canvas->Ellipse(rect);
    rect.left++;
    rect.top++;
    rect.right -= 2;
    rect.bottom -= 2;
    imgColourPicker->Picture->Bitmap->Canvas->Pen->Color = clWhite;
    imgColourPicker->Picture->Bitmap->Canvas->Ellipse(rect);
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::DrawQuickPicker()
{
    // TBD: Change to closest colour
    m_QuickColorPicker->Canvas->Pixels[0][0] = m_Palette.ZXPalette::GetColor(0xff);
    m_QuickColorPicker->Canvas->Pixels[0][1] = m_Palette.ZXPalette::GetColor(0x92);
    m_QuickColorPicker->Canvas->Pixels[0][2] = m_Palette.ZXPalette::GetColor(0x49);
    m_QuickColorPicker->Canvas->Pixels[0][3] = m_Palette.ZXPalette::GetColor(0x00);
    m_QuickColorPicker->Canvas->Pixels[0][4] = m_Palette.ZXPalette::GetColor(m_Palette.ZXPalette::GetClosestColor(clFuchsia));
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::DrawSpectrumPicker()
{
    float w = m_SpectrumColorPicker->Width;
    THsl hsl;
    float h = m_SpectrumColorPicker->Height / 2.f;
    for (int y = 0; y <= h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            hsl.h = ((float)x / w);
            hsl.s = 1.0f;
            hsl.l = 1.0f - ((float)y / h);
            m_SpectrumColorPicker->Canvas->Pixels[x][y] = m_Palette.ZXPalette::GetColor(m_Palette.ZXPalette::GetClosestColor(hsl));
        }
    }
    for (int y = 0; y <= h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            hsl.h = ((float)x / w);
            hsl.s = 0.5f;
            hsl.l = 1.0f - ((float)y / h);
            m_SpectrumColorPicker->Canvas->Pixels[x][m_SpectrumColorPicker->Height - y] = m_Palette.ZXPalette::GetColor(m_Palette.ZXPalette::GetClosestColor(hsl));
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::DrawGridPicker()
{
    int cols = 32;
    int rows = 256 / cols;
    int w = m_GridColorPicker->Width / cols;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            m_GridColorPicker->Canvas->Pixels[c][r] = m_Palette.ZXPalette::GetColor(r * cols + c);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::DrawHuePicker()
{
    TColor colorTable[256];
    int cols = 32;
    int rows = 256 / cols;
    int w = m_GridColorPicker->Width / cols;
    if (m_Palette.ZXPalette::GetColorTable(colorTable, 256, ctsHueHSBSorted))
    {
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                m_HueColorPicker->Canvas->Pixels[c][r] = colorTable[r * cols + c];
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXSpectrum::DrawLuminancePicker()
{
    TColor colorTable[256];
    int cols = 32;
    int rows = 256 / cols;
    int w = m_GridColorPicker->Width / cols;
    if (m_Palette.ZXPalette::GetColorTable(colorTable, 256, ctsLuminance))
    {
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                m_LuminanceColorPicker->Canvas->Pixels[c][r] = colorTable[r * cols + c];
            }
        }
    }
}
//---------------------------------------------------------------------------

