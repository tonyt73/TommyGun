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
#ifndef ZXTableManagerH
#define ZXTableManagerH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
class ZXTableManager
{
private:
    typedef struct
    {
        String                      sName;
        std::vector<String>         Strings;
        std::vector<String>         IDs;
    } ZXStringTable;

    typedef std::vector<ZXStringTable>  ZXTables;

    ZXTables            m_Tables;
    bool                m_bDirty;

    int     __fastcall  GetTableCount(void);
    int     __fastcall  FindTable(const String& sName);

public:
            __fastcall  ZXTableManager();
            __fastcall ~ZXTableManager();

    bool    __fastcall  Load(KXmlInfo* xmlInfo);
    bool    __fastcall  Save(KXmlInfo* xmlInfo);
    void    __fastcall  Clear(void);

    int     __fastcall  Strings(unsigned int iTableIndex);
    String  __fastcall  GetName(unsigned int iTableIndex);
    String  __fastcall  GetString(unsigned int iTableIndex, unsigned int iStringIndex);
    String  __fastcall  GetID(unsigned int iTableIndex, unsigned int iStringIndex);
    bool    __fastcall  TableExists(const String& sName);

    int     __fastcall  AddTable(const String& sName);
    int     __fastcall  RemoveTable(const String& sName);
    int     __fastcall  CloneTable(unsigned int iTableIndex, const String& sName);
    int     __fastcall  RenameTable(unsigned int iTableIndex, const String& sName);
    int     __fastcall  UpTable(unsigned int iTableIndex);
    int     __fastcall  DownTable(unsigned int iTableIndex);

    int     __fastcall  AddString(unsigned int iTableIndex, const String& sID, const String& sValue);
    int     __fastcall  RemoveString(unsigned int iTableIndex, unsigned int iStringIndex);
    int     __fastcall  CloneString(unsigned int iTableIndex, unsigned int iStringIndex);
    int     __fastcall  SetString(unsigned int iTableIndex, unsigned int iStringIndex, const String& sValue);
    int     __fastcall  SetID(unsigned int iTableIndex, unsigned int iStringIndex, const String& sID);
    int     __fastcall  UpString(unsigned int iTableIndex, unsigned int iStringIndex);
    int     __fastcall  DownString(unsigned int iTableIndex, unsigned int iStringIndex);

    __property  int     Tables  = { read = GetTableCount            };
    __property  bool    IsDirty = { read = m_bDirty                 };
};
//---------------------------------------------------------------------------
#endif

