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
#ifndef _KXmlInfo_h
#define _KXmlInfo_h
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
//---------------------------------------------------------------------------
#include <set>
#include <list>
#include <string>
#include <strstream>
//---------------------------------------------------------------------------
class PACKAGE KXmlInfo;
//---------------------------------------------------------------------------
// ZXXmlItem
/**
 * Contains an XML attribute
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 */
//---------------------------------------------------------------------------
class ZXXmlItem
{
public:
	ZXXmlItem(const AnsiString& sName, const AnsiString& sValue = AnsiString());
	ZXXmlItem(LPCTSTR szName = NULL, LPCTSTR szValue = NULL);
	ZXXmlItem(const ZXXmlItem& item);
	virtual ~ZXXmlItem(void) {};

	ZXXmlItem& operator=(const ZXXmlItem& item);
	bool	  operator<(const ZXXmlItem& item) const;

	const AnsiString&	GetName(void) const { return m_strName; }
	const AnsiString&	GetValue(void) const { return m_strValue; }
	void			SetValue(const AnsiString& strValue) const;

	friend std::ostream& operator<<(std::ostream& ostr, const ZXXmlItem& item);
	friend std::istream& operator>>(std::istream& istr, ZXXmlItem& item);

private:
	AnsiString		m_strName;			// Item name
	mutable AnsiString		m_strValue;			// Item value
};

typedef std::set<ZXXmlItem> ZXXmlItems;

std::ostream& operator<<(std::ostream& ostr, const ZXXmlItems& items);
std::istream& operator>>(std::istream& istr, ZXXmlItems& items);

//---------------------------------------------------------------------------
// KXmlNodes
/**
 * Collection of KXmlInfo nodes, used to hold children of a node.
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 */
//---------------------------------------------------------------------------
class KXmlNodes : public std::list<KXmlInfo*>
{
public:
	KXmlNodes();
	KXmlNodes(const KXmlNodes& nodes);
	virtual ~KXmlNodes() {};

	KXmlNodes& operator=(const KXmlNodes& nodes);

	void clear();

	friend std::ostream& operator<<(std::ostream& ostr, const KXmlNodes& nodes);
	friend std::istream& operator>>(std::istream& istr, KXmlNodes& nodes);

private:
	void copy(const KXmlNodes& nodes);
};

//---------------------------------------------------------------------------
// KXmlInfo
/**
 * Xml node/document, a node may contain attributes and child nodes
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 */
//---------------------------------------------------------------------------
class KXmlInfo
{
private:
	AnsiString			m_tagName;		// Tag name
	AnsiString			m_tagValue;		// Tag value

	ZXXmlItems		m_items;		// Set of interface items
	KXmlNodes		m_nodes;		// List of child nodes
	KXmlInfo*		m_pHeader;		// root node header

public:
	__fastcall KXmlInfo(const AnsiString& sTag = AnsiString(), const AnsiString& sValue = AnsiString());
	__fastcall KXmlInfo(const KXmlInfo& info);
	virtual __fastcall ~KXmlInfo();

    static bool     m_bRemoveWhitespace;

	KXmlInfo& operator=(const KXmlInfo& info);
	bool	IsHeader(void) const;
	bool	HasHeader(void) const { return m_pHeader != NULL; }
	void	Reset(void);

	// Tag name/value
	const AnsiString&		GetName(void) const { return m_tagName; }
	const AnsiString&		GetText(void) const { return m_tagValue; }
	const KXmlInfo*	    GetHeader(void) const { return m_pHeader; }
	int					GetInt(void) const;
	unsigned int		GetUInt(void) const;
	double				GetDouble(void) const;
	bool				GetBool(void) const;

	void	SetName(const AnsiString& sName)	{ m_tagName = sName; }
	void    SetText(const AnsiString& sValue)	{ m_tagValue = sValue; }
	void    SetText(LPCTSTR sValue)			{ m_tagValue = sValue; }
	void    SetText(int value);
	void    SetText(unsigned int value);
	void    SetText(long value);
	void    SetText(double value);
	void    SetText(bool value);
	void	SetHeader(const KXmlInfo& rHeader);

