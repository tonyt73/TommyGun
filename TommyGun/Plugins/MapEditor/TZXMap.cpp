/*---------------------------------------------------------------------------

    (c) 2004 Scorpio Software
        19 Wittama Drive
        Glenmore Park
        Sydney NSW 2745
        Australia

-----------------------------------------------------------------------------

    Edits the Map layout

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
//---------------------------------------------------------------------------
using namespace Scorpio;
//- CONSTANTS ---------------------------------------------------------------
const   int     g_iDefaultScreenWidth   = 256;
const   int     g_iDefaultScreenHeight  = 192;
const   int     g_iNoScreenFound        =  -1;
const   int     g_iNoActiveScreen       =  -1;
const   int     g_iTileNotFound         =  -1;
const   String  g_sTileNotFound         = "";
const   String  g_sSignature            = "Map";
const   DWORD   g_dwVersion             = 0x00000100;   // 0.0.1.0
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool ScreenCompare(TTiledScreen* S1, TTiledScreen* S2)
{
    int s1 = (S1->m_iTop * 16) + S1->m_iLeft;
    int s2 = (S2->m_iTop * 16) + S2->m_iLeft;
    return s1 < s2;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
__fastcall TZXMap::TZXMap()
:   m_bIsDirty(false),
    m_bMergeDupScreens(true),
    m_bUndoInProgress(false),
    m_iScreenWidth(g_iDefaultScreenWidth),
    m_iScreenHeight(g_iDefaultScreenHeight),
    m_iScreensAcross(16),
    m_iScreensDown(16),
    m_cBackgroundColor(clBlack)
{
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
__fastcall TZXMap::~TZXMap()
{
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::BuildScreenTable(bool bMergeDuplicates)
{
    ClearScreenTable();
    int iUniqueScreens = 0;
    for (unsigned int s = 0; s < m_Screens.size(); s++)
    {
        TScreenEntry Screen;
        Screen.m_iScreensIndex = s;
        Screen.m_iTop          = m_Screens[s]->m_iTop;
        Screen.m_iLeft         = m_Screens[s]->m_iLeft;
        iUniqueScreens++;
        if (true == bMergeDuplicates)
        {
            int iDupScreen = FindDuplicateScreen(s);
            if (g_iNoScreenFound != iDupScreen)
            {
                Screen.m_iScreensIndex = iDupScreen;
                iUniqueScreens--;
            }
        }
        m_ScreenTable.push_back(Screen);
    }
    return iUniqueScreens;
}
//---------------------------------------------------------------------------
// ClearScreenTable
/**
 * Clears the screen table entries
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::ClearScreenTable(void)
{
	m_ScreenTable.clear();
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::Clear(void)
{
	for (unsigned int s = 0; s < m_Screens.size(); s++)
	{
		DeleteScreen(s);
	}
	m_Screens.clear();
	ClearScreenTable();
	m_bIsDirty = false;
}
//---------------------------------------------------------------------------
bool __fastcall TZXMap::New(int screenWidth, int screenHeight, int screensAcross, int screensDown, bool overwrite)
{
	if (overwrite || m_Screens.size() == 0)
	{
		if (m_iScreensAcross == screensAcross && m_iScreensDown == screensDown)
		{
			// try to update the map with new screen size
			m_iScreenWidth = screenWidth;
			m_iScreenHeight = screenHeight;
			for (unsigned int s = 0; s < m_Screens.size(); s++)
			{
				for (unsigned int t = 0; t < m_Screens[s]->m_ScreenTiles.size(); t++)
				{
					TTile* tile = m_Screens[s]->m_ScreenTiles[t];
					int x = tile->m_iLeft;
					int y = tile->m_iTop;
					int w = m_TileManager->Find(tile->m_sTile)->Width;
					int h = m_TileManager->Find(tile->m_sTile)->Height;
					if (x < 0)					tile->m_iLeft = 0;
					if (y < 0)					tile->m_iTop = 0;
					if (x + w > screenWidth)	tile->m_iLeft = screenWidth - w;
					if (y + h > screenHeight)	tile->m_iTop = screenHeight - h;
				}
				for (unsigned int sp = 0; sp < m_Screens[s]->m_ScreenSprites.size(); sp++)
				{
					TSprite* sprite = m_Screens[s]->m_ScreenSprites[sp];
					int x = sprite->m_iLeft;
					int y = sprite->m_iTop;
					int w = m_SpriteManager->Find(sprite->m_sSprite)->Width;
					int h = m_SpriteManager->Find(sprite->m_sSprite)->Height;
					if (x < 0)					sprite->m_iLeft = 0;
					if (y < 0)					sprite->m_iTop = 0;
					if (x + w > screenWidth)	sprite->m_iLeft = screenWidth - w;
					if (y + h > screenHeight)	sprite->m_iTop = screenHeight - h;
				}
			}
			return true;
		}
		else
		{
			Clear();
			m_iScreenWidth = screenWidth;
			m_iScreenHeight = screenHeight;
			m_iScreensAcross = screensAcross;
			m_iScreensDown = screensDown;
			return true;
		}
	}
    return false;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::IsScreenDuplicate(int iScreen)
{
    return m_ScreenTable[iScreen].m_iScreensIndex != iScreen;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::GetDuplicateScreen(int iScreen)
{
    return m_ScreenTable[iScreen].m_iScreensIndex;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
unsigned int __fastcall TZXMap::Screens(void)
{
    int iScreens = 0;
    if (0 == m_ScreenTable.size())
    {
        iScreens = m_Screens.size();
    }
    else
    {
        iScreens = m_ScreenTable.size(); 
    }
    return iScreens;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::GetScreenTiles(int iScreen)
{
    int iTiles = g_iTileNotFound;
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        iTiles = m_Screens[iScreen]->m_ScreenTiles.size();
    }
    return iTiles;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::GetScreenPosition(int iScreen, int& iLeft, int& iTop)
{
    iLeft = 0;
    iTop  = 0;

    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        iLeft = m_Screens[iScreen]->m_iLeft;
        iTop  = m_Screens[iScreen]->m_iTop;
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::GetTileSize(const String& sTile, int& iWidth, int& iHeight)
{
    iWidth  = 0;
    iHeight = 0;
    ZXBitmap pTile = m_TileManager->Find(sTile);
    if (true == SAFE_PTR(pTile))
    {
        iWidth  = pTile->Width;
        iHeight = pTile->Height;
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::GetScreenTile(int iScreen, int iTile, TTile& Tile)
{
    bool bTileExists = false;
    if (0 != m_ScreenTable.size())
    {
        iScreen = m_ScreenTable[iScreen].m_iScreensIndex;
    }
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iTile && iTile < (int)m_Screens[iScreen]->m_ScreenTiles.size())
    {
        Tile.m_sTile = m_Screens[iScreen]->m_ScreenTiles[iTile]->m_sTile;
        Tile.m_iLeft = m_Screens[iScreen]->m_ScreenTiles[iTile]->m_iLeft;
        Tile.m_iTop  = m_Screens[iScreen]->m_ScreenTiles[iTile]->m_iTop;
    }
    return bTileExists;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::DoesTileOverlap(int iScreen, TTile* CheckTile, bool bAllowIntersections)
{
    bool bOverlaps = false;
    if (true == SAFE_PTR(CheckTile) && 0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        ZXBitmap Tile = m_TileManager->Find(CheckTile->m_sTile);
        if (true == SAFE_PTR(Tile))
        {
            int iTileX = CheckTile->m_iLeft;
			int iTileY = CheckTile->m_iTop;
			int iTileW;
			int iTileH;
			m_TileManager->GetSize(Tile, iTileW, iTileH);
            TRect TileRect(iTileX, iTileY, iTileX + iTileW, iTileY + iTileH);
            TRect TempRect;
            if (false == bAllowIntersections)
            {
                // check the tile is not intersecting any tiles in the screen
                for (unsigned int i = 0; i < m_Screens[iScreen]->m_ScreenTiles.size() && false == bOverlaps; i++)
                {
                    if (CheckTile != m_Screens[iScreen]->m_ScreenTiles[i])
                    {
                        TempRect.Left    = m_Screens[iScreen]->m_ScreenTiles[i]->m_iLeft;
                        TempRect.Top     = m_Screens[iScreen]->m_ScreenTiles[i]->m_iTop;
                        ZXBitmap TmpTile = m_TileManager->Find(m_Screens[iScreen]->m_ScreenTiles[i]->m_sTile);
                        if (true == SAFE_PTR(TmpTile))
                        {
                            int TTW;
                            int TTH;
                            m_TileManager->GetSize(TmpTile, TTW, TTH);
                            TempRect.Right  = TempRect.Left + TTW;
                            TempRect.Bottom = TempRect.Top  + TTH;
                            TRect OverRect(std::max(TileRect.Left  , TempRect.Left  ),
                                           std::max(TileRect.Top   , TempRect.Top   ),
                                           std::min(TileRect.Right , TempRect.Right ),
                                           std::min(TileRect.Bottom, TempRect.Bottom));
                            bOverlaps = OverRect.Top < OverRect.Bottom && OverRect.Left < OverRect.Right;
                        }
                    }
                }
                // check the tile is not outside the screen
                bOverlaps |= (iTileX < 0 || iTileY < 0 || iTileX + iTileW >= m_iScreenWidth || iTileY + iTileH >= m_iScreenHeight);
            }
            // check the tile is not COMPLETELY outside the screen
            bOverlaps |= (iTileX + iTileW <= 0 || iTileY + iTileH <= 0 || iTileX >= m_iScreenWidth || iTileY >= m_iScreenHeight);
        }
    }
    return bOverlaps;
}
//---------------------------------------------------------------------------
bool __fastcall TZXMap::DoesTileOverlap(int iScreen, int iTileX, int iTileY, int iTileW, int iTileH, bool bAllowIntersections)
{
    bool bOverlaps = false;
    TRect TileRect(iTileX, iTileY, iTileX + iTileW, iTileY + iTileH);
    TRect TempRect;
    if (false == bAllowIntersections)
    {
        // check the tile is not intersecting any tiles in the screen
        for (unsigned int i = 0; i < m_Screens[iScreen]->m_ScreenTiles.size() && false == bOverlaps; i++)
        {
            TempRect.Left    = m_Screens[iScreen]->m_ScreenTiles[i]->m_iLeft;
            TempRect.Top     = m_Screens[iScreen]->m_ScreenTiles[i]->m_iTop;
            ZXBitmap TmpTile = m_TileManager->Find(m_Screens[iScreen]->m_ScreenTiles[i]->m_sTile);
            if (true == SAFE_PTR(TmpTile))
            {
                int TTW;
                int TTH;
                m_TileManager->GetSize(TmpTile, TTW, TTH);
                TempRect.Right  = TempRect.Left + TTW;
                TempRect.Bottom = TempRect.Top  + TTH;
                TRect OverRect(std::max(TileRect.Left  , TempRect.Left  ),
                               std::max(TileRect.Top   , TempRect.Top   ),
                               std::min(TileRect.Right , TempRect.Right ),
                               std::min(TileRect.Bottom, TempRect.Bottom));
                bOverlaps = OverRect.Top < OverRect.Bottom && OverRect.Left < OverRect.Right;
            }
        }
        // check the tile is not outside the screen
        bOverlaps |= (iTileX < 0 || iTileY < 0 || iTileX + iTileW >= m_iScreenWidth || iTileY + iTileH >= m_iScreenHeight);
    }
    // check the tile is not COMPLETELY outside the screen
    bOverlaps |= (iTileX + iTileW <= 0 || iTileY + iTileH <= 0 || iTileX >= m_iScreenWidth || iTileY >= m_iScreenHeight);
    return bOverlaps;
}
//---------------------------------------------------------------------------
void __fastcall TZXMap::RemoveOverlapTiles(int iScreen, int iTileX, int iTileY, int iTileW, int iTileH)
{
    TRect TileRect(iTileX, iTileY, iTileX + iTileW, iTileY + iTileH);
    TRect TempRect;
    // check the tile is not intersecting any tiles in the screen
    for (unsigned int i = 0; i < m_Screens[iScreen]->m_ScreenTiles.size(); i++)
    {
        TempRect.Left    = m_Screens[iScreen]->m_ScreenTiles[i]->m_iLeft;
        TempRect.Top     = m_Screens[iScreen]->m_ScreenTiles[i]->m_iTop;
        ZXBitmap TmpTile = m_TileManager->Find(m_Screens[iScreen]->m_ScreenTiles[i]->m_sTile);
        if (true == SAFE_PTR(TmpTile))
        {
            int TTW;
            int TTH;
            m_TileManager->GetSize(TmpTile, TTW, TTH);
            TempRect.Right  = TempRect.Left + TTW;
            TempRect.Bottom = TempRect.Top  + TTH;
            TRect OverRect(std::max(TileRect.Left  , TempRect.Left  ),
                           std::max(TileRect.Top   , TempRect.Top   ),
                           std::min(TileRect.Right , TempRect.Right ),
                           std::min(TileRect.Bottom, TempRect.Bottom));
            if (OverRect.Top < OverRect.Bottom && OverRect.Left < OverRect.Right)
            {
                m_Screens[iScreen]->m_ScreenTiles.erase(m_Screens[iScreen]->m_ScreenTiles.begin() + i);
                i--;                
            }
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::Dirty(int iScreen)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        m_Screens[iScreen]->m_bDirty = true;
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::FindScreenTile(int iScreen, int X, int Y)
{
    int iTile = g_iTileNotFound;
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        TRect TempRect;
        for (unsigned int i = 0; i < m_Screens[iScreen]->m_ScreenTiles.size() && g_iTileNotFound == iTile; i++)
        {
            TempRect.Left   = m_Screens[iScreen]->m_ScreenTiles[i]->m_iLeft;
            TempRect.Top    = m_Screens[iScreen]->m_ScreenTiles[i]->m_iTop;
            ZXBitmap Tile = m_TileManager->Find(m_Screens[iScreen]->m_ScreenTiles[i]->m_sTile);
            if (true == SAFE_PTR(Tile))
            {
                int TTW;
                int TTH;
                m_TileManager->GetSize(Tile, TTW, TTH);
                TempRect.Right  = TempRect.Left + TTW;
                TempRect.Bottom = TempRect.Top  + TTH;
                if (true == PointIsInRect(X, Y, TempRect))
                {
                    iTile = i;
                }
            }
        }
    }
    return iTile;
}
//---------------------------------------------------------------------------
int __fastcall TZXMap::FindScreenSprite(int iScreen, int X, int Y)
{
    int iTile = g_iTileNotFound;
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        TRect TempRect;
        for (unsigned int i = 0; i < m_Screens[iScreen]->m_ScreenSprites.size() && g_iTileNotFound == iTile; i++)
        {
            TempRect.Left   = m_Screens[iScreen]->m_ScreenSprites[i]->m_iLeft;
            TempRect.Top    = m_Screens[iScreen]->m_ScreenSprites[i]->m_iTop;
            ZXBitmap Tile = m_SpriteManager->Find(m_Screens[iScreen]->m_ScreenSprites[i]->m_sSprite);
            if (true == SAFE_PTR(Tile))
            {
                int TTW;
                int TTH;
                m_TileManager->GetSize(Tile, TTW, TTH);
                TempRect.Right  = TempRect.Left + TTW;
                TempRect.Bottom = TempRect.Top  + TTH;
                if (true == PointIsInRect(X, Y, TempRect))
                {
                    iTile = i;
                }
            }
        }
    }
    return iTile;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 16 December 2006
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::FindScreenTiles(int iScreen, const TRect& Rect, TSelectionList& List) const
{
    List.clear();

    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        TRect TempRect;
        for (unsigned int i = 0; i < m_Screens[iScreen]->m_ScreenTiles.size(); i++)
        {
            TempRect.Left = m_Screens[iScreen]->m_ScreenTiles[i]->m_iLeft;
            TempRect.Top  = m_Screens[iScreen]->m_ScreenTiles[i]->m_iTop;
            ZXBitmap Tile = m_TileManager->Find(m_Screens[iScreen]->m_ScreenTiles[i]->m_sTile);
            if (true == SAFE_PTR(Tile))
            {
                int TTW;
                int TTH;
                m_TileManager->GetSize(Tile, TTW, TTH);
                TempRect.Right  = TempRect.Left + TTW;
                TempRect.Bottom = TempRect.Top  + TTH;
                if (true == RectsIntersect(Rect, TempRect))
                {
                    TTileSelect TileInfo;
                    TileInfo.Tile = i;
                    TileInfo.Start.x = TempRect.Left;
                    TileInfo.Start.y = TempRect.Top;
                    TileInfo.Current = TileInfo.Start;
                    TileInfo.Last    = TileInfo.Start;
                    TileInfo.TileBG  = NULL;
                    List.push_back(TileInfo);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::SetManagers(ZXTileManager* TileManager, ZXSpriteManager* SpriteManager)
{
    m_TileManager = TileManager;
    m_SpriteManager = SpriteManager;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::SetScreenSize(int iWidth, int iHeight)
{
    m_iScreenWidth  = iWidth;
    m_iScreenHeight = iHeight;
    m_bIsDirty     |= m_Screens.size() > 0 ? true : false;
    for (unsigned int i = 0; i < m_Screens.size(); i++)
    {
        if (true == SAFE_PTR(m_Screens[i]->m_bmScreen))
        {
            m_Screens[i]->m_bmScreen->Width  = iWidth;
            m_Screens[i]->m_bmScreen->Height = iHeight;
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::SetScreenGrid(int iAcross, int iDown)
{
    m_iScreensAcross = iAcross;
    m_iScreensDown   = iDown;
    m_bIsDirty      |= m_Screens.size() > 0 ? true : false;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::SetBackgroundColor(TColor cColor)
{
    m_cBackgroundColor = cColor;
    m_bIsDirty        |= m_Screens.size() > 0 ? true : false;
    for (unsigned int i = 0; i < m_Screens.size(); i++)
    {
        if (true == SAFE_PTR(m_Screens[i]->m_bmScreen))
        {
            m_Screens[i]->m_bmScreen->Canvas->Brush->Color = cColor;
            m_Screens[i]->m_bDirty = true;
        }
    }
}
//---------------------------------------------------------------------------
// ClearDirty
/**
 * Clears the dirty flag
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::ClearDirty(void)
{
    m_bIsDirty = false;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::AddScreenTile(int iScreen, TTile& Tile, eUndoMode UndoMode)
{
    return AddScreenTile(iScreen, Tile.m_sTile, Tile.m_iLeft, Tile.m_iTop, UndoMode);
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::AddScreenTile(int iScreen, const String& sTile, int iLeft, int iTop, eUndoMode UndoMode, int iIndex)
{
    bool bTileAdded = false;
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        TTile* Tile   = new TTile();
        Tile->m_sTile = sTile;
        Tile->m_iTop  = iTop;
        Tile->m_iLeft = iLeft;
        m_Screens[iScreen]->m_bDirty = true;
        int iTile = 0;
        if (-1 == iIndex || iIndex >= (int)m_Screens[iScreen]->m_ScreenTiles.size())
        {
            m_Screens[iScreen]->m_ScreenTiles.push_back(Tile);
            iTile = m_Screens[iScreen]->m_ScreenTiles.size() - 1;
        }
        else
        {
            iTile = iIndex;
            m_Screens[iScreen]->m_ScreenTiles.insert(m_Screens[iScreen]->m_ScreenTiles.begin() + iIndex, Tile);
        }
        m_bIsDirty = true;
        bTileAdded = true;
        if (false == m_bUndoInProgress && UndoMode != umSkip)
        {
            if (m_UndoInfo.empty())
            {
                m_UndoInfo.Add("Operation"  , "TileAdd"    );
                m_UndoInfo.Add("Plugin"     , "Map Editor" );
                m_UndoInfo.Add("Screen"     , iScreen      );
                m_RedoInfo.Add("Operation"  , "TileAdd"    );
                m_RedoInfo.Add("Plugin"     , "Map Editor" );
                m_RedoInfo.Add("Screen"     , iScreen      );
                if (UndoMode == umAdd)
                {
                    m_UndoInfo.Add("Description", "Add Tile " + sTile + "@" + IntToStr(iLeft) + ", " + IntToStr(iTop));
                    m_RedoInfo.Add("Description", "Add Tile " + sTile + "@" + IntToStr(iLeft) + ", " + IntToStr(iTop));
                }
                else
                {
                    m_UndoInfo.Add("Description", "Add Tiles");
                    m_RedoInfo.Add("Description", "Add Tiles");
                }
            }
            // add undo information
            KXmlInfo Info("TileInfo");
            Info.Add("Tile"       , ""          );
            Info.Add("TileIndex"  , iTile       );
            Info.Add("Left"       , iLeft       );
            Info.Add("Top"        , iTop        );
            m_UndoInfo.Add(Info);
            // set the redo information
            Info.GetNode("Tile", 0)->SetText(sTile);
            m_RedoInfo.Add(Info);
            if (UndoMode == umBatchEnd || UndoMode == umAdd)
            {
                PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&m_UndoInfo, utUndo, 0);
                PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&m_RedoInfo, utRedo, 0);
                m_UndoInfo.Reset();
                m_RedoInfo.Reset();
            }
        }
    }
    return bTileAdded;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::PointIsInRect(int X, int Y, TRect Rect)
{
    return X >= Rect.Left && X <= Rect.Right && Y >= Rect.Top && Y <= Rect.Bottom;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::RectsIntersect(const TRect& Rect1, const TRect& Rect2) const
{
    bool bIntersectsX = (Rect1.Left   >= Rect2.Left && Rect1.Left   <= Rect2.Right ) ||
                        (Rect1.Right  >= Rect2.Left && Rect1.Right  <= Rect2.Right ) ||
                        (Rect2.Left   >= Rect1.Left && Rect2.Left   <= Rect1.Right ) ||
                        (Rect2.Right  >= Rect1.Left && Rect2.Right  <= Rect1.Right );
    bool bIntersectsY = (Rect1.Top    >= Rect2.Top  && Rect1.Top    <= Rect2.Bottom) ||
                        (Rect1.Bottom >= Rect2.Top  && Rect1.Bottom <= Rect2.Bottom) ||
                        (Rect2.Top    >= Rect1.Top  && Rect2.Top    <= Rect1.Bottom) ||
                        (Rect2.Bottom >= Rect1.Top  && Rect2.Bottom <= Rect1.Bottom);
    return bIntersectsX && bIntersectsY;

}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
TTiledScreen* __fastcall TZXMap::Screen(int iScreen)
{
    return m_Screens[iScreen];
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
TTile* __fastcall TZXMap::Tile(int iScreen, int iTile)
{
    return m_Screens[iScreen]->m_ScreenTiles[iTile];
}
//---------------------------------------------------------------------------
TSprite* __fastcall TZXMap::Sprite(int iScreen, int iTile)
{
    return m_Screens[iScreen]->m_ScreenSprites[iTile];
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::MoveTile(int iScreen, int iTile, int X, int Y, eUndoMode UndoMode)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iTile && iTile < (int)m_Screens[iScreen]->m_ScreenTiles.size())
    {
        if (!m_bUndoInProgress && UndoMode != umSkip)
        {
            if (m_UndoInfo.empty())
            {
                m_UndoInfo.Add("Operation"  , "TileMove"   );
                m_UndoInfo.Add("Plugin"     , "Map Editor");
                m_UndoInfo.Add("Screen"     , iScreen     );
                m_UndoInfo.Add("Description", "Move Tile(s)");
                m_RedoInfo.Add("Operation"  , "TileMove"   );
                m_RedoInfo.Add("Plugin"     , "Map Editor");
                m_RedoInfo.Add("Screen"     , iScreen     );
                m_RedoInfo.Add("Description", "Move Tile(s)");
            }
            int SX = m_Screens[iScreen]->m_ScreenTiles[iTile]->m_iLeft;
            int SY = m_Screens[iScreen]->m_ScreenTiles[iTile]->m_iTop;
            // add undo information
            KXmlInfo Info("TileInfo");
            Info.Add("Tile"       , iTile       );
            Info.Add("X"          , SX          );
            Info.Add("Y"          , SY          );
            m_UndoInfo.Add(Info);
            // add the redo information
            Info.GetNode("X", 0)->SetText(X);
            Info.GetNode("Y", 0)->SetText(Y);
            m_RedoInfo.Add(Info);

            if (UndoMode == umBatchEnd || UndoMode == umAdd)
            {
                PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&m_UndoInfo, utUndo, 0);
                PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&m_RedoInfo, utRedo, 0);
                m_UndoInfo.Reset();
                m_RedoInfo.Reset();
            }
        }
        m_Screens[iScreen]->m_ScreenTiles[iTile]->m_iLeft = X;
        m_Screens[iScreen]->m_ScreenTiles[iTile]->m_iTop  = Y;
        m_Screens[iScreen]->m_bDirty = true;
        m_bIsDirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMap::MoveSprite(int iScreen, int iTile, int X, int Y, eUndoMode UndoMode)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iTile && iTile < (int)m_Screens[iScreen]->m_ScreenSprites.size())
    {
        m_Screens[iScreen]->m_ScreenSprites[iTile]->m_iLeft = X;
        m_Screens[iScreen]->m_ScreenSprites[iTile]->m_iTop  = Y;
        m_Screens[iScreen]->m_bDirty = true;
        m_bIsDirty = true;
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::DeleteTile(int iScreen, int iTile, eUndoMode UndoMode)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iTile && iTile < (int)m_Screens[iScreen]->m_ScreenTiles.size())
    {
        String sTile = m_Screens[iScreen]->m_ScreenTiles[iTile]->m_sTile;
        int iLeft = m_Screens[iScreen]->m_ScreenTiles[iTile]->m_iLeft;
        int iTop  = m_Screens[iScreen]->m_ScreenTiles[iTile]->m_iTop;
        SAFE_DELETE(m_Screens[iScreen]->m_ScreenTiles[iTile]);
        m_Screens[iScreen]->m_ScreenTiles.erase(m_Screens[iScreen]->m_ScreenTiles.begin() + iTile);
        m_Screens[iScreen]->m_bDirty = true;
        m_bIsDirty = true;
        if (false == m_bUndoInProgress && UndoMode != umSkip)
        {
            if (m_UndoInfo.empty())
            {
                m_UndoInfo.Add("Operation"  , "TileDel"       );
                m_UndoInfo.Add("Plugin"     , "Map Editor"    );
                m_UndoInfo.Add("Screen"     , iScreen         );
                m_RedoInfo.Add("Operation"  , "TileDel"       );
                m_RedoInfo.Add("Plugin"     , "Map Editor"    );
                m_RedoInfo.Add("Screen"     , iScreen         );
                if (UndoMode == umAdd)
                {
                    m_UndoInfo.Add("Description", "Delete Tile " + sTile + "@" + IntToStr(iLeft) + ", " + IntToStr(iTop));
                    m_RedoInfo.Add("Description", "Delete Tile " + sTile + "@" + IntToStr(iLeft) + ", " + IntToStr(iTop));
                }
                else
                {
                    m_UndoInfo.Add("Description", "Delete Tiles");
                    m_RedoInfo.Add("Description", "Delete Tiles");
                }
            }
            // add undo information
            KXmlInfo Info("TileInfo");
            Info.Add("TileIndex"  , iTile       );
            Info.Add("Tile"       , sTile       );
            Info.Add("Left"       , iLeft       );
            Info.Add("Top"        , iTop        );
            m_UndoInfo.Add(Info);
            // add the redo information
            Info.GetNode("TileIndex", 0)->SetText(-1);
            m_RedoInfo.Add(Info);
            if (UndoMode == umBatchEnd || UndoMode == umAdd)
            {
                PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&m_UndoInfo, utUndo, 0);
                PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&m_RedoInfo, utRedo, 0);
                m_UndoInfo.Reset();
                m_RedoInfo.Reset();
            }
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::RenameTile(const String& sOldName, const String& sNewName)
{
    for (unsigned int s = 0; s < m_Screens.size(); s++)
    {
        for (unsigned int t = 0; t < m_Screens[s]->m_ScreenTiles.size(); t++)
        {
            if (m_Screens[s]->m_ScreenTiles[t]->m_sTile == sOldName)
            {
                m_Screens[s]->m_ScreenTiles[t]->m_sTile = sNewName;
            }
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::RemoveTile(const String& sName)
{
    for (unsigned int s = 0; s < m_Screens.size(); s++)
    {
        for (unsigned int t = 0; t < m_Screens[s]->m_ScreenTiles.size(); t++)
        {
            if (m_Screens[s]->m_ScreenTiles[t]->m_sTile == sName)
            {
                m_Screens[s]->m_bDirty = true;
                DeleteTile(s, t, umAdd);
                t = -1;
            }
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::CountTileUsage(const String& sTile)
{
    int iCount = 0;
    for (unsigned int s = 0; s < m_Screens.size(); s++)
    {
        for (unsigned int st = 0; st < m_Screens[s]->m_ScreenTiles.size(); st++)
        {
            if (m_Screens[s]->m_ScreenTiles[st]->m_sTile == sTile)
            {
                iCount++;
            }
        }
    }
    return iCount;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::AddScreen(int iLeft, int iTop, int iIndex)
{
    int iScreen = g_iNoActiveScreen;
    TTiledScreen* Screen = new TTiledScreen();
    if (true == SAFE_PTR(Screen))
    {
        Screen->m_iLeft  = iLeft;
        Screen->m_iTop   = iTop;
        Screen->m_bDirty = true;
        Screen->m_bmScreen = new Graphics::TBitmap();
        if (true == SAFE_PTR(Screen->m_bmScreen))
        {
            Screen->m_bmScreen->PixelFormat = pf24bit;
            Screen->m_bmScreen->Canvas->Brush->Color = m_cBackgroundColor;
            Screen->m_bmScreen->Width  = m_iScreenWidth;
            Screen->m_bmScreen->Height = m_iScreenHeight;
            Screen->m_bmScreen->Canvas->FillRect(Rect(0, 0, m_iScreenWidth, m_iScreenHeight));
        }
        if (iIndex == -1 || iIndex >= (int)m_Screens.size())
        {
            iScreen = m_Screens.size();
            m_Screens.push_back(Screen);
        }
        else
        {
            iScreen = iIndex;
            m_Screens.insert(m_Screens.begin() + iIndex, Screen);
        }
        if (false == m_bUndoInProgress)
        {
            // add undo information
            KXmlInfo Undo;
            Undo.Add("Operation"  , "ScreenAdd" );
            Undo.Add("Plugin"     , "Map Editor");
            Undo.Add("Screen"     , iScreen     );
            Undo.Add("Left"       , iLeft       );
            Undo.Add("Top"        , iTop        );
            Undo.Add("Undo"       , true        );
            Undo.Add("Description", "Add Screen " + IntToStr(iScreen) + " at " + IntToStr(iLeft) + ", " + IntToStr(iTop));
            PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
            // add the redo information
            Undo.GetNode("Undo", 0)->SetText(false);
            PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
        }

        //std::sort(m_Screens.begin(), m_Screens.end(), ScreenCompare);
        m_bIsDirty = true;
    }
    return iScreen;
}
//---------------------------------------------------------------------------
// AddScreen
/**
 * Adds a new screen object to the world map
 * @returns g_iNoActiveScreen if failed to add a new screen, else it returns the index of the new screen in the world map
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::AddScreen(void)
{
    //DrawScreenTiles();
    int iScreen = g_iNoActiveScreen;
    for (int iTop = 0; iTop < m_iScreensDown && g_iNoActiveScreen == iScreen; iTop++)
    {
        for (int iLeft = 0; iLeft < m_iScreensAcross && g_iNoActiveScreen == iScreen; iLeft++)
        {
            if (g_iNoActiveScreen == FindScreen(iLeft, iTop))
            {
                iScreen = AddScreen(iLeft, iTop);
            }
        }
    }
    //std::sort(m_Screens.begin(), m_Screens.end());
    return iScreen;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::CopyScreen(int iSrc, int iDest)
{
    if (0 <= iSrc && iSrc < (int)m_Screens.size() && 0 <= iDest && iDest < (int)m_Screens.size())
    {
        // remove all tiles from the destination screen
        for (unsigned int i = 0; i < m_Screens[iDest]->m_ScreenTiles.size(); i++)
        {
            SAFE_DELETE(m_Screens[iDest]->m_ScreenTiles[i]);
        }
        // and clear the tile entries
        m_Screens[iDest]->m_ScreenTiles.clear();

        // now copy the elements from the src screen and put them in the dest screen
        for (unsigned int i = 0; i < m_Screens[iSrc]->m_ScreenTiles.size(); i++)
        {
            AddScreenTile
            (
                iDest,
                m_Screens[iSrc]->m_ScreenTiles[i]->m_sTile,
                m_Screens[iSrc]->m_ScreenTiles[i]->m_iLeft,
                m_Screens[iSrc]->m_ScreenTiles[i]->m_iTop,
                i == (m_Screens[iSrc]->m_ScreenTiles.size() - 1) ? umBatchEnd : umBatchAdd
            );
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::DeleteScreen(int iScreen)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        KXmlInfo Undo;
        if (!m_bUndoInProgress)
        {
            // add undo information
            Undo.Add("Operation"  , "ScreenDel"                );
            Undo.Add("Plugin"     , "Map Editor"               );
            Undo.Add("Screen"     , iScreen                    );
            Undo.Add("Left"       , m_Screens[iScreen]->m_iLeft);
            Undo.Add("Top"        , m_Screens[iScreen]->m_iTop );
            Undo.Add("Undo"       , true                       );
            Undo.Add("Description", "Delete Screen " + IntToStr(iScreen));
            Undo.Add("Tiles"      , m_Screens[iScreen]->m_ScreenTiles.size());
        }
        // delete all the screens tiles
        for (unsigned int i = 0; i < m_Screens[iScreen]->m_ScreenTiles.size(); i++)
        {
            if (!m_bUndoInProgress)
            {
                // the tiles to the undo info
                Undo.Add("Tile" + IntToStr(i), m_Screens[iScreen]->m_ScreenTiles[i]->m_sTile);
                Undo.Add("Left" + IntToStr(i), m_Screens[iScreen]->m_ScreenTiles[i]->m_iLeft);
                Undo.Add("Top"  + IntToStr(i), m_Screens[iScreen]->m_ScreenTiles[i]->m_iTop );
            }
            SAFE_DELETE(m_Screens[iScreen]->m_ScreenTiles[i]);
        }
        // and clear the tile entries
        m_Screens[iScreen]->m_ScreenTiles.clear();
        // remove the bitmap
        SAFE_DELETE(m_Screens[iScreen]->m_bmScreen);
        // and remove the screen object
        SAFE_DELETE(m_Screens[iScreen]);
        // and the screen entry in the list
        m_Screens.erase(m_Screens.begin() + iScreen);
        // delete screen table entry too
        for (unsigned int i = 0; i < m_ScreenTable.size(); i++)
        {
            if (m_ScreenTable[i].m_iScreensIndex == iScreen)
            {
                m_ScreenTable.erase(m_ScreenTable.begin() + i);
                --i;
            }
        }
        if (!m_bUndoInProgress)
        {
            // add the undo info
            PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
            // add the redo information
            Undo.GetNode("Undo", 0)->SetText(false);
            PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
        }
        m_bIsDirty = true;
    }
}
//---------------------------------------------------------------------------
// FindScreen
/**
 * Finds a screen at a given world map coordinate
 * @param   iLeft   the left coordinate in the world map
 * @param   iTop    the top coordinate in the world map
 * @returns the screen index of the screen in the screen table
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::FindScreen(int iLeft, int iTop)
{
    int iScreen = g_iNoActiveScreen;
    if (0 == m_ScreenTable.size())
    {
        for (unsigned int i = 0; i < m_Screens.size() && g_iNoActiveScreen == iScreen; i++)
        {
            if (m_Screens[i]->m_iLeft == iLeft && m_Screens[i]->m_iTop == iTop)
            {
                iScreen = i;
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < m_ScreenTable.size() && g_iNoActiveScreen == iScreen; i++)
        {
            if (m_ScreenTable[i].m_iLeft == iLeft && m_ScreenTable[i].m_iTop == iTop)
            {
                iScreen = m_ScreenTable[i].m_iScreensIndex;
            }
        }
    }
    return iScreen;
}
//---------------------------------------------------------------------------
// NumberOfTiles
/**
 * Returns the number of tiles in the active scren
 * @returns the number of tile in the active screen
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::NumberOfTiles(int iScreen)
{
    int iTiles = 0;
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        iTiles = m_Screens[iScreen]->m_ScreenTiles.size();
    }
    return iTiles;
}
//---------------------------------------------------------------------------
// Sort
/**
 * Sorts the screen table
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::Sort(void)
{
    std::sort(m_Screens.begin(), m_Screens.end(), ScreenCompare);
    m_bIsDirty = true;
}
//---------------------------------------------------------------------------
// FindDuplicateScreen
/**
 * Checks to see if a screen is a duplicate of an existing screen
 * @param   iScreen the screen to check for a duplicate of
 * @returns g_iNoScreenFound if no duplicate screen exists, else it returns the number of the screen it is a duplicate of
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::FindDuplicateScreen(int iScreen)
{
    int iDuplicateScreen = g_iNoScreenFound;
    for (int s = 0; s < iScreen && g_iNoScreenFound == iDuplicateScreen; s++)
    {
        // does the number of tiles on each screen match?
        if (m_Screens[iScreen]->m_ScreenTiles.size() == m_Screens[s]->m_ScreenTiles.size())
        {
            bool bTheSame = true;
            // now compare all the tiles in both screens
            for (unsigned int t = 0; t < m_Screens[iScreen]->m_ScreenTiles.size() && true == bTheSame; t++)
            {
                TTile* Tile = m_Screens[iScreen]->m_ScreenTiles[t];
                if (false == TileIsInScreen(s, Tile))
                {
                    bTheSame = false;
                }
            }
            if (true == bTheSame)
            {
                iDuplicateScreen = s;
            }
        }
    }
    return iDuplicateScreen;
}
//---------------------------------------------------------------------------
// TileIsInScreen
/**
 * Checks to see if a tile exists in another screen
 * @param   iScreen the screen to check
 * @param   Tile    the tile to check for
 * @returns true if tile exists in another screen
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::TileIsInScreen(int iScreen, TTile* Tile)
{
    if (true == SAFE_PTR(Tile) && 0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        for (unsigned int t = 0; t < m_Screens[iScreen]->m_ScreenTiles.size(); t++)
        {
            if (Tile->m_sTile == m_Screens[iScreen]->m_ScreenTiles[t]->m_sTile &&
                Tile->m_iTop  == m_Screens[iScreen]->m_ScreenTiles[t]->m_iTop  &&
                Tile->m_iLeft == m_Screens[iScreen]->m_ScreenTiles[t]->m_iLeft)
            {
                return true;
            }
        }
    }
    return false;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::Load(KXmlInfo& xmlInfo)
{
    bool bLoaded = false;
    // find the image editor node
    KXmlInfo* MapNode;
    KXmlInfo* SettingsNode;
    m_bUndoInProgress = true;
    if (xmlInfo.Find(SettingsNode, "Properties", 0))
    {
        if (xmlInfo.Find(MapNode, "Screens", 0))
        {
            bLoaded = true;
            KXmlInfo* node = NULL;
            // get the type of the image list
            KXmlInfo* nScreenWidth     = SettingsNode->GetNode("ScreenWidth", 0);
            KXmlInfo* nScreenHeight    = SettingsNode->GetNode("ScreenHeight", 0);
            KXmlInfo* nScreensAcross   = SettingsNode->GetNode("ScreensAcross", 0);
            KXmlInfo* nScreensDown     = SettingsNode->GetNode("ScreensDown", 0);
            KXmlInfo* nBackgroundColor = SettingsNode->GetNode("BackgroundColor", 0);

            if (nScreenWidth && nScreenHeight && nScreensAcross && nScreensDown && nBackgroundColor)
            {
                SetScreenSize(nScreenWidth->GetInt(), nScreenHeight->GetInt());
                SetScreenGrid(nScreensAcross->GetInt(), nScreensDown->GetInt());
                SetBackgroundColor(StringToColor(nBackgroundColor->GetText()));
                int screen = 0;
                // load the image lists (loop thru "Screen" nodes)
                for (KXmlNodes::iterator it = MapNode->begin(); it != MapNode->end() && true == bLoaded; it++)
                {
                    bLoaded = LoadScreen(*(*it));
                }
            }
            else
            {
                bLoaded = false;
            }
        }
    }
    m_bUndoInProgress = false;
    // maps are now no longer dirty
    m_bIsDirty = false;
    return bLoaded;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
bool __fastcall TZXMap::LoadScreen(KXmlInfo& xmlInfo)
{
    bool bLoaded = false;
    KXmlInfo* nDupOf    = xmlInfo.GetNode("DuplicateOf", 0);
    KXmlInfo* nLeft     = xmlInfo.GetNode("Left", 0);
    KXmlInfo* nTop      = xmlInfo.GetNode("Top", 0);
    KXmlInfo* nTiles    = xmlInfo.GetNode("Tiles", 0);
    KXmlInfo* nSprites  = xmlInfo.GetNode("Sprites", 0);

    if (nLeft && nTop)
    {
        int iScreen = AddScreen(nLeft->GetInt(), nTop->GetInt());
        bLoaded = true;

        if (nDupOf)
        {
            // screen is a duplicate of another so just copy that screen
            CopyScreen(nDupOf->GetInt(), iScreen);
        }
        else if (nTiles)
        {
            // we have tiles so lets load 'em
            for (KXmlNodes::iterator it = nTiles->begin(); it != nTiles->end() && true == bLoaded; it++)
            {
                KXmlInfo* nName = (*it)->GetNode("Name", 0);
                nLeft = (*it)->GetNode("Left", 0);
                nTop = (*it)->GetNode("Top", 0);
                if (nName && nLeft && nTop)
                {
                    AddScreenTile
                    (
                        iScreen,
                        nName->GetText(),
                        nLeft->GetInt(),
                        nTop->GetInt(),
                        umSkip
                    );
                }
                else
                {
                    bLoaded = false;
                }
            }
        }
        if (nSprites)
        {
            // we have sprites so lets load 'em
            for (KXmlNodes::iterator it = nSprites->begin(); it != nSprites->end() && true == bLoaded; it++)
            {
                KXmlInfo* nName = (*it)->GetNode("Name", 0);
                nLeft = (*it)->GetNode("Left", 0);
                nTop = (*it)->GetNode("Top", 0);
                KXmlInfo* nType = (*it)->GetNode("Type", 0);
                if (nName && nLeft && nTop && nType)
                {
                    AddScreenSprite
                    (
                        iScreen,
                        nName->GetText(),
                        nType->GetInt(),
                        nLeft->GetInt(),
                        nTop->GetInt()
                    );
                }
                else
                {
                    bLoaded = false;
                }
            }
        }
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::Save(KXmlInfo& xmlInfo, bool bCleanDirty)
{
    // remove the old map editor node
    KXmlInfo* Node;
    if (xmlInfo.Find(Node, "Screens", 0))
    {
        xmlInfo.Remove(Node);
    }
    if (xmlInfo.Find(Node, "Properties", 0))
    {
        xmlInfo.Remove(Node);
    }
    // create a new map editor node
    KXmlInfo Settings("Properties");
    // store the map details
    Settings.Add("ScreenWidth", m_iScreenWidth);
    Settings.Add("ScreenHeight", m_iScreenHeight);
    Settings.Add("ScreensAcross", m_iScreensAcross);
    Settings.Add("ScreensDown", m_iScreensDown);
    Settings.Add("BackgroundColor", ColorToString(m_cBackgroundColor));
    Settings.Add("GridWidth", m_iTileWidth);
    Settings.Add("GridHeight", m_iTileHeight);
    xmlInfo.Add(Settings);
    KXmlInfo Map("Screens");
    // store the screens of the map
    for (unsigned int i = 0; i < Screens(); i++)
    {
        SaveScreen(Map, i);
    }
    // add the new map node to the xml object
    xmlInfo.Add(Map);
    // maps are now no longer dirty
    if (bCleanDirty)
    {
        m_bIsDirty = false;
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::SaveScreen(KXmlInfo& xmlInfo, int iScreen)
{
    // save the screen details
    KXmlInfo Screen("Screen");
    bool bNotDuplicate = true;
    if (m_bMergeDupScreens)
    {
        int iDupScreen = FindDuplicateScreen(iScreen);
        if (iDupScreen != g_iNoScreenFound)
        {
            Screen.Add("Left", m_Screens[iScreen]->m_iLeft);
            Screen.Add("Top", m_Screens[iScreen]->m_iTop);
            Screen.Add("DuplicateOf", iDupScreen);
            bNotDuplicate = false;
        }
    }
    if (bNotDuplicate)
    {
        Screen.Add("Left", m_Screens[iScreen]->m_iLeft);
        Screen.Add("Top", m_Screens[iScreen]->m_iTop);
        // save all the tiles of the screen
        KXmlInfo Tiles("Tiles");
        KXmlInfo Tile;
        for (unsigned int i = 0; i < m_Screens[iScreen]->m_ScreenTiles.size(); i++)
        {
            Tile.Reset();
            Tile.SetName("Tile");
            // save the name of the tile
            Tile.Add("Name", m_Screens[iScreen]->m_ScreenTiles[i]->m_sTile);
            // save the left and top positions of the tile
            Tile.Add("Left", m_Screens[iScreen]->m_ScreenTiles[i]->m_iLeft);
            Tile.Add("Top", m_Screens[iScreen]->m_ScreenTiles[i]->m_iTop);
            // add the tile to the tiles list
            Tiles.Add(Tile);
        }
        // add the tiles to the screen
        Screen.Add(Tiles);
    }

    // save all the sprites of the screen
    KXmlInfo Sprites("Sprites");
    KXmlInfo Sprite;
    for (unsigned int i = 0; i < m_Screens[iScreen]->m_ScreenSprites.size(); i++)
    {
        Sprite.Reset();
        Sprite.SetName("Sprite");
        // save the name of the sprite
        Sprite.Add("Name", m_Screens[iScreen]->m_ScreenSprites[i]->m_sSprite);
        // save the type of the sprite
        Sprite.Add("Type", m_Screens[iScreen]->m_ScreenSprites[i]->m_iType);
        // save the left and top positions of the tile
        Sprite.Add("Left", m_Screens[iScreen]->m_ScreenSprites[i]->m_iLeft);
        Sprite.Add("Top", m_Screens[iScreen]->m_ScreenSprites[i]->m_iTop);
        // add the tile to the tiles list
        Sprites.Add(Sprite);
    }
    // add the sprites to the screen
    Screen.Add(Sprites);

    // and add the screen to the xml object
    xmlInfo.Add(Screen);
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
unsigned int __fastcall TZXMap::Bytes(void)
{
    int iUniqueScreens = BuildScreenTable(!m_bMergeDupScreens);
    unsigned int iBytes = 0;
    for (unsigned int i = 0; i < m_ScreenTable.size(); ++i)
    {
        if (false == IsScreenDuplicate(i))
        {
            iBytes += 1 + (3 * m_Screens[i]->m_ScreenTiles.size());
        }
    }
    return iBytes;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::BringToFront(int iScreen, int iTile)
{
    int iNewTile = iTile;
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iTile && iTile < (int)m_Screens[iScreen]->m_ScreenTiles.size() - 1)
    {
        TTile* tmpTile = m_Screens[iScreen]->m_ScreenTiles[iTile];
        m_Screens[iScreen]->m_ScreenTiles[iTile] = m_Screens[iScreen]->m_ScreenTiles[m_Screens[iScreen]->m_ScreenTiles.size() - 1];
        m_Screens[iScreen]->m_ScreenTiles[m_Screens[iScreen]->m_ScreenTiles.size() - 1] = tmpTile;
        iNewTile = m_Screens[iScreen]->m_ScreenTiles.size() - 1;
    }
    return iNewTile;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::SendToBack(int iScreen, int iTile)
{
    int iNewTile = iTile;
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 < iTile && iTile < (int)m_Screens[iScreen]->m_ScreenTiles.size())
    {
        TTile* tmpTile = m_Screens[iScreen]->m_ScreenTiles[iTile];
        m_Screens[iScreen]->m_ScreenTiles[iTile] = m_Screens[iScreen]->m_ScreenTiles[0];
        m_Screens[iScreen]->m_ScreenTiles[0] = tmpTile;
        iNewTile = 0;
    }
    return iNewTile;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
int __fastcall TZXMap::FindTile(int iScreen, const String& sTile, int iLeft, int iTop)
{
    TTiledScreen* pScreen = Screen(iScreen);
    if (true == SAFE_PTR(pScreen))
    {
        for (int i = 0; i < (int)pScreen->m_ScreenTiles.size(); i++)
        {
            if (iLeft == pScreen->m_ScreenTiles[i]->m_iLeft && iTop == pScreen->m_ScreenTiles[i]->m_iTop && pScreen->m_ScreenTiles[i]->m_sTile == sTile)
            {
                return i;
            }
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::UndoRestore(KXmlInfo* xmlInfo)
{
    KXmlInfo* pOperation = xmlInfo->GetNode("Operation", 0);

    if (true == SAFE_PTR(pOperation))
    {
        String sOperation = pOperation->GetText();
        m_bUndoInProgress = true;
        if (sOperation == "TileMove")
        {
            UndoTileMove(xmlInfo);
        }
        else if (sOperation == "TileAdd")
        {
            UndoTileAdd(xmlInfo);
        }
        else if (sOperation == "TileDel")
        {
            UndoTileDel(xmlInfo);
        }
        else if (sOperation == "ScreenAdd")
        {
            UndoScreenAdd(xmlInfo);
        }
        else if (sOperation == "ScreenDel")
        {
            UndoScreenDel(xmlInfo);
        }
        else if (sOperation == "ScreenSwap")
        {
            UndoScreenSwap(xmlInfo);
        }
        m_bUndoInProgress = false;
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::UndoTileMove(KXmlInfo* xmlInfo)
{
    int iScreen = xmlInfo->GetNode("Screen", 0)->GetInt();
    for (KXmlNodes::iterator it = xmlInfo->begin(); it != xmlInfo->end(); it++)
    {
        if ((*it)->GetName() == "TileInfo")
        {
            int iLeft   = (*it)->GetNode("X", 0)->GetInt();
            int iTop    = (*it)->GetNode("Y", 0)->GetInt();
            int iTile   = (*it)->GetNode("Tile", 0)->GetInt();
            MoveTile(iScreen, iTile, iLeft, iTop, umSkip);
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::UndoTileAdd(KXmlInfo* xmlInfo)
{
    int iScreen = xmlInfo->GetNode("Screen", 0)->GetInt();
    for (KXmlNodes::iterator it = xmlInfo->begin(); it != xmlInfo->end(); it++)
    {
        if ((*it)->GetName() == "TileInfo")
        {
            int iLeft   = (*it)->GetNode("Left", 0)->GetInt();
            int iTop    = (*it)->GetNode("Top", 0)->GetInt();
            int iTile   = (*it)->GetNode("TileIndex", 0)->GetInt();
            String sTile= (*it)->GetNode("Tile", 0)->GetText();

            if (sTile == "")
            {
                // undo - ie. remove the screen tile
                //int iTile = FindTile(iScreen, sTile, iLeft, iTop);
                DeleteTile(iScreen, iTile, umSkip);
            }
            else
            {
                // redo - ie. add the screen tile back
                AddScreenTile(iScreen, sTile, iLeft, iTop, umSkip, iTile);
            }
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::UndoTileDel(KXmlInfo* xmlInfo)
{
    int iScreen = xmlInfo->GetNode("Screen", 0)->GetInt();
    for (KXmlNodes::iterator it = xmlInfo->begin(); it != xmlInfo->end(); it++)
    {
        if ((*it)->GetName() == "TileInfo")
        {
            int iLeft   = (*it)->GetNode("Left", 0)->GetInt();
            int iTop    = (*it)->GetNode("Top", 0)->GetInt();
            int iTile   = (*it)->GetNode("TileIndex", 0)->GetInt();
            String sTile= (*it)->GetNode("Tile", 0)->GetText();

            if (-1 != iTile)
            {
                // undo - ie. add the screen tile
                AddScreenTile(iScreen, sTile, iLeft, iTop, umSkip, iTile);
            }
            else
            {
                // redo - ie. delete the screen tile
                int iTile = FindTile(iScreen, sTile, iLeft, iTop);
                DeleteTile(iScreen, iTile, umSkip);
            }
        }
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::UndoScreenAdd(KXmlInfo* xmlInfo)
{
    int iScreen = xmlInfo->GetNode("Screen", 0)->GetInt();
    int iLeft   = xmlInfo->GetNode("Left", 0)->GetInt();
    int iTop    = xmlInfo->GetNode("Top", 0)->GetInt();
    bool bUndo  = xmlInfo->GetNode("Undo", 0)->GetBool();

    if (bUndo)
    {
        // undo - ie. delete the screen
        DeleteScreen(iScreen);
    }
    else
    {
        // redo - ie. add the screen back
        AddScreen(iLeft, iTop);
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::UndoScreenDel(KXmlInfo* xmlInfo)
{
    int iScreen = xmlInfo->GetNode("Screen", 0)->GetInt();
    int iLeft   = xmlInfo->GetNode("Left", 0)->GetInt();
    int iTop    = xmlInfo->GetNode("Top", 0)->GetInt();
    bool bUndo  = xmlInfo->GetNode("Undo", 0)->GetBool();

    if (bUndo)
    {
        // undo - ie. add the screen back
        AddScreen(iLeft, iTop, iScreen);

        int iTiles = xmlInfo->GetNode("Tiles", 0)->GetInt();
        for (int i = 0; i < iTiles; i++)
        {
            String sTile = xmlInfo->GetNode("Tile" + IntToStr(i), 0)->GetText();
            int    iLeft = xmlInfo->GetNode("Left" + IntToStr(i), 0)->GetInt();
            int    iTop  = xmlInfo->GetNode("Top"  + IntToStr(i), 0)->GetInt();
            AddScreenTile(iScreen, sTile, iLeft, iTop, umSkip);
        }
    }
    else
    {
        // redo - ie. delete the screen
        DeleteScreen(iScreen);
    }
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
void __fastcall TZXMap::UndoScreenSwap(KXmlInfo* xmlInfo)
{
    int iScreen1 = xmlInfo->GetNode("Screen1", 0)->GetInt();
    int iLeft1   = xmlInfo->GetNode("Left1", 0)->GetInt();
    int iTop1    = xmlInfo->GetNode("Top1", 0)->GetInt();
    int iScreen2 = xmlInfo->GetNode("Screen2", 0)->GetInt();
    int iLeft2   = xmlInfo->GetNode("Left2", 0)->GetInt();
    int iTop2    = xmlInfo->GetNode("Top2", 0)->GetInt();
    bool bUndo   = xmlInfo->GetNode("Undo", 0)->GetBool();

    if (bUndo)
    {
        Screen(iScreen1)->m_iLeft = iLeft1;
        Screen(iScreen1)->m_iTop  = iTop1;
        Screen(iScreen2)->m_iLeft = iLeft2;
        Screen(iScreen2)->m_iTop  = iTop2;
    }
    else
    {
        Screen(iScreen1)->m_iLeft = iLeft2;
        Screen(iScreen1)->m_iTop  = iTop2;
        Screen(iScreen2)->m_iLeft = iLeft1;
        Screen(iScreen2)->m_iTop  = iTop1;
    }
    //Screen(iScreen1)->m_bDirty = true;
    //Screen(iScreen2)->m_bDirty = true;
    m_bIsDirty = true;
}
//---------------------------------------------------------------------------
//
/**
 *
 * @param
 * @author  Tony Thompson
 * @date    Created 2 January 2007
 */
