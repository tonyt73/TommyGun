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
TdlgImageSheetImporter *dlgImageSheetImporter;
//---------------------------------------------------------------------------
__fastcall TdlgImageSheetImporter::TdlgImageSheetImporter(TComponent* Owner)
: TForm(Owner)
, m_ImageSheet(NULL)
, m_WorkSheet(NULL)
, m_PaletteSignatures(NULL)
, m_Operation(opNone)
, m_GridX(0)
, m_GridY(0)
, m_GridW(8)
, m_GridH(8)
, m_StartX(0)
, m_StartY(0)
, m_EndX(0)
, m_EndY(0)
, m_SelSX(-1)
, m_SelSY(-1)
, m_SelEX(-1)
, m_SelEY(-1)
{
    m_ImageSheet = new Graphics::TBitmap();
    m_WorkSheet  = new Graphics::TBitmap();
}
//---------------------------------------------------------------------------
__fastcall TdlgImageSheetImporter::~TdlgImageSheetImporter()
{
    delete m_WorkSheet;
    delete m_ImageSheet;
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::panMaskColourClick(TObject *Sender)
{
    if (dlgColour->Execute())
    {
        panMaskColour->Color = dlgColour->Color;
    }
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::btnHelpClick(TObject *Sender)
{
    panHelp->Visible = btnHelp->Down;
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::imgSheetMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    X /= edtZoom->Value;
    Y /= edtZoom->Value;
    if (m_Operation == opNone)
    {
        if (Button == mbLeft)
        {
            // select grid elements
            m_Operation     = opSelecting;
            m_SelEX         = X;
            m_SelEY         = Y;
            if (!Shift.Contains(ssCtrl) || X < 0 || Y < 0)
            {
                m_SelSX     = X;
                m_SelSY     = Y;
            }
        }
        else if (Button == mbRight)
        {
            if (Shift.Contains(ssShift))
            {
                m_Operation = opResizing;
                m_PanningX  = m_GridW;
                m_PanningY  = m_GridH;
                m_StartX    = X;
                m_StartY    = Y;
                m_GridX     = X;
                m_GridY     = Y;
            }
            else
            {
                m_Operation = opPanning;
                m_PanningX  = X;
                m_PanningY  = Y;
                m_StartX    = X;
                m_StartY    = Y;
            }
        }
        else if (Button == mbMiddle)
        {
            m_Operation = opScrolling;
            m_StartX = X;
            m_StartY = Y;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::imgSheetMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    X /= edtZoom->Value;
    Y /= edtZoom->Value;
    if (panHelp->Visible)
    {
        btnHelp->Down = false;
        panHelp->Visible = false;
    }
    if (Shift.Contains(ssLeft) && m_Operation == opSelecting)
    {
        m_SelEX = std::max(0, std::min(X, m_ImageSheet->Width ));
        m_SelEY = std::max(0, std::min(Y, m_ImageSheet->Height));
        ResetCanvas(true);
    }
    else if (Shift.Contains(ssRight) && m_Operation == opPanning)
    {
        m_GridX = m_PanningX + (X - m_StartX);
        m_GridY = m_PanningY + (Y - m_StartY);
        ResetCanvas(true);
    }
    else if (Shift.Contains(ssRight) && m_Operation == opResizing)
    {
        m_GridW = std::max(1, m_PanningX + (X - m_StartX));
        m_GridH = std::max(1, m_PanningY + (Y - m_StartY));
        ResetCanvas(true);
    }
    else if (Shift.Contains(ssMiddle) && m_Operation == opScrolling)
    {
        if (true == sbxImage->HorzScrollBar->Visible)
        {
            sbxImage->HorzScrollBar->Position = sbxImage->HorzScrollBar->Position + (m_StartX - X);
        }
        if (true == sbxImage->VertScrollBar->Visible)
        {
            sbxImage->VertScrollBar->Position = sbxImage->VertScrollBar->Position + (m_StartY - Y);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::imgSheetMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_Operation != opNone)
    {
        if (Button == mbLeft && m_Operation == opSelecting)
        {
            // select grid elements
            m_Operation = opNone;
        }
        else if (Button == mbRight && (m_Operation == opResizing || m_Operation == opPanning))
        {
            if (Shift.Contains(ssShift))
            {
                // resizing
                m_GridX = m_GridX % m_GridW;
                m_GridY = m_GridY % m_GridH;
                m_Operation = opNone;
            }
            else
            {
                // panning
                m_Operation = opNone;
                m_GridX %= m_GridW;
                m_GridY %= m_GridH;
            }
        }
        else if (Button == mbMiddle && m_Operation == opScrolling)
        {
            // Scrolling
            m_Operation = opNone;
        }
    }
    UpdateStats();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::edtZoomChange(TObject *Sender)
{
    ResetCanvas(true);
    UpdateStats();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::sbxImageMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    static float delta = 0.f;
    const float threshold = 500.f;

    delta += WheelDelta;
    if (delta > threshold)
    {
        edtZoom->Value = edtZoom->Value + 1;
        delta -= threshold;
    }
    if (delta < -threshold)
    {
        edtZoom->Value = edtZoom->Value - 1;
        delta += threshold;
    }
    UpdateStats();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::chkImageIsMaskedClick(TObject *Sender)
{
    radMaskEmpty->Enabled = chkImageIsMasked->Checked;
    radMaskBackground->Enabled = chkImageIsMasked->Checked;
    panMaskColour->Enabled = chkImageIsMasked->Checked;
    lblMaskColour->Enabled = chkImageIsMasked->Checked;
    UpdateStats();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::radTypeTileClick(TObject *Sender)
{
    lblSpriteMultiFrameWidth->Enabled = radTypeSprite->Checked;
    edtSpriteMultiFrameWidth->Enabled = radTypeSprite->Checked;
    lblFrames->Enabled = radTypeSprite->Checked;
    UpdateStats();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::edtSpriteMultiFrameWidthChange(TObject *Sender)
{
    UpdateStats();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::edtNewNameChange(TObject *Sender)
{
    btnAdd->Enabled = edtNewName->Text.Trim() != "";
    lstImages->ItemIndex = -1;
    for (unsigned int i = 0; i < m_Images.size(); i++)
    {
        if (m_Images[i].Name.LowerCase() == edtNewName->Text.LowerCase().Trim())
        {
            btnAdd->Enabled = false;
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::btnAddClick(TObject *Sender)
{
    if (btnAdd->Caption == "Add")
    {
        // add new entry
        TImageInfo ImageInfo;

        ImageInfo.Name          = edtNewName->Text.Trim();
        ImageInfo.GridX         = m_GridX;
        ImageInfo.GridY         = m_GridY;
        ImageInfo.GridW         = m_GridW;
        ImageInfo.GridH         = m_GridH;
        ImageInfo.SelSX         = m_SelSX;
        ImageInfo.SelSY         = m_SelSY;
        ImageInfo.SelEX         = m_SelEX;
        ImageInfo.SelEY         = m_SelEY;
        ImageInfo.Type          = radTypeTile->Checked; // true = tile, false = sprite
        ImageInfo.FrameWidth    = edtSpriteMultiFrameWidth->Value;
        ImageInfo.Palette       = cmbImageFormat->ItemIndex;
        ImageInfo.IsMasked      = chkImageIsMasked->Checked;
        ImageInfo.UseEmptyMask  = radMaskEmpty->Checked;
        ImageInfo.MaskColor     = panMaskColour->Color;

        m_Images.push_back(ImageInfo);

        lstImages->Items->Add(ImageInfo.Name + String(ImageInfo.Type ? " - Tile" : " - Sprite"));

        btnAdd->Enabled = false;
        edtNewName->Text = "";
    }
    else if (lstImages->ItemIndex >= 0)
    {

        // update the current entry
        TImageInfo& ImageInfo = m_Images[lstImages->ItemIndex];

        ImageInfo.Name          = edtNewName->Text.Trim();
        ImageInfo.GridX         = m_GridX;
        ImageInfo.GridY         = m_GridY;
        ImageInfo.GridW         = m_GridW;
        ImageInfo.GridH         = m_GridH;
        ImageInfo.SelSX         = m_SelSX;
        ImageInfo.SelSY         = m_SelSY;
        ImageInfo.SelEX         = m_SelEX;
        ImageInfo.SelEY         = m_SelEY;
        ImageInfo.Type          = radTypeTile->Checked; // true = tile, false = sprite
        ImageInfo.FrameWidth    = edtSpriteMultiFrameWidth->Value;
        ImageInfo.Palette       = cmbImageFormat->ItemIndex;
        ImageInfo.IsMasked      = chkImageIsMasked->Checked;
        ImageInfo.UseEmptyMask  = radMaskEmpty->Checked;
        ImageInfo.MaskColor     = panMaskColour->Color;
        lstImages->Items->Strings[lstImages->ItemIndex] = ImageInfo.Name + String(ImageInfo.Type ? " - Tile" : " - Sprite");
    }
    UpdateStats();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::btnRemoveClick(TObject *Sender)
{
    if (lstImages->ItemIndex >= 0)
    {
        int index = lstImages->ItemIndex;
        m_Images.erase(m_Images.begin() + index);
        lstImages->Items->Delete(index);
    }

    lstImages->ItemIndex = -1;
    btnRemove->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::lstImagesClick(TObject *Sender)
{
    if (lstImages->ItemIndex >= 0)
    {
        TImageInfo& ImageInfo = m_Images[lstImages->ItemIndex];
        edtNewName->Text    = ImageInfo.Name;
        m_GridX = ImageInfo.GridX;
        m_GridY = ImageInfo.GridY;
        m_GridW = ImageInfo.GridW;
        m_GridH = ImageInfo.GridH;
        m_SelSX = ImageInfo.SelSX;
        m_SelSY = ImageInfo.SelSY;
        m_SelEX = ImageInfo.SelEX;
        m_SelEY = ImageInfo.SelEY;
        if (ImageInfo.Type) radTypeTile->Checked = true; else radTypeSprite->Checked = true;
        edtSpriteMultiFrameWidth->Value = ImageInfo.FrameWidth;
        cmbImageFormat->ItemIndex = ImageInfo.Palette;
        chkImageIsMasked->Checked = ImageInfo.IsMasked;
        if (ImageInfo.UseEmptyMask) radMaskEmpty->Checked = true; else radMaskBackground->Checked = true;
        panMaskColour->Color = ImageInfo.MaskColor;
        btnAdd->Caption = "Apply";
        btnAdd->Enabled = true;
    }
    ResetCanvas(true);
    UpdateStats();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::btnResetClick(TObject *Sender)
{
    panMaskColour->Color = m_ImageSheet->Canvas->Pixels[0][m_ImageSheet->Height-1];
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::cmdImportClick(TObject *Sender)
{
    String sErrorMsgs;
    bool bNoErrors = true;
    for (unsigned int i = 0; i < m_Images.size(); i++)
    {
        TImageInfo& Info = m_Images[i];
        TRect PixRect = CalcPixelPos(Info);

        if (Info.Type)
        {
            bNoErrors &= AddTile(Info, sErrorMsgs);
        }
        else
        {
            bNoErrors &= AddSprite(Info, sErrorMsgs);
        }

        // shade the imported region on the original image sheet
        m_ImageSheet->Canvas->Brush->Color = Info.MaskColor;

        bool odd = true;
        for (int y = PixRect.Top; y < PixRect.Bottom; ++y)
        {
            odd = y % 2;
            unsigned char* row = (unsigned char*)m_ImageSheet->ScanLine[y];
            for (int x = PixRect.Left; x < PixRect.Right; x += 3)
            {
                if (odd)
                {
                    row[x+0] = (int)((float)row[x+0] * .33);
                    row[x+1] = (int)((float)row[x+1] * .33);
                    row[x+2] = (int)((float)row[x+2] * .33);
                }
                else
                {
                    row[x+0] = (int)((float)row[x+0] * .66);
                    row[x+1] = (int)((float)row[x+1] * .66);
                    row[x+2] = (int)((float)row[x+2] * .66);
                }
                odd = !odd;
            }
        }
    }

    if (false == bNoErrors)
    {
        ZXMessageBox MessageBox;
        MessageBox.ShowMessage
        (
            mbtError,
            "Failed to Import Images",
            "Failed to import some or all of the selected images.",
            "TommyGun failed to Import some of all of the images from the image sheet.\nBelow are the errrors found\n" + sErrorMsgs,
            "Close",
            "",
            ""
        );
    }

    m_Images.clear();
    lstImages->Items->Clear();
    ResetCanvas(true);
    UpdateStats();
}
//---------------------------------------------------------------------------















//---------------------------------------------------------------------------
bool __fastcall TdlgImageSheetImporter::Execute(const String& File, std::vector<String>* PaletteSignatures)
{
    m_PaletteSignatures = PaletteSignatures;
    m_WorkSheet->LoadFromFile(File);
    m_ImageSheet->LoadFromFile(File);
    imgSheet->Picture->Bitmap->HandleType = bmDIB;
    imgSheet->Picture->Bitmap->PixelFormat = pf24bit;
    m_WorkSheet->HandleType = bmDIB;
    m_WorkSheet->PixelFormat = pf24bit;
    m_ImageSheet->HandleType = bmDIB;
    m_ImageSheet->PixelFormat = pf24bit;
    ResetCanvas(false);
    btnResetClick(NULL);
    sbxImage->DoubleBuffered = true;
    ShowModal();
    return ModalResult == mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::ResetCanvas(bool bUpdate)
{
    m_WorkSheet->Width  = m_ImageSheet->Width  * edtZoom->Value;
    m_WorkSheet->Height = m_ImageSheet->Height * edtZoom->Value;
    imgSheet->Picture->Bitmap->Width  = m_WorkSheet->Width;
    imgSheet->Picture->Bitmap->Height = m_WorkSheet->Height;
    imgSheet->Width  = m_WorkSheet->Width;
    imgSheet->Height = m_WorkSheet->Height;
    // clear the work sheet to the original image
    StretchBlt
    (
        m_WorkSheet->Canvas->Handle,
        0,
        0,
        m_WorkSheet->Width,
        m_WorkSheet->Height,
        m_ImageSheet->Canvas->Handle,
        0,
        0,
        m_ImageSheet->Width,
        m_ImageSheet->Height,
        SRCCOPY
    );
    DrawSelection();
    DrawGrid();
    BitBlt
    (
        imgSheet->Picture->Bitmap->Canvas->Handle,
        0,
        0,
        m_WorkSheet->Width,
        m_WorkSheet->Height,
        m_WorkSheet->Canvas->Handle,
        0,
        0,
        SRCCOPY
    );
    if (bUpdate)
    {
        imgSheet->Refresh();
        panStats->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::DrawGrid(void)
{
    // set the pen color to yellow
    m_WorkSheet->Canvas->Pen->Color = clYellow;
    // draw the vertical lines
    int Zoom = edtZoom->Value;
    int gx = std::max(0, m_GridX % m_GridW);
    int gy = std::max(0, m_GridY % m_GridH);
    for (int x = gx; x < m_ImageSheet->Width; x += m_GridW)
    {
        m_WorkSheet->Canvas->MoveTo(x * Zoom, 0);
        m_WorkSheet->Canvas->LineTo(x * Zoom, m_WorkSheet->Height);
    }
    // then the horizontal lines
    for (int y = gy; y < m_ImageSheet->Height; y += m_GridH)
    {
        m_WorkSheet->Canvas->MoveTo(0, y * Zoom);
        m_WorkSheet->Canvas->LineTo(m_WorkSheet->Width, y * Zoom);
    }
    UpdateStats();
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::DrawSelection()
{
    if (m_SelSX >= 0)
    {
        int Zoom = edtZoom->Value;
        int sx = std::min((m_SelSX - m_GridX) / m_GridW, (m_SelEX - m_GridX) / m_GridW);
        int sy = std::min((m_SelSY - m_GridY) / m_GridH, (m_SelEY - m_GridY) / m_GridH);
        int ex = std::max((m_SelSX - m_GridX) / m_GridW, (m_SelEX - m_GridX) / m_GridW) + 1;
        int ey = std::max((m_SelSY - m_GridY) / m_GridH, (m_SelEY - m_GridY) / m_GridH) + 1;
        sx = ((sx * m_GridW) + m_GridX) * Zoom * 3;
        sy = ((sy * m_GridH) + m_GridY) * Zoom;
        ex = std::min(((ex * m_GridW) + m_GridX) * Zoom * 3, m_WorkSheet->Width  * 3);
        ey = std::min(((ey * m_GridH) + m_GridY) * Zoom    , m_WorkSheet->Height    );

        for (int y = sy; y < ey; ++y)
        {
            unsigned char* row = (unsigned char*)m_WorkSheet->ScanLine[y];
            for (int x = sx; x < ex; x += 3)
            {
                row[x+0] = row[x+0] >> 1;
                row[x+1] = row[x+1] >> 1;
                row[x+2] = row[x+2] >> 1;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TdlgImageSheetImporter::UpdateStats(void)
{
    int sx = std::min((m_SelSX - m_GridX) / m_GridW, (m_SelEX - m_GridX) / m_GridW);
    int sy = std::min((m_SelSY - m_GridY) / m_GridH, (m_SelEY - m_GridY) / m_GridH);
    int ex = std::max((m_SelSX - m_GridX) / m_GridW, (m_SelEX - m_GridX) / m_GridW) + 1;
    int ey = std::max((m_SelSY - m_GridY) / m_GridH, (m_SelEY - m_GridY) / m_GridH) + 1;
    int w  = (ex - sx) * m_GridW;
    int h  = (ey - sy) * m_GridH;
    lblSelectionSizeValue->Caption = IntToStr(w      ) + " x " + IntToStr(h      );
    lblGridSizeValue->Caption      = IntToStr(m_GridW) + " x " + IntToStr(m_GridH);
    lblGridOffsetValue->Caption    = IntToStr(m_GridX) + ", "  + IntToStr(m_GridY);
    if (radTypeSprite->Checked)
    {
        float frames = (float)w / (float)edtSpriteMultiFrameWidth->Value;
        lblFrames->Caption = "Frames: " + FloatToStrF(frames, ffFixed, 7, 1);
    }
    else
    {
        lblFrames->Caption = "Frames: n/a";
    }
    btnRemove->Enabled = (lstImages->ItemIndex >= 0);
    cmdImport->Enabled = m_Images.size() > 0;
}
//---------------------------------------------------------------------------
int __fastcall TdlgImageSheetImporter::AddImage(const String& sType, const String& sPalette, const String& sName, int iWidth, int iHeight, bool bMasked, ZXImage** pImage)
{
    int iImage = -1;
    if (true == SAFE_PTR(m_pImageManager))
    {
        iImage = m_pImageManager->AddImage(sType, sPalette, sName, iWidth, iHeight, bMasked, pImage);
    }
    return iImage;
}
//---------------------------------------------------------------------------
bool __fastcall TdlgImageSheetImporter::AddTile(TImageInfo& Info, String& sError)
{
    bool bResult = false;
    TRect PixRect = CalcPixelPos(Info, 1);

    // create a bitmap to import into a ZXImage
    ZXImage* pImage = NULL;
    Graphics::TBitmap* pBitmap  = new Graphics::TBitmap();
    pBitmap->Width              = PixRect.Width();
    pBitmap->Height             = PixRect.Height();
    pBitmap->PixelFormat        = m_ImageSheet->PixelFormat;
    // copy the source bitmap into the work bitmap
    BitBlt
    (
        pBitmap->Canvas->Handle, 0, 0, pBitmap->Width, pBitmap->Height,
        m_ImageSheet->Canvas->Handle, PixRect.Left, PixRect.Top,
        SRCCOPY
    );

    // convert the bitmap to the graphic format required
    AddImage
    (
        "Tile",
        (*m_PaletteSignatures)[Info.Palette],
        Info.Name,
        pBitmap->Width,
        pBitmap->Height,
        Info.IsMasked,
        &pImage
    );
    if (true == SAFE_PTR(pImage))
    {
        bResult = pImage->ConvertBitmap(pBitmap);
        if (!bResult)
        {
            sError = "Failed to convert the bitmap to a tile image. Name: " + Info.Name;
        }
        else
        {
            if (Info.IsMasked && !Info.UseEmptyMask)
            {
                pImage->ConvertBitmapMask(pBitmap, Info.MaskColor);
            }
        }
    }
    else
    {
        sError = "Failed to create the tile image to place the bitmap into. Name: " + Info.Name;
    }
    return bResult;
}
//---------------------------------------------------------------------------
bool __fastcall TdlgImageSheetImporter::AddSprite(TImageInfo& Info, String& sError)
{
    bool bResult = false;
    TRect PixRect = CalcPixelPos(Info, 1);

    // create a bitmap to import into a ZXImage as a set of sprite frames
    int FrameWidth              = Info.FrameWidth;
    ZXImage* pImage             = NULL;
    Graphics::TBitmap* pBitmap  = new Graphics::TBitmap();
    pBitmap->Width              = FrameWidth;
    pBitmap->Height             = PixRect.Height();
    pBitmap->PixelFormat        = m_ImageSheet->PixelFormat;
    int Frames = (PixRect.Width() % FrameWidth) ? ((PixRect.Width() / FrameWidth) + 1) : (PixRect.Width() / FrameWidth);
    for (int i = 0; i < Frames; ++i)
    {
        // copy the source bitmap into the work bitmap
        BitBlt
        (
            pBitmap->Canvas->Handle, 0, 0, pBitmap->Width, pBitmap->Height,
            m_ImageSheet->Canvas->Handle, PixRect.Left + (i * FrameWidth), PixRect.Top,
            SRCCOPY
        );

        // convert the bitmap to the graphic format required
        AddImage
        (
            "Sprite",
            (*m_PaletteSignatures)[Info.Palette],
            Info.Name,
            pBitmap->Width,
            pBitmap->Height,
            Info.IsMasked,
            &pImage
        );
        if (true == SAFE_PTR(pImage))
        {
            bResult = pImage->ConvertBitmap(pBitmap);
            if (!bResult)
            {
                sError = "Failed to convert the bitmap to a tile image. Name: " + Info.Name;
            }
            else
            {
                if (Info.IsMasked && !Info.UseEmptyMask)
                {
                    pImage->ConvertBitmapMask(pBitmap, Info.MaskColor);
                }
            }
        }
        else
        {
            sError = "Failed to create the tile image to place the bitmap into. Name: " + Info.Name;
        }
    }

    return bResult;
}
//---------------------------------------------------------------------------
TRect __fastcall TdlgImageSheetImporter::CalcPixelPos(TImageInfo& Info, int XScalar)
{
    TRect PixRect;
    PixRect.Left   = std::min((Info.SelSX - Info.GridX) / Info.GridW, (Info.SelEX - Info.GridX) / Info.GridW);
    PixRect.Top    = std::min((Info.SelSY - Info.GridY) / Info.GridH, (Info.SelEY - Info.GridY) / Info.GridH);
    PixRect.Right  = std::max((Info.SelSX - Info.GridX) / Info.GridW, (Info.SelEX - Info.GridX) / Info.GridW) + 1;
    PixRect.Bottom = std::max((Info.SelSY - Info.GridY) / Info.GridH, (Info.SelEY - Info.GridY) / Info.GridH) + 1;
    PixRect.Left   =          ((PixRect.Left   * Info.GridW) + Info.GridX) * XScalar;
    PixRect.Top    =          ((PixRect.Top    * Info.GridH) + Info.GridY);
    PixRect.Right  = std::min(((PixRect.Right  * Info.GridW) + Info.GridX) * XScalar, (long)(m_ImageSheet->Width  * XScalar));
    PixRect.Bottom = std::min(((PixRect.Bottom * Info.GridH) + Info.GridY)          , (long)(m_ImageSheet->Height          ));
    return PixRect;
}
//---------------------------------------------------------------------------

