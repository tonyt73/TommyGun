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
#pragma link "KRegistry"
#pragma link "KSpinEdit"
#pragma link "KIconButton"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmEditorProperties *frmEditorProperties = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmEditorProperties::TfrmEditorProperties(TComponent* Owner, ZXFileManager& FileManager)
: TForm(Owner)
, m_FileManager(FileManager)
, m_ForeColor(clWhite)
, m_BackColor(clBlack)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::FormCreate(TObject *Sender)
{
    m_ForePanel = panColoursWhite;
    m_BackPanel = panColoursBlack;
    pgcProperties->TabIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::FormShow(TObject *Sender)
{
    if (cmbColoursSpeedSettings->Items->Count == 0)
    {
        ZXColorSetting* Setting = NULL;
        int i = 0;

        while (g_EditorSettings.GetSetting(i, Setting))
        {
            cmbColoursSpeedSettings->Items->Add(Setting->Name);
        }
    }
    GetFonts();

    ReadGeneral();
    ReadDisplay();
    ReadKeyMappings();
    ReadColours();

    cmbColoursSpeedSettings->ItemIndex = 0;
    cmbColoursSpeedSettingsChange(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::cmdApplyClick(TObject *Sender)
{
    ApplyGeneral();
    ApplyDisplay();
    ApplyKeyMappings();
    ApplyColours();
    g_EditorSettings.Write();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::cmdRestoreDefaultsClick(TObject *Sender)
{
    int iAnswer;
    Message
    (
        mbtQuestion,
        "Are you sure you want to RESET your settings?",
        "Resetting the settings will lose your changes.",
        "You are about to RESET your changes back to the system defaults.\n"
        "This means you WILL LOSE your current settings.\n\n"
        "Click,\n"
        "\tYes\tIf you have stuffed up the settings and want to restore order.\n"
        "\tNo\tIf you think you can still stuff things up furhter."
        "\n\n*** You will still need to click APPLY to make the changes permanent! ***",
        "No",
        "Yes",
        "",
        iAnswer
    );
    if (iAnswer == 1)
    {
        g_EditorSettings.Reset();
        ReadGeneral();
        ReadDisplay();
        ReadKeyMappings();
        ReadColours();
        cmbColoursSpeedSettings->ItemIndex = 0;
        cmbColoursSpeedSettingsChange(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::cmbColoursSpeedSettingsChange(TObject *Sender)
{
    ZXColorSetting* Setting = NULL;
    if (g_EditorSettings.GetSetting(cmbColoursSpeedSettings->ItemIndex, Setting))
    {
        //synEdit->Lines->Assign(Setting->Strings);
        //synEdit->Highlighter = Setting->Highlighter;

        lstColoursElements->Items->Clear();
        TColorSetting ColorSetting;
        int i = 0;

        while (Setting->GetSetting(i++, ColorSetting))
        {
            lstColoursElements->Items->Add(ColorSetting.Name);
        }
        lstColoursElements->ItemIndex = 0;
        lstColoursElementsClick(NULL);
    }
    ReadColours();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::lstColoursElementsClick(TObject *Sender)
{
    ZXColorSetting* Setting = NULL;
    if (g_EditorSettings.GetSetting(cmbColoursSpeedSettings->ItemIndex, Setting))
    {
        TColorSetting ColorSetting;
        if (Setting->GetSetting(lstColoursElements->ItemIndex, ColorSetting))
        {
            UpdateColors(ColorSetting.ForeColor, ColorSetting.BackColor);
            UpdateFontStyles(ColorSetting);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::ApplyGeneral(void)
{
    g_EditorSettings.TabsToSpaces       = chkGeneralTabsToSpaces->Checked;
    g_EditorSettings.TabWidth           = edtGeneralTabWidth->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::ApplyDisplay(void)
{
    g_EditorSettings.LineNumbers        = chkDisplayLineNumbers->Checked;
    g_EditorSettings.Font               = cmbDisplayFonts->Items->Strings[cmbDisplayFonts->ItemIndex];
    g_EditorSettings.FontSize           = edtDisplayFontSize->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::ApplyKeyMappings(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::ApplyColours(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::ReadGeneral(void)
{
    chkGeneralTabsToSpaces->Checked         = g_EditorSettings.TabsToSpaces;
    edtGeneralTabWidth->Value               = g_EditorSettings.TabWidth;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::ReadDisplay(void)
{
    chkDisplayLineNumbers->Checked          = g_EditorSettings.LineNumbers;
    edtDisplayFontSize->Value               = g_EditorSettings.FontSize; 

    Select(cmbDisplayFonts, g_EditorSettings.Font);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::ReadKeyMappings(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::ReadColours(void)
{
        
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::panDisplayGutterStartColourClick(TObject *Sender)
{
    TPanel* panel = dynamic_cast<TPanel*>(Sender);
    if (SAFE_PTR(panel))
    {
        dlgColor->Color = panel->Color;
        if (dlgColor->Execute())
        {
            panel->Color = dlgColor->Color;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::Select(TComboBox* pComboBox, String sText)
{
    if (SAFE_PTR(pComboBox))
    {
        for (int i = 0; i < pComboBox->Items->Count; ++i)
        {
            if (pComboBox->Items->Strings[i] == sText)
            {
                pComboBox->ItemIndex = i;
                return;
            }
        }
    }
    pComboBox->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::cmbDisplayFontsChange(TObject *Sender)
{
    panDisplayFontSample->Font->Name = cmbDisplayFonts->Items->Strings[cmbDisplayFonts->ItemIndex];
    panDisplayFontSample->Font->Size = edtDisplayFontSize->Value;
    panDisplayFontSample->Font->Pitch= fpFixed;
    //synEdit->Font->Name = cmbDisplayFonts->Items->Strings[cmbDisplayFonts->ItemIndex];
    //synEdit->Font->Size = edtDisplayFontSize->Value;
    //synEdit->Font->Pitch= fpFixed;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::GetFonts(void)
{
    /*bool bValue = true;
    regScorpio->Read("CodeEditor\\Display", "NoTrueTypeFonts", bValue);
    chkDisplayFixedFontsOnly->Checked = bValue;

    if (bValue)
    {
        TFont* font = new TFont;
        font->Size = 10;
        for (int i = 0; i < Screen->Fonts->Count; ++i)
        {
            font->Name = Screen->Fonts->Strings[i];
            font->Pitch = fpFixed;
            font->Charset = ANSI_CHARSET;
            if (font->Pitch == fpFixed && Screen->Fonts->Strings[i] == font->Name)
            {
                cmbDisplayFonts->Items->Add(font->Name);
            }
        }
    }
    else*/
    {
        cmbDisplayFonts->Items->Assign(Screen->Fonts);
    }
    Select(cmbDisplayFonts, "Courier New");
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::chkDisplayFixedFontsOnlyClick(TObject *Sender)
{
    GetFonts();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::UpdateColors(TColor ForeColor, TColor BackColor)
{
    m_ForePanel->Caption = "";
    m_BackPanel->Caption = "";

    if (ForeColor == BackColor)
    {
        m_ForePanel = FindColor(ForeColor);
        m_ForePanel->Caption = "FB";
        m_BackPanel = m_ForePanel;
    }
    else
    {
        m_ForePanel = FindColor(ForeColor);
        m_ForePanel->Caption = "FG";

        m_BackPanel = FindColor(BackColor);
        m_BackPanel->Caption = "BG";
    }
    m_ForeColor = m_ForePanel->Color;
    m_BackColor = m_BackPanel->Color;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::UpdateFontStyles(const TColorSetting& ColorSetting)
{
    chkColoursFontBold->Checked = ColorSetting.FontStyle.Contains(fsBold);
    chkColoursFontItalic->Checked = ColorSetting.FontStyle.Contains(fsItalic);
    chkColoursFontUnderline->Checked = ColorSetting.FontStyle.Contains(fsUnderline);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::panColoursBlackMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    TPanel* Panel = dynamic_cast<TPanel*>(Sender);
    if (SAFE_PTR(Panel))
    {
        if (Button == mbLeft)
        {
            m_ForeColor = Panel->Color;
        }
        if (Button == mbRight)
        {
            m_BackColor = Panel->Color;
        }
        UpdateColors(m_ForeColor, m_BackColor);

        ZXColorSetting* Setting = NULL;
        if (g_EditorSettings.GetSetting(cmbColoursSpeedSettings->ItemIndex, Setting))
        {
            TColorSetting ColorSetting;
            if (Setting->GetSetting(lstColoursElements->ItemIndex, ColorSetting))
            {
                ColorSetting.ForeColor = m_ForeColor;
                ColorSetting.BackColor = m_BackColor;
                Setting->SetSetting(lstColoursElements->ItemIndex, ColorSetting);
            }
        }
    }
}
//---------------------------------------------------------------------------
TPanel* __fastcall TfrmEditorProperties::FindColor(TColor Color)
{
    switch(Color)
    {
        case clWhite    :   return panColoursWhite;
        case clAqua     :   return panColoursAqua;
        case clFuchsia  :   return panColoursFuchsia;
        case clBlue     :   return panColoursBlue;
        case clYellow   :   return panColoursYellow;
        case clLime     :   return panColoursLime;
        case clRed      :   return panColoursRed;
        case clGray     :   return panColoursGray;
        case clSilver   :   return panColoursSilver;
        case clTeal     :   return panColoursTeal;
        case clPurple   :   return panColoursPurple;
        case clNavy     :   return panColoursNavy;
        case clOlive    :   return panColoursOlive;
        case clGreen    :   return panColoursGreen;
        case clMaroon   :   return panColoursMaroon;
    }
    return panColoursBlack;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::chkColoursFontBoldClick(TObject *Sender)
{
    ZXColorSetting* Setting = NULL;
    if (g_EditorSettings.GetSetting(cmbColoursSpeedSettings->ItemIndex, Setting))
    {
        TColorSetting ColorSetting;
        if (Setting->GetSetting(lstColoursElements->ItemIndex, ColorSetting))
        {
            ColorSetting.FontStyle = chkColoursFontBold->Checked      ? ColorSetting.FontStyle << fsBold      : ColorSetting.FontStyle >> fsBold;
            ColorSetting.FontStyle = chkColoursFontItalic->Checked    ? ColorSetting.FontStyle << fsItalic    : ColorSetting.FontStyle >> fsItalic;
            ColorSetting.FontStyle = chkColoursFontUnderline->Checked ? ColorSetting.FontStyle << fsUnderline : ColorSetting.FontStyle >> fsUnderline;
            Setting->SetSetting(lstColoursElements->ItemIndex, ColorSetting);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::btnGeneralClick(TObject *Sender)
{
    TComponent* Button = dynamic_cast<TComponent*>(Sender);
    if (true == SAFE_PTR(Button))
    {
        pgcProperties->ActivePageIndex = Button->Tag;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorProperties::pgcPropertiesChange(TObject *Sender)
{
    switch (pgcProperties->TabIndex)
    {
        case 0: btnGeneral->Selected = true;    break;
        case 1: btnDisplay->Selected = true;    break;
        case 2: btnColours->Selected = true;    break;
    }
}
//---------------------------------------------------------------------------


