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
#define SUPPORTED_PALETTES 6
String g_sSupportedPalettes[SUPPORTED_PALETTES] =
{
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
ZXImageParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXImageParserPlugin();
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
__fastcall ZXImageParserPlugin::ZXImageParserPlugin()
: m_pPixels(NULL)
, m_pAttrs(NULL)
, m_pMasks(NULL)
, m_Mode(cmScanlines)
, m_UseAttributes(true)
{
    RL_METHOD
    frmZXImageParserOptions = new TfrmZXImageParserOptions(NULL);
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
__fastcall ZXImageParserPlugin::~ZXImageParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_ARRAY_DELETE(m_pPixels);
    SAFE_ARRAY_DELETE(m_pAttrs);
    SAFE_ARRAY_DELETE(m_pMasks);
    SAFE_DELETE(frmZXImageParserOptions);
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
HRESULT __fastcall ZXImageParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmZXImageParserOptions))
    {
        hResult = frmZXImageParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall ZXImageParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmZXImageParserOptions))
    {
        hResult = frmZXImageParserOptions->Release();
    }
    SAFE_DELETE(frmZXImageParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmZXImageParserOptions))
    {
        Panel = frmZXImageParserOptions->panZXImageParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
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
HRESULT __fastcall ZXImageParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
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
HRESULT __fastcall ZXImageParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
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
                // set the parser data parameter from the GUI
                if (frmZXImageParserOptions->radZXImageParserPixelsRowColumn->Checked)
                {
                    ParserData = "ScanlinesRowColumn";
                    m_Mode = cmScanlines;
                }
                else
                {
                    if (frmZXImageParserOptions->chkUseAttributes->Checked)
                    {
                        if (frmZXImageParserOptions->radZXImageParserAttributesEnd->Checked)
                        {
                            ParserData = "CharBlocks:AttrsAtEnd";
                            m_Mode = cmCharBlockAttrEnd;
                        }
                        else
                        {
                            ParserData = "CharBlocks:AttrsInterleaved";
                            m_Mode = cmCharBlockAttrInterleaved;
                        }
                    }
                }

                m_PlaceSize = false;
                if (frmZXImageParserOptions->chkPlaceSize->Checked)
                {
                    ParserData += ":PlaceSize";
                    m_PlaceSize = true;
                }

                m_ConvertX = false;
                if (frmZXImageParserOptions->chkConvertX->Checked)
                {
                    ParserData += ":XChar";
                    m_ConvertX = true;
                }

                m_ConvertY = false;
                if (frmZXImageParserOptions->chkConvertY->Checked)
                {
                    ParserData += ":YChar";
                    m_ConvertY = true;
                }

                m_MaskAfter = false;
                m_MaskBeforePixels = false;
                if (frmZXImageParserOptions->radZXImageParserAfterPixels->Checked)
                {
                    ParserData += ":MaskAfter";
                    m_MaskAfter = true;
                }
                else
                {
                    ParserData += ":MaskBeforePixels";
                    m_MaskBeforePixels = frmZXImageParserOptions->radZXImageParserMaskBefore->Checked;
                }

                m_MaskInvert = false;
                if (frmZXImageParserOptions->radZXImageParserMaskCovers->Checked)
                {
                    ParserData += ":MaskInvert";
                    m_MaskInvert = true;
                }
                m_ZigZagged = false;
                if (frmZXImageParserOptions->radZXImageParserRowOrderZigZag->Checked)
                {
                    m_ZigZagged = true;
                    ParserData += ":ZigZagged";
                }
                m_UseAttributes = false;
                if (frmZXImageParserOptions->chkUseAttributes->Checked)
                {
                    m_UseAttributes = true;
                    ParserData += ":UseAttributes";
                }
            }
            else
            {
                // set it from the parser data string

                // default to scanlines output
                m_Mode = cmScanlines;
                if (ParserData.Pos("CharBlocks:AttrsAtEnd") > 0)
                {
                    m_Mode = cmCharBlockAttrEnd;
                }
                else if (ParserData.Pos("CharBlocks:AttrsInterleaved"))
                {
                    m_Mode = cmCharBlockAttrInterleaved;
                }
                m_PlaceSize         = ParserData.Pos("PlaceSize"        ) > 0;
                m_ConvertX          = ParserData.Pos("XChar"            ) > 0;
                m_ConvertY          = ParserData.Pos("YChar"            ) > 0;
                m_MaskAfter         = ParserData.Pos("MaskAfter"        ) > 0;
                m_MaskInvert        = ParserData.Pos("MaskInvert"       ) > 0;
                m_MaskBeforePixels  = ParserData.Pos("MaskBeforePixels" ) > 0;
                m_ZigZagged         = ParserData.Pos("ZigZagged"        ) > 0;
                m_UseAttributes     = ParserData.Pos("UseAttributes"    ) > 0;
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
void __fastcall ZXImageParserPlugin::GetResourceInfo(const String& sResource, String& sType, String& sName)
{
    int iSlash = sResource.Pos('\\');
    if (iSlash)
    {
        sType = sResource.SubString(1, iSlash - 1);
        sName = sResource.SubString(iSlash + 1, sResource.Length());
    }
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall ZXImageParserPlugin::GetResourceNode(KXmlInfo*& XmlData, const String& sType, const String& sName)
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
HRESULT __fastcall ZXImageParserPlugin::ParseXmlNode(KXmlInfo*& ResNode, TStringList*& Code)
{
    HRESULT hResult = S_OK;

    try
    {
        // convert the Resource Node into a image array
        int iFrame = 0;
        bool bMultiFramed = ResNode->size() > 1;
        for (KXmlNodes::iterator FrameIt = ResNode->begin(); FrameIt != ResNode->end(); FrameIt++)
        {
            bool bMasked = (*FrameIt)->GetNode("IsMasked", 0)->GetText().LowerCase() == "true";
            //bool bMaskInvert = (*FrameIt)->GetNode("MaskInvert", 0)->GetText().LowerCase() == "true";
            // get the name of the frame and make a label
            String sName = (*FrameIt)->GetNode("Name", 0)->GetText().Trim();

            // get the frames properties
            int iWidth = (*FrameIt)->GetNode("Width", 0)->GetInt();
            int iHeight = (*FrameIt)->GetNode("Height", 0)->GetInt();
            String sPalette = (*FrameIt)->GetNode("Palette", 0)->GetText();
            String sPixels = (*FrameIt)->GetNode("Pixels", 0)->GetText();
            String sAttrs;
            String sMasks;
            if (sPalette != "Monochrome")
            {
                sAttrs = (*FrameIt)->GetNode("Attributes", 0)->GetText();
            }
            if (bMasked)
            {
                sMasks = (*FrameIt)->GetNode("Masks", 0)->GetText();
            }

            Code->Add("; Name   : " + sName);
            if (bMultiFramed)
            {
                Code->Add("; Frame  : " + IntToStr(iFrame));
            }
            Code->Add("; Size   : " + IntToStr(iWidth) + "x" + IntToStr(iHeight));
            Code->Add("; Palette: " + sPalette);
            Code->Add("; Masked : " + (bMasked ? String("Yes") : String("No")));
            Code->Add("; RowOrder: " + (m_ZigZagged ? String("ZigZag") : String("Classic")));

            if (bMultiFramed)
            {
                String sFrame = "000" + IntToStr(iFrame);
                Code->Add(sName + sFrame.SubString(sFrame.Length()-2, 3) + ":");
                iFrame++;
            }
            else
            {
                Code->Add(sName + ":");
            }

            bool bPixelsOK =                    ((iWidth / 8) *  iHeight      * 2) == sPixels.Length();
            bool bAttrsOK  = sAttrs.Length() ? (((iWidth / 8) * (iHeight / 8) * 2) == sAttrs.Length()) : true;
                 bAttrsOK |= sAttrs.Length() ? (((iWidth / 8) * (iHeight    ) * 2) == sAttrs.Length()) : true;
            bool bMasksOK  = sMasks.Length() ? (((iWidth / 8) *  iHeight      * 2) == sMasks.Length()) : true;
                 m_AttributeBlocks = (((iWidth / 8) * (iHeight / 8) * 2) == sAttrs.Length());

            if (bPixelsOK && bAttrsOK && bMasksOK)
            {
                if (m_PlaceSize)
                {
                    int w = iWidth;
                    int h = iHeight;
                    String sX("(pixels x ");
                    String sY("pixels)");
                    if (m_ConvertX)
                    {
                        w /= 8;
                        sX = "(chars x ";
                    }
                    if (m_ConvertY)
                    {
                        h /= 8;
                        sY = "chars)";
                    }
                    Code->Add("defb " + IntToStr(w) + ", " + IntToStr(h) + "             ; size: WxH - " + sX + sY);
                }
                GetFrameData(sPixels, sAttrs, sMasks, sPalette, iWidth / 8);
                if (cmScanlines == m_Mode)
                {
                    ParseScanlines(iWidth, iHeight, Code);
                }
                else if (cmCharBlockAttrEnd == m_Mode)
                {
                    ParseCharBlockAttrEnd(iWidth, iHeight, Code);
                }
                else
                {
                    ParseCharBlockAttrInterleaved(iWidth, iHeight, Code);
                }
            }
        }
    }
    catch(...)
    {
        hResult = E_FAIL;
    }

    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageParserPlugin::GetFrameData(const String& sPixels, const String& sAttrs, const String& sMasks, const String& sPalette, int iWidth)
{
    if (sPixels.Trim() != "")
    {
        ConvertStringToData(m_pPixels, sPixels, iWidth);
    }
    if (sMasks.Trim() != "")
    {
        ConvertStringToData(m_pMasks, sMasks, iWidth, m_MaskInvert);
    }
    if (sAttrs.Trim() != "")
    {
        bool zigzag = m_ZigZagged;
        m_ZigZagged = false;
        ConvertStringToData(m_pAttrs, sAttrs, iWidth);
        m_ZigZagged = zigzag;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageParserPlugin::ConvertStringToData(unsigned char*& pData, const String& sData, int iWidth, bool bInvertByte)
{
    // delete the old data
    SAFE_ARRAY_DELETE(pData);
    // now allocate some new data
    int iSize = sData.Length() / 2;
    pData = new unsigned char[iSize];
    // now convert the ascii-hex
    for (int i = 0; i < iSize; i++)
    {
        if (!m_ZigZagged || ((i / iWidth) % 2) == 0)
        {
            pData[i] = ((sData[i * 2 + 1] - 'A') << 4) | (sData[i * 2 + 2] - 'A');
        }
        else
        {
            int j = (i - (i % iWidth) + (iWidth - 1)) - (i % iWidth);
            pData[i] = ((sData[j * 2 + 1] - 'A') << 4) | (sData[j * 2 + 2] - 'A');
        }

        if (bInvertByte)
        {
            pData[i] = pData[i] ^ 255;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageParserPlugin::ParseScanlines(int iWidth, int iHeight, TStringList*& Code)
{
    iWidth >>= 3;
    int i = 0;
    if (true == SAFE_PTR(m_pMasks) && m_MaskAfter)
    {
        Code->Add("; pixels");
    }
    else
    {
        Code->Add("; pixels and mask bit pairs");
    }
    for (int h = 0; h < iHeight; h++)
    {
        String sLine = "";
        for (int w = 0; w < iWidth; w++)
        {
            if (w)
            {
                sLine = sLine + ", ";
            }
            if (!m_MaskBeforePixels)
            {
                sLine = sLine + NumToStr(m_pPixels[i]);
                if (true == SAFE_PTR(m_pMasks) && !m_MaskAfter)
                {
                    sLine = sLine + ", ";
                    sLine = sLine + NumToStr(m_pMasks[i]);
                }
                ++i;
            }
            else
            {
                if (true == SAFE_PTR(m_pMasks) && !m_MaskAfter)
                {
                    sLine = sLine + NumToStr(m_pMasks[i]);
                    sLine = sLine + ", ";
                }
                sLine = sLine + NumToStr(m_pPixels[i]);
                ++i;
            }
        }
        Code->Add("defb " + sLine);
    }
    if (true == SAFE_PTR(m_pMasks) && m_MaskAfter)
    {
        Code->Add("; mask bits");
        int i = 0;
        for (int h = 0; h < iHeight; h++)
        {
            String sLine = "";
            for (int w = 0; w < iWidth; w++)
            {
                if (w)
                {
                    sLine = sLine + ", ";
                }
                sLine = sLine + NumToStr(m_pMasks[i++]);
            }
            Code->Add("defb " + sLine);
        }
    }
    if (true == SAFE_PTR(m_pAttrs) && m_UseAttributes)
    {
        Code->Add("; attrs");
        if (m_AttributeBlocks) iHeight >>= 3;
        int i = 0;
        for (int h = 0; h < iHeight; h++)
        {
            String sLine = "";
            for (int w = 0; w < iWidth; w++)
            {
                if (w)
                {
                    sLine = sLine + ", ";
                }
                sLine = sLine + NumToStr(m_pAttrs[i++]);
            }
            Code->Add("defb " + sLine);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageParserPlugin::ParseCharBlockAttrEnd(int iWidth, int iHeight, TStringList*& Code)
{
    iWidth >>= 3;
    if (m_AttributeBlocks) iHeight >>= 3;

    for (int h = 0; h < iHeight; h++)
    {
        for (int w = 0; w < iWidth; w++)
        {
            String sLine = "";
            for (int i = 0; i < 8; i++)
            {
                if (i)
                {
                    sLine = sLine + ", ";
                }
                sLine = sLine + NumToStr(m_pPixels[(h * iWidth * 8) + (i * iWidth) + w]);
                if (true == SAFE_PTR(m_pMasks) && !m_MaskAfter)
                {
                    sLine = sLine + ", ";
                    sLine = sLine + NumToStr(m_pMasks[(h * iWidth * 8) + (i * iWidth) + w]);
                }
            }
            Code->Add("defb " + sLine + "  ; char block [" + IntToStr(w) + ", " + IntToStr(h) + "]");
        }
    }
    if (true == SAFE_PTR(m_pMasks) && m_MaskAfter)
    {
        for (int h = 0; h < iHeight; h++)
        {
            for (int w = 0; w < iWidth; w++)
            {
                String sLine = "";
                for (int i = 0; i < 8; i++)
                {
                    if (i)
                    {
                        sLine = sLine + ", ";
                    }
                    sLine = sLine + NumToStr(m_pMasks[(h * iWidth * 8) + (i * iWidth) + w]);
                }
                Code->Add("defb " + sLine + "  ; char block [" + IntToStr(w) + ", " + IntToStr(h) + "]");
            }
        }
    }
    if (true == SAFE_PTR(m_pAttrs) && m_UseAttributes)
    {
        Code->Add("; attrs");
        int i = 0;
        for (int h = 0; h < iHeight; h++)
        {
            String sLine = "";
            for (int w = 0; w < iWidth; w++)
            {
                if (w)
                {
                    sLine = sLine + ", ";
                }
                sLine = sLine + NumToStr(m_pAttrs[i++]);
            }
            Code->Add("defb " + sLine);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageParserPlugin::ParseCharBlockAttrInterleaved(int iWidth, int iHeight, TStringList*& Code)
{
    iWidth >>= 3;
    if (m_AttributeBlocks) iHeight >>= 3;

    for (int h = 0; h < iHeight; h++)
    {
        for (int w = 0; w < iWidth; w++)
        {
            String sLine = "";
            for (int i = 0; i < 8; i++)
            {
                if (i)
                {
                    sLine = sLine + ", ";
                }
                sLine = sLine + NumToStr(m_pPixels[(h * iWidth * 8) + (i * iWidth) + w]);
                if (true == SAFE_PTR(m_pMasks) && !m_MaskAfter)
                {
                    sLine = sLine + ", " + NumToStr(m_pMasks[(h * iWidth * 8) + (i * iWidth) + w]);
                }
            }
            if (true == SAFE_PTR(m_pMasks) && m_MaskAfter)
            {
                for (int i = 0; i < 8; i++)
                {
                    if (i)
                    {
                        sLine = sLine + ", ";
                    }
                    sLine = sLine + NumToStr(m_pMasks[(h * iWidth * 8) + (i * iWidth) + w]);
                }
            }
            if (true == SAFE_PTR(m_pAttrs) && m_UseAttributes)
            {
                sLine = sLine + ", " + NumToStr(m_pAttrs[h * iWidth + h]);
            }
            Code->Add("defb " + sLine + "  ; char block [" + IntToStr(w) + ", " + IntToStr(h) + "] + attr");
        }
    }
}
//---------------------------------------------------------------------------
String __fastcall ZXImageParserPlugin::NumToStr(unsigned char iNum)
{
    String sNum = "   " + IntToStr(iNum);
    sNum = sNum.SubString(sNum.Length() - 2, 3);
    return sNum;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageParserPlugin::PaletteSupported(const String& sPalette)
{
    bool bSupported = false;
    for (int i = 0; i < SUPPORTED_PALETTES && false == bSupported; i++)
    {
        bSupported = g_sSupportedPalettes[i].LowerCase() == sPalette.LowerCase();
    }
    return bSupported;
}
//---------------------------------------------------------------------------

