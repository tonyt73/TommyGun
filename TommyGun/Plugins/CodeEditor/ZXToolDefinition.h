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
#ifndef ZXToolDefinitionH
#define ZXToolDefinitionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <vector>
//---------------------------------------------------------------------------
enum TToolType
{
    ttBuilder,
    ttEmulator
};
//---------------------------------------------------------------------------
class ZXToolDefinition
{
public:
            __fastcall  ZXToolDefinition();
            __fastcall ~ZXToolDefinition();
    bool    __fastcall  Save(KXmlInfo& xmlInfo);
    bool    __fastcall  Load(KXmlInfo& xmlInfo);

    String      m_Name;
    String      m_Executable;
    String      m_DefaultParameters;
    TToolType   m_Type;
    String      m_Extensions;
    String      m_PrefixError;
    String      m_PrefixFile;
    String      m_PrefixLine;
    bool        m_AcceptsMultipleInputFiles;
};
//---------------------------------------------------------------------------
class ZXToolDefinitions
{
private:
    std::vector<ZXToolDefinition>       m_ToolDefinitions;
public:
            __fastcall  ZXToolDefinitions();
            __fastcall ~ZXToolDefinitions();
    bool    __fastcall  Save(void);
    bool    __fastcall  Load(void);

    bool    __fastcall  Add(ZXToolDefinition& definition);
    bool    __fastcall  Update(int index, ZXToolDefinition& definition);
    bool    __fastcall  Remove(int index);

    bool    __fastcall  Get(int i, ZXToolDefinition& definition);
    int     __fastcall  GetIndex(String name);
    int     __fastcall  GetExecutableIndex(String name, bool ignorePath = false);
    bool    __fastcall  Exists(String name);
    bool    __fastcall  ExecutableExists(String name);
    int     __fastcall  Count() { return m_ToolDefinitions.size(); }
};
//---------------------------------------------------------------------------
#endif
