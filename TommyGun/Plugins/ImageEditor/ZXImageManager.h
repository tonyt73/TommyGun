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
#ifndef ZXImageManagerH
#define ZXImageManagerH
//---------------------------------------------------------------------------
#include "ZXImage.h"
#include "ZXPalette.h"
#include <KXmlInfo.h>
#include <FrameworkInterface.h>
//---------------------------------------------------------------------------
enum TZXChangeOperation { coNone, coAdded, coFrameAdded, coRemoved, coFrameRemoved, coChanged, coFrameChanged };
enum TZXMsgRecipenent   { mrCore, mrSubPlugins, mrBoth };
typedef void __fastcall (__closure *ZXImageChangedEvent)(const String& sName, const String& sOwner, TZXChangeOperation Operation);
typedef void __fastcall (__closure *ZXImageRenamedEvent)(const String& sOldName, const String& sNewName, const String& sOwner, int iIndex);
typedef void __fastcall (__closure *ZXPostMessage      )(TZXMsgRecipenent Recipenent, DWORD dwMsg, LPDATA lpData, DWORD dwParam, DWORD dwArg);

__declspec( dllexport ) class ZXImageManager
{
private:    // typedefs
    typedef struct
    {
        std::vector<ZXImage*>   vFrames;    // the list of images the type plugin owns
    } ZXFrames;
    typedef struct
    {
        String                  sOwner;     // image type signature of the owner
        std::vector<ZXFrames*>  vImages;    // the list of image frames the type plugin owns
    } ZXImageInfo;

private:    // events
    ZXImageChangedEvent         FOnImageChanged;
    ZXImageRenamedEvent         FOnImageRenamed;
    ZXPostMessage               FOnPostMessage;

private:    // member variables
    std::vector<ZXImageInfo*>   m_vImages;
    std::vector<ZXPalette*>     m_vPalettes;
    bool                        m_bDirty;
    bool                        m_bUndoInProgress;

private:    // member functions
    ZXPalette*  __fastcall  FindPalette(const String& sSignature) const;
    int         __fastcall  FindImageIndex(const ZXImageInfo* const pImageInfo, const ZXImage* const pImage) const;
    int         __fastcall  FindOwner(const String& sOwner) const;
   ZXImageInfo* __fastcall  FindImageInfo(const String& sOwner) const;
   ZXImageInfo* __fastcall  GetImageInfo(const String& sOwner);
    ZXImage*    __fastcall  CreateImage(const String& sOwner, const String& sPalSignature, int iWidth, int iHeight, bool bMasked, bool bCanResize);
    //int         __fastcall  AddImage(const String& sOwner, ZXImage* Image);
    bool        __fastcall  DoesOwnerExist(const String& sOwner) const;
    int         __fastcall  ImageIndex(const ZXImageInfo* ImageInfo, const String& sName) const;
    void        __fastcall  UndoImageReorder(KXmlInfo* xmlInfo);
    void        __fastcall  UndoImageCreate(KXmlInfo* xmlInfo);
    void        __fastcall  UndoImageRemoveFrame(KXmlInfo* xmlInfo);
    void        __fastcall  UndoImageRemoveAll(KXmlInfo* xmlInfo);
    void        __fastcall  UndoImageRename(KXmlInfo* xmlInfo);
    void        __fastcall  UndoImageClone(KXmlInfo* xmlInfo);
    void        __fastcall  UndoImageResize(KXmlInfo* xmlInfo);
    void        __fastcall  UndoImageMakeMask(KXmlInfo* xmlInfo);
    void        __fastcall  ApplyVersion_1_0_Fixes(KXmlInfo& xmlInfo, const String& sPalette);

public:     // public member functions
                __fastcall  ZXImageManager();
                __fastcall ~ZXImageManager();

    // XML loading/saving
    HRESULT     __fastcall  Save(KXmlInfo& xmlInfo, bool bCleanDirty = true);
    HRESULT     __fastcall  Load(KXmlInfo& xmlInfo);

    void        __fastcall  ClearImages(void);
    bool        __fastcall  DoesImageExist(const String& sType, const String& sName) const;
    int         __fastcall  AddImage(const String& sType, const String& sPalSignature, const String& sName, int iWidth, int iHeight, bool bMasked, ZXImage** pImage = NULL, bool bCanResize = false);
    int         __fastcall  CloneImage(const String& sType, const String& sName, unsigned int iIndex, int iFrame = -1);
    bool        __fastcall  RemoveImage(const String& sType, unsigned int iIndex, int iFrame = -1);
    bool        __fastcall  ReorderFrame(const String& sType, unsigned int iIndex, int iOldFrame, int iNewFrame);
    bool        __fastcall  ResizeImage(const String& sOwner,  ZXImage* pImage, int iLeft, int iTop, int iWidth, int iHeight);
    ZXImage*    __fastcall  GetImage(const String& sType, unsigned int iIndex, int iFrame);
    void        __fastcall  SetPalettes(std::vector<ZXPalette*>& vPalettes);
    ZXPalette*  __fastcall  GetPalette(int iPalette);
    ZXPalette*  __fastcall  GetPalette(const AnsiString& name);
    void        __fastcall  GetImageList(const String& sType, TStrings* pList);
    int         __fastcall  GetImageCount(const String& sType) const;
    int         __fastcall  GetFrameCount(const String& sType, int iIndex) const;
    bool        __fastcall  RenameImage(const String& sType, unsigned int iIndex, const String& sNewName);
    void        __fastcall  GetImageNames(std::vector<String>* vpNames, const String& sType, int iSubTypeFilter = -1);
    void        __fastcall  GetImageBitmaps(std::vector<Graphics::TBitmap*>* vpImages, const String& sType, int iSubTypeFilter = -1);
    void        __fastcall  GetImageSubTypes(std::vector<int>* vpSubTypes, const String& sType, int iSubTypeFilter = -1);
    void        __fastcall  GetImageFrameBitmaps(std::vector<Graphics::TBitmap*>* vpFrames, int iIndex, const String& sType);
    bool        __fastcall  IsDirty(void);
    bool        __fastcall  UndoRestore(KXmlInfo* xmlInfo);
    void        __fastcall  SetMaskMode(bool MaskOn);
    void        __fastcall  InvertMask(const String& sOwner,  ZXImage* pImage);
    bool        __fastcall  GenerateMask(const String& sOwner,  ZXImage* pImage, int BorderStyle, int iPaletteIndex);
    ZXImage*    __fastcall  GetPreviousFrame(ZXImage* pImage);
    int         __fastcall  GetSubType(const String& sType, unsigned int iIndex);
    void        __fastcall  SetSubType(const String& sType, unsigned int iIndex, int subType);

    __property  ZXImageChangedEvent OnImageChanged  = { read = FOnImageChanged  , write = FOnImageChanged   };
    __property  ZXImageRenamedEvent OnImageRenamed  = { read = FOnImageRenamed  , write = FOnImageRenamed   };
    __property  ZXPostMessage       OnPostMessage   = { read = FOnPostMessage   , write = FOnPostMessage    };
};
//---------------------------------------------------------------------------
#endif
