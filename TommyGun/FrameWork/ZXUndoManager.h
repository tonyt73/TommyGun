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
#ifndef ZXUndoManagerH
#define ZXUndoManagerH
//---------------------------------------------------------------------------
#include <vector>
#include "FrameWorkInterface.h"
#include "ZXUndoItem.h"
#include "fUndoList.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace GUI;
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GUI
    {
        //---------------------------------------------------------------------------
        class ZXUndoManager
        {
        private:
            typedef std::list<ZXUndoItem> ZXUndoVector;

        private:
            bool                    m_bUndoEnabled;
            bool                    m_bRedoEnabled;
            bool                    m_bInProgress;
            bool                    m_bGroupByPlugin;
            bool                    m_bAutoSwitchTo;                    
            bool                    m_bMemoryLimited;
            bool                    m_bEnableStackDialog;
            int                     m_iMemoryLimit;
            unsigned long           m_iMemoryUsed;              // memory used so far

            TAction*                m_UndoAction;
            TAction*                m_RedoAction;
            TAction*                m_ListAction;

            ZXUndoVector::iterator  m_UndoPos;      // current position in RUndo list
            ZXUndoVector::iterator  m_RedoPos;      // current position in redo list
            ZXUndoVector            m_UndoList;
            ZXUndoVector            m_RedoList;

            void    __fastcall  OnUndoExecute(TObject* Sender);
            void    __fastcall  OnRedoExecute(TObject* Sender);
            void    __fastcall  OnListExecute(TObject* Sender);
            void    __fastcall  UpdateActions(void);

        public:
                    __fastcall  ZXUndoManager();
                    __fastcall ~ZXUndoManager();

            void    __fastcall  Initialize(TAction* actUndo, TAction* actRedo, TAction* actUndoList);

            void    __fastcall  Add(const KXmlInfo* xmlUndo, ZXUndoType Type = utUndo);
            void    __fastcall  Undo(void);
            void    __fastcall  Redo(void);
            void    __fastcall  Clear(void);
            void    __fastcall  UpdateSettings(void);
            void    __fastcall  List(TStrings* StringList);
        };
    }
}
//---------------------------------------------------------------------------
extern Scorpio::GUI::ZXUndoManager g_UndoManager;
//---------------------------------------------------------------------------
#endif

