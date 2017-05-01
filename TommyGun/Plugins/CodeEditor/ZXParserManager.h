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
#ifndef ZXParserManagerH
#define ZXParserManagerH
//---------------------------------------------------------------------------
#include "fInsertResource.h"
#include "ZXParserPluginInfo.h"
//---------------------------------------------------------------------------
class ZXParserManager
{
private:
    TfrmInsertResource*         m_frmInsertResource;
    ZXParserPluginInfoVector*   m_ParserPlugins;
    TPanel*                     m_OptionsPanel;
    TWinControl*                m_OptionParent;
    KXmlInfo*                   m_XmlData;
    TStrings*                   m_SourceCode;
    String                      m_CommentL;
    String                      m_CommentR;

    void    __fastcall  OnResourceParserChange(TObject* Sender);
    void    __fastcall  OnResourceTypeChange(TObject* Sender);
    void    __fastcall  OnResourceInsert(TObject* Sender);

    void    __fastcall  LoadResources(void);
    void    __fastcall  LoadParsers(void);
    void    __fastcall  LoadResourceTypes(void);

    ZXParserPluginInfo* __fastcall FindParser(const String& sParserDescription);
    int     __fastcall  FindLine(const TStrings*& pSourceCode, const String& sText, int iStartLine = 0) const;
    int     __fastcall  FindLineEnd(const TStrings*& pSourceCode, int iStartLine) const;
    int     __fastcall  FindEndOfResources(TStrings*& pSourceCode) const;
    bool    __fastcall  IsResourceIsUnique(const TStrings*& pSourceCode, const String& sResourceTag) const;
    void    __fastcall  InsertResource(const String& sResource, const String& ParserData, TStrings* pSourceCode, TStringList* ParsedCode, bool bBegin, bool bEnd);
    //void    __fastcall  ParseAGD(TStrings*& Lines);

public:
            __fastcall  ZXParserManager();
            __fastcall ~ZXParserManager();

    void    __fastcall  Initialize(ZXParserPluginInfoVector* ParserPlugins);
    bool    __fastcall  Execute(TStrings*& Lines, bool bIsCFile);
    bool    __fastcall  Update(TStrings*& Lines, const String& Filename, bool bIsCFile);
    void    __fastcall  Hide(void);
};
//---------------------------------------------------------------------------
#endif

