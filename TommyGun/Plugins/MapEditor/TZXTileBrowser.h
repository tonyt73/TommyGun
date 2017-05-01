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
#ifndef TZXTileBrowserH
#define TZXTileBrowserH
//- VCL ---------------------------------------------------------------------
#include "KBitmapPanel.h"
//- STD ---------------------------------------------------------------------
#include <vector>
//- APP ---------------------------------------------------------------------
#include "ZXTileManager.h"
#include "Types.h"
//---------------------------------------------------------------------------
class TZXProject;
//---------------------------------------------------------------------------
class TZXTileBrowser
{
private:
    TPanel*                 m_BitmapPanel;
    TStatusBar*             m_StatusBar; 
    std::vector<TTileImage> m_Tiles;
    ZXTileManager*          m_TileManager;
    int                     m_Zoom;

    int         __fastcall  FindTile(KBitmapPanel* Panel);
    void        __fastcall  ArrangePanels(void);
    void        __fastcall  OnTileClick(TObject* Sender);
    void        __fastcall  OnBitmapMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

public:
                __fastcall  TZXTileBrowser();
                __fastcall ~TZXTileBrowser();

    void        __fastcall  Setup(TPanel* Panel, TStatusBar* stsStatus, ZXTileManager* TileManager);
    void        __fastcall  Refresh(void);
    void        __fastcall  Clear(void);
    void        __fastcall  Zoom(int Zoom);
};
//---------------------------------------------------------------------------
#endif
