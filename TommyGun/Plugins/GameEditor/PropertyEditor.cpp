//---------------------------------------------------------------------------
#pragma hdrstop
#include "pch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GameEditor;
//---------------------------------------------------------------------------
__fastcall PropertyEditor::PropertyEditor()
: m_CurrentNode(0)
, m_CurrentProperty(0)
{
}
//---------------------------------------------------------------------------
__fastcall PropertyEditor::~PropertyEditor()
{
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::Init(TTreeView* propertyView, TValueListEditor* propertyEditor)
{
    m_PropertyView = propertyView;
    m_PropertyEditor = propertyEditor;

    m_PropertyView->Items->Clear();
}
//---------------------------------------------------------------------------
int __fastcall PropertyEditor::AddRootNode(PropertyObject* owner, const AnsiString& name, int iconIndex)
{
    TPropertyNode* node = new TPropertyNode();
    int nodeIndex = m_Nodes.size();
    node->Owner = owner;
    node->Node = m_PropertyView->Items->Add(NULL, name);
    node->Node->ImageIndex = iconIndex;
    node->Node->SelectedIndex = iconIndex;
    m_Nodes.push_back(node);
    return nodeIndex;
}
//---------------------------------------------------------------------------
int __fastcall PropertyEditor::AddProperty(int node, const AnsiString& key, int value)
{
    if (0 <= node && node < (int)m_Nodes.size())
    {
        TProperty* property = new TProperty(key);
        property->SetInt(value);
        m_Nodes[node]->Properties.push_back(property);
        return m_Nodes[node]->Properties.size() - 1;
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall PropertyEditor::AddProperty(int node, const AnsiString& key, const AnsiString& value)
{
    if (0 <= node && node < (int)m_Nodes.size())
    {
        TProperty* property = new TProperty(key);
        property->SetString(value);
        m_Nodes[node]->Properties.push_back(property);
        return m_Nodes[node]->Properties.size() - 1;
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall PropertyEditor::AddProperty(int node, const AnsiString& key, bool value)
{
    if (0 <= node && node < (int)m_Nodes.size())
    {
        TProperty* property = new TProperty(key);
        property->SetBool(value);
        m_Nodes[node]->Properties.push_back(property);
        return m_Nodes[node]->Properties.size() - 1;
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall PropertyEditor::AddProperty(int node, const AnsiString& key, float value)
{
    if (0 <= node && node < (int)m_Nodes.size())
    {
        TProperty* property = new TProperty(key);
        property->SetFloat(value);
        m_Nodes[node]->Properties.push_back(property);
        return m_Nodes[node]->Properties.size() - 1;
    }
    return -1;
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::UpdateProperty(int node, int property, int value)
{
    if (0 <= node && node < (int)m_Nodes.size() && 0 <= property && property < (int)m_Nodes[node]->Properties.size())
    {
        m_Nodes[node]->Properties[property]->SetInt(value);
        if (node == m_CurrentNode)
            m_PropertyEditor->Values[m_Nodes[node]->Properties[property]->Key] = m_Nodes[node]->Properties[property]->Value;
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::UpdateProperty(int node, int property, const AnsiString& value)
{
    if (0 <= node && node < (int)m_Nodes.size() && 0 <= property && property < (int)m_Nodes[node]->Properties.size())
    {
        m_Nodes[node]->Properties[property]->SetString(value);
        if (node == m_CurrentNode)
            m_PropertyEditor->Values[m_Nodes[node]->Properties[property]->Key] = m_Nodes[node]->Properties[property]->Value;
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::UpdateProperty(int node, int property, bool value)
{
    if (0 <= node && node < (int)m_Nodes.size() && 0 <= property && property < (int)m_Nodes[node]->Properties.size())
    {
        m_Nodes[node]->Properties[property]->SetBool(value);
        if (node == m_CurrentNode)
            m_PropertyEditor->Values[m_Nodes[node]->Properties[property]->Key] = m_Nodes[node]->Properties[property]->Value;
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::UpdateProperty(int node, int property, float value)
{
    if (0 <= node && node < (int)m_Nodes.size() && 0 <= property && property < (int)m_Nodes[node]->Properties.size())
    {
        m_Nodes[node]->Properties[property]->SetFloat(value);
        if (node == m_CurrentNode)
            m_PropertyEditor->Values[m_Nodes[node]->Properties[property]->Key] = m_Nodes[node]->Properties[property]->Value;
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::GetProperty(int node, int property, int& value)
{
    if (0 <= node && node < (int)m_Nodes.size() && 0 <= property && property < (int)m_Nodes[node]->Properties.size())
    {
        value = m_Nodes[node]->Properties[property]->GetInt();
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::GetProperty(int node, int property, AnsiString& value)
{
    if (0 <= node && node < (int)m_Nodes.size() && 0 <= property && property < (int)m_Nodes[node]->Properties.size())
    {
        value = m_Nodes[node]->Properties[property]->GetString();
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::GetProperty(int node, int property, bool& value)
{
    if (0 <= node && node < (int)m_Nodes.size() && 0 <= property && property < (int)m_Nodes[node]->Properties.size())
    {
        value = m_Nodes[node]->Properties[property]->GetBool();
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::GetProperty(int node, int property, float& value)
{
    if (0 <= node && node < (int)m_Nodes.size() && 0 <= property && property < (int)m_Nodes[node]->Properties.size())
    {
        value = m_Nodes[node]->Properties[property]->GetFloat();
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::SelectNode(int node)
{
    m_PropertyEditor->Strings->Clear();
    m_CurrentNode = node;
    for (int i = 0; i < (int)m_Nodes[node]->Properties.size(); i++)
    {
        String keyValuePair = m_Nodes[node]->Properties[i]->Key + "=" + m_Nodes[node]->Properties[i]->Value;
        m_PropertyEditor->Strings->Add(keyValuePair);
    }
    m_PropertyEditor->Update();
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::SetActiveNode(const AnsiString& node)
{
    for (int i = 0; i < (int)m_Nodes.size(); i++)
    {
        if (m_Nodes[i]->Node->Text == node)
        {
            // select the node
            SelectNode(i);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::OnChange(TTreeNode* node)
{
    for (int i = 0; i < (int)m_Nodes.size(); i++)
    {
        if (m_Nodes[i]->Node == node)
        {
            // select the node
            SelectNode(i);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::OnSelect(int row)
{
    m_CurrentProperty = row;
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::OnItemChanged()
{
	m_Nodes[m_CurrentNode]->Owner->OnPropertyChanged(m_CurrentProperty);
	m_PropertyEditor->Values[m_PropertyEditor->Keys[m_CurrentProperty+1]] = m_Nodes[m_CurrentNode]->Properties[m_CurrentProperty]->Value;
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::OnItemExit()
{
	OnItemChanged();
}
//---------------------------------------------------------------------------
void __fastcall PropertyEditor::SetItemText(int row, AnsiString value)
{
    if (0 <= m_CurrentNode && m_CurrentNode < (int)m_Nodes.size() && 0 <= row && row < (int)m_Nodes[m_CurrentNode]->Properties.size())
    {
        m_Nodes[m_CurrentNode]->Properties[row]->Value = value;
    }
}
//---------------------------------------------------------------------------

