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
#pragma hdrstop
//---------------------------------------------------------------------------
#include "..\..\SafeMacros.h"
#include "..\Include\CustomEvents.h"
//---------------------------------------------------------------------------
//#include "ZXLogFile.h"
#include "ZXImageManager.h"
#include "ZXPalette.h"
#include "ZXImageNotifications.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXImageManager::ZXImageManager()
: m_bUndoInProgress(false)
{
}
//---------------------------------------------------------------------------
__fastcall ZXImageManager::~ZXImageManager()
{
    m_bUndoInProgress = true;
    ClearImages();
    m_bUndoInProgress = false;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::ClearImages(void)
{
    while(m_vImages.size())
    {
        RemoveImage(m_vImages[0]->sOwner, 0);
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageManager::DoesImageExist(const String& sOwner, const String& sName) const
{
    bool bFound = false;
    for (unsigned int i = 0; i < m_vImages.size() && false == bFound; ++i)
    {
        if (sOwner == m_vImages[i]->sOwner)
        {
            for (unsigned int j = 0; j < m_vImages[i]->vImages.size() && 0 < m_vImages[i]->vImages[j]->vFrames.size() && false == bFound; j++)
            {
                bFound = m_vImages[i]->vImages[j]->vFrames[0]->Name == sName;
            }
        }
    }
    return bFound;
}
//---------------------------------------------------------------------------
int __fastcall ZXImageManager::ImageIndex(const ZXImageInfo* ImageInfo, const String& sName) const
{
    int iIndex = -1;
    for (unsigned int i = 0; i < ImageInfo->vImages.size() && -1 == iIndex; i++)
    {
        if (sName == ImageInfo->vImages[i]->vFrames[0]->Name)
        {
            iIndex = i;
        }
    }
    return iIndex;
}
//---------------------------------------------------------------------------
/*int __fastcall ZXImageManager::AddImage(const String& sOwner, ZXImage* Image)
{
    int iImage = -1;
    if (true == SAFE_PTR(Image))
    {
        ZXImageInfo* pImageInfo = GetImageInfo(sOwner);
        if (true == SAFE_PTR(pImageInfo))
        {
            int iImageIndex = ImageIndex(pImageInfo, Image->Name);
            ZXFrames* Frames = NULL;
            if (-1 != iImageIndex)
            {
                Frames = pImageInfo->vImages[iImageIndex];
            }
            else
            {
                Frames = new ZXFrames();
                pImageInfo->vImages.push_back(Frames);
            }
            if (true == SAFE_PTR(Frames))
            {
                Frames->vFrames.push_back(Image);
                m_bDirty = true;
            }
        }
    }
    return iImage;
}*/
//---------------------------------------------------------------------------
bool __fastcall ZXImageManager::RemoveImage(const String& sOwner, unsigned int iIndex, int iFrame)
{
    bool bRemoved = false;
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo))
    {
        if (iIndex < pImageInfo->vImages.size())
        {
            String sName = pImageInfo->vImages[iIndex]->vFrames[0]->Name;
            String sOwner = pImageInfo->sOwner;
            String sPalSignature;
            try
            {
                sPalSignature = pImageInfo->vImages[iIndex]->vFrames[0]->Palette->Signature;
            }
            catch(EAccessViolation&)
            {
                // palettes have being destroyed
            }
            int iWidth = pImageInfo->vImages[iIndex]->vFrames[0]->Width;
            int iHeight = pImageInfo->vImages[iIndex]->vFrames[0]->Height;
            bool bMasked = pImageInfo->vImages[iIndex]->vFrames[0]->IsMasked;
            if (-1 == iFrame)
            {
                // remove all the frames of the image
                if (FOnPostMessage && !m_bUndoInProgress)
                {
                    KXmlInfo Undo;
                    Undo.Add("Operation"    , "ImageRemoveAll");
                    Undo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
                    Undo.Add("Description"  , "Remove Image (" + sName + ") ");
                    Undo.Add("Owner"        , sOwner);
                    Undo.Add("PalSignature" , sPalSignature);
                    Undo.Add("Name"         , sName  );
                    Undo.Add("Width"        , iWidth );
                    Undo.Add("Height"       , iHeight);
                    Undo.Add("Masked"       , bMasked);
                    Undo.Add("Undo"         , true);
                    Undo.Add("Index"        , iIndex);

                    // free all the frames
                    for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
                    {
                        // save the undo frames
                        KXmlInfo Frame;
                        Frame.Reset();
                        Frame.SetName("Frame" + IntToStr(f));
                        pImageInfo->vImages[iIndex]->vFrames[f]->Save(Frame, false);
                        Undo.Add(Frame);
                        SAFE_DELETE(pImageInfo->vImages[iIndex]->vFrames[f]);
                    }
                    FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                    Undo.GetNode("Undo")->SetText(false);
                    FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
                }
                // free the frame list
                SAFE_DELETE(pImageInfo->vImages[iIndex]);
                pImageInfo->vImages.erase(pImageInfo->vImages.begin() + iIndex);
                if (FOnImageChanged)
                {
                    FOnImageChanged(sName, sOwner, coRemoved);
                }
            }
            else
            {
                if (0 <= iFrame && iFrame < (int)pImageInfo->vImages[iIndex]->vFrames.size())
                {
                    // remove the selected frame
                    String sName = pImageInfo->vImages[iIndex]->vFrames[0]->Name;
                    KXmlInfo Undo;
                    Undo.Add("Operation"    , "ImageRemoveFrame");
                    Undo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
                    Undo.Add("Description"  , "Remove Frame (" + sName + ") ");
                    Undo.Add("Owner"        , sOwner);
                    Undo.Add("PalSignature" , sPalSignature);
                    Undo.Add("Name"         , sName  );
                    Undo.Add("Width"        , iWidth );
                    Undo.Add("Height"       , iHeight);
                    Undo.Add("Masked"       , bMasked);
                    Undo.Add("Undo"         , true);
                    Undo.Add("Index"        , iIndex);
                    Undo.Add("Frame"        , iFrame);
                    KXmlInfo Frame;
                    Frame.Reset();
                    Frame.SetName("Frame0");
                    pImageInfo->vImages[iIndex]->vFrames[iFrame]->Save(Frame, false);
                    Undo.Add(Frame);
                    if (FOnPostMessage && !m_bUndoInProgress)
                    {
                        FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                        Undo.GetNode("Undo")->SetText(false);
                        FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
                    }
                    if (FOnImageChanged)
                    {
                        FOnImageChanged(sName, sOwner, coFrameRemoved);
                    }
                    SAFE_DELETE(pImageInfo->vImages[iIndex]->vFrames[iFrame]);
                    pImageInfo->vImages[iIndex]->vFrames.erase(pImageInfo->vImages[iIndex]->vFrames.begin() + iFrame);
                }
            }
            bRemoved = true;
            m_bDirty = true;
        }
        if (0 == pImageInfo->vImages.size())
        {
            // no more images/frames so remove the images object
            std::vector<ZXImageInfo*>::iterator it = std::find(m_vImages.begin(), m_vImages.end(), pImageInfo);
            if (it != m_vImages.end())
            {
                m_vImages.erase(it);
            }
            else
            {
                // TODO: assert object not found, thats crap!
            }
        }
    }
    return bRemoved;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageManager::ReorderFrame(const String& sOwner, unsigned int iIndex, int iOldFrame, int iNewFrame)
{
    bool bReordered = false;
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo))
    {
        if (iIndex < pImageInfo->vImages.size())
        {
            if
            (
                iOldFrame < (int)pImageInfo->vImages[iIndex]->vFrames.size()
                &&
                iNewFrame < (int)pImageInfo->vImages[iIndex]->vFrames.size()
            )
            {
                // can order so reorder them
                KXmlInfo Undo;
                Undo.Add("Operation", "ImageFrameReorder");
                Undo.Add("Plugin", "Image Editor (" + sOwner + ")");
                Undo.Add("Description", "Reorder Frame (" + pImageInfo->vImages[iIndex]->vFrames[iOldFrame]->Name + ") " + IntToStr(iOldFrame) + " to " + IntToStr(iNewFrame));
                Undo.Add("Owner", sOwner  );
                Undo.Add("Index", iIndex  );
                Undo.Add("OldFrame", iOldFrame);
                Undo.Add("NewFrame", iNewFrame);
                if (FOnPostMessage && !m_bUndoInProgress && iOldFrame != iNewFrame)
                {
                    FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                }
                ZXImage* tmpFrame = pImageInfo->vImages[iIndex]->vFrames[iOldFrame];
                pImageInfo->vImages[iIndex]->vFrames[iOldFrame] = pImageInfo->vImages[iIndex]->vFrames[iNewFrame];
                pImageInfo->vImages[iIndex]->vFrames[iNewFrame] = tmpFrame;
                if (FOnPostMessage && !m_bUndoInProgress && iOldFrame != iNewFrame)
                {
                    Undo.GetNode("OldFrame")->SetText(iNewFrame);
                    Undo.GetNode("NewFrame")->SetText(iOldFrame);
                    FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
                }
                m_bDirty = true;
                bReordered = true;
            }
        }
    }
    return bReordered;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageManager::ResizeImage(const String& sOwner, ZXImage* pImage, int iLeft, int iTop, int iWidth, int iHeight)
{
    bool bResized = false;
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo))
    {
        int iIndex = -1;
        for (unsigned int i = 0; i < pImageInfo->vImages.size() && iIndex == -1; i++)
        {
            for (unsigned int f = 0; f < pImageInfo->vImages[i]->vFrames.size(); f++)
            {
                if (pImageInfo->vImages[i]->vFrames[f] == pImage)
                {
                    iIndex = i;
                    break;
                }
            }
        }

        if (0 <= iIndex && iIndex < (int)pImageInfo->vImages.size())
        {
            String sName = pImageInfo->vImages[iIndex]->vFrames[0]->Name;
            String sOwner = pImageInfo->sOwner;
            String sPalSignature;
            try
            {
                sPalSignature = pImageInfo->vImages[iIndex]->vFrames[0]->Palette->Signature;
            }
            catch(EAccessViolation&)
            {
                // palettes have being destoryed
            }
            int iOldWidth = pImageInfo->vImages[iIndex]->vFrames[0]->Width;
            int iOldHeight = pImageInfo->vImages[iIndex]->vFrames[0]->Height;
            bool bMasked = pImageInfo->vImages[iIndex]->vFrames[0]->IsMasked;
            // remove all the frames of the image
            if (FOnPostMessage && !m_bUndoInProgress)
            {
                KXmlInfo Undo;
                Undo.Add("Operation"    , "ImageResize");
                Undo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
                Undo.Add("Description"  , "Resize Image (" + sName + ") from " + IntToStr(iOldWidth) + "x" + IntToStr(iOldHeight) + " to " + IntToStr(iWidth) + "x" + IntToStr(iHeight) );
                Undo.Add("Owner"        , sOwner);
                Undo.Add("Name"         , sName  );
                Undo.Add("Width"        , iOldWidth );
                Undo.Add("Height"       , iOldHeight);
                Undo.Add("Index"        , iIndex);

                // free all the frames
                for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
                {
                    // save the undo frames
                    KXmlInfo Frame;
                    Frame.Reset();
                    Frame.SetName("Frame" + IntToStr(f));
                    pImageInfo->vImages[iIndex]->vFrames[f]->Save(Frame, false);
                    Undo.Add(Frame);
                }
                FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
            }
            for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
            {
                pImageInfo->vImages[iIndex]->vFrames[f]->Resize(iLeft, iTop, iWidth, iHeight);
            }

            if (FOnPostMessage && !m_bUndoInProgress)
            {
                KXmlInfo Redo;
                Redo.Add("Operation"    , "ImageResize");
                Redo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
                Redo.Add("Description"  , "Resize Image (" + sName + ") from " + IntToStr(iWidth) + "x" + IntToStr(iHeight) + " to " + IntToStr(iOldWidth) + "x" + IntToStr(iOldHeight));
                Redo.Add("Owner"        , sOwner);
                Redo.Add("Name"         , sName  );
                Redo.Add("Width"        , iWidth );
                Redo.Add("Height"       , iHeight);
                Redo.Add("Index"        , iIndex);
                for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
                {
                    KXmlInfo Frame;
                    Frame.Reset();
                    Frame.SetName("Frame" + IntToStr(f));
                    pImageInfo->vImages[iIndex]->vFrames[f]->Save(Frame, false);
                    Redo.Add(Frame);
                }
                FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Redo, utRedo, 0);
            }
            bResized = true;
            m_bDirty = true;
        }
    }
    return bResized;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageManager::RenameImage(const String& sOwner, unsigned int iIndex, const String& sNewName)
{
    bool bRenamed = false;
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo))
    {
        if (iIndex < pImageInfo->vImages.size())
        {
            String sOldName;
            if (0 < pImageInfo->vImages[iIndex]->vFrames.size())
            {
                sOldName = pImageInfo->vImages[iIndex]->vFrames[0]->Name;
            }
            // rename all the frames in the image
            for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
            {
                //String sOldName = pImageInfo->vImages[iIndex]->vFrames[f]->Name;
                pImageInfo->vImages[iIndex]->vFrames[f]->Name = sNewName;
            }
            KXmlInfo Undo;
            Undo.Add("Operation"    , "ImageRename");
            Undo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
            Undo.Add("Description"  , "Rename " + sOwner + " (" + sOldName + " to " + sNewName + ")");
            Undo.Add("Owner"        , sOwner);
            Undo.Add("Name"         , sOldName);
            Undo.Add("Index"        , iIndex);
            if (FOnPostMessage && !m_bUndoInProgress)
            {
                FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                Undo.GetNode("Name")->SetText(sNewName);
                FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
            }
            if (FOnImageRenamed)
            {
                FOnImageRenamed(sOldName, sNewName, sOwner, iIndex);
            }
            bRenamed = true;
            m_bDirty = true;
        }
    }
    return bRenamed;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageManager::GenerateMask(const String& sOwner,  ZXImage* pImage, int BorderStyle, int iPaletteIndex)
{
    bool bGenerated = false;
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo))
    {
        // find the image set
        int iIndex = -1;
        for (unsigned int i = 0; i < pImageInfo->vImages.size() && iIndex == -1; i++)
        {
            for (unsigned int f = 0; f < pImageInfo->vImages[i]->vFrames.size(); f++)
            {
                if (pImageInfo->vImages[i]->vFrames[f] == pImage)
                {
                    iIndex = i;
                    break;
                }
            }
        }

        // generate the masks for all frames
        if (0 <= iIndex && iIndex < (int)pImageInfo->vImages.size())
        {
            String sName = pImageInfo->vImages[iIndex]->vFrames[0]->Name;
            String sOwner = pImageInfo->sOwner;
            String sPalSignature;
            try
            {
                sPalSignature = pImageInfo->vImages[iIndex]->vFrames[0]->Palette->Signature;
            }
            catch(EAccessViolation&)
            {
                // palettes have being destoryed
            }
            bool bMasked = pImageInfo->vImages[iIndex]->vFrames[0]->IsMasked;
            // remove all the frames of the image
            if (FOnPostMessage && !m_bUndoInProgress)
            {
                KXmlInfo Undo;
                Undo.Add("Operation"    , "ImageMakeMask");
                Undo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
                Undo.Add("Description"  , "Generate Mask for Image: " + sName);
                Undo.Add("Owner"        , sOwner);
                Undo.Add("Name"         , sName  );
                Undo.Add("Index"        , iIndex);

                // save the undo frames
                for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
                {
                    KXmlInfo Frame;
                    Frame.Reset();
                    Frame.SetName("Frame" + IntToStr(f));
                    pImageInfo->vImages[iIndex]->vFrames[f]->Save(Frame, false);
                    Undo.Add(Frame);
                }
                FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
            }
            for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
            {
                pImageInfo->vImages[iIndex]->vFrames[f]->GenerateMask(BorderStyle, iPaletteIndex);
            }

            if (FOnPostMessage && !m_bUndoInProgress)
            {
                KXmlInfo Redo;
                Redo.Add("Operation"    , "ImageMakeMask");
                Redo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
                Redo.Add("Description"  , "Generate Mask for Image: " + sName);
                Redo.Add("Owner"        , sOwner);
                Redo.Add("Name"         , sName );
                Redo.Add("Index"        , iIndex);
                for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
                {
                    KXmlInfo Frame;
                    Frame.Reset();
                    Frame.SetName("Frame" + IntToStr(f));
                    pImageInfo->vImages[iIndex]->vFrames[f]->Save(Frame, false);
                    Redo.Add(Frame);
                }
                FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Redo, utRedo, 0);
            }
            bGenerated = true;
            m_bDirty = true;
        }
    }
    return bGenerated;
}
//---------------------------------------------------------------------------
ZXImage* __fastcall ZXImageManager::GetImage(const String& sOwner, unsigned int iIndex, int iFrame)
{
    ZXImage* pImage = NULL;
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo))
    {
        if (iIndex < pImageInfo->vImages.size())
        {
            if (iFrame == -1)
            {
                iFrame = pImageInfo->vImages[iIndex]->vFrames.size() - 1;
            }
            if (0 <= iFrame && iFrame < (int)pImageInfo->vImages[iIndex]->vFrames.size())
            {
                pImage = pImageInfo->vImages[iIndex]->vFrames[iFrame];
            }
        }
    }
    return pImage;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::SetPalettes(std::vector<ZXPalette*>& vPalettes)
{
    m_vPalettes.assign(vPalettes.begin(), vPalettes.end());
}
//---------------------------------------------------------------------------
int __fastcall ZXImageManager::FindOwner(const String& sOwner) const
{
    for (unsigned int i = 0; i < m_vImages.size(); i++)
    {
        if (m_vImages[i]->sOwner == sOwner)
        {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
ZXImageManager::ZXImageInfo* __fastcall ZXImageManager::FindImageInfo(const String& sOwner) const
{
    ZXImageInfo* pImageInfo = NULL;
    for (unsigned int i = 0; i < m_vImages.size() && NULL == pImageInfo; i++)
    {
        if (m_vImages[i]->sOwner == sOwner)
        {
            pImageInfo = m_vImages[i];
        }
    }
    return pImageInfo;
}
//---------------------------------------------------------------------------
ZXImageManager::ZXImageInfo* __fastcall ZXImageManager::GetImageInfo(const String& sOwner)
{
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (false == SAFE_PTR(pImageInfo))
    {
        try
        {
            pImageInfo = new ZXImageInfo();
            pImageInfo->sOwner = sOwner;
            m_vImages.push_back(pImageInfo);
        }
        catch(EOutOfMemory&)
        {
            pImageInfo = NULL;
        }
    }
    return pImageInfo;
}
//---------------------------------------------------------------------------
ZXPalette* __fastcall ZXImageManager::FindPalette(const String& sSignature) const
{
    ZXPalette* pPalette = NULL;
    for (unsigned int i = 0; i < m_vPalettes.size() && NULL == pPalette; i++)
    {
        String sig = m_vPalettes[i]->Signature;
        if (sSignature == sig)
        {
            pPalette = m_vPalettes[i];
        }
    }
    return pPalette;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageManager::Save(KXmlInfo& xmlInfo, bool bCleanDirty)
{
    bool bSaved = true;
    KXmlInfo* EditorNode;
    if (xmlInfo.Find(EditorNode, "ImageEditor"))
    {
        xmlInfo.Remove(EditorNode);
    }

    KXmlInfo ImageEditor("ImageEditor");
    // create a palette node
    KXmlInfo Palettes("Palettes");
    for (int i = 0; i < (int)m_vPalettes.size(); i++)
    {
        m_vPalettes[i]->Save(Palettes);
    }
    ImageEditor.Add(Palettes);

    // create an image node
    KXmlInfo Images("Images");
    // save all the image types
    for (unsigned int i = 0; i < m_vImages.size(); i++)
    {
        KXmlInfo Image;
        Images.Reset();
        Images.SetName("Images");
        // write the owner of the images
        Images.Add("Type", m_vImages[i]->sOwner);
        for (unsigned int s = 0; s < m_vImages[i]->vImages.size() && true == bSaved; s++)
        {
            KXmlInfo Frame;
            Image.Reset();
            Image.SetName("Image");
            // write out the frames of the image
            for (unsigned int f = 0; f < m_vImages[i]->vImages[s]->vFrames.size() && true == bSaved; f++)
            {
                // get the images bitmap
                ZXImage* pImage = m_vImages[i]->vImages[s]->vFrames[f];
                Frame.Reset();
                Frame.SetName("Frame");
                if (true == SAFE_PTR(pImage))
                {
                    // save the images bitmap to the xml object
                    bSaved = pImage->Save(Frame, bCleanDirty);
                }
                Image.Add(Frame);
            }
            Images.Add(Image);
        }
        ImageEditor.Add(Images);
    }
    xmlInfo.Add(ImageEditor);
    if (bCleanDirty)
    {
        m_bDirty = false;
    }
    return bSaved ? S_OK : S_FALSE;
}
//---------------------------------------------------------------------------
HRESULT __fastcall ZXImageManager::Load(KXmlInfo& xmlInfo)
{
    bool bLoaded = false;
    m_bUndoInProgress = true;
    // find the image editor node
    String sVersion = "1.0";
    KXmlInfo* VersionNode;
    if (xmlInfo.Find(VersionNode, "Version"))
    {
        sVersion = VersionNode->GetText();
    }

    KXmlInfo* EditorNode;
    if (xmlInfo.Find(EditorNode, "ImageEditor"))
    {
        bLoaded = true;
        KXmlInfo* PalettesNode = EditorNode->GetNode("Palettes");
        if (true == SAFE_PTR(PalettesNode))
        {
            // loop through the palettes and load the applicable data
            for (KXmlNodes::iterator it = PalettesNode->begin(); it != PalettesNode->end(); it++)
            {
                KXmlInfo* pName = (*it)->GetNode("Name");
                if (true == SAFE_PTR(pName))
                {
                    ZXPalette*  pPalette = FindPalette(String(pName->GetText()));
                    if (true == SAFE_PTR(pPalette))
                    {
                        pPalette->Load(*(*it));
                    }
                }
            }
        }

        KXmlInfo* node = NULL;
        // load the image lists (loop thru "Images" nodes)
        for (KXmlNodes::iterator it = EditorNode->begin(); it != EditorNode->end(); it++)
        {
            // get the type of the image list
            node = (*it)->GetNode("Type");

            if (node)
            {
                String sOwner = node->GetText();
                // loop through the "Image" nodes
                for (KXmlNodes::iterator itI = (*it)->begin(); itI != (*it)->end(); itI++)
                {
                    if ((*itI)->GetName() == "Image")
                    {
                        // each image has 1 - n frames
                        for (KXmlNodes::iterator itF = (*itI)->begin(); itF != (*itI)->end(); itF++)
                        {
                            int iWidth      = 0;
                            int iHeight     = 0;
                            String sPalette = "";
                            String sName    = "";
                            bool bIsMasked  = false;
                            // get the width, height, palette and mask properties
                            KXmlInfo* nWidth    = (*itF)->GetNode("Width");
                            KXmlInfo* nHeight   = (*itF)->GetNode("Height");
                            KXmlInfo* nPalette  = (*itF)->GetNode("Palette");
                            KXmlInfo* nName     = (*itF)->GetNode("Name");
                            KXmlInfo* nIsMasked = (*itF)->GetNode("IsMasked");
                            if (nWidth && nHeight && nPalette && nIsMasked)
                            {
                                iWidth      = nWidth->GetInt();
                                iHeight     = nHeight->GetInt();
                                sPalette    = nPalette->GetText();
                                sName       = nName->GetText();
                                bIsMasked   = nIsMasked->GetBool();

                                ZXImage* image = NULL;
                                AddImage(sOwner, sPalette, sName, iWidth, iHeight, bIsMasked, &image);
                                if (true == SAFE_PTR(image))
                                {
                                    bLoaded = image->Load(*(*itF), true, sVersion);
                                }
                            }
                            else
                            {
                                bLoaded = false;
                            }
                        }
                    }
                }
            }
        }
    }
    m_bUndoInProgress = false;
    m_bDirty = false;
    return bLoaded ? S_OK : S_FALSE;
}
//---------------------------------------------------------------------------
ZXImage* __fastcall ZXImageManager::CreateImage(const String& sOwner, const String& sPalSignature, int iWidth, int iHeight, bool bMasked, bool bCanResize)
{
    ZXImage* pImage = NULL;
    ZXPalette* pPalette = FindPalette(sPalSignature);
    if (true == SAFE_PTR(pPalette))
    {
        try
        {
            pImage = new ZXImage(iWidth, iHeight, bMasked, pPalette, bCanResize);
        }
        catch(EOutOfMemory&)
        {
            pImage = NULL;
        }
    }
    return pImage;
}
//---------------------------------------------------------------------------
int __fastcall ZXImageManager::AddImage(const String& sOwner, const String& sPalSignature, const String& sName, int iWidth, int iHeight, bool bMasked, ZXImage** pZxImage, bool bCanResize)
{
    int iIndex = -1;
    ZXImage* pImage = CreateImage(sOwner, sPalSignature, iWidth, iHeight, bMasked, bCanResize);
    if (true == SAFE_PTR(pImage))
    {
        if (pZxImage)
        {
            *pZxImage = pImage;
        }
        pImage->Name = sName;
        ZXImageInfo* pImageInfo = GetImageInfo(sOwner);
        if (true == SAFE_PTR(pImageInfo))
        {
            ZXFrames* Frames = NULL;
            if (false == DoesImageExist(sOwner, sName))
            {
                KXmlInfo Undo;
                Undo.Add("Operation"    , "ImageCreate");
                Undo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
                Undo.Add("Description"  , "Create Image (" + sName + ") ");
                Undo.Add("Owner"        , sOwner);
                Undo.Add("PalSignature" , sPalSignature);
                Undo.Add("Name"         , sName  );
                Undo.Add("Width"        , iWidth );
                Undo.Add("Height"       , iHeight);
                Undo.Add("Masked"       , bMasked);
                Undo.Add("Undo"         , true);
                Undo.Add("Index"        , pImageInfo->vImages.size());
                Undo.Add("Frame"        , -1);
                if (FOnPostMessage && !m_bUndoInProgress)
                {
                    FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                    Undo.GetNode("Undo")->SetText(false);
                    FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
                }
                // add a new image, first frame
                Frames = new ZXFrames();
                pImageInfo->vImages.push_back(Frames);
                Frames->vFrames.push_back(pImage);
            }
            else
            {
                KXmlInfo Undo;
                Undo.Add("Operation"    , "ImageCreate");
                Undo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
                Undo.Add("Description"  , "Create New Frame (" + sName + " : " + IntToStr(Frames) + ")");
                Undo.Add("Owner"        , sOwner);
                Undo.Add("PalSignature" , sPalSignature);
                Undo.Add("Name"         , sName  );
                Undo.Add("Width"        , iWidth );
                Undo.Add("Height"       , iHeight);
                Undo.Add("Masked"       , bMasked);
                Undo.Add("Undo"         , true);
                Undo.Add("Index"        , FindOwner(sOwner));
                Undo.Add("Frame"        , pImageInfo->vImages.size());
                Frames = pImageInfo->vImages[ImageIndex(pImageInfo, sName)];
                pImage->MaskMode = pImageInfo->vImages[0]->vFrames[0]->MaskMode;
                // add a new frame to an existing image
                Frames->vFrames.push_back(pImage);
                if (FOnPostMessage && !m_bUndoInProgress)
                {
                    FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                    Undo.GetNode("Undo")->SetText(false);
                    FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
                }
            }
            m_bDirty = true;
            iIndex = FindImageIndex(GetImageInfo(sOwner), pImage);
            if (-1 != iIndex && FOnImageChanged)
            {
                FOnImageChanged(sName, sOwner, coAdded);
            }
        }
        else
        {
            SAFE_DELETE(pImageInfo);
        }
    }
    return iIndex;
}
//---------------------------------------------------------------------------
int __fastcall ZXImageManager::CloneImage(const String& sOwner, const String& sName, unsigned int iIndex, int iFrame)
{
    int iCloneIndex = -1;
    int iCloneFrame = -1;
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo))
    {
        if (iIndex < pImageInfo->vImages.size())
        {
            if (-1 == iFrame)
            {
                // clone all frames of the image
                ZXFrames* Frames = new ZXFrames();
                pImageInfo->vImages.push_back(Frames);
                for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
                {
                    ZXImage* pOriginalImage = pImageInfo->vImages[iIndex]->vFrames[f];
                    if (true == SAFE_PTR(pOriginalImage) && true == SAFE_PTR(pOriginalImage->Palette))
                    {
                        ZXImage* pImage = CreateImage(sOwner, pOriginalImage->Palette->Signature, pOriginalImage->Width, pOriginalImage->Height, pOriginalImage->IsMasked, pOriginalImage->CanResize);
                        if (true == SAFE_PTR(pImage))
                        {
                           *pImage = *pOriginalImage;
                            Frames->vFrames.push_back(pImage);
                            pImage->Name = sName;
                            iCloneIndex = FindImageIndex(pImageInfo, pImage);
                            m_bDirty = true;
                        }
                    }
                }
                if (-1 != iCloneIndex && FOnImageChanged)
                {
                    FOnImageChanged(sName, sOwner, coAdded);
                }
            }
            else
            {
                // clone only the frame
                if (0 <= iFrame && iFrame < (int)pImageInfo->vImages[iIndex]->vFrames.size())
                {
                    // only clone the selected frame
                    ZXImage* pOriginalImage = pImageInfo->vImages[iIndex]->vFrames[iFrame];
                    if (true == SAFE_PTR(pOriginalImage) && true == SAFE_PTR(pOriginalImage->Palette))
                    {
                        ZXImage* pImage = CreateImage(sOwner, pOriginalImage->Palette->Signature, pOriginalImage->Width, pOriginalImage->Height, pOriginalImage->IsMasked, pOriginalImage->CanResize);
                        if (true == SAFE_PTR(pImage))
                        {
                           *pImage = *pOriginalImage;
                            iCloneFrame = pImageInfo->vImages[iIndex]->vFrames.size();
                            pImageInfo->vImages[iIndex]->vFrames.push_back(pImage);
                            pImage->Name = sName;
                            iCloneIndex = FindImageIndex(pImageInfo, pImage);
                            m_bDirty = true;
                        }
                    }
                }
                if (-1 != iCloneIndex && FOnImageChanged)
                {
                    FOnImageChanged(sName, sOwner, coFrameAdded);
                }
            }
            if (FOnPostMessage && !m_bUndoInProgress)
            {
                // save all the frames
                KXmlInfo Undo;
                Undo.Add("Operation"    , "ImageClone");
                Undo.Add("Plugin"       , "Image Editor (" + sOwner + ")");
                if (iFrame == -1)
                {
                    Undo.Add("Description"  , "Clone " + sOwner + " (" + sName + ")");
                }
                else
                {
                    Undo.Add("Description"  , "Clone " + sOwner + " (" + sName + ", Frame: " + IntToStr(iFrame) + ")");
                }
                Undo.Add("Owner"        , sOwner);
                Undo.Add("Name"         , sName);
                Undo.Add("Index"        , iIndex);
                Undo.Add("CloneIndex"   , iCloneIndex);
                Undo.Add("CloneFrame"   , iCloneFrame);
                Undo.Add("Frame"        , iFrame);
                Undo.Add("Undo"         , true);
                FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utUndo, 0);
                Undo.GetNode("Undo")->SetText(false);
                FOnPostMessage(mrCore, TZXN_XML_UNDO_ADD, (LPDATA)&Undo, utRedo, 0);
            }
        }
    }
    return iCloneIndex;
}
//---------------------------------------------------------------------------
int __fastcall ZXImageManager::FindImageIndex(const ZXImageInfo* const pImageInfo, const ZXImage* const pImage) const
{
    int iImageIndex = -1;
    if (true == SAFE_PTR(pImageInfo))
    {
        for (unsigned int i = 0; i < pImageInfo->vImages.size() && -1 == iImageIndex; i++)
        {
            // search the images frames
            for (unsigned int f = 0; f < pImageInfo->vImages[i]->vFrames.size() && -1 == iImageIndex; f++)
            {
                if (pImageInfo->vImages[i]->vFrames[f] == pImage)
                {
                    iImageIndex = i;
                }
            }
        }
    }
    return iImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::GetImageList(const String& sOwner, TStrings* pList)
{
    if (true == SAFE_PTR(pList))
    {
        pList->Clear();
        if (true == DoesOwnerExist(sOwner))
        {
            ZXImageInfo* pImageInfo = GetImageInfo(sOwner);
            if (true == SAFE_PTR(pImageInfo))
            {
                for (unsigned int i = 0; i < pImageInfo->vImages.size(); i++)
                {
                    pList->Add(pImageInfo->vImages[i]->vFrames[0]->Name);
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageManager::DoesOwnerExist(const String& sOwner) const
{
    bool bExists = false;
    for (unsigned int i = 0; i < m_vImages.size() && false == bExists; i++)
    {
        bExists = (sOwner == m_vImages[i]->sOwner);
    }
    return bExists;
}
//---------------------------------------------------------------------------
int __fastcall ZXImageManager::GetImageCount(const String& sOwner) const
{
    int iCount = 0;
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo))
    {
        iCount = pImageInfo->vImages.size();
    }
    return iCount;
}
//---------------------------------------------------------------------------
int __fastcall ZXImageManager::GetFrameCount(const String& sOwner, int iIndex) const
{
    int iCount = 0;
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo) && 0 <= iIndex && iIndex < (int)pImageInfo->vImages.size())
    {
        iCount = pImageInfo->vImages[iIndex]->vFrames.size();
    }
    return iCount;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::GetImageNames(std::vector<String>* vpNames, const String& sOwner, int iSubTypeFilter)
{
    if (true == SAFE_PTR(vpNames))
    {
        ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
        if (true == SAFE_PTR(pImageInfo))
        {
            vpNames->clear();
            for (unsigned int i = 0; i < pImageInfo->vImages.size(); i++)
            {
                if (iSubTypeFilter == -1 || iSubTypeFilter == pImageInfo->vImages[i]->vFrames[0]->SubType)
                    vpNames->push_back(pImageInfo->vImages[i]->vFrames[0]->Name);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::GetImageSubTypes(std::vector<int>* vpSubTypes, const String& sOwner, int iSubTypeFilter)
{
    if (true == SAFE_PTR(vpSubTypes))
    {
        ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
        if (true == SAFE_PTR(pImageInfo))
        {
            vpSubTypes->clear();
            for (unsigned int i = 0; i < pImageInfo->vImages.size(); i++)
            {
                if (iSubTypeFilter == -1 || iSubTypeFilter == pImageInfo->vImages[i]->vFrames[0]->SubType)
                    vpSubTypes->push_back(pImageInfo->vImages[i]->vFrames[0]->SubType);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::GetImageBitmaps(std::vector<Graphics::TBitmap*>* vpImages, const String& sOwner, int iSubTypeFilter)
{
    if (true == SAFE_PTR(vpImages))
    {
        ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
        if (true == SAFE_PTR(pImageInfo) && vpImages->size() <= pImageInfo->vImages.size())
        {
            int ii = 0;
            for (unsigned int i = 0; i < pImageInfo->vImages.size(); i++)
            {
                if (iSubTypeFilter != -1 && iSubTypeFilter != pImageInfo->vImages[i]->vFrames[0]->SubType)
                    continue;
                int X = 0;
                Graphics::TBitmap* pImage = (*vpImages)[ii++];
                if (true == SAFE_PTR(pImage))
                {
                    pImage->Width  = pImageInfo->vImages[i]->vFrames[0]->Width * pImageInfo->vImages[i]->vFrames.size() * pImageInfo->vImages[i]->vFrames[0]->ModeScaleX * pImageInfo->vImages[i]->vFrames[0]->Palette->ScalarX;
                    pImage->Height = pImageInfo->vImages[i]->vFrames[0]->Height * pImageInfo->vImages[i]->vFrames[0]->ModeScaleY * pImageInfo->vImages[i]->vFrames[0]->Palette->ScalarY;// + 1;
                    TColor MaskColor = clBlack;
                    if (SAFE_PTR(pImageInfo->vImages[i]->vFrames[0]->Palette))
                    {
                        pImage->PixelFormat = pf32bit;
                        pImage->Transparent = true;
                        MaskColor = pImageInfo->vImages[i]->vFrames[0]->Palette->GetColor(0);
                    }
                    else
                    {
                        pImage->PixelFormat = pf1bit;
                        pImage->Transparent = true;
                    }
                    // encode the real width and height of the image into the text flags
                    pImage->Canvas->TextFlags = pImageInfo->vImages[i]->vFrames[0]->Width + (pImageInfo->vImages[i]->vFrames[0]->Height << 16);
                    if (pImageInfo->vImages[i]->vFrames[0]->IsMasked)
                    {
                        MaskColor = TColor(clBlack + 1);
                    }
                    pImage->Canvas->Brush->Color = MaskColor;
                    for (unsigned int f = 0; f < pImageInfo->vImages[i]->vFrames.size(); f++)
                    {
                        pImage->TransparentColor = MaskColor;
                        pImageInfo->vImages[i]->vFrames[f]->Invalidate();
                        pImageInfo->vImages[i]->vFrames[f]->ReDraw();
                        pImageInfo->vImages[i]->vFrames[f]->Draw(pImage->Canvas, 1, X, 0);
                        if (pImageInfo->vImages[i]->vFrames[f]->IsMasked)
                        {
                            pImageInfo->vImages[i]->vFrames[f]->DrawMask(pImage->Canvas, X, 0, MaskColor);
                        }
                        X += pImageInfo->vImages[i]->vFrames[f]->Width;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageManager::IsDirty(void)
{
    bool bDirty = m_bDirty;
    if (false == bDirty)
    {
        for (unsigned int i = 0; i < m_vImages.size() && false == bDirty; ++i)
        {
            for (unsigned int j = 0; j < m_vImages[i]->vImages.size() && false == bDirty; ++j)
            {
                for (unsigned int f = 0; f < m_vImages[i]->vImages[j]->vFrames.size() && false == bDirty; ++f)
                {
                    bDirty = m_vImages[i]->vImages[j]->vFrames[f]->IsDirty;
                }
            }
        }
    }
    return bDirty;
}
//---------------------------------------------------------------------------
bool __fastcall ZXImageManager::UndoRestore(KXmlInfo* xmlInfo)
{
    bool bUndone = false;

    m_bUndoInProgress = true;
    KXmlInfo* pOperation = xmlInfo->GetNode("Operation");

    if (true == SAFE_PTR(pOperation))
    {
        String sOperation = pOperation->GetText();

        if (true == SAFE_PTR(pOperation))
        {
            String sOperation = pOperation->GetText();

            if (sOperation == "ImageFrameReorder")
            {
                UndoImageReorder(xmlInfo);
                bUndone = true;
            }
            else if (sOperation == "ImageCreate")
            {
                UndoImageCreate(xmlInfo);
                bUndone = true;
            }
            else if (sOperation == "ImageRemoveFrame")
            {
                UndoImageRemoveFrame(xmlInfo);
                bUndone = true;
            }
            else if (sOperation == "ImageRemoveAll")
            {
                UndoImageRemoveAll(xmlInfo);
                bUndone = true;
            }
            else if (sOperation == "ImageRename")
            {
                UndoImageRename(xmlInfo);
                bUndone = true;
            }
            else if (sOperation == "ImageClone")
            {
                UndoImageClone(xmlInfo);
                bUndone = true;
            }
            else if (sOperation == "ImageResize")
            {
                UndoImageResize(xmlInfo);
                bUndone = true;
            }
            else if (sOperation == "ImageMakeMask")
            {
                UndoImageMakeMask(xmlInfo);
                bUndone = true;
            }
        }
    }
    m_bUndoInProgress = false;
    return bUndone;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::UndoImageReorder(KXmlInfo* xmlInfo)
{
    // find the image and load the change
    String sOwner = xmlInfo->GetNode("Owner")->GetText();
    int iIndex = xmlInfo->GetNode("Index")->GetInt();
    int iOldFrame = xmlInfo->GetNode("OldFrame")->GetInt();
    int iNewFrame = xmlInfo->GetNode("NewFrame")->GetInt();

    ReorderFrame(sOwner, iIndex, iOldFrame, iNewFrame);
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::UndoImageCreate(KXmlInfo* xmlInfo)
{
    String sOwner = xmlInfo->GetNode("Owner")->GetText();
    String sPalSig = xmlInfo->GetNode("PalSignature")->GetText();
    String sName = xmlInfo->GetNode("Name")->GetText();
    int iWidth = xmlInfo->GetNode("Width")->GetInt();
    int iHeight = xmlInfo->GetNode("Height")->GetInt();
    bool bMasked = xmlInfo->GetNode("Masked")->GetBool();
    bool bUndo = xmlInfo->GetNode("Undo")->GetBool();
    int iIndex = xmlInfo->GetNode("Index")->GetInt();
    int iFrame = xmlInfo->GetNode("Frame")->GetInt();

    if (bUndo)
    {
        // delete the created image
        RemoveImage(sOwner, iIndex, iFrame);
    }
    else
    {
        // recreate the created image
        int iNewIndex = AddImage(sOwner, sPalSig, sName, iWidth, iHeight, bMasked);
        int iFrames = GetFrameCount(sOwner, iNewIndex);
        if (iNewIndex != iIndex)
        {
            ZXImageInfo* pImageInfo = GetImageInfo(sOwner);
            if (true == SAFE_PTR(pImageInfo))
            {
                ZXFrames* OldFrames = pImageInfo->vImages.back();
                pImageInfo->vImages.pop_back();
                pImageInfo->vImages.insert(pImageInfo->vImages.begin() + iIndex, OldFrames);
            }
        }
        if (iFrames != iFrame)
        {
            // reposition the addition
            ReorderFrame(sOwner, iIndex, iFrames, iFrame);
        }
    }
    if (FOnPostMessage)
    {
        FOnPostMessage(mrSubPlugins, IMAGE_EDITOR_REFRESH_LIST, NULL, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::UndoImageRemoveFrame(KXmlInfo* xmlInfo)
{
    String sOwner = xmlInfo->GetNode("Owner")->GetText();
    String sPalSig = xmlInfo->GetNode("PalSignature")->GetText();
    String sName = xmlInfo->GetNode("Name")->GetText();
    int iWidth = xmlInfo->GetNode("Width")->GetInt();
    int iHeight = xmlInfo->GetNode("Height")->GetInt();
    bool bMasked = xmlInfo->GetNode("Masked")->GetBool();
    bool bUndo = xmlInfo->GetNode("Undo")->GetBool();
    int iIndex = xmlInfo->GetNode("Index")->GetInt();
    int iFrame = xmlInfo->GetNode("Frame")->GetInt();
    KXmlInfo* Frame0 = xmlInfo->GetNode("Frame0");

    if (bUndo)
    {
        // recreate the delete image
        int iNewIndex = AddImage(sOwner, sPalSig, sName, iWidth, iHeight, bMasked);
        int iFrames = GetFrameCount(sOwner, iNewIndex) - 1;
        ZXImage* pImage = GetImage(sOwner, iNewIndex, iFrames);
        if (true == SAFE_PTR(pImage))
        {
            pImage->Load(*Frame0, true);
        }
        if (iNewIndex != iIndex)
        {
            ZXImageInfo* pImageInfo = GetImageInfo(sOwner);
            if (true == SAFE_PTR(pImageInfo))
            {
                m_vImages.insert(m_vImages.begin() + iIndex, pImageInfo);
                m_vImages.pop_back();
            }
        }
        if (iFrames != iFrame)
        {
            // reposition the addition
            ReorderFrame(sOwner, iIndex, iFrames, iFrame);
        }
    }
    else
    {
        // delete the created image
        RemoveImage(sOwner, iIndex, iFrame);
    }
    if (FOnPostMessage)
    {
        FOnPostMessage(mrSubPlugins, IMAGE_EDITOR_REFRESH_LIST, NULL, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::UndoImageRemoveAll(KXmlInfo* xmlInfo)
{
    String sOwner = xmlInfo->GetNode("Owner")->GetText();
    String sPalSig = xmlInfo->GetNode("PalSignature")->GetText();
    String sName = xmlInfo->GetNode("Name")->GetText();
    int iWidth = xmlInfo->GetNode("Width")->GetInt();
    int iHeight = xmlInfo->GetNode("Height")->GetInt();
    bool bMasked = xmlInfo->GetNode("Masked")->GetBool();
    bool bUndo = xmlInfo->GetNode("Undo")->GetBool();
    int iIndex = xmlInfo->GetNode("Index")->GetInt();

    if (bUndo)
    {
        // recreate the deleted images
        int iNewIndex = AddImage(sOwner, sPalSig, sName, iWidth, iHeight, bMasked);
        // now add all the images back too
        int i = 0;
        KXmlInfo* Frame = xmlInfo->GetNode("Frame0");
        while (Frame)
        {
            ZXImage* pImage = GetImage(sOwner, iNewIndex, i);
            if (true == SAFE_PTR(pImage))
            {
                pImage->Load(*Frame, true);
            }
            Frame = xmlInfo->GetNode("Frame" + IntToStr(++i));
            if (Frame)
            {
                AddImage(sOwner, sPalSig, sName, iWidth, iHeight, bMasked);
            }
        }
        if (iNewIndex != iIndex)
        {
            ZXImageInfo* pImageInfo = GetImageInfo(sOwner);
            if (true == SAFE_PTR(pImageInfo))
            {
                m_vImages.insert(m_vImages.begin() + iIndex, pImageInfo);
                m_vImages.pop_back();
            }
        }
    }
    else
    {
        // delete the created image
        RemoveImage(sOwner, iIndex, -1);
    }
    if (FOnPostMessage)
    {
        FOnPostMessage(mrSubPlugins, IMAGE_EDITOR_REFRESH_LIST, NULL, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::UndoImageRename(KXmlInfo* xmlInfo)
{
    String sOwner = xmlInfo->GetNode("Owner")->GetText();
    String sName = xmlInfo->GetNode("Name")->GetText();
    int iIndex = xmlInfo->GetNode("Index")->GetInt();
    RenameImage(sOwner, iIndex, sName);
    if (FOnPostMessage)
    {
        FOnPostMessage(mrSubPlugins, IMAGE_EDITOR_REFRESH_LIST, NULL, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::UndoImageClone(KXmlInfo* xmlInfo)
{
    String sOwner = xmlInfo->GetNode("Owner")->GetText();
    String sName = xmlInfo->GetNode("Name")->GetText();
    bool bUndo = xmlInfo->GetNode("Undo")->GetBool();
    int iIndex = xmlInfo->GetNode("Index")->GetInt();
    int iCloneIndex = xmlInfo->GetNode("CloneIndex")->GetInt();
    int iCloneFrame = xmlInfo->GetNode("CloneFrame")->GetInt();
    int iFrame = xmlInfo->GetNode("Frame")->GetInt();

    if (bUndo)
    {
        // delete the created image
        RemoveImage(sOwner, iCloneIndex, iCloneFrame);
    }
    else
    {
        CloneImage(sOwner, sName, iIndex, iFrame);
    }
    if (FOnPostMessage)
    {
        FOnPostMessage(mrSubPlugins, IMAGE_EDITOR_REFRESH_LIST, NULL, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::UndoImageResize(KXmlInfo* xmlInfo)
{
    String sOwner = xmlInfo->GetNode("Owner")->GetText();
    String sName = xmlInfo->GetNode("Name")->GetText();
    int iWidth = xmlInfo->GetNode("Width")->GetInt();
    int iHeight = xmlInfo->GetNode("Height")->GetInt();
    int iIndex = xmlInfo->GetNode("Index")->GetInt();

    ZXImage* pImage = GetImage(sOwner, iIndex, 0);
    ResizeImage(sOwner,  pImage, 0, 0, iWidth, iHeight);
    // now add all the images back too
    int i = 0;
    KXmlInfo* Frame = xmlInfo->GetNode("Frame0");
    while (Frame)
    {
        ZXImage* pImage = GetImage(sOwner, iIndex, i);
        if (true == SAFE_PTR(pImage))
        {
            pImage->Load(*Frame, true);
        }
        Frame = xmlInfo->GetNode("Frame" + IntToStr(++i));
    }
    if (FOnPostMessage)
    {
        FOnPostMessage(mrSubPlugins, IMAGE_EDITOR_REFRESH_LIST, NULL, 0, 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::UndoImageMakeMask(KXmlInfo* xmlInfo)
{
    String sOwner = xmlInfo->GetNode("Owner")->GetText();
    String sName = xmlInfo->GetNode("Name")->GetText();
    int iIndex = xmlInfo->GetNode("Index")->GetInt();

    ZXImage* pImage = GetImage(sOwner, iIndex, 0);
    // now load all the previous masked images
    int i = 0;
    KXmlInfo* Frame = xmlInfo->GetNode("Frame0");
    while (Frame)
    {
        ZXImage* pImage = GetImage(sOwner, iIndex, i);
        if (true == SAFE_PTR(pImage))
        {
            pImage->Load(*Frame, true);
        }
        Frame = xmlInfo->GetNode("Frame" + IntToStr(++i));
    }
    if (FOnPostMessage)
    {
        FOnPostMessage(mrSubPlugins, IMAGE_EDITOR_REFRESH_LIST, NULL, 0, 0);
    }
}
//---------------------------------------------------------------------------
ZXPalette* __fastcall ZXImageManager::GetPalette(int iPalette)
{
    ZXPalette* pPalette = NULL;
    if (0 <= iPalette && iPalette < (int)m_vPalettes.size())
    {
        pPalette = m_vPalettes[iPalette];
    }
    return pPalette;
}
//---------------------------------------------------------------------------
ZXPalette* __fastcall ZXImageManager::GetPalette(const AnsiString& name)
{
    for (unsigned int i = 0; i < m_vPalettes.size(); i++)
    {
        if (m_vPalettes[i]->Name == name)
        {
            return m_vPalettes[i];
        }
    }
    return NULL;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::ApplyVersion_1_0_Fixes(KXmlInfo& xmlInfo, const String& sPalette)
{
    KXmlInfo* node = xmlInfo.GetNode("Pixels");
    if (sPalette == "ZX Spectrum" || sPalette == "Monochrome")
    {

    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::SetMaskMode(bool MaskOn)
{
    for (unsigned int i = 0; i < m_vImages.size(); i++)
    {
        for (unsigned int v = 0; v < m_vImages[i]->vImages.size(); v++)
        {
            for (unsigned int f = 0; f < m_vImages[i]->vImages[v]->vFrames.size(); f++)
            {
                m_vImages[i]->vImages[v]->vFrames[f]->MaskMode = MaskOn;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::InvertMask(const String& sOwner,  ZXImage* pImage)
{
    ZXImageInfo* pImageInfo = FindImageInfo(sOwner);
    if (true == SAFE_PTR(pImageInfo))
    {
        int iIndex = -1;
        for (unsigned int i = 0; i < pImageInfo->vImages.size() && iIndex == -1; i++)
        {
            for (unsigned int f = 0; f < pImageInfo->vImages[i]->vFrames.size(); f++)
            {
                if (pImageInfo->vImages[i]->vFrames[f] == pImage)
                {
                    iIndex = i;
                    break;
                }
            }
        }
        if (0 <= iIndex && iIndex < (int)pImageInfo->vImages.size())
        {
            for (unsigned int f = 0; f < pImageInfo->vImages[iIndex]->vFrames.size(); f++)
            {
                pImageInfo->vImages[iIndex]->vFrames[f]->InvertMask();
            }
        }
    }
}
//---------------------------------------------------------------------------
ZXImage* __fastcall ZXImageManager::GetPreviousFrame(ZXImage* pImage)
{
    ZXImage* pPreviousImage = NULL;
    for (unsigned int i = 0; i < m_vImages.size(); i++)
    {
        for (unsigned int v = 0; v < m_vImages[i]->vImages.size(); v++)
        {
            for (unsigned int f = 1; f < m_vImages[i]->vImages[v]->vFrames.size(); f++)
            {
                if (m_vImages[i]->vImages[v]->vFrames[f] == pImage)
                {
                    pPreviousImage = m_vImages[i]->vImages[v]->vFrames[f-1];
                    break;
                }
            }
        }
    }
    return pPreviousImage;
}
//---------------------------------------------------------------------------
int __fastcall ZXImageManager::GetSubType(const String& sType, unsigned int iIndex)
{
    ZXImageInfo* pImageInfo = FindImageInfo(sType);
    if (true == SAFE_PTR(pImageInfo))
    {
        if (iIndex < pImageInfo->vImages.size())
        {
            return pImageInfo->vImages[iIndex]->vFrames[0]->SubType;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
void __fastcall ZXImageManager::SetSubType(const String& sType, unsigned int iIndex, int subType)
{
    ZXImageInfo* pImageInfo = FindImageInfo(sType);
    if (true == SAFE_PTR(pImageInfo))
    {
        if (iIndex < pImageInfo->vImages.size())
        {
            pImageInfo->vImages[iIndex]->vFrames[0]->SubType = subType;
        }
    }
}
//---------------------------------------------------------------------------

