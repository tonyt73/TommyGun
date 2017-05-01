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
//    imgPalette->Picture->Bitmap = new Graphics::TBitmap();
//    if (true == SAFE_PTR(imgPalette->Picture))
//    {
//        imgPalette->Picture->Bitmap->Width = imgPalette->Width;
//        imgPalette->Picture->Bitmap->Height = imgPalette->Height;
//        imgPalette->Picture->Bitmap->PixelFormat = pf32bit;
//    }
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
	panPen->Color = m_Palette.ZXPalette::GetColor(m_Palette.Pen);
	panPen->Font->Color = (ZXPalette::Luminance(panPen->Color) < 128) ? clWhite : clBlack;
	panBrush->Color = m_Palette.ZXPalette::GetColor(m_Palette.Brush);
	panBrush->Font->Color = (ZXPalette::Luminance(panBrush->Color) < 128) ? clWhite : clBlack;
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
			imgColourPicker->Picture->Bitmap->Canvas->Brush->Color = m_Palette.ZXPalette::GetColor(y * 64 + x);
			imgColourPicker->Picture->Bitmap->Canvas->FillRect(Rect((x * dX) + 1, (y * dY) + 1, (x * dX) + (dX - 2), (y * dY) + (dY - 2)));
        }
	}
	UpdatePaletteImage();
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
	if (Shift.Contains(ssRight))
	{
		imgColourPickerMouseDown(Sender, mbRight, Shift, X, Y);
	}
	UpdatePaletteImage();
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
		unsigned char index = y * 64 + x;
		if (Button == mbLeft)
		{
			// set Pen
			m_Palette.Pen = index;
		}
		else if (Button == mbRight)
		{
			// set Brush
			m_Palette.Brush = index;
		}

		UpdatePaletteImage();
		m_ImageEditor.SystemRefreshView(m_PluginHandle);
	}
}
//---------------------------------------------------------------------------

