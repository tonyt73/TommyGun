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
#include <vcl.h>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <memory>
#include <algorithm>
#include "KXmlInfo.h"
#include "ZXString.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
typedef auto_ptr<KXmlInfo> XmlInfoPtr;

const String XmlTrue("true");
const String XmlFalse("false");

const TCHAR TagStart(_T('<'));
const TCHAR TagEnd(_T('>'));
const TCHAR TagTerm(_T('/'));
const TCHAR TagTermHeader(_T('?'));

const TCHAR AttrDelim(_T('\''));
const TCHAR AttrSep(_T('='));
const TCHAR Space(_T(' '));
const TCHAR Tab(_T('\t'));


LPCTSTR szXmlHeader = "?xml";
LPCTSTR szCrlf		= "\r\n";

bool KXmlInfo::m_bRemoveWhitespace = false;


class CNestLevel
{
public:
	CNestLevel(int& level):
		m_rlevel(level)
		{
			++m_rlevel;
		}
	int operator()(void)
		{
			return m_rlevel*3;
		}
	~CNestLevel(void)
		{
			--m_rlevel;
			if(m_rlevel < 0)
			{
				m_rlevel = 0;
			}
		}
private:
	int&	m_rlevel;
};

/////////////////////////////////////////
//
// Xml Special character translations
//
// &  &amp;
// <  &lt;
// >  &gt;
// "  &quot;
// '  &apos;
/////////////////////////////////////////

const LPCTSTR XmlSpecialCharacters	= _T("\"&'<>");
const TCHAR	  XmlSpecial			= _T('&');
const TCHAR	  XmlSpecialEnd			= _T(';');

// not translations must be in same order as XmlSpecialCharacters
LPCTSTR CharToXmlTbl[] =
{
	_T("&quot;"),	//	 34 0x22 = "
	_T("&amp;"),	//	 38 0x26 = &
	_T("&apos;"),	//	 39 0x27 = '
	_T("&lt;"),		//	 60 0x3c = <
	_T("&gt;"),		//	 62 0x3e = >
	NULL			//	 end
};

//---------------------------------------------------------------------------
// XmlToChar
/**
 * Translates Xml escape sequence to Xml special

 * @param	strXmlText	Text string to xml string to translate
 * @return  translated string
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
String XmlToChar(const String& astrXmlText)
{
    String strXml = "";
    String strXmlText(astrXmlText);
	if (0 == strXmlText.Pos(XmlSpecial))
	{
		// no translation required
		return astrXmlText;
	}

	//////////////////////////////////////////////////////////
	// translate xml escape sequence to special characters  //
	//////////////////////////////////////////////////////////
    for (int i = 1; i <= strXmlText.Length(); ++i)
    {
        if (strXmlText[i] == XmlSpecial)
        {
            int iEnd = strXmlText.Pos(XmlSpecialEnd);
            String sXmlSpecial = strXmlText.SubString(i, iEnd - i + 1);
            strXmlText[i] = ' ';
            strXmlText[iEnd] = ' ';
            for(int j = 0; CharToXmlTbl[j]; j++)
            {
                if (sXmlSpecial == String(CharToXmlTbl[j]))
                {
                    strXml += XmlSpecialCharacters[j];
                    break;
                }
            }
            i = iEnd;
        }
        else
        {
            strXml += strXmlText[i];
        }
	}

	return strXml;
}

//---------------------------------------------------------------------------
// CharToXml
/**
 * Translates Xml special characters to Xml escape sequence

 * @param	strText	Text string to translate into xml
 * @return  translated string
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
String CharToXml(const String& aStrText)
{
    ZXString strText(aStrText);

	// check if strText has special characters
	int i = strText.FindOneOf(XmlSpecialCharacters);
	if (0 > i)
	{
		// no translation required
		return aStrText;
	}

	//////////////////////////////////////////////////////////
	// translate special characters to xml esacpe sequence  //
	//////////////////////////////////////////////////////////
	ostrstream oXml;
	oXml << (LPCTSTR)strText.Left(i);
	for(int j = i; j < strText.GetLength(); j++)
	{
		TCHAR c = strText[j];
		LPCTSTR pSpecial = ::_tcschr(XmlSpecialCharacters,c);
		if (pSpecial)
		{
            OutputDebugString("bye\n");
			oXml << (LPCTSTR)CharToXmlTbl[pSpecial-XmlSpecialCharacters];
		}
		else
		{
			oXml << c;
		}
	}
	oXml << ends;

	// return translated string
	String strXml( oXml.str() );
	oXml.freeze(false);
	return strXml;
}



//---------------------------------------------------------------------------
// ZXXmlItem
/**
 * Default constructor

 * @param	szName	Attribute name
 * @param	szValue Attribute value
 * @return  void
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
ZXXmlItem::ZXXmlItem(const String& sName, const String& sValue)
:	m_strName(sName)
,	m_strValue(sValue)
{
	// Empty
}

//---------------------------------------------------------------------------
// ZXXmlItem
/**
 * Default constructor

 * @param	szName	Attribute name
 * @param	szValue Attribute value
 * @return  void
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
ZXXmlItem::ZXXmlItem(LPCTSTR szName, LPCTSTR szValue)
:	m_strName(szName)
,	m_strValue(szValue)
{
	// Empty
}

//---------------------------------------------------------------------------
// ZXXmlItem
/**
 * Copy constructor

 * @param	item	Attribute to copy
 * @return  void
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
ZXXmlItem::ZXXmlItem(const ZXXmlItem& item)
:	m_strName(item.m_strName)
,	m_strValue(item.m_strValue)
{
	// Empty
}


//---------------------------------------------------------------------------
// ~ZXXmlItem
/**
 * Destructor
 * @return  void
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
/*ZXXmlItem::~ZXXmlItem(void)
{
	// Empty
}*/


