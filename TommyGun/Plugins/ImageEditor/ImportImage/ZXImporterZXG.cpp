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
__fastcall ZXImporterZXG::ZXImporterZXG()
: ZXImporterSpectrum()
{
}
//---------------------------------------------------------------------------
__fastcall ZXImporterZXG::~ZXImporterZXG()
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXImporterZXG::Import(TStrings* sFiles)
{
    bool bLoaded = false;
    TfrmImportZXG* frmImportZXG = new TfrmImportZXG(NULL);
    if (true == SAFE_PTR(frmImportZXG) && frmImportZXG->Execute())
    {
        bool bAsTile = frmImportZXG->radImportAsTile->Checked;
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
                    // read the width and height of the .zxg image
                    unsigned char iWidth;
                    unsigned char iHeight;
                    
                    ifs.read((char*)&iWidth , sizeof(unsigned char));
                    ifs.read((char*)&iHeight, sizeof(unsigned char));
                    // is the image is big enough
                    if (0 != iWidth * iHeight)
                    {
                        // yep, so create the image
                        ZXImage* pImage = NULL;
                        // convert the bitmap to the graphic format required
                        String sType = bAsTile ? "Tile" : "Sprite";
                        String sFile = ChangeFileExt(ExtractFileName(sFilename), "");
                        if (-1 != AddImage(sType, sFile, iWidth * 8, iHeight * 8, false, &pImage))
                        {
                            // and then load the file into the image
                            ifs.read(pImage->Pixels    , (iHeight * 8) * iWidth);
                            ifs.read(pImage->Attributes,  iHeight      * iWidth);
                            // flips the spectrum bits over
                            //FlipBits(pImage->Pixels, (iHeight * 8) * iWidth);
                            bLoaded = true;
                        }
                        else
                        {
                            throw(String("Failed to create a image in the current project"));
                        }
                    }
                    else
                    {
                        throw(String("Failed to read the file format correctly. File maybe corrupt. File: " + sFilename));
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
        SAFE_DELETE(frmImportZXG);
    }
    else
    {
        m_sError = "Failed to create import dialog or Import operation cancelled";
    }
    return bLoaded;
}
//---------------------------------------------------------------------------

