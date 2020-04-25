#include <iostream>
#include <string>
#include <polyglot/CodeAnalysis/Delphi/DelphiParser.hpp>

int main()
{
    using namespace polyglot::CodeAnalysis;

    const std::string code{"procedure Hello(const aName: String);\n"
                           "var\n"
                           "  lText: String;\n"
                           "begin\n"
                           "  lText := 'Hello, \"' + aName + '\"!';\n"
                           "  WriteLn(lText);\n"
                           "end;\n"};

    DelphiParser parser{code};
    parser.parse();

    std::cout << "Token Count: " << parser.tokenCount() << "\n";
    std::cout << "Lexing took " << parser.lexingDuration() << " ms\n";

    return 0;
}
