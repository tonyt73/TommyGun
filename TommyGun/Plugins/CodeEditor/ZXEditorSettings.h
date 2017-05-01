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
#ifndef ZXEditorSettingsH
#define ZXEditorSettingsH
//---------------------------------------------------------------------------
#include <vector>
#include "KRegistry.h"
#include "ZXFileManager.h"
#include "ZXColorSettings.h"
#include "SciScintillaMemo.hpp"
//---------------------------------------------------------------------------
using namespace Scorpio;
//---------------------------------------------------------------------------
class ZXEditorSettings
{
private:
    KRegistry*          m_regScorpio;

    void    __fastcall  Read(void);

    // GENERAL properties
    bool                m_TabsToSpaces;
    int                 m_TabWidth;
    bool                m_AutoCloseBraces;
    bool                m_AutoCloseQuotes;

    void    __fastcall  WriteGeneral(void);
    void    __fastcall  ReadGeneral(void);
    void    __fastcall  ApplyGeneral(TScintillaMemo* Editor);

    // DISPLAY properties
    bool                m_LineNumbers;
    String              m_Font;
    int                 m_FontSize;
    int                 m_Whitespace;
    bool                m_ShowGuides;
    int                 m_GuideWidth;

    void    __fastcall  WriteDisplay(void);
    void    __fastcall  ReadDisplay(void);

public:
            __fastcall  ZXEditorSettings();
            __fastcall ~ZXEditorSettings();

    void    __fastcall  Write(void);
    void    __fastcall  Apply(TScintillaMemo* Editor);
    void    __fastcall  Apply(TSciDoc* Document);
    void    __fastcall  Reset(void);

    // tabs
    __property  bool    TabsToSpaces        = { read = m_TabsToSpaces       , write = m_TabsToSpaces        };
    __property  int     TabWidth            = { read = m_TabWidth           , write = m_TabWidth            };
    // alignment guides
    __property  bool    ShowGuides          = { read = m_ShowGuides         , write = m_ShowGuides          };
    __property  int     GuideWidth          = { read = m_GuideWidth         , write = m_GuideWidth          };
    // display
    __property  bool    AutoCloseBraces     = { read = m_AutoCloseBraces    , write = m_AutoCloseBraces     };
    __property  bool    AutoCloseQuotes     = { read = m_AutoCloseQuotes    , write = m_AutoCloseQuotes     };
    __property  bool    LineNumbers         = { read = m_LineNumbers        , write = m_LineNumbers         };
    __property  String  Font                = { read = m_Font               , write = m_Font                };
    __property  int     FontSize            = { read = m_FontSize           , write = m_FontSize            };
    __property  int     Whitespace          = { read = m_Whitespace         , write = m_Whitespace          };
};
//---------------------------------------------------------------------------
extern ZXEditorSettings g_EditorSettings;
//---------------------------------------------------------------------------
#endif

