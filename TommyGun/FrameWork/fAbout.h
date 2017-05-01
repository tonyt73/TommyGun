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
#ifndef fAboutH
#define fAboutH
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
class TfrmAbout : public TForm
{
__published:	// IDE-managed Components
    TImage *imgTitle;
    TPanel *panButtons;
    TBevel *bvlLine;
    TButton *cmdOK;
    TLabel *lblVersion;
    TLabel *lblFreeware;
    TLabel *lblProgrammedBy;
    TLabel *lblSynEdit;
    TLabel *lblSuggestions;
    TLabel *lblEmail;
    TImage *imgClickMe;
    TPanel *panTitle;
    TLabel *lblFooodsIcons;
    TLabel *lblFooodWebSite;
    TImage *imgEMail;
    TLabel *lblAboutSynEdit;
    TImage *Image1;
    TLabel *lblWebsite;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TShape *Shape1;
    TLabel *Label5;
    void __fastcall lblEmailClick(TObject *Sender);
    void __fastcall lblWebsiteClick(TObject *Sender);
    void __fastcall lblSynEditClick(TObject *Sender);
    void __fastcall lblFooodWebSiteClick(TObject *Sender);
    void __fastcall Label2Click(TObject *Sender);
    void __fastcall Label4Click(TObject *Sender);
private:	// User declarations
    void __fastcall OpenLink(char* sLink);
public:		// User declarations
            __fastcall TfrmAbout(TComponent* Owner);
    void    __fastcall Execute(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
#endif
