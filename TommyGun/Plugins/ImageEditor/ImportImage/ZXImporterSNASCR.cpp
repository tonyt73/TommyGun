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
const   int g_iSCRFileSize       =  6912;
const   int g_iSNAFileSize       = 49179;
const   int g_iSNAHeaderSize     =    27;
const   int g_iCharactersPerRow  =    32;
const   int g_iLinesPerSection   =    64;
const   int g_i1stSectionOffset  =     0;
const   int g_i2ndSectionOffset  =  2048;
const   int g_i3rdSectionOffset  =  4096;
const   int g_iAttributesOffset  =  6144;
const   int g_iAttributesLength  =   768;
//---------------------------------------------------------------------------
const   int g_iScreenOffsets[64] =
{
   0,   // Row 0
 256,
 512,
 768,
1024,
1280,
1536,
1792,

  32,   // Row 1
 288,
 544,
 800,
1056,
1312,
1568,
1824,

  64,   // Row 2
 320,
 576,
 832,
1088,
1344,
1600,
1856,

  96,   // Row 3
 352,
 608,
 864,
1120,
1376,
1632,
1888,

 128,   // Row 4
 384,
 640,
 896,
1152,
1408,
1664,
1920,

 160,   // Row 5
 416,
 672,
 928,
1184,
1440,
1696,
1952,

 192,   // Row 6
 448,
 704,
 960,
1216,
1472,
1728,
1984,

 224,   // Row 7
 480,
 736,
 992,
1248,
1504,
1760,
2016
};
//---------------------------------------------------------------------------
__fastcall ZXImporterZXScreen::ZXImporterZXScreen(int iFileHeaderOffset, int iFileSize)
: ZXImporterSpectrum()
, m_iFileHeaderOffset(iFileHeaderOffset)
, m_iFileSize(iFileSize)
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXImporterZXScreen::Import(TStrings* sFiles)
{
    bool bLoaded = false;
    for (int i = 0; i < sFiles->Count; i++)
    {
        String sFilename = sFiles->Strings[i];
        if (true == FileExists(sFilename))
        {
            try
            {
                ifstream ifs;
                ifs.open(sFilename.c_str(),ios::binary );
                if (!ifs.is_open())
                {
                    throw(String("Unable to open file: " + sFilename));
                }
                String sName = ChangeFileExt(ExtractFileName(sFiles->Strings[i]), "");
                // get length of file
                ifs.seekg(0, ios::end);
                int iLength = ifs.tellg();
                ifs.seekg(0, ios::beg);

                if (m_iFileSize == iLength)
                {
                    ZXImage* pImage = NULL;
                    if (-1 != AddImage("Screen", sName, 256, 192, false, &pImage))
                    {
                        bLoaded = true;
                        // read the scr file and place the data into the image
                        unsigned char* Pixels = pImage->Pixels;
                        // read the pixel data for the 1st section
                        for (int i = 0; i < g_iLinesPerSection; i++)
                        {
                            // move to the next line in the file pixel buffer
                            ifs.seekg(m_iFileHeaderOffset + g_i1stSectionOffset + g_iScreenOffsets[i], ios::beg);
                            // read a line of pixels
                            ifs.read(Pixels, g_iCharactersPerRow);
                            //FlipBits(Pixels, g_iCharactersPerRow);
                            // move to next line in our pixel buffer
                            Pixels += g_iCharactersPerRow;
                        }
                        // read the pixel data for the 2nd section
                        for (int i = 0; i < g_iLinesPerSection; i++)
                        {
                            // move to the next line in the file pixel buffer
                            ifs.seekg(m_iFileHeaderOffset + g_i2ndSectionOffset + g_iScreenOffsets[i], ios::beg);
                            // read a line of pixels
                            ifs.read(Pixels, g_iCharactersPerRow);
                            //FlipBits(Pixels, g_iCharactersPerRow);
                            // move to next line in our pixel buffer
                            Pixels += g_iCharactersPerRow;
                        }
                        // read the pixel data for the 3rd section
                        for (int i = 0; i < g_iLinesPerSection; i++)
                        {
                            // move to the next line in the file pixel buffer
                            ifs.seekg(m_iFileHeaderOffset + g_i3rdSectionOffset + g_iScreenOffsets[i], ios::beg);
                            // read a line of pixels
                            ifs.read(Pixels, g_iCharactersPerRow);
                            //FlipBits(Pixels, g_iCharactersPerRow);
                            // move to next line in our pixel buffer
                            Pixels += g_iCharactersPerRow;
                        }
                        ifs.seekg(m_iFileHeaderOffset + g_iAttributesOffset, ios::beg);
                        ifs.read(pImage->Attributes, g_iAttributesLength);
                    }
                    else
                    {
                        throw(String("Failed to create a screen image in the current project"));
                    }
                }
                // close the import file
                ifs.close();
            }
            catch (const String& str)
            {
                m_sError = str;
            }
            catch (...)
            {
                m_sError = "An unexpected exception occurred!";
            }
        }
        else
        {
            m_sError = "Failed to locate file specified.\n\tPlease supply a correct the file name and file path.";
        }
    }
    return bLoaded;
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
__fastcall ZXImporterSNA::ZXImporterSNA()
: ZXImporterZXScreen(g_iSNAHeaderSize, g_iSNAFileSize)
{
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
__fastcall ZXImporterSCR::ZXImporterSCR()
: ZXImporterZXScreen(0, g_iSCRFileSize)
{
}
//---------------------------------------------------------------------------

