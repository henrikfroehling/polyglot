#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <polyglot/CodeAnalysis/Core/SyntaxToken.hpp>
#include <polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp>
#include <polyglot/CodeAnalysis/Delphi/DelphiSyntaxFacts.hpp>

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

    DelphiLexer lexer{code};
    SyntaxToken token{};
    std::vector<SyntaxToken> tokens{};

    const auto start = std::chrono::steady_clock::now();

    do
    {
        token = lexer.nextToken();
        tokens.push_back(token);
        std::cout << "Token => "
                  << "kind = " << DelphiSyntaxFacts::syntaxKindName(token.kind)
                  << " // position = " << token.position
                  << " // text = \"" << token.text << "\"\n";
    }
    while (token.kind != SyntaxKind::EndOfTileToken);

    const auto end = std::chrono::steady_clock::now();
    std::cout << "Token Count: " << tokens.size() << "\n";
    std::cout << "Lexing took " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    return 0;
}
