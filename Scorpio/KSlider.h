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
#ifndef SliderH
#define SliderH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class PACKAGE KSlider : public TGraphicControl
{
private:
    int				FPosition;
    int				FMin;
    int				FMax;
    bool			FFlat;
    TColor			FColorFore;
    TColor			FColorShadow;
    TColor			FColorBack;
    TColor			FColorCursor;
    TColor			FColorCursorShadow;
    TCustomEdit*	FEditBox;

    TMouseEvent 	FOnMouseDown;
    TMouseMoveEvent FOnMouseMove;
    TNotifyEvent	FOnChange;

	void __fastcall SetColorFore( TColor color );
	void __fastcall SetColorBack( TColor color );
	void __fastcall SetColorShadow( TColor color );
	void __fastcall SetColorCursor( TColor color );
	void __fastcall SetColorCursorShadow( TColor color );
	void __fastcall SetPosition( int pos );
	void __fastcall SetMin( int min );
	void __fastcall SetMax( int max );
	void __fastcall SetEditBox( TCustomEdit* editbox );
	void __fastcall SetFlat( bool flat );

	void __fastcall drawBar( int offset );
	void __fastcall drawCursor( int offset );

protected:
    virtual void __fastcall Paint();
    DYNAMIC void __fastcall Resize( void );
    DYNAMIC void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
    DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);

public:
	__fastcall KSlider(TComponent* Owner);
	__fastcall ~KSlider();
    void __fastcall Notification( TComponent* AComponent, TOperation Operation );

__published:
    __property TColor ColorForeground = { read = FColorFore, write = SetColorFore };
    __property TColor ColorBackground = { read = FColorBack, write = SetColorBack };
    __property TColor ColorShadow = { read = FColorShadow, write = SetColorShadow };
    __property TColor ColorCursor = { read = FColorCursor, write = SetColorCursor };
    __property TColor ColorCursorShadow = { read = FColorCursorShadow, write = SetColorCursorShadow };
    __property int Position = { read = FPosition, write = SetPosition };
    __property int Min = { read = FMin, write = SetMin };
    __property int Max = { read = FMax, write = SetMax };
    __property TCustomEdit* EditBox = { read = FEditBox, write = SetEditBox };
    __property bool Flat = { read = FFlat, write = SetFlat };

    // custom events
    __property TNotifyEvent OnChange = { read = FOnChange, write = FOnChange };

    // inherited properties from TGraphicControl
    __property Align;
    __property Anchors;
    //__property Constraints;
    __property Height;
    __property Width;
    __property ShowHint;
    __property Visible;
    __property Enabled;

    // inherited events from TGraphicControl
    __property OnCanResize;
    __property OnClick;
    __property OnConstrainedResize;
    __property OnDblClick;
    __property OnMouseDown;
    __property OnMouseMove;
	__property OnMouseUp;
    __property OnResize;
};
//---------------------------------------------------------------------------
#endif
 