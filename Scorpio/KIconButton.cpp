/*---------------------------------------------------------------------------

	(c) 2002 Scorpio Software
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
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "KIconButton.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(KIconButton *)
{
    new KIconButton(NULL);
}
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the state of the button
 * @param   Owner the vcl owner of the button
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
__fastcall KIconButton::KIconButton(TComponent* Owner)
    : TGraphicControl(Owner),
      m_bMouseButtonDown(false),
      FFont(NULL)
{
    Width           = 82;
    Height          = 74;
    Color           = clBtnFace;
    FIconIndex      = 0;
    FColorBackground= clBtnFace;
    FColorBorder    = clWindowFrame;
    FColorSelected  = clWindow;
    FSelected       = false;
    FGrouped        = false;
    FIconsHot       = NULL;
    FIconsCold      = NULL;
    FFont           = new TFont;
    FFont->Assign(Font);
}
//---------------------------------------------------------------------------
// Destructor
/**
 * Frees allocated resources
 * @author  Tony Thompson
 * @date    Created 4 December 2005
 */
//---------------------------------------------------------------------------
__fastcall KIconButton::~KIconButton()
{
    delete FFont;
}
//---------------------------------------------------------------------------
// DoFullPaint
/**
 * Redraws the entire control from scratch
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::Paint(void)
{
    // erase the background
    Canvas->Brush->Color = FColorBackground;
    Canvas->FillRect(Rect(0, 0, Width, Height));
    // select the colors for drawing the round rectangle
    Canvas->Pen->Color   = FSelected ? FColorBorderSelected : FColorBorder;
    Canvas->Brush->Color = FSelected ? FColorSelected : (MouseCapture ? FColorHighlight : Color);
    // and draw the rounded rectangle
    Canvas->RoundRect(0, 0, Width, Height, FCornerWidth, FCornerHeight);
    DrawCaption();
    DrawIcon();
}
//---------------------------------------------------------------------------
// DoMouseDown
/**
 * MouseDown event handler
 * @param   Button the mouse button pressed
 * @param   Shift the state of the shift keys and mouse buttons
 * @param   X the x position of the mouse
 * @param   Y the y position of the mouse
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::DoMouseDown (TMouseButton Button, TShiftState /*Shift*/, int /*X*/, int /*Y*/)
{
    // left mouse button pressed?
    if (mbLeft == Button)
    {
        // yep, so flag the button down
        m_bMouseButtonDown = true;
        // select the button
        Selected = true;
        // and capture the button if we are not a grouped button
        MouseCapture = !FGrouped;
    }
}
//---------------------------------------------------------------------------
// DoMouseUp
/**
 * MouseDown event handler
 * @param   Button the mouse button pressed
 * @param   Shift the state of the shift keys and mouse buttons
 * @param   X the x position of the mouse
 * @param   Y the y position of the mouse
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::DoMouseUp(TMouseButton Button, TShiftState /*Shift*/, int /*X*/, int /*Y*/)
{
    // left button released and not grouped?
    if (mbLeft == Button && false == FGrouped)
    {
        // yep, unselect button
        Selected = false;
    }
    // button is now up
    m_bMouseButtonDown = false;
    // and release the mouse
    MouseCapture = false;
}
//---------------------------------------------------------------------------
// DoMouseUp
/**
 * MouseDown event handler
 * @param   Button the mouse button pressed
 * @param   Shift the state of the shift keys and mouse buttons
 * @param   X the x position of the mouse
 * @param   Y the y position of the mouse
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::DoMouseMove(TShiftState /*Shift*/, int X, int Y)
{
    if (false == ComponentState.Contains(csDesigning))
    {
        if (false == MouseCapture)
        {
            // capture the mouse if we haven't already
            MouseCapture = true;
            // draw the highlight (mouse over) color
            Invalidate();
        }
        else
        {
            // do we need to release the mouse yet?
            if ((X < 0 || X > Width || Y < 0 || Y > Height) && (FGrouped || !m_bMouseButtonDown))
            {
                // the mouse if outside the button and
                // either the button is not grouped or the button is grouped but no mouse buttons are pressed
                // so release the mouse
                MouseCapture = false;
                // and draw the unselected (normal) color
                Invalidate();
            }
        }
    }
}
//---------------------------------------------------------------------------
// DrawIcon
/**
 * Draws the icon for the button
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::DrawIcon(void)
{
    TImageList* Icons = FSelected ? FIconsHot : FIconsCold;
    if (NULL != Icons)
    {
        int iIconWidth  = Icons->Width;
        // center the icon horizontally
        int iIconX      = (Width >> 1) - (iIconWidth >> 1);
        // and draw it
        Icons->Draw(Canvas, iIconX, 4, FIconIndex, true);
    }
}
//---------------------------------------------------------------------------
// DrawCaption
/**
 * Draws the caption of the button
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::DrawCaption(void)
{
    if (Caption != "")
    {
        // split the caption
        String sLine1;
        String sLine2;
        SplitCaption(sLine1, sLine2);
        // get the luminance of the color
        DWORD TmpColor = FSelected ? ColorToRGB(FColorSelected) : MouseCapture ? ColorToRGB(FColorHighlight) : ColorToRGB(Color);
        DWORD dwRed   = (TmpColor & 0x000000FF) >>  0;
        DWORD dwGreen = (TmpColor & 0x0000FF00) >>  8;
        DWORD dwBlue  = (TmpColor & 0x00FF0000) >> 16;
        DWORD dwLuminance = ((0.299f * (float)dwRed) + (0.587f * (float)dwGreen) + (0.114f * (float)dwBlue));
        // and set the font color to the appropreiate color
        FFont->Color = dwLuminance > 128 ? clBlack : clWhite;
        // add bold if selected, else remove bold from the font
        FFont->Style = FSelected ? FFont->Style << fsBold : FFont->Style >> fsBold;
        Canvas->Font->Assign(FFont);
        // draw the 2 lines of text
        DrawLine(sLine1, 2);
        DrawLine(sLine2, 1);
    }
}
//---------------------------------------------------------------------------
// SplitCaption
/**
 * Trys to split a caption into 2 lines
 * @param   sLine1 the first line for the text
 * @param   sLine2 the second line for the text
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::SplitCaption(String& sLine1, String& sLine2)
{
    // calculate the font size with bold enabled
    Font->Style = Font->Style << fsBold;
    sLine1 = FCaption;
    sLine2 = "";
    int iMaxTextWidth = Width - 8;
    while (iMaxTextWidth < Canvas->TextWidth(sLine1))
    {
        // remove a word from line1 and put it in Line2
        int iX = sLine1.Length();
        while(0 != iX && sLine1[iX] != ' ')
        {
            sLine2 = String(sLine1[iX]) + sLine2;
            --iX;
        }
        sLine1 = sLine1.SubString(1, iX);
    }
    // alway have the bottom line printed, if the Line2 is blank
    if (sLine2 == "")
    {
        sLine2 = sLine1;
        sLine1 = "";
    }
    sLine1 = sLine1.Trim();
    sLine2 = sLine2.Trim();
}
//---------------------------------------------------------------------------
// DrawLine
/**
 * Draws a line of text
 * @param   sText       the text to draw
 * @param   iLineIndex  the line index to draw the text at
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::DrawLine(const String& sText, int iLineIndex)
{
    TSize TextSize = Canvas->TextExtent(sText);
    int iTextY = (Height - 4) - (TextSize.cy * iLineIndex);
    int iTextX = (Width >> 1) - (TextSize.cx >> 1);
    Canvas->TextRect(TRect(2, iTextY, Width - 4, iTextY + TextSize.cy), iTextX, iTextY, sText);
}
//---------------------------------------------------------------------------
// UnselectButtons
/**
 * Unselects the buttons in contained by the same as parent as this button
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::UnselectButtons(void)
{
    // find all the KIconButtons that have the same parent as us and reset the selected flag for all grouped items
    for (int i = 0; i < Parent->ControlCount; i++)
    {
        KIconButton* IconButton = dynamic_cast<KIconButton*>(Parent->Controls[i]);
        if (NULL != IconButton && IconButton != this && IconButton->Grouped)
        {
            IconButton->Selected = false;
        }
    }
}
//---------------------------------------------------------------------------
// SetColor
/**
 * Sets properties of the Control by Index
 * @param   iIndex      the index of the property type to set
 * @param   cValue      the value to set the property to
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::SetColor(int iIndex, TColor cValue)
{
    switch(iIndex)
    {
        case eColorBackground:
        {
            FColorBackground = cValue;
            break;
        }
        case eColorSelected:
        {
            FColorSelected = cValue;
            break;
        }
        case eColorBorder:
        {
            FColorBorder = cValue;
            break;
        }
        case eColorBorderSelected:
        {
            FColorBorderSelected = cValue;
            break;
        }
        case eColorHighlight:
        {
            FColorHighlight = cValue;
            break;
        }
    }
    // redraw the control
    Invalidate();
}
//---------------------------------------------------------------------------
// SetBool
/**
 * Sets properties of the Control by Index
 * @param   iIndex      the index of the property type to set
 * @param   bValue      the value to set the property to
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::SetBool(int iIndex, bool bValue)
{
    switch(iIndex)
    {
        case eFlagSelected:
        {
            if (FSelected != bValue)
            {
                // redraw the control
                Invalidate();
                if (false == FGrouped)
                {
                    FSelected = bValue && m_bMouseButtonDown;
                }
                else
                {
                    FSelected = bValue;
                    if (true == bValue)
                    {
                        UnselectButtons();
                    }
                }
            }
            break;
        }
        case eFlagGrouped:
        {
            FGrouped = bValue;
            if (FSelected)
            {
                UnselectButtons();
            }
            Invalidate();
        }
    }
}
//---------------------------------------------------------------------------
// SetString
/**
 * Sets properties of the Control by Index
 * @param   iIndex      the index of the property type to set
 * @param   sValue      the value to set the property to
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::SetString(int iIndex, String sValue)
{
    switch(iIndex)
    {
        case eStringCaption:
        {
            FCaption = sValue;
            break;
        }
    }
    Invalidate();
}
//---------------------------------------------------------------------------
// SetInt
/**
 * Sets properties of the Control by Index
 * @param   iIndex      the index of the property type to set
 * @param   iValue      the value to set the property to
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::SetInt(int iIndex, int iValue)
{
    switch(iIndex)
    {
        case eIntIconIndex:
        {
            FIconIndex = iValue;
            break;
        }
        case eIntCornerWidth:
        {
            FCornerWidth = iValue;
            break;
        }
        case eIntCornerHeight:
        {
            FCornerHeight = iValue;
            break;
        }
    }
    Invalidate();
}
//---------------------------------------------------------------------------
// SetIcons
/**
 * Sets properties of the Control by Index
 * @param   iIndex      the index of the property type to set
 * @param   ImageList   the image list to set the property to
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::SetIcons(int iIndex, TImageList* Icons)
{
    switch(iIndex)
    {
        case eIconsHot:
        {
            FIconsHot = Icons;
            break;
        }
        case eIconsCold:
        {
            FIconsCold = Icons;
            break;
        }
    }
    Invalidate();
}
//---------------------------------------------------------------------------
// SetFont
/**
 * Sets font properties of the Control
 * @param   pFont   the font properties
 * @author  Tony Thompson
 * @date    Created 4 December 2005
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::SetFont(TFont* pFont)
{
    FFont->Assign(pFont);
    Invalidate();
}
//---------------------------------------------------------------------------
// MouseDown
/**
 * MouseDown event handler for the control.  This handler takes care of the mundane
 * mouse tasks, and asks the derived control to handle the event itself.
 * @param   Button the mouse button pressed
 * @param   Shift the state of the shift keys
 * @param   X the X position of the mouse
 * @param   Y the Y position of the mouse
 * @author  Tony Thompson
 * @date    Created 14 March 2002
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::MouseDown (TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (true == Enabled)
    {
        // let the derived control process the event
        DoMouseDown(Button, Shift, X, Y);

        // trigger the on mouse down event if required
        if(OnMouseDown)
        {
            OnMouseDown(this, Button, Shift, X, Y);
        }
    }
}
//---------------------------------------------------------------------------
// MouseUp
/**
 * MouseUp event handler for the control.  This handler takes care of the mundane
 * mouse tasks, and asks the derived control to handle the event itself.
 * @param   Button the mouse button pressed
 * @param   Shift the state of the shift keys
 * @param   X the X position of the mouse
 * @param   Y the Y position of the mouse
 * @author  Tony Thompson
 * @date    Created 14 March 2002
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::MouseUp (TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (true == Enabled)
    {
        // let the derived control process the event
        DoMouseUp(Button, Shift, X, Y);
        if(OnMouseUp)
        {
            OnMouseUp(this, Button, Shift, X, Y);
        }
    }
}
//---------------------------------------------------------------------------
// MouseMove
/**
 * MouseMove event handler for the control.  This handler takes care of the mundane
 * mouse tasks, and asks the derived control to handle the event itself.
 * @param   Shift the state of the shift keys
 * @param   X the X position of the mouse
 * @param   Y the Y position of the mouse
 * @author  Tony Thompson
 * @date    Created 14 March 2002
 */
//---------------------------------------------------------------------------
void __fastcall KIconButton::MouseMove (Classes::TShiftState Shift, int X, int Y)
{
    if (true == Enabled)
    {
        // let the derived control process the event
        DoMouseMove(Shift, X, Y);
        if(OnMouseMove)
        {
            OnMouseMove(this, Shift, X, Y);
        }
    }
}
//---------------------------------------------------------------------------
// Register
/**
 * Registers the control with the Borland Builder IDE
 * @author  Tony Thompson
 * @date    Created 18 September 2003
 */
//---------------------------------------------------------------------------
namespace Kiconbutton
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(KIconButton)};
         RegisterComponents("Scorpio", classes, 0);
    }
}
//---------------------------------------------------------------------------
