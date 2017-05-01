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
using namespace AGDParser;
//---------------------------------------------------------------------------
AnsiString g_colors[8] =
{
    "BLACK  ",
    "BLUE   ",
    "RED    ",
    "MAGENTA",
    "GREEN  ",
    "CYAN   ",
    "YELLOW ",
    "WHITE  ",
};
//---------------------------------------------------------------------------
AnsiString g_blockTypes[7] =
{
    "Space   ",
    "Platform",
    "Wall    ",
    "Ladder  ",
    "Fodder  ",
    "Deadly  ",
    "Custom  ",
};
//---------------------------------------------------------------------------
struct MapObject
{
    AnsiString Name;
    int Screen;
    int X;
    int Y;
};
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from CodeEditor.cpp to create a new Plugin object. The AGDEditor.cpp only uses the
 * Base class reference. So this function returns a Plugin object to use of type class ZXBasePlugin.
 * @return  ZXBasePlugin a ZXBasePlugin compatible object
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
AGDParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new AGDParserPlugin();
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
__fastcall AGDParserPlugin::AGDParserPlugin()
{
    RL_METHOD
    frmAGDParserOptions = new TfrmAGDParserOptions(NULL);
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
__fastcall AGDParserPlugin::~AGDParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmAGDParserOptions);
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
HRESULT __fastcall AGDParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmAGDParserOptions))
    {
        hResult = frmAGDParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall AGDParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmAGDParserOptions))
    {
        hResult = frmAGDParserOptions->Release();
    }
    SAFE_DELETE(frmAGDParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall AGDParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmAGDParserOptions))
    {
        Panel = frmAGDParserOptions->panAGDParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall AGDParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
{
    return E_FAIL;
    /*
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Types))
    {
        Types->Clear();
        KXmlInfo* CodeEditor = XmlData->GetNode("CodeEditor", 0);
        if (true == SAFE_PTR(CodeEditor))
        {
            Types->Add("Arcade Game Designer");
        }
        return Types->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;*/
}
//---------------------------------------------------------------------------
HRESULT __fastcall AGDParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
{
    return E_FAIL;
/*    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Resources))
    {
        Resources->Clear();
        KXmlInfo* CodeEditor = XmlData->GetNode("CodeEditor", 0);

        if (true == SAFE_PTR(CodeEditor))
        {
            KXmlInfo* Files = CodeEditor->GetNode("Files", 0);
            if (true == SAFE_PTR(Files))
            {
                // TODO: Find the AgdGameEngine.asm file
                // insert the resources into it
                for (KXmlNodes::iterator it = Files->begin(); it != Files->end(); it++)
                {
                    String sFile = (*it)->GetText();
                    if (sFile == "AgdGameEngine.asm" && FileExists(sFile))
                    {
                        Resources->Add("All AGD Data");
                    }
                }
            }
        }
        return Resources->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;*/
}
//---------------------------------------------------------------------------
// ParseResources
/**
 * Parse the AGD resources into the AGD game engine
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  Tony Thompson
 * @date    Created 19 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
HRESULT __fastcall AGDParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
{
    HRESULT hResult = E_FAIL;

    if (Resource == "AGD")
    {
        ParseSettings(XmlData, Code);
        ParseStrings(XmlData, Code);
        ParseScreens(XmlData, Code);
        ParseSprites(XmlData, Code);
        ParseSounds(XmlData, Code);
        ParseObjects(XmlData, Code);
        ParseTiles(XmlData, Code);
        ParseEvents(XmlData, Code);
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
// ParseSettings
/**
 * Parse the AGD settings (keys, window, etc) into the AGD game engine
 * @author  Tony Thompson
 * @date    Created 19 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::ParseSettings(KXmlInfo*& XmlData, TStringList*& Code)
{
    // find GameDesigner node
    // find keys, set keys defb
    int keys[7];
    int window[4];
    int jumps[23];
    memset(keys, 0, sizeof(int) * 7);
    memset(window, 0, sizeof(int) * 4);
    memset(jumps, 0, sizeof(int) * 23);
    jumps[22] = 99;

    int collisionDistance = 15;
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Code))
    {
        KXmlInfo* tmp = XmlData;
        KXmlInfo* Editor = XmlData->GetNode("GameDesigner", 0);
        if (true == SAFE_PTR(Editor))
        {
            KXmlInfo* Keys = Editor->GetNode("Keys", 0);
            if (true == SAFE_PTR(Keys))
            {
                // loop through the tables and load the applicable data
                int ki = 0;
                for (KXmlNodes::iterator it = Keys->begin(); it != Keys->end(); it++)
                {
                    keys[ki++] = StrToInt((*it)->GetText());
                }
            }
            KXmlInfo* AreaNode = Editor->GetNode("WindowArea", 0);
            if (true == SAFE_PTR(AreaNode))
            {
                KXmlInfo* nValue = AreaNode->GetNode("Top", 0);
                if (nValue) window[1] = nValue->GetInt();
                nValue = AreaNode->GetNode("Left", 0);
                if (nValue) window[0] = nValue->GetInt();
                nValue = AreaNode->GetNode("Height", 0);
                if (nValue) window[2] = nValue->GetInt();
                nValue = AreaNode->GetNode("Width", 0);
                if (nValue) window[3] = nValue->GetInt();
            }
            KXmlInfo* Jumps = Editor->GetNode("JumpTable", 0);
            if (true == SAFE_PTR(Jumps))
            {
                // loop through the tables and load the applicable data
                int ji = 0;
                for (KXmlNodes::iterator it = Jumps->begin(); it != Jumps->end(); it++)
                {
                    jumps[ji++] = StrToInt((*it)->GetText());
                }
            }
            KXmlInfo* ColDist = Editor->GetNode("CollisionDistance", 0);
            if (true == SAFE_PTR(ColDist))
            {
                collisionDistance = ColDist->GetNode("Distance")->GetInt();
            }
        }
    }
    // find keys table
    int lineNo = DeleteLines(Code, "keys", "defb", 1);
    if (lineNo != -1)
    {
        AnsiString line = "keys    defb ";
        for (int i = 0; i < 7; ++i)
        {
            line = line + IntToStr(keys[i]) + ", ";
        }
        line = line.SubString(1, line.Length() - 2);
        Code->Insert(lineNo, line);
    }
    // find window area
    lineNo = DeleteLines(Code, "wintop", "defb", 4);
    if (lineNo != -1)
    {
        // set wintop, winlft, winhgt, winwid
        Code->Insert(lineNo, "winwid defb " + NumToStr(window[3], 3, true) + "            ; window width");
        Code->Insert(lineNo, "winhgt defb " + NumToStr(window[2], 3, true) + "            ; window height");
        Code->Insert(lineNo, "winlft defb " + NumToStr(window[0], 3, true) + "            ; window left");
        Code->Insert(lineNo, "wintop defb " + NumToStr(window[1], 3, true) + "            ; window top");
    }
    // find jump table
    lineNo = DeleteLines(Code, ";", "TG:JUMP TABLE");
    if (lineNo != -1)
    {
        // set jumps (jtab) 2's complement  (22 entries + 99)
        int const numTableEntries = 23;
        AnsiString line = "jtab    defb ";
        const int maxCols = 4;
        int cols = maxCols;
        for (int i = 0; i < numTableEntries; ++i)
        {
            unsigned char jump = jumps[i];
            line = line + NumToStr(jump, 3);
            if (--cols == 0)
            {
                Code->Insert(++lineNo, line);
                cols = maxCols;
                line = "        defb ";
            }
            else if (i != numTableEntries - 1)
            {

                line += ", ";
            }
        }
        Code->Insert(++lineNo, line);
    }

    // find collision distance, set equ value
    lineNo = DeleteLines(Code, "COLDST", "equ", 1);
    if (lineNo != -1)
    {
        Code->Insert(lineNo, "COLDST equ " + NumToStr(collisionDistance, 3, true) + "             ; maximum collision distance");         
    }
}
//---------------------------------------------------------------------------
// ParseStrings
/**
 * Parse the AGD strings into the AGD game engine
 * @author  Tony Thompson
 * @date    Created 19 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::ParseStrings(KXmlInfo*& XmlData, TStringList*& Code)
{
    TStringList* strings = new TStringList();
    // find StringEditor/Tables/Table/Name=AGD Strings
    // get the string to change
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Code))
    {
        KXmlInfo* Editor = XmlData->GetNode("StringEditor", 0);
        if (true == SAFE_PTR(Editor))
        {
            KXmlInfo* TablesNode = Editor->GetNode("Tables", 0);
            if (true == SAFE_PTR(TablesNode))
            {
                int messages = 0;
                // loop through the tables and load the applicable data
                for (KXmlNodes::iterator it = TablesNode->begin(); it != TablesNode->end(); it++)
                {
                    for (KXmlNodes::iterator itT = (*it)->begin(); itT != (*it)->end(); itT++)
                    {
                        if ((*itT)->GetName() == "String")
                        {
                            KXmlInfo* pValue = (*itT)->GetNode("Value");
                            if (SAFE_PTR(pValue))
                            {
                                AnsiString string = pValue->GetText();
                                // replace \r\n with \r
                                int nl = string.Pos("\n");
                                if (nl)
                                {
                                    string.Delete(nl, 1);
                                }
                                strings->Add(string);
                                messages++;
                            }
                        }
                    }
                }
                int lineNo = DeleteLines(Code, "nummsg", "defb", 1);
                Code->Insert(lineNo, "nummsg defb " + NumToStr(messages, 3, true) + "            ; number of messages.");
            }
        }
    }

    // set msgdat
    // The last character of each message is marked with bit 7 set high,
    // so the sequence 65,66,67,141 displays ABC and a newline character at the end.

    if (strings->Count > 0)
    {
        // find the msgdat table and delete the old version
        int lineNo = DeleteLines(Code, ";", "TG:STRINGS");
        if (lineNo != -1)
        {
            AnsiString line;
            // add the new version
            for (int i = strings->Count - 1; i > 0; --i)
            {
                line = "       defb '" + strings->Strings[i].SubString(1, strings->Strings[i].Length() - 1) + "', " + IntToStr(strings->Strings[i][strings->Strings[i].Length()] + 128);
                Code->Insert(lineNo + 1, line);
            }
            // add the label and the
            line = "msgdat defb '" + strings->Strings[0].SubString(1, strings->Strings[0].Length() - 1) + "', " + IntToStr(strings->Strings[0][strings->Strings[0].Length()] + 128);
            Code->Insert(lineNo + 1, line);
        }
    }
    SAFE_DELETE(strings);
}
//---------------------------------------------------------------------------
// ParseScreens
/**
 * Parse the AGD screens (map) into the AGD game engine
 * @author  Tony Thompson
 * @date    Created 19 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::ParseScreens(KXmlInfo*& XmlData, TStringList*& Code)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Code))
    {
        KXmlInfo* ScreensNode = NULL;
        KXmlInfo* MapEditor = XmlData->GetNode("MapEditor", 0);
        if (true == SAFE_PTR(MapEditor))
        {
            ScreensNode = MapEditor->GetNode("Screens");
        }

        if (ScreensNode == NULL)
            return;

        AnsiString line;
        unsigned char screenTotal = 0;
        unsigned char screens[10][8];
        // default all rooms to empty
        memset(screens, 255, sizeof(unsigned char) * 10 * 8);
        int lineNo = DeleteLines(Code, ";", "TG:MAPTABLE");
        if (lineNo != -1)
        {
            int startScreen = 0;
            KXmlInfo* Settings = MapEditor->GetNode("Settings");
            if (true == SAFE_PTR(Settings))
            {
                KXmlInfo* StartScreen = Settings->GetNode("StartScreen");
                if (StartScreen)
                {
                    startScreen = StartScreen->GetNode("Screen")->GetInt();
                }
            }
            // generate the map table
            int roomtb = 0;
            unsigned char screen = 0;
            for (KXmlNodes::iterator it = ScreensNode->begin(); it != ScreensNode->end(); it++)
            {
                int x = (*it)->GetNode("Left")->GetInt();
                int y = (*it)->GetNode("Top")->GetInt();
                KXmlInfo* Tiles = (*it)->GetNode("Tiles");
                if (screens[x][y] == 255 && Tiles != NULL && Tiles->size() > 0)
                {

                    screenTotal++;
                    screens[x][y] = screen;
                    if (screen == startScreen)
                    {
                        roomtb = (y * 10) + x;
                    }
                }
                screen++;
            }
            // output the map table
            line = "mapdat defb ";
            for (int r = 0; r < 8; r++)
            {
                for (int c = 0; c < 10; c++)
                {
                    line += NumToStr(screens[c][r], 3);
                    if (c < 9) line += ", ";
                }
                Code->Insert(++lineNo, line);
                line = "       defb ";
            }

            // set the number of screens
            lineNo = DeleteLines(Code, "numsc", "defb", 1);
            if (lineNo != -1)
            {
                Code->Insert(lineNo, "numsc  defb " + NumToStr(screenTotal, 3, true) + "            ; number of screens.");
            }

            // set the start screen
            lineNo = DeleteLines(Code, "roomtb", "defb", 1);
            if (lineNo != -1)
            {
                Code->Insert(lineNo, "roomtb defb " + NumToStr(roomtb, 3, true));
            }
        }
        lineNo = DeleteLines(Code, ";", "TG:MAPROOMS");
        if (lineNo != -1)
        {
            int rw = 32;
            int rh = 24;
            KXmlInfo* Props = MapEditor->GetNode("Properties");
            if (true == SAFE_PTR(Props))
            {
                rw = Props->GetNode("ScreenWidth")->GetInt() / 8;
                rh = Props->GetNode("ScreenHeight")->GetInt() / 8;
            }
            // need to map all tiles names to tile indexes
            std::map<AnsiString, int> TileMap;  // map of tile name to tile index
            KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor", 0);
            if (ImageEditor)
            {
                KXmlInfo* Tiles = NULL;
                // loop thru' images and the tiles image node
                for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
                {
                    KXmlInfo* Node = (*it);
                    if (true == SAFE_PTR(Node) && Node->GetName() == "Images")
                    {
                        KXmlInfo* Type = Node->GetNode("Type", 0);
                        if (true == SAFE_PTR(Type) && Type->GetText() == "Tile")
                        {
                            Tiles = Node;
                            break;
                        }
                    }
                }
                if (Tiles)
                {
                    // got the tiles node so map the names
                    int tileIndex = 0;
                    for (KXmlNodes::iterator it = Tiles->begin(); it != Tiles->end(); it++)
                    {
                        if ((*it)->GetName() != "Image") continue;
                        AnsiString name = (*it)->GetNode("Frame")->GetNode("Name")->GetText();
                        TileMap[name] = tileIndex++;
                    }
                }
            }
            // build the screens/rooms
            unsigned char* room = new unsigned char[rw*rh];
            unsigned char* compressedRoom = new unsigned char[rw*rh];
            int crSizes[8*10]; // size of all the compressed rooms
            memset(crSizes, 0, sizeof(int) * 8 * 10);
            for (int si = 0; si < screenTotal; si++)
            {
                int rs = rw * rh;
                // default all room tiles to tile/block 0
                memset(room, 0, rs);
                // build the room
                KXmlInfo* RoomTiles = (ScreensNode->GetNode("Screen", si))->GetNode("Tiles");
                for (KXmlNodes::iterator it = RoomTiles->begin(); it != RoomTiles->end(); it++)
                {
                    AnsiString name = (*it)->GetNode("Name")->GetText();
                    int x = (*it)->GetNode("Left")->GetInt() / 8;
                    int y = (*it)->GetNode("Top")->GetInt() / 8;
                    if (TileMap.count(name) != 0)
                    {
                        room[y * rw + x] = TileMap[name];
                    }
                }
                // now we need to compress the built room
                int crIndex = 0;            // the current write position for the compressed room
                unsigned char tile = room[0];   // current tile index
                int run = 1;                // the run of the current tile
                const int maxRun = 253;
                for (int i = 1; i < rs; i++)
                {
                    // do we a change of tile or a max run of tiles?
                    if (room[i] != tile || run == maxRun)
                    {
                        // yep, so do we have a run of tiles?
                        if (run > 3 || run == maxRun)
                        {
                            // output the tiles
                            compressedRoom[crIndex++] = 255;
                            compressedRoom[crIndex++] = tile;
                            compressedRoom[crIndex++] = run;
                        }
                        else
                        {
                            // nope, output the run as is
                            for (int r = 0; r < run; ++r)
                            {
                                compressedRoom[crIndex++] = tile;
                            }
                        }
                        // reset tile and the run count
                        tile = room[i];
                        run = 0;
                    }
                    run++;
                }
                // save the size of the room compressed
                crSizes[si] = crIndex;

                // now we output the compressed room
                AnsiString line = "rmdat" + NumToStr(si, 2, true) + " defb ";
                for (int i = 0; i < crIndex; i++)
                {
                    line += NumToStr(compressedRoom[i], 3);
                    if ((i % rw < (rw - 1)) && (i != crIndex - 1))
                    {
                        line += ", ";
                    }
                    else
                    {
                        Code->Insert(++lineNo, line);
                        line = "        defb ";
                    }
                }
                if (line != "        defb ")
                {
                    // output the last line if needed
                    Code->Insert(++lineNo, line);
                }
            }
            // generate the map room table (store the room sizes)
            lineNo = DeleteLines(Code, ";", "TG:MAPROOMTABLE");
            if (lineNo != -1)
            {
                line = "maprtab defw ";
                for (int i = 0; i < screenTotal; ++i)
                {
                    line += IntToStr(crSizes[i]);
                    Code->Insert(++lineNo, line);
                    line = "        defw ";
                }
                lineNo = DeleteLines(Code, "scrptr", "defw", 1);
                if (lineNo != -1)
                {
                    Code->Insert(lineNo, "scrptr defw maprtab        ; address of map rooms.");
                }
            }
            SAFE_DELETE(room);
            SAFE_DELETE(compressedRoom);
        }
    }
}
//---------------------------------------------------------------------------
// ParseSprites
/**
 * Parse the AGD sprites into the AGD game engine
 * @author  Tony Thompson
 * @date    Created 25 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::ParseSprites(KXmlInfo*& XmlData, TStringList*& Code)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Code))
    {
        KXmlInfo* Sprites = NULL;
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor", 0);
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' images and get all types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Node = (*it);
                if (true == SAFE_PTR(Node) && Node->GetName() == "Images")
                {
                    KXmlInfo* Type = Node->GetNode("Type", 0);
                    if (true == SAFE_PTR(Type) && Type->GetText() == "Sprite")
                    {
                        Sprites = Node;
                        break;
                    }
                }
            }
        }

        if (Sprites == NULL)
            return;

        int lineNo = DeleteLines(Code, ";", "TG:SPRITE FRAME LIST");
        // loop through each sprite image getting the number of frames
        AnsiString line = "frmlst defb 0, ";
        int totalFrames = 0;
        int sprites = 0;
        std::vector<int> framesList;
        for (KXmlNodes::iterator it = Sprites->begin(); it != Sprites->end(); it++)
        {
            if ((*it)->GetName() != "Image") continue;
            if ((*it)->GetNode("Frame")->GetNode("SubType")->GetText() != "0") continue;
            int frames = 0;
            KXmlInfo* Frame = NULL;
            while ((Frame = (*it)->GetNode("Frame", frames++)) != NULL);
            AnsiString name = (*it)->GetNode("Frame", 0)->GetNode("Name", 0)->GetText();
            frames--;   // take away the frame that wasn't found
            line += IntToStr(frames) + "    ; " + name;
            Code->Insert(++lineNo, line);
            line = "       defb 0, ";
            framesList.push_back(frames);
            totalFrames += frames;
            sprites++;
        }

        lineNo = DeleteLines(Code, "numspr", "defb", 1);
        Code->Insert(lineNo, "numspr defb " + NumToStr(sprites, 3, true) + "            ; number of sprites.");
        lineNo = DeleteLines(Code, "totfrm", "defb", 1);
        Code->Insert(lineNo, "totfrm defb " + NumToStr(totalFrames, 3, true) + "            ; total sprite frames.");

        // find the sprite table reference and update it
        lineNo = DeleteLines(Code, "sprptr", "defw", 1);
        std::vector<AnsiString> spriteNames;
        if (lineNo != -1)
        {
            Code->Insert(lineNo, "sprptr defw sprgfx         ; sprite graphics.");
            lineNo = DeleteLines(Code, ";", "TG:SPRITE DATA");
            if (lineNo != -1)
            {
                AnsiString line = "sprgfx defb ";
                int iSprite = 0;
                for (KXmlNodes::iterator it = Sprites->begin(); it != Sprites->end(); it++)
                {
                    if ((*it)->GetName() != "Image") continue;
                    if ((*it)->GetNode("Frame")->GetNode("SubType")->GetText() != "0") continue;
                    for (int f = 0; f < framesList[iSprite]; f++)
                    {
                        KXmlInfo* Frame = (*it)->GetNode("Frame", f);
                        if (Frame)
                        {
                            AnsiString name = Frame->GetNode("Name")->GetText();
                            KXmlInfo* width  = Frame->GetNode("Width" , 0);
                            KXmlInfo* height = Frame->GetNode("Height", 0);
                            if (width && height && width->GetInt() == 16 && height->GetInt() == 16)
                            {
                                if (f == 0)
                                {
                                    spriteNames.push_back(name);
                                }
                                AnsiString pixelData = Frame->GetNode("Pixels", 0)->GetText();
                                unsigned char pixels[32];
                                ConvertStringToData(pixels, pixelData, false);
                                unsigned char psl;
                                unsigned char psr;

                                // generate 4 copies of the sprite frame (pre-shifted by 2 each time)
                                for (int i = 0; i < 4; i++)
                                {
                                    // output the line
                                    for (int p = 0; p < 32; p++)
                                    {
                                        line += NumToStr(pixels[p],3);
                                        if (p < 31) line += ",";
                                    }
                                    // shift the data
                                    for (int p = 0; p < 32; p += 2)
                                    {
                                        unsigned char l = (pixels[p+0] >> 2) & 0x3F;
                                        unsigned char r = (pixels[p+1] << 6) & 0xC0;
                                        psl = l | r;
                                        psr = ((pixels[p+1] >> 2) & 0x3F) | ((pixels[p+0] << 6) & 0xC0);
                                        pixels[p+0] = psl;
                                        pixels[p+1] = psr;
                                    }
                                    if (i == 0)
                                    {
                                        line += " ; " + name + " - Frame: " + IntToStr(f);
                                    }
                                    Code->Insert(++lineNo, line);
                                    line = "       defb ";
                                }
                            }
                        }
                    }
                }
            }
        }

        lineNo = DeleteLines(Code, ";", "TG:MAP SPRITES");
        if (lineNo != -1)
        {
            KXmlInfo* MapSprites = NULL;
            KXmlInfo* MapEditor = XmlData->GetNode("MapEditor", 0);
            if (true == SAFE_PTR(MapEditor))
            {
                bool output = false;
                AnsiString line = "nmedat defb ";
                KXmlInfo* Screens = MapEditor->GetNode("Screens");
                if (true == SAFE_PTR(Screens))
                {
                    int screen = 0;
                    for (KXmlNodes::iterator it = Screens->begin(); it != Screens->end(); it++)
                    {
                        // loop through each screen and get the sprites for it
                        KXmlInfo* Sprites = (*it)->GetNode("Sprites");
                        if (true == SAFE_PTR(Sprites) && Sprites->size() > 0)
                        {
                            for (KXmlNodes::iterator spit = Sprites->begin(); spit != Sprites->end(); spit++)
                            {
                                int spriteIndex = -1;
                                AnsiString name = (*spit)->GetNode("Name")->GetText();
                                for (unsigned int i = 0; i < spriteNames.size(); i++)
                                {
                                    if (spriteNames[i] == name)
                                    {
                                        spriteIndex = i;
                                        break;
                                    }
                                }
                                if (spriteIndex != -1)
                                {
                                    output = true;
                                    int type = (*spit)->GetNode("Type")->GetInt();
                                    int x = (*spit)->GetNode("Left")->GetInt();
                                    int y = (*spit)->GetNode("Top")->GetInt();
                                    line += NumToStr(screen, 3) + ", " + NumToStr(type, 3) + ", " + NumToStr(spriteIndex, 3) + ", ";
                                    line += NumToStr(x, 3) + ", " + NumToStr(y, 3);
                                    Code->Insert(++lineNo, line);
                                    line = "       defb ";
                                }
                            }
                            // add a end of screen marker
                            line = "       defb 255";
                            Code->Insert(++lineNo, line);
                            line = "       defb ";
                        }
                        screen++;
                    }
                }
                if (!output)
                {
                    line += "0, 0, 0, 0, 0  ; no sprites on any screens";
                    Code->Insert(++lineNo, line);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
// ParseSounds
/**
 * Parse the AGD sounds into the AGD game engine
 * @author  Tony Thompson
 * @date    Created 19 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::ParseSounds(KXmlInfo*& XmlData, TStringList*& Code)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Code))
    {
        // read sound files
        std::vector<MapObject> mapObjects;
        KXmlInfo* Editor = XmlData->GetNode("GameDesigner", 0);
        if (true == SAFE_PTR(Editor))
        {
            AnsiString sfxPath = ExtractFilePath(Application->ExeName) + "AGD\\";
            KXmlInfo* Sounds;
            TStrings* Lines = new TStringList;
            if (Editor->Find(Sounds, "Sounds", 0))
            {
                int fx = 0;
                int dl = 0;
                int lineNo = DeleteLines(Code, ";", "TG:SOUNDS");
                if (lineNo != -1)
                {
                    lineNo++;
                    // load the sound filenames
                    AnsiString file;
                    AnsiString line;
                    for (int i = 0;;i++)
                    {
                        KXmlInfo* File;
                        if (!Sounds->Find(File, "File", i))
                        {
                            break;
                        }
                        dl = 0;
                        file = File->GetText();
                        if (FileExists(sfxPath + file))
                        {
                            // load the file
                            Lines->Clear();
                            Lines->LoadFromFile(sfxPath + file);
                            ++fx;
                            for (int i = 0; i < Lines->Count; ++i)
                            {
                                line = Lines->Strings[i].Trim();
                                if (line[1] == ';')
                                {
                                    Code->Insert(lineNo++, "       " + line);
                                }
                                else
                                {
                                    dl++;
                                    if (dl == 1)
                                    {
                                        Code->Insert(lineNo++, "fx" + NumToStr(fx, 3, true) + "  " + line);
                                    }
                                    else
                                    {
                                        Code->Insert(lineNo++, "       " + line);
                                    }
                                }
                            }
                        }
                    }
                    if (fx > 0)
                    {
                        lineNo = DeleteLines(Code, "sndptr", "defw", 1);
                        if (lineNo != -1)
                            Code->Insert(lineNo, "sndptr defw fx1            ; pointer to sounds.");
                    }
                }
            }
            SAFE_DELETE(Lines);
        }
    }
}
//---------------------------------------------------------------------------
// ParseObjects
/**
 * Parse the AGD objects into the AGD game engine
 * @author  Tony Thompson
 * @date    Created 25 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::ParseObjects(KXmlInfo*& XmlData, TStringList*& Code)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Code))
    {
        // read map objects
        std::vector<MapObject> mapObjects;
        KXmlInfo* MapEditor = XmlData->GetNode("MapEditor", 0);
        if (true == SAFE_PTR(MapEditor))
        {
            KXmlInfo* Objects = MapEditor->GetNode("Objects");
            if (true == SAFE_PTR(Objects))
            {
                // loop thru' all the objects
                for (KXmlNodes::iterator it = Objects->begin(); it != Objects->end(); it++)
                {
                    MapObject mo;
                    mo.Name = (*it)->GetNode("Name")->GetText();
                    mo.Screen = (*it)->GetNode("Screen")->GetInt();
                    mo.X = (*it)->GetNode("Left")->GetInt();
                    mo.Y = (*it)->GetNode("Top")->GetInt();
                    mapObjects.push_back(mo);
                }
            }
        }

        KXmlInfo* Sprites = NULL;
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor", 0);
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' images and get all types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Node = (*it);
                if (true == SAFE_PTR(Node) && Node->GetName() == "Images")
                {
                    KXmlInfo* Type = Node->GetNode("Type", 0);
                    if (true == SAFE_PTR(Type) && Type->GetText() == "Sprite")
                    {
                        Sprites = Node;
                        break;
                    }
                }
            }
        }
        if (Sprites == NULL)
            return;

        int lineNo = DeleteLines(Code, "objptr", "defw", 1);
        if (lineNo != -1)
        {
            Code->Insert(lineNo, "objptr defw objdat         ; pointer to objects.");
        }

        lineNo = DeleteLines(Code, ";", "TG:OBJECTS");
        // loop through each sprite image getting the number of frames
        AnsiString line = "objdat defb ";
        int objects = 0;
        // find the image name in the map object list
        for (unsigned int i = 0; i < mapObjects.size(); i++)
        {
            for (KXmlNodes::iterator it = Sprites->begin(); it != Sprites->end(); it++)
            {
                if ((*it)->GetName() != "Image") continue;
                if ((*it)->GetNode("Frame")->GetNode("SubType")->GetText() != "1") continue;
                AnsiString name   = (*it)->GetNode("Frame")->GetNode("Name")->GetText();

                if (mapObjects[i].Name == name)
                {
                    Code->Insert(++lineNo, "       ; " + name);
                    AnsiString pixels = (*it)->GetNode("Frame")->GetNode("Pixels")->GetText();
                    unsigned char pixelsData[32];
                    ConvertStringToData(pixelsData, pixels, false);
                    for (int i = 0; i < 32; i++)
                    {
                        line += NumToStr(pixelsData[i], 3) + ", ";
                        if (i == 15 || i == 31)
                        {
                            Code->Insert(++lineNo, line.SubString(1, line.Length() - 2));
                            line = "       defb ";
                        }
                    }
                    line = "       defb   0,   0,   0  ; variables";
                    Code->Insert(++lineNo, line);
                    // find object
                    line = "       defb " + NumToStr(mapObjects[i].Screen, 3) + ", ";
                    line += NumToStr(mapObjects[i].X, 3) + ", ";
                    line += NumToStr(mapObjects[i].Y, 3);
                    line += "  ; screen, x, y";
                    Code->Insert(++lineNo, line);
                    objects++;
                    line = "       defb ";
                    break;
                }
            }
        }
        if (objects == 0)
        {
            Code->Insert(++lineNo, line + "0");
        }
    }
}
//---------------------------------------------------------------------------
// ParseTiles
/**
 * Parse the AGD tiles(blocks) into the AGD game engine
 * @author  Tony Thompson
 * @date    Created 19 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::ParseTiles(KXmlInfo*& XmlData, TStringList*& Code)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Code))
    {
        KXmlInfo* Tiles = NULL;
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor", 0);
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' images and get all types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Node = (*it);
                if (true == SAFE_PTR(Node) && Node->GetName() == "Images")
                {
                    KXmlInfo* Type = Node->GetNode("Type", 0);
                    if (true == SAFE_PTR(Type) && Type->GetText() == "Tile")
                    {
                        Tiles = Node;
                        break;
                    }
                }
            }
        }
        if (Tiles == NULL)
            return;

        // code output
        // ; Character block graphics.
        // chgfx defb ...
        // ; Block colours.
        // bcol   defb ...
        // ; Block properties.
        // bprop  defb ...


        int lineNo = DeleteLines(Code, ";", "TG:TILES");
        if (lineNo == -1)
        {
            return;
        }
        lineNo++;

        Code->Insert(lineNo++, "; Character block graphics.");
        AnsiString nl = "chgfx  defb ";
        int blocks = 0;
        // loop through each tile image pixels
        for (KXmlNodes::iterator it = Tiles->begin(); it != Tiles->end(); it++)
        {
            if ((*it)->GetName() != "Image") continue;
            KXmlInfo* Frame = (*it)->GetNode("Frame");
            if (Frame)
            {
                // check width and height are 8x8
                // get the images' sub-type, pixels, and attributes
                KXmlInfo* width  = Frame->GetNode("Width" , 0);
                KXmlInfo* height = Frame->GetNode("Height", 0);
                if (width && height && width->GetText() == "8" && height->GetText() == "8")
                {
                    KXmlInfo* name = Frame->GetNode("Name", 0);
                    KXmlInfo* pixels = Frame->GetNode("Pixels", 0);
                    // convert string to data and convert into code
                    unsigned char pixelsData[8];
                    ConvertStringToData(pixelsData, pixels->GetText(), false);
                    for (int i = 0; i < 8; ++i)
                    {
                        nl += NumToStr(pixelsData[i], 3);
                        if (i < 7)
                            nl += ", ";
                    }
                    nl += "    ; " + name->GetText();
                    Code->Insert(lineNo++, nl);
                    nl = "       defb ";
                    blocks++;
                }
            }
        }
        nl = "bcol   defb ";
        AnsiString al;
        Code->Insert(lineNo++, "\n; Block colours.");
        // loop through each tile image attributes
        for (KXmlNodes::iterator it = Tiles->begin(); it != Tiles->end(); it++)
        {
            if ((*it)->GetName() != "Image") continue;
            KXmlInfo* Frame = (*it)->GetNode("Frame");
            if (Frame)
            {
                // check width and height are 8x8
                // get the images' sub-type, pixels, and attributes
                KXmlInfo* width  = Frame->GetNode("Width" , 0);
                KXmlInfo* height = Frame->GetNode("Height", 0);
                if (width && height && width->GetText() == "8" && height->GetText() == "8")
                {
                    KXmlInfo* name = Frame->GetNode("Name", 0);
                    KXmlInfo* attr = Frame->GetNode("Attributes", 0);
                    unsigned char at;
                    ConvertStringToData(&at, attr->GetText(), false);
                    al = "    ; " + name->GetText();
                    al += AnsiString::StringOfChar(' ', std::max(1, 20 - name->GetText().Length()));
                    al += g_colors[at & 0x7] + ":";
                    al += g_colors[((at & 0x38) >> 3)];
                    if (at & 0x40) al += ":B"; else al += ":b";
                    if (at & 0x80) al += ":F"; else al += ":f";
                    nl += NumToStr(at, 3) + al;
                    Code->Insert(lineNo++, nl);
                    nl = "       defb ";
                }
            }
        }
        nl = "bprop  defb ";
        Code->Insert(lineNo++, "\n; Block properties.");
        // loop through each tile image subtype
        for (KXmlNodes::iterator it = Tiles->begin(); it != Tiles->end(); it++)
        {
            if ((*it)->GetName() != "Image") continue;
            KXmlInfo* Frame = (*it)->GetNode("Frame");
            if (Frame)
            {
                // check width and height are 8x8
                // get the images' sub-type, pixels, and attributes
                KXmlInfo* width  = Frame->GetNode("Width" , 0);
                KXmlInfo* height = Frame->GetNode("Height", 0);
                if (width && height && width->GetText() == "8" && height->GetText() == "8")
                {
                    KXmlInfo* name = Frame->GetNode("Name", 0);
                    KXmlInfo* type = Frame->GetNode("SubType", 0);
                    int st = atoi(type->GetText().c_str());
                    nl += NumToStr(st, 3);
                    nl += "    ; " + name->GetText() + " - " + g_blockTypes[st];
                    Code->Insert(lineNo++, nl);
                    nl = "       defb ";
                }
            }
        }
        lineNo = DeleteLines(Code, "numch", "defb", 1);
        Code->Insert(lineNo, "numch  defb " + NumToStr(blocks, 3, true) + "            ; number of chars.");
    }
}
//---------------------------------------------------------------------------
// ParseEvents
/**
 * Parse the AGD events into the AGD game engine
 * @author  Tony Thompson
 * @date    Created 25 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::ParseEvents(KXmlInfo*& XmlData, TStringList*& Code)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Code))
    {
        int lineNo = DeleteLines(Code, ";", "TG:EVENTS");
        KXmlInfo* CodeEditor = XmlData->GetNode("CodeEditor", 0);
        if (true == SAFE_PTR(CodeEditor))
        {
            KXmlInfo* Files = CodeEditor->GetNode("Files", 0);
            if (true == SAFE_PTR(Files))
            {
                // Find the AgdGameEngine.asm file
                // insert the resources into it
                for (KXmlNodes::iterator it = Files->begin(); it != Files->end(); it++)
                {
                    AnsiString sFile = (*it)->GetText();
                    if (ExtractFileExt(sFile) == ".agd" && FileExists(sFile))
                    {
                        sFile[sFile.Length()-0] = 'm';
                        sFile[sFile.Length()-1] = 's';
                        Code->Insert(++lineNo, "include \"" + sFile + "\"");
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
// DeleteLines
/**
 * Deletes the section of code indicated by s1 and s2 being present
 * If maxlines is >0 then that number of lines are removed
 * else it stops deleting when s1 and s2 are true again.
 * Basically we are clearing a section of code lines to be replaced with the
 * newly generated code lines. 
 * @author  Tony Thompson
 * @date    Created 19 December 2012
 * @remarks Copyright Scorpio Software 2012
 */
//---------------------------------------------------------------------------
int __fastcall AGDParserPlugin::DeleteLines(TStringList*& Code, const AnsiString& s1,const AnsiString& s2, int maxLines)
{
    int line = -1;
    for (int i = 0; i < Code->Count && line == -1; ++i)
    {
        int p1 = Code->Strings[i].Pos(s1);
        int p2 = Code->Strings[i].Pos(s2);
        if (p1 && p2 && p1 < p2)
        {
            line = i;
        }
    }
    if (line != -1)
    {
        if (maxLines > 0)
        {
            int dl = line;
            // delete the lines until we find the next marker again
            while (maxLines-- > 0)
            {
                Code->Delete(dl);
            }
        }
        else
        {
            int dl = line + 1;
            // delete the lines until we find the next marker again
            bool stop = false;
            while (!stop)
            {
                int p1 = Code->Strings[dl].Pos(s1);
                int p2 = Code->Strings[dl].Pos(s2);
                stop = (p1 && p2 && p1 < p2);
                if (!stop)
                {
                    Code->Delete(dl);
                }
            }
        }
    }
    return line;
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
AnsiString __fastcall AGDParserPlugin::NumToStr(int number, int len, bool leftAlign)
{
    AnsiString num;
    if (leftAlign)
    {
        num = IntToStr(number) + AnsiString::StringOfChar(' ', len);
        num = num.SubString(1, len);
    }
    else
    {
        num = AnsiString::StringOfChar(' ', len) + IntToStr(number);
        num = num.SubString(num.Length() - len + 1, len);
    }
    return num;
}
//---------------------------------------------------------------------------
// ConvertStringToData
/**
 * Converts the XML Image data (Alpha-Hexidecimal) into binary form
 * @param   pData       the buffer to receive the converted data
 * @param   sData       the string buffer to convert
 * @param   bInvertByte flag: indicates that the data is mask data and needs to be inverted
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall AGDParserPlugin::ConvertStringToData(unsigned char* pData, const AnsiString& sData, bool bInvertByte)
{
    // now allocate some new data
    int iSize = sData.Length() / 2;
    unsigned char invertByte = bInvertByte ? 255 : 0;
    // now convert the ascii-hex
    for (int i = 0; i < iSize; i++)
    {
        pData[i] = ((sData[i * 2 + 1] - 'A') << 4) | (sData[i * 2 + 2] - 'A');
        pData[i] = pData[i] ^ invertByte;
    }
}
//---------------------------------------------------------------------------

