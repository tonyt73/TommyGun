//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
#include "ZXSymbolsManager.h"
//- STL ---------------------------------------------------------------------
#include <sstream>
#include <iostream>
//---------------------------------------------------------------------------
#include "SafeMacros.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXSymbolsManager::ZXSymbolsManager()
{
}
//---------------------------------------------------------------------------
__fastcall ZXSymbolsManager::~ZXSymbolsManager()
{
    m_SymbolsMap.clear();
}
//---------------------------------------------------------------------------
bool __fastcall ZXSymbolsManager::LoadMapFile(const String& MapFile)
{
    if (FileExists(MapFile))
    {
        m_SymbolsMap.clear();
        TStringList* lines = new TStringList();
        lines->LoadFromFile(MapFile);

        for (int i = 0; i < lines->Count; i++)
        {
            String line = lines->Strings[i].Trim();
            int s1 = line.Pos('\t');
            if (!s1) s1 = line.Pos(' ');
            int s2 = line.LastDelimiter(" ");
            String symbol = line.SubString(1, s1 - 1);
            String svalue = line.SubString(s2 + 1, line.Length() - 1 - s2);
            unsigned int value = 0;
            std::stringstream ss;
            ss << std::hex << svalue.c_str();
            ss >> value;
            m_SymbolsMap[value] = symbol;
        }

        SAFE_DELETE(lines);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
String __fastcall ZXSymbolsManager::GetSymbol(unsigned int Value)
{
    std::map<unsigned int, String>::iterator it = m_SymbolsMap.find(Value);
    if (it != m_SymbolsMap.end())
    {
        return it->second;
    }
    return "";
}
//---------------------------------------------------------------------------
unsigned int __fastcall ZXSymbolsManager::GetSymbol(const String& Symbol)
{
    for (std::map<unsigned int, String>::iterator it = m_SymbolsMap.begin(); it != m_SymbolsMap.end(); ++it)
    {
        if (it->second == Symbol)
        {
            return it->first;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
void __fastcall ZXSymbolsManager::GetSymbols(std::list<String>& Symbols)
{
    for (std::map<unsigned int, String>::iterator it = m_SymbolsMap.begin(); it != m_SymbolsMap.end(); ++it)
    {
        Symbols.push_back(it->second);
    }
}
//---------------------------------------------------------------------------