	// Attribute name/value pairs
	void	SetValue(const AnsiString& sName, const AnsiString& strValue);
	void	SetValue(const AnsiString& sName, LPCTSTR szValue);
	void	SetValue(const AnsiString& sName, long value);
	void	SetValue(const AnsiString& sName, int  value);
	void	SetValue(const AnsiString& sName, unsigned int  value);
	void	SetValue(const AnsiString& sName, bool flag);
	void	SetValue(const AnsiString& sName, double value);

	bool	GetValue(const AnsiString& sName, AnsiString& sValue) const;
	bool	GetValue(const AnsiString& sName, long& value) const;
	bool	GetValue(const AnsiString& sName, int&	value) const;
	bool	GetValue(const AnsiString& sName, unsigned int&	value) const;
	bool	GetValue(const AnsiString& sName, bool& flag) const;
	bool	GetValue(const AnsiString& sName, double& value) const;

	// Child nodes
	KXmlInfo&	AddTag(const AnsiString& strName);
#ifdef USE_PCH
	KXmlInfo&	Add(const AnsiString& strName, const AnsiString& szValue);
	KXmlInfo&	Add(const AnsiString& strName, LPCTSTR  value);
	KXmlInfo&	Add(const AnsiString& strName, int		value);
	KXmlInfo&	Add(const AnsiString& strName, unsigned int	value);
	KXmlInfo&	Add(const AnsiString& strName, long		value);
	KXmlInfo&	Add(const AnsiString& strName, double	value);
	KXmlInfo&	Add(const AnsiString& strName, bool		value);

	bool		Find(KXmlInfo*& node, const AnsiString& szName);
	bool		Find(KXmlInfo*& node, const AnsiString& szName, int index);
	KXmlInfo*	GetNode(const AnsiString& szName);
	KXmlInfo*	GetNode(const AnsiString& szName, int index);

	KXmlNodes::const_iterator  find(const AnsiString& sName, int index) const;
	KXmlNodes::iterator        find(const AnsiString& sName, int index);

#else
	KXmlInfo&	Add(const AnsiString& strName, const AnsiString& szValue = AnsiString());
	KXmlInfo&	Add(const AnsiString& strName, LPCTSTR  value = "");
	KXmlInfo&	Add(const AnsiString& strName, int		value = 0);
	KXmlInfo&	Add(const AnsiString& strName, unsigned int	value = 0);
	KXmlInfo&	Add(const AnsiString& strName, long		value = 0);
	KXmlInfo&	Add(const AnsiString& strName, double	value = 0);
	KXmlInfo&	Add(const AnsiString& strName, bool		value = false);

	bool		Find(KXmlInfo*& node, const AnsiString& szName, int index = 0);
	KXmlInfo*	GetNode(const AnsiString& szName, int index = 0);

	KXmlNodes::const_iterator  find(const AnsiString& sName, int index = 0) const;
	KXmlNodes::iterator        find(const AnsiString& sName, int index = 0);

#endif /* USE_PCH */
	KXmlInfo&	Add(const KXmlInfo& info);
	bool		Remove(KXmlInfo* pInfo);

	KXmlNodes::iterator	    begin(void)         { return m_nodes.begin(); }
	KXmlNodes::iterator        end(void)           { return m_nodes.end(); }
	KXmlNodes::const_iterator	begin(void) const   { return m_nodes.begin(); }
	KXmlNodes::const_iterator  end(void)   const   { return m_nodes.end(); }
	bool				        empty(void) const   { return m_nodes.empty(); }
	unsigned int		        size(void)          { return m_nodes.size(); }
	unsigned int		        size(void) const    { return m_nodes.size(); }

	// XML string handling
	AnsiString	GetXmlString(void) const;
	bool	SetXmlString(const AnsiString& strXml, AnsiString& strError = AnsiString());
	bool	MergeXmlString(const AnsiString& strXml);

	bool	MergeXmlInfo(const KXmlInfo& rhs);

	// XML File handling
	bool	LoadFile(const AnsiString& sFileName, AnsiString& strError = AnsiString());
	bool	SaveFile(const AnsiString&, AnsiString& strError = AnsiString());

	friend std::ostream& operator<<(std::ostream& ostr, const KXmlInfo& info);
	friend std::istream& operator>>(std::istream& istr, KXmlInfo& info);

	static bool GetToken(std::istream& istr, AnsiString& str, TCHAR cDelim);
	static bool GetToken(std::istream& istr, AnsiString& str, const AnsiString& strDelim);
};
//---------------------------------------------------------------------------
#endif //_KXmlInfo_h
