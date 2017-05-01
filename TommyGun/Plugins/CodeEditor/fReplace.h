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
#ifndef fReplaceH
#define fReplaceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmReplace : public TForm
{
__published:	// IDE-managed Components
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
    TRadioButton *radSelectedText;
    TGroupBox *grpOrigin;
    TRadioButton *radFromCursor;
    TRadioButton *radEntireScope;
    TButton *cmdOK;
    TButton *cmdCancel;
    TLabel *lblRepalceWith;
    TComboBox *cmbReplaceText;
    TCheckBox *chkPromptOnReplace;
    TButton *cmdReplaceAll;
    void __fastcall cmdReplaceAllClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    enum eBools     { eCaseSensitive, eWholeWordsOnly, ePromptOnReplace,
                      eForward, eBackward,
                      eGlobal, eSelectedText,
                      eFromCursor, eEntireScope,
                      eReplaceAll
                    };
    enum eStrings   { eFindText, eReplaceText
                    };

    bool                m_bReplaceAll;
                    
    bool    __fastcall  GetBool(int iIndex);
    void    __fastcall  SetBool(int iIndex, bool bValue);
    String  __fastcall  GetText(int iIndex);
    void    __fastcall  SetText(int iIndex, String bValue);
    
public:		// User declarations
            __fastcall  TfrmReplace(TComponent* Owner);
            
    bool    __fastcall  Execute(void);

    __property  bool    CaseSensitive   = { read = GetBool, write = SetBool, index = eCaseSensitive     };
    __property  bool    WholeWordsOnly  = { read = GetBool, write = SetBool, index = eWholeWordsOnly    };
    __property  bool    PromptOnReplace = { read = GetBool, write = SetBool, index = ePromptOnReplace   };
    __property  bool    Forward         = { read = GetBool, write = SetBool, index = eForward           };
    __property  bool    Backward        = { read = GetBool, write = SetBool, index = eBackward          };
    __property  bool    Global          = { read = GetBool, write = SetBool, index = eGlobal            };
    __property  bool    SelectedText    = { read = GetBool, write = SetBool, index = eSelectedText      };
    __property  bool    FromCursor      = { read = GetBool, write = SetBool, index = eFromCursor        };
    __property  bool    EntireScope     = { read = GetBool, write = SetBool, index = eEntireScope       };
    __property  bool    ReplaceAll      = { read = GetBool,                  index = eReplaceAll    };
    __property  String  FindText        = { read = GetText, write = SetText, index = eFindText          };
    __property  String  ReplaceText     = { read = GetText, write = SetText, index = eReplaceText       };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmReplace *frmReplace;
//---------------------------------------------------------------------------
#endif
