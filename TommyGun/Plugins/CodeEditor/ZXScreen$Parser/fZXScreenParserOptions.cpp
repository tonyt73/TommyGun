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
using namespace ScreenParser;
//---------------------------------------------------------------------------
TfrmZXScreenParserOptions *frmZXScreenParserOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmZXScreenParserOptions::TfrmZXScreenParserOptions(TComponent* Owner)
: TForm(Owner)
, m_pPlugin(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXScreenParserOptions::Initialize(ZXPlugin* pPlugin)
{
    RL_HRESULT(S_OK);
    m_pPlugin = pPlugin;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmZXScreenParserOptions::Release(void)
{
    RL_HRESULT(S_OK);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXScreenParserOptions::radZXScreenParserOrgDefaultClick(TObject *Sender)
{
    TRadioButton* Button = dynamic_cast<TRadioButton*>(Sender);
    if (true == SAFE_PTR(Button))
    {
        edtZXScreenParserOrgValue->Enabled = Button->Tag == 3;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmZXScreenParserOptions::edtZXScreenParserOrgValueKeyPress(TObject *Sender, char &Key)
{
    if ((Key < '0' || Key > '9') && Key != 'x' && Key != 'X' && Key != '\b')
    {
        Key = '\0';
    }
}
//---------------------------------------------------------------------------


