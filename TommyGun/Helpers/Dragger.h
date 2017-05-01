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
#ifndef DraggerH
#define DraggerH
//---------------------------------------------------------------------------
/**
 *  Dragger class
 * @code
 * This class is used to move VCL TControl decendant objects around
 * It is designed to handle a certain type of VCL object structure.
 *
 * How Its Structured.
 *   +---------------------------------+
 *   |                                 |
 *   |<=Draggable Panel Container=====>|
 *   |                                 |
 *  +-----------------------------------+
 *  ||+-------------------------------+||
 *  |||+-----------------------------+|||
 *  |||| Caption Panel (alNone)      ||||
 *  |||+-----------------------------+|||
 *  |||                               |||
 *  |||<==Draggable panel============>|||
 *  |||   alTop                       |||
 *  |||                               |||
 *  |||                               |||
 *  ||+-------------------------------+||
 *  ||                                 ||
 *  ||                                 ||
 *  ||                                 ||
 *  |<=Container View Panel============>|
 *  ||                                 ||
 *  || This panel/form or scrollbox    ||
 *  || is used to set the ClipRegion   ||
 *  || of the Desktop, when drawing    ||
 *  || the DragRect and Icons          ||
 *  ||                                 ||
 *  || Contains the Draggable Panel    ||
 *  || Container.                      ||
 *  ||                                 ||
 *  +-----------------------------------+
 *   |                                 |
 *   |<==Draggable Panel Container====>|
 *   |                                 |
 *   |   Contains Draggable Panels     |
 *   |                                 |
 *   +---------------------------------+
 * Diagram 1.
 *
 * The diagram shows 4 TControls, from here on assumed to be TPanels (panels).
 * The lower most panel(grandparent) is the Container View Panel. It holds ALL the other panels.
 * It only really holds 1 other panel called the Draggable Panel Container. But its
 * main job is to provide the viewing rectangle from which to see the panels from within.
 * The panel it holds, the Draggable Panel Container, it not aligned to anything. This is
 * so the panel can be moved up/down if you so wish to do so. Its main task is to hold the group
 * of Draggable panels. The Draggable panels hold what you would like dragged around.
 * This panel, although is the one moved is not the panel that is used to respond to messages.
 * That job is given to the Caption Panel, because this is the control we want to use
 * to move the Draggable Panel with. Much like a Window and its caption bar. The Caption
 * Panel could be any TControl object, even a label, anything really.
 *
 * Limitations.
 * 1. The panels(Draggable Panels) can only be moved up or down with in the Draggable Panel Container.
 * 2. You cannot undock the panels.
 * 3. You must supply a pointer to a TImage object that containers the arrow pointers to use.
 * 4. The Draggable Panels MUST BE align alTop.
 *
 * How to Use.
 *
 * 1. Declare a object in your header file
 *
 *  someunit.h
 *       TZXDragger myDragger;
 *
 * 2. Set the arrow image in the forms on create or
 *
 * someunit::OnCreate( )
 *      myDragger.SetArrowImage( imgMyArrows );
 *
 * 3. Call the mouse methods from your panels mouse event
 *
 * someunit::MouseDown( Sender, Button, X, Y )
 *  if ( Button == mbLeft )
 *      myDragger.MouseDown( Sender, X, Y )
 *
 * someunit::MouseUp( Sender, Button, X, Y )
 *  if ( Button == mbLeft )
 *      myDragger.MouseUp( Sender, X, Y )
 *
 * someunit::MouseMove( Sender, Shift, X, Y )
 *  if ( Shift.Contains( ssLeft ) )
 *      myDragger.MouseMove( Sender, X, Y )
 *
 * @endcode
 */
//---------------------------------------------------------------------------
// Drag Image Operations
#define DRAG_OP_DRAW            0x0001
#define DRAG_OP_ERASE           0x0002
#define DRAG_OP_MOVE            0x0003
//---------------------------------------------------------------------------
__declspec ( dllexport) class ZXDragger
{
private:
    // drag members
    HDC                 DesktopDC;          // Device context for the Desktop
    HRGN                ClipRgn;            // Clip Region for the desktop
    HGDIOBJ             OldBrush;           // Old brush of the Desktop
    HRESULT             hResult;            // hResult used to store all the WINAPI return codes

    Graphics::TBitmap*  ArrowBackground;    // copy of what the arrows have overdrawn

    TPoint              DragOffset;         // offset into the panel of the cursor at the start of the drag
    TPoint              DropPosition;       // the position the arrows are position, and the panel will be dropped

    bool                bEraseArrows;       // flag: erase the arrows
    bool                bDragInProgress;    // flag: drag is in progress

    int                 HeaderOffset;       // offset from the top of the Draggable Container panel of constrain the cursor too.
    int                 FooterOffset;       // same as above but for the bottom

    TImage*             imgArrows;          // a pointer to a TImage control that has our arrow images

    // drag methods
    // handles the drawing of Drag Rectangle and Arrow Icons.
    void        __fastcall DrawDragRect( TControl* Control, TPoint& Pt, int DrawOp );
    // draws the drag rectangle
    void        __fastcall DrawDragImage( TControl* Control, TPoint& Pt );
    // constrains the cursor position to be with in the Draggable Panel Container
    TPoint      __fastcall ConstrainDragPoint( TControl* Control, TPoint& Pt );
    // finds the control the cursor will place the object about to be dropped, between(after)
    TControl*   __fastcall FindBetweenControl( TControl* Control, TPoint& Pt );

public:
                __fastcall  ZXDragger( );
                __fastcall ~ZXDragger( );

    ///@name Mouse Event Handlers
    //@{
    void        __fastcall MouseDown( TObject *Sender, int X, int Y );
    void        __fastcall MouseUp  ( TObject *Sender, int X, int Y );
    void        __fastcall MouseMove( TObject *Sender, int X, int Y );
    //@}

    // query: returns the state of the DragInProgress flag
    bool        __fastcall Dragging( void ) { return bDragInProgress; };

    ///@name Set functions
    //@{
    // sets the image to use for the arrows
    void        __fastcall SetArrowImage( TImage* image );
    // sets the header offset
    void        __fastcall SetHeaderOffset( int offset );
    // sets the footer offset
    void        __fastcall SetFooterOffset( int offset );
    //@}
};
//---------------------------------------------------------------------------
#endif
