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
__fastcall ZXParserManager::ZXParserManager()
: m_frmInsertResource(NULL)
, m_OptionsPanel(NULL)
, m_OptionParent(NULL)
, m_XmlData(NULL)
, m_SourceCode(NULL)
{
}
//---------------------------------------------------------------------------
__fastcall ZXParserManager::~ZXParserManager()
{
    SAFE_DELETE(m_frmInsertResource);
}
//---------------------------------------------------------------------------
void __fastcall ZXParserManager::Initialize(ZXParserPluginInfoVector* ParserPlugins)
{
    m_ParserPlugins = ParserPlugins;
}
//---------------------------------------------------------------------------
bool __fastcall ZXParserManager::Execute(TStrings*& Lines, bool bIsCFile)
{
    String sCurDir = GetCurrentDir();
    String sFolder;
    PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);
    ChDir(sFolder);

    m_ResourceInserted = false;
    m_SourceCode = Lines;
    m_CommentL = ";";
    m_CommentR = "";
    if (bIsCFile)
    {
        m_CommentL = "/*";
        m_CommentR = "*/";
    }
    if (false == SAFE_PTR(m_frmInsertResource))
    {
        m_frmInsertResource = new TfrmInsertResource(NULL);
        m_frmInsertResource->lstResourceParser->OnClick = OnResourceParserChange;
        m_frmInsertResource->cmbResourceType->OnChange = OnResourceTypeChange;
        m_frmInsertResource->cmdInsert->OnClick = OnResourceInsert;
    }
    if (true == SAFE_PTR(m_frmInsertResource) && !m_frmInsertResource->Visible)
    {
        m_XmlData = NULL;
        if (GetXmlInfo(m_XmlData) == S_OK && true == SAFE_PTR(m_XmlData))
        {
            // load the parser combo box with the available parsers
            LoadParsers();
            // request the XML objects
            m_frmInsertResource->ShowModal();
        }
        else
        {
            int iAnswer;
            Message
            (
                mbtError,
                "Failed to retrieve the XML Resource Data!",
                "Cannot convert resources without the XML Data.",
                "The TommyGun main framework has failed to return the XML data when requested.\n\n"
                "This is unusually so please shutdown TommyGun and try again after Restarting.",
                "Ok",
                "",
                "",
                iAnswer
            );
        }
    }
    ChDir(sCurDir);
    return m_ResourceInserted;
}
//---------------------------------------------------------------------------
bool __fastcall ZXParserManager::Update(TStrings*& Lines, const String& Filename, bool bIsCFile)
{
    String sCurDir = GetCurrentDir();
    String sFolder;
    PostNotifyEvent(NULL, TZX_QUERY_PROJECT_FOLDER, (LPDATA)&sFolder, 0, 0);
    ChDir(sFolder);

    bool bResult = false;
    // get the xml resources
    m_XmlData = NULL;
    m_CommentL = ";";
    m_CommentR = "";
    if (bIsCFile)
    {
        m_CommentL = "/*";
        m_CommentR = "*/";
    }
    if (GetXmlInfo(m_XmlData) == S_OK && true == SAFE_PTR(m_XmlData))
    {
        // Special AGD Hack:
        // Doing this because I don't want to mark up the AgdGameEngine.asm source code with the TG
        // Resource markers. So the AGD parser will work directly on the file and use simplified markers.
        /*if (Filename.LowerCase() == "agdgameengine.asm")
        {
            ParseAGD(Lines);
            return true;
        }*/
        int iResourcesBegin = FindLine(Lines, "[RESOURCES SECTION");
        int iResourcesEnd   = FindLine(Lines, "]RESOURCES SECTION", iResourcesBegin);

        if (iResourcesBegin != -1 && iResourcesEnd != -1)
        {
            // ok, we have a resources section so lets each the resource and update them
            int iResourceStart = FindLine(Lines, "[RESOURCE:", iResourcesBegin + 1);
            int iResourceEnd   = FindLineEnd(Lines, iResourceStart  + 1);

            while (iResourceStart != -1)
            {
                if (iResourceEnd == -1)
                {
                    iResourceEnd = iResourcesEnd;
                }
                String sLine = Lines->Strings[iResourceStart];
                // get the parser details, but don't re-parse pre parse tags
                if (sLine.Pos("<Parser:") > 0 && sLine.Pos("[Begin]") == 0)
                {
                    try
                    {
                        // got a parser so lets get it
                        String sParser = sLine.SubString(sLine.Pos("<Parser:") + 8, 65535);
                        sParser = sParser.SubString(1, sParser.Pos(">") - 1);
                        // get the resource name
                        String sResource = sLine.SubString(sLine.Pos("<Resource:") + 10, 65535);
                        sResource = sResource.SubString(1, sResource.Pos(">") - 1);
                        String sParserData = sLine.SubString(sLine.Pos("<Data:") + 6, 65535);
                        sParserData = sParserData.SubString(1, sParserData.Pos(">") - 1);
                        // now find the parser object
                        ZXParserPluginInfo* pParser = FindParser(sParser);
                        if (true == SAFE_PTR(pParser))
                        {
                            // got a parser, so ask it to parse the resource (if it exists in the xml data)
                            TStringList* ParsedCode = new TStringList();
                            if (S_OK == pParser->pParseResourceFunc(m_XmlData, sResource, ParsedCode, sParserData))
                            {
                                // we need to find the resources position and the end of it
                                // and then remove it
                                for (int j = iResourceStart; j < iResourceEnd; j++)
                                {
                                    Lines->Delete(iResourceStart);
                                    iResourcesEnd--;
                                }
                                int iResourcePosition = iResourceStart;

                                // add in the new code
                                iResourcesEnd += ParsedCode->Count + 1;
                                Lines->Insert(iResourcePosition++, sLine);
                                for (int l = 0; l < ParsedCode->Count; l++)
                                {
                                    Lines->Insert(iResourcePosition++, ParsedCode->Strings[l]);
                                }
                            }
                        }
                    }
                    catch(...)
                    {
                        // either an exception get the strings from the parser line or
                        // a processing error, either way lets just move onto the next resource
                    }
                }
                // get the next resource
                iResourceStart = FindLine(Lines, "[RESOURCE:", iResourceStart + 1);
                iResourceEnd   = FindLineEnd(Lines, iResourceStart + 1);
            }


            // 1. find the resources section
            // 2. find each resource item in the resources section
            // 3. for each resource we get the parser details
            // 4. find the parser for the resource
            // 5. find the resource in the xml data
            // 6. if both exist get the parser to parse the new xml data
            // 7. update the parsed data back into the lines of code
            // 8. simple really! ;-)

            // or there is the earlier

            // need to get a resource and its tag
            // need to find the correct parser
            // then need to send resource tag to parser and get new source code
            // then find the existing resources start and end lines remove it
            // and the insert the new code
            bResult = true;
        }
    }
    ChDir(sCurDir);
    return bResult;
}
//---------------------------------------------------------------------------
/*void __fastcall ZXParserManager::ParseAGD(TStrings*& Lines)
{
    // process the agd game resources
    ZXParserPluginInfo* pParser = FindParser("Arcade Game Designer");
    if (true == SAFE_PTR(pParser))
    {
        // copy the lines to a string list for processing
        TStringList* lines = new TStringList();
        lines->AddStrings(Lines);
        String parserData;
        String resource = "AGD";
        if (S_OK == pParser->pParseResourceFunc(m_XmlData, resource, lines, parserData))
        {
            // copy the new code for returning back to the file manager
            Lines->Clear();
            Lines->AddStrings(lines);
        }
    }
}*/
//---------------------------------------------------------------------------
void __fastcall ZXParserManager::OnResourceParserChange(TObject* Sender)
{
    LoadResourceTypes();
    if (true == SAFE_PTR(m_ParserPlugins) && (*m_ParserPlugins)[m_frmInsertResource->lstResourceParser->ItemIndex]->pGetOptionsPanelFunc)
    {
        if (true == SAFE_PTR(m_OptionsPanel))
        {
            m_OptionsPanel->Parent = m_OptionParent;
        }
        TPanel* pPanel = NULL;
        (*m_ParserPlugins)[m_frmInsertResource->lstResourceParser->ItemIndex]->pGetOptionsPanelFunc(pPanel);
        if (true == SAFE_PTR(pPanel))
        {
            m_OptionParent = pPanel->Parent;
            m_OptionsPanel = pPanel;
            pPanel->Parent = m_frmInsertResource->panResourceOptions;

            m_frmInsertResource->lblResourceParserDescription->Caption = "";
            if ((*m_ParserPlugins)[m_frmInsertResource->lstResourceParser->ItemIndex]->pDescriptionFunc)
            {
                String sDescription;
                (*m_ParserPlugins)[m_frmInsertResource->lstResourceParser->ItemIndex]->pDescriptionFunc(sDescription);
                int iPos = sDescription.Pos("(");
                if (iPos)
                {
                    m_frmInsertResource->lblResourceParserDescription->Caption = sDescription.SubString(iPos + 1, sDescription.Length() - iPos - 1);
                }
            }
        }
        m_frmInsertResource->lstResourcesClickCheck(NULL);
        m_frmInsertResource->cmbResourceTypeChange(NULL);
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXParserManager::OnResourceTypeChange(TObject* Sender)
{
    LoadResources();
    m_frmInsertResource->lstResourcesClickCheck(NULL);
}
//---------------------------------------------------------------------------
void __fastcall ZXParserManager::OnResourceInsert(TObject* Sender)
{
    // parse the resource and insert it into the current file
    bool bCreateInEditor = true;//m_frmInsertResource->chkCreateInEditor->Checked;
    m_ResourceInserted = true;
    TStrings* pSourceCode = NULL;
    if (bCreateInEditor)
    {
        // creating code in the editor
        pSourceCode = m_SourceCode;
    }
    else
    {
        // get the file manager to create/get a file for the source code
        // and return the Lines for it
    }

    // close the insert resources dialog
    m_frmInsertResource->Close();
    if (NULL != pSourceCode)
    {
        int iResourcesEnd = FindEndOfResources(pSourceCode);

        if (-1 != iResourcesEnd)
        {
            // get the data parsed
            ZXParserPluginInfo* Parser = (*m_ParserPlugins)[m_frmInsertResource->lstResourceParser->ItemIndex];
            String Resource;
            TStringList* ParsedCode = new TStringList();
            String ParserData;
            String sType = m_frmInsertResource->cmbResourceType->Items->Strings[m_frmInsertResource->cmbResourceType->ItemIndex];

            ParsedCode->Clear();
            ParserData = "[Begin]";
            if (S_OK == Parser->pParseResourceFunc(m_XmlData, sType, ParsedCode, ParserData))
            {
                InsertResource(sType, ParserData, pSourceCode, ParsedCode, true, false);
            }

            for (int i = 0; i < m_frmInsertResource->lstResources->Items->Count; i++)
            {
                if (m_frmInsertResource->lstResources->Checked[i])
                {
                    Resource = sType + "\\" + m_frmInsertResource->lstResources->Items->Strings[i];
                    ParsedCode->Clear();
                    ParserData = "";
                    if (S_OK == Parser->pParseResourceFunc(m_XmlData, Resource, ParsedCode, ParserData))
                    {
                        InsertResource(Resource, ParserData, pSourceCode, ParsedCode, true, true);
                    }
                    else
                    {
                        int iAnswer;
                        Message
                        (
                            mbtError,
                            "Failed to Parse the XML Data",
                            "The Parser failed to convert the XML data into Source Code",
                            "A problem occurred when trying to convert the XML data into Source Code.\n\nNo solution available at present\n\n\Click,\n\tOk\tto return to the Code Editor.",
                            "Ok",
                            "",
                            "",
                            iAnswer
                        );
                    }
                }
            }

            // get the post parsing code
            ParsedCode->Clear();
            ParserData = "[End]";

            if (S_OK != Parser->pParseResourceFunc(m_XmlData, sType, ParsedCode, ParserData))
            {
                ParsedCode->Clear();
            }
            InsertResource(sType, ParserData, pSourceCode, ParsedCode, false, true);
            m_frmInsertResource->lstResourcesClickCheck(NULL);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXParserManager::InsertResource(const String& sResource, const String& ParserData, TStrings* pSourceCode, TStringList* ParsedCode, bool bBegin, bool bEnd)
{
    String sResourceTag = m_CommentL + " [RESOURCE: ";
    sResourceTag += "<Parser:" + m_frmInsertResource->lstResourceParser->Items->Strings[m_frmInsertResource->lstResourceParser->ItemIndex] + ">";
    sResourceTag += "<Resource:" + sResource + ">";
    String sResourceEndTag = m_CommentL + " ]RESOURCE: ";
    sResourceEndTag += "<Parser:" + m_frmInsertResource->lstResourceParser->Items->Strings[m_frmInsertResource->lstResourceParser->ItemIndex] + ">";
    sResourceEndTag += "<Resource:" + sResource + ">]";
    int Spaces = (78 - sResourceEndTag.Length());
    sResourceEndTag += (Spaces > 0 ? AnsiString::StringOfChar(' ', Spaces) : AnsiString(""));
    sResourceEndTag += m_CommentR;
    // xml data was parsed successfully,
    // now if it doesn't exist add it else give a warning resource already exists
    int iResourcesEnd = FindEndOfResources(pSourceCode);
    int iResourcePosition = iResourcesEnd;
    bool bSkip = false;

    if (!IsResourceIsUnique(pSourceCode, sResourceTag))
    {
        bSkip = frmBuildOptions->chkOptionsCodeEditorResourceSkip->Checked;

        if (frmBuildOptions->chkOptionsCodeEditorResourceAsk->Checked)
        {
            int iAnswer = 0;
            Message
            (
                mbtWarning,
                "What would like to do to the duplicate Resource?",
                "The Resource already exists.",
                "The Resource [" + sResource + "] already exists.\n\nWould like to\n"
                "\tOverwrite\tOverwrite the existing Resource data\n"
                "\tSkip\t\tSkip the Resource and leave it unchanged\n",
                "Skip",
                "Overwrite",
                "",
                iAnswer
            );
            bSkip = (iAnswer == 0);
        }

        if (!bSkip && bBegin)
        {
            // we need to find the resources position and the end of it
            // and then remove it
            int iResBgn = FindLine(pSourceCode, sResourceTag);
            int iResEnd = FindLine(pSourceCode, sResourceEndTag);

            //assert(iResBgn != -1);

            if (iResEnd == -1)
            {
                iResEnd = iResourcesEnd;
            }

            for (int j = iResBgn; j < iResEnd; j++)
            {
                pSourceCode->Delete(iResBgn);
                iResourcesEnd--;
            }
            iResourcePosition = iResBgn;
        }
    }

    if (!bSkip)
    {
        sResourceTag += "<Data:" + ParserData + ">]";
        int Spaces = (78 - sResourceTag.Length());
        sResourceTag += Spaces > 0 ? AnsiString::StringOfChar(' ', Spaces) : AnsiString("");
        sResourceTag += m_CommentR;
        // add the resource
        if (bBegin)
        {
            pSourceCode->Insert(iResourcePosition++, sResourceTag);
        }
        for (int l = 0; l < ParsedCode->Count; l++)
        {
            pSourceCode->Insert(iResourcePosition++, ParsedCode->Strings[l]);
        }
        if (bEnd)
        {
            pSourceCode->Insert(iResourcePosition++, sResourceEndTag);
            pSourceCode->Insert(iResourcePosition++, "");
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXParserManager::LoadParsers(void)
{
    m_frmInsertResource->lblNoParsers->Visible = true;
    m_frmInsertResource->lstResourceParser->Items->Clear();
    if (true == SAFE_PTR(m_ParserPlugins))
    {
        for (int i = 0; i < (int)m_ParserPlugins->size(); i++)
        {
            String sDescription;
            if ((*m_ParserPlugins)[i]->pDescriptionFunc)
            {
                (*m_ParserPlugins)[i]->pDescriptionFunc(sDescription);
                if (sDescription.Trim() != "")
                {
                    int iPos = sDescription.Pos("(");
                    if (iPos)
                    {
                        sDescription = sDescription.SubString(1, iPos - 1);
                    }
                    m_frmInsertResource->lstResourceParser->Items->Add(sDescription.Trim());
                }
            }
        }
        if (m_frmInsertResource->lstResourceParser->Items->Count > 0)
        {
            m_frmInsertResource->lstResourceParser->ItemIndex = 0;
            OnResourceParserChange(NULL);
        }
        m_frmInsertResource->lstResourceParser->Enabled = true;
        m_frmInsertResource->cmbResourceType->Enabled = true;
        m_frmInsertResource->cmdInsert->Enabled = true;
        m_frmInsertResource->lblNoParsers->Visible = false;
    }
    else
    {
        m_frmInsertResource->lstResourceParser->Items->Add("NO PARSERS");
        m_frmInsertResource->lstResourceParser->ItemIndex = 0;
        m_frmInsertResource->lstResourceParser->Enabled = false;
        m_frmInsertResource->cmbResourceType->Enabled = false;
        m_frmInsertResource->cmdInsert->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXParserManager::LoadResourceTypes(void)
{
    m_frmInsertResource->cmbResourceType->Items->Clear();
    m_frmInsertResource->lstResources->Items->Clear();
    if (true == SAFE_PTR(m_ParserPlugins))
    {
        if ((*m_ParserPlugins)[m_frmInsertResource->lstResourceParser->ItemIndex]->pGetResourceTypesFunc)
        {
            TStringList* pTypesList = new TStringList();
            if (true == SAFE_PTR(pTypesList))
            {
                (*m_ParserPlugins)[m_frmInsertResource->lstResourceParser->ItemIndex]->pGetResourceTypesFunc(m_XmlData, pTypesList);
                m_frmInsertResource->cmbResourceType->Items->AddStrings(pTypesList);
                if (m_frmInsertResource->cmbResourceType->Items->Count > 0)
                {
                    m_frmInsertResource->cmbResourceType->ItemIndex = 0;
                    LoadResources();
                }
                SAFE_DELETE(pTypesList);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXParserManager::LoadResources(void)
{
    m_frmInsertResource->lstResources->Items->Clear();
    if (true == SAFE_PTR(m_ParserPlugins))
    {
        if ((*m_ParserPlugins)[m_frmInsertResource->lstResourceParser->ItemIndex]->pGetResourcesListFunc)
        {
            TStringList* pResourcesList = new TStringList();
            if (true == SAFE_PTR(pResourcesList))
            {
                if
                (
                    S_OK ==
                    (*m_ParserPlugins)[m_frmInsertResource->lstResourceParser->ItemIndex]->pGetResourcesListFunc
                    (
                        m_XmlData,
                        m_frmInsertResource->cmbResourceType->Items->Strings[m_frmInsertResource->cmbResourceType->ItemIndex],
                        pResourcesList
                    )
                )
                {
                    m_frmInsertResource->lstResources->Items->AddStrings(pResourcesList);
                }
            }
            if (m_frmInsertResource->lstResources->Items->Count)
            {
                m_frmInsertResource->lstResources->ItemIndex = 0;
            }
            for (int i = 0; i < m_frmInsertResource->lstResources->Items->Count; ++i)
            {
                m_frmInsertResource->lstResources->Checked[i] = true;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ZXParserManager::Hide(void)
{
    if (true == SAFE_PTR(m_frmInsertResource) && m_frmInsertResource->Visible)
    {
        m_frmInsertResource->Visible = false;
    }
}
//---------------------------------------------------------------------------
ZXParserPluginInfo* __fastcall ZXParserManager::FindParser(const String& sParserDescription)
{
    ZXParserPluginInfo* pParser = NULL;
    if (true == SAFE_PTR(m_ParserPlugins))
    {
        for (int i = 0; i < (int)m_ParserPlugins->size(); i++)
        {
            String sDescription;
            if ((*m_ParserPlugins)[i]->pDescriptionFunc)
            {
                (*m_ParserPlugins)[i]->pDescriptionFunc(sDescription);
                int iBracket = sDescription.Pos("(");
                if (iBracket)
                {
                    sDescription = sDescription.SubString(1, iBracket - 1).Trim();
                }
                if (sDescription.Trim().LowerCase() == sParserDescription.Trim().LowerCase())
                {
                    pParser = (*m_ParserPlugins)[i];
                    break;
                }
            }
        }
    }
    return pParser;
}
//---------------------------------------------------------------------------
int __fastcall ZXParserManager::FindLine(const TStrings*& pSourceCode, const String& sText, int iStartLine) const
{
    int iLine = -1;
    TStrings* SourceCode = const_cast<TStrings*>(pSourceCode);
    if (0 <= iStartLine && iStartLine < SourceCode->Count)
    {
        for (int i = iStartLine; i < SourceCode->Count && -1 == iLine; i++)
        {
            if (SourceCode->Strings[i].Pos(sText) /* == 1 */)
            {
                iLine = i;
            }
        }
    }
    return iLine;
}
//---------------------------------------------------------------------------
int __fastcall ZXParserManager::FindLineEnd(const TStrings*& pSourceCode, int iStartLine) const
{
    int iLine = -1;
    int iMatches = 1;
    TStrings* SourceCode = const_cast<TStrings*>(pSourceCode);
    if (0 <= iStartLine && iStartLine < SourceCode->Count)
    {
        for (int i = iStartLine; i < SourceCode->Count && -1 == iLine; i++)
        {
            if (SourceCode->Strings[i].Pos(m_CommentL + " [") == 1)
            {
                iMatches++;
            }
            if (SourceCode->Strings[i].Pos(m_CommentL + " ]") == 1)
            {
                iMatches--;
            }
            if (iMatches == 0)
            {
                iLine = i;
                break;
            }
        }
    }
    return iLine;
}
//---------------------------------------------------------------------------
int __fastcall ZXParserManager::FindEndOfResources(TStrings*& pSourceCode) const
{
    // we need to locate the resources section of the code
    // if it doesn't exist we need to add it to the end of the editor code

    // search the code editor lines for the resources section
    // ; [RESOURCES SECTION
    // ; [RESOURCE:{parser data for resource}]
    //
    // ; ]RESOURCES SECTION
    int iResourcesBegin = FindLine(pSourceCode, "[RESOURCES SECTION");
    int iResourcesEnd   = FindLine(pSourceCode, "]RESOURCES SECTION", iResourcesBegin);
    int iResourceFirst  = FindLine(pSourceCode, "[RESOURCE:");

    if (-1 != iResourcesBegin)
    {
        if (-1 == iResourcesEnd)
        {
            // resources section is missing the end tag so add it to the end of the file
            iResourcesEnd = pSourceCode->Add(m_CommentL + " ]RESOURCES SECTION                                                         " + m_CommentR);
        }
    }
    else
    {
        if (-1 == iResourcesEnd)
        {
            // no resources section, so add one
            pSourceCode->Add(m_CommentL + "****************************************************************************" + m_CommentR);
            pSourceCode->Add(m_CommentL + "                      WARNING: DO NOT EDIT THIS SECTION!                    " + m_CommentR);
            pSourceCode->Add(m_CommentL + "      This section gets automatically generated by the Resource Editor      " + m_CommentR);
            pSourceCode->Add(m_CommentL + "   And any data here will get overwritten, when the resources are updated   " + m_CommentR);
            pSourceCode->Add(m_CommentL + "****************************************************************************" + m_CommentR);
            iResourcesBegin = pSourceCode->Add(m_CommentL + " [RESOURCES SECTION                                                         " + m_CommentR);
            iResourcesEnd   = pSourceCode->Add(m_CommentL + " ]RESOURCES SECTION                                                         " + m_CommentR);
        }
        else
        {
            // we have an end resources section but no start section
            if (-1 == iResourceFirst)
            {
                // no resources so, add it before the resources end line
                pSourceCode->Add(m_CommentL + "****************************************************************************" + m_CommentR);
                pSourceCode->Add(m_CommentL + "                      WARNING: DO NOT EDIT THIS SECTION!                    " + m_CommentR);
                pSourceCode->Add(m_CommentL + "      This section gets automatically generated by the Resource Editor      " + m_CommentR);
                pSourceCode->Add(m_CommentL + "   And any data here will get overwritten, when the resources are updated   " + m_CommentR);
                pSourceCode->Add(m_CommentL + "****************************************************************************" + m_CommentR);
                pSourceCode->Insert(iResourcesEnd, String(m_CommentL + " [RESOURCES SECTION                                                         " + m_CommentR));
                iResourcesBegin = iResourcesEnd;
                iResourcesEnd++;
            }
            else
            {
                // add it before the first resource
                pSourceCode->Add(m_CommentL + "****************************************************************************" + m_CommentR);
                pSourceCode->Add(m_CommentL + "                      WARNING: DO NOT EDIT THIS SECTION!                    " + m_CommentR);
                pSourceCode->Add(m_CommentL + "      This section gets automatically generated by the Resource Editor      " + m_CommentR);
                pSourceCode->Add(m_CommentL + "   And any data here will get overwritten, when the resources are updated   " + m_CommentR);
                pSourceCode->Add(m_CommentL + "****************************************************************************" + m_CommentR);
                pSourceCode->Insert(iResourceFirst, m_CommentL + " [RESOURCES SECTION                                                         " + m_CommentR);
                iResourcesBegin = iResourceFirst;
                iResourceFirst++;
            }
        }
    }

    if (-1 == iResourcesEnd)
    {
        // error
        int iAnswer;
        Message
        (
            mbtError,
            "Failed to find/create Resources Section",
            "",
            "The Insert Resources dialog failed to locate or create the Resource"
            " Section to place your resources into.",
            "Ok",
            "",
            "",
            iAnswer
        );
    }
    return iResourcesEnd;
}
//---------------------------------------------------------------------------
bool __fastcall ZXParserManager::IsResourceIsUnique(const TStrings*& pSourceCode, const String& sResourceTag) const
{
    bool bIsUnique = true;

    int iResourcesBegin = FindLine(pSourceCode, String("[RESOURCES SECTION"));
    int iResourcesEnd   = FindLine(pSourceCode, String("]RESOURCES SECTION"), iResourcesBegin);

    //assert(iResourcesBegin != -1);
    //assert(iResourcesEnd   != -1);

    TStrings* SourceCode = const_cast<TStrings*>(pSourceCode);
    for (int i = iResourcesBegin + 1; i < iResourcesEnd && bIsUnique; i++)
    {
        if (i < SourceCode->Count && SourceCode->Strings[i].Pos(sResourceTag) == 1)
        {
            bIsUnique = false;
        }
    }

    return bIsUnique;
}
//---------------------------------------------------------------------------

