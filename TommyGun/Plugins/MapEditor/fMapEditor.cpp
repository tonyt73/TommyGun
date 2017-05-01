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
#pragma link "KSlider"
#pragma link "KSpinEdit"
//-- VCL FORM OBJECT --------------------------------------------------------
TfrmMapEditor *frmMapEditor;
const String g_sInvalidChars = "\\ / : * ? \" < > | & ^\n\n";
const String g_sBlank        = "";
#define TILE_BUTTONS 6
TToolButton* DrawModes[TILE_BUTTONS];
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the class and reset some member variables
 * @param   Owner the VCL owner of the form
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @date    Modified 3 May 2002 by Tony Thompson
 * @remarks Copyright KiwiWare 2001
 */
//---------------------------------------------------------------------------
__fastcall TfrmMapEditor::TfrmMapEditor(TComponent* Owner)
    : TForm(Owner),
      m_bInitialized(false),
      m_bSaved(false),
      m_bImageChanged(false),
      m_PluginHandle(NULL),
      m_mnuMap(NULL)
{
    RL_METHOD
    m_MapEditor.SetMap(&m_Map);
    m_MapEditor.SetManagers(&m_TileManager, &m_SpriteManager, &m_ObjectManager);
    m_MapEditor.SetScreenGrid(16, 16);
    m_MapEditor.SetScreenGap(0);
    m_MapEditor.SetScreenScale(1);
    m_MapEditor.SetMapScale(100);
    m_MapEditor.SetScreenSize(256, 192);
    m_MapEditor.SetGridInfo(true, 8, 8);
    m_MapEditor.SetBackgroundColor(clBlack);
    m_ObjectManager.Init(imgObjects);
    m_SpriteManager.Init(imgSprites);
    m_TileBrowser.Setup(panMapBitmapPanels, stsMapBitmapsStatus, &m_TileManager);
    m_SpriteBrowser.Setup(panMapSpritePanels, stsMapSpriteStatus, &m_SpriteManager);
    m_ObjectBrowser.Setup(lstObjects, stsMapObjectStatus, &m_ObjectManager);
    m_MapEditor.Mode(moSelectTile);
}
//---------------------------------------------------------------------------
// Destructor
/**
 * @brief   Frees allocated resources
 * @author  Tony Thompson
 * @date    Created 10 March 2003 by Tony Thompson
 * @remarks Copyright KiwiWare 2003
 */
