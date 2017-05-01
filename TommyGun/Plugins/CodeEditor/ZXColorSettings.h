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
#ifndef ZXColorSettingsH
#define ZXColorSettingsH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
typedef struct
{
    String      Name;
    TColor      ForeColor;
    TColor      BackColor;
    TFontStyles FontStyle;
} TColorSetting;
//---------------------------------------------------------------------------
class ZXColorSetting
{
private:
    std::vector<TColorSetting>  m_Settings;
                    __fastcall  ZXColorSetting();

        String                  m_sName;
        TStringList*            m_Strings;

protected:
            void    __fastcall  Add(String sName, TColor ForeColor, TColor BackColor, TFontStyles FontStyles = TFontStyles());
            void    __fastcall  AddLine(String sLine);
    virtual void    __fastcall  ApplySetting(int i, TColorSetting Setting) = 0;
            void    __fastcall  ClearSettings();
    virtual void    __fastcall  DoReset() = 0;

        //TSynCustomHighlighter*  m_SynEdit;
        //TSynCustomHighlighter*  m_HL;

public:
                    __fastcall  ZXColorSetting(String sName);
    virtual         __fastcall ~ZXColorSetting();

            int     __fastcall  Count();

            bool    __fastcall  GetSetting(int i, TColorSetting& Setting);
            void    __fastcall  SetSetting(int i, TColorSetting Setting);
    virtual void    __fastcall  Update() = 0;
            void    __fastcall  Reset();

            void    __fastcall  Read(KRegistry* regScorpio);
            void    __fastcall  Write(KRegistry* regScorpio);

    __property  String                  Name        = { read = m_sName      };
    __property  TStringList*            Strings     = { read = m_Strings    };
    //__property  TSynCustomHighlighter*  Highlighter = { read = m_HL         };
};
//---------------------------------------------------------------------------
class ZXColorAsm :public ZXColorSetting
{
public:
                    __fastcall  ZXColorAsm();
                    __fastcall ~ZXColorAsm();

            void    __fastcall  ApplySetting(int i, TColorSetting Setting);
            void    __fastcall  Update();
            void    __fastcall  DoReset();
};
//---------------------------------------------------------------------------
class ZXColorZXBASIC :public ZXColorSetting
{
public:
                    __fastcall  ZXColorZXBASIC();
                    __fastcall ~ZXColorZXBASIC();

            void    __fastcall  ApplySetting(int i, TColorSetting Setting);
            void    __fastcall  Update();
            void    __fastcall  DoReset();
};
//---------------------------------------------------------------------------
class ZXColorC : public ZXColorSetting
{
public:
                    __fastcall  ZXColorC();
                    __fastcall ~ZXColorC();

            void    __fastcall  ApplySetting(int i, TColorSetting Setting);
            void    __fastcall  Update();
            void    __fastcall  DoReset();
};
//---------------------------------------------------------------------------
class ZXColorText : public ZXColorSetting
{
public:
                    __fastcall  ZXColorText();
                    __fastcall ~ZXColorText();

            void    __fastcall  ApplySetting(int i, TColorSetting Setting);
            void    __fastcall  Update();
            void    __fastcall  DoReset();
};
//---------------------------------------------------------------------------
#endif

