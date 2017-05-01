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
#ifndef ZXScorePanelH
#define ZXScorePanelH
//- APP ---------------------------------------------------------------------
#include "ZXTileManager.h"
//---------------------------------------------------------------------------
class TZXScorePanel
{
    private:
    TImage*                 m_ScorePanelImage;
    ZXBitmap                m_ScorePanelTile;
    bool                    m_bEnabled;

    public:
                __fastcall  TZXScorePanel();
                __fastcall ~TZXScorePanel();

    void        __fastcall  Setup(TImage* pImage);
    void        __fastcall  Update();
    void        __fastcall  Refresh(void);

    __property  bool        Enabled     = { write = m_bEnabled  };
};
//---------------------------------------------------------------------------
#endif

