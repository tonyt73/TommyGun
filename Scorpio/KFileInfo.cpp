/*---------------------------------------------------------------------------

	(c) 2001 ResMed Ltd
    	97 Waterloo Road, North Ryde, 2113, Australia
      	Tel +61 2 9886 5000; Fax +61 9878 0120

-----------------------------------------------------------------------------

    $Workfile::   KFileInfo.cpp                                           $
    $Revision::   1.2                                                     $
    $Date::   May 09 2003 15:29:50                                        $
    $Author::   GavinT                                                    $

---------------------------------------------------------------------------*/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <malloc.h>
#include "KFileInfo.h"
#include "winver.h"
#include "SafeMacros.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const String g_sNotAvailable = "Not Available";
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
static inline void ValidCtrCheck(KFileInfo *)
{
    new KFileInfo(NULL);
}
//---------------------------------------------------------------------------
// Constructor
/**
 * Initializes the control
 * @param   Owner the owner of this control
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
__fastcall KFileInfo::KFileInfo(TComponent* Owner)
  : TComponent(Owner)
{
}
//---------------------------------------------------------------------------
// GetFileVersionInformation
/**
 * Retrieves the Version Information from a file
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
void __fastcall KFileInfo::GetFileVersionInformation(void)
{
    if (false == FFileName.IsEmpty())
    {
        // set the default property values
        FFileInfoValid = false;

        FBuildNumber      = 0;
        FReleaseNumber    = 0;
        FMajorVersion     = 0;
        FMinorVersion     = 0;

        FComments         = g_sNotAvailable;
        FCompanyName      = g_sNotAvailable;
        FFileDescription  = g_sNotAvailable;
        FFileVersion      = g_sNotAvailable;
        FInternalName     = g_sNotAvailable;
        FLegalCopyright   = g_sNotAvailable;
        FLegalTrademarks  = g_sNotAvailable;
        FOriginalFilename = g_sNotAvailable;
        FProductName      = g_sNotAvailable;
        FProductVersion   = g_sNotAvailable;
        FProductVersion   = g_sNotAvailable;

        //Get size of file version structure .. will be zero if 16 bit image or no file version info available
        DWORD dwFileVersionHandle = 0;
        long FileInfoSize = GetFileVersionInfoSize(FFileName.c_str(), &dwFileVersionHandle);

        if (0 != FileInfoSize)
        {
            void *FileInfoData = NULL;

            try
            {
                FileInfoData = new char[ FileInfoSize ];
            }
            catch(EOutOfMemory&)
            {
                FileInfoData = NULL;
            }

            if (true == SAFE_PTR(FileInfoData))
            {
                // Read the file version information block from the file
                if (GetFileVersionInfo(FFileName.c_str(), 0, FileInfoSize, FileInfoData))
                {
                    // Now get the standard VS_FIXEDFILEINFO structure
                    unsigned int uiInfoSize = sizeof(VS_FIXEDFILEINFO);
                    VS_FIXEDFILEINFO *FileInfo = NULL;

                    if (VerQueryValue(FileInfoData, "\\", (void**)&FileInfo, &uiInfoSize))
                    {
                        FBuildNumber   = LOWORD(FileInfo->dwFileVersionLS);
                        FReleaseNumber = HIWORD(FileInfo->dwFileVersionLS);
                        FMajorVersion  = HIWORD(FileInfo->dwFileVersionMS);
                        FMinorVersion  = LOWORD(FileInfo->dwFileVersionMS);
                    }

                    // Get the language dependant strings

                    // Structure used to store enumerated languages and code pages.
                    struct LANGANDCODEPAGE
                    {
                      WORD wLanguage;
                      WORD wCodePage;
                    } *lpTranslate;

                    // Read the list of languages and code pages.
                    if (VerQueryValue(FileInfoData, TEXT("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &uiInfoSize))
                    {
                        char* pcStringBuffer = NULL;

                        // We have a language and code page to work with, so
                        String sSubBlock;
                        String sSubBlockPrefix = "\\StringFileInfo\\" + IntToHex(lpTranslate[0].wLanguage, 4) + IntToHex(lpTranslate[0].wCodePage, 4) + "\\";

                        // Retrieve strings for the default language and code page

                        sSubBlock = sSubBlockPrefix + "Comments";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FComments = pcStringBuffer;

                        sSubBlock = sSubBlockPrefix + "CompanyName";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FCompanyName = pcStringBuffer;

                        sSubBlock = sSubBlockPrefix + "FileDescription";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FFileDescription = pcStringBuffer;

                        sSubBlock = sSubBlockPrefix + "FileVersion";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FFileVersion = pcStringBuffer;

                        sSubBlock = sSubBlockPrefix + "InternalName";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FInternalName = pcStringBuffer;

                        sSubBlock = sSubBlockPrefix + "LegalCopyright";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FLegalCopyright = pcStringBuffer;

                        sSubBlock = sSubBlockPrefix + "LegalTrademarks";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FLegalTrademarks = pcStringBuffer;

                        sSubBlock = sSubBlockPrefix + "OriginalFilename";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FOriginalFilename = pcStringBuffer;

                        sSubBlock = sSubBlockPrefix + "ProductName";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FProductName = pcStringBuffer;

                        sSubBlock = sSubBlockPrefix + "ProductVersion";
                        VerQueryValue(FileInfoData, sSubBlock.c_str(), (void**)(&pcStringBuffer), &uiInfoSize);
                        FProductVersion = pcStringBuffer;

                        FFileInfoValid = true;
                    }
                }

                // release the file information data
                SAFE_ARRAY_DELETE(FileInfoData);
            }
        }
    }
}
//---------------------------------------------------------------------------
// SetFilename
/**
 * Sets the filename that the control needs to retrieve version information for.
 * Then retrieves the version information and makes it available through the
 * controls properties.
 * @param   FileName the file to get version information from
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
void __fastcall KFileInfo::SetFilename(TFileName FileName)
{
    FFileName = FileName;
    GetFileVersionInformation();
}
//---------------------------------------------------------------------------
// Register
/**
 * Registers the control with the Borland Builder IDE
 * @author  Tony Thompson
 * @date    Created 1 August 2001
 */
//---------------------------------------------------------------------------
namespace Kfileinfo
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(KFileInfo)};
        RegisterComponents("Scorpio", classes, 0);
    }
}
//---------------------------------------------------------------------------

