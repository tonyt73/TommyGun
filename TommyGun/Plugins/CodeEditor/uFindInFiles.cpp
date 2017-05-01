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
#include "fSearching.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TFindInFiles::TFindInFiles()
: m_FoundItems(NULL)
, m_bCaseSensitive(false)
, m_bWholeWords(false)
, m_bRecursive(false)
, m_Text("")
, m_Folder("")
{
    m_FoundItems = new TStringList;
}
//---------------------------------------------------------------------------
__fastcall TFindInFiles::~TFindInFiles()
{
    SAFE_DELETE(m_FoundItems);
}
//---------------------------------------------------------------------------
void __fastcall TFindInFiles::Find(ZXFileManager& FileManager)
{
    if (!m_bCaseSensitive)
    {
        m_Text = m_Text.LowerCase();
    }

    TStrings* FileLines = new TStringList();
    for (int i = 0; i < FileManager.Files(); i++)
    {
        if (FileManager.GetLines(i, FileLines))
        {
            SearchLines(FileLines, FileManager.GetFilename(i));
        }
        else
        {
            m_FoundItems->Add("Failed to open file: " + FileManager.GetFilename(i));
        }
    }
    SAFE_DELETE(FileLines);
}
//---------------------------------------------------------------------------
void __fastcall TFindInFiles::SearchLines(TStrings* Lines, const String& File)
{
    for (int i = 0; i < Lines->Count; i++)
    {
        String Line = Lines->Strings[i];
        int iPos = 0;
        if (!m_bCaseSensitive)
        {
            Line = Line.LowerCase();
        }

        // no need to find whole words
        iPos = Line.Pos(m_Text);
        if (m_bWholeWords && iPos)
        {
            int iLen = m_Text.Length();
            int iEnd = Line.Length() - iLen + 1;
            // need to test if its the whole word only
            bool bLeftOK = iPos == 1 || (Line[iPos-1] <= 32);
            bool bRightOK = iPos == iEnd || (Line[iPos + iLen] <= 32);
            if (!bLeftOK || !bRightOK)
            {
                // not whole word
                int iOldPos = iPos;
                iPos = 0;
                // need to search the rest of the line slowly to find another match
                for (int j = iOldPos + 1; j <= iEnd; j++)
                {
                    String Sub = Line.SubString(j, iLen);
                    if (Sub == m_Text)
                    {
                        bLeftOK = Line[j-1] <= 32;
                        bRightOK = j == iEnd || (Line[j + iLen] <= 32);
                        if (bLeftOK && bRightOK)
                        {
                            iPos = j;
                            break;
                        }
                    }
                }
            }
        }
        if (iPos)
        {
            // match found
            String Found = File + "(" + IntToStr(i+1) + ", " + IntToStr(iPos) + "): " + Lines->Strings[i];
            m_FoundItems->Add(Found);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFindInFiles::SearchFolder(const String& sFolder, const String& sFilemask)
{
    // find the files in this folder with the supplied file mask
    TSearchRec sr;
    if (0 == FindFirst(sFolder + sFilemask, faAnyFile, sr))
    {
        do
        {
            if ((sr.Attr & (faDirectory | faSysFile)) == 0)
            {
                // read the file
                TStrings* Lines = new TStringList;
                Lines->LoadFromFile(sFolder + sr.Name);
                SearchLines(Lines, sFolder + sr.Name);
                SAFE_DELETE(Lines);
            }
            Application->ProcessMessages();
        }
        while(0 == FindNext(sr) && (frmSearching == NULL || frmSearching->ModalResult != mrCancel));
        FindClose(sr);
    }
    // find the folders in this folder and search them
    if (m_bRecursive)
    {
        TSearchRec sr;
        if (0 == FindFirst(sFolder + "*.*", faAnyFile, sr))
        {
            do
            {
                if ((sr.Attr & faDirectory) && sr.Name[1] != '.')
                {
                    String sNewFolder = sFolder + sr.Name + "\\";
                    if (DirectoryExists(sNewFolder))
                    {
                        SearchFolder(sNewFolder, sFilemask);
                    }
                }
                Application->ProcessMessages();
            }
            while(0 == FindNext(sr) && (frmSearching == NULL || frmSearching->ModalResult != mrCancel));
            FindClose(sr);
        }
    }
}
//---------------------------------------------------------------------------

