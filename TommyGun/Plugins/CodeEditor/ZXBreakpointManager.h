//---------------------------------------------------------------------------
#ifndef ZXBreakpointManagerH
#define ZXBreakpointManagerH
//---------------------------------------------------------------------------
#include <list>
#include <map>
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "KXmlInfo.h"
//---------------------------------------------------------------------------
class TBreakpoint
{
public:
    String          file;
    int             line;
    bool            enabled;
    unsigned int    passCount;
    unsigned int    passCountReset;
    
    TBreakpoint()
    : file("")
    , line(-1)
    , enabled(false)
    , passCount(0)
    {
    }
    
    TBreakpoint(const TBreakpoint& bp)
    : file(bp.file)
    , line(bp.line)
    , enabled(bp.enabled)
    , passCount(bp.passCount)
    , passCountReset(bp.passCountReset)
    {
    }

    TBreakpoint(const String& file, int line)
    : file(file)
    , line(line)
    , enabled(true)
    , passCount(0)
    , passCountReset(0)
    {
    }
    
    bool operator== (const TBreakpoint& bp) const
    {
        return bp.line == line && bp.file == file;
    }

    void Reset()
    {
        passCount = passCountReset;
    }
};

typedef std::list<TBreakpoint>  TBreakpointList;
typedef TBreakpointList::iterator  TBreakpointListIt;

class ZXBreakpointManager
{
public:
                __fastcall  ZXBreakpointManager();
                __fastcall ~ZXBreakpointManager();

    void        __fastcall  Clear();
    void        __fastcall  Reset();
    void        __fastcall  Add(const String& File, int Line);
    void        __fastcall  Remove(const String& File, int Line);
    void        __fastcall  RemoveAll();
    void        __fastcall  Enable(const String& File, int Line);
    void        __fastcall  EnableAll();
    void        __fastcall  Disable(const String& File, int Line);
    void        __fastcall  DisableAll();
    void        __fastcall  PassCount(const String& File, int Line, unsigned int Count);
    bool        __fastcall  ShouldBreak(const String& File, int Line);
    void        __fastcall  Get(TBreakpointList& list);
    TBreakpoint __fastcall  Get(const String& File, int Line);

    HRESULT     __fastcall  Load(KXmlInfo& xmlInfo);
    HRESULT     __fastcall  Save(KXmlInfo& xmlInfo);

private:

    TBreakpointList m_Breakpoints;
};
//---------------------------------------------------------------------------
#endif
