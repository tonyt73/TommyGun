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
//---------------------------------------------------------------------------
__fastcall ZXColorSetting::ZXColorSetting(String sName)
: m_sName(sName)
{
    m_Strings = new TStringList;
}
//---------------------------------------------------------------------------
__fastcall ZXColorSetting::~ZXColorSetting()
{
    SAFE_DELETE(m_Strings);
}
//---------------------------------------------------------------------------
void __fastcall ZXColorSetting::ClearSettings()
{
    m_Settings.clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXColorSetting::Add(String sName, TColor ForeColor, TColor BackColor, TFontStyles FontStyles)
{
    TColorSetting Setting;

    Setting.Name      = sName;
    Setting.ForeColor = ForeColor;
    Setting.BackColor = BackColor;
    Setting.FontStyle = FontStyles;

    m_Settings.push_back(Setting);
}
//---------------------------------------------------------------------------
void __fastcall ZXColorSetting::AddLine(String sLine)
{
    m_Strings->Add(sLine);
}
//---------------------------------------------------------------------------
int __fastcall ZXColorSetting::Count()
{
    return m_Settings.size();
}
//---------------------------------------------------------------------------
void __fastcall ZXColorSetting::Reset()
{
    ClearSettings();
    DoReset();
    for (int i = 0; i < (int)m_Settings.size(); ++i)
    {
        ApplySetting(i, m_Settings[i]);
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXColorSetting::GetSetting(int i, TColorSetting& Setting)
{
    if (0 <= i && i < (int)m_Settings.size())
    {
        Setting = m_Settings[i];
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall ZXColorSetting::SetSetting(int i, TColorSetting Setting)
{
    if (0 <= i && i < (int)m_Settings.size())
    {
        m_Settings[i] = Setting;
        ApplySetting(i, Setting);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXColorSetting::Read(KRegistry* regScorpio)
{
    int iSize = m_Settings.size();;
    for (int i = 0; i < iSize; ++i)
    {
        TColor color;
        if (regScorpio->Read("CodeEditor\\Colours\\" + Name, "Setting_ForeColor_" + IntToStr(i) , color)) m_Settings[i].ForeColor = color;
        if (regScorpio->Read("CodeEditor\\Colours\\" + Name, "Setting_BackColor_" + IntToStr(i) , color)) m_Settings[i].BackColor = color;
        int iFontStyle = 0;
        if (regScorpio->Read("CodeEditor\\Colours\\" + Name, "Setting_FontStyle_" + IntToStr(i) , iFontStyle))
        {
            m_Settings[i].FontStyle = iFontStyle & 0x01 ? m_Settings[i].FontStyle << fsBold      : m_Settings[i].FontStyle >> fsBold;
            m_Settings[i].FontStyle = iFontStyle & 0x02 ? m_Settings[i].FontStyle << fsItalic    : m_Settings[i].FontStyle >> fsItalic;
            m_Settings[i].FontStyle = iFontStyle & 0x04 ? m_Settings[i].FontStyle << fsUnderline : m_Settings[i].FontStyle >> fsUnderline;
        }
        ApplySetting(i, m_Settings[i]);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXColorSetting::Write(KRegistry* regScorpio)
{
    int iSize = m_Settings.size();
    regScorpio->Write("CodeEditor\\Colours\\" + Name, "Settings", iSize);
    for (int i = 0; i < iSize; ++i)
    {
        regScorpio->Write("CodeEditor\\Colours\\" + Name, "Setting_ForeColor_" + IntToStr(i) , m_Settings[i].ForeColor);
        regScorpio->Write("CodeEditor\\Colours\\" + Name, "Setting_BackColor_" + IntToStr(i) , m_Settings[i].BackColor);
        int iFontStyle = 0;
        iFontStyle |= m_Settings[i].FontStyle.Contains(fsBold     ) ? 0x01 : 0x00;
        iFontStyle |= m_Settings[i].FontStyle.Contains(fsItalic   ) ? 0x02 : 0x00;
        iFontStyle |= m_Settings[i].FontStyle.Contains(fsUnderline) ? 0x04 : 0x00;
        regScorpio->Write("CodeEditor\\Colours\\" + Name, "Setting_FontStyle_" + IntToStr(i) , iFontStyle);
    }
}
//---------------------------------------------------------------------------
__fastcall ZXColorAsm::ZXColorAsm(/*TSynCustomHighlighter*& synEdit*/)
: ZXColorSetting("Assembler")
{
    AddLine("; Syntax highlighting");
    AddLine("SCREEN:     equ     16384               ; spectrum display memory address");
    AddLine("ATTR:       equ     22528               ; spectrum attribute memory address");
    AddLine("SCRLEN:     equ     6144                ; size of the screen pixels in bytes");
    AddLine("ATTRLEN:    equ     768                 ; size of the ATTR in bytes");
    AddLine("");
    AddLine("include \"screen.inc\"");
    AddLine("");
    AddLine("            org 24768");
    AddLine("            jp Start");
    AddLine("            defb 0");
    AddLine("MemScr:     defs 5632                   ; off screen memory aligned to 4 byte boundary");
    AddLine("MemAttr:    defs 705");
    AddLine("");
    AddLine("Start:      call ClrScr");
    AddLine("            call DrwPanel");
    AddLine("            call DrwMapPos");
    AddLine("            call DrawMap");
    AddLine("            call SM_Draw");
    AddLine("            ret");
    AddLine("");
    AddLine("Pause:      push bc                     ; save bc");
    AddLine("            push de                     ; save de");
    AddLine("            push hl                     ; hl");
    AddLine("            ld bc, 5000                 ; define the pause length");
    AddLine("            ld de, 0                    ; define block transfer destination");
    AddLine("            ld hl, 0                    ; define block transfer source");
    AddLine("            ldir                        ; do a block transfer (takes a little while)");
    AddLine("            pop hl                      ; restore hl");
    AddLine("            pop de                      ; restore de");
    AddLine("            pop bc                      ; restore bc");
    AddLine("            ret                         ; pause complete");

    /*
    m_HL = new TSynGeneralSyn(NULL);
    TSynGeneralSyn* HL1 = dynamic_cast<TSynGeneralSyn*>(m_SynEdit);
    TSynGeneralSyn* HL2 = dynamic_cast<TSynGeneralSyn*>(m_HL);
    HL2->Comments = HL2->Comments << csAsmStyle;
    HL2->KeyWords->Assign(HL1->KeyWords);
    HL2->IdentifierChars = HL1->IdentifierChars;
    HL2->StringDelim = sdDoubleQuote;
    HL2->CommentAttri->Background = HL1->CommentAttri->Background;
    HL2->CommentAttri->Foreground = HL1->CommentAttri->Foreground;
    HL2->CommentAttri->Style = HL1->CommentAttri->Style;
    HL2->IdentifierAttri->Assign(HL1->IdentifierAttri);
    HL2->KeyAttri->Assign(HL1->KeyAttri);
    HL2->KeyWords->Assign(HL1->KeyWords);
    HL2->NumberAttri->Assign(HL1->NumberAttri);
    HL2->PreprocessorAttri->Assign(HL1->PreprocessorAttri);
    HL2->SpaceAttri->Assign(HL1->SpaceAttri);
    HL2->StringAttri->Assign(HL1->StringAttri);
    HL2->SymbolAttri->Assign(HL1->SymbolAttri);
    */

    Reset();
}
//---------------------------------------------------------------------------
__fastcall ZXColorAsm::~ZXColorAsm()
{
}

//---------------------------------------------------------------------------
void __fastcall ZXColorAsm::DoReset()
{
    Add("Comment", clLime, clBlack, TFontStyles() << fsItalic);
    Add("Identifier", clWhite, clBlack);
    Add("Mnemonic", clAqua, clBlack, TFontStyles() << fsBold);
    Add("Number", clRed, clBlack);
    Add("String", clBlue, clWhite);
    Add("Symbol", clYellow, clBlack);
    Add("Whitespace", clAqua, clBlack);
}
//---------------------------------------------------------------------------
void __fastcall ZXColorAsm::ApplySetting(int i, TColorSetting Setting)
{
    /*
    TSynGeneralSyn* HL = dynamic_cast<TSynGeneralSyn*>(m_HL);
    if (SAFE_PTR(HL))
    {
        switch(i)
        {
            case 0: // comment
                HL->CommentAttri->Background    = Setting.BackColor;
                HL->CommentAttri->Foreground    = Setting.ForeColor;
                HL->CommentAttri->Style         = Setting.FontStyle;
                break;
            case 1: // identifier
                HL->IdentifierAttri->Background = Setting.BackColor;
                HL->IdentifierAttri->Foreground = Setting.ForeColor;
                HL->IdentifierAttri->Style      = Setting.FontStyle;
                break;
            case 2: // mnemonic
                HL->KeyAttri->Background        = Setting.BackColor;
                HL->KeyAttri->Foreground        = Setting.ForeColor;
                HL->KeyAttri->Style             = Setting.FontStyle;
                break;
            case 3: // number
                HL->NumberAttri->Background     = Setting.BackColor;
                HL->NumberAttri->Foreground     = Setting.ForeColor;
                HL->NumberAttri->Style          = Setting.FontStyle;
                break;
            case 4: // string
                HL->StringAttri->Background     = Setting.BackColor;
                HL->StringAttri->Foreground     = Setting.ForeColor;
                HL->StringAttri->Style          = Setting.FontStyle;
                break;
            case 5: // symbol
                HL->SymbolAttri->Background     = Setting.BackColor;
                HL->SymbolAttri->Foreground     = Setting.ForeColor;
                HL->SymbolAttri->Style          = Setting.FontStyle;
                break;
            case 6: // whitespace
            default:
                HL->SpaceAttri->Background      = Setting.BackColor;
                HL->SpaceAttri->Foreground      = Setting.ForeColor;
                HL->SpaceAttri->Style           = Setting.FontStyle;
                break;
        }
    }
    */
}
//---------------------------------------------------------------------------
void __fastcall ZXColorAsm::Update()
{
    /*
    if (SAFE_PTR(m_SynEdit) && SAFE_PTR(m_HL))
    {
        TSynGeneralSyn* HL2 = dynamic_cast<TSynGeneralSyn*>(m_SynEdit);
        TSynGeneralSyn* HL1 = dynamic_cast<TSynGeneralSyn*>(m_HL);
        HL2->Comments = HL2->Comments << csAsmStyle;
        HL2->KeyWords->Assign(HL1->KeyWords);
        HL2->IdentifierChars = HL1->IdentifierChars;
        HL2->StringDelim = sdDoubleQuote;
        HL2->CommentAttri->Background = HL1->CommentAttri->Background;
        HL2->CommentAttri->Foreground = HL1->CommentAttri->Foreground;
        HL2->CommentAttri->Style = HL1->CommentAttri->Style;
        HL2->IdentifierAttri->Assign(HL1->IdentifierAttri);
        HL2->KeyAttri->Assign(HL1->KeyAttri);
        HL2->KeyWords->Assign(HL1->KeyWords);
        HL2->NumberAttri->Assign(HL1->NumberAttri);
        HL2->PreprocessorAttri->Assign(HL1->PreprocessorAttri);
        HL2->SpaceAttri->Assign(HL1->SpaceAttri);
        HL2->StringAttri->Assign(HL1->StringAttri);
        HL2->SymbolAttri->Assign(HL1->SymbolAttri);
    }
    */
}
//---------------------------------------------------------------------------
__fastcall ZXColorZXBASIC::ZXColorZXBASIC(/*TSynCustomHighlighter*& synEdit*/)
: ZXColorSetting("ZX BASIC")
{
    AddLine("REM Syntax Highlighting");
    AddLine("10 GOSUB 1000");
    AddLine("20 GOTO 2000");
    AddLine("30 STOP");
    AddLine("1000 FOR I = 0 TO 100");
    AddLine("1010 PLOT I, I");
    AddLine("1020 DRAW 100 - I, I");
    AddLine("1030 NEXT I");
    AddLine("1040 RETURN");
    AddLine("2000 FOR n = 0 TO 1000: BEEP .5,n: NEXT n");
    AddLine("2010 GOTO 30");
    AddLine("3000 LET a$ = \"HELLO\"");
    AddLine("3010 LET b = 100.0");
    AddLine("3010 LET c = 100");
    AddLine("3010 LET b = BIN 01001100");

    /*
    m_HL = new __declspec(uuid("{533E9B20-6C80-4936-A4CD-4F03AA3D9B29}"))TSynGeneralSyn(NULL);
    TSynGeneralSyn* HL1 = dynamic_cast<TSynGeneralSyn*>(m_SynEdit);
    TSynGeneralSyn* HL2 = dynamic_cast<TSynGeneralSyn*>(m_HL);
    HL2->Comments = HL2->Comments << csBasStyle;
    HL2->KeyWords->Assign(HL1->KeyWords);
    HL2->IdentifierChars = HL1->IdentifierChars;
    HL2->StringDelim = sdDoubleQuote;
    HL2->CommentAttri->Background = HL1->CommentAttri->Background;
    HL2->CommentAttri->Foreground = HL1->CommentAttri->Foreground;
    HL2->CommentAttri->Style = HL1->CommentAttri->Style;
    HL2->IdentifierAttri->Assign(HL1->IdentifierAttri);
    HL2->KeyAttri->Assign(HL1->KeyAttri);
    HL2->KeyWords->Assign(HL1->KeyWords);
    HL2->NumberAttri->Assign(HL1->NumberAttri);
    HL2->PreprocessorAttri->Assign(HL1->PreprocessorAttri);
    HL2->SpaceAttri->Assign(HL1->SpaceAttri);
    HL2->StringAttri->Assign(HL1->StringAttri);
    HL2->SymbolAttri->Assign(HL1->SymbolAttri);
    */

    Reset();
}
//---------------------------------------------------------------------------
__fastcall ZXColorZXBASIC::~ZXColorZXBASIC()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXColorZXBASIC::DoReset()
{
    Add("Comment", clLime, clBlack, TFontStyles() << fsItalic);
    Add("Identifier", clWhite, clBlack);
    Add("Keyword", clAqua, clBlack, TFontStyles() << fsBold);
    Add("Number", clRed, clBlack);
    Add("String", clBlue, clWhite);
    Add("Symbol", clYellow, clBlack);
    Add("Whitespace", clWhite, clBlack);
}
//---------------------------------------------------------------------------
void __fastcall ZXColorZXBASIC::ApplySetting(int i, TColorSetting Setting)
{
    /*
    TSynGeneralSyn* HL = dynamic_cast<TSynGeneralSyn*>(m_HL);
    if (SAFE_PTR(HL))
    {
        switch(i)
        {
            case 0: // comment
                HL->CommentAttri->Background    = Setting.BackColor;
                HL->CommentAttri->Foreground    = Setting.ForeColor;
                HL->CommentAttri->Style         = Setting.FontStyle;
                break;
            case 1: // identifier
                HL->IdentifierAttri->Background = Setting.BackColor;
                HL->IdentifierAttri->Foreground = Setting.ForeColor;
                HL->IdentifierAttri->Style      = Setting.FontStyle;
                break;
            case 2: // keyword
                HL->KeyAttri->Background        = Setting.BackColor;
                HL->KeyAttri->Foreground        = Setting.ForeColor;
                HL->KeyAttri->Style             = Setting.FontStyle;
                break;
            case 3: // number
                HL->NumberAttri->Background     = Setting.BackColor;
                HL->NumberAttri->Foreground     = Setting.ForeColor;
                HL->NumberAttri->Style          = Setting.FontStyle;
                break;
            case 4: // string
                HL->StringAttri->Background     = Setting.BackColor;
                HL->StringAttri->Foreground     = Setting.ForeColor;
                HL->StringAttri->Style          = Setting.FontStyle;
                break;
            case 5: // symbol
                HL->SymbolAttri->Background     = Setting.BackColor;
                HL->SymbolAttri->Foreground     = Setting.ForeColor;
                HL->SymbolAttri->Style          = Setting.FontStyle;
                break;
            case 6: // whitespace
            default:
                HL->SpaceAttri->Background      = Setting.BackColor;
                HL->SpaceAttri->Foreground      = Setting.ForeColor;
                HL->SpaceAttri->Style           = Setting.FontStyle;
                break;
        }
    }
    */
}
//---------------------------------------------------------------------------
void __fastcall ZXColorZXBASIC::Update()
{
    /*
    if (SAFE_PTR(m_SynEdit) && SAFE_PTR(m_HL))
    {
        TSynGeneralSyn* HL2 = dynamic_cast<TSynGeneralSyn*>(m_SynEdit);
        TSynGeneralSyn* HL1 = dynamic_cast<TSynGeneralSyn*>(m_HL);
        HL2->Comments = HL2->Comments << csAsmStyle;
        HL2->KeyWords->Assign(HL1->KeyWords);
        HL2->IdentifierChars = HL1->IdentifierChars;
        HL2->StringDelim = sdDoubleQuote;
        HL2->CommentAttri->Background = HL1->CommentAttri->Background;
        HL2->CommentAttri->Foreground = HL1->CommentAttri->Foreground;
        HL2->CommentAttri->Style = HL1->CommentAttri->Style;
        HL2->IdentifierAttri->Assign(HL1->IdentifierAttri);
        HL2->KeyAttri->Assign(HL1->KeyAttri);
        HL2->KeyWords->Assign(HL1->KeyWords);
        HL2->NumberAttri->Assign(HL1->NumberAttri);
        HL2->PreprocessorAttri->Assign(HL1->PreprocessorAttri);
        HL2->SpaceAttri->Assign(HL1->SpaceAttri);
        HL2->StringAttri->Assign(HL1->StringAttri);
        HL2->SymbolAttri->Assign(HL1->SymbolAttri);
    }
    */
}
//---------------------------------------------------------------------------
__fastcall ZXColorC::ZXColorC(/*TSynCustomHighlighter*& synEdit*/)
: ZXColorSetting("C/C++")
{
    AddLine("// Syntax Highlighting");
    AddLine("void __fastcall MyClass::MyClass()");
    AddLine("{");
    AddLine("    int         i    = 123456;");
    AddLine("    std::string	text = \"hello\";");
    AddLine("    double      big  = 123.45;");
    AddLine("    char        chr  = 'a';");
    AddLine("    char        hex  = 0x73;");
    AddLine("");
    AddLine("#ifdef DO_FOO");
    AddLine("    asm");
    AddLine("    {");
    AddLine("        ASM MOV AX, 32000");
    AddLine("        ASM MOV BX, 16384");
    AddLine("    }");
    AddLine("#endif /* DO_FOO */");
    AddLine("");
    AddLine("    for (int i = 0; i < 10; ++i)");
    AddLine("    {");
    AddLine("    	printf(\"number: %d\\n\", i);");
    AddLine("    }");
    AddLine("}");

    /*
    m_HL = new TSynCppSyn(NULL);
    TSynCppSyn* HL1 = dynamic_cast<TSynCppSyn*>(m_SynEdit);
    TSynCppSyn* HL2 = dynamic_cast<TSynCppSyn*>(m_HL);
    HL2->CommentAttri->Assign(HL1->CommentAttri);
    HL2->AsmAttri->Assign(HL1->AsmAttri);
    HL2->IdentifierAttri->Assign(HL1->IdentifierAttri);
    HL2->InvalidAttri->Assign(HL1->InvalidAttri);
    HL2->KeyAttri->Assign(HL1->KeyAttri);
    HL2->HexAttri->Assign(HL1->HexAttri);
    HL2->FloatAttri->Assign(HL1->FloatAttri);
    HL2->OctalAttri->Assign(HL1->OctalAttri);
    HL2->NumberAttri->Assign(HL1->NumberAttri);
    HL2->DirecAttri->Assign(HL1->DirecAttri);
    HL2->SpaceAttri->Assign(HL1->SpaceAttri);
    HL2->StringAttri->Assign(HL1->StringAttri);
    HL2->SymbolAttri->Assign(HL1->SymbolAttri);
    */
    Reset();
}
//---------------------------------------------------------------------------
__fastcall ZXColorC::~ZXColorC()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXColorC::DoReset()
{
    Add("Assembler", clSilver, clBlack);
    Add("Character", clBlue, clWhite);
    Add("Comment", clLime, clBlack, TFontStyles() << fsItalic);
    Add("Preprocessor", clGreen, clBlack);
    Add("Float", clFuchsia, clWhite);
    Add("Hex", clBlack, clLime);
    Add("Identifier", clWhite, clBlack);
    Add("Invalid", clSilver, clBlack);
    Add("Keyword", clAqua, clBlack, TFontStyles() << fsBold);
    Add("Number", clRed, clBlack);
    Add("Octal", clFuchsia, clBlack);
    Add("Whitespace", clWhite, clBlack);
    Add("String", clBlue, clWhite);
    Add("Symbol", clYellow, clBlack);
}
//---------------------------------------------------------------------------
void __fastcall ZXColorC::ApplySetting(int i, TColorSetting Setting)
{
    /*
    TSynCppSyn* HL = dynamic_cast<TSynCppSyn*>(m_HL);
    if (SAFE_PTR(HL))
    {
        switch(i)
        {
            case 0: // assembler
                HL->AsmAttri->Background        = Setting.BackColor;
                HL->AsmAttri->Foreground        = Setting.ForeColor;
                HL->AsmAttri->Style             = Setting.FontStyle;
                break;
            case 1: // char
                HL->CharAttri->Background       = Setting.BackColor;
                HL->CharAttri->Foreground       = Setting.ForeColor;
                HL->CharAttri->Style            = Setting.FontStyle;
                break;
            case 2: // comment
                HL->CommentAttri->Background    = Setting.BackColor;
                HL->CommentAttri->Foreground    = Setting.ForeColor;
                HL->CommentAttri->Style         = Setting.FontStyle;
                break;
            case 3: // preprocessor
                HL->DirecAttri->Background      = Setting.BackColor;
                HL->DirecAttri->Foreground      = Setting.ForeColor;
                HL->DirecAttri->Style           = Setting.FontStyle;
                break;
            case 4: // float
                HL->FloatAttri->Background      = Setting.BackColor;
                HL->FloatAttri->Foreground      = Setting.ForeColor;
                HL->FloatAttri->Style           = Setting.FontStyle;
                break;
            case 5: // hex
                HL->HexAttri->Background        = Setting.BackColor;
                HL->HexAttri->Foreground        = Setting.ForeColor;
                HL->HexAttri->Style             = Setting.FontStyle;
                break;
            case 6: // identifier
                HL->IdentifierAttri->Background = Setting.BackColor;
                HL->IdentifierAttri->Foreground = Setting.ForeColor;
                HL->IdentifierAttri->Style      = Setting.FontStyle;
                break;
            case 7: // invalid
                HL->InvalidAttri->Background    = Setting.BackColor;
                HL->InvalidAttri->Foreground    = Setting.ForeColor;
                HL->InvalidAttri->Style         = Setting.FontStyle;
                break;
            case 8: // keyword
                HL->KeyAttri->Background        = Setting.BackColor;
                HL->KeyAttri->Foreground        = Setting.ForeColor;
                HL->KeyAttri->Style             = Setting.FontStyle;
                break;
            case 9: // number
                HL->NumberAttri->Background     = Setting.BackColor;
                HL->NumberAttri->Foreground     = Setting.ForeColor;
                HL->NumberAttri->Style          = Setting.FontStyle;
                break;
            case 10: // octal
                HL->OctalAttri->Background      = Setting.BackColor;
                HL->OctalAttri->Foreground      = Setting.ForeColor;
                HL->OctalAttri->Style           = Setting.FontStyle;
                break;
            case 12: // string
                HL->StringAttri->Background     = Setting.BackColor;
                HL->StringAttri->Foreground     = Setting.ForeColor;
                HL->StringAttri->Style          = Setting.FontStyle;
                break;
            case 13: // symbol
                HL->SymbolAttri->Background     = Setting.BackColor;
                HL->SymbolAttri->Foreground     = Setting.ForeColor;
                HL->SymbolAttri->Style          = Setting.FontStyle;
                break;
            case 11: // whitespace
            default:
                HL->SpaceAttri->Background      = Setting.BackColor;
                HL->SpaceAttri->Foreground      = Setting.ForeColor;
                HL->SpaceAttri->Style           = Setting.FontStyle;
                break;
        }
    }
    */
}
//---------------------------------------------------------------------------
void __fastcall ZXColorC::Update()
{
    /*
    if (SAFE_PTR(m_SynEdit) && SAFE_PTR(m_HL))
    {
        TSynCppSyn* HL2 = dynamic_cast<TSynCppSyn*>(m_SynEdit);
        TSynCppSyn* HL1 = dynamic_cast<TSynCppSyn*>(m_HL);
        HL2->CommentAttri->Assign(HL1->CommentAttri);
        HL2->AsmAttri->Assign(HL1->AsmAttri);
        HL2->IdentifierAttri->Assign(HL1->IdentifierAttri);
        HL2->InvalidAttri->Assign(HL1->InvalidAttri);
        HL2->KeyAttri->Assign(HL1->KeyAttri);
        HL2->HexAttri->Assign(HL1->HexAttri);
        HL2->FloatAttri->Assign(HL1->FloatAttri);
        HL2->OctalAttri->Assign(HL1->OctalAttri);
        HL2->NumberAttri->Assign(HL1->NumberAttri);
        HL2->DirecAttri->Assign(HL1->DirecAttri);
        HL2->SpaceAttri->Assign(HL1->SpaceAttri);
        HL2->StringAttri->Assign(HL1->StringAttri);
        HL2->SymbolAttri->Assign(HL1->SymbolAttri);
    }
    */
}
//---------------------------------------------------------------------------
__fastcall ZXColorText::ZXColorText()
: ZXColorSetting("Text")
{
    AddLine("Welcome to TommyGun");
    AddLine("");
    AddLine("Thanks for trying TommyGun and thanks for reading this file.");
    AddLine("");
    AddLine("TommyGun is a retro development environment for ");
    AddLine("creating software to run on old 8 and 16 bit machines.");
    AddLine("");
    AddLine("Quick Start Guide");
    AddLine("=================");
    AddLine("Want to see what TommyGun can do but without having to write ");
    AddLine("any code or draw any artwork?");
    AddLine("Then please read the Getting Started Guide.doc for how to ");
    AddLine("run the SabreWulf project.");

    //m_HL = new TSynGeneralSyn(NULL);
    //m_HL->Assign(synEdit);
    Reset();
}
//---------------------------------------------------------------------------
__fastcall ZXColorText::~ZXColorText()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXColorText::DoReset()
{
    Add("Whitespace", clBlack, clWhite);
}
//---------------------------------------------------------------------------
void __fastcall ZXColorText::ApplySetting(int i, TColorSetting Setting)
{
    /*
    TSynGeneralSyn* HL = dynamic_cast<TSynGeneralSyn*>(m_HL);
    if (SAFE_PTR(HL))
    {
        HL->CommentAttri->Background    = Setting.BackColor;
        HL->CommentAttri->Foreground    = Setting.ForeColor;
        HL->CommentAttri->Style         = Setting.FontStyle;
        HL->IdentifierAttri->Background = Setting.BackColor;
        HL->IdentifierAttri->Foreground = Setting.ForeColor;
        HL->IdentifierAttri->Style      = Setting.FontStyle;
        HL->KeyAttri->Background        = Setting.BackColor;
        HL->KeyAttri->Foreground        = Setting.ForeColor;
        HL->KeyAttri->Style             = Setting.FontStyle;
        HL->NumberAttri->Background     = Setting.BackColor;
        HL->NumberAttri->Foreground     = Setting.ForeColor;
        HL->NumberAttri->Style          = Setting.FontStyle;
        HL->StringAttri->Background     = Setting.BackColor;
        HL->StringAttri->Foreground     = Setting.ForeColor;
        HL->StringAttri->Style          = Setting.FontStyle;
        HL->SymbolAttri->Background     = Setting.BackColor;
        HL->SymbolAttri->Foreground     = Setting.ForeColor;
        HL->SymbolAttri->Style          = Setting.FontStyle;
        HL->SpaceAttri->Background      = Setting.BackColor;
        HL->SpaceAttri->Foreground      = Setting.ForeColor;
        HL->SpaceAttri->Style           = Setting.FontStyle;
    }
    */
}
//---------------------------------------------------------------------------
void __fastcall ZXColorText::Update()
{
    /*
    if (SAFE_PTR(m_SynEdit) && SAFE_PTR(m_HL))
    {
        TSynGeneralSyn* HL1 = dynamic_cast<TSynGeneralSyn*>(m_SynEdit);
        TSynGeneralSyn* HL2 = dynamic_cast<TSynGeneralSyn*>(m_HL);
        HL1->Assign(HL2);
    }
    */
}
//---------------------------------------------------------------------------

