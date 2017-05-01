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
#ifndef fSearchH
#define fSearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmSearch : public TForm
{
__published:	// IDE-managed Components
    TButton *cmdOK;
    TButton *cmdCancel;
    TLabel *lblTextToFind;
    TComboBox *cmbFindText;
    TGroupBox *grpOptoins;
    TCheckBox *chkCaseSensitive;
    TCheckBox *chkWholeWordsOnly;
    TGroupBox *grpDirection;
    TRadioButton *radForward;
    TRadioButton *radBackwards;
    TGroupBox *grpScope;
    TRadioButton *radGlobal;
    TRadioButton *radAllFiles;
    TRadioButton *radProjectFiles;
    TGroupBox *grpOrigin;
    TRadioButton *radFromCursor;
    TRadioButton *radEntireScope;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall cmdOKClick(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    enum eBools     {
                        eCaseSensitive, eWholeWordsOnly,
                        eForward, eBackward,
                        eGlobal, eSelectedText, eProjectFiles,
                        eFromCursor, eEntireScope,
                    };
    enum eStrings   {
                        eFindText
                    };

    bool    __fastcall  GetBool(int iIndex);
    void    __fastcall  SetBool(int iIndex, bool bValue);
    String  __fastcall  GetText(int iIndex);
    void    __fastcall  SetText(int iIndex, String bValue);

public:		// User declarations
            __fastcall  TfrmSearch(TComponent* Owner);
            
    bool    __fastcall  Execute(void);

    __property  bool    CaseSensitive   = { read = GetBool, write = SetBool, index = eCaseSensitive     };
    __property  bool    WholeWordsOnly  = { read = GetBool, write = SetBool, index = eWholeWordsOnly    };
    __property  bool    Forward         = { read = GetBool, write = SetBool, index = eForward           };
    __property  bool    Backward        = { read = GetBool, write = SetBool, index = eBackward          };
    __property  bool    Global          = { read = GetBool, write = SetBool, index = eGlobal            };
    __property  bool    ProjectFiles    = { read = GetBool, write = SetBool, index = eProjectFiles      };
    __property  bool    FromCursor      = { read = GetBool, write = SetBool, index = eFromCursor        };
    __property  bool    EntireScope     = { read = GetBool, write = SetBool, index = eEntireScope       };
    __property  String  FindText        = { read = GetText, write = SetText, index = eFindText          };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSearch *frmSearch;
//---------------------------------------------------------------------------
#endif
