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
TdlgCommodoreColors *dlgCommodoreColors;
//---------------------------------------------------------------------------
__fastcall TdlgCommodoreColors::TdlgCommodoreColors(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TdlgCommodoreColors::Execute(int iColor, bool bShowAllColors)
{
    for (int i = 0; i < ControlCount; i++)
    {
        TPanel* Panel = dynamic_cast<TPanel*>(Controls[i]);
        if (true == SAFE_PTR(Panel) && 0 < Panel->Tag)
        {
            Panel->BevelOuter = Panel->Tag == iColor ? bvLowered : bvRaised;
            Panel->Visible    = Panel->Tag < 8 || bShowAllColors;
        }
    }
    ShowModal();
    return ModalResult == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TdlgCommodoreColors::panC64BlackClick(TObject *Sender)
{
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    if (true == SAFE_PTR(Panel))
    {
        m_Color = Panel->Tag;
        for (int i = 0; i < ControlCount; i++)
        {
            TPanel* Panel = dynamic_cast<TPanel*>(Controls[i]);
            if (true == SAFE_PTR(Panel) && 0 <= Panel->Tag)
            {
                Panel->BevelOuter = (Panel == Sender) ? bvLowered : bvRaised;
            }
        }
    }
}
//---------------------------------------------------------------------------



