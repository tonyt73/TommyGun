//---------------------------------------------------------------------------

#include <basepch.h>

#pragma hdrstop

#include "KXml.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(KXml *)
{
    new KXml(NULL);
}
//---------------------------------------------------------------------------
__fastcall KXml::KXml(TComponent* Owner)
    : TComponent(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall KXml::SetString(int iIndex, String sValue)
{
    switch(iIndex)
    {
        case kxFile:
            m_sFilename = sValue.Trim();
            break;
        default:
            break;
    }
}
//---------------------------------------------------------------------------
bool __fastcall KXml::LoadFile(String& strError)
{
    bool result = false;
    if (m_sFilename != "")
    {
        result = m_Xml.LoadFile(m_sFilename, strError);
    }
    return result;
}
//---------------------------------------------------------------------------
bool __fastcall KXml::SaveFile(String& strError)
{
    bool result = false;
    if (m_sFilename != "")
    {
        result = m_Xml.SaveFile(m_sFilename, strError);
    }
    return result;
}
//---------------------------------------------------------------------------
namespace Kxml
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(KXml)};
         RegisterComponents("Scorpio", classes, 0);
    }
}
//---------------------------------------------------------------------------
 