//---------------------------------------------------------------------------
#pragma hdrstop
#include "pch.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GameEditor;
//---------------------------------------------------------------------------
__fastcall Sounds::Sounds()
: m_IsDirty(false)
, m_PropertyNode(-1)
{
}
//---------------------------------------------------------------------------
Sounds::~Sounds()
{
}
//---------------------------------------------------------------------------
void __fastcall Sounds::Init(TListView* availableSfx, TListView* gameSfx)
{
    m_AvailableSfx = availableSfx;
    m_GameSfx = gameSfx;
    m_PropertyNode = frmGameEditor->GetPropertyEditor().AddRootNode(this, "Sounds", tviSounds);
    //frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Key7", cKeyInfo[m_Keys[6]].key);
}
//---------------------------------------------------------------------------
bool __fastcall Sounds::FindStr(const AnsiString& line, const AnsiString& subStr, AnsiString& value)
{
    int pos = line.LowerCase().Pos(subStr);
    if (pos > 0)
    {
        for (int s = pos + 1; s <= line.Length(); ++s)
        {
            if (line[s] == ' ' || line[s] == ':')
            {
                value = line.SubString(s + 1, line.Length()).Trim();
                return true;
            }
        }
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall Sounds::Load(KXmlInfo& xmlInfo)
{
    // load the available sound
    AnsiString sfxPath = ExtractFilePath(Application->ExeName) + "AGD\\";
    AnsiString sfxFiles = sfxPath + "*.sfx";
    TSearchRec sr;
    TStrings* Lines = new TStringList;
    if (0 == FindFirst(sfxFiles, faAnyFile, sr))
    {
        do
        {
            if ((sr.Attr & (faDirectory | faSysFile)) == 0)
            {
                // read the file
                Lines->Clear();
                Lines->LoadFromFile(sfxPath + sr.Name);
                TSoundInfo si;
                si.file = sr.Name;
                for (int i = 0; i < Lines->Count; ++i)
                {
                    AnsiString line = Lines->Strings[i];
                    if (!FindStr(line, "author", si.author))
                    {
                        if (!FindStr(line, "name", si.name))
                        {
                            FindStr(line, "description", si.description);
                        }
                    }
                }
                if (si.name == "")
                {
                    si.name = ExtractFileName(si.file);
                }
                m_AvailableSounds.push_back(si);
                TListItem* item = m_AvailableSfx->Items->Add();
                if (SAFE_PTR(item))
                {
                    item->Caption = si.name;
                    item->SubItems->Add(si.author);
                    item->SubItems->Add(si.description);
                }
            }
        }
        while(0 == FindNext(sr));
        FindClose(sr);
    }
    SAFE_DELETE(Lines);

    bool bLoaded = false;
    KXmlInfo* Sounds;
    if (xmlInfo.Find(Sounds, "Sounds", 0))
    {
        // load the sound filenames
        AnsiString file;
        for (int i = 0;;i++)
        {
            KXmlInfo* File;
            if (!Sounds->Find(File, "File", i))
            {
                break;
            }
            file = File->GetText();
            // find the file in the m_AvailableSounds list
            for (unsigned int s = 0; s < m_AvailableSounds.size(); s++)
            {
                if (m_AvailableSounds[s].file == file)
                {
                    m_GameSounds.push_back(s);
                    break;
                }
            }
        }
        UpdateList();
        bLoaded = true;
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
void __fastcall Sounds::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo* Node;
    if (xmlInfo.Find(Node, "Sounds", 0))
    {
        xmlInfo.Remove(Node);
    }
    // create a new map editor node
    KXmlInfo sounds("Sounds");
    // store the map details
    for (unsigned int i = 0; i < m_GameSounds.size(); i++)
    {
        sounds.Add("File", m_AvailableSounds[m_GameSounds[i]].file);
    }
    xmlInfo.Add(sounds);
    m_IsDirty = false;
}
//---------------------------------------------------------------------------
void __fastcall Sounds::OnPropertyChanged(int node)
{
}
//---------------------------------------------------------------------------
void __fastcall Sounds::Add()
{
    if (m_AvailableSfx->Selected != NULL)
    {
        std::vector<int>::iterator it = std::find(m_GameSounds.begin(), m_GameSounds.end(), m_AvailableSfx->Selected->Index);
        if (it == m_GameSounds.end())
        {
            m_GameSounds.push_back(m_AvailableSfx->Selected->Index);
            UpdateList();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall Sounds::Remove()
{
    if (m_GameSfx->Selected)
    {
        m_GameSounds.erase(m_GameSounds.begin() + m_GameSfx->Selected->Index);
        m_GameSfx->Selected = NULL;
        UpdateList();
    }
}
//---------------------------------------------------------------------------
void __fastcall Sounds::Up()
{
    if (m_GameSfx->Selected)
    {
        int si = m_GameSfx->Selected->Index;
        int index = m_GameSounds[si];
        m_GameSounds.erase(m_GameSounds.begin() + si);
        m_GameSounds.insert(m_GameSounds.begin() + si - 1, index);
        m_GameSfx->Selected = NULL;        
        UpdateList(si-1);
    }
}
//---------------------------------------------------------------------------
void __fastcall Sounds::Down()
{
    if (m_GameSfx->Selected)
    {
        int si = m_GameSfx->Selected->Index;
        int index = m_GameSounds[si];
        m_GameSounds.erase(m_GameSounds.begin() + si);
        m_GameSounds.insert(m_GameSounds.begin() + si + 1, index);
        m_GameSfx->Selected = NULL;
        UpdateList(si+1);
    }
}
//---------------------------------------------------------------------------
void __fastcall Sounds::UpdateList(int si)
{
    int index = si;
    if (m_GameSfx->Selected) index = m_GameSfx->Selected->Index;
    m_GameSfx->Items->Clear();
    for (unsigned int i = 0; i < m_GameSounds.size(); i++)
    {
        TListItem* item = m_GameSfx->Items->Add();
        if (SAFE_PTR(item))
        {
            item->Caption = "FX"+IntToStr(i);
            item->SubItems->Add(m_AvailableSounds[m_GameSounds[i]].name);
            if (item->Index == index) m_GameSfx->Selected = item;
        }
    }
}
//---------------------------------------------------------------------------


