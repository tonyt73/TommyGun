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
#pragma package(smart_init)
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
//---------------------------------------------------------------------------
// HexToColor
/**
 * @brief   Converts a Hex string to a color value
 * @param   Hex the hex string to convert
 * @returns TColor the color value
 * @author  Tony Thompson
 * @date    Created 20 September 2001 by Tony Thompson
 * @remarks Copyright KiwiWare 2004
 */
//---------------------------------------------------------------------------
TColor __fastcall HexToColor(const String& Hex)
{
    long lHex = 0;

    // use upper case chanracters only
    String sHex = Hex.UpperCase();

    // scan the hex string
    for ( int i = 1; i <= sHex.Length(); i++ )
    {
        // move the last conversion across
        lHex <<= 4;

        // get the next hex character from the string to convert to a hex number (nibble)
        char chr = sHex[i];

        // convert it to a nibble value
        chr -= '0';

        if (chr > ('9' - '0'))
        {
            // compensate for the gap between the characters 9 and A
            chr -= (('A' - '9') - 1);
        }

        // place the hex nibble into the hex value
        lHex |= chr;
    }

    // convert the hex value to a TColor value
    TColor color = static_cast<TColor>(lHex);
    return color;
}
#endif//__BORLANDC__
//---------------------------------------------------------------------------

