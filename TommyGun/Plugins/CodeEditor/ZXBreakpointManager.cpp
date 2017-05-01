//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ZXBreakpointManager.h"
#include "SafeMacros.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall  ZXBreakpointManager::ZXBreakpointManager()
{
}
//---------------------------------------------------------------------------
__fastcall ZXBreakpointManager::~ZXBreakpointManager()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::Clear()
{
    m_Breakpoints.clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::Reset()
{
    for (TBreakpointListIt it = m_Breakpoints.begin(); it != m_Breakpoints.end(); ++it)
    {
        (*it).Reset();
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::Add(const String& File, int Line)
{
    TBreakpoint bp(File, Line);
    TBreakpointListIt it = std::find(m_Breakpoints.begin(), m_Breakpoints.end(), bp);
    if (it == m_Breakpoints.end())
    {
        m_Breakpoints.push_back(bp);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::Remove(const String& File, int Line)
{
    TBreakpointListIt it = std::find(m_Breakpoints.begin(), m_Breakpoints.end(), TBreakpoint(File, Line));
    if (it != m_Breakpoints.end())
    {
        m_Breakpoints.erase(it);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::RemoveAll()
{
    m_Breakpoints.clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::Enable(const String& File, int Line)
{
    TBreakpointListIt it = std::find(m_Breakpoints.begin(), m_Breakpoints.end(), TBreakpoint(File, Line));
    if (it == m_Breakpoints.end())
    {
        it->enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::EnableAll()
{
    for (TBreakpointListIt it = m_Breakpoints.begin(); it != m_Breakpoints.end(); ++it)
    {
        it->enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::Disable(const String& File, int Line)
{
    TBreakpointListIt it = std::find(m_Breakpoints.begin(), m_Breakpoints.end(), TBreakpoint(File, Line));
    if (it != m_Breakpoints.end())
    {
        it->enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::DisableAll()
{
    for (TBreakpointListIt it = m_Breakpoints.begin(); it != m_Breakpoints.end(); ++it)
    {
        it->enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::PassCount(const String& File, int Line, unsigned int Count)
{
    TBreakpointListIt it = std::find(m_Breakpoints.begin(), m_Breakpoints.end(), TBreakpoint(File, Line));
    if (it != m_Breakpoints.end())
    {
        it->passCount = Count;
        it->passCountReset = Count;
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXBreakpointManager::ShouldBreak(const String& File, int Line)
{
    TBreakpointListIt it = std::find(m_Breakpoints.begin(), m_Breakpoints.end(), TBreakpoint(File, Line));
    if (it != m_Breakpoints.end())
    {
        int pc = it->passCount;
        if (pc > 0)
            it->passCount--;
        return it->enabled && pc == 0;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXBreakpointManager::Get(TBreakpointList& list)
{
    list.clear();
    for (TBreakpointListIt it = m_Breakpoints.begin(); it != m_Breakpoints.end(); ++it)
    {
        list.push_back(*it);
    }
}
//---------------------------------------------------------------------------
TBreakpoint __fastcall ZXBreakpointManager::Get(const String& File, int Line)
{
    TBreakpoint bp;
    TBreakpointListIt it = std::find(m_Breakpoints.begin(), m_Breakpoints.end(), TBreakpoint(File, Line));
    if (it != m_Breakpoints.end())
    {
        return (*it);
    }
    return bp;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXBreakpointManager::Load(KXmlInfo& xmlInfo)
{
    KXmlInfo* bps;
    if (xmlInfo.Find(bps, "Breakpoints", 0))
    {
        for (KXmlNodes::iterator it = bps->begin(); it != bps->end(); it++)
        {
            if ((*it)->GetName() == "Breakpoint")
            {
                KXmlInfo* pFile = (*it)->GetNode("File");
                KXmlInfo* pLine = (*it)->GetNode("Line");
                KXmlInfo* pEnabled = (*it)->GetNode("Enabled");
                KXmlInfo* pPassCount = (*it)->GetNode("PassCount");
                if (SAFE_PTR(pFile) && SAFE_PTR(pLine) && SAFE_PTR(pEnabled) && SAFE_PTR(pPassCount))
                {
                    TBreakpoint bp(pFile->GetText(), pLine->GetInt());
                    bp.enabled = pEnabled->GetBool();
                    bp.passCountReset = pPassCount->GetInt();
                    bp.Reset();
                    m_Breakpoints.push_back(bp);
                }
            }
        }
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXBreakpointManager::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo& bps = xmlInfo.AddTag("Breakpoints");
    for (TBreakpointListIt it = m_Breakpoints.begin(); it != m_Breakpoints.end(); ++it)
    {
        // save the file link to the xml object
        KXmlInfo& bp = bps.AddTag("Breakpoint");
        bp.Add("File", it->file);
        bp.Add("Line", it->line);
        bp.Add("Enabled", it->enabled);
        bp.Add("PassCount", it->passCountReset);
    }
    return S_OK;
}
//---------------------------------------------------------------------------

