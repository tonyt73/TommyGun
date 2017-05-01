//---------------------------------------------------------------------------
#pragma hdrstop
#include "ZXDisplay.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const int g_FlashDelay  = 500;
const int g_AttrPtr     = 22528;
//---------------------------------------------------------------------------
const DWORD g_ColorsSpectrum[16] =
{
    //AlReGrBl
    0x00000000, // black
    0x000000BF, // blue
    0x00BF0000, // red
    0x00BF00BF, // magenta
    0x0000BF00, // green
    0x0000BFBF, // cyan
    0x00BFBF00, // yellow
    0x00BFBFBF, // gray
    0x00000000, // bright black
    0x000000FF, // bright blue
    0x00FF0000, // bright red
    0x00FF00FF, // bright magenta
    0x0000FF00, // bright green
    0x0000FFFF, // bright cyan
    0x00FFFF00, // bright yellow
    0x00FFFFFF  // white
};
//---------------------------------------------------------------------------
unsigned int g_ScreenOffsets[192] =
{
     0 * 32 + 256 * 0,
     0 * 32 + 256 * 1,
     0 * 32 + 256 * 2,
     0 * 32 + 256 * 3,
     0 * 32 + 256 * 4,
     0 * 32 + 256 * 5,
     0 * 32 + 256 * 6,
     0 * 32 + 256 * 7,

     1 * 32 + 256 * 0,
     1 * 32 + 256 * 1,
     1 * 32 + 256 * 2,
     1 * 32 + 256 * 3,
     1 * 32 + 256 * 4,
     1 * 32 + 256 * 5,
     1 * 32 + 256 * 6,
     1 * 32 + 256 * 7,

     2 * 32 + 256 * 0,
     2 * 32 + 256 * 1,
     2 * 32 + 256 * 2,
     2 * 32 + 256 * 3,
     2 * 32 + 256 * 4,
     2 * 32 + 256 * 5,
     2 * 32 + 256 * 6,
     2 * 32 + 256 * 7,

     3 * 32 + 256 * 0,
     3 * 32 + 256 * 1,
     3 * 32 + 256 * 2,
     3 * 32 + 256 * 3,
     3 * 32 + 256 * 4,
     3 * 32 + 256 * 5,
     3 * 32 + 256 * 6,
     3 * 32 + 256 * 7,

     4 * 32 + 256 * 0,
     4 * 32 + 256 * 1,
     4 * 32 + 256 * 2,
     4 * 32 + 256 * 3,
     4 * 32 + 256 * 4,
     4 * 32 + 256 * 5,
     4 * 32 + 256 * 6,
     4 * 32 + 256 * 7,

     5 * 32 + 256 * 0,
     5 * 32 + 256 * 1,
     5 * 32 + 256 * 2,
     5 * 32 + 256 * 3,
     5 * 32 + 256 * 4,
     5 * 32 + 256 * 5,
     5 * 32 + 256 * 6,
     5 * 32 + 256 * 7,

     6 * 32 + 256 * 0,
     6 * 32 + 256 * 1,
     6 * 32 + 256 * 2,
     6 * 32 + 256 * 3,
     6 * 32 + 256 * 4,
     6 * 32 + 256 * 5,
     6 * 32 + 256 * 6,
     6 * 32 + 256 * 7,

     7 * 32 + 256 * 0,
     7 * 32 + 256 * 1,
     7 * 32 + 256 * 2,
     7 * 32 + 256 * 3,
     7 * 32 + 256 * 4,
     7 * 32 + 256 * 5,
     7 * 32 + 256 * 6,
     7 * 32 + 256 * 7,
};
//---------------------------------------------------------------------------
__fastcall ZXDisplay::ZXDisplay()
: m_Display(NULL)
, m_Flash(0)
, m_FlashTimer(g_FlashDelay)
, m_LastTime(0)
, m_ShowAttributes(true)
, m_WhiteBackground(true)
{
    m_Display = new TDisplay();
    m_Display->Width  = 256;
    m_Display->Height = 192;
    m_Display->PixelFormat = pf32bit;
    m_Display->Canvas->Brush->Color = clBlack;
    m_Display->Canvas->FillRect(TRect(0,0,m_Display->Width,m_Display->Height));
}
//---------------------------------------------------------------------------
__fastcall ZXDisplay::~ZXDisplay()
{
    delete m_Display;
}
//---------------------------------------------------------------------------
void __fastcall ZXDisplay::Draw(TImage* Image)
{
    StretchBlt(Image->Picture->Bitmap->Canvas->Handle,
        0, 0, Image->Width, Image->Height,
        m_Display->Canvas->Handle, 0, 0, m_Display->Width, m_Display->Height,
        SRCCOPY);
}
//---------------------------------------------------------------------------
void __fastcall ZXDisplay::Flash()
{
    DWORD dwTime = timeGetTime();
    m_FlashTimer -= dwTime - m_LastTime;
    m_LastTime = dwTime;

    if (m_FlashTimer < 0)
    {
        m_FlashTimer = g_FlashDelay;
        m_Flash ^= 1;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXDisplay::DrawFrame(const char* Memory)
{
    Flash();
    
    int iFlash;
    int iBright;
    int iPaper;
    int iInk;
    int baseOffset;
    int line;
    int segment;
    byte attr;
    byte pixels;

    DWORD colors[] =
    {
        0x00FFFFFF, // white paper
        0x00000000  // black ink
    };

    if (!m_WhiteBackground)
    {
        colors[0] = 0x00000000;
        colors[1] = 0x00FFFFFF;
    }

    for (int y = 0; y < 192; y += 8)
    {
        segment =  y % 64;
        line    = (y & 0xFFC0) << 5;

        for (int x = 0; x < 256; x += 8)
        {
            if (m_ShowAttributes)
            {
                // calculate the ink and paper colours
                byte attr = Memory[g_AttrPtr + ((y << 2) + (x >> 3))];
                iFlash  = ((attr & 0x80) >> 7) * m_Flash;
                iBright =  (attr & 0x40) >> 3;
                iPaper  =  (attr & 0x38) >> 3;
                iInk    =  (attr & 0x07);

                colors[1 - iFlash] = g_ColorsSpectrum[iBright + iInk  ];
                colors[    iFlash] = g_ColorsSpectrum[iBright + iPaper];
            }

            int baseOffset = 16384 + line + (x >> 3);

            // draw the character block lines
            for (int i = 0; i < 8; ++i)
            {
                DWORD* pLine = (DWORD*)m_Display->ScanLine[y + i];
                // get the pixel address
                pixels = Memory[baseOffset + g_ScreenOffsets[segment + i]];

                pLine[x + 0] = colors[(pixels & 0x80) >> 7];
                pLine[x + 1] = colors[(pixels & 0x40) >> 6];
                pLine[x + 2] = colors[(pixels & 0x20) >> 5];
                pLine[x + 3] = colors[(pixels & 0x10) >> 4];
                pLine[x + 4] = colors[(pixels & 0x08) >> 3];
                pLine[x + 5] = colors[(pixels & 0x04) >> 2];
                pLine[x + 6] = colors[(pixels & 0x02) >> 1];
                pLine[x + 7] = colors[(pixels & 0x01)     ];
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXDisplay::DrawLine(const char* Memory, int y)
{
    Flash();
    
    int iFlash;
    int iBright;
    int iPaper;
    int iInk;
    int baseOffset;
    int line;
    int segment;
    byte attr;
    byte pixels;

    DWORD colors[] =
    {
        0x00FFFFFF, // white paper
        0x00000000  // black ink
    };

    if (!m_WhiteBackground)
    {
        colors[0] = 0x00000000;
        colors[1] = 0x00FFFFFF;
    }

    segment =  y % 64;
    line    = (y & 0xFFC0) << 5;

    for (int x = 0; x < 256; x += 8)
    {
        if (m_ShowAttributes)
        {
            // calculate the ink and paper colours
            byte attr = Memory[g_AttrPtr + ((y << 2) + (x >> 3))];
            iFlash  = ((attr & 0x80) >> 7) * m_Flash;
            iBright =  (attr & 0x40) >> 3;
            iPaper  =  (attr & 0x38) >> 3;
            iInk    =  (attr & 0x07);

            colors[1 - iFlash] = g_ColorsSpectrum[iBright + iInk  ];
            colors[    iFlash] = g_ColorsSpectrum[iBright + iPaper];
        }

        int baseOffset = 16384 + line + (x >> 3);

        // draw the character block line
        DWORD* pLine = (DWORD*)m_Display->ScanLine[y];
        // get the pixel address
        pixels = Memory[baseOffset + g_ScreenOffsets[segment]];

        pLine[x + 0] = colors[(pixels & 0x80) >> 7];
        pLine[x + 1] = colors[(pixels & 0x40) >> 6];
        pLine[x + 2] = colors[(pixels & 0x20) >> 5];
        pLine[x + 3] = colors[(pixels & 0x10) >> 4];
        pLine[x + 4] = colors[(pixels & 0x08) >> 3];
        pLine[x + 5] = colors[(pixels & 0x04) >> 2];
        pLine[x + 6] = colors[(pixels & 0x02) >> 1];
        pLine[x + 7] = colors[(pixels & 0x01)     ];
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXDisplay::SetAttributes(bool Visible, bool WhiteBackground)
{
    m_ShowAttributes  = Visible;
    m_WhiteBackground = WhiteBackground;
}
//---------------------------------------------------------------------------
