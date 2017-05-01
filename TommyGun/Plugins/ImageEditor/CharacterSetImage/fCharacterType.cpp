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
#pragma link "KSpinEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageTypes;
//---------------------------------------------------------------------------
TfrmCharacterType *frmCharacterType = NULL;
//---------------------------------------------------------------------------
const   int     g_iCharacters                   = 96;
const   String  g_sSpecials = " !\"#$%&\'{}*+,-./:;<=>?@[\\]^_£{|}~©";
//---------------------------------------------------------------------------
__fastcall TfrmCharacterType::TfrmCharacterType(TComponent* Owner)
    : TForm(Owner)
    , m_iActiveCharacter(-1)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCharacterType::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    TTabSheet* pTabSheet = NULL;
    m_ImageEditor.TypeAddTab(PluginHandle, "Fonts", imgIcon->Picture->Bitmap, pTabSheet);
    if (true == SAFE_PTR(pTabSheet))
    {
        panCharacterSet->Parent = pTabSheet;
    }
    m_ImageEditor.TypeGetImageManager(PluginHandle, m_pImageManager);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmCharacterType::Release(void)
{
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures)
{
    cmbCharacterSetFormat->Items->Clear();
    cmbCharacterSetFormat->Enabled = false;
    if (true == SAFE_PTR(pPalettes) && 0 < pPalettes->Count)
    {
        // filter out the required palettes
        for (int i = 0; i < pPalettes->Count; i++)
        {
            ZXPalette* pPalette = m_pImageManager->GetPalette(i);
            if (true == SAFE_PTR(pPalette) && pPalette->IsImageTypeSupported(itFont))
            {
                cmbCharacterSetFormat->Items->Add(pPalette->Name);
                m_vPaletteSignatures.push_back(vSignatures[i]);
            }
        }
        //cmbCharacterSetFormat->Items->AddStrings(pPalettes);
        cmbCharacterSetFormat->Enabled   = cmbCharacterSetFormat->Items->Count > 0;
        cmbCharacterSetFormat->ItemIndex = 0;
        //m_vPaletteSignatures.assign(vSignatures.begin(), vSignatures.end());
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::edtCharacterSetNameChange(TObject *Sender)
{
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::cmdCharacterSetAddClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iIndex;
        for (int i = 0; i < g_iCharacters; i++)
        {
            String sName = GetCharName(edtCharacterSetName->Text, i);
            iIndex = m_pImageManager->AddImage(g_sTypeSignature,
                                               m_vPaletteSignatures[cmbCharacterSetFormat->ItemIndex],
                                               sName,
                                               edtCharacterSetWidth->Value,
                                               edtCharacterSetHeight->Value,
                                               chkTileMasked->Checked);
        }
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex / g_iCharacters, 0);
            TStringList* pStrings = new TStringList();
            m_pImageManager->GetImageList(g_sTypeSignature, pStrings);
            lstCharacterSetList->Items->Clear();
            for (int i = 0; i < pStrings->Count; i += g_iCharacters)
            {
                lstCharacterSetList->Items->Add(pStrings->Strings[i].SubString(1, pStrings->Strings[i].Length() - 10));
            }
            lstCharacterSetList->ItemIndex = iIndex / g_iCharacters;
            SAFE_DELETE(pStrings);
            ResizeChars(edtCharacterSetWidth->Value, edtCharacterSetHeight->Value);
            UpdatePreview();
            UpdateButtons();
            spdCharacterSetSpaceClick(spdCharacterSetSpace);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::cmdCharacterSetRemoveClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iAnswer = 0;
        m_ImageEditor.SystemMessageBox(mbtWarning,
                      "Do you want to Remove the Font?",
                      "You are about to remove a Font from the Font list.",
                      "You have choosen to remove a Font from the Font list\n"
                      "This is a permanent operation and you will not be able to Undo this operation\n\n"
                      "Click\n"
                      "\tYes\tto Remove the tile permanently\n"
                      "\tNo\tto cancel the operation and leave the tile in the list",
                      "No", "Yes", "", iAnswer );
        if (1 == iAnswer)
        {
            for (int i = 0; i < g_iCharacters; i++)
            {
                m_pImageManager->RemoveImage(g_sTypeSignature, lstCharacterSetList->ItemIndex * g_iCharacters);
            }
            RefreshList();
            lstCharacterSetList->ItemIndex = -1;
            edtCharacterSetName->Text = "";
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, -1, 0);
            UpdatePreview();
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::cmdCharacterSetCloneClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        String sName = edtCharacterSetName->Text;
        while (true == m_pImageManager->DoesImageExist(g_sTypeSignature, sName + "_ascii_032"))
        {
            sName = "Copy of " + sName;
        }
        int iIndex;
        for (int i = 0; i < g_iCharacters; i++)
        {
            String sCloneName = GetCharName(sName, i);
            int iCharacter = (lstCharacterSetList->ItemIndex * g_iCharacters) + i;
            iIndex = m_pImageManager->CloneImage(g_sTypeSignature, sCloneName, iCharacter);
        }
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex / g_iCharacters, 0);
            RefreshList();
            lstCharacterSetList->ItemIndex = iIndex / g_iCharacters;
            UpdatePreview();
            UpdateButtons();
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::cmdCharacterSetRenameClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager) && -1 != lstCharacterSetList->ItemIndex)
    {
        for (int i = 0; i < g_iCharacters; i++)
        {
            int iChar = (lstCharacterSetList->ItemIndex * g_iCharacters) + i;
            String sName = GetCharName(edtCharacterSetName->Text, i);
            m_pImageManager->RenameImage(g_sTypeSignature, iChar, sName);
        }
        lstCharacterSetList->Items->Strings[lstCharacterSetList->ItemIndex] = edtCharacterSetName->Text;
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::lstCharacterSetListClick(TObject *Sender)
{
    // select character A of the character set
    if (lstCharacterSetList->ItemIndex >= 0)
    {
        edtCharacterSetName->Text = lstCharacterSetList->Items->Strings[lstCharacterSetList->ItemIndex];
    }
    ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstCharacterSetList->ItemIndex * g_iCharacters, 0);
    if (true == SAFE_PTR(pImage))
    {
        edtCharacterSetWidth->Value  = pImage->Width;
        edtCharacterSetHeight->Value = pImage->Height;
        chkTileMasked->Checked       = pImage->IsMasked;
        m_iPixelsHigh                = pImage->Palette->PixelsHighPerAttribute;
        edtCharacterSetHeight->Step  = m_iPixelsHigh;
        SetComboText(cmbCharacterSetFormat, pImage->Palette->Name);
        ResizeChars(pImage->Width, pImage->Height);
    }
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstCharacterSetList->ItemIndex * g_iCharacters, 0);
    UpdateButtons();
    UpdatePreview();
    spdCharacterSetSpaceClick(spdCharacterSetSpace);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::spdCharacterSetSpaceClick(TObject *Sender)
{
    // select an image
    TSpeedButton* pButton = dynamic_cast<TSpeedButton*>(Sender);
    if (true == SAFE_PTR(pButton))
    {
        m_iActiveCharacter = pButton->Tag;
        int iCharacter = (lstCharacterSetList->ItemIndex * g_iCharacters) + m_iActiveCharacter;
        m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iCharacter , 0);
        UpdateButtons();
        UpdatePreview();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::pbxCharacterSetPreviewPaint(TObject *Sender)
{
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::pbxCharacterSetPreviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    int px = pbxCharacterSetPreview->Width;
    int cw = edtCharacterSetWidth->Value * 2;
    int ch = edtCharacterSetHeight->Value * 2;
    int cpw = px / cw;
    m_iActiveCharacter = std::max(0, std::min(g_iCharacters - 1, (X / cw) + ((Y / ch) * cpw)));
    int iCharacter = (lstCharacterSetList->ItemIndex * g_iCharacters) + m_iActiveCharacter;
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iCharacter, 0);
    UpdateButtons();
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::cmbCharacterSetFormatChange(TObject *Sender)
{
    ZXPalette* pPalette = m_pImageManager->GetPalette(cmbCharacterSetFormat->Items->Strings[cmbCharacterSetFormat->ItemIndex]);
    if (true == SAFE_PTR(pPalette))
    {
        m_iPixelsHigh = pPalette->PixelsHighPerAttribute;
        edtCharacterSetHeight->Step = m_iPixelsHigh;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::UpdatePreview(void)
{
    if (lstCharacterSetList->Items->Count && lstCharacterSetList->ItemIndex != -1)
    {
        pbxCharacterSetPreview->Canvas->Brush->Color = clBlack;
        pbxCharacterSetPreview->Canvas->FillRect(pbxCharacterSetPreview->ClientRect);
        if (true == SAFE_PTR(m_pImageManager))
        {
            int cx = 0;
            int cy = 0;
            for (int i = 0; i < g_iCharacters; i++)
            {
                int iCharacter = (lstCharacterSetList->ItemIndex * g_iCharacters) + i;
                ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, iCharacter, 0);
                if (true == SAFE_PTR(pImage))
                {
                    pImage->Invalidate();
                    pImage->ReDraw();
                    if (cx + (pImage->Width * 2) > pbxCharacterSetPreview->Width)
                    {
                        cx = 0;
                        cy += pImage->Height * 2;
                    }
                    pImage->Draw(pbxCharacterSetPreview->Canvas, 2, cx, cy);
                    if (i == m_iActiveCharacter)
                    {
                        TRect TheRect = Rect(cx, cy, cx + (pImage->Width * 2), cy + (pImage->Height * 2));
                        pbxCharacterSetPreview->Canvas->Brush->Color = clRed;
                        pbxCharacterSetPreview->Canvas->FrameRect(TheRect);
                    }
                    cx += pImage->Width * 2;
                }
            }
        }
    }
    else
    {
        pbxCharacterSetPreview->Canvas->Brush->Color = clWhite;
        pbxCharacterSetPreview->Canvas->FillRect(pbxCharacterSetPreview->ClientRect);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::UpdateButtons(void)
{
    cmdCharacterSetAdd->Enabled     = false;
    cmdCharacterSetRemove->Enabled  = false;
    cmdCharacterSetRename->Enabled  = false;
    cmdCharacterSetClone->Enabled   = false;
    if (true == SAFE_PTR(m_pImageManager))
    {
        cmdCharacterSetAdd->Enabled     = edtCharacterSetName->Text.Trim() != "";
        if (cmdCharacterSetAdd->Enabled)
        {
            cmdCharacterSetAdd->Enabled    &= !m_pImageManager->DoesImageExist(g_sTypeSignature, edtCharacterSetName->Text + "_A");
        }
        cmdCharacterSetRename->Enabled  = cmdCharacterSetAdd->Enabled && -1 != lstCharacterSetList->ItemIndex;
        cmdCharacterSetRemove->Enabled  = 0 != m_pImageManager->GetImageCount(g_sTypeSignature);
        cmdCharacterSetClone->Enabled   = edtCharacterSetName->Text.Trim() != "" && 0 != m_pImageManager->GetImageCount(g_sTypeSignature) && -1 != lstCharacterSetList->ItemIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::RefreshList(void)
{
    lstCharacterSetList->ItemIndex = -1;
    TStringList* pStrings = new TStringList();
    m_pImageManager->GetImageList(g_sTypeSignature, pStrings);
    lstCharacterSetList->Items->Clear();
    for (int i = 0; i < pStrings->Count; i += g_iCharacters)
    {
        String sName = pStrings->Strings[i];
        if (0 == sName.Pos("_ascii_"))
        {
            String sNum = "000" + IntToStr(32 + (i % 96));
            sNum = sNum.SubString(sNum.Length()-2, 3);
            sName = sName.SubString(1, sName.Length() - 2) + "_ascii_" + sNum;
            m_pImageManager->RenameImage(g_sTypeSignature, i, sName);
        }
        // rename the old style font names if needed
        lstCharacterSetList->Items->Add(sName.SubString(1, sName.Length() - 10));
    }
    if (0 < lstCharacterSetList->Items->Count)
    {
        lstCharacterSetList->ItemIndex = 0;
        lstCharacterSetListClick(NULL);
    }
    SAFE_DELETE(pStrings);
    UpdatePreview();
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCharacterType::SetComboText(TComboBox* pComboBox, String sText)
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
void __fastcall TfrmCharacterType::ResizeChars(int W, int H)
{
    int rows = (W * 2 * 96) / pbxCharacterSetPreview->Width;
    pbxCharacterSetPreview->Height = H * rows * 2;
}
//---------------------------------------------------------------------------
String __fastcall TfrmCharacterType::GetCharName(String sName, int Index)
{
    String sNum = "000" + IntToStr(32 + Index);
    sNum = sNum.SubString(sNum.Length()-2, 3);
    return sName + "_ascii_" + sNum;
}
//---------------------------------------------------------------------------

