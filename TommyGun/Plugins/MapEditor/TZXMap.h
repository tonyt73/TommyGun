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
#ifndef TZXMapH
#define TZXMapH
//- SYSTEM ------------------------------------------------------------------
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
//- VCL ---------------------------------------------------------------------
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <StdActns.hpp>
//- APP ---------------------------------------------------------------------
//#include "TZXImage.h"
#include "ZXTileManager.h"
#include "ZXSpriteManager.h"
#include "ZXTile.h"
#include "ZXComments.h"
//---------------------------------------------------------------------------
/**
 * @class   TTiledScreen
 * @brief   This class is used to store the tiles in a screen. It also contains the
 *          Bitmap used to draw the screen contents
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
typedef struct
{
    bool                        m_bDirty;               // flag: the screen has changed and needs redrawing and/or saving
    int                         m_iLeft;                // the left position of the screen in the layout editor
    int                         m_iTop;                 // the top position of the screen in the layout editor
    Graphics::TBitmap*          m_bmScreen;             // a bitmap used to as an off screen buffer - used when editing the layout of the screens
    std::vector<TTile*>         m_ScreenTiles;          // the list of on screen tiles
    std::vector<TSprite*>       m_ScreenSprites;        // the list of on screen sprites
    ZXComments                  m_Comments;             // the list of comments for the screen
} TTiledScreen;
//---------------------------------------------------------------------------
/**
 * @class   TScreenTable
 * @brief   This class is used to store the screen table when the project is exported
 *          It is used by the BuildScreenTable() to merge duplicate screens if required
 * @author  Tony Thompson
 * @date    Created 4 May 2003
 */
//---------------------------------------------------------------------------
typedef struct
{
    int m_iScreensIndex;    // the index maps into the screens table that represents screen to use
    int m_iLeft;            // the left position of the screen in the layout editor
    int m_iTop;             // the top position of the screen in the layout editor
} TScreenEntry;
//---------------------------------------------------------------------------
enum eUndoMode { umAdd, umBatchAdd, umBatchEnd, umSkip };
//---------------------------------------------------------------------------
class TZXMap
{
private:
    std::vector<TTiledScreen*>  m_Screens;              // the list of on screen tiles
    std::vector<TScreenEntry>   m_ScreenTable;          // the list of mappings for screens
    ZXTileManager*              m_TileManager;          // the tile manager
    ZXSpriteManager*            m_SpriteManager;        // the sprite manager

    int                         m_iScreenWidth;         // width of the screen
    int                         m_iScreenHeight;        // height of the screen
    int                         m_iScreensAcross;       // the number of screens across
    int                         m_iScreensDown;         // the number of screens down
    int                         m_iTileWidth;           // width of tile spacing
    int                         m_iTileHeight;          // height of tile spacing
    bool                        m_bIsDirty;             // flag: tiles not saved
    bool                        m_bMergeDupScreens;     // flag: states whether duplicate screens are allowed or removed
    bool                        m_bUndoInProgress;      // flag: undo operation in progress
    TColor                      m_cBackgroundColor;     // the color the background
    KXmlInfo                    m_UndoInfo;
    KXmlInfo                    m_RedoInfo;

    bool        __fastcall  PointIsInRect(int X, int Y, TRect Rect);
    bool        __fastcall  RectsIntersect(const TRect& Rect1, const TRect& Rect2) const;
    int         __fastcall  CountTileUsage(const String& sTile);
    int         __fastcall  FindDuplicateScreen(int iScreen);
    bool        __fastcall  TileIsInScreen(int iScreen, TTile* Tile);
    bool        __fastcall  IsScreenDuplicate(int iScreen);
    int         __fastcall  GetDuplicateScreen(int iScreen);
    bool        __fastcall  LoadScreen(KXmlInfo& xmlInfo);
    void        __fastcall  SaveScreen(KXmlInfo& xmlInfo, int iScreen);
    int         __fastcall  FindTile(int iScreen, const String& sTile, int iLeft, int iTop);
    void        __fastcall  UndoTileMove(KXmlInfo* xmlInfo);
    void        __fastcall  UndoTileAdd(KXmlInfo* xmlInfo);
    void        __fastcall  UndoTileDel(KXmlInfo* xmlInfo);
    void        __fastcall  UndoScreenMove(KXmlInfo* xmlInfo);
    void        __fastcall  UndoScreenAdd(KXmlInfo* xmlInfo);
    void        __fastcall  UndoScreenDel(KXmlInfo* xmlInfo);
    void        __fastcall  UndoScreenSwap(KXmlInfo* xmlInfo);

public:
                __fastcall  TZXMap();
                __fastcall ~TZXMap();

