//---------------------------------------------------------------------------

#ifndef fSetupWizardH
#define fSetupWizardH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmSetupWizard : public TForm
{
__published:	// IDE-managed Components
    TPanel *panMessageHeader;
    TLabel *lblMessageTitle;
    TLabel *lblShortMessage;
    TBevel *bvlMessageTop;
    TImage *imgMessageIcon;
    TImage *imgInformation;
    TPanel *panRed;
    TPanel *panYellow;
    TPanel *panGreen;
    TPanel *panCyan;
    TButton *cmdClose;
    TPanel *Panel1;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmSetupWizard(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSetupWizard *frmSetupWizard;
//---------------------------------------------------------------------------
#endif
