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
#ifndef ImageImport_PCH_H
#define ImageImport_PCH_H
#undef _USE_OLD_RW_STL
//-- VCL --------------------------------------------------------------------
#include <vcl.h>
#include <utilcls.h>
//-- SYSTEM -----------------------------------------------------------------
#include <windows.h>
//#include <assert.h>
#include <fstream.h>
//-- APP --------------------------------------------------------------------
#include "..\..\..\Logging\MessageLogger.h"
#include "..\..\..\SafeMacros.h"
#include "..\..\Include\CustomEvents.h"
#include "..\..\..\Framework\ZXMessageBox.h"
//-- APP --------------------------------------------------------------------
#include "ImportPluginInterface.h"
#include "..\ZXImage.h"
#include "..\ZXPalette.h"
#include "fImageImport.h"
#include "fImageSheetImporter.h"
#include "fImportBitmap.h"
#include "fImportZXG.h"
#include "ZXImageImport.h"
#include "ZXImporter.h"
#include "ZXImporterSpectrum.h"
#include "ZXImporterBitmap.h"
#include "ZXImporterZXG.h"
#include "ZXImporterSNASCR.h"
#include "ZXImporterSevenuP.h"
//---------------------------------------------------------------------------
#endif // ImageImport_PCH_H
