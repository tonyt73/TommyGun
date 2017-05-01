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
#ifndef TZXObjectBrowserH
#define TZXObjectBrowserH
//- VCL ---------------------------------------------------------------------
#include "KBitmapPanel.h"
//- STD ---------------------------------------------------------------------
#include <vector>
//- APP ---------------------------------------------------------------------
#include "ZXObjectManager.h"
#include "Types.h"
//---------------------------------------------------------------------------
class TZXProject;
//---------------------------------------------------------------------------
class TZXObjectBrowser
{
private:
    TListView*              m_ListView;
    TStatusBar*             m_StatusBar;
    ZXObjectManager*        m_ObjectManager;

public:
                __fastcall  TZXObjectBrowser();
                __fastcall ~TZXObjectBrowser();

    void        __fastcall  Setup(TListView* ListView, TStatusBar* stsStatus, ZXObjectManager* ObjectManager);
    void        __fastcall  Refresh(void);
    void        __fastcall  Clear(void);
};
//---------------------------------------------------------------------------
#endif
