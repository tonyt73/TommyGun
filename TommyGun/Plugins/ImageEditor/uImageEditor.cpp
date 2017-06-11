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
#include <clipbrd.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace ImageEditor;
//-- CONSTANTS --------------------------------------------------------------
const String g_sPluginTitle = "Images";
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
HRESULT __fastcall TfrmImageEditor::Initialise(TZX_HPLUGIN PluginHandle)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    // save the plugin handle
    m_PluginHandle = PluginHandle;
    // place the form onto the tab control
    TWinControl* tmpWindow = NULL;
    hResult = S_FALSE;
    tbrImageGridTools->CustomizeKeyName = "Software\\Scorpio\\TommyGun";
    tbrImageGridTools->CustomizeValueName = "ToolBars";
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
            //AddToolBar(tbrImagePaintTools);
            //AddToolBar(tbrImageGridTools);
            OnTabHide(NULL);
            LoadSettings();
            m_bInitialized = true;
            hResult = S_OK;
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
HRESULT __fastcall TfrmImageEditor::Release(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    SaveSettings();
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
bool __fastcall TfrmImageEditor::AddToolBar(TToolBar* ToolBar)
{
    static int iNextX = 0;
    bool bToolBarAdded = false;
    bool bToolBarAttached = false;
    ToolBar->Parent   = cbrImageEditor;
    ToolBar->Top      = 22;
    ToolBar->Left     = iNextX;
    iNextX           += ToolBar->Width;
    bToolBarAttached  = true;
    if (true == bToolBarAttached)
    {
        TMenuItem* ViewMenu = Application->MainForm->Menu->Items->Find("View");
        if (ViewMenu)
        {
            TMenuItem* Toolbars = ViewMenu->Find("Toolbars");
            if (Toolbars)
            {
                TMenuItem* ToolBarMenu  = new TMenuItem(NULL);
                ToolBarMenu->Caption    = ToolBar->Caption;
                ToolBarMenu->Checked    = true;
                ToolBarMenu->Tag        = (int)ToolBar;
                ToolBarMenu->OnClick    = OnMenuClick;
                ToolBarMenu->Visible    = S_OK == IsActivePlugin(m_PluginHandle);
                Toolbars->Add(ToolBarMenu);
                bToolBarAdded           = true;
                m_ToolBars.push_back(ToolBar);
                m_ToolBarMenus.push_back(ToolBarMenu);
            }
        }
    }
    tbrImagePaintTools->Left = 0;
    tbrImagePaintTools->Top  = 0;
    tbrImageGridTools->Left  = tbrImagePaintTools->Width;
    tbrImageGridTools->Top   = 0;
    return bToolBarAdded;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::OnMenuClick(TObject* Sender)
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
void __fastcall TfrmImageEditor::TrapTabEvents(TWinControl* Control)
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
void __fastcall TfrmImageEditor::OnTabHide(TObject *Sender)
{
    actZoomIn->Enabled = false;
    actZoomOut->Enabled = false;
    actToggleCharGrid->Enabled = false;
    actTogglePixelGrid->Enabled = false;
    MenusRemove();
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
void __fastcall TfrmImageEditor::OnTabShow(TObject *Sender)
{
    MenusAdd();
    actZoomIn->Enabled = true;
    actZoomOut->Enabled = true;
    actToggleCharGrid->Enabled = true;
    actTogglePixelGrid->Enabled = true;
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
    ZXImage::SetTransparentMode(chkTransparentHide->Checked);
    ZXImage::SetBackgroundColor(panBackgroundColor->Color);
    ZXImage::SetTransparentColor(panTransparentColor->Color);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::RefreshView(void)
{
    if (true == SAFE_PTR(m_pImage))
    {
        UpdateMagnification();
        imgCanvas->Canvas->Brush->Color = panBackgroundColor->Color;
        int iWidth  = (m_pImage->Width  * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification) + 1;
        int iHeight = (m_pImage->Height * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification) + 1;
        while (iWidth > 2048 || iHeight > 2048)
        {
            --m_iMagnification;
            iWidth  = (m_pImage->Width  * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification) + 1;
            iHeight = (m_pImage->Height * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification) + 1;
        };
        imgCanvas->Width  = iWidth;
        imgCanvas->Height = iHeight;
        imgCanvas->Picture->Bitmap->Width  = imgCanvas->Width;
        imgCanvas->Picture->Bitmap->Height = imgCanvas->Height;
        m_pCanvas->Width  = imgCanvas->Width;
        m_pCanvas->Height = imgCanvas->Height;
        imgCanvas->Picture->Bitmap->PixelFormat = m_pImage->Palette->PixelFormat;
        m_pImage->ReDraw();
        m_pImage->Draw(m_pCanvas->Canvas, m_iMagnification);
        UpdateImage();
    }
    else
    {
        imgCanvas->Width  = 0;
        imgCanvas->Height = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::SetImage(ZXImage* Image, const String& sOwner)
{
    m_bPasting = false;
    m_Selection.Active = false;
    m_Selection.Dragging = false;
    tbnImageResize->Enabled = false;
    if (true == SAFE_PTR(Image))
    {
        Image->Invalidate();
        g_Plugin->SelectPalette(Image->Palette);
        g_Plugin->DoToolImageChange(Image);
        tbnPaletteShowAttributes->Enabled = !Image->Palette->SupportsPixelsOnly;
        tbnPaletteHideAttributes->Enabled = !Image->Palette->SupportsPixelsOnly;
        actMaskModeOn->Enabled   = Image->IsMasked;
        actMaskGenerate->Enabled = Image->IsMasked;
        actMaskInvert->Enabled = Image->IsMasked;
        if (false == Image->IsMasked)
        {
            actMaskModeOn->Checked  = false;
            actMaskModeOff->Checked = true;
            tbnMaskModeOff->Down = true;
        }
        else
        {
            slrMaskTransparency->Position = Image->MaskAlpha * 100;
            actMaskModeOn->Checked  =  Image->MaskMode;
            actMaskModeOff->Checked = !Image->MaskMode;
            panMaskColor->Color     =  Image->MaskColor;
        }
        Image->SetSelectionRect(TRect(0, 0, Image->Width, Image->Height));
        tbnImageResize->Enabled = Image->CanResize;
    }
    m_pImage = Image;
    m_sOwner = sOwner;
    UpdateModeScale();
    UpdateMagnification();
    RefreshView();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmImageEditor::MergePaintToolBar(TToolBar* ToolBar)
{
    bool bMerged = false;
    if (true == SAFE_PTR(ToolBar))
    {
        TImageList* Images = dynamic_cast<TImageList*>(ToolBar->Images);
        if (true == SAFE_PTR(Images))
        {
            if (ToolBar->ButtonCount == Images->Count && Images->Width == imgPaintToolBar->Width && Images->Height == imgPaintToolBar->Height)
            {
                tbrImagePaintTools->Constraints->MinWidth = tbrImagePaintTools->Width + ToolBar->Width;
                tbrImagePaintTools->Constraints->MaxWidth = tbrImagePaintTools->Constraints->MinWidth;
                int iBarWidth = tbrImagePaintTools->Width;
                int iImages = imgPaintToolBar->Count;
                imgPaintToolBar->AddImages(Images);
                // images added, so add the toolbars buttons
                tbrImagePaintTools->RemoveControl(tbnToolSelect);
                tbrImagePaintTools->Width = tbrImagePaintTools->Width + ToolBar->Width;
                while(ToolBar->ButtonCount)
                {
                    // get the button from the toolbar
                    TToolButton* Button = ToolBar->Buttons[0];
                    Button->Grouped = true;
                    Button->Style = tbsCheck;
                    Button->AllowAllUp = false;
                    ToolBar->RemoveControl(Button);
                    tbrImagePaintTools->InsertControl(Button);
                    Button->ImageIndex = Button->ImageIndex + iImages;
                }
                tbrImagePaintTools->InsertControl(tbnToolSelect);
                bMerged = true;
            }
        }
    }
    return bMerged;
}
//---------------------------------------------------------------------------
String __fastcall TfrmImageEditor::ZeroPadInt(int iValue, int iSize)
{
    String sValue = "000" + IntToStr(iValue);
    sValue = sValue.SubString(sValue.Length() - iSize + 1, iSize);
    return sValue;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::PasteObject(void)
{
    if (true == SAFE_PTR(m_pImage))
    {
        Graphics::TBitmap* tmpBmp = new Graphics::TBitmap();
        if (true == SAFE_PTR(tmpBmp))
        {
            PushUndo(m_pImage, utUndo, "Edit:Paste");
            // get the image into a tmp bitmap
            tmpBmp->PixelFormat = m_pPasteObject->PixelFormat;
            tmpBmp->Width  = m_pImage->Width;
            tmpBmp->Height = m_pImage->Height;
            m_pImage->Draw(tmpBmp->Canvas);
            // paste the paste object into the tmp bitmap
            BitBlt
            (
                tmpBmp->Canvas->Handle,
                m_Selection.X,
                m_Selection.Y,
                m_rPaste.Width(),
                m_rPaste.Height(),
                m_pPasteObject->Canvas->Handle,
                m_rPaste.Left,
                m_rPaste.Top,
                SRCCOPY
            );
            // make the image convert the new pasted image
            m_pImage->ConvertBitmap(tmpBmp);
            PushUndo(m_pImage, utRedo, "Edit:Paste");
            SAFE_DELETE(tmpBmp);
            m_pImage->Invalidate();
            UpdateImage();
            RefreshView();
            g_MiniPluginManager.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
        }
        m_bPasting = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::DrawPasteObject(void)
{
    if (true == SAFE_PTR(m_pImage) && m_bPasting)
    {
        float fScalarX = (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification;
        float fScalarY = (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification;
        StretchBlt
        (
            m_pCanvas->Canvas->Handle,
            (m_Selection.X + m_PasteOffset.x) * fScalarX,
            (m_Selection.Y + m_PasteOffset.y) * fScalarY,
            m_rPaste.Width()  * fScalarX,
            m_rPaste.Height() * fScalarY,
            m_pPasteObject->Canvas->Handle,
            m_rPaste.Left,
            m_rPaste.Top,
            m_rPaste.Width(),
            m_rPaste.Height(),
            SRCCOPY
        );
        m_Selection.Active = true;
        m_Selection.Rect.Left   = m_Selection.X + m_PasteOffset.x;
        m_Selection.Rect.Top    = m_Selection.Y + m_PasteOffset.y;
        m_Selection.Rect.Right  = m_Selection.X + m_PasteOffset.x + m_rPaste.Width();
        m_Selection.Rect.Bottom = m_Selection.Y + m_PasteOffset.y + m_rPaste.Height();
        DrawSelection();
        m_Selection.Active = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::DrawPreviousFrame(void)
{
    if (tbnAnimationUnderlay->Down && true == SAFE_PTR(m_pImage) && m_iMagnification > 4)
    {
        ZXImageManager* pImageManager;
        TypeGetImageManager(NULL, pImageManager);
        if (SAFE_PTR(pImageManager))
        {
            ZXImage* pImage = pImageManager->GetPreviousFrame(m_pImage);
            if (SAFE_PTR(pImage))
            {
                m_pUnderlay1->Width  = pImage->Width;
                m_pUnderlay1->Height = pImage->Height;
                m_pUnderlay2->Width  = pImage->Width;
                m_pUnderlay2->Height = pImage->Height;
                m_pImage->Invalidate();
                m_pImage->Draw(m_pUnderlay1->Canvas, 1);
                pImage->Invalidate();
                pImage->Draw(m_pUnderlay2->Canvas, 1);
                // get the masks RGB colors as floats
                int MaskColor = ColorToRGB(m_pImage->MaskColor);
                float fMaskAlpha = m_pImage->MaskAlpha;
                float MaskR = (float)((MaskColor & 0x000000FF)      ) * fMaskAlpha;
                float MaskG = (float)((MaskColor & 0x0000FF00) >>  8) * fMaskAlpha;
                float MaskB = (float)((MaskColor & 0x00FF0000) >> 16) * fMaskAlpha;
                float fAlpha = 1.f - fMaskAlpha;
                unsigned int R = 0;
                unsigned int G = 0;
                unsigned int B = 0;
                unsigned int C = 0;
                TColor BgColor = pImage->Palette->GetColor(0);
                for (int y = 0; y < m_pImage->Height; y++)
                {
                    for (int x = 0; x < m_pImage->Width; x++)
                    {
                        if (m_pUnderlay2->Canvas->Pixels[x][y] != BgColor)
                        {
                            // blend the colors
                            int Color = ColorToRGB(m_pUnderlay1->Canvas->Pixels[x][y]);
                            float PixR = (float)((Color & 0x000000FF)      ) * fAlpha;
                            float PixG = (float)((Color & 0x0000FF00) >>  8) * fAlpha;
                            float PixB = (float)((Color & 0x00FF0000) >> 16) * fAlpha;
                            R = PixR + MaskR;
                            G = PixG + MaskG;
                            B = PixB + MaskB;
                            C = R + (G << 8) + (B << 16);
                            m_pUnderlay1->Canvas->Pixels[x][y] = (TColor)C;
                        }
                        else if (m_pUnderlay1->Canvas->Pixels[x][y] != BgColor)
                        {
                            // blend the colors
                            int Color = ColorToRGB(m_pUnderlay1->Canvas->Pixels[x][y]);
                            float PixR = (float)((Color & 0x000000FF)      ) * fAlpha;
                            float PixG = (float)((Color & 0x0000FF00) >>  8) * fAlpha;
                            float PixB = (float)((Color & 0x00FF0000) >> 16) * fAlpha;
                            R = PixR;
                            G = PixG;
                            B = PixB;
                            C = R + (G << 8) + (B << 16);
                            m_pUnderlay1->Canvas->Pixels[x][y] = (TColor)C;
                        }
                    }
                }
                StretchBlt
                (
                    m_pCanvas->Canvas->Handle,
                    0,
                    0,
                    m_pImage->Width * m_iMagnification,
                    m_pImage->Height * m_iMagnification,
                    m_pUnderlay1->Canvas->Handle,
                    0,
                    0,
                    m_pImage->Width,
                    m_pImage->Height,
                    SRCCOPY
                );
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::DrawGridLines(TRect& UpdateRect)
{
    //PERFORMANCE_PUSH
    float fScalarX = (m_pImage->Palette->ScalarX / m_fModeScaleX);
    float fScalarY = (m_pImage->Palette->ScalarY / m_fModeScaleY);
    m_pCanvas->Canvas->Pen->Color = panBackgroundColor->Color;
    m_pCanvas->Canvas->MoveTo(m_pCanvas->Width - 1, 0);
    m_pCanvas->Canvas->LineTo(m_pCanvas->Width - 1, m_pCanvas->Height - 1);
    m_pCanvas->Canvas->LineTo(0, m_pCanvas->Height - 1);

    if (true == tbnGridPixel->Down && 4 <= m_iMagnification)
    {
        m_pCanvas->Canvas->Pen->Color = panPixelLineColor->Color;//(TColor)0x00004080;
        int xs = UpdateRect.Left;
        int xe = UpdateRect.Right;
        int ys = UpdateRect.Top;
        int ye = UpdateRect.Bottom;
        for (int x = xs; x <= xe; x++)
        {
            m_pCanvas->Canvas->MoveTo(x * fScalarX * m_iMagnification, UpdateRect.Top    * fScalarY * m_iMagnification);
            m_pCanvas->Canvas->LineTo(x * fScalarX * m_iMagnification, UpdateRect.Bottom * fScalarY * m_iMagnification);
        }
        for (int y = ys; y <= ye; y++)
        {
            m_pCanvas->Canvas->MoveTo(UpdateRect.Left  * fScalarX * m_iMagnification, y * fScalarY * m_iMagnification);
            m_pCanvas->Canvas->LineTo(UpdateRect.Right * fScalarX * m_iMagnification, y * fScalarY * m_iMagnification);
        }
    }
    if (true == tbnGridCharacter->Down)
    {
        m_pCanvas->Canvas->Pen->Color = panChrLineColor->Color;//(TColor)0x0048BAF7;
        int xs = UpdateRect.Left   - UpdateRect.Left   % 8;
        int xe = UpdateRect.Right  - UpdateRect.Right  % 8;
        int ys = UpdateRect.Top    - UpdateRect.Top    % 8;
        int ye = UpdateRect.Bottom - UpdateRect.Bottom % 8;
        for (int x = xs; x <= xe; x += 8)
        {
            m_pCanvas->Canvas->MoveTo(x * fScalarX * m_iMagnification, UpdateRect.Top    * fScalarY * m_iMagnification);
            m_pCanvas->Canvas->LineTo(x * fScalarX * m_iMagnification, UpdateRect.Bottom * fScalarY * m_iMagnification);
        }
        for (int y = ys; y <= ye; y += 8)
        {
            m_pCanvas->Canvas->MoveTo(UpdateRect.Left  * fScalarX * m_iMagnification    , y * fScalarY * m_iMagnification);
            m_pCanvas->Canvas->LineTo(UpdateRect.Right * fScalarX * m_iMagnification + 1, y * fScalarY * m_iMagnification);
        }
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::DrawSelection(void)
{
    if (true == m_Selection.Active || true == m_Selection.Dragging)
    {
        m_pCanvas->Canvas->Pen->Color = clWhite;
        m_pCanvas->Canvas->Brush->Color = clBlack;
        m_pCanvas->Canvas->Pen->Style = psDot;
        //m_pCanvas->Canvas->Pen->Mode  = pmXor;
        //m_pCanvas->Canvas->Brush->Color = (TColor)clBlack;
        m_pCanvas->Canvas->MoveTo(m_Selection.Rect.Left  * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification, m_Selection.Rect.Top    * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification);
        m_pCanvas->Canvas->LineTo(m_Selection.Rect.Right * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification, m_Selection.Rect.Top    * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification);
        m_pCanvas->Canvas->LineTo(m_Selection.Rect.Right * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification, m_Selection.Rect.Bottom * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification);
        m_pCanvas->Canvas->LineTo(m_Selection.Rect.Left  * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification, m_Selection.Rect.Bottom * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification);
        m_pCanvas->Canvas->LineTo(m_Selection.Rect.Left  * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification, m_Selection.Rect.Top    * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification);
        m_pCanvas->Canvas->Pen->Style = psSolid;
        //m_pCanvas->Canvas->Pen->Mode  = pmCopy;
    }
    //PERFORMANCE_POP(__FUNC__);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::DrawHotSpot(void)
{
    if (m_pImage->UsesHotSpot && tbnShowHotSpot->Down)
    {
        int xs =   m_pImage->HotSpotX      * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification;
        int ys =   m_pImage->HotSpotY      * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification;
        int xe = ((m_pImage->HotSpotX + 1) * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification) - 1;
        int ye = ((m_pImage->HotSpotY + 1) * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification) - 1;

        m_pCanvas->Canvas->Pen->Color = clLime;
        m_pCanvas->Canvas->Pen->Width = m_iMagnification == 1 ? 1 : 2;
        m_pCanvas->Canvas->MoveTo(xs + (m_iMagnification >> 1), ys);
        m_pCanvas->Canvas->LineTo(xs + (m_iMagnification >> 1), ye);
        m_pCanvas->Canvas->MoveTo(xs, ys + (m_iMagnification >> 1));
        m_pCanvas->Canvas->LineTo(xe, ys + (m_iMagnification >> 1));
        m_pCanvas->Canvas->Pen->Width = 1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::UpdateImage(ZXImage* Image, bool bIsATypePlugin)
{
    // only update the current image being editted, stops a plugin from send it
    // redundant updates and crap.
    if (true == bIsATypePlugin)
    {
        // then change the current image to the supplied image
        m_pImage = Image;
        m_pImage->Invalidate();
        UpdateModeScale();
    }
    if (Image == m_pImage)
    {
        UpdateImage();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::UpdateImage(void)
{
    if (true == SAFE_PTR(m_pImage))
    {
        // calculate the largest update rect required
        TRect UpdateRect = m_pImage->DirtyRect;
        if (true == m_Selection.Active)
        {
            // selection, only need to update for this then
            //UpdateRect = m_Selection.RectLast;
            UpdateRect.Left   = std::min(m_Selection.RectLast.Left  , std::min(UpdateRect.Left  , m_Selection.Rect.Left  ));
            UpdateRect.Right  = std::max(m_Selection.RectLast.Right , std::max(UpdateRect.Right , m_Selection.Rect.Right ));
            UpdateRect.Top    = std::min(m_Selection.RectLast.Top   , std::min(UpdateRect.Top   , m_Selection.Rect.Top   ));
            UpdateRect.Bottom = std::max(m_Selection.RectLast.Bottom, std::max(UpdateRect.Bottom, m_Selection.Rect.Bottom));
        }
        m_pImage->Draw(m_pCanvas->Canvas, m_iMagnification, UpdateRect);
        DrawPreviousFrame();
        // draw the paste bitmap
        DrawPasteObject();
        // draw the grid lines and the selection
        DrawGridLines(UpdateRect);
        DrawSelection();
        DrawHotSpot();
        // show the results on the image
        BitBlt(imgCanvas->Picture->Bitmap->Canvas->Handle,
               UpdateRect.Left * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification,
               UpdateRect.Top  * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification,
             ((UpdateRect.Right  - UpdateRect.Left) * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification) + 1,
             ((UpdateRect.Bottom - UpdateRect.Top ) * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification) + 1,
               m_pCanvas->Canvas->Handle,
               UpdateRect.Left * (m_pImage->Palette->ScalarX / m_fModeScaleX) * m_iMagnification,
               UpdateRect.Top  * (m_pImage->Palette->ScalarY / m_fModeScaleY) * m_iMagnification,
               SRCCOPY);
        imgCanvas->Refresh();
        m_Selection.RectLast = m_Selection.Rect;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TfrmImageEditor::AddTab(const String& sCaption, Graphics::TBitmap* pBitmap, TTabSheet*& pTabSheet)
{
    bool bAdded = false;
    try
    {
        pTabSheet = new TTabSheet(this);
    }
    catch(EOutOfMemory&)
    {
        pTabSheet = NULL;
    }
    if (true == SAFE_PTR(pTabSheet))
    {
        pTabSheet->PageControl = pgcTools;
        pTabSheet->Caption     = sCaption;
        pTabSheet->PageIndex   = pgcTools->PageCount - 2;
        pTabSheet->TabVisible  = true;
        if (true == SAFE_PTR(pBitmap))
        {
            pTabSheet->ImageIndex = imgTabImages->AddMasked(pBitmap, clFuchsia);
        }
        pgcTools->ActivePageIndex = 0;
    }
    return bAdded;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::LoadSettings(void)
{
    bool bValue = false;
    int  iValue = 0;
    TColor cValue = clBlack;

    if (regScorpio->Read("ImageEditor", "CenterImage"     , bValue)) chkCenterImage->Checked = bValue;
    if (regScorpio->Read("ImageEditor", "BackgroundColor" , cValue)) panBackgroundColor->Color = cValue;
    if (regScorpio->Read("ImageEditor", "ShowGridChar"    , bValue)) chkGridCharacter->Checked = bValue;
    if (regScorpio->Read("ImageEditor", "ShowGridPixel"   , bValue)) chkGridPixel->Checked = bValue;
    if (regScorpio->Read("ImageEditor", "AutoMagnify"     , bValue)) chkAutoMagnification->Checked = bValue;
    if (regScorpio->Read("ImageEditor", "Magnification"   , iValue)) slrDisplayMagnification->Position = iValue;
    if (regScorpio->Read("ImageEditor", "MaskTransparency", iValue)) slrMaskTransparency->Position = iValue;
    if (regScorpio->Read("ImageEditor", "MaskColor"       , cValue)) panMaskColor->Color = cValue;
    if (regScorpio->Read("ImageEditor", "ChrLineColor"    , cValue)) panChrLineColor->Color = cValue;
    if (regScorpio->Read("ImageEditor", "PixelLineColor"  , cValue)) panPixelLineColor->Color = cValue;
    if (regScorpio->Read("ImageEditor", "XScaleFacter"    , iValue)) slrCustomXScale->Position = iValue;
    if (regScorpio->Read("ImageEditor", "YScaleFacter"    , iValue)) slrCustomYScale->Position = iValue;
    if (regScorpio->Read("ImageEditor", "ScaleMode"       , iValue))
    {
        radModeScaleDefault->Checked = iValue == 0;
        radModeScaleRemove->Checked  = iValue == 1;
        radModeScaleCustom->Checked  = iValue == 2;
        UpdateModeScale();
    }
    sbxEditor->Color = panBackgroundColor->Color;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::SaveSettings(void)
{
    regScorpio->Write("ImageEditor", "CenterImage"      , chkCenterImage->Checked           );
    regScorpio->Write("ImageEditor", "BackgroundColor"  , panBackgroundColor->Color         );
    regScorpio->Write("ImageEditor", "ShowGridChar"     , chkGridCharacter->Checked         );
    regScorpio->Write("ImageEditor", "ShowGridPixel"    , chkGridPixel->Checked             );
    regScorpio->Write("ImageEditor", "AutoMagnify"      , chkAutoMagnification->Checked     );
    regScorpio->Write("ImageEditor", "Magnification"    , slrDisplayMagnification->Position );
    regScorpio->Write("ImageEditor", "MaskTransparency" , slrMaskTransparency->Position     );
    regScorpio->Write("ImageEditor", "MaskColor"        , panMaskColor->Color               );
    regScorpio->Write("ImageEditor", "ChrLineColor"     , panChrLineColor->Color            );
    regScorpio->Write("ImageEditor", "PixelLineColor"   , panPixelLineColor->Color          );
    regScorpio->Write("ImageEditor", "XScaleFactor"     , slrCustomXScale->Position         );
    regScorpio->Write("ImageEditor", "YScaleFactor"     , slrCustomYScale->Position         );
    if (radModeScaleDefault->Checked) regScorpio->Write("ImageEditor", "ScaleMode" , 0);
    else if (radModeScaleRemove->Checked) regScorpio->Write("ImageEditor", "ScaleMode" , 1);
    else regScorpio->Write("ImageEditor", "ScaleMode" , 2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::EditCopy(void)
{
    if (m_Selection.Active && true == SAFE_PTR(m_pImage))
    {
        m_pPasteObject->Width  = m_pImage->Width;
        m_pPasteObject->Height = m_pImage->Height;
        m_pPasteObject->PixelFormat = m_pImage->Palette->PixelFormat;
        m_pImage->Draw(m_pPasteObject->Canvas);
        m_rPaste = m_Selection.Rect;
        SaveToClipboard(m_pPasteObject, m_rPaste);
        m_Selection.Active = false;
        m_Selection.Rect = TRect(0, 0, imgCanvas->Width, imgCanvas->Height);
        m_Selection.RectLast = m_Selection.Rect;
        m_pImage->SetSelectionRect(m_Selection.Rect);
        m_pImage->Invalidate();
        UpdateImage();
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::EditCut(void)
{
    if (m_Selection.Active && true == SAFE_PTR(m_pImage))
    {
        PushUndo(m_pImage, utUndo, "Edit:Cut");
        Graphics::TBitmap* tmpBmp = new Graphics::TBitmap();
        tmpBmp->Width = m_pImage->Width;
        tmpBmp->Height = m_pImage->Height;
        tmpBmp->PixelFormat = m_pImage->Palette->PixelFormat;
        m_pPasteObject->Width  = m_pImage->Width;
        m_pPasteObject->Height = m_pImage->Height;
        m_pPasteObject->PixelFormat = m_pImage->Palette->PixelFormat;
        m_pImage->Draw(m_pPasteObject->Canvas);
        m_pImage->Draw(tmpBmp->Canvas);
        tmpBmp->Canvas->Brush->Color = m_pImage->Palette->BrushColor;
        m_rPaste = m_Selection.Rect;
        SaveToClipboard(m_pPasteObject, m_rPaste);
        tmpBmp->Canvas->FillRect(m_rPaste);
        m_pImage->ConvertBitmap(tmpBmp);
        g_MiniPluginManager.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
        m_Selection.Active = false;
        m_Selection.Rect = TRect(0, 0, imgCanvas->Width, imgCanvas->Height);
        m_Selection.RectLast = m_Selection.Rect;
        m_pImage->SetSelectionRect(m_Selection.Rect);
        m_pImage->Invalidate();
        UpdateImage();
        //RefreshView();
        PushUndo(m_pImage, utRedo, "Edit:Cut");
        SAFE_DELETE(tmpBmp);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::EditPaste(void)
{
    if (true == SAFE_PTR(m_pImage))
    {
        if (Clipboard()->HasFormat(CF_BITMAP))
        {
            m_pPasteObject->Assign(Clipboard());
            m_rPaste = TRect(0, 0, m_pPasteObject->Width, m_pPasteObject->Height);
        }
        m_Selection.Rect = TRect(0, 0, imgCanvas->Width, imgCanvas->Height);
        m_Selection.RectLast = m_Selection.Rect;
        m_Selection.Active = false;
        m_pImage->SetSelectionRect(m_Selection.Rect);
        m_bPasting = true;
        m_PasteOffset.x = 0;
        m_PasteOffset.y = 0;
        m_pImage->Invalidate();
        UpdateImage();
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::PushUndo(ZXImage* pImage, ZXUndoType UndoType, String sTool)
{
    KXmlInfo Undo;
    Undo.Add("Operation", "ImageChange");
    Undo.Add("Plugin", "ImageEditor");
    Undo.Add("Description", sTool + " [" + pImage->Name + "]");
    KXmlInfo Image("Image");
    pImage->Save(Image, false);
    Undo.Add(Image);
    g_Plugin->NotifyPluginEvent(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, UndoType, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::SaveToClipboard(Graphics::TBitmap* Bitmap, TRect Rect)
{
    Graphics::TBitmap* ClipBitmap = new Graphics::TBitmap();
    if (true == SAFE_PTR(ClipBitmap))
    {
        ClipBitmap->PixelFormat = Bitmap->PixelFormat;
        ClipBitmap->Width = Rect.Width();
        ClipBitmap->Height = Rect.Height();
        BitBlt
        (
            ClipBitmap->Canvas->Handle,
            0,
            0,
            ClipBitmap->Width,
            ClipBitmap->Height,
            Bitmap->Canvas->Handle,
            Rect.Left,
            Rect.Top,
            SRCCOPY
        );
        Clipboard()->Assign(ClipBitmap);
        SAFE_DELETE(ClipBitmap);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::UpdateMagnification(void)
{
    if (true == chkAutoMagnification->Checked && true == SAFE_PTR(m_pImage))
    {
        // calculate the optimal size for the grid
        int iMagW = sbxEditor->Width  / (m_pImage->Width  * (m_pImage->Palette->ScalarX / m_fModeScaleX));
        int iMagH = sbxEditor->Height / (m_pImage->Height * (m_pImage->Palette->ScalarY / m_fModeScaleY));
        int iMag  = std::min(32, std::max(1, std::min(iMagW, iMagH)));
        if (slrDisplayMagnification->Position != iMag)
        {
            slrDisplayMagnification->Position = std::max(1, std::min(32, iMag));
            slrDisplayMagnificationChange(NULL);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::UpdateModeScale(void)
{
    bool bSupported = false;
    m_fModeScaleX = 1.f;
    m_fModeScaleY = 1.f;
    if (true == SAFE_PTR(m_pImage))
    {
        bSupported = m_pImage->Palette->ScalarX != 1.0f || m_pImage->Palette->ScalarY != 1.0f;
    }
    radModeScaleDefault->Enabled = bSupported;
    radModeScaleRemove->Enabled = bSupported;
    radModeScaleCustom->Enabled = bSupported;
    lblCustomXAxis->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    lblCustomYAxis->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    lblCustomX25->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    lblCustomX50->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    lblCustomX100->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    lblCustomX200->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    lblCustomY25->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    lblCustomY50->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    lblCustomY100->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    lblCustomY200->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    slrCustomXScale->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    slrCustomYScale->Enabled = radModeScaleCustom->Enabled && radModeScaleCustom->Checked;
    if (true == SAFE_PTR(m_pImage))
    {
        if (radModeScaleDefault->Checked)
        {
            m_fModeScaleX = 1.f;
            m_fModeScaleY = 1.f;
        }
        else if (radModeScaleRemove->Checked)
        {
            m_fModeScaleX = m_pImage->Palette->ScalarX;
            m_fModeScaleY = m_pImage->Palette->ScalarY;
        }
        else if (radModeScaleCustom->Checked)
        {
            float sf[4] = {4.f, 2.f, 1.0f, 0.5f};

            m_fModeScaleX = sf[slrCustomXScale->Position];
            m_fModeScaleY = sf[slrCustomYScale->Position];
        }
        m_pImage->ModeScaleX = m_fModeScaleX;
        m_pImage->ModeScaleY = m_fModeScaleY;
    }

    UpdateMagnification();
    RefreshView();
    CenterImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::CenterImage(void)
{
    if (chkCenterImage->Checked)
    {
        imgCanvas->Left = std::max(0, (sbxEditor->Width  - imgCanvas->Width ) / 2);
        imgCanvas->Top  = std::max(0, (sbxEditor->Height - imgCanvas->Height) / 2);
    }
    else
    {
        imgCanvas->Left = 0;
        imgCanvas->Top  = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::MenusAdd(void)
{
    if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
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
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::MenusRemove(void)
{
    if (true == SAFE_PTR(Application->MainForm) && true == SAFE_PTR(Application->MainForm->Menu))
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
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageEditor::ResizeImage(int iLeft, int iTop, int iWidth, int iHeight)
{
    ZXImageManager* pImageManager;
    TypeGetImageManager(NULL, pImageManager);
    pImageManager->ResizeImage(m_sOwner, m_pImage, iLeft, iTop, iWidth, iHeight);
    UpdateImage();
    RefreshView();
    g_MiniPluginManager.Notify(NULL, IMAGE_EDITOR_IMAGE_CHANGED, NULL, 0, 0);
}
//---------------------------------------------------------------------------

