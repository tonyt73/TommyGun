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
#pragma link "KSpinEdit"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace MapParser;
//---------------------------------------------------------------------------
TfrmMapParserOptions *frmMapParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmMapParserOptions::TfrmMapParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
, m_NumberBase(nbHexidecimal)
, m_Initialized(false)
{
    m_Prefixes[0]  = "";     // decimal
    m_Prefixes[1]  = "0x";   // hexidecimal
    m_Prefixes[2]  = "%";    // binary
    m_Prefixes[3]  = "0";    // octal

    m_Postfixes[0] = "";    // decimal
    m_Postfixes[1] = "";    // hexidecimal
    m_Postfixes[2] = "";    // binary
    m_Postfixes[3] = "";    // octal
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmMapParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    String sValue;
    if (regScorpio->Read("CodeEditor", "PPApp", sValue))
    {
        edtApplication->Text = sValue;
    }
    if (regScorpio->Read("CodeEditor", "PPParam", sValue))
    {
        edtParameters->Text = sValue;
    }
    m_Initialized = true;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmMapParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::edtNumberBasePrefixChange(TObject *Sender)
{
    m_Prefixes[m_NumberBase] = edtNumberBasePrefix->Text;
    UpdateExample();

}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::edtNumberBasePostfixChange(TObject *Sender)
{
    m_Postfixes[m_NumberBase] = edtNumberBasePostfix->Text;
    UpdateExample();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::radDecimalClick(TObject *Sender)
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
void __fastcall TfrmMapParserOptions::UpdateExample(void)
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
String __fastcall TfrmMapParserOptions::GetPrefix(int NumberBase)
{
    return m_Prefixes[NumberBase];
}
//---------------------------------------------------------------------------
String __fastcall TfrmMapParserOptions::GetPostfix(int NumberBase)
{
    return m_Postfixes[NumberBase];
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::radUseCoordIndexClick(TObject *Sender)
{
    chkConvertX->Enabled            = radUseCoordIndex->Checked;
    chkConvertY->Enabled            = radUseCoordIndex->Checked;
    chkOverrideTileSize->Enabled    = radUseIndexOnly->Checked;
    lblTileWidth->Enabled           = radUseIndexOnly->Checked && chkOverrideTileSize->Checked;
    lblTileHeight->Enabled          = radUseIndexOnly->Checked && chkOverrideTileSize->Checked;
    edtTileWidth->Enabled           = radUseIndexOnly->Checked && chkOverrideTileSize->Checked;
    edtTileHeight->Enabled          = radUseIndexOnly->Checked && chkOverrideTileSize->Checked;
    lblDefaultTileIndex->Enabled    = radUseIndexOnly->Checked;
    edtDefaultTileIndex->Enabled    = radUseIndexOnly->Checked;
    lblDefaultMessage->Enabled      = radUseIndexOnly->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::chkUsePostProcessorClick(TObject *Sender)
{
    lblApplication->Enabled         = chkUsePostProcessor->Checked;
    edtApplication->Enabled         = chkUsePostProcessor->Checked;
    cmdApplication->Enabled         = chkUsePostProcessor->Checked;
    lblParameters->Enabled          = chkUsePostProcessor->Checked;
    edtParameters->Enabled          = chkUsePostProcessor->Checked;
    radConvertToSourceCode->Enabled = chkUsePostProcessor->Checked;
    lblConvertToSourceCode->Enabled = chkUsePostProcessor->Checked;
    radUseOutputBinary->Enabled     = chkUsePostProcessor->Checked;
    lblUseOutputBinary->Enabled     = chkUsePostProcessor->Checked;
    radLittleEndian->Enabled        = chkUsePostProcessor->Checked;
    radBigEndian->Enabled           = chkUsePostProcessor->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::cmdApplicationClick(TObject *Sender)
{
    if (dlgBrowse->Execute())
    {
        edtApplication->Text = dlgBrowse->FileName;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::edtApplicationChange(TObject *Sender)
{
    if (m_Initialized)
    {
        regScorpio->Write("CodeEditor", "PPApp", edtApplication->Text);
        regScorpio->Write("CodeEditor", "PPParam", edtParameters->Text);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::lstTileTableFormatChange(TObject *Sender, TListItem *Item, TItemChange Change)
{
    bool bHasSelection = lstTileTableFormat->ItemIndex != -1;
    bool bHasMultiple  = lstTileTableFormat->Items->Count > 1;
    bool bIsImagePtr   = lstTileTableFormat->Selected ? lstTileTableFormat->Selected->ImageIndex == 0 : false;
    cmdTilesTableFormatUp->Enabled = bHasSelection && bHasMultiple && lstTileTableFormat->ItemIndex > 0;
    cmdTilesTableFormatDown->Enabled = bHasSelection && bHasMultiple && lstTileTableFormat->ItemIndex < lstTileTableFormat->Items->Count - 1;
    cmdTilesTableFormatRemove->Enabled = bHasSelection && !bIsImagePtr;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::lstItemsAvailableChange(TObject *Sender, TListItem *Item, TItemChange Change)
{
    bool bHasSelection = lstItemsAvailable->ItemIndex != -1;
    cmdTilesTableFormatAdd->Enabled = bHasSelection;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::cmdTilesTableFormatAddClick(TObject *Sender)
{
    if (cmdTilesTableFormatAdd->Enabled)
    {
        TListItem* NewItem = lstTileTableFormat->Items->Add();
        NewItem->Assign(lstItemsAvailable->Selected);
        lstTileTableFormat->Selected = NewItem;
        lstItemsAvailable->Items->Delete(lstItemsAvailable->ItemIndex);
        lstItemsAvailable->ItemIndex = -1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::cmdTilesTableFormatRemoveClick(TObject *Sender)
{
    if (cmdTilesTableFormatRemove->Enabled)
    {
        TListItem* NewItem = lstItemsAvailable->Items->Add();
        NewItem->Assign(lstTileTableFormat->Selected);
        lstItemsAvailable->Selected = NewItem;
        lstTileTableFormat->Items->Delete(lstTileTableFormat->ItemIndex);
        lstTileTableFormat->ItemIndex = -1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::cmdTilesTableFormatUpClick(TObject *Sender)
{
    if (cmdTilesTableFormatUp->Enabled)
    {
        TListItem* NewItem = lstTileTableFormat->Items->Insert(lstTileTableFormat->ItemIndex - 1);
        NewItem->Assign(lstTileTableFormat->Selected);
        lstTileTableFormat->Items->Delete(lstTileTableFormat->ItemIndex);
        lstTileTableFormat->Update();
        lstTileTableFormat->ItemIndex = lstTileTableFormat->Items->IndexOf(NewItem);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapParserOptions::cmdTilesTableFormatDownClick(TObject *Sender)
{
    if (cmdTilesTableFormatDown->Enabled)
    {
        TListItem* NewItem = lstTileTableFormat->Items->Insert(lstTileTableFormat->ItemIndex + 2);
        NewItem->Assign(lstTileTableFormat->Selected);
        lstTileTableFormat->Items->Delete(lstTileTableFormat->ItemIndex);
        lstTileTableFormat->ItemIndex = lstTileTableFormat->Items->IndexOf(NewItem);
    }
}
//---------------------------------------------------------------------------

