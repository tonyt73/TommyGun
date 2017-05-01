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
#ifndef TZXMapEditorH
#define TZXMapEditorH
//- SYSTEM ------------------------------------------------------------------
#include <vector>
#include <algorithm>
#include <functional>
//- VCL ---------------------------------------------------------------------
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <StdActns.hpp>
//- APP ---------------------------------------------------------------------
#include "..\..\Framework\FrameworkInterface.h"
#include "ZXTile.h"
//---------------------------------------------------------------------------
typedef struct
{
    int                 Tile;       // the tile index
    TPoint              Start;      // where the tile started from
    TPoint              Current;    // where the tile current is
    TPoint              Last;       // where the tile was
    Graphics::TBitmap*  TileBG;     // the background behind a tile when it is being moved
}
TTileSelect;
typedef std::vector<TTileSelect>    TSelectionList;
typedef TSelectionList::iterator    TSelectionListIterator;
//---------------------------------------------------------------------------
typedef struct
{
    std::vector<TTile>  Tiles;
    int                 Screen;
}
TCopyInfo;
//---------------------------------------------------------------------------
typedef std::vector<TPoint>         TPointList;
//---------------------------------------------------------------------------
#include "TZXMap.h"
#include "ZXTileManager.h"
#include "ZXSpriteManager.h"
#include "ZXObjectManager.h"
//---------------------------------------------------------------------------
/**
 * @class   eModes
 * @brief   This enumeration is used for indicating the mode the editor is in
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
enum eModes             { moSelectTile = 1, moSelectSprite, moSelectObject,
                          moTileFree, moTileLine,
                          moTileDropper, moTileRect, moTileRectFill, moTileCircle,
                          moTileCircleFill, moMoveScreen, moAddComment,
                        };
enum eScoreAlignment    { saTop, saBottom, saLeft, saRight                          };
enum eMouseZone         { mzNone, mzScreenWindow = 1, mzMapWindow                   };
//---------------------------------------------------------------------------
/**
 * @class   TZXMapEditor
 * @brief   This class handles the editing of tiles onto offscreen bitmaps
 * @author  Tony Thompson
 * @date    Created 8 Feburary 2004
 */
//---------------------------------------------------------------------------
class TZXMapEditor
{
private:

    typedef struct
    {
        TRect           Rect;
        bool            Active;
        int             Screen;         // the screen that the selection is from
        TSelectionList  ActiveList;     // the current list of selected items
        TSelectionList  SelectList;     // the list of items partial selected during a drag event
    } TSelectionInfo;

    typedef struct
    {
        TRect           Position;
        Text            String;
    } TCommentRect;

private:
    Graphics::TBitmap*          m_bmMapBackground;      // the background behind a screen when it is being moved in the map editor
    TZXMap*                     m_Map;                  // the map we are editing
    Graphics::TBitmap*          m_bmScorePanel;         // the score panel bitmap
    TImage*                     m_imgScreenEditor;      // the image control to blit the tile editor screen buffer to
    TImage*                     m_imgMapEditor;         // the image control to blit the layout editor screen buffer to
    ZXTileManager*              m_TileManager;          // the tile manager
    ZXSpriteManager*            m_SpriteManager;        // the sprite manager
    ZXObjectManager*            m_ObjectManager;        // the object manager
    eModes                      m_Mode;                 // the mode of the editor
    eModes                      m_OldMode;              // the old mode of the editor (before a screen move event)
    eScoreAlignment             m_ScorePanelAlignment;  // the alignment of the score panel
    String                      m_sScorePanel;          // the file name of the score panel being used
    eMouseZone                  m_MouseZone;
    DWORD                       m_dwError;
    TZX_HPLUGIN                 m_PluginHandle;         // the handle of the plugin

    // selection
    TSelectionInfo              m_Selection;
    TCopyInfo                   m_CopyInfo;
    TPointList                  m_PointList;            // list of points used during free draw tool

