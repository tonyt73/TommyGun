/*---------------------------------------------------------------------------

	(c) 2002 Scorpio Software
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
//---------------------------------------------------------------------------
#include <algorithm>
#include "KBitmapPanel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(KBitmapPanel *)
{
	new KBitmapPanel(NULL);
}
//---------------------------------------------------------------------------
__fastcall KBitmapPanel::KBitmapPanel(TComponent* Owner)
	: TCustomPanel(Owner)
{
    // initialize the panel
    Parent = TCustomPanel::Parent;
    BorderStyle = bsNone;
    BevelInner = bvNone;
    BevelOuter = bvNone;
    AutoSize = false;
    ParentBackground = false;
    //Width = 64;
    //Height = 64;

	// initialize our members
    FChecked_ = false;
    FCenterImage = false;
    FEdge = 4;
    FLabelEdge = 4;
    FBitmapWidth = 64;
    FBitmapHeight = 64;
    FKeepBitmapSize = true;
    FColorSelected = clHighlight;
	FColorUnSelected = Color;
    FColorSelectedText = clHighlightText;
    FColorUnSelectedText = clWindowText;
    FCaption = Name;
    FSelected = false;
    FShowLabel = true;
    FGroupIndex = 0;
    FTransparent = false;

    // setup our components
	FLabel = new TLabel( this );
    FLabel->Parent = this;
    FLabel->AutoSize = false;
    FLabel->Anchors >> akLeft >> akRight >> akBottom >> akTop;
    FLabel->Height = 26;
    FLabel->Left = FLabelEdge;
    FLabel->Width = Width - ( Edge * 2 );
    FLabel->Top = Height - FEdge - FLabel->Height;
    FLabel->ParentColor = true;
    FLabel->Alignment = taCenter;
    FLabel->Caption = FCaption;
    FLabel->Visible = true;
    FLabel->WordWrap = true;
    FLabel->OnClick = ComponentClick;
    FLabel->OnDblClick = ComponentDblClick;

	FImage = new TImage( this );
    FImage->Parent = this;
    FImage->AutoSize = false;
	FImage->Left = FEdge;
    FImage->Width = Width - FEdge - FEdge;
    FImage->Anchors >> akLeft >> akRight >> akBottom >> akTop;
    FImage->OnClick = ComponentClick;
    FImage->OnDblClick = ComponentDblClick;
    FImage->Height = Height - FEdge - FEdge - ( FShowLabel ? FLabel->Height : 0 );
    FImage->Transparent = true;
    FImage->Stretch = true;
    FImage->Picture->Bitmap->TransparentColor = clFuchsia;
    FImage->Picture->Bitmap->TransparentMode = tmFixed;

    // refresh the component
    //Change( );
}
//---------------------------------------------------------------------------
__fastcall KBitmapPanel::~KBitmapPanel( )
{
	delete FLabel;
    delete FImage;
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::Change( void )
{
    Resize( );
}
//---------------------------------------------------------------------------
TPicture* __fastcall KBitmapPanel::GetPicture( void )
{
	return FImage->Picture;
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::LoadFromFile( String& bmpFile )
{
    TPicture* Picture = new TPicture();
    Picture->LoadFromFile(bmpFile);
    SetPicture(Picture);
    delete Picture;
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::SetPicture( TPicture* Value )
{
	FImage->Picture->Assign( Value );
    //FImage->Width   = BitmapWidth;
    //FImage->Height  = BitmapHeight;
    FImage->Stretch = false;
    if (CenterImage)
    {
        FImage->AutoSize = true;
    }
    FImage->Width  = std::min(BitmapWidth , FImage->Width );
    FImage->Height = std::min(BitmapHeight, FImage->Height);
    /*if ((Value->Width != BitmapWidth || Value->Height != BitmapHeight))
    {
        if (Value->Width != Value->Height)
        {
            if (Value->Width > Value->Height)
            {
                // keep width, adjust image height
                float fPortion = (float)Value->Height / (float)Value->Width;
                FImage->Height = (int)((float)FImage->Height * fPortion);
            }
            else
            {
                float fPortion = (float)Value->Width / (float)Value->Height;
                FImage->Width  = (int)((float)FImage->Width * fPortion);
            }
        }
    }*/
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::SetInt(int Index, int Value )
{
	switch( Index )
    {
    	case 0:
        	if ( Value > 0 && Value < 64 )
	        	FEdge = Value;
            if ( FEdge < 1 )
            	FEdge = 1;
            if ( FEdge > 64 )
            	FEdge = 64;
            //Width = FEdge + FBitmapWidth + FEdge;
        	break;
        case 1:
        	if ( Value >= 8 && Value <= 256 )
	        	FBitmapWidth = Value;

            if ( FBitmapWidth < 8 )
            	FBitmapWidth = 8;
            if ( FBitmapWidth > 256 )
            	FBitmapWidth = 256;

            //Width = FEdge + FBitmapWidth + FEdge;
            break;
        case 2:
        	if ( Value >= 8 && Value <= 256 )
	        	FBitmapHeight = Value;

            if ( FBitmapHeight < 8 )
            	FBitmapHeight = 8;
            if ( FBitmapHeight > 256 )
            	FBitmapHeight = 256;

            //Height = Value + FTopEdge + FTopEdge + FLabel->Height;
            break;
        case 3:
        	if ( Value >= 0 )
            	FGroupIndex = Value;
            break;
    	case 4:
        	if ( Value > 0 && Value < 64 )
	        	FLabelEdge = Value;
            if ( FLabelEdge < 1 )
            	FLabelEdge = 1;
            if ( FLabelEdge > 64 )
            	FLabelEdge = 64;
        	break;
    	case 5:
        	if ( Value > 0 && Value < 64 )
	        	FTopEdge = Value;
            if ( FTopEdge < 1 )
            	FTopEdge = 1;
            if ( FTopEdge > 64 )
            	FTopEdge = 64 ;
            //Height = Value + FTopEdge + FTopEdge + FLabel->Height;
        	break;
    	default:
        	break;
    }
    Resize( );
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::SetBool(int Index, bool Value )
{
	switch( Index )
    {
		case 0:
        	FKeepBitmapSize = Value;
            break;
        case 1:
        	FSelected = Value;

            if ( Value )
	            FLabel->Font->Color = FColorSelectedText;
            else
	            FLabel->Font->Color = FColorUnSelectedText;

            if ( Value && Parent != NULL )
            {
                for ( int i = 0; i < Parent->ControlCount; i++ )
                {
	                if ( Parent->Controls[i]->ClassNameIs( "KBitmapPanel" ) )
    	            {
		                KBitmapPanel* Sibling = (KBitmapPanel*)Parent->Controls[i];

        		        if ( ( Sibling != this ) && ( Sibling->GroupIndex == GroupIndex ) )
                            Sibling->Selected = false;
                    }
                }
            }

            break;
        case 2:
        	FBitmapStretch = Value;
            FImage->Stretch = Value;
            break;
        case 3:
        	FShowLabel = Value;
            break;
        case 4:
        	FTransparent = Value;
            FImage->Transparent = Value;
            break;
        case 5:
        	FCenterImage = Value;
            break;
    }
    Change( );
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::SetString(int Index, AnsiString Value )
{
	switch( Index )
    {
    	case 0:
        	FCaption = Value;
            FLabel->Caption = FCaption;
            break;
        case 1:
            FFile = Value;
            break;
    	default:
        	break;
    }
    Change( );
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::SetColor(int Index, TColor Value )
{
	switch ( Index )
    {
		case 0:
        	FColorSelected = Value;
            break;
        case 1:
        	FColorUnSelected = Value;
            TCustomPanel::Color = Value;
            break;
        case 2:
        	FColorSelectedText = Value;

            if ( FSelected )
	            FLabel->Font->Color = Value;
            break;
        case 3:
        	FColorUnSelectedText = Value;

            if ( !FSelected )
	            FLabel->Font->Color = Value;
            break;
    }
    Change( );
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::Resize()
{
	int height;

    TCustomPanel::Resize();
    
    if ( ComponentState.Contains( csDesigning ) )
    {
	    FLabel->Visible = true;
    	height = FLabel->Height;
    }
    else
    {
	    FLabel->Visible = FShowLabel;
    	height = FShowLabel ? FLabel->Height : 0;
    }

    if ( FKeepBitmapSize )
    {
    	Height = FTopEdge + FBitmapHeight + height + FTopEdge;
        Width = FEdge + FBitmapWidth + FEdge;
    }

    FLabel->Top = Height - FTopEdge - FLabel->Height;
    FLabel->Left = FLabelEdge;
    FLabel->Width = Width - ( FLabelEdge + FLabelEdge );
	FLabel->Caption = FCaption;
    Color = FSelected ? FColorSelected : FColorUnSelected;

    if (!FCenterImage)
    {
        FImage->Top = FTopEdge;
        FImage->Left = FEdge;
        FImage->Height = Height - FTopEdge - FTopEdge - height;
        FImage->Width = Width - ( FEdge + FEdge );
    }
    else
    {
        FImage->Top = (FLabel->Top - FImage->Height) / 2;
        FImage->Left = (Width - FImage->Width) / 2;
        FImage->Width  = std::min(BitmapWidth , FImage->Width );
        FImage->Height = std::min(BitmapHeight, FImage->Height);
        //FImage->Height = Height - FTopEdge - FTopEdge - height;
        //FImage->Width = Width - ( FEdge + FEdge );
    }

    if ( OnResize != NULL )
        OnResize( this );
}
//---------------------------------------------------------------------------
/*void __fastcall KBitmapPanel::DoEnter()
{
	TCustomPanel::DoEnter( );
	Selected = true;
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::DoExit()
{
	TCustomPanel::DoExit( );
	//Selected = false;
}
*/
/*//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::Click( )
{
	//TCustomPanel::Click( );
    ComponentClick( this );
}*/
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::ComponentClick( TObject* /*Sender*/ )
{
    if ( OnClick != NULL )
    	OnClick( this );
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::ComponentDblClick( TObject* /*Sender*/ )
{
    if ( OnDblClick != NULL )
    	OnDblClick( this );
}
//---------------------------------------------------------------------------
void __fastcall KBitmapPanel::ReloadBitmap( void )
{
    try
    {
        bool isTransparent = FImage->Transparent;
        FImage->Transparent = false;

        AnsiString bmpFile = ChangeFileExt(File, ".bmp");

    	if ( FileExists( bmpFile ) )
			FImage->Picture->LoadFromFile( bmpFile );
		
        FImage->Transparent = isTransparent;
    }
    catch ( Exception& e )
    {
    }
    FImage->Invalidate();
}
//---------------------------------------------------------------------------
namespace Kbitmappanel
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(KBitmapPanel)};
		RegisterComponents("Scorpio", classes, 0);
	}
}
//---------------------------------------------------------------------------
