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
#ifndef COMMONPLUGIN_H
#define COMMONPLUGIN_H
//---------------------------------------------------------------------------
#include <windows.h>
#include <mmsystem.h>
#include <algorithm>
#include <KRegistry.h>
#include "SafeMacros.h"
#include "Logging\MessageLogger.h"
#include "FrameWork\ZXMessageBox.h"
#include "KFileInfo.h"
#include "Helpers\ZXLogFile.h"
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
#endif//COMMONPLUGIN_H
