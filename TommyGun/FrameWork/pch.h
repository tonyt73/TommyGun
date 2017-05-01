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
#ifndef COREUTILS_PCH_H
#define COREUTILS_PCH_H
//-- VCL --------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include <sysutils.hpp>
//-- SYSTEM -----------------------------------------------------------------
#include <stdio.h>
#include <dos.h>
//-- STL --------------------------------------------------------------------
#include <vector>
#include <algorithm>
//-- KIWIWARE----------------------------------------------------------------
#include <KRegistry.h>          // ResSuite VCL Component
//-- APP --------------------------------------------------------------------
#include "..\SafeMacros.h"
#include "Dragger.h"
#include "Conversion.h"
#include "BandManager.h"
#include "WndProcHandlers.h"
#include "fMessage.h"
#include "ZXMessageBox.h"
#include "ZXUndoItem.h"
#include "ZXUndoManager.h"
#include "ZXBackup.h"
//---------------------------------------------------------------------------
#endif//COREUTILS_PCH_H
