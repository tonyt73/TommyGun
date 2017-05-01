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
#ifndef CORE_COMMONPLUGIN_H
#define CORE_COMMONPLUGIN_H
//---------------------------------------------------------------------------
#include <windows.h>
#include <mmsystem.h>
#include <algorithm>
#include <KRegistry.h>
#include "..\SafeMacros.h"
#include "..\..\Logging\MessageLogger.h"
#include "..\..\SafeMacros.h"
#include "ZXMessageBox.h"
#include "KFileInfo.h"
#include "ZXLogFile.h"
#include "ZXTypes.h"
#include "ZXPluginManager.h"
#include "ZXPlugin.h"
#ifdef USE_GUI_MANAGER
    #include "ZXGuiManager.h"
    #include "ZXUndoManager.h"
#else
#include "ZXEventManager.h"
#include "ZXBasePlugin.h"
#endif
//---------------------------------------------------------------------------
#endif//CORE_COMMONPLUGIN_H
