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
RL_MESSAGE_LOGGER_OBJECT
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace Plugin;
using namespace Logging;
using namespace TiledMapParser;
//- GLOBAL LOG FILE ---------------------------------------------------------
ZXLogFile g_LogFile;
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from CodeEditor.cpp to create a new Plugin object. The MapEditor.cpp only uses the
 * Base class reference. So this function returns a Plugin object to use of type class ZXBasePlugin.
 * @return  ZXBasePlugin a ZXBasePlugin compatible object
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
TiledMapParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new TiledMapParserPlugin();
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
__fastcall TiledMapParserPlugin::TiledMapParserPlugin()
{
    RL_METHOD
    frmTiledMapParserOptions = new TfrmTiledMapParserOptions(NULL);
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
__fastcall TiledMapParserPlugin::~TiledMapParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmTiledMapParserOptions);
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
HRESULT __fastcall TiledMapParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmTiledMapParserOptions))
    {
        hResult = frmTiledMapParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall TiledMapParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmTiledMapParserOptions))
    {
        hResult = frmTiledMapParserOptions->Release();
    }
    SAFE_DELETE(frmTiledMapParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TiledMapParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall TiledMapParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmTiledMapParserOptions))
    {
        Panel = frmTiledMapParserOptions->panTiledMapParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TiledMapParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Types))
    {
        Types->Clear();
        KXmlInfo* MapEditor = XmlData->GetNode("MapEditor", 0);
        if (true == SAFE_PTR(MapEditor))
        {
            Types->Add("Map Data");
        }
        return Types->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TiledMapParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Resources))
    {
        Resources->Clear();
        KXmlInfo* MapEditor = XmlData->GetNode("MapEditor", 0);
        if (true == SAFE_PTR(MapEditor))
        {
            KXmlInfo* Screens = MapEditor->GetNode("Screens", 0);
            if (true == SAFE_PTR(Screens))
            {
                KXmlInfo* Screen = Screens->GetNode("Screen", 0);
                if (true == SAFE_PTR(Screen))
                {
                    Resources->Add("Map Table and Screens");
                }
            }
        }
        return Resources->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TiledMapParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
{
    HRESULT hResult = E_POINTER;

    if (ParserData != "[Begin]" && ParserData != "[End]")
    {
        if (true == SAFE_PTR(XmlData) && SAFE_PTR(Code))
        {
            if (ParserData.Trim() != "")
            {
                m_ConvertX = ParserData.Pos("XChr") > 0;
                m_ConvertY = ParserData.Pos("YChr") > 0;
                // todo: get map name
                int iComma = ParserData.Pos(",");
                m_sMapName = ParserData.SubString(1, iComma - 1);
                int iColon = ParserData.Pos(":");
                m_sPrefix  = ParserData.SubString(iComma + 1, iColon - iComma - 1);
            }
            else
            {
                m_sMapName = frmTiledMapParserOptions->edtTableName->Text.Trim() == "" ? String("MapTable") : frmTiledMapParserOptions->edtTableName->Text.Trim();
                m_sPrefix  = frmTiledMapParserOptions->edtPrefix->Text.Trim() == "" ? String("Screen") : frmTiledMapParserOptions->edtPrefix->Text.Trim();
            }
            GetScreenProperties(XmlData);
            BuildTilesMap(XmlData);
            ParserData = m_sMapName + "," + m_sPrefix + ":";
            if (m_ConvertX)
            {
                ParserData += "XChr";
            }
            if (m_ConvertY)
            {
                ParserData += "YChr";
            }
            return ParseMap(XmlData, Code);
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
HRESULT __fastcall TiledMapParserPlugin::ParseMap(KXmlInfo*& XmlData, TStringList*& Code)
{
    HRESULT hResult = E_FAIL;
    if (true == SAFE_PTR(XmlData))
    {
        KXmlInfo* MapEditor = XmlData->GetNode("MapEditor", 0);
        if (true == SAFE_PTR(MapEditor))
        {
            KXmlInfo* Screens = MapEditor->GetNode("Screens", 0);
            if (true == SAFE_PTR(Screens))
            {
                if (frmTiledMapParserOptions->chkBuildTilesTable)
                {
                    Code->Add(";");
                    Code->Add("; MAP TILES TABLE");
                    Code->Add(";");
                    Code->Add("TilesTable:");
                    for (int i = 0; i < (int)m_sTiles.size(); i++)
                    {
                        Code->Add("defw " + m_sTiles[i]);
                    }
                }
                m_MapTable.clear();
                // loop through the screens and build each screen
                Code->Add(";");
                Code->Add("; MAP SCREENS");
                Code->Add(";");
                for (KXmlNodes::const_iterator	it = Screens->begin(); it != Screens->end(); it++)
                {
                    KXmlInfo* node = (*it);
                    ParseScreen(node, Code);
                }
                Code->Add(";");
                Code->Add("; MAP TABLE (" + IntToStr(m_iAcross) + " x " + IntToStr(m_iDown) + ")");
                Code->Add(";");
                Code->Add(m_sMapName + ":");
                // now build the screens table
                for (int i = 0; i < (int)m_MapTable.size(); i++)
                {
                    Code->Add("defw " + m_MapTable[i]);
                }
                hResult = S_OK;
            }
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TiledMapParserPlugin::ParseScreen(KXmlInfo*& XmlData, TStringList*& Code)
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
        String sDEFx = frmTiledMapParserOptions->chkUseDefw->Checked ? "defw " : "defb ";
        if (true == SAFE_PTR(DupOf))
        {
            // don't generate this screen
            m_MapTable.push_back(m_MapTable[DupOf->GetInt()]);
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
                NewCode->Add(sDEFx + NumToStr(iTile) + ", " + NumToStr(x) + ", " + NumToStr(y) + "    ; " + sName);
            }
            m_MapTable.push_back(m_sPrefix + NumToStr(iLeft, '0') + "x" + NumToStr(iTop, '0'));
        }
        else
        {
            NewCode->Add(";");
            NewCode->Add("; SCREEN (" + IntToStr(iLeft) + ", " + IntToStr(iTop) + ")");
            NewCode->Add(";");
            NewCode->Add(m_sPrefix + NumToStr(iLeft, '0') + "x" + NumToStr(iTop, '0') + ":");

            NewCode->Add(sDEFx + NumToStr(0) + "              ; no tiles");
            m_MapTable.push_back("0");
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
//---------------------------------------------------------------------------
String __fastcall TiledMapParserPlugin::NumToStr(unsigned char iNum, char cPrefix)
{
    String sNum = AnsiString::StringOfChar(cPrefix, 4) + IntToStr(iNum);
    sNum = sNum.SubString(sNum.Length() - 2, 3);
    return sNum;
}
//---------------------------------------------------------------------------
void __fastcall TiledMapParserPlugin::BuildTilesMap(KXmlInfo*& XmlData)
{
    int iTiles = 0;
    m_TilesMap.clear();
    m_sTiles.clear();
    if (true == SAFE_PTR(XmlData))
    {
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor", 0);
        if (true == SAFE_PTR(ImageEditor))
        {
            for (KXmlNodes::const_iterator	it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Type = NULL;
                if ((*it)->Find(Type, "Type", 0))
                {
                    if (Type->GetText() == "Tile")
                    {
                        for (KXmlNodes::const_iterator Iit = (*it)->begin(); Iit != (*it)->end(); Iit++)
                        {
                            KXmlInfo* Frame = NULL;
                            if ((*Iit)->Find(Frame, "Frame", 0))
                            {
                                KXmlInfo* Name = NULL;
                                if (Frame->Find(Name, "Name", 0))
                                {
                                    m_TilesMap[Name->GetText()] = iTiles++;
                                    m_sTiles.push_back(Name->GetText());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TiledMapParserPlugin::GetScreenProperties(KXmlInfo*& XmlData)
{
    m_iAcross = 1;
    m_iDown = 1;
    if (true == SAFE_PTR(XmlData))
    {
        KXmlInfo* ImageEditor = XmlData->GetNode("MapEditor", 0);
        if (true == SAFE_PTR(ImageEditor))
        {
            KXmlInfo* Properties = ImageEditor->GetNode("Properties", 0);
            if (true == SAFE_PTR(Properties))
            {
                try
                {
                    m_iAcross = Properties->GetNode("ScreensAcross", 0)->GetInt();
                }
                catch(...)
                {
                    m_iAcross = 16;
                }
                try
                {
                    m_iDown   = Properties->GetNode("ScreensDown", 0)->GetInt();
                }
                catch(...)
                {
                    m_iDown = 16;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
int __fastcall TiledMapParserPlugin::GetTileIndex(const String& sName)
{
    if (m_TilesMap.find(sName) != m_TilesMap.end())
    {
        return m_TilesMap[sName];
    }
    return -1;
}
//---------------------------------------------------------------------------

