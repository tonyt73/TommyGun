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
#include <Windows.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
//---------------------------------------------------------------------------
const String g_sSignature   = "Code Editor";
const String g_sVersion     = "2.0";
//---------------------------------------------------------------------------
const   int     g_iFileNotFound     = -1; 
//---------------------------------------------------------------------------
__fastcall ZXFileManager::ZXFileManager()
: m_bDirty(false)
, m_Documents(NULL)
, m_DocumentsOther(NULL)
{
}
//---------------------------------------------------------------------------
__fastcall ZXFileManager::~ZXFileManager()
{
    Clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::SetSciTabControls(TSciDocumentTabControl* documents, TSciDocumentTabControl* otherDocuments)
{
	m_Documents = documents;
	m_DocumentsOther = otherDocuments;
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::sciEditorModified(TObject *Sender, const int position, const int modificationType, PChar text, const int len, const int linesAdded, const int line, const int foldLevelNow, const int foldLevelPrev)
{
    if (m_bOpeningFile || m_Documents == NULL)
        return;
    m_Documents->ActiveDocument->Modified = true;
    String sFile = m_Documents->ActiveDocument->FileName;
    int index = FindFile(sFile);
    if (index != -1)
    {
        MakeDirty();
        m_vFiles[index].bDirty = true;
        if (m_vFiles[index].pLines == NULL)
        {
            m_vFiles[index].pLines = new TStringList();
        }
        m_vFiles[index].pLines->Assign(((TScintilla*)(m_Documents->Editor))->Lines);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::sciEditorModifiedOther(TObject *Sender, const int position, const int modificationType, PChar text, const int len, const int linesAdded, const int line, const int foldLevelNow, const int foldLevelPrev)
{
	if (m_bOpeningFile || m_DocumentsOther == NULL)
		return;
	m_DocumentsOther->ActiveDocument->Modified = true;
	String sFile = m_DocumentsOther->ActiveDocument->FileName;
	int index = FindFile(sFile);
	if (index != -1)
	{
		MakeDirty();
		m_vFiles[index].bDirty = true;
		if (m_vFiles[index].pLines == NULL)
		{
			m_vFiles[index].pLines = new TStringList();
		}
		m_vFiles[index].pLines->Assign(((TScintilla*)(m_DocumentsOther->Editor))->Lines);
	}
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::Clear(void)
{
    //m_Documents = NULL;
    m_vFiles.clear();
    m_bDirty = false;
}
//---------------------------------------------------------------------------
int __fastcall ZXFileManager::Add(const String& sFile, bool bSilent)
{
    int iAddedIndex = g_iFileNotFound;
    if (sFile.Trim() != "")
    {
        iAddedIndex = FindFile(sFile);
        if (g_iFileNotFound == iAddedIndex)
        {
            // does the file exist in a different directory?
            String sProjectFolder;
            PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sProjectFolder, 0, 0);
            String sFileFolder = ExtractFilePath(sFile);
            if (sFileFolder != sProjectFolder)
            {
                String sNewFile = sProjectFolder + ExtractFileName(sFile);
                // need to copy the file into the project folder
                CopyFile(sFile.c_str(), sNewFile.c_str(), TRUE);
                // and load it
                LoadFile(iAddedIndex, false);
            }

            // add the file to the file list
            TZXFile zxFile;
            zxFile.bDirty  = false;
            zxFile.sFile   = ExtractFileName(sFile);
            iAddedIndex    = m_vFiles.size();
            m_vFiles.push_back(zxFile);
            m_bDirty       = true;
        }
        else
        {
            if (false == bSilent)
            {
                int iAnswer;
                Message
                (
                    mbtError,
                    "File already exists!",
                    "File exists in project",
                    "This filename already exists in the current project\n"
                    "An existing file of the same name cannot be added to the project.\n"
                    "Please rename the file if it is different to the one in the project "
                    "and then add it to the project\n",
                    "Ok",
                    "",
                    "",
                    iAnswer
                );
            }
        }
    }
    return iAddedIndex;
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::Remove(int iIndex)
{
    if (0 <= iIndex && iIndex < (int)m_vFiles.size())
	{
		bool wasOtherView = m_vFiles[iIndex].bOtherView;
		Close(iIndex);
		m_vFiles.erase(m_vFiles.begin() + iIndex);
		m_bDirty = true;
        RenumberTabs(wasOtherView);
    }
}
//---------------------------------------------------------------------------
int __fastcall ZXFileManager::Rename(int iIndex, const String& sNewName)
{
    if (0 <= iIndex && iIndex < (int)m_vFiles.size())
    {
        String sFolder;
        PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);
        String sOldFile = sFolder + ExtractFileName(m_vFiles[iIndex].sFile);
        String sNewFile = sFolder + ExtractFileName(sNewName);
        m_vFiles[iIndex].sFile = sNewName;
        m_bDirty = true;
		if (m_vFiles[iIndex].iDocumentIndex != -1)
		{
			if (!m_vFiles[iIndex].bOtherView)
				m_Documents->Document[m_vFiles[iIndex].iDocumentIndex]->FileName = sNewFile;
			else
				m_DocumentsOther->Document[m_vFiles[iIndex].iDocumentIndex]->FileName = sNewFile;
		}
        if (FileExists(sOldFile))
        {
            RenameFile(sOldFile, sNewFile);
        }
        RenumberTabs(m_vFiles[iIndex].bOtherView);
    }
    return iIndex;
}
//---------------------------------------------------------------------------
int __fastcall ZXFileManager::FindFile(const String& sFile)
{
    int iFileIndex = g_iFileNotFound;
    for (int i = 0; i < (int)m_vFiles.size() && g_iFileNotFound == iFileIndex; i++)
    {
        if (m_vFiles[i].sFile.LowerCase().Trim() == ExtractFileName(sFile).LowerCase().Trim())
        {
            iFileIndex = i;
        }
    }
    return iFileIndex;
}
//---------------------------------------------------------------------------
String __fastcall ZXFileManager::GetFilename(int iIndex) const
{
    String sFile;
    if (0 <= iIndex && iIndex < (int)m_vFiles.size())
    {
        sFile = m_vFiles[iIndex].sFile;
    }
    return sFile;
}
//---------------------------------------------------------------------------
int __fastcall ZXFileManager::GetLineCount(int iIndex)
{
    int count = 0;
    if (0 <= iIndex && iIndex < (int)m_vFiles.size())
    {
        if (m_vFiles[iIndex].pLines != NULL)
        {
            return m_vFiles[iIndex].pLines->Count;
        }
        TStrings* lines = new TStringList();
        if (GetLines(iIndex, lines))
        {
            count = lines->Count;
        }
        SAFE_DELETE(lines);
    }
    return count;
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::FileNameExists(const String& sFile)
{
    bool bExists = false;
    for (int i = 0; i < (int)m_vFiles.size() && false == bExists; i++)
    {
        bExists = sFile.Trim().LowerCase() == m_vFiles[i].sFile.Trim().LowerCase();
    }
    return bExists;
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::IsFileOpen(int iIndex)
{
    return m_vFiles[iIndex].iDocumentIndex != -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXFileManager::LoadFile(int iIndex, bool inOtherView = false)
{
	m_bOpeningFile = true;
	TSciDocumentTabControl* documents = !inOtherView ? m_Documents : m_DocumentsOther;
	if (documents != NULL)
	{
		documents->Visible = true;
		documents->Invalidate();
	}
	frmCodeEditor->Refresh();
	frmCodeEditor->Update();
	int docIndex = -1;
	if (0 <= iIndex && iIndex < (int)m_vFiles.size())
	{
		String sFile = m_vFiles[iIndex].sFile;
		// now if the file exists then load it
		String sFolder;
		PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);
		String sProjectFile = sFolder + ExtractFileName(sFile);
		m_vFiles[iIndex].bDirty = false;
		//if (FileExists(sProjectFile))
		{
			/*if (m_Documents->Open(sProjectFile))
			{
				docIndex = m_Documents->ActiveDocument->Index;
				m_vFiles[iIndex].iDocumentIndex = docIndex;
			}*/
			docIndex = m_vFiles[iIndex].iDocumentIndex;
			if (docIndex == -1)
			{
				if (documents != NULL)
				{
					docIndex = documents->Add(ExtractFileName(sProjectFile), sProjectFile);
				}
				if (docIndex != -1)
				{
					TScintilla* editor = !inOtherView ? frmCodeEditor->sciEditor : frmCodeEditor->sciEditorOther;
					if (inOtherView && !frmCodeEditor->splOtherView->Visible)
					{
						frmCodeEditor->splOtherView->Visible = true;
						frmCodeEditor->sciTabControlOther->Visible = true;
					}
					if (FileExists(sProjectFile))
					{
						bool ro = frmCodeEditor->sciEditor->ReadOnly;
						if (!inOtherView)
						{
							editor->ReadOnly = false;
							editor->LoadFromFile(sProjectFile);
							editor->ReadOnly = ro;
						}
						else
						{
							editor->ReadOnly = false;
							editor->LoadFromFile(sProjectFile);
							editor->ReadOnly = ro;
						}
					}
					String Language;
					documents->OnDetectHighlighter(NULL, ExtractFileExt(sProjectFile), Language);

					editor->SelectedLanguage = Language;
					m_vFiles[iIndex].iDocumentIndex = docIndex;
					g_EditorSettings.Apply(documents->Document[docIndex]);
					g_EditorSettings.Apply((TScintillaMemo*)documents->Editor);
				}
			}
			else
			{
				documents->Document[docIndex]->Activate();
				g_EditorSettings.Apply(documents->Document[docIndex]);
                g_EditorSettings.Apply((TScintillaMemo*)documents->Editor);
            }
			if (documents != NULL && documents->Count > 1)
			{
				for (int i = 0; i < documents->Count; ++i)
				{
					if (documents->Document[i]->IsUntitled())
					{
                        documents->Close(i);
                    }
                }
            }
            RenumberTabs(inOtherView);
			if (documents != NULL)
			{
				documents->Visible = documents->Count > 1 || !documents->ActiveDocument->IsUntitled();
				frmCodeEditor->splOtherView->Left = 0;
				frmCodeEditor->splOtherView->Visible = frmCodeEditor->sciEditorOther;
			}
		}
	}
	m_bOpeningFile = false;
	return docIndex;
}
//---------------------------------------------------------------------------
int __fastcall ZXFileManager::Open(int iIndex, bool inOtherView = false)
{
    return LoadFile(iIndex, inOtherView);
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::Close(int iIndex)
{
    if (0 <= iIndex && iIndex < (int)m_vFiles.size())
    {
        if (m_vFiles[iIndex].iDocumentIndex != -1)
		{
			bool wasInOtherView = m_vFiles[iIndex].bOtherView;
			if (m_vFiles[iIndex].bOtherView == false)
			{
				m_Documents->Close(m_vFiles[iIndex].iDocumentIndex, true);
			}
			else
			{
				m_DocumentsOther->Close(m_vFiles[iIndex].iDocumentIndex, true);
			}
			m_vFiles[iIndex].iDocumentIndex = -1;
			RenumberTabs(wasInOtherView);
			return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::Close(String sFile)
{
    int index = FindFile(sFile);
    if (index != -1)
    {
        return Close(index);
    }
    return false;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXFileManager::Load(KXmlInfo& xmlInfo)
{
    // load the list of files
    KXmlInfo* Files;

    if (xmlInfo.Find(Files, "Files", 0))
    {
        // load the files lists (loop thru "Files" nodes)
        for (KXmlNodes::iterator it = Files->begin(); it != Files->end(); it++)
        {
            String sFile = (*it)->GetText();
            if (sFile.Trim() != "")
            {
                Add(sFile);
            }
        }
    }

    // and then load the files into the string lists
    m_bDirty = false;
    for (int i = 0; i < (int)m_vFiles.size(); ++i)
    {
        m_vFiles[i].bDirty = false;
    }
    return S_FALSE;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXFileManager::Save(KXmlInfo& xmlInfo)
{
    Save();
    KXmlInfo& Files = xmlInfo.AddTag("Files");
    for (int i = 0; i < (int)m_vFiles.size(); i++)
    {
        // save the file link to the xml object
        KXmlInfo& File = Files.Add("File", m_vFiles[i].sFile);
    }
    m_bDirty = false;
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::Save(void)
{
    // save the documents
	int activeDocIndex = m_Documents->ActiveDocument->Index;
	for (int i = 0; i < m_Documents->Count; ++i)
    {
        if (m_Documents->Document[i]->Modified)
        {
            m_Documents->Activate(i);
            m_Documents->Editor->SaveToFile(m_Documents->Document[i]->FileName);
            m_Documents->Document[i]->Modified = false;
        }
    }
	m_Documents->Activate(activeDocIndex);
	// save the documents
	if (m_DocumentsOther->Count > 0)
	{
		activeDocIndex = m_DocumentsOther->ActiveDocument->Index;
		for (int i = 0; i < m_DocumentsOther->Count; ++i)
		{
			if (m_DocumentsOther->Document[i]->Modified)
			{
				m_DocumentsOther->Activate(i);
				m_DocumentsOther->Editor->SaveToFile(m_Documents->Document[i]->FileName);
				m_DocumentsOther->Document[i]->Modified = false;
			}
		}
		m_DocumentsOther->Activate(activeDocIndex);
	}
	for (int i = 0; i < (int)m_vFiles.size(); i++)
    {
        m_vFiles[i].bDirty = false;
    }
    m_bDirty = false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::IsFileDirty(int iIndex)
{
    if (0 <= iIndex && iIndex < (int)m_vFiles.size())
    {
        return m_vFiles[iIndex].bDirty;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::MoveUp(int iIndex)
{
    if (0 < iIndex && iIndex < (int)m_vFiles.size())
    {
        // swap elements
        TZXFile tmp = m_vFiles[iIndex];
        m_vFiles[iIndex] = m_vFiles[iIndex - 1];
        m_vFiles[iIndex - 1] = tmp;
        m_bDirty = true;
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::MoveDown(int iIndex)
{
    if (0 <= iIndex && iIndex < (int)m_vFiles.size() - 1)
    {
        // swap elements
        TZXFile tmp = m_vFiles[iIndex];
        m_vFiles[iIndex] = m_vFiles[iIndex + 1];
        m_vFiles[iIndex + 1] = tmp;
        m_bDirty = true;
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::MakeDirty(void)
{
    if (m_bOpeningFile)
        return;
    m_bDirty = true;
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::GetDirty(void)
{
    for (int i = 0; i < (int)m_vFiles.size() && false == m_bDirty; i++)
    {
        m_bDirty |= IsFileDirty(i);
    }
    return m_bDirty;
}
//---------------------------------------------------------------------------
int __fastcall ZXFileManager::Files(void) const
{
    return m_vFiles.size();
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::IsCFile(int iIndex) const
{
    String sExt = ExtractFileExt(GetFilename(iIndex)).Trim().LowerCase();
    return (sExt == ".c" || sExt == ".h" || sExt == ".cpp" || sExt == ".cxx" || sExt == ".hpp");
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::GetLines(int iIndex, TStrings* pLines)
{
    if (0 <= iIndex && iIndex < static_cast<int>(m_vFiles.size()) && pLines != NULL)
    {
        // load the lines of the file for the client
        String sFile = m_vFiles[iIndex].sFile;
        String sFolder;
        PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);
        sFile = sFolder + sFile;
        if (FileExists(sFile))
        {
            pLines->LoadFromFile(sFile);
        }
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::PutLines(int iIndex,  TStrings* pLines)
{
    if (0 <= iIndex && iIndex < static_cast<int>(m_vFiles.size()) && pLines != NULL)
    {
        String sFile = m_vFiles[iIndex].sFile;
        String sFolder;
        PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);
        sFile = sFolder + sFile;
        pLines->SaveToFile(sFile);
        if (m_vFiles[iIndex].iDocumentIndex != -1)
        {
            m_Documents->Open(sFile);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::AdjustTabIndexes(int index)
{
    for (int i = 0; i < (int)m_vFiles.size(); ++i)
    {
        if (m_vFiles[i].iDocumentIndex > index)
        {
            m_vFiles[i].iDocumentIndex = m_vFiles[i].iDocumentIndex - 1;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::RenumberTabs(bool bOtherView)
{
	TSciDocumentTabControl* documents = !bOtherView ? m_Documents : m_DocumentsOther;
	if (documents != NULL)
	{
		for (int i = 0; i < documents->Tabs->Count; ++i)
		{
			String title = ExtractFileName(documents->Document[i]->FileName);
			documents->Tabs->Strings[i] = IntToStr(i + 1) + " " + title;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::ChangeDirectoryAttribute(TCHAR* m_szFdPath)
{
   HANDLE hFile;
   WIN32_FIND_DATA FileInformation;
   TCHAR m_szPath[MAX_PATH];
   TCHAR m_szFolderInitialPath[MAX_PATH];
   TCHAR wildCard[MAX_PATH] = "\\*.*";

   strcpy(m_szPath, m_szFdPath);
   strcpy(m_szFolderInitialPath, m_szFdPath);
   strcat(m_szFolderInitialPath, wildCard);
 
   hFile = ::FindFirstFile(m_szFolderInitialPath, &FileInformation);
   if (hFile != INVALID_HANDLE_VALUE)
   {
      do
      {
         if (FileInformation.cFileName[0] != '.')
         {
            strcpy(m_szPath,m_szFdPath);
            strcat(m_szPath,"\\");
            strcat(m_szPath,FileInformation.cFileName);
            if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
               //it is a sub directory
               ::SetFileAttributes(m_szPath, FILE_ATTRIBUTE_NORMAL);
               ChangeDirectoryAttribute(m_szPath);
            }
            else
            {
               //it is a file
               ::SetFileAttributes(m_szPath, FILE_ATTRIBUTE_NORMAL);
            }
         }
      }
      while (::FindNextFile(hFile, &FileInformation) == TRUE);
      // Close handle
      ::FindClose(hFile);
      DWORD dwError = ::GetLastError();
      if (dwError == ERROR_NO_MORE_FILES)
      {
         //Attributes successfully changed
      }
   }
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::HasOpenDocument()
{
	for (int i = 0; i < (int)m_vFiles.size(); i++)
	{
		if (m_vFiles[i].iDocumentIndex != -1)
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXFileManager::SelectFile(int iIndex)
{
	int docIndex = m_vFiles[iIndex].iDocumentIndex;
	if (docIndex != -1)
	{
		TSciDocumentTabControl* documents = !m_vFiles[iIndex].bOtherView ? m_Documents : m_DocumentsOther;
		documents->Document[docIndex]->Activate();
		g_EditorSettings.Apply(documents->Document[docIndex]);
		g_EditorSettings.Apply((TScintillaMemo*)documents->Editor);
	}
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::ActiveDocument(String& File, int& Line)
{
	if (m_Documents->ActiveDocument != NULL)
	{
		int iDocIndex = m_Documents->ActiveDocument->Index;
		for (int i = 0; i < (int)m_vFiles.size(); i++)
		{
			if (m_vFiles[i].iDocumentIndex == iDocIndex)
            {
                File = m_vFiles[i].sFile;
                Line = m_Documents->Editor->GetCurrentLineNumber();
                return true;
            }
        }
    }
	if (m_DocumentsOther->ActiveDocument != NULL)
	{
		int iDocIndex = m_DocumentsOther->ActiveDocument->Index;
		for (int i = 0; i < (int)m_vFiles.size(); i++)
		{
			if (m_vFiles[i].iDocumentIndex == iDocIndex)
			{
				File = m_vFiles[i].sFile;
				Line = m_DocumentsOther->Editor->GetCurrentLineNumber();
				return true;
			}
		}
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall ZXFileManager::IsActiveDocument(const String& File)
{
    if (m_Documents->ActiveDocument != NULL)
    {
        int iDocIndex = m_Documents->ActiveDocument->Index;
        for (int i = 0; i < (int)m_vFiles.size(); i++)
        {
            if (m_vFiles[i].iDocumentIndex == iDocIndex)
            {
                return File == m_vFiles[i].sFile;
            }
        }
    }
	if (m_DocumentsOther->ActiveDocument != NULL)
	{
		int iDocIndex = m_DocumentsOther->ActiveDocument->Index;
		for (int i = 0; i < (int)m_vFiles.size(); i++)
		{
			if (m_vFiles[i].iDocumentIndex == iDocIndex)
			{
				return File == m_vFiles[i].sFile;
			}
		}
	}
	return false;
}
//---------------------------------------------------------------------------

