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
#include "ZXToolDefinition.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXToolDefinition::ZXToolDefinition()
{
}
//---------------------------------------------------------------------------
__fastcall ZXToolDefinition::~ZXToolDefinition()
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinition::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo Definition("Definition");
    Definition.Add("Name", m_Name);
    Definition.Add("Executable", m_Executable);
    Definition.Add("Extensions", m_Extensions);
    Definition.Add("DefaultParameters", m_DefaultParameters);
    Definition.Add("AcceptsMultipleInputFiles", m_AcceptsMultipleInputFiles);
    Definition.Add("Type", m_Type == ttBuilder ? "Builder" : "Emulator");
    Definition.Add("PrefixError", m_PrefixError);
    Definition.Add("PrefixFile", m_PrefixFile);
    Definition.Add("PrefixLine", m_PrefixLine);
    xmlInfo.Add(Definition);
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinition::Load(KXmlInfo& xmlInfo)
{
    KXmlInfo* node = xmlInfo.GetNode("Name");
    if (SAFE_PTR(node)) m_Name = node->GetText();
    node = xmlInfo.GetNode("Executable");
    if (SAFE_PTR(node)) m_Executable = node->GetText();
    node = xmlInfo.GetNode("Extensions");
    if (SAFE_PTR(node)) m_Extensions = node->GetText();
    node = xmlInfo.GetNode("DefaultParameters");
    if (SAFE_PTR(node)) m_DefaultParameters = node->GetText();
    node = xmlInfo.GetNode("AcceptsMultipleInputFiles");
    if (SAFE_PTR(node)) m_AcceptsMultipleInputFiles = node->GetBool();
    node = xmlInfo.GetNode("Type");
    if (SAFE_PTR(node)) m_Type = node->GetText() == "Builder" ? ttBuilder : ttEmulator;
    node = xmlInfo.GetNode("PrefixError");
    if (SAFE_PTR(node))  m_PrefixError = node->GetText();
    node = xmlInfo.GetNode("PrefixFile");
    if (SAFE_PTR(node)) m_PrefixFile = node->GetText();
    node = xmlInfo.GetNode("PrefixLine");
    if (SAFE_PTR(node)) m_PrefixLine = node->GetText();
    return true;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
__fastcall ZXToolDefinitions::ZXToolDefinitions()
{
}
//---------------------------------------------------------------------------
__fastcall ZXToolDefinitions::~ZXToolDefinitions()
{
    m_ToolDefinitions.clear();
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinitions::Save(void)
{
    KXmlInfo ToolDefinitions("Definitions");

    for (int i = 0; i < (int)m_ToolDefinitions.size(); i++)
    {
        m_ToolDefinitions[i].Save(ToolDefinitions);
    }

    String sFile = ExtractFilePath(Application->ExeName) + "Tools.xml";
    return ToolDefinitions.SaveFile(sFile);
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinitions::Load(void)
{
    String sFile = ExtractFilePath(Application->ExeName) + "Tools.xml";
    KXmlInfo ToolDefinitions;
    ToolDefinitions.Reset();
    ToolDefinitions.LoadFile(sFile);
    for (KXmlNodes::iterator it = ToolDefinitions.begin(); it != ToolDefinitions.end(); it++)
    {
        ZXToolDefinition definition;
        definition.Load(*(*it));
        m_ToolDefinitions.push_back(definition);
    }
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinitions::Add(ZXToolDefinition& definition)
{
    bool canAdd = true;
    for (int i = 0; i < (int)m_ToolDefinitions.size(); i++)
    {
        if (m_ToolDefinitions[i].m_Name == definition.m_Name)
        {
            canAdd = false;
            break;
        }
    }
    if (canAdd)
    {
        m_ToolDefinitions.push_back(definition);
    }
    return canAdd;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinitions::Update(int index, ZXToolDefinition& definition)
{
    if (m_ToolDefinitions[index].m_Name == definition.m_Name)
    {
        m_ToolDefinitions[index] = definition;
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinitions::Remove(int index)
{
    if (index >= 0 && index < (int)m_ToolDefinitions.size())
    {
        m_ToolDefinitions.erase(m_ToolDefinitions.begin() + index);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinitions::Get(int i, ZXToolDefinition& definition)
{
    if (i >= 0 && i < (int)m_ToolDefinitions.size())
    {
        definition = m_ToolDefinitions[i];
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
int __fastcall ZXToolDefinitions::GetIndex(String name)
{
    for (int i = 0; i < (int)m_ToolDefinitions.size(); i++)
    {
        if (m_ToolDefinitions[i].m_Name == name)
        {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXToolDefinitions::GetExecutableIndex(String name, bool ignorePath)
{
    for (int i = 0; i < (int)m_ToolDefinitions.size(); i++)
    {
        if (!ignorePath)
        {
            if (m_ToolDefinitions[i].m_Executable == name)
            {
                return i;
            }
        }
        else
        {
            if (ExtractFileName(m_ToolDefinitions[i].m_Executable).LowerCase() == name.LowerCase())
            {
                return i;
            }
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinitions::ExecutableExists(String name)
{
    for (int i = 0; i < (int)m_ToolDefinitions.size(); i++)
    {
        if (m_ToolDefinitions[i].m_Name == name)
        {
            String sFile = m_ToolDefinitions[i].m_Executable;
            frmCodeEditor->DoSubstitutes(sFile);
            return FileExists(sFile);
        }
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXToolDefinitions::Exists(String name)
{
    for (int i = 0; i < (int)m_ToolDefinitions.size(); i++)
    {
        if (m_ToolDefinitions[i].m_Name == name)
        {
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------

