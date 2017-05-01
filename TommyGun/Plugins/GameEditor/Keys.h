//---------------------------------------------------------------------------
#ifndef KeysH
#define KeysH
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
        class Keys : public PropertyObject
        {
        private:
            TImage*             m_Image;
            TImage*             m_ImgKeys[7];
            int                 m_Keys[7];
            int                 m_HighlightX;
            int                 m_HighlightY;
            int                 m_HighlightKey;
            bool                m_IsDirty;
            int                 m_PropertyNode;

            int     __fastcall  FindHighlightKey(int X, int Y);
            void    __fastcall  DrawHighlightCursor();
            void    __fastcall  DrawHighlight(int X, int Y);
            void    __fastcall  LayoutKeys();

        public:
                    __fastcall  Keys();
                    __fastcall ~Keys();

            void    __fastcall  Init(TImage* image, TImage* k0, TImage* k1, TImage* k2, TImage* k3, TImage* k4, TImage* k5, TImage* k6);
            void    __fastcall  MouseMove(int X, int Y);
            void    __fastcall  KeyDown(WORD &Key);

            // file
            bool    __fastcall  Load(KXmlInfo& xmlInfo);
            void    __fastcall  Save(KXmlInfo& xmlInfo);
            bool    __fastcall  IsDirty() { return m_IsDirty; }

            void    __fastcall  OnPropertyChanged(int node);
            void    __fastcall  OnPropertyRefresh() { LayoutKeys(); }
        };
    }
}
//---------------------------------------------------------------------------
#endif
