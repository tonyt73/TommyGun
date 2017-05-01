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

-----------------------------------------------------------------------------
 Project's main entry point.
 Borland uses this file as the entry point into the DLL.
 You do not need to add or modify this file.
---------------------------------------------------------------------------*/
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
// DllEntryPoint
/**
 * Main entry point into the DLL
 * @param   hinst       DLL HINSTANCE
 * @param   reason      Reason the DllMain function was called (startup, closedown)
 * @param   lpReserved  I don't know! It's a Windows thing!
 * @return  BOOL Always TRUE
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    return TRUE;
}
//---------------------------------------------------------------------------
 
