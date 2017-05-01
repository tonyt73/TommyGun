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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace Plugin;
using namespace StringTableParser;
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from CodeEditor.cpp to create a new Plugin object. The StringTableEditor.cpp only uses the
 * Base class reference. So this function returns a Plugin object to use of type class ZXBasePlugin.
 * @return  ZXBasePlugin a ZXBasePlugin compatible object
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
StringTableParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new StringTableParserPlugin();
}
//---------------------------------------------------------------------------
// Constructor
/**
 * Allocates resource for use by the Plugin class
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
__fastcall StringTableParserPlugin::StringTableParserPlugin()
{
    RL_METHOD
    frmStringTableParserOptions = new TfrmStringTableParserOptions(NULL);
}
//---------------------------------------------------------------------------
// Destructor
/**
 * Frees the resources of the Plugin class
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
__fastcall StringTableParserPlugin::~StringTableParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmStringTableParserOptions);
    Release();
}
//---------------------------------------------------------------------------
// InitialisePlugin
/**
 * Initialises the plugin for use
 * @param   PluginHandle the handle allocated to the plugin
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall StringTableParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmStringTableParserOptions))
    {
        hResult = frmStringTableParserOptions->Initialize(pPlugin);
    }
    return hResult;
}
//---------------------------------------------------------------------------
// ReleasePlugin
/**
 * Releases the resources associated with the Plugin
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall StringTableParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmStringTableParserOptions))
    {
        hResult = frmStringTableParserOptions->Release();
    }
    SAFE_DELETE(frmStringTableParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall StringTableParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall StringTableParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmStringTableParserOptions))
    {
        Panel = frmStringTableParserOptions->panStringTableParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall StringTableParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Types))
    {
        Types->Clear();
        KXmlInfo* StringTableEditor = XmlData->GetNode("StringEditor", 0);
        if (true == SAFE_PTR(StringTableEditor))
        {
            Types->Add("Master String Table");
            Types->Add("String Tables");
        }
        return Types->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;
}
//---------------------------------------------------------------------------
HRESULT __fastcall StringTableParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Resources))
    {
        Resources->Clear();
        KXmlInfo* StringTableEditor = XmlData->GetNode("StringEditor", 0);
        if (true == SAFE_PTR(StringTableEditor))
        {
            KXmlInfo* Tables = StringTableEditor->GetNode("Tables", 0);
            if (true == SAFE_PTR(Tables))
            {
                if (sType == "Master String Table")
                {
                    Resources->Add("Master Table");
                }
                else
                {
                    Resources->Add("All String Tables");
                }
            }
        }
        return Resources->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;
}
//---------------------------------------------------------------------------
HRESULT __fastcall StringTableParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
{
    HRESULT hResult = E_POINTER;

    if (ParserData != "[Begin]" && ParserData != "[End]")
    {
        String sType;
        String sName;
        GetResourceInfo(Resource, sType, sName);
        
        if (true == SAFE_PTR(XmlData) && SAFE_PTR(Code))
        {
            if (sType == "Master String Table")
            {
                return ParseMasterTable(XmlData, Code, sName);
            }

            return ParseStringTable(XmlData, Code);
        }
    }
    else
    {
        // ignore the begin and end pre and post parsing tags
        hResult = E_FAIL;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall StringTableParserPlugin::ParseMasterTable(KXmlInfo*& XmlData, TStringList*& Code, const String& sName)
{
    HRESULT hResult = E_FAIL;
    KXmlInfo* StringTableEditor = XmlData->GetNode("StringEditor", 0);
    if (true == SAFE_PTR(StringTableEditor))
    {
        KXmlInfo* Tables = StringTableEditor->GetNode("Tables", 0);
        if (true == SAFE_PTR(Tables))
        {
            Code->Add(";");
            Code->Add("; MASTER STRING TABLE");
            Code->Add(";");
            Code->Add("MasterStringTable:");
            // loop through the tables and load the applicable data
            for (KXmlNodes::iterator it = Tables->begin(); it != Tables->end(); it++)
            {
                KXmlInfo* pName = (*it)->GetNode("Name");
                if (SAFE_PTR(pName))
                {
                    Code->Add("    defw " + pName->GetText());
                }
            }
            hResult = S_OK;
        }
    }

    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall StringTableParserPlugin::ParseStringTable(KXmlInfo*& XmlData, TStringList*& Code)
{
    HRESULT hResult = E_FAIL;
    if (true == SAFE_PTR(XmlData))
    {
        KXmlInfo* EditorNode;
        if (XmlData->Find(EditorNode, "StringEditor"))
        {
            KXmlInfo* TablesNode = EditorNode->GetNode("Tables");
            if (true == SAFE_PTR(TablesNode))
            {
                Code->Add(";");
                Code->Add("; STRING TABLES");
                Code->Add(";");
                Code->Add("");
                // loop through the tables and load the applicable data
                for (KXmlNodes::iterator it = TablesNode->begin(); it != TablesNode->end(); it++)
                {
                    KXmlInfo* pName = (*it)->GetNode("Name");
                    if (SAFE_PTR(pName))
                    {
                        Code->Add(";");
                        Code->Add("; String Table: " + pName->GetText());
                        Code->Add(";");
                        Code->Add(pName->GetText() + ":");
                        int iIndex = 0;
                        for (KXmlNodes::iterator itT = (*it)->begin(); itT != (*it)->end(); itT++)
                        {
                            if ((*itT)->GetName() == "String")
                            {
                                KXmlInfo* pID = (*itT)->GetNode("ID");
                                KXmlInfo* pValue = (*itT)->GetNode("Value");
                                if (SAFE_PTR(pID) && SAFE_PTR(pValue))
                                {
                                    if (pID->GetText().Trim() != "")
                                    {
                                        Code->Add("defw " + pID->GetText());
                                    }
                                    else
                                    {
                                        Code->Add("defw " + pName->GetText() + NumToStr(iIndex, '0'));
                                    }
                                }
                            }
                            iIndex++;
                        }
                    }
                }
                Code->Add("");
                Code->Add(";");
                Code->Add("; STRINGS");
                Code->Add(";");
                // loop through the tables and load the applicable data
                for (KXmlNodes::iterator it = TablesNode->begin(); it != TablesNode->end(); it++)
                {
                    KXmlInfo* pName = (*it)->GetNode("Name");
                    if (SAFE_PTR(pName))
                    {
                        int iIndex = 0;
                        for (KXmlNodes::iterator itT = (*it)->begin(); itT != (*it)->end(); itT++)
                        {
                            if ((*itT)->GetName() == "String")
                            {
                                KXmlInfo* pID = (*itT)->GetNode("ID");
                                KXmlInfo* pValue = (*itT)->GetNode("Value");
                                if (SAFE_PTR(pID) && SAFE_PTR(pValue))
                                {
                                    String sName;
                                    String sLine;
                                    if (pID->GetText().Trim() != "")
                                    {
                                        sName = pID->GetText();
                                    }
                                    else
                                    {
                                        String sName = pName->GetText() + NumToStr(iIndex, '0');
                                    }
                                    sLine = sName + ": " + AnsiString::StringOfChar(' ', 20 - sName.Length()) + "defb ";

                                    for (int i = 1; i <= pValue->GetText().Length(); i++)
                                    {
                                        sLine += "$" + IntToHex(pValue->GetText()[i], 2) + ",";
                                    }
                                    sLine += "$00";

                                    Code->Add(sLine);
                                }
                            }
                            iIndex++;
                        }
                    }
                }
                hResult = S_OK;
            }
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
/*void __fastcall StringTableParserPlugin::ParseScreen(KXmlInfo*& XmlData, TStringList*& Code)
{
    bool bParsed = true;
    int iLeft = 0;
    int iTop = 0;
    TStringList* NewCode = NULL;
    try
    {
        // create a temporary string list to place the parsed data
        NewCode = new TStringList;
        iLeft = XmlData->GetNode("Left", 0)->GetInt();
        iTop = XmlData->GetNode("Top", 0)->GetInt();

        KXmlInfo* Tiles = XmlData->GetNode("Tiles", 0);
        KXmlInfo* DupOf = XmlData->GetNode("DuplicateOf", 0);
        int iTiles = 0;
        String sDEFx = frmStringTableParserOptions->chkUseDefw->Checked ? "defw " : "defb ";
        if (true == SAFE_PTR(DupOf))
        {
            // don't generate this screen
            m_StringTableTable.push_back(m_StringTableTable[DupOf->GetInt()]);
        }
        else if (true == SAFE_PTR(Tiles))
        {
            NewCode->Add(";");
            NewCode->Add("; SCREEN (" + IntToStr(iLeft) + ", " + IntToStr(iTop) + ")");
            NewCode->Add(";");
            NewCode->Add(m_sPrefix + NumToStr(iLeft, '0') + "x" + NumToStr(iTop, '0') + ":");

            int iTiles = Tiles->size();
            NewCode->Add("defb " + NumToStr(iTiles) + "              ; " + IntToStr(iTiles) + " tiles");

            // loop through all the tiles
            for (KXmlNodes::iterator it = Tiles->begin(); it != Tiles->end(); it++)
            {
                String sName = (*it)->GetNode("Name", 0)->GetText();
                int x = (*it)->GetNode("Left", 0)->GetInt();
                int y = (*it)->GetNode("Top", 0)->GetInt();
                int iTile = GetTileIndex(sName);
                if (frmStringTableParserOptions->chkConvertX->Checked) x /= 8;
                if (frmStringTableParserOptions->chkConvertY->Checked) y /= 8;
                NewCode->Add(sDEFx + NumToStr(iTile) + ", " + NumToStr(x) + ", " + NumToStr(y) + "    ; " + sName);
            }
            m_StringTableTable.push_back(m_sPrefix + NumToStr(iLeft, '0') + "x" + NumToStr(iTop, '0'));
        }
        else
        {
            NewCode->Add(";");
            NewCode->Add("; SCREEN (" + IntToStr(iLeft) + ", " + IntToStr(iTop) + ")");
            NewCode->Add(";");
            NewCode->Add(m_sPrefix + NumToStr(iLeft, '0') + "x" + NumToStr(iTop, '0') + ":");

            NewCode->Add(sDEFx + NumToStr(0) + "              ; no tiles");
            m_StringTableTable.push_back("0");
        }
    }
    catch(...)
    {
        bParsed = false;
    }
    if (bParsed)
    {
        // add the code
        if (true == SAFE_PTR(NewCode))
        {
            Code->AddStrings(NewCode);
        }
    }
    SAFE_DELETE(NewCode);
}
*/
//---------------------------------------------------------------------------
void __fastcall StringTableParserPlugin::GetResourceInfo(const String& sResource, String& sType, String& sName)
{
    int iSlash = sResource.Pos('\\');
    if (iSlash)
    {
        sType = sResource.SubString(1, iSlash - 1);
        sName = sResource.SubString(iSlash + 1, sResource.Length());
    }
}
//---------------------------------------------------------------------------
String __fastcall StringTableParserPlugin::NumToStr(unsigned char iNum, char cPrefix)
{
    String sNum = AnsiString::StringOfChar(cPrefix, 4) + IntToStr(iNum);
    sNum = sNum.SubString(sNum.Length() - 2, 3);
    return sNum;
}
//---------------------------------------------------------------------------

