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
#ifndef fProblemsH
#define fProblemsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "KRegistry.h"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmProblems : public TForm
{
__published:	// IDE-managed Components
    TListView *lstProblems;
    KRegistry *regScorpio;
    TPanel *panContainer;
    TLabel *lblViewLog;
    TButton *cmdClose;
    TCheckBox *chkDonotShow;
    TPanel *panMessageHeader;
    TLabel *lblMessageTitle;
    TLabel *lblShortMessage;
    TBevel *bvlMessageTop;
    TImage *imgMessageIcon;
    TImage *imgWarning;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    void __fastcall lblViewLogClick(TObject *Sender);
    void __fastcall chkDonotShowClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmProblems(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmProblems *frmProblems;
//---------------------------------------------------------------------------
#endif
