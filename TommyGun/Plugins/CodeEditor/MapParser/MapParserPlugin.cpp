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
using namespace MapParser;
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
MapParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new MapParserPlugin();
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
__fastcall MapParserPlugin::MapParserPlugin()
: m_NumberBase(nbHexidecimal)
{
    RL_METHOD
    frmMapParserOptions = new TfrmMapParserOptions(NULL);
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
__fastcall MapParserPlugin::~MapParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmMapParserOptions);
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
HRESULT __fastcall MapParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmMapParserOptions))
    {
        hResult = frmMapParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall MapParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmMapParserOptions))
    {
        hResult = frmMapParserOptions->Release();
    }
    SAFE_DELETE(frmMapParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall MapParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall MapParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmMapParserOptions))
    {
        Panel = frmMapParserOptions->panMapParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall MapParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
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
HRESULT __fastcall MapParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
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
HRESULT __fastcall MapParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
{
    HRESULT hResult = E_POINTER;

    if (ParserData != "[Begin]" && ParserData != "[End]")
    {
        if (true == SAFE_PTR(XmlData) && SAFE_PTR(Code))
        {
            GetScreenProperties(XmlData);
            
            if (ParserData.Trim() != "")
            {
                m_MapSortColRow = ParserData.Pos(":MSOCR");
                m_ConvertX = ParserData.Pos("XChr") > 0;
                m_ConvertY = ParserData.Pos("YChr") > 0;
                // todo: get map name
                int iComma = ParserData.Pos(",");
                m_sMapName = ParserData.SubString(1, iComma - 1);
                int iColon = ParserData.Pos(":");
                m_sPrefix  = ParserData.SubString(iComma + 1, iColon - iComma - 1);
                m_IndexOnly = ParserData.Pos(":IO") > 0;
                m_BuildTilesTable = ParserData.Pos(":BTT") > 0;
                m_UseDefwIndexes =  ParserData.Pos(":IDW") > 0;
                m_UseDefwCoords = ParserData.Pos(":CDW") > 0;
                m_UsePostProcessor = ParserData.Pos(":PP") > 0;
                m_LittleEndian = ParserData.Pos(":LE") > 0;
                if (m_UsePostProcessor)
                {
                    m_ConvertToSource = ParserData.Pos(":CTS") > 0;
                    m_Application = "";
                    m_Parameters  = "";
                    int App = ParserData.Pos("APPL|");
                    int Par = ParserData.Pos("PARM|");
                    if (App > 0)
                    {
                        // read the application string
                        m_Application = ParserData.SubString(App + 5, 10000);
                        int bar = m_Application.Pos("|");
                        if (bar > 0)
                        {
                            m_Application = m_Application.SubString(1, bar - 1);
                        }
                    }
                    if (Par > 0)
                    {
                        m_Parameters = ParserData.SubString(Par + 5, 10000);
                        int bar = m_Parameters.Pos("|");
                        if (bar > 0)
                        {
                            m_Parameters = m_Parameters.SubString(1, bar - 1);
                        }
                    }
                }
                if (m_IndexOnly)
                {
                    int ws = ParserData.Pos(":IO");
                    if (ws)
                    {
                        int Width = -1;
                        int Height = -1;

                        ws += 3;
                        int hs = ws;
                        int len = ParserData.Length();
                        for (int i = ws; i < ws + 8 && i <= len; i++)
                        {
                            if (ParserData[i] == 'x')
                            {
                                hs = i + 1;
                                Width = StrToInt(ParserData.SubString(ws, i - ws));
                            }
                            else if (ParserData[i] == ':' || i == (ws + 8) || i == len)
                            {
                                Height = StrToInt(ParserData.SubString(hs, i - hs));
                            }
                        }
                        if (Width != -1 && Height != -1)
                        {
                            m_GridWidth  = Width;
                            m_GridHeight = Height;
                        }
                    }
                }
            }
            else
            {
                m_MapSortColRow = frmMapParserOptions->radMapColRow->Checked;
                m_ConvertX = frmMapParserOptions->chkConvertX->Checked;
                m_ConvertY = frmMapParserOptions->chkConvertY->Checked;
                m_sMapName = frmMapParserOptions->edtTableName->Text.Trim() == "" ? String("MapTable") : frmMapParserOptions->edtTableName->Text.Trim();
                m_sPrefix = frmMapParserOptions->edtPrefix->Text.Trim() == "" ? String("Screen") : frmMapParserOptions->edtPrefix->Text.Trim();
                m_IndexOnly = frmMapParserOptions->radUseIndexOnly->Checked;
                m_BuildTilesTable = frmMapParserOptions->chkBuildTilesTable->Checked;
                m_UseDefwIndexes = frmMapParserOptions->chkIndexUseDefw->Checked;
                m_UseDefwCoords = frmMapParserOptions->chkCoordUseDefw->Checked;
                m_UsePostProcessor  = frmMapParserOptions->chkUsePostProcessor->Checked;
                m_ConvertToSource = m_UsePostProcessor && frmMapParserOptions->radConvertToSourceCode->Checked;
                m_Application = frmMapParserOptions->edtApplication->Text;
                m_Parameters = frmMapParserOptions->edtParameters->Text;
                m_LittleEndian = frmMapParserOptions->radLittleEndian->Checked;
                if (m_IndexOnly && frmMapParserOptions->chkOverrideTileSize->Checked)
                {
                    m_GridWidth = frmMapParserOptions->edtTileWidth->Value;
                    m_GridHeight = frmMapParserOptions->edtTileHeight->Value;
                }
            }

            BuildTilesMap(XmlData);
            ParserData = m_sMapName + "," + m_sPrefix + ":";

            if (m_MapSortColRow)
            {
                ParserData += ":MSOCR";
            }
            if (m_ConvertX)
            {
                ParserData += ":XChr";
            }
            if (m_ConvertY)
            {
                ParserData += ":YChr";
            }
            if (m_IndexOnly)
            {
                ParserData += ":IO";
                ParserData += IntToStr(m_GridWidth) + "x" + IntToStr(m_GridHeight);
            }
            if (m_BuildTilesTable)
            {
                ParserData += ":BTT";
            }
            if (m_UseDefwIndexes)
            {
                ParserData += ":IDW";
            }
            if (m_UseDefwCoords)
            {
                ParserData += ":CDW";
            }
            if (m_UsePostProcessor)
            {
                ParserData += ":PP";
                if (m_ConvertToSource)
                {
                    ParserData += ":CTS";
                }
                if (m_LittleEndian)
                {
                    ParserData += ":LE";
                }
                if (m_Application.Trim() != "")
                {
                    ParserData += ":APPL|" + m_Application + "|";
                }
                if (m_Parameters.Trim() != "")
                {
                    ParserData += ":PARM|" + m_Parameters  + "|";
                }
            }

            DeleteBinFiles();

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
HRESULT __fastcall MapParserPlugin::ParseMap(KXmlInfo*& XmlData, TStringList*& Code)
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
                if (m_BuildTilesTable)
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
                m_ScreenIndex = 0;
                int OLE = 0;
                int ILE = 0;
                if (m_MapSortColRow)
                {
                    OLE = m_iAcross;
                    ILE = m_iDown;
                }
                else
                {
                    OLE = m_iDown;
                    ILE = m_iAcross;
                }

                for (int OL = 0; OL < OLE; ++OL)
                {
                    for (int IL = 0; IL < ILE; ++IL)
                    {
                        for (KXmlNodes::const_iterator	it = Screens->begin(); it != Screens->end(); it++)
                        {
                            // find the right screen for the position (IL, OL)
                            KXmlInfo* node = (*it);
                            int iLeft = node->GetNode("Left", 0)->GetInt();
                            int iTop = node->GetNode("Top", 0)->GetInt();
                            if (m_MapSortColRow)
                            {
                                // inner loop is col(x) and outer loop is row(y)
                               if (iLeft != IL || iTop != OL)
                                {
                                    continue;
                                }
                            }
                            else
                            {
                                // inner loop is row(y) and outer loop is col(x)
                                if (iLeft != OL || iTop != IL)
                                {
                                    continue;
                                }
                            }
                            // parser the screen found
                            if (m_IndexOnly)
                            {
                                ParseScreenOnlyIndexes(node, Code);
                            }
                            else
                            {
                                ParseScreenWithCoords(node, Code);
                            }
                            m_ScreenIndex++;
                            break;
                        }
                    }
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
void __fastcall MapParserPlugin::ParseScreenWithCoords(KXmlInfo*& XmlData, TStringList*& Code)
{
    bool bParsed = true;
    int iLeft = 0;
    int iTop = 0;
    TStringList* NewCode = NULL;
    try
    {
        unsigned char PPBuffer[256 * 1024];     // 256Kb post processor buffer
        int PPBufferPos = 0;
        // create a temporary string list to place the parsed data
        NewCode = new TStringList;
        iLeft = XmlData->GetNode("Left", 0)->GetInt();
        iTop = XmlData->GetNode("Top", 0)->GetInt();

        KXmlInfo* Tiles = XmlData->GetNode("Tiles", 0);
        KXmlInfo* DupOf = XmlData->GetNode("DuplicateOf", 0);
        int iTiles = 0;
        String sDEFx = m_UseDefwCoords ? "defw " : "defb ";
        if (true == SAFE_PTR(DupOf))
        {
            // don't generate this screen
            if (m_MapSortColRow)
            {
                m_MapTable.push_back(m_MapTable[DupOf->GetInt()]);
            }
            else
            {
                // convert the index back into col/row
                int col = DupOf->GetInt() % m_iAcross;
                int row = DupOf->GetInt() / m_iAcross;
                m_MapTable.push_back(m_sPrefix + NumToStr(col, nbDecimal, '0') + "x" + NumToStr(row, nbDecimal, '0'));
            }
        }
        else if (true == SAFE_PTR(Tiles))
        {
            NewCode->Add(";");
            NewCode->Add("; SCREEN (" + IntToStr(iLeft) + ", " + IntToStr(iTop) + ")");
            NewCode->Add(";");
            NewCode->Add(m_sPrefix + NumToStr(iLeft, nbDecimal, '0') + "x" + NumToStr(iTop, nbDecimal, '0') + ":");

            int iTiles = Tiles->size();
            if (!m_UsePostProcessor)
            {
                NewCode->Add((iTiles < 256 ? "defb " : "defw") + NumToStr(iTiles) + "              ; " + IntToStr(iTiles) + " tiles");
            }
            else
            {
                if (iTiles < 256)
                {
                    BufferAdd((unsigned char)iTiles, PPBuffer, PPBufferPos);
                }
                else
                {
                    BufferAdd(iTiles, PPBuffer, PPBufferPos);
                }
            }

            // loop through all the tiles
            for (KXmlNodes::iterator it = Tiles->begin(); it != Tiles->end(); it++)
            {
                String sName = (*it)->GetNode("Name", 0)->GetText();
                int x = (*it)->GetNode("Left", 0)->GetInt();
                int y = (*it)->GetNode("Top", 0)->GetInt();
                int iTile = GetTileIndex(sName);
                if (m_ConvertX) x /= 8;
                if (m_ConvertY) y /= 8;
                if (!m_UsePostProcessor)
                {
                    NewCode->Add(sDEFx + NumToStr(iTile) + ", " + NumToStr(x) + ", " + NumToStr(y) + "    ; " + sName);
                }
                else
                {
                    if (!m_UseDefwCoords)
                    {
                        BufferAdd((unsigned char)iTile, PPBuffer, PPBufferPos);
                        BufferAdd((unsigned char)x, PPBuffer, PPBufferPos);
                        BufferAdd((unsigned char)y, PPBuffer, PPBufferPos);
                    }
                    else
                    {
                        BufferAdd(iTile, PPBuffer, PPBufferPos);
                        BufferAdd(x, PPBuffer, PPBufferPos);
                        BufferAdd(y, PPBuffer, PPBufferPos);
                    }
                }
            }

            if (m_UsePostProcessor)
            {
                DoPostProcess(PPBuffer, PPBufferPos, NewCode);
            }

            m_MapTable.push_back(m_sPrefix + NumToStr(iLeft, nbDecimal, '0') + "x" + NumToStr(iTop, nbDecimal, '0'));
        }
        else
        {
            NewCode->Add(";");
            NewCode->Add("; SCREEN (" + IntToStr(iLeft) + ", " + IntToStr(iTop) + ")");
            NewCode->Add(";");
            NewCode->Add(m_sPrefix + NumToStr(iLeft, nbDecimal, '0') + "x" + NumToStr(iTop, nbDecimal, '0') + ":");

            NewCode->Add("defb 0              ; No tiles");
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
void __fastcall MapParserPlugin::ParseScreenOnlyIndexes(KXmlInfo*& XmlData, TStringList*& Code)
{
    bool bParsed = true;
    TStringList* NewCode = NULL;
    try
    {
        // create a temporary string list to place the parsed data
        NewCode = new TStringList;
        int iLeft = XmlData->GetNode("Left", 0)->GetInt();
        int iTop = XmlData->GetNode("Top", 0)->GetInt();

        KXmlInfo* Tiles = XmlData->GetNode("Tiles", 0);
        KXmlInfo* DupOf = XmlData->GetNode("DuplicateOf", 0);
        int iTiles = 0;
        String sDEFx = m_UseDefwCoords ? "defw " : "defb ";
        if (true == SAFE_PTR(DupOf))
        {
            // don't generate this screen
            m_MapTable.push_back(m_MapTable[DupOf->GetInt()]);
        }
        else
        {
            int iTilesAcross = m_iWidth  / m_GridWidth;
            int iTilesDown   = m_iHeight / m_GridHeight;
            // make a new tile grid
            unsigned char* TilesGrid = new unsigned char[iTilesAcross * iTilesDown];
            ZeroMemory(TilesGrid, iTilesAcross * iTilesDown);

            NewCode->Add(";");
            NewCode->Add("; SCREEN (" + IntToStr(iLeft) + ", " + IntToStr(iTop) + ")");
            NewCode->Add(";");
            NewCode->Add(m_sPrefix + NumToStr(iLeft, nbDecimal, '0') + "x" + NumToStr(iTop, nbDecimal, '0') + ":");

            if (true == SAFE_PTR(Tiles))
            {
                // loop through all the tiles and pack them into the tile grid
                for (KXmlNodes::iterator it = Tiles->begin(); it != Tiles->end() && bParsed; it++)
                {
                    String sName = (*it)->GetNode("Name", 0)->GetText();
                    int x = (*it)->GetNode("Left", 0)->GetInt();
                    int y = (*it)->GetNode("Top", 0)->GetInt();
                    int iTile = GetTileIndex(sName);
                    x /= m_GridWidth;
                    y /= m_GridHeight;
                    if (x >=0 && x < iTilesAcross && y >= 0&& y < iTilesDown)
                    {
                        if (!TilesGrid[y * iTilesAcross + x])
                        {
                            TilesGrid[y * iTilesAcross + x] = iTile;
                        }
                        else
                        {
                            bParsed = false;
                        }
                    }
                }
            }


            if (m_UsePostProcessor)
            {
                DoPostProcess(TilesGrid, iTilesAcross * iTilesDown, NewCode);
            }
            else
            {
                // serialize the tile grid out as tile index output
                for (int y = 0; y < iTilesDown; y++)
                {
                    String sLine = sDEFx;
                    for (int x = 0; x < iTilesAcross; x++)
                    {
                        sLine += NumToStr(TilesGrid[y * iTilesAcross + x]) + (x + 1 < iTilesAcross ? ", " : "");
                    }
                    NewCode->Add(sLine);
                }
            }

            delete[] TilesGrid;
            
            m_MapTable.push_back(m_sPrefix + NumToStr(iLeft, nbDecimal, '0') + "x" + NumToStr(iTop, nbDecimal, '0'));
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
    else
    {
        Code->Add("Failed to parse the Map data correctly.");
        Code->Add(" * Check you have no map tiles overlapping");
        Code->Add(" * Check you have all your tile positions snapped to the grid");
    }
    SAFE_DELETE(NewCode);
}
//---------------------------------------------------------------------------
// NumToStr
/**
 * Converts an integer to a number string using the current number base
 * @return  String  the integer converted to a number in the specified base
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
String __fastcall MapParserPlugin::NumToStr(unsigned char iNum, eNumberBase NumberBase, char Filler)
{
    String sNum;
    int Width = 1;
    if (NumberBase == nbDefault)
    {
        NumberBase = m_NumberBase;
    }
    switch(NumberBase)
    {
        case nbHexidecimal:
            sNum = "00" + IntToHex(iNum, 2);
            Width = 2;
            break;
        case nbBinary:
            sNum += iNum & 0x80 ? "1" : "0";
            sNum += iNum & 0x40 ? "1" : "0";
            sNum += iNum & 0x20 ? "1" : "0";
            sNum += iNum & 0x10 ? "1" : "0";
            sNum += iNum & 0x08 ? "1" : "0";
            sNum += iNum & 0x04 ? "1" : "0";
            sNum += iNum & 0x02 ? "1" : "0";
            sNum += iNum & 0x01 ? "1" : "0";
            Width = 8;
            break;
        case nbOctal:
            sNum += IntToStr(iNum / 64);
            iNum -= (iNum / 64) * 64;
            sNum += IntToStr(iNum / 16);
            iNum -= (iNum / 16) * 16;
            sNum += IntToStr(iNum);
            Width = 3;
            break;
        case nbDecimal:
        default:
			sNum = String::StringOfChar(Filler, 3);
            sNum += IntToStr(iNum);
            Width = 3;
            break;
    }
    sNum = frmMapParserOptions->GetPrefix(NumberBase) + sNum.SubString(sNum.Length() - (Width - 1), Width) + frmMapParserOptions->GetPostfix(NumberBase);
    return sNum;
}
//---------------------------------------------------------------------------
void __fastcall MapParserPlugin::BuildTilesMap(KXmlInfo*& XmlData)
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
void __fastcall MapParserPlugin::GetScreenProperties(KXmlInfo*& XmlData)
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
                    m_iWidth = Properties->GetNode("ScreenWidth", 0)->GetInt();
                }
                catch(...)
                {
                    m_iWidth = 256;
                }
                try
                {
                    m_iHeight = Properties->GetNode("ScreenHeight", 0)->GetInt();
                }
                catch(...)
                {
                    m_iHeight = 192;
                }
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
                try
                {
                    m_GridWidth = Properties->GetNode("GridWidth", 0)->GetInt();
                }
                catch(...)
                {
                    m_GridWidth = 8;
                }
                try
                {
                    m_GridHeight = Properties->GetNode("GridHeight", 0)->GetInt();
                }
                catch(...)
                {
                    m_GridHeight = 8;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
int __fastcall MapParserPlugin::GetTileIndex(const String& sName)
{
    if (m_TilesMap.find(sName) != m_TilesMap.end())
    {
        return m_TilesMap[sName];
    }
    return -1;
}
//---------------------------------------------------------------------------
void __fastcall MapParserPlugin::BufferAdd(unsigned char Data, unsigned char* pBuffer, int& Pos)
{
    pBuffer[Pos] = Data;
    Pos++;
}
//---------------------------------------------------------------------------
void __fastcall MapParserPlugin::BufferAdd(int Data, unsigned char* pBuffer, int& Pos)
{
    if (m_LittleEndian)
    {
        pBuffer[Pos+0] = (Data & 0x00FF)     ;
        pBuffer[Pos+1] = (Data & 0xFF00) >> 8;
    }
    else
    {
        pBuffer[Pos+0] = (Data & 0xFF00) >> 8;
        pBuffer[Pos+1] = (Data & 0x00FF)     ;
    }
    Pos += 2;
}
//---------------------------------------------------------------------------
int __fastcall MapParserPlugin::FileSize(const String& sFile)
{
    int size = 0;
    if (FileExists(sFile))
    {
        FILE* fh = fopen(sFile.c_str(), "rb");
        if (fh)
        {
            fseek(fh, 0, SEEK_END);
            size = ftell(fh);
            fclose(fh);
        }
    }
    return size;
}
//---------------------------------------------------------------------------
void __fastcall MapParserPlugin::DoPostProcess(unsigned char* pBuffer, int Size, TStringList*& NewCode)
{
    // save the buffer to in.bin
    FILE* fh = fopen("in.bin", "wb+");
    if (fh)
    {
        fwrite(pBuffer, 1, Size, fh);
        fclose(fh);

        DeleteFile("out.bin");
        // run the post processor on the data
        if (FileExists(m_Application))
        {
            STARTUPINFO si;
            PROCESS_INFORMATION pi;

            ZeroMemory( &si, sizeof(si) );
            si.cb = sizeof(si);
            si.dwFlags = STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_MINIMIZE;

            // Start the child process.
            String sCL = m_Application + " " + m_Parameters;
            if
            ( !CreateProcess(
                NULL,        // no module needed
                sCL.c_str(), // supply command line from the user
                NULL,        // Process handle not inheritable.
                NULL,        // Thread handle not inheritable.
                FALSE,       // Set handle inheritance to FALSE.
                0,           // No creation flags.
                NULL,        // Use parent's environment block.
                NULL,        // Use parent's starting directory.
                &si,         // Pointer to STARTUPINFO structure.
                &pi )        // Pointer to PROCESS_INFORMATION structure.
            )
            {
                NewCode->Add("; failed to launch the post-process application: [" + m_Application + "]");
            }

            // execute the application and wait up to 30 seconds for it to complete
            DWORD dwResult = 0;
            int countDown = 30;
            do
            {
                // Wait until child process exits.
                dwResult = WaitForSingleObject( pi.hProcess, 1000 );
                Application->ProcessMessages();
            }
            while (dwResult == WAIT_TIMEOUT && countDown--);

            // Close process and thread handles.
            CloseHandle( pi.hProcess );
            CloseHandle( pi.hThread );
        }
        else
        {
            NewCode->Add("; post-process application: [" + m_Application + "] does not exist!");
        }

        if (FileExists("out.bin"))
        {
            if (m_ConvertToSource)
            {
                // read in the out.bin file and convert to source code
                FILE* fh = fopen("out.bin", "rb");
                if (fh)
                {
                    int bytes = 0;
                    int ch = 0;
                    int col = 0;
                    String sLine = "";
                    do
                    {
                        ch = fgetc(fh);
                        if (ch != EOF)
                        {
                            bytes++;
                            if (col == 0)
                            {
                                sLine = "defb ";
                            }
                            else
                            {
                                sLine += ", ";
                            }
                            col++;
                            sLine += NumToStr(ch);
                            if (col == 8)
                            {
                                col = 0;
                                NewCode->Add(sLine);
                                sLine = "";
                            }
                        }
                    }
                    while (ch != EOF);
                    fclose(fh);

                    if (sLine != "")
                    {
                        NewCode->Add(sLine);
                    }

                    if (bytes != Size)
                    {
                        NewCode->Add("; size is " + IntToStr(bytes) + " bytes; was originally " + IntToStr(Size) + " bytes");
                        NewCode->Add("");
                    }
                }
                else
                {
                    NewCode->Add("; failed to open the out.bin file for reading!");
                }
            }
            else
            {
                // copy the out.bin file to screen[n].bin
                String sFile = "screen" + NumToStr(m_ScreenIndex, nbDecimal, '0') + ".bin";
                DeleteFile(sFile);
                RenameFile("out.bin", sFile);
                if (FileSize(sFile) != Size)
                {
                    NewCode->Add("incbin \"" + sFile + "\"      ; size is " + IntToStr(FileSize(sFile)) + " bytes; was originally " + IntToStr(Size) + " bytes");
                }
            }
        }
        else
        {
            NewCode->Add("; out.bin was not generated!");
        }

        DeleteFile("in.bin");
        DeleteFile("out.bin");
    }
    else
    {
        NewCode->Add("; failed to create in.bin for post processing of screen " + IntToStr(m_ScreenIndex));
    }
}
//---------------------------------------------------------------------------
void __fastcall MapParserPlugin::DeleteBinFiles()
{
    for (int i = 0; i < 999; ++i)
    {
        String sFile = "screen" + NumToStr(m_ScreenIndex, nbDecimal, '0') + ".bin";
        if (FileExists(sFile))
        {
            DeleteFile(sFile);
        }
    }
}
//---------------------------------------------------------------------------

