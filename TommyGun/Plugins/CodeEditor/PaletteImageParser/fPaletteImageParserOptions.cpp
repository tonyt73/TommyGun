#pragma link "KSpinEdit"
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
#pragma link "KXmlInfo"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageParser;
//---------------------------------------------------------------------------
TfrmPaletteImageParserOptions *frmPaletteImageParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmPaletteImageParserOptions::TfrmPaletteImageParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmPaletteImageParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    String Prefix;
    regScorpio->Read("PaletteBasedImages", "Prefix", Prefix);
    int iState = 0;
    if (regScorpio->Read("PaletteBasedImages", "NumberBase", iState))
    {
        switch(iState)
        {
            case 1:
                radZXImageParserHexidecimal->Checked = true;
                break;
            case 2:
                radZXImageParserBinary->Checked = true;
                break;
            case 0:
            default:
                radZXImageParserDecimal->Checked = true;
        }
    }
    if (Prefix.Trim() != "")
    {
        edtNumericalPrefix->Text = Prefix;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmPaletteImageParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteImageParserOptions::radZXImageParserDecimalClick(TObject *Sender)
{
    edtNumericalPrefix->Text = "";
    edtBit7Change(NULL);
    regScorpio->Write("PaletteBasedImages", "NumberBase", 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteImageParserOptions::radZXImageParserHexidecimalClick(TObject *Sender)
{
    edtNumericalPrefix->Text = "$";
    edtBit7Change(NULL);
    regScorpio->Write("PaletteBasedImages", "NumberBase", 1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteImageParserOptions::radZXImageParserBinaryClick(TObject *Sender)
{
    edtNumericalPrefix->Text = "%";
    edtBit7Change(NULL);
    regScorpio->Write("PaletteBasedImages", "NumberBase", 2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteImageParserOptions::edtBit7Change(TObject *Sender)
{
    lblRemapResult->Caption = NumToStr(RemapValue(edtTestValue->Value));
    lblRemapValue->Caption = NumToStr(edtTestValue->Value);
}
//---------------------------------------------------------------------------
unsigned char __fastcall TfrmPaletteImageParserOptions::RemapValue(unsigned char iNum)
{
    unsigned char rv = 0;

    rv |= (iNum & 0x01) << (edtBit0->Value);
    edtBit1->Value >= 1 ? (rv |= (iNum & 0x02) << (edtBit1->Value - 1)) : (rv |= (iNum & 0x02) >> (1 - edtBit1->Value)); 
    edtBit2->Value >= 2 ? (rv |= (iNum & 0x04) << (edtBit2->Value - 2)) : (rv |= (iNum & 0x04) >> (2 - edtBit2->Value));
    edtBit3->Value >= 3 ? (rv |= (iNum & 0x08) << (edtBit3->Value - 3)) : (rv |= (iNum & 0x08) >> (3 - edtBit3->Value));
    edtBit4->Value >= 4 ? (rv |= (iNum & 0x10) << (edtBit4->Value - 4)) : (rv |= (iNum & 0x10) >> (4 - edtBit4->Value));
    edtBit5->Value >= 5 ? (rv |= (iNum & 0x20) << (edtBit5->Value - 5)) : (rv |= (iNum & 0x20) >> (5 - edtBit5->Value));
    edtBit6->Value >= 6 ? (rv |= (iNum & 0x40) << (edtBit6->Value - 6)) : (rv |= (iNum & 0x40) >> (6 - edtBit6->Value));
    edtBit7->Value >= 7 ? (rv |= (iNum & 0x80) << (edtBit7->Value - 7)) : (rv |= (iNum & 0x80) >> (7 - edtBit7->Value));

    return rv;
}
//---------------------------------------------------------------------------
String __fastcall TfrmPaletteImageParserOptions::NumToStr(unsigned char iNum)
{
    String sNum = "";
    String sPrefix = frmPaletteImageParserOptions->edtNumericalPrefix->Text.Trim();
    if (radZXImageParserDecimal->Checked)
    {
        sNum = "   " + IntToStr(iNum);
        sNum = sPrefix + sNum.SubString(sNum.Length() - 2, 3);
    }
    else if (radZXImageParserHexidecimal->Checked)
    {
        sNum = "00" + IntToHex(iNum, 2);
        sNum = sPrefix + sNum.SubString(sNum.Length() - 1, 2);
    }
    else if (radZXImageParserBinary->Checked)
    {
        sNum = sPrefix;
        unsigned char bitmask = 0x80;

        for (int i = 0; i < 8; i++)
        {
            sNum += iNum & bitmask ? "1" : "0";
            bitmask >>= 1;
        }
    }
    return sNum;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteImageParserOptions::chkEnabledRemapClick(TObject *Sender)
{
    edtBit0->Enabled = chkEnabledRemap->Checked;
    edtBit1->Enabled = chkEnabledRemap->Checked;
    edtBit2->Enabled = chkEnabledRemap->Checked;
    edtBit3->Enabled = chkEnabledRemap->Checked;
    edtBit4->Enabled = chkEnabledRemap->Checked;
    edtBit5->Enabled = chkEnabledRemap->Checked;
    edtBit6->Enabled = chkEnabledRemap->Checked;
    edtBit7->Enabled = chkEnabledRemap->Checked;
    lblBit0->Enabled = chkEnabledRemap->Checked;
    lblBit1->Enabled = chkEnabledRemap->Checked;
    lblBit2->Enabled = chkEnabledRemap->Checked;
    lblBit3->Enabled = chkEnabledRemap->Checked;
    lblBit4->Enabled = chkEnabledRemap->Checked;
    lblBit5->Enabled = chkEnabledRemap->Checked;
    lblBit6->Enabled = chkEnabledRemap->Checked;
    lblBit7->Enabled = chkEnabledRemap->Checked;
    edtTestValue->Enabled = chkEnabledRemap->Checked;
    lblResult->Enabled = chkEnabledRemap->Checked;
    lblRemapResult->Enabled = chkEnabledRemap->Checked;
    lblValue->Enabled = chkEnabledRemap->Checked;
    lblRemapValue->Enabled = chkEnabledRemap->Checked;
    lblTestValue->Enabled = chkEnabledRemap->Checked;
    lblRemappingPresets->Enabled = chkEnabledRemap->Checked;
    cmbRemapPreset->Enabled = chkEnabledRemap->Checked;
    spdRemapPresetSave->Enabled = chkEnabledRemap->Checked;
    spdRemapPresetDelete->Enabled = chkEnabledRemap->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteImageParserOptions::edtLabelPrefixChange(TObject *Sender)
{
    lblExample->Caption = edtLabelPrefix->Text + "MyLabel" + edtLabelPostfix->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteImageParserOptions::edtNumericalPrefixChange(TObject *Sender)
{
    regScorpio->Write("PaletteBasedImages", "Prefix", edtNumericalPrefix->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteImageParserOptions::radSourceCodeAsmClick(TObject *Sender)
{
    lblPrefix->Enabled              = radSourceCodeAsm->Checked;
    edtPrefix->Enabled              = radSourceCodeAsm->Checked;
    chkSourceCodeUseLabel->Enabled  = radSourceCodeAsm->Checked;
    lblLabelPrefix->Enabled         = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
    lblLabelPostfix->Enabled        = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
    edtLabelPrefix->Enabled         = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
    edtLabelPostfix->Enabled        = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
    lblExample->Enabled             = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteImageParserOptions::chkPlaceSizeClick(TObject *Sender)
{
    chkConvertX->Enabled = chkPlaceSize->Checked;
    chkConvertY->Enabled = chkPlaceSize->Checked;
    lblSizeOrder->Enabled = chkPlaceSize->Checked;
    radSizeWidthHeight->Enabled = chkPlaceSize->Checked;
    radSizeHeightWidth->Enabled = chkPlaceSize->Checked;
}
//---------------------------------------------------------------------------

