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
#ifndef ZXProjectManagerH
#define ZXProjectManagerH
//---------------------------------------------------------------------------
#include "FrameWorkInterface.h"
#include "ZXBackup.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace Project
    {
        enum TSaveQuery         { sqNone, sqSaved, sqCancelled };
        typedef struct
        {
            String          File;
            String          Machine;
            TDateTime       TimeStamp;
            bool            Exists;
        } TMRUProject;
        typedef std::vector<TMRUProject>        TMRUProjectsVector;
        typedef TMRUProjectsVector::iterator    TMRUProjectsVectorIterator;

        class ZXProjectManager
        {
        private:

            enum ZXFileErrorType { fetError, fetWarning, fetInfo };

            typedef struct
            {
                ZXFileErrorType     Type;
                String              Plugin;
                String              Message;
            } ZXFileMessage;
            typedef std::vector<ZXFileMessage>  ZXFileMessageVector;

        private:
            String                  m_sFilename;
            String                  m_sMachine;
            TMRUProjectsVector      m_MRUProjects;
            ZXFileMessageVector     m_FileMessages;
            KXmlInfo*               m_XmlInfo;
            KXmlInfo*               m_XmlDefaults;
            KXmlInfo*               m_XmlUpdate;
            DWORD                   m_dwVersion;             

            void        __fastcall  Clear               (void);
            bool        __fastcall  IsDirty             (void);
            void        __fastcall  UpdateTGRExtension  (void);
            void        __fastcall  AddProjectFileToMRU (const String& sFilename);
            String      __fastcall  GetMachine          (const String& sFile);
            void        __fastcall  LogFileError        (ZXFileErrorType MessageType, const String& sPlugin, String sErrorMessage);
            //void        __fastcall  DisplayFileMessages (void);
            void        __fastcall  LoadDefaultsXml     (const String& sMachine);
            void        __fastcall  BackupProjectFile   (void);
            void        __fastcall  OnQuerySave         (bool &bSaved);
            void        __fastcall  OnQueryProjectFolder(String& sFolder);
            void        __fastcall  SaveMRU             (void);
            bool        __fastcall  Delete              (int iProject);
            bool        __fastcall  CopyFiles           (String sOldName, String sNewName);

        public:
                        __fastcall  ZXProjectManager    ();
                        __fastcall ~ZXProjectManager    ();

            bool        __fastcall  Initialize          (HINSTANCE hInstance);
            void        __fastcall  Release             (void);

            TSaveQuery  __fastcall  QuerySave           (void);
            void        __fastcall  New                 (const String& sProjectFile, const String& sMachine);
            bool        __fastcall  Load                (const String& sFile);
            void        __fastcall  Reload              (void);
            bool        __fastcall  Merge               (const String& sFile);
            bool        __fastcall  Save                (const String& sFile);
            bool        __fastcall  LoadProject         (bool bClearProject);
            bool        __fastcall  SaveProject         (void);
            bool        __fastcall  Save                (void);
            bool        __fastcall  Close               (void);
            void        __fastcall  Copy                (String sOldName, String sNewName);
            void        __fastcall  Remove              (String sProjectName, bool bRemoveFolder);
            void        __fastcall  Rename              (String sOldName, String sNewName);
            void        __fastcall  Restore             (String sProjectName);
            void        __fastcall  GetMRUList          (TMRUProjectsVector& mruProjects, bool bGetMachine);
            KXmlInfo*   __fastcall  GetXmlInfo          (void);
            bool        __fastcall  SortProjects        (int iColumn);
    static  bool        __fastcall  DeleteFolder        (String sFolder, bool bRemoveFolder = true);

            __property  String      ProjectFile         = { read = m_sFilename  };
            __property  DWORD       ProjectVersion      = { read = m_dwVersion  };
        };
    }
}
//---------------------------------------------------------------------------
extern Scorpio::Project::ZXProjectManager g_ProjectManager;
//---------------------------------------------------------------------------
#endif
