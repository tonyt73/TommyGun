/*---------------------------------------------------------------------------

	(c) 2001 ResMed Ltd
    	97 Waterloo Road, North Ryde, 2113, Australia
      	Tel +61 2 9886 5000; Fax +61 9878 0120

-----------------------------------------------------------------------------

    $Workfile::   SafeMacros.h                                            $
    $Revision::   1.3                                                     $
    $Date::   02 Jul 2003 12:36:38                                        $
    $Author::   tonyt                                                     $

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#ifndef SafeMacrosH
#define SafeMacrosH
//---------------------------------------------------------------------------
//#include "CustomAllocator.h"
#include "..\..\TommyGun\Logging\MessageLogger.h"
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma warn -8004  // Turn OFF Warning W8004: Identifier is assigned a value that is not used.
#pragma warn -8026  // Turn OFF Warning W8026: Functions taking class-by-value args are not expanded inline
#pragma warn -8027  // Turn OFF Warning W8027: Functions containing switch are not expanded inline
#endif//__BORLANDC__
//- COMPILER DEPENDENT STRING DEFINITION ------------------------------------
#ifndef RWSTRING
  #ifdef __BORLANDC__
    #define RWSTRING AnsiString
    #define RWSTRING_LENGTH(a) a.Length()
    #define RWSTRING_CSTR(a) a.c_str()
  #else
    #define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
    #include <afxwin.h>         // MFC core and standard components
    #define RWSTRING CString
    #define RWSTRING_LENGTH(a) a.GetLength()
    #define RWSTRING_CSTR(a) LPCTSTR(a)
  #endif//__BORLANDC__
#endif//RWSTRING
//- COMPILER DEPENDENT CALLING CONVENTION TO USE ----------------------------
#ifndef CALLSTYLE
  #ifdef __BORLANDC__
    #define CALLSTYLE __fastcall
  #else
    #define CALLSTYLE
  #endif//__BORLANDC__
#endif//CALLSTYLE*/
//---------------------------------------------------------------------------
//#if defined(_DEBUG) && defined(__BORLANDC__)
#if defined(__BORLANDC__)
  #ifndef DEBUG_MSG
    #ifdef USE_REMOTE_LOGGING
      #pragma message("Defining DEBUG_MSG to use RemoteLogging RL_EXCEPTION")
      #define DEBUG_MSG( s ) RL_EXCEPTION(s)
    #else//USE_REMOTE_LOGGING
      #pragma message("Defining DEBUG_MSG to use OutputDebugString")
      #define DEBUG_MSG( s ) OutputDebugString(AnsiString(s).c_str());
    #endif//USE_REMOTE_LOGGING
  #endif//DEBUG_MSG
#else
  #define DEBUG_MSG
