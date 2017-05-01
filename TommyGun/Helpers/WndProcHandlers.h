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
#ifndef WndProcHandlersH
#define WndProcHandlersH
#ifndef DOXYGEN_VC_SKIP
//---------------------------------------------------------------------------
/*
    TAG Usage:

    Toolbar Tags
    These tags hold 2 things in the DWORD Tag field.

    1.  An 8 bit Docking Station ID.        0x000F
        The ControlBar bars on the frame have a unique TAG value.
        The Toolbars have a matching TAG ID.
        When docking occurs, the tag of a toolbar is checked against the docking station
        or ControlBar. If the 2 match then the toolbar may dock at that control.
        If not then the toolbar, is not valid for the dock station.
    2.  An 8 bit Window State parameter.    0x00F0
        The window state is used when the user clicks the X to close the toolbar.
        Because the frame's Hide the floating toolbars, when the main applications
        tabs are changed. We need to differentiate between the user hiding the toolbar
        ( X Close), and the application hiding the toolbar.  So this information is
        held in the 2 byte of the Tag field.  This means that a user closed toolbar
        will not reappear if you switch to another tab, and then switch back again to
        the orginal tab, where the app will show any toolbars, that are floating, hidden,
        and not closed by the user. whew!

    Popup Toolbar Menu Tags
    These hold a reference to an associated toolbar. A check means the toolbar is
    visible.
    The reference is used to turn the visibility of the toolbar on/off, and to updated
    the menus check mark before the menu items are shown.

*/
//---------------------------------------------------------------------------
#define TAG_MASK_DOCKSTATION_ID 0x000F
#define TAG_MASK_WINDOWSTATE    0x00F0
#define WINDOW_NOT_CLOSED       0x0000
#define WINDOW_CLOSED_ON_HIDE   0x0010
#define WINDOW_CLOSED_BY_USER   0x0020
//---------------------------------------------------------------------------
/** @class TRWBaseWindowProcHandler
 *  @brief Base class to handle Window Proc message redirection
 */
__declspec ( dllexport) class TRWBaseWindowProcHandler
{
protected:
    TWndMethod      m_OldWindowProc;
    TWinControl*    m_WinControl;

    virtual void __fastcall NewWindowProc(Messages::TMessage &Message) = 0;

public:
            __fastcall  TRWBaseWindowProcHandler( TWinControl* WinControl );
    virtual __fastcall ~TRWBaseWindowProcHandler( );
};


/** @class TRWToolbarHandler
 *  @brief Handles the showing and hiding of toolbars
 */
__declspec ( dllexport) class TRWToolbarHandler : public TRWBaseWindowProcHandler
{
private:
    void    __fastcall NewWindowProc( Messages::TMessage &Message );

public:
            __fastcall  TRWToolbarHandler( TWinControl* WinControl );
    virtual __fastcall ~TRWToolbarHandler( );

    void    __fastcall  ShowFloating( );
    void    __fastcall  HideFloating( );
};


/** @class TRWToolbarHandler
 *  @brief Removes flicker from the Coolbar, by igoring the erase background message
 */
__declspec ( dllexport) class TRWControlBarHandler : public TRWBaseWindowProcHandler
{
private:

    void    __fastcall NewWindowProc( Messages::TMessage &Message );

public:
            __fastcall  TRWControlBarHandler( TWinControl* WinControl );
    virtual __fastcall ~TRWControlBarHandler( );
};
//---------------------------------------------------------------------------
#endif //DOXYGEN_VC_SKIP
#endif //WndProxHandlersH
