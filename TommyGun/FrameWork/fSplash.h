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
#ifndef fSplashH
#define fSplashH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
#include "pngimage.hpp"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GUI
    {
        class TfrmSplash : public TForm
        {
        __published:	// IDE-managed Components
            TImage *imgSplash;
            void __fastcall FormCreate(TObject *Sender);
        private:	// User declarations
        public:		// User declarations
            __fastcall TfrmSplash(TComponent* Owner);
        };
    }
}
//---------------------------------------------------------------------------
#endif
