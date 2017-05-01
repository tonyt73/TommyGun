//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
#include "ZXDebugFileManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//- STL ---------------------------------------------------------------------
#include <sstream>
#include <iostream>
//---------------------------------------------------------------------------
#include "SafeMacros.h"
//---------------------------------------------------------------------------
__fastcall ZXDebugFileManager::ZXDebugFileManager()
{
}
//---------------------------------------------------------------------------
__fastcall ZXDebugFileManager::~ZXDebugFileManager()
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXDebugFileManager::LoadDebugFile(const String& DebugFile)
{
    if (FileExists(DebugFile))
    {
        // reset the map
        for (int i = 0; i < 65536; i++)
        {
            m_DebugMap[i].Line = -1;
            m_DebugMap[i].File = "";
        }

        // load the new map
        TStringList* lines = new TStringList();
        lines->LoadFromFile(DebugFile);

        for (int i = 0; i < lines->Count; i++)
        {
            String line = lines->Strings[i].Trim();
            int s1 = line.Pos('\t');
            int s2 = line.LastDelimiter("\t");
            String saddress = line.SubString(1, s1 - 1);
            String sline = line.SubString(s1 + 1, s2 - s1 - 1);
            String file = line.SubString(s2 + 1, line.Length() - s2);
            unsigned int lineNo = StrToInt(sline);
            unsigned int address = 0;
            std::stringstream ss;
            ss << std::hex << saddress.c_str();
            ss >> address;
            m_DebugMap[address].Line = lineNo;
            m_DebugMap[address].File = file;
        }

        SAFE_DELETE(lines);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXDebugFileManager::GetLocation(unsigned int Address, String& File, int& Line)
{
    File = m_DebugMap[Address].File;
    Line = m_DebugMap[Address].Line;
}
//---------------------------------------------------------------------------
bool __fastcall ZXDebugFileManager::DoesCodeExistAt(unsigned int Address)
{
    return m_DebugMap[Address].File.Length() > 1; 
}
//---------------------------------------------------------------------------
