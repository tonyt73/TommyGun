//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "fBreakpointProperties.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KSpinEdit"
#pragma resource "*.dfm"
TfrmBreakpointProperties *frmBreakpointProperties;
//---------------------------------------------------------------------------
__fastcall TfrmBreakpointProperties::TfrmBreakpointProperties(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool __fastcall TfrmBreakpointProperties::Execute(bool PropertiesOrAdd, TBreakpoint& breakpoint, ZXFileManager& fileManager)
{
    int files = fileManager.Files();
    for (int i = 0; i < files; ++i)
    {
        String file = fileManager.GetFilename(i);
        file = ExtractFileName(file);
        cmbFiles->Items->Add(file);
        if (cmbFiles->ItemIndex == -1)
        {
            cmbFiles->ItemIndex = 0;
        }
        if (file.LowerCase() == breakpoint.file.LowerCase())
        {
            cmbFiles->ItemIndex = i;
        }
    }
    spnLine->Value = breakpoint.line;
    spnPassCount->Value = breakpoint.passCountReset;
    if (PropertiesOrAdd)
    {
        // Properties
        Caption = "Breakpoint Properties";
        cmbFiles->Enabled = false;
        spnLine->Enabled = false;
    }
    else
    {
        // Add
        Caption = "Add Breakpoint";
        cmbFiles->Enabled = true;
        cmbFiles->ItemIndex = 0;
        spnLine->Enabled = true;
    }
    m_fileManager = &fileManager;
    ShowModal();
    if (mrCancel != ModalResult)
    {
        breakpoint.file = cmbFiles->Items->Strings[cmbFiles->ItemIndex];
        breakpoint.line = spnLine->Value;
        breakpoint.passCountReset = spnPassCount->Value;
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBreakpointProperties::cmbFilesChange(TObject *Sender)
{
    int index = m_fileManager->FindFile(cmbFiles->Items->Strings[cmbFiles->ItemIndex]);
    if (index >= 0)
    {
        spnLine->Min = 1;
        spnLine->Max = m_fileManager->GetLineCount(index);
    }
}
//---------------------------------------------------------------------------
