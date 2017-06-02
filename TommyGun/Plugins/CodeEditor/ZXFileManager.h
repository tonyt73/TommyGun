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
#ifndef ZXFileManagerH
#define ZXFileManagerH
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
#include "SciDocTabCtrl.hpp"
//---------------------------------------------------------------------------
using namespace Scorpio;
//---------------------------------------------------------------------------
class ZXFileManager
{
private:
    class TZXFile
    {
        public:
        __fastcall TZXFile()
        : bDirty(false)
        , iDocumentIndex(-1)
		, pLines(NULL)
		, bOtherView(false)
        {
        }
        
        String              sFile;
        bool                bDirty;
        TStringList*        pLines;
		int                 iDocumentIndex;
		bool				bOtherView;
    };

private:
    std::vector<TZXFile>    m_vFiles;
    bool                    m_bDirty;
    bool                    m_bOpeningFile;
    TSciDocumentTabControl* m_Documents;
    TSciDocumentTabControl* m_DocumentsOther;

    int         __fastcall  LoadFile(int iIndex, bool inOtherView);
    bool        __fastcall  GetDirty(void);
    void        __fastcall  RenumberTabs();

public:
                __fastcall  ZXFileManager();
                __fastcall ~ZXFileManager();

    void        __fastcall  sciEditorModified(TObject *Sender, const int position, const int modificationType, PChar text, const int len, const int linesAdded, const int line, const int foldLevelNow, const int foldLevelPrev);
    void        __fastcall  sciEditorModifiedOther(TObject *Sender, const int position, const int modificationType, PChar text, const int len, const int linesAdded, const int line, const int foldLevelNow, const int foldLevelPrev);
	void        __fastcall  SetSciTabControls(TSciDocumentTabControl* documents, TSciDocumentTabControl* otherDocuments);

    void        __fastcall  Clear(void);
    int         __fastcall  Add(const String& sFile, bool bSilent = false);
    void        __fastcall  Remove(int iIndex);
    int         __fastcall  Rename(int iIndex, const String& sNewName);
    String      __fastcall  GetFilename(int iIndex) const;
    int         __fastcall  GetLineCount(int iIndex);
    bool        __fastcall  FileNameExists(const String& sFile);
    bool        __fastcall  IsFileDirty(int iIndex);
    bool        __fastcall  MoveUp(int iIndex);
    bool        __fastcall  MoveDown(int iIndex);
    void        __fastcall  MakeDirty(void);
    int         __fastcall  Open(int iIndex, bool inOtherView);
    void        __fastcall  Save(void);
    bool        __fastcall  Close(String sFile);
    bool        __fastcall  Close(int iIndex);
    int         __fastcall  FindFile(const String& sFile);
    int         __fastcall  Files(void) const;
    bool        __fastcall  IsCFile(int iIndex) const;
    bool        __fastcall  GetLines(int iIndex, TStrings* pLines);
    void        __fastcall  PutLines(int iIndex, TStrings* pLines);
    void        __fastcall  AdjustTabIndexes(int index);
    void        __fastcall  ChangeDirectoryAttribute(TCHAR* m_szFdPath);
    bool        __fastcall  HasOpenDocument();
    bool        __fastcall  IsFileOpen(int iIndex);
    void        __fastcall  SelectFile(int iIndex);
    bool        __fastcall  ActiveDocument(TSciDocumentTabControl* Documents, String& File, int& Line);
    bool        __fastcall  IsActiveDocument(TSciDocumentTabControl* Documents, const String& File);
    int         __fastcall  OpenedDocuments();
    bool        __fastcall  InOtherView(int iIndex);

    HRESULT     __fastcall  Load(KXmlInfo& xmlInfo);
    HRESULT     __fastcall  Save(KXmlInfo& xmlInfo);

    __property bool         IsDirty         = { read = GetDirty         };
    __property bool         IsOpeningFile   = { read = m_bOpeningFile   };
};
//---------------------------------------------------------------------------
#endif
