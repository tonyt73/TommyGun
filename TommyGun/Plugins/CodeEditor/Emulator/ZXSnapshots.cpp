//---------------------------------------------------------------------------
#include "..\pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SnapshotManager::Snapshot::Snapshot()
{
}
//---------------------------------------------------------------------------
void __fastcall SnapshotManager::Snapshot::Get(Z80* cpuContext, unsigned char* memory)
{
    memcpy(cpuContext, &m_Context, sizeof(Z80));
    memcpy(memory, &m_Memory, 65536);
}
//---------------------------------------------------------------------------
void __fastcall SnapshotManager::Snapshot::Set(Z80* cpuContext, unsigned char* memory)
{
    memcpy(&m_Context, cpuContext, sizeof(Z80));
    memcpy(&m_Memory, memory, 65536);
}
//---------------------------------------------------------------------------
__fastcall SnapshotManager::SnapshotManager(int minutes)
: m_StartPosition(0)
, m_EndPosition(0)
, m_CurrentPosition(0)
{
    m_TotalFrames = 50 * 60 * minutes;    // 50 frames per second * 60 seconds per minutes * number of minutes of snapshot buffer
    int totalMemory = m_TotalFrames * sizeof(Snapshot);
    m_Snapshots = new Snapshot*[m_TotalFrames];
    for (int i = 0; i < m_TotalFrames; ++i)
    {
        try
        {
            m_Snapshots[i] = new Snapshot();
        }
        catch(...)
        {
            m_TotalFrames = i;
        }
    }
}
//---------------------------------------------------------------------------
__fastcall SnapshotManager::~SnapshotManager()
{
    for (int i = 0; i < m_TotalFrames; ++i)
    {
        delete m_Snapshots[i];
    }
    delete[] m_Snapshots;
}
//---------------------------------------------------------------------------
void __fastcall SnapshotManager::Clear()
{
    m_StartPosition = 0;
    m_EndPosition = 0;
    m_CurrentPosition = 0;
}
//---------------------------------------------------------------------------
void __fastcall SnapshotManager::Push(Z80* context, unsigned char* memory)
{
    // clear from position to end
    m_EndPosition = m_CurrentPosition;
    m_Snapshots[m_CurrentPosition]->Set(context, memory);
    m_CurrentPosition = (m_CurrentPosition + 1) % m_TotalFrames;
    if (m_CurrentPosition == m_StartPosition)
    {
        m_StartPosition++;
    }
}
//---------------------------------------------------------------------------
bool __fastcall SnapshotManager::Rewind(Z80* context, unsigned char* memory)
{
    if (m_CurrentPosition != m_StartPosition)
    {
        m_CurrentPosition = (m_TotalFrames + m_CurrentPosition - 1) % m_TotalFrames;
        m_Snapshots[m_CurrentPosition]->Get(context, memory);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall SnapshotManager::Forward(Z80* context, unsigned char* memory)
{
    if (m_CurrentPosition != m_EndPosition)
    {
        m_CurrentPosition = (m_CurrentPosition + 1) % m_TotalFrames;
        m_Snapshots[m_CurrentPosition]->Get(context, memory);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
