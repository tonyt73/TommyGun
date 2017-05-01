//---------------------------------------------------------------------------
#ifndef fSamCoupeColorsH
#define fSamCoupeColorsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TdlgSamCoupeColors : public TForm
{
__published:	// IDE-managed Components
    TPanel *panButtons;
    TBevel *bvlButtons;
    TButton *cmdCancel;
    TButton *cmdOK;
    TImage *imgSamPalette;
    TLabel *lblColourIndex;
    TLabel *lblColourIndexValue;
    TLabel *lblColourRGB;
    TPanel *panColour;
    TLabel *lblSelectedColour;
    TLabel *lblSelectedColourIndex;
    TPanel *panMessageHeader;
    TBevel *bvlMessageTop;
    TImage *imgMessageIcon;
    TImage *imgLogo;
    TLabel *Label1;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    void __fastcall panC64BlackClick(TObject *Sender);
    void __fastcall imgSamPaletteMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgSamPaletteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
    TColor      m_Color;
public:		// User declarations
            __fastcall TdlgSamCoupeColors(TComponent* Owner);

    bool    __fastcall Execute(int iColor);

    __property  TColor  Color = { read = m_Color    };
};
//---------------------------------------------------------------------------
extern PACKAGE TdlgSamCoupeColors *dlgSamCoupeColors;
//---------------------------------------------------------------------------
#endif
