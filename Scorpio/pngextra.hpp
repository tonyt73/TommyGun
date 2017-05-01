// CodeGear C++Builder
// Copyright (c) 1995, 2007 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Pngextra.pas' rev: 11.00

#ifndef PngextraHPP
#define PngextraHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Pngimage.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <Extctrls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Pngextra
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TPNGButtonStyle { pbsDefault, pbsFlat, pbsNoFrame };
#pragma option pop

#pragma option push -b-
enum TPNGButtonLayout { pbsImageAbove, pbsImageBellow, pbsImageLeft, pbsImageRight };
#pragma option pop

#pragma option push -b-
enum TPNGButtonState { pbsNormal, pbsDown, pbsDisabled };
#pragma option pop

class DELPHICLASS TPNGButton;
class PASCALIMPLEMENTATION TPNGButton : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	TPNGButtonStyle fButtonStyle;
	bool fMouseOverControl;
	AnsiString FCaption;
	TPNGButtonLayout FButtonLayout;
	TPNGButtonState FButtonState;
	Pngimage::TPNGObject* FImageDown;
	Pngimage::TPNGObject* fImageNormal;
	Pngimage::TPNGObject* fImageDisabled;
	Pngimage::TPNGObject* fImageOver;
	Classes::TNotifyEvent fOnMouseEnter;
	Classes::TNotifyEvent fOnMouseExit;
	void __fastcall SetButtonStyle(const TPNGButtonStyle Value);
	void __fastcall SetCaption(const AnsiString Value);
	void __fastcall SetButtonLayout(const TPNGButtonLayout Value);
	void __fastcall SetButtonState(const TPNGButtonState Value);
	void __fastcall SetImageNormal(const Pngimage::TPNGObject* Value);
	void __fastcall SetImageDown(const Pngimage::TPNGObject* Value);
	void __fastcall SetImageOver(const Pngimage::TPNGObject* Value);
	
__published:
	__property Font ;
	__property Visible  = {default=1};
	__property TPNGButtonLayout ButtonLayout = {read=FButtonLayout, write=SetButtonLayout, nodefault};
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
	__property Pngimage::TPNGObject* ImageNormal = {read=fImageNormal, write=SetImageNormal};
	__property Pngimage::TPNGObject* ImageDown = {read=FImageDown, write=SetImageDown};
	__property Pngimage::TPNGObject* ImageOver = {read=fImageOver, write=SetImageOver};
	__property TPNGButtonStyle ButtonStyle = {read=fButtonStyle, write=SetButtonStyle, nodefault};
	__property Enabled  = {default=1};
	__property ParentShowHint  = {default=1};
	__property ShowHint ;
	__property Anchors  = {default=3};
	__property OnMouseDown ;
	__property OnClick ;
	__property OnMouseUp ;
	__property OnMouseMove ;
	__property OnDblClick ;
	__property Classes::TNotifyEvent OnMouseEnter = {read=fOnMouseEnter, write=fOnMouseEnter};
	__property Classes::TNotifyEvent OnMouseExit = {read=fOnMouseExit, write=fOnMouseExit};
	
public:
	__property TPNGButtonState ButtonState = {read=FButtonState, write=SetButtonState, nodefault};
	
protected:
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Click(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Messages::TMessage &Message);
	
public:
	__property bool IsMouseOver = {read=fMouseOverControl, nodefault};
	__fastcall virtual TPNGButton(Classes::TComponent* AOwner);
	__fastcall virtual ~TPNGButton(void);
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);
extern PACKAGE void __fastcall MakeImageHalfTransparent(Pngimage::TPNGObject* Source, Pngimage::TPNGObject* Dest);

}	/* namespace Pngextra */
using namespace Pngextra;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Pngextra
