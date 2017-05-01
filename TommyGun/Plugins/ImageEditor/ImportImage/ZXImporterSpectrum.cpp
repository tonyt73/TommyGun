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
#pragma hdrstop
#include "ZXImporterSpectrum.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXImporterSpectrum::ZXImporterSpectrum()
: ZXImporter()
{
}
//---------------------------------------------------------------------------
__fastcall ZXImporterSpectrum::~ZXImporterSpectrum()
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXImporterSpectrum::ChoosePalette(TStrings* sFiles, TStrings* pPalettes)
{
    bool bResult = false;
    for (int i = 0; i < pPalettes->Count && false == bResult; i++)
    {
        bResult = pPalettes->Strings[i] == "ZX Spectrum";
    }
    m_sPaletteSignature = "ZX Spectrum";
    return bResult;
}
//---------------------------------------------------------------------------
/*void __fastcall ZXImporterSpectrum::FlipBits(unsigned char* Pixels, unsigned int iSize)
{
    // changes the bits in a .scr character array from Little Endian to Big Endian
    // ie. 76543210 -> 01234567
    unsigned char beByte;   // Big    Endian Byte (Intel???)
    unsigned char leByte;   // Little Endian Byte (Z80???) or is it the other way around???
    // loop through the bytes to convert
    for (unsigned int i = 0; i < iSize; i++)
    {
        // get the original little endian byte
        leByte = Pixels[i];
        // reset the big endian byte
        beByte = 0;
        // is the little endian a zero?
        if (0 != leByte)
        {
            // no, so we need to convert the byte to big endian
            // loop through the 8 bits of the byte
            for (unsigned int bit = 0; bit < 8; bit++)
            {
                // move the big endian byte to the left 1 bit
                beByte  =  beByte << 1;
                // or into the big endian byte the first bit of the little endian byte
                beByte |=  leByte & 0x01;
                // and move the rest of the little endian bits down 1 bit
                leByte  =  leByte >> 1;
            }
        }
        // store the resulting big endian bytes in place of the little endian
        Pixels[i] = beByte;
    }
}*/
//---------------------------------------------------------------------------

