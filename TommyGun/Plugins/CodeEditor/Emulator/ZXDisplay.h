//---------------------------------------------------------------------------
#ifndef ZXDisplayH
#define ZXDisplayH
//- VCL ---------------------------------------------------------------------
#include <Classes.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class ZXSpectrum;
//---------------------------------------------------------------------------
class ZXDisplay
{
public:
            __fastcall  ZXDisplay();
            __fastcall ~ZXDisplay();

    void    __fastcall  Draw(TImage* Bitmap);
    void    __fastcall  SetAttributes(bool Visible, bool WhiteBackground);

protected:
    friend ZXSpectrum;

    void    __fastcall  DrawFrame(const char* Memory);
    void    __fastcall  DrawLine(const char* Memory, int y);

private:
    typedef Graphics::TBitmap TDisplay;

    TDisplay*           m_Display;
    int                 m_Flash;                    // The current state of the flash bit
    int                 m_FlashTimer;               // The timer used to toggle the flash bit
    DWORD               m_LastTime;                 // The last time we processed the display
    bool                m_ShowAttributes;           // flag: Show attributes when drawing the screen
    bool                m_WhiteBackground;          // flag: When not showing attributes show a white background else use black

    void                Flash();
};
//---------------------------------------------------------------------------
#endif
