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
#ifndef fGotoLineH
#define fGotoLineH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "KSpinEdit.h"
//---------------------------------------------------------------------------
class TfrmGotoLine : public TForm
{
__published:	// IDE-managed Components
    TButton *cmdOK;
    TButton *cmdCancel;
    TLabel *lblEnterNewLineNumber;
    TEdit *edtLineNumber;
    void __fastcall edtLineNumberChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmGotoLine(TComponent* Owner);

    int     __fastcall  Execute(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmGotoLine *frmGotoLine;
//---------------------------------------------------------------------------
#endif

