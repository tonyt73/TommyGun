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
TfrmConfirmReplace *frmConfirmReplace = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmConfirmReplace::TfrmConfirmReplace(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TfrmConfirmReplace::Execute(TRect AEditorRect, int X, int Y1, int Y2, const String& AReplaceText)
{
    lblConfirmation->Caption = "Replace this occurence of " + AReplaceText;
    int nW = AEditorRect.Right  - AEditorRect.Left;
    int nH = AEditorRect.Bottom - AEditorRect.Top;

    if (nW <= Width)
    {
        X = AEditorRect.Left - (Width - nW) << 1;
    }
    else
    {
        if (X + Width > AEditorRect.Right)
        {
            X = AEditorRect.Right - Width;
        }
    }
    if (Y2 > AEditorRect.Top + MulDiv(nH, 2, 3))
    {
        Y2 = Y1 - Height - 4;
    }
    else
    {
        Y2 += 4;
    }
    SetBounds(X, Y2, Width, Height);
    ShowModal();
    return mrCancel != ModalResult;
}
//---------------------------------------------------------------------------
