//---------------------------------------------------------------------------

#ifndef fEnterpriseColorsH
#define fEnterpriseColorsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TdlgEnterpriseColors : public TForm
{
__published:	// IDE-managed Components
    TPanel *panButtons;
    TBevel *bvlButtons;
    TButton *cmdCancel;
    TButton *cmdOK;
    TImage *imgPalette;
    TPanel *panMessageHeader;
    TBevel *bvlMessageTop;
    TImage *imgMessageIcon;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TImage *imgLogo;
    TLabel *Label1;
    TPanel *panColorInfo;
    TLabel *lblColourDetails;
    TLabel *lblRGBLabel;
    TLabel *lblRGB;
    TLabel *lblIndexLabel;
    TLabel *lblIndex;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TSpeedButton *spdR1;
    TSpeedButton *spdR2;
    TSpeedButton *spdR3;
    TSpeedButton *spdR4;
    TSpeedButton *spdR5;
    TSpeedButton *spdR6;
    TSpeedButton *spdR7;
    TSpeedButton *spdR8;
    TSpeedButton *spdG1;
    TSpeedButton *spdG2;
    TSpeedButton *spdG3;
    TSpeedButton *spdG4;
    TSpeedButton *spdG5;
    TSpeedButton *spdG6;
    TSpeedButton *spdG7;
    TSpeedButton *spdG8;
    TSpeedButton *spdB1;
    TSpeedButton *spdB2;
    TSpeedButton *spdB3;
    TSpeedButton *spdB4;
    TPanel *panColour;
    TPanel *panBias;
    TLabel *lblFixBiasDetails;
    TLabel *lblFixBiasIndex;
    TLabel *lblFixBias;
    TBevel *bvlBias;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall imgPaletteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall spdR1Click(TObject *Sender);
    void __fastcall spdG1Click(TObject *Sender);
    void __fastcall spdB1Click(TObject *Sender);
private:	// User declarations
    TColor      m_Color;
    int         m_Index;
    int         m_RedIndex;
    int         m_GreenIndex;
    int         m_BlueIndex;
    bool        m_BiasMode;

    void    __fastcall UpdateColor();
    void    __fastcall UpdateGUI();

public:		// User declarations
            __fastcall TdlgEnterpriseColors(TComponent* Owner);

    bool    __fastcall Execute(int iColor, bool bUseBias = false);
    TColor  __fastcall GetColor(int iIndex);
    int     __fastcall GetIndex(TColor Colour);

    __property  TColor  Color = { read = m_Color    };
    __property  int     Index = { read = m_Index    };
};
//---------------------------------------------------------------------------
extern PACKAGE TdlgEnterpriseColors *dlgEnterpriseColors;
//---------------------------------------------------------------------------
#endif
