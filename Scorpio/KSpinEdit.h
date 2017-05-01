/*---------------------------------------------------------------------------

	(c) 2008 Scorpio Software
		1 Nancybell Court
		Bellmere
		Brisbane QLD 4510
		Australia

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef KSpinEditH
#define KSpinEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
enum TIntValue  { eIntValue, eIntValueMin, eIntValueMax, eIntValueStep };
//---------------------------------------------------------------------------
/**
 * This class represents a Windows Media Player 11 Vista Glass style button.
 *
 * It supports several styles of buttons. You can choose from a standard
 * round cornered button or one with a flat bottom. Each type can then have
 * a drop down button as well. If the drop down is present then it is
 * activated by a separate button and uses the assigned popup menu to display
 * the execute.
 *
 */
//---------------------------------------------------------------------------
class PACKAGE KSpinEdit : public TPanel
{
private:
    TEdit*		        m_Edit;
    TBitBtn*	        m_Up;
    TBitBtn*            m_Down;
    Graphics::TBitmap*  m_ArrowUp;
    Graphics::TBitmap*  m_ArrowDown;
    int                 m_Value;
    int                 m_LastValue;
    int                 m_Min;
    int                 m_Max;
    int                 m_Step;
    bool                m_Enabled;
    bool                m_Changing;

    TNotifyEvent        FOnChanged;
    TNotifyEvent        FOnChangedUp;
    TNotifyEvent        FOnChangedDown;

    void    __fastcall  OnEditChange(TObject* Sender);
    void    __fastcall  OnKeyPress(TObject *Sender, char &key);
    void    __fastcall  OnValueInc(TObject* Sender);
    void    __fastcall  OnValueDec(TObject* Sender);
    void    __fastcall  OnExit(TObject* Sender);
    void    __fastcall  Validate();
    void    __fastcall  SetInt(int index, int value);
    void    __fastcall  SetEnabled(bool value);

public:
            __fastcall  KSpinEdit(TComponent* Owner);
            __fastcall ~KSpinEdit();

DYNAMIC void __fastcall Resize(void);

__published:
    // custom properties
    __property  int         Value           = { read = m_Value  , write = SetInt, index = eIntValue    , default = 0    };
    __property  int         Min             = { read = m_Min    , write = SetInt, index = eIntValueMin , default = 0    };
    __property  int         Max             = { read = m_Max    , write = SetInt, index = eIntValueMax , default = 100  };
    __property  int         Step            = { read = m_Step   , write = SetInt, index = eIntValueStep, default = 1    };
    __property  bool        Enabled         = { read = m_Enabled, write = SetEnabled                   , default = true };
    // custom events
	__property TNotifyEvent OnChanged       = { read = FOnChanged, write = FOnChanged                   };
	__property TNotifyEvent OnChangedUp     = { read = FOnChangedUp, write = FOnChangedUp               };
	__property TNotifyEvent OnChangedDown   = { read = FOnChangedDown, write = FOnChangedDown           };
};
//---------------------------------------------------------------------------
#endif
