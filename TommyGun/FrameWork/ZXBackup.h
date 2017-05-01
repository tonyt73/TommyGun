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
#ifndef ZXBackupH
#define ZXBackupH
//---------------------------------------------------------------------------
enum ZXBackupEvent  { beOnSave, beOnClose   };
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace Project
    {
        class ZXBackup
        {
        private:
            bool                m_bEnabled;
            bool                m_bOnSave;
            bool                m_bLimitFolders;
            int                 m_iFolderLimit;
            String              m_sProjectName;

            void    __fastcall  GetFolderDetails(const String& sFolder, int& iFiles, int& iSize);
            void    __fastcall  ReadSettings(void);
            bool    __fastcall  QueryBackup(ZXBackupEvent Event);
            String  __fastcall  GetBackupPath(const String& sFilename);
            void    __fastcall  PruneFolders(const String& sBackupPath);

        public:
                    __fastcall  ZXBackup();
                    __fastcall ~ZXBackup();

            void    __fastcall  Backup(const String& sProject, ZXBackupEvent Event);
            void    __fastcall  Restore(const String& sProject);
        };
    }
}
//---------------------------------------------------------------------------
#endif

