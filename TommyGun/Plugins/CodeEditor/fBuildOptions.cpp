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
#include "fBuildOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KIconButton"
#pragma link "cspin"
#pragma link "KSpinEdit"
#pragma link "KRegistry"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmBuildOptions *frmBuildOptions = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmBuildOptions::TfrmBuildOptions(TComponent* Owner)
: TForm(Owner)
, m_currentToolDefinition(-1)
, m_bDirty(false)
{
}
//---------------------------------------------------------------------------
__fastcall TfrmBuildOptions::~TfrmBuildOptions()
{
}
//---------------------------------------------------------------------------
void __fastcall  TfrmBuildOptions::Load(void)
{
    m_ToolDefinitions.Load();
    RefreshToolDefinitions();
    pgcProperties->TabIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall  TfrmBuildOptions::EditCopy(void)
{
    if (m_Edit || ActiveControl)
    {
        SendMessage(m_Edit ? m_Edit->Handle : ActiveControl->Handle, WM_COPY, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall  TfrmBuildOptions::EditCut(void)
{
    if (m_Edit || ActiveControl)
    {
        SendMessage(m_Edit ? m_Edit->Handle : ActiveControl->Handle, WM_CUT, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall  TfrmBuildOptions::EditPaste(void)
{
    if (m_Edit || ActiveControl)
    {
        SendMessage(m_Edit ? m_Edit->Handle : ActiveControl->Handle, WM_PASTE, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnGeneralClick(TObject *Sender)
{
    TComponent* Button = dynamic_cast<TComponent*>(Sender);
    if (true == SAFE_PTR(Button))
    {
        pgcProperties->ActivePageIndex = Button->Tag;
    }
}
//---------------------------------------------------------------------------
String __fastcall TfrmBuildOptions::GUID()
{
    UUID uuid;
    UuidCreate(&uuid);

    unsigned char* str;
    UuidToStringA(&uuid, &str);

    String s((char*) str);
    RpcStringFreeA ( &str );
    return s;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::cmbTypeChange(TObject *Sender)
{
    grpPrefixes->Visible = cmbType->ItemIndex == 0;
    m_bDirty = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::frmBuildChange(TObject *Sender)
{
    bool blankEdit = edtName->Text.Trim() == "" || edtExecutable->Text.Trim() == "";
    btnToolAdd->Enabled = !m_ToolDefinitions.Exists(edtName->Text) && FileExists(edtExecutable->Text);
    btnToolUpdate->Enabled = m_currentToolDefinition == m_ToolDefinitions.GetIndex(edtName->Text) && !blankEdit;
    btnToolRemove->Enabled = m_currentToolDefinition == m_ToolDefinitions.GetIndex(edtName->Text);
    m_bDirty = true;
    cmbTypeChange(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::frmBuildEnter(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::frmBuildExit(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnToolAddClick(TObject *Sender)
{
    ZXToolDefinition definition;
    definition.m_Name = edtName->Text;
    definition.m_Executable = edtExecutable->Text;
    definition.m_Extensions = edtExtensions->Text;
    definition.m_Type = (TToolType) cmbType->ItemIndex;
    definition.m_DefaultParameters = edtDefaultParameters->Text;
    definition.m_PrefixError = edtPrefixError->Text;
    definition.m_PrefixFile = edtPrefixFile->Text;
    definition.m_PrefixLine = edtPrefixLineNo->Text;
    definition.m_AcceptsMultipleInputFiles = chkAcceptsMultipleFiles->Checked;
    m_ToolDefinitions.Add(definition);
    m_currentToolDefinition = m_ToolDefinitions.Count();
    RefreshToolDefinitions();
    edtName->Text = "";
    edtExecutable->Text = "";
    edtExtensions->Text = "";
    cmbType->ItemIndex = 0;
    m_currentToolDefinition = -1;
    frmBuildChange(NULL);
    m_ToolDefinitions.Save();
    m_bDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnToolUpdateClick(TObject *Sender)
{
    m_bDirty = false;
    ZXToolDefinition definition;
    m_ToolDefinitions.Get(m_currentToolDefinition, definition);
    definition.m_Name = edtName->Text;
    definition.m_Executable = edtExecutable->Text;
    definition.m_Extensions = edtExtensions->Text;
    definition.m_DefaultParameters = edtDefaultParameters->Text;
    definition.m_Type = (TToolType) cmbType->ItemIndex;
    definition.m_PrefixError = edtPrefixError->Text;
    definition.m_PrefixFile = edtPrefixFile->Text;
    definition.m_PrefixLine = edtPrefixLineNo->Text;
    definition.m_AcceptsMultipleInputFiles = chkAcceptsMultipleFiles->Checked;
    m_ToolDefinitions.Update(m_currentToolDefinition, definition);
    RefreshToolDefinitions();
    frmBuildChange(NULL);
    m_ToolDefinitions.Save();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnToolRemoveClick(TObject *Sender)
{
    SaveIfDirty();
    m_ToolDefinitions.Remove(m_currentToolDefinition);
    m_currentToolDefinition = -1;
    RefreshToolDefinitions();
    frmBuildChange(NULL);
    m_ToolDefinitions.Save();
    m_bDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnClearClick(TObject *Sender)
{
    SaveIfDirty();
    edtName->Text = "";
    edtExecutable->Text = "";
    edtExtensions->Text = "";
    edtDefaultParameters->Text = "";
    chkAcceptsMultipleFiles->Checked = false;
    cmbType->ItemIndex = 0;
    edtPrefixError->Text = "ERROR";
    edtPrefixFile->Text = "file";
    edtPrefixLineNo->Text = "line";
    frmBuildChange(NULL);
    m_bDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::RefreshToolDefinitions()
{
    String tool1 = cmbTool1->ItemIndex == -1 ? String() : cmbTool1->Items->Strings[cmbTool1->ItemIndex];
    String tool2 = cmbTool2->ItemIndex == -1 ? String() : cmbTool2->Items->Strings[cmbTool2->ItemIndex];
    String tool3 = cmbTool3->ItemIndex == -1 ? String() : cmbTool3->Items->Strings[cmbTool3->ItemIndex];
    String emulator = cmbEmulator->ItemIndex == -1 ? String() : cmbEmulator->Items->Strings[cmbEmulator->ItemIndex];
    cmbTool1->Items->Clear();
    cmbTool2->Items->Clear();
    cmbTool3->Items->Clear();
    cmbEmulator->Items->Clear();
    lstTools->Items->Clear();
    TListItem* item;
    for (int i = 0; i < m_ToolDefinitions.Count(); ++i)
    {
        ZXToolDefinition def;
        m_ToolDefinitions.Get(i, def);
        item = lstTools->Items->Add();
        item->Caption = def.m_Name;
        item->Data = (void*)i;
        item->SubItems->Add(def.m_Type == ttBuilder ? "Builder" : "Emulator");
        String sFile = def.m_Executable;
        frmCodeEditor->DoSubstitutes(sFile);
        item->SubItems->Add(FileExists(sFile) ? "Yes" : "NO");
        item->SubItems->Add(def.m_Extensions);
        item->SubItems->Add(def.m_Executable);
        item->Selected = (i == m_currentToolDefinition);
        if (def.m_Type == ttBuilder)
        {
            cmbTool1->Items->Add(def.m_Name);
            cmbTool2->Items->Add(def.m_Name);
            cmbTool3->Items->Add(def.m_Name);
            if (def.m_Name == tool1)
            {
                cmbTool1->ItemIndex = cmbTool1->Items->Count - 1;
                cmbTool1Select(NULL);
            }
            if (def.m_Name == tool2)
            {
                cmbTool2->ItemIndex = cmbTool2->Items->Count - 1;
                cmbTool2Select(NULL);
            }
            if (def.m_Name == tool3)
            {
                cmbTool3->ItemIndex = cmbTool3->Items->Count - 1;
                cmbTool3Select(NULL);
            }
        }
        else
        {
            cmbEmulator->Items->Add(def.m_Name);
            if (def.m_Name == emulator)
            {
                cmbEmulator->ItemIndex = cmbEmulator->Items->Count - 1;
                cmbEmulatorSelect(NULL);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::lstToolsSelectItem(TObject *Sender, TListItem *Item, bool Selected)
{
    SaveIfDirty();
    m_currentToolDefinition = (int)Item->Data;
    ZXToolDefinition def;
    if (m_ToolDefinitions.Get(m_currentToolDefinition, def))
    {
        edtName->Text = def.m_Name;
        edtExecutable->Text = def.m_Executable;
        edtExtensions->Text = def.m_Extensions;
        edtDefaultParameters->Text = def.m_DefaultParameters;
        cmbType->ItemIndex = (int)def.m_Type;
        chkAcceptsMultipleFiles->Checked = def.m_AcceptsMultipleInputFiles;
        edtPrefixError->Text = def.m_PrefixError;
        edtPrefixFile->Text = def.m_PrefixFile;
        edtPrefixLineNo->Text = def.m_PrefixLine;
        frmBuildChange(NULL);
    }
    m_bDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::cmbEmulatorSelect(TObject *Sender)
{
    if (cmbEmulator->ItemIndex == -1)
    {
        lblEmulatorNotFound->Visible = false;
        lblEmulatorDefaults->Visible = false;
    }
    else
    {
        ZXToolDefinition def;
        m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(cmbEmulator->Items->Strings[cmbEmulator->ItemIndex]), def);
        lblEmulatorNotFound->Visible = !m_ToolDefinitions.ExecutableExists(cmbEmulator->Items->Strings[cmbEmulator->ItemIndex]);
        lblEmulatorDefaults->Hint = def.m_DefaultParameters;
        lblEmulatorDefaults->ShowHint = true;
        lblEmulatorDefaults->Visible = lblEmulatorDefaults->Caption.Trim() != "";
    }
    btnUpdateTool->Visible = lblEmulatorNotFound->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnUpdateToolClick(TObject *Sender)
{
    int index = m_ToolDefinitions.GetIndex(cmbEmulator->Items->Strings[cmbEmulator->ItemIndex]);
    if (index != -1)
    {
        btnTools->Selected = true;
        lstTools->ItemIndex = index;
        pgcProperties->TabIndex = 1;
        edtExecutable->SetFocus();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnUpdateTool1Click(TObject *Sender)
{
    int index = m_ToolDefinitions.GetIndex(cmbTool1->Items->Strings[cmbTool1->ItemIndex]);
    if (index != -1)
    {
        btnTools->Selected = true;
        lstTools->ItemIndex = index;
        pgcProperties->TabIndex = 1;
        edtExecutable->SetFocus();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnUpdateTool2Click(TObject *Sender)
{
    int index = m_ToolDefinitions.GetIndex(cmbTool2->Items->Strings[cmbTool2->ItemIndex]);
    if (index != -1)
    {
        btnTools->Selected = true;
        lstTools->ItemIndex = index;
        pgcProperties->TabIndex = 1;
        edtExecutable->SetFocus();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnUpdateTool3Click(TObject *Sender)
{
    int index = m_ToolDefinitions.GetIndex(cmbTool3->Items->Strings[cmbTool3->ItemIndex]);
    if (index != -1)
    {
        btnTools->Selected = true;
        lstTools->ItemIndex = index;
        pgcProperties->TabIndex = 1;
        edtExecutable->SetFocus();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::cmbTool1Select(TObject *Sender)
{
    if (cmbTool1->ItemIndex == -1)
    {
        lblMissingTool1->Visible = false;
    }
    else
    {
        lblMissingTool1->Visible = !m_ToolDefinitions.ExecutableExists(cmbTool1->Items->Strings[cmbTool1->ItemIndex]);
        ZXToolDefinition def;
        m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(cmbTool1->Items->Strings[cmbTool1->ItemIndex]), def);
        lblTool1Defaults->Hint = def.m_DefaultParameters;
        lblTool1Defaults->ShowHint = true;
        lblTool1Defaults->Visible = true;
        cmbTool1Change(NULL);
    }
    btnUpdateTool1->Visible = lblMissingTool1->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::cmbTool2Select(TObject *Sender)
{
    if (cmbTool2->ItemIndex == -1)
    {
        lblMissingTool2->Visible = false;
    }
    else
    {
        lblMissingTool2->Visible = !m_ToolDefinitions.ExecutableExists(cmbTool2->Items->Strings[cmbTool2->ItemIndex]);
        ZXToolDefinition def;
        m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(cmbTool2->Items->Strings[cmbTool2->ItemIndex]), def);
        lblTool2Defaults->Hint = def.m_DefaultParameters;
        lblTool2Defaults->ShowHint = true;
        lblTool2Defaults->Visible = true;
        cmbTool2Change(NULL);
    }
    btnUpdateTool2->Visible = lblMissingTool2->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::cmbTool3Select(TObject *Sender)
{
    if (cmbTool3->ItemIndex == -1)
    {
        lblMissingTool3->Visible = false;
    }
    else
    {
        lblMissingTool3->Visible = !m_ToolDefinitions.ExecutableExists(cmbTool3->Items->Strings[cmbTool3->ItemIndex]);
        ZXToolDefinition def;
        m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(cmbTool3->Items->Strings[cmbTool3->ItemIndex]), def);
        lblTool3Defaults->Hint = def.m_DefaultParameters;
        lblTool3Defaults->ShowHint = true;
        lblTool3Defaults->Visible = true;
    }
    btnUpdateTool3->Visible = lblMissingTool3->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::cmbTool1Change(TObject *Sender)
{
    chkTool2->Visible = cmbTool1->ItemIndex != -1 && !lblMissingTool1->Visible;
    chkTool2->Enabled = true;
    grpTool2->Visible = chkTool2->Visible;
    grpTool2->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::cmbTool2Change(TObject *Sender)
{
    chkTool3->Visible = cmbTool2->ItemIndex != -1 && !lblMissingTool2->Visible;
    chkTool3->Enabled = true;
    grpTool3->Visible = chkTool3->Visible;
    grpTool3->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::chkTool2Click(TObject *Sender)
{
    grpTool2->Enabled = chkTool2->Checked;
    if (!chkTool2->Checked)
    {
        cmbTool2->ItemIndex = -1;
        edtParameters2->Text = "";
        lblMissingTool2->Visible = false;
        lblTool2Defaults->Visible = false;
        btnUpdateTool2->Visible = false;
        chkTool3->Enabled = false;
        chkTool3->Visible = false;
        grpTool3->Visible = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::chkTool3Click(TObject *Sender)
{
    grpTool3->Enabled = chkTool3->Checked;
    if (!chkTool3->Checked)
    {
        cmbTool3->ItemIndex = -1;
        edtParameters3->Text = "";
        lblMissingTool3->Visible = false;
        lblTool3Defaults->Visible = false;
        btnUpdateTool3->Visible = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnFindExecutableClick(TObject *Sender)
{
    String path = ExtractFilePath(edtExecutable->Text);
    if (DirectoryExists(path))
    {
        dlgFindApp->InitialDir = path;
    }
    if (dlgFindApp->Execute())
    {
        edtExecutable->Text = dlgFindApp->FileName;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnEmulatorDefaultsClick(TObject *Sender)
{
    ZXToolDefinition def;
    m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(cmbEmulator->Items->Strings[cmbEmulator->ItemIndex]), def);
    edtEmulatorParameters->Text = def.m_DefaultParameters;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::lblTool1DefaultsClick(TObject *Sender)
{
    ZXToolDefinition def;
    m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(cmbTool1->Items->Strings[cmbTool1->ItemIndex]), def);
    edtParameters1->Text = def.m_DefaultParameters;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::lblTool2DefaultsClick(TObject *Sender)
{
    ZXToolDefinition def;
    m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(cmbTool2->Items->Strings[cmbTool2->ItemIndex]), def);
    edtParameters2->Text = def.m_DefaultParameters;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::lblTool3DefaultsClick(TObject *Sender)
{
    ZXToolDefinition def;
    m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(cmbTool3->Items->Strings[cmbTool3->ItemIndex]), def);
    edtParameters3->Text = def.m_DefaultParameters;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::SetBuildTool(int tool, String name)
{
    if (0 <= tool && tool < 3)
    {
        std::vector<TComboBox*> combos;
        combos.push_back(cmbTool1);
        combos.push_back(cmbTool2);
        combos.push_back(cmbTool3);

        for (int i = 0; i < combos[tool]->Items->Count; ++i)
        {
            if (combos[tool]->Items->Strings[i] == name)
            {
                combos[tool]->ItemIndex = i;
                if (i == 0) cmbTool1Select(NULL);
                if (i == 1) cmbTool2Select(NULL);
                if (i == 2) cmbTool3Select(NULL);
                return;
            }
        }

        String file = ExtractFileName(name);
        // find the executable
        int toolIndex = m_ToolDefinitions.GetExecutableIndex(file, true);
        if (toolIndex != -1)
        {
            ZXToolDefinition def;
            m_ToolDefinitions.Get(toolIndex, def);

            for (int i = 0; i < combos[tool]->Items->Count; ++i)
            {
                if (combos[tool]->Items->Strings[i] == def.m_Name)
                {
                    combos[tool]->ItemIndex = i;
                    if (i == 0) cmbTool1Select(NULL);
                    if (i == 1) cmbTool2Select(NULL);
                    if (i == 2) cmbTool3Select(NULL);
                    return;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::SetBuildParameters(int tool, String parameters)
{
    switch (tool)
    {
        case 0:
            edtParameters1->Text = parameters;
            break;
        case 1:
            edtParameters2->Text = parameters;
            break;
        case 2:
            edtParameters3->Text = parameters;
            break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::SetEmulatorTool(String name)
{
    for (int i = 0; i < cmbEmulator->Items->Count; ++i)
    {
        if (cmbEmulator->Items->Strings[i] == name)
        {
            cmbEmulator->ItemIndex = i;
            cmbEmulatorSelect(NULL);
            return;
        }
    }

    String file = ExtractFileName(name);
    // find the executable
    int toolIndex = m_ToolDefinitions.GetExecutableIndex(file, true);
    if (toolIndex != -1)
    {
        ZXToolDefinition def;
        m_ToolDefinitions.Get(toolIndex, def);

        for (int i = 0; i < cmbEmulator->Items->Count; ++i)
        {
            if (cmbEmulator->Items->Strings[i] == def.m_Name)
            {
                cmbEmulator->ItemIndex = i;
                return;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::SetEmulatorParameters(String parameters)
{
    edtEmulatorParameters->Text = parameters;
}
//---------------------------------------------------------------------------
String __fastcall TfrmBuildOptions::GetEmulator()
{
    if (cmbEmulator->ItemIndex != -1)
    {
        ZXToolDefinition def;
        m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(cmbEmulator->Text), def);
        return def.m_Executable;
    }
    return String();
}
//---------------------------------------------------------------------------
String __fastcall TfrmBuildOptions::GetEmulatorParameters()
{
    return edtEmulatorParameters->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::GetPrefixes(int tool, String& error, String& file, String& lineNo)
{
    if (0 <= tool && tool < 3)
    {
        std::vector<TComboBox*> combos;
        combos.push_back(cmbTool1);
        combos.push_back(cmbTool2);
        combos.push_back(cmbTool3);
        if (combos[tool]->ItemIndex != -1)
        {
            ZXToolDefinition def;
            m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(combos[tool]->Text), def);
            error = def.m_PrefixError;
            file = def.m_PrefixFile;
            lineNo = def.m_PrefixLine;
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall TfrmBuildOptions::GetBuilder(int tool, ZXToolDefinition& builder)
{
    if (0 <= tool && tool < 3)
    {
        std::vector<TComboBox*> combos;
        combos.push_back(cmbTool1);
        combos.push_back(cmbTool2);
        combos.push_back(cmbTool3);
        if (combos[tool]->ItemIndex != -1)
        {
            m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(combos[tool]->Text), builder);
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
String __fastcall TfrmBuildOptions::GetBuilderParameters(int tool)
{
    if (0 <= tool && tool < 3)
    {
        std::vector<TEdit*> edits;
        edits.push_back(edtParameters1);
        edits.push_back(edtParameters2);
        edits.push_back(edtParameters3);
        return edits[tool]->Text;
    }
    return "";
}
//---------------------------------------------------------------------------
bool __fastcall TfrmBuildOptions::DoesToolSupportExtension(int tool, String ext)
{
    if (0 <= tool && tool < 3)
    {
        std::vector<TComboBox*> combos;
        combos.push_back(cmbTool1);
        combos.push_back(cmbTool2);
        combos.push_back(cmbTool3);
        if (combos[tool]->ItemIndex != -1)
        {
            ZXToolDefinition def;
            m_ToolDefinitions.Get(m_ToolDefinitions.GetIndex(combos[tool]->Text), def);
            return def.m_Extensions.LowerCase().AnsiPos(ext.LowerCase()) > 0;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::FormShow(TObject *Sender)
{
    GetFonts();
    SetEditorOptions();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::tabBuildersEnter(TObject *Sender)
{
    RefreshToolDefinitions();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::btnToolsClick(TObject *Sender)
{
    RefreshToolDefinitions();
    btnGeneralClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::SaveIfDirty()
{
    static bSaving = false;
    if (!bSaving && m_bDirty)
    {
        bSaving = true;
        int iAnswer = 0;
        Message
        (
            mbtWarning,
            "You have unsaved tool changes.",
            "Would you like to save them?",
            "You have changed the settings for the current tool.\n\nClick\n\tYes\tto Save the changes.\n\tNo\tto ignore the changes.",
            "No",
            "Yes",
            "",
            iAnswer
        );
        if (iAnswer == 1)
        {
            // save the file being removed
            btnToolUpdateClick(NULL);
        }
        bSaving = false;
    }
    m_bDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::cmbDisplayFontsChange(TObject *Sender)
{
    panDisplayFontSample->Font->Name = cmbDisplayFonts->Items->Strings[cmbDisplayFonts->ItemIndex];
    panDisplayFontSample->Font->Size = edtDisplayFontSize->Value;
    panDisplayFontSample->Font->Pitch= fpFixed;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::GetFonts()
{
    cmbDisplayFonts->Items->Clear();
    bool bValue = true;
    regScorpio->Read("CodeEditor\\Display", "NoTrueTypeFonts", bValue);
    chkDisplayFixedFontsOnly->Checked = bValue;

    if (bValue)
    {
        Graphics::TBitmap* bmp = new Graphics::TBitmap();
        bmp->Width = 200;
        bmp->Height = 200;
        TFont* font = new TFont;
        font->Size = 10;
        for (int i = 0; i < Screen->Fonts->Count; ++i)
        {
            font->Name = Screen->Fonts->Strings[i];
            font->Charset = ANSI_CHARSET;
            font->Pitch = fpVariable;
            bmp->Canvas->Font->Assign(font);
            int wi = bmp->Canvas->TextWidth("iiiiiiii");
            int ws = bmp->Canvas->TextWidth("        ");
            int ww = bmp->Canvas->TextWidth("wwwwwwww");
            int wc = bmp->Canvas->TextWidth("COLUMNS         equ        4");
            int wr = bmp->Canvas->TextWidth("ROWS            equ        4");
            if (wi == ww && wi == ws && wc == wr)
            {
                bmp->Canvas->Font->Style = TFontStyles() << fsBold;
                int bwi = bmp->Canvas->TextWidth("iiiiiiii");
                int bws = bmp->Canvas->TextWidth("        ");
                int bww = bmp->Canvas->TextWidth("wwwwwwww");
                int bwc = bmp->Canvas->TextWidth("COLUMNS         equ        4");
                int bwr = bmp->Canvas->TextWidth("ROWS            equ        4");
                if (wi == bwi && ww == bww && ws == bws && bwc == bwr)
                {
                    cmbDisplayFonts->Items->Add(Screen->Fonts->Strings[i]);
                }
            }
        }
        SAFE_DELETE(bmp);
    }
    else
    {
        cmbDisplayFonts->Items->Assign(Screen->Fonts);
    }
    panDisplayFontSample->Font->Name = cmbDisplayFonts->Items->Strings[cmbDisplayFonts->ItemIndex];
    panDisplayFontSample->Font->Size = edtDisplayFontSize->Value;
    panDisplayFontSample->Font->Pitch= fpFixed;
    Select(cmbDisplayFonts, g_EditorSettings.Font);
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::chkDisplayFixedFontsOnlyClick(TObject *Sender)
{
    regScorpio->Write("CodeEditor\\Display", "NoTrueTypeFonts", chkDisplayFixedFontsOnly->Checked);
    GetFonts();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::Select(TComboBox* pComboBox, String sText)
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
void __fastcall TfrmBuildOptions::cmdCloseClick(TObject *Sender)
{
    g_EditorSettings.AutoCloseBraces = chkAutoCloseBraces->Checked;
    g_EditorSettings.AutoCloseQuotes = chkAutoCloseQuotes->Checked;
    g_EditorSettings.TabsToSpaces    = radTabUseSpaces->Checked;
    g_EditorSettings.TabWidth        = edtTabWidth->Value;
    g_EditorSettings.ShowGuides      = chkAlignmentShow->Checked;
    g_EditorSettings.GuideWidth      = edtGuideWidth->Value;
    g_EditorSettings.LineNumbers     = chkShowLineNumbers->Checked;
    g_EditorSettings.Font            = cmbDisplayFonts->Text;
    g_EditorSettings.FontSize        = edtDisplayFontSize->Value;
    g_EditorSettings.Whitespace      = radWhitespaceNever->Checked ? 0 : (radWhitespaceAlways->Checked ? 1 : 2);
    g_EditorSettings.Write();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::SetEditorOptions()
{
    chkAutoCloseBraces->Checked = g_EditorSettings.AutoCloseBraces;
    chkAutoCloseQuotes->Checked = g_EditorSettings.AutoCloseQuotes;
    if (g_EditorSettings.TabsToSpaces) radTabUseSpaces->Checked = true; else radTabsUse->Checked = true;
    edtTabWidth->Value = g_EditorSettings.TabWidth;
    chkAlignmentShow->Checked = g_EditorSettings.ShowGuides;
    edtGuideWidth->Value = g_EditorSettings.GuideWidth;
    chkShowLineNumbers->Checked = g_EditorSettings.LineNumbers;
    cmbDisplayFonts->Text = g_EditorSettings.Font;
    edtDisplayFontSize->Value = g_EditorSettings.FontSize;
    if (g_EditorSettings.Whitespace == 0)
        radWhitespaceNever->Checked = true;
    else if (g_EditorSettings.Whitespace == 1)
        radWhitespaceAlways->Checked = true;
    else
        radWhitespaceAfterIndent->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBuildOptions::SetTargetFile(String file)
{
    for (int i = 0; i < cmbTargetFile->Items->Count; i++)
    {
        if (cmbTargetFile->Items->Strings[i].LowerCase() == file.LowerCase())
        {
            cmbTargetFile->ItemIndex = i;
            return;
        }
    }
    cmbTargetFile->ItemIndex = cmbTargetFile->Items->Count > 0 ? 0 : -1;
}
//---------------------------------------------------------------------------
String __fastcall TfrmBuildOptions::GetTargetFile()
{
    return cmbTargetFile->Items->Strings[cmbTargetFile->ItemIndex];
}
//---------------------------------------------------------------------------

