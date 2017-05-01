/*---------------------------------------------------------------------------

	(c) 2002 Scorpio Software
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
#ifndef KIconButtonH
#define KIconButtonH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE KIconButton : public TGraphicControl
{
private:
    int                     FIconIndex;
    bool                    FSelected;
    bool                    FGrouped;
    TColor                  FColorBackground;
    TColor                  FColorSelected;
    TColor                  FColorBorder;
    TColor                  FColorBorderSelected;
    TColor                  FColorHighlight;
    String                  FCaption;
    TImageList*             FIconsHot;
    TImageList*             FIconsCold;
    int                     FCornerWidth;
    int                     FCornerHeight;
    TFont*                  FFont;

    bool                    m_bMouseButtonDown;

    enum RSetColorValues   {eColorBackground, eColorSelected, eColorBorder, eColorBorderSelected, eColorHighlight   };
    enum RSetBoolValues    {eFlagSelected, eFlagGrouped                                                             };
    enum RSetStringValues  {eStringCaption                                                                          };
    enum RSetImageValues   {eIconsHot, eIconsCold                                                                   };
    enum RSetIntValues     {eIntIconIndex, eIntCornerWidth, eIntCornerHeight                                        };

            void __fastcall SetColor(int iIndex, TColor cValue);
            void __fastcall SetBool(int iIndex, bool bValue);
            void __fastcall SetString(int iIndex, String sValue);
            void __fastcall SetIcons(int iIndex, TImageList* Icons);
            void __fastcall SetInt(int iIndex, int iValue);
            void __fastcall SetFont(TFont* pFont);

            void __fastcall DrawCaption(void);
            void __fastcall SplitCaption(String& Line1, String& Line2);
            void __fastcall DrawIcon(void);
            void __fastcall DrawLine(const String& sText, int iLineIndex);
            void __fastcall UnselectButtons(void);

protected:
            void __fastcall DoMouseDown (TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall DoMouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall DoMouseMove(TShiftState Shift, int X, int Y);
    virtual void __fastcall Paint(void);
    DYNAMIC void __fastcall MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall MouseUp(TMouseButton Button, TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);

public:
                __fastcall  KIconButton(TComponent* Owner);
                __fastcall ~KIconButton();

__published:

    __property TColor       ColorBackground     = {read = FColorBackground      , write = SetColor  , index = eColorBackground      };
    __property TColor       ColorSelected       = {read = FColorSelected        , write = SetColor  , index = eColorSelected        };
    __property TColor       ColorBorder         = {read = FColorBorder          , write = SetColor  , index = eColorBorder          };
    __property TColor       ColorBorderSelected = {read = FColorBorderSelected  , write = SetColor  , index = eColorBorderSelected  };
    __property TColor       ColorHighlight      = {read = FColorHighlight       , write = SetColor  , index = eColorHighlight       };
    __property bool         Grouped             = {read = FGrouped              , write = SetBool   , index = eFlagGrouped          };
    __property bool         Selected            = {read = FSelected             , write = SetBool   , index = eFlagSelected         };
    __property String       Caption             = {read = FCaption              , write = SetString , index = eStringCaption        };
    __property TImageList*  IconsHot            = {read = FIconsHot             , write = SetIcons  , index = eIconsHot             };
    __property TImageList*  IconsCold           = {read = FIconsCold            , write = SetIcons  , index = eIconsCold            };
    __property int          IconIndex           = {read = FIconIndex            , write = SetInt    , index = eIntIconIndex         };
    __property int          CornerWidth         = {read = FCornerWidth          , write = SetInt    , index = eIntCornerWidth       };
    __property int          CornerHeight        = {read = FCornerHeight         , write = SetInt    , index = eIntCornerHeight      };
    __property TFont*       Font                = {read = FFont                 , write = SetFont                                   };

    // Inherited Properties
    __property Align;
    __property Anchors;
    __property Color;
    __property Constraints;
    __property Cursor;
    __property PopupMenu;
    __property ShowHint;
    __property Visible;
    __property Width;
    __property Height;
    __property ParentColor;

    // Inherited Events
    __property OnClick;
    __property OnDblClick;
    __property OnMouseDown;
    __property OnMouseMove;
    __property OnMouseUp;
    __property OnResize;
};
//---------------------------------------------------------------------------
#endif
