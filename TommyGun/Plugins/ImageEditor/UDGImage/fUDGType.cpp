#pragma link "cspin"
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
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageTypes;
//---------------------------------------------------------------------------
const   String  g_sMonochromePaletteSignature   = "Monochrome";
const   int     g_iCharacters                   = 21;
//---------------------------------------------------------------------------
TfrmUDGType *frmUDGType = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmUDGType::TfrmUDGType(TComponent* Owner)
    : TForm(Owner)
    , m_iActiveCharacter(-1)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmUDGType::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    TTabSheet* pTabSheet = NULL;
    m_ImageEditor.TypeAddTab(PluginHandle, "UDG", imgIcon->Picture->Bitmap, pTabSheet);
    if (true == SAFE_PTR(pTabSheet))
    {
        panUDGs->Parent = pTabSheet;
    }
    m_ImageEditor.TypeGetImageManager(PluginHandle, m_pImageManager);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmUDGType::Release(void)
{
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures)
{
    std::vector<String>::iterator it = std::find(vSignatures.begin(), vSignatures.end(), g_sMonochromePaletteSignature);
    bool bFound = it != vSignatures.end();
    lblPaletteWarning->Visible               =!bFound;
    edtUDGName->Enabled                      = bFound;
    panUserDefinedGraphicsButtons->Enabled   = bFound;
    cmdUserDefinedGraphicsSetAdd->Enabled    = bFound;
    cmdUserDefinedGraphicsSetRemove->Enabled = false;
    cmdUserDefinedGraphicsSetClone->Enabled  = false;
    cmdUserDefinedGraphicsSetRename->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::edtUDGNameChange(TObject *Sender)
{
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::cmdUserDefinedGraphicsSetAddClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iIndex;
        for (int i = 0; i < g_iCharacters; i++)
        {
            String sName = edtUDGName->Text + "_" + AnsiString::StringOfChar('A' + i, 1);
            iIndex = m_pImageManager->AddImage(g_sTypeSignature,
                                               g_sMonochromePaletteSignature,
                                               sName,
                                               8,
                                               8,
                                               false);
        }
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex / g_iCharacters, 0);
            TStringList* pStrings = new TStringList();
            m_pImageManager->GetImageList(g_sTypeSignature, pStrings);
            lstUDGList->Items->Clear();
            for (int i = 0; i < pStrings->Count; i += g_iCharacters)
            {
                lstUDGList->Items->Add(pStrings->Strings[i].SubString(1, pStrings->Strings[i].Length() - 2));                
            }
            lstUDGList->ItemIndex = iIndex / g_iCharacters;
            SAFE_DELETE(pStrings);
            UpdatePreview();
            UpdateButtons();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::cmdUserDefinedGraphicsSetRemoveClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        int iAnswer = 0;
        m_ImageEditor.SystemMessageBox(mbtWarning,
                      "Do you want to Remove a UDG set?",
                      "You are about to remove a UDG set.",
                      "You have choosen to remove a UDG set\n"
                      "This is a permanent operation and you will not be able to Undo this operation\n\n"
                      "Click\n"
                      "\tYes\tto Remove the UDG set permanently\n"
                      "\tNo\tto cancel the operation and leave the UDG set",
                      "No", "Yes", "", iAnswer );
        if (1 == iAnswer)
        {
            for (int i = 0; i < g_iCharacters; i++)
            {
                m_pImageManager->RemoveImage(g_sTypeSignature, lstUDGList->ItemIndex * g_iCharacters);
            }
            RefreshList();
            lstUDGList->ItemIndex = -1;
            edtUDGName->Text = "";
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, -1, 0);
            UpdatePreview();
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::cmdUserDefinedGraphicsSetCloneClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager))
    {
        String sName = edtUDGName->Text;
        while (true == m_pImageManager->DoesImageExist(g_sTypeSignature, sName + "_A"))
        {
            sName = "Copy of " + sName;
        }
        int iIndex;
        for (int i = 0; i < g_iCharacters; i++)
        {
            String sCloneName = sName + "_" + AnsiString::StringOfChar('A' + i, 1);
            int iCharacter = (lstUDGList->ItemIndex * g_iCharacters) + i;
            iIndex = m_pImageManager->CloneImage(g_sTypeSignature, sCloneName, iCharacter);
        }
        if (-1 != iIndex)
        {
            m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iIndex / g_iCharacters, 0);
            RefreshList();
            lstUDGList->ItemIndex = iIndex / g_iCharacters;
            UpdatePreview();
            UpdateButtons();
        }
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::cmdUserDefinedGraphicsSetRenameClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImageManager) && -1 != lstUDGList->ItemIndex)
    {
        for (int i = 0; i < g_iCharacters; i++)
        {
            int iChar = (lstUDGList->ItemIndex * g_iCharacters) + i;
            String sName = edtUDGName->Text + "_" + AnsiString::StringOfChar('A' + i, 1);
            m_pImageManager->RenameImage(g_sTypeSignature, iChar, sName);
        }
        lstUDGList->Items->Strings[lstUDGList->ItemIndex] = edtUDGName->Text;
    }
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::spdUserDefinedGraphicsAClick(TObject *Sender)
{
    // select an image
    TSpeedButton* pButton = dynamic_cast<TSpeedButton*>(Sender);
    if (true == SAFE_PTR(pButton))
    {
        m_iActiveCharacter = pButton->Tag;
        int iCharacter = (lstUDGList->ItemIndex * g_iCharacters) + m_iActiveCharacter;
        m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iCharacter, 0);
        UpdateButtons();
        UpdatePreview();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::UpdatePreview(void)
{
    int s = spnScale->Value * 8;
    pbxUserDefinedGraphics->Height = ((g_iCharacters / (pbxUserDefinedGraphics->Width / s)) + 1) * s;
    if (lstUDGList->Items->Count && lstUDGList->ItemIndex != -1)
    {
        pbxUserDefinedGraphics->Canvas->Brush->Color = clBlack;
        pbxUserDefinedGraphics->Canvas->FillRect(pbxUserDefinedGraphics->ClientRect);
        if (true == SAFE_PTR(m_pImageManager))
        {
            int cx = 0;
            int cy = 0;
            int s = spnScale->Value;
            for (int i = 0; i < g_iCharacters; i++)
            {
                int iCharacter = (lstUDGList->ItemIndex * g_iCharacters) + i;
                ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, iCharacter, 0);
                if (true == SAFE_PTR(pImage))
                {
                    pImage->Invalidate();
                    pImage->ReDraw();
                    pImage->Invalidate();
                    if (cx + (pImage->Width * s) > pbxUserDefinedGraphics->Width)
                    {
                        cx = 0;
                        cy += pImage->Height * s;
                    }
                    pImage->Draw(pbxUserDefinedGraphics->Canvas, s, cx, cy);
                    if (i == m_iActiveCharacter)
                    {
                        TRect TheRect = Rect(cx, cy, cx + (pImage->Width * s), cy + (pImage->Height * s));
                        pbxUserDefinedGraphics->Canvas->Brush->Color = clRed;
                        pbxUserDefinedGraphics->Canvas->FrameRect(TheRect);
                    }
                    cx += pImage->Width * s;
                }
            }
        }
    }
    else
    {
        pbxUserDefinedGraphics->Canvas->Brush->Color = clWhite;
        pbxUserDefinedGraphics->Canvas->FillRect(pbxUserDefinedGraphics->ClientRect);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::UpdateButtons(void)
{
    panUserDefinedGraphicsButtons->Enabled    = false;
    cmdUserDefinedGraphicsSetAdd->Enabled     = false;
    cmdUserDefinedGraphicsSetRemove->Enabled  = false;
    cmdUserDefinedGraphicsSetRename->Enabled  = false;
    cmdUserDefinedGraphicsSetClone->Enabled   = false;
    spnScale->Enabled                         = false;
    if (true == SAFE_PTR(m_pImageManager))
    {
        panUserDefinedGraphicsButtons->Enabled    = lstUDGList->ItemIndex != -1;
        spnScale->Enabled                         = lstUDGList->ItemIndex != -1;
        cmdUserDefinedGraphicsSetAdd->Enabled     = edtUDGName->Text.Trim() != "";
        if (cmdUserDefinedGraphicsSetAdd->Enabled)
        {
            cmdUserDefinedGraphicsSetAdd->Enabled&= !m_pImageManager->DoesImageExist(g_sTypeSignature, edtUDGName->Text + "_A");
        }
        cmdUserDefinedGraphicsSetRename->Enabled  = cmdUserDefinedGraphicsSetAdd->Enabled && -1 != lstUDGList->ItemIndex;
        cmdUserDefinedGraphicsSetRemove->Enabled  = 0 != m_pImageManager->GetImageCount(g_sTypeSignature);
        cmdUserDefinedGraphicsSetClone->Enabled   = edtUDGName->Text.Trim() != "" && 0 != m_pImageManager->GetImageCount(g_sTypeSignature) && -1 != lstUDGList->ItemIndex;
        ZXImage* pImage = m_pImageManager->GetImage(g_sTypeSignature, lstUDGList->ItemIndex, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::pbxUserDefinedGraphicsPaint(TObject *Sender)
{
    UpdatePreview();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::lstUDGListClick(TObject *Sender)
{
    // select character A of the UDG set
    if (lstUDGList->ItemIndex >= 0)
    {
        edtUDGName->Text = lstUDGList->Items->Strings[lstUDGList->ItemIndex];
    }
    if (m_iActiveCharacter == -1)
    {
        m_iActiveCharacter = 0;
    }
    UpdatePreview();
    spdUserDefinedGraphicsAClick(spdUserDefinedGraphicsA);
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::RefreshList(void)
{
    lstUDGList->ItemIndex = -1;
    TStringList* pStrings = new TStringList();
    m_pImageManager->GetImageList(g_sTypeSignature, pStrings);
    lstUDGList->Items->Clear();
    for (int i = 0; i < pStrings->Count; i += g_iCharacters)
    {
        lstUDGList->Items->Add(pStrings->Strings[i].SubString(1, pStrings->Strings[i].Length() - 2));
    }
    if (0 < lstUDGList->Items->Count)
    {
        lstUDGList->ItemIndex = 0;
    }
    SAFE_DELETE(pStrings);
    UpdatePreview();
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::pbxUserDefinedGraphicsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    int px = pbxUserDefinedGraphics->Width;
    int cw = 8 * spnScale->Value;
    int ch = 8 * spnScale->Value;
    int cpw = px / cw;
    m_iActiveCharacter = std::max(0, std::min(g_iCharacters-1, (X / cw) + ((Y / ch) * cpw)));
    int iCharacter = (lstUDGList->ItemIndex * g_iCharacters) + m_iActiveCharacter;
    m_ImageEditor.TypeSelectImage(m_PluginHandle, g_sTypeSignature, iCharacter, 0);
    UpdateButtons();
    UpdatePreview();

}
//---------------------------------------------------------------------------
void __fastcall TfrmUDGType::spnScaleChange(TObject *Sender)
{
    UpdatePreview();
}
//---------------------------------------------------------------------------

