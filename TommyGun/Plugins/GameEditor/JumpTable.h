//---------------------------------------------------------------------------
#ifndef JumpTableH
#define JumpTableH
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
//-- APP --------------------------------------------------------------------
#include "PropertyObject.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GameEditor
    {
        class JumpTable : public PropertyObject
        {
        private:
            TImage*             m_Window;
            bool                m_IsDirty;
            int                 m_Steps[22];
            int                 m_ActiveStep;
            int                 m_Ratio;
            int                 m_PropertyNode;

        public:
                    __fastcall  JumpTable();
                    __fastcall ~JumpTable();

            void    __fastcall  Init(TImage* window);
            void    __fastcall  SetRatio(int ratio) { if (m_Ratio != ratio) { m_Ratio = ratio; Update(); } }
            int     __fastcall  GetRatio()          { return m_Ratio;  }
            void    __fastcall  MouseDown(TShiftState Shift, int X, int Y);
            void    __fastcall  MouseMove(TShiftState Shift, int X, int Y);
            void    __fastcall  MouseWheel(int dY);
            void    __fastcall  Update();
            void    __fastcall  ResetDefaults();

            // file
            bool    __fastcall  Load(KXmlInfo& xmlInfo);
            void    __fastcall  Save(KXmlInfo& xmlInfo);
            bool    __fastcall  IsDirty() { return m_IsDirty; }

            void    __fastcall  OnPropertyChanged(int node) {}
            void    __fastcall  OnPropertyRefresh() { Update(); }
        };
    }
}
//---------------------------------------------------------------------------
#endif