//---------------------------------------------------------------------------
ZXComments* __fastcall TZXMap::Comments(int iScreen)
{
    ZXComments* Comments = NULL;
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        Comments = &m_Screens[iScreen]->m_Comments;
    }
    return Comments;
}
//---------------------------------------------------------------------------
int __fastcall TZXMap::GetScreenSprites(int iScreen)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        return m_Screens[iScreen]->m_ScreenSprites.size();
    }
    return 0;
}
//---------------------------------------------------------------------------
bool __fastcall TZXMap::GetScreenSprite(int iScreen, int iSprite, TSprite& Sprite)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iSprite && iSprite < (int)m_Screens[iScreen]->m_ScreenSprites.size())
    {
        Sprite = *m_Screens[iScreen]->m_ScreenSprites[iSprite];
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall TZXMap::AddScreenSprite(int iScreen, const String& sSprite)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        TSprite* sprite = new TSprite();
        sprite->m_sSprite = sSprite;
        sprite->m_iType = 0;
        sprite->m_iLeft = (256 - 16) / 2;
        sprite->m_iTop = (192 - 16) / 2;
        m_Screens[iScreen]->m_ScreenSprites.push_back(sprite);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall TZXMap::AddScreenSprite(int iScreen, const String& sSprite, int iType, int iLeft, int iTop)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size())
    {
        TSprite* sprite = new TSprite();
        sprite->m_sSprite = sSprite;
        sprite->m_iType = iType;
        sprite->m_iLeft = iLeft;
        sprite->m_iTop = iTop;
        m_Screens[iScreen]->m_ScreenSprites.push_back(sprite);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TZXMap::RemoveScreenSprite(int iScreen, int iSprite)
{
	if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iSprite && iSprite < (int)m_Screens[iScreen]->m_ScreenSprites.size())
    {
        m_Screens[iScreen]->m_ScreenSprites.erase(m_Screens[iScreen]->m_ScreenSprites.begin() + iSprite);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMap::SetScreenSpriteImage(int iScreen, int iSprite, const String& sSprite)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iSprite && iSprite < (int)m_Screens[iScreen]->m_ScreenSprites.size())
    {
        m_Screens[iScreen]->m_ScreenSprites[iSprite]->m_sSprite = sSprite;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMap::SetScreenSpriteType(int iScreen, int iSprite, int iType)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iSprite && iSprite < (int)m_Screens[iScreen]->m_ScreenSprites.size())
    {
        m_Screens[iScreen]->m_ScreenSprites[iSprite]->m_iType = iType;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMap::SetScreenSpritePos(int iScreen, int iSprite, int iX, int iY)
{
    if (0 <= iScreen && iScreen < (int)m_Screens.size() && 0 <= iSprite && iSprite < (int)m_Screens[iScreen]->m_ScreenSprites.size())
    {
        m_Screens[iScreen]->m_ScreenSprites[iSprite]->m_iLeft = iX;
        m_Screens[iScreen]->m_ScreenSprites[iSprite]->m_iTop = iY;
    }
}
//---------------------------------------------------------------------------

