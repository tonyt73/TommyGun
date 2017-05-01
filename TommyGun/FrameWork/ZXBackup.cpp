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
#include "KRegistry.h"
#include "ZXProjectManager.h"
#include "fRestoreProject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Project;
//---------------------------------------------------------------------------
__fastcall ZXBackup::ZXBackup()
: m_bEnabled(true)
, m_bOnSave(true)
, m_bLimitFolders(true)
, m_iFolderLimit(32)
{
}
//---------------------------------------------------------------------------
__fastcall ZXBackup::~ZXBackup()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXBackup::Backup(const String& sProject, ZXBackupEvent Event)
{
    ReadSettings();
    if (QueryBackup(Event))
    {
        String sBackupBasePath = GetBackupPath(sProject);
        String sBackupPath = sBackupBasePath + TDateTime::CurrentDateTime().FormatString("yyyymmdd-hhmmss") + "\\";
        // lets not get pedantic here, if the user saves with 1 second let just skip the backup
        if (!DirectoryExists(sBackupPath))
        {
            // create the new backup directory
            if (ForceDirectories(sBackupPath))
            {
                // copy the files across to the directory
                String sPath = ExtractFilePath(sProject);
                TSearchRec sr;
                int iFH = FindFirst(sPath + "*.*", faAnyFile, sr);
                while (!iFH)
                {
                    if (sr.Name[1] != '.' && ((sr.Attr & faDirectory) == 0))
                    {
                        // copy the file
                        String sFromFile = sPath + sr.Name;
                        String sToFile   = sBackupPath + sr.Name;
                        CopyFile(sFromFile.c_str(), sToFile.c_str(), TRUE);
                    }
                    iFH = FindNext(sr);
                }
                FindClose(sr);
                // prune directories
                PruneFolders(sBackupBasePath);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXBackup::Restore(const String& sProject)
{
    ReadSettings();
    String sPath = GetBackupPath(sProject);
    std::vector<String> vFolders;
    TSearchRec sr;
    ZXRestoreItems vItems;
    int iFH = FindFirst(sPath + "*.*", faAnyFile, sr);
    while (!iFH)
    {
        if (sr.Name[1] != '.' && (sr.Attr & faDirectory) == faDirectory)
        {
            // get the folder details
            if (sr.Name[9] == '-' && StrToInt(sr.Name.SubString(1, 8)) > 20000000L)
            {
                ZXRestoreItem ri;
                TDate dtDate(
                                StrToInt(sr.Name.SubString(1, 4)),
                                StrToInt(sr.Name.SubString(5, 2)),
                                StrToInt(sr.Name.SubString(7, 2))
                             );
                TTime dtTime(
                                StrToInt(sr.Name.SubString(10, 2)),
                                StrToInt(sr.Name.SubString(12, 2)),
                                StrToInt(sr.Name.SubString(14, 2)),
                                0
                             );
                ri.dtDate = dtDate + dtTime;
                int iFiles = 0;
                int iSize = 0;
                GetFolderDetails(sPath + sr.Name, ri.iFiles, ri.iSize);
                vItems.push_back(ri);
            }
        }
        iFH = FindNext(sr);
    }
    FindClose(sr);

    TfrmRestoreProject* frmRestore = new TfrmRestoreProject(NULL);
    int iRestoreIndex = frmRestore->Execute(m_sProjectName, vItems);
    SAFE_DELETE(frmRestore);
    if (iRestoreIndex >= 0)
    {
        String sBackupPath = sPath + vItems[iRestoreIndex].dtDate.FormatString("yyyymmdd-hhmmss");
        // lets not get pedantic here, if the user saves with 1 second let just skip the backup
        String sPath = ExtractFilePath(sProject);
        if (DirectoryExists(sBackupPath) && DirectoryExists(sPath))
        {
            // clear the folder contents
            ZXProjectManager::DeleteFolder(sPath, false);
            // copy the files across to the directory
            TSearchRec sr;
            int iFH = FindFirst(sBackupPath + "\\*.*", faAnyFile, sr);
            while (!iFH)
            {
                if (sr.Name[1] != '.' && ((sr.Attr & faDirectory) == 0))
                {
                    // copy the file
                    String sFromFile = sBackupPath + "\\" + sr.Name;
                    String sToFile   = sPath + sr.Name;
                    CopyFile(sFromFile.c_str(), sToFile.c_str(), TRUE);
                }
                iFH = FindNext(sr);
            }
            FindClose(sr);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXBackup::GetFolderDetails(const String& sFolder, int& iFiles, int& iSize)
{
    iFiles = 0;
    iSize = 0;
    TSearchRec sr;
    int iFH = FindFirst(sFolder + "\\*.*", faAnyFile, sr);
    while (!iFH)
    {
        if (sr.Name[1] != '.' && (sr.Attr & faDirectory) != faDirectory)
        {
            iFiles++;
            iSize += sr.Size;
        }
        iFH = FindNext(sr);
    }
    FindClose(sr);
}
//---------------------------------------------------------------------------
void __fastcall ZXBackup::ReadSettings(void)
{
    bool bBackupOk = false;
    KRegistry* Registry = new KRegistry(NULL);

    Registry->RootKey = rkHKEY_CURRENT_USER;
    Registry->Section = "TommyGun";
    Registry->SoftwareKey = "\\Software\\Scorpio\\";

    bool bValue = true;
    if (Registry->Read("Backup", "EnableBackup", bValue))
    {
        m_bEnabled = bValue;
    }
    bValue = true;
    if (true == Registry->Read("Backup", "EnableFolderLimit", bValue))
    {
        m_bLimitFolders = bValue;
    }
    int iValue = 32;
    if (true == Registry->Read("Backup", "FolderLimit", iValue))
    {
        m_iFolderLimit = std::max(4, std::min(64, iValue));
    }
    bValue = true;
    if (true == Registry->Read("Backup", "BackOnSave", bValue))
    {
        m_bOnSave = bValue;
    }

    SAFE_DELETE(Registry);
}
//---------------------------------------------------------------------------
bool __fastcall ZXBackup::QueryBackup(ZXBackupEvent Event)
{
    return m_bEnabled && ((Event == beOnSave && m_bOnSave) || (Event == beOnClose && !m_bOnSave));
}
//---------------------------------------------------------------------------
String __fastcall ZXBackup::GetBackupPath(const String& sFilename)
{
    String sPath = ExtractFilePath(sFilename);
    // remove the end slash
    sPath = sPath.SubString(1, sPath.Length() - 1);
    // find the last slash
    int iLastSlash = sPath.LastDelimiter("\\/");
    m_sProjectName = "Unknown";
    if (iLastSlash)
    {
        m_sProjectName = sPath.SubString(iLastSlash, sPath.Length());
        sPath = sPath.SubString(1, iLastSlash);
    }
    // get the projects backup path
    sPath = sPath + "Backup" + m_sProjectName + "\\";
    // create the new backup folder name from the year/month/day/hour/min/secs
    return sPath;
}
//---------------------------------------------------------------------------
void __fastcall ZXBackup::PruneFolders(const String& sBackupPath)
{
    if (m_bLimitFolders)
    {
        String sPath = sBackupPath;
        // find the folders in the backup folder
        std::vector<String> vFolders;
        TSearchRec sr;
        int iFH = FindFirst(sPath + "*.*", faAnyFile, sr);
        while (!iFH)
        {
            if (sr.Name[1] != '.' && (sr.Attr & faDirectory) == faDirectory)
            {
                vFolders.push_back(sr.Name);
            }
            iFH = FindNext(sr);
        }
        FindClose(sr);
        while (m_iFolderLimit < (int)vFolders.size())
        {
            // need to prune folders
            int iPath = 0;
            for (int i = 1; i < (int)vFolders.size(); i++)
            {
                if (vFolders[i] < vFolders[iPath])
                {
                    iPath = i;
                }
            }
            // delete the folder
            ZXProjectManager::DeleteFolder(sPath + vFolders[iPath] + "\\");
            // remove it from the list
            vFolders.erase(vFolders.begin() + iPath);
            // keep going until we are less than or equal to the folder limit
        }
    }
}
//---------------------------------------------------------------------------

