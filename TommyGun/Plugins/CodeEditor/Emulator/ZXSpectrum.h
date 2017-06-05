//---------------------------------------------------------------------------
//
// ZX SPECTRUM class
//
// This is the simplistic ZX Spectrum implementation
// Handles the CPU, Display, Keyboard.
// Provides a hook for the debugger to control it and query its state.
//
//---------------------------------------------------------------------------
#ifndef ZXSpectrumH
#define ZXSpectrumH
//- VCL ---------------------------------------------------------------------
#include <Classes.hpp>
#include <ExtCtrls.hpp>
//- EMU ---------------------------------------------------------------------
#include "Z80.h"
#include "ZXDisplay.h"
#include "ZXKeyboard.h"
#include "ZXSnapshots.h"
//---------------------------------------------------------------------------
class ZXSpectrum
{
public: // methods
                __fastcall  ZXSpectrum();
                __fastcall ~ZXSpectrum();

                            // cpu debugger routines
    void        __fastcall  Reset();
    void        __fastcall  Run();
    void        __fastcall  StepInto();
    void        __fastcall  SetQueryBreakFunc(bool(*QueryBreak)(word)) { m_QueryBreakFunc = QueryBreak; }
                            // Display the back buffer to an image
    void        __fastcall  DrawFrame(TImage* DisplayImage, bool Refresh);
                            // Load a Snapshot
    void        __fastcall  LoadSNA(const AnsiString& File);
                            // Z80 emulation support routines
    void        __fastcall  WrZ80(register word Addr,register byte Value);
    byte        __fastcall  RdZ80(register word Addr);
    void        __fastcall  OutZ80(register word Port,register byte Value);
    byte        __fastcall  InZ80(register word Port);
    void        __fastcall  PatchZ80(register Z80 *R);
    byte        __fastcall  DebugZ80(register Z80 *R);
    word        __fastcall  LoopZ80(register Z80 *R);
    void        __fastcall  StackOp(TStackOp StackOp, char* Operand, WORD Value, WORD Func);
    void        __fastcall  DebugString(Z80* R);
                            // states whether we are valid and capable of running
    bool        __fastcall  CanRun() { return true;  }
                            // retrieves the cpu context
    void        __fastcall  GetContext(Z80& Context);
    void        __fastcall  GetMemory(unsigned int address, unsigned int bytes, char* buffer);
    byte        __fastcall  GetByte(unsigned int address);
    word        __fastcall  GetWord(unsigned int address);

    void        __fastcall  Debug(const String& msg);
    void        __fastcall  Debug(const String& msg, const String& value1);
	void        __fastcall  Debug(const String& msg, const String& value1, const String& value2);
	void		__fastcall	DumpMemory();

	void        __fastcall  SnapshotReset();
	bool        __fastcall  SnapshotRewind();
	bool        __fastcall  SnapshotForward();

	__property ZXDisplay    Display     = { read = m_Display    };
	__property ZXKeyboard   Keyboard    = { read = m_Keyboard   };

	__property Z80          Context     = { read = m_Z80Context };

private:    // methods

private:    // members

    ZXKeyboard              m_Keyboard;                 // The Spectrum keyboard mapper
    ZXDisplay               m_Display;                  // The Spectrum display
    unsigned char*          m_Memory;                   // Spectrum memory
    Z80                     m_Z80Context;               // The current cpu context
    int                     m_CurrentLine;              // The current scanline
    int                     m_InstructionsToRun;        // Number of instructions to run before exiting the emulation loop
    bool                    (*m_QueryBreakFunc)(word);  // A function ptr to a function that decides whether to break at this point
    SnapshotManager         m_SnapshotManager;          // The snapshots manager

    static const unsigned char m_48KRom[16384];
};
//---------------------------------------------------------------------------
#endif // ZXSpectrumH

