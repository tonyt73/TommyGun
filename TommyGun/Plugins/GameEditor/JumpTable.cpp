//---------------------------------------------------------------------------
#pragma hdrstop
#include "pch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const int cMaxSteps = 22;
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GameEditor;
//---------------------------------------------------------------------------
__fastcall JumpTable::JumpTable()
: m_Window(NULL)
, m_IsDirty(false)
, m_ActiveStep(1)
, m_Ratio(1)
, m_PropertyNode(-1)
{
    ResetDefaults();
}
//---------------------------------------------------------------------------
__fastcall JumpTable::~JumpTable()
{
}
//---------------------------------------------------------------------------
void __fastcall JumpTable::Init(TImage* window)
{
    m_Window = window;
    window->Picture->Bitmap->Width = 256;
    window->Picture->Bitmap->Height = 192;
    //m_PropertyNode = frmGameEditor->GetPropertyEditor().AddRootNode(this, "Jump Table", tviJump);
    Update();
}
//---------------------------------------------------------------------------
bool __fastcall JumpTable::Load(KXmlInfo& xmlInfo)
{
    bool bLoaded = false;
    KXmlInfo* StepsNode;
    if (xmlInfo.Find(StepsNode, "JumpTable", 0))
    {
        for (int i = 1; i < cMaxSteps; i++)
        {
            KXmlInfo* nValue = StepsNode->GetNode("Step" + IntToStr(i), 0);
            if (nValue)
                m_Steps[i] = std::min(24, std::max(-24, nValue->GetInt()));
        }
        bLoaded = true;
        Update();
        m_Window->Refresh();
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
void __fastcall JumpTable::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo* Node;
    if (xmlInfo.Find(Node, "JumpTable", 0))
    {
        xmlInfo.Remove(Node);
    }
    // create a new map editor node
    KXmlInfo steps("JumpTable");
    // store the jump table
    for (int i = 1; i < cMaxSteps; i++)
    {
        steps.Add("Step"+IntToStr(i), m_Steps[i]);
    }
    xmlInfo.Add(steps);
    m_IsDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall JumpTable::Update()
{
    PatBlt(m_Window->Picture->Bitmap->Canvas->Handle, 0, 0, 256, 192, WHITENESS);

    int x = 0;
    int y = 80;
    m_Window->Picture->Bitmap->Canvas->Pen->Color = clBlack;
    m_Window->Picture->Bitmap->Canvas->Brush->Color = clRed;
    for (int i = 0; i < cMaxSteps; i++)
    {
        y += m_Steps[i];

        if (i == m_ActiveStep)
        {
            m_Window->Picture->Bitmap->Canvas->FillRect(TRect(x, 0, x + 8, 192));
        }

        m_Window->Picture->Bitmap->Canvas->MoveTo(x, y);
        m_Window->Picture->Bitmap->Canvas->LineTo(x + 8, y);

        x += 8;
    }
}
//---------------------------------------------------------------------------
void __fastcall JumpTable::MouseDown(TShiftState Shift, int X, int Y)
{
}
//---------------------------------------------------------------------------
void __fastcall JumpTable::MouseMove(TShiftState Shift, int X, int Y)
{
    X /= (m_Ratio * 8);
    if (0 < X && X < 22)
    {
        m_ActiveStep = X;
        Update();
        m_Window->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall JumpTable::MouseWheel(int dY)
{
    if (dY > 0 && m_Steps[m_ActiveStep] < 24)
        m_Steps[m_ActiveStep]++;
    else if (dY < 0 && m_Steps[m_ActiveStep] > -24)
        m_Steps[m_ActiveStep]--;
    Update();
    m_Window->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall JumpTable::ResetDefaults()
{
    m_Steps[ 0] =   0;
    m_Steps[ 1] = -15;
    m_Steps[ 2] = -12;
    m_Steps[ 3] =  -9;
    m_Steps[ 4] =  -4;
    m_Steps[ 5] =  -4;
    m_Steps[ 6] =  -2;
    m_Steps[ 7] =  -2;
    m_Steps[ 8] =  -2;
    m_Steps[ 9] =   0;
    m_Steps[10] =   0;
    m_Steps[11] =   0;
    m_Steps[12] =   2;
    m_Steps[13] =   2;
    m_Steps[14] =   2;
    m_Steps[15] =   4;
    m_Steps[16] =   4;
    m_Steps[17] =   8;
    m_Steps[18] =  12;
    m_Steps[19] =  16;
    m_Steps[20] =  16;
    m_Steps[21] =  16;
    if (m_Window)
    {
        Update();
        m_Window->Refresh();
    }
}
//---------------------------------------------------------------------------
