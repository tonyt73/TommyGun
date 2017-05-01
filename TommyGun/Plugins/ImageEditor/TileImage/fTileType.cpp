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
#include "fTileType.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KSpinEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageTypes;
//---------------------------------------------------------------------------
TfrmTileType *frmTileType = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmTileType::TfrmTileType(TComponent* Owner)
: TForm(Owner)
, m_pImageManager(NULL)
, m_bSizeEnabled(true)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmTileType::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    TTabSheet* pTabSheet = NULL;
    m_ImageEditor.TypeAddTab(PluginHandle, "Tiles", imgIcon->Picture->Bitmap, pTabSheet);
    if (true == SAFE_PTR(pTabSheet))
    {
        panTiles->Parent = pTabSheet;
    }
    m_ImageEditor.TypeGetImageManager(PluginHandle, m_pImageManager);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmTileType::Release(void)
{
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures)
{
    cmbTileFormat->Items->Clear();
    cmbTileFormat->Enabled = false;
    if (true == SAFE_PTR(pPalettes) && 0 < pPalettes->Count)
    {
        // filter out the required palettes
        for (int i = 0; i < pPalettes->Count; i++)
        {
            ZXPalette* pPalette = m_pImageManager->GetPalette(i);
            if (true == SAFE_PTR(pPalette) && pPalette->IsImageTypeSupported(itTile))
            {
                cmbTileFormat->Items->Add(pPalette->Name);
                m_vPaletteSignatures.push_back(vSignatures[i]);
            }
        }
        //cmbTileFormat->Items->AddStrings(pPalettes);
        cmbTileFormat->Enabled   = cmbTileFormat->Items->Count > 0;
        cmbTileFormat->ItemIndex = 0;
        //m_vPaletteSignatures.assign(vSignatures.begin(), vSignatures.end());
    }
    edtTileName->Enabled   = (0 < pPalettes->Count);
    lstTileList->Enabled   = edtTileName->Enabled;
    edtTileWidth->Enabled  = edtTileName->Enabled;
    edtTileHeight->Enabled = edtTileName->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::cmdTileAddClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iMinWidth = 8;
        ZXPalette* pPalette = m_pImageManager->GetPalette(cmbTileFormat->Items->Strings[cmbTileFormat->ItemIndex]);
        if (SAFE_PTR(pPalette))
        {
            iMinWidth = pPalette->PixelsPerByte;
        }
        if (edtTileWidth->Enabled && edtTileWidth->Value % iMinWidth)
        {
            edtTileWidth->Value = (edtTileWidth->Value + iMinWidth) - (edtTileWidth->Value % iMinWidth);
        }
        if (edtTileHeight->Enabled && edtTileHeight->Value % m_iPixelsHigh)
        {
            edtTileHeight->Value = (edtTileHeight->Value + m_iPixelsHigh) - (edtTileHeight->Value % m_iPixelsHigh);
        }
        int iIndex = m_pImageManager->AddImage(g_sTypeSignature,
                                               m_vPaletteSignatures[cmbTileFormat->ItemIndex],
                                               edtTileName->Text,
                                               edtTileWidth->Value,
                                               edtTileHeight->Value,
                                               chkTileMasked->Checked,
                                               NULL,
                                               true);
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex, 0);
            m_pImageManager->GetImageList(g_sTypeSignature, lstTileList->Items);
            lstTileList->ItemIndex = iIndex;
            UpdatePreview();
            UpdateButtons();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::lstTileListClick(TObject *Sender)
{
    ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstTileList->ItemIndex, 0);
    if (true == SAFE_PTR(pImage))
    {
        pImage->CanResize           = true;
        edtTileName->Text           = pImage->Name;
        edtTileWidth->Value         = edtTileWidth->Enabled ? pImage->Width : 8;
        edtTileHeight->Value        = edtTileHeight->Enabled ? pImage->Height : 8;
        m_iPixelsHigh               = pImage->Palette->PixelsHighPerAttribute;
        chkTileMasked->Checked      = pImage->IsMasked;
        edtTileHeight->Step         = m_iPixelsHigh;
        SetComboText(cmbTileFormat, pImage->Palette->Name);
        cmbType->ItemIndex          = m_pImageManager->GetSubType(g_sTypeSignature, lstTileList->ItemIndex);
    }
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstTileList->ItemIndex, 0);
    UpdateButtons();
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::pbxTilePreviewPaint(TObject *Sender)
{
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::UpdatePreview(void)
{
    pbxTilePreview->Canvas->Brush->Color = clWhite;
	pbxTilePreview->Canvas->FillRect(pbxTilePreview->ClientRect);
	if (true == SAFE_PTR(m_pImageManager))
	{
		ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstTileList->ItemIndex, 0);
		if (true == SAFE_PTR(pImage))
		{
			bool bMaskMode = pImage->MaskMode;
			m_pImageManager->SetMaskMode(false);
			pImage->Invalidate();
			float fImgX = pImage->ModeScaleX;
			float fImgY = pImage->ModeScaleY;
			pImage->ModeScaleX = pImage->Palette->ScalarX;
			pImage->ModeScaleY = pImage->Palette->ScalarY;
			int sw = std::max((int)((int)(panTilePreview->Width  / pImage->Width ) / pImage->Palette->ScalarX), 1);
			int sh = std::max((int)((int)(panTilePreview->Height / pImage->Height) / pImage->Palette->ScalarY), 1);
			int ss = std::min(sw, sh);
			pbxTilePreview->Width  = ss * pImage->Width;
			pbxTilePreview->Height = ss * pImage->Height;
			pbxTilePreview->Left = ((panTilePreview->Width  - pbxTilePreview->Width ) / 2) - 1;
			pbxTilePreview->Top  = ((panTilePreview->Height - pbxTilePreview->Height) / 2) - 1;
			pImage->Draw(pbxTilePreview->Canvas, ss);
			pImage->ModeScaleX = fImgX;
            pImage->ModeScaleY = fImgY;
            edtTileWidth->Value = edtTileWidth->Enabled ? pImage->Width : 8;
            edtTileHeight->Value = edtTileHeight->Enabled ? pImage->Height : 8;
            m_pImageManager->SetMaskMode(bMaskMode);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::edtTileNameChange(TObject *Sender)
{
    edtTileWidth->Enabled = m_bSizeEnabled || edtTileName->Text.LowerCase() == "scorepanel";
    edtTileHeight->Enabled = m_bSizeEnabled || edtTileName->Text.LowerCase() == "scorepanel";
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::UpdateButtons(void)
{
    cmdTileAdd->Enabled     = false;
    cmdTileRemove->Enabled  = false;
    cmdTileRename->Enabled  = false;
    cmdTileClone->Enabled   = false;
    if (true == SAFE_PTR(m_pImageManager))
    {
        cmdTileAdd->Enabled     = edtTileName->Text != "";
        cmdTileAdd->Enabled    &= !m_pImageManager->DoesImageExist(g_sTypeSignature, edtTileName->Text);
        cmdTileRename->Enabled  = cmdTileAdd->Enabled && -1 != lstTileList->ItemIndex; 
        cmdTileRemove->Enabled  = 0 != m_pImageManager->GetImageCount(g_sTypeSignature);
        cmdTileClone->Enabled   = 0 != m_pImageManager->GetImageCount(g_sTypeSignature) && -1 != lstTileList->ItemIndex;
        ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstTileList->ItemIndex, 0);
        if (true == SAFE_PTR(pImage))
        {
            edtTileWidth->Value  = pImage->Width;
            edtTileHeight->Value = pImage->Height;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::cmdTileRemoveClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iAnswer = 0;
        m_ImageEditor.SystemMessageBox(mbtWarning,
                      "Do you want to Remove a tile image?",
                      "You are about to remove a tile.",
                      "You have choosen to remove a tile\n"
                      "This is a permanent operation and you will not be able to Undo this operation\n\n"
                      "Click\n"
                      "\tYes\tto Remove the tile permanently\n"
                      "\tNo\tto cancel the operation and leave the tile",
                      "No", "Yes", "", iAnswer );
        if (1 == iAnswer)
        {
            if (true == m_pImageManager->RemoveImage(g_sTypeSignature, lstTileList->ItemIndex))
            {
                lstTileList->Items->Strings[lstTileList->ItemIndex] = edtTileName->Text;
                m_pImageManager->GetImageList(g_sTypeSignature, lstTileList->Items);
                lstTileList->ItemIndex = -1;
                edtTileName->Text = "";
                m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, -1, 0);
                UpdatePreview();
            }
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::cmdTileCloneClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        String sName = edtTileName->Text;
        while (true == m_pImageManager->DoesImageExist(g_sTypeSignature, sName))
        {
            sName = "Copy of " + sName;
        }
        int iIndex = m_pImageManager->CloneImage(g_sTypeSignature, sName, lstTileList->ItemIndex);
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex, 0);
            m_pImageManager->GetImageList(g_sTypeSignature, lstTileList->Items);
            lstTileList->ItemIndex = iIndex;
            UpdatePreview();
            UpdateButtons();
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::cmdTileRenameClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager) && -1 != lstTileList->ItemIndex)
    {
        if (true == m_pImageManager->RenameImage(g_sTypeSignature, lstTileList->ItemIndex, edtTileName->Text))
        {
            lstTileList->Items->Strings[lstTileList->ItemIndex] = edtTileName->Text;
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::RefreshList(void)
{
    lstTileList->ItemIndex = -1;
    m_pImageManager->GetImageList(g_sTypeSignature, lstTileList->Items);
    if (0 < lstTileList->Items->Count)
    {
        lstTileList->ItemIndex = 0;
    }
    UpdatePreview();
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::SetComboText(TComboBox* pComboBox, String sText)
{
    for (int i = 0; i < pComboBox->Items->Count; i++)
    {
        if (pComboBox->Items->Strings[i] == sText)
        {
            pComboBox->ItemIndex = i;
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::cmbTileFormatChange(TObject *Sender)
{
    ZXPalette* pPalette = m_pImageManager->GetPalette(cmbTileFormat->Items->Strings[cmbTileFormat->ItemIndex]);
    if (true == SAFE_PTR(pPalette))
    {
        m_iPixelsHigh = pPalette->PixelsHighPerAttribute;
        edtTileHeight->Step = m_iPixelsHigh;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTileType::cmbTypeChange(TObject *Sender)
{
    m_pImageManager->SetSubType(g_sTypeSignature, lstTileList->ItemIndex, cmbType->ItemIndex);
}
//---------------------------------------------------------------------------


