//---------------------------------------------------------------------------
#pragma hdrstop
#include "pch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GameEditor;
//---------------------------------------------------------------------------
__fastcall CollisionDistance::CollisionDistance()
: m_Distance(15)
, m_PropertyNode(-1)
{
}
//---------------------------------------------------------------------------
__fastcall CollisionDistance::~CollisionDistance()
{
}
//---------------------------------------------------------------------------
void __fastcall CollisionDistance::Init()
{
    m_PropertyNode = frmGameEditor->GetPropertyEditor().AddRootNode(this, "Collision Distance", tviWindow);
    m_DistanceNode = frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Distance", m_Distance);
}
//---------------------------------------------------------------------------
bool __fastcall CollisionDistance::Load(KXmlInfo& xmlInfo)
{
    bool bLoaded = false;
    KXmlInfo* Node;
    if (xmlInfo.Find(Node, "CollisionDistance", 0))
    {
        KXmlInfo* nValue = Node->GetNode("Distance", 0);
        if (nValue) m_Distance = std::max(10, std::min(15, nValue->GetInt()));
        bLoaded = true;
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
void __fastcall CollisionDistance::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo* Node;
    if (xmlInfo.Find(Node, "CollisionDistance", 0))
    {
        xmlInfo.Remove(Node);
    }
    // create a new map editor node
    KXmlInfo node("CollisionDistance");
    // store the map details
    node.Add("Distance", m_Distance);
    xmlInfo.Add(node);
}
//---------------------------------------------------------------------------
void __fastcall CollisionDistance::UpdateProperties()
{
    frmGameEditor->GetPropertyEditor().UpdateProperty(m_PropertyNode, m_DistanceNode, m_Distance);
}
//---------------------------------------------------------------------------
void __fastcall CollisionDistance::OnPropertyChanged(int node)
{
    int value;
    frmGameEditor->GetPropertyEditor().GetProperty(m_PropertyNode, node, value);
    if (node == m_DistanceNode)
    {
        m_Distance = std::max(10, std::min(15, value));
    }
    UpdateProperties();
}
//---------------------------------------------------------------------------

