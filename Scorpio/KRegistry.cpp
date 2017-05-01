/*---------------------------------------------------------------------------

	(c) 2002 Scorpio Software
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
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "KRegistry.h"
#include "SafeMacros.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
static inline void ValidCtrCheck(KRegistry *)
{
	new KRegistry(NULL);
}
//---------------------------------------------------------------------------
const String g_sBlankKey      = "";
const String g_sKeyDivider    = "\\";
//const String g_sRootKeyString = "\\Software\\Scorpio\\";
//const HKEY   g_hkRootKey      = HKEY_LOCAL_MACHINE;
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the control
 * @param   Owner the owner of the control
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
__fastcall KRegistry::KRegistry(TComponent* Owner)
	: TComponent(Owner),
      m_sRootKeyString("\\Software\\Scorpio\\"),
      m_Root(rkHKEY_CURRENT_USER)
{
    m_Registry = new KSuperRegistry;
    m_sSection = g_sBlankKey;
}
//---------------------------------------------------------------------------
// Destructor
/**
 * Frees the controls resources
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
__fastcall KRegistry::~KRegistry()
{
	SAFE_DELETE(m_Registry);
}
//---------------------------------------------------------------------------
// OpenKey
/**
 * Opens a registry key. This method is limited to only opening keys 1 level
 * deep from the ResMed section. Although the registry will easily allow
 * recursive creation of keys, this is deemed to add unnecessary complexity
 * to this control.
 * @param   sKey the key to open
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::OpenKey(const AnsiString sKey)
{
    bool bResult = false;

    try
    {
        if (true == SAFE_PTR(m_Registry) && m_sSection != g_sBlankKey)
        {
            AnsiString tKey;

            if (sKey != g_sBlankKey)
            {
                tKey = g_sKeyDivider + sKey;
            }

            HKEY hkRootKey = HKEY_CURRENT_USER;
            if (rkHKEY_LOCAL_MACHINE == m_Root)
            {
                hkRootKey = HKEY_LOCAL_MACHINE;
            }
            else if (rkHKEY_USERS == m_Root)
            {
                hkRootKey = HKEY_USERS;
            }
            m_Registry->RootKey = hkRootKey;
            m_Registry->OpenKey(NULL, false);

            bResult = m_Registry->OpenKey(m_sRootKeyString + m_sSection + tKey, true);
        }
    }
    catch(ERegistryException&)
    {
        bResult = false;
    }

    return bResult;
}
//---------------------------------------------------------------------------
// CloseKey
/**
 * Closes the the last key opened
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
void __fastcall KRegistry::CloseKey(void)
{
    try
    {
        if (true == SAFE_PTR(m_Registry))
        {
            m_Registry->CloseKey();
        }
    }
    catch(ERegistryException&)
    {
    }
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads an integer value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   iValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sKey, const AnsiString& sName, int& iValue)
{
    return ReadValue(sKey, sName, iValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads an integer value
 * @param   sName the name of the data item
 * @param   iValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sName, int& iValue)
{
	return Read(g_sBlankKey, sName, iValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a float value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   fValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sKey, const AnsiString& sName, double& fValue)
{
    return ReadValue(sKey, sName, fValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a float value
 * @param   sName the name of the data item
 * @param   fValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sName, double& fValue)
{
	return Read(g_sBlankKey, sName, fValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a string value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   sValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sKey, const AnsiString& sName, AnsiString& sValue)
{
    return ReadValue(sKey, sName, sValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a string value
 * @param   sName the name of the data item
 * @param   sValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sName, AnsiString &sValue)
{
	return Read(g_sBlankKey, sName, sValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a color value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   cValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sKey, const AnsiString& sName, TColor& cValue)
{
    return ReadValue(sKey, sName, cValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a color value
 * @param   sName the name of the data item
 * @param   cValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sName, TColor& cValue)
{
	return Read(g_sBlankKey, sName, cValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a bool value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   bValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sKey, const AnsiString& sName, bool& bValue)
{
    return ReadValue(sKey, sName, bValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a bool value
 * @param   sName the name of the data item
 * @param   bValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sName, bool& bValue)
{
	return Read(g_sBlankKey, sName, bValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a date/time value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   dtValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sKey, const AnsiString& sName, TDateTime& dtValue)
{
    double dValue = static_cast<double>(dtValue);
    return ReadValue(sKey, sName, dValue);
}
//---------------------------------------------------------------------------
// Read
/**
 * Reads a date/time value
 * @param   sName the name of the data item
 * @param   dtValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Read(const AnsiString& sName, class TDateTime &dtValue)
{
	return Read(g_sBlankKey, sName, dtValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a bool value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   bValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sKey, const AnsiString& sName, const bool& bValue)
{
    return WriteValue(sKey, sName, bValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a bool value
 * @param   sName the name of the data item
 * @param   bValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sName, const bool& bValue)
{
	return Write(g_sBlankKey, sName, bValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes an integer value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   iValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sKey, const AnsiString& sName, const int& iValue)
{
    return WriteValue(sKey, sName, iValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a integer value
 * @param   sName the name of the data item
 * @param   iValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sName, const int& iValue)
{
	return Write(g_sBlankKey, sName, iValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a float value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   fValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sKey, const AnsiString& sName, const double& fValue)
{
    return WriteValue(sKey, sName, fValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a float value
 * @param   sName the name of the data item
 * @param   fValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sName, const double& fValue)
{
	return Write(g_sBlankKey, sName, fValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a string value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   sValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sKey, const AnsiString& sName, const AnsiString& sValue)
{
    return WriteValue(sKey, sName, sValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a string value
 * @param   sName the name of the data item
 * @param   sValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sName, const AnsiString& sValue)
{
	return Write(g_sBlankKey, sName, sValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a color value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   cValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sKey, const AnsiString& sName, const TColor& cValue)
{
    return WriteValue(sKey, sName, cValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a color value
 * @param   sName the name of the data item
 * @param   cValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sName, const TColor& cValue)
{
	return Write(g_sBlankKey, sName, cValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a date/time value
 * @param   sKey the key to read from
 * @param   sName the name of the data item
 * @param   dtValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sKey, const AnsiString& sName, const class TDateTime& dtValue)
{
    return WriteValue(sKey, sName, dtValue);
}
//---------------------------------------------------------------------------
// Write
/**
 * Writes a date/time value
 * @param   sName the name of the data item
 * @param   dtValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::Write(const AnsiString& sName, const class TDateTime& dtValue)
{
	return Write(g_sBlankKey, sName, dtValue);
}
//---------------------------------------------------------------------------
// KeyExists
/**
 * Checks if a key exists
 * @param   sKey the key to check for
 * @param   fValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::KeyExists(const AnsiString& sKey)
{
    bool bResult = false;

    try
    {
        if (true == SAFE_PTR(m_Registry))
        {
            bResult = m_Registry->KeyExists(sKey);
        }
    }
    catch(ERegistryException&)
    {
        bResult = false;
    }

    return bResult;
}
//---------------------------------------------------------------------------
// ClearKey
/**
 * Clears for the entries under a key
 * @param   sKey the key to clear
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::ClearKey(const AnsiString& sKey)
{
    bool bResult = false;

    try
    {
        if (true == SAFE_PTR(m_Registry) && true == OpenKey(sKey))
        {
            try
            {
                // create a string list to place the names to delete
                TStrings *slNames = new TStringList;

                if (true == SAFE_PTR(slNames))
                {
                    // do an NT friendly delete subkeys
                    try
                    {
                        // read the names for the key
                        m_Registry->GetValueNames(slNames);

                        // delete each name from the list
                        for (int i = 0; i < slNames->Count; i++)
                        {
                            m_Registry->DeleteValue(slNames->Strings[i]);
                        }

                        if (true == m_Registry->HasSubKeys())
                        {
                            // delete all sub keys and values within
                            m_Registry->GetKeyNames(slNames);

                            for (int i = 0; i < slNames->Count; i++)
                            {
                                // recursive entry into clearkey
                                CloseKey();
                                ClearKey(slNames->Strings[i]);
                                OpenKey(sKey);
                                m_Registry->DeleteKey(slNames->Strings[i]);
                            }
                        }

                        bResult = true;
                    }
                    __finally
                    {
                        // free the string list
                        SAFE_DELETE(slNames);
                    }
                }
            }
            __finally
            {
                // close the registry key
                CloseKey();
            }
        }
    }
    catch(ERegistryException&)
    {
        bResult = false;
    }

    return bResult;
}
//---------------------------------------------------------------------------
// ClearValue
/**
 * Clears a value entry
 * @param   sKey the key to read from
 * @param   sValue the name of the data item to clear
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::ClearValue(const AnsiString& sKey, const AnsiString& sValue)
{
    bool bResult = false;

    try
    {
        if (true == SAFE_PTR(m_Registry) && true == OpenKey(sKey))
        {
            try
            {
                m_Registry->DeleteValue(sValue);
                bResult = true;
            }
            __finally
            {
                CloseKey();
            }
        }
    }
    catch(ERegistryException&)
    {
        bResult = false;
    }

    return bResult;
}
//---------------------------------------------------------------------------
// ValueExists
/**
 * Checks for the existance of a value
 * @param   sKey the key to read from
 * @param   sName the name of the data item to check for
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::ValueExists(const AnsiString& sKey, const AnsiString& sName)
{
	bool bResult = false;

    try
    {
        if (true == SAFE_PTR(m_Registry) && true == OpenKey(sKey))
        {
            bResult = m_Registry->ValueExists(sName);
            CloseKey();
        }
    }
    catch(ERegistryException&)
    {
        bResult = false;
    }

	return bResult;
}
//---------------------------------------------------------------------------
// ValueExists
/**
 * Checks the currently opened key for the existance of a value
 * @param   sName the name of the data item to check for
 * @param   fValue the value of the data item
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::ValueExists(const AnsiString& sName)
{
    bool bResult = false;

    try
    {
        if (true == SAFE_PTR(m_Registry))
        {
            bResult = m_Registry->ValueExists(sName);
        }
    }
    catch(ERegistryException&)
    {
        bResult = false;
    }

    return bResult;
}
//---------------------------------------------------------------------------
// GetValues
/**
 * Gets all the values under a key
 * @param   sKey the key to read from
 * @param   slList the string list to place all the value entries
 * @return  true is successful, false is not
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
bool __fastcall KRegistry::GetValues(const AnsiString& sKey, TStringList* slList)
{
	bool bResult = false;

    try
    {
        if (true == SAFE_PTR(m_Registry) && true == SAFE_PTR(slList) && true == OpenKey(sKey))
        {
            try
            {
                m_Registry->GetValueNames(slList);
                bResult = true;
            }
            __finally
            {
                CloseKey();
            }
        }
    }
    catch(ERegistryException&)
    {
        bResult = false;
    }

    return bResult;
}
//---------------------------------------------------------------------------
// Register
/**
 * Registers the control with the Borland Builder IDE
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
namespace Kregistry
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(KRegistry)};
		RegisterComponents("Scorpio", classes, 0);
	}
}
//---------------------------------------------------------------------------
