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
//---------------------------------------------------------------------------
__fastcall ZXTableManager::ZXTableManager()
: m_bDirty(false)
{
}
//---------------------------------------------------------------------------
__fastcall ZXTableManager::~ZXTableManager()
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXTableManager::Load(KXmlInfo* xmlInfo)
{
    KXmlInfo* EditorNode;
    if (xmlInfo->Find(EditorNode, "StringEditor"))
    {
        KXmlInfo* TablesNode = EditorNode->GetNode("Tables");
        if (true == SAFE_PTR(TablesNode))
        {
            Clear();
            // loop through the tables and load the applicable data
            for (KXmlNodes::iterator it = TablesNode->begin(); it != TablesNode->end(); it++)
            {
                KXmlInfo* pName = (*it)->GetNode("Name");
                if (SAFE_PTR(pName))
                {
                    int iTable = AddTable(pName->GetText());
                    for (KXmlNodes::iterator itT = (*it)->begin(); itT != (*it)->end(); itT++)
                    {
                        if ((*itT)->GetName() == "String")
                        {
                            KXmlInfo* pID = (*itT)->GetNode("ID");
                            KXmlInfo* pValue = (*itT)->GetNode("Value");
                            if (SAFE_PTR(pID) && SAFE_PTR(pValue))
                            {
                                AddString(iTable, pID->GetText(), pValue->GetText());
                            }
                        }
                    }
                }
            }
        }
    }
    m_bDirty = false;
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall ZXTableManager::Save(KXmlInfo* xmlInfo)
{
    KXmlInfo* EditorNode;
    if (xmlInfo->Find(EditorNode, "StringEditor"))
    {
        xmlInfo->Remove(EditorNode);
    }

    if (m_Tables.size())
    {
        KXmlInfo StringEditor("StringEditor");
        // create a palette node
        KXmlInfo Tables("Tables");
        for (int i = 0; i < (int)m_Tables.size(); i++)
        {
            KXmlInfo Table;
            Table.Reset();
            Table.SetName("Table");
            Table.Add("Name", m_Tables[i].sName);

            for (unsigned int j = 0; j < m_Tables[i].Strings.size(); j++)
            {
                KXmlInfo Entry;
                Entry.Reset();
                Entry.SetName("String");
                Entry.Add("ID", m_Tables[i].IDs[j]);
                Entry.Add("Value", m_Tables[i].Strings[j]);

                Table.Add(Entry);
            }
            Tables.Add(Table);
        }
        StringEditor.Add(Tables);
        xmlInfo->Add(StringEditor);
    }
    m_bDirty = false;
    return true;
}
//---------------------------------------------------------------------------
void __fastcall ZXTableManager::Clear(void)
{
    m_Tables.clear();
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::GetTableCount(void)
{
    return m_Tables.size();
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::Strings(unsigned int iTableIndex)
{
    int iStrings = 0;
    if (iTableIndex < m_Tables.size())
    {
        iStrings = m_Tables[iTableIndex].Strings.size();
    }
    return iStrings;
}
//---------------------------------------------------------------------------
String __fastcall ZXTableManager::GetName(unsigned int iTableIndex)
{
    String sName;
    if (iTableIndex < m_Tables.size())
    {
        sName = m_Tables[iTableIndex].sName;
    }
    return sName;
}
//---------------------------------------------------------------------------
String __fastcall ZXTableManager::GetString(unsigned int iTableIndex, unsigned int iStringIndex)
{
    String sString;
    if (iTableIndex < m_Tables.size())
    {
        if (iStringIndex < m_Tables[iTableIndex].Strings.size())
        {
            sString = m_Tables[iTableIndex].Strings[iStringIndex];
        }
    }
    return sString;
}
//---------------------------------------------------------------------------
String __fastcall ZXTableManager::GetID(unsigned int iTableIndex, unsigned int iStringIndex)
{
    String sID;
    if (iTableIndex < m_Tables.size())
    {
        if (iStringIndex < m_Tables[iTableIndex].Strings.size())
        {
            sID = m_Tables[iTableIndex].IDs[iStringIndex];
        }
    }
    return sID;
}
//---------------------------------------------------------------------------
bool __fastcall ZXTableManager::TableExists(const String& sName)
{
    return FindTable(sName) != -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::AddTable(const String& sName)
{
    int table = FindTable(sName);
    if (table == -1)
    {
        ZXStringTable Table;
        Table.sName = sName;
        m_Tables.push_back(Table);
        m_bDirty = true;
        table = m_Tables.size() - 1;
    }
    return table;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::RemoveTable(const String& sName)
{
    int iTableIndex = FindTable(sName);
    if (iTableIndex != -1)
    {
        m_Tables.erase(m_Tables.begin() + iTableIndex);
        m_bDirty = true;
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::CloneTable(unsigned int iTableIndex, const String& sName)
{
    if (iTableIndex < m_Tables.size())
    {
        int iIndex = AddTable(sName);
        for (unsigned int i = 0; i < m_Tables[iTableIndex].Strings.size(); i++)
        {
            AddString(iIndex, m_Tables[iTableIndex].IDs[i], m_Tables[iTableIndex].Strings[i]);
        }
        m_bDirty = true;
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::RenameTable(unsigned int iTableIndex, const String& sName)
{
    if (iTableIndex < m_Tables.size())
    {
        m_Tables[iTableIndex].sName = sName;
        m_bDirty = true;
        return iTableIndex;
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::UpTable(unsigned int iTableIndex)
{
    if (iTableIndex < m_Tables.size())
    {
        ZXStringTable sCurr = m_Tables[iTableIndex  ];
        ZXStringTable sPrev = m_Tables[iTableIndex-1];
        m_Tables[iTableIndex  ] = sPrev;
        m_Tables[iTableIndex-1] = sCurr;
        m_bDirty = true;
        return iTableIndex - 1;
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::DownTable(unsigned int iTableIndex)
{
    if (iTableIndex < m_Tables.size())
    {
        ZXStringTable sCurr = m_Tables[iTableIndex  ];
        ZXStringTable sPrev = m_Tables[iTableIndex+1];
        m_Tables[iTableIndex  ] = sPrev;
        m_Tables[iTableIndex+1] = sCurr;
        m_bDirty = true;
        return iTableIndex + 1;
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::AddString(unsigned int iTableIndex, const String& sID, const String& sValue)
{
    if (iTableIndex < m_Tables.size())
    {
        m_Tables[iTableIndex].Strings.push_back(sValue);
        m_Tables[iTableIndex].IDs.push_back(sID);
        m_bDirty = true;
        return m_Tables[iTableIndex].Strings.size() - 1;
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::RemoveString(unsigned int iTableIndex, unsigned int iStringIndex)
{
    if (iTableIndex < m_Tables.size())
    {
        if (iStringIndex < m_Tables[iTableIndex].Strings.size())
        {
            m_Tables[iTableIndex].Strings.erase(m_Tables[iTableIndex].Strings.begin() + iStringIndex);
            m_bDirty = true;
            return iStringIndex;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::CloneString(unsigned int iTableIndex, unsigned int iStringIndex)
{
    if (iTableIndex < m_Tables.size())
    {
        if (iStringIndex < m_Tables[iTableIndex].Strings.size())
        {
            return AddString(iTableIndex, m_Tables[iTableIndex].IDs[iStringIndex], m_Tables[iTableIndex].Strings[iStringIndex]);
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::SetString(unsigned int iTableIndex, unsigned int iStringIndex, const String& sValue)
{
    if (iTableIndex < m_Tables.size())
    {
        if (iStringIndex < m_Tables[iTableIndex].Strings.size())
        {
            m_Tables[iTableIndex].Strings[iStringIndex] = sValue;
            m_bDirty = true;
            return iStringIndex;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::SetID(unsigned int iTableIndex, unsigned int iStringIndex, const String& sID)
{
    if (iTableIndex < m_Tables.size())
    {
        if (iStringIndex < m_Tables[iTableIndex].Strings.size())
        {
            m_Tables[iTableIndex].IDs[iStringIndex] = sID;
            m_bDirty = true;
            return iStringIndex;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::UpString(unsigned int iTableIndex, unsigned int iStringIndex)
{
    if (iTableIndex < m_Tables.size())
    {
        if (1 <= iStringIndex && iStringIndex < m_Tables[iTableIndex].Strings.size())
        {
            String sCurr = m_Tables[iTableIndex].Strings[iStringIndex  ];
            String sPrev = m_Tables[iTableIndex].Strings[iStringIndex-1];
            m_Tables[iTableIndex].Strings[iStringIndex  ] = sPrev;
            m_Tables[iTableIndex].Strings[iStringIndex-1] = sCurr;
            sCurr = m_Tables[iTableIndex].IDs[iStringIndex  ];
            sPrev = m_Tables[iTableIndex].IDs[iStringIndex-1];
            m_Tables[iTableIndex].IDs[iStringIndex  ] = sPrev;
            m_Tables[iTableIndex].IDs[iStringIndex-1] = sCurr;
            m_bDirty = true;
            return iStringIndex - 1;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::DownString(unsigned int iTableIndex, unsigned int iStringIndex)
{
    if (iTableIndex < m_Tables.size())
    {
        if (iStringIndex < m_Tables[iTableIndex].Strings.size() - 1)
        {
            String sCurr = m_Tables[iTableIndex].Strings[iStringIndex  ];
            String sNext = m_Tables[iTableIndex].Strings[iStringIndex+1];
            m_Tables[iTableIndex].Strings[iStringIndex  ] = sNext;
            m_Tables[iTableIndex].Strings[iStringIndex+1] = sCurr;
            sCurr = m_Tables[iTableIndex].IDs[iStringIndex  ];
            sNext = m_Tables[iTableIndex].IDs[iStringIndex+1];
            m_Tables[iTableIndex].IDs[iStringIndex  ] = sNext;
            m_Tables[iTableIndex].IDs[iStringIndex+1] = sCurr;
            m_bDirty = true;
            return iStringIndex + 1;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXTableManager::FindTable(const String& sName)
{
    for (unsigned int i = 0; i < m_Tables.size(); i++)
    {
        if (m_Tables[i].sName == sName)
        {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------

