//---------------------------------------------------------------------------
#ifndef KXmlH
#define KXmlH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include "ZXXmlInfo.h"
//---------------------------------------------------------------------------
class PACKAGE KXml : public TComponent
{
private:
    enum    KXmlStrings     { kxFile        };

private:
    //ZXXmlInfo               m_Xml;
    String                  m_sFilename;

    void        __fastcall  SetString(int iIndex, String sValue);
protected:
public:
                __fastcall  KXml(TComponent* Owner);

	bool        __fastcall  LoadFile(String& strError = String());
	bool	    __fastcall  SaveFile(String& strError = String());

    //ZXXmlInfo&  __fastcall  Xml(void)   { return m_Xml; };

__published:

    __property  String      File    = { read = m_sFilename, write = SetString, index = kxFile   };
};
//---------------------------------------------------------------------------
#endif
 