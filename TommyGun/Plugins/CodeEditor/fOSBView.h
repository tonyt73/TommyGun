//---------------------------------------------------------------------------
#ifndef fOSBViewH
#define fOSBViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "KSpinEdit.h"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
class TfrmOSBView : public TForm
{
__published:	// IDE-managed Components
    TPanel *panOSBDisplayBlack;
    TPanel *panOSBDisplayWhite;
    TPopupMenu *popOSBOptions;
    TMenuItem *popOSBNormalSize;
    TMenuItem *popOSBDoubleSize;
    TMenuItem *popOSBTripleSize;
    TMenuItem *popOSBLine00;
    TMenuItem *popOSBShowAttributes;
    TMenuItem *popOSBHideAttributes;
    TPanel *Panel1;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    KSpinEdit *spnWidth;
    TLabel *Label3;
    KSpinEdit *spnHeight;
    TListView *lstBuffers;
    TPanel *Panel2;
    TToolBar *tbrOptions;
    TToolButton *tbnAdd;
    TToolButton *tbnRemove;
    TToolButton *tbnUpdate;
    TImageList *ImageList1;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TComboBox *cmbSymbol;
    TLabel *Label4;
    TToolButton *ToolButton4;
    TPanel *Panel3;
    TGroupBox *GroupBox2;
    TScrollBox *ScrollBox1;
    TImage *imgOSBDisplay;
    void __fastcall tbnAddClick(TObject *Sender);
    void __fastcall tbnRemoveClick(TObject *Sender);
    void __fastcall tbnUpdateClick(TObject *Sender);
    void __fastcall lstBuffersClick(TObject *Sender);
    void __fastcall popOSBNormalSizeClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall lstBuffersChange(TObject *Sender, TListItem *Item, TItemChange Change);
    void __fastcall lstBuffersChanging(TObject *Sender, TListItem *Item, TItemChange Change, bool &AllowChange);
private:	// User declarations
    struct TBufferDefinition
    {
        String              Symbol;
        unsigned int        Width;
        unsigned int        Height;
        bool                Visible;
        Graphics::TBitmap*  Bitmap;
    };

    std::vector<TBufferDefinition>  m_Buffers;
    TFont*                          m_Font;
    char*                           m_Memory;
    int                             m_ImageWidth;
    int                             m_ImageHeight;
    int                             m_ImageScale;
    bool                            m_Loading;

    void    __fastcall  UpdateList();
    void    __fastcall  ResizeImage();
    void    __fastcall  DrawBuffer(int bufIndex);

public:		// User declarations
            __fastcall  TfrmOSBView(TComponent* Owner);
    void    __fastcall  Update();
    void    __fastcall  RedrawBuffers();
    HRESULT __fastcall  Save(KXmlInfo& info);
    HRESULT __fastcall  Load(KXmlInfo& info);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOSBView *frmOSBView;
//---------------------------------------------------------------------------
#endif
