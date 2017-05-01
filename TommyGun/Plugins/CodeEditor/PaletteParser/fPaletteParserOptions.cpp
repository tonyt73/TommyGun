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
using namespace PaletteParser;
//---------------------------------------------------------------------------
TfrmPaletteParserOptions *frmPaletteParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmPaletteParserOptions::TfrmPaletteParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmPaletteParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    String Prefix;
    regScorpio->Read("PaletteParser", "Prefix", Prefix);
    int iState = 0;
    if (regScorpio->Read("PaletteParser", "NumberBase", iState))
    {
        switch(iState)
        {
            case 1:
                radZXPaletteParserHexidecimal->Checked = true;
                break;
            case 2:
                radZXPaletteParserBinary->Checked = true;
                break;
            case 0:
            default:
                radZXPaletteParserDecimal->Checked = true;
        }
    }
    if (Prefix.Trim() != "")
    {
        edtNumericalPrefix->Text = Prefix;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmPaletteParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteParserOptions::radZXPaletteParserDecimalClick(TObject *Sender)
{
    edtNumericalPrefix->Text = "";
    regScorpio->Write("PaletteParser", "NumberBase", 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteParserOptions::radZXPaletteParserHexidecimalClick(TObject *Sender)
{
    edtNumericalPrefix->Text = "$";
    regScorpio->Write("PaletteParser", "NumberBase", 1);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteParserOptions::radZXPaletteParserBinaryClick(TObject *Sender)
{
    edtNumericalPrefix->Text = "%";
    regScorpio->Write("PaletteParser", "NumberBase", 2);
}
//---------------------------------------------------------------------------
String __fastcall TfrmPaletteParserOptions::NumToStr(unsigned char iNum)
{
    String sNum = "";
    String sPrefix = frmPaletteParserOptions->edtNumericalPrefix->Text.Trim();
    if (radZXPaletteParserDecimal->Checked)
    {
        sNum = "   " + IntToStr(iNum);
        sNum = sPrefix + sNum.SubString(sNum.Length() - 2, 3);
    }
    else if (radZXPaletteParserHexidecimal->Checked)
    {
        sNum = "00" + IntToHex(iNum, 2);
        sNum = sPrefix + sNum.SubString(sNum.Length() - 1, 2);
    }
    else if (radZXPaletteParserBinary->Checked)
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
void __fastcall TfrmPaletteParserOptions::edtLabelPrefixChange(TObject *Sender)
{
    lblExample->Caption = edtLabelPrefix->Text + "MyLabel" + edtLabelPostfix->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteParserOptions::edtNumericalPrefixChange(TObject *Sender)
{
    regScorpio->Write("PaletteParser", "Prefix", edtNumericalPrefix->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteParserOptions::radSourceCodeAsmClick(TObject *Sender)
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