//---------------------------------------------------------------------------
// operator=
/**
 * Assigment operator

 * @param	item	Attribute to copy
 * @return  reference to this
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
ZXXmlItem& ZXXmlItem::operator=(const ZXXmlItem& item)
{
	if (this != &item)
	{
		m_strName = item.m_strName;
		m_strValue = item.m_strValue;
	}
	return *this;
}

//---------------------------------------------------------------------------
// operator<
/**
 * Less than operator for collection ordering

 * @param	item	Attribute to compare with
 * @return  true if this < item, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool ZXXmlItem::operator<(const ZXXmlItem& item) const
{
	return (m_strName < item.m_strName);
}

//---------------------------------------------------------------------------
// SetValue
/**
 * Sets the attribute value

 * @param	strValue	New value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void ZXXmlItem::SetValue(const String& strValue) const
{
	m_strValue = strValue;
}


//////////////////////////////////////////////////////////////////////////////////////
// FUNCTION:    KXmlInfo::KXmlInfo
// OVERVIEW:    Copy constructor
// INPUTS:      info	XML info to copy
// OUTPUTS:     None
// 
//---------------------------------------------------------------------------
__fastcall KXmlInfo::KXmlInfo(const KXmlInfo& info)
:   m_tagName(info.m_tagName)
,	m_tagValue(info.m_tagValue)
,	m_items(info.m_items)
,	m_nodes(info.m_nodes)
,	m_pHeader((info.m_pHeader) ? new KXmlInfo(*info.m_pHeader) : NULL)
{
	// Empty
}

//---------------------------------------------------------------------------
// KXmlInfo
/**
 * Default constructor
 * @param	szTag		Tag name
 * @param	szValue		Tag address
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
__fastcall KXmlInfo::KXmlInfo(const String& sTag, const String& sValue)
:   m_tagName(sTag)
,	m_tagValue(sValue)
,	m_pHeader(NULL)
{
}

//---------------------------------------------------------------------------
// ~KXmlInfo
/**
 * Destructor
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
__fastcall KXmlInfo::~KXmlInfo(void)
{
	try
	{
		if (m_pHeader)
		{
			delete m_pHeader;
		}
	}
	catch(...)
	{
	}
}

//---------------------------------------------------------------------------
// Reset
/**
 * Reset the contents of the XML node.
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::Reset(void)
{
	m_tagName = "";
	m_tagValue = "";
	m_items.clear();
	m_nodes.clear();
}


//---------------------------------------------------------------------------
// Reset
/**
 * Reset the contents of the XML node.
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::IsHeader(void) const
{
	return m_tagName == szXmlHeader;
}


//---------------------------------------------------------------------------
// Reset
/**
 * Reset the contents of the XML node.
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetHeader(const KXmlInfo& rHeader)
{
	std::auto_ptr<KXmlInfo> ptrHeater(new KXmlInfo(rHeader));
	m_pHeader = ptrHeater.release();
}



//////////////////////////////////////////////////////////////////////////////////////
// FUNCTION:    KXmlInfo::operator=
// OVERVIEW:    Assignment operator
// INPUTS:      info	XML node to copy
// OUTPUTS:     None
// 
//---------------------------------------------------------------------------
// operator=
/**
 * Assignment operator
 * @param	info	XML node to copy
 * @return  reference to this
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::operator=(const KXmlInfo& info)
{
	if (this != &info)
	{
		m_tagName = info.m_tagName;
		m_tagValue = info.m_tagValue;
		m_items = info.m_items;
		m_nodes = info.m_nodes;
		if (info.m_pHeader)
		{
			m_pHeader = new KXmlInfo(*info.m_pHeader);
		}
	}
	return *this;
}


//---------------------------------------------------------------------------
// SetValue
/**
 * Set the value of the named attribute
 * @param	strName		Attribute name
 * @param	value		Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetText(int value)
{
	m_tagValue.printf("%d", value);
}

//---------------------------------------------------------------------------
// SetText
/**
 * Set the value of the named attribute
 * @param	value		Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetText(long value)
{
	m_tagValue.printf("%d", value);
}

//---------------------------------------------------------------------------
// SetText
/**
 * Set the value of the named attribute
 * @param	value		Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetText(bool flag)
{
	SetText((flag) ? XmlTrue : XmlFalse);
}

//---------------------------------------------------------------------------
// SetText
/**
 * Set the value of the named attribute
 * @param	value		Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetText(double value)
{
	m_tagValue.printf("%f", value);
}

//---------------------------------------------------------------------------
// GetInt
/**
 * Get the text value as int
 * @param	int text value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
int	KXmlInfo::GetInt(void) const
{
	int value = ::_ttoi(m_tagValue.c_str());
	return value;
}

//---------------------------------------------------------------------------
// GetInt
/**
 * Get the text value as int
 * @param	int text value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
unsigned int KXmlInfo::GetUInt(void) const
{
	unsigned int value = ::_ttoi(m_tagValue.c_str());
	return value;
}


//---------------------------------------------------------------------------
// GetDouble
/**
 * Get the text value as double
 * @param	int text value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
double KXmlInfo::GetDouble(void) const
{
	double value = ::atof(m_tagValue.c_str());
	return value;
}

//---------------------------------------------------------------------------
// GetBool
/**
 * Get the text value as bool
 * @param	int text value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::GetBool(void) const
{
	return m_tagValue == XmlTrue;
}

//---------------------------------------------------------------------------
// SetValue
/**
 * Set the value of the named attribute
 * @param	strName		Attribute name
 * @param	strValue	Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetValue(const String& strName, const String& strValue)
{
	ZXXmlItems::iterator itr = m_items.find(ZXXmlItem(strName));
	if (itr == m_items.end())
	{
		m_items.insert( ZXXmlItem(strName, strValue) );
	}
	else
	{
		itr->SetValue(strValue);
	}
}

//---------------------------------------------------------------------------
// SetValue
/**
 * Set the value of the named attribute
 * @param	strName		Attribute name
 * @param	strValue	Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetValue(const String& strName, LPCTSTR szValue)
{
	ZXXmlItems::iterator itr = m_items.find(ZXXmlItem(szValue));
	if (itr == m_items.end())
	{
		m_items.insert( ZXXmlItem(strName, String(szValue)) );
	}
	else
	{
		itr->SetValue(szValue);
	}
}


//---------------------------------------------------------------------------
// SetValue
/**
 * Set the value of the named attribute
 * @param	strName		Attribute name
 * @param	value		Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetValue(const String& strName, int value)
{
	String strValue;
	strValue.printf("%d", value);
	SetValue(strName, strValue);
}

//---------------------------------------------------------------------------
// SetValue
/**
 * Set the value of the named attribute
 * @param	strName		Attribute name
 * @param	value		Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetValue(const String& strName, unsigned int value)
{
	String strValue;
	strValue.printf("%u", value);
	SetValue(strName, strValue);
}


//---------------------------------------------------------------------------
// SetValue
/**
 * Set the value of the named attribute
 * @param	strName		Attribute name
 * @param	value		Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetValue(const String& strName, long value)
{
	String strValue;
	strValue.printf("%d", value);
	SetValue(strName, strValue);
}

//---------------------------------------------------------------------------
// SetValue
/**
 * Set the value of the named attribute
 * @param	strName		Attribute name
 * @param	value		Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetValue(const String& strName, bool flag)
{
	SetValue(strName, (flag) ? XmlTrue : XmlFalse);
}

//---------------------------------------------------------------------------
// SetValue
/**
 * Set the value of the named attribute
 * @param	strName		Attribute name
 * @param	value		Attribute value
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlInfo::SetValue(const String& strName, double value)
{
	String strValue;
	strValue.printf("%f", value);
	SetValue(strName, strValue);
}
//---------------------------------------------------------------------------
// GetValue
/**
 * Get the value of the named attribute
 * @param	strName		Attribute name
 * @param	strValue	Attribute value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::GetValue(const String& strName, String& strValue) const
{
	strValue = "";

	ZXXmlItems::const_iterator itr = m_items.find(ZXXmlItem(strName));
	if (itr == m_items.end())
	{
		return false;
	}

	strValue = itr->GetValue();
	return true;
}

//---------------------------------------------------------------------------
// GetValue
/**
 * Get the value of the named attribute
 * @param	strName		Attribute name
 * @param	Value		Attribute value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::GetValue(const String& strName, long& value) const
{
	String strValue;
	if (GetValue(strName, strValue))
	{
		value = ::_ttoi(strValue.c_str());
		return true;
	}

	value = 0;
	return false;
}

//---------------------------------------------------------------------------
// GetValue
/**
 * Get the value of the named attribute
 * @param	strName		Attribute name
 * @param	Value		Attribute value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::GetValue(const String& strName, int& value) const
{
	String strValue;
	if (GetValue(strName, strValue))
	{
		value = ::_ttoi(strValue.c_str());
		return true;
	}

	value = 0;
	return false;
}

//---------------------------------------------------------------------------
// GetValue
/**
 * Get the value of the named attribute
 * @param	strName		Attribute name
 * @param	Value		Attribute value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::GetValue(const String& strName, unsigned int& value) const
{
	String strValue;
	if (GetValue(strName, strValue))
	{
		value = ::_ttoi(strValue.c_str());
		return true;
	}

	value = 0;
	return false;
}


//---------------------------------------------------------------------------
// GetValue
/**
 * Get the value of the named attribute
 * @param	strName		Attribute name
 * @param	Value		Attribute value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::GetValue(const String& strName, bool& flag) const
{
	String strValue;
	if (GetValue(strName, strValue))
	{
		flag = (strValue == XmlTrue);
		return true;
	}
	flag = false;
	return false;
}

//---------------------------------------------------------------------------
// GetValue
/**
 * Get the value of the named attribute
 * @param	strName		Attribute name
 * @param	Value		Attribute value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::GetValue(const String& strName, double& value) const
{
	String strValue;
	if (GetValue(strName, strValue))
	{
		value = ::atof(strValue.c_str());
		return true;
	}

	value = 0;
	return false;
}
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::AddTag(const String& strName)
{
    return Add(strName, "");
}
//---------------------------------------------------------------------------
// Add
/**
 * Add a child to the current node
 * @param	szName		Tag name
 * @param	szValue		Tag value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::Add(const String& sName, const String& sValue)
{
	m_nodes.push_back(new KXmlInfo(sName, sValue));
	return (*m_nodes.back());
}

//---------------------------------------------------------------------------
// Add
/**
 * Add a child to the current node
 * @param	szName		Tag name
 * @param	szValue		Tag value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::Add(const String& sName, LPCTSTR sValue)
{
	m_nodes.push_back(new KXmlInfo(sName, sValue));
	return (*m_nodes.back());
}

//---------------------------------------------------------------------------
// Add
/**
 * Add a child to the current node
 * @param	szName		Tag name
 * @param	szValue		Tag value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::Add(const String& sName, int value)
{
	String strValue;
	strValue.printf("%d", value);
	m_nodes.push_back(new KXmlInfo(sName, strValue));
	return (*m_nodes.back());
}

//---------------------------------------------------------------------------
// Add
/**
 * Add a child to the current node
 * @param	szName		Tag name
 * @param	szValue		Tag value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::Add(const String& sName, unsigned int value)
{
	String strValue;
	strValue.printf("%u", value);
	m_nodes.push_back(new KXmlInfo(sName, strValue));
	return (*m_nodes.back());
}

//---------------------------------------------------------------------------
// Add
/**
 * Add a child to the current node
 * @param	szName		Tag name
 * @param	szValue		Tag value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::Add(const String& sName, long value)
{
	String strValue;
	strValue.printf("%d", value);
	m_nodes.push_back(new KXmlInfo(sName, strValue));
	return (*m_nodes.back());
}

//---------------------------------------------------------------------------
// Add
/**
 * Add a child to the current node
 * @param	szName		Tag name
 * @param	szValue		Tag value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::Add(const String& sName, double value)
{
	String strValue;
	strValue.printf("%f", value);
	m_nodes.push_back(new KXmlInfo(sName, strValue));
	return (*m_nodes.back());
}

//---------------------------------------------------------------------------
// Add
/**
 * Add a child to the current node
 * @param	szName		Tag name
 * @param	szValue		Tag value
 * @return  true if value found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::Add(const String& sName, bool flag)
{
	return Add(sName, (flag) ? XmlTrue : XmlFalse);
}

//---------------------------------------------------------------------------
// Add
/**
 * Add an xml fragment into the current document
 * @param	info		KXmlInfo to add
 * @return  reference to node just added
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo& KXmlInfo::Add(const KXmlInfo& info)
{
	m_nodes.push_back(new KXmlInfo(info));
	return (*m_nodes.back());
}

//---------------------------------------------------------------------------
// Remove
/**
 * Add an xml fragment into the current document
 * @param	pInfo		pointer to node to remove
 * @return  true if remove successful, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::Remove(KXmlInfo* pInfo)
{
	try
	{
		KXmlNodes::iterator itr = std::find(m_nodes.begin(), m_nodes.end(), pInfo);
		if (itr != end())
		{
			m_nodes.erase(itr);
			delete pInfo;
			return true;
		}
	}
	catch(...)
	{
	}
	return false;
}

//---------------------------------------------------------------------------
// GetNode
/**
 * Get the specified instance of a node.
 * @param	sName	Tag name
 * @param	index	Instance
 * @return  pointer to node if found, otherwise NULL
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlInfo* KXmlInfo::GetNode(const String& szName)
{
    return GetNode(szName, 0);
}
//---------------------------------------------------------------------------
KXmlInfo* KXmlInfo::GetNode(const String& szName, int index)
{
   KXmlInfo* pNode = NULL;
   Find(pNode, szName, index);
   return pNode;
}

//---------------------------------------------------------------------------
// Find
/**
 * Find the specified instance of a node.
 * @param	node	reference to store node found
 * @param	sName	Tag name
 * @param	index	Instance
 * @return  true if found, otherwise false
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::Find(KXmlInfo*& node, const String& sName)
{
    return Find(node, sName, 0);
}
//---------------------------------------------------------------------------
bool KXmlInfo::Find(KXmlInfo*& node, const String& sName, int index)
{
	KXmlNodes::iterator itr = find(sName.c_str(), index);
	if (itr != end())
	{
		node = *itr;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------
// Find
/**
 * Find the nth instance of node szName.
 * @param	sName	Tag name
 * @param	index	0 based index of tag instance
 * @return  KXmlNodes iterator, if found pointing to node, otherwise pointing to end
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlNodes::const_iterator KXmlInfo::find(const String& sName, int index) const
{
	for (KXmlNodes::const_iterator itr = m_nodes.begin(); itr != m_nodes.end(); ++itr)
	{
		const KXmlInfo& info = **itr;
		if (info.m_tagName == sName)
		{
			if (--index < 0)
			{
				return itr; 
			}
		}
	}
	return m_nodes.end();
}

//---------------------------------------------------------------------------
// Find
/**
 * Find the nth instance of node szName.
 * @param	sName	Tag name
 * @param	index	0 based index of tag instance
 * @return  KXmlNodes iterator, if found pointing to node, otherwise pointing to end
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlNodes::iterator KXmlInfo::find(const String& sName, int index)
{
	for (KXmlNodes::iterator itr = m_nodes.begin(); itr != m_nodes.end(); ++itr)
	{
		const KXmlInfo& info = **itr;
		if (info.m_tagName == sName)
		{
			if (--index < 0)
			{
				return itr;
			}
		}
	}
	return m_nodes.end();
}

//---------------------------------------------------------------------------
// GetXmlString 
/**
 * Convert the XmlInfo object to an XML string
 * @return  Returns the contents of the node as an XML string
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
AnsiString KXmlInfo::GetXmlString(void) const
{
	ostrstream ostr;

    ostr << "<?xml version='1.0' encoding='utf-8' ?>\r\n";
	ostr << *this << ends;
		
	AnsiString strInfo( ostr.str() );
	ostr.freeze(false);

	return strInfo;
}

//---------------------------------------------------------------------------
// SetXmlString 
/**
 * Load the node from an XML string
 * @param	strXml		XML string to load
 * @return  Returns true if ok, flase if XML parsing failed
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::SetXmlString(const AnsiString& strXml, AnsiString& strError)
{
	static LPCTSTR _METHOD_ = "KXmlInfo::SetXmlString";

	try
	{
		istrstream istr(strXml.c_str());
		istr >> *this;
		return true;
	}
	catch (const AnsiString& str)
	{
		strError.printf("[%s] Xml parse error:[%s]", _METHOD_, str);
	}
	catch (...)
	{
		strError.printf("[%s] Xml parse error:[Unhandled exception]", _METHOD_);
	}
	return false;
}


//---------------------------------------------------------------------------
// MergeXmlString 
/**
 * Merge an Xml string into this XmlInfo
 * @param	strXml	xml string to merge
 * @return  Returns true if merged ok, flase if not
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::MergeXmlString(const AnsiString& strXml)
{
	if (strXml.IsEmpty())
	{
		return false;
	}
	try
	{
		KXmlInfo* newXml = new KXmlInfo();
		newXml->SetXmlString(strXml);
		newXml->MergeXmlInfo(*this);
		*this = *newXml;
        delete newXml;
		return true;
	}
	catch(...)
	{
	}
	return false;
}

//---------------------------------------------------------------------------
// MergeXmlInfo 
/**
 * Merge an XmlInfo into this XmlInfo i.e. this <- rhs
	Note:
	if left and right hand side tag names match left side tag remains unchanged.
	if right hand tag not found in left. Right hand tag added to left.

 * @param	rhs	xml info to merge
 * @return  Returns true if merged ok, flase if not
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::MergeXmlInfo(const KXmlInfo& rhs)
{
	try
	{
		// for each node in right hand side
		for (KXmlNodes::const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
		{
			KXmlInfo* pNode;
			// if left and right nodes match
			if (Find(pNode,(*itr)->GetName()))
			{
				// merge matching nodes
				pNode->MergeXmlInfo(**itr);
			}
			else
			{
				// Add new nodes
				Add(**itr);
			}
		}
		return true;
	}
	catch(...)
	{
	}
	return false;
}


//---------------------------------------------------------------------------
// GetToken
/**
 * Get the next token from the input stream using cDelim as the delimiter
 * @param	istr		Input stream
 * @param	str			AnsiString to store token
 * @param	cDelim		Delimeter character
 * @return  Returns true if token read ok, flase if not
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::GetToken(istream& istr, AnsiString& str, TCHAR cDelim)
{
	TCHAR delims[] = { 0, 0 };
	delims[0] = cDelim;
	return GetToken(istr, str, delims);
}

//---------------------------------------------------------------------------
// GetToken 
/**
 * Get the next token from the input stream using cDelim as the delimiter
 * @param	istr		Input stream
 * @param	str			AnsiString to store token
 * @param	strDelim	Delimeter characters
 * @return  Returns true if token read ok, flase if not
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::GetToken(istream& istr, AnsiString& str, const AnsiString& strDelim)
{
	str = "";

	istr >> ws;				// Skip over whitespace

	while (!istr.eof())
	{
		TCHAR c = istr.get();		// Get next character

		str += c;

		if (strDelim.AnsiPos(c) > 0)	// Is character a delimeter
		{
			break;
		}
	}

	str.TrimRight();				// Remove white space from end of token
	return (!str.IsEmpty());
}


//---------------------------------------------------------------------------
// LoadFile
/**
 * Load an XML nodes from a file
 * @param	szFileName	file to load
 * @param	strError	contains error message if any.
 * @return  returns true if file loaded ok, otherwise returns false.
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::LoadFile(const AnsiString& sFileName, AnsiString& strError)
{
	static LPCTSTR _METHOD_ = "KXmlInfo::LoadFile";
	
	try
	{
		Reset();
		ifstream ifs;
		ifs.open(sFileName.c_str(),ios::binary );
		if (!ifs.is_open())
		{
			throw(AnsiString("Unable to open"));
		}

		// get length of file:
		ifs.seekg (0, ios::end);
		int length = ifs.tellg();
		ifs.seekg (0, ios::beg);

		AnsiString strXml;
		strXml.SetLength(length+1);
		LPSTR buffer = strXml.c_str();
		// read data as a block:
		ifs.read (buffer,length);

		// build xml
		SetXmlString(strXml);
		return true;
	}
	catch (const AnsiString& str)
	{
		strError.printf("[%s] File[%s] [%s]", _METHOD_,sFileName.c_str(), str);
	}
	catch (...)
	{
		strError.printf("[%s] File[%s] caught exception", _METHOD_,sFileName.c_str());
	}

	return false;
}


//---------------------------------------------------------------------------
// SaveFile
/**
 * Save current Xml Nodes to file
 * @param	szFileName	file to save
 * @param	strError	contains error message if any.
 * @return  returns true if file loaded ok, otherwise returns false.
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
bool KXmlInfo::SaveFile(const AnsiString& sFileName, AnsiString& strError)
{
	static LPCTSTR _METHOD_ = "KXmlInfo::SaveFile";
	try
	{
		ofstream ofs;
		ofs.open(sFileName.c_str(),std::ios::binary);
		if (!ofs.is_open())
		{
			throw(AnsiString("Unable to open"));
		}

		ofs << GetXmlString().c_str();
//		ofs << *this;
		return true;
	}
	catch (const AnsiString& str)
	{
		strError.printf("[%s] File[%s] [%s]", _METHOD_,sFileName.c_str(), str);
	}
	catch (...)
	{
		strError.printf("[%s] File[%s] caught exception", _METHOD_,sFileName.c_str());
	}
	return false;
}




//////////////////////////////////////////////////////////////////////////////////////
// FUNCTION:    KXmlNodes::KXmlNodes
// OVERVIEW:    Default consructor
// INPUTS:      None
// OUTPUTS:     None
// 
//---------------------------------------------------------------------------
// KXmlNodes 
/**
 * Default consructor
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlNodes::KXmlNodes(void)
{
	// Empty
}

//---------------------------------------------------------------------------
// KXmlNodes 
/**
 * Copy constructor
 * @param	nodes		List of nodes to copy
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlNodes::KXmlNodes(const KXmlNodes& nodes)
{
	copy(nodes);		// Deep copy of nodes
}

//---------------------------------------------------------------------------
// ~KXmlNodes 
/**
 * Destructor
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
/*KXmlNodes::~KXmlNodes(void)
{
	clear();			// Delete all node objects
}*/

