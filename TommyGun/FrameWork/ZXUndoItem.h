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
#ifndef ZXUndoItemH
#define ZXUndoItemH
//---------------------------------------------------------------------------
#include "KXmlInfo.h"
#include "FrameWorkInterface.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
using namespace Interface;
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GUI
    {
        //---------------------------------------------------------------------------
        class ZXUndoItem
        {
        private:
            KXmlInfo            m_XmlInfo;

                    __fastcall  ZXUndoItem();

            String  __fastcall  GetDescription(void);
            String  __fastcall  GetPlugin(void);
            int     __fastcall  GetSize(void);

        public:
                    __fastcall  ZXUndoItem(const KXmlInfo& xmlInfo);
                    __fastcall  ZXUndoItem(const ZXUndoItem& undoItem);

            void    __fastcall  Restore(void);
            String  __property  Description = { read = GetDescription   };
            String  __property  Plugin      = { read = GetPlugin        };
            int     __property  Size        = { read = GetSize          };
        };
    }
}
//---------------------------------------------------------------------------
#endif

