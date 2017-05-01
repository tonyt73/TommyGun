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
//---------------------------------------------------------------------------
#ifndef DOXYGEN_VC_SKIP
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//
//  TRWBaseWindowProcHandler
//
//---------------------------------------------------------------------------
// Constructor
/**
 * Hooks the WindowProc with a new handler
 * @param   Control the control to hook into
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
__fastcall TRWBaseWindowProcHandler::TRWBaseWindowProcHandler( TWinControl* WinControl )
{
    m_WinControl = NULL;

    if (true == SAFE_PTR(WinControl))
    {
        m_WinControl = WinControl;
        m_OldWindowProc = WinControl->WindowProc;
    }
}
//---------------------------------------------------------------------------
// Destructor
/**
 * Unhooks the WindowProc back to normal
 *
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
__fastcall TRWBaseWindowProcHandler::~TRWBaseWindowProcHandler( )
{
    if (true == SAFE_PTR(m_WinControl))
    {
        m_WinControl->WindowProc = m_OldWindowProc;
    }
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
//
//  TRWToolbarHandler
//
//---------------------------------------------------------------------------
// Constructor
/**
 * Hooks in the WindowProc of the TWinControl
 *
 * @param   Control the control to hook into
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
__fastcall TRWToolbarHandler::TRWToolbarHandler( TWinControl* WinControl )
: TRWBaseWindowProcHandler( WinControl )
{
    // cannot place this initialization code in the base class as the
    // vtable is not complete at that stage, and thus NewWindowProc is not valid!
    if (true == SAFE_PTR(m_WinControl))
    {
        m_WinControl->WindowProc = NewWindowProc;
    }
}
//---------------------------------------------------------------------------
// Destructor
/**
 * Implements the virtual destructor
 *
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
__fastcall TRWToolbarHandler::~TRWToolbarHandler( )
{
}
//---------------------------------------------------------------------------
// NewWindowProc
/**
 * Reprocesses the controls Window messages to intercept the CM_VISIBLECHANGED message
 * so it can track the toolbars visible state
 *
 * @param   Message the Windows Message sent to the control
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TRWToolbarHandler::NewWindowProc( Messages::TMessage &Message )
{
    if (true == SAFE_PTR(m_WinControl))
    {
        if (CM_VISIBLECHANGED == Message.Msg)
        {
            if ( (false == m_WinControl->Visible) &&
                 (WINDOW_CLOSED_ON_HIDE != (m_WinControl->Tag & TAG_MASK_WINDOWSTATE)))
            {
                m_WinControl->Tag = ( m_WinControl->Tag & ~TAG_MASK_WINDOWSTATE ) | WINDOW_CLOSED_BY_USER;
            }
        }

        if (NULL != m_OldWindowProc)
        {
            m_OldWindowProc( Message );
        }
    }
}
//---------------------------------------------------------------------------
// ShowFloating
/**
 * Shows the toolbar if the tag flags so it can be done
 *
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TRWToolbarHandler::ShowFloating( )
{
    if (true == SAFE_PTR(m_WinControl))
    {
        if ( ( m_WinControl->Tag & TAG_MASK_WINDOWSTATE ) == WINDOW_CLOSED_ON_HIDE && m_WinControl->Floating )
        {
            m_WinControl->Tag = ( m_WinControl->Tag & ~TAG_MASK_WINDOWSTATE );
            m_WinControl->Visible = true;
        }
    }
}
//---------------------------------------------------------------------------
// HideFloating
/**
 * Hides the toolbar if the tag flags so it can be done
 *
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TRWToolbarHandler::HideFloating( )
{
    // hide the menus toolbar if its floating
    if (true == SAFE_PTR(m_WinControl))
    {
        if (m_WinControl->Visible && m_WinControl->Floating)
        {
            if (WINDOW_NOT_CLOSED == ( m_WinControl->Tag & TAG_MASK_WINDOWSTATE ))
            {
                m_WinControl->Tag = ( m_WinControl->Tag & ~TAG_MASK_WINDOWSTATE ) | WINDOW_CLOSED_ON_HIDE;
            }

            m_WinControl->Visible = false;
        }
    }
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
//
//  TRWControlBarHandler
//
//---------------------------------------------------------------------------
// Constructor
/**
 * Hooks in the WindowProc of the TWinControl
 *
 * @param   Control the control to hook into
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
__fastcall TRWControlBarHandler::TRWControlBarHandler( TWinControl* WinControl )
: TRWBaseWindowProcHandler( WinControl )
{
    // cannot place this initialization code in the base class as the
    // vtable is not complete at that stage, and thus NewWindowProc is not valid!
    if (true == SAFE_PTR(m_WinControl))
    {
        m_WinControl->WindowProc = NewWindowProc;
    }
}
//---------------------------------------------------------------------------
// Destructor
/**
 * unhooks the control
 *
 * @param   Control the control to double buffer
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
__fastcall TRWControlBarHandler::~TRWControlBarHandler( )
{
}
//---------------------------------------------------------------------------
// NewWindowProc
/**
 * Redraws the control bar as soon as it gets a WM_ERASEBKGND message to stop flicker
 *
 * @param   Control the control to double buffer
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall TRWControlBarHandler::NewWindowProc( Messages::TMessage &Message )
{
    if (true == SAFE_PTR(m_WinControl))
    {
        // handle the message as normal
        if (NULL != m_OldWindowProc)
        {
            m_OldWindowProc( Message );
        }

        // if we are erasing the control
        if (WM_ERASEBKGND == Message.Msg)
        {
            // tell the control to draw itself RIGHT AWAY!
            m_WinControl->Perform( WM_PAINT, reinterpret_cast<WPARAM>(static_cast<TControlBar*>(m_WinControl)->Canvas->Handle), NULL );
        }
    }
}
//---------------------------------------------------------------------------
#endif //DOXYGEN_VC_SKIP


