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
#ifndef fRenameProjectH
#define fRenameProjectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "pngimage.hpp"
//---------------------------------------------------------------------------
class TfrmRenameProject : public TForm
{
__published:	// IDE-managed Components
    TPanel *panMessageHeader;
    TLabel *lblMessageTitle;
    TBevel *bvlMessageTop;
    TImage *imgInformation;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TPanel *panButtons;
    TButton *cmdCancel;
    TButton *cmdOK;
    TLabel *lblShortMessage;
    TLabel *Label1;
    TLabel *lblOldName;
    TLabel *Label2;
    TEdit *edtNewName;
    TBevel *Bevel1;
    TLabel *Label3;
    TImage *imgMessageIcon;
    void __fastcall edtNewNameChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
            __fastcall  TfrmRenameProject(TComponent* Owner);

    bool    __fastcall  Execute(String sOldName);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRenameProject *frmRenameProject;
//---------------------------------------------------------------------------
#endif

