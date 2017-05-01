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
static TfrmImportBitmap* frmImportBitmap = NULL;
//---------------------------------------------------------------------------
__fastcall ZXImporterBitmap::ZXImporterBitmap()
: ZXImporter()
{
}
//---------------------------------------------------------------------------
__fastcall ZXImporterBitmap::~ZXImporterBitmap()
{
    SAFE_DELETE(frmImportBitmap);
}
//---------------------------------------------------------------------------
bool __fastcall ZXImporterBitmap::ChoosePalette(TStrings* sFiles, TStrings* pPalettes)
{
    bool bResult = false;
    // create the importing object and get it to do its work
    if (NULL == frmImportBitmap)
    {
        frmImportBitmap = new TfrmImportBitmap(NULL);
    }
    if (true == SAFE_PTR(frmImportBitmap))
    {
        // load the palette combo with the palette names
        frmImportBitmap->cmbImageFormat->Items->Clear();
        for (int i = 0; i < pPalettes->Count; i++)
        {
            frmImportBitmap->cmbImageFormat->Items->Add(pPalettes->Strings[i]);
        }
        frmImportBitmap->cmbImageFormat->Enabled = pPalettes->Count > 1;
        frmImportBitmap->cmbImageFormat->ItemIndex = 0;
        bResult = frmImportBitmap->Execute(sFiles);
        m_sPaletteSignature = frmImportBitmap->cmbImageFormat->Text;
    }
    else
    {
        m_sError = "Failed to create the Import Bitmap dialog!\n\tCould be out of memory!";
    }
    return bResult;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImporterBitmap::Import(TStrings* sFiles)
{
    bool bResult = false;
    if (true == frmImportBitmap->radImportAsScreen->Checked)
    {
        bResult = AddScreen(sFiles);
    }
    else if (true == frmImportBitmap->radImportAsSprite->Checked)
    {
        bResult = AddSprites(sFiles);
    }
    else if (true == frmImportBitmap->radImportAsTile->Checked)
    {
        bResult = AddTile(sFiles);
    }
    return bResult;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImporterBitmap::AddSprites(TStrings* sFiles)
{
    bool bResult = false;
    ZXImage* pImage = NULL;

    for (int f = 0; f < sFiles->Count; f++)
    {
        String sFile = sFiles->Strings[f];
        frmImportBitmap->imgBitmap->Picture->Bitmap->LoadFromFile(sFile);
        if (frmImportBitmap->radSpriteSingle->Checked || frmImportBitmap->edtNewName->Visible)
        {
            if (frmImportBitmap->edtNewName->Visible)
            {
                sFile = frmImportBitmap->edtNewName->Text;
            }
            sFile = ChangeFileExt(ExtractFileName(sFile), "");
            // convert the bitmap to the graphic format required
            AddImage
            (
                "Sprite",
                sFile,
                frmImportBitmap->imgBitmap->Picture->Bitmap->Width,
                frmImportBitmap->imgBitmap->Picture->Bitmap->Height,
                frmImportBitmap->chkImageIsMasked,
                &pImage
            );
            if (true == SAFE_PTR(pImage))
            {
                bResult = pImage->ConvertBitmap(frmImportBitmap->imgBitmap->Picture->Bitmap);
                if (!bResult)
                {
                    m_sError = "Fail to convert the bitmap to an image. File: " + sFile;
                }
                else
                {
                    if (frmImportBitmap->chkImageIsMasked && frmImportBitmap->chkMaskBackground)
                    {
                        pImage->ConvertBitmapMask(frmImportBitmap->imgBitmap->Picture->Bitmap, frmImportBitmap->panMaskColour->Color);
                    }
                }
            }
            else
            {
                m_sError = "Failed to create an image in the project. File: " + sFile;
            }
        }
        else
        {
            // extract the frames and add them
            Graphics::TBitmap* pFrame = new Graphics::TBitmap();
            if (true == SAFE_PTR(pFrame))
            {
                int iWidth       = frmImportBitmap->imgBitmap->Picture->Bitmap->Width;
                int iHeight      = frmImportBitmap->imgBitmap->Picture->Bitmap->Height;
                int iSpriteWidth = frmImportBitmap->edtSpriteMultiFrameWidth->Value;
                pFrame->Width    = iSpriteWidth;
                pFrame->Height   = iHeight;

                for (int i = 0; i < iWidth / frmImportBitmap->edtSpriteMultiFrameWidth->Value; i++)
                {
                    // and copy the frame into the frame bitmap
                    BitBlt
                    (
                        pFrame->Canvas->Handle,
                        0, 0, iSpriteWidth, iHeight,
                        frmImportBitmap->imgBitmap->Picture->Bitmap->Canvas->Handle,
                        i * iSpriteWidth, 0,
                        SRCCOPY
                    );
                    String sName = sFiles->Strings[0];
                    if (sFiles->Count > 1)
                    {
                        frmImportBitmap->edtNewName->Text;
                    }
                    sName = ChangeFileExt(ExtractFileName(sName), "");
                    AddImage
                    (
                        "Sprite",
                        sName,
                        iSpriteWidth,
                        iHeight,
                        false,
                        &pImage
                    );
                    if (true == SAFE_PTR(pImage))
                    {
                        bResult = pImage->ConvertBitmap(pFrame);
                        if (!bResult)
                        {
                            m_sError = "Failed to convert the bitmap to an image. File: " + sFile;
                        }
                        else
                        {
                            if (frmImportBitmap->chkImageIsMasked && frmImportBitmap->chkMaskBackground)
                            {
                                pImage->ConvertBitmapMask(frmImportBitmap->imgBitmap->Picture->Bitmap, frmImportBitmap->panMaskColour->Color);
                            }
                        }
                    }
                    else
                    {
                        m_sError = "Failed to add an image to the frame. File: " + sFile;
                    }
                }
            }
            else
            {
                m_sError = "Failed to create a frame in the current image. File: " + sFile;
            }
        }
    }
    if (!bResult)
    {
        m_sError += "\nFailed to add the bitmap as a sprite";
    }
    return bResult;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImporterBitmap::AddScreen(TStrings* sFiles)
{
    // TODO: Remove dependency on 256x192 screens
    // read the screen size from the project xml system properties
    bool bResult = false;
    ZXImage* pImage = NULL;

    Graphics::TBitmap* pBitmap = new Graphics::TBitmap();
    for (int f = 0; f < sFiles->Count; f++)
    {
        String sFile = sFiles->Strings[f];
        frmImportBitmap->imgBitmap->Picture->Bitmap->LoadFromFile(sFile);
        // stretch the bitmap into a screen$ sized bitmap
        pBitmap->Width  = 256;
        pBitmap->Height = 192;
        StretchBlt
        (
            pBitmap->Canvas->Handle,
            0, 0, 256, 192,
            frmImportBitmap->imgBitmap->Picture->Bitmap->Canvas->Handle,
            0, 0,
            frmImportBitmap->imgBitmap->Picture->Bitmap->Width,
            frmImportBitmap->imgBitmap->Picture->Bitmap->Height,
            SRCCOPY
        );
        // convert the bitmap to the graphic format required
        AddImage
        (
            "Screen",
            ChangeFileExt(ExtractFileName(sFile), ""),
            256,
            192,
            false,
            &pImage
        );
        if (true == SAFE_PTR(pImage))
        {
            bResult = pImage->ConvertBitmap(pBitmap);
            if (!bResult)
            {
                m_sError = "Failed to convert the bitmap to a screen image. File: " + sFile;
            }
        }
        else
        {
            m_sError = "Failed to create the screen image to place the bitmap into. File: " + sFile;
        }
    }
    if (!bResult)
    {
        m_sError += "\nFailed to import bitmap as screen image";
    }
    // free the stretched bitmap
    SAFE_DELETE(pBitmap);

    return bResult;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImporterBitmap::AddTile(TStrings* sFiles)
{
    bool bResult = false;
    ZXImage* pImage = NULL;

    Graphics::TBitmap* pBitmap = frmImportBitmap->imgBitmap->Picture->Bitmap;
    for (int f = 0; f < sFiles->Count; f++)
    {
        String sFile = sFiles->Strings[f];
        frmImportBitmap->imgBitmap->Picture->Bitmap->LoadFromFile(sFile);
        // convert the bitmap to the graphic format required
        AddImage
        (
            "Tile",
            ChangeFileExt(ExtractFileName(sFile), ""),
            frmImportBitmap->imgBitmap->Picture->Bitmap->Width,
            frmImportBitmap->imgBitmap->Picture->Bitmap->Height,
            frmImportBitmap->chkImageIsMasked,
            &pImage
        );
        if (true == SAFE_PTR(pImage))
        {
            bResult = pImage->ConvertBitmap(pBitmap);
            if (!bResult)
            {
                m_sError = "Failed to convert the bitmap to a tile image. File: " + sFile;
            }
            else
            {
                if (frmImportBitmap->chkImageIsMasked && frmImportBitmap->chkMaskBackground)
                {
                    pImage->ConvertBitmapMask(frmImportBitmap->imgBitmap->Picture->Bitmap, frmImportBitmap->panMaskColour->Color);
                }
            }
        }
        else
        {
            m_sError = "Failed to create the tile image to place the bitmap into. File: " + sFile;
        }
    }
    if (!bResult)
    {
        m_sError += "\nFailed to import bitmap as tile image";
    }
    return bResult;
}
//---------------------------------------------------------------------------

