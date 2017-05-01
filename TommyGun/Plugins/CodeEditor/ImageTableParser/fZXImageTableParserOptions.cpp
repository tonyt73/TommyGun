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
using namespace ImageTableParser;
//---------------------------------------------------------------------------
TfrmZXImageTableParserOptions *frmZXImageTableParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmZXImageTableParserOptions::TfrmZXImageTableParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXImageTableParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    chkTableAddNumberClick(NULL);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXImageTableParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageTableParserOptions::chkTableAddNumberClick(TObject *Sender)
{
    // update the preview window
    rdtZXImageTableParserPreview->Lines->Clear();
    Preview();
    // move the cursor to the top of the memobox
    rdtZXImageTableParserPreview->CaretPos = TPoint(0, 1);
    rdtZXImageTableParserPreview->SelStart = 0;
    rdtZXImageTableParserPreview->SelLength = 1;
    rdtZXImageTableParserPreview->SelText = rdtZXImageTableParserPreview->SelText;
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageTableParserOptions::Preview(void)
{
    // preview Pixels Row/Column - Attributes At End
    AddText(";", clLime, false, true);
    AddText("; Images Table", clLime, false, true);
    AddText(";", clLime, false, true);
    String sTableName = edtTableName->Text.Trim() != "" ? edtTableName->Text.Trim() : String("{ImageType}Table");
    AddText(sTableName + ":", clWhite, true, false);
    if (chkTableAddNumber->Checked)
    {
        AddText("defb {n}   ; number of images", clLime, false, false);
        SetAttr( 0, 4, clAqua);
        SetAttr( 5, 4, clWhite);
    }
    AddText("defw Image1", clWhite, false, false);
    SetAttr( 0, 4, clAqua);
    AddText("defw Image1", clWhite, false, false);
    SetAttr( 0, 4, clAqua);
    AddText("defw ...", clWhite, false, false);
    SetAttr( 0, 4, clAqua);
    AddText("; end of table", clLime, false, true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageTableParserOptions::AddText(String sText, TColor cColor, bool bBold, bool bItalic)
{
    rdtZXImageTableParserPreview->CaretPos = TPoint(65536, rdtZXImageTableParserPreview->CaretPos.y - 1);
    rdtZXImageTableParserPreview->SelAttributes->Color = cColor;

    if (bBold)
        rdtZXImageTableParserPreview->SelAttributes->Style = rdtZXImageTableParserPreview->SelAttributes->Style << fsBold;
    else
        rdtZXImageTableParserPreview->SelAttributes->Style = rdtZXImageTableParserPreview->SelAttributes->Style >> fsBold;

    if (bItalic)
        rdtZXImageTableParserPreview->SelAttributes->Style = rdtZXImageTableParserPreview->SelAttributes->Style << fsItalic;
    else
        rdtZXImageTableParserPreview->SelAttributes->Style = rdtZXImageTableParserPreview->SelAttributes->Style >> fsItalic;

    m_iCharacters = rdtZXImageTableParserPreview->Text.Length();
    rdtZXImageTableParserPreview->Lines->Add(sText);
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXImageTableParserOptions::SetAttr(int iStart, int iLen, TColor cColor)
{
    rdtZXImageTableParserPreview->CaretPos = TPoint(0, rdtZXImageTableParserPreview->CaretPos.y - 1);
    rdtZXImageTableParserPreview->SelStart = m_iCharacters + iStart;
    rdtZXImageTableParserPreview->SelLength = iLen;
    rdtZXImageTableParserPreview->SelAttributes->Color = cColor;
    rdtZXImageTableParserPreview->CaretPos = TPoint(0, rdtZXImageTableParserPreview->CaretPos.y);
}
//---------------------------------------------------------------------------

