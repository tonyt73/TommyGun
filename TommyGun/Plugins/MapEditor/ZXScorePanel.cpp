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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//- CONSTANTS ---------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TZXScorePanel::TZXScorePanel()
: m_ScorePanelImage(NULL),
  m_ScorePanelTile(NULL),
  m_bEnabled(false)
{
}
//---------------------------------------------------------------------------
__fastcall TZXScorePanel::~TZXScorePanel()
{
}
//---------------------------------------------------------------------------
void __fastcall TZXScorePanel::Setup(TImage* pImage)
{
    m_ScorePanelImage = pImage;
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TZXScorePanel::Update()
{
    if (m_bEnabled && true == SAFE_PTR(m_ScorePanelTile) && m_ScorePanelImage->Width > 0 && m_ScorePanelImage->Width > 0)
    {
        // clear the score panel image
        m_ScorePanelImage->Canvas->Brush->Color = m_ScorePanelTile->Canvas->Pixels[0][0];
        m_ScorePanelImage->Canvas->FillRect(TRect(0, 0, m_ScorePanelImage->Width, m_ScorePanelImage->Height));
        // stretch blit the score panel tile onto the image
        StretchBlt
        (
            m_ScorePanelImage->Canvas->Handle, 0, 0, m_ScorePanelImage->Width, m_ScorePanelImage->Height,   // DST
            m_ScorePanelTile->Canvas->Handle, 0, 0, m_ScorePanelTile->Width, m_ScorePanelTile->Height,      // SRC
            SRCCOPY
        );
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXScorePanel::Refresh(void)
{
    // update the score panel tile
#if 0
    m_ScorePanelTile = m_TileManager->Find("ScorePanel");
    if (false == SAFE_PTR(m_ScorePanelTile))
    {
        m_ScorePanelTile = m_TileManager->Find("Score Panel");
    }
#endif
    std::vector<String> vTileNames;
    String sPlugin = "Screen";
    if (S_OK == PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_GET_IMAGE_NAMES, (LPDATA)&vTileNames, (DWORD)&sPlugin, -1))
    {
        int scorePanel = -1;
        for (unsigned int i = 0; i < vTileNames.size() && scorePanel == -1; i++)
        {
            if (vTileNames[i].LowerCase() == "scorepanel")
            {
                scorePanel = i;
            }
        }
        if (scorePanel != -1)
        {
            if (m_ScorePanelTile == NULL)
            {
                m_ScorePanelTile = new Graphics::TBitmap();
            }
            // build the bitmap list
            std::vector<ZXBitmap> vTileBitmaps;
            vTileBitmaps.push_back(m_ScorePanelTile);
            // grab the bitmaps
            PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_GET_IMAGE_BITMAPS, (LPDATA)&vTileBitmaps, (DWORD)&sPlugin, -1);
            //m_ScorePanelImage->Picture->Bitmap->Assign(m_ScorePanelTile);
            //m_ScorePanelImage->Stretch = true;
        }
    }
}
//---------------------------------------------------------------------------

