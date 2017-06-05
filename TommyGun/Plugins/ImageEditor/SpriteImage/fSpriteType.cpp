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
#include "fSpriteType.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KSlider"
#pragma link "KSpinEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageTypes;
//---------------------------------------------------------------------------
const int g_iSpeeds[10] =
{
       1,   //    1 ms
      10,   //   10 ms
      25,   //   25 ms
      50,   //   50 ms
     100,   //  100 ms
     200,   //  200 ms
     250,   //  250 ms
     500,   //  500 ms
     750,   //  750 ms
    1000    // 1000 ms (1 second)
};
//---------------------------------------------------------------------------
TfrmSpriteType *frmSpriteType = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmSpriteType::TfrmSpriteType(TComponent* Owner)
    : TForm(Owner),
      m_pImageManager(NULL),
      m_bSkipReorder(false),
      m_iLastFrameIndex(0)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmSpriteType::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    m_pTabSheet = NULL;
    m_ImageEditor.TypeAddTab(PluginHandle, "Sprites", imgIcon->Picture->Bitmap, m_pTabSheet);
    if (true == SAFE_PTR(m_pTabSheet))
    {
        panSprites->Parent = m_pTabSheet;
        m_pTabSheet->OnHide = OnTabHide;
    }
    m_ImageEditor.TypeGetImageManager(PluginHandle, m_pImageManager);
    sbxFrames->DoubleBuffered = true;
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmSpriteType::Release(void)
{
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::OnTabHide(TObject *Sender)
{
    tmrAnimator->Enabled = false;
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::edtSpriteNameChange(TObject *Sender)
{
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::lstSpriteListClick(TObject *Sender)
{
    tbnFrameStopClick(NULL);
    // reset to the first frame
    int iFrames = 1;
    m_iLastFrameIndex = 0;
    edtFramesIndex->Value = iFrames;
    if (true == SAFE_PTR(m_pImageManager))
    {
        iFrames = m_pImageManager->GetFrameCount(g_sTypeSignature, lstSpriteList->ItemIndex);
        edtFramesIndex->Max = iFrames;
    }
    edtFramesIndex->Enabled  = iFrames > 1;
    lblFramesOf->Caption     = " of " + IntToStr(iFrames);
    ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstSpriteList->ItemIndex, 0);
    if (true == SAFE_PTR(pImage))
    {
        m_fScalarX                 = pImage->Palette->ScalarX;
        m_fScalarY                 = pImage->Palette->ScalarY;
        m_iPixelsHigh              = pImage->Palette->PixelsHighPerAttribute;
        edtSpriteHeight->Step      = m_iPixelsHigh;
        edtSpriteName->Text        = pImage->Name;
        edtSpriteWidth->Value      = pImage->Width;
        edtSpriteHeight->Value     = pImage->Height;
        chkSpriteMasked->Checked   = pImage->IsMasked;
        SetComboText(cmbSpriteFormat, pImage->Palette->Name);
        cmbType->ItemIndex         = m_pImageManager->GetSubType(g_sTypeSignature, lstSpriteList->ItemIndex);

        int i = 0;
        while (pImage)
        {
            pImage = m_pImageManager->GetImage(g_sTypeSignature, lstSpriteList->ItemIndex, i++);
            if (true == SAFE_PTR(pImage))
            {
                pImage->CanResize  = true;
            }
        }
    }
    // select the image and the first frame
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstSpriteList->ItemIndex, 0);
    // show the result
    UpdateButtons();
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::cmdSpriteAddClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iMinWidth = 8;
        int iIncWidth = 8;
        int iMinHeight = 8;
        int iIncHeight = 8;
        ZXPalette* pPalette = m_pImageManager->GetPalette(cmbSpriteFormat->Items->Strings[cmbSpriteFormat->ItemIndex]);
        if (SAFE_PTR(pPalette))
        {
            iMinWidth = pPalette->DefaultSpriteWidth;
            iIncWidth = pPalette->IncSpriteWidth;
            iMinHeight = pPalette->DefaultSpriteHeight;
            iIncHeight = pPalette->IncSpriteHeight;
        }
        if (edtSpriteWidth->Value % iIncWidth)
        {
            edtSpriteWidth->Value = (edtSpriteWidth->Value + iIncWidth) - (edtSpriteWidth->Value % iIncWidth);
        }
        if (edtSpriteWidth->Value < iMinWidth)
        {
            edtSpriteWidth->Value = iMinWidth;
        }
        if (edtSpriteHeight->Value % iIncHeight)
        {
            edtSpriteHeight->Value = (edtSpriteHeight->Value + m_iPixelsHigh) - (edtSpriteHeight->Value % m_iPixelsHigh);
        }
        if (edtSpriteHeight->Value < iMinHeight)
        {
            edtSpriteHeight->Value = iMinHeight;
        }
        int iIndex = m_pImageManager->AddImage(g_sTypeSignature,
                                               m_vPaletteSignatures[cmbSpriteFormat->ItemIndex],
                                               edtSpriteName->Text,
                                               edtSpriteWidth->Value,
                                               edtSpriteHeight->Value,
                                               chkSpriteMasked->Checked,
                                               NULL,
                                               true);
        tbnFrameStopClick(NULL);
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex, 0);
            m_pImageManager->GetImageList(g_sTypeSignature, lstSpriteList->Items);
            lstSpriteList->ItemIndex = iIndex;
            edtFramesIndex->Max      = 1;
            edtFramesIndex->Value    = 1;
            edtFramesIndex->Enabled  = false;
            lblFramesOf->Caption     = " of 0";
            lstSpriteListClick(NULL);
            UpdatePreview();
            UpdateButtons();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures)
{
    cmbSpriteFormat->Items->Clear();
    cmbSpriteFormat->Enabled = false;
    if (true == SAFE_PTR(pPalettes) && 0 < pPalettes->Count)
    {
        // filter out the required palettes
        for (int i = 0; i < pPalettes->Count; i++)
        {
            ZXPalette* pPalette = m_pImageManager->GetPalette(i);
            if (true == SAFE_PTR(pPalette) && pPalette->IsImageTypeSupported(itSprite))
            {
                cmbSpriteFormat->Items->Add(pPalette->Name);
                m_vPaletteSignatures.push_back(vSignatures[i]);
            }
        }
        cmbSpriteFormat->Enabled   = cmbSpriteFormat->Items->Count > 0;
        cmbSpriteFormat->ItemIndex = 0;
        /*cmbSpriteFormat->Items->AddStrings(pPalettes);
        m_vPaletteSignatures.assign(vSignatures.begin(), vSignatures.end());*/
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::cmdSpriteRemoveClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iAnswer = 0;
        m_ImageEditor.SystemMessageBox(mbtWarning,
                      "Do you want to Remove the sprite?",
                      "You are about to remove a sprite.",
                      "You have choosen to remove a sprite\n"
                      "This is a permanent operation and you will not be able to Undo this operation\n\n"
                      "Click\n"
                      "\tYes\tto Remove the sprite permanently\n"
                      "\tNo\tto cancel the operation and leave the sprite",
                      "No", "Yes", "", iAnswer );
        if (1 == iAnswer)
        {
            tbnFrameStopClick(NULL);
            if (true == SAFE_PTR(m_pImageManager))
            {
                if (true == m_pImageManager->RemoveImage(g_sTypeSignature, lstSpriteList->ItemIndex))
                {
                    lstSpriteList->Items->Strings[lstSpriteList->ItemIndex] = edtSpriteName->Text;
                    m_pImageManager->GetImageList(g_sTypeSignature, lstSpriteList->Items);
                    lstSpriteList->ItemIndex = -1;
                    edtSpriteName->Text = "";
                    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, -1, 0);
                    UpdatePreview();
                }
            }
            UpdateButtons();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::cmdSpriteCloneClick(TObject *Sender)
{
    tbnFrameStopClick(NULL);
    if (true == SAFE_PTR(m_pImageManager))
    {
        String sName = edtSpriteName->Text;
        while (true == m_pImageManager->DoesImageExist(g_sTypeSignature, sName))
        {
            sName = "Copy of " + sName;
        }
        int iIndex = m_pImageManager->CloneImage(g_sTypeSignature, sName, lstSpriteList->ItemIndex);
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex, 0);
            m_pImageManager->GetImageList(g_sTypeSignature, lstSpriteList->Items);
            lstSpriteList->ItemIndex = iIndex;
            UpdatePreview();
            UpdateButtons();
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::cmdSpriteRenameClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager) && -1 != lstSpriteList->ItemIndex)
    {
        if (true == m_pImageManager->RenameImage(g_sTypeSignature, lstSpriteList->ItemIndex, edtSpriteName->Text))
        {
            lstSpriteList->Items->Strings[lstSpriteList->ItemIndex] = edtSpriteName->Text;
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::UpdatePreview(void)
{
    static bool bUpdating = false;
    if (true == SAFE_PTR(m_pImageManager) && false == bUpdating)
    {
        bUpdating = true;
        ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstSpriteList->ItemIndex, edtFramesIndex->Value - 1);
        if (true == SAFE_PTR(pImage))
        {
            // draw the indicated frame
            panAnimationContainer->Height = pImage->Height;
            pbxSpritesFramesAnimation->Canvas->Brush->Color = clWhite;
            pbxSpritesFramesAnimation->Canvas->FillRect(pbxSpritesFramesAnimation->ClientRect);
            if (true == SAFE_PTR(pImage))
            {
                bool bMaskOn = pImage->MaskMode;
                m_pImageManager->SetMaskMode(false);
                pImage->Invalidate();
                float fImgX = pImage->ModeScaleX;
                float fImgY = pImage->ModeScaleY;
                pImage->ModeScaleX = pImage->Palette->ScalarX;
                pImage->ModeScaleY = pImage->Palette->ScalarY;
                pImage->Draw(pbxSpritesFramesAnimation->Canvas, 1);
                pImage->ModeScaleX = fImgX;
                pImage->ModeScaleY = fImgY;
                edtSpriteWidth->Value  = pImage->Width;
                edtSpriteHeight->Value = pImage->Height;
                m_pImageManager->SetMaskMode(bMaskOn);
            }

            panFrames->Height = pImage->Height + 26;
            int h = panAnimationContainer->Height + panFramesSpeed->Height + panFramesInfo->Height + tbnSpriteFrames->Height + panFrames->Height + 26;
            grpFrames->Height = h;
            grpFrames->Constraints->MaxHeight = h;
            grpFrames->Constraints->MinHeight = h;
            panSprites->Height = grpFrames->Top + grpFrames->Height + 8;
            // draw the frames of the sprite
            int iFrames = m_pImageManager->GetFrameCount(g_sTypeSignature, lstSpriteList->ItemIndex);
            pbxSpritePreview->Width  = 4 + ((pImage->Width  + 4) * iFrames);
            pbxSpritePreview->Height =       pImage->Height + 8;
            pbxSpritePreview->Canvas->Brush->Color = clWhite;
            pbxSpritePreview->Canvas->FillRect(pbxSpritePreview->ClientRect);
            int X = 4;
            for (int f = 0; f < iFrames; f++)
            {
                ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstSpriteList->ItemIndex, f);
                if (f == edtFramesIndex->Value - 1)
                {
                    pbxSpritePreview->Canvas->Brush->Color = clRed;
                    TRect SelectRect(X - 4, 0, X + pImage->Width + 4, pImage->Height + 8);
                    pbxSpritePreview->Canvas->FillRect(SelectRect);
                }
                if (true == SAFE_PTR(pImage))
                {
                    pImage->Invalidate();
                    float fImgX = pImage->ModeScaleX;
                    float fImgY = pImage->ModeScaleY;
                    pImage->ModeScaleX = pImage->Palette->ScalarX;
                    pImage->ModeScaleY = pImage->Palette->ScalarY;
                    pImage->ReDraw();
                    pImage->Draw(pbxSpritePreview->Canvas, 1, X, 4);
                    pImage->ModeScaleX = fImgX;
                    pImage->ModeScaleY = fImgY;
                    X += 4;
                    X += pImage->Width;
                }
            }
        }
        bUpdating = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::UpdateButtons(void)
{
    int iFrames = m_pImageManager->GetFrameCount(g_sTypeSignature, lstSpriteList->ItemIndex);
    cmdSpriteAdd->Enabled      = false;
    cmdSpriteRemove->Enabled   = false;
    cmdSpriteRename->Enabled   = false;
    cmdSpriteClone->Enabled    = false;
    bool bSelected = lstSpriteList->ItemIndex != -1;
    tbnFramesFirst->Enabled    = bSelected && !tmrAnimator->Enabled && iFrames > 1;
    tbnFramesPrevious->Enabled = bSelected && !tmrAnimator->Enabled && iFrames > 1;
    tbnFramePlay->Enabled      = bSelected && !tmrAnimator->Enabled && iFrames > 1;
    tbnFrameStop->Enabled      = bSelected &&  tmrAnimator->Enabled && iFrames > 1;
    tbnFramesNext->Enabled     = bSelected && !tmrAnimator->Enabled && iFrames > 1;
    tbnFramesLast->Enabled     = bSelected && !tmrAnimator->Enabled && iFrames > 1;
    tbnFramesRepeat->Enabled   = bSelected && !tmrAnimator->Enabled && iFrames > 1;
    tbnFramesInsert->Enabled   = bSelected && !tmrAnimator->Enabled;
    tbnFramesRemove->Enabled   = bSelected && !tmrAnimator->Enabled && iFrames > 1;
    tbnFramesClone->Enabled    = bSelected && !tmrAnimator->Enabled;
    if (true == SAFE_PTR(m_pImageManager))
    {
        cmdSpriteAdd->Enabled     = edtSpriteName->Text != "";
        cmdSpriteAdd->Enabled    &= !m_pImageManager->DoesImageExist(g_sTypeSignature, edtSpriteName->Text);
        cmdSpriteRename->Enabled  = cmdSpriteAdd->Enabled && -1 != lstSpriteList->ItemIndex;
        cmdSpriteRemove->Enabled  = 0 != m_pImageManager->GetImageCount(g_sTypeSignature);
        cmdSpriteClone->Enabled   = 0 != m_pImageManager->GetImageCount(g_sTypeSignature) && -1 != lstSpriteList->ItemIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::RefreshList(void)
{
    lstSpriteList->ItemIndex = -1;
    m_pImageManager->GetImageList(g_sTypeSignature, lstSpriteList->Items);
    if (0 < lstSpriteList->Items->Count)
    {
        lstSpriteList->ItemIndex = 0;
    }
    UpdatePreview();
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::pbxSpritePreviewPaint(TObject *Sender)
{
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tbnFramesInsertClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstSpriteList->ItemIndex, 0);
        if (true == SAFE_PTR(pImage))
        {
            int iIndex = m_pImageManager->AddImage(g_sTypeSignature,
                                                   pImage->Palette->Name,
                                                   edtSpriteName->Text,
                                                   edtSpriteWidth->Value,
                                                   edtSpriteHeight->Value,
                                                   pImage->IsMasked);
            if (-1 != iIndex)
            {
                m_bSkipReorder = true;
                int iFrames = m_pImageManager->GetFrameCount(g_sTypeSignature, lstSpriteList->ItemIndex);
                m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex, iFrames - 1);
                edtFramesIndex->Max      = iFrames;
                edtFramesIndex->Enabled  = iFrames > 1;
                edtFramesIndex->Value    = iFrames;
                lblFramesOf->Caption     = " of " + IntToStr(iFrames);
                m_bSkipReorder = false;
            }
            UpdateButtons();
            UpdatePreview();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tbnFramesRemoveClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iAnswer = 0;
        m_ImageEditor.SystemMessageBox(mbtWarning,
                      "Do you want to Remove the frame from the sprite?",
                      "You are about to remove a frame from the sprite.",
                      "You have choosen to remove a frame from the sprite\n"
                      "This is a permanent operation and you will not be able to Undo this operation\n\n"
                      "Click\n"
                      "\tYes\tto Remove the frame permanently\n"
                      "\tNo\tto cancel the operation and leave the frame in the sprite",
                      "No", "Yes", "", iAnswer );
        if (1 == iAnswer)
        {
            if (true == m_pImageManager->RemoveImage(g_sTypeSignature, lstSpriteList->ItemIndex, edtFramesIndex->Value - 1))
            {
                int iFrame = edtFramesIndex->Value;
                int iFrames = m_pImageManager->GetFrameCount(g_sTypeSignature, lstSpriteList->ItemIndex);
                edtFramesIndex->Max      = iFrames;
                edtFramesIndex->Value    = std::min(iFrame, iFrames);
                edtFramesIndex->Enabled  = iFrames > 1;
                lblFramesOf->Caption     = " of " + IntToStr(iFrames);
                m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstSpriteList->ItemIndex, edtFramesIndex->Value - 1);
            }
            UpdatePreview();
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tbnFramesCloneClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iIndex = m_pImageManager->CloneImage(g_sTypeSignature,
                                                 edtSpriteName->Text,
                                                 lstSpriteList->ItemIndex,
                                                 edtFramesIndex->Value - 1);
        if (-1 != iIndex)
        {
            int iFrames = m_pImageManager->GetFrameCount(g_sTypeSignature, lstSpriteList->ItemIndex);
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex, iFrames - 1);
            edtFramesIndex->Max      = iFrames;
            edtFramesIndex->Enabled  = iFrames > 1;
            edtFramesIndex->Value    = iFrames;
            lblFramesOf->Caption     = " of " + IntToStr(iFrames);
        }
        UpdateButtons();
        UpdatePreview();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tbnFramesFirstClick(TObject *Sender)
{
    m_bSkipReorder = true;
    edtFramesIndex->Value = 1;
    m_bSkipReorder = false;
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstSpriteList->ItemIndex, 0);
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tbnFramesPreviousClick(TObject *Sender)
{
    m_bSkipReorder = true;
    if (false == tbnFramesRepeat->Down)
    {
        edtFramesIndex->Value = std::max(1, edtFramesIndex->Value - 1);
    }
    else
    {
        int iFrame  = edtFramesIndex->Value - 1;
        int iFrames = edtFramesIndex->Max;
        int iNewFrame = 1 + ((iFrames + iFrame - 1) % iFrames);
        edtFramesIndex->Value = std::max(1, iNewFrame);
    }
    m_bSkipReorder = false;
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstSpriteList->ItemIndex, edtFramesIndex->Value - 1);
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tbnFramePlayClick(TObject *Sender)
{
    tmrAnimator->Interval = g_iSpeeds[slrFramesSpeed->Position];
    tmrAnimator->Enabled = true;
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tbnFrameStopClick(TObject *Sender)
{
    tbnFrameStop->Down = true;
    tmrAnimator->Enabled = false;
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tbnFramesNextClick(TObject *Sender)
{
    m_bSkipReorder = true;
    int iFrames = m_pImageManager->GetFrameCount(g_sTypeSignature, lstSpriteList->ItemIndex);
    if (false == tbnFramesRepeat->Down)
    {
        edtFramesIndex->Value = std::min(iFrames, edtFramesIndex->Value + 1);
    }
    else
    {
        int iFrame  = edtFramesIndex->Value - 1;
        int iFrames = edtFramesIndex->Max;
        int iNewFrame = 1 + ((iFrames + iFrame + 1) % iFrames);
        edtFramesIndex->Value = std::min(iFrames, iNewFrame);
    }
    m_bSkipReorder = false;
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstSpriteList->ItemIndex, edtFramesIndex->Value - 1);
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tbnFramesLastClick(TObject *Sender)
{
    m_bSkipReorder = true;
    int iFrames = m_pImageManager->GetFrameCount(g_sTypeSignature, lstSpriteList->ItemIndex);
    edtFramesIndex->Value = iFrames;
    m_bSkipReorder = false;
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstSpriteList->ItemIndex, iFrames - 1);
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::pbxSpritePreviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    // select the frame of the sprite
    int iFrame = (X  / (edtSpriteWidth->Value + 4));// + 1;
    SelectFrame(iFrame);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::SelectFrame(int iFrame)
{
    m_bSkipReorder = true;
    edtFramesIndex->Value = iFrame + 1;
    m_bSkipReorder = false;
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstSpriteList->ItemIndex, iFrame);
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::tmrAnimatorTimer(TObject *Sender)
{
    int iFrame  = edtFramesIndex->Value - 1;
    int iFrames = edtFramesIndex->Max;
    int iNewFrame = tbnFramesRepeat->Down ? (1 + ((iFrames + iFrame + 1) % iFrames)) : iFrame + 2;
    if (iNewFrame <= iFrames)
    {
        m_bSkipReorder = true;
        edtFramesIndex->Value = iNewFrame;
        if (true == chkSpriteShowInEditor->Checked)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, lstSpriteList->ItemIndex, edtFramesIndex->Value - 1);
        }
        m_iLastFrameIndex = edtFramesIndex->Value - 1;
        // show the result
        UpdatePreview();
        m_bSkipReorder = false;
    }
    else
    {
        tbnFrameStopClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::slrFramesSpeedChange(TObject *Sender)
{
    tmrAnimator->Interval = g_iSpeeds[slrFramesSpeed->Position];
    lblFramesSpeed->Caption = IntToStr(g_iSpeeds[slrFramesSpeed->Position]) + " ms";
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::SetComboText(TComboBox* pComboBox, String sText)
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
void __fastcall TfrmSpriteType::cmbSpriteFormatChange(TObject *Sender)
{
    ZXPalette* pPalette = m_pImageManager->GetPalette(cmbSpriteFormat->Items->Strings[cmbSpriteFormat->ItemIndex]);
    if (true == SAFE_PTR(pPalette))
    {
        edtSpriteWidth->Value = pPalette->DefaultSpriteWidth;
        edtSpriteHeight->Value = pPalette->DefaultSpriteHeight;
        edtSpriteWidth->Step = pPalette->IncSpriteWidth;
        edtSpriteHeight->Step = pPalette->IncSpriteHeight;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSpriteType::cmbTypeChange(TObject *Sender)
{
    m_pImageManager->SetSubType(g_sTypeSignature, lstSpriteList->ItemIndex, cmbType->ItemIndex);
}
//---------------------------------------------------------------------------