//---------------------------------------------------------------------------
// operator= 
/**
 * Assignment operator, deep copy of nodes
 * @param	nodes		Nodes to copy
 * @return  reference to this
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
KXmlNodes& KXmlNodes::operator=(const KXmlNodes& nodes)
{
	if (this != &nodes)
	{
		clear();
		copy(nodes);
	}
	return *this;
}

//---------------------------------------------------------------------------
// clear
/**
 * Delete all nodes and empty list
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void __fastcall KXmlNodes::clear(void)
{
	for (iterator itr = begin(); itr != end(); ++itr)
	{
		delete *itr;
	}
	erase(begin(), end());
}

//---------------------------------------------------------------------------
// copy 
/**
 * Perform a deep copy from one node list to this list
 * @param	nodes		Nodes to copy
 * @return  none
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
void KXmlNodes::copy(const KXmlNodes& nodes)
{
	for (const_iterator itr = nodes.begin(); itr != nodes.end(); ++itr)
	{
		push_back(new KXmlInfo(**itr));
	}
}

//---------------------------------------------------------------------------
// ::operator<<
/**
 * Save an XML attribute to an output stream
 * @param	ostr		Output stream
 * @param	item		Attribute to save
 * @return  reference to ostr
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
ostream& operator<<(ostream& ostr, const ZXXmlItem& item)
{
	if (!item.m_strValue.IsEmpty())
	{
		ostr << " "
			 << string(CharToXml(item.m_strName).c_str())
			 << AttrSep
			 << AttrDelim
			 << string(CharToXml(item.m_strValue).c_str())
			 << AttrDelim;
	}
	return ostr;
}

//---------------------------------------------------------------------------
// ::operator<<
/**
 * Save a set of attributes to an output stream
 * @param	ostr		Output stream
 * @param	items		Set of items to save
 * @return  reference to ostr
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
ostream& operator<<(ostream& ostr, const ZXXmlItems& items)
{
	for (ZXXmlItems::const_iterator itr = items.begin(); itr != items.end(); ++itr)
	{
		ostr << *itr;
	}
	return ostr;
}

//---------------------------------------------------------------------------
// ::operator<<
/**
 * Save a list of nodes to an output stream
 * @param	ostr		Output stream
 * @param	nodes		List of nodes
 * @return  reference to ostr
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
ostream& operator<<(ostream& ostr, const KXmlNodes& nodes)
{
    for (KXmlNodes::const_iterator itr = nodes.begin(); itr != nodes.end(); ++itr)
    {
        ostr << **itr;
    }
	return ostr;
}

//---------------------------------------------------------------------------
// ::operator<<
/**
 * Save a node to an output stream
 * @param	ostr		Output stream
 * @param	info		XML node
 * @return  reference to ostr
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
ostream& operator<<(ostream& ostr, const KXmlInfo& info)
{
    static int iDepth = -1;

    if (info.m_tagName.Trim() != "")
    {
        AnsiString sSpaces = AnsiString::StringOfChar(' ', (++iDepth) * 2);

        if (KXmlInfo::m_bRemoveWhitespace == false)
        {
            ostr << sSpaces.c_str();
        }

        ostr << TagStart
             << CharToXml(info.m_tagName).c_str()    			// Save tag name
             << info.m_items;						// Save attributes within tag

        // If no tag value and no child nodes, write end of tag
        if (info.m_nodes.empty() && info.m_tagValue.IsEmpty())
        {
            ostr << TagTerm << TagEnd << szCrlf;
        }
        else
        {
            LPCTSTR str = (info.m_nodes.size() > 0) ? szCrlf : "";
            // Save tag value and child nodes.
            ostr << TagEnd
                 << str
                 << CharToXml(info.m_tagValue).c_str()
                 << info.m_nodes;

            if (KXmlInfo::m_bRemoveWhitespace == false && info.m_nodes.size() > 0)
            {
                ostr << sSpaces.c_str();
            }
            // Write terminating tag
            ostr << TagStart << TagTerm
                 << CharToXml(info.m_tagName).c_str()
                 << TagEnd
                 << szCrlf;
        }
        --iDepth;
    }
	return ostr;
}

//---------------------------------------------------------------------------
// ::operator>>
/**
 * Load an attribute from an input stream		name='value'
 * @param	istr		Input stream
 * @param	item		Item to load
 * @return  reference to istr
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
istream& operator>>(istream& istr, ZXXmlItem& item)
{
	KXmlInfo::GetToken(istr, item.m_strName, AttrSep);
	item.m_strName.SetLength(item.m_strName.Length()-1);
	// Character following '=' is assumed to be the quote character, value is terminated by
	// a second quote character
	TCHAR delim = istr.get();
	KXmlInfo::GetToken(istr, item.m_strValue, delim);
	item.m_strValue.SetLength(item.m_strValue.Length()-1);

	return istr;
}

//---------------------------------------------------------------------------
// ::operator>>
/**
 * Load a set of attributes from an input stream
 * @param	istr		Input stream
 * @param	items		Set of attributes to load
 * @return  reference to istr
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
istream& operator>>(istream& istr, ZXXmlItems& items)
{
	while (!istr.eof())
	{
		istr >> ws;				// Skip over whitespace
		// Check for '>' or '/>' signalling end of attributes
		TCHAR delim = istr.peek();
		if ((TagEnd == delim) || (TagTerm == delim) || (TagTermHeader == delim))
		{
			break;
		}

		ZXXmlItem item;
		istr >> item;
		items.insert(item);
	} 
	return istr;
}

//---------------------------------------------------------------------------
// ::operator>>
/**
 * Load a list of nodes from an input stream
 * @param	istr		Input stream
 * @param	Load a list of nodes from an input stream
 * @return  reference to istr
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
istream& operator>>(istream& istr, KXmlNodes& nodes)
{
	while (!istr.eof())
	{
		// Check for '</' signalling end of child nodes.
		// Skip to next '<'
		AnsiString whiteSpace;
		if (!KXmlInfo::GetToken(istr, whiteSpace, TagStart))
		{
			break; // no more tags
		}

		TCHAR c = TagStart;
		bool bTerm = (TagTerm == istr.peek());
		istr.putback(c);
		if (bTerm)
		{
			break;
		}

		XmlInfoPtr info(new KXmlInfo);
		istr >> *info;
		nodes.push_back(info.release());
	}
	
	return istr;
}

//---------------------------------------------------------------------------
// ::operator>>
/**
 * Load an XML nodes form an input stream
 * @param	istr		Input stream
 * @param	info		Xml node to load.
 * @return  reference to istr
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
istream& operator>>(istream& istr, KXmlInfo& info)
{
	info.Reset();
    AnsiString strXml;
	if (!KXmlInfo::GetToken(istr, strXml, _T(" />")))
	{
		return istr;
	}
    // convert xml special characters
    info.m_tagName = XmlToChar(strXml);

	TCHAR delim = info.m_tagName[info.m_tagName.Length()];
    {
	int ts = info.m_tagName.Pos(TagStart);
	int te = info.m_tagName.Pos(TagEnd);
	int tt = info.m_tagName.Pos(TagTerm);
    int e = info.m_tagName.Length();
    if (tt)
    {
        e = tt;
    }
    else if(te)
    {
        e = te;
    }
    int l = e - (ts+1);
    info.m_tagName = info.m_tagName.SubString(ts+1,l);
    }
	// If Tag name not delimited by '>' or '/>' look for attributes contained in tag
	if ((TagTerm != delim) && (TagEnd != delim))
	{
		istr >> info.m_items;

		delim = istr.get();
	}

	// If tag terminated by '/>' then there are no child nodes and no tag value.
	if (TagTerm == delim || TagTermHeader == delim)
	{
		istr.get();

		// if xml header just read extract the rest of the stream
		if (info.IsHeader())
		{
			if (info.m_pHeader)
			{
				try
				{
					delete info.m_pHeader;
				}
				catch(...)
				{
				}
			}
			info.m_pHeader = new KXmlInfo(info);
			istr >> info;
		}

		return istr;
	}

	// Check for a tag value.
	if (KXmlInfo::GetToken(istr, strXml, TagStart))
	{
        // convert xml special characters
        info.m_tagValue = XmlToChar(strXml);
		info.m_tagValue.SetLength(info.m_tagValue.Length()-1);
		istr.putback(TagStart);
	}

	// If tag/value is not followed by terminating tag, load the list of child nodes
	TCHAR c = istr.get();
	bool bTerm = (TagTerm == istr.peek());
	istr.putback(c);
	if (!bTerm)
	{
		istr >> info.m_nodes;
	}

	// Get the terminating tag
	AnsiString strEndTag;
	KXmlInfo::GetToken(istr, strEndTag, TagEnd);
    {
	int ts = strEndTag.Pos(TagStart);
    int te = strEndTag.Pos(TagEnd);
	int tt = strEndTag.Pos(TagTerm);
    int e = strEndTag.Length();
    if (tt)
    {
        e = tt;
    }
    else if(te)
    {
        e = te;
    }
    int l = e - (ts+1);
    strEndTag = strEndTag.SubString(ts+1,l);
    }

	// Check that the terminating tag matches the tag name.
	if (!strEndTag.IsEmpty() && (strEndTag != info.m_tagName))
	{
		AnsiString str;
		str.printf("End tag mismatch Tag:[%s] EndTag:[%s]", info.m_tagName, strEndTag);
		throw str;
	}
	return istr;
}
//---------------------------------------------------------------------------

