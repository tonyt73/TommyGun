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
#ifndef BandManagerH
#define BandManagerH
#ifndef DOXYGEN_VC_SKIP
//---------------------------------------------------------------------------
#include <vector>
#include <KRegistry.h>          // ResSuite VCL Component
#include "Dragger.h"
//---------------------------------------------------------------------------
/** @file BandManager.h
 * This class is used to manage draggable Controls.  The Controls are registered
 * with the manager.  Other controls that do not need saving, can be used as well.
 * But for registered Controls, everytime the mouse is released after the Control
 * has been dragged the Controls positions are saved to the registry.  If the
 * Control is not registered then it is not saved.  You can use the BandManager
 * just like a dragger object. With the one exception that you have to register
 * the controls you would like saved to the registry.<BR><BR>  
 * @code
 * How To Use.
 * someunit.h
 *  TZXBandManager  myBandManager;
 *
 * someunit.cpp
 * someunit::OnCreate (...) or someunit::Activate(...)
 *  RegisterBandControls( )
 *
 *
 * someunit::RegisterBandControls( )
 *   myBandManager( panGraph1Title );
 *   myBandManager( panGraph2Title );
 *   myBandManager( panGraph3Title );
 *   myBandManager( panGraph4Title );
 *   myBandManager( panGraph5Title );
 *
 *
 * someunit::OnMouseDown(...)
 *  myBandManager.MouseDown( Sender, X, Y );
 *
 * someunit::OnMouseUp(...)
 *  myBandManager.MouseUp( Sender, X, Y );
 *
 * someunit::OnMouseMove(...)
 *  myBandManager.MouseMove( Sender, X, Y );
 *
 *
 * NOTE: You register the control you want to use that does the dragging.
 *  In the example I use a panel, that sit on top of the Panel that will be
 *  dragged.
 *
 * !!!IT IS ALWAYS THE CONTROL UNDER THE REGISTERED CONTROL THAT GETS DRAGGED!!!
 * @endcode
 */
//---------------------------------------------------------------------------
struct TBandInfo
{
    TControl*   Control;        // control that generates the mouse events
    AnsiString  Name;           // name of the registry entry to use
    int         Position;       // position of control, used to sort

    // used by std::sort to order the bands based on their position
    bool operator<( const TBandInfo& info )
    {
        return this->Position < info.Position;
    }
};

/// a Vector of BandInfo type
typedef std::vector<TBandInfo> BandVector;
//---------------------------------------------------------------------------
__declspec ( dllexport) class ZXBandManager
{
private:

    ZXDragger           BandDragger;                // Dragger to drag the bands around
    KRegistry*          BandRegistry;               // Registry component to save/load the
    BandVector          Bands;                      // vector of controls
    /// find a band index by Control reference
    int     __fastcall  FindBand( TControl* Control );
    /// save the bands to the registry
    void    __fastcall  SaveBands( );

public:
            __fastcall  ZXBandManager( );
            __fastcall ~ZXBandManager( );

    /// register a control for saving to the registry
    void    __fastcall  RegisterControl( TControl* Control, const AnsiString& BandName );
    /// unregister a control
    void    __fastcall  UnRegisterControl( TControl* Control );
    /// manually set the band position
    void    __fastcall  SetBandPosition( TControl* Control, int Position );
    int     __fastcall  GetBandPosition( TControl* Control );
    /// restore the bands from the registry
    void    __fastcall  RestoreBands( );

    ///@name Dragger responses to the MouseXXXX message from the control
    //@{
    void    __fastcall  MouseDown( TObject *Sender, int X, int Y );
    void    __fastcall  MouseUp  ( TObject *Sender, int X, int Y );
    void    __fastcall  MouseMove( TObject *Sender, int X, int Y );
    //@}

    ///@name Dragger pass through fucntions
    //@{
    bool    __fastcall  Dragging( ) { return BandDragger.Dragging( ); }
    void    __fastcall  SetArrowImage  ( TImage* image ) { BandDragger.SetArrowImage  ( image  ); }
    void    __fastcall  SetHeaderOffset( int offset    ) { BandDragger.SetHeaderOffset( offset ); }
    void    __fastcall  SetFooterOffset( int offset    ) { BandDragger.SetFooterOffset( offset ); }
    //@}
};
//---------------------------------------------------------------------------
#endif //DOXYGEN_VC_SKIP
#endif //BandManagerH
