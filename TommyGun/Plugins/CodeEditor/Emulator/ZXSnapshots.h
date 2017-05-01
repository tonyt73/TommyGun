//---------------------------------------------------------------------------
#ifndef ZXSnapshotsH
#define ZXSnapshotsH
//---------------------------------------------------------------------------
#include <list>
//---------------------------------------------------------------------------
class SnapshotManager
{
public:
                __fastcall  SnapshotManager(int minutes);
                __fastcall ~SnapshotManager();

    void        __fastcall  Clear();
    void        __fastcall  Push(Z80* context, unsigned char* memory);
    bool        __fastcall  Rewind(Z80* context, unsigned char* memory);
    bool        __fastcall  Forward(Z80* context, unsigned char* memory);

private:
    class Snapshot
    {
    public:
                __fastcall  Snapshot();
        void    __fastcall  Get(Z80* cpuContext, unsigned char* memory);
        void    __fastcall  Set(Z80* cpuContext, unsigned char* memory);

    private:
        Z80                 m_Context;
        unsigned char       m_Memory[65536];
    };

    Snapshot**              m_Snapshots;
    unsigned int            m_StartPosition;
    unsigned int            m_EndPosition;
    unsigned int            m_CurrentPosition;
    unsigned int            m_TotalFrames;
};
//---------------------------------------------------------------------------
#endif
