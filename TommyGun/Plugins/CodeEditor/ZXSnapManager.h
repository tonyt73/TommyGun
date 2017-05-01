//---------------------------------------------------------------------------
#ifndef SnapManagerH
#define SnapManagerH
//- VCL ---------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//- STL ---------------------------------------------------------------------
#include <vector>
#include <map>
//---------------------------------------------------------------------------
enum TSnapEdge  { seNone, seLeft, seRight, seTop, seBottom };
//---------------------------------------------------------------------------
class ZXSnapManager
{
private:
	enum TSnapState { ssNothing, ssScreen, ssParent             };
	enum TDockRange { drVertical, drHorizontal                  };

	struct TSnapWindow
	{
		TSnapState  SnapState;
		TSnapEdge   SnapEdge;
		TForm*      SnapParent;
		TPoint      SnapPoint;
	};

	typedef std::map<TForm*, TPanel*>       TSnapPanels;
	typedef std::map<TForm*, TSnapWindow>   TSnapForms;
	typedef TSnapForms::iterator            TSnapFormsIt;

	static TSnapPanels                      m_SnapPanels;
    static TSnapForms                       m_SnapForms;
    static TForm*                           m_SnapForm;
    static TPanel*                          m_SnapPanel;

    static int                              m_MouseX;
    static int                              m_MouseY;

                    __fastcall  ZXSnapManager();
                    __fastcall ~ZXSnapManager();

    static bool     __fastcall  IsClose(int a, int b);
    static void     __fastcall  SnapToWorkArea(TForm* form, RECT*& rect, const RECT& wa, TSnapState snapState);
    static void     __fastcall  GetParentWorkArea(TForm* form, RECT& wa);

public:

	static bool     __fastcall  ProcessMoving(Messages::TMessage &Message, TForm* form);
    static void     __fastcall  RegisterDocking(TForm* form, TPanel* snapPanel);
    static void     __fastcall  RegisterSnapClient(TForm* clientForm, TForm* parentForm, TSnapEdge snapEdge, int xOffset = 0, int yOffset = 0);
    static void     __fastcall  Unregister(TForm* form);
    static TPoint   __fastcall  SnapPoint(TForm* form, TRect* rect);
    static void     __fastcall  UpdateSnapClients(TForm* parentForm);
};
//---------------------------------------------------------------------------
#endif
