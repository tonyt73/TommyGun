//---------------------------------------------------------------------------
#include <stdio.h>
//---------------------------------------------------------------------------
#include "ZXSpectrum.h"
#include "ZXSpectrum48KROM.h"
//---------------------------------------------------------------------------
const byte g_UlaDefault = 0xFF;
static ZXSpectrum* g_Instance = NULL;
//---------------------------------------------------------------------------
__fastcall ZXSpectrum::ZXSpectrum()
: m_Memory(NULL)
, m_CurrentLine(0)
, m_InstructionsToRun(-1)
, m_QueryBreakFunc(NULL)
, m_SnapshotManager(5)
{
    if (g_Instance == NULL)
    {
        g_Instance = this;
        m_Memory = new byte[65536];
        Reset();
    }
    else
    {
        // only make machine instance please!
        assert(0);
    }
}
//---------------------------------------------------------------------------
__fastcall ZXSpectrum::~ZXSpectrum()
{
    delete[] m_Memory;

    m_Memory = NULL;
    m_CurrentLine = -1;
    g_Instance = NULL;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::Reset()
{
    memset(m_Memory, 0, 65536);
    memcpy(m_Memory, m_48KRom, 16384);

    // update every hsync
    m_Z80Context.IPeriod = (3.5f * 1000000.f) / 60.f / 192.f;
    m_Z80Context.Trace = 0;
    m_Z80Context.Trap = 0xFFFF;

    // reset the z80
    ResetZ80(&m_Z80Context);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::Run()
{
    
    m_Z80Context.Trace = 0;
    m_InstructionsToRun = -1;
    RunZ80(&m_Z80Context);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::StepInto()
{
    m_Z80Context.Trace = 1;
    m_InstructionsToRun = 1;
    RunZ80(&m_Z80Context);
}
//---------------------------------------------------------------------------
void __fastcall WrZ80(register word Addr,register byte Value)
{
    g_Instance->WrZ80(Addr, Value);
}
//---------------------------------------------------------------------------
byte __fastcall RdZ80(register word Addr)
{
    return g_Instance->RdZ80(Addr);
}
//---------------------------------------------------------------------------
void __fastcall OutZ80(register word Port,register byte Value)
{
    g_Instance->OutZ80(Port, Value);
}
//---------------------------------------------------------------------------
byte __fastcall InZ80(register word Port)
{
    return g_Instance->InZ80(Port);
}
//---------------------------------------------------------------------------
void __fastcall PatchZ80(register Z80 *R)
{
    g_Instance->PatchZ80(R);
}
//---------------------------------------------------------------------------
byte __fastcall DebugZ80(register Z80 *R)
{
    return g_Instance->DebugZ80(R);
}
//---------------------------------------------------------------------------
word __fastcall LoopZ80(register Z80 *R)
{
    return g_Instance->LoopZ80(R);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::WrZ80(register word Addr,register byte Value)
{
    m_Memory[Addr] = Value;
}
//---------------------------------------------------------------------------
byte __fastcall ZXSpectrum::RdZ80(register word Addr)
{
    return m_Memory[Addr];
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::OutZ80(register word Port,register byte Value)
{
    // do nothing for the moment
}
//---------------------------------------------------------------------------
byte __fastcall ZXSpectrum::InZ80(register word Port)
{
    // we don't do tape processing or any other port related features
    // we are only concerned with reading the keyboard and possibly the kempston joystick/mouse
    byte value = g_UlaDefault;
    value &= m_Keyboard.Read(~(Port >> 8));
    return value;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::PatchZ80(register Z80 *R)
{
}
//---------------------------------------------------------------------------
byte __fastcall ZXSpectrum::DebugZ80(register Z80 *R)
{
    Debug("DebugZ80: Address:" + IntToStr(R->PC.W) + "  IFF: " + IntToStr(R->IFF));
    if (m_QueryBreakFunc != NULL && m_QueryBreakFunc(R->PC.W))
    {
        // stop in the QueryBreakFunc() returns true
        return 0;
    }
    if (m_Z80Context.Trace)
    {
        // stop if we where asked to execute n instructions
        return m_InstructionsToRun--;
    }
    // don't stop
    return 1;
}
//---------------------------------------------------------------------------
word __fastcall ZXSpectrum::LoopZ80(register Z80 *R)
{
    Debug("LoopZ80: Address:" + IntToStr(R->PC.W) + "  IFF: " + IntToStr(R->IFF));
    word interruptCode = INT_NONE;
    /*if (inDebugStepMode)
    {
        // update the current display line
        m_Display.DrawLine(m_Memory, m_CurrentLine);
    }*/
//    if (m_CurrentLine == 0)
//    {
//        R->Trace = 1;
//        m_InstructionsToRun = 0;
//        // refresh the screen
//        interruptCode = INT_QUIT;
//    }
    ++m_CurrentLine;
    if (m_CurrentLine == 192)
    {
        // snapshot the frame
        m_SnapshotManager.Push(R, m_Memory);
        R->Trace = 1;
        m_InstructionsToRun = 0;
        m_CurrentLine = 0;
        // generate an interrupt and the end of the screen
        interruptCode = INT_IRQ;
    }
    return interruptCode;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::DrawFrame(TImage* DisplayImage, bool Refresh)
{
    if (Refresh)
    {
        m_Display.DrawFrame(m_Memory);
    }
    m_Display.Draw(DisplayImage);
    DisplayImage->Refresh();
}
/*---------------------------------------------------------------------------
   Offset   Size   Description
  ---------------------------------------------------------------------------
   0        1      byte   I
   1        8      word   HL',DE',BC',AF'
   9        10     word   HL,DE,BC,IY,IX
   19       1      byte   Interrupt (bit 2 contains IFF2, 1=EI/0=DI)
   20       1      byte   R
   21       4      words  AF,SP
   25       1      byte   IntMode (0=IM0/1=IM1/2=IM2)
   26       1      byte   BorderColor (0..7, not used by Spectrum 1.7)
   27       49152  bytes  RAM dump 16384..65535
  ---------------------------------------------------------------------------*/
void __fastcall ZXSpectrum::LoadSNA(const AnsiString& File)
{
    Reset();
    byte buffer[49180];

    FILE* fh = fopen(File.c_str(), "rb");
    if (fh)
    {
        fread(buffer, 49179, 1, fh);
        fclose(fh);

        // copy snapshot into memory
        memcpy(m_Memory + 16384, buffer + 27, 49152);

        // update the cpu context
        m_Z80Context.I       = buffer[0];
        m_Z80Context.HL1.B.l = buffer[1];
        m_Z80Context.HL1.B.h = buffer[2];
        m_Z80Context.DE1.B.l = buffer[3];
        m_Z80Context.DE1.B.h = buffer[4];
        m_Z80Context.BC1.B.l = buffer[5];
        m_Z80Context.BC1.B.h = buffer[6];
        m_Z80Context.AF1.B.l = buffer[7];
        m_Z80Context.AF1.B.h = buffer[8];

        m_Z80Context.HL.B.l = buffer[ 9];
        m_Z80Context.HL.B.h = buffer[10];
        m_Z80Context.DE.B.l = buffer[11];
        m_Z80Context.DE.B.h = buffer[12];
        m_Z80Context.BC.B.l = buffer[13];
        m_Z80Context.BC.B.h = buffer[14];
        m_Z80Context.IX.B.l = buffer[15];
        m_Z80Context.IX.B.h = buffer[16];
        m_Z80Context.IY.B.l = buffer[17];
        m_Z80Context.IY.B.h = buffer[18];

        m_Z80Context.IFF    = buffer[19] << 1;  // IFF2 for sna is bit 2 (0x04) but IFF_2 is 0x08 for us
        m_Z80Context.R      = buffer[20];

        m_Z80Context.AF.B.l = buffer[21];
        m_Z80Context.AF.B.h = buffer[22];
        m_Z80Context.SP.B.l = buffer[23];
        m_Z80Context.SP.B.h = buffer[24];

        // retn in rom
        m_Z80Context.PC.W   = 0x0072; 
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::GetContext(Z80& Context)
{
    memcpy(&Context, &m_Z80Context, sizeof(Z80));
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::GetMemory(unsigned int address, unsigned int bytes, char* buffer)
{
    if (address + bytes < 65536)
    {
        memcpy(buffer, m_Memory + address, bytes);
    }
}
//---------------------------------------------------------------------------
byte __fastcall ZXSpectrum::GetByte(unsigned int address)
{
    if (address < 65536)
    {
        return m_Memory[address];
    }
    return 0;
}
//---------------------------------------------------------------------------
word __fastcall ZXSpectrum::GetWord(unsigned int address)
{
    if (address + 1 < 65536)
    {
        return m_Memory[address] + (256 * m_Memory[address+1]);
    }
    return 0;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::Debug(const String& msg)
{
    //OutputDebugString(msg.c_str());
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::Debug(const String& msg, const String& value1)
{
    //String m = msg + " : " + value1;
    //OutputDebugString(m.c_str());
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::Debug(const String& msg, const String& value1, const String& value2)
{
    //String m = msg + " : " + value1 + " : " + value2;
    //OutputDebugString(m.c_str());
}
//---------------------------------------------------------------------------
void __fastcall ZXSpectrum::SnapshotReset()
{
    m_SnapshotManager.Clear();
}
//---------------------------------------------------------------------------
bool __fastcall ZXSpectrum::SnapshotRewind()
{
    return m_SnapshotManager.Rewind(&m_Z80Context, m_Memory);
}
//---------------------------------------------------------------------------
bool __fastcall ZXSpectrum::SnapshotForward()
{
    return m_SnapshotManager.Forward(&m_Z80Context, m_Memory);
}
//---------------------------------------------------------------------------

