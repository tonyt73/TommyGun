//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ZXSnapManager.h"
//#include "GlassManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const int g_SnapRange = 20; // in pixels
ZXSnapManager::TSnapPanels ZXSnapManager::m_SnapPanels;
ZXSnapManager::TSnapForms ZXSnapManager::m_SnapForms;
TForm* ZXSnapManager::m_SnapForm = NULL;
TPanel* ZXSnapManager::m_SnapPanel = NULL;
int ZXSnapManager::m_MouseX = 0;
int ZXSnapManager::m_MouseY = 0;
//---------------------------------------------------------------------------
__fastcall ZXSnapManager::ZXSnapManager()
{
}
//---------------------------------------------------------------------------
__fastcall ZXSnapManager::~ZXSnapManager()
{
    m_SnapPanels.clear();
    m_SnapForms.clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXSnapManager::RegisterDocking(TForm* form, TPanel* snapPanel)
{
    m_SnapPanels[form] = snapPanel;
}
//---------------------------------------------------------------------------
void __fastcall ZXSnapManager::RegisterSnapClient(TForm* clientForm, TForm* snapForm, TSnapEdge snapEdge, int xOffset, int yOffset)
{
	// store the childs parent
	TSnapWindow snapWindow = { ssNothing, seNone, snapForm };
	m_SnapForms[clientForm] = snapWindow;
	// place the window
	if (snapEdge)
	{
		TPanel* snapPanel = m_SnapPanels[snapForm];
		TPoint pt(snapPanel->ClientToScreen(TPoint(0, 0)));

		m_SnapForms[clientForm].SnapState = ssParent;
		m_SnapForms[clientForm].SnapEdge = snapEdge;

		if (snapEdge == seLeft)
		{
			clientForm->Left = pt.x;
			if (yOffset >= 0)
			{
				clientForm->Top  = pt.y + yOffset;
			}
			else
			{
				clientForm->Top  = pt.y + snapPanel->Height - yOffset;

			}
		}
		else if (snapEdge == seTop)
		{
			clientForm->Left = pt.x + xOffset;
			if (xOffset >= 0)
			{
				clientForm->Left  = pt.x + xOffset;
			}
			else
			{
				clientForm->Left  = pt.x + snapPanel->Width + yOffset;

			}
		}
		else if (snapEdge == seRight)
		{
			clientForm->Left = pt.x + snapPanel->Width - clientForm->Width;
			if (yOffset >= 0)
			{
				clientForm->Top  = pt.y + yOffset;
			}
			else
			{
				clientForm->Top  = pt.y + snapPanel->Height + yOffset;

			}
		}
		else if (snapEdge == seBottom)
		{
			clientForm->Left = pt.x + xOffset;
			if (xOffset >= 0)
			{
				clientForm->Left  = pt.x + xOffset;
			}
			else
			{
				clientForm->Left  = pt.x + snapPanel->Width + yOffset;

			}
		}
		m_SnapForms[clientForm].SnapPoint.x = clientForm->Left - pt.x;
		m_SnapForms[clientForm].SnapPoint.y = clientForm->Top  - pt.y;
	}
}
//---------------------------------------------------------------------------
bool __fastcall ZXSnapManager::IsClose(int a, int b)
{
    return abs(a-b) < g_SnapRange;
}
//---------------------------------------------------------------------------
void __fastcall ZXSnapManager::SnapToWorkArea(TForm* form, RECT*& rect, const RECT& wa, TSnapState snapState)
{
    if(IsClose(rect->left, wa.left))
    {
        // snap to left screen edge
        m_SnapForms[form].SnapState = snapState;
        m_SnapForms[form].SnapEdge = seLeft;
        m_SnapForms[form].SnapPoint.y = rect->top - wa.top;
        OffsetRect(rect, wa.left - rect->left, 0);
    }
    else if(IsClose(wa.right, rect->right))
    {
        // snap to right screen edge
        m_SnapForms[form].SnapState = snapState;
        m_SnapForms[form].SnapEdge = seRight;
        m_SnapForms[form].SnapPoint.y = rect->top - wa.top;
        OffsetRect(rect, wa.right - rect->right, 0);
    }

    if(IsClose(rect->top, wa.top))
    {
        // snap to top screen edge
        m_SnapForms[form].SnapState = snapState;
        m_SnapForms[form].SnapEdge = seTop;
        m_SnapForms[form].SnapPoint.x = rect->left - wa.left;
        OffsetRect(rect, 0, wa.top - rect->top);
    }
    else if(IsClose(wa.bottom, rect->bottom))
    {
        // snap to bottom screen edge
        m_SnapForms[form].SnapState = snapState;
        m_SnapForms[form].SnapEdge = seBottom;
        m_SnapForms[form].SnapPoint.x = rect->left - wa.left;
        OffsetRect(rect, 0, wa.bottom - rect->bottom);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSnapManager::GetParentWorkArea(TForm* form, RECT& wa)
{
    TPanel* parent = m_SnapPanels[m_SnapForms[form].SnapParent];
    wa.left   = parent->ClientToScreen(TPoint(0, 0)).x;
    wa.top    = parent->ClientToScreen(TPoint(0, 0)).y;
    wa.right  = parent->ClientToScreen(TPoint(parent->Width, parent->Height)).x;
    wa.bottom = parent->ClientToScreen(TPoint(parent->Width, parent->Height)).y;
}
//---------------------------------------------------------------------------
bool __fastcall ZXSnapManager::ProcessMoving(Messages::TMessage &Message, TForm* form)
{
    bool processed = false;

    if (Message.Msg == WM_ENTERSIZEMOVE)
    {
        processed = true;
        // get relative mouse position
        POINT cur_pos;
        GetCursorPos(&cur_pos);
        m_MouseX = cur_pos.x - form->Left;
        m_MouseY = cur_pos.y - form->Top;
    }
    else if (Message.Msg == WM_MOVING)
    {
        processed = true;
        // rect of the window that is moving
        RECT* rect = (RECT*)Message.LParam;
        POINT cur_pos;
        // screen work area
        RECT wa;
        GetCursorPos(&cur_pos);
        // offset the rect by the original mouse delta
        OffsetRect(rect, cur_pos.x - (rect->left + m_MouseX),
        cur_pos.y - (rect->top + m_MouseY));
        // get the screen work area
        SystemParametersInfo(SPI_GETWORKAREA, 0, &wa, 0);

        m_SnapForms[form].SnapState = ssNothing;
        m_SnapForms[form].SnapEdge = seNone;
        SnapToWorkArea(form, rect, wa, ssScreen);

        if (m_SnapPanels.count(form) == 0)
        {
            // is not a main form so must be a child window
            // get the work area of the forms parent control
            GetParentWorkArea(form, wa);
            SnapToWorkArea(form, rect, wa, ssParent);
        }
        else
        {
            UpdateSnapClients(form);
        }
    }
    return processed;
}
//---------------------------------------------------------------------------
void __fastcall ZXSnapManager::UpdateSnapClients(TForm* parentForm)
{
    for (TSnapFormsIt it = m_SnapForms.begin(); it != m_SnapForms.end(); it++)
    {
        TForm* snapForm = (*it).first;
        TSnapWindow& snapWindow = (*it).second;
        if (snapWindow.SnapParent == parentForm && snapWindow.SnapState == ssParent)
        {
            RECT wa;
            GetParentWorkArea(snapForm, wa);
            //TPanel* panel = m_SnapPanels[parentForm];
            
            if (snapWindow.SnapEdge == seLeft)
            {
                snapForm->Left = wa.left;
                snapForm->Top = wa.top + snapWindow.SnapPoint.y;
            }
            else if (snapWindow.SnapEdge == seRight)
            {
                snapForm->Left = wa.right - snapForm->Width;
                snapForm->Top = wa.top + snapWindow.SnapPoint.y;
            }

            if (snapWindow.SnapEdge == seTop)
            {
                snapForm->Top = wa.top;
                snapForm->Left = wa.left + snapWindow.SnapPoint.x;
            }
            else if (snapWindow.SnapEdge == seBottom)
            {
                snapForm->Top = wa.bottom - snapForm->Height;
                snapForm->Left = wa.left + snapWindow.SnapPoint.x;
            }
        }
    }
}
//---------------------------------------------------------------------------

