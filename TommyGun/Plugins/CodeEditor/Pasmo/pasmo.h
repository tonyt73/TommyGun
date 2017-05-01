//---------------------------------------------------------------------------
#ifndef PasmoH
#define PasmoH
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
#if defined(CPPBUILDER)
class Pasmo
{
public:
    static bool Compile(const std::string& infile, std::string& output);
private:
    static std::string ChangeExt(const std::string& infile, const std::string& outFile);
};
#endif // !defined(CONSOLE)
//---------------------------------------------------------------------------
#endif // PasmoH