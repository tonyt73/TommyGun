//---------------------------------------------------------------------------
#pragma hdrstop
#include "pch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace GameEditor;
//---------------------------------------------------------------------------
const int cNoKeyFound       = -1;
const int cKeyHeight        = 23;                       // all keys height
const int cKeyRows[4]       = { 90, 146, 202, 258 };    // y position of key rows
const int cKeyWidth[3]      = { 37, 48, 65 };           // normal key, caps, space
/*const int cKeyInfo[4][30] =                           // key x position, width index into cKeyWidth, key number
{
    {  37(37), 0,  92(29), 0, 147(21), 0, 202(13), 0, 257(5), 0, 367(12), 0, 422(20), 0, 477(28), 0, 532(36), 0, },
    {  64(38), 0, 119(30), 0, 174(22), 0, 229(14), 0, 284(6), 0, 394(11), 0, 449(19), 0, 504(27), 0, 559(35), 0, },
    {  76(39), 0, 131(31), 0, 186(23), 0, 241(15), 0, 296(7), 0, 406(10), 0, 461(18), 0, 516(26), 0, 571(34), 0, },
    {  37(40), 1, 103(32), 0, 158(24), 0, 213(16), 0, 268(8), 0, 378( 9), 0, 433(17), 0, 488(25), 0, 543(33), 2, }
};*/
struct KeyInfo
{
    int x;
    int row;
    int width;
    String key;
};
const KeyInfo cKeyInfo[40] = 
{
    { 323, 3, 0, "B" },  // B
    { 351, 2, 0, "H" },  // H
    { 339, 1, 0, "Y" },  // Y
    { 312, 0, 0, "6" },  // 6
    { 257, 0, 0, "5" },  // 5
    { 284, 1, 0, "T" },  // T
    { 296, 2, 0, "G" },  // G
    { 268, 3, 0, "V" },  // V
    { 378, 3, 0, "N" },  // N
    { 406, 2, 0, "J" },  // J
    { 394, 1, 0, "U" },  // U
    { 367, 0, 0, "7" },  // 7
    { 202, 0, 0, "4" },  // 4
    { 229, 1, 0, "R" },  // R
    { 241, 2, 0, "F" },  // F
    { 213, 3, 0, "C" },  // C
    { 433, 3, 0, "M" },  // M
    { 461, 2, 0, "K" },  // K
    { 449, 1, 0, "I" },  // I
    { 422, 0, 0, "8" },  // 8
    { 147, 0, 0, "3" },  // 3
    { 174, 1, 0, "E" },  // E
    { 186, 2, 0, "D" },  // D
    { 158, 3, 0, "X" },  // X
    { 488, 3, 0, "Symbol Shift" },  // SYM SHIFT
    { 516, 2, 0, "L" },  // L
    { 504, 1, 0, "O" },  // O
    { 477, 0, 0, "9" },  // 9
    {  92, 0, 0, "2" },  // 2
    { 119, 1, 0, "W" },  // W
    { 131, 2, 0, "S" },  // S
    { 103, 3, 0, "Z" },  // Z
    { 543, 3, 2, "Space" },  // SPACE
    { 571, 2, 0, "Enter" },  // ENTER
    { 559, 1, 0, "P" },  // P
    { 532, 0, 0, "0" },  // 0
    {  37, 0, 0, "1" },  // 1
    {  64, 1, 0, "Q" },  // Q
    {  76, 2, 0, "A" },  // A
    {  37, 3, 1, "Caps Shift" }   // CAPS SHIFT
};
//---------------------------------------------------------------------------
Keys::Keys()
: m_Image(NULL)
, m_HighlightX(0)
, m_HighlightY(0)
, m_HighlightKey(cNoKeyFound)
, m_IsDirty(false)
, m_PropertyNode(-1)
{
    // set default keys to Interface II Port 2
    m_Keys[0] = 3;  // 6 - left
    m_Keys[1] = 11; // 7 - right
    m_Keys[2] = 27; // 9 - up
    m_Keys[3] = 19; // 8 - down
    m_Keys[4] = 35; // 0 - fire
    m_Keys[5] = 16; // m - button 1
    m_Keys[6] = 0;  // b - button 2
}
//---------------------------------------------------------------------------
Keys::~Keys()
{
    m_Image = NULL;
}
//---------------------------------------------------------------------------
void __fastcall Keys::Init(TImage* image, TImage* k0, TImage* k1, TImage* k2, TImage* k3, TImage* k4, TImage* k5, TImage* k6)
{
    m_Image = image;
    m_ImgKeys[0] = k0;
    m_ImgKeys[1] = k1;
    m_ImgKeys[2] = k2;
    m_ImgKeys[3] = k3;
    m_ImgKeys[4] = k4;
    m_ImgKeys[5] = k5;
    m_ImgKeys[6] = k6;
    LayoutKeys();
    m_PropertyNode = frmGameEditor->GetPropertyEditor().AddRootNode(this, "Keys", tviKeys);
    frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Key1", cKeyInfo[m_Keys[0]].key);
    frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Key2", cKeyInfo[m_Keys[1]].key);
    frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Key3", cKeyInfo[m_Keys[2]].key);
    frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Key4", cKeyInfo[m_Keys[3]].key);
    frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Key5", cKeyInfo[m_Keys[4]].key);
    frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Key6", cKeyInfo[m_Keys[5]].key);
    frmGameEditor->GetPropertyEditor().AddProperty(m_PropertyNode, "Key7", cKeyInfo[m_Keys[6]].key);
}
//---------------------------------------------------------------------------
int __fastcall Keys::FindHighlightKey(int X, int Y)
{
    for (int i = 0; i < 40; i++)
    {
        int kxs = cKeyInfo[i].x;
        int kxe = kxs + cKeyWidth[cKeyInfo[i].width];
        if (kxs <= X && X <= kxe)
        {
            int kys = cKeyRows[cKeyInfo[i].row];
            int kye = kys + cKeyHeight;
            if (kys <= Y && Y < kye)
            {
                return i;
            }
        }
    }
    return cNoKeyFound;
}
//---------------------------------------------------------------------------
void __fastcall Keys::DrawHighlightCursor()
{
    if (m_HighlightKey >= 0)
    {
        int kxs = cKeyInfo[m_HighlightKey].x;
        int kxe = kxs + cKeyWidth[cKeyInfo[m_HighlightKey].width];
        int kys = cKeyRows[cKeyInfo[m_HighlightKey].row];
        int kye = kys + cKeyHeight;
        m_Image->Canvas->Pen->Color = clWhite;
        m_Image->Canvas->Pen->Mode = pmXor;
        m_Image->Canvas->MoveTo(kxs - 12, kys - 12);
        m_Image->Canvas->LineTo(kxe + 12, kys - 12);
        m_Image->Canvas->LineTo(kxe + 12, kye + 12);
        m_Image->Canvas->LineTo(kxs - 12, kye + 12);
        m_Image->Canvas->LineTo(kxs - 12, kys - 12);
    }
}
//---------------------------------------------------------------------------
void __fastcall Keys::DrawHighlight(int X, int Y)
{
    int hlKey = FindHighlightKey(X, Y);
    if (hlKey != m_HighlightKey)
    {
        DrawHighlightCursor();
        m_HighlightKey = hlKey;
        DrawHighlightCursor();        
    }
}
//---------------------------------------------------------------------------
void __fastcall Keys::LayoutKeys()
{
    if (m_Image != NULL)
    {
        for (int i = 0; i < 7; i++)
        {
            int key = m_Keys[i];
            m_ImgKeys[i]->Left = m_Image->Left + (cKeyInfo[key].x + cKeyWidth[cKeyInfo[key].width] - 8);
            m_ImgKeys[i]->Top = m_Image->Top + (cKeyRows[cKeyInfo[key].row] - 8);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall Keys::MouseMove(int X, int Y)
{
    DrawHighlight(X, Y);                                            
}
//---------------------------------------------------------------------------
void __fastcall Keys::KeyDown(WORD &Key)
{
    if (m_HighlightKey != cNoKeyFound && '1' <= Key && Key <= '7')
    {
        int key = Key - '1';
        m_Keys[key] = m_HighlightKey;
        LayoutKeys();
        m_IsDirty = true;
    }
}
//---------------------------------------------------------------------------
bool __fastcall Keys::Load(KXmlInfo& xmlInfo)
{
    bool bLoaded = false;
    KXmlInfo* KeysNode;
    if (xmlInfo.Find(KeysNode, "Keys", 0))
    {
        for (int i = 0; i < 7; i++)
        {
            AnsiString key = "Key" + IntToStr(i+1);
            KXmlInfo* nKey = KeysNode->GetNode(key, 0);
            if (nKey)
            {
                int keyCode = nKey->GetInt();
                m_Keys[i] = std::min(39, std::max(0, keyCode));
            }
        }
        bLoaded = true;
        LayoutKeys();
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
void __fastcall Keys::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo* Node;
    if (xmlInfo.Find(Node, "Keys", 0))
    {
        xmlInfo.Remove(Node);
    }
    // create a new map editor node
    KXmlInfo keys("Keys");
    // store the map details
    keys.Add("Key1", m_Keys[0]);
    keys.Add("Key2", m_Keys[1]);
    keys.Add("Key3", m_Keys[2]);
    keys.Add("Key4", m_Keys[3]);
    keys.Add("Key5", m_Keys[4]);
    keys.Add("Key6", m_Keys[5]);
    keys.Add("Key7", m_Keys[6]);
    xmlInfo.Add(keys);
    m_IsDirty = false;
    LayoutKeys();
}
//---------------------------------------------------------------------------
void __fastcall Keys::OnPropertyChanged(int node)
{
    AnsiString value;
    frmGameEditor->GetPropertyEditor().GetProperty(m_PropertyNode, node, value);
    // find the key string
    for (int i = 0; i < 40; ++i)
    {
        if (cKeyInfo[i].key.LowerCase() == value.LowerCase())
        {
            // found key
            m_Keys[node] = i;
            break;
        }
    }
    LayoutKeys();
}
//---------------------------------------------------------------------------

