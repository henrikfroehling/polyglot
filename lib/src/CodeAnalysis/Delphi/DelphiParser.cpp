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

#ifdef COLLECT_BENCHMARKS
    _ptrLexer->benchmark().setDuration(std::chrono::duration<double, std::milli>(end - start).count());
    std::cout << _ptrLexer->benchmark() << "\n";
#endif
}

void DelphiParser::parseUnitBody() noexcept
{

}

} // end namespace polyglot::CodeAnalysis
