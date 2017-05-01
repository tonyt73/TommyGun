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
#ifndef ImageRenderH
#define ImageRenderH
//---------------------------------------------------------------------------
class ZXImageRender
{
private:
    bool                        m_bDirty;

protected:
    virtual void    __fastcall  DoRefresh() {};
    virtual void    __fastcall  DoRender() = 0;

            void    __fastcall  Dirty() { m_bDirty = true; }

public:
                    __fastcall  ZXImageRender();

    virtual void    __fastcall  Init() = 0;
            void    __fastcall  Render();
            void    __fastcall  Refresh();

    __property bool IsDirty = { read = m_bDirty };
};
//---------------------------------------------------------------------------
class ZXGridRender : public ZXImageRender
{
private:
    int                 m_iGridWidth;
    int                 m_iGridHeight;
    int                 m_iSectionWidth;
    int                 m_iHighlightColumn;
    bool                m_bStretch;

    TColor              m_LightSection;
    TColor              m_DarkSection;
    TColor              m_LightLine;
    TColor              m_MediumLine;
    TColor              m_BrightLine;
    TColor              m_Highlight;

    void    __fastcall  SetWidth(int Width)         { m_iGridWidth  = Width ; Dirty();          };
    void    __fastcall  SetHeight(int Height)       { m_iGridHeight = Height; Dirty();          };
    void    __fastcall  SetHighlight(int highlight) { m_iHighlightColumn = highlight; Dirty();  }

protected:
    void    __fastcall  RenderGrid(TCanvas* pCanvas, int Width, int Height);

public:

            __fastcall  ZXGridRender();

    __property int      GridWidth  = { read = m_iGridWidth      , write = SetWidth      };
    __property int      GridHeight = { read = m_iGridHeight     , write = SetHeight     };
    __property int      Highlight  = { read = m_iHighlightColumn, write = SetHighlight  };
};
//---------------------------------------------------------------------------
#endif
