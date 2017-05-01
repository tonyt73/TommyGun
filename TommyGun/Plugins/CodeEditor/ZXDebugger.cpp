//---------------------------------------------------------------------------
#pragma hdrstop
//- APP --------------------------------------------------------------------------
#include "ZXDebugger.h"
#include "fDisplayView.h"
#include "fDebuggerStateView.h"
#include "fCodeEditor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TDebugger* g_Debugger = new TDebugger();
//---------------------------------------------------------------------------
__fastcall TDebugger::TDebugger()
: m_StopFunction(sfNothing)
, m_CallCount(0)
, m_InstructionCount(0)
, m_LastQueryBreakAddress(0)
{
    m_Machine.SetQueryBreakFunc(TDebugger::QueryBreak);
}
//---------------------------------------------------------------------------
__fastcall TDebugger::~TDebugger()
{
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::Reset()
{
    m_Stack.clear();
    m_Machine.Reset();
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::LoadSNA(const AnsiString& File)
{
    Machine.LoadSNA(File);
    m_Stack.clear();
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::LoadMap(const AnsiString& File)
{
    m_SymbolsManager.LoadMapFile(File);
    m_Stack.clear();
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::Run()
{
    m_InstructionCount = m_Machine.Context.InstrCount;
    m_CallCount = 0;
    m_StopFunction = sfNothing;
    m_Machine.Run();
    UpdateDisplay();
    UpdateStateView();
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::StepOver()
{
    m_InstructionCount = m_Machine.Context.InstrCount;
    m_CallCount = 0;
    m_StopFunction = sfStepOver;
    while (m_StopFunction == sfStepOver)
    {
        m_Machine.Run();
        UpdateDisplay();
        UpdateStateView();
        Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::StepInto()
{
    m_StopFunction = sfStepInto;
    m_InstructionCount = m_Machine.Context.InstrCount;
    m_Machine.StepInto();
    UpdateDisplay();
    UpdateStateView();
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::StepOut()
{
    m_StopFunction = sfStepOut;
    m_InstructionCount = m_Machine.Context.InstrCount;
    m_CallCount = 0;
    while (m_StopFunction == sfStepOut)
    {
        m_Machine.Run();
        UpdateDisplay();
        UpdateStateView();
        Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::UpdateDisplay()
{
    m_Machine.DrawFrame(frmDisplayView->imgMainDisplay, true);
    frmOSBView->RedrawBuffers();
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::UpdateStateView()
{
    Z80 context;
    m_Machine.GetContext(context);
    frmDebuggerStateView->SetContext(context);
    frmOSBView->RedrawBuffers();
}
//---------------------------------------------------------------------------
void __fastcall StackOp(Z80* R, TStackOp StackOp, char* Operand, word Value, word StackPtr, word FuncAddr)
{
    g_Debugger->StackOp(R, StackOp, Operand, Value, StackPtr, FuncAddr);
}
//---------------------------------------------------------------------------
void __fastcall DebugString(Z80* R)
{
    g_Debugger->DebugString(R);
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::DebugString(Z80* R)
{
    // call back to editor
    switch (R->AF.B.h)
    {
        case 0:     // Source code file,line
        {
            String File;
            int Line;
            m_DebugFileManager.GetLocation(R->PC.W, File, Line);
            if (Line != -1)
            {
                frmCodeEditor->ConsolePrint("Source: " +  File + "@" + IntToStr(Line-1));
            }
            break;
        }
        case 1:     // var 1 bytes
        {
            int symbol = R->HL.W;
            String name = m_SymbolsManager.GetSymbol(symbol);
            if (name != "")
            {
                byte value = m_Machine.GetByte(symbol);
                frmCodeEditor->ConsolePrint(name + "=" + IntToStr(value) + ", $" + IntToHex(value, 2));
            }
            break;
        }
        case 2:     // var 2 bytes
        {
            int symbol = R->HL.W;
            String name = m_SymbolsManager.GetSymbol(symbol);
            if (name != "")
            {
                word value = m_Machine.GetWord(symbol);
                frmCodeEditor->ConsolePrint(name + "=" + IntToStr(value) + ", $" + IntToHex(value, 4));
            }
            break;
        }
        case 3:     // memory dump
        {
            String msg;
            unsigned int address = R->HL.W;
            String symname = m_SymbolsManager.GetSymbol(address);
            if (symname == "")
            {
                symname = "$" + IntToHex(R->HL.W, 4);
            }
            frmCodeEditor->ConsolePrint("Memory dump - Address: " + symname + ", Length: $" + IntToHex(R->BC.W, 4));
            for (int i = 0; i < R->BC.W; ++i)
            {
                msg += IntToHex(m_Machine.GetByte(address), 2) + " ";
                if ((i+1) % R->DE.B.l == 0)
                {
                    frmCodeEditor->ConsolePrint(msg);
                    msg = "";
                }
                address++;
            }
            if (msg != "")
            {
                frmCodeEditor->ConsolePrint(msg);
            }
            break;
        }
        default:    // user defined messages
        {
            if (128 <= R->AF.B.h && R->AF.B.h < 255)
            {
                // TODO: Maybe one day if I need them?
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TDebugger::StackOp(Z80* R, TStackOp StackOp, char* Operand, word Value, word StackPtr, word FuncAddr)
{
    TStackInfo stackInfo;
    switch (StackOp)
    {
    case soPop:
        m_Stack.pop_front();
        break;
    case soRet:
        // take the item off the stack
        m_CallCount--;
        m_Stack.pop_front();
        break;
    case soPush:
        stackInfo.Value    = Value;
        if (Value == R->PC.W)
        {
            // push pc and jp = call for interrupts
            m_CallCount++;
        }
        stackInfo.StackOp  = StackOp;
        stackInfo.Operand  = Operand;
        stackInfo.StackPtr = StackPtr;
        stackInfo.Label    = ToLabel(Value);
        m_Stack.push_front(stackInfo);
        break;
    case soCall:
        m_CallCount++;
        stackInfo.Value    = Value;
        stackInfo.StackOp  = StackOp;
        stackInfo.Operand  = Operand;
        stackInfo.StackPtr = StackPtr;
        stackInfo.Label    = ToLabel(Value);
        stackInfo.FuncAddr = ToLabel(FuncAddr);
        m_Stack.push_front(stackInfo);
        break;
    }
}
//---------------------------------------------------------------------------
bool TDebugger::QueryBreak(word Address)
{
    return g_Debugger->DoQueryBreak(Address);
}
//---------------------------------------------------------------------------
bool TDebugger::DoQueryBreak(word Address)
{
    // check breakpoints
    static String File;
    static int Line;
    m_DebugFileManager.GetLocation(Address, File, Line);
    m_Machine.Debug("File: " + File + ", Line: " + IntToStr(Line) + ", Label: " + ToLabel(Address));
    if (m_Breakpoints.ShouldBreak(File, Line) && m_LastQueryBreakAddress != Address)
    {
        m_StopFunction = sfNothing;
        m_LastQueryBreakAddress = Address;
        m_OnBreakpointHit(File, Line);
        return true;
    }

    if (m_StopFunction != sfNothing)
    {
        // are we stepping over a call
        if (m_StopFunction == sfStepOver && m_CallCount == 0 && (m_Machine.Context.InstrCount - m_InstructionCount) >= 1 && m_LastQueryBreakAddress != Address)
        {
            // stop we have executed 1 instruction or jumped over a function call
            m_StopFunction = sfNothing;
            return true;
        }
        if (m_StopFunction == sfStepOut && m_CallCount == -1)
        {
            m_StopFunction = sfNothing;
            return true;
        }
        if (m_StopFunction == sfStepInto && (m_Machine.Context.InstrCount - m_InstructionCount) == 1)
        {
            m_StopFunction = sfNothing;
            return true;
        }
    }
    m_LastQueryBreakAddress = Address;
    return false;
}
//---------------------------------------------------------------------------
String __fastcall TDebugger::ToLabel(word Value)
{
    return m_SymbolsManager.GetSymbol(Value);
}
//---------------------------------------------------------------------------

