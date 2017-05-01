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
PaletteImageParserPlugin* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new PaletteImageParserPlugin();
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
__fastcall PaletteImageParserPlugin::PaletteImageParserPlugin()
: m_pPixels(NULL)
, m_pMasks(NULL)
, m_bMasked(false)
, m_MaskInvert(true)
, m_PlaceSize(true)
, m_ConvertX(true)
, m_ConvertY(false)
, m_WidthHeight(true)
, m_Interleaved(false)
, m_ZigZagged(false)
, m_UseLabel(true)
, m_BitsPerPixel(0)
, m_MaskOrder(moPixelMask)
, m_Compiler(asmGeneric)
, m_NumberBase(nbHexidecimal)
, m_BytePrefix("DEFB")
, m_LabelPrefix("")
, m_LabelPostfix(":")
{
    RL_METHOD
    frmPaletteImageParserOptions = new TfrmPaletteImageParserOptions(NULL);
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
__fastcall PaletteImageParserPlugin::~PaletteImageParserPlugin()
{
    RL_METHOD
    // release our resources before dying
    SAFE_ARRAY_DELETE(m_pPixels);
    SAFE_ARRAY_DELETE(m_pMasks);
    SAFE_DELETE(frmPaletteImageParserOptions);
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
HRESULT __fastcall PaletteImageParserPlugin::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    if (true == SAFE_PTR(frmPaletteImageParserOptions))
    {
        hResult = frmPaletteImageParserOptions->Initialize(pPlugin);
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
HRESULT __fastcall PaletteImageParserPlugin::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmPaletteImageParserOptions))
    {
        hResult = frmPaletteImageParserOptions->Release();
    }
    SAFE_DELETE(frmPaletteImageParserOptions);
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall PaletteImageParserPlugin::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall PaletteImageParserPlugin::GetOptionsPanel(TPanel*& Panel)
{
    RL_METHOD
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(frmPaletteImageParserOptions))
    {
        Panel = frmPaletteImageParserOptions->panPaletteImageParser;
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall PaletteImageParserPlugin::GetResourceTypes(KXmlInfo*& XmlData, TStringList*& Types)
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
HRESULT __fastcall PaletteImageParserPlugin::GetResourcesList(KXmlInfo*& XmlData, const String& sType, TStringList*& Resources)
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
HRESULT __fastcall PaletteImageParserPlugin::ParseResources(KXmlInfo*& XmlData, String& Resource, TStringList*& Code, String& ParserData)
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
            KXmlInfo* ResNode = GetResourceNode(XmlData, sType, sName, sPalette);
            SetPaletteParameters(sPalette);

            if (ParserData.Trim() == "")
            {
                if (frmPaletteImageParserOptions->radSourceCodeAsm->Checked)
                {
                    m_BytePrefix   = frmPaletteImageParserOptions->edtPrefix->Text;
                    m_LabelPrefix  = frmPaletteImageParserOptions->edtLabelPrefix->Text;
                    m_LabelPostfix = frmPaletteImageParserOptions->edtLabelPostfix->Text;
                    ParserData  = ":scAsm";                 // Assembler
                    ParserData += ":ap" + m_BytePrefix;     // Assembler Prefix
                    ParserData += ":lpr" + m_LabelPrefix + "rpl";
                    ParserData += ":lpo" + m_LabelPostfix + "opl:";
                    m_Compiler = asmGeneric;
                    m_UseLabel = true;
                    if (!frmPaletteImageParserOptions->chkSourceCodeUseLabel->Checked)
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
                m_ZigZagged = false;
                if (frmPaletteImageParserOptions->radZXImageParserRowOrderZigZag->Checked)
                {
                    m_ZigZagged = true;
                    ParserData += ":ZigZagged";
                }
                m_PlaceSize = false;
                if (frmPaletteImageParserOptions->chkPlaceSize->Checked)
                {
                    ParserData += ":PlaceSize";
                    m_PlaceSize = true;
                }
                m_ConvertX = false;
                if (frmPaletteImageParserOptions->chkConvertX->Checked)
                {
                    ParserData += ":XChar";
                    m_ConvertX = true;
                }
                m_ConvertY = false;
                if (frmPaletteImageParserOptions->chkConvertY->Checked)
                {
                    ParserData += ":YChar";
                    m_ConvertY = true;
                }
                m_WidthHeight = true;
                if (frmPaletteImageParserOptions->radSizeHeightWidth->Checked)
                {
                    ParserData += ":HW";
                    m_WidthHeight = false;
                }
                if (frmPaletteImageParserOptions->radZXImageParserPixelMaskNone->Checked)
                {
                    ParserData += ":NoMask";
                    m_MaskOrder = moNoMask;
                }
                if (frmPaletteImageParserOptions->radZXImageParserPixelMaskBytePairs->Checked)
                {
                    ParserData += ":PixelMask";
                    m_MaskOrder = moPixelMask;
                }
                if (frmPaletteImageParserOptions->radZXImageParserMaskPixelBytePairs->Checked)
                {
                    ParserData += ":MaskPixel";
                    m_MaskOrder = moMaskPixel;
                }
                else if (frmPaletteImageParserOptions->radZXImageParserBeforePixels->Checked)
                {
                    ParserData += ":BeforePixel";
                    m_MaskOrder = moBeforePixel;
                }
                else if (frmPaletteImageParserOptions->radZXImageParserAfterPixels->Checked)
                {
                    ParserData += ":AfterPixel";
                    m_MaskOrder = moAfterPixel;
                }
                m_MaskInvert = false;
                if (frmPaletteImageParserOptions->radZXImageParserMaskCovers->Checked)
                {
                    ParserData += ":MaskInvert";
                    m_MaskInvert = true;
                }
                if (m_Interleaved)
                {
                    ParserData += ":Interleaved";
                }
                if (m_BitsPerPixel == 1)
                {
                    ParserData += ":BPP_1";
                }
                else if (m_BitsPerPixel == 2)
                {
                    ParserData += ":BPP_2";
                }
                else if (m_BitsPerPixel == 4)
                {
                    ParserData += ":BPP_4";
                }
                else
                {
                    ParserData += ":BPP_8";
                }
                if (frmPaletteImageParserOptions->radZXImageParserDecimal->Checked)
                {
                    m_NumberBase = nbDecimal;
                    ParserData += ":Dec";               // Base: Decimal
                }
                else if (frmPaletteImageParserOptions->radZXImageParserBinary->Checked)
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

                // Get the flag settings
                m_PlaceSize   = ParserData.Pos("PlaceSize"  ) > 0;
                m_ConvertX    = ParserData.Pos("XChar"      ) > 0;
                m_ConvertY    = ParserData.Pos("YChar"      ) > 0;
                m_MaskInvert  = ParserData.Pos("MaskInvert" ) > 0;
                m_Interleaved = ParserData.Pos("Interleaved") > 0;
                m_ZigZagged   = ParserData.Pos("ZigZagged"  ) > 0;
                m_BitsPerPixel= ParserData.Pos("BPP_1"      ) > 0 ? 1 :
                               (ParserData.Pos("BPP_2"      ) > 0 ? 2 :
                               (ParserData.Pos("BPP_4"      ) > 0 ? 4 : 8));
                m_WidthHeight = ParserData.Pos("HW"         ) == 0;

                // Get the mask order
                m_MaskOrder = moNoMask;
                if (ParserData.Pos("PixelMask") > 0)
                    m_MaskOrder = moPixelMask;
                else if (ParserData.Pos("MaskPixel") > 0)
                    m_MaskOrder = moMaskPixel;
                else if (ParserData.Pos("BeforePixel") > 0)
                    m_MaskOrder = moBeforePixel;
                else if (ParserData.Pos("AfterPixel") > 0)
                    m_MaskOrder = moAfterPixel;
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
void __fastcall PaletteImageParserPlugin::GetResourceInfo(const String& sResource, String& sType, String& sName)
{
    int iSlash = sResource.Pos('\\');
    if (iSlash)
    {
        sType = sResource.SubString(1, iSlash - 1);
        sName = sResource.SubString(iSlash + 1, sResource.Length());
    }
}
//---------------------------------------------------------------------------
KXmlInfo* __fastcall PaletteImageParserPlugin::GetResourceNode(KXmlInfo*& XmlData, const String& sType, const String& sName, String& sPalette)
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
                                        KXmlInfo* Palette = Frame->GetNode("Palette", 0);
                                        if (Palette)
                                        {
                                            sPalette = Palette->GetText();
                                        }
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
HRESULT __fastcall PaletteImageParserPlugin::ParseXmlNode(KXmlInfo*& ResNode, TStringList*& Code)
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

        int iFrame = 0;
        bool bMultiFramed = ResNode->size() > 1;
        for (KXmlNodes::iterator FrameIt = ResNode->begin(); FrameIt != ResNode->end(); FrameIt++)
        {
            String sMasked = (*FrameIt)->GetNode("IsMasked", 0)->GetText().LowerCase();
            m_bMasked = sMasked == "true" && m_MaskOrder != moNoMask;
            // get the name of the frame and make a label
            String sName = (*FrameIt)->GetNode("Name", 0)->GetText().Trim();

            // get the frames properties
            int iWidth = (*FrameIt)->GetNode("Width", 0)->GetInt();
            int iHeight = (*FrameIt)->GetNode("Height", 0)->GetInt();
            String sPalette = (*FrameIt)->GetNode("Palette", 0)->GetText();
            String sPixels = (*FrameIt)->GetNode("Pixels", 0)->GetText();
            String sMasks("");
            if (m_bMasked)
            {
                sMasks = (*FrameIt)->GetNode("Masks", 0)->GetText();
            }

            Code->Add(m_CL + "Name    : " + sName + m_CR);
            if (bMultiFramed)
            {
                Code->Add(m_CL + "Frame   : " + IntToStr(iFrame) + m_CR);
            }
            //Code->Add(m_CL + "Size    : " + IntToStr(iWidth) + "x" + IntToStr(iHeight) + m_CR);
            Code->Add(m_CL + "Palette : " + sPalette + m_CR);
            Code->Add(m_CL + "Masked  : " + (m_bMasked ? String("Yes") : String("No")) + m_CR);
            Code->Add(m_CL + "RowOrder: " + (m_ZigZagged ? String("ZigZag") : String("Classic")) + m_CR);

            m_Name = sName;
            if (bMultiFramed)
            {
                String sFrame = "000" + IntToStr(iFrame);
                m_Name = sName + sFrame.SubString(sFrame.Length()-2, 3);
                iFrame++;
            }

            // pixels per byte
            // sPixels length div 2 because 1 byte is 2 characters
            // div height because each row is made of bytes
            // div result gives pixels per byte for the palette
            int iPixelsPerByte = iWidth / ((sPixels.Length() >> 1) / iHeight);
            bool bPixelsOK = iPixelsPerByte >= 1 && iPixelsPerByte <= 8;

            if (bPixelsOK)
            {
                m_iConvertedW = iWidth;
                m_iConvertedH = iHeight;
                if (m_PlaceSize)
                {
                    int w = iWidth;
                    int h = iHeight;
                    String sX("pixels");
                    String sY("pixels");
                    if (m_ConvertX)
                    {
                        w /= iPixelsPerByte;
                        sX = "bytes";
                    }
                    if (m_ConvertY)
                    {
                        h /= 8;
                        sY = "chars";
                    }
                    if (m_WidthHeight)
                        Code->Add(m_CL + "Size: " + IntToStr(w) + " x " + IntToStr(h) + " - (" + sX + " x " + sY + ")" + m_CR);
                    else
                        Code->Add(m_CL + "Size: " + IntToStr(h) + " x " + IntToStr(w) + " - (" + sY + " x " + sX + ")" + m_CR);
                    m_iConvertedW = w;
                    m_iConvertedH = h;
                }
                GetFrameData(sPixels, sMasks, sPalette, iWidth / iPixelsPerByte);
                ParseIntoSourceCode(iWidth / iPixelsPerByte, iHeight, Code);
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
void __fastcall PaletteImageParserPlugin::GetFrameData(const String& sPixels, const String& sMasks, const String& sPalette, int iWidth)
{
    if (sPixels.Trim() != "")
    {
        ConvertStringToData(m_pPixels, sPixels, iWidth);
    }
    if (m_bMasked && sMasks.Trim() != "")
    {
        ConvertStringToData(m_pMasks, sMasks, iWidth, m_MaskInvert);
    }
}
//---------------------------------------------------------------------------
// Convert the string data into byte pixel data
//---------------------------------------------------------------------------
void __fastcall PaletteImageParserPlugin::ConvertStringToData(unsigned char*& pData, const String& sData, int iWidth, bool bInvertByte)
{
    // delete the old data
    SAFE_ARRAY_DELETE(pData);
    // now allocate some new data
    int iSize = sData.Length() / 2;
    pData = new unsigned char[iSize];
	unsigned char invertByte = bInvertByte ? 255 : 0;
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

		pData[i] = pData[i] ^ invertByte;
	}
}
//---------------------------------------------------------------------------
unsigned char __fastcall PaletteImageParserPlugin::ConvertToInterleave(unsigned char cp)
{
    unsigned char np = cp;
    if (m_Interleaved)
    {

        // need to re-arrange the bits
        if (m_BitsPerPixel == 2)
        {
            np = 0;
            // bit 0,1 pen 3
            // bit 2,3 pen 2
            // bit 4,5 pen 1
            // bit 6,7 pen 0
            np |= (cp & 0x01) ? 0x01 : 0x00;    // p3(0)
            np |= (cp & 0x02) ? 0x10 : 0x00;    // p3(1)
            np |= (cp & 0x04) ? 0x02 : 0x00;    // p2(0)
            np |= (cp & 0x08) ? 0x20 : 0x00;    // p2(1)
            np |= (cp & 0x10) ? 0x04 : 0x00;    // p1(0)
            np |= (cp & 0x20) ? 0x40 : 0x00;    // p1(1)
            np |= (cp & 0x40) ? 0x08 : 0x00;    // p0(0)
            np |= (cp & 0x80) ? 0x80 : 0x00;    // p0(1)
        }
        else if (m_BitsPerPixel == 4)
        {
            np = 0;
            // bit 0-3 pen 1
            // bit 4-7 pen 0
            np |= (cp & 0x10) ? 0x80 : 0x00;    // p1(0)
            np |= (cp & 0x20) ? 0x08 : 0x00;    // p1(1)
            np |= (cp & 0x40) ? 0x20 : 0x00;    // p1(2)
            np |= (cp & 0x80) ? 0x02 : 0x00;    // p1(3)

            np |= (cp & 0x01) ? 0x40 : 0x00;    // p0(0)
            np |= (cp & 0x02) ? 0x04 : 0x00;    // p0(1)
            np |= (cp & 0x04) ? 0x10 : 0x00;    // p0(2)
            np |= (cp & 0x08) ? 0x01 : 0x00;    // p0(3)
        }
    }
    return np;
}
//---------------------------------------------------------------------------
void __fastcall PaletteImageParserPlugin::ParsePixels(int iWidth, int iHeight, TStringList*& Code)
{
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
            if (m_MaskOrder == moPixelMask)
            {
                sLine = sLine + NumToStr(ConvertToInterleave(m_pPixels[i]));
                if (true == m_bMasked && true == SAFE_PTR(m_pMasks))
                    sLine = sLine + ", " + NumToStr(GetMaskFor(w, h, iWidth));
            }
            else
            {
                if (true == m_bMasked && true == SAFE_PTR(m_pMasks) && m_MaskOrder == moMaskPixel)
                    sLine = sLine + NumToStr(GetMaskFor(w, h, iWidth)) + ", ";
                sLine = sLine + NumToStr(ConvertToInterleave(m_pPixels[i]));
            }
            ++i;
        }
        if (m_Compiler == asmGeneric)
        {
            Code->Add(m_BytePrefix + " " + sLine);
        }
        else
        {
            Code->Add("\t" + sLine + ((h < (iHeight - 1) || m_MaskOrder == moAfterPixel) ? "," : ""));
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall PaletteImageParserPlugin::ParseMasks(int iWidth, int iHeight, TStringList*& Code)
{
    if (true == m_bMasked && true == SAFE_PTR(m_pMasks) && m_MaskOrder >= moBeforePixel)
    {
        for (int h = 0; h < iHeight; h++)
        {
            String sLine = "";
            for (int w = 0; w < iWidth; w++)
            {
                if (w) sLine = sLine + ", ";

                sLine = sLine + NumToStr(GetMaskFor(w, h, iWidth));
            }
            if (m_Compiler == asmGeneric)
                Code->Add(m_BytePrefix + " " + sLine);
            else
                Code->Add("\t" + sLine + ((h < (iHeight - 1) || m_MaskOrder == moBeforePixel) ? "," : ""));
        }
    }
}
//---------------------------------------------------------------------------
unsigned char MaskBits[8] =
{
    0x80,
    0x40,
    0x20,
    0x10,
    0x08,
    0x04,
    0x02,
    0x01
};
/*unsigned char Masks2BPP[8] =
{
    0xC0,
    0x30,
    0x0C,
    0x30
};*/
//---------------------------------------------------------------------------
unsigned char __fastcall PaletteImageParserPlugin::GetMaskFor(int w, int h, int iWidth)
{
    unsigned char Mask = 0;
    int PixelsPerByte = 8 / m_BitsPerPixel;
    int MaskStride = (iWidth * PixelsPerByte) / 8;
    for (int i = 0; i < PixelsPerByte; ++i)
    {
        // masks are 1 bit per pixel
        int px = (w * PixelsPerByte) + i;
        unsigned int TmpMask = m_pMasks[(px / 8) + (h * MaskStride)];
        TmpMask = TmpMask & MaskBits[px % 8];

        // is the mask bit set for the pixel?
        if (TmpMask)
        {
            switch(m_BitsPerPixel)
            {
                case 8:
                    Mask = 0xFF;
                    break;
                case 4:
                    Mask |= (0xF0 >> (i * 4));
                    break;
                case 2:
                    Mask |= (0xC0 >> (i * 2));
                    break;
                case 1:
                default:
                    Mask |= TmpMask;
                    break;
            }
        }
    }
    return ConvertToInterleave(Mask);
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
void __fastcall PaletteImageParserPlugin::ParseIntoSourceCode(int iWidth, int iHeight, TStringList*& Code)
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
void __fastcall PaletteImageParserPlugin::ParseIntoC(int iWidth, int iHeight, TStringList*& Code)
{
    int iPs = (iWidth * iHeight);   // Pixels Size in bytes
    int iSize = m_bMasked ? iPs * 2 : iPs;

    iSize += m_PlaceSize ? 2 : 0;
    Code->Add("unsigned char " + m_Name + "[" + IntToStr(iSize) + "] =");
    Code->Add("{");

    if (m_PlaceSize)
    {
        if (m_WidthHeight)
            Code->Add("\t" + NumToStr(m_iConvertedW) + ", " + NumToStr(m_iConvertedH) + ", \t\t /* Width x Height */");
        else
            Code->Add("\t" + NumToStr(m_iConvertedH) + ", " + NumToStr(m_iConvertedW) + ", \t\t /* Height x Width */");
    }

    ParseScanlines(iWidth, iHeight, Code);
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
void __fastcall PaletteImageParserPlugin::ParseIntoAsm(int iWidth, int iHeight, TStringList*& Code)
{
    if (m_UseLabel)
    {
        Code->Add(m_LabelPrefix + m_Name + m_LabelPostfix);
    }
    if (m_PlaceSize)
    {
        if (m_WidthHeight)
            Code->Add(m_BytePrefix + " " + NumToStr(m_iConvertedW) + ", " + NumToStr(m_iConvertedH) + "\t\t; Width x Height");
        else
            Code->Add(m_BytePrefix + " " + NumToStr(m_iConvertedH) + ", " + NumToStr(m_iConvertedW) + "\t\t; Height x Width");
    }

    ParseScanlines(iWidth, iHeight, Code);
}
//---------------------------------------------------------------------------
void __fastcall PaletteImageParserPlugin::ParseScanlines(int iWidth, int iHeight, TStringList*& Code)
{
    if (true == m_bMasked && true == SAFE_PTR(m_pMasks) && m_MaskOrder < moBeforePixel)
    {
        if (m_MaskOrder == moPixelMask)
            Code->Add(m_CL + "pixel and mask bit pairs" + m_CR);
        else
            Code->Add(m_CL + "mask and pixel bit pairs" + m_CR);
        ParsePixels(iWidth, iHeight, Code);
    }
    else
    {
        if (m_MaskOrder == moBeforePixel)
        {
            if (m_bMasked)
            {
                Code->Add(m_CL + "masks" + m_CR);
                ParseMasks(iWidth, iHeight, Code);
            }
            Code->Add(m_CL + "pixels" + m_CR);
            ParsePixels(iWidth, iHeight, Code);
        }
        else
        {
            Code->Add(m_CL + "pixels" + m_CR);
            ParsePixels(iWidth, iHeight, Code);
            if (m_bMasked)
            {
                Code->Add(m_CL + "masks" + m_CR);
                ParseMasks(iWidth, iHeight, Code);
            }
        }
    }
}
//---------------------------------------------------------------------------
String __fastcall PaletteImageParserPlugin::NumToStr(unsigned char iNum)
{
    String sNum = "";
    String sPrefix = frmPaletteImageParserOptions->edtNumericalPrefix->Text.Trim();
    if (frmPaletteImageParserOptions->radZXImageParserDecimal->Checked)
    {
        sNum = "   " + IntToStr(iNum);
        sNum = sPrefix + sNum.SubString(sNum.Length() - 2, 3);
    }
    else if (frmPaletteImageParserOptions->radZXImageParserHexidecimal->Checked)
    {
        if (sPrefix == "")
        {
            sPrefix = "$";
        }
        sNum = "00" + IntToHex(iNum, 2);
        sNum = sPrefix + sNum.SubString(sNum.Length() - 1, 2);
    }
    else if (frmPaletteImageParserOptions->radZXImageParserBinary->Checked)
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
#define SUPPORTED_PALETTES 11
String g_sSupportedPalettes[SUPPORTED_PALETTES] =
{
    "Amstrad CPC Mode 0",               // 0
    "Amstrad CPC Mode 1",               // 1
    "Amstrad CPC Mode 2",               // 2
    "Sam Coupe Mode 3",                 // 3
    "Sam Coupe Mode 4",                 // 4
    "C64 MultiColor Palette",           // 5
    "Monochrome",                       // 6
    "Enterprise 64/128 - 2 Colours",    // 7
    "Enterprise 64/128 - 4 Colours",    // 8
    "Enterprise 64/128 - 16 Colours",   // 9
    "Enterprise 64/128 - 256 Colours"   // 10
};
//---------------------------------------------------------------------------
bool __fastcall PaletteImageParserPlugin::PaletteSupported(const String& sPalette)
{
    bool bSupported = false;
    for (int i = 0; i < SUPPORTED_PALETTES && false == bSupported; i++)
    {
        bSupported = g_sSupportedPalettes[i].LowerCase() == sPalette.LowerCase();
    }
    return bSupported;
}
//---------------------------------------------------------------------------
void __fastcall PaletteImageParserPlugin::SetPaletteParameters(const String& sPalette)
{
    if (sPalette == g_sSupportedPalettes[10])       // ep32 256 color
    {
        m_BitsPerPixel = 8;
        m_Interleaved  = false;
    }
    else if (sPalette == g_sSupportedPalettes[0] || // cpc mode 0
             sPalette == g_sSupportedPalettes[9])   // ep32 16 color
    {
        m_BitsPerPixel = 4;
        m_Interleaved  = true;
    }
    else if (sPalette == g_sSupportedPalettes[1] || // cpc mode 1
             sPalette == g_sSupportedPalettes[8])   // ep32 4 color
    {
        m_BitsPerPixel = 2;
        m_Interleaved  = true;
    }
    else if (sPalette == g_sSupportedPalettes[2] || // cpc mode 2
             sPalette == g_sSupportedPalettes[4] || // sam mode 4
             sPalette == g_sSupportedPalettes[6] || // monochrome
             sPalette == g_sSupportedPalettes[7])   // ep32 2 color
    {
        m_BitsPerPixel = 1;
        m_Interleaved  = false;
    }
}
//---------------------------------------------------------------------------

