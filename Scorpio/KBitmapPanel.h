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
#ifndef BitmapPanelH
#define BitmapPanelH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//#include <TFlatPanelUnit.hpp>
//---------------------------------------------------------------------------
class PACKAGE KBitmapPanel : public TCustomPanel
{
private:
	TImage*         		FImage;
    TLabel*					FLabel;
	AnsiString				FCaption;
    AnsiString				FFile;
    int						FEdge;
    int						FLabelEdge;
    int						FTopEdge;
    int						FGroupIndex;
    int						FBitmapWidth;
    int						FBitmapHeight;
    bool					FBitmapStretch;
    bool					FKeepBitmapSize;
    bool					FSelected;
    bool					FShowLabel;
    bool					FTransparent;
    bool					FChecked_;
    bool                    FCenterImage;
    TColor					FColorSelected;
    TColor					FColorUnSelected;
    TColor					FColorSelectedText;
    TColor					FColorUnSelectedText;
    //KScrollPanel*			FScroller;


	TPicture* __fastcall 	GetPicture( void );

	void __fastcall 		SetPicture( TPicture* Value );
	void __fastcall 		SetInt(int Index, int Value );
	void __fastcall 		SetBool(int Index, bool Value );
	void __fastcall 		SetString(int Index, AnsiString Value );
	void __fastcall 		SetColor(int Index, TColor Value );

	void __fastcall 		Change( void );
	void __fastcall 		ComponentClick( TObject* Sender );
	void __fastcall 		ComponentDblClick( TObject* Sender );

protected:

    DYNAMIC void __fastcall Resize();
    //DYNAMIC void __fastcall Click();
    //DYNAMIC void __fastcall DoEnter();
    //DYNAMIC void __fastcall DoExit();

public:
	__fastcall KBitmapPanel(TComponent* Owner);
	__fastcall ~KBitmapPanel( );
    void __fastcall ReloadBitmap( void );
    void __fastcall LoadFromFile( String& bmpFile );
__published:

    __property TPicture*	Picture = { read = GetPicture, write = SetPicture };
    __property AnsiString	File = { read = FFile, write = SetString, index = 1 };
    __property AnsiString	Caption = { read = FCaption, write = SetString, index = 0, stored = true };

    __property int 			Edge    = { read = FEdge, write = SetInt, index = 0, default = 4, stored = true };
    __property int			BitmapWidth  = { read = FBitmapWidth , write = SetInt, index = 1, default = 64, stored = true };
    __property int			BitmapHeight = { read = FBitmapHeight, write = SetInt, index = 2, default = 64, stored = true };
    __property int			GroupIndex = { read = FGroupIndex, write = SetInt, index = 3, default = 0, stored = true };
    __property int 			LabelEdge    = { read = FLabelEdge, write = SetInt, index = 4, default = 4, stored = true };
    __property int 			TopEdge    = { read = FTopEdge, write = SetInt, index = 5, default = 4, stored = true };

    __property bool			KeepBitmapSize = { read = FKeepBitmapSize, write = SetBool, index = 0, default = true, stored = true };
    __property bool			Selected = { read = FSelected, write = SetBool, index = 1, default = false, stored = true };
    __property bool			StretchBitmap = { read = FBitmapStretch, write = SetBool, index = 2, default = true, stored = true };
    __property bool			ShowLabel = { read = FShowLabel, write = SetBool, index = 3, default = true, stored = true };
    __property bool			Transparent = { read = FTransparent, write = SetBool, index = 4, default = false, stored = true };
    __property bool			CenterImage = { read = FCenterImage, write = SetBool, index = 5, default = false, stored = true };

    __property TColor		ColorSelected = { read = FColorSelected, write = SetColor, index = 0, stored = true };
    __property TColor		ColorUnSelected = { read = FColorUnSelected, write = SetColor, index = 1, stored = true };
    __property TColor		ColorSelectedText = { read = FColorSelectedText, write = SetColor, index = 2, stored = true };
    __property TColor		ColorUnSelectedText = { read = FColorUnSelectedText, write = SetColor, index = 3, stored = true };

    // inherited properties from TCustomPanel
    __property Align;
    __property Anchors;
    //__property AutoSize;
    //__property BiDiMode;
    //__property BevelInner;
    //__property BevelOuter;
    // __property BevelWidth;
    //__property BorderStyle;
    //__property BorderWidth;
    __property Color;	// = { read = FColorUnSelected, write = SetColor, index = 1, stored = true };
    __property Constraints;
    __property DragCursor;
    __property DragKind;
    __property DragMode;
    __property Enabled;
    __property Font;
    __property FullRepaint;
    //__property ParentBiDiMode;
    __property ParentColor;
    __property ParentFont;
    __property ParentShowHint;
	__property PopupMenu;
    __property Tag;
	__property TabOrder;
    __property TabStop;
    __property Visible;

    // inherited events from TCustomPanel
    __property OnCanResize;
    __property OnClick;
    __property OnConstrainedResize;
    __property OnDblClick;
    __property OnDragOver;
    __property OnEndDrag;
    __property OnEnter;
    __property OnExit;
    __property OnGetSiteInfo;
    __property OnMouseDown;
    __property OnMouseMove;
	__property OnMouseUp;
    __property OnResize;
    __property OnStartDrag;
};
//---------------------------------------------------------------------------
#endif
