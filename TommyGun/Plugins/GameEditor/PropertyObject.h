//---------------------------------------------------------------------------
#ifndef PropertyObjectH
#define PropertyObjectH
//---------------------------------------------------------------------------
namespace Scorpio
{
    namespace GameEditor
    {
        class PropertyObject
        {
        public:
            virtual void __fastcall OnPropertyChanged(int node) = 0;
            virtual void __fastcall OnPropertyRefresh() = 0;
        };
    }
}
//---------------------------------------------------------------------------
#endif