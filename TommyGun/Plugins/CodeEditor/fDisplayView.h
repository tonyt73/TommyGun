//---------------------------------------------------------------------------
#ifndef fDisplayViewH
#define fDisplayViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfrmDisplayView : public TForm
{
__published:	// IDE-managed Components
    TPanel *panMainDisplayBlack;
    TPanel *panMainDisplayWhite;
    TImage *imgMainDisplay;
    TPopupMenu *popSVOptions;
    TMenuItem *popSVNormalSize;
    TMenuItem *popSVDoubleSize;
    TMenuItem *popSVTripleSize;
    TMenuItem *popSVLine00;
    TMenuItem *popSVShowAttributes;
    TMenuItem *popTranslucent;
    TMenuItem *popBlackOnWhite;
    TMenuItem *popWhiteOnBlack;
    void __fastcall panMainDisplayWhiteResize(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall popSVNormalSizeClick(TObject *Sender);
    void __fastcall popSVDoubleSizeClick(TObject *Sender);
    void __fastcall popSVTripleSizeClick(TObject *Sender);
    void __fastcall popSVShowAttributesClick(TObject *Sender);
    void __fastcall FormMouseEnter(TObject *Sender);
    void __fastcall FormMouseLeave(TObject *Sender);
    void __fastcall popTranslucentClick(TObject *Sender);
    void __fastcall popBlackOnWhiteClick(TObject *Sender);
private:	// User declarations
//    void    __fastcall  SubClassWndProc(Messages::TMessage &Message);
    bool            m_Initializing;
public:		// User declarations
    __fastcall TfrmDisplayView(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDisplayView *frmDisplayView;
//---------------------------------------------------------------------------
#endif
