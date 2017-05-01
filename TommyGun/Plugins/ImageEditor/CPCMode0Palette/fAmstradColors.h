//---------------------------------------------------------------------------

#ifndef fAmstradColorsH
#define fAmstradColorsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TdlgAmstradColors : public TForm
{
__published:	// IDE-managed Components
    TPanel *panButtons;
    TBevel *bvlButtons;
    TButton *cmdCancel;
    TButton *cmdOK;
    TPanel *Panel1;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TTabSheet *TabSheet3;
    TPanel *panC64Black;
    TPanel *panC64White;
    TPanel *panC64Red;
    TPanel *panC64Cyan;
    TPanel *panC64Purple;
    TPanel *panC64Green;
    TPanel *panC64Blue;
    TPanel *panC64Yellow;
    TPanel *panC64Orange;
    TPanel *panC64Brown;
    TPanel *panC64LtRed;
    TPanel *panC64DarkGray;
    TPanel *panC64MedGray;
    TPanel *panC64LtGreen;
    TPanel *panC64LtBlue;
    TPanel *panC64LtGray;
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *Panel4;
    TPanel *Panel5;
    TPanel *Panel6;
    TPanel *Panel7;
    TPanel *Panel8;
    TPanel *Panel9;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TPanel *Panel14;
    TPanel *Panel15;
    TPanel *Panel16;
    TPanel *Panel17;
    TPanel *Panel18;
    TPanel *Panel19;
    TPanel *Panel21;
    TPanel *Panel23;
    TPanel *Panel25;
    TPanel *Panel26;
    TPanel *Panel27;
    TPanel *Panel28;
    TPanel *Panel29;
    TPanel *Panel30;
    TPanel *Panel31;
    TPanel *Panel32;
    TPanel *Panel33;
    TPanel *Panel35;
    TPanel *Panel36;
    TPanel *Panel37;
    TPanel *Panel39;
    TPanel *Panel40;
    TPanel *Panel41;
    TPanel *Panel42;
    TPanel *Panel43;
    TPanel *Panel45;
    TPanel *Panel46;
    TPanel *Panel47;
    TPanel *Panel48;
    TPanel *Panel49;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TPanel *Panel20;
    TPanel *Panel22;
    TPanel *Panel34;
    TPanel *Panel50;
    TPanel *Panel52;
    TPanel *Panel54;
    TPanel *Panel55;
    TPanel *Panel56;
    TPanel *Panel57;
    TPanel *Panel58;
    TPanel *Panel59;
    TPanel *Panel60;
    TPanel *Panel62;
    TPanel *Panel63;
    TPanel *Panel64;
    TPanel *Panel65;
    TPanel *Panel66;
    TPanel *Panel67;
    TPanel *Panel68;
    TPanel *Panel69;
    TPanel *Panel70;
    TPanel *Panel71;
    TPanel *Panel72;
    TPanel *Panel73;
    TPanel *Panel74;
    TPanel *Panel75;
    TPanel *Panel76;
    TTabSheet *TabSheet4;
    TPanel *Panel78;
    TPanel *Panel79;
    TPanel *Panel80;
    TPanel *Panel81;
    TPanel *Panel84;
    TPanel *Panel85;
    TPanel *Panel86;
    TPanel *Panel87;
    TPanel *Panel88;
    TPanel *Panel89;
    TPanel *Panel90;
    TPanel *Panel91;
    TPanel *Panel92;
    TPanel *Panel94;
    TPanel *Panel95;
    TPanel *Panel96;
    TPanel *Panel98;
    TPanel *Panel99;
    TPanel *Panel100;
    TPanel *Panel101;
    TPanel *Panel102;
    TPanel *Panel103;
    TPanel *Panel104;
    TPanel *Panel105;
    TPanel *Panel106;
    TPanel *Panel107;
    TPanel *Panel108;
    TPanel *Panel44;
    TPanel *panMessageHeader;
    TBevel *bvlMessageTop;
    TImage *imgMessageIcon;
    TImage *imgLogo;
    TLabel *Label5;
    TPanel *Panel24;
    TPanel *Panel38;
    TPanel *Panel51;
    TPanel *Panel53;
    void __fastcall panC64BlackClick(TObject *Sender);
private:	// User declarations
    TColor      m_Color;
public:		// User declarations
            __fastcall TdlgAmstradColors(TComponent* Owner);

    bool    __fastcall Execute(int iColor);

    __property  TColor  Color = { read = m_Color    };
};
//---------------------------------------------------------------------------
extern PACKAGE TdlgAmstradColors *dlgAmstradColors;
//---------------------------------------------------------------------------
#endif
