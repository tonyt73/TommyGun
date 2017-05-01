//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "fDebuggerStateView.h"
#include "ZXDebugger.h"
#include "ZXSnapManager.h"
#include "fCodeEditor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmDebuggerStateView *frmDebuggerStateView;
//---------------------------------------------------------------------------
__fastcall TfrmDebuggerStateView::TfrmDebuggerStateView(TComponent* Owner)
 : TForm(Owner)
// , m_WindowState(wsNone)
// , m_OldHeight(700)
{
//    WindowProc = SubClassWndProc;
}
//---------------------------------------------------------------------------
//void __fastcall TfrmDebuggerStateView::SubClassWndProc(Messages::TMessage &Message)
//{
//    if (!SnapManager::ProcessMoving(Message, this))
//    {
//        WndProc(Message);
//    }
//}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::FormCreate(TObject *Sender)
{
    //SnapManager::RegisterSnapClient(frmDebuggerStateView, frmMain, seRight, 0, 1);
    memset(&m_Context, 0, sizeof(Z80));
    m_FontBlack = new TFont();
    m_FontBlack->Assign(Font);
    m_FontRed = new TFont();
    m_FontRed->Assign(Font);
    m_FontRed->Color = clRed;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::FormResize(TObject *Sender)
{
//    if (m_WindowState == wsNone)
//    {
//        m_WindowState = wsResizing;
//
//        if (Height > Constraints->MinHeight + 32)
//        {
//            m_OldHeight = Height;
//        }
//        btnCollapse->Down = (Height == Constraints->MinHeight);
//
//        m_WindowState = wsNone;
//    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::FormMouseEnter(TObject *Sender)
{
//    AlphaBlend = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::FormMouseLeave(TObject *Sender)
{
//    AlphaBlend = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::btnCollapseClick(TObject *Sender)
{
//    if (m_WindowState == wsNone)
//    {
//        m_WindowState = wsCollapsing;
//        if (Height != Constraints->MinHeight)
//        {
//            m_OldHeight = Height;
//            Height =  Constraints->MinHeight;
//        }
//        else
//        {
//            Height = m_OldHeight;
//        }
//        m_WindowState = wsNone;
//    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::SetValue(TLabeledEdit* Label, WORD Value, bool CanBeSplit)
{
    AnsiString oldText = Label->Text;
    AnsiString text;
    if (rad8bit->Checked && CanBeSplit)
    {
        AnsiString Hi;
        AnsiString Lo;
        AnsiString Pr = radHex->Checked ? "$" : "";
        int len = radHex->Checked ? 2 : 3;

        Hi = "  " + (radHex->Checked ? IntToHex(Value >> 8  , 2) : IntToStr(Value >> 8  ));
        Lo = "  " + (radHex->Checked ? IntToHex(Value & 0xFF, 2) : IntToStr(Value & 0xFF));
        Hi = Hi.SubString(Hi.Length() - len + 1, len);
        Lo = Lo.SubString(Lo.Length() - len + 1, len);
        text = Pr + Hi + " " + Pr + Lo;
    }
    else
    {
        if (radHex->Checked)
        {
            text = "$" + IntToHex(Value, 4);
        }
        else
        {
            text = "    " + IntToStr(Value);
            text = text.SubString(text.Length() - 4, 5);
        }
    }
    Label->Text = text;
    Label->Font->Color = (Label->Text != oldText) ? clRed : clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::SetValue(TLabeledEdit* Label, BYTE Value)
{
    AnsiString oldText = Label->Text;
    AnsiString Num;
    AnsiString Pr = radHex->Checked ? "$" : "";
    int len = radHex->Checked ? 2 : 3;

    Num = "  " + (radHex->Checked ? IntToHex(Value, 2) : IntToStr(Value));
    Num = Num.SubString(Num.Length() - len + 1, len);

    Label->Text = Pr + Num;
    Label->Font->Color = (Label->Text != oldText) ? clRed : clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::SetContext(const Z80& Context)
{
    m_TStates =  Context.ITotal - m_Context.ITotal;
    // copy the context
    memcpy(&m_Context, &Context, sizeof(Z80));
    UpdateView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::UpdateView()
{
    // display the context
    SetValue(lblRegsPC , m_Context.PC.W , false);
    SetValue(lblRegsSP , m_Context.SP.W , false);
    SetValue(lblRegsAF , m_Context.AF.W , true );
    SetValue(lblRegsBC , m_Context.BC.W , true );
    SetValue(lblRegsDE , m_Context.DE.W , true );
    SetValue(lblRegsHL , m_Context.HL.W , true );
    SetValue(lblRegsAF_, m_Context.AF1.W, true );
    SetValue(lblRegsBC_, m_Context.BC1.W, true );
    SetValue(lblRegsDE_, m_Context.DE1.W, true );
    SetValue(lblRegsHL_, m_Context.HL1.W, true );
    SetValue(lblRegsIX , m_Context.IX.W , false);
    SetValue(lblRegsIY , m_Context.IY.W , false);
    SetValue(lblRegsI  , m_Context.I           );
    SetValue(lblRegsR  , m_Context.R           );

    chkRegsFlags_S->Checked = !!(m_Context.AF.B.l & S_FLAG);
    chkRegsFlags_Z->Checked = !!(m_Context.AF.B.l & Z_FLAG);
    chkRegsFlags_H->Checked = !!(m_Context.AF.B.l & H_FLAG);
    chkRegsFlags_V->Checked = !!(m_Context.AF.B.l & V_FLAG);
    chkRegsFlags_N->Checked = !!(m_Context.AF.B.l & N_FLAG);
    chkRegsFlags_C->Checked = !!(m_Context.AF.B.l & C_FLAG);

    lblRegsIM->Text = (m_Context.IFF & IFF_IM1) ? "1" : "2";
    chkRegsInterrupts->Checked = !!(m_Context.IFF);
    lblRegsTStates->Text = IntToStr(m_TStates);

    // update the stack view
    txtStack->Lines->Clear();
    const TDebugStack& stack = g_Debugger->GetStack();
    for (TDebugStackConstIt it = stack.begin(); it != stack.end(); ++it)
    {
        const TStackInfo& info = (*it);
        String line = "$" + IntToHex(info.StackPtr, 4) + ": $" + IntToHex(info.Value, 4) + " (" + info.Operand + ")";
        if (info.Label.Trim() != "")
        {
            line += " [" + info.Label + "]";
        }
        if (info.FuncAddr.Trim() != "")
        {
            line += " [" + info.FuncAddr + "]";
        }
        txtStack->Lines->Add(line);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::btnHexClick(TObject *Sender)
{
    UpdateView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::rad8bitClick(TObject *Sender)
{
    UpdateView();    
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::rad100pcClick(TObject *Sender)
{
    static int times[5] = { 200, 180, 100, 50, 1 };
    frmCodeEditor->tmrDebugger->Interval = times[((TControl*)Sender)->Tag];
}
//---------------------------------------------------------------------------
void __fastcall TfrmDebuggerStateView::pgcRegistersDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    TPageControl* pc = (TPageControl*)Control;
    static Graphics::TBitmap* bm = NULL;
    Control->Canvas->Brush->Color = clWhite;
    Control->Canvas->FillRect(Rect);
    TTabSheet* sheet = pc->Pages[TabIndex];
    int cw = Control->Canvas->TextWidth(sheet->Caption) / 2;
    int ch = Control->Canvas->TextHeight(sheet->Caption) / 2;
    int rl = Rect.Left;
    int rt = Rect.Top;
    int cx = Rect.Width() / 2;
    int cy = Rect.Height() / 2;
    Control->Canvas->Font->Color = clBlack;
    Control->Canvas->Font->Height = 12;
    Control->Canvas->Font->Style = Active ? TFontStyles() << fsBold : TFontStyles();
    Control->Canvas->TextRect(Rect, rl + 10 + cx - cw, rt + cy - ch, sheet->Caption);
    pc->Images->Draw(Control->Canvas, rl + 10 + cx - cw - 20, rt + cy - 8, sheet->ImageIndex, true);

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

