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
#ifndef TimelineH
#define TimelineH
//---------------------------------------------------------------------------
class ZXTimeline : public ZXImageRender
{
private:
    int                 m_iGridWidth;
    int                 m_iGridHeight;

    void    __fastcall  OnResize(TObject *Sender);
    void    __fastcall  DoRender();

public:
            __fastcall  ZXTimeline();

    void    __fastcall  Init();
    void    __fastcall  Scroll(int delta);
    void    __fastcall  Zoom(int delta);
};
//---------------------------------------------------------------------------
#endif
