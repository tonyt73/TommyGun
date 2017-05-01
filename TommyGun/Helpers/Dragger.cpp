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
//---------------------------------------------------------------------------
// DragImage constants (DI)
const int cDIWidth     = 16;    // width of the icons
const int cDIHeight    = 32;    // height of the icons
const int cDIYOffset   = 15;    // y offset to start drawing icons from bottom of the control
const int cDIXOffset   = 15;    // x offset to start drawing icon from the left edge of the control
const int cDILineSize  =  3;    // the size of the drag rectangle
const int cArrowWidth  = 40;
const int cArrowHeight = 32;
//-----------------------------------------------------------------------------------------------------------------------
// Constructor
/**
 * Initializes the class, and creates the background arrow bitmap
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
__fastcall ZXDragger::ZXDragger( )
: imgArrows( NULL ),
  bDragInProgress( false ),
  HeaderOffset( 0 ),
  FooterOffset( 0 ),
  DesktopDC( NULL )
{
    // create the background saving bitmap
    ArrowBackground = new Graphics::TBitmap;
    ArrowBackground->Width  = cArrowWidth ;
    ArrowBackground->Height = cArrowHeight;
}
//-----------------------------------------------------------------------------------------------------------------------
// Destructor
/**
 * frees resources used by ZXDragger
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
__fastcall ZXDragger::~ZXDragger( )
{
    imgArrows = NULL;
    SAFE_DELETE( ArrowBackground );
}
//-----------------------------------------------------------------------------------------------------------------------
// SetArrowImage
/**
 * Sets the image that contains the arrow bitmaps to draw
 * @param           image the TImage control that contains the arrows
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXDragger::SetArrowImage( TImage* image )
{
    imgArrows = image;
}
//-----------------------------------------------------------------------------------------------------------------------
// SetHeaderOffset
/**
 * Sets the header offset used when dropping a control with respect to its parent
 * @param           offset the offset to incur when drawing
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXDragger::SetHeaderOffset( int offset )
{
    HeaderOffset = offset;
}
//-----------------------------------------------------------------------------------------------------------------------
// SetFooterOffset
/**
 * Same as SetHeaderOffset except for the bottom
 * @param           offset the offset from the bottom of the parent
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXDragger::SetFooterOffset( int offset )
{
    FooterOffset = offset;
}
//-----------------------------------------------------------------------------------------------------------------------
// MoveDown
/**
 * The mouse down event processor
 * @param           Sender the control that generated the mouse down event
// \parma           X the X position of the mouse within the control
 * @param           Y the Y position of the mouse within the control
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXDragger::MouseDown( TObject *Sender, int X, int Y)
{
    if (false == bDragInProgress)
    {
        // get the control who initiated the drag
        TControl* control = dynamic_cast<TControl*>(Sender);

        if (true == SAFE_PTR(control))
        {
            SetCaptureControl(control);
            // valid control, so dragging in progress
            bDragInProgress = true;

            // stop hints from activating
            Application->ShowHint = false;

            // get the desktop DC
            //DesktopDC = GetDCEx( GetDesktopWindow( ), 0, DCX_CACHE | DCX_LOCKWINDOWUPDATE);
            DesktopDC = GetDC(NULL);

            if (NULL != DesktopDC)
            {
                // save the old brush to be restored on mouse up
                OldBrush = SelectObject( DesktopDC, GetStockObject( BLACK_BRUSH ) );

                // find the client rect of the great grandparent (Container View Panel)
                ClipRgn = NULL;

                // find the control, that has alTop set,
                // and set clipPanel to the grandparent control.
                TControl* clipPanel = control;

                while ( clipPanel && clipPanel->Align != alTop )
                {
                    clipPanel = clipPanel->Parent;
                }

                if (true == SAFE_PTR(clipPanel)/* && clipPanel->Align == alTop*/)
                {
                    while (clipPanel && clipPanel->Align != alClient)
                    {
                        clipPanel = clipPanel->Parent;
                    }
                    if (true == SAFE_PTR(clipPanel))
                    {
                        // we have a great grandparent, so calculate a cliprect based on its clientrect
                        TPoint tl = clipPanel->ClientToScreen( TPoint( clipPanel->ClientRect.left , clipPanel->ClientRect.top    ) );
                        TPoint br = clipPanel->ClientToScreen( TPoint( clipPanel->ClientRect.right, clipPanel->ClientRect.bottom ) );
                        // create a region based on the client rect in screen coords
                        ClipRgn = CreateRectRgn( tl.x, tl.y, br.x, br.y);

                        if ( NULL != ClipRgn )
                        {
                            // select the clip region, into the Desktop DC
                            SelectClipRgn( DesktopDC, ClipRgn );
                        }
                    }
                }

                // no arrows drawn, so don't erase
                bEraseArrows = false;

                // calculate the cursor offset into the dragging object
                DragOffset = TPoint( control->Left + X, control->Top + Y );

                // draw the highlight rect
                TPoint origin( 0,0 );
                TPoint controlPoint = control->Parent->ClientToScreen( origin );

                DrawDragImage( control->Parent, controlPoint );

                // draw the selection rect
                DrawDragRect( control, TPoint( X, Y - DragOffset.y ), DRAG_OP_DRAW );
            }
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------
// MouseUp
/**
 * The mouse up event processor
 * @param           Sender the control that generated the event
 * @param           X the X position of the mouse within the control
 * @param           Y the Y position of the mouse within the control
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXDragger::MouseUp( TObject *Sender, int X, int Y)
{
    if ( bDragInProgress )
    {
        // stop the dragging, and give the hints back
        bDragInProgress = false;
        Application->ShowHint = true;
        SetCaptureControl(NULL);

        // is the sender a valid win control
        TControl* control = dynamic_cast<TControl*>(Sender);

        if (true == SAFE_PTR(control))
        {
            // save the drop position for use later, as DrawDragRect will reset to an invalid value
            TPoint OldDropPosition = DropPosition;
            // erase the drag rect
            DrawDragRect( control, TPoint( 0,0 ), DRAG_OP_ERASE );

            // erase the object highlight rect
            while ( control && control->Align != alTop )
            {
                control = control->Parent;
            }

            TPoint origin( 0,0 );
            TPoint controlPoint = control->ClientToScreen( origin );
            DrawDragImage( control, controlPoint );

            // delete the desktop clip region
            if (NULL != ClipRgn)
            {
                DeleteObject( ClipRgn );
            }

            // replace the old desktop brush
            SelectObject( DesktopDC, OldBrush );

            // release the desktop DC, and reset the DC value
            ReleaseDC( GetDesktopWindow( ), DesktopDC );

            DesktopDC = NULL;
            // change the position of the control to the drop position
            OldDropPosition.y -= cDIYOffset;
            control->Top = control->Parent->ScreenToClient( OldDropPosition ).y;
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------
// MouseMove
/**
 * The mouse move event processor
 * @param           Sender the control that generated the event
 * @param           X the X position of the mouse within the control
 * @param           Y the Y position of the mouse within the control
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXDragger::MouseMove(TObject *Sender, int X, int Y)
{
    if (true == bDragInProgress)
    {
        // valid dragging in progress
        TControl* control = dynamic_cast<TControl*>(Sender);

        if (true == SAFE_PTR(control))
        {
            // valid drag object
            DrawDragRect( control, TPoint( X, Y - DragOffset.y ), DRAG_OP_MOVE );
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------
// DrawDragRect
/**
 * Draws the rectangle used when dragging
 * @param           Control the control that we are dragging
 * @param           Pt the point at which we are dragging from
 * @param           DrawOp the drawing operation we are performing
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXDragger::DrawDragRect( TControl* Control, TPoint& Pt, int DrawOp )
{
    static TPoint screenPt;
    static TPoint lastScreenPt;
    static TPoint lastDropPosition;

    if (NULL != DesktopDC)
    {
        // constrain the cursor position to parents X position and Width, and
        // make it in screen coords
        screenPt = ConstrainDragPoint( Control->Parent, Pt );

        if (DRAG_OP_ERASE == (DrawOp & DRAG_OP_ERASE))
        {
            // erase the last drag rect
            DrawDragImage( Control->Parent, lastScreenPt );
        }

        // find the control that the cursor is over
        TControl* control = Control;

        while ( control && control->Align != alTop )
        {
            control = control->Parent;
        }

        control = FindBetweenControl( control->Parent, screenPt );

        // reset the drop point the last drop position
        DropPosition = lastDropPosition;

        if (true == SAFE_PTR(control))
        {
            // found a valid control so we can draw the arrows and
            // calculate a position to drop the object
            DropPosition = control->ClientToScreen( TPoint( 0, control->Height ) );
        }
        else
        {
            // no valid control, so drop at the top of the grandparent
            DropPosition = Control->Parent->Parent->ClientToScreen( TPoint( 1, 1 + HeaderOffset ) );
        }

        if (true == bEraseArrows)
        {
            // erase the arrows
            BitBlt( DesktopDC, lastDropPosition.x + cDILineSize, lastDropPosition.y - cDIYOffset, cDIWidth, cDIHeight, ArrowBackground->Canvas->Handle, 0, 0, SRCCOPY );
            BitBlt( DesktopDC, lastDropPosition.x + Control->Parent->Width - cDIXOffset - cDILineSize, lastDropPosition.y - cDIYOffset, cDIWidth, cDIHeight, ArrowBackground->Canvas->Handle, cDIWidth, 0, SRCCOPY );
            // arrows erased
            bEraseArrows = false;
        }

        if ((DRAG_OP_DRAW == (DrawOp & DRAG_OP_DRAW)) && true == SAFE_PTR(imgArrows))
        {
            // copy the arrow background
            BitBlt( ArrowBackground->Canvas->Handle, 0, 0, cDIWidth, cDIHeight, DesktopDC, DropPosition.x + cDILineSize, DropPosition.y - cDIYOffset, SRCCOPY );
            BitBlt( ArrowBackground->Canvas->Handle, cDIWidth, 0, cDIWidth, cDIHeight, DesktopDC, DropPosition.x + Control->Parent->Width - cDIXOffset - cDILineSize, DropPosition.y - cDIYOffset, SRCCOPY );
            // draw the arrow icons
            BitBlt( DesktopDC, DropPosition.x + cDILineSize, DropPosition.y - cDIYOffset, cDIWidth, cDIHeight, imgArrows->Canvas->Handle, 0, 0, SRCCOPY );
            BitBlt( DesktopDC, DropPosition.x + Control->Parent->Width - cDIXOffset - cDILineSize, DropPosition.y - cDIYOffset, cDIWidth, cDIHeight, imgArrows->Canvas->Handle, 0, 0, SRCCOPY );
            // arrows should be erased
            bEraseArrows = true;
            // save the position we drew the arrow at
            lastDropPosition = DropPosition;
        }

        if (DRAG_OP_DRAW == (DrawOp & DRAG_OP_DRAW))
        {
            // draw the new drag rect
            DrawDragImage( Control->Parent, screenPt );
            // save where we drew the rectangle
            lastScreenPt = screenPt;
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------
// DrawDragImage
/**
 * Pattern Blits the dragging rectangle to the screen
 * @param           Control the control we are dragging
 * @param           Pt the point at which to draw the rectangle
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXDragger::DrawDragImage( TControl* Control, TPoint& Pt )
{
    // setup the rect parameters
    int Top    = Pt.y;
    int Bottom = Top + Control->Height;
    int Left   = Control->ClientToScreen( TPoint( 0, 0 ) ).x;
    int Right  = Left + Control->Width;

    // draw a dragging rect the size of the dragged object
    PatBlt(DesktopDC, Left + cDILineSize, Top, Right - Left - cDILineSize, cDILineSize, DSTINVERT);
    PatBlt(DesktopDC, Right - cDILineSize, Top + cDILineSize, cDILineSize, Bottom - Top - cDILineSize, DSTINVERT);
    PatBlt(DesktopDC, Left, Bottom - cDILineSize, Right - Left - cDILineSize, cDILineSize, DSTINVERT);
    PatBlt(DesktopDC, Left, Top, cDILineSize, Bottom - Top - cDILineSize, DSTINVERT);
}
//-----------------------------------------------------------------------------------------------------------------------
// ContainDragPoint
/**
 * Constrains the point to be within the limits on the parent control
 * @param           Control to constrain
 * @param           Pt reference point to constrain by
 * @return          TPoint the constrained point
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
TPoint __fastcall ZXDragger::ConstrainDragPoint( TControl* Control, TPoint& Pt )
{
    // convert the pt to screen coords
    TPoint screenPt = Control->ClientToScreen( Pt );
    // get the top and bottom screen coords on the control
    long toplimit    = Control->Parent->ClientToScreen( TPoint( 0, 0 ) ).y;
    long bottomlimit = Control->Parent->ClientToScreen( TPoint( 0, Control->Parent->Height - Control->Height ) ).y;

    // confine the y coords to be within the limits
    screenPt.y = std::max( screenPt.y, toplimit );
    screenPt.y = std::min( screenPt.y, bottomlimit );

    // return the converted screen point
    return screenPt;
}
//-----------------------------------------------------------------------------------------------------------------------
// FindBetweenControl
/**
 * Finds a control that the point is between
 * @param           Control the control we are dragging
 * @param           The point to test against
 * @return          TControl the control that we are between
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
TControl* __fastcall ZXDragger::FindBetweenControl( TControl* Control, TPoint& Pt )
{
    // get a pointer to a TWinControl object
    TWinControl* winControl = dynamic_cast<TWinControl*>(Control);
    TControl* control = NULL;

    if (true == SAFE_PTR(winControl))
    {
        // the Control is a TWinControl object
        for ( int i = 0; i < winControl->ControlCount && NULL == control; i++ )
        {
            // get the current controls screen coords
            TPoint tPt = winControl->Controls[i]->ClientToScreen( TPoint( 0, 0 ) );
            TPoint bPt = winControl->Controls[i]->ClientToScreen( TPoint( 0, winControl->Controls[i]->Height ) );

            // check to see if the pt falls within the controls limits
            if (tPt.y < Pt.y && Pt.y <= bPt.y)
            {
                control = winControl->Controls[i];
            }
        }
    }

    // return the control pointer
    return control;
}
//---------------------------------------------------------------------------
