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
#ifndef DOXYGEN_VC_SKIP
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

// used by std::sort to order 2 BandInfo objects, based on their position
bool operator<( const TBandInfo& info1, const TBandInfo& info2  )
{
    return info1.Position < info2.Position;
}

//---------------------------------------------------------------------------
const int g_iBandNotFound = -1;
String g_sRegistrySection = "ASR";
String g_sRegistryBandKey = "Bands";
//-----------------------------------------------------------------------------------------------------------------------
// Constructor
/**
 * Initializes the class, and creates a new registry control
 * @param           none
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
__fastcall ZXBandManager::ZXBandManager( )
{
    // make a new registry component
    BandRegistry = new KRegistry( NULL );

    // say which product we want to affect
    BandRegistry->Section = "ASR";
}
//-----------------------------------------------------------------------------------------------------------------------
// Destructor
/**
 * Frees resources used by ZXBandManager
 * @param           none
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
__fastcall ZXBandManager::~ZXBandManager( )
{
    // clear the bands vector
    Bands.clear( );

    // delete the registry
    SAFE_DELETE( BandRegistry );
}
//-----------------------------------------------------------------------------------------------------------------------
// RegisterControl
/**
 * Registers a control be to draggable
 * @param           Control the control we can drag
 * @param           BandName the name of the band
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXBandManager::RegisterControl( TControl* Control, const AnsiString& BandName )
{
    int band = FindBand( Control );

    if ( g_iBandNotFound == band )
    {
        // add the new control
        TBandInfo bandInfo;

        bandInfo.Control = Control;
        bandInfo.Name = BandName;
        bandInfo.Position = 0;

        Bands.push_back( bandInfo );
    }
}
//-----------------------------------------------------------------------------------------------------------------------
// UnRegisterControl
/**
 * Removes the control from the draggable bands list
 * @param           Control the control to remove
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXBandManager::UnRegisterControl( TControl* Control )
{
    int band = FindBand( Control );

    if ( g_iBandNotFound != band )
    {
        // remove the band element
        Bands.erase( Bands.begin( ) + band );
    }
}
//-----------------------------------------------------------------------------------------------------------------------
// SetBandPosition
/**
 * Sets the position of the band
 * @param           Control the control who's position we have to set
 * @param           Position the position to set
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXBandManager::SetBandPosition( TControl* Control, int Position )
{
    int band = FindBand( Control );

    if ( g_iBandNotFound != band )
    {
        // change the bands position on the container
        Bands[band].Control->Parent->Top = Position;
    }
}
//-----------------------------------------------------------------------------------------------------------------------
// GeBandPosition
/**
 * Returns the position of a band control
 * @param           Control the control to return the position of
 * @return          int the position of the control
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
int __fastcall ZXBandManager::GetBandPosition( TControl* Control )
{
    int band = FindBand( Control );

    if ( g_iBandNotFound != band )
    {
        // change the bands position on the container
        return Bands[band].Control->Parent->Top;
    }

    return g_iBandNotFound;
}
//-----------------------------------------------------------------------------------------------------------------------
// SaveBands
/**
 * Saves the position of each band into the registry
 * @param           none
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXBandManager::SaveBands( )
{
    for ( unsigned int i = 0; i < Bands.size( ); i++ )
    {
        // write the position of the band to the registry
        BandRegistry->Write( "Bands", Bands[i].Name, Bands[i].Control->Parent->Top );
    }
}
//-----------------------------------------------------------------------------------------------------------------------
// RestoreBands
/**
 * Loads the band positions from the registry and set their positions
 * @param           none
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXBandManager::RestoreBands( )
{
    for ( unsigned int i = 0; i < Bands.size( ); i++ )
    {
        int bandPosition;
        // read the band positions
        if ( BandRegistry->Read( "Bands", Bands[i].Name, bandPosition ) )
        {
            // set the position member so we can sort the bands into order
            // before settings the position on the container
            Bands[i].Position = bandPosition;
        }
    }

    // sort the Bands by Position
    std::sort( Bands.begin( ), Bands.end( ) );

    // loop through the bands making them order correctly
    for ( unsigned int i = 0; i < Bands.size( ); i++ )
    {
        Bands[i].Control->Parent->Top = Bands[i].Position;
    }
}
//-----------------------------------------------------------------------------------------------------------------------
// FindBand
/**
 * Finds a bands index based on its Control pointer
 * @param           Control the band to find
 * @return          index of the band in the band list
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
int __fastcall ZXBandManager::FindBand( TControl* Control )
{
    // default is not found
    int band = g_iBandNotFound;
    // loop through the bands, until one if found or all exhausted
    for ( unsigned int i = 0; i < Bands.size( ) && band == g_iBandNotFound; i++ )
    {
        if ( Bands[i].Control == Control )
        {
            // found the band
            band = i;
        }
    }

    return band;
}
//-----------------------------------------------------------------------------------------------------------------------
// MouseDown
/**
 * Mouse down event handler
 * @param           Sender the control that generated the event
 * @param           X the X position of the mouse within the control
 * @param           Y the Y position of the mouse within the control
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXBandManager::MouseDown( TObject *Sender, int X, int Y )
{
    BandDragger.MouseDown( Sender, X, Y );
}
//-----------------------------------------------------------------------------------------------------------------------
// MouseUp
/**
 * Mouse up event handler
 * @param           Sender the control that generated the event
 * @param           X the X position of the mouse within the control
 * @param           Y the Y position of the mouse within the control
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXBandManager::MouseUp( TObject *Sender, int X, int Y )
{
    BandDragger.MouseUp( Sender, X, Y );
    SaveBands( );
}
//-----------------------------------------------------------------------------------------------------------------------
// MouseMove
/**
 * Mouse move event handler
 * @param           Sender the control that generated the event
 * @param           X the X position of the mouse within the control
 * @param           Y the Y position of the mouse within the control
 * @author          Tony Thompson
 * @date            Last Modified 29 October 2001
 */
//---------------------------------------------------------------------------
void __fastcall ZXBandManager::MouseMove( TObject *Sender, int X, int Y )
{
    BandDragger.MouseMove( Sender, X, Y );
}
//---------------------------------------------------------------------------
#endif //DOXYGEN_VC_SKIP

