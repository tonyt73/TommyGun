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
#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ZXObjectManager::ZXObjectManager()
{
}
//---------------------------------------------------------------------------
__fastcall ZXObjectManager::~ZXObjectManager()
{
    Clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::SetSelected(String sValue)
{
    m_sSelected = sValue;
    ZXBitmap pBitmap = Find(sValue);
    if (NULL == pBitmap)
    {
        m_sSelected = "";
    }
    if (FOnClick)
    {
        FOnClick(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::Refresh(void)
{
    m_vNames.clear();
    String sPlugin = "Sprite";
    // 0 - is sprite type,
    // 1 - object type
    if (S_OK == PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_GET_IMAGE_NAMES, (LPDATA)&m_vNames, (DWORD)&sPlugin, 1))
    {
        ResizeBitmapVector();
        PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_GET_IMAGE_BITMAPS, (LPDATA)&m_vBitmaps, (DWORD)&sPlugin, 1);
        m_pImageList->Clear();
        for (unsigned int i = 0; i < m_vBitmaps.size(); ++i)
        {
            ZXBitmap bitmap = m_vBitmaps[i];
            ZXBitmap imgbmp = new Graphics::TBitmap();
            imgbmp->Width = m_pImageList->Width;
            imgbmp->Height = m_pImageList->Height;
            //imgbmp->Canvas->Brush->Color = clWhite;
            //imgbmp->Canvas->FillRect(TRect(0, 0, imgbmp->Width, imgbmp->Height));
            //StretchBlt(imgbmp->Canvas->Handle, 2, 2, imgbmp->Width - 4, imgbmp->Height - 4, bitmap->Canvas->Handle, 0, 0, 16, 16, SRCCOPY);
            StretchBlt(imgbmp->Canvas->Handle, 0, 0, imgbmp->Width, imgbmp->Height, bitmap->Canvas->Handle, 0, 0, 16, 16, SRCCOPY);
            m_pImageList->Add(imgbmp, NULL);
        }
        m_pImageList->DrawingStyle = (TDrawingStyle)3;
        m_pImageList->DrawingStyle = dsTransparent;
        SyncLists();
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXObjectManager::Remove(const String& sName)
{
    bool bRemoved = false;
    for (unsigned int i = 0; i < m_vNames.size() && false == bRemoved; i++)
    {
        if (m_vNames[i] == sName)
        {
            m_vNames.erase(m_vNames.begin() + i);
            m_vBitmaps.erase(m_vBitmaps.begin() + i);
            bRemoved = true;
        }
    }
    SyncLists();
    return bRemoved;
}
//---------------------------------------------------------------------------
bool __fastcall ZXObjectManager::Rename(const String& sOldName, const String& sNewName)
{
    bool bRenamed = false;
    for (unsigned int i = 0; i < m_vNames.size() && false == bRenamed; i++)
    {
        if (m_vNames[i] == sOldName)
        {
            m_vNames[i] = sNewName;
            bRenamed = true;
        }
    }
    return bRenamed;
}
//---------------------------------------------------------------------------
ZXBitmap __fastcall ZXObjectManager::Find(const String& sName)
{
    ZXBitmap pBitmap = NULL;
    for (unsigned int i = 0; i < m_vNames.size() && NULL == pBitmap; i++)
    {
        if (m_vNames[i].LowerCase() == sName.LowerCase())
        {
            pBitmap = m_vBitmaps[i];
        }
    }
    return pBitmap;
}
//---------------------------------------------------------------------------
String __fastcall ZXObjectManager::Name(unsigned int iIndex)
{
    String sName;
    if (iIndex < m_vNames.size())
    {
        sName = m_vNames[iIndex];
    }
    return sName;
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::ResizeBitmapVector(void)
{
    if (m_vNames.size() < m_vBitmaps.size())
    {
        // remove bitmaps from the list
        while (m_vNames.size() != m_vBitmaps.size())
        {
            SAFE_DELETE(*m_vBitmaps.begin());
            m_vBitmaps.erase(m_vBitmaps.begin());
        }
    }
    else if (m_vNames.size() > m_vBitmaps.size())
    {
        // add bitmaps to the list
        while (m_vNames.size() != m_vBitmaps.size())
        {
            m_vBitmaps.push_back(new Graphics::TBitmap());
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::Clear(void)
{
    while (m_vNames.size())
    {
        Remove(m_vNames[0]);
    }
    m_vObjects.clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::GetSize(const String& sName, int& iWidth, int& iHeight)
{
    GetSize(Find(sName), iWidth, iHeight);
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::GetSize(const ZXBitmap Bitmap, int& iWidth, int& iHeight)
{
    iWidth  = -1;
    iHeight = -1;
    if (SAFE_PTR(Bitmap))
    {
        iWidth  = (unsigned int)Bitmap->Canvas->TextFlags & 0xFFFF;
        iHeight = (unsigned int)Bitmap->Canvas->TextFlags >> 16;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::SyncLists()
{
    // add new items from the m_vNames list into the m_vObjects list
	for (unsigned int i = 0; i < m_vNames.size(); ++i)
    {
        bool found = false;
        for (unsigned int j = 0; j < m_vObjects.size() && !found; ++j)
        {
            TMapObject obj = m_vObjects[j];
            if (m_vObjects[j].m_sObject == m_vNames[i])
            {
                found = true;
            }
        }
        if (!found)
        {
            TMapObject object;
            object.m_iScreen = 254;
            object.m_iLeft = 0;
            object.m_iTop = 0;
            object.m_sObject = m_vNames[i];
            m_vObjects.push_back(object);
        }
    }
    // remove objects from the m_vObjects list that arent in the m_vNames list
    for (int i = m_vObjects.size()-1; i >= 0; --i)
    {
        bool found = false;
        for (unsigned int j = 0; j < m_vNames.size() && !found; ++j)
        {
            if (m_vObjects[i].m_sObject == m_vNames[j])
            {
                found = true;
            }
        }
        if (!found)
        {
            m_vObjects.erase(m_vObjects.begin() + i);
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXObjectManager::Load(KXmlInfo& xmlInfo)
{
    bool bLoaded = false;
    KXmlInfo* ObjectsNode;
    if (xmlInfo.Find(ObjectsNode, "Objects", 0))
    {
        bLoaded = true;
        // we have objects so lets load 'em
        for (KXmlNodes::iterator it = ObjectsNode->begin(); it != ObjectsNode->end() && true == bLoaded; it++)
        {
            KXmlInfo* nName = (*it)->GetNode("Name", 0);
            KXmlInfo* nLeft = (*it)->GetNode("Left", 0);
            KXmlInfo* nTop = (*it)->GetNode("Top", 0);
            KXmlInfo* nScreen = (*it)->GetNode("Screen", 0);
            if (nName && nLeft && nTop && nScreen)
            {
                TMapObject object;
                object.m_sObject = nName->GetText();
                object.m_iScreen = nScreen->GetInt();
                object.m_iTop = nTop->GetInt();
                object.m_iLeft = nLeft->GetInt();
                m_vObjects.push_back(object);
            }
            else
            {
                bLoaded = false;
            }
        }
    }
    return bLoaded;
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::Save(KXmlInfo& xmlInfo)
{
    KXmlInfo* Node;
    if (xmlInfo.Find(Node, "Objects", 0))
    {
        xmlInfo.Remove(Node);
    }
    KXmlInfo Objects("Objects");
    // store the objects of the map
    for (unsigned int i = 0; i < m_vObjects.size(); i++)
    {
        KXmlInfo Object("Object");
        Object.Add("Name", m_vObjects[i].m_sObject);
        Object.Add("Screen", m_vObjects[i].m_iScreen);
        Object.Add("Top", m_vObjects[i].m_iTop);
        Object.Add("Left", m_vObjects[i].m_iLeft);

        Objects.Add(Object);
    }
    // add the new objects list to the xml object
    xmlInfo.Add(Objects);
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::GetObject(int iIndex, TMapObject& Object)
{
    if (0 <= iIndex && iIndex < (int)m_vObjects.size())
    {
        Object = m_vObjects[iIndex];
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::GetObject(const String& sObject, TMapObject& Object)
{
	for (int i = 0; i < (int)m_vObjects.size(); ++i)
    {
        if (m_vObjects[i].m_sObject == sObject)
        {
            Object = m_vObjects[i];
            return; 
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::GetObjectNames(int iScreen, std::vector<String>& objectNames)
{
    for (int i = 0; i < (int)m_vObjects.size(); ++i)
    {
        if (m_vObjects[i].m_iScreen == iScreen)
        {
            objectNames.push_back(m_vObjects[i].m_sObject);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::SetObjectScreen(int iIndex, int iScreen)
{
    if (0 <= iIndex && iIndex < (int)m_vObjects.size())
    {
        m_vObjects[iIndex].m_iScreen = iScreen;
    }
}
//---------------------------------------------------------------------------
int __fastcall ZXObjectManager::FindObject(int iScreen, int X, int Y)
{
    for (unsigned int i = 0; i < m_vObjects.size(); ++i)
    {
        if (m_vObjects[i].m_iScreen == iScreen)
        {
            int ox = m_vObjects[i].m_iLeft;
            int oy = m_vObjects[i].m_iTop;
            if (ox <= X && X <= ox + 15 && oy <= Y && Y <= oy + 15)
            {
                return i;
            }
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall ZXObjectManager::FindObject(const String& sObject)
{
    for (unsigned int i = 0; i < m_vObjects.size(); ++i)
    {
        if (m_vObjects[i].m_sObject == sObject)
        {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
void __fastcall ZXObjectManager::MoveObject(int iIndex, int X, int Y)
{
    if (0 <= iIndex && iIndex < (int)m_vObjects.size())
    {
        m_vObjects[iIndex].m_iLeft = X;
        m_vObjects[iIndex].m_iTop = Y;
    }
}
//---------------------------------------------------------------------------

