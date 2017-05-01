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
#ifndef fPaletteChangeH
#define fPaletteChangeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmChangePalette : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grpNewPaletteType;
    TComboBox *cmbPalettes;
    TButton *cmdCancel;
    TButton *cmdOk;
private:	// User declarations
public:		// User declarations
            __fastcall  TfrmChangePalette(TComponent* Owner);

    bool    __fastcall  Execute(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmChangePalette *frmChangePalette;
//---------------------------------------------------------------------------
#endif

