/*---------------------------------------------------------------------------

    (c) 2004 Scorpio Software
        19 Wittama Drive
        Glenmore Park
        Sydney NSW 2745
        Australia

-----------------------------------------------------------------------------

    $Workfile::                                                           $
    $Revision::                                                           $
        $Date::                                                           $
      $Author::                                                           $

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef fStringDlgH
#define fStringDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmStringDlg : public TForm
{
__published:	// IDE-managed Components
    TPanel *panButtons;
    TButton *cmdOk;
    TButton *cmdCancel;
    TLabel *lblID;
    TEdit *edtID;
    TLabel *lblValue;
    TMemo *memoValue;
    TGroupBox *grpStringInformaton;
    TLabel *lblNote;
    void __fastcall edtIDChange(TObject *Sender);
    void __fastcall memoValueKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
            __fastcall  TfrmStringDlg(TComponent* Owner);
    bool    __fastcall  Execute(bool bAdd, const String& sID, const String& sValue);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStringDlg *frmStringDlg;
//---------------------------------------------------------------------------
#endif

