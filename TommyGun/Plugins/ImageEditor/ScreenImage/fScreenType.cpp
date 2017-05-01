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
#include "fScreenType.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KSpinEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageTypes;
//---------------------------------------------------------------------------
TfrmScreenType *frmScreenType = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmScreenType::TfrmScreenType(TComponent* Owner)
: TForm(Owner)
, m_pImageManager(NULL)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmScreenType::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    TTabSheet* pTabSheet = NULL;
    m_ImageEditor.TypeAddTab(PluginHandle, "Screens", imgIcon->Picture->Bitmap, pTabSheet);
    if (true == SAFE_PTR(pTabSheet))
    {
        panScreens->Parent = pTabSheet;
    }
    m_ImageEditor.TypeGetImageManager(PluginHandle, m_pImageManager);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmScreenType::Release(void)
{
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures)
{
    cmbScreenFormat->Items->Clear();
    cmbScreenFormat->Enabled = false;
    if (true == SAFE_PTR(pPalettes) && 0 < pPalettes->Count)
    {
        // filter out the required palettes
        for (int i = 0; i < pPalettes->Count; i++)
        {
            ZXPalette* pPalette = m_pImageManager->GetPalette(i);
            if (true == SAFE_PTR(pPalette) && pPalette->IsImageTypeSupported(itScreen))
            {
                cmbScreenFormat->Items->Add(pPalette->Name);
                m_vPaletteSignatures.push_back(vSignatures[i]);
            }
        }
        cmbScreenFormat->Enabled   = cmbScreenFormat->Items->Count > 0;
        cmbScreenFormat->ItemIndex = 0;
        /*cmbScreenFormat->Items->AddStrings(pPalettes);
        m_vPaletteSignatures.assign(vSignatures.begin(), vSignatures.end());*/
    }
    edtScreenName->Enabled   = (0 < pPalettes->Count);
    lstScreenList->Enabled   = edtScreenName->Enabled;
    //edtScreenWidth->Enabled  = cmdScreenAdd->Enabled;
    //edtScreenHeight->Enabled = cmdScreenAdd->Enabled;
    cmbScreenFormatChange(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::RefreshList(void)
{
    lstScreenList->ItemIndex = -1;
    m_pImageManager->GetImageList(g_sTypeSignature, lstScreenList->Items);
    if (0 < lstScreenList->Items->Count)
    {
        lstScreenList->ItemIndex = 0;
    }
    UpdatePreview();
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::UpdateButtons(void)
{
    cmdScreenAdd->Enabled     = false;
    cmdScreenRemove->Enabled  = false;
    cmdScreenRename->Enabled  = false;
    cmdScreenClone->Enabled   = false;
    if (true == SAFE_PTR(m_pImageManager))
    {
        cmdScreenAdd->Enabled     = edtScreenName->Text.Trim() != "";
        cmdScreenAdd->Enabled    &= !m_pImageManager->DoesImageExist(g_sTypeSignature, edtScreenName->Text);
        cmdScreenRename->Enabled  = cmdScreenAdd->Enabled && -1 != lstScreenList->ItemIndex;
        cmdScreenRemove->Enabled  = 0 != m_pImageManager->GetImageCount(g_sTypeSignature);
        cmdScreenClone->Enabled   = 0 != m_pImageManager->GetImageCount(g_sTypeSignature) && -1 != lstScreenList->ItemIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::UpdatePreview(void)
{
    pbxScreenPreview->Canvas->Brush->Color = clWhite;
    pbxScreenPreview->Canvas->FillRect(pbxScreenPreview->ClientRect);
    if (true == SAFE_PTR(m_pImageManager))
    {
        ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstScreenList->ItemIndex, 0);
        if (true == SAFE_PTR(pImage))
        {
            pImage->Invalidate();
            pImage->Draw(pbxScreenPreview->Canvas, 1);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::cmdScreenAddClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iIndex = m_pImageManager->AddImage(g_sTypeSignature,
                                               m_vPaletteSignatures[cmbScreenFormat->ItemIndex],
                                               edtScreenName->Text,
                                               edtScreensWidth->Value,
                                               edtScreensHeight->Value,
                                               false);
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex, 0);
            m_pImageManager->GetImageList(g_sTypeSignature, lstScreenList->Items);
            lstScreenList->ItemIndex = iIndex;
            UpdatePreview();
            UpdateButtons();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::cmdScreenRemoveClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iAnswer = 0;
        m_ImageEditor.SystemMessageBox(mbtWarning,
                      "Do you want to Remove a screen image?",
                      "You are about to remove a screen.",
                      "You have choosen to remove a screen\n"
                      "This is a permanent operation and you will not be able to Undo this operation\n\n"
                      "Click\n"
                      "\tYes\tto Remove the screen permanently\n"
                      "\tNo\tto cancel the operation and leave the screen",
                      "No", "Yes", "", iAnswer );
        if (1 == iAnswer)
        {
            if (true == m_pImageManager->RemoveImage(g_sTypeSignature, lstScreenList->ItemIndex))
            {
                lstScreenList->Items->Strings[lstScreenList->ItemIndex] = edtScreenName->Text;
                m_pImageManager->GetImageList(g_sTypeSignature, lstScreenList->Items);
                lstScreenList->ItemIndex = -1;
                edtScreenName->Text = "";
                m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, -1, 0);
                UpdatePreview();
            }
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::cmdScreenCloneClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        String sName = edtScreenName->Text;
        while (true == m_pImageManager->DoesImageExist(g_sTypeSignature, sName))
        {
            sName = "Copy of " + sName;
        }
        int iIndex = m_pImageManager->CloneImage(g_sTypeSignature, sName, lstScreenList->ItemIndex);
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex, 0);
            m_pImageManager->GetImageList(g_sTypeSignature, lstScreenList->Items);
            lstScreenList->ItemIndex = iIndex;
            UpdatePreview();
            UpdateButtons();
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::cmdScreenRenameClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager) && -1 != lstScreenList->ItemIndex)
    {
        if (true == m_pImageManager->RenameImage(g_sTypeSignature, lstScreenList->ItemIndex, edtScreenName->Text))
        {
            lstScreenList->Items->Strings[lstScreenList->ItemIndex] = edtScreenName->Text;
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::edtScreenNameChange(TObject *Sender)
{
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::lstScreenListClick(TObject *Sender)
{
    ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstScreenList->ItemIndex, 0);
    if (true == SAFE_PTR(pImage))
    {
        edtScreenName->Text     = pImage->Name;
        edtScreensWidth->Value  = pImage->Width;
        edtScreensHeight->Value = pImage->Height;
        SetComboText(cmbScreenFormat, pImage->Palette->Name);
    }
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstScreenList->ItemIndex, 0);
    UpdateButtons();
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::pbxScreenPreviewPaint(TObject *Sender)
{
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::SetComboText(TComboBox* pComboBox, String sText)
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
void __fastcall TfrmScreenType::cmbScreenFormatChange(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        ZXPalette* pPalette = m_pImageManager->GetPalette(cmbScreenFormat->Items->Strings[cmbScreenFormat->ItemIndex]);
        if (true == SAFE_PTR(pPalette))
        {
            int iWidth = pPalette->DefaultScreenWidth;
            int iHeight = pPalette->DefaultScreenHeight;
            edtScreensWidth->Enabled  = pPalette->ScreenResizeable;
            edtScreensHeight->Enabled = pPalette->ScreenResizeable;
            edtScreensWidth->Value  = iWidth;
            edtScreensHeight->Value = iHeight;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmScreenType::AddScorePanel(void)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        if (!m_pImageManager->DoesImageExist(g_sTypeSignature, "ScorePanel"))
        {
            m_pImageManager->AddImage(g_sTypeSignature,
                                      m_vPaletteSignatures[cmbScreenFormat->ItemIndex],
                                      "ScorePanel",
                                      edtScreensWidth->Value,
                                      edtScreensHeight->Value,
                                      false);
        }
    }       
}
//---------------------------------------------------------------------------

