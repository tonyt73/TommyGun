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
#ifndef fImageRotateH
#define fImageRotateH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "KSpinEdit.h"
#include "KSlider.h"
#include "KSpinEdit.h"
#include "..\ZXImageInterface.h"
//---------------------------------------------------------------------------
// The Representation of a 32 bit color table entry
#pragma pack(push)
#pragma pack(1)
typedef struct ssBGR
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char pad;
} sBGR;
typedef sBGR *pBGR;
#pragma pack(pop)
//---------------------------------------------------------------------------
class TfrmImageRotate : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grpAngleOfRotation;
    TLabel *lblAngle;
    KSpinEdit *edtAngle;
    KSlider *slrAngle;
    TGroupBox *grpCentreOfRotation;
    TLabel *lblXCoord;
    KSpinEdit *edtXCoord;
    TLabel *lblYCoord;
    KSpinEdit *edtYCoord;
    TGroupBox *grpPreviewOfRotation;
    TPanel *panPreview;
    TLabel *lblPreviewNote;
    TImage *imgPreview;
    TImage *imgCursorCenter;
    KSpinEdit *edtAngleSnap;
    TLabel *lblSnapModulo;
    TImage *imgCursorTo;
    TLabel *lblRightClick;
    TLabel *lblHoldShift;
    TPanel *panView;
    TImage *imgView;
    TLabel *lblSnappedAngle;
    TLabel *lblSnappedAngleValue;
    TButton *cmdOk;
    TButton *cmdCancel;
    void __fastcall imgPreviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgPreviewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgCursorCenterMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgCursorCenterMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall edtAngleChange(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
private:	// User declarations
    Graphics::TBitmap*  m_Bitmap;
    Graphics::TBitmap*  m_RotatedBitmap;
    Graphics::TBitmap*  m_RotatingBitmap;
    double              m_ImageScale;
    double              m_TargetX;
    double              m_TargetY;
    double              m_iSize;
    TColor              m_BackColor;
    bool                m_bNoResizeCalls;

    void    __fastcall  UpdateGui(bool bUpdateAngle);
    void    __fastcall  UpdateCursors(void);
    void    __fastcall  UpdateCursor(int X, int Y, TShiftState Shift);
    void    __fastcall  UpdateBitmap(void);
    void    __fastcall  ResizePreview(void);
    void    __fastcall  DrawRect(TRect rect, TColor color);
    int     __fastcall  SnapAngle(void);

    void    __fastcall  RotateBitmap(Graphics::TBitmap* SourceBitmap, Graphics::TBitmap*& DestBitmap, TPoint Center, double Angle);



public:		// User declarations
            __fastcall  TfrmImageRotate(TComponent* Owner);
            __fastcall ~TfrmImageRotate();

    bool    __fastcall  Execute(Graphics::TBitmap* pBitmap, TColor BackColor);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmImageRotate *frmImageRotate;
//---------------------------------------------------------------------------
#endif

