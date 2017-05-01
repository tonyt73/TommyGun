//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "fOSBView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KSpinEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#include "ZXDebugger.h"
//---------------------------------------------------------------------------
TfrmOSBView *frmOSBView;
//---------------------------------------------------------------------------
__fastcall TfrmOSBView::TfrmOSBView(TComponent* Owner)
 : TForm(Owner)
 , m_Memory(NULL)
 , m_ImageScale(1)
 , m_Loading(false)
{
    m_Memory = new char[65536];
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::FormCreate(TObject *Sender)
{
    DoubleBuffered = true;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::Update()
{
    cmbSymbol->Items->Clear();
    std::list<String> Symbols;
    g_Debugger->Symbols.GetSymbols(Symbols);
    for (std::list<String>::iterator it = Symbols.begin(); it != Symbols.end(); ++it)
    {
        if (it->LowerCase().Pos("buf"))
        {
            cmbSymbol->Items->Add(*it);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::UpdateList()
{
    int i = lstBuffers->ItemIndex;
    lstBuffers->Items->Clear();
    for (std::vector<TBufferDefinition>::iterator it = m_Buffers.begin(); it != m_Buffers.end(); ++it)
    {
        TListItem* lvi = lstBuffers->Items->Add();
        lvi->Checked = it->Visible;
        lvi->SubItems->Add(it->Symbol);
        lvi->SubItems->Add(IntToStr(it->Width) + "x" + IntToStr(it->Height));
    }
    if (i < lstBuffers->Items->Count)
    {
        lstBuffers->ItemIndex = i;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::tbnAddClick(TObject *Sender)
{
    TBufferDefinition bd;
    bd.Symbol = cmbSymbol->Text;
    bd.Width = spnWidth->Value;
    bd.Height = spnHeight->Value;
    bd.Visible = true;
    bd.Bitmap = new Graphics::TBitmap();
    bd.Bitmap->Width = bd.Width * 8;
    bd.Bitmap->Height = bd.Height;
    bd.Bitmap->PixelFormat = pf32bit;
    bd.Bitmap->Canvas->Brush->Color = clBlack;
    bd.Bitmap->Canvas->FillRect(TRect(0,0,bd.Bitmap->Width,bd.Bitmap->Height));
    bd.Bitmap->Canvas->Font->Color = clYellow;
    bd.Bitmap->Canvas->Font->Height = 15;
    bd.Bitmap->Canvas->Font->Style = Active ? TFontStyles() << fsBold : TFontStyles();
    m_Buffers.push_back(bd);
    UpdateList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::tbnRemoveClick(TObject *Sender)
{
    if (lstBuffers->ItemIndex != -1)
    {
        std::vector<TBufferDefinition>::iterator it = m_Buffers.begin() + lstBuffers->ItemIndex;
        SAFE_DELETE(it->Bitmap);
        m_Buffers.erase(it);
        UpdateList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::tbnUpdateClick(TObject *Sender)
{
    if (lstBuffers->ItemIndex != -1)
    {
        int bufIndex = lstBuffers->ItemIndex;
        m_Buffers[bufIndex].Symbol = cmbSymbol->Text;
        m_Buffers[bufIndex].Width = spnWidth->Value;
        m_Buffers[bufIndex].Height = spnHeight->Value;
        if (m_Buffers[bufIndex].Width != m_Buffers[bufIndex].Bitmap->Width || m_Buffers[bufIndex].Height != m_Buffers[bufIndex].Bitmap->Height)
        {
            SAFE_DELETE(m_Buffers[bufIndex].Bitmap);
            m_Buffers[bufIndex].Bitmap = new Graphics::TBitmap();
            m_Buffers[bufIndex].Bitmap->Width = m_Buffers[bufIndex].Width * 8;
            m_Buffers[bufIndex].Bitmap->Height = m_Buffers[bufIndex].Height;
            m_Buffers[bufIndex].Bitmap->PixelFormat = pf32bit;
            m_Buffers[bufIndex].Bitmap->Canvas->Brush->Color = clBlack;
            m_Buffers[bufIndex].Bitmap->Canvas->FillRect(TRect(0,0,m_Buffers[bufIndex].Bitmap->Width,m_Buffers[bufIndex].Bitmap->Height));
            m_Buffers[bufIndex].Bitmap->Canvas->Font->Color = clWhite;
            m_Buffers[bufIndex].Bitmap->Canvas->Font->Height = 15;
            m_Buffers[bufIndex].Bitmap->Canvas->Font->Style = Active ? TFontStyles() << fsBold : TFontStyles();
        }
        UpdateList();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::lstBuffersClick(TObject *Sender)
{
    if (lstBuffers->ItemIndex != -1)
    {
        TListItem* lvi = lstBuffers->Items->Item[lstBuffers->ItemIndex];
        cmbSymbol->Text = lvi->SubItems->Strings[0];
        String size = lvi->SubItems->Strings[1];
        spnWidth->Value = StrToInt(size.SubString(1, size.Pos("x")-1));
        spnHeight->Value = StrToInt(size.SubString(size.Pos("x")+1, 100));
    }
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmOSBView::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo& buffers = xmlInfo.AddTag("Buffers");
    for (std::vector<TBufferDefinition>::iterator it = m_Buffers.begin(); it != m_Buffers.end(); ++it)
    {
        // save the file link to the xml object
        KXmlInfo& buffer = buffers.AddTag("Buffer");
        buffer.Add("Symbol", it->Symbol);
        buffer.Add("Width", it->Width);
        buffer.Add("Height", it->Height);
        buffer.Add("Visible", it->Visible);
    }
    return S_OK;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmOSBView::Load(KXmlInfo& xmlInfo)
{
    m_Loading = true;
    m_Buffers.clear();
    KXmlInfo* buffers;
    if (xmlInfo.Find(buffers, "Buffers", 0))
    {
        for (KXmlNodes::iterator it = buffers->begin(); it != buffers->end(); it++)
        {
            if ((*it)->GetName() == "Buffer")
            {
                KXmlInfo* pSymbol = (*it)->GetNode("Symbol");
                KXmlInfo* pWidth = (*it)->GetNode("Width");
                KXmlInfo* pHeight = (*it)->GetNode("Height");
                KXmlInfo* pVisible = (*it)->GetNode("Visible");
                if (SAFE_PTR(pSymbol) && SAFE_PTR(pSymbol) && SAFE_PTR(pHeight) && SAFE_PTR(pVisible))
                {
                    TBufferDefinition bd;
                    bd.Symbol = pSymbol->GetText();
                    bd.Width = pWidth->GetInt();
                    bd.Height = pHeight->GetInt();
                    bd.Visible = pVisible->GetBool();
                    bd.Bitmap = new Graphics::TBitmap();
                    bd.Bitmap->Width = bd.Width * 8;
                    bd.Bitmap->Height = bd.Height;
                    bd.Bitmap->PixelFormat = pf32bit;
                    bd.Bitmap->Canvas->Brush->Color = clBlack;
                    bd.Bitmap->Canvas->FillRect(TRect(0,0,bd.Bitmap->Width,bd.Bitmap->Height));
                    bd.Bitmap->Canvas->Font->Color = clWhite;
                    bd.Bitmap->Canvas->Font->Height = 15;
                    bd.Bitmap->Canvas->Font->Style = Active ? TFontStyles() << fsBold : TFontStyles();
                    m_Buffers.push_back(bd);
                }
            }
        }
        ResizeImage();
        UpdateList();
    }
    m_Loading = false;
    return S_OK;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::popOSBNormalSizeClick(TObject *Sender)
{
    m_ImageScale = ((TMenuItem*)Sender)->Tag;
    ((TMenuItem*)Sender)->Checked = true;
    ResizeImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::lstBuffersChanging(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange)
{
    AllowChange = Change == ctState;
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::lstBuffersChange(TObject *Sender, TListItem *Item, TItemChange Change)
{
    if (!m_Loading && Item->Index != -1 && Item->Index < m_Buffers.size())
    {
        m_Buffers[Item->Index].Visible = Item->Checked;
        // work out image size
        ResizeImage();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::ResizeImage()
{
    // h = all check height + 20 pixels / title
    // w = max width
    m_ImageWidth = 0;
    m_ImageHeight = 0;
    int th = imgOSBDisplay->Picture->Bitmap->Canvas->TextHeight("A");

    for (std::vector<TBufferDefinition>::iterator it = m_Buffers.begin(); it != m_Buffers.end(); ++it)
    {
        if (it->Visible)
        {
            m_ImageWidth = std::max((unsigned int)m_ImageWidth, (it->Width * 8) + 8);
            m_ImageHeight += it->Height + th + 8;
        }
    }
    
    imgOSBDisplay->Width = m_ImageWidth * m_ImageScale;
    imgOSBDisplay->Height = m_ImageHeight * m_ImageScale;
    imgOSBDisplay->Picture->Bitmap->Width  = imgOSBDisplay->Width;
    imgOSBDisplay->Picture->Bitmap->Height = imgOSBDisplay->Height;

    RedrawBuffers();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::RedrawBuffers()
{
    if (!Visible || m_Buffers.size() == 0)
        return;
    int i = 0;
    int top = 0;
    int th = imgOSBDisplay->Picture->Bitmap->Canvas->TextHeight("A");
    imgOSBDisplay->Picture->Bitmap->Canvas->Brush->Color = clWhite;
    PatBlt(imgOSBDisplay->Picture->Bitmap->Canvas->Handle, 0, 0, imgOSBDisplay->Width, imgOSBDisplay->Height, PATCOPY);
    for (std::vector<TBufferDefinition>::iterator it = m_Buffers.begin(); it != m_Buffers.end(); ++i, ++it)
    {
        if (it->Visible)
        {
            // draw title
            imgOSBDisplay->Picture->Bitmap->Canvas->Brush->Color = clWhite;
            imgOSBDisplay->Picture->Bitmap->Canvas->TextOut(4, top + 2, it->Symbol);
            top += th + 4;
            // rect
            DrawBuffer(i);
            StretchBlt(imgOSBDisplay->Picture->Bitmap->Canvas->Handle,
                4, top, it->Bitmap->Width * m_ImageScale, it->Bitmap->Height * m_ImageScale,
                it->Bitmap->Canvas->Handle, 0, 0, it->Bitmap->Width, it->Bitmap->Height,
                SRCCOPY);
            top += it->Height * m_ImageScale;
        }
    }

    imgOSBDisplay->Invalidate();
    imgOSBDisplay->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOSBView::DrawBuffer(int bufIndex)
{
    if (m_Buffers.size() == 0)
    {
        return;
    }
    String symbol = m_Buffers[bufIndex].Symbol;
    unsigned int address = g_Debugger->Symbols.GetSymbol(symbol);
    if (address == 0)
    {
        return;
    }

    int width = m_Buffers[bufIndex].Width;
    int height = m_Buffers[bufIndex].Height;

    g_Debugger->Machine.GetMemory(address, width * height, m_Memory);
    Graphics::TBitmap* bitmap = m_Buffers[bufIndex].Bitmap;

    DWORD colors[] =
    {
        0x00000000, // black paper
        0x00FFFFFF, // white ink
    };
    byte pixels;

    for (int y = 0; y < bitmap->Height; y++)
    {
        DWORD* pLine = (DWORD*)bitmap->ScanLine[y];
        for (int x = 0; x < bitmap->Width; x += 8)
        {
            pixels = m_Memory[y * width + (x >> 3)];
            pLine[x + 0] = colors[(pixels & 0x80) >> 7];
            pLine[x + 1] = colors[(pixels & 0x40) >> 6];
            pLine[x + 2] = colors[(pixels & 0x20) >> 5];
            pLine[x + 3] = colors[(pixels & 0x10) >> 4];
            pLine[x + 4] = colors[(pixels & 0x08) >> 3];
            pLine[x + 5] = colors[(pixels & 0x04) >> 2];
            pLine[x + 6] = colors[(pixels & 0x02) >> 1];
            pLine[x + 7] = colors[(pixels & 0x01)     ];
        }
    }
}
//---------------------------------------------------------------------------

