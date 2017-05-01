//---------------------------------------------------------------------------
#ifndef fImageSheetImporterH
#define fImageSheetImporterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "..\ZXImageInterface.h"
#include "KSpinEdit.h"
//---------------------------------------------------------------------------
class TdlgImageSheetImporter : public TForm
{
__published:	// IDE-managed Components
    TColorDialog *dlgColour;
    KSpinEdit *edtZoom;
    KSpinEdit *edtSpriteMultiFrameWidth;
    TBevel *bvlMessageTop;
    TCheckBox *chkImageIsMasked;
    TComboBox *cmbImageFormat;
    TEdit *edtNewName;
    TListBox *lstImages;
    TScrollBox *sbxImage;
    TImage *imgSheet;
    TImage *imgInformation;
    TPanel *penRed;
    TPanel *penYellow;
    TPanel *penGreen;
    TPanel *penCyan;
    TPanel *panContainer;
    TPanel *panImages;
    TGroupBox *grpSprite;
    TGroupBox *grpImageIsMasked;
    TRadioButton *radTypeSprite;
    TRadioButton *radTypeTile;
    TRadioButton *radMaskEmpty;
    TRadioButton *radMaskBackground;
    TPanel *panStats;
    TPanel *panMessageHeader;
    TPanel *panMaskColour;
    TPanel *panHelp;
    TSpeedButton *btnHelp;
    TButton *btnAdd;
    TButton *btnRemove;
    TButton *btnReset;
    TButton *cmdImport;
    TButton *cmdClose;
    TLabel *lblMaskColour;
    TLabel *lblImages;
    TLabel *lblImageFormat;
    TLabel *lblMessageTitle;
    TLabel *lblShortMessage;
    TLabel *lblNewName;
    TLabel *lblType;
    TLabel *lblFrames;
    TLabel *lblSpriteMultiFrameWidth;
    TLabel *lblHelp00;
    TLabel *lblHelp01;
    TLabel *lblHelp02;
    TLabel *lblHelp03;
    TLabel *lblHelp04;
    TLabel *lblHelp05;
    TLabel *lblHelp06;
    TLabel *lblHelp07;
    TLabel *lblHelp08;
    TLabel *lblHelp09;
    TLabel *lblHelp10;
    TLabel *lblGridOffset;
    TLabel *lblGridOffsetValue;
    TLabel *lblGridSizeValue;
    TLabel *lblGridSize;
    TLabel *lblZoom;
    TLabel *lblSelectionSize;
    TLabel *lblSelectionSizeValue;
    TImage *Image1;
    void __fastcall panMaskColourClick(TObject *Sender);
    void __fastcall imgSheetMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgSheetMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgSheetMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall sbxImageMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall chkImageIsMaskedClick(TObject *Sender);
    void __fastcall radTypeTileClick(TObject *Sender);
    void __fastcall edtZoomChange(TObject *Sender);
    void __fastcall edtSpriteMultiFrameWidthChange(TObject *Sender);
    void __fastcall edtNewNameChange(TObject *Sender);
    void __fastcall lstImagesClick(TObject *Sender);
    void __fastcall btnHelpClick(TObject *Sender);
    void __fastcall btnAddClick(TObject *Sender);
    void __fastcall btnRemoveClick(TObject *Sender);
    void __fastcall btnResetClick(TObject *Sender);
    void __fastcall cmdImportClick(TObject *Sender);
private:	// User declarations

    enum TOperation { opNone, opSelecting, opPanning, opResizing, opScrolling };

    typedef struct
    {
        String      Name;
        int         GridX;
        int         GridY;
        int         GridW;
        int         GridH;
        int         SelSX;
        int         SelSY;
        int         SelEX;
        int         SelEY;
        int         Palette;
        int         FrameWidth;
        bool        Type;
        bool        IsMasked;
        bool        UseEmptyMask;
        TColor      MaskColor;

    } TImageInfo;

    Graphics::TBitmap*  m_ImageSheet;
    Graphics::TBitmap*  m_WorkSheet;
    int                 m_GridX;
    int                 m_GridY;
    int                 m_GridW;
    int                 m_GridH;
    int                 m_SelSX;
    int                 m_SelSY;
    int                 m_SelEX;
    int                 m_SelEY;

    TOperation          m_Operation;
    int                 m_StartX;
    int                 m_StartY;
    int                 m_EndX;
    int                 m_EndY;

    int                 m_PanningX;         // the grid X, Y position when panning started
    int                 m_PanningY;

    std::vector<TImageInfo> m_Images;
    std::vector<String>*    m_PaletteSignatures;

    void    __fastcall  ResetCanvas(bool bUpdate);
    void    __fastcall  DrawGrid(void);
    void    __fastcall  DrawSelection();
    void    __fastcall  UpdateStats(void);
    int     __fastcall  AddImage(const String& sType, const String& sPalette, const String& sName, int iWidth, int iHeight, bool bMasked, ZXImage** pImage);
    bool    __fastcall  AddTile(TImageInfo& Info, String& sError);
    bool    __fastcall  AddSprite(TImageInfo& Info, String& sError);
    TRect   __fastcall  CalcPixelPos(TImageInfo& Info, int XScalar = 3);

public:		// User declarations
            __fastcall  TdlgImageSheetImporter(TComponent* Owner);
            __fastcall ~TdlgImageSheetImporter();

    bool    __fastcall  Execute(const String& File, std::vector<String>* PaletteSignatures);

    ZXImageManager*     m_pImageManager;
};
//---------------------------------------------------------------------------
extern PACKAGE TdlgImageSheetImporter *dlgImageSheetImporter;
//---------------------------------------------------------------------------
#endif
