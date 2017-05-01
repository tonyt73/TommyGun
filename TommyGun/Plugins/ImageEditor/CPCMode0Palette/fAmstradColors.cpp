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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TdlgAmstradColors *dlgAmstradColors;
//---------------------------------------------------------------------------
__fastcall TdlgAmstradColors::TdlgAmstradColors(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TdlgAmstradColors::Execute(int iColor)
{
    for (int i = 0; i < ControlCount; i++)
    {
        TPanel* Panel = dynamic_cast<TPanel*>(Controls[i]);
        if (true == SAFE_PTR(Panel) && 0 < Panel->Tag)
        {
            Panel->BevelOuter = /*Panel->Tag == iColor + 1 ? bvLowered :*/ bvRaised;
        }
    }
    ShowModal();
    return ModalResult == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TdlgAmstradColors::panC64BlackClick(TObject *Sender)
{
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    if (true == SAFE_PTR(Panel))
    {
        m_Color = Panel->Color;
        for (int i = 0; i < ComponentCount; i++)
        {
            TPanel* Panel = dynamic_cast<TPanel*>(Components[i]);
            if (true == SAFE_PTR(Panel) && 0 < Panel->Tag)
            {
                Panel->BevelOuter = (Panel == Sender) ? bvLowered : bvRaised;
            }
        }
    }
}
//---------------------------------------------------------------------------

