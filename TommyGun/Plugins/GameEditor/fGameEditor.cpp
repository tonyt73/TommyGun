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
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "KRegistry"
#pragma link "shdocvw_ocx"
#pragma link "pngimage"
//-- NAMESPACES -------------------------------------------------------------
using namespace Scorpio;
using namespace Logging;
using namespace GameEditor;
//-- VCL FORM OBJECT --------------------------------------------------------
TfrmGameEditor *frmGameEditor;
//-- CONSTANTS --------------------------------------------------------------
const String g_sPluginTitle = "Designer";
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the class and reset some member variables
 * @param   Owner the VCL owner of the form
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @date    Modified 3 May 2002 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
__fastcall TfrmGameEditor::TfrmGameEditor(TComponent* Owner)
: TForm(Owner)
, m_bInitialized(false)
, m_bSaved(true)
, m_bScorePanelFound(true)
, m_GameStyle(gsNone)
{
    RL_METHOD
}
//---------------------------------------------------------------------------
// Destructor
/**
 * @brief   Frees allocated resources
 * @author  Tony Thompson
 * @date    Created 10 March 2003 by Tony Thompson
 * @remarks Copyright Scorpio Software 2003
 */
//---------------------------------------------------------------------------
__fastcall TfrmGameEditor::~TfrmGameEditor()
{
    RL_METHOD
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::FormCreate(TObject *Sender)
{
    RL_METHOD
    //MenusAdd();
    DoubleBuffered = true;
    pgcEditors->Visible = false;
    m_PropertyEditor.Init(tvwPropertyView, vlePropertyEditor);
    SetupWelcome();
    TResourceStream* rs = new TResourceStream((unsigned)HInstance, AnsiString("AGDHELP"), RT_RCDATA);
    rteHelp->PlainText = false;
    rteHelp->Lines->LoadFromStream(rs);
    delete rs;
}
//---------------------------------------------------------------------------
// Initialise
/**
 * Initialises the object, and integrates into the Shell evnironment
 * @param   PluginHandle the handle allocated to the plugin
 * @return  S_OK initialization successful, S_FALSE initalization failed
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmGameEditor::Initialise(TZX_HPLUGIN PluginHandle)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    // save the plugin handle
    m_PluginHandle = PluginHandle;
    // place the form onto the tab control
    TWinControl* tmpWindow = NULL;
    hResult = S_FALSE;
    if (S_OK == AddPage(PluginHandle, tmpWindow, g_sPluginTitle))
    {
        if (NULL != tmpWindow->Handle)
        {
            m_TabHandle = tmpWindow->Handle;

            hResult = SetPageBitmap( m_PluginHandle, m_TabHandle, imgSmallIcon, imgLargeIcon );
            Parent = tmpWindow;
            Visible = true;
            AddPluginIcon(m_PluginHandle, imgSmallIcon, "");
            TrapTabEvents(tmpWindow);
            OnTabHide(NULL);
            //LoadSettings();
            m_bInitialized = true;
            hResult = S_OK;

            // Initialise the Editor objects
            m_WindowArea.Init(imgLayout, imgWindow, imgCheckers);
            m_Keys.Init(imgKeyboard, imgKey1, imgKey2, imgKey3, imgKey4, imgKey5, imgKey6, imgKey7);
            m_CollisionDistance.Init();
            m_JumpTable.Init(imgJumpTable);
            m_Sounds.Init(lstAvailableSfx, lstGameSfx);
        }
    }
    return hResult;
}
//---------------------------------------------------------------------------
// Release
/**
 * Releases the resources associated with the Plugin
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmGameEditor::Release(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    //SaveSettings();
    for (unsigned int i = 0; i < m_ToolBarMenus.size(); i++)
    {
        SAFE_DELETE(m_ToolBarMenus[i]);
    }
    // Hide the form before releasing
    Visible = false;
    // Detach ourselves from the parent
    Parent->RemoveControl(this);
    // remove the tab we were allocated by shell
    RemovePage(m_PluginHandle, m_TabHandle);
    // reset our handle
    m_PluginHandle = 0;
    m_bInitialized = false;
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::OnMenuClick(TObject* Sender)
{
    TMenuItem* Menu = dynamic_cast<TMenuItem*>(Sender);
    if (true == SAFE_PTR(Menu))
    {
        Menu->Checked = !Menu->Checked;
        TToolBar* Toolbar = (TToolBar*)(Menu->Tag);
        if (true == SAFE_PTR(Toolbar))
        {
            Toolbar->Visible = Menu->Checked;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::TrapTabEvents(TWinControl* Control)
{
    if (true == SAFE_PTR(Control))
    {
        TTabSheet* TabSheet = dynamic_cast<TTabSheet*>(Control);
        if (true == SAFE_PTR(TabSheet))
        {
            TabSheet->OnHide = OnTabHide;
            TabSheet->OnShow = OnTabShow;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::OnTabHide(TObject *Sender)
{
    //MenusRemove();
    if (m_ToolBars.size() == m_ToolBarMenus.size())
    {
        for (unsigned int i = 0; i < m_ToolBars.size(); i++)
        {
            //m_ToolBars[i]->Visible = false;
            if (true == SAFE_PTR(m_ToolBarMenus[i]))
            {
                m_ToolBarMenus[i]->Visible  = false;
            }
            else
            {
                // why is the menu NULL?
                m_ToolBarMenus[i] = NULL;
            }
        }
    }
    else
    {
        //ZX_LOG_ERROR(lfGeneral, "The ToolBar list and the ToolbarMenu list sizes do not match!")
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::OnTabShow(TObject *Sender)
{
    if (m_ToolBars.size() == m_ToolBarMenus.size())
    {
        for (unsigned int i = 0; i < m_ToolBars.size(); i++)
        {
            m_ToolBarMenus[i]->Visible  = true;
            //m_ToolBars[i]->Visible = m_ToolBarMenus[i]->Checked;
        }
    }
    else
    {
        //ZX_LOG_ERROR(lfGeneral, "The ToolBar list and the ToolbarMenu list sizes do not match!")
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::RefreshView(void)
{
	// update stuff
}
//---------------------------------------------------------------------------
String __fastcall TfrmGameEditor::ZeroPadInt(int iValue, int iSize)
{
    String sValue = "000" + IntToStr(iValue);
    sValue = sValue.SubString(sValue.Length() - iSize + 1, iSize);
    return sValue;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::LoadSettings(void)
{
    bool bValue = false;
    int  iValue = 0;
    TColor cValue = clBlack;

    /*if (regScorpio->Read("GameEditor", "CenterImage"     , bValue)) chkCenterImage->Checked = bValue;
    if (regScorpio->Read("GameEditor", "BackgroundColor" , cValue)) panBackgroundColor->Color = cValue;
    if (regScorpio->Read("GameEditor", "ShowGridChar"    , bValue)) chkGridCharacter->Checked = bValue;
    if (regScorpio->Read("GameEditor", "ShowGridPixel"   , bValue)) chkGridPixel->Checked = bValue;
    if (regScorpio->Read("GameEditor", "AutoMagnify"     , bValue)) chkAutoMagnification->Checked = bValue;
    if (regScorpio->Read("GameEditor", "Magnification"   , iValue)) slrDisplayMagnification->Position = iValue;
    if (regScorpio->Read("GameEditor", "MaskTransparency", iValue)) slrMaskTransparency->Position = iValue;
    if (regScorpio->Read("GameEditor", "MaskColor"       , cValue)) panMaskColor->Color = cValue;
    if (regScorpio->Read("GameEditor", "ChrLineColor"    , cValue)) panChrLineColor->Color = cValue;
    if (regScorpio->Read("GameEditor", "PixelLineColor"  , cValue)) panPixelLineColor->Color = cValue;
    if (regScorpio->Read("GameEditor", "XScaleFacter"    , iValue)) slrCustomXScale->Position = iValue;
    if (regScorpio->Read("GameEditor", "YScaleFacter"    , iValue)) slrCustomYScale->Position = iValue;
    if (regScorpio->Read("GameEditor", "ScaleMode"       , iValue))
    {
        radModeScaleDefault->Checked = iValue == 0;
        radModeScaleRemove->Checked  = iValue == 1;
        radModeScaleCustom->Checked  = iValue == 2;
        UpdateModeScale();
    }
    sbxEditor->Color = panBackgroundColor->Color;
    */
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::SaveSettings(void)
{
    /*regScorpio->Write("GameEditor", "CenterImage"      , chkCenterImage->Checked           );
    regScorpio->Write("GameEditor", "BackgroundColor"  , panBackgroundColor->Color         );
    regScorpio->Write("GameEditor", "ShowGridChar"     , chkGridCharacter->Checked         );
    regScorpio->Write("GameEditor", "ShowGridPixel"    , chkGridPixel->Checked             );
    regScorpio->Write("GameEditor", "AutoMagnify"      , chkAutoMagnification->Checked     );
    regScorpio->Write("GameEditor", "Magnification"    , slrDisplayMagnification->Position );
    regScorpio->Write("GameEditor", "MaskTransparency" , slrMaskTransparency->Position     );
    regScorpio->Write("GameEditor", "MaskColor"        , panMaskColor->Color               );
    regScorpio->Write("GameEditor", "ChrLineColor"     , panChrLineColor->Color            );
    regScorpio->Write("GameEditor", "PixelLineColor"   , panPixelLineColor->Color          );
    regScorpio->Write("GameEditor", "XScaleFactor"     , slrCustomXScale->Position         );
    regScorpio->Write("GameEditor", "YScaleFactor"     , slrCustomYScale->Position         );
    if (radModeScaleDefault->Checked) regScorpio->Write("GameEditor", "ScaleMode" , 0);
    else if (radModeScaleRemove->Checked) regScorpio->Write("GameEditor", "ScaleMode" , 1);
    else regScorpio->Write("GameEditor", "ScaleMode" , 2);
    */
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::EditCopy(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::EditCut(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::EditPaste(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::MenusAdd(void)
{
    /*if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
    {
        popImage->Items->Remove(popToggleGridChar);
        popImage->Items->Remove(popToggleGridPixel);
        popImage->Items->Remove(popZoomIn);
        popImage->Items->Remove(popZoomOut);
        TMenuItem* mnuEdit = Application->MainForm->Menu->Items->Find("&Edit");
        if (true == SAFE_PTR(mnuEdit))
        {
            mnuEdit->NewBottomLine();
            mnuEdit->Add(popToggleGridChar);
            mnuEdit->Add(popToggleGridPixel);
            mnuEdit->Add(popZoomIn);
            mnuEdit->Add(popZoomOut);
        }
    }*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::MenusRemove(void)
{
    /*if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
    {
        TMenuItem* mnuEdit = Application->MainForm->Menu->Items->Find("&Edit");
        if (true == SAFE_PTR(mnuEdit))
        {
            mnuEdit->NewBottomLine();
            mnuEdit->Remove(popToggleGridChar);
            mnuEdit->Remove(popToggleGridPixel);
            mnuEdit->Remove(popZoomIn);
            mnuEdit->Remove(popZoomOut);
        }
        popImage->Items->Add(popToggleGridChar);
        popImage->Items->Add(popToggleGridPixel);
        popImage->Items->Add(popZoomIn);
        popImage->Items->Add(popZoomOut);
    }*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::imgKeyboardMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    m_Keys.MouseMove(X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    m_Keys.KeyDown(Key);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::New()
{
    tabWelcome->TabVisible = true;
    tabWindowArea->TabVisible = false;
    tabKeys->TabVisible = false;
    tabJumpTable->TabVisible = false;
    tabSounds->TabVisible = false;
    pgcEditors->ActivePage = tabWelcome;

    // get the project folder
    String sProjectFolder;
    PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sProjectFolder, 0, 0);
    // copy the game engine file into the project folder
    String appPath = ExtractFilePath(Application->ExeName);
    if (FileExists(appPath + "AGD\\AgdGameEngine.asm"))
    {
        String srcFile = appPath + "AGD\\AgdGameEngine.asm";
        String dstFile = sProjectFolder + "AgdGameEngine.asm";
        CopyFile(srcFile.c_str(), dstFile.c_str(), FALSE);
        SetFileAttributes(dstFile.c_str(), FILE_ATTRIBUTE_NORMAL);
    }

    // create a new map, string table etc
    const TRect& rect = m_WindowArea.GetRect();
    m_lastWindowWidth = rect.Right;
    m_lastWindowHeight = rect. Bottom;
    PostNotifyEvent(NULL, TZXC_AGD_NEW, 1, m_lastWindowWidth * 8, m_lastWindowHeight * 8);

    RefreshTiles();
    pgcEditors->Visible = true;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmGameEditor::Load(KXmlInfo& xmlInfo)
{
    KXmlInfo* GamesNode;
    if (xmlInfo.Find(GamesNode, "GameDesigner", 0))
    {
        KXmlInfo* Node;
        m_GameStyle = gsArcade;
        if (GamesNode->Find(Node, "GameStyle", 0)) m_GameStyle = (GameStyle)Node->GetInt();
        if (GamesNode->Find(Node, "ScorePanelShow", 0)) chkShowScorePanel->Checked = Node->GetBool();
        tabWelcome->TabVisible = false;
        tabWindowArea->TabVisible = true;
        tabKeys->TabVisible = true;
        tabJumpTable->TabVisible = true;
        tabSounds->TabVisible = true;
        m_Keys.Load(*GamesNode);
        m_WindowArea.Load(*GamesNode);
        m_JumpTable.Load(*GamesNode);
        m_CollisionDistance.Load(*GamesNode);
        m_Sounds.Load(*GamesNode);
        pgcEditors->ActivePage = tabWindowArea;
        m_PropertyEditor.SetActiveNode("Window Area");
    }
    else
    {
        New();
    }
    // create a new map, string table etc
    const TRect& rect = m_WindowArea.GetRect();
    m_lastWindowWidth = rect.Right;
    m_lastWindowHeight = rect. Bottom;
    PostNotifyEvent(NULL, TZXC_AGD_NEW, 1, m_lastWindowWidth * 8, m_lastWindowHeight * 8);

    RefreshTiles();
    pgcEditors->Visible = true;
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo* GamesNode;
    if (xmlInfo.Find(GamesNode, "GameDesigner", 0))
    {
        xmlInfo.Remove(GamesNode);
    }
    // create a new map editor node
    KXmlInfo gamesNode("GameDesigner");
    gamesNode.Add("GameStyle", m_GameStyle);
    gamesNode.Add("ScorePanelShow", chkShowScorePanel->Checked);
    // store the map details
    m_Keys.Save(gamesNode);
    m_WindowArea.Save(gamesNode);
    m_JumpTable.Save(gamesNode);
    m_CollisionDistance.Save(gamesNode);
    m_Sounds.Save(gamesNode);
    xmlInfo.Add(gamesNode);
    m_bSaved = true;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmGameEditor::IsDirty()
{
    bool isDirty = m_bSaved;
    isDirty |= m_Keys.IsDirty();
    isDirty |= m_WindowArea.IsDirty();
    isDirty |= m_JumpTable.IsDirty();
    isDirty |= m_CollisionDistance.IsDirty();
    return isDirty;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::Update()
{
    RefreshTiles();
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::tabWindowAreaResize(TObject *Sender)
{
    int widthRatio  = panLayoutContainer->Width  / 256;
    int heightRatio = panLayoutContainer->Height / 192;

    int ratio = std::min(widthRatio, heightRatio);

    m_WindowArea.SetRatio(ratio);

    panWindowArea->Width  = (256 * ratio) + 4;
    panWindowArea->Height = (192 * ratio) + 4;
    panWindowArea->Left   = (panLayoutContainer->Width  - panWindowArea->Width ) >> 1;
    panWindowArea->Top    = (panLayoutContainer->Height - panWindowArea->Height) >> 1;

    chkShowScorePanelClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::tabJumpTableResize(TObject *Sender)
{
    int widthRatio  = panJumpTableContainer->Width  / 256;
    int heightRatio = panJumpTableContainer->Height / 192;

    int ratio = std::min(widthRatio, heightRatio);

    m_JumpTable.SetRatio(ratio);

    panJumpTable->Width  = (256 * ratio) + 4;
    panJumpTable->Height = (192 * ratio) + 4;
    panJumpTable->Left   = (panJumpTableContainer->Width  - panJumpTable->Width ) >> 1;
    panJumpTable->Top    = (panJumpTableContainer->Height - panJumpTable->Height) >> 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::chkShowScorePanelClick(TObject *Sender)
{
    static bool refreshing = false;
    if (!refreshing)
    {
        refreshing = true;
        if (m_bScorePanelFound && chkShowScorePanel->Checked)
        {
            RefreshTiles();
            imgScorePanel->Left   = 0;
            imgScorePanel->Top    = 0;
            imgScorePanel->Width  = imgScorePanel->Picture->Bitmap->Width  * m_WindowArea.GetRatio();
            imgScorePanel->Height = imgScorePanel->Picture->Bitmap->Height * m_WindowArea.GetRatio();
        }
        imgScorePanel->Visible = chkShowScorePanel->Checked;
        refreshing = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::RefreshTiles()
{
    m_bScorePanelFound = false;
    m_vTileNames.clear();
    String sPlugin = "Screen";	// TODO: ?Previously "Tile"
    if (S_OK == PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_GET_IMAGE_NAMES, (LPDATA)&m_vTileNames, (DWORD)&sPlugin, -1))
    {
        int scorePanel = -1;
        for (unsigned int i = 0; i < m_vTileNames.size() && scorePanel == -1; i++)
        {
            if (m_vTileNames[i].LowerCase() == "scorepanel")
            {
                scorePanel = i;
                m_bScorePanelFound = true;
            }
        }
        if (scorePanel != -1)
        {
            // build the bitmap list
            m_vTileBitmaps.clear();
            for (unsigned int i = 0; i < m_vTileNames.size(); i++)
            {
                m_vTileBitmaps.push_back(new Graphics::TBitmap());
            }
            // grab the bitmaps
            PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_GET_IMAGE_BITMAPS, (LPDATA)&m_vTileBitmaps, (DWORD)&sPlugin, -1);
            imgScorePanel->Picture->Bitmap->Assign(m_vTileBitmaps[scorePanel]);
            imgScorePanel->Stretch = true;
            for (unsigned int i = 0; i < m_vTileNames.size(); i++)
            {
                delete m_vTileBitmaps[i];
            }
            m_vTileBitmaps.clear();
            m_vTileNames.clear();
        }
        else
        {
            imgScorePanel->Picture->Bitmap->Width = 0;
            imgScorePanel->Picture->Bitmap->Height = 0;
        }
    }
    chkShowScorePanelClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::SetupWelcome()
{
    rteWelcome->Lines->Clear();
    rteWelcome->SelAttributes->Size = 12;
    rteWelcome->SelText = "The Game Designer for ";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style << fsBold;
    rteWelcome->SelAttributes->Color = (TColor)0x00846142;
    rteWelcome->SelText = "TommyGun";
    rteWelcome->SelAttributes->Color = clBlack;
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style >> fsBold;
    rteWelcome->SelText = " allows you to create games using Jonathan Cauldwell's ";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style << fsBold;
    rteWelcome->SelText = "Arcade Game Designer, Platform Game Designer";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style >> fsBold;
    rteWelcome->SelText = " and ";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style << fsBold;
    rteWelcome->SelText = "Shoot'Em Up Designer";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style >> fsBold;
    rteWelcome->SelText = " though using a Windows editing environment. Using ";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style << fsBold;
    rteWelcome->SelAttributes->Color = (TColor)0x00846142;
    rteWelcome->SelText = "TommyGun";
    rteWelcome->SelAttributes->Color = clBlack;
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style >> fsBold;
    rteWelcome->SelText = " offers you more flexible art, map, sound and coding tools. It also allows you to use more memory in your games as you no longer need to include the designer editors in the original game.\n\n";
    rteWelcome->SelAttributes->Size = 12;
    rteWelcome->SelText = "Simply choose the style of game to create and then go about creating your game resources and script as per the normal ";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style << fsBold;
    rteWelcome->SelText = "AGD, PGD";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style >> fsBold;
    rteWelcome->SelText = " and ";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style << fsBold;
    rteWelcome->SelText = "SEUD";
    rteWelcome->SelAttributes->Style = rteWelcome->SelAttributes->Style >> fsBold;
    rteWelcome->SelText = " tools.";
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::btnArcadeClick(TObject *Sender)
{
    m_GameStyle = gsArcade;
    m_bSaved = false;
    tabWelcome->TabVisible = false;
    tabWindowArea->TabVisible = true;
    tabKeys->TabVisible = true;
    tabJumpTable->TabVisible = true;
    tabSounds->TabVisible = true;
    pgcEditors->ActivePage = tabWindowArea;
    // todo: messages
    //      code editor     - load agd file
    //      image editor    - create default sprites
    //                        create default tiles
    //      map editor      - create map
    //                        AxB screens of NxM size
    //      string editor   - create string table
    
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::btnPlatformClick(TObject *Sender)
{
    m_GameStyle = gsPlatform;
    m_bSaved = false;
    tabWelcome->TabVisible = false;
    tabWindowArea->TabVisible = true;
    tabKeys->TabVisible = true;
    tabJumpTable->TabVisible = true;
    tabSounds->TabVisible = true;
    pgcEditors->ActivePage = tabWindowArea;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::btnShootemUpClick(TObject *Sender)
{
    m_GameStyle = gsShootEmUp;
    m_bSaved = false;
    tabWelcome->TabVisible = false;
    tabWindowArea->TabVisible = true;
    tabKeys->TabVisible = true;
    tabJumpTable->TabVisible = true;
    tabSounds->TabVisible = true;
    pgcEditors->ActivePage = tabWindowArea;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::imgWindowMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    POINT pt;
    if (GetCursorPos(&pt))
    {
        m_WindowArea.MouseDown(Shift, pt.x, pt.y);
    }
    tmrUpdate->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::imgWindowMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    POINT pt;
    if (GetCursorPos(&pt))
    {
        m_WindowArea.MouseMove(Shift, pt.x, pt.y, X, Y);
        btnUpdate->Enabled = m_WindowArea.IsResized(m_lastWindowWidth, m_lastWindowHeight);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::imgWindowMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    POINT pt;
    if (GetCursorPos(&pt))
    {
        m_WindowArea.MouseUp(Shift, pt.x, pt.y);
    }
    tmrUpdate->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::imgJumpTableMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_JumpTable.MouseDown(Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::imgJumpTableMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    m_JumpTable.MouseMove(Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    m_JumpTable.MouseWheel(WheelDelta);
    Handled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::btnResetClick(TObject *Sender)
{
    int iAnswer;
    Message(mbtQuestion,
        "Reset Jump Table",
        "Would you like to Reset the Jump table to the defaults?",
        "Resetting the Jump table will lose any work you have already made.\n\n"\
        "Yes\tTo Reset the table\nNo\tTo keep your current table",
        "No", "Yes", "",
        iAnswer);
    if (iAnswer == 1)
    {
        m_JumpTable.ResetDefaults();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::btnUpdateClick(TObject *Sender)
{
    int iAnswer;
    Message
    (
        mbtWarning,
        "Would you like to resize the map window?",
        "The Window area has being resized and the map needs to be updated",
		"The Window area has being changed and resizing the map window to match will update all the tiles and sprites on the map.\n"
		"If any tiles or sprites are off screen they will be moved to inside the screen area.\n"
		"You may need to edit the changes to correct any issues with your screen.\n"
		"But this should be easier than clearing the map and you having to start again.\n"
		"\n\nAre you sure you would like to continue?\n\Click\n\tYes\tto Resize and UPDATE the map\n\tNo\tto keep the current window size and map contents",
        "No",
        "Yes",
        "",
        iAnswer
    );
    if (iAnswer == 1)
    {
        const TRect& rect = m_WindowArea.GetRect();
        m_lastWindowWidth = rect.Right;
        m_lastWindowHeight = rect. Bottom;
        PostNotifyEvent(NULL, TZXC_AGD_NEW, 2, m_lastWindowWidth * 8, m_lastWindowHeight * 8);
    }
    else
    {
        m_WindowArea.SizeWindow(m_lastWindowWidth, m_lastWindowHeight);
    }
    btnUpdate->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::tvwPropertyViewChange(TObject *Sender, TTreeNode *Node)
{
    m_PropertyEditor.OnChange(Node);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::vlePropertyEditorSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
    m_PropertyEditor.OnSelect(ARow-1);
    CanSelect = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::vlePropertyEditorKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == 13)
    {
        m_PropertyEditor.OnItemChanged();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::vlePropertyEditorExit(TObject *Sender)
{
    m_PropertyEditor.OnItemExit();
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::vlePropertyEditorSetEditText(TObject *Sender, int ACol, int ARow, const AnsiString Value)
{
    m_PropertyEditor.SetItemText(ARow-1, Value);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::pgcEditorsChange(TObject *Sender)
{
    m_PropertyEditor.SetActiveNode(pgcEditors->ActivePage->Caption);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::tmrUpdateTimer(TObject *Sender)
{
    RefreshTiles();
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::tabSoundsResize(TObject *Sender)
{
    panLeft->Width = (panSounds->Width - panCenter->Width) / 2;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::UpdateSndButtons()
{
    cmdSndAdd->Enabled = lstAvailableSfx->Selected != NULL;
    cmdSndRemove->Enabled = lstGameSfx->Selected != NULL;
    cmdSndUp->Enabled = lstGameSfx->Selected && lstGameSfx->Selected->Index > 0;
    cmdSndDown->Enabled = lstGameSfx->Selected && lstGameSfx->Selected->Index < lstGameSfx->Items->Count - 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::lstAvailableSfxSelectItem(TObject *Sender, TListItem *Item, bool Selected)
{
    UpdateSndButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::lstGameSfxSelectItem(TObject *Sender, TListItem *Item, bool Selected)
{
    UpdateSndButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::cmdSndAddClick(TObject *Sender)
{
    m_Sounds.Add();
    UpdateSndButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::cmdSndRemoveClick(TObject *Sender)
{
    m_Sounds.Remove();
    UpdateSndButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::cmdSndUpClick(TObject *Sender)
{
    m_Sounds.Up();
    UpdateSndButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmGameEditor::cmdSndDownClick(TObject *Sender)
{
    m_Sounds.Down();
    UpdateSndButtons();
}
//---------------------------------------------------------------------------

