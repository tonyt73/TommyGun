//---------------------------------------------------------------------------

#ifndef fCommodoreColorsH
#define fCommodoreColorsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TdlgCommodoreColors : public TForm
{
__published:	// IDE-managed Components
    TPanel *panButtons;
    TBevel *bvlButtons;
    TButton *cmdCancel;
    TButton *cmdOK;
    TPanel *panMessageHeader;
    TBevel *bvlMessageTop;
    TImage *imgMessageIcon;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TLabel *lblCommodoreColors;
    TPanel *panV20Black;
    TPanel *panV20White;
    TPanel *panV20Red;
    TPanel *panV20Cyan;
    TPanel *panV20Purple;
    TPanel *panV20Green;
    TPanel *panV20Blue;
    TPanel *panV20Yellow;
    TPanel *panV20Orange;
    TPanel *panV20Brown;
    TPanel *panV20LtRed;
    TPanel *panV20DarkGray;
    TPanel *panV20MedGray;
    TPanel *panV20LtGreen;
    TPanel *panV20LtBlue;
    TPanel *panV20LtGray;
    TImage *Image1;
    void __fastcall panC64BlackClick(TObject *Sender);
private:	// User declarations
    int                 m_Color;
public:		// User declarations
            __fastcall  TdlgCommodoreColors(TComponent* Owner);

    bool    __fastcall  Execute(int iColor);

    __property  int     Color = { read = m_Color    };
};
//---------------------------------------------------------------------------
extern PACKAGE TdlgCommodoreColors *dlgCommodoreColors;
//---------------------------------------------------------------------------
#endif
