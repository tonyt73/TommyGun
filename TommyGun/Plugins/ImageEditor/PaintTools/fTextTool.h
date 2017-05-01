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
#ifndef fTextToolH
#define fTextToolH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include "KSlider.h"
#include "KSpinEdit.h"
//---------------------------------------------------------------------------
#include "..\ZXImage.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace PaintTools
    {
        //---------------------------------------------------------------------------
        class TfrmTextDialog : public TForm
        {
        __published:	// IDE-managed Components
            TGroupBox *grpFont;
            TGroupBox *grpPreview;
            TEdit *edtText;
            TLabel *lblFont;
            TLabel *lblMagnification;
            KSlider *slrMagnification;
    KSpinEdit *edtMagnification;
            TLabel *lblFontName;
            TButton *cmdFont;
            TLabel *lblSize;
            TFontDialog *dlgFont;
            TLabel *lblSample;
            TLabel *lblFontSample;
            TLabel *lblFontSize;
            TScrollBox *sbxImagePreview;
            TImage *imgPreview;
    TCheckBox *chkAutoUpdate;
    TButton *cmdOK;
    TButton *cmdCancel;
            void __fastcall cmdFontClick(TObject *Sender);
            void __fastcall dlgFontApply(TObject *Sender, HWND Wnd);
            void __fastcall slrMagnificationChange(TObject *Sender);
    void __fastcall chkAutoUpdateClick(TObject *Sender);
    void __fastcall edtMagnificationChange(TObject *Sender);
        private:	// User declarations
            ZXImage*    m_Image;
            int         m_iX;
            int         m_iY;

            void    __fastcall UpdatePreview(void);

        public:		// User declarations
                    __fastcall TfrmTextDialog(TComponent* Owner);

            bool    __fastcall Execute(int X, int Y, ZXImage* Image);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::PaintTools::TfrmTextDialog *frmTextDialog;
//---------------------------------------------------------------------------
#endif
