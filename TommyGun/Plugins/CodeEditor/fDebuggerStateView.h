//---------------------------------------------------------------------------
#ifndef fDebuggerStateViewH
#define fDebuggerStateViewH
//- VCL ---------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//- APP ---------------------------------------------------------------------
#include "Z80.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TfrmDebuggerStateView : public TForm
{
__published:	// IDE-managed Components
    TPageControl *pgcRegisters;
    TTabSheet *tabRegisters;
    TTabSheet *tabAYRegisters;
    TPageControl *pgcStack;
    TTabSheet *tabStack;
    TPageControl *pgcPorts;
    TTabSheet *tabPorts;
    TMemo *txtStack;
    TMemo *txtAYRegisters;
    TPanel *panButtons;
    TSpeedButton *btnCollapse;
    TPanel *panSpeed;
    TGroupBox *GroupBox1;
    TRadioButton *rad1pc;
    TRadioButton *rad10pc;
    TRadioButton *rad25pc;
    TRadioButton *rad50pc;
    TRadioButton *rad100pc;
    TGroupBox *GroupBox2;
    TPanel *Panel1;
    TRadioButton *radHex;
    TRadioButton *radDecimal;
    TPanel *Panel2;
    TRadioButton *rad16bit;
    TRadioButton *rad8bit;
    TPanel *Panel3;
    TLabel *lblRegsFlags;
    TLabel *lblRegsInterrupts;
    TLabeledEdit *lblRegsPC;
    TLabeledEdit *lblRegsAF;
    TLabeledEdit *lblRegsBC;
    TLabeledEdit *lblRegsDE;
    TLabeledEdit *lblRegsHL;
    TLabeledEdit *lblRegsIX;
    TLabeledEdit *lblRegsSP;
    TLabeledEdit *lblRegsAF_;
    TLabeledEdit *lblRegsBC_;
    TLabeledEdit *lblRegsDE_;
    TLabeledEdit *lblRegsHL_;
    TLabeledEdit *lblRegsIY;
    TLabeledEdit *lblRegsI;
    TLabeledEdit *lblRegsR;
    TCheckBox *chkRegsFlags_S;
    TCheckBox *chkRegsFlags_Z;
    TCheckBox *chkRegsFlags_5;
    TCheckBox *chkRegsFlags_H;
    TCheckBox *chkRegsFlags_3;
    TCheckBox *chkRegsFlags_V;
    TCheckBox *chkRegsFlags_N;
    TCheckBox *chkRegsFlags_C;
    TLabeledEdit *lblRegsIM;
    TCheckBox *chkRegsInterrupts;
    TLabeledEdit *lblRegsTStates;
    TPanel *Panel4;
    TLabel *lblPortsFEdef;
    TLabel *lblPorts7FFDdef;
    TLabel *lblPorts1FFDdef;
    TLabeledEdit *lblPortsFE;
    TLabeledEdit *lblPorts7FFD;
    TLabeledEdit *lblPorts1FFD;
    TLabeledEdit *lblPorts3FFD;
    TLabeledEdit *lblPortsBFFD;
    TLabeledEdit *lblPortsFFFD;
    TImageList *imgDebugView;
    void __fastcall btnCollapseClick(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormMouseEnter(TObject *Sender);
    void __fastcall FormMouseLeave(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnHexClick(TObject *Sender);
    void __fastcall rad8bitClick(TObject *Sender);
    void __fastcall rad100pcClick(TObject *Sender);
    void __fastcall pgcRegistersDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active);
private:	// User declarations
//    enum eWindowState
//    {
//        wsNone,
//        wsResizing,
//        wsCollapsing
//    };

//    eWindowState    m_WindowState;
//    int             m_OldHeight;
    Z80             m_Context;
    int             m_TStates;
    TFont*          m_FontBlack;
    TFont*          m_FontRed;

//    void    __fastcall  SubClassWndProc(Messages::TMessage &Message);
    void    __fastcall  SetValue(TLabeledEdit* Label, WORD Value, bool CanBeSplit);
    void    __fastcall  SetValue(TLabeledEdit* Label, BYTE Value);
    void    __fastcall  UpdateView();

public:		// User declarations
            __fastcall  TfrmDebuggerStateView(TComponent* Owner);

    void    __fastcall  SetContext(const Z80& Context);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDebuggerStateView *frmDebuggerStateView;
//---------------------------------------------------------------------------
#endif
