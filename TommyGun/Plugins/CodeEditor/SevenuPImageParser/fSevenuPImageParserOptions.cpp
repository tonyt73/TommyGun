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
TfrmSevenuPImageParserOptions *frmSevenuPImageParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmSevenuPImageParserOptions::TfrmSevenuPImageParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
, m_DataOutputted(doGraphicsAttributes)
, m_Compiler(asmGeneric)
, m_NumberBase(nbHexidecimal)
, m_Interleave(iSprite)
, m_MaskBefore(false)
{
    m_Prefixes[0]  = "";     // decimal
    m_Prefixes[1]  = "0x";   // hexidecimal
    m_Prefixes[2]  = "%";    // binary
    m_Prefixes[3]  = "0";    // octal

    m_Postfixes[0] = "";    // decimal
    m_Postfixes[1] = "";    // hexidecimal
    m_Postfixes[2] = "";    // binary
    m_Postfixes[3] = "";    // octal

    radSourceCodeC->Checked = true;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmSevenuPImageParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmSevenuPImageParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::radSourceCodeAsmClick(TObject *Sender)
{
    lblPrefix->Enabled              = radSourceCodeAsm->Checked;
    edtPrefix->Enabled              = radSourceCodeAsm->Checked;
    chkSourceCodeUseLabel->Enabled  = radSourceCodeAsm->Checked;
    radBinary->Enabled              = radSourceCodeAsm->Checked;
    lblLabelPrefix->Enabled         = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
    lblLabelPostfix->Enabled        = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
    edtLabelPrefix->Enabled         = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
    edtLabelPostfix->Enabled        = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
    lblExample->Enabled             = radSourceCodeAsm->Checked && chkSourceCodeUseLabel->Checked;
    radHexidecimal->Checked        |= radBinary->Checked;
    m_Compiler = asmGeneric;
    if (radSourceCodeC->Checked)
    {
        m_Compiler = cGeneric;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::chkMaskingAttributeMaskClick(TObject *Sender)
{
    chkMaskingAttributeInk->Enabled    = chkMaskingAttributeMask->Checked;
    chkMaskingAttributePaper->Enabled  = chkMaskingAttributeMask->Checked;
    chkMaskingAttributeBright->Enabled = chkMaskingAttributeMask->Checked;
    chkMaskingAttributeFlash->Enabled  = chkMaskingAttributeMask->Checked;

    UpdateAttributeMask();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::chkMaskingAttributeInkClick(TObject *Sender)
{
    UpdateAttributeMask();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::edtNumberBasePrefixChange(TObject *Sender)
{
    m_Prefixes[m_NumberBase] = edtNumberBasePrefix->Text;
    UpdateExample();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::edtNumberBasePostfixChange(TObject *Sender)
{
    m_Postfixes[m_NumberBase] = edtNumberBasePostfix->Text;
    UpdateExample();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::radDataGraphicsAttributesClick(TObject *Sender)
{
    TRadioButton* Button = dynamic_cast<TRadioButton*>(Sender);
    if (Button)
    {
        m_DataOutputted = (eDataOutputted)Button->Tag;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::radDecimalClick(TObject *Sender)
{
    TRadioButton* Button = dynamic_cast<TRadioButton*>(Sender);
    if (Button)
    {
        m_NumberBase = (eNumberBase)Button->Tag;
        edtNumberBasePrefix->Text  = m_Prefixes[m_NumberBase];
        edtNumberBasePostfix->Text = m_Postfixes[m_NumberBase];
        UpdateExample();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::radInterleaveLineClick(TObject *Sender)
{
    TRadioButton* Button = dynamic_cast<TRadioButton*>(Sender);
    if (Button)
    {
        m_Interleave = (eInterleave)Button->Tag;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::radAssemblerGenericClick(TObject *Sender)
{
    TRadioButton* Button = dynamic_cast<TRadioButton*>(Sender);
    if (Button)
    {
        m_Compiler = (eCompiler)Button->Tag;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::lstByteSortPriorityClick(TObject *Sender)
{
    cmdSortListMoveUp->Enabled = lstByteSortPriority->ItemIndex > 0;
    cmdSortListMoveDown->Enabled = lstByteSortPriority->ItemIndex >=0 && lstByteSortPriority->ItemIndex < 4;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::cmdSortListMoveUpClick(TObject *Sender)
{
    int ItemIndex =  lstByteSortPriority->ItemIndex;

    String tmp = lstByteSortPriority->Items->Strings[lstByteSortPriority->ItemIndex];
    lstByteSortPriority->Items->Strings[lstByteSortPriority->ItemIndex] = lstByteSortPriority->Items->Strings[lstByteSortPriority->ItemIndex - 1];
    lstByteSortPriority->Items->Strings[lstByteSortPriority->ItemIndex - 1] = tmp;

    lstByteSortPriority->ItemIndex = ItemIndex - 1;
    lstByteSortPriorityClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::cmdSortListMoveDownClick(TObject *Sender)
{
    int ItemIndex =  lstByteSortPriority->ItemIndex;

    String tmp = lstByteSortPriority->Items->Strings[lstByteSortPriority->ItemIndex];
    lstByteSortPriority->Items->Strings[lstByteSortPriority->ItemIndex] = lstByteSortPriority->Items->Strings[lstByteSortPriority->ItemIndex + 1];
    lstByteSortPriority->Items->Strings[lstByteSortPriority->ItemIndex + 1] = tmp;

    lstByteSortPriority->ItemIndex = ItemIndex + 1;
    lstByteSortPriorityClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::cmdListDefaultClick(TObject *Sender)
{
    lstByteSortPriority->Items->Strings[0] = "X Char";
    lstByteSortPriority->Items->Strings[1] = "Char Line";
    lstByteSortPriority->Items->Strings[2] = "Y Char";
    lstByteSortPriority->Items->Strings[3] = "Mask";
    lstByteSortPriority->Items->Strings[4] = "Frame Number";
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::UpdateExample(void)
{
    String Value;
    switch(m_NumberBase)
    {
        case nbHexidecimal:
            Value = "7B";
            break;
        case nbBinary:
            Value = "1111011";
            break;
        case nbOctal:
            Value = "173";
            break;
        case nbDecimal:
        default:
            Value = "123";
            break;
    }
    lblExampleValue->Caption = edtNumberBasePrefix->Text + Value + edtNumberBasePostfix->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::UpdateAttributeMask(void)
{
    m_AttributeMask = 0;
    m_AttributeMask |= chkMaskingAttributeInk->Checked    ? 0x07 : 0x00;
    m_AttributeMask |= chkMaskingAttributePaper->Checked  ? 0x38 : 0x00;
    m_AttributeMask |= chkMaskingAttributeBright->Checked ? 0x40 : 0x00;
    m_AttributeMask |= chkMaskingAttributeFlash->Checked  ? 0x80 : 0x00;
}
//---------------------------------------------------------------------------
String __fastcall TfrmSevenuPImageParserOptions::GetPrefix(int NumberBase)
{
    return m_Prefixes[NumberBase];
}
//---------------------------------------------------------------------------
String __fastcall TfrmSevenuPImageParserOptions::GetPostfix(int NumberBase)
{
    return m_Postfixes[NumberBase];
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::chkMaskingBeforeGraphicsClick(TObject *Sender)
{
    m_MaskBefore = chkMaskingBeforeGraphics->Checked;
}
//---------------------------------------------------------------------------
String __fastcall TfrmSevenuPImageParserOptions::GetAsmPrefix()
{
    return edtPrefix->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSevenuPImageParserOptions::edtLabelPostfixChange(TObject *Sender)
{
    lblExample->Caption = edtLabelPrefix->Text + "MyLabel" + edtLabelPostfix->Text;
}
//---------------------------------------------------------------------------

