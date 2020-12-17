#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <polyglot/CodeAnalysis/CodeAnalysis.hpp>
#include <polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp>

std::string readFile(const std::string& filename);

int main(int argc,
         char** argv)
{
    using namespace polyglot::CodeAnalysis;

    const std::string sourceText = readFile(argv[1]);
    auto ptrSyntaxTree = Delphi::parseSourceText(argv[1], sourceText);

    std::string str;
    std::getline(std::cin, str);

    return 0;
}

std::string readFile(const std::string& filename)
{
    std::ifstream file{filename};
    std::string str;

    file.seekg(0, std::ios::end);
    str.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());

    return str;
}
