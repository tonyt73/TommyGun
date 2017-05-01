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
#ifndef fImageMaskH
#define fImageMaskH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "ZXPalette.h"
#include <Graphics.hpp>
//---------------------------------------------------------------------------
enum TMaskBorderStyle   { mbsNone, mbsStar, mbsSquare };
//---------------------------------------------------------------------------
class TfrmImageMask : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grpBorderStyle;
    TRadioButton *radBorderStyleStar;
    TRadioButton *radBorderStyleNone;
    TGroupBox *grpColour;
    //TColorComboBox *cmbColors;
    TImage *imgNone;
    TImage *imgStar;
    TRadioButton *radBorderStyleSquare;
    TImage *imgSquare;
    TButton *cmdOk;
    TButton *cmdCancel;
    void __fastcall radBorderStyleNoneClick(TObject *Sender);
    void __fastcall radBorderStyleStarClick(TObject *Sender);
    void __fastcall radBorderStyleSquareClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
            TMaskBorderStyle    m_bBorderStyle;
            __fastcall TfrmImageMask(TComponent* Owner);
    bool    __fastcall Execute(ZXPalette* pPalette);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmImageMask *frmImageMask;
//---------------------------------------------------------------------------
#endif

