#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <streambuf>
#include <polyglot/Core/Types.hpp>
#include <polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp>

pg_string readFile(const std::string& filename);

int main(int argc,
         char** argv)
{
    const std::string filenameArgument{argv[1]};

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    pg_string filename = converter.from_bytes(filenameArgument);

    const pg_string sourceText = readFile(filenameArgument);
    auto ptrSyntaxTree = polyglot::Delphi::Syntax::IDelphiSyntaxTree::parseSourceText(filename, sourceText);

    std::string str;
    std::getline(std::cin, str);

    return 0;
}

pg_string readFile(const std::string& filename)
{
    std::wifstream file{filename};
    pg_string str;

    file.seekg(0, std::ios::end);
    str.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<pg_char>(file)),
                std::istreambuf_iterator<pg_char>());

    return str;
}
