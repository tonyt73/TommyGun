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
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "KSlider.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(KSlider *)
{
	new KSlider(NULL);
}
//---------------------------------------------------------------------------
__fastcall KSlider::KSlider(TComponent* Owner)
	: TGraphicControl(Owner)
{
	Constraints->MinHeight = 16;
    Constraints->MaxHeight = 16;

    FMin = 0;
    FMax = 100;
    FPosition = 0;
    Width = 100;
    Height = 16;

    FColorShadow = clBtnFace;
    FColorCursorShadow = clBtnFace;
    FColorBack = clBtnFace;
    FColorFore = clBtnText;
    FColorCursor = clBtnText;
}
//---------------------------------------------------------------------------
__fastcall KSlider::~KSlider()
{
}
//---------------------------------------------------------------------------
void __fastcall KSlider::Paint()
{
	if ( Visible )
    {
    	// clear the canvas
    	Canvas->Brush->Color = FColorBack;        
    	Canvas->FillRect( Rect( 0,0,Width,Height ) );

    	if ( Enabled )
        {
        	if ( !FFlat )
            {
	        	Canvas->Pen->Color = FColorShadow;
            	drawBar( 1 );

	        	Canvas->Pen->Color = FColorCursorShadow;
	            drawCursor( 1 );
            }

            Canvas->Pen->Color = FColorFore;
            drawBar( 0 );

            Canvas->Pen->Color = FColorCursor;
            drawCursor( 0 );
        }
	    else
    	{
        	Canvas->Pen->Color = clBtnHighlight;
            drawBar( 1 );

            Canvas->Pen->Color = clBtnHighlight;
            drawCursor( 1 );

            Canvas->Pen->Color = clBtnShadow;
            drawBar( 0 );

            Canvas->Pen->Color = clBtnShadow;
            drawCursor( 0 );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall KSlider::drawBar( int offset )
{
	// Draw the component lines
    int h = 4 + offset;
    Canvas->MoveTo( 6 + offset        , offset );
    Canvas->LineTo( 6 + offset        , h      );
    Canvas->LineTo( Width + offset - 6, h      );
    Canvas->LineTo( Width + offset - 6, offset );
}
//---------------------------------------------------------------------------
void __fastcall KSlider::drawCursor( int offset )
{
	int h = 4 + offset;
    
	// draw the arrow
    float wd = (float)(Width - 12);
    float rg = (float)(FMax - FMin);
    float fx = FPosition - FMin;
    float fs = wd / rg;

    int x = (int)(fx * fs);

    Canvas->MoveTo(   6 + x + offset      , h + 1 );
    Canvas->LineTo( ( 6 + x + offset ) - 5, h + 6 );
    Canvas->LineTo( ( 6 + x + offset ) + 5, h + 6 );
    Canvas->LineTo(   6 + x + offset      , h + 1 );
}
//---------------------------------------------------------------------------
void __fastcall KSlider::Resize( void )
{
	// do not resize during the close down cycle
	if ( ComponentState.Contains( csDestroying ) )
    	return;

    // check for IDE mode
	if ( Visible || ComponentState.Contains( csDesigning ) )
    {
    	// draw the component
        Invalidate();
    }

    if ( OnResize )
    	OnResize( this );
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetColorFore( TColor color )
{
	FColorFore = color;
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetColorBack( TColor color )
{
	FColorBack = color;
    Canvas->Brush->Color = color;
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetColorShadow( TColor color )
{
	FColorShadow = color;
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetColorCursor( TColor color )
{
	FColorCursor = color;
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetColorCursorShadow( TColor color )
{
	FColorCursorShadow = color;
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetPosition( int pos )
{
	if ( pos != FPosition && pos >= FMin && pos <= FMax )
    {
		FPosition = pos;

        if ( FEditBox )
        	FEditBox->Text = IntToStr( FPosition );

		if ( OnChange )
        	OnChange( this );
        
	    Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetMin( int min )
{
	if ( min != FMin && min < FMax )
    {
		FMin = min;

        if ( FPosition < min )
        	Position = min;
        else
			if ( OnChange )
    	    	OnChange( this );

	    Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetMax( int max )
{
	if ( max != FMax && max > FMin )
    {
		FMax = max;

        if ( FPosition > max )
        	Position = max;
        else
			if ( OnChange )
    	    	OnChange( this );

	    Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetEditBox( TCustomEdit* editbox )
{
	if ( editbox != FEditBox )
    {
		FEditBox = editbox;

        if ( editbox )
        	editbox->Text = IntToStr( FPosition );
    }
}
//---------------------------------------------------------------------------
void __fastcall KSlider::SetFlat( bool flat )
{
	if ( flat != FFlat )
    {
		FFlat = flat;
        Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall KSlider::Notification( TComponent* AComponent, TOperation Operation )
{
	if ( Operation == opRemove && AComponent == FEditBox )
    	FEditBox = NULL;
}
//---------------------------------------------------------------------------
void __fastcall KSlider::MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
	if ( Enabled )
    {
		// convert the x position to a position value
    	float mx = X - 6;

	    float ps =  mx / (float)(Width - 12);
    	float rg = (float)(FMax - FMin);

	    Position = (int)(rg * ps ) + FMin;
    }

    if ( TGraphicControl::OnMouseDown )
    	TGraphicControl::OnMouseDown( this, Button, Shift, X, Y );
}
//---------------------------------------------------------------------------
void __fastcall KSlider::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
	if ( Enabled && Shift.Contains( ssLeft ) )
    {
	    float mx = X - 6;

    	float ps = mx / (float)(Width - 12);
	    float rg = (float)(FMax - FMin);

	    Position = (int)(rg * ps ) + FMin;
    }

    if ( TGraphicControl::OnMouseMove )
    	TGraphicControl::OnMouseMove( this, Shift, X, Y );
}
//---------------------------------------------------------------------------
namespace Kslider
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(KSlider)};
		RegisterComponents("Scorpio", classes, 0);
	}
}
//---------------------------------------------------------------------------
 