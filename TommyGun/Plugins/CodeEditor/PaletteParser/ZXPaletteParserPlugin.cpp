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
using namespace PaletteParser;
//- GLOBAL LOG FILE ---------------------------------------------------------
ZXLogFile g_LogFile;
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
ZXPaletteParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXPaletteParserPlugin();
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
__fastcall ZXPaletteParserPlugin::ZXPaletteParserPlugin()
: m_pPixels(NULL)
, m_pAttrs(NULL)
, m_pMasks(NULL)
, m_Mode(cmScanlines)
{
    RL_METHOD
    frmZXPaletteParserOptions = new TfrmZXPaletteParserOptions(NULL);
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
__fastcall ZXPaletteParserPlugin::~ZXPaletteParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_ARRAY_DELETE(m_pPixels);
    SAFE_ARRAY_DELETE(m_pAttrs);
    SAFE_ARRAY_DELETE(m_pMasks);
    SAFE_DELETE(frmZXPaletteParserOptions);
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
HRESULT __fastcall ZXPaletteParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmZXPaletteParserOptions))
    {
        hResult = frmZXPaletteParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall ZXPaletteParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmZXPaletteParserOptions))
    {
        hResult = frmZXPaletteParserOptions->Release();
    }
    SAFE_DELETE(frmZXPaletteParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXPaletteParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaletteParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmZXPaletteParserOptions))
    {
        Panel = frmZXPaletteParserOptions->panZXPaletteParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaletteParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Types))
    {
        Types->Clear();
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor");
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' images and get all types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Node = (*it);
                if (true == SAFE_PTR(Node) && Node->GetName() == "Images")
                {
                    KXmlInfo* Type = Node->GetNode("Type");
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
HRESULT __fastcall ZXPaletteParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
{
    if (true == SAFE_PTR(XmlData) && true == SAFE_PTR(Resources))
    {
        Resources->Clear();
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor");
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' images and get all types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Images = (*it);
                if (true == SAFE_PTR(Images) && Images->GetName() == "Images")
                {
                    KXmlInfo* Type = Images->GetNode("Type");
                    if (true == SAFE_PTR(Type) && Type->GetText() == sType)
                    {
                        for (KXmlNodes::iterator Iit = Images->begin(); Iit != Images->end(); Iit++)
                        {
                            if ((*Iit)->GetName() == "Image")
                            {
                                KXmlInfo* Frame = (*Iit)->GetNode("Frame");
                                if (true == SAFE_PTR(Frame))
                                {
                                    KXmlInfo* Name = Frame->GetNode("Name");
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
        return Resources->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaletteParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
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
                if (frmZXPaletteParserOptions->radZXPaletteParserPixelsRowColumn->Checked)
                {
                    ParserData = "ScanlinesRowColumn";
                    m_Mode = cmScanlines;
                }
                else
                {
                    if (frmZXPaletteParserOptions->radZXPaletteParserAttributesEnd->Checked)
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

                m_PlaceSize = false;
                if (frmZXPaletteParserOptions->chkPlaceSize->Checked)
                {
                    ParserData += ":PlaceSize";
                    m_PlaceSize = true;
                }

                m_ConvertX = false;
                if (frmZXPaletteParserOptions->chkConvertX->Checked)
                {
                    ParserData += ":XChar";
                    m_ConvertX = true;
                }

                m_ConvertY = false;
                if (frmZXPaletteParserOptions->chkConvertY->Checked)
                {
                    ParserData += ":YChar";
                    m_ConvertY = true;
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
                m_PlaceSize = ParserData.Pos("PlaceSize") > 0;
                m_ConvertX  = ParserData.Pos("XChar") > 0;
                m_ConvertY  = ParserData.Pos("YChar") > 0;
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
void __fastcall ZXPaletteParserPlugin::GetResourceInfo(const String& sResource, String& sType, String& sName)
{
    int iSlash = sResource.Pos('\\');
    if (iSlash)
    {
        sType = sResource.SubString(1, iSlash - 1);
        sName = sResource.SubString(iSlash + 1, sResource.Length());
    }
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall ZXPaletteParserPlugin::GetResourceNode(KXmlInfo*& XmlData, const String& sType, const String& sName)
{
    if (true == SAFE_PTR(XmlData))
    {
        KXmlInfo* ImageEditor = XmlData->GetNode("ImageEditor");
        if (true == SAFE_PTR(ImageEditor))
        {
            // loop thru' images and get all types
            for (KXmlNodes::iterator it = ImageEditor->begin(); it != ImageEditor->end(); it++)
            {
                KXmlInfo* Images = (*it);
                if (true == SAFE_PTR(Images) && Images->GetName() == "Images")
                {
                    KXmlInfo* Type = Images->GetNode("Type");
                    if (true == SAFE_PTR(Type) && Type->GetText() == sType)
                    {
                        for (KXmlNodes::iterator Iit = Images->begin(); Iit != Images->end(); Iit++)
                        {
                            if ((*Iit)->GetName() == "Image")
                            {
                                KXmlInfo* Frame = (*Iit)->GetNode("Frame");
                                if (true == SAFE_PTR(Frame))
                                {
                                    KXmlInfo* Name = Frame->GetNode("Name");
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
HRESULT __fastcall ZXPaletteParserPlugin::ParseXmlNode(KXmlInfo*& ResNode, TStringList*& Code)
{
    HRESULT hResult = S_OK;

    try
    {
        // convert the Resource Node into a image array
        int iFrame = 0;
        bool bMultiFramed = ResNode->size() > 1;
        for (KXmlNodes::iterator FrameIt = ResNode->begin(); FrameIt != ResNode->end(); FrameIt++)
        {
            bool bMasked = (*FrameIt)->GetNode("IsMasked")->GetInt();
            // get the name of the frame and make a label
            String sName = (*FrameIt)->GetNode("Name")->GetText().Trim();

            // get the frames properties
            int iWidth = (*FrameIt)->GetNode("Width")->GetInt();
            int iHeight = (*FrameIt)->GetNode("Height")->GetInt();
            String sPalette = (*FrameIt)->GetNode("Palette")->GetText();
            String sPixels = (*FrameIt)->GetNode("Pixels")->GetText();
            String sAttrs;
            String sMasks;
            if (sPalette != "Monochrome")
            {
                sAttrs = (*FrameIt)->GetNode("Attributes")->GetText();
            }
            if (bMasked)
            {
                sMasks = (*FrameIt)->GetNode("Masks")->GetText();
            }

            Code->Add("; Name   : " + sName);
            if (bMultiFramed)
            {
                Code->Add("; Frame  : " + IntToStr(iFrame));
            }
            Code->Add("; Size   : " + IntToStr(iWidth) + "x" + IntToStr(iHeight));
            Code->Add("; Palette: " + sPalette);
            Code->Add("; Masked : " + (bMasked ? String("Yes") : String("No")));

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
            bool bMasksOK  = sMasks.Length() ? (((iWidth / 8) *  iHeight      * 2) == sMasks.Length()) : true;

            if (bPixelsOK && bAttrsOK && bMasksOK)
            {
                if (m_PlaceSize)
                {
                    int w = iWidth;
                    int h = iHeight;
                    if (m_ConvertX)
                    {
                        w /= 8;
                    }
                    if (m_ConvertY)
                    {
                        h /= 8;
                    }
                    Code->Add("defb " + IntToStr(w) + ", " + IntToStr(h) + "             ; size: WxH");
                }
                GetFrameData(sPixels, sAttrs, sMasks, sPalette);
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
void __fastcall ZXPaletteParserPlugin::GetFrameData(const String& sPixels, const String& sAttrs, const String& sMasks, const String& sPalette)
{
    if (sPixels.Trim() != "")
    {
        ConvertStringToData(m_pPixels, sPixels, true);
    }
    if (sAttrs.Trim() != "")
    {
        ConvertStringToData(m_pAttrs, sAttrs, false);
    }
    if (sMasks.Trim() != "")
    {
        ConvertStringToData(m_pMasks, sMasks, true);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXPaletteParserPlugin::ConvertStringToData(unsigned char*& pData, const String& sData, bool bChangeEndianess)
{
    // delete the old data
    SAFE_ARRAY_DELETE(pData);
    // now allocate some new data
    int iSize = sData.Length() / 2;
    pData = new unsigned char[iSize];
    // now convert the ascii-hex
    for (int i = 0; i < iSize; i++)
    {
        if (bChangeEndianess)
        {
            unsigned char leData = ((sData[i * 2 + 1] - 'A') << 4) | (sData[i * 2 + 2] - 'A');
            unsigned char beData = 0;
            // data needs to be in big endian
            unsigned char leBit = 0x01; // little endian bit
            unsigned char beBit = 0x80; // big endian bit
            for (int i = 0; i < 8; i++)
            {
                if (leData & leBit)
                {
                    beData |= beBit;
                }
                leBit <<= 1;
                beBit >>= 1;
            }
            pData[i] = beData;
        }
        else
        {
            pData[i] = ((sData[i * 2 + 1] - 'A') << 4) | (sData[i * 2 + 2] - 'A');
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXPaletteParserPlugin::ParseScanlines(int iWidth, int iHeight, TStringList*& Code)
{
    iWidth >>= 3;
    int i = 0;
    Code->Add("; pixels");
    for (int h = 0; h < iHeight; h++)
    {
        String sLine = "";
        for (int w = 0; w < iWidth; w++)
        {
            if (w)
            {
                sLine = sLine + ", ";
            }
            sLine = sLine + NumToStr(m_pPixels[i++]);
        }
        Code->Add("defb " + sLine);
    }
    if (true == SAFE_PTR(m_pAttrs))
    {
        Code->Add("; attrs");
        iHeight >>= 3;
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
void __fastcall ZXPaletteParserPlugin::ParseCharBlockAttrEnd(int iWidth, int iHeight, TStringList*& Code)
{
    iWidth >>= 3;
    iHeight >>= 3;

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
            }
            Code->Add("defb " + sLine + "  ; char block [" + IntToStr(w) + ", " + IntToStr(h) + "]");
        }
    }
    if (true == SAFE_PTR(m_pAttrs))
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
void __fastcall ZXPaletteParserPlugin::ParseCharBlockAttrInterleaved(int iWidth, int iHeight, TStringList*& Code)
{
    iWidth >>= 3;
    iHeight >>= 3;

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
            }
            if (true == SAFE_PTR(m_pAttrs))
            {
                sLine = sLine + ", " + NumToStr(m_pAttrs[h * iWidth + h]);
            }
            Code->Add("defb " + sLine + "  ; char block [" + IntToStr(w) + ", " + IntToStr(h) + "] + attr");
        }
    }
}
//---------------------------------------------------------------------------
String __fastcall ZXPaletteParserPlugin::NumToStr(unsigned char iNum)
{
    String sNum = "   " + IntToStr(iNum);
    sNum = sNum.SubString(sNum.Length() - 2, 3);
    return sNum;
}
//---------------------------------------------------------------------------