    bool                        m_bScreenCursorDrawn;   // flag: whether the screen cursor has been drawn
    bool                        m_bSnapToGrid;          // flag: whether the tiles should snap to a grid
    bool                        m_bAllowIntersections;  // flag: whether the tiles can be overlapped
    bool                        m_bOverwriteOverlaps;   // flag: whether the place tile should replace the overlapped tile
    bool                        m_bShowGrid;            // flag: whether to show the alignment grid
    bool                        m_bDraggingScreen;      // flag: user is dragging a screen for relocation
    bool                        m_bUndoInProgress;      // flag: undo operation is in progress
    bool                        m_bPlaceTileAdded;      // flag: indicates that we have added the place tile to the screen
    bool                        m_bDraggingSelection;   // flag: indicates we are dragging the selected tiles
    int                         m_iScreenBeingDragged;  // the screen index of the screen being dragged
    int                         m_iActiveScreen;        // the currently active screen being edited
    int                         m_iStartScreen;         // the screen selected as the start screen
    int                         m_iSelectedScreen;      // the currently selected screen in the layout editor
    int                         m_iLastScreenX;         // the last X position of the screen cursor
    int                         m_iLastScreenY;         // the last Y position of the screen cursor
    int                         m_iGridWidth;           // the width of the grid to snap to
    int                         m_iGridHeight;          // the height of the grid to snap to
    int                         m_iScreenScale;         // the scaling of the edit screen
    int                         m_iMapScale;            // the scaling of the map screens
    int                         m_iScreenGap;           // the gap between screens in the layout editor
    int                         m_iLastMouseX;          // last x position of the mouse
    int                         m_iLastMouseY;          // last y position of the mouse
    int                         m_iDragOffsetX;         // dragging offset
    int                         m_iDragOffsetY;         // dragging offset
    int                         m_iLayoutScreenWidth;   // the width of the layout screens to draw
    int                         m_iLayoutScreenHeight;  // the height of the layout screens to draw
    TRect                       m_TileShapeBounds;      // the bounds of the current tile tool ie. sx,sy->ex,ey

    TMouseEvent                 FOnMapMouseDown;
    TMouseEvent                 FOnMapMouseUp;
    TMouseMoveEvent             FOnMapMouseMove;
    int                         m_iMapBackX;
    int                         m_iMapBackY;
    int                         m_iMapBackW;
    int                         m_iMapBackH;
    int                         m_iMapScrollX;
    int                         m_iMapScrollY;
    int                         m_iScreenX;
    int                         m_iScreenY;

    TMouseEvent                 FOnScreenMouseDown;
    TMouseEvent                 FOnScreenMouseUp;
    TMouseMoveEvent             FOnScreenMouseMove;

    // screen layout editor
    void        __fastcall  SaveScreenTile(int iScreen, int iSelectIndex);
    void        __fastcall  RestoreScreenTiles(void);
    void        __fastcall  RestoreScreenTile(int iSelectIndex = 0);
    void        __fastcall  UpdateScreenEditor(void);
    void        __fastcall  ClearScreen(int iScreen);
    void        __fastcall  BlitScreen(int iScreen);
    void        __fastcall  DrawScreenBorder(int iScreen, TTile* STile, TColor cColor);
    void        __fastcall  DrawScreenBorder(int iScreen, TSprite* STile, TColor cColor);
    void        __fastcall  DrawScreenBorder(int iScreen, TMapObject* STile, TColor cColor);
    void        __fastcall  DrawScreenTile(int iScreen, int iSelectIndex);
    void        __fastcall  DrawScreenTile(int iScreen, const String& sTile, int X, int Y);
    void        __fastcall  DrawScreenSprite(int iScreen, int iTile);
    void        __fastcall  DrawScreenSprite(int iScreen, const String& sTile, int X, int Y);
    void        __fastcall  DrawScreenObject(int iScreen, const String& sObject);
    void        __fastcall  DrawScreen(int iScreen);
    void        __fastcall  UpdateScreens(void);
    void        __fastcall  DrawGrid(void);

	// map layout drawing
	void        __fastcall  RestoreMapBackground(void);
	void        __fastcall  SaveMapBackground(void);
	void        __fastcall  EraseMapCursor(bool bRefresh = true);
	void        __fastcall  DrawMapCursor(bool bRefresh = true);
	void        __fastcall  XorMapCursor(bool bRefresh = true);
	void        __fastcall  BlitMapScreen(int iScreen);
	void        __fastcall  BlitDragScreen(void);
	void 		__fastcall 	DrawStartScreenBorder();

    // misc
    void        __fastcall  SnapPointsToGrid(int& X, int& Y);
    bool        __fastcall  DoesTileOverlap(int iTileIndex = 0);
    bool        __fastcall  DoesTileOverlap(int x, int y, int w, int h);
    void        __fastcall  RemoveOverlapTiles(int x, int y, int w, int h);
    void        __fastcall  ClearSelection(void);

    // drawing tools
    void        __fastcall  DrawTilesShape(void);

    // editting
    void        __fastcall  MoveTile(int iTile, int X, int Y, bool bUpdate = true);
    void        __fastcall  MoveSprite(int iTile, int X, int Y, bool bUpdate = true);
    void        __fastcall  MoveObject(int iTile, int X, int Y, bool bUpdate = true);
    void        __fastcall  PlaceTile(void);
    void        __fastcall  DrawTileFree(bool bAddToMap = false);
    void        __fastcall  DrawTileLine(bool bAddToMap = false);
    void        __fastcall  DrawTileDropper(bool bAddToMap = false);
    void        __fastcall  DrawTileRect(bool bAddToMap = false);
    void        __fastcall  DrawTileRectFill(bool bAddToMap = false);
    void        __fastcall  DrawEllipsePoint(int x, int y, bool bFill, bool bAddToMap, bool bEndBatch);
    void        __fastcall  DrawEllipsePoints(int x, int y, bool bFill, bool bAddToMap, bool bEndBatch);
    void        __fastcall  DrawTileEllipse(bool bFill, bool bAddToMap);
    void        __fastcall  DrawTileCircle(bool bAddToMap = false);
    void        __fastcall  DrawTileCircleFill(bool bAddToMap = false);
    void        __fastcall  AddTileShapeToScreen(void);

