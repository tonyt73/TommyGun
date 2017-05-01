//---------------------------------------------------------------------------

#ifndef fChooseBuildFileH
#define fChooseBuildFileH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "pngimage.hpp"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmChooseBuildFile : public TForm
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
    TButton *cmdOK;
    TLabel *Label1;
    TComboBox *cmbFiles;
private:	// User declarations
public:		// User declarations
    __fastcall TfrmChooseBuildFile(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmChooseBuildFile *frmChooseBuildFile;
//---------------------------------------------------------------------------
#endif
