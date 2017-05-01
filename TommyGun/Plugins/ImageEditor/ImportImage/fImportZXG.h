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
#ifndef fImportZXGH
#define fImportZXGH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "pngimage.hpp"
//---------------------------------------------------------------------------
class TfrmImportZXG : public TForm
{
__published:	// IDE-managed Components
    TRadioButton *radImportAsTile;
    TRadioButton *radImportAsSprite;
    TLabel *lblDescription;
    TLabel *lblPleaseSelectType;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TBevel *Bevel1;
    TImage *imgInformation;
    TImage *Image1;
    TPanel *Panel10;
    TPanel *Panel11;
    TPanel *Panel12;
    TPanel *Panel13;
    TButton *cmdImport;
    TButton *cmdCancel;
private:	// User declarations
public:		// User declarations
            __fastcall TfrmImportZXG(TComponent* Owner);

    bool    __fastcall  Execute(void);
};
//---------------------------------------------------------------------------
#endif

