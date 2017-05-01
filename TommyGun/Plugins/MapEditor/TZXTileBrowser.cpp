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
const int   g_iNotFound = -1;
//---------------------------------------------------------------------------
__fastcall TZXTileBrowser::TZXTileBrowser()
: m_BitmapPanel(NULL)
, m_Zoom(1)
{
}
//---------------------------------------------------------------------------
__fastcall TZXTileBrowser::~TZXTileBrowser()
{
    m_BitmapPanel = NULL;
    m_Tiles.clear();
}
//---------------------------------------------------------------------------
void __fastcall TZXTileBrowser::Setup(TPanel* Panel, TStatusBar* stsStatus, ZXTileManager* TileManager)
{
    m_BitmapPanel = Panel;
    m_StatusBar   = stsStatus;
    m_TileManager = TileManager;
}
//---------------------------------------------------------------------------
void __fastcall TZXTileBrowser::OnTileClick(TObject* Sender)
{
    KBitmapPanel* Panel = dynamic_cast<KBitmapPanel*>(Sender);
    if (true == SAFE_PTR(Panel))
    {
        int iTile = FindTile(Panel);
        if (g_iNotFound != iTile)
        {
            //m_StatusBar->SimpleText = m_sSelectedTile + " [" + IntToStr(m_Tiles[iTile].Image->Width) + " x " + IntToStr(m_Tiles[iTile].Image->Height) + "]";
            if (true == SAFE_PTR(m_TileManager))
            {
                m_TileManager->Selected = Panel->Caption;
            }
            TScrollBox* SP = dynamic_cast<TScrollBox*>(m_BitmapPanel->Parent);
            int iOldT = SP->VertScrollBar->Position;
            Panel->Selected = (m_TileManager->Selected == Panel->Caption);
            SP->VertScrollBar->Position = iOldT;
        }
        else
        {
            // delete the panel?
            SAFE_DELETE(Panel);
        }
    }
}
//---------------------------------------------------------------------------
int __fastcall TZXTileBrowser::FindTile(KBitmapPanel* Panel)
{
    int iTile = g_iNotFound;
    for (unsigned int i = 0; i < m_Tiles.size() && g_iNotFound == iTile; i++)
    {
        if (m_Tiles[i].Panel == Panel)
        {
            iTile = i;
        }
    }
    return iTile;
}
//---------------------------------------------------------------------------
void __fastcall TZXTileBrowser::Clear(void)
{
    // remove all the tiles that are not in use
    for (unsigned int i = 0; i < m_Tiles.size(); i++)
    {
        // remove the panel
        SAFE_DELETE(m_Tiles[i].Panel);
    }
    // and clear the tile list
    m_Tiles.clear();
    ArrangePanels();
}
//---------------------------------------------------------------------------
void __fastcall TZXTileBrowser::Refresh(void)
{
    m_TileManager->Refresh();
    if (true == SAFE_PTR(m_BitmapPanel))
    {
        Clear();
        // rebuild the tiles list
        for (unsigned int i = 0; i < m_TileManager->Tiles(); i++)
        {
            String sName = m_TileManager->Name(i);
            if (sName != "ScorePanel")
            {
                TTileImage TileImage;
                ZXBitmap Tile = m_TileManager->Find(sName);
                if (true == SAFE_PTR(Tile))
                {
                    // add a new tile panel
                    TileImage.sName  = sName;
                    TileImage.Panel  = new KBitmapPanel(NULL);
                    TileImage.Panel->BitmapWidth  = std::max(16, Tile->Width);
                    TileImage.Panel->BitmapHeight = std::max(16, Tile->Height);
                    TileImage.Panel->OnClick      = OnTileClick;
                    TileImage.Panel->Caption      = sName;
                    TileImage.Panel->ShowLabel    = false;
                    TileImage.Panel->Transparent  = false;
                    TileImage.Panel->Edge         = 8;
                    TileImage.Panel->TopEdge      = 8;
                    TileImage.Panel->ColorUnSelected = clWhite;
                    TileImage.Panel->OnMouseMove  = OnBitmapMouseMove;
                    //TileImage.Panel->DoubleBuffered = true;
                    m_Tiles.push_back(TileImage);
                }
                // update the bitmap panel to contain the lastest picture
                TPicture* Picture = new TPicture();
                Picture->Assign(Tile);
                TileImage.Panel->Picture = Picture;
                TileImage.Panel->KeepBitmapSize=m_Zoom == 1;
                TileImage.Panel->StretchBitmap= m_Zoom != 1;
                TileImage.Panel->Width        = std::max(16, Tile->Width)  * m_Zoom;
                TileImage.Panel->Height       = std::max(16, Tile->Height) * m_Zoom;
                SAFE_DELETE(Picture);
            }
        }

        for (unsigned int i = 0; i < m_Tiles.size(); i++)
        {
            m_Tiles[i].Panel->Parent = m_BitmapPanel;
        }
    }
    // try to find the current selected tile and make it the selection, if not found then clear selection
    bool bSelectionMade = false;
    for (unsigned int i = 0; i < m_Tiles.size() && false == bSelectionMade; i++)
    {
        if (m_Tiles[i].sName == m_TileManager->Selected)
        {
            bSelectionMade = true;
            m_Tiles[i].Panel->Selected = true;
        }
    }
    // reset the selection tile if not panel is found
    if (false == bSelectionMade)
    {
        m_TileManager->Selected = "";
    }
    ArrangePanels();
}
//---------------------------------------------------------------------------
void __fastcall TZXTileBrowser::ArrangePanels(void)
{
    // sort the panels
    /*for (unsigned int i = 1; i < m_Tiles.size(); i++)
    {
        m_Tiles[i].Panel->KeepBitmapSize= m_Zoom == 1;
        m_Tiles[i].Panel->StretchBitmap = m_Zoom != 1;
        m_Tiles[i].Panel->Width         = m_Tiles[i].Panel->BitmapWidth  * m_Zoom;
        m_Tiles[i].Panel->Height        = m_Tiles[i].Panel->BitmapHeight * m_Zoom;
    }*/

    for (unsigned int i = 1; i < m_Tiles.size(); i++)
    {
        // order the tiles by height first, and then name if the heights are equal
        if ( (m_Tiles[i].Panel->Height <  m_Tiles[i - 1].Panel->Height) ||
            ((m_Tiles[i].Panel->Height == m_Tiles[i - 1].Panel->Height) &&
              m_Tiles[i].Panel->Name   <  m_Tiles[i - 1].Panel->Name   ))
        {
            // swap the tiles
            TTileImage TmpTile = m_Tiles[i - 1];
            m_Tiles[i - 1]     = m_Tiles[i];
            m_Tiles[i    ]     = TmpTile;
            i = 0;
        }
    }
    // now arrange the bitmap panels
    int iXGap = 4;
    int iYGap = 4;
    int iX = iXGap;
    int iY = iYGap;
    int iLastHeight = 16 * m_Zoom;
    for (unsigned int i = 0; i < m_Tiles.size(); i++)
    {
        // wrap the bitmap panels around if needed
        if (iX + m_Tiles[i].Panel->Width + iXGap > m_BitmapPanel->Width)// || m_Tiles[i].Panel->Height != iLastHeight)
        {
            iX  = iXGap;
            iY += iLastHeight + iYGap;
        }
        // reposition the bitmap panel
        m_Tiles[i].Panel->Left = iX;
        m_Tiles[i].Panel->Top  = iY;
        // work out the next position to place a panel
        iX += m_Tiles[i].Panel->Width + iXGap;
        iLastHeight = m_Tiles[i].Panel->Height;
    }
    if (true == SAFE_PTR(m_BitmapPanel))
    {
        // resize the container panel that houses all our bitmap panels
        m_BitmapPanel->Height = iY + iLastHeight + iYGap;
        TScrollBox* SP = dynamic_cast<TScrollBox*>(m_BitmapPanel->Parent->Parent->Parent);
        if (true == SAFE_PTR(SP))
        {
            SP->Invalidate();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXTileBrowser::OnBitmapMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    KBitmapPanel* Panel = dynamic_cast<KBitmapPanel*>(Sender);

    if (true == SAFE_PTR(Panel))
    {
        int iTile = FindTile(Panel);
        if (iTile != -1)
        {
            m_StatusBar->SimpleText = "  " + m_Tiles[iTile].sName;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXTileBrowser::Zoom(int Zoom)
{
    if (m_Zoom != Zoom)
    {
        TScrollBox* SP = NULL;
        TWinControl* parent = m_BitmapPanel;
        while (SP == NULL)
        {
            parent = parent->Parent;
            SP = dynamic_cast<TScrollBox*>(parent);
        }
        float iOldT = SP->VertScrollBar->Position;
        float iOldH = SP->VertScrollBar->Range;
        float p = 0;
        if (iOldH)
        {
            p = iOldT / iOldH;
        }
        m_Zoom = Zoom;
        Refresh();
        SP->VertScrollBar->Position = (float)SP->Height * p;
    }
}
//---------------------------------------------------------------------------

