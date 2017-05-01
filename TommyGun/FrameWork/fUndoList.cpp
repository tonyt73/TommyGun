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
#include <vcl.h>
#pragma hdrstop
#include "fUndoList.h"
#include "fMain.h"
#include "ZXUndoManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmUndoList *frmUndoList = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmUndoList::TfrmUndoList(TComponent* Owner)
: TForm      ( Owner )
, firstItem_ ( NULL  )
, lastItem_  ( NULL  )
, bSelecting_( false )
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::Execute( void )
{
    fillUndoList( );
    Show( );
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::cmdUndoClick(TObject *Sender)
{
    if ( cmdUndo->Caption == "Undo" )
    {
        for ( int i = firstItem_->Index; i <= lastItem_->Index; i++ )
        {
            g_UndoManager.Undo( );
        }
    }
    else
    {
        if ( firstItem_ == NULL )
        {
            for ( int i = lastItem_->Index; i < lstUndo->Items->Count; i++ )
            {
                g_UndoManager.Redo( );
            }
        }
        else
        {
            for ( int i = lastItem_->Index; i < firstItem_->Index; i++ )
            {
                g_UndoManager.Redo( );
            }
        }
    }
    fillUndoList( );
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::fillUndoList( void )
{
    if ( !ComponentState.Contains( csDestroying ) )
    {
        TStringList* list = new TStringList();
        AnsiString op;
        AnsiString desc;
        AnsiString plugin;
        firstItem_ = NULL;
        g_UndoManager.List( list );
        if ( list->Count )
        {
            cmdUndo->Enabled = true;
            if ( lastItem_ != NULL && list->Count < lastItem_->Index )
            {
                lastItem_ = NULL;
            }
            for ( int i = 0; i < list->Count; i++ )
            {
                int iPos = list->Strings[i].Pos("|");
                int iLen = list->Strings[i].Length();
                if (iPos)
                {
                    plugin = list->Strings[i].SubString( 2, iPos - 2 );
                    desc   = list->Strings[i].SubString( iPos + 1, iLen);
                }
                else
                {
                    plugin = "Unknown";
                    desc = list->Strings[i].SubString( 2, iLen );
                }
                op = "Undo";
                if ( list->Strings[i][1] == 'R' )
                {
                    op = "Redo";
                }

                if ( i < lstUndo->Items->Count )
                {
                    TListItem* item = lstUndo->Items->Item[i];
                    item->Caption = op;
                    item->SubItems->Strings[0] = plugin;
                    item->SubItems->Strings[1] = desc;
                    if ( firstItem_ == NULL && op == "Undo" )
                    {
                        firstItem_ = item;
                    }
                }
                else
                {
                    // add a new item
                    TListItem* item = lstUndo->Items->Add();
                    item->Caption = op;
                    item->SubItems->Add( plugin );
                    item->SubItems->Add( desc );
                    if ( firstItem_ == NULL && op == "Undo" )
                    {
                        firstItem_ = item;
                    }
                }
            }
            // clear the unused items
            if ( list->Count < lstUndo->Items->Count )
            {
                for ( int i = list->Count; i < lstUndo->Items->Count; i++ )
                {
                    lstUndo->Items->Delete(i);
                }
            }
            selectItems( );
        }
        else
        {
            // clear the unused items
            for ( int i = 0; i < lstUndo->Items->Count; i++ )
            {
                lstUndo->Items->Delete(i);
            }
            cmdUndo->Enabled = false;
        }
        SAFE_DELETE(list);
    }
    cmdUndo->Enabled = lstUndo->SelCount > 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::tmrRefreshUndoListTimer(TObject *Sender)
{
    fillUndoList( );
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::FormShow(TObject *Sender)
{
    fillUndoList( );
    tmrRefreshUndoList->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::FormHide(TObject *Sender)
{
    tmrRefreshUndoList->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::FormClose(TObject *Sender, TCloseAction &Action)
{
    tmrRefreshUndoList->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::cmdCloseClick(TObject *Sender)
{
    Close( );
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::FormCreate(TObject *Sender)
{
    lstUndo->DoubleBuffered = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::selectItems( void )
{
    if ( !ComponentState.Contains( csDestroying ) )
    {
        bSelecting_ = true;
        if ( lastItem_ != NULL )//&& lastItem_ != firstItem_ )
        {
            // unselect all
            for ( int i = 0; i < lstUndo->Items->Count; i++ )
            {
                lstUndo->Items->Item[i]->Selected = false;
            }
            // select the operations
            if ( firstItem_ == NULL )
            {
                // all redos
                lstUndo->Selected = lastItem_;
                for ( int i = lastItem_->Index; i < lstUndo->Items->Count; i++ )
                {
                    lstUndo->Items->Item[i]->Selected = true;
                }
                cmdUndo->Caption = "Redo";
            }
            else
            {
                //lstUndo->Selected = firstItem_;
                if ( lastItem_->Index < firstItem_->Index )
                {
                    // redo
                    lstUndo->Selected = lastItem_;
                    for ( int i = lastItem_->Index; i < firstItem_->Index; i++ )
                    {
                        lstUndo->Items->Item[i]->Selected = true;
                    }
                    cmdUndo->Caption = "Redo";
                }
                else
                {
                    // undo
                    lstUndo->Selected = firstItem_;
                    for ( int i = firstItem_->Index; i <= lastItem_->Index; i++ )
                    {
                        lstUndo->Items->Item[i]->Selected = true;
                    }
                    cmdUndo->Caption = "Undo";
                }
            }
        }
        bSelecting_ = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmUndoList::lstUndoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if ( !bSelecting_ )
    {
        lastItem_ = lstUndo->GetItemAt( X, Y );
        selectItems( );
        cmdUndo->Enabled = lstUndo->SelCount > 0;
    }
}
//---------------------------------------------------------------------------
