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
#include "fGotoLine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "KSpinEdit"
//---------------------------------------------------------------------------
__fastcall TfrmGotoLine::TfrmGotoLine(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int __fastcall TfrmGotoLine::Execute(void)
{
    int iLine = -1;
    if (mrOk == ShowModal())
    {
        if (!TryStrToInt(edtLineNumber->Text, iLine))
        {
            iLine = -1;
        }
    }
    return iLine;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGotoLine::edtLineNumberChange(TObject *Sender)
{
    int value;
    if (TryStrToInt(edtLineNumber->Text, value))
    {
        edtLineNumber->Color = clWhite;
    }
    else
    {
        edtLineNumber->Color = (TColor)0x007F7FFF;
    }
}
//---------------------------------------------------------------------------


