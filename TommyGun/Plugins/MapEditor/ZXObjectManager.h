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
#ifndef ZXObjectManagerH
#define ZXObjectManagerH
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
class ZXObjectManager
{
private:
    TNotifyEvent                FOnClick;
    
    String                      m_sSelected;
    std::vector<String>         m_vNames;
    std::vector<ZXBitmap>       m_vBitmaps;
    TImageList*                 m_pImageList;
    std::vector<TMapObject>     m_vObjects;

    void            __fastcall  SetSelected(String sValue);
    void            __fastcall  ResizeBitmapVector(void);
    void            __fastcall  SyncLists();

public:
                    __fastcall  ZXObjectManager();
                    __fastcall ~ZXObjectManager();

    void            __fastcall  Init(TImageList* imageList) { m_pImageList = imageList; }
    void            __fastcall  Refresh(void);
    bool            __fastcall  Remove(const String& sName);
    bool            __fastcall  Rename(const String& sOldName, const String& sNewName);
    ZXBitmap        __fastcall  Find(const String& sName);
    unsigned int    __fastcall  Objects(void) { return m_vNames.size(); }
    String          __fastcall  Name(unsigned int iIndex);
    void            __fastcall  Clear(void);
    void            __fastcall  GetSize(const String& sName, int& iWidth, int& iHeight);
    void            __fastcall  GetSize(const ZXBitmap Bitmap, int& iWidth, int& iHeight);
    void            __fastcall  GetObject(int iIndex, TMapObject& Object);
    void            __fastcall  GetObject(const String& sObject, TMapObject& Object);
    void            __fastcall  GetObjectNames(int iScreen, std::vector<String>& objectNames);
    void            __fastcall  SetObjectScreen(int iObject, int iScreen);
    void            __fastcall  MoveObject(int iIndex, int X, int Y);
    int             __fastcall  FindObject(int iScreen, int X, int Y);   
    int             __fastcall  FindObject(const String& sObject);   
    bool            __fastcall  Load(KXmlInfo& xmlInfo);
    void            __fastcall  Save(KXmlInfo& xmlInfo);
};
//---------------------------------------------------------------------------
#endif
 
