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
#ifndef fComfirmReplaceH
#define fComfirmReplaceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmConfirmReplace : public TForm
{
__published:	// IDE-managed Components
    TImage *lblIcon;
    TLabel *lblConfirmation;
    TButton *btnReplace;
    TButton *btnSkip;
    TButton *btnCancel;
    TButton *btnReplaceAll;
private:	// User declarations
public:		// User declarations
            __fastcall  TfrmConfirmReplace(TComponent* Owner);

    bool    __fastcall  Execute(TRect AEditorRect, int X, int Y1, int Y2, const String& AReplaceText);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConfirmReplace *frmConfirmReplace;
//---------------------------------------------------------------------------
#endif
