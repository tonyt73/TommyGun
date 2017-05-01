/*---------------------------------------------------------------------------

    (c) 2004 Scorpio Software
        19 Wittama Drive
        Glenmore Park
        Sydney NSW 2745
        Australia

-----------------------------------------------------------------------------

    Edits the Screens

    $Workfile::                                                           $
    $Revision::                                                           $
        $Date::                                                           $
      $Author::                                                           $

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
#include <vcl\Clipbrd.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//- CONSTANTS ---------------------------------------------------------------
const   String  g_sTileNotFound         =  "";
const   int     g_iTileNotFound         =  -1;
const   int     g_iNoActiveScreen       =  -1;
const   int     g_iScreenNotFound       =  -1;
const   int     g_iMaximumTileSize      = 256;
const   int     g_iDefaultGridSize      =  16;
//---------------------------------------------------------------------------
__fastcall TZXMapEditor::TZXMapEditor()
:   m_bmMapBackground(NULL),
    m_imgScreenEditor(NULL),
    m_imgMapEditor(NULL),
    m_Mode(moSelectTile),
    m_bScreenCursorDrawn(false),
    m_bAllowIntersections(false),
    m_bOverwriteOverlaps(false),
    m_bSnapToGrid(true),
    m_bDraggingScreen(false),
    m_bUndoInProgress(false),
    m_bPlaceTileAdded(false),
    m_iScreenBeingDragged(g_iNoActiveScreen),
    m_iActiveScreen(g_iNoActiveScreen),
    m_iStartScreen(g_iNoActiveScreen),
    m_iGridWidth(g_iDefaultGridSize),
    m_iGridHeight(g_iDefaultGridSize),
    m_MouseZone(mzNone),
    m_iMapScale(100),
    m_iLastScreenX(0),
    m_iLastScreenY(0)
{
    m_bmMapBackground = new Graphics::TBitmap();
    if (true == SAFE_PTR(m_bmMapBackground))
    {
        m_bmMapBackground->Width        = g_iMaximumTileSize;
        m_bmMapBackground->Height       = g_iMaximumTileSize;
        m_bmMapBackground->PixelFormat  = pf24bit;
    }
    m_Selection.Active = false;
}
//---------------------------------------------------------------------------
__fastcall TZXMapEditor::~TZXMapEditor()
{
    ClearSelection();
    // clear the tile list
    Clear();
    SAFE_DELETE(m_bmMapBackground );
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetMap(TZXMap* Map)
{
    m_Map = Map;
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetCanvas(TImage* ScreenImage, TImage* MapImage)
{
    m_imgScreenEditor = ScreenImage;
    if (true == SAFE_PTR(m_imgScreenEditor))
    {
        m_imgScreenEditor->Parent->DoubleBuffered = true;
        FOnScreenMouseDown = m_imgScreenEditor->OnMouseDown;
        FOnScreenMouseMove = m_imgScreenEditor->OnMouseMove;
        FOnScreenMouseUp   = m_imgScreenEditor->OnMouseUp;
        m_imgScreenEditor->OnMouseDown = ScreenMouseDown;
        m_imgScreenEditor->OnMouseMove = ScreenMouseMove;
        m_imgScreenEditor->OnMouseUp   = ScreenMouseUp;
    }
	m_imgMapEditor = MapImage;
    if (true == SAFE_PTR(m_imgMapEditor))
    {
        m_imgMapEditor->Picture->Bitmap->PixelFormat = pf24bit;
        m_imgMapEditor->Parent->DoubleBuffered = true;
        FOnMapMouseDown = m_imgMapEditor->OnMouseDown;
        FOnMapMouseMove = m_imgMapEditor->OnMouseMove;
        FOnMapMouseUp   = m_imgMapEditor->OnMouseUp;
        m_imgMapEditor->OnMouseDown = MapMouseDown;
        m_imgMapEditor->OnMouseMove = MapMouseMove;
        m_imgMapEditor->OnMouseUp   = MapMouseUp;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetManagers(ZXTileManager* TileManager, ZXSpriteManager* SpriteManager, ZXObjectManager* ObjectManager)
{
    m_TileManager = TileManager;
    m_SpriteManager = SpriteManager;
    m_ObjectManager = ObjectManager;
    m_TileManager->OnClick = OnTileClick;
    //m_SpriteManager->OnClick = OnTileClick;
    m_Map->SetManagers(TileManager, SpriteManager);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetActiveScreen(int iScreen, bool bUpdate)
{
    ClearSelection();
    m_iActiveScreen = g_iNoActiveScreen;
    if (0 <= iScreen && iScreen < (int)m_Map->Screens())
    {
        m_iActiveScreen = iScreen;
    }
    if (true == bUpdate)
    {
        UpdateScreenWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetBackgroundColor(TColor cColor)
{
    m_Map->SetBackgroundColor(cColor);
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetScreenSize(int iWidth, int iHeight)
{
    m_Map->SetScreenSize(iWidth, iHeight);
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetGridInfo(bool bSnapToGrid, int iWidth, int iHeight)
{
    m_bSnapToGrid = bSnapToGrid;
    m_iGridWidth  = iWidth;
    m_iGridHeight = iHeight;
    m_Map->TileWidth = iWidth;
    m_Map->TileHeight = iHeight;
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetScreenGrid(int iAcross, int iDown)
{
    m_Map->SetScreenGrid(iAcross, iDown);
    UpdateMapWindow();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetScreenGap(int iGap)
{
    m_iScreenGap = iGap;
    UpdateMapWindow();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetScreenScale(int iScale)
{
    m_iScreenScale = iScale;
    UpdateScreenWindow();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetMapScale(int iScale)
{
    m_iMapScale = iScale;
    UpdateMapWindow();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::OnTileClick(TObject* Sender)
{
    // a tile has been selected
    RestoreScreenTiles();
    if (moTileFree <= m_Mode && m_Mode <= moTileCircleFill)
    {
        if (!m_bPlaceTileAdded)
        {
            //PlaceTile();
        }
        else
        {
            m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[0].Tile)->m_sTile = m_TileManager->Selected;
        }
    }
    DrawScreen(m_iActiveScreen);
    UpdateScreenEditor();
    // refresh the map window
    m_imgMapEditor->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::ScreenMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (FOnScreenMouseDown)
    {
        FOnScreenMouseDown(Sender, Button, Shift, X, Y);
    }
    if (mbLeft == Button && g_iNoActiveScreen != m_iActiveScreen)
    {
        EraseMapCursor();
        //float dx, dy;
        //m_TileManager->GetScalar(dx, dy);
        X = (X / m_iScreenScale) - m_iScreenX;
        Y = (Y / m_iScreenScale) - m_iScreenY;
        if (moAddComment == m_Mode)
        {
            
        }
        else if (moTileFree <= m_Mode && m_Mode <= moTileCircleFill)
        {
            m_TileShapeBounds.Left   = X;
            m_TileShapeBounds.Top    = Y;
            m_TileShapeBounds.Right  = X;
            m_TileShapeBounds.Bottom = Y;
            ClearSelection();
            m_bPlaceTileAdded = false;
            m_Selection.Active = false;
            m_PointList.clear();
            DrawTilesShape();
        }
        else if (moSelectSprite == m_Mode)
        {
            ClearSelection();

            m_Selection.Active = true;
            m_Selection.Screen = m_iActiveScreen;
            m_Selection.Rect   = TRect(X, Y, X, Y);
            int iSprite = m_Map->FindScreenSprite(m_iActiveScreen, X, Y);
            if (iSprite != -1)
            {
                TTileSelect TileInfo;
                TileInfo.Tile    = iSprite;
                TileInfo.Start.x = m_Map->Sprite(m_iActiveScreen, iSprite)->m_iLeft;
                TileInfo.Start.y = m_Map->Sprite(m_iActiveScreen, iSprite)->m_iTop;
                TileInfo.Current = TileInfo.Start;
                TileInfo.Last    = TileInfo.Start;
                TileInfo.TileBG  = NULL;

                m_Selection.ActiveList.push_back(TileInfo);
            }
            m_Selection.Active = false;
        }
        else if (moSelectObject == m_Mode)
        {
            ClearSelection();
            m_Selection.Active = true;
            m_Selection.Screen = m_iActiveScreen;
            m_Selection.Rect   = TRect(X, Y, X, Y);
            int iObject = m_ObjectManager->FindObject(m_iActiveScreen, X, Y);
            if (iObject != -1)
            {
                TMapObject object;
                m_ObjectManager->GetObject(iObject, object);
                TTileSelect TileInfo;
                TileInfo.Tile    = iObject;
                TileInfo.Start.x = object.m_iLeft;
                TileInfo.Start.y = object.m_iTop;
                TileInfo.Current = TileInfo.Start;
                TileInfo.Last    = TileInfo.Start;
                TileInfo.TileBG  = NULL;

                m_Selection.ActiveList.push_back(TileInfo);
                m_Selection.Active = false;
            }
        }
        else if (moSelectTile == m_Mode)
        {
            if (m_Selection.ActiveList.size() && IsSelected(m_Map->FindScreenTile(m_iActiveScreen, X, Y)))
            {
                // a tile that is part of the active selection list is clicked on so start a move or clone operation
                if (Shift.Contains(ssCtrl))
                {
                    // clone the tiles in active list
                    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
                    {
                        m_Map->AddScreenTile
                        (
                            m_iActiveScreen,
                           *m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[i].Tile),
                           i == (m_Selection.ActiveList.size() - 1) ? umBatchEnd : umBatchAdd
                        );
                        m_Selection.ActiveList[i].Tile = m_Map->NumberOfTiles(m_iActiveScreen) - 1;
                    }
                }
            }
            else
            {
                if (!Shift.Contains(ssCtrl))
                {
                    ClearSelection();
                }

                m_Selection.Active = true;
                m_Selection.Screen = m_iActiveScreen;
                m_Selection.Rect   = TRect(X, Y, X, Y);
                int iTile = m_Map->FindScreenTile(m_iActiveScreen, X, Y);
                if (iTile != -1)
                {
                    TTileSelect TileInfo;
                    TileInfo.Tile    = iTile;
                    TileInfo.Start.x = m_Map->Tile(m_iActiveScreen, iTile)->m_iLeft;
                    TileInfo.Start.y = m_Map->Tile(m_iActiveScreen, iTile)->m_iTop;
                    TileInfo.Current = TileInfo.Start;
                    TileInfo.Last    = TileInfo.Start;
                    TileInfo.TileBG  = NULL;

                    m_Selection.ActiveList.push_back(TileInfo);
                    m_Selection.Active = false;
                }
                else
                {
                    m_Map->FindScreenTiles(m_iActiveScreen, TRect(X, Y, X + 1, Y + 1), m_Selection.SelectList);
                }
            }
            DrawScreen(m_iActiveScreen);
        }
        UpdateScreenEditor();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::ScreenMouseMove(TObject* Sender, TShiftState Shift, int X, int Y)
{
    if (FOnScreenMouseMove)
    {
        FOnScreenMouseMove(Sender, Shift, X, Y);
    }
    m_MouseZone = mzScreenWindow;
    if (g_iNoActiveScreen != m_iActiveScreen)
    {
        //float dx, dy;
        //m_TileManager->GetScalar(dx, dy);
        X = (X - (m_iScreenX * m_iScreenScale)) / m_iScreenScale;
        Y = (Y - (m_iScreenY * m_iScreenScale)) / m_iScreenScale;
        if (moTileFree <= m_Mode && m_Mode <= moTileCircleFill)
        {
            if (Shift.Contains(ssLeft))
            {
                m_TileShapeBounds.Right  = X;
                m_TileShapeBounds.Bottom = Y;
                DrawTilesShape();
            }
        }
        else if (moSelectSprite == m_Mode)
        {
            SetStatusSlot(m_PluginHandle, "[No Sprite]", 2);
            if (Shift.Contains(ssLeft))
            {
                if (!m_Selection.Active &&  m_Selection.ActiveList.size())
                {
                    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
                    {
                        int NX  = m_Selection.ActiveList[i].Current.x + (X - m_iLastMouseX);
                        int NY  = m_Selection.ActiveList[i].Current.y + (Y - m_iLastMouseY);
                        MoveSprite(m_Selection.ActiveList[i].Tile, NX, NY, false);
                    }
                    m_bDraggingSelection = true;

                    BlitScreen(m_iActiveScreen);
                    BlitMapScreen(m_iActiveScreen);
                    m_imgMapEditor->Refresh();
                }
                else if (m_Selection.Active)
                {
                    m_Selection.Rect.Right  = std::max(0, std::min(X, m_Map->ScreenWidth));
                    m_Selection.Rect.Bottom = std::max(0, std::min(Y, m_Map->ScreenHeight));
                }
            }
            else
            {
                // find a tile to select
                DrawScreen(m_iActiveScreen);
                int iSprite = m_Map->FindScreenSprite(m_iActiveScreen, X, Y);
                if (g_iTileNotFound != iSprite)
                {
                    SetStatusSlot(m_PluginHandle, m_Map->Sprite(m_iActiveScreen, iSprite)->m_sSprite, 2);
                    DrawScreenBorder(m_iActiveScreen, m_Map->Sprite(m_iActiveScreen, iSprite), clBlue);
                }
            }
            UpdateScreenEditor();
        }
        else if (moSelectObject == m_Mode)
        {
            SetStatusSlot(m_PluginHandle, "[No Object]", 2);
            if (Shift.Contains(ssLeft))
            {
                if (!m_Selection.Active &&  m_Selection.ActiveList.size())
                {
                    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
                    {
                        int NX  = m_Selection.ActiveList[i].Current.x + (X - m_iLastMouseX);
                        int NY  = m_Selection.ActiveList[i].Current.y + (Y - m_iLastMouseY);
                        MoveObject(m_Selection.ActiveList[i].Tile, NX, NY, false);
                    }
                    m_bDraggingSelection = true;

                    BlitScreen(m_iActiveScreen);
                    BlitMapScreen(m_iActiveScreen);
                    m_imgMapEditor->Refresh();
                }
                else if (m_Selection.Active)
                {
                    m_Selection.Rect.Right  = std::max(0, std::min(X, m_Map->ScreenWidth));
                    m_Selection.Rect.Bottom = std::max(0, std::min(Y, m_Map->ScreenHeight));
                }
            }
            else
            {
                // find a tile to select
                DrawScreen(m_iActiveScreen);
                int iObject = m_ObjectManager->FindObject(m_iActiveScreen, X, Y);
                if (g_iTileNotFound != iObject)
                {
                    TMapObject object;
                    m_ObjectManager->GetObject(iObject, object);
                    SetStatusSlot(m_PluginHandle, object.m_sObject, 2);
                    DrawScreenBorder(m_iActiveScreen, &object, clBlue);
                }
            }
            UpdateScreenEditor();
        }
        else if (moSelectTile == m_Mode)
        {
            SetStatusSlot(m_PluginHandle, "[No Tile]", 2);

            if (Shift.Contains(ssLeft))
            {
                if (!m_Selection.Active &&  m_Selection.ActiveList.size())
                {
                    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
                    {
                        int NX  = m_Selection.ActiveList[i].Current.x + (X - m_iLastMouseX);
                        int NY  = m_Selection.ActiveList[i].Current.y + (Y - m_iLastMouseY);
                        MoveTile(m_Selection.ActiveList[i].Tile, NX, NY, false);
                    }
                    m_bDraggingSelection = true;

                    BlitScreen(m_iActiveScreen);
                    BlitMapScreen(m_iActiveScreen);
                    m_imgMapEditor->Refresh();
                }
                else if (m_Selection.Active)
                {
                    m_Selection.Rect.Right  = std::max(0, std::min(X, m_Map->ScreenWidth));
                    m_Selection.Rect.Bottom = std::max(0, std::min(Y, m_Map->ScreenHeight));
                }
            }
            else
            {
                // find a tile to select
                DrawScreen(m_iActiveScreen);
                int iTile = m_Map->FindScreenTile(m_iActiveScreen, X, Y);
                if (g_iTileNotFound != iTile)
                {
                    SetStatusSlot(m_PluginHandle, m_Map->Tile(m_iActiveScreen, iTile)->m_sTile, 2);
                    DrawScreenBorder(m_iActiveScreen, m_Map->Tile(m_iActiveScreen, iTile), clBlue);
                }
            }
            UpdateScreenEditor();
        }
    }
    m_iLastMouseX = X;
    m_iLastMouseY = Y;
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::ScreenMouseUp(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	m_bDraggingSelection = false;
    if (FOnScreenMouseUp)
    {
        FOnScreenMouseUp(Sender, Button, Shift, X, Y);
    }
    if (mbLeft == Button && g_iNoActiveScreen != m_iActiveScreen)
    {
        //float dx, dy;
        //m_TileManager->GetScalar(dx, dy);
        X = (X / m_iScreenScale) - m_iScreenX;
        Y = (Y / m_iScreenScale) - m_iScreenY;
        if (moTileFree <= m_Mode && m_Mode <= moTileCircleFill)
        {
            // TODO: Add the tile shape to the screen
            m_TileShapeBounds.Right  = X;
            m_TileShapeBounds.Bottom = Y;
            AddTileShapeToScreen();
            DrawScreen(m_iActiveScreen);
            UpdateScreenEditor();
        }
        if (moSelectTile == m_Mode)
        {
            if (m_Selection.Active)
            {
                if (m_Selection.Rect.Left > m_Selection.Rect.Right)
                {
                    m_Selection.Rect.Left   ^= m_Selection.Rect.Right;
                    m_Selection.Rect.Right  ^= m_Selection.Rect.Left;
                    m_Selection.Rect.Left   ^= m_Selection.Rect.Right;
                }
                if (m_Selection.Rect.Top > m_Selection.Rect.Bottom)
                {
                    m_Selection.Rect.Top    ^= m_Selection.Rect.Bottom;
                    m_Selection.Rect.Bottom ^= m_Selection.Rect.Top;
                    m_Selection.Rect.Top    ^= m_Selection.Rect.Bottom;
                }
                m_Map->FindScreenTiles(m_iActiveScreen, m_Selection.Rect, m_Selection.SelectList);
                // add the selected item to the active list
                for (unsigned int i = 0; i < m_Selection.SelectList.size(); i++)
                {
                    m_Selection.ActiveList.push_back(m_Selection.SelectList[i]);
				}
            }
            if (!m_Selection.Active && m_Selection.ActiveList.size())
            {
                bool bCanMove = true;
                for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
                {
                    bCanMove &= false == DoesTileOverlap(i);
                }
                if (!bCanMove)
                {
                    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
                    {
                        m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[i].Tile)->m_iLeft = m_Selection.ActiveList[i].Start.x;
                        m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[i].Tile)->m_iTop  = m_Selection.ActiveList[i].Start.y;
                        m_Selection.ActiveList[i].Current = m_Selection.ActiveList[i].Start;
                        m_Selection.ActiveList[i].Last    = m_Selection.ActiveList[i].Start;
                    }
                }
                else
                {
                    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
                    {
                        m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[i].Tile)->m_iLeft = m_Selection.ActiveList[i].Start.x;
                        m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[i].Tile)->m_iTop  = m_Selection.ActiveList[i].Start.y;
                        m_Map->MoveTile
                        (
                            m_iActiveScreen,
                            m_Selection.ActiveList[i].Tile,
                            m_Selection.ActiveList[i].Last.x,
                            m_Selection.ActiveList[i].Last.y, i == (m_Selection.ActiveList.size()-1) ? umBatchEnd : umBatchAdd
                        );
                        m_Selection.ActiveList[i].Current = m_Selection.ActiveList[i].Last;
                        m_Selection.ActiveList[i].Start   = m_Selection.ActiveList[i].Last;
                    }
                }
                DrawScreen(m_iActiveScreen);
            }
            m_Selection.Active = false;
            UpdateScreenEditor();
        }
		DrawMapCursor();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::MapMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (FOnMapMouseDown)
    {
        FOnMapMouseDown(Sender, Button, Shift, X, Y);
    }
    if (mbLeft == Button)
    {
        EraseMapCursor();
    }
    m_OldMode = m_Mode;
    m_Mode = moMoveScreen;
    DrawScreen(m_iActiveScreen);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::MapMouseMove(TObject* Sender, TShiftState Shift, int X, int Y)
{
    m_MouseZone = mzMapWindow;
    if (FOnMapMouseMove)
    {
        FOnMapMouseMove(Sender, Shift, X, Y);
    }
    if (true == SAFE_PTR(m_imgMapEditor))
    {
        if (false == Shift.Contains(ssLeft))
        {
            if (false == Shift.Contains(ssMiddle))
            {
                float fScale = (float)m_iMapScale / 100.f;
                float dx, dy;
                m_TileManager->GetScalar(dx, dy);
                int iWidth   = (int)((float)m_Map->ScreenWidth  * fScale * dx) + m_iScreenGap;
                int iHeight  = (int)((float)m_Map->ScreenHeight * fScale * dy) + m_iScreenGap;
                int iLeft    = std::min(m_Map->ScreensAcross, std::max(0, X / iWidth ));
                int iTop     = std::min(m_Map->ScreensDown  , std::max(0, Y / iHeight));
                EraseMapCursor(false);
                m_iSelectedScreen = m_Map->FindScreen(iLeft, iTop);
                if (g_iNoActiveScreen != m_iSelectedScreen)
                {
                    m_iLastScreenX = iLeft;
                    m_iLastScreenY = iTop;
                }
				DrawMapCursor();
            }
        }
        else
        {
            int iWidth   = m_iLayoutScreenWidth  + m_iScreenGap;
            int iHeight  = m_iLayoutScreenHeight + m_iScreenGap;
            int iLeft    = std::min(m_Map->ScreensAcross, std::max(0, X / iWidth ));
            int iTop     = std::min(m_Map->ScreensDown  , std::max(0, Y / iHeight));
            int iScreen  = m_Map->FindScreen(iLeft, iTop);
            if (false == m_bDraggingScreen)
            {
                // setup the dragging of the screen
                if (g_iNoActiveScreen != iScreen)
                {
                    //EraseMapCursor();
                    m_iScreenBeingDragged = iScreen;
					m_bDraggingScreen = true;
                    m_iDragOffsetX = (m_Map->Screen(iScreen)->m_iLeft * iWidth ) - X;
                    m_iDragOffsetY = (m_Map->Screen(iScreen)->m_iTop  * iHeight) - Y;
                    // erase the screen we are dragging
                    int iLeft = m_Map->Screen(iScreen)->m_iLeft * iWidth;
                    int iTop  = m_Map->Screen(iScreen)->m_iTop  * iHeight;
                    if (false == Shift.Contains(ssCtrl))
                    {
						PatBlt(m_imgMapEditor->Canvas->Handle, iLeft, iTop, iWidth, iHeight, PATCOPY);
                    }
                    m_iLastMouseX = X;
                    m_iLastMouseY = Y;
					SaveMapBackground();
					BlitDragScreen();
                    m_imgMapEditor->Refresh();
                }
            }
            else
            {
                if (m_iLastMouseX != X || m_iLastMouseY != Y)
                {
                    // highlight drop point
                    RestoreMapBackground();
                    m_iLastMouseX = X;
                    m_iLastMouseY = Y;
                    if (g_iNoActiveScreen == iScreen)
                    {
                        m_iLastScreenX = iLeft;
                        m_iLastScreenY = iTop;
                    }
					SaveMapBackground();
                    BlitDragScreen();
					m_imgMapEditor->Refresh();
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::MapMouseUp(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (mbLeft == Button)
    {
        if (true == m_bDraggingScreen)
        {
            if (g_iNoActiveScreen != m_iScreenBeingDragged)
            {
                RestoreMapBackground();
                SetActiveScreen(m_iScreenBeingDragged, false);
                // drop the screen
                int iWidth   = m_iLayoutScreenWidth  + m_iScreenGap;
                int iHeight  = m_iLayoutScreenHeight + m_iScreenGap;
                int iLeft    = std::min(m_Map->ScreensAcross, std::max(0, X / iWidth ));
                int iTop     = std::min(m_Map->ScreensDown  , std::max(0, Y / iHeight));
                int iScreen  = m_Map->FindScreen(iLeft, iTop);
                if (g_iNoActiveScreen == iScreen)
                {
                    if (false == Shift.Contains(ssCtrl))
                    {
                        KXmlInfo Undo;
                        Undo.Add("Operation"  , "ScreenMove"    );
                        Undo.Add("Plugin"     , "Map Editor"    );
                        Undo.Add("Screen"     , m_iActiveScreen );
                        Undo.Add("Left"       , m_Map->Screen(m_iActiveScreen)->m_iLeft);
                        Undo.Add("Top"        , m_Map->Screen(m_iActiveScreen)->m_iTop );
                        Undo.Add("Description", "Move Screen " + IntToStr(m_iActiveScreen));
                        PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                        // add the redo information
                        Undo.GetNode("Left", 0)->SetText(iLeft);
                        Undo.GetNode("Top" , 0)->SetText(iTop);
                        PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
                        // relocate the screen since it does not intersect any other screens
                        m_Map->Screen(m_iActiveScreen)->m_iLeft = iLeft;
                        m_Map->Screen(m_iActiveScreen)->m_iTop  = iTop;
                    }
                    else
                    {
                        // clone the screen
                        CloneScreen(iLeft, iTop);
                    }
                }
                else
                {
                    if (Shift.Contains(ssShift))
                    {
                        // do a screen swap
                        KXmlInfo Undo;
                        Undo.Add("Operation"  , "ScreenSwap"    );
                        Undo.Add("Plugin"     , "Map Editor"    );
                        Undo.Add("Screen1"    , m_iActiveScreen );
                        Undo.Add("Left1"      , m_Map->Screen(m_iActiveScreen)->m_iLeft);
                        Undo.Add("Top1"       , m_Map->Screen(m_iActiveScreen)->m_iTop );
                        Undo.Add("Screen2"    , iScreen );
                        Undo.Add("Left2"      , m_Map->Screen(iScreen)->m_iLeft);
                        Undo.Add("Top2"       , m_Map->Screen(iScreen)->m_iTop );
                        Undo.Add("Undo"       , true        );
                        Undo.Add("Description", "Swap Screens " + IntToStr(m_iActiveScreen) + " and " + IntToStr(iScreen));
                        PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                        Undo.GetNode("Undo", 0)->SetText(false);
                        PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
                        // swap the screens since it does not intersect any other screens
                        int iS1X = m_Map->Screen(m_iActiveScreen)->m_iLeft;
                        int iS1Y = m_Map->Screen(m_iActiveScreen)->m_iTop;
                        int iS2X = m_Map->Screen(iScreen        )->m_iLeft;
                        int iS2Y = m_Map->Screen(iScreen        )->m_iTop;
                        m_Map->Screen(m_iActiveScreen)->m_iLeft = iS2X;
                        m_Map->Screen(m_iActiveScreen)->m_iTop  = iS2Y;
                        m_Map->Screen(iScreen        )->m_iLeft = iS1X;
                        m_Map->Screen(iScreen        )->m_iTop  = iS1Y;
                        BlitMapScreen(iScreen);
                    }
                }
                BlitMapScreen(m_iActiveScreen);
                m_bDraggingScreen     = false;
                m_iScreenBeingDragged = g_iNoActiveScreen;
            }
        }
        else
        {
            // add undo information
            if (m_iActiveScreen != m_iSelectedScreen)
            {
                KXmlInfo Undo;
                Undo.Add("Operation"  , "ScreenSelect"  );
                Undo.Add("Plugin"     , "Map Editor"    );
                Undo.Add("Screen"     , m_iActiveScreen );
                Undo.Add("Description", "Select Screen " + IntToStr(m_iSelectedScreen));
                PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                // add the redo information
                Undo.GetNode("Screen", 0)->SetText(m_iSelectedScreen);
                PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
            }
            // change the active screen to the selected screen
            SetActiveScreen(m_iSelectedScreen, false);
        }
        DrawScreen(m_iActiveScreen);
        UpdateScreenWindow();
		BlitMapScreen(m_iActiveScreen);
		DrawMapCursor();
        m_imgMapEditor->Refresh();
    }
    m_Mode = m_OldMode;
    if (FOnMapMouseUp)
    {
        FOnMapMouseUp(Sender, Button, Shift, X, Y);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::Mode(eModes Mode)
{
    if (Mode < moTileFree)
        ClearSelection();
    RestoreScreenTiles();
    if (Mode == moAddComment)
    {
        m_OldMode = m_Mode;
    }
    m_Mode = Mode;
    if (!(moTileFree <= m_Mode && m_Mode <= moTileCircleFill) && m_bPlaceTileAdded)
    {
        m_Map->DeleteTile(m_iActiveScreen,  m_Selection.ActiveList[0].Tile, umSkip);
        m_bPlaceTileAdded = false;
        m_Selection.ActiveList.clear();
    }
    m_Selection.Active = false;
    DrawScreen(m_iActiveScreen);
    UpdateScreenEditor();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::ClearSelection(void)
{
    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
    {
        SAFE_DELETE(m_Selection.ActiveList[i].TileBG);
    }
    m_Selection.ActiveList.clear();
    m_Selection.Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::Clear(void)
{
    ClearSelection();
    m_iActiveScreen = g_iNoActiveScreen;
    m_Map->Clear();
    ClearScreen(m_iActiveScreen);
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::RemoveScreen(void)
{
    if (g_iNoActiveScreen != m_iActiveScreen)
    {
        m_Map->DeleteScreen(m_iActiveScreen);
        m_iActiveScreen = g_iNoActiveScreen;
        ClearScreen(g_iNoActiveScreen);
        Update();
    }
}
//---------------------------------------------------------------------------
int __fastcall TZXMapEditor::ReplaceTile(String sTileToFind, String sReplaceWith)
{
    int iReplacements = 0;
    // search all the screens and replace the tiles
    for (unsigned int s = 0; s < m_Map->Screens(); s++)
    {
        bool bReplaced = false;
        for (unsigned int t = 0; t < m_Map->Screen(s)->m_ScreenTiles.size(); t++)
        {
            if (m_Map->Screen(s)->m_ScreenTiles[t]->m_sTile == sTileToFind)
            {
                iReplacements++;
                m_Map->Screen(s)->m_ScreenTiles[t]->m_sTile = sReplaceWith;
                bReplaced = true;
            }
        }
        if (true == bReplaced)
        {
            DrawScreen(s);
            BlitMapScreen(s);
            m_imgScreenEditor->Refresh();
            m_imgMapEditor->Refresh();
        }
    }
    return iReplacements;
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::Copy(void)
{
    m_CopyInfo.Tiles.clear();

    m_CopyInfo.Screen = m_iActiveScreen;
    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
    {
        TTile Tile = *m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[i].Tile);
        m_CopyInfo.Tiles.push_back(Tile);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::Cut(void)
{
    Copy();
    Delete();
    ClearSelection();
    UpdateScreenEditor();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::Paste(void)
{
    ClearSelection();
    for (unsigned int i = 0; i < m_CopyInfo.Tiles.size(); i++)
    {
        // add the tile
        m_Map->AddScreenTile
        (
            m_iActiveScreen,
            m_CopyInfo.Tiles[i],
            i == (m_CopyInfo.Tiles.size() - 1) ? umBatchEnd : umBatchAdd
        );
        // select the tile
        TTileSelect TileInfo;
        int iTile        = m_Map->NumberOfTiles(m_iActiveScreen) - 1;
        TileInfo.Tile    = iTile;
        TileInfo.Start.x = m_Map->Tile(m_iActiveScreen, iTile)->m_iLeft;
        TileInfo.Start.y = m_Map->Tile(m_iActiveScreen, iTile)->m_iTop;
        TileInfo.Current = TileInfo.Start;
        TileInfo.Last    = TileInfo.Start;
        TileInfo.TileBG  = NULL;
        m_Selection.ActiveList.push_back(TileInfo);
    }
    UpdateScreenEditor();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::Delete(void)
{
    if (mzScreenWindow == m_MouseZone)
    {
        if (moSelectTile == m_Mode && 0 <= m_iActiveScreen && m_iActiveScreen < (int)m_Map->Screens())
        {
            while (m_Selection.ActiveList.size())
            {
                // find the highest tile index in the selection
                int HighIndex = 0;
                for (unsigned int i = 1; i < m_Selection.ActiveList.size(); i++)
                {
                    if (m_Selection.ActiveList[i].Tile > m_Selection.ActiveList[HighIndex].Tile)
                    {
                        HighIndex = i;
                    }
                }
                // delete the tile at high index in the selection list
                m_Map->DeleteTile
                (
                    m_iActiveScreen,
                    m_Selection.ActiveList[HighIndex].Tile,
                    m_Selection.ActiveList.size() == 1 ? umBatchEnd : umBatchAdd
                );
                // remove the high index item
                m_Selection.ActiveList.erase(m_Selection.ActiveList.begin() + HighIndex);
            }
            DrawScreen(m_iActiveScreen);
            UpdateScreenEditor();
        }
    }
    if (mzMapWindow == m_MouseZone)
    {
        RemoveScreen();
    }
}
//---------------------------------------------------------------------------
int __fastcall TZXMapEditor::AddScreen(int iLeft, int iTop)
{
    return m_Map->AddScreen(iLeft, iTop);
}
//---------------------------------------------------------------------------
int __fastcall TZXMapEditor::AddScreen(void)
{
    return m_Map->AddScreen();
}
//---------------------------------------------------------------------------
int __fastcall TZXMapEditor::CloneScreen(int iLeft, int iTop)
{
    int iNewScreen = g_iScreenNotFound;
    if (g_iNoActiveScreen != m_iActiveScreen)
    {
        if (-1 == iLeft || -1 == iTop)
        {
            iNewScreen = AddScreen();
        }
        else
        {
            iNewScreen = AddScreen(iLeft, iTop);
        }
        if (g_iScreenNotFound != iNewScreen)
        {
            // copy the active screen into the new screen
            m_Map->CopyScreen(m_iActiveScreen, iNewScreen);
            int iOldScreen = m_iActiveScreen;
            m_iActiveScreen = iNewScreen;
            DrawScreen(iOldScreen);
            DrawScreen(m_iActiveScreen);
        }
    }
    return iNewScreen;
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SnapPointsToGrid(int& X, int& Y)
{
    if (true == m_bSnapToGrid)
    {
        X -= (X % m_iGridWidth );
        Y -= (Y % m_iGridHeight);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::IntersectionsAllowed(bool bState)
{
    m_bAllowIntersections = bState;
    DrawScreen(m_iActiveScreen);
    UpdateScreenEditor();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::OverwriteOverlaps(bool bState)
{
    m_bOverwriteOverlaps = bState;
    DrawScreen(m_iActiveScreen);
    UpdateScreenEditor();
}
//---------------------------------------------------------------------------
bool __fastcall TZXMapEditor::DoesTileOverlap(int iTileIndex)
{
    if (0 <= iTileIndex && iTileIndex < (int)m_Selection.ActiveList.size())
    {
        TTile* Tile = m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[iTileIndex].Tile);
        //SnapPointsToGrid(iTileX, iTileY);
        return m_Map->DoesTileOverlap(m_iActiveScreen, Tile, m_bAllowIntersections || m_bOverwriteOverlaps);
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall TZXMapEditor::DoesTileOverlap(int x, int y, int w, int h)
{
    return m_Map->DoesTileOverlap(m_iActiveScreen, x, y, w, h, m_bAllowIntersections || m_bOverwriteOverlaps);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::RemoveOverlapTiles(int x, int y, int w, int h)
{
    m_Map->RemoveOverlapTiles(m_iActiveScreen, x, y, w, h);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::Invalidate(void)
{
    for (int i = 0; i < (int)m_Map->Screens(); i++)
    {
        m_Map->Screen(i)->m_bDirty = true;
    }
    Update();
}
//---------------------------------------------------------------------------






int __fastcall TZXMapEditor::GetTileSelect(int iTile)
{
    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
    {
        if (iTile == m_Selection.ActiveList[i].Tile)
        {
            return i;
        }
    }
    return -1;
}




//---------------------------------------------------------------------------
//
//   S C R E E N   F U N C T I O N S
//
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::MoveTile(int iTile, int X, int Y, bool bUpdate)
{
    int iSelectIndex = GetTileSelect(iTile);
    if (iSelectIndex >= 0)
    {
        m_Selection.ActiveList[iSelectIndex].Current.x = X;
        m_Selection.ActiveList[iSelectIndex].Current.y = Y;
        SnapPointsToGrid(X, Y);
        if (X != m_Selection.ActiveList[iSelectIndex].Last.x || Y != m_Selection.ActiveList[iSelectIndex].Last.y)
        {
            RestoreScreenTile(iSelectIndex);
            SaveScreenTile(m_iActiveScreen, iSelectIndex);
            m_Map->MoveTile(m_iActiveScreen, m_Selection.ActiveList[iSelectIndex].Tile, X, Y, umSkip);
            DrawScreenTile(m_iActiveScreen, m_Selection.ActiveList[iSelectIndex].Tile);
            if (bUpdate)
            {
                BlitMapScreen(m_iActiveScreen);
            }
            m_Selection.ActiveList[iSelectIndex].Last.x = X;
            m_Selection.ActiveList[iSelectIndex].Last.y = Y;
            if (bUpdate)
            {
                BlitScreen(m_iActiveScreen);
                m_imgMapEditor->Refresh();
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::MoveSprite(int iTile, int X, int Y, bool bUpdate)
{
    int iSelectIndex = GetTileSelect(iTile);
    if (iSelectIndex >= 0)
    {
        m_Selection.ActiveList[iSelectIndex].Current.x = X;
        m_Selection.ActiveList[iSelectIndex].Current.y = Y;
        SnapPointsToGrid(X, Y);
        if (X != m_Selection.ActiveList[iSelectIndex].Last.x || Y != m_Selection.ActiveList[iSelectIndex].Last.y)
        {
            RestoreScreenTile(iSelectIndex);
            SaveScreenTile(m_iActiveScreen, iSelectIndex);
            m_Map->MoveSprite(m_iActiveScreen, m_Selection.ActiveList[iSelectIndex].Tile, X, Y, umSkip);
            DrawScreenSprite(m_iActiveScreen, m_Selection.ActiveList[iSelectIndex].Tile);
            if (bUpdate)
            {
                BlitMapScreen(m_iActiveScreen);
            }
            m_Selection.ActiveList[iSelectIndex].Last.x = X;
            m_Selection.ActiveList[iSelectIndex].Last.y = Y;
            if (bUpdate)
            {
                BlitScreen(m_iActiveScreen);
                m_imgMapEditor->Refresh();
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::MoveObject(int iTile, int X, int Y, bool bUpdate)
{
    int iSelectIndex = GetTileSelect(iTile);
    if (iSelectIndex >= 0)
    {
        m_Selection.ActiveList[iSelectIndex].Current.x = X;
        m_Selection.ActiveList[iSelectIndex].Current.y = Y;
        SnapPointsToGrid(X, Y);
        if (X != m_Selection.ActiveList[iSelectIndex].Last.x || Y != m_Selection.ActiveList[iSelectIndex].Last.y)
        {
            RestoreScreenTile(iSelectIndex);
            SaveScreenTile(m_iActiveScreen, iSelectIndex);
            m_ObjectManager->MoveObject(m_Selection.ActiveList[iSelectIndex].Tile, X, Y);
            DrawScreenTile(m_iActiveScreen, m_Selection.ActiveList[iSelectIndex].Tile);
            if (bUpdate)
            {
                BlitMapScreen(m_iActiveScreen);
            }
            m_Selection.ActiveList[iSelectIndex].Last.x = X;
            m_Selection.ActiveList[iSelectIndex].Last.y = Y;
            if (bUpdate)
            {
                BlitScreen(m_iActiveScreen);
                m_imgMapEditor->Refresh();
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SaveScreenTile(int iScreen, int iSelectIndex)
{
    if (0 <= iSelectIndex && iSelectIndex < (int)m_Selection.ActiveList.size())
    {
        ZXBitmap pTile = m_TileManager->Find(m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[iSelectIndex].Tile)->m_sTile);
        if (0 <= iScreen && iScreen < (int)m_Map->Screens() && SAFE_PTR(pTile))
        {
            int iWidth  = pTile->Width;
            int iHeight = pTile->Height;
            if (false == SAFE_PTR(m_Selection.ActiveList[iSelectIndex].TileBG))
            {
                m_Selection.ActiveList[iSelectIndex].TileBG = new Graphics::TBitmap();
                if (true == SAFE_PTR(m_Selection.ActiveList[iSelectIndex].TileBG))
                {
                    m_Selection.ActiveList[iSelectIndex].TileBG->Width       = iWidth;
                    m_Selection.ActiveList[iSelectIndex].TileBG->Height      = iHeight;
                    m_Selection.ActiveList[iSelectIndex].TileBG->PixelFormat = pTile->PixelFormat;
                }
            }
            if (true == SAFE_PTR(m_Selection.ActiveList[iSelectIndex].TileBG))
            {
                // copy the background where the tile will go (including the 2 pixel border)
                int X = m_Selection.ActiveList[iSelectIndex].Last.x - 2;
                int Y = m_Selection.ActiveList[iSelectIndex].Last.y - 2;
                BitBlt(m_Selection.ActiveList[iSelectIndex].TileBG->Canvas->Handle, 0, 0, iWidth + 4, iHeight + 4, m_Map->Screen(iScreen)->m_bmScreen->Canvas->Handle, X, Y, SRCCOPY);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::RestoreScreenTiles(void)
{
    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
    {
        RestoreScreenTile(i);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::RestoreScreenTile(int iSelectIndex)
{
    if (0 <= iSelectIndex && iSelectIndex < (int)m_Selection.ActiveList.size() && true == SAFE_PTR(m_Selection.ActiveList[iSelectIndex].TileBG))
    {
        int iBackI = m_Selection.ActiveList[iSelectIndex].Tile;
        int iBackX = m_Selection.ActiveList[iSelectIndex].Last.x - 2;
        int iBackY = m_Selection.ActiveList[iSelectIndex].Last.y - 2;
        int iBackW;
        int iBackH;
        m_Map->GetTileSize(m_Map->Tile(m_iActiveScreen, iBackI)->m_sTile, iBackW, iBackH);
        // bitblt the background over the tile
        if (SAFE_PTR(m_Selection.ActiveList[iSelectIndex].TileBG))
        {
            BitBlt(m_Map->Screen(m_iActiveScreen)->m_bmScreen->Canvas->Handle, iBackX, iBackY, iBackW, iBackH, m_Selection.ActiveList[iSelectIndex].TileBG->Canvas->Handle, 0, 0, SRCCOPY);
            SAFE_DELETE(m_Selection.ActiveList[iSelectIndex].TileBG);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::UpdateScreenEditor(void)
{
    if (true == SAFE_PTR(m_imgScreenEditor) && 0 <= m_iActiveScreen && m_iActiveScreen < (int)m_Map->Screens())
    {
        // copy the screen buffer to the image
        int sw = m_Map->Screen(m_iActiveScreen)->m_bmScreen->Width;
        int sh = m_Map->Screen(m_iActiveScreen)->m_bmScreen->Height;
        if (0 != StretchBlt(m_imgScreenEditor->Picture->Bitmap->Canvas->Handle, m_iScreenX * m_iScreenScale, m_iScreenY * m_iScreenScale, sw * m_iScreenScale, sh * m_iScreenScale,
                            m_Map->Screen(m_iActiveScreen)->m_bmScreen->Canvas->Handle, 0, 0, sw, sh, SRCCOPY))
        {
            DrawGrid();
            DrawSelection(true);
            // get the image to refresh
            m_imgScreenEditor->Refresh();
        }
        m_dwError = GetLastError();
    }
    else
    {
        ClearScreen(g_iNoActiveScreen);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::ClearScreen(int iScreen)
{
    if (0 <= iScreen && iScreen < (int)m_Map->Screens())
    {
        PatBlt(m_Map->Screen(iScreen)->m_bmScreen->Canvas->Handle, 0, 0, m_Map->Screen(iScreen)->m_bmScreen->Width, m_Map->Screen(iScreen)->m_bmScreen->Height, PATCOPY);
    }
    else
    {
        if (true == SAFE_PTR(m_imgScreenEditor))
        {
            m_imgScreenEditor->Canvas->Brush->Color = clWhite;
            PatBlt(m_imgScreenEditor->Canvas->Handle, m_iScreenX * m_iScreenScale, m_iScreenY * m_iScreenScale, m_Map->ScreenWidth * m_iScreenScale, m_Map->ScreenHeight * m_iScreenScale, PATCOPY);
            m_imgScreenEditor->Refresh();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::BlitScreen(int iScreen)
{
    if (0 <= iScreen && iScreen < (int)m_Map->Screens())
    {
        // update the screen if need be
        DrawScreen(iScreen);
        //int iLeft = m_Map->Screen(iScreen)->m_iLeft * (m_iLayoutScreenWidth  + m_iScreenGap);
        //int iTop  = m_Map->Screen(iScreen)->m_iTop  * (m_iLayoutScreenHeight + m_iScreenGap);
        //StretchBlt(m_imgScreenEditor->Canvas->Handle, iLeft, iTop, m_iLayoutScreenWidth, m_iLayoutScreenHeight,
        //           m_Map->Screen(iScreen)->m_bmScreen->Canvas->Handle, 0, 0, m_Map->Screen(iScreen)->m_bmScreen->Width, m_Map->Screen(iScreen)->m_bmScreen->Height, SRCCOPY);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawScreenBorder(int iScreen, TTile* STile, TColor cColor)
{
    ZXBitmap Tile = m_TileManager->Find(STile->m_sTile);
    if (true == SAFE_PTR(Tile))
    {
        TColor BackColor = m_Map->Screen(iScreen)->m_bmScreen->Canvas->Brush->Color;
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->Brush->Color = cColor;
        int iWidth  = Tile->Width;
        int iHeight = Tile->Height;
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->FrameRect(Rect(STile->m_iLeft - 1, STile->m_iTop - 1, STile->m_iLeft + iWidth + 1, STile->m_iTop + iHeight + 1));
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->Brush->Color = BackColor;
        m_Map->Screen(iScreen)->m_bDirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawScreenBorder(int iScreen, TSprite* STile, TColor cColor)
{
    ZXBitmap Tile = m_SpriteManager->Find(STile->m_sSprite);
    if (true == SAFE_PTR(Tile))
    {
        TColor BackColor = m_Map->Screen(iScreen)->m_bmScreen->Canvas->Brush->Color;
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->Brush->Color = cColor;
        int iWidth  = Tile->Width;
        int iHeight = Tile->Height;
        m_SpriteManager->GetSize(STile->m_sSprite, iWidth, iHeight);
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->FrameRect(Rect(STile->m_iLeft - 1, STile->m_iTop - 1, STile->m_iLeft + iWidth + 1, STile->m_iTop + iHeight + 1));
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->Brush->Color = BackColor;
        m_Map->Screen(iScreen)->m_bDirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawScreenBorder(int iScreen, TMapObject* STile, TColor cColor)
{
    ZXBitmap Tile = m_ObjectManager->Find(STile->m_sObject);
    if (true == SAFE_PTR(Tile))
    {
        TColor BackColor = m_Map->Screen(iScreen)->m_bmScreen->Canvas->Brush->Color;
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->Brush->Color = cColor;
        int iWidth  = Tile->Width;
        int iHeight = Tile->Height;
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->FrameRect(Rect(STile->m_iLeft - 1, STile->m_iTop - 1, STile->m_iLeft + iWidth + 1, STile->m_iTop + iHeight + 1));
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->Brush->Color = BackColor;
        m_Map->Screen(iScreen)->m_bDirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawScreenTile(int iScreen, int iTile)
{
    TTile* Tile = m_Map->Tile(iScreen, iTile);
    DrawScreenTile(iScreen, Tile->m_sTile, Tile->m_iLeft, Tile->m_iTop);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawScreenSprite(int iScreen, int iTile)
{
    TSprite* Tile = m_Map->Sprite(iScreen, iTile);
    DrawScreenSprite(iScreen, Tile->m_sSprite, Tile->m_iLeft, Tile->m_iTop);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawScreenTile(int iScreen, const String& sTile, int X, int Y)
{
    ZXBitmap Tile = m_TileManager->Find(sTile);
    float dx, dy;
    m_TileManager->GetScalar(dx, dy);
    if (SAFE_PTR(Tile))
    {
        if (m_bOverwriteOverlaps)
        {
            Tile->Transparent = false;
        }
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->Draw(X * dx, Y * dy, Tile);
        Tile->Transparent = true;
    }
    /*else
    {
        // TODO: need to draw the missing tile image (ie. a square with a cross in it
    }
    */
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawScreenObject(int iScreen, const String& sObject)
{
    ZXBitmap Tile = m_ObjectManager->Find(sObject);
    float dx, dy;
    m_TileManager->GetScalar(dx, dy);
    if (SAFE_PTR(Tile))
    {
        TMapObject object;
        m_ObjectManager->GetObject(sObject, object);
        if (m_bOverwriteOverlaps)
        {
            Tile->Transparent = false;
        }
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->Draw(object.m_iLeft * dx, object.m_iTop * dy, Tile);
        Tile->Transparent = true;
    }
    /*else
    {
        // TODO: need to draw the missing tile image (ie. a square with a cross in it
    }
    */
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawScreenSprite(int iScreen, const String& sTile, int X, int Y)
{
    ZXBitmap Tile = m_SpriteManager->Find(sTile);
    float dx, dy;
    m_TileManager->GetScalar(dx, dy);
    if (SAFE_PTR(Tile))
    {
        int w, h;
        m_SpriteManager->GetSize(sTile, w, h);
        ZXBitmap tmp = new Graphics::TBitmap();
        tmp->Assign(Tile);
        tmp->Width = w;
        tmp->Height = h;
        if (m_bOverwriteOverlaps)
        {
            tmp->Transparent = false;
        }
        tmp->Canvas->Draw(0, 0, Tile);
        m_Map->Screen(iScreen)->m_bmScreen->Canvas->Draw(X * dx, Y * dy, tmp);
        Tile->Transparent = true;
        SAFE_DELETE(tmp);
    }
    /*else
    {
        // TODO: need to draw the missing tile image (ie. a square with a cross in it
    }
    */
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawScreen(int iScreen)
{
    static bool in = false;
    if (!in)
    {
        in = true;
        ClearScreen(iScreen);
        if (0 <= iScreen && iScreen < (int)m_Map->Screens() && true == SAFE_PTR(m_Map->Screen(iScreen)->m_bmScreen))
		{
            bool bIntersects = false;
            for (unsigned int i = 0; i < m_Map->Screen(iScreen)->m_ScreenTiles.size() && false == bIntersects; i++)
            {
                int iSelectIndex = GetTileSelect(i);
                bIntersects = DoesTileOverlap(iSelectIndex);
            }
            // draw the tiles
            for (unsigned int i = 0; i < m_Map->Screen(iScreen)->m_ScreenTiles.size(); i++)
            {
                DrawScreenTile(iScreen, i);
                // draw a border around the currently selected tiles
                if (iScreen == m_iActiveScreen && moMoveScreen != m_Mode && IsSelected(i) && m_Mode != moSelectSprite && m_Mode != moSelectObject)
                {
                    DrawScreenBorder(iScreen, m_Map->Screen(iScreen)->m_ScreenTiles[i], !m_bDraggingSelection ? clWhite : (bIntersects ? clRed : clLime));
                }
            }
            // draw the sprites
            for (unsigned int i = 0; i < m_Map->Screen(iScreen)->m_ScreenSprites.size(); i++)
            {
                DrawScreenSprite(iScreen, i);
                if (iScreen == m_iActiveScreen && moMoveScreen != m_Mode && IsSelected(i) && m_Mode != moSelectTile && m_Mode != moSelectObject)
                {
                    DrawScreenBorder(iScreen, m_Map->Screen(iScreen)->m_ScreenSprites[i], !m_bDraggingSelection ? clWhite : clLime);
                }
            }
            // draw the objects
            std::vector<String> objectNames;
            m_ObjectManager->GetObjectNames(iScreen, objectNames);
            for (unsigned int i = 0; i < objectNames.size(); i++)
            {
                DrawScreenObject(iScreen, objectNames[i]);
                int objIdx = m_ObjectManager->FindObject(objectNames[i]);
                if (iScreen == m_iActiveScreen && moMoveScreen != m_Mode && IsSelected(objIdx) && m_Mode != moSelectSprite && m_Mode != moSelectTile)
                {
                    TMapObject object;
                    m_ObjectManager->GetObject(objectNames[i], object);
                    DrawScreenBorder(iScreen, &object, !m_bDraggingSelection ? clWhite : clLime);
                }
            }

            ZXComments* Comments = m_Map->Comments(iScreen);
            if (true == SAFE_PTR(Comments))
            {
                Comments->Draw(m_Map->Screen(iScreen)->m_bmScreen->Canvas);
            }
            // update the map window view
            BlitMapScreen(iScreen);
	        // refresh the map window
    	    m_imgMapEditor->Refresh();
        }
        in = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::UpdateScreens(void)
{
    if (true == SAFE_PTR(m_Map))
    {
        // redraw all the dirty screens
		for (int i = 0; i < (int)m_Map->Screens(); i++)
        {
            if (true == m_Map->Screen(i)->m_bDirty)
            {
				DrawScreen(i);
                m_Map->Screen(i)->m_bDirty = false;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::UpdateScreenWindow(bool bRedrawScreen)
{
    static bool In = false;
    if (In == false)
    {
        In = true;
        if (g_iScreenNotFound != m_iActiveScreen)
        {
            frmMapEditor->edtMapEditorScreenLayoutMagnificationSizeChange(NULL);
            if (bRedrawScreen)
            {
                DrawScreen(m_iActiveScreen);
            }
            // copy the screens bitmap to the editor window
            TTiledScreen* pScreen = m_Map->Screen(m_iActiveScreen);
            if (true == SAFE_PTR(pScreen))
            {
                int sw = pScreen->m_bmScreen->Width;
                int sh = pScreen->m_bmScreen->Height;
                if (0 != StretchBlt(m_imgScreenEditor->Picture->Bitmap->Canvas->Handle, m_iScreenX * m_iScreenScale, m_iScreenY * m_iScreenScale, sw * m_iScreenScale, sh * m_iScreenScale,
                                    m_Map->Screen(m_iActiveScreen)->m_bmScreen->Canvas->Handle, 0, 0, sw, sh, SRCCOPY))
                {
                    DrawGrid();
                }
            }
            // get the image to refresh
            m_imgScreenEditor->Refresh();

            m_dwError = GetLastError();
        }
        else
        {
            ClearScreen(m_iActiveScreen);
        }
        In = false;
    }
}
//---------------------------------------------------------------------------














//---------------------------------------------------------------------------
//
//   M A P   F U N C T I O N S
//
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::RestoreMapBackground(void)
{
    // copy the background under the screen
    BitBlt(m_imgMapEditor->Canvas->Handle, m_iMapBackX, m_iMapBackY, m_iMapBackW, m_iMapBackH, m_bmMapBackground->Canvas->Handle, 0, 0, SRCCOPY);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SaveMapBackground(void)
{
    m_iMapBackX = m_iLastMouseX + m_iDragOffsetX;
    m_iMapBackY = m_iLastMouseY + m_iDragOffsetY;
    float fScale = (float)m_iMapScale / 100.f;
    float dx, dy;
    m_TileManager->GetScalar(dx, dy);
    m_iMapBackW = (int)((float)m_Map->ScreenWidth  * fScale * dx) + m_iScreenGap;
    m_iMapBackH = (int)((float)m_Map->ScreenHeight * fScale * dy) + m_iScreenGap;
    // copy the background under the screen
    BitBlt(m_bmMapBackground->Canvas->Handle, 0, 0, m_iMapBackW, m_iMapBackH, m_imgMapEditor->Canvas->Handle, m_iMapBackX, m_iMapBackY, SRCCOPY);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::EraseMapCursor(bool bRefresh)
{
    if (true == m_bScreenCursorDrawn)
    {
        m_bScreenCursorDrawn = false;
        XorMapCursor(bRefresh);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawStartScreenBorder()
{
	if (m_iStartScreen != g_iScreenNotFound)
	{
		int x, y;
		m_Map->GetScreenPosition(m_iStartScreen, x, y);
		int iWidth  = m_iLayoutScreenWidth;
		int iHeight = m_iLayoutScreenHeight;
		int iLeft = (x * (iWidth  + m_iScreenGap)) + 1;
		int iTop  = (y * (iHeight + m_iScreenGap)) + 1;
		iWidth  -= 2;
		iHeight -= 2;
		m_imgMapEditor->Canvas->Pen->Mode  = pmCopy;
		m_imgMapEditor->Canvas->Pen->Color = clLime;
		m_imgMapEditor->Canvas->Pen->Width = 2;
		m_imgMapEditor->Canvas->MoveTo(iLeft         , iTop          );
		m_imgMapEditor->Canvas->LineTo(iLeft + iWidth, iTop          );
		m_imgMapEditor->Canvas->LineTo(iLeft + iWidth, iTop + iHeight);
		m_imgMapEditor->Canvas->LineTo(iLeft         , iTop + iHeight);
		m_imgMapEditor->Canvas->LineTo(iLeft         , iTop + 1      );
	}
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawMapCursor(bool bRefresh)
{
	DrawStartScreenBorder();
	if (false == m_bScreenCursorDrawn && g_iNoActiveScreen != m_iSelectedScreen)
	{
		m_bScreenCursorDrawn = true;
		XorMapCursor(bRefresh);
	}
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::XorMapCursor(bool bRefresh)
{
    if (true == SAFE_PTR(m_imgMapEditor))
    {
        int iWidth  = m_iLayoutScreenWidth;
        int iHeight = m_iLayoutScreenHeight;
        int iLeft = (m_iLastScreenX * (iWidth  + m_iScreenGap)) + 1;
        int iTop  = (m_iLastScreenY * (iHeight + m_iScreenGap)) + 1;
        iWidth  -= 2;
        iHeight -= 2;
        m_imgMapEditor->Canvas->Pen->Mode  = pmXor;
        m_imgMapEditor->Canvas->Pen->Color = clWhite;
        m_imgMapEditor->Canvas->Pen->Width = 2;
        m_imgMapEditor->Canvas->MoveTo(iLeft         , iTop          );
        m_imgMapEditor->Canvas->LineTo(iLeft + iWidth, iTop          );
        m_imgMapEditor->Canvas->LineTo(iLeft + iWidth, iTop + iHeight);
        m_imgMapEditor->Canvas->LineTo(iLeft         , iTop + iHeight);
        m_imgMapEditor->Canvas->LineTo(iLeft         , iTop + 1      );
        if (bRefresh)
        {
            m_imgMapEditor->Refresh();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::BlitMapScreen(int iScreen)
{
    if (0 <= iScreen && iScreen < (int)m_Map->Screens())
    {
        int iLeft = m_Map->Screen(iScreen)->m_iLeft * (m_iLayoutScreenWidth  + m_iScreenGap);
        int iTop  = m_Map->Screen(iScreen)->m_iTop  * (m_iLayoutScreenHeight + m_iScreenGap);
        StretchBlt(m_imgMapEditor->Canvas->Handle, iLeft, iTop, m_iLayoutScreenWidth, m_iLayoutScreenHeight,
                   m_Map->Screen(iScreen)->m_bmScreen->Canvas->Handle, 0, 0, m_Map->Screen(iScreen)->m_bmScreen->Width, m_Map->Screen(iScreen)->m_bmScreen->Height, SRCCOPY);
        // refresh the map window
        //m_imgMapEditor->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::BlitDragScreen(void)
{
    if (g_iNoActiveScreen != m_iScreenBeingDragged)
    {
        int iLeft = m_Map->Screen(m_iScreenBeingDragged)->m_iLeft * (m_iLayoutScreenWidth  + m_iScreenGap);
        int iTop  = m_Map->Screen(m_iScreenBeingDragged)->m_iTop  * (m_iLayoutScreenHeight + m_iScreenGap);
        StretchBlt(m_imgMapEditor->Canvas->Handle, m_iLastMouseX + m_iDragOffsetX, m_iLastMouseY + m_iDragOffsetY, m_iLayoutScreenWidth, m_iLayoutScreenHeight,
                   m_Map->Screen(m_iScreenBeingDragged)->m_bmScreen->Canvas->Handle, 0, 0, m_Map->Screen(m_iScreenBeingDragged)->m_bmScreen->Width, m_Map->Screen(m_iScreenBeingDragged)->m_bmScreen->Height, SRCCOPY);
        m_dwError = GetLastError();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::UpdateMapWindow(void)
{
    if (true == SAFE_PTR(m_imgMapEditor))
    {
        EraseMapCursor();
        // work out the scaling of the screens
        float fScale = (float)m_iMapScale / 100.f;
        float dx, dy;
        m_TileManager->GetScalar(dx, dy);
        m_iLayoutScreenWidth  = (int)((float)m_Map->ScreenWidth  * fScale * dx);
        m_iLayoutScreenHeight = (int)((float)m_Map->ScreenHeight * fScale * dy);
        // make the layout image fit the screens
        m_imgMapEditor->Width  = (m_Map->ScreensAcross * (m_iLayoutScreenWidth  + m_iScreenGap));
        m_imgMapEditor->Height = (m_Map->ScreensDown   * (m_iLayoutScreenHeight + m_iScreenGap));
        m_imgMapEditor->Picture->Bitmap->Width  = m_imgMapEditor->Width;
        m_imgMapEditor->Picture->Bitmap->Height = m_imgMapEditor->Height;
        // clear the layout image
        m_imgMapEditor->Canvas->Brush->Color = clBlue;
        PatBlt(m_imgMapEditor->Canvas->Handle, 0, 0, m_imgMapEditor->Width, m_imgMapEditor->Height, PATCOPY);
        // blit the screens to the layout image
        if (0 < m_Map->Screens())
        {
            UpdateScreens();
            for (unsigned int i = 0; i < m_Map->Screens(); i++)
            {
                if ((int)i != m_iScreenBeingDragged || false == m_bDraggingScreen)
                {
                    BlitMapScreen(i);
                }
            }
            // show the screens
            m_imgMapEditor->Refresh();
        }
		DrawStartScreenBorder();
		DrawMapCursor();
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::Update(void)
{
    UpdateScreens();
    UpdateScreenWindow();
    UpdateMapWindow();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::ShowGrid(bool bShow)
{
    m_bShowGrid = bShow;
    UpdateScreenWindow();
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawGrid(void)
{
    // draw the grid lines
    if (m_bShowGrid)
    {
        //int iMag = m_imgScreenEditor->Width / m_Map->Screen(m_iActiveScreen)->m_bmScreen->Width;
        m_imgScreenEditor->Picture->Bitmap->Canvas->Pen->Color = (TColor)0x0048BAF7;
        int sx = m_iScreenX * m_iScreenScale;
        int sy = m_iScreenY * m_iScreenScale;
        int sw = m_Map->Screen(m_iActiveScreen)->m_bmScreen->Width * m_iScreenScale;
        int sh = m_Map->Screen(m_iActiveScreen)->m_bmScreen->Height * m_iScreenScale;
        for (int y = sy; y <= sy + sh; y += (GridHeight * m_iScreenScale))
        {
            m_imgScreenEditor->Picture->Bitmap->Canvas->MoveTo(sx, y);
            m_imgScreenEditor->Picture->Bitmap->Canvas->LineTo(sx+sw, y);
        }
        for (int x = sx; x <= sx + sw; x += (GridWidth * m_iScreenScale))
        {
            m_imgScreenEditor->Picture->Bitmap->Canvas->MoveTo(x, sy);
            m_imgScreenEditor->Picture->Bitmap->Canvas->LineTo(x, sy+sh);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::BringToFront(void)
{
    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
    {
        m_Selection.ActiveList[i].Tile = m_Map->BringToFront(m_iActiveScreen, m_Selection.ActiveList[i].Tile);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SendToBack(void)
{
    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
    {
        m_Selection.ActiveList[i].Tile = m_Map->SendToBack(m_iActiveScreen, m_Selection.ActiveList[i].Tile);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::UndoRestore(KXmlInfo* xmlInfo)
{
    KXmlInfo* pOperation = xmlInfo->GetNode("Operation", 0);

    if (true == SAFE_PTR(pOperation))
    {
        String sOperation = pOperation->GetText();
        m_bUndoInProgress = true;
        if (sOperation == "ScreenSelect")
        {
            UndoScreenSelect(xmlInfo);
        }
        else if (sOperation == "ScreenMove")
        {
            UndoScreenMove(xmlInfo);
        }
        m_bUndoInProgress = false;
    }
    // update the selections
    if (-1 != m_iActiveScreen && m_Selection.Screen == m_iActiveScreen)
    {
        for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
        {
            m_Selection.ActiveList[i].Start.x = m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[i].Tile)->m_iLeft;
            m_Selection.ActiveList[i].Start.y = m_Map->Tile(m_iActiveScreen, m_Selection.ActiveList[i].Tile)->m_iTop;
            m_Selection.ActiveList[i].Current = m_Selection.ActiveList[i].Start;
            m_Selection.ActiveList[i].Last    = m_Selection.ActiveList[i].Start;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::UndoScreenSelect(KXmlInfo* xmlInfo)
{
    int iScreen = xmlInfo->GetNode("Screen", 0)->GetInt();
    SetActiveScreen(iScreen, true);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::UndoScreenMove(KXmlInfo* xmlInfo)
{
    int iScreen = xmlInfo->GetNode("Screen", 0)->GetInt();
    int iLeft   = xmlInfo->GetNode("Left"  , 0)->GetInt();
    int iTop    = xmlInfo->GetNode("Top"   , 0)->GetInt();

    m_Map->Screen(iScreen)->m_iLeft = iLeft;
    m_Map->Screen(iScreen)->m_iTop  = iTop;
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SaveBitmap(const String& sFile)
{
    EraseMapCursor(false);
    m_imgMapEditor->Picture->SaveToFile(sFile);
    DrawMapCursor(false);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawSelection(bool bShow)
{
    int iMagnification = m_iScreenScale;
    if (m_Selection.Active && m_Selection.Rect.Width() && m_Selection.Rect.Height())
    {
        HRGN rgn;
        int w = m_Map->ScreenWidth * iMagnification;
        int h = m_Map->ScreenHeight * iMagnification;
        rgn = ::CreateRectRgn(m_iScreenX * iMagnification, m_iScreenY * iMagnification, m_iScreenX * iMagnification + w, m_iScreenY * iMagnification + h);
        ::SelectClipRgn(m_imgScreenEditor->Picture->Bitmap->Canvas->Handle, rgn);
        m_imgScreenEditor->Picture->Bitmap->Canvas->Pen->Color = clWhite;
        m_imgScreenEditor->Picture->Bitmap->Canvas->Brush->Color = clBlack;
        m_imgScreenEditor->Picture->Bitmap->Canvas->Pen->Style = psDot;
        //m_imgScreenEditor->Picture->Bitmap->Canvas->Pen->Mode = pmXor;
        m_imgScreenEditor->Picture->Bitmap->Canvas->MoveTo((m_iScreenX + m_Selection.Rect.Left ) * iMagnification, (m_iScreenY + m_Selection.Rect.Top   ) * iMagnification);
        m_imgScreenEditor->Picture->Bitmap->Canvas->LineTo((m_iScreenX + m_Selection.Rect.Right) * iMagnification, (m_iScreenY + m_Selection.Rect.Top   ) * iMagnification);
        m_imgScreenEditor->Picture->Bitmap->Canvas->LineTo((m_iScreenX + m_Selection.Rect.Right) * iMagnification, (m_iScreenY + m_Selection.Rect.Bottom) * iMagnification);
        m_imgScreenEditor->Picture->Bitmap->Canvas->LineTo((m_iScreenX + m_Selection.Rect.Left ) * iMagnification, (m_iScreenY + m_Selection.Rect.Bottom) * iMagnification);
        m_imgScreenEditor->Picture->Bitmap->Canvas->LineTo((m_iScreenX + m_Selection.Rect.Left ) * iMagnification, (m_iScreenY + m_Selection.Rect.Top   ) * iMagnification);
        m_imgScreenEditor->Picture->Bitmap->Canvas->Pen->Style = psSolid;
        ::SelectClipRgn(m_imgScreenEditor->Picture->Bitmap->Canvas->Handle, NULL);
        ::DeleteObject(rgn);
    }
}
//---------------------------------------------------------------------------
bool __fastcall TZXMapEditor::IsSelected(int iTile)
{
    for (unsigned int i = 0; i < m_Selection.ActiveList.size(); i++)
    {
        if (m_Selection.ActiveList[i].Tile == iTile)
        {
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::CommentAdd(const TRect& Rect)
{
    if (g_iNoActiveScreen != m_iActiveScreen)
    {
        m_Map->Comments(m_iActiveScreen)->Add(Rect, String("TEST ONLY!"));
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawTilesShape(void)
{
    if (g_iNoActiveScreen != m_iActiveScreen)
    {
        // clear the screen
        DrawScreen(m_iActiveScreen);
        // draw the set of tiles for the selected tool
        switch(m_Mode)
        {
        case moTileFree:
            DrawTileFree();
            break;
        case moTileLine:
            DrawTileLine();
            break;
        case moTileDropper:
            DrawTileDropper();
            break;
        case moTileRect:
            DrawTileRect();
            break;
        case moTileRectFill:
            DrawTileRectFill();
            break;
        case moTileCircle:
            DrawTileCircle();
            break;
        case moTileCircleFill:
            DrawTileCircleFill();
            break;
        default:
            break;
        }
        UpdateScreenWindow(false);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawTileFree(bool bAddToMap)
{
    String sTile = m_TileManager->Selected;
    if (sTile.Trim() != "")
    {
        if (!bAddToMap)
        {
            ZXBitmap pTile = m_TileManager->Find(sTile);
            int w;
            int h;
            m_TileManager->GetSize(pTile, w, h);
            int x = m_TileShapeBounds.Right;
            int y = m_TileShapeBounds.Bottom;
            SnapPointsToGrid(x, y);
            bool bAdd = true;
            if (m_bOverwriteOverlaps && bAddToMap)
            {
                RemoveOverlapTiles(x, y, w, h);
            }
            // does the new tile intersect with any existing tiles?
            if (!DoesTileOverlap(x, y, w, h) || m_bOverwriteOverlaps)
            {
                TRect TileRect(x, y, x + w, y + h);
                TRect TempRect;
                // no, so do we have tile in our point list that matches it?
                for (unsigned int i = 0; i < m_PointList.size(); i++)
                {
                    if (bAdd && x == m_PointList[i].x && y == m_PointList[i].y)
                    {
                        bAdd = false;
                    }
                    // if disallow intersections is on then check we are not
                    // intersecting any new tiles as well
                    if (!m_bAllowIntersections && bAdd)
                    {
                        TempRect.Left   = m_PointList[i].x;
                        TempRect.Top    = m_PointList[i].y;
                        TempRect.Right  = TempRect.Left + w;
                        TempRect.Bottom = TempRect.Top  + h;
                        TRect OverRect(std::max(TileRect.Left  , TempRect.Left  ),
                                       std::max(TileRect.Top   , TempRect.Top   ),
                                       std::min(TileRect.Right , TempRect.Right ),
                                       std::min(TileRect.Bottom, TempRect.Bottom));
                        if (OverRect.Top < OverRect.Bottom && OverRect.Left < OverRect.Right)
                            bAdd = false;
                    }
                }
                if (bAdd)
                {
                    TPoint pt;
                    pt.x = x;
                    pt.y = y;
                    m_PointList.push_back(pt);
                }
            }
            for (unsigned int i = 0; i < m_PointList.size(); i++)
            {
                DrawScreenTile(m_iActiveScreen, sTile, m_PointList[i].x, m_PointList[i].y);
            }
        }
        else
        {
            int tiles = m_Map->NumberOfTiles(m_iActiveScreen) - 1;
            for (unsigned int i = 0; i < m_PointList.size(); i++)
            {
                m_Map->AddScreenTile(m_iActiveScreen, sTile, m_PointList[i].x, m_PointList[i].y, i+1 < m_PointList.size()  ? umBatchAdd : umBatchEnd, tiles);
            }
            m_PointList.clear();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawTileLine(bool bAddToMap)
{
    static int iTilesAdded;
    if (!bAddToMap)
        iTilesAdded = 0;
    String sTile = m_TileManager->Selected;
    if (sTile.Trim() != "")
    {
        int xs = m_TileShapeBounds.Left;
        int ys = m_TileShapeBounds.Top;
        int xe = m_TileShapeBounds.Right;
        int ye = m_TileShapeBounds.Bottom;
        int tiles = m_Map->NumberOfTiles(m_iActiveScreen) - 1;

        SnapPointsToGrid(xs, ys);
        SnapPointsToGrid(xe, ye);

        TRect Rect(xs, ys, xe, ye);
        ZXBitmap Tile = m_TileManager->Find(sTile);
        int w, h;
        m_TileManager->GetSize(Tile, w, h);

        int iDX = w;
        int iDY = h;
        int iPX = Rect.Left;
        int iPY = Rect.Top;

        int iYDiff = (Rect.Bottom - Rect.Top) / h;
        if (iYDiff < 0)
        {
            iYDiff = -iYDiff;
            iDY = -h;
        }

        int iXDiff = (Rect.Right - Rect.Left) / w;
        if (iXDiff < 0)
        {
            iXDiff = -iXDiff;
            iDX = -w;
        }

        int iError = 0;
        if (iXDiff > iYDiff)
        {
            for (int i = 0; i <= iXDiff; ++i)
            {
                if (m_bOverwriteOverlaps && bAddToMap)
                {
                    RemoveOverlapTiles(iPX, iPY, w, h);
                }
                if (!DoesTileOverlap(iPX, iPY, w, h) || m_bOverwriteOverlaps)
                {
                    if (bAddToMap)
                    {
                        --iTilesAdded;
                        m_Map->AddScreenTile(m_iActiveScreen, sTile, iPX, iPY, iTilesAdded > 0 ? umBatchAdd : umBatchEnd, tiles);
                    }
                    else
                    {
                        DrawScreenTile(m_iActiveScreen, sTile, iPX, iPY);
                        ++iTilesAdded;
                    }
                }
                iPX += iDX;
                iError += iYDiff;
                if (iError >= iXDiff)
                {
                    iError -= iXDiff;
                    iPY += iDY;
                }
            }
        }
        else
        {
            for (int i = 0; i <= iYDiff; ++i)
            {
                if (m_bOverwriteOverlaps && bAddToMap)
                {
                    RemoveOverlapTiles(iPX, iPY, w, h);
                }
                if (!DoesTileOverlap(iPX, iPY, w, h) || m_bOverwriteOverlaps)
                {
                    if (bAddToMap)
                    {
                        --iTilesAdded;
                        m_Map->AddScreenTile(m_iActiveScreen, sTile, iPX, iPY, iTilesAdded > 0 ? umBatchAdd : umBatchEnd, tiles);
                    }
                    else
                    {
                        DrawScreenTile(m_iActiveScreen, sTile, iPX, iPY);
                        ++iTilesAdded;
                    }
                }
                iPY += iDY;
                iError += iXDiff;
                if (iError >= iYDiff)
                {
                    iError -= iYDiff;
                    iPX += iDX;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawTileDropper(bool bAddToMap)
{
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawTileRect(bool bAddToMap)
{
    static int iTilesAdded;
    if (!bAddToMap)
        iTilesAdded = 0;
    String sTile = m_TileManager->Selected;
    if (sTile.Trim() != "")
    {
        ZXBitmap Tile = m_TileManager->Find(sTile);
        int w, h;
        m_TileManager->GetSize(Tile, w, h);
        int xl = std::min(m_TileShapeBounds.Left, m_TileShapeBounds.Right );
        int xr = std::max(m_TileShapeBounds.Left, m_TileShapeBounds.Right );
        int yt = std::min(m_TileShapeBounds.Top , m_TileShapeBounds.Bottom);
        int yb = std::max(m_TileShapeBounds.Top , m_TileShapeBounds.Bottom);
        int rr = 0;
        int tiles = m_Map->NumberOfTiles(m_iActiveScreen) - 1;
        for (int x = xl; x <= xr; x += w)
        {
            SnapPointsToGrid(x, yt);
            SnapPointsToGrid(x, yb);
            rr = x;
            if (m_bOverwriteOverlaps && bAddToMap)
            {
                RemoveOverlapTiles(x, yt, w, h);
            }
            if (!DoesTileOverlap(x, yt, w, h) || m_bOverwriteOverlaps)
            {
                if (bAddToMap)
                {
                    --iTilesAdded;
                    m_Map->AddScreenTile(m_iActiveScreen, sTile, x, yt, iTilesAdded > 0 ? umBatchAdd : umBatchEnd, tiles);
                }
                else
                {
                    DrawScreenTile(m_iActiveScreen, sTile, x, yt);
                    ++iTilesAdded;
                }
            }
            if (yb - yt > h)
            {
                if (m_bOverwriteOverlaps && bAddToMap)
                {
                    RemoveOverlapTiles(x, yb, w, h);
                }
                if (!DoesTileOverlap(x, yb, w, h) || m_bOverwriteOverlaps)
                {
                    if (bAddToMap)
                    {
                        --iTilesAdded;
                        m_Map->AddScreenTile(m_iActiveScreen, sTile, x, yb, iTilesAdded > 0 ? umBatchAdd : umBatchEnd, tiles);
                    }
                    else
                    {
                        DrawScreenTile(m_iActiveScreen, sTile, x, yb);
                        ++iTilesAdded;
                    }
                }
            }
        }
        for (int y = yt + h; y <= yb - h; y += h)
        {
            SnapPointsToGrid(xl, y);
            if (m_bOverwriteOverlaps && bAddToMap)
            {
                RemoveOverlapTiles(xl, y, w, h);
            }
            if (!DoesTileOverlap(xl, y, w, h) || m_bOverwriteOverlaps)
            {
                if (bAddToMap)
                {
                    --iTilesAdded;
                    m_Map->AddScreenTile(m_iActiveScreen, sTile, xl, y, iTilesAdded > 0 ? umBatchAdd : umBatchEnd, tiles);
                }
                else
                {
                    DrawScreenTile(m_iActiveScreen, sTile, xl, y);
                    ++iTilesAdded;
                }
            }
            if (rr - xl > w)
            {
                if (m_bOverwriteOverlaps && bAddToMap)
                {
                    RemoveOverlapTiles(rr, y, w, h);
                }
                if (!DoesTileOverlap(rr, y, w, h) || m_bOverwriteOverlaps)
                {
                    if (bAddToMap)
                    {
                        --iTilesAdded;
                        m_Map->AddScreenTile(m_iActiveScreen, sTile, rr, y, iTilesAdded > 0 ? umBatchAdd : umBatchEnd, tiles);
                    }
                    else
                    {
                        DrawScreenTile(m_iActiveScreen, sTile, rr, y);
                        ++iTilesAdded;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawTileRectFill(bool bAddToMap)
{
    static int iTilesAdded;
    if (!bAddToMap)
        iTilesAdded = 0;
    String sTile = m_TileManager->Selected;
    if (sTile.Trim() != "")
    {
        ZXBitmap Tile = m_TileManager->Find(sTile);
        int w, h;
        m_TileManager->GetSize(Tile, w, h);
        int xl = std::min(m_TileShapeBounds.Left, m_TileShapeBounds.Right );
        int xr = std::max(m_TileShapeBounds.Left, m_TileShapeBounds.Right );
        int yt = std::min(m_TileShapeBounds.Top , m_TileShapeBounds.Bottom);
        int yb = std::max(m_TileShapeBounds.Top , m_TileShapeBounds.Bottom);
        int tiles = m_Map->NumberOfTiles(m_iActiveScreen) - 1;
        for (int y = yt, tile = 0; y <= yb; y += h)
        {
            for (int x = xl; x <= xr; ++tile, x += w)
            {
                bool finished = (x + w > xr) && (y + h > yb);
                SnapPointsToGrid(x, y);
                if (m_bOverwriteOverlaps && bAddToMap)
                {
                    RemoveOverlapTiles(x, y, w, h);
                }
                if (!DoesTileOverlap(x, y, w, h) || m_bOverwriteOverlaps)
                {
                    if (bAddToMap)
                    {
                        --iTilesAdded;
                        m_Map->AddScreenTile(m_iActiveScreen, sTile, x, y, iTilesAdded > 0 ? umBatchAdd : umBatchEnd, tiles);
                    }
                    else
                    {
                        DrawScreenTile(m_iActiveScreen, sTile, x, y);
                        ++iTilesAdded;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawEllipsePoint(int x, int y, bool bFill, bool bAddToMap, bool bEndBatch)
{
    String sTile = m_TileManager->Selected;
    int tiles = m_Map->NumberOfTiles(m_iActiveScreen) - 1;
    ZXBitmap Tile = m_TileManager->Find(sTile);
    int w, h;
    m_TileManager->GetSize(Tile, w, h);
    SnapPointsToGrid(x, y);
    if (m_bOverwriteOverlaps && bAddToMap)
    {
        RemoveOverlapTiles(x, y, w, h);
    }
    if (!DoesTileOverlap(x, y, w, h) || m_bOverwriteOverlaps)
    {
        if (!bAddToMap)
            DrawScreenTile(m_iActiveScreen, sTile, x, y);
        else
            m_Map->AddScreenTile(m_iActiveScreen, sTile, x, y, bEndBatch ? umBatchEnd : umBatchAdd, tiles);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawEllipsePoints(int x, int y, bool bFill, bool bAddToMap, bool bEndBatch)
{
    String sTile = m_TileManager->Selected;
    int xs = m_TileShapeBounds.Left;
    int ys = m_TileShapeBounds.Top;
    ZXBitmap Tile = m_TileManager->Find(sTile);
    int w, h;
    m_TileManager->GetSize(Tile, w, h);
    if (bFill)
    {
        for (int i = xs - x; i < xs + x; i += w)
        {
            DrawEllipsePoint(i, ys + y, bFill, bAddToMap, false);
            DrawEllipsePoint(i, ys - y, bFill, bAddToMap, bEndBatch && ((i + w) >= (xs + x)));
        }
    }
    else
    {
        DrawEllipsePoint(xs + x, ys + y, bFill, bAddToMap, false);
        DrawEllipsePoint(xs - x, ys + y, bFill, bAddToMap, false);
        DrawEllipsePoint(xs - x, ys - y, bFill, bAddToMap, false);
        DrawEllipsePoint(xs + x, ys - y, bFill, bAddToMap, bEndBatch);
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawTileEllipse(bool bFill, bool bAddToMap)
{
    static int iTilesAdded;
    if (!bAddToMap)
        iTilesAdded = 0;

    String sTile = m_TileManager->Selected;
    if (sTile.Trim() != "")
    {
        int xs = m_TileShapeBounds.Left;
        int ys = m_TileShapeBounds.Top;
        int xe = m_TileShapeBounds.Right;
        int ye = m_TileShapeBounds.Bottom;
        ZXBitmap Tile = m_TileManager->Find(sTile);
        int w, h;
        m_TileManager->GetSize(Tile, w, h);

        SnapPointsToGrid(xs, ys);
        SnapPointsToGrid(xe, ye);

        int XRadius = std::max(1, abs(xe - xs) / w);
        int YRadius = std::max(1, abs(ye - ys) / h);

        int TwoASquare = 2 * XRadius * XRadius;
        int TwoBSquare = 2 * YRadius * YRadius;
        int X = XRadius;
        int Y = 0;
        int XChange = YRadius * YRadius * (1 - 2 * XRadius);
        int YChange = XRadius * XRadius;
        int EllipseError = 0;
        int StoppingX = TwoBSquare * XRadius;
        int StoppingY = 0;

        while ( StoppingX >= StoppingY )
        {
            iTilesAdded = bAddToMap ? iTilesAdded - 1 : iTilesAdded + 1;
            DrawEllipsePoints(X * w, Y * h, bFill, bAddToMap, iTilesAdded > 0);
            ++Y;
            StoppingY += TwoASquare;
            EllipseError += YChange;
            YChange += TwoASquare;

            if (( 2 * EllipseError + XChange) > 0 )
            {
                --X;
                StoppingX -= TwoBSquare;
                EllipseError += XChange;
                XChange += TwoBSquare;
            }
        }
        X = 0;
        Y = YRadius;
        XChange = YRadius * YRadius;
        YChange = XRadius * XRadius * (1 - 2 * YRadius);
        EllipseError = 0;
        StoppingX = 0;
        StoppingY = TwoASquare * YRadius;
        while ( StoppingX <= StoppingY )
        {
            iTilesAdded = bAddToMap ? iTilesAdded - 1 : iTilesAdded + 1;
            DrawEllipsePoints(X * w, Y * h, bFill, bAddToMap, iTilesAdded > 0);
            ++X;
            StoppingX += TwoBSquare;
            EllipseError += XChange;
            XChange += TwoBSquare;
            if (( 2 * EllipseError + YChange) > 0 )
            {
                --Y;
                StoppingY -= TwoASquare;
                EllipseError += YChange;
                YChange += TwoASquare;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawTileCircle(bool bAddToMap)
{
    DrawTileEllipse(false, bAddToMap);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::DrawTileCircleFill(bool bAddToMap)
{
    DrawTileEllipse(true, bAddToMap);
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::AddTileShapeToScreen(void)
{
    switch(m_Mode)
    {
    case moTileFree:
        DrawTileFree(true);
        break;
    case moTileLine:
        DrawTileLine(true);
        break;
    case moTileDropper:
        DrawTileDropper(true);
        break;
    case moTileRect:
        DrawTileRect(true);
        break;
    case moTileRectFill:
        DrawTileRectFill(true);
        break;
    case moTileCircle:
        DrawTileCircle(true);
        break;
    case moTileCircleFill:
        DrawTileCircleFill(true);
        break;
    default:
        break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TZXMapEditor::SetStartScreen()
{
	int oldStartScreen = m_iStartScreen;
	if (m_Map->GetScreenTiles(m_iActiveScreen) > 0)
	{
		m_iStartScreen = m_iActiveScreen;
	}
	if (oldStartScreen != -1)
	{
		DrawScreen(oldStartScreen);
	}
	DrawStartScreenBorder();
}
//---------------------------------------------------------------------------