    // set functions
    void        __fastcall  SetManagers(ZXTileManager* TileManager, ZXSpriteManager* SpriteManager);
    void        __fastcall  SetBackgroundColor(TColor cColor);
    void        __fastcall  SetScreenSize(int iWidth, int iHeight);
    void        __fastcall  SetScreenGrid(int iAcross, int iDown);
    // screen/tile functions
    int         __fastcall  BuildScreenTable(bool bMergeDuplicates);
    void        __fastcall  ClearScreenTable(void);
    void        __fastcall  ClearDirty(void);
   unsigned int __fastcall  Screens(void);
    int         __fastcall  GetScreenTiles(int iScreen);
    void        __fastcall  GetScreenPosition(int iScreen, int& iLeft, int& iTop);
    void        __fastcall  GetTileSize(const String& sTile, int& iWidth, int& iHeight);
    bool        __fastcall  GetScreenTile(int iScreen, int iTile, TTile& Tile);
    bool        __fastcall  AddScreenTile(int iScreen, TTile& Tile, eUndoMode UndoMode);
    bool        __fastcall  AddScreenTile(int iScreen, const String& sTile, int iLeft, int iTop, eUndoMode UndoMode, int iIndex = -1);
    int         __fastcall  AddScreen(int iLeft, int iTop, int iIndex = -1);
    int         __fastcall  AddScreen(void);
    void        __fastcall  CopyScreen(int iSrc, int iDest);
    void        __fastcall  DeleteScreen(int iScreen);
    int         __fastcall  NumberOfTiles(int iScreen);
    int         __fastcall  FindScreen(int iLeft, int iTop);
    void        __fastcall  RenameTile(const String& sOldName, const String& sNewName);
    void        __fastcall  RemoveTile(const String& sName);
    int         __fastcall  BringToFront(int iScreen, int iTile);
    int         __fastcall  SendToBack(int iScreen, int iTile);
    int         __fastcall  GetScreenSprites(int iScreen);
    bool        __fastcall  GetScreenSprite(int iScreen, int iSprite, TSprite& Sprite);
    bool        __fastcall  AddScreenSprite(int iScreen, const String& sSprite);
    bool        __fastcall  AddScreenSprite(int iScreen, const String& sSprite, int iType, int iLeft, int iTop);
    void        __fastcall  RemoveScreenSprite(int iScreen, int iSprite);
    void        __fastcall  SetScreenSpriteImage(int iScreen, int iSprite, const String& sSprite);
    void        __fastcall  SetScreenSpriteType(int iScreen, int iSprite, int iType);
    void        __fastcall  SetScreenSpritePos(int iScreen, int iSprite, int iX, int iY);

    // misc functions
    void        __fastcall  Clear(void);
    bool        __fastcall  New(int screenWidth, int screenHeight, int screensAcross, int screensDown, bool overwrite);
    void        __fastcall  Sort(void);
    int         __fastcall  ReplaceTile(String sTileToFind, String sReplaceWith);
    bool        __fastcall  DoesTileOverlap(int iScreen, TTile* Tile, bool bAllowIntersections);
    bool        __fastcall  DoesTileOverlap(int iScreen, int iTileX, int iTileY, int iTileW, int iTileH, bool bAllowIntersections);
    void        __fastcall  RemoveOverlapTiles(int iScreen, int iTileX, int iTileY, int iTileW, int iTileH);
    int         __fastcall  FindScreenTile(int iScreen, int X, int Y);
    int         __fastcall  FindScreenSprite(int iScreen, int X, int Y);
    void        __fastcall  FindScreenTiles(int iScreen, const TRect& Rect, TSelectionList& List) const;
  TTiledScreen* __fastcall  Screen(int iScreen);
    TTile*      __fastcall  Tile(int iScreen, int iTile);
    TSprite*    __fastcall  Sprite(int iScreen, int iTile);
    ZXComments* __fastcall  Comments(int iScreen);
    void        __fastcall  MoveTile(int iScreen, int iTile, int X, int Y, eUndoMode UndoMode);
    void        __fastcall  MoveSprite(int iScreen, int iTile, int X, int Y, eUndoMode UndoMode);
    void        __fastcall  DeleteTile(int iScreen, int iTile, eUndoMode UndoMode);
    void        __fastcall  Dirty(int iScreen);
    bool        __fastcall  Load(KXmlInfo& xmlInfo);
    void        __fastcall  Save(KXmlInfo& xmlInfo, bool bCleanDirty = true);
   unsigned int __fastcall  Bytes(void);
    void        __fastcall  UndoRestore(KXmlInfo* xmlInfo);

    __property  int         ScreenWidth         = { read = m_iScreenWidth       };
    __property  int         ScreenHeight        = { read = m_iScreenHeight      };
    __property  int         ScreensAcross       = { read = m_iScreensAcross     };
    __property  int         ScreensDown         = { read = m_iScreensDown       };
    __property  int         TileWidth           = { read = m_iTileWidth, write = m_iTileWidth   };
    __property  int         TileHeight          = { read = m_iTileHeight, write = m_iTileHeight  };
    __property  TColor      BackgroundColor     = { read = m_cBackgroundColor   };
    __property  bool        IsDirty             = { read = m_bIsDirty           };
    __property  bool        MergeDupScreens     = { read = m_bMergeDupScreens, write = m_bMergeDupScreens   };
};
//---------------------------------------------------------------------------
#endif
 
