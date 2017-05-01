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
using namespace ImageParser;
//---------------------------------------------------------------------------
#define SUPPORTED_PALETTES 7
String g_sSupportedPalettes[SUPPORTED_PALETTES] =
{
    "Monochrome",
    "ZX Spectrum",
    "ZX Spectrum Hi Colour",
    "ZX Spectrum ULAplus",
    "Enterprise 64/128 - Attribute Graphics",
    "Sam Coupe Mode 1",
    "Sam Coupe Mode 2"
};
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from ImageEditor.cpp to create a new Plugin object. The ImageEditor.cpp only uses the
 * Base class reference. So this function returns a Plugin object to use of type class ZXBasePlugin.
 * @return  ZXBasePlugin a ZXBasePlugin compatible object
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
SevenuPImageParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new SevenuPImageParserPlugin();
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
__fastcall SevenuPImageParserPlugin::SevenuPImageParserPlugin()
: m_DataOutputted(doGraphicsAttributes)
, m_Compiler(asmGeneric)
, m_Interleave(iSprite)
, m_NumberBase(nbHexidecimal)
, m_AttributeMaskBits(0xFF)
, m_AttributeMask(false)
, m_MaskBefore(false)
, m_UseLabel(true)
, m_ZigZagged(false)
, m_AddZ88DK(true)
{
    RL_METHOD
    frmSevenuPImageParserOptions = new TfrmSevenuPImageParserOptions(NULL);
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
__fastcall SevenuPImageParserPlugin::~SevenuPImageParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmSevenuPImageParserOptions);
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
HRESULT __fastcall SevenuPImageParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmSevenuPImageParserOptions))
    {
        hResult = frmSevenuPImageParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall SevenuPImageParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmSevenuPImageParserOptions))
    {
        hResult = frmSevenuPImageParserOptions->Release();
    }
    SAFE_DELETE(frmSevenuPImageParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
// RegisterEvents
/**
 * Register for events from with the plugin environment
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
void __fastcall SevenuPImageParserPlugin::RegisterEvents(void)
{
}
//---------------------------------------------------------------------------
// GetOptionsPanel
/**
 * Gets our GUI Options panel
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
HRESULT __fastcall SevenuPImageParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmSevenuPImageParserOptions))
    {
        Panel = frmSevenuPImageParserOptions->panSevenuPImageParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
// GetResourceTypes
/**
 * Generates a list of resource types we can parse
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
HRESULT __fastcall SevenuPImageParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Types))
    {
        Types->Clear();
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
                    if (true == SAFE_PTR(Type))
                    {
                        Types->Add(Type->GetText());
                    }
                }
            }
        }
        return Types->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;
}
//---------------------------------------------------------------------------
// GetResourcesList
/**
 * Generates a list of resources that this plugin can parse
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
HRESULT __fastcall SevenuPImageParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Resources))
    {
        Resources->Clear();
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor", 0);
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' images and get all types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Images = (*it);
                if (true == SAFE_PTR(Images) && Images->GetName() == "Images")
                {
                    KXmlInfo* Type = Images->GetNode("Type", 0);
                    if (true == SAFE_PTR(Type) && Type->GetText() == sType)
                    {
                        for (KXmlNodes::iterator Iit = Images->begin(); Iit != Images->end(); Iit++)
                        {
                            if ((*Iit)->GetName() == "Image")
                            {
                                KXmlInfo* Frame = (*Iit)->GetNode("Frame", 0);
                                if (true == SAFE_PTR(Frame))
                                {
                                    KXmlInfo* Palette = Frame->GetNode("Palette", 0);
                                    if (true == SAFE_PTR(Palette) && PaletteSupported(Palette->GetText()))
                                    {
                                        KXmlInfo* Name = Frame->GetNode("Name", 0);
                                        if (true == SAFE_PTR(Name))
                                        {
                                            Resources->Add(Name->GetText());
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return Resources->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;
}
//---------------------------------------------------------------------------
// ParseResources
/**
 * Generates the Parse tags and then generates the source code for the image
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
HRESULT __fastcall SevenuPImageParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
{
    HRESULT hResult = E_POINTER;
    String sType;
    String sName;

    if (ParserData != "[Begin]" && ParserData != "[End]")
    {
        GetResourceInfo(Resource, sType, sName);

        if (true == SAFE_PTR(XmlData) && SAFE_PTR(Code) && sType != "" && sName != "")
        {
            if (ParserData.Trim() == "")
            {
                m_BytePrefix = "";
                // set the parser data parameter from the GUI
                // Assembly options
                if (frmSevenuPImageParserOptions->radSourceCodeAsm->Checked)
                {
                    m_BytePrefix   = frmSevenuPImageParserOptions->edtPrefix->Text;
                    m_LabelPrefix  = frmSevenuPImageParserOptions->edtLabelPrefix->Text;
                    m_LabelPostfix = frmSevenuPImageParserOptions->edtLabelPostfix->Text;
                    ParserData  = ":scAsm";                 // Assembler
                    ParserData += ":ap" + m_BytePrefix;     // Assembler Prefix
                    ParserData += ":lpr" + m_LabelPrefix + "rpl";
                    ParserData += ":lpo" + m_LabelPostfix + "opl:";
                    m_Compiler = asmGeneric;
                    m_UseLabel = true;
                    if (!frmSevenuPImageParserOptions->chkSourceCodeUseLabel->Checked)
                    {
                        m_UseLabel = false;
                        ParserData += ":NAL";               // No Assembly Label
                    }
                }
                else
                {
                    m_Compiler = cGeneric;
                    ParserData = "scC";                     // C Compiler
                }

                m_AddZ88DK = false;
                if (frmSevenuPImageParserOptions->chkSourceCodeZ88DK->Checked)
                {
                    ParserData += ":Z88DK";             // Z88DK 
                    m_AddZ88DK = true;
                }

                m_ZigZagged = false;
                if (frmSevenuPImageParserOptions->chkMiscZigZag->Checked)
                {
                    m_ZigZagged = true;
                    ParserData += ":ZZ";                // Zig Zagged lines
                }

                if (frmSevenuPImageParserOptions->radDataGraphicsAttributes->Checked)
                {
                    ParserData += ":doGA";              // Data Out: Graphics+Attributes
                    m_DataOutputted = doGraphicsAttributes;
                }
                else if (frmSevenuPImageParserOptions->radDataAttributesGraphics->Checked)
                {
                    ParserData += ":doAG";              // Data Out: Attributes+Graphics
                    m_DataOutputted = doAttributesGraphics;
                }
                else if (frmSevenuPImageParserOptions->radDataGraphics->Checked)
                {
                    ParserData += ":doGr";              // Data Out: Graphics
                    m_DataOutputted = doGraphics;
                }
                else
                {
                    ParserData += ":doAt";              // Data Out: Attributes
                    m_DataOutputted = doAttributes;
                }

                m_MaskBefore = false;
                if (frmSevenuPImageParserOptions->chkMaskingBeforeGraphics->Checked)
                {
                    ParserData += ":MB";                // Mask Before
                    m_MaskBefore = true;
                }

                m_AttributeMask = false;
                if (frmSevenuPImageParserOptions->chkMaskingAttributeMask->Checked)
                {
                    ParserData += ":AM";                // Use Attribute Mask
                    m_AttributeMask = true;
                    m_AttributeMaskBits = 0;
                    if (frmSevenuPImageParserOptions->chkMaskingAttributeInk->Checked)
                    {
                        m_AttributeMaskBits |= abInk;   // Attr Mask: Ink
                        ParserData += ":abIn";
                    }
                    if (frmSevenuPImageParserOptions->chkMaskingAttributePaper->Checked)
                    {
                        m_AttributeMaskBits |= abPaper; // Attr Mask: Paper
                        ParserData += ":abPa";
                    }
                    if (frmSevenuPImageParserOptions->chkMaskingAttributeBright->Checked)
                    {
                        m_AttributeMaskBits |= abBright;// Attr Mask: Bright
                        ParserData += ":abBr";
                    }
                    if (frmSevenuPImageParserOptions->chkMaskingAttributeFlash->Checked)
                    {
                        m_AttributeMaskBits |= abFlash; // Attr Mask: Flash
                        ParserData += ":abFl";
                    }
                }

                m_MaskInvert = false;
                if (frmSevenuPImageParserOptions->radMaskingMaskCovers->Checked)
                {
                    ParserData += ":MI";                // Mask Invert
                    m_MaskInvert = true;
                }

                if (frmSevenuPImageParserOptions->radInterleaveLine->Checked)
                {
                    m_Interleave = iLine;
                    ParserData += ":ilLn";              // Interleave: Line
                }
                else if (frmSevenuPImageParserOptions->radInterleaveCharacter->Checked)
                {
                    m_Interleave = iCharacter;
                    ParserData += ":ilCh";              // Interleave: Character
                }
                else if (frmSevenuPImageParserOptions->radInterleaveColumn->Checked)
                {
                    m_Interleave = iColumn;
                    ParserData += ":ilCn";              // Interleave: Column
                }
                else if (frmSevenuPImageParserOptions->radInterleaveFrames->Checked)
                {
                    m_Interleave = iFrames;
                    ParserData += ":ilFr";              // Interleave: Frames
                }
                else if (frmSevenuPImageParserOptions->radInterleaveSprite->Checked)
                {
                    m_Interleave = iSprite;
                    ParserData += ":ilSp";              // Interleave: Sprite (default)
                }

                for (int i = 0; i < frmSevenuPImageParserOptions->lstByteSortPriority->Items->Count; i++)
                {
                    if (frmSevenuPImageParserOptions->lstByteSortPriority->Items->Strings[i] == "X Char")
                    {
                        ParserData += ":soXC";          // Sort Order: X Char
                        m_SortOrder[i] = soXChar;
                    }
                    else if (frmSevenuPImageParserOptions->lstByteSortPriority->Items->Strings[i] == "Y Char")
                    {
                        ParserData += ":soYC";
                        m_SortOrder[i] = soYChar;       // Sort Order: Y Char
                    }
                    else if (frmSevenuPImageParserOptions->lstByteSortPriority->Items->Strings[i] == "Char Line")
                    {
                        ParserData += ":soCL";
                        m_SortOrder[i] = soCharLine;    // Sort Order: Char Line
                    }
                    else if (frmSevenuPImageParserOptions->lstByteSortPriority->Items->Strings[i] == "Mask")
                    {
                        ParserData += ":soMk";          // Sort Order: Mask
                        m_SortOrder[i] = soMask;
                    }
                    else if (frmSevenuPImageParserOptions->lstByteSortPriority->Items->Strings[i] == "Frame Number")
                    {
                        ParserData += ":soFN";          // Sort Order: Frame Number
                        m_SortOrder[i] = soFrameNumber;
                    }
                }

                if (frmSevenuPImageParserOptions->radDecimal->Checked)
                {
                    m_NumberBase = nbDecimal;
                    ParserData += ":Dec";               // Base: Decimal
                }
                else if (frmSevenuPImageParserOptions->radHexidecimal->Checked)
                {
                    m_NumberBase = nbHexidecimal;
                    ParserData += ":Hex";               // Base: Hexidecimal
                }
                else if (frmSevenuPImageParserOptions->radBinary->Checked)
                {
                    m_NumberBase = nbBinary;
                    ParserData += ":Bin";               // Base: Binary
                }
                else
                {
                    m_NumberBase = nbOctal;
                    ParserData += ":Oct";               // Base: Octal
                }
            }
            else
            {
                // set the parser data from the parser data string

                // Get Number Base
                if (ParserData.Pos("Dec") > 0)
                    m_NumberBase = nbDecimal;
                else if (ParserData.Pos("Hex") > 0)
                    m_NumberBase = nbHexidecimal;
                else if (ParserData.Pos("Bin") > 0)
                    m_NumberBase = nbBinary;
                else
                    m_NumberBase = nbOctal;

                // Get Compiler
                m_Compiler = cGeneric;
                if (ParserData.Pos("scAsm"))
                {
                    m_Compiler = asmGeneric;
                }

                // Get Assembler Prefix
                m_BytePrefix = "";
                if (m_Compiler == asmGeneric && ParserData.Pos("ap") > 0)
                {
                    int pos = ParserData.Pos("ap");
                    for (int i = pos + 2; i <= ParserData.Length() && ParserData[i] != ':'; i++)
                    {
                        m_BytePrefix += ParserData[i];
                    }
                }

                // Get Data Output (Default: Graphics + Attribute)
                m_DataOutputted = doGraphicsAttributes;
                if (ParserData.Pos("doAG") > 0)
                {
                    // Attr + Graphics
                    m_DataOutputted = doAttributesGraphics;
                }
                else if (ParserData.Pos("doGr") > 0)
                {
                    // Graphics
                    m_DataOutputted = doGraphics;
                }
                else if (ParserData.Pos("doAt") > 0)
                {
                    // Attributes
                    m_DataOutputted = doAttributes;
                }

                // Get Interleave (default: Sprite)
                m_Interleave = iSprite;
                if (ParserData.Pos("ilLn") > 0)
                {
                    // Line
                    m_Interleave = iLine;
                }
                else if (ParserData.Pos("ilCh") > 0)
                {
                    // Character
                    m_Interleave = iCharacter;
                }
                else if (ParserData.Pos("ilCn") > 0)
                {
                    // Column
                    m_Interleave = iColumn;
                }
                else if (ParserData.Pos("ilFr") > 0)
                {
                    // Frames
                    m_Interleave = iFrames;
                }

                // Get Sort Order
                int SortPos[5];
                SortPos[0] = ParserData.Pos(":soXC");
                SortPos[1] = ParserData.Pos(":soCL");
                SortPos[2] = ParserData.Pos(":soYC");
                SortPos[3] = ParserData.Pos(":soMk");
                SortPos[4] = ParserData.Pos(":soFN");

                // find the mininum sort order position
                int min = SortPos[0];
                for (int i = 1; i < 5; i++)
                {
                    if (SortPos[i] < min)
                    {
                        min = SortPos[i];
                    }
                }

                // convert the sort order positions into Sort Order values
                for (int i = 0; i < 5; i++)
                {
                    SortPos[i] -= min;
                    SortPos[i] /= 5;
                }

                // transfer the sort positions into the sort order array
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        // find position i
                        if (SortPos[j] == i)
                        {
                            // Sort Pos j holds sort order i
                            m_SortOrder[i] = static_cast<eSortOrder>(j);
                            break;
                        }
                    }
                }

                // get the last of the flags
                m_UseLabel      = ParserData.Pos("NAL"  ) == 0;
                m_AddZ88DK      = ParserData.Pos("Z88DK") > 0;
                m_AttributeMask = ParserData.Pos("AM"   ) > 0;
                m_MaskInvert    = ParserData.Pos("MI"   ) > 0;
                m_MaskBefore    = ParserData.Pos("MB"   ) > 0;
                m_ZigZagged     = ParserData.Pos("ZZ"   ) > 0;

                // get the attribute mask
                m_AttributeMaskBits = 0;
                if (m_AttributeMask)
                {
                    m_AttributeMaskBits |= ParserData.Pos("abIn") > 0 ? abInk    : 0;
                    m_AttributeMaskBits |= ParserData.Pos("abPa") > 0 ? abPaper  : 0;
                    m_AttributeMaskBits |= ParserData.Pos("abBr") > 0 ? abBright : 0;
                    m_AttributeMaskBits |= ParserData.Pos("abFl") > 0 ? abFlash  : 0;
                }

                m_LabelPrefix = "";
                int l = ParserData.Pos(":lpr");
                int r = ParserData.Pos("rpl" );
                if (l > 0 && r > 0)
                {
                    m_LabelPrefix = ParserData.SubString(l + 4, r - l - 4);
                }

                m_LabelPostfix = ":";
                l = ParserData.Pos(":lpo");
                r = ParserData.Pos("opl" );
                if (l > 0 && r > 0)
                {
                    m_LabelPostfix = ParserData.SubString(l + 4, r - l - 4);
                }
            }

            // parse the xml data into code
            KXmlInfo* ResNode = GetResourceNode(XmlData, sType, sName);
            if (true == SAFE_PTR(ResNode))
            {
                // process the node
                hResult = ParseXmlNode(ResNode, Code);
            }
            else
            {
                // ERROR! Failed to find the resource XML node
                hResult = E_FAIL;
            }
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
// GetResourceInfo
/**
 *
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall SevenuPImageParserPlugin::GetResourceInfo(const String& sResource, String& sType, String& sName)
{
    int iSlash = sResource.Pos('\\');
    if (iSlash)
    {
        sType = sResource.SubString(1, iSlash - 1);
        sName = sResource.SubString(iSlash + 1, sResource.Length());
    }
}
//---------------------------------------------------------------------------
// GetResourceKXmlNodes
/**
 * Gets a Resource KXmlNodes from the XML data
 * @param   XmlData     the xml data block to search
 * @param   sType       the type of data to find
 * @param   sName       the name of the data to find
 * @return  The XML Info block that contains the resource data needed
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
KXmlInfo* __fastcall SevenuPImageParserPlugin::GetResourceNode(KXmlInfo*& XmlData, const String& sType, const String& sName)
{
    if (true == SAFE_PTR(XmlData))
    {
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor", 0);
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' images and get all types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Images = (*it);
                if (true == SAFE_PTR(Images) && Images->GetName() == "Images")
                {
                    KXmlInfo* Type = Images->GetNode("Type", 0);
                    if (true == SAFE_PTR(Type) && Type->GetText() == sType)
                    {
                        for (KXmlNodes::iterator Iit = Images->begin(); Iit != Images->end(); Iit++)
                        {
                            if ((*Iit)->GetName() == "Image")
                            {
                                KXmlInfo* Frame = (*Iit)->GetNode("Frame", 0);
                                if (true == SAFE_PTR(Frame))
                                {
                                    KXmlInfo* Name = Frame->GetNode("Name", 0);
                                    if (Name->GetText() == sName)
                                    {
                                        return (*Iit);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return NULL;
}
//---------------------------------------------------------------------------
// ParseXmlKXmlNodes
/**
 * Parses the XML KXmlNodes into Source Code (adds the generic source code header)
 * @param   ResNode     Resource KXmlNodes to parse
 * @param   Code        the Source Code block to parse the data into
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
HRESULT __fastcall SevenuPImageParserPlugin::ParseXmlNode(KXmlInfo*& ResNode, TStringList*& Code)
{
    HRESULT hResult = S_OK;

    ZeroMemory(m_pPixels, 256 * sizeof(unsigned char*));
    ZeroMemory(m_pAttrs , 256 * sizeof(unsigned char*));
    ZeroMemory(m_pMasks , 256 * sizeof(unsigned char*));

    try
    {
        // convert the Resource KXmlNodes into a image array
        int iFrame = 0;
        bool bMultiFramed = ResNode->size() > 1;
        String CL, CR;
        if (m_Compiler == cGeneric)
        {
            Code->Add("/***************************************************************************/");
            Code->Add("/* C source file created by TommyGun (Based on output from SevenuP v1.20   */");
            Code->Add("/* SevenuP  (C) Copyright 2002-2006 by Jaime Tejedor Gomez, aka Metalbrain */");
            Code->Add("/* TommyGun (C) Copyright 2005-2007 by Tony Thompson, aka Kiwi             */");
            Code->Add("/***************************************************************************/");
            CL = "/* ";
            CR = " */";
        }
        else
        {
            Code->Add(";-------------------------------------------------------------------------;");
            Code->Add("; C source file created by TommyGun (Based on output from SevenuP v1.20   ;");
            Code->Add("; SevenuP  (C) Copyright 2002-2006 by Jaime Tejedor Gomez, aka Metalbrain ;");
            Code->Add("; TommyGun (C) Copyright 2005-2007 by Tony Thompson, aka Kiwi             ;");
            Code->Add(";-------------------------------------------------------------------------;");
            CL = "; ";
        }

        // get ALL the frame data
        m_Frames = ResNode->size();
        String* sPalette = new String[m_Frames];
        String* sPixels  = new String[m_Frames];
        String* sAttrs   = new String[m_Frames];
        String* sMasks   = new String[m_Frames];

        for (KXmlNodes::iterator FrameIt = ResNode->begin(); FrameIt != ResNode->end(); FrameIt++, ++iFrame)
        {
            m_IsMasked = (*FrameIt)->GetNode("IsMasked", 0)->GetText().LowerCase() == "true";
            // get the frames properties
            int iWidth = (*FrameIt)->GetNode("Width", 0)->GetInt();
            int iHeight = (*FrameIt)->GetNode("Height", 0)->GetInt();
            sPalette[iFrame] = (*FrameIt)->GetNode("Palette", 0)->GetText();
            sPixels[iFrame] = (*FrameIt)->GetNode("Pixels", 0)->GetText();
            if (sPalette[iFrame] != "Monochrome")
            {
                sAttrs[iFrame] = (*FrameIt)->GetNode("Attributes", 0)->GetText();
            }
            if (m_IsMasked)
            {
                sMasks[iFrame] = (*FrameIt)->GetNode("Masks", 0)->GetText();
            }

            bool bPixelsOK =                            ((iWidth / 8) *  iHeight      * 2) == sPixels[iFrame].Length();
            bool bAttrsOK  = sAttrs[iFrame].Length() ? (((iWidth / 8) * (iHeight / 8) * 2) == sAttrs[iFrame].Length()) : true;
                 bAttrsOK |= sAttrs[iFrame].Length() ? (((iWidth / 8) * (iHeight    ) * 2) == sAttrs[iFrame].Length()) : true;
                 bAttrsOK |= sPalette[iFrame] == "Monochrome";
            bool bMasksOK  = sMasks[iFrame].Length() ? (((iWidth / 8) *  iHeight      * 2) == sMasks[iFrame].Length()) : true;

            if (bPixelsOK && bAttrsOK && bMasksOK)
            {
                GetFrameData(iFrame, sPixels[iFrame], sAttrs[iFrame], sMasks[iFrame], sPalette[iFrame], iWidth / 8);
            }
        }

        // then parse all the frames together
        // get the name of the frame and make a label
        m_sName = (*ResNode->begin())->GetNode("Name", 0)->GetText().Trim();
        // get the frames properties
        int iWidth = (*ResNode->begin())->GetNode("Width", 0)->GetInt();
        int iHeight = (*ResNode->begin())->GetNode("Height", 0)->GetInt();
        Code->Add(CL + "Name   : " + m_sName + CR);
        if (bMultiFramed)
        {
            Code->Add(CL + "Frames : " + IntToStr(m_Frames) + CR);
        }
        Code->Add(CL + "Size   : " + IntToStr(iWidth) + "x" + IntToStr(iHeight) + CR);
        Code->Add(CL + "Palette: " + sPalette[0] + CR);
        Code->Add(CL + "Masked : " + (m_IsMasked ? String("Yes") : String("No")) + CR);
        Code->Add(CL + "RowOrder: " + (m_ZigZagged ? String("ZigZag") : String("Classic")) + CR);
        if (m_AddZ88DK)
        {
            Code->Add(CL + "Z88DK: First 2 bytes are Pixel Height and Width of image" + CR);
        }

        bool bPixelsOK =                       ((iWidth / 8) *  iHeight      * 2) == sPixels[0].Length();
        bool bAttrsOK  = sAttrs[0].Length() ? (((iWidth / 8) * (iHeight / 8) * 2) == sAttrs[0].Length()) : true;
             bAttrsOK |= sAttrs[0].Length() ? (((iWidth / 8) * (iHeight    ) * 2) == sAttrs[0].Length()) : true;
        bool bMasksOK  = sMasks[0].Length() ? (((iWidth / 8) *  iHeight      * 2) == sMasks[0].Length()) : true;

        if (bPixelsOK && bAttrsOK && bMasksOK)
        {
            ParseSevenuPData(iWidth, iHeight, Code);
        }

        // free the buffers
        for (; m_Frames; --m_Frames)
        {
            SAFE_ARRAY_DELETE(sPalette);
            SAFE_ARRAY_DELETE(sPixels);
            SAFE_ARRAY_DELETE(sAttrs);
            SAFE_ARRAY_DELETE(sMasks);
            SAFE_ARRAY_DELETE(m_pPixels[m_Frames-1]);
            SAFE_ARRAY_DELETE(m_pAttrs[m_Frames-1]);
            SAFE_ARRAY_DELETE(m_pMasks[m_Frames-1]);
        }
    }
    catch(...)
    {
        hResult = E_FAIL;
    }

    return hResult;
}
//---------------------------------------------------------------------------
// ParseSevenuPData
/**
 * Parses the image to Source Code
 * @param   iWidth  the width of the image
 * @param   iHeight the height of the image
 * @param   Code    the Source Code block to place the conversion
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall SevenuPImageParserPlugin::ParseSevenuPData(int iWidth, int iHeight, TStringList*& Code)
{
    if (m_Compiler == cGeneric)
    {
        ParseIntoC(iWidth, iHeight, Code);
    }
    else
    {
        ParseIntoAsm(iWidth, iHeight, Code);
    }
}
//---------------------------------------------------------------------------
// ParseIntoC
/**
 * Parses the image into C Source Code
 * @param   iWidth  the width of the image
 * @param   iHeight the height of the image
 * @param   Code    the Source Code block to place the conversion
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall SevenuPImageParserPlugin::ParseIntoC(int iWidth, int iHeight, TStringList*& Code)
{
    int iCw = (iWidth  / 8) + ((iWidth  % 8) ? 1 : 0);  // Char width of image
    int iHw = (iHeight / 8) + ((iHeight % 8) ? 1 : 0);  // Char height of image
    int iPs = (iCw * iHeight) * (m_IsMasked ? 2 : 1);   // Pixels Size in bytes
    int iAs = (iCw * iHw);
    int iSize = 0;

    switch(m_DataOutputted)
    {
        case doAttributesGraphics:
        case doGraphicsAttributes:
            iSize = iPs + iAs;
            break;
        case doGraphics:
            iSize = iPs;
            break;
        case doAttributes:
            iSize = iAs;
            break;
    }
    iSize *= m_Frames;
    iSize += m_AddZ88DK ? 2 : 0;
    Code->Add("unsigned char " + m_sName + "[" + IntToStr(iSize) + "] =");
    Code->Add("{");

    if (m_AddZ88DK)
    {
        Code->Add("\t" + m_BytePrefix + "\t" + NumToStr(iHeight) + ", " + NumToStr(iWidth) + ", ");
    }

    switch (m_DataOutputted)
    {
    case doGraphicsAttributes:
        OutputGraphics(iWidth, iHeight, Code);
        OutputAttributes(iWidth, iHeight, Code, true);
        break;
    case doAttributesGraphics:
        OutputAttributes(iWidth, iHeight, Code);
        OutputGraphics(iWidth, iHeight, Code, true);
        break;
    case doGraphics:
        OutputGraphics(iWidth, iHeight, Code, true);
        break;
    case doAttributes:
        OutputAttributes(iWidth, iHeight, Code, true);
        break;
    }
    Code->Add("};");
}
//---------------------------------------------------------------------------
// ParseIntoAsm
/**
 * Parses the image to Assembler
 * @param   iWidth  the width of the image
 * @param   iHeight the height of the image
 * @param   Code    the Source Code block to place the conversion
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall SevenuPImageParserPlugin::ParseIntoAsm(int iWidth, int iHeight, TStringList*& Code)
{
    if (m_UseLabel)
    {
        Code->Add(m_LabelPrefix + m_sName + m_LabelPostfix);
    }
    if (m_AddZ88DK)
    {
        Code->Add("\t" + m_BytePrefix + "\t" + NumToStr(iHeight) + ", " + NumToStr(iWidth) + ", ");
    }

    switch (m_DataOutputted)
    {
    case doGraphicsAttributes:
        OutputGraphics(iWidth, iHeight, Code);
        OutputAttributes(iWidth, iHeight, Code);
        break;
    case doAttributesGraphics:
        OutputAttributes(iWidth, iHeight, Code);
        OutputGraphics(iWidth, iHeight, Code);
        break;
    case doGraphics:
        OutputGraphics(iWidth, iHeight, Code);
        break;
    case doAttributes:
        OutputAttributes(iWidth, iHeight, Code);
        break;
    }
}
//---------------------------------------------------------------------------
// OutputGraphics
/**
 * Outputs the pixel/mask data into Source Code
 * @param   iWidth  the width of the image
 * @param   iHeight the height of the image
 * @param   Code    the Source Code block to place the conversion
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall SevenuPImageParserPlugin::OutputGraphics(int iWidth, int iHeight, TStringList*& Code, bool bLastComma)
{
    // indexes
    int iCw = (iWidth  / 8) + ((iWidth  % 8) ? 1 : 0);  // Char width of image
    int iCh = (iHeight / 8) + ((iHeight % 8) ? 1 : 0);  // Char height of image
    int iXc = 0;                                        // X Char priority position
    int iCl = 0;                                        // Char Line priority position
    int iYc = 0;                                        // Y Char priority position
    int iMk = 0;                                        // Mask priority position
    int iFn = 0;                                        // Frame Number priority position
    int iIs = m_Frames * iCw * iHeight;                 // Image Size in bytes
    int iIc = 0;                                        // Image count
    // setup the loop counters for the sort order priorities
    int LoopCounts[5];
    int Loop[5];
    for (int i = 0; i < 5; i++)
    {
        switch (m_SortOrder[i])
        {
            case soXChar:
                LoopCounts[i] = iCw;
                iXc = i;
                break;
            case soCharLine:
                LoopCounts[i] = 8;
                iCl = i;
                break;
            case soYChar:
                LoopCounts[i] = iCh;
                iYc = i;
                break;
            case soMask:
                LoopCounts[i] = m_IsMasked ? 2 : 1;
                iMk = i;
                break;
            case soFrameNumber:
                LoopCounts[i] = m_Frames;
                iFn = i;
                break;
        }
    }
    int iColumn = -1;
    String CodeLine;
    unsigned char Data = 0;
    // generate values by looping through the sort order in the correct priority
    for (Loop[4] = 0; Loop[4] < LoopCounts[4]; ++Loop[4])
    {
        for (Loop[3] = 0; Loop[3] < LoopCounts[3]; ++Loop[3])
        {
            for (Loop[2] = 0; Loop[2] < LoopCounts[2]; ++Loop[2])
            {
                for (Loop[1] = 0; Loop[1] < LoopCounts[1]; ++Loop[1])
                {
                    for (Loop[0] = 0; Loop[0] < LoopCounts[0]; ++Loop[0])
                    {
                        int iXos = ((m_ZigZagged && (Loop[iYc] * 8) + Loop[iCl]) % 2) ? iCw - Loop[iXc]: Loop[iXc];
                        int Offset = (((Loop[iYc] * 8) +
                                        Loop[iCl]) *
                                        iCw) +              // y row +
                                        iXos;               // x column
                        if (m_IsMasked && ((Loop[iMk] && !m_MaskBefore) || (!Loop[iMk] && m_MaskBefore)))
                        {
                            // offset is into the mask
                            Data = m_pMasks[Loop[iFn]][Offset];
                            if (m_MaskInvert)
                            {
                                Data = Data ^ 255;
                            }
                        }
                        else
                        {
                            // offset is into the image
                            Data = m_pPixels[Loop[iFn]][Offset];
                        }

                        // construct the code line of 8 values
                        // get the column pos
                        iColumn = (iColumn + 1) % 8;
                        if (iColumn == 0)
                        {
                            // first column so add the assembler prefix (eg.  defb )
                            CodeLine = "\t" + m_BytePrefix + "\t";
                        }
                        // append the value
                        CodeLine += NumToStr(Data);
                        ++iIc;
                        bool bAddComma = !bLastComma || iIc < iIs;
                        if (m_Compiler != cGeneric && iColumn == 7)
                        {
                            bAddComma = false;
                        }
                        if (bAddComma)
                        {
                            // not the end of the line so add a comma
                            CodeLine += ", ";
                        }
                        if (iColumn == 7)
                        {
                            // is the end of the line so add the line to our source code
                            Code->Add(CodeLine);
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
// OutputAttributes
/**
 * Outputs the attributes data into Source Code
 * @param   iWidth  the width of the image
 * @param   iHeight the height of the image
 * @param   Code    the Source Code block to place the conversion
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall SevenuPImageParserPlugin::OutputAttributes(int iWidth, int iHeight, TStringList*& Code, bool bLastComma)
{
    // indexes
    int iCw = (iWidth  / 8) + ((iWidth  % 8) ? 1 : 0);  // Char width of image
    int iCh = (iHeight / 8) + ((iHeight % 8) ? 1 : 0);  // Char height of image
    int iXc = 0;                                        // X Char priority position
    int iYc = 0;                                        // Y Char priority position
    int iMk = 0;                                        // Mask priority position
    int iFn = 0;                                        // Frame Number priority position
    int iIs = m_Frames * iCw * iCh;                     // Image Size in bytes
    int iIc = 0;                                        // Image count
    // setup the loop counters for the sort order priorities
    int LoopCounts[4];
    int Loop[4];
    int li = 0;
    for (int i = 0; i < 5; i++)
    {
        switch (m_SortOrder[i])
        {
            case soXChar:
                LoopCounts[li] = iCw;
                iXc = li;
                li++;
                break;
            case soYChar:
                LoopCounts[li] = iCh;
                iYc = li;
                li++;
                break;
            case soMask:
                // attributes aren't masked
                LoopCounts[li] = m_IsMasked ? 2 : 1;
                iMk = li;
                li++;
                break;
            case soFrameNumber:
                LoopCounts[li] = m_Frames;
                iFn = li;
                li++;
                break;
        }
    }
    int iColumn = -1;
    String CodeLine;
    unsigned char Data = 0;
    unsigned char AttrMask = m_AttributeMask ? m_AttributeMaskBits : 0xFF;
    // generate values by looping through the sort order in the correct priority
    for (Loop[3] = 0; Loop[3] < LoopCounts[3]; ++Loop[3])
    {
        for (Loop[2] = 0; Loop[2] < LoopCounts[2]; ++Loop[2])
        {
            for (Loop[1] = 0; Loop[1] < LoopCounts[1]; ++Loop[1])
            {
                for (Loop[0] = 0; Loop[0] < LoopCounts[0]; ++Loop[0])
                {
                    int Offset = (Loop[iYc] * iCw) +  // y row +
                                  Loop[iXc];          // x column
                    if (m_IsMasked && ((Loop[iMk] && !m_MaskBefore) || (!Loop[iMk] && m_MaskBefore)))
                    {
                        // value is the attribute mask
                        Data = AttrMask;
                    }
                    else
                    {
                        // offset is into the image attributes
                        Data = (m_pAttrs[Loop[iFn]][Offset]);
                    }

                    // construct the code line of 8 values
                    // get the column pos
                    iColumn = (iColumn + 1) % 8;
                    if (iColumn == 0)
                    {
                        // first column so add the assembler prefix (eg.  defb )
                        CodeLine = "\t" + m_BytePrefix + "\t";
                    }
                    // append the value
                    CodeLine += NumToStr(Data);
                    ++iIc;
                    bool bAddComma = !bLastComma || iIc < iIs;
                    if (m_Compiler != cGeneric && iColumn == 7)
                    {
                        bAddComma = false;
                    }
                    if (bAddComma)
                    {
                        // not the end of the line so add a comma
                        CodeLine += ", ";
                    }
                    if (iColumn == 7)
                    {
                        // is the end of the line so add the line to our source code
                        Code->Add(CodeLine);
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
// GetFrameData
/**
 * Retrieves the alpha-hexidecimal data from the XML node
 * Gets the pixels, attributes and mask data
 * @param   index       the frame index (used to store the converted data into the pixel/attr/mask arrays)
 * @param   sPixels     the pixel data to convert
 * @param   sAttrs      the attribute data to convert
 * @param   sMasks      the mask data to convert
 * @param   sPalette    the palette of the image
 * @param   iWidth      the width of the image
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall SevenuPImageParserPlugin::GetFrameData(int index, const String& sPixels, const String& sAttrs, const String& sMasks, const String& sPalette, int iWidth)
{
    if (sPixels.Trim() != "")
    {
        ConvertStringToData(m_pPixels[index], sPixels, iWidth);
    }
    if (sMasks.Trim() != "")
    {
        ConvertStringToData(m_pMasks[index], sMasks, iWidth, m_MaskInvert);
    }
    if (sAttrs.Trim() != "")
    {
        ConvertStringToData(m_pAttrs[index], sAttrs, iWidth);
    }
}
//---------------------------------------------------------------------------
// ConvertStringToData
/**
 * Converts the XML Image data (Alpha-Hexidecimal) into binary form
 * @param   pData       the buffer to receive the converted data
 * @param   sData       the string buffer to convert
 * @param   iWidth      the width of the image
 * @param   bInvertByte flag: indicates that the data is mask data and needs to be inverted
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall SevenuPImageParserPlugin::ConvertStringToData(unsigned char*& pData, const String& sData, int iWidth, bool bInvertByte)
{
    // delete the old data
    SAFE_ARRAY_DELETE(pData);
    // now allocate some new data
    int iSize = sData.Length() / 2;
	unsigned char invertByte = bInvertByte ? 255 : 0;
    pData = new unsigned char[iSize];
    // now convert the ascii-hex
    for (int i = 0; i < iSize; i++)
    {
        pData[i] = ((sData[i * 2 + 1] - 'A') << 4) | (sData[i * 2 + 2] - 'A');
		pData[i] = pData[i] ^ invertByte;
	}
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
String __fastcall SevenuPImageParserPlugin::NumToStr(unsigned char iNum)
{
    String sNum;
    int Width = 1;
    switch(m_NumberBase)
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
            sNum = "   ";
            sNum += IntToStr(iNum);
            Width = 3;
            break;
    }
    sNum = frmSevenuPImageParserOptions->GetPrefix(m_NumberBase) + sNum.SubString(sNum.Length() - (Width - 1), Width) + frmSevenuPImageParserOptions->GetPostfix(m_NumberBase);
    return sNum;
}
//---------------------------------------------------------------------------
// PaletteSupported
/**
 *
 * @return  bool        true palette support - false not supported
 * @param   sPalette    the palette to test support for
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
bool __fastcall SevenuPImageParserPlugin::PaletteSupported(const String& sPalette)
{
    bool bSupported = false;
    for (int i = 0; i < SUPPORTED_PALETTES && false == bSupported; i++)
    {
        bSupported = g_sSupportedPalettes[i].LowerCase() == sPalette.LowerCase();
    }
    return bSupported;
}
//---------------------------------------------------------------------------

