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
__fastcall ZXSpriteManager::ZXSpriteManager()
{
}
//---------------------------------------------------------------------------
__fastcall ZXSpriteManager::~ZXSpriteManager()
{
    Clear();
}
//---------------------------------------------------------------------------
void __fastcall ZXSpriteManager::SetSelected(String sValue)
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
void __fastcall ZXSpriteManager::Refresh(void)
{
    m_vNames.clear();
    String sPlugin = "Sprite";
    // 0 - is sprite type,
    // 1 - object type
    if (S_OK == PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_GET_IMAGE_NAMES, (LPDATA)&m_vNames, (DWORD)&sPlugin, 0))
    {
        ResizeBitmapVector();
        PostNotifyEvent(NULL, TZXC_IMAGE_EDITOR_GET_IMAGE_BITMAPS, (LPDATA)&m_vBitmaps, (DWORD)&sPlugin, 0);
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
    }
}
//---------------------------------------------------------------------------
bool __fastcall ZXSpriteManager::Remove(const String& sName)
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
    return bRemoved;
}
//---------------------------------------------------------------------------
bool __fastcall ZXSpriteManager::Rename(const String& sOldName, const String& sNewName)
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
ZXBitmap __fastcall ZXSpriteManager::Find(const String& sName)
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
int __fastcall ZXSpriteManager::IndexOf(const String& sName)
{
    for (unsigned int i = 0; i < m_vNames.size(); i++)
    {
        if (m_vNames[i].LowerCase() == sName.LowerCase())
        {
            return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
String __fastcall ZXSpriteManager::Name(unsigned int iIndex)
{
    String sName;
    if (iIndex < m_vNames.size())
    {
        sName = m_vNames[iIndex];
    }
    return sName;
}
//---------------------------------------------------------------------------
void __fastcall ZXSpriteManager::ResizeBitmapVector(void)
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
void __fastcall ZXSpriteManager::Clear(void)
{
    while (m_vNames.size())
    {
        Remove(m_vNames[0]);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXSpriteManager::GetSize(const String& sName, int& iWidth, int& iHeight)
{
    GetSize(Find(sName), iWidth, iHeight);
}
//---------------------------------------------------------------------------
void __fastcall ZXSpriteManager::GetSize(const ZXBitmap Bitmap, int& iWidth, int& iHeight)
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
void __fastcall ZXSpriteManager::GetScalar(float& dX, float& dY)
{
    dX = 1.0f;
    dY = 1.0f;
    if (m_vBitmaps.size())
    {
        int W, H;
        GetSize(m_vBitmaps[0], W, H);
        dX = (float)m_vBitmaps[0]->Width  / (float)W;
        dY = (float)m_vBitmaps[0]->Height / (float)H;
    }
}
//---------------------------------------------------------------------------

