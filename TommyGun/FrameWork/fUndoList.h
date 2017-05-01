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
#ifndef fUndoListH
#define fUndoListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmUndoList : public TForm
{
__published:    // IDE-managed Components
    TTimer      *tmrRefreshUndoList;
    TListView   *lstUndo;
    TPanel *panButtons;
    TButton *cmdUndo;
    TButton *cmdClose;
    TPanel *panTitle;
    TLabel *lblUndoSelection;
    void __fastcall cmdUndoClick(TObject *Sender);
    void __fastcall tmrRefreshUndoListTimer(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall cmdCloseClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall lstUndoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

private:    // User declarations
    TListItem*  firstItem_;
    TListItem*  lastItem_;
    bool        bSelecting_;

    void    __fastcall fillUndoList( void );
    void    __fastcall selectItems( void );

public:     // User declarations

            __fastcall TfrmUndoList(TComponent* Owner);
    void    __fastcall Execute( void );
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUndoList *frmUndoList;
//---------------------------------------------------------------------------
#endif
