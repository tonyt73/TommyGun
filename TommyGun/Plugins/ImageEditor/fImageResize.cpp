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
#pragma resource "*.dfm"
#pragma "KSpinEdit.obj"
//-- NAMESPACES -------------------------------------------------------------
using namespace Scorpio;
using namespace Logging;
using namespace ImageEditor;
//-- VCL FORM OBJECT --------------------------------------------------------
TfrmImageResize *frmImageResize = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmImageResize::TfrmImageResize(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TfrmImageResize::Execute(ZXImage* pImage)
{
    m_pImage                    = pImage;
    m_bNoUpdate                 = true;
    lblCurrentWidth->Caption    = IntToStr(pImage->Width);
    lblCurrentHeight->Caption   = IntToStr(pImage->Height);
    edtNewWidth->Value          = pImage->Width;
    edtNewHeight->Value         = pImage->Height;
    m_bNoUpdate                 = false;
    Update();
    ShowModal();
    m_iLeft                     = edtLeft->Value;
    m_iTop                      = edtTop->Value;
    m_iWidth                    = edtNewWidth->Value;
    m_iHeight                   = edtNewHeight->Value;
    return (ModalResult == mrOk);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageResize::Update(void)
{
    if (m_bNoUpdate) return;

    edtLeft->Min        = -(m_pImage->Width  - 1);
    edtLeft->Max        =  edtNewWidth->Value - 1;
    edtRight->Min       =  1;
    edtRight->Max       =  edtNewWidth->Value  + m_pImage->Width  - 1;
    edtTop->Min         = -(m_pImage->Height - 1);
    edtTop->Max         =  edtNewHeight->Value - 1;
    edtBottom->Min      =  1;
    edtBottom->Max      =  edtNewHeight->Value + m_pImage->Height - 1;

    m_bNoUpdate = true;
    lblLeft->Enabled    = radHCustom->Checked;
    lblRight->Enabled   = radHCustom->Checked;
    edtLeft->Enabled    = radHCustom->Checked;
    edtRight->Enabled   = radHCustom->Checked;
    if (radHLeft->Checked)
    {
        edtLeft->Value  = 0;
        edtRight->Value = edtLeft->Value      + m_pImage->Width;
    }
    else if (radHCentre->Checked)
    {
        edtLeft->Value  = (edtNewWidth->Value - m_pImage->Width) / 2;
        edtRight->Value =  edtLeft->Value     + m_pImage->Width;
    }
    else if (radHRight->Checked)
    {
        edtLeft->Value  = edtNewWidth->Value  - m_pImage->Width;
        edtRight->Value = edtLeft->Value      + m_pImage->Width;
    }
    else
    {
        edtLeftChange(NULL);
    }

    lblTop->Enabled     = radVCustom->Checked;
    lblBottom->Enabled  = radVCustom->Checked;
    edtTop->Enabled     = radVCustom->Checked;
    edtBottom->Enabled  = radVCustom->Checked;
    if (radVTop->Checked)
    {
        edtTop->Value   = 0;
        edtBottom->Value= edtTop->Value        + m_pImage->Height;
    }
    else if (radVCentre->Checked)
    {
        edtTop->Value   = (edtNewHeight->Value - m_pImage->Height) / 2;
        edtBottom->Value=  edtTop->Value       + m_pImage->Height;
    }
    else if (radVBottom->Checked)
    {
        edtTop->Value   = edtNewHeight->Value - m_pImage->Height;
        edtBottom->Value= edtTop->Value       + m_pImage->Height;
    }
    else
    {
        edtTopChange(NULL);
    }
    m_bNoUpdate = false;
    UpdateSliders();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageResize::edtLeftChange(TObject *Sender)
{
    if (m_bNoUpdate) return;
    m_bNoUpdate = true;
    edtRight->Value = edtLeft->Value + m_pImage->Width;
    m_bNoUpdate = false;
    UpdateSliders();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageResize::edtRightChange(TObject *Sender)
{
    if (m_bNoUpdate) return;
    m_bNoUpdate = true;
    edtLeft->Value = edtRight->Value - m_pImage->Width;
    m_bNoUpdate = false;
    UpdateSliders();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageResize::edtTopChange(TObject *Sender)
{
    if (m_bNoUpdate) return;
    m_bNoUpdate = true;
    edtBottom->Value = edtTop->Value + m_pImage->Height;
    m_bNoUpdate = false;
    UpdateSliders();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageResize::edtBottomChange(TObject *Sender)
{
    if (m_bNoUpdate) return;
    m_bNoUpdate = true;
    edtTop->Value = edtBottom->Value - m_pImage->Width;
    m_bNoUpdate = false;
    UpdateSliders();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageResize::UpdateSliders(void)
{
    // work out the width
    if (edtNewWidth->Value == m_pImage->Width)
    {
        // center both boxes
        panTopBox->Left   = 66;
        panTopBox->Width  = 66;
    }
    if (edtNewHeight->Value == m_pImage->Height)
    {
        // center both boxes
        panTopBox->Top    = 66;
        panTopBox->Height = 66;
    }
    if (edtNewWidth->Value > m_pImage->Width)
    {
        // center the new box (blue) top box is the current
        panTopBox->Color  = clRed;
        panBotBox->Color  = clBlue;
        // work out the current boxes width in regard to the new width
        float new2box = 66.f / (float)edtNewWidth->Value;
        float ratio = (float)m_pImage->Width / (float)edtNewWidth->Value;
        panTopBox->Left   = panBotBox->Left + (float)edtLeft->Value * new2box;
        panTopBox->Width  = panBotBox->Width * ratio;
        // work out the height
        new2box = 66.f / (float)edtNewHeight->Value;
        ratio = (float)m_pImage->Height / (float)edtNewHeight->Value;
        panTopBox->Top    = panBotBox->Top + (float)edtTop->Value * new2box;
        panTopBox->Height = panBotBox->Height * ratio;
    }
    else if (edtNewWidth->Value < m_pImage->Width)
    {
        // center the current box (red) top box is the new box
        panTopBox->Color  = clBlue;
        panBotBox->Color  = clRed;
        float cur2box = 66.f / (float)m_pImage->Width;
        float ratio = (float)edtNewWidth->Value / (float)m_pImage->Width;
        panTopBox->Left   = panBotBox->Left + (float)-edtLeft->Value * cur2box;
        panTopBox->Width  = panBotBox->Width * ratio;
        // work out the height
        cur2box = 66.f / (float)m_pImage->Height;
        ratio = (float)edtNewHeight->Value / (float)m_pImage->Height;
        panTopBox->Top    = panBotBox->Top + (float)-edtTop->Value * cur2box;
        panTopBox->Height = panBotBox->Height * ratio;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageResize::radHLeftClick(TObject *Sender)
{
    Update();
}
//---------------------------------------------------------------------------





