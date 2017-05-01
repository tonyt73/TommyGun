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
#ifndef fInsertResourceH
#define fInsertResourceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <StdActns.hpp>
#include <CheckLst.hpp>
#include "pngimage.hpp"
//---------------------------------------------------------------------------
class TfrmInsertResource : public TForm
{
__published:	// IDE-managed Components
    TPanel *panButtons;
    TBevel *bvlButtons;
    TButton *cmdInsert;
    TButton *cmdClose;
    TPanel *panMessageHeader;
    TLabel *lblMessageTitle;
    TLabel *lblShortMessage;
    TBevel *bvlMessageTop;
    TImage *imgInformation;
    TPanel *panRed;
    TPanel *panYellow;
    TPanel *panGreen;
    TPanel *panCyan;
    TPopupMenu *popSelection;
    TActionList *actResources;
    TEditSelectAll *actEditSelectAll;
    TMenuItem *popSelectAll;
    TMenuItem *popDeselectAll;
    TAction *actEditDeselectAll;
    TPanel *panLeft;
    TImage *imgStepOne;
    TImage *imgStepTwo;
    TGroupBox *grpResources;
    TCheckListBox *lstResources;
    TGroupBox *grpResourceType;
    TLabel *lblResourceParserDescription;
    TComboBox *cmbResourceType;
    TSplitter *splSplitter;
    TPanel *panClient;
    TImage *imgStepThree;
    TGroupBox *grpResourceOptions;
    TPanel *panResourceOptions;
    TLabel *lblNoParsers;
    TGroupBox *grpSourceCodeOptions;
    TRadioButton *chkCreateInEditor;
    TRadioButton *chkCreateInFile;
    TListBox *lstResourceParser;
    TImage *imgMessageIcon;
    void __fastcall cmdCloseClick(TObject *Sender);
    void __fastcall actEditSelectAllExecute(TObject *Sender);
    void __fastcall actEditDeselectAllExecute(TObject *Sender);
    void __fastcall lstResourcesClickCheck(TObject *Sender);
    void __fastcall splSplitterMoved(TObject *Sender);
    void __fastcall cmbResourceTypeChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmInsertResource(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif

