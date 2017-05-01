//---------------------------------------------------------------------------
#ifndef ZXSymbolsManagerH
#define ZXSymbolsManagerH
//- VCL ---------------------------------------------------------------------
#include <Classes.hpp>
//- STL ---------------------------------------------------------------------
#include <map>
#include <list>
//---------------------------------------------------------------------------
class ZXSymbolsManager
{
public:
                    __fastcall  ZXSymbolsManager();
                    __fastcall ~ZXSymbolsManager();

    bool            __fastcall  LoadMapFile(const String& MapFile);
    String          __fastcall  GetSymbol(unsigned int Value);
    unsigned int    __fastcall  GetSymbol(const String& Symbol);
    void            __fastcall  GetSymbols(std::list<String>& Symbols);

private:
    std::map<unsigned int, String>  m_SymbolsMap;
};
//---------------------------------------------------------------------------
#endif
