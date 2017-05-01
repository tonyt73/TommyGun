//---------------------------------------------------------------------------
#ifndef CollisionDistanceH
#define CollisionDistanceH
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
        class CollisionDistance : public PropertyObject
        {
        private:
            int                 m_Distance;
            int                 m_PropertyNode;
            int                 m_DistanceNode;

        public:
                    __fastcall  CollisionDistance();
                    __fastcall ~CollisionDistance();

            void    __fastcall  Init();
            void    __fastcall  Update() {};
            void    __fastcall  UpdateProperties();
            // file
            bool    __fastcall  Load(KXmlInfo& xmlInfo);
            void    __fastcall  Save(KXmlInfo& xmlInfo);
            bool    __fastcall  IsDirty() { return true; }

            void    __fastcall  OnPropertyChanged(int node);
            void    __fastcall  OnPropertyRefresh() { }
        };
    }
}
//---------------------------------------------------------------------------
#endif
