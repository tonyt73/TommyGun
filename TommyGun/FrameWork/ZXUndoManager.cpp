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
#include "pch.h"
#pragma hdrstop
#include <algorithm>
#include "ZXTabs.h"
#include "ZXLogFile.h"
#include "ZXGUIManager.h"
#include "ZXPluginManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace Logging;
using namespace GUI;
//---------------------------------------------------------------------------
__fastcall ZXUndoManager::ZXUndoManager()
: m_bUndoEnabled(true)
, m_bRedoEnabled(true)
, m_bInProgress(false)
, m_bGroupByPlugin(false)
, m_bAutoSwitchTo(true)
, m_bMemoryLimited(true)
, m_bEnableStackDialog(true)
, m_iMemoryLimit(16)
, m_iMemoryUsed(0)
, m_UndoAction(NULL)
, m_RedoAction(NULL)
, m_ListAction(NULL)
{
    m_UndoPos = m_UndoList.begin();
    m_RedoPos = m_RedoList.begin();
}
//---------------------------------------------------------------------------
__fastcall ZXUndoManager::~ZXUndoManager()
{
    SAFE_DELETE(frmUndoList);
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::Initialize(TAction* actUndo, TAction* actRedo, TAction* actList)
{
    m_UndoAction = actUndo;
    m_RedoAction = actRedo;
    m_ListAction = actList;

    actUndo->OnExecute = OnUndoExecute;
    actRedo->OnExecute = OnRedoExecute;
    actList->OnExecute = OnListExecute;
    actList->Enabled   = true;

    frmUndoList = new TfrmUndoList(NULL);

    UpdateSettings();
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::Undo(void)
{
    m_bInProgress = true;
    if (m_bUndoEnabled && m_UndoList.size() && m_UndoPos != m_UndoList.end())
    {
        (*m_UndoPos).Restore();
        m_UndoPos++;
        m_RedoPos++;
    }
    m_bInProgress = false;
    UpdateActions();
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::Redo(void)
{
    m_bInProgress = true;
    if (m_bRedoEnabled && m_RedoList.size() && m_RedoPos != m_RedoList.begin())
    {
        m_UndoPos--;
        m_RedoPos--;
        (*m_RedoPos).Restore();
    }
    m_bInProgress = false;
    UpdateActions();
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::List(TStrings* StringList)
{
    StringList->Clear();
    AnsiString sDesc;
    if (m_bRedoEnabled && m_RedoList.size())//&& m_RedoPos != m_RedoList.begin())
    {
        ZXUndoVector::iterator it = m_RedoList.begin();
        while (it != m_RedoPos)
        {
            // show only the unlinked items
            sDesc = "R" + (*it).Plugin + "|" + (*it).Description;
            StringList->Add(sDesc);
            it++;
        }
    }
    if (m_bUndoEnabled && m_UndoList.size())//&& m_UndoPos != m_UndoList.end())
    {
        ZXUndoVector::iterator it = m_UndoPos;
        while (it != m_UndoList.end())
        {
            // show only the unlinked items
            sDesc = "U" + (*it).Plugin + "|" + (*it).Description;
            StringList->Add(sDesc);
            it++;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::UpdateSettings(void)
{
    bool bUndoEnabled   = m_bUndoEnabled;
    bool bRedoEnabled   = m_bRedoEnabled;
    bool bMemoryLimited = m_bMemoryLimited;
    bool bAutoSwitchTo  = m_bAutoSwitchTo;
    bool bGroupByPlugin = m_bGroupByPlugin;
    int  iMemoryLimit   = m_iMemoryLimit;

    g_GuiManager.Registry()->Read("Undo", "EnableUndo"        , m_bUndoEnabled      );
    g_GuiManager.Registry()->Read("Undo", "EnabledRedo"       , m_bRedoEnabled      );
    g_GuiManager.Registry()->Read("Undo", "EnableMemoryLimit" , m_bMemoryLimited    );
    g_GuiManager.Registry()->Read("Undo", "MemoryLimit"       , m_iMemoryLimit      );
    g_GuiManager.Registry()->Read("Undo", "GroupByPlugin"     , m_bGroupByPlugin    );
    g_GuiManager.Registry()->Read("Undo", "AutoSwitchToPlugin", m_bAutoSwitchTo     );
    g_GuiManager.Registry()->Read("Undo", "EnableStackDialog" , m_bEnableStackDialog);

    m_ListAction->Visible = m_bEnableStackDialog;

    if (bUndoEnabled != m_bUndoEnabled || bRedoEnabled != m_bRedoEnabled || bGroupByPlugin != m_bGroupByPlugin)
    {
        // need to clear the history
        Clear();
    }
    UpdateActions();
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::OnUndoExecute(TObject* Sender)
{
    Undo();
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::OnRedoExecute(TObject* Sender)
{
    Redo();
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::OnListExecute(TObject* Sender)
{
    if (true == SAFE_PTR(frmUndoList))
    {
        frmUndoList->Show();
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::Clear(void)
{
    m_UndoList.clear();
    m_RedoList.clear();
    m_UndoPos = m_UndoList.begin();
    m_RedoPos = m_RedoList.begin();
    m_iMemoryUsed = 0;
    UpdateActions();
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::Add(const KXmlInfo* xmlUndo, ZXUndoType Type)
{
    static bool bLastRedo = true;
    if (m_bUndoEnabled)
    {
        bool bProcessOperation = true;
        ZXUndoVector::iterator it = m_UndoList.begin();
        ZXUndoVector::iterator rt = m_RedoList.begin();
        if (bLastRedo == (Type == utRedo) && m_bRedoEnabled)
        {
            // we have an unbalanced operation here
            // ie. 2 undos or 2 redos in a row.
            // the undo stack is always either equal or 1 greater than the redo stack
            if (Type == utRedo && m_RedoList.size() == m_UndoList.size())
            {
                // the matching undo data for this redo is missing so ignore the data
                bProcessOperation = false;
            }
            if (Type == utUndo && m_UndoList.size() >= m_RedoList.size() + 1)
            {
                // the undo list will grow to be greater than the redo list
                // this means we have missed the matching redo for the last undo
                // we have to delete the last undo operation
                bProcessOperation = false;
            }
        }
        if (bProcessOperation)
        {
            // create the undo information block
            it = m_UndoList.begin();
            rt = m_RedoList.begin();
             // erase the end of the list if its got data in it
            if (m_UndoPos != m_UndoList.begin())
            {
                // pop all elements until we reach the current pos
                while (it != m_UndoPos)
                {
                    // pop the undo data
                    m_iMemoryUsed -= (*it).Size;
                    m_UndoList.pop_front();
                    it = m_UndoList.begin();

                    // pop the redo data
                    if (m_bRedoEnabled && m_RedoList.size())
                    {
                        m_iMemoryUsed -= (*rt).Size;
                        m_RedoList.pop_front();
                        rt = m_RedoList.begin();
                    }
                }
            }
            // push the data onto the end of the right list
            if (Type == utUndo)
            {
                // add the undo data
                m_UndoList.push_front(ZXUndoItem(*xmlUndo));
                m_UndoPos = m_UndoList.begin();
            }
            else if (Type == utRedo)
            {
                // add the redo data
                m_RedoList.push_front(ZXUndoItem(*xmlUndo));
                m_RedoPos = m_RedoList.begin();
            }
        }
    }
    bLastRedo = (Type == utRedo);
    UpdateActions();
}
//---------------------------------------------------------------------------
void __fastcall ZXUndoManager::UpdateActions(void)
{
    if (true == SAFE_PTR(m_UndoAction))
    {
        m_UndoAction->Enabled = m_bUndoEnabled && m_UndoList.size() && m_UndoPos != m_UndoList.end();
        m_ListAction->Enabled = m_bUndoEnabled;
    }
    if (true == SAFE_PTR(m_RedoAction))
    {
        m_RedoAction->Enabled = m_bRedoEnabled && m_RedoPos != m_RedoList.begin();
    }
}
//---------------------------------------------------------------------------

