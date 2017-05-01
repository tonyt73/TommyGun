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
#include "ZXBuildPresets.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXBuildPreset::ZXBuildPreset()
: m_sName("")
, m_sAssembler("")
, m_sAssemblerParams("")
, m_sCompiler("")
, m_sCompilerParams("")
, m_sLinker("")
, m_sLinkerParams("")
, m_sEmulator("")
, m_sEmulatorParams("")
, m_sErrorPrefix("")
, m_sFilePrefix("")
, m_sLinePrefix("")
{
}
//---------------------------------------------------------------------------
__fastcall ZXBuildPreset::ZXBuildPreset(const ZXBuildPreset& other)
: m_sName(other.m_sName)
, m_sAssembler(other.m_sAssembler)
, m_sAssemblerParams(other.m_sAssemblerParams)
, m_sCompiler(other.m_sCompiler)
, m_sCompilerParams(other.m_sCompilerParams)
, m_sLinker(other.m_sLinker)
, m_sLinkerParams(other.m_sLinkerParams)
, m_sEmulator(other.m_sEmulator)
, m_sEmulatorParams(other.m_sEmulatorParams)
, m_sErrorPrefix(other.m_sErrorPrefix)
, m_sFilePrefix(other.m_sFilePrefix)
, m_sLinePrefix(other.m_sLinePrefix)
{
}
//---------------------------------------------------------------------------
__fastcall ZXBuildPreset::~ZXBuildPreset()
{
}
//---------------------------------------------------------------------------
void __fastcall ZXBuildPreset::SetString(int iIndex, const String& sValue)
{
    switch(iIndex)
    {
        case eName:
            m_sName = sValue.Trim();
            break;
        case eAssembler:
            m_sAssembler = sValue.Trim();
            break;
        case eAssemblerParams:
            m_sAssemblerParams = sValue.Trim();
            break;
        case eCompiler:
            m_sCompiler = sValue.Trim();
            break;
        case eCompilerParams:
            m_sCompilerParams = sValue.Trim();
            break;
        case eLinker:
            m_sLinker = sValue.Trim();
            break;
        case eLinkerParams:
            m_sLinkerParams = sValue.Trim();
            break;
        case eEmulator:
            m_sEmulator = sValue.Trim();
            break;
        case eEmulatorParams:
            m_sEmulatorParams = sValue.Trim();
            break;
        case eErrorPrefix:
            m_sErrorPrefix = sValue.Trim();
            break;
        case eFilePrefix:
            m_sFilePrefix = sValue.Trim();
            break;
        case eLinePrefix:
            m_sLinePrefix = sValue.Trim();
            break;
        default:
            break;
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXBuildPreset::Load(KXmlInfo& xmlInfo)
{
    KXmlInfo* node = xmlInfo.GetNode("Name");
    if (SAFE_PTR(node)) Name = node->GetText();
    node = xmlInfo.GetNode("Assembler");
    if (SAFE_PTR(node)) Assembler = node->GetText();
    node = xmlInfo.GetNode("AssemblerParams");
    if (SAFE_PTR(node)) AssemblerParams = node->GetText();
    node = xmlInfo.GetNode("Compiler");
    if (SAFE_PTR(node)) Compiler = node->GetText();
    node = xmlInfo.GetNode("CompilerParams");
    if (SAFE_PTR(node)) CompilerParams = node->GetText();
    node = xmlInfo.GetNode("Linker");
    if (SAFE_PTR(node)) Linker = node->GetText();
    node = xmlInfo.GetNode("LinkerParams");
    if (SAFE_PTR(node)) LinkerParams = node->GetText();
    node = xmlInfo.GetNode("Emulator");
    if (SAFE_PTR(node)) Emulator = node->GetText();
    node = xmlInfo.GetNode("EmulatorParams");
    if (SAFE_PTR(node)) EmulatorParams = node->GetText();
    node = xmlInfo.GetNode("ErrorPrefix");
    if (SAFE_PTR(node)) ErrorPrefix = node->GetText();
    node = xmlInfo.GetNode("FilePrefix");
    if (SAFE_PTR(node)) FilePrefix = node->GetText();
    node = xmlInfo.GetNode("LinePrefix");
    if (SAFE_PTR(node)) LinePrefix = node->GetText();
    return true;
}
//---------------------------------------------------------------------------
int ZXBuildPreset::operator==(const ZXBuildPreset& other)
{
    bool bSame = true;

    bSame &= m_sName            == other.m_sName;
    bSame &= m_sAssembler       == other.m_sAssembler;
    bSame &= m_sAssemblerParams == other.m_sAssemblerParams;
    bSame &= m_sCompiler        == other.m_sCompiler;
    bSame &= m_sCompilerParams  == other.m_sCompilerParams;
    bSame &= m_sLinker          == other.m_sLinker;
    bSame &= m_sLinkerParams    == other.m_sLinkerParams;
    bSame &= m_sEmulator        == other.m_sEmulator;
    bSame &= m_sEmulatorParams  == other.m_sEmulatorParams;
    bSame &= m_sErrorPrefix     == other.m_sErrorPrefix;
    bSame &= m_sFilePrefix      == other.m_sFilePrefix;
    bSame &= m_sLinePrefix      == other.m_sLinePrefix;

    return bSame;
}
//---------------------------------------------------------------------------
ZXBuildPreset& ZXBuildPreset::operator=(const ZXBuildPreset& other)
{
    m_sName             = other.m_sName;
    m_sAssembler        = other.m_sAssembler;
    m_sAssemblerParams  = other.m_sAssemblerParams;
    m_sCompiler         = other.m_sCompiler;
    m_sCompilerParams   = other.m_sCompilerParams;
    m_sLinker           = other.m_sLinker;
    m_sLinkerParams     = other.m_sLinkerParams;
    m_sEmulator         = other.m_sEmulator;
    m_sEmulatorParams   = other.m_sEmulatorParams;
    m_sErrorPrefix      = other.m_sErrorPrefix;
    m_sFilePrefix       = other.m_sFilePrefix;
    m_sLinePrefix       = other.m_sLinePrefix;

    return *this;
}
//---------------------------------------------------------------------------
__fastcall ZXBuildPresets::ZXBuildPresets()
{
}
//---------------------------------------------------------------------------
__fastcall ZXBuildPresets::~ZXBuildPresets()
{
}
//---------------------------------------------------------------------------
bool __fastcall ZXBuildPresets::Load(void)
{
    String sFile = ExtractFilePath(Application->ExeName) + "BuildPresets.xml";
    KXmlInfo Presets;
    Presets.Reset();
    Presets.LoadFile(sFile);
    for (KXmlNodes::iterator it = Presets.begin(); it != Presets.end(); it++)
    {
        ZXBuildPreset preset;
        preset.Load(*(*it));
        m_Presets.push_back(preset);
    }
    return true;
}
//---------------------------------------------------------------------------
int __fastcall ZXBuildPresets::GetCount(void)
{
    return m_Presets.size();
}
//---------------------------------------------------------------------------
bool __fastcall ZXBuildPresets::CheckAll(void)
{
    bool bFound = false;
    for (int i = 0; i < (int)m_Presets.size() && false == bFound; i++)
    {
        bFound = m_Presets[i] == reinterpret_cast<ZXBuildPreset&>(*this);
    }
    return !bFound;
}
//---------------------------------------------------------------------------
void __fastcall ZXBuildPresets::Select(const String& sName)
{
    // try to find the name and set the settings
    for (int i = 0; i < (int)m_Presets.size(); i++)
    {
        if (m_Presets[i].Name == sName)
        {
            return;
        }
    }
    // if the name doesn't exist then clear the settings, and set the new name
    reinterpret_cast<ZXBuildPreset&>(*this) = ZXBuildPreset();
    Name = sName;
}
//---------------------------------------------------------------------------

