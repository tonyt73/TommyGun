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
#ifndef CodeEditor_PCH_H
#define CodeEditor_PCH_H
//-- VCL --------------------------------------------------------------------
#include <vcl.h>
#include <utilcls.h>
//-- SYSTEM -----------------------------------------------------------------
#include <windows.h>
#include <RpcDce.h>
//-- APP --------------------------------------------------------------------
#include "..\..\Logging\MessageLogger.h"
#include "..\..\SafeMacros.h"
#include "..\..\Framework\FrameworkInterface.h"
#include "..\Include\CustomEvents.h"
//-- APP --------------------------------------------------------------------
#include "CodePluginInterface.h"
#include "ZXPluginManager.h"
#include "ZXLogFile.h"
#include "ZXCodeEditor.h"
#include "ZXFileManager.h"
#include "ZXParserManager.h"
#include "ZXEditorSettings.h"
#include "ZXColorSettings.h"
#include "ZXToolDefinition.h"
#include "ZXDebugger.h"
#include "ZXSymbolsManager.h"
#include "ZXDebugFileManager.h"
#include "ZXBreakpointManager.h"
#include "fCodeEditor.h"
#include "fSearch.h"
#include "fReplace.h"
#include "fComfirmReplace.h"
#include "fGotoLine.h"
#include "fInsertResource.h"
#include "fEditorProperties.h"
#include "fBuildOptions.h"
#include "fSearching.h"
#include "fDebuggerStateView.h"
#include "fDisplayView.h"
#include "fOSBView.h"
#include "fChooseBuildFile.h"
#include "uFindInFiles.h"
#include "ZXSnapshots.h"
//---------------------------------------------------------------------------
#endif//CodeEditor_PCH_H