#endif//_DEBUG*/
//---------------------------------------------------------------------------
// macros for testing if a pointer is safe to use
#ifndef SAFE_READ_PTR
#define SAFE_READ_PTR( a )\
( FALSE == IsBadReadPtr( (void*)a, sizeof(a)) )
#endif//SAFE_READ_PTR
//---------------------------------------------------------------------------
#ifndef SAFE_WRITE_PTR
#define SAFE_WRITE_PTR( b )\
( FALSE == IsBadWritePtr( (void*)b, sizeof(b)) )
#endif//SAFE_WRITE_PTR
//---------------------------------------------------------------------------
#ifndef SAFE_CODE_PTR
#define SAFE_CODE_PTR( c )\
( FALSE == IsBadCodePtr(reinterpret_cast<FARPROC>(c)) )
#endif//SAFE_CODE_PTR
//---------------------------------------------------------------------------
#ifndef SAFE_PTR
#define SAFE_PTR( d )\
((true == SAFE_READ_PTR(d)) && (true == SAFE_WRITE_PTR(d)))
#endif//SAFE_PTR
//---------------------------------------------------------------------------
#ifndef SAFE_BLOCK_PTR
#define SAFE_BLOCK_PTR( e, f )\
( FALSE == IsBadWritePtr( (void*)e, f) && FALSE == IsBadReadPtr( (void*)e, f) )
#endif//SAFE_BLOCK_PTR
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#ifndef TRY_ALL
#define TRY_ALL \
try\
{\
    try\
    {
#endif//TRY_ALL
#else
#ifndef TRY_ALL
#define TRY_ALL
#endif//TRY_ALL
#endif//__BORLANDC__
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#ifndef CATCH_ALL_DO_NOTHING
#define CATCH_ALL_DO_NOTHING \
    }\
    catch(Exception&)\
    {\
    }\
}\
__except(true)\
{\
}
#endif//CATCH_ALL_DO_NOTHING
#else
#ifndef CATCH_ALL_DO_NOTHING
#define CATCH_ALL_DO_NOTHING
#endif//CATCH_ALL_DO_NOTHING
#endif//__BORLANDC__
//---------------------------------------------------------------------------
#ifndef CATCH_ALL
#define CATCH_ALL( a )\
    }\
    catch(Exception&)\
    {\
        a;\
    }\
}\
__except(true)\
{\
    a;\
}
#endif//CATCH_ALL
//---------------------------------------------------------------------------
#ifndef CATCH_ALL_AND_SHOW_EXCEPTION
#define CATCH_ALL_AND_SHOW_EXCEPTION( a ) \
    }\
    catch(...)\
    {\
        m_MessageBox->ShowLastExceptionMessage(a, __FILE__, __FUNC__, __LINE__);\
    }\
}\
__except(true)\
{\
    m_MessageBox->ShowLastExceptionMessage(a, __FILE__, __FUNC__, __LINE__);\
}
#endif//CATCH_ALL_AND_SHOW_EXCEPTION
//---------------------------------------------------------------------------
#ifndef CATCH_ALL_AND_LOG_EXCEPTION
#define CATCH_ALL_AND_LOG_EXCEPTION( a ) \
    }\
    catch(...)\
    {\
        DEBUG_MSG(a);\
    }\
}\
__except(true)\
{\
    DEBUG_MSG(a);\
}
#endif//CATCH_ALL_AND_LOG_EXCEPTION
//-- MACROS -----------------------------------------------------------------
// SAFE_DELETE checks the pointer parameter to be deleted to confirm it is a valid pointer.
//   If the pointer is valid, it is deleted. The pointer is then NULLified to prevent it being used again.
//   This macro is used mainly on VCL pointers.  The use of pointers is not encouraged within this code.
//   If pointers must be used, then you should use a smart pointer class.
//---------------------------------------------------------------------------
#ifndef SAFE_DELETE
	#ifdef __BORLANDC__
		// BORLAND C++ BUILDER
		#define SAFE_DELETE( a ) \
		try\
		{\
			try\
			{\
				try\
				{\
					if (true == SAFE_PTR(a))\
					{\
						delete a;\
						a = NULL;\
					}\
				}\
				catch (Exception &exception)\
				{\
					a = NULL;\
					String sMsg = "VCL Exception: Failed to safely delete object. File:";\
					String sFile(__FILE__);\
					String sFunc(__FUNC__);\
					String sLine(__LINE__);\
					DEBUG_MSG( sMsg + sFile + ", Func: " + sFunc + ", Line: " + sLine);\
				}\
			}\
			__except(true)\
			{\
				a = NULL;\
				String sMsg = "Structured Exception: Failed to safely delete object. File:";\
				String sFile(__FILE__);\
				String sFunc(__FUNC__);\
				String sLine(__LINE__);\
				DEBUG_MSG( sMsg + sFile + ", Func: " + sFunc + ", Line: " + sLine);\
			}\
		}\
		catch(...)\
		{\
			a = NULL;\
			String sMsg = "C++ Exception: Failed to safely delete object. File:";\
			String sFile(__FILE__);\
			String sFunc(__FUNC__);\
			String sLine(__LINE__);\
			DEBUG_MSG( sMsg + sFile + ", Func: " + sFunc + ", Line: " + sLine);\
		}
	#else
		// MICROSOFT VISUAL C++
		#define SAFE_DELETE( a ) \
		try\
		{\
			if (true == SAFE_PTR(a))\
			{\
				delete a;\
				a = NULL;\
			}\
		}\
		catch(...)\
		{\
			a = NULL;\
			RWSTRING sMsg = "Structured Exception: Failed to safely delete object. File:";\
			RWSTRING sFile(__FILE__);\
			DEBUG_MSG( sMsg + sFile);\
		}
	#endif//__BORLANDC__
#endif//SAFE_DELETE

#ifndef SAFE_ARRAY_DELETE
	#ifdef __BORLANDC__
		// BORLAND C++ BUILDER
		#define SAFE_ARRAY_DELETE( a )\
		try\
		{\
			try\
			{\
				try\
				{\
					if (true == SAFE_PTR(a))\
					{\
						delete[] a;\
						a = NULL;\
					}\
				}\
				catch (Exception &exception)\
				{\
					a = NULL;\
					String sMsg = "VCL Exception: Failed to safely delete array object. File:";\
					String sFile(__FILE__);\
					String sFunc(__FUNC__);\
					String sLine(__LINE__);\
					DEBUG_MSG( sMsg + sFile + ", Func: " + sFunc + ", Line: " + sLine);\
				}\
			}\
			catch(...)\
			{\
				a = NULL;\
				String sMsg = "C++ Exception: Failed to safely delete array object. File:";\
				String sFile(__FILE__);\
				String sFunc(__FUNC__);\
				String sLine(__LINE__);\
				DEBUG_MSG( sMsg + sFile + ", Func: " + sFunc + ", Line: " + sLine);\
			}\
		}\
		__except(true)\
		{\
			a = NULL;\
			String sMsg = "Structured Exception: Failed to safely delete array object. File:";\
			String sFile(__FILE__);\
			String sFunc(__FUNC__);\
			String sLine(__LINE__);\
			DEBUG_MSG( sMsg + sFile + ", Func: " + sFunc + ", Line: " + sLine);\
		}
	#else
		// MICROSOFT VISUAL C++
		#define SAFE_ARRAY_DELETE( a )\
		try\
		{\
			if (true == SAFE_PTR(a))\
			{\
				delete[] a;\
				a = NULL;\
			}\
		}\
		catch(...)\
		{\
			a = NULL;\
			RWSTRING sMsg = "C++ Exception: Failed to safely delete array object. File:";\
			RWSTRING sFile(__FILE__);\
			DEBUG_MSG( sMsg + sFile);\
		}
	#endif//__BORLANDC__
#endif//SAFE_ARRAY_DELETE

#ifndef SAFE_NEW(a)\
    
#endif//SAFE_NEW

#ifndef CHECK_HRESULT
#define CHECK_HRESULT( a )\
if(FAILED(a))\
{\
    String sTitle = "hResult Error";\
    ShowWindowsErrorMessage( sTitle, a, __FILE__, __FUNC__, __LINE__ );\
}
#endif//CHECK_HRESULT

//---------------------------------------------------------------------------
#endif //SafeMacrosH