//---------------------------------------------------------------------------
__fastcall TfrmMapEditor::~TfrmMapEditor()
{
    RL_METHOD
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::FormCreate(TObject *Sender)
{
    m_MapEditor.SetCanvas(imgTiles, imgLayout);
    m_MapEditor.Update();
    m_ScorePanel.Setup(imgTiles);
    pgcBrowsers->DoubleBuffered = true;
    m_LastRadioButton = radMapEditorMapLayoutScreenScale100;
    MenusAdd();
    DrawModes[0] = tbnMapTileFree;
    DrawModes[1] = tbnMapTileLine;
    //DrawModes[2] = tbnMapTileDropper;
    DrawModes[2] = tbnMapTileRect;
    DrawModes[3] = tbnMapTileRectFill;
    DrawModes[4] = tbnMapTileCircle;
    DrawModes[5] = tbnMapTileCircleFill;
    //DrawModes[6] = tbnMapComment;
    UpdateControlStates();
    UpdateStartScreen();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cbrMapEditorDblClick(TObject *Sender)
{
    tbrMapTools->Visible    = !tbrMapTools->Visible;
    m_MapTools->Checked     =  tbrMapTools->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cmdTileMinimizeClick(TObject *Sender)
{
    if (0 != sbxTiles->Height && 0 != sbxScreens->Height)
    {
        m_iWindowRestore    = sbxTiles->Height;
    }
    sbxTiles->Height        = 0;
    cmdTileMinimize->Enabled= false;
    cmdTileRestore->Enabled = true;
    cmdTileMaximize->Enabled= true;
    cmdMapMinimize->Enabled = true;
    cmdMapRestore->Enabled  = true;
    cmdMapMaximize->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cmdTileRestoreClick(TObject *Sender)
{
    sbxTiles->Height        = m_iWindowRestore;
    cmdTileMinimize->Enabled= true;
    cmdTileRestore->Enabled = false;
    cmdTileMaximize->Enabled= true;
    cmdMapMinimize->Enabled = true;
    cmdMapRestore->Enabled  = false;
    cmdMapMaximize->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cmdTileMaximizeClick(TObject *Sender)
{
    if (0 != sbxTiles->Height && 0 != sbxScreens->Height)
    {
        m_iWindowRestore    = sbxTiles->Height;
    }
    sbxTiles->Height        = panEditor->Height - panMapTiles->Height - panMapMap->Height - 6;
    cmdTileMinimize->Enabled= true;
    cmdTileRestore->Enabled = true;
    cmdTileMaximize->Enabled= false;
    cmdMapMinimize->Enabled = false;
    cmdMapRestore->Enabled  = true;
    cmdMapMaximize->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::splEditorsMoved(TObject *Sender)
{
    m_iWindowRestore        = sbxTiles->Height;
    cmdTileMinimize->Enabled= true;
    cmdTileRestore->Enabled = false;
    cmdTileMaximize->Enabled= true;
    cmdMapMinimize->Enabled = true;
    cmdMapRestore->Enabled  = false;
    cmdMapMaximize->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cmdMapDecreaseClick(TObject *Sender)
{
    if (radMapEditorMapLayoutScreenScale25->Checked)    radMapEditorMapLayoutScreenScale10->Checked = true;
    if (radMapEditorMapLayoutScreenScale50->Checked)    radMapEditorMapLayoutScreenScale25->Checked = true;
    if (radMapEditorMapLayoutScreenScale75->Checked)    radMapEditorMapLayoutScreenScale50->Checked = true;
    if (radMapEditorMapLayoutScreenScale100->Checked)   radMapEditorMapLayoutScreenScale75->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cmdMapIncreaseClick(TObject *Sender)
{
    if (radMapEditorMapLayoutScreenScale75->Checked)    radMapEditorMapLayoutScreenScale100->Checked = true;
    if (radMapEditorMapLayoutScreenScale50->Checked)    radMapEditorMapLayoutScreenScale75->Checked = true;
    if (radMapEditorMapLayoutScreenScale25->Checked)    radMapEditorMapLayoutScreenScale50->Checked = true;
    if (radMapEditorMapLayoutScreenScale10->Checked)    radMapEditorMapLayoutScreenScale25->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::chkMapEditorScreenLayoutTilingDoNotIntersectClick(TObject *Sender)
{
    tbnMapAllowIntersections->Down = chkMapEditorScreenLayoutTilingDoNotIntersect->Checked;
    m_MapEditor.IntersectionsAllowed(tbnMapAllowIntersections->Down);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::chkMapEditorScreenLayoutTilingOverwriteOverlapClick(TObject *Sender)
{
    tbnOverwriteTiles->Down = chkMapEditorScreenLayoutTilingOverwriteOverlap->Checked;
    m_MapEditor.OverwriteOverlaps(tbnOverwriteTiles->Down);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapSnapToGridClick(TObject *Sender)
{
    chkMapEditorScreenLayoutTilingSnapToGrid->Checked = tbnMapSnapToGrid->Down;
    slrMapEditorScreenLayoutTilingWidth->Position     = edtMapEditorScreenLayoutTilingWidth->Value;
    slrMapEditorScreenLayoutTilingHeight->Position    = edtMapEditorScreenLayoutTilingHeight->Value;
    chkMapEditorScreenLayoutTilingSnapToGridClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::chkMapEditorScreenLayoutTilingSnapToGridClick(TObject *Sender)
{
    tbnMapSnapToGrid->Down = chkMapEditorScreenLayoutTilingSnapToGrid->Checked;
    m_MapEditor.SetGridInfo(tbnMapSnapToGrid->Down, edtMapEditorScreenLayoutTilingWidth->Value, edtMapEditorScreenLayoutTilingHeight->Value);
    slrMapEditorScreenLayoutTilingWidth->Position  = edtMapEditorScreenLayoutTilingWidth->Value;
    slrMapEditorScreenLayoutTilingHeight->Position = edtMapEditorScreenLayoutTilingHeight->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapAllowIntersectionsClick(TObject *Sender)
{
    chkMapEditorScreenLayoutTilingDoNotIntersect->Checked = tbnMapAllowIntersections->Down;
    chkMapEditorScreenLayoutTilingDoNotIntersectClick(NULL);
    //if (tbnMapAllowIntersections->Down)
    {
        //tbnOverwriteTiles->Down = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnOverwriteTilesClick(TObject *Sender)
{
    chkMapEditorScreenLayoutTilingOverwriteOverlap->Checked = tbnOverwriteTiles;
    chkMapEditorScreenLayoutTilingOverwriteOverlapClick(NULL);
    if (tbnOverwriteTiles->Down)
    {
        //tbnMapAllowIntersections->Down = false;
        tbnMapAllowIntersectionsClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapScreenAddAllClick(TObject *Sender)
{
    while(-1 != m_MapEditor.AddScreen());
    m_MapEditor.Update();
    m_MapEditor.SetActiveScreen(0);
    //TODO: m_MemoryMap.Update();
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapScreenAddClick(TObject *Sender)
{
    m_MapEditor.SetActiveScreen(m_MapEditor.AddScreen());
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapScreenRemoveClick(TObject *Sender)
{
    m_MapEditor.RemoveScreen();
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapScreenCloneClick(TObject *Sender)
{
    m_MapEditor.CloneScreen();
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapTileSelectClick(TObject *Sender)
{
    m_MapEditor.Mode(moSelectTile);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapTilePlaceClick(TObject *Sender)
{
    TToolButton* Button = dynamic_cast<TToolButton*>(Sender);
    if (SAFE_PTR(Button))
    {
        m_MapEditor.Mode((eModes)(Button->Tag + moTileFree));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::imgLayoutMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (mbRight == Button)
    {
        imgLayout->Cursor = crSizeAll;
        m_iScrollX = X;
        m_iScrollY = Y;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::imgLayoutMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    SetFocus();
    if (true == Shift.Contains(ssRight))
    {
        // scroll the scroll box
        if (true == sbxScreens->HorzScrollBar->Visible)
        {
            sbxScreens->HorzScrollBar->Position = sbxScreens->HorzScrollBar->Position + ( m_iScrollX - X );
        }
        if (true == sbxScreens->VertScrollBar->Visible)
        {
            sbxScreens->VertScrollBar->Position = sbxScreens->VertScrollBar->Position + ( m_iScrollY - Y );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::imgLayoutMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    imgLayout->Cursor = crDefault;
    RefreshSpritesList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::imgTilesMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (mbRight == Button)
    {
        imgTiles->Cursor = crSizeAll;
        m_iScrollX = X;
        m_iScrollY = Y;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::imgTilesMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    SetFocus();
    float dx = 1.0f;
    float dy = 1.0f;
    m_TileManager.GetScalar(dx, dy);
    int iMagX = edtMapEditorScreenLayoutMagnificationSize->Value * dx;
    int iMagY = edtMapEditorScreenLayoutMagnificationSize->Value * dy;
    SetStatusSlot(m_PluginHandle, "P:[" + ZeroPadInt(X / iMagX, 3) + "," + ZeroPadInt(Y / iMagY, 3) + "]", 0);
    SetStatusSlot(m_PluginHandle, "G:[" + ZeroPadInt(X / iMagX / edtMapEditorScreenLayoutTilingWidth->Value, 2) + "," + ZeroPadInt(Y / iMagY / edtMapEditorScreenLayoutTilingHeight->Value, 2) + "]", 1);
    if (true == Shift.Contains(ssRight))
    {
        // scroll the scroll box
        if (true == sbxTiles->HorzScrollBar->Visible)
        {
            sbxTiles->HorzScrollBar->Position = sbxTiles->HorzScrollBar->Position + ( m_iScrollX - X );
        }
        if (true == sbxTiles->VertScrollBar->Visible)
        {
            sbxTiles->VertScrollBar->Position = sbxTiles->VertScrollBar->Position + ( m_iScrollY - Y );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::imgTilesMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    imgTiles->Cursor = crDefault;
    RefreshSpritesList();
    m_ObjectBrowser.Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cmdMapApplyChangesClick(TObject *Sender)
{
    m_MapEditor.SetScreenSize(edtMapScreenSizeWidth->Value, edtMapScreenSizeHeight->Value);
    m_MapEditor.SetScreenGrid(edtMapMapSizeScreensAcross->Value, edtMapMapSizeScreensDown->Value);
    UpdateScreenEditor();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::radMapEditorMapLayoutScreenScale100Click(TObject *Sender)
{
    TRadioButton* RadioButton = dynamic_cast<TRadioButton*>(Sender);
    if (true == SAFE_PTR(RadioButton) && m_LastRadioButton != RadioButton)
    {
        m_LastRadioButton = RadioButton;
        m_MapEditor.SetMapScale(RadioButton->Tag);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::edtMapEditorMapLayoutGapSizeChange(TObject *Sender)
{
    m_MapEditor.SetScreenGap(edtMapEditorMapLayoutGapSize->Value);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::edtMapEditorScreenLayoutMagnificationSizeChange(TObject *Sender)
{
    slrMapEditorScreenLayoutMagnificationSize->Position = edtMapEditorScreenLayoutMagnificationSize->Value;
    m_MapEditor.SetScreenScale(edtMapEditorScreenLayoutMagnificationSize->Value);
    UpdateScreenEditor();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::TileRemove(const String& sName)
{
    m_TileManager.Remove(sName);
    m_Map.RemoveTile(sName);
    m_TileBrowser.Zoom(spnTilesZoom->Value);
    m_ScorePanel.Refresh();
    m_ScorePanel.Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::TileRename(const String& sOldName, const String& sNewName)
{
    m_TileManager.Rename(sOldName, sNewName);
    m_Map.RenameTile(sOldName, sNewName);
    m_TileBrowser.Zoom(spnTilesZoom->Value);
    m_ScorePanel.Refresh();
    m_ScorePanel.Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::SpriteRemove(const String& sName)
{
    m_SpriteManager.Remove(sName);
    m_ObjectManager.Remove(sName);
    //m_Map.RemoveSprite(sName);
    //m_Map.RemoveObject(sName);
    m_SpriteBrowser.Zoom(spnSpritesZoom->Value);
    m_ScorePanel.Refresh();
    m_ScorePanel.Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::SpriteRename(const String& sOldName, const String& sNewName)
{
    m_SpriteManager.Rename(sOldName, sNewName);
    m_ObjectManager.Rename(sOldName, sNewName);
    //m_Map.RenameSprite(sOldName, sNewName);
    //m_Map.RenameObject(sOldName, sNewName);
    m_SpriteBrowser.Zoom(spnSpritesZoom->Value);
    m_ScorePanel.Refresh();
    m_ScorePanel.Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::Save(KXmlInfo& xmlInfo, bool bCleanDirty)
{
    KXmlInfo* EditorNode;
    if (xmlInfo.Find(EditorNode, "MapEditor", 0))
    {
        xmlInfo.Remove(EditorNode);
    }

    KXmlInfo MapEditor("MapEditor");
    KXmlInfo Settings("Settings");
    KXmlInfo ScorePanel("ScorePanel");
    KXmlInfo ScreenLayout("ScreenLayout");
    KXmlInfo MapLayout("MapLayout");
    KXmlInfo StartScreen("StartScreen");

    ScorePanel.Add("Show", chkShowScorePanel->Checked);
    ScorePanel.Add("XOverlap", edtMapEditorXOverlap->Value);
    ScorePanel.Add("YOverlap", edtMapEditorYOverlap->Value);
    Settings.Add(ScorePanel);

    ScreenLayout.Add("DontIntersectTiles", chkMapEditorScreenLayoutTilingDoNotIntersect->Checked);
    ScreenLayout.Add("SnapToGrid", chkMapEditorScreenLayoutTilingSnapToGrid->Checked);
    ScreenLayout.Add("GridWidth", edtMapEditorScreenLayoutTilingWidth->Value);
    ScreenLayout.Add("GridHeight", edtMapEditorScreenLayoutTilingHeight->Value);
    ScreenLayout.Add("Magnification", edtMapEditorScreenLayoutMagnificationSize->Value);
    Settings.Add(ScreenLayout);

    StartScreen.Add("Screen", m_MapEditor.StartScreen);
    Settings.Add(StartScreen);

    MapLayout.Add("Scale", m_LastRadioButton->Tag);
    MapLayout.Add("Gap", edtMapEditorMapLayoutGapSize->Value);

    Settings.Add(MapLayout);
    MapEditor.Add(Settings);
    m_Map.Save(MapEditor, bCleanDirty);
    m_ObjectManager.Save(MapEditor);
    xmlInfo.Add(MapEditor);
}
//---------------------------------------------------------------------------
bool __fastcall TfrmMapEditor::Load(KXmlInfo& xmlInfo)
{
    bool bLoaded = false;
    KXmlInfo* EditorNode;
    KXmlInfo* ObjectsNode;
    if (xmlInfo.Find(EditorNode, "MapEditor", 0))
    {
        Clear();
        bLoaded = m_Map.Load(*EditorNode);
        bLoaded |= m_ObjectManager.Load(*EditorNode);

        KXmlInfo* Settings;
        if (EditorNode->Find(Settings, "Settings", 0))
        {
            KXmlInfo* Node;
            if (Settings->Find(Node, "ScorePanel", 0))
            {
                KXmlInfo* nShow;
                KXmlInfo* nOverlap;

                chkShowScorePanel->Checked = false;

                if (Node->Find(nShow, "Show", 0))       chkShowScorePanel->Checked = nShow->GetBool();
                if (Node->Find(nOverlap, "XOverlap"    , 0))    edtMapEditorXOverlap->Value = nOverlap->GetInt();
                if (Node->Find(nOverlap, "YOverlap"    , 0))    edtMapEditorYOverlap->Value = nOverlap->GetInt();
                m_ScorePanel.Enabled = chkShowScorePanel->Checked;
                m_MapEditor.SetScreenOffset(edtMapEditorXOverlap->Value, edtMapEditorYOverlap->Value);
            }
            if (Settings->Find(Node, "ScreenLayout", 0))
            {
                KXmlInfo* nIntersect;
                KXmlInfo* nSnapToGrid;
                KXmlInfo* nGridWidth;
                KXmlInfo* nGridHeight;
                KXmlInfo* nMagnification;

                chkMapEditorScreenLayoutTilingDoNotIntersect->Checked = true;
                chkMapEditorScreenLayoutTilingSnapToGrid->Checked = true;
                slrMapEditorScreenLayoutTilingWidth->Position = 8;
                slrMapEditorScreenLayoutTilingHeight->Position = 8;
                edtMapEditorScreenLayoutMagnificationSize->Value = 1;

                if (Node->Find(nIntersect    , "Intersect"    , 0)) chkMapEditorScreenLayoutTilingDoNotIntersect->Checked = nIntersect->GetBool();
                if (Node->Find(nSnapToGrid   , "SnapToGrid"   , 0)) chkMapEditorScreenLayoutTilingSnapToGrid->Checked = nSnapToGrid->GetBool();
                if (Node->Find(nGridWidth    , "GridWidth"    , 0)) slrMapEditorScreenLayoutTilingWidth->Position = nGridWidth->GetInt();
                if (Node->Find(nGridHeight   , "GridHeight"   , 0)) slrMapEditorScreenLayoutTilingHeight->Position = nGridHeight->GetInt();
                if (Node->Find(nMagnification, "Magnification", 0)) edtMapEditorScreenLayoutMagnificationSize->Value = nMagnification->GetInt();
            }
            if (Settings->Find(Node, "MapLayout", 0))
            {
                KXmlInfo* nScale;
                KXmlInfo* nGap;
                edtMapEditorMapLayoutGapSize->Value = 0;
                radMapEditorMapLayoutScreenScale100->Checked = true;
                if (Node->Find(nGap, "Gap", 0)) edtMapEditorMapLayoutGapSize->Value = nGap->GetInt();
                if (Node->Find(nScale, "Scale", 0))
                {
                    int iScale = nScale->GetInt();
                    if (iScale == 75)
                        radMapEditorMapLayoutScreenScale75->Checked = true;
                    else if (iScale == 50)
                        radMapEditorMapLayoutScreenScale50->Checked = true;
                    else if (iScale == 25)
                        radMapEditorMapLayoutScreenScale25->Checked = true;
                    else if (iScale == 10)
                        radMapEditorMapLayoutScreenScale10->Checked = true;
                }
            }
            if (Settings->Find(Node, "StartScreen", 0))
            {
                m_MapEditor.StartScreen = Node->GetNode("Screen")->GetInt();
                UpdateStartScreen();
            }
        }
        m_MapEditor.SetActiveScreen(0);
        RefreshView();
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::Clear(void)
{
    m_Map.Clear();
    m_MapEditor.Clear();
    m_TileManager.Clear();
    m_TileBrowser.Clear();
    m_SpriteManager.Clear();
    m_SpriteBrowser.Clear();
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::RefreshView(void)
{
    m_TileManager.Refresh();
    m_TileBrowser.Zoom(spnSpritesZoom->Value);
    m_SpriteManager.Refresh();
    m_SpriteBrowser.Zoom(spnSpritesZoom->Value);
    m_ObjectBrowser.Refresh();
    RefreshSpritesList();
    m_MapEditor.Invalidate();
    m_MapEditor.Update();
    edtMapScreenSizeWidth->Value      = m_Map.ScreenWidth;
    edtMapScreenSizeHeight->Value     = m_Map.ScreenHeight;
    edtMapMapSizeScreensAcross->Value = m_Map.ScreensAcross;
    edtMapMapSizeScreensDown->Value   = m_Map.ScreensDown;
    UpdateButtons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::edtMapScreenSizeWidthChange(TObject *Sender)
{
    slrMapScreenSizeWidth->Position  = edtMapScreenSizeWidth->Value;
    slrMapScreenSizeHeight->Position = edtMapScreenSizeHeight->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::slrMapScreenSizeHeightChange(TObject *Sender)
{
    edtMapScreenSizeWidth->Value = slrMapScreenSizeWidth->Position;
    edtMapScreenSizeHeight->Value = slrMapScreenSizeHeight->Position;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::edtMapMapSizeScreensAcrossChange(TObject *Sender)
{
    slrMapMapSizeScreensAcross->Position = edtMapMapSizeScreensAcross->Value;
    slrMapMapSizeScreensDown->Position   = edtMapMapSizeScreensDown->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cmdTileDecreaseClick(TObject *Sender)
{
    edtMapEditorScreenLayoutMagnificationSize->Value = edtMapEditorScreenLayoutMagnificationSize->Value - 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cmdTileIncreaseClick(TObject *Sender)
{
    edtMapEditorScreenLayoutMagnificationSize->Value = edtMapEditorScreenLayoutMagnificationSize->Value + 1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::chkShowScorePanelClick(TObject *Sender)
{
    UpdateScreenEditor();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnShowGridClick(TObject *Sender)
{
    m_MapEditor.ShowGrid(tbnShowGrid->Down);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::edtMapEditorScreenLayoutTilingWidthChange(TObject *Sender)
{
    slrMapEditorScreenLayoutTilingWidth->Position = edtMapEditorScreenLayoutTilingWidth->Value;
    slrMapEditorScreenLayoutTilingHeight->Position = edtMapEditorScreenLayoutTilingHeight->Value;
    m_MapEditor.SetGridInfo(tbnMapSnapToGrid->Down, edtMapEditorScreenLayoutTilingWidth->Value, edtMapEditorScreenLayoutTilingHeight->Value);
    if (tbnShowGrid->Down)
    {
        m_MapEditor.UpdateScreenWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnBringToFrontClick(TObject *Sender)
{
    m_MapEditor.BringToFront();
    m_MapEditor.UpdateScreenWindow();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnSendToBackClick(TObject *Sender)
{
    m_MapEditor.SendToBack();
    m_MapEditor.UpdateScreenWindow();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::UpdateButtons(void)
{
    bool bFull = (m_Map.Screens() == (unsigned int)(m_Map.ScreensAcross * m_Map.ScreensDown));

    tbnMapScreenAddAll->Enabled = !bFull;
    tbnMapScreenAdd->Enabled = !bFull;
    tbnMapScreenClone->Enabled = !bFull;
    tbnMapScreenRemove->Enabled = m_Map.Screens() != 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::chkMergeDuplicatesClick(TObject *Sender)
{
    m_Map.MergeDupScreens = chkMergeDuplicates->Checked;
    regScorpio->Write("MapEditor", "MergeDupScreens", chkMergeDuplicates->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::spnTilesZoomChange(TObject *Sender)
{
    m_TileBrowser.Zoom(spnTilesZoom->Value);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuSelectModeClick(TObject *Sender)
{
    tbnMapTileSelect->Down = true;
    tbnMapTileSelectClick(tbnMapTileSelect);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuPlaceModeClick(TObject *Sender)
{
    for (int i = 0; i < TILE_BUTTONS; i++)
    {
        if (DrawModes[i]->Down)
        {
            DrawModes[(i+1) % TILE_BUTTONS]->Down = true;
            tbnMapTilePlaceClick(DrawModes[(i+1) % TILE_BUTTONS]);
            return;
        }
    }
    m_MapEditor.Mode(moTileFree);
    DrawModes[0]->Down = true;
    tbnMapTilePlaceClick(DrawModes[0]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuPreviousTileToolClick(TObject *Sender)
{
    for (int i = 0; i < TILE_BUTTONS; i++)
    {
        if (DrawModes[i]->Down)
        {
            DrawModes[(TILE_BUTTONS + (i-1)) % TILE_BUTTONS]->Down = true;
            tbnMapTilePlaceClick(DrawModes[(TILE_BUTTONS + (i-1)) % TILE_BUTTONS]);
            return;
        }
    }
    m_MapEditor.Mode(moTileFree);
    DrawModes[0]->Down = true;
    tbnMapTilePlaceClick(DrawModes[0]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuSnaptoGridToggleClick(TObject *Sender)
{
    tbnMapSnapToGrid->Down = !tbnMapSnapToGrid->Down;
    tbnMapSnapToGridClick(tbnMapSnapToGrid);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuAllowIntersectClick(TObject *Sender)
{
    tbnMapAllowIntersections->Down = !tbnMapAllowIntersections->Down;
    tbnMapAllowIntersectionsClick(tbnMapAllowIntersections);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuToggleGridClick(TObject *Sender)
{
    tbnShowGrid->Down = !tbnShowGrid->Down;
    tbnShowGridClick(tbnShowGrid);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuSaveMapBitmapClick(TObject *Sender)
{
    String sFolder;
    PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);

    dlgSave->InitialDir = sFolder;
    dlgSave->FileName = "Map.bmp";
    if (dlgSave->Execute())
    {
        m_MapEditor.SaveBitmap(dlgSave->FileName); 
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapCommentShowHideClick(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnMapCommentAddClick(TObject *Sender)
{
    //
    m_MapEditor.CommentAdd(TRect(50, 50, 100, 80));
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::popToggleCommentsClick(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::slrMapMapSizeScreensAcrossChange(TObject *Sender)
{
    edtMapMapSizeScreensAcross->Value = slrMapMapSizeScreensAcross->Position;
    edtMapMapSizeScreensDown->Value   = slrMapMapSizeScreensDown->Position;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::spnSpritesZoomChanged(TObject *Sender)
{
    m_SpriteBrowser.Zoom(spnSpritesZoom->Value);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::edtMapEditorXOverlapChanged(TObject *Sender)
{
    m_MapEditor.SetScreenOffset(edtMapEditorXOverlap->Value, edtMapEditorYOverlap->Value);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::edtMapEditorYOverlapChanged(TObject *Sender)
{
    m_MapEditor.SetScreenOffset(edtMapEditorXOverlap->Value, edtMapEditorYOverlap->Value);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::UpdateScreenEditor()
{
    static bool in = false;
    if (!in)
    {
        in = true;
        m_ScorePanel.Enabled = chkShowScorePanel->Checked;
        if (chkShowScorePanel->Checked)
        {
            m_MapEditor.SetScreenOffset(edtMapEditorXOverlap->Value, edtMapEditorYOverlap->Value);
            imgTiles->Width = 256 * edtMapEditorScreenLayoutMagnificationSize->Value;
            imgTiles->Height = 192 * edtMapEditorScreenLayoutMagnificationSize->Value;
        }
        else
        {
            m_MapEditor.SetScreenOffset(0, 0);
            imgTiles->Width = edtMapScreenSizeWidth->Value * edtMapEditorScreenLayoutMagnificationSize->Value;
            imgTiles->Height = edtMapScreenSizeHeight->Value * edtMapEditorScreenLayoutMagnificationSize->Value;
        }
        imgTiles->Picture->Bitmap->Width = imgTiles->Width;
        imgTiles->Picture->Bitmap->Height = imgTiles->Height;
        edtMapEditorScreenLayoutMagnificationSizeChange(NULL);
        m_ScorePanel.Refresh();
        m_ScorePanel.Update();
        m_MapEditor.UpdateScreenWindow();
        m_MapEditor.Update();
        UpdateStartScreen();
        in = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnSpriteAddClick(TObject *Sender)
{
    if (m_SpriteManager.Selected != "")
    {
        m_Map.AddScreenSprite(m_MapEditor.ActiveScreen, m_SpriteManager.Selected);
        RefreshSpritesList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnSpriteRemoveClick(TObject *Sender)
{
    bool removed = false;
    for (int i = lstSprites->Items->Count - 1; i >= 0; --i)
    {
        if (lstSprites->Items->Item[i]->Selected)
        {
            m_Map.RemoveScreenSprite(m_MapEditor.ActiveScreen, i);
            removed = true;
        }
    }
    if (removed)
    {
        RefreshSpritesList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnSpriteAssignClick(TObject *Sender)
{
    if (m_SpriteManager.Selected != "")
    {
        for (int i = lstSprites->Items->Count - 1; i >= 0; --i)
        {
            if (lstSprites->Items->Item[i]->Selected)
            {
                m_Map.SetScreenSpriteImage(m_MapEditor.ActiveScreen, i, m_SpriteManager.Selected);
            }
        }
        RefreshSpritesList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnSpriteTypeIncClick(TObject *Sender)
{
    bool changed = false;
    for (int i = lstSprites->Items->Count - 1; i >= 0; --i)
    {
        if (lstSprites->Items->Item[i]->Selected)
        {
            TSprite sprite;
            m_Map.GetScreenSprite(m_MapEditor.ActiveScreen, i, sprite);
            m_Map.SetScreenSpriteType(m_MapEditor.ActiveScreen, i, std::min(sprite.m_iType + 1, 15));
            changed = true;
        }
    }
    if (changed)
    {
        RefreshSpritesList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::tbnSpriteTypeDecClick(TObject *Sender)
{
    bool changed = false;
    for (int i = lstSprites->Items->Count - 1; i >= 0; --i)
    {
        if (lstSprites->Items->Item[i]->Selected)
        {
            TSprite sprite;
            m_Map.GetScreenSprite(m_MapEditor.ActiveScreen, i, sprite);
            m_Map.SetScreenSpriteType(m_MapEditor.ActiveScreen, i, std::max(sprite.m_iType - 1, 0));
            changed = true;
        }
    }
    if (changed)
    {
        RefreshSpritesList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::RefreshSpritesList()
{
    int screen = m_MapEditor.ActiveScreen;
    int sprites = m_Map.GetScreenSprites(screen);

    bool keepSelections = sprites == lstSprites->Items->Count;

    std::vector<int> selections;

    if (keepSelections)
    {
        for (int i = 0; i < lstSprites->Items->Count; i++)
        {
            if (lstSprites->Items->Item[i]->Selected)
            {
                selections.push_back(i);
            }
        }
    }

    lstSprites->Items->Clear();

    for (int i = 0; i < sprites; i++)
    {
        TSprite sprite;
        m_Map.GetScreenSprite(screen, i, sprite);
        TListItem* item;
        item = lstSprites->Items->Add();
        item->Caption = sprite.m_sSprite;
        item->ImageIndex = m_SpriteManager.IndexOf(sprite.m_sSprite);
        item->SubItems->Add(IntToStr(sprite.m_iType));
        item->SubItems->Add(IntToStr(sprite.m_iLeft));
        item->SubItems->Add(IntToStr(sprite.m_iTop));

    }

    if (keepSelections)
    {
        for (unsigned int i = 0; i < selections.size(); ++i)
        {
            lstSprites->Items->Item[selections[i]]->Selected = true;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuAssignInventoryClick(TObject *Sender)
{
    for (int i = 0; i < lstObjects->Items->Count; ++i)
    {
        if (lstObjects->Items->Item[i]->Selected)
        {
            m_ObjectManager.SetObjectScreen(i, 254);
        }
    }
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuAssignScreenClick(TObject *Sender)
{
    for (int i = 0; i < lstObjects->Items->Count; ++i)
    {
        if (lstObjects->Items->Item[i]->Selected)
        {
            m_ObjectManager.SetObjectScreen(i, m_MapEditor.ActiveScreen);
        }
    }
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::mnuAssignNoScreenClick(TObject *Sender)
{
    for (int i = 0; i < lstObjects->Items->Count; ++i)
    {
        if (lstObjects->Items->Item[i]->Selected)
        {
            m_ObjectManager.SetObjectScreen(i, 255);
        }
    }
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::pgcBrowsersChange(TObject *Sender)
{
    UpdateControlStates();
    if (pgcBrowsers->ActivePage == tabMapSprites)
    {
        tbnMapTileSelect->Down = true;
        m_MapEditor.Mode(moSelectSprite);
    }
    else if (pgcBrowsers->ActivePage == tabMapObjects)
    {
        tbnMapTileSelect->Down = true;
        m_MapEditor.Mode(moSelectObject);
    }
    else //if (pgcBrowsers->ActivePage == tabMapTiles)
    {
        tbnMapTileSelect->Down = true;
        m_MapEditor.Mode(moSelectTile);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::UpdateControlStates()
{
    bool enabled = pgcBrowsers->ActivePage == tabMapTiles;

    tbnMapTileFree->Enabled = enabled;
    tbnMapTileLine->Enabled = enabled;
    tbnMapTileLine->Enabled = enabled;
    tbnMapTileRect->Enabled = enabled;
    tbnMapTileRectFill->Enabled = enabled;
    tbnMapTileCircle->Enabled = enabled;
    tbnMapTileCircleFill->Enabled = enabled;

    if (!enabled)
    {
        tbnMapTileSelect->Down = true;
        tbnMapTileSelectClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::UpdateStartScreen()
{
    if (m_MapEditor.StartScreen != -1)
    {
        lblStartScreen->Caption = "Start Screen is " + IntToStr(m_MapEditor.StartScreen);
    }
    else
    {
        lblStartScreen->Caption = "Start Screen is not set";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::cmdStartScreenClick(TObject *Sender)
{
    m_MapEditor.SetStartScreen();
    UpdateStartScreen();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMapEditor::pgcBrowsersDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    static Graphics::TBitmap* bm = NULL; 
    Control->Canvas->Brush->Color = clWhite;
    Control->Canvas->FillRect(Rect);
    TTabSheet* sheet = pgcBrowsers->Pages[TabIndex];
    int cw = Control->Canvas->TextWidth(sheet->Caption) / 2;
    int ch = Control->Canvas->TextHeight(sheet->Caption) / 2;
    int rl = Rect.Left;
    int rt = Rect.Top;
    int cx = Rect.Width() / 2;
    int cy = Rect.Height() / 2;
    Control->Canvas->Font->Color = clBlack;
    Control->Canvas->Font->Height = 15;
    Control->Canvas->Font->Style = Active ? TFontStyles() << fsBold : TFontStyles();
    Control->Canvas->TextRect(Rect, rl + 10 + cx - cw, rt + cy - ch, sheet->Caption);
    pgcBrowsers->Images->Draw(Control->Canvas, rl + 10 + cx - cw - 20, rt + cy - 8, sheet->ImageIndex, true);

    if (Active)
    {
        if (bm == NULL)
        {
            bm = new Graphics::TBitmap();
            bm->Width = 1;
            bm->Height = 1;
            bm->PixelFormat = pf32bit;
            bm->Canvas->Pixels[0][0] = (TColor)0x00846142;
            //bm->Width = 4;
            //bm->Canvas->Pixels[0][0] = clRed;
            //bm->Canvas->Pixels[1][0] = clYellow;
            //bm->Canvas->Pixels[2][0] = clLime;
            //bm->Canvas->Pixels[3][0] = clAqua;
        }
        TRect tr(Rect.left, Rect.top, Rect.right, Rect.top + 5);
        Control->Canvas->StretchDraw(tr, bm);
        SAFE_DELETE(bm);
    }
}
//---------------------------------------------------------------------------

