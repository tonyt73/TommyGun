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
#include "ZXPluginManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXUndoItem::ZXUndoItem(const KXmlInfo& xmlInfo)
{
    m_XmlInfo = xmlInfo;
}
//---------------------------------------------------------------------------
__fastcall ZXUndoItem::ZXUndoItem(const ZXUndoItem& undoItem)
{
    m_XmlInfo = undoItem.m_XmlInfo;
}
//---------------------------------------------------------------------------
String  __fastcall ZXUndoItem::GetDescription(void)
{
    String sDescription = "Unknown";
    KXmlInfo* pNode = m_XmlInfo.GetNode("Description", 0);
    if (true == SAFE_PTR(pNode))
    {
        sDescription = pNode->GetText();
    }
    return sDescription;
}
//---------------------------------------------------------------------------
String  __fastcall ZXUndoItem::GetPlugin(void)
{
    String sPlugin = "Unknown";
    KXmlInfo* pNode = m_XmlInfo.GetNode("Plugin", 0);
    if (true == SAFE_PTR(pNode))
    {
        sPlugin = pNode->GetText();
    }
    return sPlugin;
}
//---------------------------------------------------------------------------
int __fastcall ZXUndoItem::GetSize(void)
{
    try
    {
        return m_XmlInfo.GetXmlString().Length() + sizeof(this) + sizeof(m_XmlInfo);
    }
    catch(...)
    {
        return 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoItem::Restore(void)
{
    // post item restore operation
    g_PluginManager.Notify(NULL, TZXN_XML_UNDO_RESTORE, (LPDATA)&m_XmlInfo, 0, 0);
}
//---------------------------------------------------------------------------

