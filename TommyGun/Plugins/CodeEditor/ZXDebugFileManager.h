//---------------------------------------------------------------------------
#ifndef ZXDebugFileManagerH
#define ZXDebugFileManagerH
//- VCL ---------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
#include <map>
//---------------------------------------------------------------------------
class ZXDebugFileManager
{
public:
            __fastcall  ZXDebugFileManager();
            __fastcall ~ZXDebugFileManager();

    bool    __fastcall  LoadDebugFile(const String& DebugFile);
    void    __fastcall  GetLocation(unsigned int Address, String& File, int& Line);
    bool    __fastcall  DoesCodeExistAt(unsigned int Address);

private:
    typedef struct
    {
        String File;
        unsigned int Line;
    } TFileInfo;

    TFileInfo   m_DebugMap[65536];
};
//---------------------------------------------------------------------------
#endif
