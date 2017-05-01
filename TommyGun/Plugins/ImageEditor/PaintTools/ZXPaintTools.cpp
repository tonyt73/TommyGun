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
RL_MESSAGE_LOGGER_OBJECT
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace PaintTools;
using namespace Interface;
using namespace Plugin;
//---------------------------------------------------------------------------
const int crCursorDropper = 100;
const int crCursorFill    = 101;
const int crCursorPencil  = 102;
const int crCursorShape   = 103;
const int crCursorText    = 104;
//---------------------------------------------------------------------------
const int g_Cursors[] =
{
    crCursorPencil,     // free
    crCross,            // line
    crCursorDropper,    // dropper
    crCross,            // spray
    crCursorFill,       // fill
    crCursorText,       // text
    crCursorShape,      // rect
    crCursorShape,      // rect fill
    crCursorShape,      // circle
    crCursorShape,      // circle fill
    crDefault,          // invert
    crDefault,          // swap
    crCross,            // mark hot spot
    crDefault,          //
    crDefault,          //
    crDefault,          //
    crDefault,          //
    crDefault,          //
    crDefault,          //
    crDefault,          //
    crDefault,          //
    crDefault,          //
    crDefault,          //
    crDefault,          //
};
//---------------------------------------------------------------------------
// NewPluginClass
/**
 * Called from ImageEditor.cpp to create a new Plugin object. The ImageEditor.cpp only uses the
 * Base class reference. So this function returns a Plugin object to use of type class ZXBasePlugin.
 * @return  ZXBasePlugin a ZXBasePlugin compatible object
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
ZXPaintTools* NewPluginClass(void)
{
    RL_METHOD
    // create the new plugin class object
    return new ZXPaintTools();
}
//---------------------------------------------------------------------------
// Constructor
/**
 * Allocates resource for use by the Plugin class
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
__fastcall ZXPaintTools::ZXPaintTools()
{
    RL_METHOD
    Screen->Cursors[crCursorDropper] = LoadCursor(HInstance, "DROPPER");
    Screen->Cursors[crCursorFill   ] = LoadCursor(HInstance, "FILL"   );
    Screen->Cursors[crCursorPencil ] = LoadCursor(HInstance, "PENCIL" );
    Screen->Cursors[crCursorShape  ] = LoadCursor(HInstance, "SHAPE"  );
    Screen->Cursors[crCursorText   ] = LoadCursor(HInstance, "TEXT"   );
    
    frmPaintTools = new TfrmPaintTools(NULL);
    frmTextDialog = new TfrmTextDialog(NULL);
    m_Tools[ 0]   = new ZXToolDrawFree();
    m_Tools[ 1]   = new ZXToolDrawLine();
    m_Tools[ 2]   = new ZXToolDrawDropper();
    m_Tools[ 3]   = new ZXToolDrawSpray();
    m_Tools[ 4]   = new ZXToolDrawFill();
    m_Tools[ 5]   = new ZXToolDrawText();
    m_Tools[ 6]   = new ZXToolDrawRect();
    m_Tools[ 7]   = new ZXToolDrawRectFill();
    m_Tools[ 8]   = new ZXToolDrawCircle();
    m_Tools[ 9]   = new ZXToolDrawCircleFill();
    m_Tools[10]   = new ZXToolDrawInvert();
    m_Tools[11]   = new ZXToolDrawSwap();
    m_Tools[12]   = new ZXToolHotSpot();
}
//---------------------------------------------------------------------------
// Destructor
/**
 * Frees the resources of the Plugin class
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
__fastcall ZXPaintTools::~ZXPaintTools()
{
    RL_METHOD
    // release our resources before dying
    SAFE_DELETE(frmTextDialog);
    SAFE_DELETE(frmPaintTools);
    Release();
}
//---------------------------------------------------------------------------
// InitialisePlugin
/**
 * Initialises the plugin for use
 * @param   PluginHandle the handle allocated to the plugin
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaintTools::InitialisePlugin(ZXPlugin* pPlugin)
{
    RL_METHOD
    HRESULT hResult = E_POINTER;
    m_ImageEditor.GetInterfaces(pPlugin->ParentInstance);
    // use the hInstanceParent to get the Parent Interfaces using GetProcAddress
    // if the interfaces do not exist then fail the Initialization
    // if it passes then
    //   TODO: create the paint tool buttons
    //   and add them the parent plugin
    if (true == SAFE_PTR(frmPaintTools))
    {
        hResult = frmPaintTools->Initialize(pPlugin->Handle, pPlugin->ParentInstance);
    }
    return hResult;
}
//---------------------------------------------------------------------------
// ReleasePlugin
/**
 * Releases the resources associated with the Plugin
 * @return  HRESULT S_OK success, S_FALSE failure
 * @author  KiwiWare Plugin Wizard
 * @date    Created 17 December 2001 by Tony Thompson
 * @remarks Copyright Scorpio Software 2001
 */
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaintTools::ReleasePlugin(void)
{
    RL_METHOD
    RL_HRESULT(S_OK)
    if (true == SAFE_PTR(frmPaintTools))
    {
        hResult = frmPaintTools->Release();
    }
    return hResult;
}
//---------------------------------------------------------------------------
void __fastcall ZXPaintTools::RegisterEvents(void)
{
    // TODO: Register for the parent plugin events we need
    //RegisterEvent(TZX_QUERY_DATASAVED   , EventSaveQuery    );
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaintTools::MouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    RL_METHOD
    RL_HRESULT(E_FAIL)
    int iTool = GetCurrentTool();
    if (-1 != iTool)
    {
        // save the undo information
        PushUndo(Image, utUndo, iTool);
        // start the tool operation
        hResult = m_Tools[iTool]->MouseDown(Image, Button, Shift, X, Y) ? S_OK : S_FALSE;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaintTools::MouseMove(ZXImage* Image, TShiftState Shift, int X, int Y)
{
    //RL_METHOD
    RL_HRESULT(E_FAIL)
    int iTool = GetCurrentTool();
    if (-1 != iTool)
    {
        hResult = m_Tools[iTool]->MouseMove(Image, Shift, X, Y) ? S_OK : S_FALSE;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaintTools::MouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    RL_METHOD
    RL_HRESULT(E_FAIL)
    int iTool = GetCurrentTool();
    if (-1 != iTool)
    {
        // finish the tool operation
        hResult = m_Tools[iTool]->MouseUp(Image, Button, Shift, X, Y) ? S_OK : S_FALSE;
        // save the redo information
        PushUndo(Image, utRedo, iTool);
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaintTools::Cursor(TCursor& Cursor)
{
    RL_METHOD
    RL_HRESULT(E_FAIL)
    int iTool = GetCurrentTool();
    if (-1 != iTool)
    {
        Cursor  = (TCursor)g_Cursors[iTool];
        hResult = S_OK;
    }
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXPaintTools::ImageChange(ZXImage* Image)
{
    RL_METHOD
    m_Tools[frmPaintTools->tbnToolInvert->Tag]->Enabled = false == Image->Palette->SupportsPixelsOnly;
    m_Tools[frmPaintTools->tbnToolSwapAttributes->Tag]->Enabled = false == Image->Palette->SupportsPixelsOnly;
    frmPaintTools->tbnToolInvert->Enabled = false == Image->Palette->SupportsPixelsOnly;
    frmPaintTools->tbnToolSwapAttributes->Enabled = false == Image->Palette->SupportsPixelsOnly;
    return S_OK;
}
//---------------------------------------------------------------------------
int __fastcall ZXPaintTools::GetCurrentTool(void)
{
    int iTool = -1;
    iTool = frmPaintTools->tbnToolFreeHand->Down       ? frmPaintTools->tbnToolFreeHand->Tag       : iTool;
    iTool = frmPaintTools->tbnToolLine->Down           ? frmPaintTools->tbnToolLine->Tag           : iTool;
    iTool = frmPaintTools->tbnToolAttribute->Down      ? frmPaintTools->tbnToolAttribute->Tag      : iTool;
    iTool = frmPaintTools->tbnToolSpray->Down          ? frmPaintTools->tbnToolSpray->Tag          : iTool;
    iTool = frmPaintTools->tbnToolFill->Down           ? frmPaintTools->tbnToolFill->Tag           : iTool;
    iTool = frmPaintTools->tbnToolText->Down           ? frmPaintTools->tbnToolText->Tag           : iTool;
    iTool = frmPaintTools->tbnToolRectangle->Down      ? frmPaintTools->tbnToolRectangle->Tag      : iTool;
    iTool = frmPaintTools->tbnToolRectangleFill->Down  ? frmPaintTools->tbnToolRectangleFill->Tag  : iTool;
    iTool = frmPaintTools->tbnToolCircle->Down         ? frmPaintTools->tbnToolCircle->Tag         : iTool;
    iTool = frmPaintTools->tbnToolCircleFill->Down     ? frmPaintTools->tbnToolCircleFill->Tag     : iTool;
    iTool = frmPaintTools->tbnToolInvert->Down         ? frmPaintTools->tbnToolInvert->Tag         : iTool;
    iTool = frmPaintTools->tbnToolSwapAttributes->Down ? frmPaintTools->tbnToolSwapAttributes->Tag : iTool;
    iTool = frmPaintTools->tbnToolHotSpot->Down        ? frmPaintTools->tbnToolHotSpot->Tag        : iTool;
    return iTool;
}
//---------------------------------------------------------------------------
void __fastcall ZXPaintTools::PushUndo(ZXImage* pImage, ZXUndoType UndoType, int iTool)
{
    KXmlInfo Undo;
    Undo.Add("Operation", "ImageChange");
    Undo.Add("Plugin", "Paint Tools");
    Undo.Add("Description", String(m_Tools[iTool]->Name + " [" + pImage->Name + "]"));
    KXmlInfo Image("Image");
    pImage->Save(Image, false);
    Undo.Add(Image);
    m_ImageEditor.Notify(NULL, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, UndoType, 0);
}
//---------------------------------------------------------------------------

