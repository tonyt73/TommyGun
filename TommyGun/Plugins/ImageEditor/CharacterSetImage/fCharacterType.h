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
#ifndef fCharacterTypeH
#define fCharacterTypeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include "..\ZXImageInterface.h"
#include "KSpinEdit.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    //using namespace ImageEditor;
    namespace ImageTypes
    {
        //---------------------------------------------------------------------------
        class TfrmCharacterType : public TForm
        {
        __published:	// IDE-managed Components
            TPanel *panCharacterSet;
            TImage *imgIcon;
            TLabel *lblCharacterSetName;
            TLabel *lblCharacterSetFormat;
            TLabel *lblCharacterSetWidth;
            TLabel *lblCharacterSetHeight;
            TEdit *edtCharacterSetName;
            TComboBox *cmbCharacterSetFormat;
            TBitBtn *cmdCharacterSetAdd;
            TBitBtn *cmdCharacterSetRemove;
            TBitBtn *cmdCharacterSetRename;
            TBitBtn *cmdCharacterSetClone;
            KSpinEdit *edtCharacterSetWidth;
            KSpinEdit *edtCharacterSetHeight;
            TPanel *panCharacters;
            TScrollBox *sbxCharacters;
            TPaintBox *pbxCharacterSetPreview;
            TListBox *lstCharacterSetList;
            TCheckBox *chkTileMasked;
            TPanel *Panel1;
            TSpeedButton *spdCharacterSetSpace;
            TSpeedButton *spdCharacterSetExclamation;
            TSpeedButton *spdCharacterSetQuoteDouble;
            TSpeedButton *spdCharacterSetHash;
            TSpeedButton *spdCharacterSetDollar;
            TSpeedButton *spdCharacterSetPercentage;
            TSpeedButton *spdCharacterSetAmpersand;
            TSpeedButton *spdCharacterSetQuoteSingle;
            TSpeedButton *spdCharacterSetBracketOpen;
            TSpeedButton *spdCharacterSetBracketClosed;
            TSpeedButton *spdCharacterSetAsterix;
            TSpeedButton *spdCharacterSetPlus;
            TSpeedButton *spdCharacterSetComma;
            TSpeedButton *spdCharacterSetMinus;
            TSpeedButton *spdCharacterSetPeriod;
            TSpeedButton *spdCharacterSetSlashForward;
            TSpeedButton *spdCharacterSet0;
            TSpeedButton *spdCharacterSet1;
            TSpeedButton *spdCharacterSet2;
            TSpeedButton *spdCharacterSet3;
            TSpeedButton *spdCharacterSet4;
            TSpeedButton *spdCharacterSet5;
            TSpeedButton *spdCharacterSet6;
            TSpeedButton *spdCharacterSet7;
            TSpeedButton *spdCharacterSet8;
            TSpeedButton *spdCharacterSet9;
            TSpeedButton *spdCharacterSetColon;
            TSpeedButton *spdCharacterSetColonSemi;
            TSpeedButton *spdCharacterSetCompareLessThan;
            TSpeedButton *spdCharacterSetCompareEquals;
            TSpeedButton *spdCharacterSetCompareGreaterThan;
            TSpeedButton *spdCharacterSetQuestionMark;
            TSpeedButton *spdCharacterSetAt;
            TSpeedButton *spdCharacterSet__A;
            TSpeedButton *spdCharacterSet__B;
            TSpeedButton *spdCharacterSet__C;
            TSpeedButton *spdCharacterSet__D;
            TSpeedButton *spdCharacterSet__E;
            TSpeedButton *spdCharacterSet__F;
            TSpeedButton *spdCharacterSet__G;
            TSpeedButton *spdCharacterSet__H;
            TSpeedButton *spdCharacterSet__I;
            TSpeedButton *spdCharacterSet__J;
            TSpeedButton *spdCharacterSet__K;
            TSpeedButton *spdCharacterSet__L;
            TSpeedButton *spdCharacterSet__M;
            TSpeedButton *spdCharacterSet__N;
            TSpeedButton *spdCharacterSet__O;
            TSpeedButton *spdCharacterSet__P;
            TSpeedButton *spdCharacterSet__Q;
            TSpeedButton *spdCharacterSet__R;
            TSpeedButton *spdCharacterSet__S;
            TSpeedButton *spdCharacterSet__T;
            TSpeedButton *spdCharacterSet__U;
            TSpeedButton *spdCharacterSet__V;
            TSpeedButton *spdCharacterSet__W;
            TSpeedButton *spdCharacterSet__X;
            TSpeedButton *spdCharacterSet__Y;
            TSpeedButton *spdCharacterSet__Z;
            TSpeedButton *spdCharacterSetBraceSquareOpen;
            TSpeedButton *spdCharacterSetSlashBackwards;
            TSpeedButton *spdCharacterSetBraceSquareClosed;
            TSpeedButton *spdCharacterSetHat;
            TSpeedButton *spdCharacterSetUnderline;
            TSpeedButton *spdCharacterSetPound;
            TSpeedButton *spdCharacterSet_a;
            TSpeedButton *spdCharacterSet_b;
            TSpeedButton *spdCharacterSet_c;
            TSpeedButton *spdCharacterSet_d;
            TSpeedButton *spdCharacterSet_e;
            TSpeedButton *spdCharacterSet_f;
            TSpeedButton *spdCharacterSet_g;
            TSpeedButton *spdCharacterSet_h;
            TSpeedButton *spdCharacterSet_i;
            TSpeedButton *spdCharacterSet_j;
            TSpeedButton *spdCharacterSet_k;
            TSpeedButton *spdCharacterSet_l;
            TSpeedButton *spdCharacterSet_m;
            TSpeedButton *spdCharacterSet_n;
            TSpeedButton *spdCharacterSet_o;
            TSpeedButton *spdCharacterSet_p;
            TSpeedButton *spdCharacterSet_q;
            TSpeedButton *spdCharacterSet_r;
            TSpeedButton *spdCharacterSet_s;
            TSpeedButton *spdCharacterSet_t;
            TSpeedButton *spdCharacterSet_u;
            TSpeedButton *spdCharacterSet_v;
            TSpeedButton *spdCharacterSet_w;
            TSpeedButton *spdCharacterSet_x;
            TSpeedButton *spdCharacterSet_y;
            TSpeedButton *spdCharacterSet_z;
            TSpeedButton *spdCharacterSetBraceCurlyOpen;
            TSpeedButton *spdCharacterSetLine;
            TSpeedButton *spdCharacterSetBraceCurlyClosed;
            TSpeedButton *spdCharacterSetTide;
            TSpeedButton *spdCharacterSetCopyright;
            void __fastcall edtCharacterSetNameChange(TObject *Sender);
            void __fastcall cmdCharacterSetAddClick(TObject *Sender);
            void __fastcall cmdCharacterSetRemoveClick(TObject *Sender);
            void __fastcall cmdCharacterSetCloneClick(TObject *Sender);
            void __fastcall cmdCharacterSetRenameClick(TObject *Sender);
            void __fastcall lstCharacterSetListClick(TObject *Sender);
            void __fastcall spdCharacterSetSpaceClick(TObject *Sender);
            void __fastcall pbxCharacterSetPreviewPaint(TObject *Sender);
            void __fastcall pbxCharacterSetPreviewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
            void __fastcall cmbCharacterSetFormatChange(TObject *Sender);
        private:	// User declarations
            ZXImageInterface        m_ImageEditor;
            TZX_HPLUGIN             m_PluginHandle;
            ZXImageManager*         m_pImageManager;
            std::vector<String>     m_vPaletteSignatures;
            int                     m_iPixelsHigh;
            int                     m_iActiveCharacter;

            void        __fastcall  UpdateButtons(void);
            void        __fastcall  SetComboText(TComboBox* pComboBox, String sText);
            void        __fastcall  ResizeChars(int W, int H);
            String      __fastcall  GetCharName(String sName, int Index);

        public:		// User declarations
                        __fastcall  TfrmCharacterType(TComponent* Owner);

            HRESULT     __fastcall  Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance);
            HRESULT     __fastcall  Release(void);
            void        __fastcall  SetPalettes(TStrings* pPalettes, std::vector<String>& vSignatures);
            void        __fastcall  RefreshList(void);
            void        __fastcall  UpdatePreview(void);
        };
        //---------------------------------------------------------------------------
    }
}
//---------------------------------------------------------------------------
extern PACKAGE Scorpio::ImageTypes::TfrmCharacterType *frmCharacterType;
//---------------------------------------------------------------------------
#endif
