//---------------------------------------------------------------------------

#ifndef frmBreakpointPropertiesH
#define frmBreakpointPropertiesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "KSpinEdit.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "pch.h"
#include "ZXFileManager.h"
#include "ZXBreakpointManager.h"
//---------------------------------------------------------------------------
class TfrmBreakpointProperties : public TForm
{
__published:	// IDE-managed Components
    TButton *btnCancel;
    TButton *btnOk;
    TLabel *Label1;
    TComboBox *cmbFiles;
    TLabel *Label2;
    KSpinEdit *spnLine;
    KSpinEdit *spnPassCount;
    TLabel *Label3;
    void __fastcall cmbFilesChange(TObject *Sender);
private:	// User declarations
    ZXFileManager* m_fileManager;
public:		// User declarations
            __fastcall  TfrmBreakpointProperties(TComponent* Owner);

    bool    __fastcall  Execute(bool PropertiesOrAdd, TBreakpoint& breakpoint, ZXFileManager& fileManager);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBreakpointProperties *frmBreakpointProperties;
//---------------------------------------------------------------------------
#endif
