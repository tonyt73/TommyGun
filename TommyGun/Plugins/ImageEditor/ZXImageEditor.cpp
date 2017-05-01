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
//- NAMESPACES --------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
using namespace Plugin;
using namespace Logging;
//- MINI-PLUGIN MANAGER -----------------------------------------------------
ZXPluginManager g_MiniPluginManager(".ipi");
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Logging;
using namespace ImageEditor;
//---------------------------------------------------------------------------
const String    g_sSignature    = "ImageEditor";
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
ZXImageEditor* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXImageEditor();
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
__fastcall ZXImageEditor::ZXImageEditor()
: m_bDirty(false)
, m_bUndoInProgress(false)
, m_pPalettePanel(NULL)
{
    RL_METHOD
    Screen->Cursors[99] = LoadCursor(HInstance, "SELECT");
    // create the vcl form the plugin uses
    try
    {
        frmImageEditor = new TfrmImageEditor(NULL);
        //frmImageEditor->SetImageManager(&m_ImageManager);
    }
    catch(...)
    {
        frmImageEditor = NULL;
    }
    m_ImageManager.OnImageChanged = OnImageChanged;
    m_ImageManager.OnImageRenamed = OnImageRenamed;
    m_ImageManager.OnPostMessage  = OnPostMessage;

    m_CurrentImage.sOwner = "";
    m_CurrentImage.iIndex = -1;
    m_CurrentImage.iFrame = -1;
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
__fastcall ZXImageEditor::~ZXImageEditor()
{
    RL_METHOD
    // release our resources before dying
    Release();
    // destroy the vcl form the plugin used
    SAFE_DELETE(frmImageEditor);
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
HRESULT __fastcall ZXImageEditor::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_FAIL;
    if (true == SAFE_PTR(frmImageEditor))
    {
        g_MiniPluginManager.Initialize(pPlugin->Handle);
        hResult = frmImageEditor->Initialise(pPlugin->Handle);
        //ZX_LOG_INFO(lfPlugin, "Loading ImageEditor Mini-Plugins")
        int iPluginsLoaded = g_MiniPluginManager.LoadPlugins(pPlugin->Handle, pPlugin->ParentSignature);
        if (0 < iPluginsLoaded)
        {
            OrganisePlugins();
        }
        // TODO: add icons to Options here
        //ZX_LOG_INFO(lfPlugin, "Loaded " + IntToStr(iPluginsLoaded) + " ImageEditor Mini-Plugin(s)")
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
HRESULT __fastcall ZXImageEditor::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    g_MiniPluginManager.UnloadPlugins();
    g_MiniPluginManager.Release();
    if (true == SAFE_PTR(frmImageEditor))
    {
        hResult = frmImageEditor->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::RegisterEvents(void)
{
    // standard events
    RegisterEvent(TZX_QUERY_DATASAVED                   , EventSaveQuery        );
    // custom events
    RegisterEvent(TZXC_IMAGE_EDITOR_GET_IMAGE_NAMES     , EventGetImageNames    );
    RegisterEvent(TZXC_IMAGE_EDITOR_GET_IMAGE_BITMAPS   , EventGetImageBitmaps  );
    RegisterEvent(TZXC_IMAGE_EDITOR_GET_IMAGE_SUBTYPES  , EventGetImageSubTypes );
    RegisterEvent(TZXN_XML_NEW                          , EventXmlNew           );
    RegisterEvent(TZXN_XML_POST_LOAD                    , EventXmlPostLoad      );
    RegisterEvent(TZXN_XML_PRE_SAVE                     , EventXmlPreSave       );
    RegisterEvent(TZXN_XML_UPDATE                       , EventXmlUpdate        );
    RegisterEvent(TZXN_XML_UNDO_RESTORE                 , EventXmlUndoRestore   );
    RegisterEvent(TZX_QUERY_COPYPASTE                   , EventQueryEditFeatures);
    RegisterEvent(TZX_VERB_COPY                         , EventEditCopy         );
    RegisterEvent(TZX_VERB_CUT                          , EventEditCut          );
    RegisterEvent(TZX_VERB_PASTE                        , EventEditPaste        );
    RegisterEvent(TZX_VERB_DELETE                       , EventEditDelete       );
    RegisterEvent(TZX_QUERY_KEY_PANEL                   , EventKeyPanel         );
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventSaveQuery(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        bool* bNeedToSave = (bool*)lpData;
        *bNeedToSave |= _this->m_bDirty || _this->m_ImageManager.IsDirty();
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventGetImageBitmaps(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        hResult = E_FAIL;
        std::vector<Graphics::TBitmap*>* vpImages = reinterpret_cast<std::vector<Graphics::TBitmap*>*>(lpData);
        if (true == SAFE_PTR(vpImages))
        {
            _this->m_ImageManager.GetImageBitmaps(vpImages, *(String*)dwParam, dwArg);
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventGetImageNames(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        hResult = E_FAIL;
        std::vector<String>* vpNames = reinterpret_cast<std::vector<String>*>(lpData);
        if (true == SAFE_PTR(vpNames))
        {
            _this->m_ImageManager.GetImageNames(vpNames, *(String*)dwParam, dwArg);
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventGetImageSubTypes(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        hResult = E_FAIL;
        std::vector<int>* vpSubTypes = reinterpret_cast<std::vector<int>*>(lpData);
        if (true == SAFE_PTR(vpSubTypes))
        {
            _this->m_ImageManager.GetImageSubTypes(vpSubTypes, *(String*)dwParam, dwArg);
            hResult = S_OK;
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventXmlNew(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        _this->m_ImageManager.ClearImages();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventXmlPostLoad(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        hResult = E_FAIL;
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            hResult = _this->m_ImageManager.Load(*xmlInfo);
            _this->NotifyPluginEvent(NULL, TZXN_XML_POST_LOAD, lpData, dwParam, dwArg);
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventXmlPreSave(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            hResult = _this->m_ImageManager.Save(*xmlInfo);
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventXmlUpdate(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            hResult = _this->m_ImageManager.Save(*xmlInfo, false);
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventXmlUndoRestore(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this) && true == SAFE_PTR(lpData))
    {
        KXmlInfo* xmlInfo = reinterpret_cast<KXmlInfo*>(lpData);
        if (true == SAFE_PTR(xmlInfo))
        {
            _this->UndoRestore(xmlInfo);
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventQueryEditFeatures(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    // we support finding, undo, redo and copy, cut and paste
    return S_QUERY_YES;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventEditCopy(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        frmImageEditor->EditCopy();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventEditCut(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        frmImageEditor->EditCut();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventEditPaste(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        frmImageEditor->EditPaste();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventEditDelete(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    ZXImageEditor* _this = dynamic_cast<ZXImageEditor*>(EventManager);
    if (true == SAFE_PTR(_this))
    {
        frmImageEditor->EditCut();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT WINAPI ZXImageEditor::EventKeyPanel(ZXEventManager* EventManager, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    RL_HRESULT(E_POINTER);
    if (true == SAFE_PTR(lpData))
    {
        *((TPanel**)lpData) = frmImageEditor->panImageKeysPanel;
        hResult = S_QUERY_YES;
    }
    return hResult;
}
//---------------------------------------------------------------------------
String __fastcall ZXImageEditor::ExtractPurpose(const String& sPluginDescription)
{
    String sPurpose;
    int iOpen  = sPluginDescription.Pos("(");
    int iClose = sPluginDescription.LastDelimiter(")");
    if (0 != iOpen && 0 != iClose)
    {
        sPurpose = sPluginDescription.SubString(iOpen + 1, iClose - iOpen - 1);
    }
    else
    {
        //ZX_LOG_ERROR(lfPlugin, "Failed to read purpose from " + sPluginDescription);
    }
    return sPurpose;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::GetFormatInterfaces(ZXPlugin* Plugin)
{
	for (std::vector<ZXFormatPluginInfo*>::iterator it = m_FormatPlugins.begin(); it != m_FormatPlugins.end(); it++)
	{
		if (ExtractFileName((*it)->pPlugin->Filename) == ExtractFileName(Plugin->Filename))
		{
			return;
		}
	}
	ZXFormatPluginInfo* FPi = new ZXFormatPluginInfo();
	if (true == SAFE_PTR(FPi))
	{
		int iInterfaces = 0;
		FPi->sPaletteName = ExtractPurpose(Plugin->Description);
		FPi->pPlugin = Plugin;
		FPi->pGetPaletteFunc = reinterpret_cast<GetPalettePtr>(GetProcAddress(Plugin->Handle, "GetPalette"));
		iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(FPi->pGetPaletteFunc))) ? 1 : 0;
		FPi->pGetPalettePanelFunc = reinterpret_cast<GetPalettePanelPtr>(GetProcAddress(Plugin->Handle, "GetPalettePanel"));
		iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(FPi->pGetPalettePanelFunc))) ? 1 : 0;
		FPi->pPaletteSignatureFunc = reinterpret_cast<PaletteSignaturePtr>(GetProcAddress(Plugin->Handle, "PalSignature"));
		iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(FPi->pPaletteSignatureFunc))) ? 1 : 0;
		FPi->sSignature   = NULL;
		FPi->pPalettePanel = NULL;
		FPi->pPalette      = NULL;
		if (3 == iInterfaces)
		{
			//ZX_LOG_INFO(lfPlugin, "Found all required Image Editor Palette Plugin interfaces");
			if (S_OK == FPi->pGetPalettePanelFunc(FPi->pPalettePanel) && S_OK == FPi->pGetPaletteFunc(FPi->pPalette) && S_OK == FPi->pPaletteSignatureFunc(FPi->sSignature))
			{
				if (true == SAFE_PTR(FPi->pPalettePanel))
				{
					FPi->pPalettePanel->Visible = false;
				}
				m_FormatPlugins.push_back(FPi);
            }
            else
            {
                //ZX_LOG_ERROR(lfPlugin, "Failed to get the Palette Object, the Palette Panel and the Palettes signature from mini-plugin + " + Plugin->Description);
            }
        }
        else
        {
            //ZX_LOG_ERROR(lfPlugin, "Failed to find all required Palette Interfaces from mini-plugin + " + Plugin->Description);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::GetToolInterfaces(ZXPlugin* Plugin)
{
    ZXToolPluginInfo* TPi = new ZXToolPluginInfo();
    if (true == SAFE_PTR(TPi))
    {
        TPi->pPlugin  = Plugin;
        int iInterfaces = 0;
        TPi->pMouseDownFunc = reinterpret_cast<MouseDownPtr>(GetProcAddress(Plugin->Handle, "MouseDown"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(TPi->pMouseDownFunc))) ? 1 : 0;
        TPi->pMouseMoveFunc = reinterpret_cast<MouseMovePtr>(GetProcAddress(Plugin->Handle, "MouseMove"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(TPi->pMouseMoveFunc))) ? 1 : 0;
        TPi->pMouseUpFunc = reinterpret_cast<MouseUpPtr>(GetProcAddress(Plugin->Handle, "MouseUp"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(TPi->pMouseUpFunc))) ? 1 : 0;
        TPi->pCursorFunc = reinterpret_cast<CursorPtr>(GetProcAddress(Plugin->Handle, "Cursor"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(TPi->pCursorFunc))) ? 1 : 0;
        TPi->pImageChangeFunc = reinterpret_cast<ImageChangePtr>(GetProcAddress(Plugin->Handle, "ImageChange"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(TPi->pImageChangeFunc))) ? 1 : 0;
        if (5 == iInterfaces)
        {
            //ZX_LOG_INFO(lfPlugin, "Found all required Image Editor Tool Plugin interfaces");
            m_ToolPlugins.push_back(TPi);
        }
        else
        {
            //ZX_LOG_ERROR(lfPlugin, "Failed to find all required Tool Interfaces from mini-plugin + " + Plugin->Description);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::GetTypeInterfaces(ZXPlugin* Plugin)
{
    ZXTypePluginInfo* TPi = new ZXTypePluginInfo();
    if (true == SAFE_PTR(TPi))
    {
        TPi->sPurpose = ExtractPurpose(Plugin->Description);
        TPi->pPlugin  = Plugin;
        int iInterfaces = 0;
        TPi->pTypeSignatureFunc = reinterpret_cast<TypeSignaturePtr>(GetProcAddress(Plugin->Handle, "TypeSignature"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(TPi->pTypeSignatureFunc))) ? 1 : 0;
        TPi->pTypeSetPalettesFunc = reinterpret_cast<TypeSetPalettesPtr>(GetProcAddress(Plugin->Handle, "SetPalettes"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(TPi->pTypeSetPalettesFunc))) ? 1 : 0;
        if (2 == iInterfaces)
        {
            //ZX_LOG_INFO(lfPlugin, "Found all required Image Editor Type Plugin interfaces");
            m_TypePlugins.push_back(TPi);
        }
        else
        {
            //ZX_LOG_ERROR(lfPlugin, "Failed to find all required Type Interfaces from mini-plugin + " + Plugin->Description);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::GetImportInterfaces(ZXPlugin* Plugin)
{
    ZXImportPluginInfo* IPi = new ZXImportPluginInfo();
    if (true == SAFE_PTR(IPi))
    {
        IPi->sPurpose = ExtractPurpose(Plugin->Description);
        IPi->pPlugin  = Plugin;
        int iInterfaces = 0;
        IPi->pTypeSetPalettesFunc = reinterpret_cast<TypeSetPalettesPtr>(GetProcAddress(Plugin->Handle, "SetPalettes"));
        iInterfaces += (FALSE == IsBadCodePtr(reinterpret_cast<StdCallPtr>(IPi->pTypeSetPalettesFunc))) ? 1 : 0;
        if (1 == iInterfaces)
        {
            //ZX_LOG_INFO(lfPlugin, "Found all required Image Import Plugin interfaces");
            m_ImportPlugins.push_back(IPi);
        }
        else
        {
            //ZX_LOG_ERROR(lfPlugin, "Failed to find all required Import Interfaces from mini-plugin + " + Plugin->Description);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::GetExportInterfaces(ZXPlugin* Plugin)
{
    ZXExportPluginInfo* EPi = new ZXExportPluginInfo();
    if (true == SAFE_PTR(EPi))
    {
        EPi->sPurpose = ExtractPurpose(Plugin->Description);
        EPi->pPlugin  = Plugin;
        m_ExportPlugins.push_back(EPi);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::OrganisePlugins(void)
{
    m_FormatPlugins.clear();
    m_ToolPlugins.clear();
    m_ImportPlugins.clear();
    m_ExportPlugins.clear();
    ZXPlugin* Plugin = g_MiniPluginManager.GetFirstPlugin();
    while (true == SAFE_PTR(Plugin))
    {
		String sDescription = Plugin->Description;
		if (0 != sDescription.Pos("Palette Plugin"))
		{
			GetFormatInterfaces(Plugin);
        }
        else if (0 != sDescription.Pos("Tool Plugin"))
        {
            GetToolInterfaces(Plugin);
        }
        else if (0 != sDescription.Pos("Type Plugin"))
        {
            GetTypeInterfaces(Plugin);
        }
        else if (0 != sDescription.Pos("Import Plugin"))
        {
            GetImportInterfaces(Plugin);
        }
        else if (0 != sDescription.Pos("Export Plugin"))
        {
            GetExportInterfaces(Plugin);
        }
        else
        {
            //ZX_LOG_ERROR(lfPlugin, "Invalid Image Editor plugin [" + sDescription + "]");
        }
        Plugin = g_MiniPluginManager.GetNextPlugin();
    };
    AssignPalettes();
    FillFormatBoxes();
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::FillFormatBoxes(void)
{
    std::vector<String>  vPaletteSignatures;
    TStringList* pPalettes = NULL;
    try
    {
        pPalettes = new TStringList();
    }
    catch(EOutOfMemory&)
    {
        pPalettes = NULL;
    }
    if (true == SAFE_PTR(pPalettes))
    {
        for (unsigned int i = 0; i < m_FormatPlugins.size(); ++i)
        {
            pPalettes->Add(m_FormatPlugins[i]->sPaletteName);
            vPaletteSignatures.push_back(m_FormatPlugins[i]->sSignature);
        }
        for (unsigned int i = 0; i < m_TypePlugins.size(); i++)
        {
            m_TypePlugins[i]->pTypeSetPalettesFunc(pPalettes, vPaletteSignatures);
        }
        for (unsigned int i = 0; i < m_ImportPlugins.size(); i++)
        {
            m_ImportPlugins[i]->pTypeSetPalettesFunc(pPalettes, vPaletteSignatures);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::AssignPalettes(void)
{
    // special case: move the monochrome palette to the end of the list
    for (unsigned int i = 0; i < m_FormatPlugins.size(); i++)
    {
        if (m_FormatPlugins[i]->pPlugin->Description.Pos("(Monochrome)") != 0)
        {
            ZXFormatPluginInfo* pi = m_FormatPlugins[i];
            m_FormatPlugins.push_back(pi);
            m_FormatPlugins.erase(m_FormatPlugins.begin() + i);
            break;
        }
    }
    std::vector<ZXPalette*> vPalettes;
    for (unsigned int i = 0; i < m_FormatPlugins.size(); i++)
    {
        vPalettes.push_back(m_FormatPlugins[i]->pPalette);
    }
    m_ImageManager.SetPalettes(vPalettes);
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::SelectFormat(unsigned int iFormat)
{
    static unsigned int iLastFormat = -2;
    if (iFormat != iLastFormat)
    {
        // hide the last palette panel
        if (true == SAFE_PTR(m_pPalettePanel))
        {
            m_pPalettePanel->Visible = false;
        }
        if (true == SAFE_PTR(frmImageEditor) && iFormat < m_FormatPlugins.size())
        {
            m_pPalettePanel = m_FormatPlugins[iFormat]->pPalettePanel;
            if (true == SAFE_PTR(m_pPalettePanel))
            {
                frmImageEditor->panPaletteContainer->Height = m_pPalettePanel->Height;
                m_pPalettePanel->Parent  = frmImageEditor->panPaletteContainer;
                m_pPalettePanel->Align   = alClient;
                m_pPalettePanel->Visible = true;
            }
        }
        else
        {
            frmImageEditor->panPaletteContainer->Height = 0;
        }
        iLastFormat = iFormat;
    }
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::SystemUpdateImage(TZX_HPLUGIN PluginHandle, ZXImage* Image)
{
    RL_METHOD
    RL_HRESULT(E_FAIL)
    if (true == SAFE_PTR(frmImageEditor))
    {
        bool bIsATypePlugin = false;
        for (unsigned int i = 0; i < m_TypePlugins.size() && false == bIsATypePlugin; ++i)
        {
            bIsATypePlugin = m_TypePlugins[i]->pPlugin->Handle == PluginHandle;
        }
        frmImageEditor->UpdateImage(Image, bIsATypePlugin);
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::SystemRefreshView(TZX_HPLUGIN PluginHandle)
{
    RL_METHOD
    RL_HRESULT(E_FAIL)
    if (true == SAFE_PTR(frmImageEditor))
    {
        frmImageEditor->RefreshView();
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::SystemAddToolBar(TZX_HPLUGIN PluginHandle, TToolBar* ToolBar)
{
    RL_METHOD
    RL_HRESULT(E_FAIL)
    if (true == SAFE_PTR(frmImageEditor))
    {
        hResult = frmImageEditor->AddToolBar(ToolBar) ? S_OK : E_FAIL;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::ToolMergePaintToolBar(TZX_HPLUGIN PluginHandle, TToolBar* ToolBar)
{
    RL_METHOD
    RL_HRESULT(E_FAIL)
    if (true == SAFE_PTR(frmImageEditor))
    {
        hResult = frmImageEditor->MergePaintToolBar(ToolBar) ? S_OK : E_FAIL;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::TypeAddTab(TZX_HPLUGIN PluginHandle, const String& sCaption, Graphics::TBitmap* pBitmap, TTabSheet*& pTabSheet)
{
    RL_METHOD
    RL_HRESULT(E_FAIL)
    if (true == SAFE_PTR(frmImageEditor))
    {
        hResult = frmImageEditor->AddTab(sCaption, pBitmap, pTabSheet) ? S_OK : E_FAIL;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::TypeGetImageManager(TZX_HPLUGIN PluginHandle, ZXImageManager*& pImageManager)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    pImageManager = &m_ImageManager;
    return hResult;
}
//---------------------------------------------------------------------------
ZXImage* __fastcall ZXImageEditor::CreateImage(int iWidth, int iHeight, bool bMasked, unsigned int iPalette)
{
    ZXImage* Image = NULL;
    if (iPalette < m_FormatPlugins.size())
    {
        Image = new ZXImage(iWidth, iHeight, bMasked, m_FormatPlugins[iPalette]->pPalette);
    }
    return Image;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::SelectPalette(ZXPalette* Palette)
{
    if (true == SAFE_PTR(Palette))
    {
        for (unsigned int i = 0; i < m_FormatPlugins.size(); ++i)
        {
            if (m_FormatPlugins[i]->pPalette == Palette)
            {
                SelectFormat(i);
                break;
            }
        }
    }
    else
    {
        SelectFormat(-1);
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageEditor::DoToolMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDone = false;
    // loop through the tool plugins until one return S_OK
    for (unsigned int i = 0; i < m_ToolPlugins.size() && false == bDone; ++i)
    {
        bDone = (S_OK == m_ToolPlugins[i]->pMouseDownFunc(Image, Button, Shift, X, Y));
    }
    return bDone;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageEditor::DoToolMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    bool bDone = false;
    // loop through the tool plugins until one return S_OK
    for (unsigned int i = 0; i < m_ToolPlugins.size() && false == bDone; ++i)
    {
        bDone = (S_OK == m_ToolPlugins[i]->pMouseMoveFunc(Image, Shift, X, Y));
    }
    return bDone;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageEditor::DoToolMouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    bool bDone = false;
    // loop through the tool plugins until one return S_OK
    for (unsigned int i = 0; i < m_ToolPlugins.size() && false == bDone; ++i)
    {
        bDone = (S_OK == m_ToolPlugins[i]->pMouseUpFunc(Image, Button, Shift, X, Y));
    }
    return bDone;
}
//---------------------------------------------------------------------------
TCursor __fastcall ZXImageEditor::DoToolCursor(void)
{
    bool bDone = false;
    TCursor Cursor = crDefault;
    // loop through the tool plugins until one return S_OK
    for (unsigned int i = 0; i < m_ToolPlugins.size() && false == bDone; ++i)
    {
        bDone = (S_OK == m_ToolPlugins[i]->pCursorFunc(Cursor));
    }
    return Cursor;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::DoToolImageChange(ZXImage* Image)
{
    // loop through the tool plugins until one return S_OK
    for (unsigned int i = 0; i < m_ToolPlugins.size(); ++i)
    {
        m_ToolPlugins[i]->pImageChangeFunc(Image);
    }
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::TypeSelectImage(TZX_HPLUGIN PluginHandle, const String& sOwner, int iIndex, int iFrame)
{
    RL_HRESULT(E_POINTER)
    KXmlInfo Undo;
    Undo.Add("Operation", "ImageSelect");
    Undo.Add("Plugin", "Image Editor");
    if (m_CurrentImage.iIndex != -1)
    {
        ZXImage* pOldImage = m_ImageManager.GetImage(m_CurrentImage.sOwner, m_CurrentImage.iIndex, m_CurrentImage.iFrame);
        if (true == SAFE_PTR(pOldImage))
        {
            Undo.Add("Description", String("Selection of " + pOldImage->Name));
        }
        else
        {
            Undo.Add("Description", String("No current selection"));
        }
    }
    else
    {
        Undo.Add("Description", "No current selection");
    }
    Undo.Add("Owner", m_CurrentImage.sOwner);
    Undo.Add("Index", m_CurrentImage.iIndex);
    Undo.Add("Frame", m_CurrentImage.iFrame);
    if (!m_bUndoInProgress)
    {
        PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
    }

    ZXImage* pImage = m_ImageManager.GetImage(sOwner, iIndex, iFrame);
    if (true == SAFE_PTR(frmImageEditor))
    {
        m_CurrentImage.sOwner = sOwner;
        m_CurrentImage.iIndex = iIndex;
        m_CurrentImage.iFrame = iFrame;
        frmImageEditor->SetImage(pImage, sOwner);
        hResult = S_OK;
    }
    KXmlInfo Redo;
    Redo.Add("Operation", "ImageSelect");
    Redo.Add("Plugin", "Image Editor");
    if (true == SAFE_PTR(pImage))
    {
        Redo.Add("Description", String("Selection of " + pImage->Name));
    }
    else
    {
        Redo.Add("Description", String("No current selection"));
    }
    Redo.Add("Owner", m_CurrentImage.sOwner);
    Redo.Add("Index", m_CurrentImage.iIndex);
    Redo.Add("Frame", m_CurrentImage.iFrame);
    if (!m_bUndoInProgress)
    {
        PostNotifyEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Redo, utRedo, 0);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::RegisterPluginEvent(TZX_HPLUGIN PluginHandle, TZX_EVENT Event)
{
    return g_MiniPluginManager.RegisterPluginEvent(PluginHandle, Event);    
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::NotifyPluginEvent(TZX_HPLUGIN PluginHandle, TZX_EVENT Event, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (TZXN_XML_UNDO_ADD == Event)
    {
        KXmlInfo* XmlUndo = (KXmlInfo*)lpData;
        if (true == SAFE_PTR(XmlUndo))
        {
            // add the current image details
            XmlUndo->Add("Owner", m_CurrentImage.sOwner);
            XmlUndo->Add("Index", m_CurrentImage.iIndex);
            XmlUndo->Add("Frame", m_CurrentImage.iFrame);
        }
        // send the undo information onto the framework
        return PostNotifyEvent(m_PluginHandle, Event, lpData, dwParam, dwArg);
    }
    return g_MiniPluginManager.Notify(PluginHandle, Event, lpData, dwParam, dwArg);
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageEditor::ImageGetCurrent(ZXImage*& pImage)
{
    pImage = frmImageEditor->GetCurrentImage();
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::OnPostMessage(TZXMsgRecipenent Recipenent, DWORD dwMsg, LPDATA lpData, DWORD dwParam, DWORD dwArg)
{
    if (!m_bUndoInProgress && Recipenent == mrCore || Recipenent == mrBoth)
    {
        PostNotifyEvent(NULL, dwMsg, lpData, dwParam, dwArg);
    }
    if (Recipenent == mrSubPlugins || (!m_bUndoInProgress && Recipenent == mrBoth))
    {
        g_MiniPluginManager.Notify(NULL, dwMsg, lpData, dwParam, dwArg);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::OnImageChanged(const String& sName, const String& sOwner, TZXChangeOperation Operation)
{
    g_MiniPluginManager.Notify(NULL, TZXC_IMAGE_EDITOR_IMAGE_CHANGED, (LPDATA)&sName, (DWORD)&sOwner, Operation);
    PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_IMAGE_CHANGED, (LPDATA)&sName, (DWORD)&sOwner, Operation);
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::OnImageRenamed(const String& sOldName, const String& sNewName, const String& sOwner, int iIndex)
{
    g_MiniPluginManager.Notify(NULL, TZXC_IMAGE_EDITOR_IMAGE_RENAMED, (LPDATA)&sOldName, (DWORD)&sOwner, (DWORD)&sNewName);
    PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_IMAGE_RENAMED, (LPDATA)&sOldName, (DWORD)&sOwner, (DWORD)&sNewName);
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::UndoRestore(KXmlInfo* xmlInfo)
{
    m_bUndoInProgress = true;
    if (false == m_ImageManager.UndoRestore(xmlInfo))
    {
        KXmlInfo* pOperation = xmlInfo->GetNode("Operation");

        if (true == SAFE_PTR(pOperation))
        {
            String sOperation = pOperation->GetText();

            if (sOperation == "ImageChange")
            {
                UndoImageChange(xmlInfo);
            }
            else if (sOperation == "ImageSelect")
            {
                UndoImageSelection(xmlInfo);
            }
        }
    }
    else
    {
        g_MiniPluginManager.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
        frmImageEditor->RefreshView();
        frmImageEditor->CenterImage();
    }
    m_bUndoInProgress = false;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::UndoImageChange(KXmlInfo* xmlInfo)
{
    // find the image and load the change
    KXmlInfo* Image = xmlInfo->GetNode("Image");
    if (true == SAFE_PTR(Image))
    {
        String sOwner = xmlInfo->GetNode("Owner")->GetText();
        int    iIndex = xmlInfo->GetNode("Index")->GetInt();
        int    iFrame = xmlInfo->GetNode("Frame")->GetInt();

        ZXImage* pImage = m_ImageManager.GetImage(sOwner, iIndex, iFrame);
        if (true == SAFE_PTR(pImage))
        {
            pImage->Load(*Image, false);
            m_CurrentImage.sOwner = sOwner;
            m_CurrentImage.iIndex = iIndex;
            m_CurrentImage.iFrame = iFrame;
            frmImageEditor->SetImage(pImage, sOwner);
            g_MiniPluginManager.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageEditor::UndoImageSelection(KXmlInfo* xmlInfo)
{
    m_CurrentImage.sOwner = xmlInfo->GetNode("Owner")->GetText();
    m_CurrentImage.iIndex = xmlInfo->GetNode("Index")->GetInt();
    m_CurrentImage.iFrame = xmlInfo->GetNode("Frame")->GetInt();

    if (-1 != m_CurrentImage.iIndex)
    {
        ZXImage* pImage = m_ImageManager.GetImage(m_CurrentImage.sOwner, m_CurrentImage.iIndex, m_CurrentImage.iFrame);
        if (true == SAFE_PTR(pImage))
        {
            frmImageEditor->SetImage(pImage, m_CurrentImage.sOwner);
            g_MiniPluginManager.Notify(NULL, IMAGE_EDITOR_IMAGE_SELECT, NULL, m_CurrentImage.iIndex, m_CurrentImage.iFrame);
            g_MiniPluginManager.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
        }
    }
    else
    {
        frmImageEditor->SetImage(NULL, "");
    }
}
//---------------------------------------------------------------------------


