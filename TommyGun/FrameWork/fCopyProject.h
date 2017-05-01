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
#ifndef fCopyProjectH
#define fCopyProjectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "pngimage.hpp"
//---------------------------------------------------------------------------
class TfrmCopyProject : public TForm
{
__published:	// IDE-managed Components
    TPanel *panMessageHeader;
    TLabel *lblMessageTitle;
    TBevel *bvlMessageTop;
    TImage *imgMessageIcon;
    TImage *imgInformation;
    TLabel *lblShortMessage;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TPanel *panButtons;
    TBevel *Bevel1;
    TButton *cmdCancel;
    TButton *cmdOK;
    TLabel *lblOldName;
    TLabel *Label3;
    TLabel *Label2;
    TLabel *Label1;
    TEdit *edtNewName;
    void __fastcall edtNewNameChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
            __fastcall  TfrmCopyProject(TComponent* Owner);
            
    bool    __fastcall  Execute(String sOldName);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCopyProject *frmCopyProject;
//---------------------------------------------------------------------------
#endif

