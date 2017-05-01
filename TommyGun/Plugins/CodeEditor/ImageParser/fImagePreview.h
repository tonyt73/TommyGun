//---------------------------------------------------------------------------

#ifndef fImagePreviewH
#define fImagePreviewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TGroupBoxUnit.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmPreview : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TfrmPreview(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPreview *frmPreview;
//---------------------------------------------------------------------------
#endif

