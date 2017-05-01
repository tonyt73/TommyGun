//---------------------------------------------------------------------------
#ifndef SoundsH
#define SoundsH
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
//-- APP --------------------------------------------------------------------
#include "PropertyObject.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GameEditor
    {
        class Sounds : public PropertyObject
        {
        private:
            struct TSoundInfo
            {
                AnsiString file;
                AnsiString name;
                AnsiString author;
                AnsiString description;
            };
            
        private:
            bool                    m_IsDirty;
            int                     m_PropertyNode;
            std::vector<TSoundInfo> m_AvailableSounds;
            std::vector<int>        m_GameSounds;
            TListView*              m_AvailableSfx;
            TListView*              m_GameSfx;

            bool    __fastcall      FindStr(const AnsiString& line, const AnsiString& subStr, AnsiString& value);

        public:
                    __fastcall      Sounds();
                    __fastcall     ~Sounds();
            void    __fastcall      Init(TListView* availableSfx, TListView* gameSfx);
            void    __fastcall      Add();
            void    __fastcall      Remove();
            void    __fastcall      Up();
            void    __fastcall      Down();
            void    __fastcall      UpdateList(int si = -1);

            // file
            bool    __fastcall      Load(KXmlInfo& xmlInfo);
            void    __fastcall      Save(KXmlInfo& xmlInfo);
            bool    __fastcall      IsDirty() { return m_IsDirty; }

            void    __fastcall      OnPropertyChanged(int node);
            void    __fastcall      OnPropertyRefresh() { }
        };
    }
}
//---------------------------------------------------------------------------
#endif
