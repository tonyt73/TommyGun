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
#ifndef RegistryH
#define RegistryH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Registry.hpp>
//---------------------------------------------------------------------------
#include "SafeMacros.h"
//---------------------------------------------------------------------------
/**
 * @class KSuperRegistry
 * This class overloads the Borland VCL Registry class so it can provide
 * overloaded Read and Write methods to the registry.
 */
//---------------------------------------------------------------------------
class PACKAGE KSuperRegistry : public TRegistry
{
public:
    // Read overloads
	virtual void __fastcall Read(const AnsiString& sName, bool& bValue)
    {
        bValue = ReadBool(sName);
    }
	virtual void __fastcall Read(const AnsiString& sName, int& iValue)
    {
        iValue = ReadInteger(sName);
    }
	virtual void __fastcall Read(const AnsiString& sName, double& fValue)
    {
        fValue = ReadFloat(sName);
    }
	virtual void __fastcall Read(const AnsiString& sName, AnsiString& sValue)
    {
        sValue = ReadString(sName);
    }
	virtual void __fastcall Read(const AnsiString& sName, TColor& cValue)
    {
        cValue = static_cast<TColor>(ReadInteger(sName));
    }
	virtual void __fastcall Read(const AnsiString& sName, TDateTime& dtValue)
    {
        dtValue = ReadDateTime(sName);
    }
    // Write overloads
	virtual void __fastcall Write(const AnsiString& sName, const bool& bValue)
    {
        WriteBool(sName, bValue);
    }
	virtual void __fastcall Write(const AnsiString& sName, const int& iValue)
    {
        WriteInteger(sName, iValue);
    }
	virtual void __fastcall Write(const AnsiString& sName, const double& fValue)
    {
        WriteFloat(sName, fValue);
    }
	virtual void __fastcall Write(const AnsiString& sName, const AnsiString& sValue)
    {
        WriteString(sName, sValue);
    }
	virtual void __fastcall Write(const AnsiString& sName, const TColor& cValue)
    {
        WriteInteger(sName, static_cast<int>(cValue));
    }
	virtual void __fastcall Write(const AnsiString& sName, const TDateTime& dtValue)
    {
        WriteDateTime(sName, dtValue);
    }
};
//---------------------------------------------------------------------------
enum KRootKey { rkHKEY_LOCAL_MACHINE, rkHKEY_CURRENT_USER, rkHKEY_USERS };
//---------------------------------------------------------------------------
/**
 * @class KRegistry
 * This class implements the new VCL registry object that you place onto a form to get access
 * to the registry. It uses templates to remove alot of duplicate code. The template code uses the
 * KSuperRegistry class to read and write to the registry.
 *
 * @verbatim
   Registry Component
    Allows easy access the the registry for the storage of application
   data and preferences.
   The Key path is
    \\HKEY_CURRENT_USER\Software\ResMed\{SECTION_NAME}[\KEY]\VALUE_NAME

   You MUST set a Section Name before you can use a KRegistry object

   SECTION_NAME is the usually the sName of the application
   KEY is an optional sub sKey to place the data into
   VALUE_NAME is the sName of where to place the data

  	Can read and write the following types
  		BOOL
  		INTEGER		4 bytes
  		ANSISTRING
  		FLOAT
  		TCOLOR
  		DATE/TIME

  	You can also query to see if a key or value exists in the registry
 * @endverbatim
 */
//---------------------------------------------------------------------------
class PACKAGE KRegistry : public TComponent
{
// template definitions
private:

/**
 * Reads a data item from the registry
 * @param   R the Registry object to read with
 * @param   S the name of the data item to read
 * @param   T the type of the data item to read
 * @author  Tony Thompson
 * @date    Created 15 March 2002
 */
template <class R, class S, class T>
T ReadRegistry(R Registry, S sName)
{
    T Value;
    Registry->Read(sName, Value);
    return Value;
}

/**
 * Writes a data item to the registry
 * @param   R the Registry object to write with
 * @param   S the name of the data item to write
 * @param   T the type of the data item to write
 * @author  Tony Thompson
 * @date    Created 15 March 2002
 */
template <class R, class S, class T>
void WriteRegistry(R Registry, S sName, T Value)
{
    Registry->Write(sName, Value);
}

/**
 * Reads a data item from the registry
 * @param   sKey the key to read from
 * @param   sName the name of the data item to read
 * @param   Value the value of the data item that was read
 * @return  true is successful, false if not
 * @author  Tony Thompson
 * @date    Created 15 March 2002
 */
template <class T>
bool ReadValue(const String& sKey, const String& sName, T& Value)
{
    bool bResult = false;

    // is safe to use the registry? if yes, open the key and check the item exists
	if (true == SAFE_PTR(m_Registry) && true == OpenKey(sKey) && true == ValueExists(sName))
    {
    	try
        {
            // read the value from registry
            Value = ReadRegistry<KSuperRegistry*, const String&, T>(m_Registry, sName);
            bResult = true;
        }
        __finally
        {
            // close the key
        	CloseKey();
        }
    }

    return bResult;
}

/**
 * Writes a data item to the registry
 * @param   sKey the key to write to
 * @param   sName the name of the data item to write
 * @param   Value the value of the data item to write
 * @return  true is successful, false if not
 * @author  Tony Thompson
 * @date    Created 15 March 2002
 */
template <class T>
bool WriteValue(const String& sKey, const String& sName, T& Value)
{
    bool bResult = false;

    // is safe to use the registry? if yes, open the key
	if (true == SAFE_PTR(m_Registry) && true == OpenKey(sKey))
    {
    	try
        {
            // write the data items value to the registry
			WriteRegistry(m_Registry, sName, Value);
            bResult = true;
        }
        __finally
        {
            // close the key
        	CloseKey();
        }
    }

    return bResult;
}

// private members
private:
	String                  m_sSection;
    String                  m_sRootKeyString;
	KSuperRegistry*         m_Registry;
    KRootKey                m_Root;

