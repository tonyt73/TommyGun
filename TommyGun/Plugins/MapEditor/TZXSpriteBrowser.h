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
#ifndef TZXSpriteBrowserH
#define TZXSpriteBrowserH
//- VCL ---------------------------------------------------------------------
#include "KBitmapPanel.h"
//- STD ---------------------------------------------------------------------
#include <vector>
//- APP ---------------------------------------------------------------------
#include "ZXSpriteManager.h"
#include "Types.h"
//---------------------------------------------------------------------------
class TZXProject;
//---------------------------------------------------------------------------
class TZXSpriteBrowser
{
private:
    TPanel*                 m_BitmapPanel;
    TStatusBar*             m_StatusBar; 
    std::vector<TTileImage> m_Tiles;
    ZXSpriteManager*        m_SpriteManager;
    int                     m_Zoom;

    int         __fastcall  FindTile(KBitmapPanel* Panel);
    void        __fastcall  ArrangePanels(void);
    void        __fastcall  OnSpriteClick(TObject* Sender);
    void        __fastcall  OnBitmapMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

public:
                __fastcall  TZXSpriteBrowser();
                __fastcall ~TZXSpriteBrowser();

    void        __fastcall  Setup(TPanel* Panel, TStatusBar* stsStatus, ZXSpriteManager* SpriteManager);
    void        __fastcall  Refresh(void);
    void        __fastcall  Clear(void);
    void        __fastcall  Zoom(int Zoom);
};
//---------------------------------------------------------------------------
#endif
