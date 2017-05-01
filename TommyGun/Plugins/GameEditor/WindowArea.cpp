//---------------------------------------------------------------------------
#pragma hdrstop
#include "pch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GameEditor;
//---------------------------------------------------------------------------
__fastcall WindowArea::WindowArea()
: m_WindowRect(8,4,24,16)
, m_IsDirty(false)
, m_Layout(NULL)
, m_Window(NULL)
, m_Checkers(NULL)
, m_Ratio(1)
, m_Operation(opNone)
, m_PropertyNode(-1)
{
}
//---------------------------------------------------------------------------
__fastcall WindowArea::~WindowArea()
{
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::Init(TImage* layout, TImage* window, TImage* checkers)
{
    m_Layout   = layout;
    m_Window   = window;
    m_Checkers = checkers;
    m_PropertyNode = frmGameEditor->GetPropertyEditor().AddRootNode(this, "Window Area", tviWindow);
    m_PnLeft = frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Left", (int)m_WindowRect.Left);
    m_PnTop = frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Top", (int)m_WindowRect.Top);
    m_PnWidth = frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Width", (int)m_WindowRect.Right);
    m_PnHeight = frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Height", (int)m_WindowRect.Bottom);
    Update();
}
//---------------------------------------------------------------------------
bool __fastcall WindowArea::Load(KXmlInfo& xmlInfo)
{
    bool bLoaded = false;
    KXmlInfo* AreaNode;
    if (xmlInfo.Find(AreaNode, "WindowArea", 0))
    {
        KXmlInfo* nValue = AreaNode->GetNode("Left", 0);
        if (nValue) m_WindowRect.left = std::min(32-7, std::max(0, nValue->GetInt()));
        nValue = AreaNode->GetNode("Top", 0);
        if (nValue) m_WindowRect.top = std::min(24-7, std::max(0, nValue->GetInt()));
        nValue = AreaNode->GetNode("Width", 0);
        if (nValue) m_WindowRect.right = std::min(32, std::max(7, nValue->GetInt()));
        nValue = AreaNode->GetNode("Height", 0);
        if (nValue) m_WindowRect.bottom = std::min(24, std::max(7, nValue->GetInt()));
        bLoaded = true;
        Update();
        UpdateProperties();
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo* Node;
    if (xmlInfo.Find(Node, "WindowArea", 0))
    {
        xmlInfo.Remove(Node);
    }
    // create a new map editor node
    KXmlInfo area("WindowArea");
    // store the map details
    area.Add("Left", m_WindowRect.left);
    area.Add("Top", m_WindowRect.top);
    area.Add("Width", m_WindowRect.right);
    area.Add("Height", m_WindowRect.bottom);
    xmlInfo.Add(area);
    m_IsDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::Update()
{
    m_Window->Picture->Bitmap->Width  = m_WindowRect.right  * 8;
    m_Window->Picture->Bitmap->Height = m_WindowRect.bottom * 8;
    BitBlt(m_Window->Picture->Bitmap->Canvas->Handle, 0, 0, m_Checkers->Picture->Bitmap->Width, m_Checkers->Picture->Bitmap->Height, m_Checkers->Picture->Bitmap->Canvas->Handle, 0, 0, SRCCOPY);

    m_Window->Left   = (m_WindowRect.left   * 8) * m_Ratio;
    m_Window->Top    = (m_WindowRect.top    * 8) * m_Ratio;
    m_Window->Width  = (m_WindowRect.right  * 8) * m_Ratio;
    m_Window->Height = (m_WindowRect.bottom * 8) * m_Ratio;
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::UpdateProperties()
{
    frmGameEditor->GetPropertyEditor().UpdateProperty(m_PropertyNode, m_PnLeft, (int)m_WindowRect.Left);
    frmGameEditor->GetPropertyEditor().UpdateProperty(m_PropertyNode, m_PnTop, (int)m_WindowRect.Top);
    frmGameEditor->GetPropertyEditor().UpdateProperty(m_PropertyNode, m_PnWidth, (int)m_WindowRect.Right);
    frmGameEditor->GetPropertyEditor().UpdateProperty(m_PropertyNode, m_PnHeight, (int)m_WindowRect.Bottom);
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::MoveWindow(int X, int Y)
{
    int nx = std::max(0, std::min(X, m_Layout->Width  - m_Window->Width ));
    int ny = std::max(0, std::min(Y, m_Layout->Height - m_Window->Height));

    m_Window->Left = nx;
    m_Window->Top  = ny;
    m_WindowRect.left = m_Window->Left / (m_Ratio * 8);
    m_WindowRect.top  = m_Window->Top  / (m_Ratio * 8);
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::SizeWindowLeft(int X, int Y)
{
    int modRatio = m_Ratio * 8;
    int dx = X - m_Mx;
    dx -= (dx % modRatio);
    int w = (m_Sx - dx) / modRatio;
    if (m_Wx + dx >= 0 && w > 4)
    {
        m_Window->Left = m_Wx + dx;
        m_Window->Width = m_Sx - dx;
        m_WindowRect.left  = m_Window->Left / modRatio;
        m_WindowRect.right = m_Window->Width / modRatio;
    }
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::SizeWindowRight(int X, int Y)
{
    int modRatio = m_Ratio * 8;
    int dx = m_Mx - X;
    dx -= (dx % modRatio);
    int w = (m_Sx - dx) / modRatio;
    if ((m_Wx + m_Sx - dx) <= m_Layout->Width && w >= 7)
    {
        m_Window->Width = m_Sx - dx;
        m_WindowRect.right = m_Window->Width / modRatio;
    }
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::SizeWindowTop(int X, int Y)
{
    int modRatio = m_Ratio * 8;
    int dy = Y - m_My;
    dy -= (dy % modRatio);
    int h = (m_Sy - dy) / modRatio;
    if (m_Wy + dy >= 0 && h > 4)
    {
        m_Window->Top = m_Wy + dy;
        m_Window->Height = m_Sy - dy;
        m_WindowRect.top = m_Window->Top / modRatio;
        m_WindowRect.bottom = m_Window->Height / modRatio;
    }
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::SizeWindowBottom(int X, int Y)
{
    int modRatio = m_Ratio * 8;
    int dy = m_My - Y;
    dy -= (dy % modRatio);
    int h = (m_Sy - dy) / modRatio;
    if ((m_Wy + m_Sy - dy) <= m_Layout->Height && h >= 7)
    {
        m_Window->Height = m_Sy - dy;
        m_WindowRect.bottom = m_Window->Height / modRatio;
    }
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::SizeWindow(int X, int Y)
{
    m_WindowRect.Right = X;
    m_WindowRect.Bottom = Y;
    Update();
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::MouseDown(TShiftState Shift, int X, int Y)
{
    if (!m_bMouseDown && Shift.Contains(ssLeft))
    {
        m_Mx = X;
        m_My = Y;
        m_Wx = m_Window->Left;
        m_Wy = m_Window->Top;
        m_Sx = m_Window->Width;
        m_Sy = m_Window->Height;
        m_bMouseDown = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::MouseMove(TShiftState Shift, int X, int Y, int LX, int LY)
{
    int modRatio = m_Ratio * 8;
    if (!m_bMouseDown)
    {
        if (LX < modRatio)
        {
            m_Operation = opSizeLeft;
            m_Window->Cursor = crSizeWE;
            if (LY < modRatio)
            {
                m_Operation = opSizeTopLeft;
                m_Window->Cursor = crSizeNWSE;
            }
            else if (LY > m_Window->Height - modRatio)
            {
                m_Operation = opSizeBottomLeft;
                m_Window->Cursor = crSizeNESW;
            }
        }
        else if (LY < modRatio)
        {
            m_Operation = opSizeTop;
            m_Window->Cursor = crSizeNS;
            if (LX < modRatio)
            {
                m_Operation = opSizeTopLeft;
                m_Window->Cursor = crSizeNESW;
            }
            else if (LX > m_Window->Width - modRatio)
            {
                m_Operation = opSizeTopRight;
                m_Window->Cursor = crSizeNESW;
            }
        }
        else if (LX > m_Window->Width - modRatio)
        {
            m_Operation = opSizeRight;
            m_Window->Cursor = crSizeWE;
            if (LY < (8 * m_Ratio))
            {
                m_Operation = opSizeTopRight;
                m_Window->Cursor = crSizeNESW;
            }
            else if (LY > m_Window->Height - modRatio)
            {
                m_Operation = opSizeBottomRight;
                m_Window->Cursor = crSizeNWSE;
            }
        }
        else if (LY > m_Window->Height - modRatio)
        {
            m_Operation = opSizeBottom;
            m_Window->Cursor = crSizeNS;
            if (LX < modRatio)
            {
                m_Operation = opSizeBottomLeft;
                m_Window->Cursor = crSizeNESW;
            }
            else if (LX > m_Window->Width - modRatio)
            {
                m_Operation = opSizeBottomRight;
                m_Window->Cursor = crSizeNWSE;
            }
        }
        else
        {
            m_Operation = opMove;
            m_Window->Cursor = crSizeAll;
        }
    }
    else
    {
        if (Shift.Contains(ssLeft))
        {
            // move the window
            switch(m_Operation)
            {
                case opMove:
                {
                    int dx = X - m_Mx;
                    int dy = Y - m_My;
                    dx -= (dx % modRatio);
                    dy -= (dy % modRatio);
                    MoveWindow(m_Wx + dx, m_Wy + dy);
                    break;
                }
                case opSizeLeft:
                {
                    SizeWindowLeft(X, Y);
                    Update();
                    break;
                }
                case opSizeRight:
                {
                    SizeWindowRight(X, Y);
                    Update();
                    break;
                }
                case opSizeTop:
                {
                    SizeWindowTop(X, Y);
                    Update();
                    break;
                }
                case opSizeBottom:
                {
                    SizeWindowBottom(X, Y);
                    Update();
                    break;
                }
                case opSizeTopLeft:
                {
                    SizeWindowTop(X, Y);
                    SizeWindowLeft(X, Y);
                    Update();
                    break;
                }
                case opSizeTopRight:
                {
                    SizeWindowTop(X, Y);
                    SizeWindowRight(X, Y);
                    Update();
                    break;
                }
                case opSizeBottomLeft:
                {
                    SizeWindowBottom(X, Y);
                    SizeWindowLeft(X, Y);
                    Update();
                    break;
                }
                case opSizeBottomRight:
                {
                    SizeWindowBottom(X, Y);
                    SizeWindowRight(X, Y);
                    Update();
                    break;
                }
            }
        }
        else
        {
            m_bMouseDown = false;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::MouseUp(TShiftState Shift, int X, int Y)
{
    UpdateProperties();
    m_bMouseDown = false;
}
//---------------------------------------------------------------------------
void __fastcall WindowArea::OnPropertyChanged(int node)
{
    int value;
    frmGameEditor->GetPropertyEditor().GetProperty(m_PropertyNode, node, value);
    if (node == m_PnLeft)
    {
        m_WindowRect.Left = std::max(0, value);
        m_WindowRect.Left = std::min(31, value);
    }
    else if (node == m_PnTop)
    {
        m_WindowRect.Top = std::max(0, value);
        m_WindowRect.Top = std::min(23, value);
    }
    else if (node == m_PnWidth)
    {
        m_WindowRect.Right = value;
        if (m_WindowRect.Left + m_WindowRect.Right > 32)
            m_WindowRect.Right = 32 - m_WindowRect.Left;
    }
    else if (node == m_PnHeight)
    {
        m_WindowRect.Bottom = value;
        if (m_WindowRect.Top + m_WindowRect.Bottom > 24)
            m_WindowRect.Bottom = 24 - m_WindowRect.Top;
    }
    Update();
    UpdateProperties();
}
//---------------------------------------------------------------------------

