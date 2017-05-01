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
#ifndef fRestoreProjectH
#define fRestoreProjectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include "pngimage.hpp"
#include <vector>
//---------------------------------------------------------------------------
typedef struct
{
    TDateTime dtDate;
    int   iFiles;
    int   iSize;
} ZXRestoreItem;
typedef std::vector<ZXRestoreItem>  ZXRestoreItems;
//---------------------------------------------------------------------------
class TfrmRestoreProject : public TForm
{
__published:	// IDE-managed Components
    TPanel *panMessageHeader;
    TLabel *lblMessageTitle;
    TBevel *bvlMessageTop;
    TImage *imgInformation;
    TLabel *lblShortMessage;
    TPanel *panRed;
    TPanel *panYellow;
    TPanel *panGreen;
    TPanel *panCyan;
    TPanel *panButtons;
    TBevel *bvlLine01;
    TButton *cmdCancel;
    TButton *cmdOK;
    TListView *lstBackups;
    TLabel *lblProjectName;
    TPanel *panProjectName;
    TImage *imgMessageIcon;
    void __fastcall lstBackupsClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
            __fastcall TfrmRestoreProject(TComponent* Owner);

    int     __fastcall  Execute(const String& sName, ZXRestoreItems& vItems);
};
//---------------------------------------------------------------------------
#endif

