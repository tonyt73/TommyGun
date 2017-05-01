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
#pragma link "KShadePanel"
#pragma link "KSlider"
//-- VCL FORM OBJECT --------------------------------------------------------
TfrmMSXTablesEditor *frmMSXTablesEditor = NULL;
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the class and reset some member variables
 * @param   Owner the VCL owner of the form
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @date    Modified 3 May 2002 by Tony Thompson
 * @remarks Copyright KiwiWare 2001
 */
//---------------------------------------------------------------------------
__fastcall TfrmMSXTablesEditor::TfrmMSXTablesEditor(TComponent* Owner)
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
 * @remarks Copyright KiwiWare 2003
 */
//---------------------------------------------------------------------------
__fastcall TfrmMSXTablesEditor::~TfrmMSXTablesEditor()
{
    RL_METHOD
}
//---------------------------------------------------------------------------
void __fastcall TfrmMSXTablesEditor::FormCreate(TObject *Sender)
{
    pgcMSXTablesMap->DoubleBuffered = true;
    //panMSXTablesMap->DoubleBuffered = true;
}
//---------------------------------------------------------------------------


