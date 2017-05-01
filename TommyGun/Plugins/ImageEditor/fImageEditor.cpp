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
#pragma link "KSlider"
#pragma link "KRegistry"
#pragma link "KSpinEdit"
//-- NAMESPACES -------------------------------------------------------------
using namespace Scorpio;
using namespace Logging;
using namespace ImageEditor;
//-- VCL FORM OBJECT --------------------------------------------------------
TfrmImageEditor *frmImageEditor;
const String g_sInvalidChars = "\\ / : * ? \" < > | & ^\n\n";
const String g_sBlank        = "";
const TCursor g_SelectCursor = (TCursor)99;
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
__fastcall TfrmImageEditor::TfrmImageEditor(TComponent* Owner)
    : TForm(Owner),
      m_bInitialized(false),
      m_bSaved(false),
      m_bPasting(false),
      m_bToolbarVisible(true),
      m_PluginHandle(NULL),
      //m_pImageManager(NULL),
      m_pImage(NULL),
      m_pCanvas(NULL),
      m_pPasteObject(NULL),
      m_pUnderlay1(NULL),
      m_pUnderlay2(NULL),
      m_sOwner(""),
      m_iMagnification(2),
      m_fModeScaleX(1.f),
      m_fModeScaleY(1.f)
{
    RL_METHOD
    m_pCanvas = new Graphics::TBitmap();
    m_pPasteObject = new Graphics::TBitmap();
    m_pUnderlay1 = new Graphics::TBitmap();
    m_pUnderlay2 = new Graphics::TBitmap();

    m_Selection.Active = false;
    m_Selection.Dragging = false;
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
__fastcall TfrmImageEditor::~TfrmImageEditor()
{
    RL_METHOD
    SAFE_DELETE(m_pUnderlay1);
    SAFE_DELETE(m_pUnderlay2);
    SAFE_DELETE(m_pPasteObject);
    SAFE_DELETE(m_pCanvas);
    SAFE_DELETE(frmImageResize);
    SAFE_DELETE(frmImageMask);
    SAFE_DELETE(frmChangePalette);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::FormCreate(TObject *Sender)
{
    //sbxEditor->DoubleBuffered = true;
    panMapTiles->DoubleBuffered = true;
    panTools->DoubleBuffered = true;
    panOptions->DoubleBuffered = true;
    pgcTools->DoubleBuffered = true;
    MenusAdd();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::slrDisplayMagnificationChange(TObject *Sender)
{
    edtDisplayScreenMagnification->Value = slrDisplayMagnification->Position;
    UpdateCanvasMagnification();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::UpdateCanvasMagnification()
{
    m_iMagnification = slrDisplayMagnification->Position;
    if (true == SAFE_PTR(m_pImage))
    {
        imgCanvas->Canvas->Brush->Color = panBackgroundColor->Color;
        imgCanvas->Width  = (m_pImage->Width  * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification) + 1;
        imgCanvas->Height = (m_pImage->Height * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification) + 1;
        imgCanvas->Picture->Bitmap->Width  = imgCanvas->Width;
        imgCanvas->Picture->Bitmap->Height = imgCanvas->Height;
        m_pCanvas->Width  = imgCanvas->Width;
        m_pCanvas->Height = imgCanvas->Height;
        m_pCanvas->PixelFormat = m_pImage->Palette->PixelFormat;
        CenterImage();
    }
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actZoomInExecute(TObject *Sender)
{
    slrDisplayMagnification->Position = slrDisplayMagnification->Position + 1;
    //RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actZoomOutExecute(TObject *Sender)
{
    slrDisplayMagnification->Position = slrDisplayMagnification->Position - 1;
    //RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::imgCanvasMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    float iScalarX = ((float)m_pImage->Palette->ScalarX / m_fModeScaleX);
    float iScalarY = ((float)m_pImage->Palette->ScalarY / m_fModeScaleY);
    m_bSnapToChar = Shift.Contains(ssShift);
    if (!m_bPasting)
    {
        if (false == tbnToolSelect->Down)
        {
            if (true == SAFE_PTR(m_pImage) && g_Plugin->DoToolMouseDown(m_pImage, Button, Shift, X / iScalarX / m_iMagnification, Y / iScalarY / m_iMagnification))
            {
                if (true == m_pImage->Draw(m_pCanvas->Canvas, m_iMagnification))
                {
                    UpdateImage();
                }
            }
        }
        else
        {
            if (!m_Selection.Active)
            {
                m_Selection.Dragging = Shift.Contains(ssLeft);
            }
            else
            {
                // deactive the selection if clicked from outside the selection rect
                m_Selection.Active = Shift.Contains(ssLeft) && PtInRect(m_Selection.Rect, TPoint(X / iScalarX / m_iMagnification, Y / iScalarY / m_iMagnification));
                // and start the dragging if it was clicked outside
                m_Selection.Dragging = !m_Selection.Active;
                if (m_Selection.Active)
                {
                    // workout the paste offsets
                    m_PasteOffset.x = (X / iScalarX / m_iMagnification) - m_Selection.Rect.Left;
                    m_PasteOffset.y = (Y / iScalarY / m_iMagnification) - m_Selection.Rect.Top;
                    // do copy/paste or cut/paste
                    if (Shift.Contains(ssCtrl))
                    {
                        EditCopy();
                        EditPaste();
                    }
                    else
                    {
                        EditCut();
                        EditPaste();
                    }
                    m_Selection.X = m_Selection.Rect.Left;
                    m_Selection.Y = m_Selection.Rect.Top;
                }
            }
            if (true == m_Selection.Dragging)
            {
                m_Selection.RectLast = TRect(0, 0, 0, 0);//imgCanvas->Width, imgCanvas->Height);
                m_Selection.X = X / iScalarX / m_iMagnification;
                m_Selection.Y = Y / iScalarY / m_iMagnification;
                if (!m_bSnapToChar)
                {
                    m_Selection.Rect = TRect(m_Selection.X, m_Selection.Y, m_Selection.X + 1, m_Selection.Y + 1);
                }
                else
                {
                    m_Selection.X = (m_Selection.X >> 3) << 3;
                    m_Selection.Y = (m_Selection.Y >> 3) << 3;
                    m_Selection.Rect = TRect(m_Selection.X, m_Selection.Y, m_Selection.X + 8, m_Selection.Y + 8);
                }
            }
            else
            {
                m_Selection.Rect = TRect(0, 0, imgCanvas->Width, imgCanvas->Height);
                m_Selection.RectLast = m_Selection.Rect;
            }
            if (true == SAFE_PTR(m_pImage))
            {
                m_pImage->SetSelectionRect(m_Selection.Rect);
                m_Selection.Rect = m_pImage->GetSelectionRect();
            }
            UpdateImage();
        }
    }
    else
    {
        if (Shift.Contains(ssLeft))
        {
            // paste the object into the image
            m_Selection.X = X / iScalarX / m_iMagnification;
            m_Selection.Y = Y / iScalarY / m_iMagnification;
            if (m_bSnapToChar)
            {
                m_Selection.X = (m_Selection.X >> 3) << 3;
                m_Selection.Y = (m_Selection.Y >> 3) << 3;
            }
            PasteObject();
        }
        m_bPasting = false;
        UpdateImage();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::imgCanvasMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    float iScalarX = ((float)m_pImage->Palette->ScalarX / m_fModeScaleX);
    float iScalarY = ((float)m_pImage->Palette->ScalarY / m_fModeScaleY);
    SetStatusSlot(m_PluginHandle, "P:[" + ZeroPadInt(X / iScalarX / m_iMagnification    , 3) + "," + ZeroPadInt(Y / iScalarY / m_iMagnification    , 3) + "]", 0);
    SetStatusSlot(m_PluginHandle, "C:[" + ZeroPadInt(X / iScalarX / m_iMagnification / 8, 2) + "," + ZeroPadInt(Y / iScalarY / m_iMagnification / 8, 2) + "]", 1);
    if (true == SAFE_PTR(m_pImage))
    {
        SetStatusSlot(m_PluginHandle, "A:[" + m_pImage->Palette->GetColorAsString(*m_pImage, X / iScalarX / m_iMagnification, Y / iScalarY / m_iMagnification) + "]" , 2);
    }
    else
    {
        SetStatusSlot(m_PluginHandle, "", 2);
    }
    if (!m_bPasting)
    {
        if (false == tbnToolSelect->Down)
        {
            imgCanvas->Cursor = g_Plugin->DoToolCursor();
            if (true == SAFE_PTR(m_pImage) && g_Plugin->DoToolMouseMove(m_pImage, Shift, X / iScalarX / m_iMagnification, Y / iScalarY / m_iMagnification))
            {
                if (true == m_pImage->Draw(m_pCanvas->Canvas, m_iMagnification))
                {
                    UpdateImage();
                }
            }
        }
        else
        {
            m_bSnapToChar = Shift.Contains(ssShift);
            imgCanvas->Cursor = g_SelectCursor;
            if (m_Selection.Active && PtInRect(m_Selection.Rect, TPoint(X / iScalarX / m_iMagnification, Y / iScalarY / m_iMagnification)))
            {
                imgCanvas->Cursor = crSize;
            }
            if (true == Shift.Contains(ssLeft))
            {
                if (true == m_Selection.Dragging)
                {
                    if (!m_bSnapToChar)
                    {
                        int iEX = (X / iScalarX / m_iMagnification) + 1;
                        int iEY = (Y / iScalarY / m_iMagnification) + 1;
                        m_Selection.Rect = TRect(std::min(m_Selection.X, iEX), std::min(m_Selection.Y, iEY), std::max(m_Selection.X, iEX), std::max(m_Selection.Y, iEY));
                    }
                    else
                    {
                        X = (X >> 3) << 3;
                        Y = (Y >> 3) << 3;
                        int iEX = (X / iScalarX / m_iMagnification) + 8;
                        int iEY = (Y / iScalarY / m_iMagnification) + 8;
                        iEX = (iEX >> 3) << 3;
                        iEY = (iEY >> 3) << 3;
                        m_Selection.Rect = TRect(std::min(m_Selection.X, iEX), std::min(m_Selection.Y, iEY), std::max(m_Selection.X, iEX), std::max(m_Selection.Y, iEY));
                    }
                    if (true == SAFE_PTR(m_pImage))
                    {
                        m_pImage->SetSelectionRect(m_Selection.Rect);
                        m_Selection.Rect = m_pImage->GetSelectionRect();
                        UpdateImage();
                    }
                }
            }
        }
    }
    else
    {
        m_bSnapToChar = Shift.Contains(ssShift);
        if (true == SAFE_PTR(m_pImage))
        {
            m_Selection.X = X / iScalarX / m_iMagnification;
            m_Selection.Y = Y / iScalarY / m_iMagnification;
            if (Shift.Contains(ssShift))
            {
                m_Selection.X = (m_Selection.X >> 3) << 3;
                m_Selection.Y = (m_Selection.Y >> 3) << 3;
            }
            imgCanvas->Cursor = g_SelectCursor;
            UpdateImage();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::imgCanvasMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (false == tbnToolSelect->Down)
    {
        if (true == SAFE_PTR(m_pImage))
        {
            float iScalarX = ((float)m_pImage->Palette->ScalarX / m_fModeScaleX);
            float iScalarY = ((float)m_pImage->Palette->ScalarY / m_fModeScaleY);
            if (g_Plugin->DoToolMouseUp(m_pImage, Button, Shift, X / iScalarX / m_iMagnification, Y / iScalarY / m_iMagnification))
            {
                if (true == m_pImage->Draw(m_pCanvas->Canvas, m_iMagnification))
                {
                    UpdateImage();
                }
            }
            g_MiniPluginManager.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
            String sName = m_pImage->Name;
            PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_IMAGE_CHANGED, (LPDATA)&sName, (DWORD)&m_sOwner, 3);
        }
    }
    else
    {
        if (Button == mbLeft && m_bPasting)
        {
            float iScalarX = ((float)m_pImage->Palette->ScalarX / m_fModeScaleX);
            float iScalarY = ((float)m_pImage->Palette->ScalarY / m_fModeScaleY);
            // paste the object into the image
            m_Selection.X = X / iScalarX / m_iMagnification;
            m_Selection.Y = Y / iScalarY / m_iMagnification;
            if (m_bSnapToChar)
            {
                m_Selection.X = (m_Selection.X >> 3) << 3;
                m_Selection.Y = (m_Selection.Y >> 3) << 3;
            }
            PasteObject();
            m_bPasting = false;
            UpdateImage();
        }
        if (m_Selection.Dragging && !m_Selection.Active)
        {
            m_Selection.Active = true;
            m_Selection.Dragging = false;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::sbxEditorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    // scroll the image using the middle mouse button
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::tbnToolSelectClick(TObject *Sender)
{
    m_Selection.Rect = TRect(0,0,imgCanvas->Width,imgCanvas->Height);
    if (true == SAFE_PTR(m_pImage))
    {
        m_pImage->SetSelectionRect(m_Selection.Rect);
        m_Selection.Rect = m_pImage->GetSelectionRect();
    }
    m_Selection.Active = false;
    m_Selection.Dragging = false;
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::cbrImageEditorDblClick(TObject *Sender)
{
    m_bToolbarVisible               =!m_bToolbarVisible;
    tbrImageGridTools->Visible      = m_bToolbarVisible;
    tbrImagePaintTools->Visible     = m_bToolbarVisible;
    tbrPaletteAttributes->Visible   = m_bToolbarVisible;
    for (int i = 0; i < (int)m_ToolBars.size(); i++)
    {
        m_ToolBars[i]->Visible      = m_bToolbarVisible;
    }
    for (int i = 0; i < (int)m_ToolBarMenus.size(); i++)
    {
        m_ToolBarMenus[i]->Checked  = m_bToolbarVisible;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::tbnPaletteShowAttributesClick(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImage) && true == SAFE_PTR(m_pImage->Palette))
    {
        m_pImage->Palette->ShowAttributes = tbnPaletteShowAttributes->Down;
        m_pImage->Invalidate();
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::edtDisplayScreenMagnificationChange(TObject *Sender)
{
    slrDisplayMagnification->Position = edtDisplayScreenMagnification->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actMaskGenerateExecute(TObject *Sender)
{
    if (false == SAFE_PTR(frmImageMask))
    {
        frmImageMask = new TfrmImageMask(NULL);
    }
    if (frmImageMask->Execute(m_pImage->Palette))
    {
        //PushUndo(m_pImage, utUndo, "Image:Generate Mask");
        ZXImageManager* pImageManager;
        TypeGetImageManager(NULL, pImageManager);
        pImageManager->GenerateMask(m_sOwner, m_pImage, frmImageMask->m_bBorderStyle, clFuchsia/*frmImageMask->cmbColors->ItemIndex*/);
        //m_pImage->GenerateMask(frmImageMask->m_bBorderStyle, frmImageMask->cmbColors->ItemIndex);
        //PushUndo(m_pImage, utRedo, "Image:Generate Mask");
        UpdateImage();
        RefreshView();
        g_MiniPluginManager.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
    }
    //RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actMaskModeOffExecute(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImage))
    {
        ZXImageManager* pImageManager;
        TypeGetImageManager(NULL, pImageManager);
        pImageManager->SetMaskMode(false);
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actMaskModeOnExecute(TObject *Sender)
{
    tbnAnimationUnderlay->Down = false;
    if (true == SAFE_PTR(m_pImage))
    {
        ZXImageManager* pImageManager;
        TypeGetImageManager(NULL, pImageManager);
        pImageManager->SetMaskMode(true);
        m_pImage->MaskAlpha = (float)edtMaskTransparency->Value / 100.f;
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actMaskInvertExecute(TObject *Sender)
{
    if (true == SAFE_PTR(m_pImage))
    {
        ZXImageManager* pImageManager;
        TypeGetImageManager(NULL, pImageManager);
        pImageManager->InvertMask(m_sOwner, m_pImage);
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::edtMaskTransparencyChange(TObject *Sender)
{
    slrMaskTransparency->Position = edtMaskTransparency->Value;
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::chkAutoMagnificationClick(TObject *Sender)
{
    lblDisplayScreenMagnification->Enabled = !chkAutoMagnification->Checked;
    edtDisplayScreenMagnification->Enabled = !chkAutoMagnification->Checked;
    slrDisplayMagnification->Enabled = !chkAutoMagnification->Checked;
    cmdZoomIn->Enabled = !chkAutoMagnification->Checked;
    cmdZoomOut->Enabled = !chkAutoMagnification->Checked;
    actZoomIn->Enabled = !chkAutoMagnification->Checked;
    actZoomOut->Enabled = !chkAutoMagnification->Checked;
    UpdateMagnification();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::sbxEditorResize(TObject *Sender)
{
    UpdateMagnification();
    RefreshView();
    CenterImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::panMaskColorClick(TObject *Sender)
{
    dlgColor->Color = panMaskColor->Color;
    if (true == dlgColor->Execute())
    {
        panMaskColor->Color = dlgColor->Color;
        if (true == SAFE_PTR(m_pImage))
        {
            m_pImage->MaskColor = dlgColor->Color;
        }
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::slrMaskTransparencyChange(TObject *Sender)
{
    edtMaskTransparency->Value = slrMaskTransparency->Position;
    if (true == SAFE_PTR(m_pImage))
    {
        m_pImage->MaskAlpha = (float)slrMaskTransparency->Position / 100.f;
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::panBackgroundColorClick(TObject *Sender)
{
    dlgColor->Color = panBackgroundColor->Color;
    if (true == dlgColor->Execute())
    {
        panBackgroundColor->Color = dlgColor->Color;
        if (true == SAFE_PTR(m_pImage))
        {
            sbxEditor->Color = dlgColor->Color;
        }
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::panChrLineColorClick(TObject *Sender)
{
    dlgColor->Color = panChrLineColor->Color;
    if (true == dlgColor->Execute())
    {
        panChrLineColor->Color = dlgColor->Color;
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::panPixelLineColorClick(TObject *Sender)
{
    dlgColor->Color = panPixelLineColor->Color;
    if (true == dlgColor->Execute())
    {
        panPixelLineColor->Color = dlgColor->Color;
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::cmdRestoreDefaultsClick(TObject *Sender)
{
    int iAnswer;

    Message
    (
        mbtQuestion,
        "Overwrite current settings, with defaults?",
        "Are you sure you want to overwrite your current settings",
        "Restoring the default settings will overwrite all your current settings.\n\n"
        "Are you sure you would like to do this?\n\n"
        "Click\n"
        "\tYes\tto Overwrite the current settings with the Default settings.\n"
        "\tNo\tto leave the current settings as they are.",
        "No",
        "Yes",
        "",
        iAnswer
    );
    if (iAnswer == 1)
    {
        chkCenterImage->Checked = false;
        chkGridCharacter->Checked = false;
        chkGridPixel->Checked = false;
        chkAutoMagnification->Checked = true;
        edtMaskTransparency->Value = 75;
        slrMaskTransparency->Position = 75;
        panBackgroundColor->Color = clWhite;
        panChrLineColor->Color = TColor(0x0048BAF7);
        panPixelLineColor->Color = TColor(0x00004080);
        panMaskColor->Color = clRed;
        radModeScaleDefault->Checked = true;
        slrCustomXScale->Position = 2;
        slrCustomYScale->Position = 2;
        sbxEditor->Color = clWhite;
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actTogglePixelGridExecute(TObject *Sender)
{
    static bool bSetting = false;
    if (false == bSetting)
    {
        if (Sender != tbnGridPixel && Sender != chkGridPixel)
        {
            bSetting = true;
            chkGridPixel->Checked = !chkGridPixel->Checked;
            tbnGridPixel->Down = chkGridPixel->Checked;
            bSetting = false;
        }
        else if (Sender != chkGridPixel)
            chkGridPixel->Checked = tbnGridPixel->Down;
        else
            tbnGridPixel->Down = chkGridPixel->Checked;
        RefreshView();
        CenterImage();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actToggleCharGridExecute(TObject *Sender)
{
    static bool bSetting = false;
    if (false == bSetting)
    {
        if (Sender != tbnGridCharacter && Sender != chkGridCharacter)
        {
            bSetting = true;
            chkGridCharacter->Checked = !chkGridCharacter->Checked;
            tbnGridCharacter->Down = chkGridCharacter->Checked;
            bSetting = false;
        }
        else if (Sender == tbnGridCharacter)
            chkGridCharacter->Checked = tbnGridCharacter->Down;
        else if (Sender == chkGridCharacter)
            tbnGridCharacter->Down = chkGridCharacter->Checked;

        RefreshView();
        CenterImage();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::chkCenterImageClick(TObject *Sender)
{
    CenterImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::radModeScaleDefaultClick(TObject *Sender)
{
    UpdateModeScale();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::appEventsMessage(tagMSG &Msg, bool &Handled)
{
    if (!chkAutoMagnification->Checked && Msg.message == WM_MOUSEWHEEL)
    {
        int WheelDelta = GET_WHEEL_DELTA_WPARAM(Msg.wParam);
        if (WheelDelta > 0 && actZoomOut->Enabled)
        {
            actZoomOutExecute(NULL);
            Handled = true;
        }
        if (WheelDelta < 0 && actZoomIn->Enabled)
        {
            actZoomInExecute(NULL);
            Handled = true;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::tbnImageResizeClick(TObject *Sender)
{
    if (frmImageResize == NULL)
    {
        frmImageResize = new TfrmImageResize(NULL);
    }
    if (frmImageResize && SAFE_PTR(m_pImage))
    {
        if (frmImageResize->Execute(m_pImage))
        {
            // resize the current image
            //PushUndo(m_pImage, utUndo, "Image:Resize");
            ResizeImage(frmImageResize->Left, frmImageResize->Top, frmImageResize->Width, frmImageResize->Height);
            //PushUndo(m_pImage, utRedo, "Image:Resize");
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actToggleAnimationUnderlayExecute(TObject *Sender)
{
    tbnMaskModeOff->Down = true;
    if (!tbnAnimationUnderlay->Down)
    {
        grpMasking->Caption = " Masking ";
        lblMaskTransparency->Caption = "Mask Transparency";
        lblMaskColor->Caption = "Mask Transparency Color";       
    }
    else
    {
        grpMasking->Caption = " Frame Underlay ";
        lblMaskTransparency->Caption = "Frame Transparency";
        lblMaskColor->Caption = "Frame Transparency Color";
    }
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::actToggleHotSpotExecute(TObject *Sender)
{
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::tbnImageChangePaletteClick(TObject *Sender)
{
    if (false == SAFE_PTR(frmChangePalette))
    {
        frmChangePalette = new TfrmChangePalette(NULL);
    }
    if (true == SAFE_PTR(frmChangePalette))
    {
        if (frmChangePalette->Execute())
        {
        }
    }
    SAFE_DELETE(frmChangePalette);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::edtDisplayScreenMagnificationChanged(TObject *Sender, int value)
{
    slrDisplayMagnification->Position = edtDisplayScreenMagnification->Value;
    slrDisplayMagnification->Repaint();
    //slrDisplayMagnificationChange(Sender);
    UpdateCanvasMagnification();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::edtMaskTransparencyChanged(TObject *Sender, int value)
{
    slrMaskTransparency->Position = edtMaskTransparency->Value;
    slrMaskTransparencyChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::pgcToolsDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    static Graphics::TBitmap* bm = NULL; 
    Control->Canvas->Brush->Color = clWhite;
    Control->Canvas->FillRect(Rect);
    TTabSheet* sheet = pgcTools->Pages[TabIndex];
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
    pgcTools->Images->Draw(Control->Canvas, rl + 10 + cx - cw - 20, rt + cy - 8, sheet->ImageIndex, true);

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

