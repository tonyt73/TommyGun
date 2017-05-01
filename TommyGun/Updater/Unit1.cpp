//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
const   iOneMB      = 1024 * 1024;
const   iOneKB      = 1024;
const   iMachines   = 18;
//---------------------------------------------------------------------------
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
String __fastcall TForm1::IntToMemory(int iSize)
{
    String sMemory = "";
    if (iSize >= iOneMB)
    {
        float fMem = (float)iSize / (float)iOneMB;
        sMemory = FloatToStrF(fMem, ffFixed, 7, 2) + "MB";
    }
    else if (iSize >= iOneKB)
    {
        float fMem = (float)iSize / (float)iOneKB;
        sMemory = FloatToStrF(fMem, ffFixed, 7, 2) + "KB";
    }
    else
    {
        sMemory = IntToStr(iSize) + "bytes";
    }
    return sMemory;
}
//---------------------------------------------------------------------------
int __fastcall TForm1::GetFileSize(const String& sFile)
{
    int iSize = 0;
    TSearchRec sr;
    if (FindFirst(sFile, faAnyFile, sr) == 0)
    {
        iSize = sr.Size;
        FindClose(sr);
    }
    return iSize;
}
//---------------------------------------------------------------------------
int __fastcall TForm1::CopyFolder(String sSrcPath, String sDstPath)
{
    int iSize = 0;
    TSearchRec sr;
    String sPath = sSrcPath + "*.?pi";
    int AttrFilter = faSysFile | faVolumeID | faDirectory | faHidden;
    if (FindFirst(sPath, faAnyFile, sr) == 0)
    {
        do
        {
            if ((sr.Attr & AttrFilter) == 0)
            {
                String sOld = sSrcPath + sr.Name;
                String sNew = sDstPath + sr.Name;
                CopyFile(sOld.c_str(), sNew.c_str(), FALSE);
                iSize += GetFileSize(sNew);
            }
        }
        while (FindNext(sr) == 0);
        FindClose(sr);
    }
    return iSize;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    String sSrcPath = "D:\\Projects\\TommyGun\\TommyGun\\";
    String sDstPath = "D:\\Projects\\TommyGun\\TommyGun\\binaries\\";
    int iTotalSize = 0;
    int iSize;
    String path = ExtractFilePath(Application->ExeName);
    for (int i = 0; i < iMachines+1; i++)
    {
        if (!chkZXOnly->Checked || i < 12)
        {
            AnsiString sLine = stgFiles->Cells[0][i].Trim();
            if (sLine != "")
            {
                if (sLine[sLine.Length()] != '\\')
                {
                    String sOld = sSrcPath + sLine;
                    String sNew = sDstPath + sLine;
                    if (sLine.AnsiPos("Scorpio") || sLine.AnsiPos("SynEdit"))
                    {
                        AnsiString file = sLine.SubString(sLine.LastDelimiter("\\") + 1, 255);
                        sNew = sDstPath + file;
                    }
                    if (FileExists(sOld))
                    {
                        CopyFile(sOld.c_str(), sNew.c_str(), FALSE);
                        iSize = GetFileSize(sNew);
                    }
                    else
                    {
                        iSize = -1;
                    }
                }
                else
                {
                    // copy all binaries in the folder (*.mpi, *tpi)
                    iSize = CopyFolder(sSrcPath + sLine, sDstPath + sLine);
                    String sOld = sSrcPath + sLine + "defaults.xml";
                    String sNew = sDstPath + sLine + "defaults.xml";
                    CopyFile(sOld.c_str(), sNew.c_str(), FALSE);
                    iSize += GetFileSize(sNew);
                }
                stgFiles->Cells[1][i] = IntToMemory(iSize);
                iTotalSize += iSize;
            }
        }
    }
    if (!chkZXOnly->Checked)
    {
        stgFiles->Cells[1][iMachines+1] = IntToMemory(iTotalSize);
        String sOld = sSrcPath + "\\_ZX Spectrum\\UDGType.ipi";
        String sNew = sDstPath + "\\_Jupiter Ace\\UDGType.ipi";
        CopyFile(sOld.c_str(), sNew.c_str(), FALSE);
        sOld = sSrcPath + "\\_ZX Spectrum\\MonochromePalette.ipi";
        sNew = sDstPath + "\\_Jupiter Ace\\MonochromePalette.ipi";
        CopyFile(sOld.c_str(), sNew.c_str(), FALSE);
        sOld = sSrcPath + "\\_ZX Spectrum\\MonochromePalette.ipi";
        sNew = sDstPath + "\\_Sam Coupe\\MonochromePalette.ipi";
        CopyFile(sOld.c_str(), sNew.c_str(), FALSE);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    stgFiles->Cells[0][ 0] = "TommyGun.exe";
    stgFiles->Cells[0][ 1] = "Core_R6.dll";
    stgFiles->Cells[0][ 2] = "CoreUtils_R6.dll";
    stgFiles->Cells[0][ 3] = "PluginCommon_R6.dll";
    stgFiles->Cells[0][ 4] = "LogFiles_R6.dll";
    stgFiles->Cells[0][ 6] = "..\\VCL\\Scorpio_R6.bpl";
    stgFiles->Cells[0][ 5] = "..\\VCL\\Scintilla_R6.bpl";
    stgFiles->Cells[0][ 7] = "ImageLibrary_R6.dll";
    stgFiles->Cells[0][ 8] = "Plugins\\";
    stgFiles->Cells[0][ 9] = "Plugins\\_ZX Spectrum\\";
    stgFiles->Cells[0][10] = "Tools.xml";
    stgFiles->Cells[0][11] = "pasmo\\Pasmo.exe";
    //stgFiles->Cells[0][10] = "AGD\\AgdGameEngine.asm";
    //stgFiles->Cells[0][11] = "AGD\\AgdCompile.exe";
    /*
    stgFiles->Cells[0][11] = "Plugins\\_Amstrad CPC\\";
    stgFiles->Cells[0][12] = "Plugins\\_Commodore 64\\";
    stgFiles->Cells[0][13] = "Plugins\\_Enterprise\\";
    stgFiles->Cells[0][14] = "Plugins\\_Jupiter Ace\\";
    stgFiles->Cells[0][15] = "Plugins\\_Sam Coupe\\";
    stgFiles->Cells[0][16] = "Plugins\\_MSX\\";
    stgFiles->Cells[0][17] = "Plugins\\_VIC20\\";
	stgFiles->Cells[0][19] = "Plugins\\_Timex 20xx\\";
    */
}
//---------------------------------------------------------------------------

