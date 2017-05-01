//---------------------------------------------------------------------------
#ifndef ZXKeyboardH
#define ZXKeyboardH
//- EMU ---------------------------------------------------------------------
#include "Types.h"
//- VCL ---------------------------------------------------------------------
#include <Classes.hpp>
//- STD ---------------------------------------------------------------------
#include <WinUser.h>
//---------------------------------------------------------------------------
class ZXKeyboard
{
public:     // methods
            __fastcall  ZXKeyboard();
            __fastcall ~ZXKeyboard();

    void    __fastcall  KeyDown(WORD &Key, TShiftState Shift);
    void    __fastcall  KeyUp(WORD &Key, TShiftState Shift);
    void    __fastcall  ReleaseAll();

    byte    __fastcall  Read(byte Port);

private:    // members
    byte    m_Ports[8]; // the keyboard ports

    void    __fastcall  Set(WORD Key);
    void    __fastcall  Reset(WORD Key);
};
//---------------------------------------------------------------------------
#endif
