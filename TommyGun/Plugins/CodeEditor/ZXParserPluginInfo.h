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
#ifndef ParserPluginInfoH
#define ParserPluginInfoH
//---------------------------------------------------------------------------
#include "ZXPlugin.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Plugin;
//- COMMON PLUGIN INTERFACES ------------------------------------------------
typedef HRESULT(WINAPI *GetDescriptionPtr   )(String& sDescription                                                          );
//- PARSER PLUGIN INTERFACES ------------------------------------------------
typedef HRESULT(WINAPI *GetOptionsPanelPtr  )(TPanel*& OptionsPanel                                                         );
typedef HRESULT(WINAPI *GetResourceTypesPtr )(KXmlInfo*& XmlData, TStringList*& Types                                       );
typedef HRESULT(WINAPI *GetResourcesListPtr )(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources              );
typedef HRESULT(WINAPI *ParseResourcesPtr   )(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData  );
//---------------------------------------------------------------------------
typedef struct
{
    ZXPlugin*               pPlugin;
    String                  sSignature;
    TPanel*                 pParserPanel;
    // interfaces
    GetOptionsPanelPtr      pGetOptionsPanelFunc;
    GetResourceTypesPtr     pGetResourceTypesFunc;
    GetResourcesListPtr     pGetResourcesListFunc;
    ParseResourcesPtr       pParseResourceFunc;
    GetDescriptionPtr       pDescriptionFunc;
} ZXParserPluginInfo;
typedef std::vector<ZXParserPluginInfo*> ZXParserPluginInfoVector;
//---------------------------------------------------------------------------
#endif//ParserPluginInfoH
