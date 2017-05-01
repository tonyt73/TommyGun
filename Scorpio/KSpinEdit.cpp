/*---------------------------------------------------------------------------

	(c) 2008 Scorpio Software
		1 Nancybell Court
		Bellmere
		Brisbane QLD 4510
		Australia

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <algorithm>
#include <math.h>
#include <winuser.h>
//---------------------------------------------------------------------------
#include "KSpinEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(KSpinEdit *)
{
	new KSpinEdit(NULL);
}
//---------------------------------------------------------------------------
__fastcall KSpinEdit::KSpinEdit(TComponent* Owner)
: TPanel(Owner)
, m_Value(0)
, m_Min(0)
, m_Max(100)
, m_Step(1)
, m_Enabled(true)
, m_Changing(false)
{
    m_Edit = new TEdit(this);
    m_Down = new TBitBtn(this);
    m_Up   = new TBitBtn(this);

    Caption = "";

    m_Edit->Parent = this;
    m_Edit->AutoSize = false;
    m_Edit->BorderStyle = bsNone;
    m_Edit->BevelInner = bvNone;
    m_Edit->OnChange = OnEditChange;
    m_Edit->OnKeyPress = OnKeyPress;
    m_Edit->OnExit = OnExit;

    Graphics::TBitmap* tmp = new Graphics::TBitmap();
    // Load UP arrow
    tmp->Handle = LoadBitmap(NULL, (char*)32753);

    m_ArrowUp = new Graphics::TBitmap();
    m_ArrowUp->Width = 7;
    m_ArrowUp->Height = 5;
    // copy up arrow to new bitmap
    BitBlt(m_ArrowUp->Canvas->Handle, 0, 0, 7, 5, tmp->Canvas->Handle, 5, 6, SRCCOPY);

    // load down arrow
    tmp->Handle = LoadBitmap(NULL, (char*)32752);
    m_ArrowDown = new Graphics::TBitmap();
    m_ArrowDown->Width = 7;
    m_ArrowDown->Height = 5;
    // copy down arrow to new bitmap
    BitBlt(m_ArrowDown->Canvas->Handle, 0, 0, 7, 5, tmp->Canvas->Handle, 5, 7, SRCCOPY);

    // delete the tmp loading bitmap
    delete tmp;

    // assign the arrow bitmaps to the buttons
    m_Down->Parent  = this;
    m_Down->OnClick = OnValueDec;
    m_Down->Glyph->Handle = m_ArrowDown->Handle;

    m_Up->Parent    = this;
    m_Up->OnClick   = OnValueInc;
    m_Up->Glyph->Handle = m_ArrowUp->Handle;
}
//---------------------------------------------------------------------------
__fastcall KSpinEdit::~KSpinEdit()
{
    delete m_ArrowUp;
    delete m_ArrowDown;
}
//---------------------------------------------------------------------------
void __fastcall KSpinEdit::OnEditChange(TObject* Sender)
{
    if (m_Changing)
        return;
    if (TryStrToInt(m_Edit->Text, m_Value))
    {
        Validate();
        m_Edit->SelStart = m_Edit->Text.Length();
        m_Edit->SelLength = 0;
        Color = clWhite;
    }
    else
    {
        Color = (TColor)0x7F7FFF;
    }
}
//---------------------------------------------------------------------------
void __fastcall KSpinEdit::OnKeyPress(TObject *Sender, char &key)
{
    if (!m_Changing)
    {
        m_LastValue = Value;
    }
    m_Changing = true;
    if (TryStrToInt(m_Edit->Text, m_Value))
    {
        m_Edit->Color = clWhite;
    }
    else
    {
        m_Edit->Color = (TColor)0x7F7FFF;
    }
    if (key == VK_RETURN)
    {
        m_Value = StrToIntDef(m_Edit->Text, m_LastValue);
        m_Changing = false;
        Validate();
    }
}
//---------------------------------------------------------------------------
void __fastcall KSpinEdit::OnValueInc(TObject* Sender)
{
    if (m_Changing)
    {
        m_Changing = false;
        Validate();
    }
    m_Value += m_Step;
    Validate();
    if (FOnChangedUp)
    {
        FOnChangedUp(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall KSpinEdit::OnValueDec(TObject* Sender)
{
    if (m_Changing)
    {
        m_Changing = false;
        Validate();
    }
    m_Value -= m_Step;
    Validate();
    if (FOnChangedDown)
    {
        FOnChangedDown(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall KSpinEdit::OnExit(TObject* Sender)
{
    if (m_Changing)
    {
        m_Value = StrToIntDef(m_Edit->Text, m_LastValue);
        m_Changing = false;
        Validate();
    }
}
//---------------------------------------------------------------------------
void __fastcall KSpinEdit::Validate()
{
    if (m_Changing)
    {
        return;
    }
    if (!ComponentState.Contains(csLoading))
    {
        if (m_Min != m_Max != 0)
        {
            if (m_Value < m_Min)
            {
                m_Value = m_Min;
            }
            else if (m_Value > m_Max)
            {
                m_Value = m_Max;
            }
        }
    }
    m_LastValue = m_Value;
    m_Edit->Text = IntToStr(m_Value);
}
//---------------------------------------------------------------------------
void __fastcall KSpinEdit::SetInt(int index, int value)
{
    switch (index)
    {
        case eIntValue:
        {
            if (m_Value != value)
            {
                m_Value = value;
                Validate();
                if (FOnChanged)
                {
                    FOnChanged(this);
                }
            }
            Resize();
            break;
        }
        case eIntValueMin:
        {
            if (value > m_Max)
            {
                value = m_Max;
            }
            m_Min = value;
            Validate();
            Resize();
            break;
        }
        case eIntValueMax:
        {
            if (value < m_Min)
            {
                value = m_Min;
            }
            m_Max = value;
            Validate();
            Resize();
            break;
        }
        case eIntValueStep:
        {
            if (value < 1)
            {
                value = 1;
            }
            m_Step = value;
            Validate();
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall KSpinEdit::SetEnabled(bool value)
{
    m_Enabled = value;
    m_Edit->Enabled = value;
    m_Up->Enabled = value;
    m_Down->Enabled = value;
}
//---------------------------------------------------------------------------
void __fastcall KSpinEdit::Resize(void)
{
    if (m_Edit->Left != 2)
    {
        BevelOuter      = bvLowered;
        Caption         = "";
        
        m_Edit->Left    = 2;
        m_Edit->Top     = 2;
        m_Edit->Height  = this->Height - 4;

        const int ButtonWidth = 15;
        m_Up->Left      = Width - ButtonWidth - 1;
        m_Up->Top       = 1;
        m_Up->Height    = m_Edit->Height + 2;
        m_Up->Width     = ButtonWidth;
        m_Up->Anchors   = TAnchors() << akRight << akBottom << akTop;

        m_Down->Left    = m_Up->Left - ButtonWidth + 1;
        m_Down->Top     = 1;
        m_Down->Height  = m_Up->Height;
        m_Down->Width   = ButtonWidth;
        m_Down->Anchors = TAnchors() << akRight << akBottom << akTop;

        m_Edit->Width  = m_Down->Left - 3;
        m_Edit->Anchors = TAnchors() << akLeft << akRight << akBottom << akTop;

        m_Up->TabOrder = 2;
        m_Down->TabOrder = 1;
        Validate();
    }
}
//---------------------------------------------------------------------------
// Register
/**
 * Registers the control with the Borland Builder IDE
 * @author  Tony Thompson
 * @date    Created 13th July 2008
 */
//---------------------------------------------------------------------------
namespace Kspinedit
{
	void __fastcall PACKAGE Register()
	{
		 TComponentClass classes[1] = {__classid(KSpinEdit)};
		 RegisterComponents("Scorpio", classes, 0);
	}
}
//---------------------------------------------------------------------------

