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
#ifndef fSearchingH
#define fSearchingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmSearching : public TForm
{
__published:	// IDE-managed Components
    TLabel *lblSearchText;
    TLabel *lblFile;
    TButton *cmdClose;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmSearching(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSearching *frmSearching;
//---------------------------------------------------------------------------
#endif
