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
#ifndef ZXBuildPresetsH
#define ZXBuildPresetsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <vector>
//---------------------------------------------------------------------------
class ZXBuildPreset
{
private:
    enum ZXBuildPresets
    {
        eName,
        eAssembler,
        eAssemblerParams,
        eCompiler,
        eCompilerParams,
        eLinker,
        eLinkerParams,
        eEmulator,
        eEmulatorParams,
        eErrorPrefix,
        eFilePrefix,
        eLinePrefix
    };

    String              m_sName;
    String              m_sAssembler;
    String              m_sAssemblerParams;
    String              m_sCompiler;
    String              m_sCompilerParams;
    String              m_sLinker;
    String              m_sLinkerParams;
    String              m_sEmulator;
    String              m_sEmulatorParams;
    String              m_sErrorPrefix;
    String              m_sFilePrefix;
    String              m_sLinePrefix;

    void            __fastcall  SetString(int iIndex, const String& sValue);


public:
                    __fastcall  ZXBuildPreset();
                    __fastcall  ZXBuildPreset(const ZXBuildPreset& other);
    virtual         __fastcall ~ZXBuildPreset();

            bool    __fastcall  Load(KXmlInfo& xmlInfo);

    int             operator==(const ZXBuildPreset& other);
    ZXBuildPreset&  operator=(const ZXBuildPreset& other);

    __property  String  Name              = { read = m_sName,               write = SetString,  index = eName               };
    // Compiling parameters
    __property  String  Assembler         = { read = m_sAssembler,          write = SetString,  index = eAssembler          };
    __property  String  AssemblerParams   = { read = m_sAssemblerParams,    write = SetString,  index = eAssemblerParams    };
    __property  String  Compiler          = { read = m_sCompiler,           write = SetString,  index = eCompiler           };
    __property  String  CompilerParams    = { read = m_sCompilerParams,     write = SetString,  index = eCompilerParams     };
    __property  String  Linker            = { read = m_sLinker,             write = SetString,  index = eLinker             };
    __property  String  LinkerParams      = { read = m_sLinkerParams,       write = SetString,  index = eLinkerParams       };
    // Executing parameters
    __property  String  Emulator          = { read = m_sEmulator,           write = SetString,  index = eEmulator           };
    __property  String  EmulatorParams    = { read = m_sEmulatorParams,     write = SetString,  index = eEmulatorParams     };
    // Console parameters
    __property  String  ErrorPrefix       = { read = m_sErrorPrefix,        write = SetString,  index = eErrorPrefix        };
    __property  String  FilePrefix        = { read = m_sFilePrefix,         write = SetString,  index = eFilePrefix         };
    __property  String  LinePrefix        = { read = m_sLinePrefix,         write = SetString,  index = eLinePrefix         };
};
//---------------------------------------------------------------------------
class ZXBuildPresets : public ZXBuildPreset
{
private:
    std::vector<ZXBuildPreset>  m_Presets;

    int     __fastcall  GetCount(void);
    bool    __fastcall  CheckAll(void);

public:

            __fastcall  ZXBuildPresets();
            __fastcall ~ZXBuildPresets();

    bool    __fastcall  Load(void);

    void    __fastcall  Select(const String& sName);

    __property  int     Count             = { read = GetCount                                                               };
};
//---------------------------------------------------------------------------
#endif
 
