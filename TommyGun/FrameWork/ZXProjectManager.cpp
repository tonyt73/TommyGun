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
#include <fstream>
#include <iostream>
#include <vcl.h>
#pragma hdrstop
#include <assert.h>
//- APP ---------------------------------------------------------------------
#include "..\SafeMacros.h"
//- APP ---------------------------------------------------------------------
#include "ZXGuiManager.h"
#include "ZXProjectManager.h"
#include "ZXUndoManager.h"
#include "ZXPluginManager.h"
#include "ZXGuiManager.h"
#include "ZXBackup.h"
#include "ZXLogFile.h"
//#include "fProblems.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Project;
using namespace Plugin;
using namespace GUI;
using namespace Logging;
//---------------------------------------------------------------------------
const String g_sSignature   = "TommyGun Project";
const String g_sVersion     = "2.0";   // version 2.0
const String g_sTypes[]     = { "Error", "Warning", "Info" };
//---------------------------------------------------------------------------
__fastcall ZXProjectManager::ZXProjectManager()
: m_XmlInfo(NULL)
, m_XmlDefaults(NULL)
, m_XmlUpdate(NULL)
, m_dwVersion(0)
{
}
//---------------------------------------------------------------------------
__fastcall ZXProjectManager::~ZXProjectManager()
{
    Release();
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::Initialize(HINSTANCE hInstance)
{
    ZX_LOG_INFO(lfGeneral, "Initialized Project Manager")
    g_PluginManager.OnQuerySave = OnQuerySave;
    g_PluginManager.OnQueryProjectFolder = OnQueryProjectFolder;
    m_XmlInfo = new KXmlInfo();
    m_XmlDefaults = new KXmlInfo();
    return true;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::Release(void)
{
    ZX_LOG_INFO(lfGeneral, "Releasing Project Manager")
    SAFE_DELETE(m_XmlUpdate);
    SAFE_DELETE(m_XmlInfo);
    SAFE_DELETE(m_XmlDefaults);
}
//---------------------------------------------------------------------------
TSaveQuery __fastcall ZXProjectManager::QuerySave(void)
{
    TSaveQuery QueryReply = sqSaved;
    if (true == IsDirty())
    {
        int iResponse = g_GuiManager.ShowMessage(
                            mbtQuestion,
                            "Do you want to save the changes you made?",
                            "You made changes that have not been saved.",
                            "You can choose to save or discard your changes before continuing. Cancelling will leave your changes unsaved.\n\nClick,\n\tYes\tto save your changes\n\tNo\tto discard your changes\n\tCancel\tto cancel this operation and leave your changes unsaved.",
                            "Cancel", "No", "Yes");
        // respond to the users request
        if (g_msgQueryYes == iResponse)
        {
            QueryReply = sqSaved;
            if (false == Save())
            {
                QueryReply = sqCancelled;
            }
        }
        else if (g_msgQueryNo == iResponse)
        {
            QueryReply = sqSaved;
        }
        else
        {
            QueryReply = sqCancelled;
        }
    }
    return QueryReply;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::New(const String& sProjectFile, const String& sMachine)
{
    if (sqSaved == QuerySave())
    {
        m_sMachine = sMachine;
        // initialize the main xml object
        SAFE_DELETE(m_XmlInfo);
        m_XmlInfo = new KXmlInfo();
        m_XmlInfo->SetName("TommyGunProject");
        m_XmlInfo->Add("Version", "2.0");
        m_XmlInfo->Add("Machine", sMachine);
        String sErrors;
        //m_XmlInfo->SaveFile("d:\\test1.xml", sErrors);
        g_GuiManager.XmlInitialize(m_XmlInfo);
        //m_XmlInfo->SaveFile("d:\\test2.xml", sErrors);
        LoadDefaultsXml(sMachine);
        m_XmlInfo->Add(*m_XmlDefaults);
        //m_XmlInfo->SaveFile("d:\\test3.xml", sErrors);
        m_sFilename = sProjectFile;
        Clear();
        g_PluginManager.UnloadPlugins();
        g_PluginManager.LoadPlugins();
        g_GuiManager.ProjectActive(true);
        String projectName = ExtractFilePath(m_sFilename);
        projectName[projectName.LastDelimiter("\\")] = ' ';
        projectName = projectName.SubString(projectName.LastDelimiter("\\") + 1, projectName.Length()).Trim();
        g_GuiManager.ProjectTitle(projectName);
        // initialize the plugins xml data
        g_PluginManager.XmlNotify(TZXN_XML_NEW);
        BackupProjectFile();
        m_XmlInfo->SaveFile(sProjectFile);
        AddProjectFileToMRU(sProjectFile);
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::Load(const String& sFile)
{
    bool bLoaded = false;
    if (sqSaved == QuerySave())
    {
        // load the file
        m_sFilename = sFile;
        AddProjectFileToMRU(m_sFilename);
        bLoaded = LoadProject(true);
        g_GuiManager.ProjectActive(bLoaded);
        String projectName = ExtractFilePath(m_sFilename);
        projectName[projectName.LastDelimiter("\\")] = ' ';
        projectName = projectName.SubString(projectName.LastDelimiter("\\") + 1, projectName.Length()).Trim();
        g_GuiManager.ProjectTitle(projectName);
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::Reload(void)
{
    if (false == m_sFilename.Trim().IsEmpty())
    {
        Save();
        SAFE_DELETE(m_XmlInfo);
        m_XmlInfo = new KXmlInfo();
        LoadProject(true);
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::Merge(const String& sFile)
{
    // TODO: Query for the merge options - ie. ask each plugin to provide a list of items that they load/save
    // TODO: Do a merge by allowing the plugins to load the data from the new XML file
    m_sFilename = sFile;
    bool bLoaded = LoadProject(false);
    return bLoaded;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::UpdateTGRExtension(void)
{
    m_sFilename = ChangeFileExt(m_sFilename, ".xml");
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::Save(const String& sFile)
{
    UpdateTGRExtension();
    AddProjectFileToMRU(m_sFilename);
    SaveProject();
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::LoadProject(bool bClearProject)
{
    bool bLoaded = false;
    if (true == FileExists(m_sFilename))
    {
        // clear the file messages
        m_FileMessages.clear();
        if (true == bClearProject && !Close())
        {
            return false;
            // remove the old items
            //m_sMachine = "";
            //Clear();
            //g_PluginManager.XmlNotify(TZXN_XML_NEW);
            //SAFE_DELETE(m_XmlInfo);
            //m_XmlInfo = new KXmlInfo();
        }
        // load the xml object
        String sXmlErrors;
        g_PluginManager.XmlNotify(TZXN_XML_PRE_LOAD, "", m_XmlInfo);
        if (m_XmlInfo->LoadFile(m_sFilename, sXmlErrors))
        {
            String sMachine;
            KXmlInfo* node = m_XmlInfo->GetNode("Machine", 0);
            if (true == SAFE_PTR(node))
            {
                sMachine = node->GetText();
            }
            // get the project version number
            m_dwVersion = 0;
            node = m_XmlInfo->GetNode("Version", 0);
            if (true == SAFE_PTR(node))
            {
                String sVersion = node->GetText();
                int dot = sVersion.Pos('.');
                if (dot)
                {
                    m_dwVersion  = StrToInt(sVersion.SubString(1, dot - 1)) << 16;
                    m_dwVersion += StrToInt(sVersion.SubString(dot + 1, sVersion.Length()));
                }
                else
                {
                    m_dwVersion = StrToInt(sVersion);
                }
            }
            // if the machine is unkown AND the project is loading or its
            // merging and the machines are the same, then continue loading
            if (sMachine != "" && (false == bClearProject || sMachine == m_sMachine || m_sMachine == ""))
            {
                // save the machine type
                m_sMachine = sMachine;
                // and then load the defaults for it
                LoadDefaultsXml(m_sMachine);
                if (true == bClearProject)
                {
                    m_XmlInfo->Add(*m_XmlDefaults);
                    // unload the old plugins
                    g_PluginManager.UnloadPlugins();
                    // change the machine folder
                    g_GuiManager.WriteMachineFolder(sMachine);
                    // load the required plugins
                     g_PluginManager.LoadPlugins();
                }
                // notify the new plugins of the loaded xml file
                g_PluginManager.XmlNotify(TZXN_XML_POST_LOAD, "", m_XmlInfo);
                // file loaded
                bLoaded = true;
            }
            else
            {
                // TODO: failed to find the machine for the project
                int iResponse = g_GuiManager.ShowMessage(
                                    mbtError,
                                    "Failed to find the Machine for the Project!",
                                    "TommyGun failed to locate a Machine type for the project file",
                                    "TommyGun could not load the project, because the machine type is unknown. \n\nClick\n\tOK\tto continue.",
                                    "OK", "", "");
            }
        }
        else
        {
            // TODO: Show xml load errors
        }
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::SaveProject(void)
{
    bool bSaved = false;
    String sErrors;
    // read the remove whitespace flag from the registry
    KXmlInfo::m_bRemoveWhitespace = false;
    KRegistry* regScorpio = new KRegistry(NULL);
    regScorpio->Section = "TommyGun";
    regScorpio->SoftwareKey = "\\Software\\Scorpio\\";
    regScorpio->RootKey = rkHKEY_CURRENT_USER;
    regScorpio->Read("States", "RemoveXmlWhitespace", KXmlInfo::m_bRemoveWhitespace);

    g_PluginManager.XmlNotify(TZXN_XML_PRE_SAVE, "", m_XmlInfo);
    // remove the defaults node before saving
    KXmlInfo* defaults;
    if (m_XmlInfo->Find(defaults, "Defaults", 0))
    {
        m_XmlInfo->Remove(defaults);
    }
    // set the project version number
    KXmlInfo* node = m_XmlInfo->GetNode("Version", 0);
    if (true == SAFE_PTR(node))
    {
        node->SetText(g_sVersion);
    }
    BackupProjectFile();
    if (true == m_XmlInfo->SaveFile(m_sFilename, sErrors))
    {
        g_PluginManager.XmlNotify(TZXN_XML_POST_SAVE, "", m_XmlInfo);
        bSaved = true;
        ZXBackup Backup;
        Backup.Backup(m_sFilename, beOnSave);
    }
    else
    {
        // TODO: display xml save errors
    }
    // load the defaults node back into the xml node
    //LoadDefaultsXml(m_sMachine);
    bool bClearUndo = false;
    if (regScorpio->Read("Undo", "ClearAfterSave", bClearUndo) && bClearUndo)
    {
        g_UndoManager.Clear();
    }
    SAFE_DELETE(regScorpio);
    return bSaved;
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::Save(void)
{
    return Save(m_sFilename);
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::Close(void)
{
    // save the project
    if (sqSaved == QuerySave())
    {
        // then, deactivate the project actions and unload the plugins
        Application->MainForm->Caption = "TommyGun";
        g_GuiManager.ProjectActive(false);
        g_PluginManager.UnloadPlugins();
        SAFE_DELETE(m_XmlInfo);
        m_XmlInfo = new KXmlInfo();
        ZXBackup Backup;
        Backup.Backup(m_sFilename, beOnClose);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::Clear(void)
{
    // TODO: Clear the UNDO object
    g_PluginManager.Notify(NULL, TZX_VERB_NEW, NULL, 0, 0);
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::IsDirty(void)
{
    bool bNeedToSave = false;
    // Is the project? ie. Do any plugins have any unsaved data? We only need 1 plugin to answer yes
    g_PluginManager.Notify(NULL, TZX_QUERY_DATASAVED, (LPDATA)&bNeedToSave, 0, 0);
    return bNeedToSave;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::AddProjectFileToMRU(const String& sFilename)
{
    bool bExists = false;
    // is the file already in the mru list?
    GetMRUList(m_MRUProjects, false);
    if (m_MRUProjects.size())
    {
        for (unsigned int i = 0; i < m_MRUProjects.size() && !bExists; ++i)
        {
            bExists = m_MRUProjects[i].File.LowerCase() == sFilename.LowerCase();
        }
    }
    if (false == bExists)
    {
        TMRUProject mruProject;
        mruProject.File = sFilename;
        mruProject.Exists = true;
        m_MRUProjects.insert(m_MRUProjects.begin(), mruProject);
        SaveMRU();
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::SaveMRU(void)
{
    // write the list back to the registry
    KRegistry* regScorpio = new KRegistry(NULL);
    regScorpio->Section = "TommyGun";
    regScorpio->SoftwareKey = "\\Software\\Scorpio\\";
    regScorpio->RootKey = rkHKEY_CURRENT_USER;
    regScorpio->ClearKey("MRU");
    for (unsigned int i = 0; i < m_MRUProjects.size(); ++i)
    {
        regScorpio->Write("MRU", IntToStr(i), m_MRUProjects[i].File);
    }
    SAFE_DELETE(regScorpio);
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::Restore(String sProjectName)
{
    int iProject = -1;
    if (m_MRUProjects.size() == 0)
    {
        GetMRUList(m_MRUProjects, false);
    }
    for (int i = 0; i < (int)m_MRUProjects.size(); i++)
    {
        AnsiString sFile = m_MRUProjects[i].File;
        sFile = ExtractFilePath(sFile);
        sFile = sFile.SubString(1, sFile.Length() - 1);
        int iSlash = sFile.LastDelimiter("\\");
        if (iSlash)
        {
            sFile = sFile.SubString(iSlash + 1, sFile.Length());
        }
        // sfile contains the project name
        if (sProjectName == sFile)
        {
            ZXBackup Backup;
            Backup.Restore(m_MRUProjects[i].File);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::Remove(String sName, bool bRemoveFolder)
{
    int iProject = -1;
    if (m_MRUProjects.size() == 0)
    {
        GetMRUList(m_MRUProjects, false);
    }
    for (int i = 0; i < (int)m_MRUProjects.size(); i++)
    {
        AnsiString sFile = m_MRUProjects[i].File;
        sFile = ExtractFilePath(sFile);
        sFile = sFile.SubString(1, sFile.Length() - 1);
        int iSlash = sFile.LastDelimiter("\\");
        if (iSlash)
        {
            sFile = sFile.SubString(iSlash + 1, sFile.Length());
        }
        // sfile contains the project name
        if (sName == sFile)
        {
            iProject = i;
            break;
        }
    }
    if (0 <= iProject && iProject < (int)m_MRUProjects.size())
    {
        bool bDeleted = true;
        // erase the list from the list
        if (bRemoveFolder)
        {
            // delete the folder
            bDeleted = Delete(iProject);
        }
        if (bDeleted)
        {
            m_MRUProjects.erase(m_MRUProjects.begin() + iProject);
            SaveMRU();
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::DeleteFolder(String sFolder, bool bRemoveFolder)
{
    DWORD dwError = 0;
    bool bDeleted = true;
    TSearchRec sr;

    int iFound = FindFirst(sFolder + "*.*", faAnyFile, sr);
    while (0 == iFound && true == bDeleted)
    {
        if (sr.Attr & faDirectory)
        {
            if (sr.Name[1] != '.')
            {
                bDeleted = DeleteFolder(sFolder + sr.Name + "\\");
            }
        }
        else
        {
            if (FileSetAttr(sFolder + sr.Name, 0) == 0)
            {
                bDeleted = DeleteFile(sFolder + sr.Name);
            }
            else
            {
                bDeleted = false;
            }
        }
        iFound = FindNext(sr);
    }
    FindClose(sr);
    if (bRemoveFolder)
        return 0 != RemoveDirectory(sFolder.c_str());
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::Delete(int iProject)
{
    if (0 <= iProject && iProject < (int)m_MRUProjects.size())
    {
        int iAnswer;
        if (m_MRUProjects[iProject].File != m_sFilename)
        {
            if (false == DeleteFolder(ExtractFilePath(m_MRUProjects[iProject].File)))
            {
                Message
                (
                    mbtError,
                    "Failed to Delete Project Folder!",
                    "",
                    "TommyGun failed to Delete the project folder.\nThis could be because the system has a lock on a file in the folder or the directory is read-only.",
                    "Ok", "", "", iAnswer
                );
                return false;
            }
        }
        else
        {
            Message
            (
                mbtError,
                "Cannot Delete current project or last loaded project",
                "You cannot delete the current or last used project",
                "The current project or last used project will contain a system lock due to the use of the Windows Open Dialog."
                " So you cannot delete it. You must either open another project or restart TommyGun.",
                "Ok", "", "", iAnswer
            );
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::Rename(String sOldName, String sNewName)
{
    String sPath;
    int iProject = -1;
    if (m_MRUProjects.size() == 0)
    {
        GetMRUList(m_MRUProjects, false);
    }
    for (int i = 0; i < (int)m_MRUProjects.size(); i++)
    {
        String sFile = m_MRUProjects[i].File;
        sFile = ExtractFilePath(sFile);
        sFile = sFile.SubString(1, sFile.Length() - 1);
        int iSlash = sFile.LastDelimiter("\\");
        if (iSlash)
        {
            sPath = sFile.SubString(1, iSlash);
            sFile = sFile.SubString(iSlash + 1, sFile.Length());
        }
        // sfile contains the project name
        if (sOldName == sFile)
        {
            iProject = i;
            break;
        }
    }
    if (0 <= iProject && iProject < (int)m_MRUProjects.size())
    {
        sOldName = sPath + sOldName + "\\";
        sNewName = sPath + sNewName + "\\";
        int iOk;
        if (true == DirectoryExists(sOldName))
        {
            if (false == DirectoryExists(sNewName))
            {
                if (rename(sOldName.c_str(), sNewName.c_str()) == 0)
                {
                    m_MRUProjects[iProject].File = sNewName + "project.xml";
                    SaveMRU();
                }
                else
                {
                    // failed to rename the project
                    Message
                    (
                        mbtError,
                        "Failed to Rename the Project",
                        "Folder rename operation failed",
                        "Failed to Rename the Project folder to the new project name.\n"
                        "Either access was denied or the new project name contains invalid characters.",
                        "Ok", "", "", iOk
                    );
                }
            }
            else
            {
                // new name already exists
                Message
                (
                    mbtError,
                    "New Project name already exists",
                    "Cannot rename project to an existing project name",
                    "You cannot rename a project to the name of an existing project."
                    "It just ain't gonna happen dude!",
                    "Ok", "", "", iOk
                );
            }
        }
        else
        {
            // project to rename doesn't exist
            Message
            (
                mbtError,
                "Project folder does not exist",
                "Project folder to rename does not exist",
                "The project folder has disappeared and so it cannot be renamed\n"
                "Duh!",
                "Ok", "", "", iOk
            );
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::CopyFiles(String sOldName, String sNewName)
{
    if (ForceDirectories(ExtractFileDir(sNewName)))
    {
        DWORD dwError = 0;
        TSearchRec sr;

        int iFound = FindFirst(sOldName + "*.*", faAnyFile, sr);
        while (0 == iFound)
        {
            if (sr.Attr & ~faDirectory)
            {
                String sOldFile = sOldName + sr.Name;
                String sNewFile = sNewName + sr.Name;

                if (CopyFile(sOldFile.c_str(), sNewFile.c_str(), TRUE) == FALSE)
                {
                    return false;
                }
            }
            iFound = FindNext(sr);
        }
        FindClose(sr);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::Copy(String sOldName, String sNewName)
{
    String sPath;
    int iProject = -1;
    if (m_MRUProjects.size() == 0)
    {
        GetMRUList(m_MRUProjects, false);
    }
    for (int i = 0; i < (int)m_MRUProjects.size(); i++)
    {
        String sFile = m_MRUProjects[i].File;
        sFile = ExtractFilePath(sFile);
        sFile = sFile.SubString(1, sFile.Length() - 1);
        int iSlash = sFile.LastDelimiter("\\");
        if (iSlash)
        {
            sPath = sFile.SubString(1, iSlash);
            sFile = sFile.SubString(iSlash + 1, sFile.Length());
        }
        // sfile contains the project name
        if (sOldName == sFile)
        {
            iProject = i;
            break;
        }
    }
    if (0 <= iProject && iProject < (int)m_MRUProjects.size())
    {
        sOldName = sPath + sOldName + "\\";
        sNewName = sPath + sNewName + "\\";
        int iOk;
        if (true == DirectoryExists(sOldName))
        {
            if (false == DirectoryExists(sNewName))
            {
                if (CopyFiles(sOldName, sNewName))
                {
                    AddProjectFileToMRU(sNewName + "project.xml");
                    SaveMRU();
                }
                else
                {
                    // failed to copy the project
                    Message
                    (
                        mbtError,
                        "Failed to Copy the Project",
                        "Folder copy operation failed",
                        "Failed to Copy the Project folder to the new project folder name.\n"
                        "Either access was denied or the new project name contains invalid characters.",
                        "Ok", "", "", iOk
                    );
                }
            }
            else
            {
                // new name already exists
                Message
                (
                    mbtError,
                    "New Project name already exists",
                    "Cannot copy project to an existing project name",
                    "You cannot copy a project to the name of an existing project."
                    "It just ain't gonna happen dude!",
                    "Ok", "", "", iOk
                );
            }
        }
        else
        {
            // project to rename doesn't exist
            Message
            (
                mbtError,
                "Project folder does not exist",
                "Project folder to rename does not exist",
                "The project folder has disappeared and so it cannot be copied\n"
                "Duh!",
                "Ok", "", "", iOk
            );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::GetMRUList(TMRUProjectsVector& mruProjects, bool bGetMachine)
{
    PROTECT_BEGIN
    // clear the lists
    mruProjects.clear();
    TStringList* list = new TStringList();
    KRegistry* regScorpio = new KRegistry(NULL);
    regScorpio->Section = "TommyGun";
    regScorpio->SoftwareKey = "\\Software\\Scorpio\\";
    regScorpio->RootKey = rkHKEY_CURRENT_USER;
    if (true == SAFE_PTR(list))
    {
        if (regScorpio->GetValues("MRU", list) && list->Count)
        {
            // read all the files for the entries
            for (int i = 0; i < list->Count; ++i)
            {
                AnsiString sFile;
                if (regScorpio->Read("MRU", list->Strings[i], sFile))
                {
                    //sFile = ChangeFileExt(sFile, ".xml");
                    TMRUProject mruProject;
                    mruProject.File = sFile;
                    mruProject.Exists = FileExists(sFile);
                    mruProject.TimeStamp = 0;
                    // get the machine
                    mruProject.Machine = bGetMachine ? GetMachine(sFile) : String("Unknown");
                    if (mruProject.Exists)
                    {
                        // get the time stamp
                        mruProject.TimeStamp = FileDateToDateTime(FileAge(sFile));
                    }
                    mruProjects.push_back(mruProject);
                }
            }
            // sort the projects by the timestamp (using a slow bubble sort)
            /*bool bSwapped = true;
            int i = 0;
            while (i < (int)mruProjects.size() - 1)
            {
                if (mruProjects[i].TimeStamp < mruProjects[i+1].TimeStamp)
                {
                    TMRUProject temp           = mruProjects[i  ];
                    mruProjects[i  ].File      = mruProjects[i+1].File;
                    mruProjects[i  ].Machine   = mruProjects[i+1].Machine;
                    mruProjects[i  ].Exists    = mruProjects[i+1].Exists;
                    mruProjects[i  ].TimeStamp = mruProjects[i+1].TimeStamp;
                    mruProjects[i+1].File      = temp.File;
                    mruProjects[i+1].Machine   = temp.Machine;
                    mruProjects[i+1].Exists    = temp.Exists;
                    mruProjects[i+1].TimeStamp = temp.TimeStamp;
                    i = 0;
                }
                else
                {
                    ++i;
                }
            }*/
            // remove any excess items
            while (mruProjects.size() > 31)
            {
                mruProjects.pop_back();
            }
        }
    }
    SAFE_DELETE(regScorpio);
    SAFE_DELETE(list);
    PROTECT_END
}
//---------------------------------------------------------------------------
String __fastcall ZXProjectManager::GetMachine(const String& sFile)
{
    // read the machine name from the file
    String sMachine = "Unknown";
    if (FileExists(sFile))
    {
		ifstream ifs;
		ifs.open(sFile.c_str(),ios::binary );
		if (ifs.is_open())
		{
            // get length of file:
            ifs.seekg (0, ios::end);
            int length = ifs.tellg();
            ifs.seekg (0, ios::beg);

            String strXml;
            strXml.SetLength(length+1);
            LPSTR buffer = strXml.c_str();
            // read data as a block:
            ifs.read (buffer,length);
            // find the machine string
            char* pMachineBegin = strstr(buffer, "<Machine>");
            if (NULL != pMachineBegin)
            {
                char* pMachineEnd = strstr(buffer, "</Machine>");
                if (NULL != pMachineEnd)
                {
                    sMachine = String(pMachineBegin + 9, pMachineEnd - pMachineBegin - 9).Trim();
                }
            }
        }
    }
    return sMachine;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::LogFileError(ZXFileErrorType MessageType, const String& sPlugin, String sErrorMessage)
{
    ZXFileMessage message;
    message.Type = MessageType;
    message.Plugin = sPlugin;
    message.Message = sErrorMessage;
    m_FileMessages.push_back(message);
}
//---------------------------------------------------------------------------
/*void __fastcall ZXProjectManager::DisplayFileMessages(void)
{
    bool bDonNotShowProblems = false;
    KRegistry* regScorpio = new KRegistry(NULL);
    regScorpio->Section = "TommyGun";
    regScorpio->SoftwareKey = "\\Software\\Scorpio\\";
    regScorpio->RootKey = rkHKEY_CURRENT_USER;
    regScorpio->Read("States", "DoNotShowProblems", bDonNotShowProblems);
    SAFE_DELETE(regScorpio);
    if (m_FileMessages.size() && !bDonNotShowProblems)
    {
        // display a dialog with the messages in it
        frmProblems = new TfrmProblems(NULL);
        frmProblems->lstProblems->Clear();
        for (unsigned int i = 0; i < m_FileMessages.size(); ++i)
        {
            TListItem  *item = frmProblems->lstProblems->Items->Add();
            item->Caption = g_sTypes[m_FileMessages[i].Type];
            item->SubItems->Add(m_FileMessages[i].Plugin);
            item->SubItems->Add(m_FileMessages[i].Message);
        }
        frmProblems->ShowModal();
        SAFE_DELETE(frmProblems);
    }
}*/
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::LoadDefaultsXml(const String& sMachine)
{
    String sDefaultsFile = ExtractFilePath(Application->ExeName);
    sDefaultsFile += "Plugins\\_" + sMachine + "\\defaults.xml";

    if (FileExists(sDefaultsFile))
    {
        SAFE_DELETE(m_XmlDefaults);
        m_XmlDefaults = new KXmlInfo();
        m_XmlDefaults->LoadFile(sDefaultsFile);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::BackupProjectFile(void)
{
    // backup the project file before saving
    if (FileExists(m_sFilename))
    {
        String sBackupFile = ChangeFileExt(m_sFilename, ".bak");
        CopyFile(m_sFilename.c_str(), sBackupFile.c_str(), FALSE);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::OnQuerySave(bool &bSaved)
{
    bSaved = QuerySave() == sqSaved;
}
//---------------------------------------------------------------------------
void __fastcall ZXProjectManager::OnQueryProjectFolder(String& sFolder)
{
    sFolder = ProjectFile;    
}
//---------------------------------------------------------------------------
bool __fastcall ZXProjectManager::SortProjects(int iColumn)
{
    static int iLastColumn = -1;
    static bool bSortAscending = true;

    if (iLastColumn == iColumn)
    {
        bSortAscending = !bSortAscending;
    }
    iLastColumn = iColumn;

    if (m_MRUProjects.size() == 0)
    {
        GetMRUList(m_MRUProjects, false);
    }

    bool bSwapped = true;

    while(bSwapped)
    {
        bool bSwap = false;
        bSwapped = false;
        for (unsigned int i = 0; i < m_MRUProjects.size() - 1; i++)
        {
            bSwap = false;
            TMRUProject tmp = m_MRUProjects[i];
            
            switch(iColumn)
            {
                case 0: // name
                    bSwap = bSortAscending ? (m_MRUProjects[i+1].File < m_MRUProjects[i].File) : (m_MRUProjects[i].File < m_MRUProjects[i+1].File);
                    break;
                case 1: // macine
                    bSwap = bSortAscending ? (m_MRUProjects[i+1].Machine < m_MRUProjects[i].Machine) : (m_MRUProjects[i].Machine < m_MRUProjects[i+1].Machine);
                    break;
                case 2: // modified data
                    bSwap = bSortAscending ? (m_MRUProjects[i+1].TimeStamp < m_MRUProjects[i].TimeStamp) : (m_MRUProjects[i].TimeStamp < m_MRUProjects[i+1].TimeStamp);
                    break;
                default:// error :-(
                    break;
            }
            if (bSwap)
            {
                m_MRUProjects[i]   = m_MRUProjects[i+1];
                m_MRUProjects[i+1] = tmp;
            }

            bSwapped |= bSwap;
        }
    }
    SaveMRU();
    return bSortAscending;
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall ZXProjectManager::GetXmlInfo(void)
{
    SAFE_DELETE(m_XmlUpdate);
    m_XmlUpdate = new KXmlInfo();
    if (true == SAFE_PTR(m_XmlUpdate))
    {
        PostNotifyEvent(NULL, TZXN_XML_UPDATE, (LPDATA)m_XmlUpdate, NULL, 0);
        return m_XmlUpdate;
    }
    return NULL;
}
//---------------------------------------------------------------------------

