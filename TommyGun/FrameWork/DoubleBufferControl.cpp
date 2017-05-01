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
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// DoubleBufferControls
/**
 * Double buffers and control and all of its children
 *
 * @param   Control the control to double buffer
 * @author  Tony Thompson
 * @date    Last Modified 20 November 2001
 */
//---------------------------------------------------------------------------
void __fastcall DoubleBufferControls( TWinControl* control )
{
    control->DoubleBuffered = true;

    for ( int i = 0; i < control->ControlCount; i++ )
    {
        if ( control->Controls[i]->InheritsFrom( __classid( TWinControl) ) )
        {
            TWinControl* winControl = static_cast<TWinControl*>(control->Controls[i]);
            DoubleBufferControls( winControl );
        }
    }
}
//---------------------------------------------------------------------------
