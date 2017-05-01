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
#include <vcl.h>
#pragma hdrstop
#include "..\..\..\SafeMacros.h"
#include <algorithm>
#include <math.h>
#include <math.hpp>
//---------------------------------------------------------------------------
#include "fImageRotate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KSlider"
#pragma link "KSpinEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#define RAD_TO_DEG(a) ((double)(a) * (180.0 / M_PI))
#define DEG_TO_RAD(a) ((double)(a) * (M_PI / 180.0))
//---------------------------------------------------------------------------
TfrmImageRotate *frmImageRotate = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmImageRotate::TfrmImageRotate(TComponent* Owner)
: TForm(Owner)
, m_ImageScale(1.f)
{
    m_RotatedBitmap  = new Graphics::TBitmap();
    m_RotatingBitmap = new Graphics::TBitmap();
    m_RotatedBitmap->PixelFormat  = pf32bit;
    m_RotatingBitmap->PixelFormat = pf32bit;

    grpPreviewOfRotation->DoubleBuffered = true;
    panPreview->DoubleBuffered = true;
    DoubleBuffered = true;
}
//---------------------------------------------------------------------------
__fastcall TfrmImageRotate::~TfrmImageRotate()
{
    SAFE_DELETE(m_RotatedBitmap );
    SAFE_DELETE(m_RotatingBitmap);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::FormResize(TObject *Sender)
{
    if (m_bNoResizeCalls) return;
    ResizePreview();
    UpdateCursors();
    Update();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmImageRotate::Execute(Graphics::TBitmap* pBitmap, TColor BackColor)
{
    m_BackColor = BackColor;
    m_Bitmap    = pBitmap;

    if (pBitmap->Width >= pBitmap->Height)
    {
        imgView->Width  = panView->Width;
        imgView->Height = panView->Width * ((double)pBitmap->Height / (double)pBitmap->Width);
    }
    else
    {
        imgView->Height = panView->Height;
        imgView->Width  = panView->Height * ((double)pBitmap->Width / (double)pBitmap->Height);
    }

    imgView->Picture->Bitmap->Width  = m_Bitmap->Width;
    imgView->Picture->Bitmap->Height = m_Bitmap->Height;

    edtXCoord->Max  = pBitmap->Width  - 1;
    edtYCoord->Max  = pBitmap->Height - 1;
    edtXCoord->Value= pBitmap->Width  / 2;
    edtYCoord->Value= pBitmap->Height / 2;

    m_iSize = sqrt
                (
                    (double)(pBitmap->Width * pBitmap->Width)
                    +
                    (double)(pBitmap->Height * pBitmap->Height)
                );
    m_iSize = (int)m_iSize + ((int)m_iSize % 2);
    int MinSize = std::min(panPreview->Width, panPreview->Height);
    m_ImageScale = (double)MinSize / (double)m_iSize;
    ResizePreview();

    m_RotatedBitmap->Width  = m_iSize;
    m_RotatedBitmap->Height = m_iSize;
    m_RotatedBitmap->Canvas->Brush->Color = m_BackColor;
    m_RotatedBitmap->Canvas->FillRect(Rect(0,0, m_iSize, m_iSize));
    BitBlt
        (
            m_RotatedBitmap->Canvas->Handle,
            (m_iSize - pBitmap->Width ) / 2,
            (m_iSize - pBitmap->Height) / 2,
            pBitmap->Width,
            pBitmap->Height,
            pBitmap->Canvas->Handle,
            0,
            0,
            SRCCOPY
        );

    m_TargetX = 1.0;
    m_TargetY = 0.5;
    edtAngle->Value = 0;
    UpdateCursors();

    m_bNoResizeCalls = true;
    Width  = (531 - 280) + imgPreview->Width;
    Height = (439 - 280) + imgPreview->Height;
    m_bNoResizeCalls = false;
    UpdateBitmap();

    ShowModal();

    if (ModalResult == mrOk)
    {
        int W   = m_Bitmap->Width;
        int H   = m_Bitmap->Height;
        int S2  = m_iSize;
        BitBlt
        (
            m_Bitmap->Canvas->Handle,
            0,
            0,
            W,
            H,
            m_RotatedBitmap->Canvas->Handle,
            (S2 - W) / 2,
            (S2 - H) / 2,
            SRCCOPY
        );
    }

    return ModalResult;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::imgPreviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    UpdateCursor(X, Y, Shift);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::imgPreviewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    UpdateCursor(X, Y, Shift);
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::imgCursorCenterMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbLeft)
    {
        UpdateCursor(imgCursorTo->Left + X, imgCursorTo->Top + Y, Shift);
    }
    else if (Button == mbRight)
    {
        UpdateCursor(imgCursorCenter->Left + X, imgCursorCenter->Top + Y, Shift);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::imgCursorCenterMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    if (Shift.Contains(ssLeft))
    {
        UpdateCursor(imgCursorTo->Left + X, imgCursorTo->Top + Y, Shift);
    }
    else if (Shift.Contains(ssRight))
    {
        UpdateCursor(imgCursorCenter->Left + X, imgCursorCenter->Top + Y, Shift);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::edtAngleChange(TObject *Sender)
{
    try
    {
        slrAngle->Position = edtAngle->Value;
        SnapAngle();
        UpdateBitmap();
    }
    catch(...)
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::UpdateGui(bool bUpdateAngle)
{
    edtXCoord->Value = ((double)(imgCursorCenter->Left+16) / m_ImageScale) - ((m_iSize - m_Bitmap->Width ) / 2);
    edtYCoord->Value = ((double)(imgCursorCenter->Top +16) / m_ImageScale) - ((m_iSize - m_Bitmap->Height) / 2);

    if (bUpdateAngle)
    {
        // workout the angle between the centre and the target
        //            -1
        // angle = cos   (a.b)
        //              --------
        //              (|a||b|)
        float v1i = (imgCursorTo->Left + 4) - (imgCursorCenter->Left + 16);
        float v1j = (imgCursorTo->Top  + 4) - (imgCursorCenter->Top  + 16);
        float v2i = 1.f;
        float v2j = 0.f;
        // work out the quadrants and swap the vectors
        int quadrant = (v1i > 0 ? 0 : 1) + (v1j > 0 ? 2 : 0);
        v1i = fabs(v1i);
        v1j = fabs(v1j);
        v2i = fabs(v2i);
        v2j = fabs(v2j);

        float a_dot_b = (v1i * v2i) + (v1j * v2j);
        float a_len   = sqrt((v1i * v1i) + (v1j * v1j));
        float b_len   = sqrt((v2i * v2i) + (v2j * v2j));
        float al_bl   = a_len * b_len;
        if (al_bl)
        {
            float alpha   = a_dot_b / al_bl;
            float rads    = acos(alpha);
            float degs    = rads * (180 / M_PI);

            switch(quadrant)
            {
                case 1:
                    degs = (90 - degs) + 90;
                    break;
                case 2:
                    degs = (90 - degs) + 270;
                    break;
                case 3:
                    degs += 180;
                    break;
                case 0:
                default:
                    break;
            }

            edtAngle->Value = (int)degs;
            SnapAngle();
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::UpdateCursors(void)
{
    double WS = (double)m_Bitmap->Width  * m_ImageScale;
    double HS = (double)m_Bitmap->Height * m_ImageScale;
    double minx = (((double)imgPreview->Width  - WS) / 2.f);
    double miny = (((double)imgPreview->Height - HS) / 2.f);
    double ps = ((double)imgPreview->Width / (double)m_iSize) / 2.0;
    double xr = (double)edtXCoord->Value / (double)m_Bitmap->Width;
    double yr = (double)edtYCoord->Value / (double)m_Bitmap->Height;
    imgCursorCenter->Left = minx + (xr * WS) - 16.0 + ps;
    imgCursorCenter->Top  = miny + (yr * HS) - 16.0 + ps;
    imgCursorTo->Left     = (m_TargetX * imgPreview->Width ) - 5;
    imgCursorTo->Top      = (m_TargetY * imgPreview->Height) - 5;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::UpdateCursor(int X, int Y, TShiftState Shift)
{
    float WS   = (float)m_Bitmap->Width  * m_ImageScale;
    float HS   = (float)m_Bitmap->Height * m_ImageScale;
    if (Shift.Contains(ssLeft))
    {
        if (!Shift.Contains(ssShift))
        {
            imgCursorTo->Left = std::max(-5, std::min(X - 5, imgPreview->Width  - 5));
            imgCursorTo->Top  = std::max(-5, std::min(Y - 5, imgPreview->Height - 5));
        }
        else
        {
            imgCursorTo->Left = (imgPreview->Width  >> 1) - 5;
            imgCursorTo->Top  = (imgPreview->Height >> 1) - 5;
        }
        m_TargetX = (double)(imgCursorTo->Left+5) / (double)imgPreview->Width;
        m_TargetY = (double)(imgCursorTo->Top +5) / (double)imgPreview->Height;
        UpdateGui(true);
    }
    else if (Shift.Contains(ssRight))
    {
        if (!Shift.Contains(ssShift))
        {
            float minx = (((float)imgPreview->Width  - WS) / 2.f) - 16.f;
            float maxx = minx + WS;
            float miny = (((float)imgPreview->Height - HS) / 2.f) - 16.f;
            float maxy = miny + HS;
            imgCursorCenter->Left = std::min(maxx, std::max(minx, (float)(X - 16)));
            imgCursorCenter->Top  = std::min(maxy, std::max(miny, (float)(Y - 16)));
        }
        else
        {
            double ps = ((double)imgPreview->Width / (double)m_iSize) / 2.0;
            imgCursorCenter->Left = (imgPreview->Width  >> 1) - 16 + ps;
            imgCursorCenter->Top  = (imgPreview->Height >> 1) - 16 + ps;
        }
        UpdateGui(false);
    }
}
//---------------------------------------------------------------------------
int __fastcall TfrmImageRotate::SnapAngle(void)
{
    int angle   = edtAngle->Value;
    int snap    = edtAngleSnap->Value;
    angle      += snap >> 1;
    int angleMo = angle % snap;

    angle -= angleMo;
    lblSnappedAngleValue->Caption = IntToStr(angle);
    return angle;
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::ResizePreview(void)
{
    int MinSize = std::min(panPreview->Width, panPreview->Height);
    m_ImageScale = (double)MinSize / (double)m_iSize;
    imgPreview->Width  = MinSize;
    imgPreview->Height = MinSize;
    imgPreview->Picture->Bitmap->Width  = MinSize;
    imgPreview->Picture->Bitmap->Height = MinSize;

    StretchBlt
        (
            imgPreview->Picture->Bitmap->Canvas->Handle,
            0,
            0,
            imgPreview->Width,
            imgPreview->Height,
            m_RotatedBitmap->Canvas->Handle,
            0,
            0,
            m_RotatedBitmap->Width,
            m_RotatedBitmap->Height,
            SRCCOPY
        );

    float minx = ((m_iSize - (float)m_Bitmap->Width ) / 2.f);
    float maxx =      minx + (float)m_Bitmap->Width ;
    float miny = ((m_iSize - (float)m_Bitmap->Height) / 2.f);
    float maxy =      miny + (float)m_Bitmap->Height;
    DrawRect
        (
            TRect
            (
                (minx * m_ImageScale) - 1.f,
                (miny * m_ImageScale) - 1.f,
                (maxx * m_ImageScale) + 1.f,
                (maxy * m_ImageScale) + 1.f
            ),
            clWhite
        );

    //Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::DrawRect(TRect rect, TColor color)
{
    imgPreview->Picture->Bitmap->Canvas->Pen->Color = color;
    imgPreview->Picture->Bitmap->Canvas->MoveTo(rect.Left , rect.Top   );
    imgPreview->Picture->Bitmap->Canvas->LineTo(rect.Right, rect.Top   );
    imgPreview->Picture->Bitmap->Canvas->LineTo(rect.Right, rect.Bottom);
    imgPreview->Picture->Bitmap->Canvas->LineTo(rect.Left , rect.Bottom);
    imgPreview->Picture->Bitmap->Canvas->LineTo(rect.Left , rect.Top   );
}
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::UpdateBitmap(void)
{
    int W   = m_Bitmap->Width;
    int H   = m_Bitmap->Height;
    int S   = std::max(W, H);
    int S2  = m_iSize;
    int S2H = S2 >> 1;
    int W2  = W  >> 1;
    int H2  = H  >> 1;
    int CX  = edtXCoord->Value;
    int CY  = edtYCoord->Value;

    //PatBlt(tmp->Canvas->Handle, 0, 0, S2, S2, BLACKNESS);
    m_RotatingBitmap->Width  = S2;
    m_RotatingBitmap->Height = S2;
    m_RotatedBitmap->Width   = S2;
    m_RotatedBitmap->Height  = S2;

    m_RotatingBitmap->Canvas->Brush->Color = m_BackColor;//m_Bitmap->Canvas->Pixels[0][m_Bitmap->Height-1];
    m_RotatingBitmap->Canvas->FillRect(TRect(0,0,S2,S2));
    BitBlt(m_RotatingBitmap->Canvas->Handle, S2H - W2, S2H - H2, W, H, m_Bitmap->Canvas->Handle, 0, 0, SRCCOPY);

    RotateBitmap
        (
            m_RotatingBitmap,
            m_RotatedBitmap,
            TPoint
            (
                S2H - (W2 - CX),
                S2H - (H2 - CY)
            ),
            SnapAngle()
        );

    BitBlt
        (
            imgView->Picture->Bitmap->Canvas->Handle,
            0,
            0,
            W,
            H,
            m_RotatedBitmap->Canvas->Handle,
            (S2 - W) / 2,
            (S2 - H) / 2,
            SRCCOPY
        );
    imgView->Invalidate();
    ResizePreview();
    Update();
}
//---------------------------------------------------------------------------
// Code taken from
//  http://delphi.about.com/cs/adptips2001/a/bltip1201_4.htm
// Written by Zarko Gajic
// Originally written in Pascal and converted to C++ by Tony Thompson 
//---------------------------------------------------------------------------
void __fastcall TfrmImageRotate::RotateBitmap(Graphics::TBitmap* SourceBitmap, Graphics::TBitmap*& DestBitmap, TPoint Center, double Angle)
{
   double   cosRadians;
   double   sinRadians;
   double   Radians;
   int      inX;
   double   inXOriginal;
   double   inXPrime;
   double   inXPrimeRotated;
   int      inY;
   double   inYOriginal;
   double   inYPrime;
   double   inYPrimeRotated;
   void*    OriginalRow;
   void*    RotatedRow;
   DWORD    dwColor = ((DWORD*)(SourceBitmap->ScanLine[SourceBitmap->Height-1]))[0];

   Radians = Angle * (M_PI / 180.0);
   sinRadians = sin(Radians) ;
   cosRadians = cos(Radians) ;
   for(inX = DestBitmap->Height-1; inX; inX--)
   {
     RotatedRow = DestBitmap->ScanLine[inX];
     inXPrime = 2*(inX - Center.y) + 1;
     for (inY = DestBitmap->Width-1; inY; inY--)
     {
       inYPrime = 2.0 * ((double)inY - (double)Center.x) + 1.0;
       inYPrimeRotated = SimpleRoundTo(inYPrime * cosRadians - inXPrime * sinRadians, -1) ;
       inXPrimeRotated = SimpleRoundTo(inYPrime * sinRadians + inXPrime * cosRadians, -1) ;
       inYOriginal = (inYPrimeRotated - 1) / 2.0 + (double)Center.x;
       inXOriginal = (inXPrimeRotated - 1) / 2.0 + (double)Center.y;
       if
       (
         (inYOriginal >= 0.0) &&
         (inYOriginal < (double)(SourceBitmap->Width)) &&
         (inXOriginal >= 0.0) &&
         (inXOriginal < (double)(SourceBitmap->Height))
       )
       {
         OriginalRow = SourceBitmap->ScanLine[(int)inXOriginal];
         ((DWORD*)RotatedRow)[inY] = ((DWORD*)OriginalRow)[(int)inYOriginal];
       }
       else
       {
         ((DWORD*)RotatedRow)[inY] = dwColor;
       }
     }
   }
}


