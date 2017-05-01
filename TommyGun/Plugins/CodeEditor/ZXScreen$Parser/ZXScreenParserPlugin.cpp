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
using namespace ScreenParser;
//---------------------------------------------------------------------------
unsigned int ScreenOffsets[192] =
{
     0 * 32 + 256 * 0,
     0 * 32 + 256 * 1,
     0 * 32 + 256 * 2,
     0 * 32 + 256 * 3,
     0 * 32 + 256 * 4,
     0 * 32 + 256 * 5,
     0 * 32 + 256 * 6,
     0 * 32 + 256 * 7,

     1 * 32 + 256 * 0,
     1 * 32 + 256 * 1,
     1 * 32 + 256 * 2,
     1 * 32 + 256 * 3,
     1 * 32 + 256 * 4,
     1 * 32 + 256 * 5,
     1 * 32 + 256 * 6,
     1 * 32 + 256 * 7,

     2 * 32 + 256 * 0,
     2 * 32 + 256 * 1,
     2 * 32 + 256 * 2,
     2 * 32 + 256 * 3,
     2 * 32 + 256 * 4,
     2 * 32 + 256 * 5,
     2 * 32 + 256 * 6,
     2 * 32 + 256 * 7,

     3 * 32 + 256 * 0,
     3 * 32 + 256 * 1,
     3 * 32 + 256 * 2,
     3 * 32 + 256 * 3,
     3 * 32 + 256 * 4,
     3 * 32 + 256 * 5,
     3 * 32 + 256 * 6,
     3 * 32 + 256 * 7,

     4 * 32 + 256 * 0,
     4 * 32 + 256 * 1,
     4 * 32 + 256 * 2,
     4 * 32 + 256 * 3,
     4 * 32 + 256 * 4,
     4 * 32 + 256 * 5,
     4 * 32 + 256 * 6,
     4 * 32 + 256 * 7,

     5 * 32 + 256 * 0,
     5 * 32 + 256 * 1,
     5 * 32 + 256 * 2,
     5 * 32 + 256 * 3,
     5 * 32 + 256 * 4,
     5 * 32 + 256 * 5,
     5 * 32 + 256 * 6,
     5 * 32 + 256 * 7,

     6 * 32 + 256 * 0,
     6 * 32 + 256 * 1,
     6 * 32 + 256 * 2,
     6 * 32 + 256 * 3,
     6 * 32 + 256 * 4,
     6 * 32 + 256 * 5,
     6 * 32 + 256 * 6,
     6 * 32 + 256 * 7,

     7 * 32 + 256 * 0,
     7 * 32 + 256 * 1,
     7 * 32 + 256 * 2,
     7 * 32 + 256 * 3,
     7 * 32 + 256 * 4,
     7 * 32 + 256 * 5,
     7 * 32 + 256 * 6,
     7 * 32 + 256 * 7,
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
ZXScreenParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXScreenParserPlugin();
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
__fastcall ZXScreenParserPlugin::ZXScreenParserPlugin()
: m_pPixels(NULL)
, m_pAttrs(NULL)
{
    RL_METHOD
    frmZXScreenParserOptions = new TfrmZXScreenParserOptions(NULL);
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
__fastcall ZXScreenParserPlugin::~ZXScreenParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_ARRAY_DELETE(m_pPixels);
    SAFE_ARRAY_DELETE(m_pAttrs);
    SAFE_DELETE(frmZXScreenParserOptions);
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
HRESULT __fastcall ZXScreenParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmZXScreenParserOptions))
    {
        hResult = frmZXScreenParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall ZXScreenParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmZXScreenParserOptions))
    {
        hResult = frmZXScreenParserOptions->Release();
    }
    SAFE_DELETE(frmZXScreenParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXScreenParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXScreenParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmZXScreenParserOptions))
    {
        Panel = frmZXScreenParserOptions->panZXScreenParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXScreenParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
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
                    if (true == SAFE_PTR(Type) && Type->GetText() == "Screen")
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
HRESULT __fastcall ZXScreenParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
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
                    if (true == SAFE_PTR(Type) && Type->GetText() == "Screen")
                    {
                        for (KXmlNodes::iterator Iit = Images->begin(); Iit != Images->end(); Iit++)
                        {
                            if ((*Iit)->GetName() == "Image")
                            {
                                KXmlInfo* Frame = (*Iit)->GetNode("Frame", 0);
                                if (true == SAFE_PTR(Frame))
                                {
                                    KXmlInfo* Palette = Frame->GetNode("Palette", 0);
                                    if (true == SAFE_PTR(Palette) && Palette->GetText().LowerCase() == "zx spectrum")
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
HRESULT __fastcall ZXScreenParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
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
                if (frmZXScreenParserOptions->radZXScreenParserOrgDefault->Checked)
                {
                    m_Mode = omDefault;
                    ParserData = "OrgDefault";
                }
                else if (frmZXScreenParserOptions->radZXScreenParserOrgNone->Checked)
                {
                    m_Mode = omNone;
                    ParserData = "OrgNone";
                }
                else if (frmZXScreenParserOptions->radZXScreenParserOrgUser->Checked)
                {
                    ParserData = "OrgUser:" + frmZXScreenParserOptions->edtZXScreenParserOrgValue->Text;
                    m_Mode = omCustom;
                    m_UserOrg = frmZXScreenParserOptions->edtZXScreenParserOrgValue->Text;
                }
                m_IncludeAttrs = frmZXScreenParserOptions->radZXScreenParserInclude->Checked;
                if (frmZXScreenParserOptions->radZXScreenParserInclude->Checked)
                {
                    ParserData += ":IncludeAttributes";
                }
                else
                {
                    ParserData += ":ExcludeAttributes";
                }
            }
            else
            {
                // set it from the parser data string

                // default to scanlines output
                if (ParserData.Pos("OrgDefault") > 0)
                {
                    m_Mode = omDefault;
                }
                else if (ParserData.Pos("OrgNone"))
                {
                    m_Mode = omNone;
                }
                else if (ParserData.Pos("OrgCustom"))
                {
                    int pos = ParserData.Pos("OrgCustom");
                    m_Mode = omCustom;
                    m_UserOrg = ParserData.SubString(pos + 9, 255); 
                }
                m_IncludeAttrs = ParserData.Pos("IncludeAttributes") > 0;
            }

            // parse the xml data into code
            KXmlInfo* ResNode = GetResourceNode(XmlData, sName);
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
void __fastcall ZXScreenParserPlugin::GetResourceInfo(const String& sResource, String& sType, String& sName)
{
    int iSlash = sResource.Pos('\\');
    if (iSlash)
    {
        sType = sResource.SubString(1, iSlash - 1);
        sName = sResource.SubString(iSlash + 1, sResource.Length());
    }
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall ZXScreenParserPlugin::GetResourceNode(KXmlInfo*& XmlData, const String& sName)
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
                    if (true == SAFE_PTR(Type) && Type->GetText() == "Screen")
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
HRESULT __fastcall ZXScreenParserPlugin::ParseXmlNode(KXmlInfo*& ResNode, TStringList*& Code)
{
    HRESULT hResult = S_OK;

    try
    {
        // convert the Resource Node into a image array
        int iFrame = 0;
        //bool bMultiFramed = ResNode->size() > 1;
        KXmlNodes::iterator FrameIt = ResNode->begin();
        //for (KXmlNodes::iterator FrameIt = ResNode->begin(); FrameIt != ResNode->end(); FrameIt++)
        {
            // get the name of the frame and make a label
            String sName = (*FrameIt)->GetNode("Name", 0)->GetText().Trim();

            // get the frames properties
            int iWidth = (*FrameIt)->GetNode("Width", 0)->GetInt();
            int iHeight = (*FrameIt)->GetNode("Height", 0)->GetInt();
            String sPixels = (*FrameIt)->GetNode("Pixels", 0)->GetText();
            String sAttrs;
            sAttrs = (*FrameIt)->GetNode("Attributes", 0)->GetText();

            Code->Add("; Name   : " + sName);

            if (iWidth == 256 && iHeight == 192)
            {
                GetFrameData(sPixels, sAttrs);
                ParseScanlines(iWidth, iHeight, Code);
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
void __fastcall ZXScreenParserPlugin::GetFrameData(const String& sPixels, const String& sAttrs)
{
    if (sPixels.Trim() != "")
    {
        ConvertStringToData(m_pPixels, sPixels);
    }
    if (sAttrs.Trim() != "" && m_IncludeAttrs)
    {
        ConvertStringToData(m_pAttrs, sAttrs);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXScreenParserPlugin::ConvertStringToData(unsigned char*& pData, const String& sData, bool bInvertByte)
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
void __fastcall ZXScreenParserPlugin::ParseScanlines(int iWidth, int iHeight, TStringList*& Code)
{
    if (m_Mode == omDefault)
    {
        Code->Add("org 0x4000       ; default screen address");
    }
    else if (m_Mode == omCustom)
    {
        Code->Add("org " + m_UserOrg + "     ; user defined screen location");
    }

    iWidth >>= 3;
    int i = 0;
    Code->Add("; pixels");

    for (int h = 0; h < iHeight; h++)
    {
        int iOffset = (2048*(h/64))+(((h%64) / 8) * 32) + ((h % 8) * 256);
        String sLine = "";
        for (int w = 0; w < iWidth; w++)
        {
            if (w)
            {
                sLine = sLine + ", ";
            }
            sLine = sLine + NumToStr(m_pPixels[iOffset + w]);
        }
        Code->Add("defb " + sLine);
    }
    if (true == SAFE_PTR(m_pAttrs) && m_IncludeAttrs)
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
String __fastcall ZXScreenParserPlugin::NumToStr(unsigned char iNum)
{
    String sNum = "   " + IntToStr(iNum);
    sNum = sNum.SubString(sNum.Length() - 2, 3);
    return sNum;
}
//---------------------------------------------------------------------------

