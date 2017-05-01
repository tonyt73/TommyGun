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
const String g_SevenuPSignature = "Sev";
//---------------------------------------------------------------------------
__fastcall ZXImporterSevenuP::ZXImporterSevenuP()
: ZXImporterSpectrum()
{
}
//---------------------------------------------------------------------------
/*
 * SevenuP file header structure
 *
 * First comes the 14 bytes header:
 *
 * 00-03: Signature: 'Sev',0
 * 04: Major version. Valid values: 0
 * 05: Minor version. Valid values: 0,6,8
 * 06-07: Property 1: 1 without mask, 2 masked (fixed value of 1 for version 0.0)
 * 08-09: Property 2: Number of frames - 1 (fixed value of 0 for versions 0.0 and 0.6)
 * 10-11: X size, in pixels
 * 12-13: Y size, in pixels
 *
 * Then comes graphic data, stored as Gfx+Attr with the "Byte sort priority":
 * Char line
 * X Char
 * Y Char
 * Mask
 * Frame
 *
 * and interleave at Character (aka "Attribute as 9th byte" in previous versions)
 */
//---------------------------------------------------------------------------
bool __fastcall ZXImporterSevenuP::Load(const String& sFilename)
{
    bool bLoaded = false;
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
            // get length of file
            ifs.seekg (0, ios::end);
            int iLength = ifs.tellg();
            ifs.seekg (0, ios::beg);

            TSevenuPHeader Header;
            // read the header of the .sev file
    		ifs.read((char*)&Header, sizeof(TSevenuPHeader));
            if (!ifs.fail())
            {
                // validate the header
                bool bValid = false;
                String Signature(Header.Signature, 3);

                if (g_SevenuPSignature == Signature && 0 == Header.MajorVersion)
                {
                    if (0 == Header.MinorVersion || 6 == Header.MinorVersion || 8 == Header.MinorVersion)
                    {
                        // validate property 1
                        bValid = (6 <= Header.MinorVersion) ? (1 == Header.Property1 || 2 == Header.Property1) : true;
                        // reset the frame count to zero just to make sure
                        Header.Frames = Header.MinorVersion >= 8 ? Header.Frames : 1;
                        // adjust the width and height to be in characters
                        if (0 != Header.Width  % 8)
                        {
                            Header.Width  += 8 - (Header.Width  % 8);
                        }
                        Header.Width /= 8;
                        if (0 != Header.Height % 8)
                        {
                            Header.Height += 8 - (Header.Height % 8);
                        }
                        Header.Height /= 8;
                    }
                }
                if (true == bValid)
                {
                    iLength -= sizeof(TSevenuPHeader);
                    // read the rest of the file into a buffer
                    unsigned char* cBuffer = new unsigned char[iLength];
            		ifs.read(cBuffer, iLength);
                    if (!ifs.fail())
                    {
                        // transfer the formatted buffer into a sprite
                        int iBufferOffset = 0;
                        // create a sprite in the current project
                        bool bNeedToAddFrame = false;
                        String sName = ChangeFileExt(ExtractFileName(sFilename), "");
                        // now add the frames to the sprite
                        for (int f = 0; f <= Header.Frames; f++)
                        {
                            ZXImage* pImage = NULL;
                            if (-1 != AddImage("Sprite", sName, Header.Width * 8, Header.Height * 8, 2 == Header.Property1, &pImage))
                            {
                                // get the new sprite pointer
                                bLoaded = true;
                                // read in the character block
                                for (int h = 0; h < Header.Height; h++)
                                {
                                    for (int w = 0; w < Header.Width; w++)
                                    {
                                        // set in the character block pixels
                                        for (int l = 0; l < 8; l++)
                                        {
                                            pImage->Pixels[(Header.Width * (h * 8 + l)) + w] = cBuffer[iBufferOffset];
                                            iBufferOffset++;
                                        }
                                        // set in the character block attribute
                                        pImage->Attributes[Header.Width * h + w] = cBuffer[iBufferOffset];
                                        iBufferOffset++;
                                    }
                                }
                                //FlipBits(pImage->Pixels , (Header.Height * 8) * Header.Width);
                                // read in the mask if its present
                                if (2 == Header.Property1)
                                {
                                    // Read in the mask
                                    for (int h = 0; h < Header.Height; h++)
                                    {
                                        for (int w = 0; w < Header.Width; w++)
                                        {
                                            // set in the character block pixels
                                            for (int l = 0; l < 8; l++)
                                            {
                                                pImage->Masks[(Header.Width * (h * 8 + l)) + w] = cBuffer[iBufferOffset];
                                                iBufferOffset++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        // failed to read the file contents
                        throw(String("Failed to read the entire SevenuP body contents"));
                    }
                    SAFE_ARRAY_DELETE(cBuffer);
                }
                else
                {
                    throw(String("File is not a valid SevenuP file or is an unsupported version"));
                }
            }
            else
            {
                // failed to read all the header
                throw(String("Failed to read the entire SevenuP header"));
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
        // file not found
        m_sError = "Failed to locate file specified.\n\tPlease supply a correct the file name and file path.";
    }

    return bLoaded;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImporterSevenuP::Import(TStrings* sFiles)
{
    bool bResult = false;
    for (int i = 0; i < sFiles->Count; i++)
    {
        bResult |= Load(sFiles->Strings[i]);
    }
    return bResult;
}
//---------------------------------------------------------------------------

