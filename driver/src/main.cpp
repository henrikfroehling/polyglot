#include <fstream>
#include <iostream>
#include <streambuf>
#include <polyglot/Core/Types.hpp>
#include <polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp>

pg_string readFile(const pg_string& filename);

int main(int argc,
         pg_char** argv)
{
    const pg_string sourceText = readFile(argv[1]);
    auto ptrSyntaxTree = polyglot::Delphi::Syntax::IDelphiSyntaxTree::parseSourceText(argv[1], sourceText);

    std::string str;
    std::getline(std::cin, str);

    return 0;
}

pg_string readFile(const pg_string& filename)
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
