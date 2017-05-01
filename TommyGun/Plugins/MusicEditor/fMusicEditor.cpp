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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "TButtonUnit"
#pragma link "TPanelUnit"
#pragma link "TEditUnit"
#pragma link "TScrollbarUnit"
#pragma link "TSpeedButtonUnit"
#pragma link "TSpinEditUnit"
#pragma link "KRegistry"
#pragma link "KShadePanel"
//-- VCL FORM OB--------------------------------------------------------
TfrmMusicEditor *frmMusicEditor = NULL;
const String g_sInvalidChars = "\\ / : * ? \" < > | & ^\n\n";
const String g_sBlank        = "";
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the class and reset some member variables
 * @param   Owner the VCL owner of the form
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @date    Modified 3 May 2002 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
__fastcall TfrmMusicEditor::TfrmMusicEditor(TComponent* Owner)
    : TForm(Owner),
      m_bInitialized(false),
      m_bSaved(false),
      m_PluginHandle(NULL)
{
    RL_METHOD
}
//---------------------------------------------------------------------------
// Destructor
/**
 * @brief   Frees allocated resources
 * @author  Tony Thompson
 * @date    Created 10 March 2003 by Tony Thompson
 * @remarks Copyright Scorpio Software 2003
 */
//---------------------------------------------------------------------------
__fastcall TfrmMusicEditor::~TfrmMusicEditor()
{
    RL_METHOD
}
//---------------------------------------------------------------------------
void __fastcall TfrmMusicEditor::FormCreate(TObject *Sender)
{
    panPianoToolbarContainer->DoubleBuffered = true;
    //panHScroll->DoubleBuffered = true;
    //panVScroll->DoubleBuffered = true;
    scbTimeline->DoubleBuffered = true;
    scbKeyboard->DoubleBuffered = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMusicEditor::FormPaint(TObject *Sender)
{
    m_Keyboard.Render();
    m_Timeline.Render();
    m_Music.Render();
    m_Volume.Render();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMusicEditor::FormResize(TObject *Sender)
{
    panPianoPatternContainerResize(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMusicEditor::panPianoPatternContainerResize(TObject *Sender)
{
    // rescale the scroll bars
    scbTimeline->Max = std::max(0, (imgMusicCanvas->Width  - panMusicScroller->Width )/* - scbTimeline->Width */);
    scbKeyboard->Max = std::max(0, (imgMusicCanvas->Height - panMusicScroller->Height)/* - scbKeyboard->Height*/);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMusicEditor::scbTimelineScroll(TObject *Sender, int ScrollPos)
{
    imgMusicCanvas->Left  = std::max(-scbTimeline->Position, -panMusicScroller->Width );
    imgVolumeCanvas->Left = std::max(-scbTimeline->Position, -panVolumeScroller->Width);
    panPianoPatternContainer->Refresh();
    panVolumeScroller->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMusicEditor::scbKeyboardScroll(TObject *Sender, int ScrollPos)
{
    imgMusicCanvas->Top = std::max(-scbKeyboard->Position, -panMusicScroller->Height   );
    imgKeysCanvas->Top  = std::max(-scbKeyboard->Position, -panKeyboardScroller->Height);
    panPianoPatternContainer->Refresh();
}
//---------------------------------------------------------------------------

