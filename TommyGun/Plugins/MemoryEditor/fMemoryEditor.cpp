#pragma link "KSpinEdit"
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
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
///#pragma link "TScrollBox"
#pragma link "KSlider"
//-- VCL FORM OBJECT --------------------------------------------------------
TfrmMemoryEditor *frmMemoryEditor = NULL;
const String g_sInvalidChars = "\\ / : * ? \" < > | & ^\n\n";
const String g_sBlank        = "";
//---------------------------------------------------------------------------
const TColor g_MemoryColors[] =
{
            clFuchsia,  // memCustom
            clGray,     // memROM
            clSilver,   // memSystem
    (TColor)0x00E1FFFF, // memScreen
            clMaroon,   // memStack
            clOlive,    // memSpriteTable
            clYellow,   // memSprites
            clNavy,     // memTileTable
            clBlue,     // memTiles
            clAqua,     // memCharacterSets
            clGreen,    // memMapTable
            clLime,     // memMapScreens
            clBlack     // memLast
};
//---------------------------------------------------------------------------
const String g_sTypes[] =
{
    "Custom",
    "ROM",
    "System",
    "Screen",
    "Machine Stack",
    "Sprite Table",
    "Sprites",
    "Tile Table",
    "Tiles",
    "Character Set",
    "Map Table",
    "Map Screens",
    "Last",
};
//---------------------------------------------------------------------------
const int g_iMemorySize = 65536;
const int g_iBarHeight  = 48;
const int g_iMapHeader  = 16;
const int g_iMapHeight  = 64;
const int g_iTextOffset = 15;
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
__fastcall TfrmMemoryEditor::TfrmMemoryEditor(TComponent* Owner)
    : TForm(Owner),
      m_bInitialized(false),
      m_bSaved(false),
      m_iBlockSize(16384),
      m_iGameAddress(32768),
      m_PluginHandle(NULL)
{
    RL_METHOD
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
__fastcall TfrmMemoryEditor::~TfrmMemoryEditor()
{
    RL_METHOD
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::FormCreate(TObject *Sender)
{
    pgcMemoryMap->DoubleBuffered = true;
    sbxMemoryMap->DoubleBuffered = true;
    panMemoryMap->DoubleBuffered = true;
    //imgMemoryMap->DoubleBuffered = true;
    imgMemoryMap->Picture->Bitmap->Canvas->Font->Name = "Tahoma";
    imgMemoryMap->Picture->Bitmap->Canvas->Font->Size = 8;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::Update(void)
{
    // calculate the number of blocks to draw
    unsigned int iBlocks = g_iMemorySize / m_iBlockSize;
    // draw the memory map on the image
    TCanvas* Canvas = imgMemoryMap->Picture->Bitmap->Canvas;
    imgMemoryMap->Height = ((g_iMapHeight + g_iMapHeader) * iBlocks) + g_iMapHeader;
    imgMemoryMap->Picture->Bitmap->Height = ((g_iMapHeight + g_iMapHeader) * iBlocks) + g_iMapHeader;
    // clear the image
    Canvas->Brush->Color = clWhite;
    Canvas->FillRect(imgMemoryMap->ClientRect);
    int iWidth = imgMemoryMap->ClientRect.Right - imgMemoryMap->ClientRect.Left - 8;
    // draw the major blocks and their address boundaries
    int iLeft  = 0;
    int iRight = m_iBlockSize - 1;
    for (unsigned int i = 0; i < iBlocks; ++i)
    {
        Canvas->Brush->Color = clWhite;
        String sHeaderL = IntToStr(iLeft);
        String sHeaderR = IntToStr(iRight);
        int iTextY = g_iMapHeader + (i * g_iMapHeight) - g_iTextOffset;
        Canvas->TextOut(4, iTextY, sHeaderL);
        Canvas->TextOut(imgMemoryMap->ClientRect.Right - 4 - Canvas->TextWidth(sHeaderR), iTextY, sHeaderR);
        TRect Rect(4, g_iMapHeader + (i * g_iMapHeight), 5 + iWidth, g_iMapHeader + (i * g_iMapHeight) + g_iBarHeight);
        Canvas->Brush->Color = clBlack;
        Canvas->FrameRect(Rect);
        iLeft  += m_iBlockSize;
        iRight += m_iBlockSize;
    }
    // update the lists
    m_MouseRects.clear();
    m_SystemObjects.clear();
    m_CustomObjects.clear();
    ZXMemoryObject* MemObj = NULL;
    int iSystem = 0;
    int iCustom = 0;
    for (unsigned int i = 0; i < MemoryObjects(); ++i)
    {
        MemObj = MemoryObject(i);
        if (true == SAFE_PTR(MemObj) && 0 < MemObj->iSize)
        {
            DrawMemoryObject(MemObj);
            if (memCustom == MemObj->eType)
            {
                if (iCustom < lstMemoryMapCustom->Items->Count)
                {
                    lstMemoryMapCustom->Items->Strings[iCustom] = MemObj->sName;
                }
                else
                {
                    lstMemoryMapCustom->Items->Add(MemObj->sName);
                }
                lstMemoryMapCustom->Checked[iCustom] = MemObj->bEnabled;
                m_CustomObjects.push_back(MemObj);
                iCustom++;
            }
            else
            {
                if (iSystem < lstMemoryMapSystem->Items->Count)
                {
                    lstMemoryMapSystem->Items->Strings[iSystem] = MemObj->sName;
                }
                else
                {
                    lstMemoryMapSystem->Items->Add(MemObj->sName);
                }
                lstMemoryMapSystem->ItemEnabled[iSystem] = MemObj->bMoveable;
                lstMemoryMapSystem->Checked[iSystem]     = MemObj->bEnabled;
                m_SystemObjects.push_back(MemObj);
                iSystem++;
            }
        }
    }
    // clear any unnecessary items
    while (iSystem < lstMemoryMapSystem->Items->Count)
    {
        lstMemoryMapSystem->Items->Delete(lstMemoryMapSystem->Items->Count - 1);        
    }
    while (iCustom < lstMemoryMapCustom->Items->Count)
    {
        lstMemoryMapCustom->Items->Delete(lstMemoryMapCustom->Items->Count - 1);        
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::DrawMemoryObject(ZXMemoryObject* MemoryObject)
{
    if (true == SAFE_PTR(MemoryObject) && MemoryObject->bEnabled)
    {
        TCanvas* Canvas = imgMemoryMap->Picture->Bitmap->Canvas;
        // set the brush color for the memory type
        Canvas->Brush->Color = g_MemoryColors[MemoryObject->eType];
        int iAddress = MemoryObject->iAddress;
        int iSize    = MemoryObject->iSize - 1;
        int iWidth   = imgMemoryMap->ClientRect.Right - imgMemoryMap->ClientRect.Left - 8;
        // what block are we starting on?
        unsigned int iBlockStart   =  iAddress           / m_iBlockSize;
        // what block are we finishing on?
        unsigned int iBlockFinish  = (iAddress + iSize)  / m_iBlockSize;
        // what is the offset into the start block
        unsigned int iOffsetStart  =  iAddress           % m_iBlockSize;
        // what is the offset into the finish block
        unsigned int iOffsetFinish = (iAddress + iSize)  % m_iBlockSize;
        // whats the offset as a percentage of the block
        for (unsigned int i = iBlockStart; i <= iBlockFinish; ++i)
        {
            // make a default block
            TRect Rect(4, g_iMapHeader + (i * g_iMapHeight), 5 + iWidth, g_iMapHeader + (i * g_iMapHeight) + g_iBarHeight);
            if (i == iBlockStart)
            {
                // set the start of the block
                float fPercentage = (float)(iAddress % m_iBlockSize) / (float)m_iBlockSize;
                Rect.Left = 4 + (iWidth * fPercentage);
            }
            if (i == iBlockFinish)
            {
                // set the finish of the block
                float fPercentage = ((float)((iAddress + iSize) % m_iBlockSize)) / (float)m_iBlockSize;
                Rect.Right = 6 + (iWidth * fPercentage);
            }
            // draw the current rectangle
            Canvas->Rectangle(Rect);
            // save the rectangle for when the mouse is over the image
            TMouseInfo MouseInfo;
            MouseInfo.MemoryObject = MemoryObject;
            MouseInfo.Rect = Rect;
            m_MouseRects.push_back(MouseInfo);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::imgMemoryMapMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    String sHint = "";
    for (unsigned int i = 0; i < m_MouseRects.size(); ++i)
    {
        if (m_MouseRects[i].Rect.Left <= X && X <= m_MouseRects[i].Rect.Right &&
            m_MouseRects[i].Rect.Top  <= Y && Y <= m_MouseRects[i].Rect.Bottom)
        {
            sHint = "Memory is allocated as " + m_MouseRects[i].MemoryObject->sName + "\n" +
                    m_MouseRects[i].MemoryObject->sMessage +
                    //"\nType is " + g_sTypes[m_MouseRects[i].MemoryObject->eType] +
                    "\nMemory range is from " + IntToStr(m_MouseRects[i].MemoryObject->iAddress) +
                    " to  " + IntToStr(m_MouseRects[i].MemoryObject->iAddress + m_MouseRects[i].MemoryObject->iSize - 1) +
                    ".\nThere are " + IntToStr(m_MouseRects[i].MemoryObject->iSize) + " bytes allocated for this memory block." +
                    "\nThis block of memory is " + (m_MouseRects[i].MemoryObject->bMoveable ? (String)"" : (String)"not ") + "moveable.";
        }
    }
    if (imgMemoryMap->Hint != sHint)
    {
        imgMemoryMap->Hint  = sHint;
        Application->Hint = sHint;
        Application->ActivateHint(imgMemoryMap->ClientToScreen(TPoint(X, Y)));
    }
    else if (sHint == "")
    {
        imgMemoryMap->Hint  = "";
        Application->Hint = "";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::cmdMemoryMapDecreaseClick(TObject *Sender)
{
    if (m_iBlockSize != 65536)
    {
        m_iBlockSize = m_iBlockSize << 1;
        Update();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::cmdMemoryMapIncreaseClick(TObject *Sender)
{
    if (m_iBlockSize != 1024)
    {
        m_iBlockSize = m_iBlockSize >> 1;
        Update();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::lstMemoryMapCustomClickCheck(TObject *Sender)
{
    m_CustomObjects[lstMemoryMapCustom->ItemIndex]->bEnabled = lstMemoryMapCustom->Checked[lstMemoryMapCustom->ItemIndex];
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::lstMemoryMapSystemClickCheck(TObject *Sender)
{
    static bool bProcessing = false;
    if (false == bProcessing)
    {
        bProcessing = true;
        m_SystemObjects[lstMemoryMapSystem->ItemIndex]->bEnabled = lstMemoryMapSystem->Checked[lstMemoryMapSystem->ItemIndex];
        Update();
        bProcessing = false;
    }
}
//---------------------------------------------------------------------------
unsigned int __fastcall TfrmMemoryEditor::MemoryObjects(void)
{
    return m_MemoryObjects.size();
}
//---------------------------------------------------------------------------
ZXMemoryObject* __fastcall TfrmMemoryEditor::MemoryObject(unsigned int iIndex)
{
    ZXMemoryObject* MemoryObject = NULL;
    if (iIndex < m_MemoryObjects.size())
    {
        MemoryObject = m_MemoryObjects[iIndex];
    }
    return MemoryObject;
}
//---------------------------------------------------------------------------
ZXMemoryObject* __fastcall TfrmMemoryEditor::MemoryFind(String sName, eMemory Type, bool bMoveable)
{
    ZXMemoryObject* MemObj = NULL;
    ZXMemoryObject* TmpMemObj = NULL;
    for (unsigned int i = 0; i < m_MemoryObjects.size() && NULL == MemObj; ++i)
    {
        TmpMemObj = MemoryObject(i);
        if (true == SAFE_PTR(TmpMemObj))
        {
            if (TmpMemObj->sName    == sName    &&
                TmpMemObj->eType    == Type     &&
                TmpMemObj->bMoveable== bMoveable)
            {
                MemObj = TmpMemObj;
            }
        }
    }
    return MemObj;
}
//---------------------------------------------------------------------------
ZXMemoryObject* __fastcall TfrmMemoryEditor::MemoryAdd(String sName, String sMessage, unsigned int iAddress, unsigned int iSize, eMemory Type, bool bMoveable)
{
    ZXMemoryObject* MemoryObject = MemoryFind(sName, Type, bMoveable);
    if (NULL == MemoryObject)
    {
        // add a new object
        MemoryObject = new ZXMemoryObject();
        if (true == SAFE_PTR(MemoryObject))
        {
            MemoryObject->eType     = Type;
            MemoryObject->sName     = sName;
            MemoryObject->sMessage  = sMessage;
            MemoryObject->iAddress  = iAddress;
            MemoryObject->iSize     = iSize;
            MemoryObject->bEnabled  = true;
            MemoryObject->bMoveable = bMoveable;
            m_MemoryObjects.push_back(MemoryObject);
        }
    }
    else
    {
        // update the address of the object
        MemoryObject->sName    = sName;
        MemoryObject->sMessage = sMessage;
        MemoryObject->iAddress = iAddress;
        MemoryObject->iSize    = iSize;
    }
    return MemoryObject;
}
//---------------------------------------------------------------------------
ZXMemoryObject*__fastcall TfrmMemoryEditor::MemoryAdd(String sName, unsigned int iAddress, unsigned int iSize)
{
    return MemoryAdd(sName, "", iAddress, iSize, memCustom, true);
}
//---------------------------------------------------------------------------
bool __fastcall TfrmMemoryEditor::MemoryRemove(const String& sName)
{
    ZXMemoryObject* MemObj = MemoryFind(sName, memCustom, true);
    bool bRemoved = false;
    if (true == SAFE_PTR(MemObj))
    {
        m_MemoryObjects.erase(std::find(m_MemoryObjects.begin(), m_MemoryObjects.end(), MemObj));
        m_bSaved = true;
        bRemoved = true;
    }
    return bRemoved;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::InitMemoryObjects(void)
{
    m_MemoryObjects.clear();
    // add the ROM, Screen and System variables objects
    MemoryAdd("Spectrum System ROM", "©1982 Sinclair Research Ltd.", 0, 16384, memROM, false);
    MemoryAdd("Spectrum Character Set", "", 15616, 768, memCharacterSets, false);
    MemoryAdd("Screen (Pixels)", "", 16384, 6144, memScreen, false);
    MemoryAdd("Screen (Attributes)", "", 22528, 768, memScreen, false);
    MemoryAdd("Printer Buffer", "", 23296, 256, memSystem, false);
    MemoryAdd("System Variables", "", 23552, 182, memSystem, false);
    MemoryAdd("Misc System Area", "Used for Sinclair BASIC.", 23734, 1034, memSystem, false);
    MemoryAdd("Start of Useable RAM", "This is a good place to start your code.\n", 24768, 1, memSystem, false);
    MemoryAdd("Machine Stack", "You will need a LD SP,NN statement at the start of your code.\n", 63488, 2048, memStack, true);
    MemoryUpdate();
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::MemoryUpdate(void)
{
    int iStartAddress = m_iGameAddress;
    //iStartAddress    += CalculateSpriteTable    (MemoryAdd("Sprite Table"               , "", iStartAddress, 0, memSpriteTable  , true));
    //iStartAddress    += CalculateTileTable      (MemoryAdd("Tile Table"                 , "", iStartAddress, 0, memTileTable    , true));
    //iStartAddress    += CalculateMapTable       (MemoryAdd("Map Table (list of Screens)", "", iStartAddress, 0, memMapTable     , true));
    //iStartAddress    += CalculateSprites        (MemoryAdd("Sprites"                    , "", iStartAddress, 0, memSprites      , true));
    //iStartAddress    += CalculateTiles          (MemoryAdd("Tiles"                      , "", iStartAddress, 0, memTiles        , true));
    //iStartAddress    += CalculateMapScreens     (MemoryAdd("Map Screens (rooms)"        , "", iStartAddress, 0, memMapScreens   , true));
    //iStartAddress    += CalculateCharacterSets  (MemoryAdd("Character Sets"             , "", iStartAddress, 0, memCharacterSets, true));
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::sbxMemoryMapResize(TObject *Sender)
{
    imgMemoryMap->Picture->Bitmap->Width  = sbxMemoryMap->ClientWidth;
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoryEditor::pgcMemoryMapDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    static Graphics::TBitmap* bm = NULL;
    Control->Canvas->Brush->Color = clWhite;
    Control->Canvas->FillRect(Rect);
    TTabSheet* sheet = pgcMemoryMap->Pages[TabIndex];
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
    pgcMemoryMap->Images->Draw(Control->Canvas, rl + 10 + cx - cw - 20, rt + cy - 8, sheet->ImageIndex, true);

    if (Active)
    {
        if (bm == NULL)
        {
            bm = new Graphics::TBitmap();
            bm->Width = 1;
            bm->Height = 1;
            bm->PixelFormat = pf32bit;
            bm->Canvas->Pixels[0][0] = (TColor)0x00846142;
        }
        TRect tr(Rect.left, Rect.top, Rect.right, Rect.top + 5);
        Control->Canvas->StretchDraw(tr, bm);
    }
}
//---------------------------------------------------------------------------

