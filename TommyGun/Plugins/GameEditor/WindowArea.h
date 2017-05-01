//---------------------------------------------------------------------------
#ifndef WindowAreaH
#define WindowAreaH
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
        class WindowArea : public PropertyObject
        {
        private:
            enum Operation
            {   opNone,
                opMove,
                opSizeLeft, opSizeRight, opSizeTop, opSizeBottom,
                opSizeTopLeft, opSizeTopRight, opSizeBottomLeft, opSizeBottomRight
            };

            TRect               m_WindowRect;
            bool                m_IsDirty;
            TImage*             m_Layout;
            TImage*             m_Window;
            TImage*             m_Checkers;
            int                 m_Ratio;
            Operation           m_Operation;
            int                 m_PropertyNode;
            int                 m_PnLeft;
            int                 m_PnTop;
            int                 m_PnWidth;
            int                 m_PnHeight;

            int                 m_Mx;
            int                 m_My;
            bool                m_bMouseDown;
            int                 m_Wx;
            int                 m_Wy;
            int                 m_Sx;
            int                 m_Sy;

            void    __fastcall  SizeWindowLeft(int X, int Y);
            void    __fastcall  SizeWindowRight(int X, int Y);
            void    __fastcall  SizeWindowTop(int X, int Y);
            void    __fastcall  SizeWindowBottom(int X, int Y);


        public:
                    __fastcall  WindowArea();
                    __fastcall ~WindowArea();

            void    __fastcall  Init(TImage* layout, TImage* window, TImage* checkers);
            void    __fastcall  Update();
            void    __fastcall  UpdateProperties();
            void    __fastcall  SetRatio(int ratio) { if (m_Ratio != ratio) { m_Ratio = ratio; Update(); } }
            int     __fastcall  GetRatio()          { return m_Ratio;  }

            void    __fastcall  MoveWindow(int X, int Y);
            void    __fastcall  SizeWindow(int dX, int dY);
            void    __fastcall  MouseDown(TShiftState Shift, int X, int Y);
            void    __fastcall  MouseMove(TShiftState Shift, int X, int Y, int LX, int LY);
            void    __fastcall  MouseUp(TShiftState Shift, int X, int Y);
            bool    __fastcall  IsResized(int width, int height) { return m_WindowRect.Right != width || m_WindowRect.Bottom != height; }

            const TRect&
                    __fastcall  GetRect() const { return m_WindowRect; }

            // file
            bool    __fastcall  Load(KXmlInfo& xmlInfo);
            void    __fastcall  Save(KXmlInfo& xmlInfo);
            bool    __fastcall  IsDirty() { return m_IsDirty; }

            void    __fastcall  OnPropertyChanged(int node);
            void    __fastcall  OnPropertyRefresh() { Update(); }
        };
    }
}
//---------------------------------------------------------------------------
#endif
