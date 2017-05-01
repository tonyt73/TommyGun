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
//- CONSTANTS ---------------------------------------------------------------
const int   g_iNotFound = -1;
//---------------------------------------------------------------------------
__fastcall TZXObjectBrowser::TZXObjectBrowser()
: m_ListView(NULL)
{
}
//---------------------------------------------------------------------------
__fastcall TZXObjectBrowser::~TZXObjectBrowser()
{
    m_ListView = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TZXObjectBrowser::Setup(TListView* ListView, TStatusBar* stsStatus, ZXObjectManager* ObjectManager)
{
    m_ListView      = ListView;
    m_StatusBar     = stsStatus;
    m_ObjectManager = ObjectManager;
}
//---------------------------------------------------------------------------
void __fastcall TZXObjectBrowser::Clear(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TZXObjectBrowser::Refresh(void)
{
    m_ObjectManager->Refresh();
    // fill the list view
    int objects = m_ObjectManager->Objects();
	bool keepSelections = objects == m_ListView->Items->Count;
    std::vector<int> selections;
    if (keepSelections)
    {
        for (int i = 0; i < m_ListView->Items->Count; ++i)
        {
            if (m_ListView->Items->Item[i]->Selected)
            {
                selections.push_back(i);
            }
        }
    }
    m_ListView->Clear();
    TListItem* item = NULL;
    for (int i = 0; i < objects; ++i)
    {
        TMapObject object;
        m_ObjectManager->GetObject(i, object);
        item = m_ListView->Items->Add();
        item->ImageIndex = i;
        item->Caption = object.m_sObject;
        item->SubItems->Add(IntToStr(object.m_iScreen));
        item->SubItems->Add(IntToStr(object.m_iLeft));
        item->SubItems->Add(IntToStr(object.m_iTop));
    }
    if (keepSelections)
    {
        for (unsigned int i = 0; i < selections.size(); ++i)
        {
            m_ListView->Items->Item[selections[i]]->Selected = true;
        }
    }
}
//---------------------------------------------------------------------------


