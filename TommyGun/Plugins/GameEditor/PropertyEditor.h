//---------------------------------------------------------------------------
#ifndef PropertyEditorH
#define PropertyEditorH
//-- VCL --------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
//-- STL --------------------------------------------------------------------
#include <vector>
//-- APP --------------------------------------------------------------------
#include "PropertyObject.h"
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GameEditor
    {
        class PropertyEditor
        {
        public:
            enum NodeType { ntInt, ntString, ntBool, ntFloat };

        private:
            struct TProperty
            {
                public:
                    explicit TProperty(const AnsiString& key)       { Key = key;                                    }

                    void SetInt(int value)                          { Value = IntToStr(value);                      }
                    void SetBool(bool value)                        { Value = BoolToStr(value);                     }
                    void SetFloat(float value)                      { Value = FloatToStrF(value, ffFixed, 2, 10);   }
                    void SetString(const AnsiString& value)         { Value = value;                                }
                    int  GetInt()                                   { return StrToInt(Value);                       }
                    bool GetBool()                                  { return Value.LowerCase() == "true";           }
                    float GetFloat()                                { return StrToFloat(Value);                     }
                    const AnsiString& GetString()                   { return Value;                                 }
                    AnsiString      Key;
                    AnsiString      Value;
            };
            typedef std::vector<TProperty*> TPropertyList;

            struct TPropertyNode
            {
                TTreeNode*      Node;
                PropertyObject* Owner;
                TPropertyList   Properties;
            };
            typedef std::vector<TPropertyNode*> TPropertyNodeList;
            typedef std::vector<TTreeNode*>     TPropertyNodesList;

            TTreeView*          m_PropertyView;
            TValueListEditor*   m_PropertyEditor;
            TPropertyNodeList   m_Nodes;
            int                 m_CurrentNode;
            int                 m_CurrentProperty;

            void    __fastcall  SelectNode(int node);

        public:
                    __fastcall  PropertyEditor();
                    __fastcall ~PropertyEditor();

            void    __fastcall  Init(TTreeView* propertyView, TValueListEditor* propertyEditor);

            int     __fastcall  AddRootNode(PropertyObject* owner, const AnsiString& name, int iconIndex);
            int     __fastcall  AddProperty(int node, const AnsiString& key, int value);
            int     __fastcall  AddProperty(int node, const AnsiString& key, const AnsiString& value);
            int     __fastcall  AddProperty(int node, const AnsiString& key, bool value);
            int     __fastcall  AddProperty(int node, const AnsiString& key, float value);
            void    __fastcall  UpdateProperty(int node, int property, int value);
            void    __fastcall  UpdateProperty(int node, int property, const AnsiString& value);
            void    __fastcall  UpdateProperty(int node, int property, bool value);
            void    __fastcall  UpdateProperty(int node, int property, float value);
            void    __fastcall  GetProperty(int node, int property, int& value);
            void    __fastcall  GetProperty(int node, int property, AnsiString& value);
            void    __fastcall  GetProperty(int node, int property, bool& value);
            void    __fastcall  GetProperty(int node, int property, float& value);

            void    __fastcall  SetActiveNode(const AnsiString& node);
            void    __fastcall  SetItemText(int row, AnsiString value);
            void    __fastcall  OnChange(TTreeNode* node);
            void    __fastcall  OnSelect(int row);
            void    __fastcall  OnItemChanged();
            void    __fastcall  OnItemExit();

            int     __fastcall  GetNode() const     { return m_CurrentNode;     }
            int     __fastcall  GetProperty() const { return m_CurrentProperty; }
        };
    }
}
//---------------------------------------------------------------------------
#endif
