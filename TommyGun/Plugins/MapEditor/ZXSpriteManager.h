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
#ifndef ZXSpriteManagerH
#define ZXSpriteManagerH
//- STD ---------------------------------------------------------------------
#include <map>
#include <vector>
//- VCL ---------------------------------------------------------------------
#include <Graphics.hpp>
//---------------------------------------------------------------------------
typedef Graphics::TBitmap*          ZXBitmap;
typedef std::map<String, ZXBitmap>  ZXBitmaps;
typedef ZXBitmaps::iterator         ZXBitmapsIterator;
//---------------------------------------------------------------------------
class ZXSpriteManager
{
private:
    TNotifyEvent                FOnClick;
    
    String                      m_sSelected;
    std::vector<String>         m_vNames;
    std::vector<ZXBitmap>       m_vBitmaps;
    std::vector<int>            m_vSubTypes;
    TImageList*                 m_pImageList;

    void            __fastcall  SetSelected(String sValue);
    void            __fastcall  ResizeBitmapVector(void);

public:
                    __fastcall  ZXSpriteManager();
                    __fastcall ~ZXSpriteManager();

    void            __fastcall  Init(TImageList* imageList) { m_pImageList = imageList; }
    void            __fastcall  Refresh(void);
    bool            __fastcall  Remove(const String& sName);
    bool            __fastcall  Rename(const String& sOldName, const String& sNewName);
    ZXBitmap        __fastcall  Find(const String& sName);
    int             __fastcall  IndexOf(const String& sName);
    unsigned int    __fastcall  Tiles(void) { return m_vNames.size(); }
    String          __fastcall  Name(unsigned int iIndex);
    void            __fastcall  Clear(void);
    void            __fastcall  GetSize(const String& sName, int& iWidth, int& iHeight);
    void            __fastcall  GetSize(const ZXBitmap Bitmap, int& iWidth, int& iHeight);
    void            __fastcall  GetScalar(float& dX, float& dY);

    __property      String      Selected    = { read = m_sSelected  , write = SetSelected   };
    __property  TNotifyEvent    OnClick     = { read = FOnClick     , write = FOnClick      };
};
//---------------------------------------------------------------------------
#endif
 
