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
TfrmZXImageParserOptions *frmZXImageParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmZXImageParserOptions::TfrmZXImageParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXImageParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    radZXImageParserPixelsRowColumnClick(NULL);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXImageParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageParserOptions::radZXImageParserPixelsRowColumnClick(TObject *Sender)
{
    chkConvertX->Enabled = chkPlaceSize->Checked;
    chkConvertY->Enabled = chkPlaceSize->Checked;

    radZXImageParserMaskBefore->Enabled = radZXImageParserMaskBytePairs->Checked;
    radZXImageParserMaskAfter->Enabled = radZXImageParserMaskBytePairs->Checked;

    radZXImageParserAttributesEnd->Enabled = chkUseAttributes->Checked;
    radZXImageParserAttributesInterleaved->Enabled = chkUseAttributes->Checked;
    
    // update the preview window
    rdtZXImageParserPreview->Lines->Clear();
    if (radZXImageParserPixelsRowColumn->Checked)
    {
        radZXImageParserAttributesEnd->Checked = true;
        radZXImageParserAttributesInterleaved->Enabled = false;
        radZXImageParserRowOrderClassic->Enabled = true;
        radZXImageParserRowOrderZigZag->Enabled = true;
        /*if (radZXImageParserRowOrderClassic->Checked)
        {
            Preview1();
        }
        else
        {
            Preview4();
        }*/
    }
    else
    {
        radZXImageParserAttributesInterleaved->Enabled = true;
        radZXImageParserRowOrderClassic->Enabled = false;
        radZXImageParserRowOrderZigZag->Enabled = false;

        /*if (radZXImageParserAttributesEnd->Checked)
        {
            Preview2();
        }
        else
        {
            Preview3();
        }*/
    }
    // move the cursor to the top of the memobox
    rdtZXImageParserPreview->CaretPos = TPoint(0, 1);
    rdtZXImageParserPreview->SelStart = 0;
    rdtZXImageParserPreview->SelLength = 1;
    rdtZXImageParserPreview->SelText = rdtZXImageParserPreview->SelText; 
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageParserOptions::Preview1(void)
{
/*
    // preview Pixels Row/Column - Attributes At End
    AddText("ImageABCD:", clWhite, true, false);
    if (chkPlaceSize->Checked)
    {
        AddText("defb {width}, {height}", clWhite, true, true);
    }
    AddText("; pixels", clFuchsia, true, true);
    // row 0
    AddText("defb 00000000, 00000000", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 1
    AddText("defb 00111100, 01111100", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 2
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 3
    AddText("defb 01111110, 01111100", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 4
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 5
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 6
    AddText("defb 01000010, 01111100", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 7
    AddText("defb 00000000, 00000000", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);

    // row 8
    AddText("defb 00000000, 00000000", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 9
    AddText("defb 00111100, 01111100", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 10
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 11
    AddText("defb 01000000, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 12
    AddText("defb 01000000, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 13
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 14
    AddText("defb 00111100, 01111100", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 15
    AddText("defb 00000000, 00000000", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);

    if (chkUseAttributes->Checked)
    {
        // attributes
        AddText("; attributes", clFuchsia, true, true);
        AddText("defb 00010000, 00110000", clWhite, false, false);
        SetAttr( 5, 8, clRed);
        SetAttr(15, 8, clYellow);
        AddText("defb 00100000, 00101000", clWhite, false, false);
        SetAttr( 5, 8, clLime);
        SetAttr(15, 8, clAqua);
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageParserOptions::Preview2(void)
{
/*
    // preview Character Blocks by Row/Column - Attributes At End
    AddText("ImageABCD:", clWhite, true, false);
    if (chkPlaceSize->Checked)
    {
        AddText("defb {width}, {height}", clWhite, true, true);
    }
    AddText("; A pixels", clFuchsia, true, true);
    // row 0
    AddText("defb 00000000, 00111100, 01000010, ...", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clRed);
    SetAttr(25, 8, clRed);
    SetAttr(35, 3, clRed);

    // row 0
    AddText("; B pixels", clFuchsia, true, true);
    AddText("defb 00000000, 01111100, 01000010, ...", clWhite, false, false);
    SetAttr( 5, 8, clYellow);
    SetAttr(15, 8, clYellow);
    SetAttr(25, 8, clYellow);
    SetAttr(35, 3, clYellow);

    // row 8
    AddText("; C pixels", clFuchsia, true, true);
    AddText("defb 00000000, 00111100, 01000010, ...", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clLime);
    SetAttr(25, 8, clLime);
    SetAttr(35, 3, clLime);

    // row 8
    AddText("; D pixels", clFuchsia, true, true);
    AddText("defb 00000000, 01111100, 01000010, ...", clWhite, false, false);
    SetAttr( 5, 8, clAqua);
    SetAttr(15, 8, clAqua);
    SetAttr(25, 8, clAqua);
    SetAttr(35, 3, clAqua);

    if (chkUseAttributes->Checked)
    {
        // attributes
        AddText("; attributes", clFuchsia, true, true);
        AddText("defb 00010000, 00110000", clWhite, false, false);
        SetAttr( 5, 8, clRed);
        SetAttr(15, 8, clYellow);
        AddText("defb 00100000, 00101000", clWhite, false, false);
        SetAttr( 5, 8, clLime);
        SetAttr(15, 8, clAqua);
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageParserOptions::Preview3(void)
{
/*
    // preview Character Blocks by Row/Column - Attributes Interleaved
    AddText("ImageABCD:", clWhite, true, false);
    if (chkPlaceSize->Checked)
    {
        AddText("defb {width}, {height}", clWhite, true, true);
    }
    AddText("; A pixels", clFuchsia, true, true);
    // row 0
    AddText("defb 00000000, 00111100, 01000010, ...", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clRed);
    SetAttr(25, 8, clRed);
    if (chkUseAttributes->Checked)
    {
        AddText("; A attribute", clFuchsia, true, true);
        AddText("defb 00010000", clWhite, false, false);
        SetAttr( 5, 8, clRed);
    }

    // row 0
    AddText("; B pixels", clFuchsia, true, true);
    AddText("defb 00000000, 01111100, 01000010, ...", clWhite, false, false);
    SetAttr( 5, 8, clYellow);
    SetAttr(15, 8, clYellow);
    SetAttr(25, 8, clYellow);
    if (chkUseAttributes->Checked)
    {
        AddText("; B attribute", clFuchsia, true, true);
        AddText("defb 00110000", clWhite, false, false);
        SetAttr( 5, 8, clYellow);
    }

    // row 8
    AddText("; C pixels", clFuchsia, true, true);
    AddText("defb 00000000, 00111100, 01000010, ...", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clLime);
    SetAttr(25, 8, clLime);
    if (chkUseAttributes->Checked)
    {
        AddText("; C attribute", clFuchsia, true, true);
        AddText("defb 00100000", clWhite, false, false);
        SetAttr( 5, 8, clLime);
    }

    // row 8
    AddText("; D pixels", clFuchsia, true, true);
    AddText("defb 00000000, 01111100, 01000010, ...", clWhite, false, false);
    SetAttr( 5, 8, clAqua);
    SetAttr(15, 8, clAqua);
    SetAttr(25, 8, clAqua);
    if (chkUseAttributes->Checked)
    {
        AddText("; D attribute", clFuchsia, true, true);
        AddText("defb 00101000", clWhite, false, false);
        SetAttr(5, 8, clAqua);
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageParserOptions::Preview4(void)
{
/*
    // preview Pixels Row/Column - Attributes At End
    AddText("ImageABCD:", clWhite, true, false);
    if (chkPlaceSize->Checked)
    {
        AddText("defb {width}, {height}", clWhite, true, true);
    }
    AddText("; pixels", clFuchsia, true, true);
    // row 0
    AddText("defb 00000000, 00000000", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 1
    AddText("defb 01111100, 00111100", clWhite, false, false);
    SetAttr( 5, 8, clYellow);
    SetAttr(15, 8, clRed);
    // row 2
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 3
    AddText("defb 01111100, 01111110", clWhite, false, false);
    SetAttr( 5, 8, clYellow);
    SetAttr(15, 8, clRed);
    // row 4
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 5
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clYellow);
    SetAttr(15, 8, clRed);
    // row 6
    AddText("defb 01000010, 01111100", clWhite, false, false);
    SetAttr( 5, 8, clRed);
    SetAttr(15, 8, clYellow);
    // row 7
    AddText("defb 00000000, 00000000", clWhite, false, false);
    SetAttr( 5, 8, clYellow);
    SetAttr(15, 8, clRed);

    // row 8
    AddText("defb 00000000, 00000000", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 9
    AddText("defb 01111100, 00111100", clWhite, false, false);
    SetAttr( 5, 8, clAqua);
    SetAttr(15, 8, clLime);
    // row 10
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 11
    AddText("defb 01000010, 01000000", clWhite, false, false);
    SetAttr( 5, 8, clAqua);
    SetAttr(15, 8, clLime);
    // row 12
    AddText("defb 01000000, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 13
    AddText("defb 01000010, 01000010", clWhite, false, false);
    SetAttr( 5, 8, clAqua);
    SetAttr(15, 8, clLime);
    // row 14
    AddText("defb 00111100, 01111100", clWhite, false, false);
    SetAttr( 5, 8, clLime);
    SetAttr(15, 8, clAqua);
    // row 15
    AddText("defb 00000000, 00000000", clWhite, false, false);
    SetAttr( 5, 8, clAqua);
    SetAttr(15, 8, clLime);

    if (chkUseAttributes->Checked)
    {
        // attributes
        AddText("; attributes", clFuchsia, true, true);
        AddText("defb 00010000, 00110000", clWhite, false, false);
        SetAttr( 5, 8, clRed);
        SetAttr(15, 8, clYellow);
        AddText("defb 00100000, 00101000", clWhite, false, false);
        SetAttr( 5, 8, clLime);
        SetAttr(15, 8, clAqua);
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageParserOptions::AddText(String sText, TColor cColor, bool bBold, bool bItalic)
{
/*
    rdtZXImageParserPreview->CaretPos = TPoint(65536, rdtZXImageParserPreview->CaretPos.y - 1);
    rdtZXImageParserPreview->SelAttributes->Color = cColor;

    if (bBold)
        rdtZXImageParserPreview->SelAttributes->Style = rdtZXImageParserPreview->SelAttributes->Style << fsBold;
    else
        rdtZXImageParserPreview->SelAttributes->Style = rdtZXImageParserPreview->SelAttributes->Style >> fsBold;

    if (bItalic)
        rdtZXImageParserPreview->SelAttributes->Style = rdtZXImageParserPreview->SelAttributes->Style << fsItalic;
    else
        rdtZXImageParserPreview->SelAttributes->Style = rdtZXImageParserPreview->SelAttributes->Style >> fsItalic;

    m_iCharacters = rdtZXImageParserPreview->Text.Length();
    rdtZXImageParserPreview->Lines->Add(sText);
*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageParserOptions::SetAttr(int iStart, int iLen, TColor cColor)
{
/*
    rdtZXImageParserPreview->CaretPos = TPoint(0, rdtZXImageParserPreview->CaretPos.y - 1);
    rdtZXImageParserPreview->SelStart = m_iCharacters + iStart;
    rdtZXImageParserPreview->SelLength = iLen;
    rdtZXImageParserPreview->SelAttributes->Color = cColor;
    rdtZXImageParserPreview->CaretPos = TPoint(0, rdtZXImageParserPreview->CaretPos.y);
*/
}
//---------------------------------------------------------------------------

