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
using namespace PaletteParser;
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
PaletteParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new PaletteParserPlugin();
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
__fastcall PaletteParserPlugin::PaletteParserPlugin()
: m_UseLabel(true)
, m_Compiler(asmGeneric)
, m_NumberBase(nbHexidecimal)
, m_BytePrefix("DEFB")
, m_LabelPrefix("")
, m_LabelPostfix(":")
, m_pPalette(NULL)
{
    RL_METHOD
    frmPaletteParserOptions = new TfrmPaletteParserOptions(NULL);
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
__fastcall PaletteParserPlugin::~PaletteParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmPaletteParserOptions);
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
HRESULT __fastcall PaletteParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmPaletteParserOptions))
    {
        hResult = frmPaletteParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall PaletteParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmPaletteParserOptions))
    {
        hResult = frmPaletteParserOptions->Release();
    }
    SAFE_DELETE(frmPaletteParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall PaletteParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall PaletteParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmPaletteParserOptions))
    {
        Panel = frmPaletteParserOptions->panPaletteParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall PaletteParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Types))
    {
        Types->Clear();
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor", 0);
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' palettes and get all supported types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Palettes = (*it);
                if (true == SAFE_PTR(Palettes) && Palettes->GetName() == "Palettes")
                {
                    Types->Add("Palettes");
                }
            }
        }
        return Types->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;
}
//---------------------------------------------------------------------------
HRESULT __fastcall PaletteParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
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
                KXmlInfo* Palettes = (*it);
                if (true == SAFE_PTR(Palettes))
                {
                    for (KXmlNodes::iterator Iit = Palettes->begin(); Iit != Palettes->end(); Iit++)
                    {
                        KXmlInfo* Name = (*Iit)->GetNode("Name", 0);
                        if (true == SAFE_PTR(Name) && PaletteSupported(Name->GetText()))
                        {
                            Resources->Add(Name->GetText());
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
HRESULT __fastcall PaletteParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
{
    HRESULT hResult = E_POINTER;
    String sType;
    String sName;

    if (ParserData != "[Begin]" && ParserData != "[End]")
    {
        GetResourceInfo(Resource, sType, sName);

        if (true == SAFE_PTR(XmlData) && SAFE_PTR(Code) && sType != "" && sName != "")
        {
            String sPalette;
            KXmlInfo* ResNode = GetResourceNode(XmlData, sType, sName);

            if (ParserData.Trim() == "")
            {
                if (frmPaletteParserOptions->radSourceCodeAsm->Checked)
                {
                    m_BytePrefix   = frmPaletteParserOptions->edtPrefix->Text;
                    m_LabelPrefix  = frmPaletteParserOptions->edtLabelPrefix->Text;
                    m_LabelPostfix = frmPaletteParserOptions->edtLabelPostfix->Text;
                    ParserData  = ":scAsm";                 // Assembler
                    ParserData += ":ap" + m_BytePrefix;     // Assembler Prefix
                    ParserData += ":lpr" + m_LabelPrefix + "rpl";
                    ParserData += ":lpo" + m_LabelPostfix + "opl:";
                    m_Compiler = asmGeneric;
                    m_UseLabel = true;
                    if (!frmPaletteParserOptions->chkSourceCodeUseLabel->Checked)
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
                if (frmPaletteParserOptions->radZXPaletteParserDecimal->Checked)
                {
                    m_NumberBase = nbDecimal;
                    ParserData += ":Dec";               // Base: Decimal
                }
                else if (frmPaletteParserOptions->radZXPaletteParserBinary->Checked)
                {
                    m_NumberBase = nbBinary;
                    ParserData += ":Bin";               // Base: Binary
                }
                else
                {
                    m_NumberBase = nbHexidecimal;
                    ParserData += ":Hex";               // Base: Hexidecimal
                }
            }
            else
            {
                // set it from the parser data string

                // Get Number Base
                m_NumberBase = nbHexidecimal;
                if (ParserData.Pos("Dec") > 0)
                    m_NumberBase = nbDecimal;
                else if (ParserData.Pos("Bin") > 0)
                    m_NumberBase = nbBinary;

                // Get Compiler
                m_Compiler = asmGeneric;
                if (ParserData.Pos("scC"))
                {
                    m_Compiler = cGeneric;
                }
                else if (ParserData.Pos("scAsm"))
                {
                    m_Compiler = asmGeneric;
                }

                // Get Assembler Prefix
                if (m_Compiler == asmGeneric && ParserData.Pos("ap") > 0)
                {
                    m_BytePrefix = "";
                    int pos = ParserData.Pos("ap");
                    for (int i = pos + 2; i <= ParserData.Length() && ParserData[i] != ':'; i++)
                    {
                        m_BytePrefix += ParserData[i];
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
            }

            // parse the xml data into code
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
void __fastcall PaletteParserPlugin::GetResourceInfo(const String& sResource, String& sType, String& sName)
{
    int iSlash = sResource.Pos('\\');
    if (iSlash)
    {
        sType = sResource.SubString(1, iSlash - 1);
        sName = sResource.SubString(iSlash + 1, sResource.Length());
    }
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall PaletteParserPlugin::GetResourceNode(KXmlInfo*& XmlData, const String& sType, const String& sName)
{
    if (true == SAFE_PTR(XmlData))
    {
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor", 0);
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' palettes and get all types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Palettes = (*it);
                if (true == SAFE_PTR(Palettes) && Palettes->GetName() == "Palettes")
                {
                    for (KXmlNodes::iterator Iit = Palettes->begin(); Iit != Palettes->end(); Iit++)
                    {
                        if ((*Iit)->GetName() == "Palette")
                        {
                            KXmlInfo* Name = (*Iit)->GetNode("Name", 0);
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
    return NULL;
}
//---------------------------------------------------------------------------
HRESULT __fastcall PaletteParserPlugin::ParseXmlNode(KXmlInfo*& ResNode, TStringList*& Code)
{
    HRESULT hResult = S_OK;

    try
    {
        // convert the Resource Node into a image array
        m_CL = "";
        m_CR = "";
        if (m_Compiler == cGeneric)
        {
            m_CL = "/* ";
            m_CR = " */";
        }
        else
        {
            m_CL = "; ";
        }

        // get the name of the palette and make a label
        String sName = ResNode->GetNode("Name", 0)->GetText().Trim();
        Code->Add(m_CL + "Palette : " + sName + m_CR);

        m_Name = StringReplace(sName, " ", "_", TReplaceFlags() << rfReplaceAll) + "_Palette";

        SAFE_DELETE(m_pPalette);
        KXmlInfo* Colors = ResNode->GetNode("Colors");
        if (SAFE_PTR(Colors))
        {
            m_pPalette = new int[Colors->size()];
            int i = 0;
            for (KXmlNodes::iterator It = Colors->begin(); It != Colors->end(); It++)
            {
                m_pPalette[i++] = (*It)->GetInt();
            }
            ParseIntoSourceCode(Colors->size(), Code);
        }
    }
    catch(...)
    {
        hResult = E_FAIL;
    }

    return hResult;
}
//---------------------------------------------------------------------------
// ParseIntoSourceCode
/**
 * Parses the image into Source Code
 * @param   iWidth  the width of the image
 * @param   iHeight the height of the image
 * @param   Code    the Source Code block to place the conversion
 * @author  Tony Thompson
 * @date    Created 11 February 2008 by Tony Thompson
 * @remarks Copyright KiwiWare 2008
 */
//---------------------------------------------------------------------------
void __fastcall PaletteParserPlugin::ParseIntoSourceCode(int iSize, TStringList*& Code)
{
    if (m_Compiler == cGeneric)
    {
        ParseIntoC(iSize, Code);
    }
    else
    {
        ParseIntoAsm(iSize, Code);
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
void __fastcall PaletteParserPlugin::ParseIntoC(int iSize, TStringList*& Code)
{
    Code->Add("unsigned char " + m_Name + "[" + IntToStr(iSize) + "] =");
    Code->Add("{");
    ParsePalette(iSize, Code);
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
void __fastcall PaletteParserPlugin::ParseIntoAsm(int iSize, TStringList*& Code)
{
    if (m_UseLabel)
    {
        Code->Add(m_LabelPrefix + m_Name + m_LabelPostfix);
    }

    ParsePalette(iSize, Code);
}
//---------------------------------------------------------------------------
void __fastcall PaletteParserPlugin::ParsePalette(int iSize, TStringList*& Code)
{
    Code->Add(m_CL + "palette data" + m_CR);
    String sLine = "";
    for (int i = 0; i < iSize; i++)
    {
        if (i)
        {
            sLine = sLine + ", ";
        }
        sLine = sLine + NumToStr(m_pPalette[i]);
    }
    if (m_Compiler == asmGeneric)
    {
        Code->Add(m_BytePrefix + " " + sLine);
    }
    else
    {
        Code->Add("\t" + sLine);
    }
}
//---------------------------------------------------------------------------
String __fastcall PaletteParserPlugin::NumToStr(unsigned char iNum)
{
    String sNum = "";
    String sPrefix = frmPaletteParserOptions->edtNumericalPrefix->Text.Trim();
    if (frmPaletteParserOptions->radZXPaletteParserDecimal->Checked)
    {
        sNum = "   " + IntToStr(iNum);
        sNum = sPrefix + sNum.SubString(sNum.Length() - 2, 3);
    }
    else if (frmPaletteParserOptions->radZXPaletteParserHexidecimal->Checked)
    {
        if (sPrefix == "")
        {
            sPrefix = "$";
        }
        sNum = "00" + IntToHex(iNum, 2);
        sNum = sPrefix + sNum.SubString(sNum.Length() - 1, 2);
    }
    else if (frmPaletteParserOptions->radZXPaletteParserBinary->Checked)
    {
        if (sPrefix == "")
        {
            sPrefix = "%";
        }
        sNum = sPrefix;
        unsigned char bitmask = 0x80;

        for (int i = 0; i < 8; i++)
        {
            sNum += iNum & bitmask ? "1" : "0";
            bitmask >>= 1;
        }
    }
    return sNum;
}
//---------------------------------------------------------------------------
#define SUPPORTED_PALETTES 1
String g_sSupportedPalettes[SUPPORTED_PALETTES] =
{
    "ZX Spectrum ULAplus"
};
//---------------------------------------------------------------------------
bool __fastcall PaletteParserPlugin::PaletteSupported(const String& sPalette)
{
    bool bSupported = false;
    for (int i = 0; i < SUPPORTED_PALETTES && false == bSupported; i++)
    {
        bSupported = g_sSupportedPalettes[i].LowerCase() == sPalette.LowerCase();
    }
    return bSupported;
}
//---------------------------------------------------------------------------