    // mouse functions
    void        __fastcall  ScreenMouseDown (TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void        __fastcall  ScreenMouseMove (TObject* Sender, TShiftState Shift, int X, int Y);
    void        __fastcall  ScreenMouseUp   (TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void        __fastcall  MapMouseDown    (TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void        __fastcall  MapMouseMove    (TObject* Sender, TShiftState Shift, int X, int Y);
    void        __fastcall  MapMouseUp      (TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

    void        __fastcall  OnTileClick(TObject* Sender);

    void        __fastcall  UndoScreenSelect(KXmlInfo* xmlInfo);
    void        __fastcall  UndoScreenMove(KXmlInfo* xmlInfo);

    int         __fastcall  GetTileSelect(int iTile);
    void        __fastcall  DrawSelection(bool bShow);
    bool        __fastcall  IsSelected(int iTile);

    // comments
    

public:
                __fastcall  TZXMapEditor();
                __fastcall ~TZXMapEditor();
    // setup
    void        __fastcall  SetCanvas(TImage* ScreenImage, TImage* MapImage);
    void        __fastcall  SetManagers(ZXTileManager* TileManager, ZXSpriteManager* SpriteManager, ZXObjectManager* ObjectManager);
    void        __fastcall  SetMap(TZXMap* Map);
    void        __fastcall  SetBackgroundColor(TColor cColor);
    void        __fastcall  SetScreenSize(int iWidth, int iHeight);
    void        __fastcall  SetGridInfo(bool bSnapToGrid, int iWidth, int iHeight);
    void        __fastcall  ShowGrid(bool bShow);
    void        __fastcall  SetTile(const String& sTileFile);
    void        __fastcall  SetActiveScreen(int iScreen, bool bUpdate = true);
    void        __fastcall  SetScreenGrid(int iAcross, int iDown);
    void        __fastcall  SetScreenGap(int iGap);
    void        __fastcall  SetScreenScale(int iScale);
    void        __fastcall  SetMapScale(int iScale);
    void        __fastcall  SetScreenOffset(int X, int Y) { m_iScreenX = X; m_iScreenY = Y; }
    void        __fastcall  SetStartScreen();
    // editing functions
    void        __fastcall  IntersectionsAllowed(bool bState);
    void        __fastcall  OverwriteOverlaps(bool bState);
    void        __fastcall  Mode(eModes Mode);
    eModes      __fastcall  Mode(void) { return m_Mode; }
    void        __fastcall  RemoveScreen(void);
    int         __fastcall  ReplaceTile(String sTileToFind, String sReplaceWith);
    void        __fastcall  BringToFront(void);
    void        __fastcall  SendToBack(void);
    // drawing functions
    void        __fastcall  Update();
    void        __fastcall  UpdateScreenWindow(bool bRedrawScreen = true);
    void        __fastcall  UpdateMapWindow(void);
    void        __fastcall  Invalidate(void);
    // screen/tile functions
    void        __fastcall  Clear(void);
    int         __fastcall  AddScreen(int iLeft, int iTop);
    int         __fastcall  AddScreen(void);
    int         __fastcall  CloneScreen(int iLeft = -1, int iTop = -1);

    void        __fastcall  UndoRestore(KXmlInfo* xmlInfo);
    void        __fastcall  Copy(void);
    void        __fastcall  Cut(void);
    void        __fastcall  Paste(void);
    void        __fastcall  Delete(void);

    void        __fastcall  SaveBitmap(const String& sFile);

    // comments
    void        __fastcall  CommentAdd(const TRect& Rect);

    __property  int         ScreensGap          = { read  = m_iScreenGap            };
    __property  int         GridWidth           = { read  = m_iGridWidth            };
    __property  int         GridHeight          = { read  = m_iGridHeight           };
    __property  bool        AllowIntersections  = { read  = m_bAllowIntersections   };
    __property  bool        SnapToGrid          = { read  = m_bSnapToGrid           };
    __property  TZX_HPLUGIN PluginHandle        = { write = m_PluginHandle          };
    __property  int         ActiveScreen        = { read  = m_iActiveScreen         };
    __property  int         StartScreen         = { read  = m_iStartScreen, write = m_iStartScreen };
};
//---------------------------------------------------------------------------
#endif
