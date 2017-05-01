/*---------------------------------------------------------------------------

	(c) 2001 ResMed Ltd
    	97 Waterloo Road, North Ryde, 2113, Australia
      	Tel +61 2 9886 5000; Fax +61 9878 0120

-----------------------------------------------------------------------------

    $Workfile::   KFileInfo.h                                             $
    $Revision::   1.2                                                     $
    $Date::   May 09 2003 15:29:50                                        $
    $Author::   GavinT                                                    $

-----------------------------------------------------------------------------

    This file implements a VCL Component to access the file version information
    stored in Windows Binary files.

---------------------------------------------------------------------------*/
#ifndef FileInfoH
#define FileInfoH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
//#include "..\Common\Utility\Logging\RMessageLogger.h"
//#include "..\Common\Memory\SafeMacros.h"
//---------------------------------------------------------------------------
class PACKAGE KFileInfo : public TComponent
{
private:
    int             FBuildNumber;
    int             FReleaseNumber;
    int             FMajorVersion;
    int             FMinorVersion;

    String          FComments;          
    String          FCompanyName;
    String          FFileDescription;
    String          FFileVersion;
    String          FInternalName;
    String          FLegalCopyright;
    String          FLegalTrademarks;
    String          FOriginalFilename;
    String          FProductName;
    String          FProductVersion;

    TFileName       FFileName;
    bool            FFileInfoValid;

    void __fastcall GetFileVersionInformation(void);
    void __fastcall SetFilename( TFileName FileName );

public:

	__fastcall KFileInfo(TComponent* Owner);

__published:

    __property bool   FileInfoValid     = { read = FFileInfoValid                 };
    __property String FileName          = { read = FFileName, write = SetFilename };

    __property int    BuildNumber       = { read = FBuildNumber                   };
    __property int    ReleaseNumber     = { read = FReleaseNumber                 };
    __property int    MajorVersion      = { read = FMajorVersion                  };
    __property int    MinorVersion      = { read = FMinorVersion                  };

    __property String Comments          = { read = FComments                      };
    __property String CompanyName       = { read = FCompanyName                   };
    __property String FileDescription   = { read = FFileDescription               };
    __property String FileVersion       = { read = FFileVersion                   };
    __property String InternalName      = { read = FInternalName                  };
    __property String LegalCopyright    = { read = FLegalCopyright                };
    __property String LegalTrademarks   = { read = FLegalTrademarks               };
    __property String OriginalFilename  = { read = FOriginalFilename              };
    __property String ProductName       = { read = FProductName                   };
    __property String ProductVersion    = { read = FProductVersion                };

};// KFileInfo
//---------------------------------------------------------------------------
#endif//FileInfoH
