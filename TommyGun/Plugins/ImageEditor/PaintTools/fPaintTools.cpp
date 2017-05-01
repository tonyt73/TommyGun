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
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "..\..\..\SafeMacros.h"
#include "fPaintTools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace PaintTools;
//---------------------------------------------------------------------------
TfrmPaintTools *frmPaintTools = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmPaintTools::TfrmPaintTools(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmPaintTools::Initialize(TZX_HPLUGIN PluginHandle, HINSTANCE hParentInstance)
{
    RL_HRESULT(S_OK);
    m_PluginHandle = PluginHandle;
    m_ImageEditor.GetInterfaces(hParentInstance);
    m_ImageEditor.ToolMergePaintToolBar(PluginHandle, tbrPaintTools);
    return hResult;
}
//---------------------------------------------------------------------------
HRESULT __fastcall TfrmPaintTools::Release(void)
{
    RL_HRESULT(S_OK);
    // undock our toolbuttons
    tbnToolFreeHand->Parent->RemoveControl(tbnToolFreeHand);
    tbnToolLine->Parent->RemoveControl(tbnToolLine);
    tbnToolAttribute->Parent->RemoveControl(tbnToolAttribute);
    tbnToolSpray->Parent->RemoveControl(tbnToolSpray);
    tbnToolFill->Parent->RemoveControl(tbnToolFill);
    tbnToolText->Parent->RemoveControl(tbnToolText);
    tbnToolRectangle->Parent->RemoveControl(tbnToolRectangle);
    tbnToolRectangleFill->Parent->RemoveControl(tbnToolRectangleFill);
    tbnToolCircle->Parent->RemoveControl(tbnToolCircle);
    tbnToolCircleFill->Parent->RemoveControl(tbnToolCircleFill);
    tbnToolInvert->Parent->RemoveControl(tbnToolInvert);
    tbnToolSwapAttributes->Parent->RemoveControl(tbnToolSwapAttributes);
    tbnToolHotSpot->Parent->RemoveControl(tbnToolHotSpot);
    return hResult;
}
//---------------------------------------------------------------------------

