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
      
      Extends a Borland String with features similar to an MFC CString

---------------------------------------------------------------------------*/
#ifndef _ZXString_h_
#define _ZXString_h_

class ZXString
{
public:
    ZXString(LPCTSTR pszString = NULL)  : m_str(String(pszString)) {}
    ZXString(const AnsiString& aString) : m_str(aString) {}
    ZXString(const ZXString& rhs)       : m_str(rhs.m_str) {}

    ZXString&   operator=(const ZXString& rhs);

    // const methods
    bool        operator==(const ZXString& rhs) const   { return m_str == rhs.m_str; }
    bool        operator<(const ZXString& rhs)  const   { return m_str < rhs.m_str; }
    bool        operator>(const ZXString& rhs)  const   { return m_str > rhs.m_str; }
    int         Find(TCHAR aChar,int iStart=0)  const;
    int         Find(LPCTSTR pzSub)             const;
    int         FindOneOf(LPCTSTR pzCharacters) const;
    ZXString    Left(int iCount)                const;
    ZXString    Right(int iCount)               const;
    ZXString    Mid(int iFirst, int iCount = 0) const;
    int         GetLength()                     const   { return m_str.Length(); }
    operator    LPCTSTR()                       const   { return m_str.c_str(); }
    operator    String()                        const   { return m_str; }
private:
    AnsiString  m_str;
};

//---------------------------------------------------------------------------
// operator=
/**
 * assignment operator

 * @param	rhs	- object to assign
 * @return  reference to self
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
inline ZXString& ZXString::operator=(const ZXString& rhs)
{
    if (this != &rhs)
    {
        m_str = rhs.m_str;
    }
    return *this;
}

//---------------------------------------------------------------------------
// Find
/**
 * Find aChar in string

 * @param	aChar   - character to search for
 * @param	iStart	- offset in string to start search 0 = 1st character
 * @return  int - offset in string to match, 0 = ist character, otherwise < 0
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
inline int ZXString::Find(TCHAR aChar,int iStart) const
{
    int ipos = ::_tcschr(m_str.c_str()+iStart,aChar) - m_str.c_str();
    return ipos;
}

//---------------------------------------------------------------------------
// Find
/**
 * Find pzSub substring in string

 * @param	pzSub   - text to search for
 * @return  int - offset in string to match, 0 = ist character, otherwise < 0
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
inline int ZXString::Find(LPCTSTR pzSub) const
{
    return m_str.Pos(pzSub)-1;
}

//---------------------------------------------------------------------------
// Find
/**
 * Find the first character that is any one of pzCharacters in string

 * @param	pzCharacters   - characters to search for
 * @return  int - offset in string to match, 0 = 1st character, otherwise < 0
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
inline int ZXString::FindOneOf(LPCTSTR pzCharacters) const
{
    while(*pzCharacters)
    {
        int iPos = Find(*pzCharacters++);
        if (iPos >= 0)
        {
            return iPos;
        }
    }
    return -1;
}

//---------------------------------------------------------------------------
// Left
/**
 * Retuns left iCount characters of string

 * @param	iCount    - number of characters from left to extract
 * @return  ZXString  - containing left iCount characters
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
inline ZXString ZXString::Left(int iCount) const
{
    if (m_str.Length() > iCount)
    {
        return Mid(0,iCount);
    }
    return ZXString();
}

//---------------------------------------------------------------------------
// Right
/**
 * Retuns Right iCount characters of string

 * @param	iCount    - number of characters from Right to extract
 * @return  ZXString  - containing Right iCount characters
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
inline ZXString ZXString::Right(int iCount) const
{
    if (m_str.Length() > iCount)
    {
        return Mid(m_str.Length()-iCount,0);
    }
    return ZXString();
}

//---------------------------------------------------------------------------
// Mid
/**
 * Returns Mid iCount characters of string starting at iFirst

 * @param	iFirst    - offset to 1st characters to extract 0 = 1st character
 * @param	iCount    - number of characters from Right to extract, if 0
                        extracts to end of string
 * @return  ZXString  - containing Right iCount characters
 * @author  Mark Pinnuck
 * @date    Created 8 March 2004
 * @remarks Copyright Scorpio Software 2002
 */
//---------------------------------------------------------------------------
inline ZXString ZXString::Mid(int iFirst, int iCount) const
{
    ZXString mid;
    if (m_str.Length() > iFirst)
    {
        if (!iCount)
        {
            iCount = m_str.Length() - iFirst;
        }
        return m_str.SubString(iFirst+1,iCount);
    }
    return ZXString();
}

#endif  // _ZXString_h_
