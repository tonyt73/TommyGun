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
using namespace ImageTableParser;
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
ZXImageTableParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXImageTableParserPlugin();
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
__fastcall ZXImageTableParserPlugin::ZXImageTableParserPlugin()
: m_bAddFrameCount(false)
{
    RL_METHOD
    frmZXImageTableParserOptions = new TfrmZXImageTableParserOptions(NULL);
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
__fastcall ZXImageTableParserPlugin::~ZXImageTableParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmZXImageTableParserOptions);
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
HRESULT __fastcall ZXImageTableParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmZXImageTableParserOptions))
    {
        hResult = frmZXImageTableParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall ZXImageTableParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmZXImageTableParserOptions))
    {
        hResult = frmZXImageTableParserOptions->Release();
    }
    SAFE_DELETE(frmZXImageTableParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageTableParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageTableParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmZXImageTableParserOptions))
    {
        Panel = frmZXImageTableParserOptions->panZXImageTableParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageTableParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
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
HRESULT __fastcall ZXImageTableParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
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
        return Resources->Count ? S_OK : E_FAIL;
    }
    return E_POINTER;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageTableParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
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
                if (frmZXImageTableParserOptions->chkTableAddNumber->Checked)
                {
                    ParserData = "AddNumberOfImages";
                }
            }

            m_bAddFrameCount = ParserData.Pos("AddNumberOfImages") > 0;

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
        hResult = E_FAIL;
        if (ParserData == "[Begin]")
        {
            Code->Add(";");
            Code->Add("; " + Resource + " Table");
            Code->Add(";");
            Code->Add(Resource + "Table:");
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageTableParserPlugin::GetResourceInfo(const String& sResource, String& sType, String& sName)
{
    int iSlash = sResource.Pos('\\');
    if (iSlash)
    {
        sType = sResource.SubString(1, iSlash - 1);
        sName = sResource.SubString(iSlash + 1, sResource.Length());
    }
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall ZXImageTableParserPlugin::GetResourceNode(KXmlInfo*& XmlData, const String& sType, const String& sName)
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
HRESULT __fastcall ZXImageTableParserPlugin::ParseXmlNode(KXmlInfo*& ResNode, TStringList*& Code)
{
    HRESULT hResult = S_OK;

    try
    {
        // convert the Resource Node into a image array
        int iFrame = 0;
        bool bMultiFrame = ResNode->size() > 1;
        for (KXmlNodes::iterator FrameIt = ResNode->begin(); FrameIt != ResNode->end(); FrameIt++)
        {
            // get the name of the frame and make a label
            String sName = (*FrameIt)->GetNode("Name", 0)->GetText().Trim();
            if (iFrame == 0)
            {
                if (bMultiFrame)
                {
                    // if its multiframe, then use the image name as the label in the table
                    // else don't add an image label as it will conflict with the image data label name
                   Code->Add(sName + ":");
                }
                if (m_bAddFrameCount)
                {
                    // store the number of frames
                    Code->Add("defb " + IntToStr(ResNode->size()) + "           ; no of frames");
                }
            }
            if (bMultiFrame)
            {
                String sFrame = "000" + IntToStr(iFrame);
                Code->Add("defw " + sName + sFrame.SubString(sFrame.Length()-2, 3));
                iFrame++;
            }
            else
            {
                Code->Add("defw " + sName);
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
String __fastcall ZXImageTableParserPlugin::NumToStr(unsigned char iNum)
{
    String sNum = "   " + IntToStr(iNum);
    sNum = sNum.SubString(sNum.Length() - 2, 3);
    return sNum;
}
//---------------------------------------------------------------------------

