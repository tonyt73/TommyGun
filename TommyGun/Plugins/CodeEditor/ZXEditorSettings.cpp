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
using namespace Scorpio;
//---------------------------------------------------------------------------
ZXEditorSettings g_EditorSettings;
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXEditorSettings::ZXEditorSettings()
: m_regScorpio(NULL)
, m_TabsToSpaces(true)
, m_TabWidth(4)
, m_LineNumbers(true)
, m_ShowGuides(false)
, m_GuideWidth(4)
, m_Font("Courier New")
, m_FontSize(10)
, m_Whitespace(0)
{
    m_regScorpio = new KRegistry(NULL);
    if (SAFE_PTR(m_regScorpio))
    {
        m_regScorpio->Section = "TommyGun";
        m_regScorpio->SoftwareKey = "\\Software\\Scorpio\\";
        m_regScorpio->RootKey = rkHKEY_CURRENT_USER;
    }
    Read();
}
//---------------------------------------------------------------------------
__fastcall ZXEditorSettings::~ZXEditorSettings()
{
    SAFE_DELETE(m_regScorpio);
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::Read(void)
{
    ReadGeneral();
    ReadDisplay();
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::Write(void)
{
    WriteGeneral();
    WriteDisplay();
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::Write(TSciLanguageManager* LanguageManager)
{
	// copy the styles from the lang mgr
    if (SAFE_PTR(m_regScorpio))
	{
		for (int l = 0; l < LanguageManager->LanguageList->Count; l++)
		{
			for (int s = 0; s < LanguageManager->LanguageList->Items[l]->Styles->Count; s++)
			{
				String style = IntToStr(LanguageManager->LanguageList->Items[l]->Styles->Items[s]->StyleNumber);
				TColor fore = LanguageManager->LanguageList->Items[l]->Styles->Items[s]->ForeColor;
				TColor back = LanguageManager->LanguageList->Items[l]->Styles->Items[s]->BackColor;
				String key = "CodeEditor\\SciStyles\\" + LanguageManager->LanguageList->Items[l]->Name;
				m_regScorpio->Write(key, style + ".fore", fore);
				m_regScorpio->Write(key, style + ".back", back);
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::Apply(TScintillaMemo* Editor)
{
    Editor->AutoCloseBraces = m_AutoCloseBraces;
    Editor->AutoCloseQuotes = m_AutoCloseQuotes;
    Editor->Gutter0->Width  = m_LineNumbers ? 50 : 0;
    Editor->Font->Name      = m_Font;
    Editor->Font->Size      = m_FontSize;
    Editor->Font->Charset   = ANSI_CHARSET;
    Editor->Font->Pitch     = fpFixed;
    Editor->OtherOptions->ViewWSpace = (sciWSMode)m_Whitespace;
	((TScintilla*)Editor)->SelectedLanguage = ((TScintilla*)Editor)->SelectedLanguage;
	// apply available styles
	if (SAFE_PTR(m_regScorpio))
	{
		TSciLanguageManager* LanguageManager = ((TScintilla*)Editor)->LanguageManager;
		for (int l = 0; l < LanguageManager->LanguageList->Count; l++)
		{
			for (int s = 0; s < LanguageManager->LanguageList->Items[l]->Styles->Count; s++)
			{
				int styleNo = LanguageManager->LanguageList->Items[l]->Styles->Items[s]->StyleNumber;
				AnsiString style = IntToStr(styleNo);
				TColor fore = LanguageManager->LanguageList->Items[l]->Styles->Items[s]->ForeColor;
				TColor back = LanguageManager->LanguageList->Items[l]->Styles->Items[s]->BackColor;
				AnsiString key = "CodeEditor\\SciStyles\\" + LanguageManager->LanguageList->Items[l]->Name;
				TColor color;
				if (m_regScorpio->ValueExists(key, style + ".fore"))
				{
					if (m_regScorpio->Read(key, style + ".fore", color))
					{
						LanguageManager->LanguageList->Items[l]->Styles->GetStyle(styleNo)->ForeColor = color;
					}
				}
				if (m_regScorpio->ValueExists(key, style + ".back"))
				{
					if (m_regScorpio->Read(key, style + ".back", color))
					{
						LanguageManager->LanguageList->Items[l]->Styles->GetStyle(styleNo)->BackColor = color;
					}
				}
			}
		}
		((TScintilla*)Editor)->Color = FindBackColor(LanguageManager, ((TScintilla*)Editor)->SelectedLanguage);
		ApplyStylesTo(LanguageManager, Editor, ((TScintilla*)Editor)->SelectedLanguage);
	}
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::Apply(TSciDoc* Document)
{
    TIndentationOptions indents = TIndentationOptions() << KeepIndent << TabIndents << BackSpaceUnIndents;
    if (m_ShowGuides)
        indents << IndentationGuides;
    Document->Indentation = indents;
    Document->IndentWidth = m_GuideWidth;
    Document->TabWidth = m_TabWidth;
    Document->UseTabs = !m_TabsToSpaces;
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::WriteGeneral(void)
{
    if (SAFE_PTR(m_regScorpio))
    {
        m_regScorpio->Write("CodeEditor\\General", "TabsToSpaces"       , m_TabsToSpaces        );
        m_regScorpio->Write("CodeEditor\\General", "TabWidth"           , m_TabWidth            );
        m_regScorpio->Write("CodeEditor\\General", "AutoCloseBraces"    , m_AutoCloseBraces     );
        m_regScorpio->Write("CodeEditor\\General", "AutoCloseQuotes"    , m_AutoCloseQuotes     );
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::ReadGeneral(void)
{
    if (SAFE_PTR(m_regScorpio))
    {
        m_regScorpio->Read("CodeEditor\\General", "TabsToSpaces"        , m_TabsToSpaces        );
        m_regScorpio->Read("CodeEditor\\General", "TabWidth"            , m_TabWidth            );
        m_regScorpio->Read("CodeEditor\\General", "AutoCloseBraces"     , m_AutoCloseBraces     );
        m_regScorpio->Read("CodeEditor\\General", "AutoCloseQuotes"     , m_AutoCloseQuotes     );
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::WriteDisplay(void)
{
    if (SAFE_PTR(m_regScorpio))
    {
        m_regScorpio->Write("CodeEditor\\Display", "GuideWidth"         , m_GuideWidth          );
        m_regScorpio->Write("CodeEditor\\Display", "ShowGuides"         , m_ShowGuides          );
        m_regScorpio->Write("CodeEditor\\Display", "LineNumbers"        , m_LineNumbers         );
        m_regScorpio->Write("CodeEditor\\Display", "Font"               , m_Font                );
        m_regScorpio->Write("CodeEditor\\Display", "FontSize"           , m_FontSize            );
        m_regScorpio->Write("CodeEditor\\Display", "Whitespace"         , m_Whitespace          );
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::ReadDisplay(void)
{
    if (SAFE_PTR(m_regScorpio))
    {
        m_regScorpio->Read("CodeEditor\\Display", "GuideWidth"          , m_GuideWidth          );
        m_regScorpio->Read("CodeEditor\\Display", "ShowGuides"          , m_ShowGuides          );
        m_regScorpio->Read("CodeEditor\\Display", "LineNumbers"         , m_LineNumbers         );
        m_regScorpio->Read("CodeEditor\\Display", "Font"                , m_Font                );
        m_regScorpio->Read("CodeEditor\\Display", "FontSize"            , m_FontSize            );
        m_regScorpio->Read("CodeEditor\\Display", "Whitespace"          , m_Whitespace          );
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXEditorSettings::Reset(void)
{
	m_TabsToSpaces          = true;
	m_TabWidth              = 4;
	m_GuideWidth            = 4;
	m_ShowGuides            = false;
	m_LineNumbers           = true;
	m_Font                  = "Courier New";
	m_FontSize              = 10;
	m_AutoCloseBraces       = true;
	m_AutoCloseQuotes       = true;
	m_Whitespace            = 0;
}
//---------------------------------------------------------------------------
TColor __fastcall ZXEditorSettings::FindBackColor(TSciLanguageManager* langMgr, const String& Language)
{
	TSciLangItem* lang = langMgr->LanguageList->Find(Language);
	TColor back = clBlack;
	if (lang)
	{
		int max = 0;
		std::map<TColor, int> colorCounts;
		for (int i = 0; i < lang->Styles->Count; i++)
		{
			colorCounts[lang->Styles->Items[i]->BackColor]++;
			if (colorCounts[lang->Styles->Items[i]->BackColor] > max)
			{
				max = colorCounts[lang->Styles->Items[i]->BackColor];
				back = lang->Styles->Items[i]->BackColor;
			}
		}
	}
	return back;
}
//---------------------------------------------------------------------------

