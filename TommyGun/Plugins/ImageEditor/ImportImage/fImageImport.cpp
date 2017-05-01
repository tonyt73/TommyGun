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
#include "..\..\..\SafeMacros.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageImport;
//---------------------------------------------------------------------------
TfrmImageImport *frmImageImport = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmImageImport::TfrmImageImport(TComponent* Owner)
    : TForm(Owner),
      m_pImageManager(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmImageImport::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    m_pPalettes = new TStringList();

    // add the import menu to the applicaton main menu
    if (Application->MainForm && Application->MainForm->Menu)
    {
        mnuImportImage->Items->Remove(mnuImportImages);
        mnuImportImage->Items->Remove(mnuImportImageSheet);
        TMenuItem* mnuFile = Application->MainForm->Menu->Items->Find("&File");
        if (true == SAFE_PTR(mnuFile))
        {
            TMenuItem* mnuImport = mnuFile->Find("&Import");
            if (true == SAFE_PTR(mnuImport))
            {
                mnuImport->Visible = true;
                mnuImport->Add(mnuImportImages);
                mnuImport->Add(mnuImportImageSheet);
            }
        }
    }

    m_ImageEditor.TypeGetImageManager(PluginHandle, m_pImageManager);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmImageImport::Release(void)
{
    SAFE_DELETE(m_pPalettes);
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageImport::SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures)
{
    if (true == SAFE_PTR(pPalettes) && 0 < pPalettes->Count)
    {
        m_vPaletteSignatures = vSignatures;
        m_pPalettes->Assign(pPalettes);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageImport::mnuImportImagesClick(TObject *Sender)
{
    if (m_vPaletteSignatures.size() > 0)
    {
        TGenericGraphic* pGraphic = new TGenericGraphic();
        TPicture::RegisterFileFormat(__classid(TPicture), "zxg", "Spectrum Graphic", __classid(TGenericGraphic));
        TPicture::RegisterFileFormat(__classid(TPicture), "sna", "Spectrum Memory Snapshot", __classid(TGenericGraphic));
        TPicture::RegisterFileFormat(__classid(TPicture), "scr", "Spectrum Screen Snapshot", __classid(TGenericGraphic));
        TPicture::RegisterFileFormat(__classid(TPicture), "tgp", "TommyGun Project (old0", __classid(TGenericGraphic));
        TPicture::RegisterFileFormat(__classid(TPicture), "sev", "SevenuP Image", __classid(TGenericGraphic));
        if (dlgImport->Execute())
        {
            String sFile = dlgImport->FileName;
            String sExt  = ExtractFileExt(sFile).LowerCase();

            ZXImporter* pImporter = NULL;

            if (sExt == ".bmp")
            {
                pImporter = new ZXImporterBitmap();
            }
            else if (sExt == ".zxg")
            {
                pImporter = new ZXImporterZXG();
            }
            else if (sExt == ".sna")
            {
                pImporter = new ZXImporterSNA();
            }
            else if (sExt == ".scr")
            {
                pImporter = new ZXImporterSCR();
            }
            else if (sExt == ".sev")
            {
                pImporter = new ZXImporterSevenuP();
            }

            if (true == SAFE_PTR(pImporter))
            {
                pImporter->ImageManager = m_pImageManager;
                TStrings* pFiles = new TStringList();
                pFiles->AddStrings(dlgImport->Files);

                if (pImporter->ChoosePalette(pFiles, m_pPalettes))
                {
                    // selection successful
                    if (pImporter->Import(pFiles))
                    {
                        // import successful - refresh all the image editor lists
                        m_ImageEditor.Notify(m_PluginHandle, IMAGE_EDITOR_REFRESH_LIST, NULL, 0, 0);
                    }
                    else
                    {
                        String sErrorMsg = pImporter->Error;
                        // TODO: Message box - import failed
                        ZXMessageBox MessageBox;
                        MessageBox.ShowMessage
                        (
                            mbtError,
                            "Failed to Import Image",
                            "",
                            "TommyGun failed to import the image.\n"
                            "The importer returned the following error,\n\n"
                            "\tError: " + pImporter->Error + "\n",
                            "Close",
                            "",
                            ""
                        );
                    }
                }
                else
                {
                    ZXMessageBox MessageBox;
                    MessageBox.ShowMessage
                    (
                        mbtError,
                        "Failed to Import Image",
                        "",
                        "TommyGun failed to import the image because either a specific palette was not available or the Import operation was cancelled.\n"
                        "For example if you try to Import a .ZXG, SevenuP file, .SCR or .SNA file into a Commodore 64 project you will get this error.",
                        "Close",
                        "",
                        ""
                    );
                }
                SAFE_DELETE(pImporter);
                SAFE_DELETE(pFiles);
            }
            else
            {
                ZXMessageBox MessageBox;
                MessageBox.ShowMessage
                (
                    mbtError,
                    "Failed to create Importer object",
                    "File type not supported",
                    "TommyGun failed to create an Importer object responsible for importing the file type.\n"
                    "This will be because the file type is not supported.",
                    "Close",
                    "",
                    ""
                );
            }
            TPicture::UnregisterGraphicClass(__classid(TPicture), __classid(TGenericGraphic));
        }
    }
    else
    {
        ZXMessageBox MessageBox;
        MessageBox.ShowMessage
        (
            mbtError,
            "No Palette plugins available for Import",
            "",
            "TommyGun failed to find any Palette plugins which can be used to Import Images.\n",
            "Close",
            "",
            ""
        );
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageImport::mnuImportImageSheetClick(TObject *Sender)
{
    if (m_vPaletteSignatures.size() > 0)
    {
        if (dlgImportSheet->Execute())
        {
            String sFile = dlgImportSheet->FileName;
            String sExt  = ExtractFileExt(sFile).LowerCase();

            if (sExt == ".bmp")
            {
                dlgImageSheetImporter = new TdlgImageSheetImporter(NULL);
                dlgImageSheetImporter->m_pImageManager = m_pImageManager;
                // load the palette combo with the palette names
                dlgImageSheetImporter->cmbImageFormat->Items->Clear();
                for (int i = 0; i < m_pPalettes->Count; i++)
                {
                    dlgImageSheetImporter->cmbImageFormat->Items->Add(m_pPalettes->Strings[i]);
                }
                dlgImageSheetImporter->cmbImageFormat->Enabled = m_pPalettes->Count > 1;
                dlgImageSheetImporter->cmbImageFormat->ItemIndex = 0;
                dlgImageSheetImporter->Execute(sFile, &m_vPaletteSignatures);
                delete dlgImageSheetImporter;
                // import successful - refresh all the image editor lists
                m_ImageEditor.Notify(m_PluginHandle, IMAGE_EDITOR_REFRESH_LIST, NULL, 0, 0);
            }
            else
            {
                ZXMessageBox MessageBox;
                MessageBox.ShowMessage
                (
                    mbtError,
                    "Unsupported Image Sheet Format",
                    "A sheet of images must be in a Windows bitmap file.",
                    "TommyGun requires a sheet of images to be contained in a standard Windows Bitmap file.\n\n\tPlease import only Windows Bitmap files.",
                    "Close",
                    "",
                    ""
                );
            }
        }
    }
    else
    {
        ZXMessageBox MessageBox;
        MessageBox.ShowMessage
        (
            mbtError,
            "No Palette plugins available for Import",
            "",
            "TommyGun failed to find any Palette plugins which can be used to Import Images.\n",
            "Close",
            "",
            ""
        );
    }
}
//---------------------------------------------------------------------------