	        bool __fastcall OpenKey(const AnsiString sKey);
	        void __fastcall CloseKey(void);


public:
	             __fastcall KRegistry(TComponent* Owner);
	             __fastcall ~KRegistry();

    virtual bool __fastcall Read(const AnsiString& sKey, const AnsiString& sName, bool& bValue);
	virtual bool __fastcall Read(const AnsiString& sKey, const AnsiString& sName, int& iValue);
	virtual bool __fastcall Read(const AnsiString& sKey, const AnsiString& sName, double& fValue);
	virtual bool __fastcall Read(const AnsiString& sKey, const AnsiString& sName, AnsiString& sValue);
	virtual bool __fastcall Read(const AnsiString& sKey, const AnsiString& sName, TColor& cValue);
	virtual bool __fastcall Read(const AnsiString& sKey, const AnsiString& sName, class TDateTime& dtValue);

	virtual bool __fastcall Read(const AnsiString& sName, bool& bValue);
	virtual bool __fastcall Read(const AnsiString& sName, int& iValue);
	virtual bool __fastcall Read(const AnsiString& sName, double& fValue);
	virtual bool __fastcall Read(const AnsiString& sName, AnsiString& sValue);
	virtual bool __fastcall Read(const AnsiString& sName, TColor& cValue);
	virtual bool __fastcall Read(const AnsiString& sName, class TDateTime& dtValue);

	virtual bool __fastcall Write(const AnsiString& sKey, const AnsiString& sName, const bool& bValue);
	virtual bool __fastcall Write(const AnsiString& sKey, const AnsiString& sName, const int& iValue);
	virtual bool __fastcall Write(const AnsiString& sKey, const AnsiString& sName, const double& fValue);
	virtual bool __fastcall Write(const AnsiString& sKey, const AnsiString& sName, const AnsiString& sValue);
	virtual bool __fastcall Write(const AnsiString& sKey, const AnsiString& sName, const TColor& cValue);
	virtual bool __fastcall Write(const AnsiString& sKey, const AnsiString& sName, const class TDateTime& dtValue);

	virtual bool __fastcall Write(const AnsiString& sName, const bool& bValue);
	virtual bool __fastcall Write(const AnsiString& sName, const int& iValue);
	virtual bool __fastcall Write(const AnsiString& sName, const double& fValue);
	virtual bool __fastcall Write(const AnsiString& sName, const AnsiString& sValue);
	virtual bool __fastcall Write(const AnsiString& sName, const TColor& cValue);
	virtual bool __fastcall Write(const AnsiString& sName, const class TDateTime& dtValue);

    virtual bool __fastcall KeyExists  (const AnsiString& sKey);
    virtual bool __fastcall ClearKey   (const AnsiString& sKey);
    virtual bool __fastcall ClearValue (const AnsiString& sKey, const AnsiString& sValue);
    virtual bool __fastcall ValueExists(const AnsiString& sKey, const AnsiString& sName);
	virtual bool __fastcall ValueExists(const AnsiString& sName);
    virtual bool __fastcall GetValues  (const AnsiString& sKey, TStringList* slList);

__published:

	__property String   Section     = { read = m_sSection      , write = m_sSection        };
    __property KRootKey RootKey     = { read = m_Root          , write = m_Root            };
    __property String   SoftwareKey = { read = m_sRootKeyString, write = m_sRootKeyString  };
};
//---------------------------------------------------------------------------
#endif
