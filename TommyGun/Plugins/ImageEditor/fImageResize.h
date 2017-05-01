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
#ifndef fImageResizeH
#define fImageResizeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "KSpinEdit.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace Imaging;
    namespace ImageEditor
    {
        //---------------------------------------------------------------------------
        class TfrmImageResize : public TForm
        {
        __published:	// IDE-managed Components
            TGroupBox *grpDimensions;
            TLabel *lblNewWidth;
            TLabel *lblNewHeight;
            KSpinEdit *edtNewWidth;
            TLabel *lblCurrWidth;
            TLabel *lblCurrHeight;
            KSpinEdit *edtNewHeight;
            TLabel *lblCurrentWidth;
            TLabel *lblCurrentHeight;
            TGroupBox *grpImagePlacement;
            TPanel *panNewIndicator;
            TPanel *panCurIndicator;
            TGroupBox *grpHorizontalAlignment;
            TLabel *lblLeft;
            TLabel *lblRight;
            KSpinEdit *edtLeft;
            KSpinEdit *edtRight;
            TRadioButton *radHLeft;
            TRadioButton *radHCentre;
            TRadioButton *radHRight;
            TRadioButton *radHCustom;
            TGroupBox *grpVerticalAlignment;
            TLabel *lblTop;
            TLabel *lblBottom;
            KSpinEdit *edtTop;
            KSpinEdit *edtBottom;
            TRadioButton *radVTop;
            TRadioButton *radVCentre;
            TRadioButton *radVBottom;
            TRadioButton *radVCustom;
            TLabel *lblNewImageDimension;
            TLabel *lblExistingImageDimension;
            TGroupBox *grpImageRelationship;
            TPanel *panExampleArea;
            TPanel *panBotBox;
            TPanel *panTopBox;
            TLabel *lblNote;
    TButton *cmdOk;
    TButton *cmdCancel;
            void __fastcall edtLeftChange(TObject *Sender);
            void __fastcall edtRightChange(TObject *Sender);
            void __fastcall edtTopChange(TObject *Sender);
            void __fastcall edtBottomChange(TObject *Sender);
            void __fastcall radHLeftClick(TObject *Sender);
        private:	// User declarations
            void    __fastcall  Update(void);

            ZXImage*            m_pImage;
            bool                m_bNoUpdate;
            int                 m_iLeft;
            int                 m_iTop;
            int                 m_iWidth;
            int                 m_iHeight;

            void __fastcall     UpdateSliders(void);

        public:		// User declarations
                    __fastcall  TfrmImageResize(TComponent* Owner);
            bool    __fastcall  Execute(ZXImage* pImage);

            int     __property  Left   = { read = m_iLeft   };
            int     __property  Top    = { read = m_iTop    };
            int     __property  Width  = { read = m_iWidth  };
            int     __property  Height = { read = m_iHeight };
        };
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageEditor::TfrmImageResize *frmImageResize;
//---------------------------------------------------------------------------
#endif

