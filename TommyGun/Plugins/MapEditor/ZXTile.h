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
#ifndef ZXTileH
#define ZXTileH
//---------------------------------------------------------------------------
/**
 * @class   TTile
 * @brief   This class is used to store the position of a tile on screen
 * @author  Tony Thompson
 * @date    Created 20 April 2003
 */
//---------------------------------------------------------------------------
typedef struct
{
    String                  m_sTile;        /// the name of the tile to draw
    int                     m_iTop;         /// the top position of the tile on screen
    int                     m_iLeft;        /// the left position of the tile on screen
} TTile;

//---------------------------------------------------------------------------
/**
 * @class   TSprite
 * @brief   This class is used to store the position of a sprite on screen
 * @author  Tony Thompson
 * @date    Created 11 January 2011
 */
//---------------------------------------------------------------------------
typedef struct
{
    String                  m_sSprite;      /// the name of the sprite to draw
    int                     m_iType;        /// the type id of the sprite
    int                     m_iTop;         /// the top position of the tile on screen
    int                     m_iLeft;        /// the left position of the tile on screen
} TSprite;

//---------------------------------------------------------------------------
/**
 * @class   TMapObject
 * @brief   This class is used to store the position of an object on screen
 * @author  Tony Thompson
 * @date    Created 11 January 2011
 */
//---------------------------------------------------------------------------
typedef struct
{
    String                  m_sObject;      /// the name of the object to draw
    int                     m_iScreen;      /// the screen the object belongs to (could also be inventory-255, no start screen-254)
    int                     m_iTop;         /// the top position of the tile on screen
    int                     m_iLeft;        /// the left position of the tile on screen
} TMapObject;
#endif // ZXTileH
