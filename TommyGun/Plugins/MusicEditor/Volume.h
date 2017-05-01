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
#ifndef VolumeH
#define VolumeH
//---------------------------------------------------------------------------
#include "ImageRender.h"
//---------------------------------------------------------------------------
class ZXVolume : public ZXGridRender
{
private:
    bool                m_bDirty;
    void    __fastcall  DoRender();
    void    __fastcall  OnResize(TObject *Sender);

public:
            __fastcall  ZXVolume();

    void    __fastcall  Init();
};
//---------------------------------------------------------------------------
#endif
