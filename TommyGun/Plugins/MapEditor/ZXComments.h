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
#ifndef ZXCommentsH
#define ZXCommentsH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
class ZXComments
{
private:
    typedef struct
    {
        TRect   Rect;
        String  Text;
    }
    ZXComment;

    std::vector<ZXComment>  m_Comments;
    int                     m_Selected;
    
public:
                __fastcall  ZXComments();
                __fastcall ~ZXComments();

    void        __fastcall  Draw(TCanvas* Canvas);
    static void __fastcall  DrawFrame(TCanvas* Canvas, const TRect& Rect, bool bGrabPoints);
    void        __fastcall  Add(const TRect& Rect, const String& Text);
    void        __fastcall  Select(const TRect& Rect);
    bool        __fastcall  Select(int X, int Y);
    void        __fastcall  Remove(void);
    bool        __fastcall  HasSelection(void);
    void        __fastcall  SelectClear(void);
    void        __fastcall  Get(TRect& Rect, String& Text);
    void        __fastcall  Set(const TRect& Rect, const String& Text);
    void        __fastcall  Move(int dX, int dY);
};
//---------------------------------------------------------------------------
#endif

