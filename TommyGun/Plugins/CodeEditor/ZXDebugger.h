//---------------------------------------------------------------------------
#ifndef TDebuggerH
#define TDebuggerH
//- EMU ---------------------------------------------------------------------
#include "ZXSpectrum.h"
#include "ZXSymbolsManager.h"
#include "ZXDebugFileManager.h"
#include "ZXBreakpointManager.h"
//- STL ---------------------------------------------------------------------
#include <list>
//---------------------------------------------------------------------------
typedef struct
{
    TStackOp    StackOp;
    String      Operand;
    WORD        Value;
    WORD        StackPtr;
    String      Label;
    String      FuncAddr;
} TStackInfo;
typedef std::list<TStackInfo> TDebugStack;
typedef std::list<TStackInfo>::const_iterator TDebugStackConstIt;
typedef void __fastcall (__closure *TEventOnBreakpointHit)(const String& File, int Line);
//---------------------------------------------------------------------------
class TDebugger
{
public:
            __fastcall      TDebugger();
            __fastcall     ~TDebugger();

    void    __fastcall      Reset();
    void    __fastcall      LoadSNA(const AnsiString& File);
    void    __fastcall      LoadMap(const AnsiString& File);
    void    __fastcall      Run();
    void    __fastcall      StepOver();
    void    __fastcall      StepInto();
    void    __fastcall      StepOut();
    const TDebugStack&
            __fastcall      GetStack() { return m_Stack; }
    void    __fastcall      StackOp(Z80* R, TStackOp StackOp, char* Operand, word Value, word StackPtr, word FuncAddr);
    void    __fastcall      DebugString(Z80* R);

    void    __fastcall      KeyDown(WORD Key, TShiftState State);
    void    __fastcall      KeyUp(WORD Key, TShiftState State);

    bool    __fastcall      CanRun() { return m_Machine.CanRun();   }
    void    __fastcall      UpdateDisplay();

    __property ZXSpectrum               Machine         = { read = m_Machine            };
    __property ZXDebugFileManager       Debug           = { read = m_DebugFileManager   };
    __property ZXSymbolsManager         Symbols         = { read = m_SymbolsManager     };
    __property ZXBreakpointManager      Breakpoints     = { read = m_Breakpoints        };
    __property TEventOnBreakpointHit    OnBreakpointHit = { read = m_OnBreakpointHit, write = m_OnBreakpointHit };

private:
    enum StopFunction
    {
        sfNothing,
        sfStepOver,
        sfStepOut,
        sfStepInto
    };

    ZXSpectrum              m_Machine;
    TDebugStack             m_Stack;                // a description of the stack
    StopFunction            m_StopFunction;         // flag: indicates when to stop at the QueryBreak()
    int                     m_CallCount;            // number of function calls deep into a step over operation
    unsigned int            m_InstructionCount;     // number of instructions encountered
    ZXSymbolsManager        m_SymbolsManager;       // the symbols manager
    word                    m_LastQueryBreakAddress;
    ZXDebugFileManager      m_DebugFileManager;
    ZXBreakpointManager     m_Breakpoints;
    TEventOnBreakpointHit   m_OnBreakpointHit;

    void    __fastcall      UpdateStateView();
    static bool             QueryBreak(word Address);
    bool                    DoQueryBreak(word Address);
    String  __fastcall      ToLabel(word Value);
};
extern TDebugger* g_Debugger;
//---------------------------------------------------------------------------
#endif
