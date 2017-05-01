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
#ifndef ZXToolInterfaceH
#define ZXToolInterfaceH
//---------------------------------------------------------------------------
#include "..\ZXImage.h"
//---------------------------------------------------------------------------
using namespace Scorpio;
//using namespace Imaging;
//---------------------------------------------------------------------------
class ZXToolInterface
{
private:
    bool                        m_bEnabled;

                    __fastcall  ZXToolInterface();

protected:
    String                      m_sName;

    virtual bool    __fastcall  DoMouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);
    virtual bool    __fastcall  DoMouseMove(ZXImage* Image, TShiftState Shift, int X, int Y);
    virtual bool    __fastcall  DoMouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);

public:
                    __fastcall  ZXToolInterface(const String sName);
    virtual         __fastcall ~ZXToolInterface();

            bool    __fastcall  MouseDown(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);
            bool    __fastcall  MouseMove(ZXImage* Image, TShiftState Shift, int X, int Y);
            bool    __fastcall  MouseUp(ZXImage* Image, TMouseButton Button, TShiftState Shift, int X, int Y);

            bool    __property  Enabled = { read = m_bEnabled, write = m_bEnabled   };
            String  __property  Name    = { read = m_sName                          };    
};
//---------------------------------------------------------------------------
#endif
