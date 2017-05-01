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
#ifndef ImageEditor_PCH_H
#define ImageEditor_PCH_H
//-- VCL --------------------------------------------------------------------
#include <vcl.h>
#include <utilcls.h>
//-- SYSTEM -----------------------------------------------------------------
#include <windows.h>
//#include <assert.h>
//-- APP --------------------------------------------------------------------
#include "..\..\Logging\MessageLogger.h"
#include "..\..\SafeMacros.h"
#include "..\..\Framework\FrameworkInterface.h"
#include "..\Include\CustomEvents.h"
#include "..\Common\ZXPluginManager.h"
//-- APP --------------------------------------------------------------------
#include "ImagePluginInterface.h"
#include "ZXImageEditor.h"
#include "ZXLogFile.h"
#include "ZXImageManager.h"
#include "ZXPalette.h"
#include "ZXImage.h"
#include "ZXImageNotifications.h"
#include "fImageEditor.h"
#include "fImageResize.h"
#include "fImageMask.h"
#include "fPaletteChange.h"
//---------------------------------------------------------------------------
#endif//ImageEditor_PCH_H
