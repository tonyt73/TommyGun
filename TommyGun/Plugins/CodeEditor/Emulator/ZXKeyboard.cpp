//---------------------------------------------------------------------------
#pragma hdrstop
#include "ZXKeyboard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Map Standard PC keyboard to Spectrum keys
//---------------------------------------------------------------------------
struct
{
    word    Key;
    byte    Port;
    byte    Bit;
}
const g_KeyToPortBit[] =
{
    { VK_SHIFT  , 0, 0x01 },
    { 'Z'       , 0, 0x02 },
    { 'X'       , 0, 0x04 },
    { 'C'       , 0, 0x08 },
    { 'V'       , 0, 0x10 },
    { 'A'       , 1, 0x01 },
    { 'S'       , 1, 0x02 },
    { 'D'       , 1, 0x04 },
    { 'F'       , 1, 0x08 },
    { 'G'       , 1, 0x10 },
    { 'Q'       , 2, 0x01 },
    { 'W'       , 2, 0x02 },
    { 'E'       , 2, 0x04 },
    { 'R'       , 2, 0x08 },
    { 'T'       , 2, 0x10 },
    { '1'       , 3, 0x01 },
    { '2'       , 3, 0x02 },
    { '3'       , 3, 0x04 },
    { '4'       , 3, 0x08 },
    { '5'       , 3, 0x10 },
    { '0'       , 4, 0x01 },
    { '9'       , 4, 0x02 },
    { '8'       , 4, 0x04 },
    { '7'       , 4, 0x08 },
    { '6'       , 4, 0x10 },
    { 'P'       , 5, 0x01 },
    { 'O'       , 5, 0x02 },
    { 'I'       , 5, 0x04 },
    { 'U'       , 5, 0x08 },
    { 'Y'       , 5, 0x10 },
    { VK_RETURN , 6, 0x01 },
    { 'L'       , 6, 0x02 },
    { 'K'       , 6, 0x04 },
    { 'J'       , 6, 0x08 },
    { 'H'       , 6, 0x10 },
    { VK_SPACE  , 7, 0x01 },
    { VK_CONTROL, 7, 0x02 },
    { 'M'       , 7, 0x04 },
    { 'N'       , 7, 0x08 },
    { 'B'       , 7, 0x10 },
    { 0         , 0, 0x00 }
};
//---------------------------------------------------------------------------
// Map Standard PC keyboard to a combination of Spectrum key presses
//---------------------------------------------------------------------------
struct
{
    word    Key;
    int     MappedKeys[2];
}
const g_MappedKeys[] =
{
    { VK_BACK       , { VK_SHIFT    , '0'           } },
    { VK_LEFT       , { VK_SHIFT    , '5'           } },
    { VK_DOWN       , { VK_SHIFT    , '6'           } },
    { VK_UP         , { VK_SHIFT    , '7'           } },
    { VK_RIGHT      , { VK_SHIFT    , '8'           } },
    { VK_ESCAPE     , { VK_SHIFT    , ' '           } },
    { VK_INSERT     , { VK_SHIFT    , VK_CONTROL    } },
    { VK_DECIMAL    , { VK_CONTROL  , 'M'           } },
    { VK_ADD        , { VK_CONTROL  , 'K'           } },
    { VK_SUBTRACT   , { VK_CONTROL  , 'J'           } },
    { VK_MULTIPLY   , { VK_CONTROL  , 'B'           } },
    { VK_DIVIDE     , { VK_CONTROL  , 'V'           } },
    { VK_NUMPAD0    , { 0           , '0'           } },
    { VK_NUMPAD1    , { 0           , '1'           } },
    { VK_NUMPAD2    , { 0           , '2'           } },
    { VK_NUMPAD3    , { 0           , '3'           } },
    { VK_NUMPAD4    , { 0           , '4'           } },
    { VK_NUMPAD5    , { 0           , '5'           } },
    { VK_NUMPAD6    , { 0           , '6'           } },
    { VK_NUMPAD7    , { 0           , '7'           } },
    { VK_NUMPAD8    , { 0           , '8'           } },
    { VK_NUMPAD9    , { 0           , '9'           } },

    { 0             , { 0           , 0             } },
};
//---------------------------------------------------------------------------
//
//  Keyboard class
// 
//---------------------------------------------------------------------------
__fastcall ZXKeyboard::ZXKeyboard()
{
    ReleaseAll();
}
//---------------------------------------------------------------------------
__fastcall ZXKeyboard::~ZXKeyboard()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXKeyboard::Set(WORD Key)
{
    int i = 0;
    while (g_KeyToPortBit[i].Key)
    {
        if (Key == g_KeyToPortBit[i].Key)
        {
            m_Ports[g_KeyToPortBit[i].Port] &= ~g_KeyToPortBit[i].Bit;
            break;
        }
        ++i;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXKeyboard::Reset(WORD Key)
{
    int i = 0;
    while (g_KeyToPortBit[i].Key)
    {
        if (Key == g_KeyToPortBit[i].Key)
        {
            m_Ports[g_KeyToPortBit[i].Port] |= g_KeyToPortBit[i].Bit;
            break;
        }
        ++i;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXKeyboard::KeyDown(WORD &Key, TShiftState Shift)
{
    // is it a mapped key?
    int i = 0;
    while (g_MappedKeys[i].Key)
    {
        if (g_MappedKeys[i].Key == Key)
        {
            // press all the keys for the mapped key
            Set(g_MappedKeys[i].MappedKeys[0]);
            Set(g_MappedKeys[i].MappedKeys[1]);
            return;
        }
        ++i;
    }
    // must be an ordinary key
    Set(Key);
    if (Shift.Contains(ssShift))
    {
        Set(VK_SHIFT);
    }
    if (Shift.Contains(ssCtrl))
    {
        Set(VK_CONTROL);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXKeyboard::KeyUp(WORD &Key, TShiftState Shift)
{
    // is it a mapped key?
    int i = 0;
    while (g_MappedKeys[i].Key)
    {
        if (g_MappedKeys[i].Key == Key)
        {
            // press all the keys for the mapped key
            Reset(g_MappedKeys[i].MappedKeys[0]);
            Reset(g_MappedKeys[i].MappedKeys[1]);
            return;
        }
        ++i;
    }
    // must be an ordinary key
    Reset(Key);
    if (Shift.Contains(ssShift))
    {
        Reset(VK_SHIFT);
    }
    if (Shift.Contains(ssCtrl))
    {
        Reset(VK_CONTROL);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXKeyboard::ReleaseAll()
{
    memset(m_Ports, 0xFF, 8);
}
//---------------------------------------------------------------------------
byte __fastcall ZXKeyboard::Read(byte Port)
{
    for (int i = 0; i < 8; ++i, Port >>= 1)
    {
        if (Port & 0x01)
        {
            return m_Ports[i];
        }
    }
    return 0xFF;
}
//---------------------------------------------------------------------------

