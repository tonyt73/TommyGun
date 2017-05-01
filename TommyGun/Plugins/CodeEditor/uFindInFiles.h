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
#ifndef uFindInFilesH
#define uFindInFilesH
//---------------------------------------------------------------------------
#include "ZXFileManager.h"
//---------------------------------------------------------------------------
enum TSearchWhere { swSearchProject };
class TFindInFiles
{
private:
    TStrings*           m_FoundItems;

    bool                m_bCaseSensitive;   // case sensitive matches only
    bool                m_bWholeWords;      // check for whole words only
    bool                m_bRecursive;       // search sub folders
    String              m_Text;             // text to find
    String              m_Folder;           // the folder to search (can include wildcard filter)

    void    __fastcall  SearchLines(TStrings* Lines, const String& File);
    void    __fastcall  SearchFolder(const String& sFolder, const String& sFilemask);

public:
            __fastcall  TFindInFiles();
            __fastcall ~TFindInFiles();

    void    __fastcall  Find(ZXFileManager& FileManager);

    __property bool     CaseSensitive   = { read = m_bCaseSensitive , write = m_bCaseSensitive  };
    __property bool     WholeWords      = { read = m_bWholeWords    , write = m_bWholeWords     };
    __property bool     Recursive       = { read = m_bRecursive     , write = m_bRecursive      };
    __property String   Text            = { read = m_Text           , write = m_Text            };
    __property String   Folder          = { read = m_Folder         , write = m_Folder          };
    __property TStrings* Strings        = { read = m_FoundItems                                 };
};
//---------------------------------------------------------------------------
#endif
