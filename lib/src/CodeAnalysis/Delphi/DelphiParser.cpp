#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"

namespace polyglot::CodeAnalysis {

DelphiParser::DelphiParser(SourceText* sourceText) noexcept
    : Parser{std::make_unique<DelphiLexer>(sourceText)}
{}

void DelphiParser::parse() noexcept
{
    const auto start = std::chrono::steady_clock::now();
    lex();
    const auto end = std::chrono::steady_clock::now();

    std::cout << "Lexing took " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
}

void DelphiParser::parseUnitBody() noexcept
{

}

} // end namespace polyglot::CodeAnalysis
