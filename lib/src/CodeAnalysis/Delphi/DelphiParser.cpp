#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"

namespace polyglot::CodeAnalysis {

DelphiParser::DelphiParser(std::string_view code) noexcept
    : Parser{std::make_unique<DelphiLexer>(std::move(code))}
{}

void DelphiParser::parse() noexcept
{
    const auto start = std::chrono::steady_clock::now();
    lex();
    const auto end = std::chrono::steady_clock::now();

    std::cout << "Token Count: " << _tokens.size() << "\n";
    std::cout << "Lexing took " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";
}

} // end namespace polyglot::CodeAnalysis
