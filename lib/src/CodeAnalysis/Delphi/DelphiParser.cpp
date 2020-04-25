#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"
#include <chrono>
#include <memory>
#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"

namespace polyglot::CodeAnalysis {

DelphiParser::DelphiParser(std::string code) noexcept
    : Parser{std::make_unique<DelphiLexer>(code)},
      _lexingDuration{}
{}

void DelphiParser::parse() noexcept
{
    const auto start = std::chrono::steady_clock::now();
    lex();
    const auto end = std::chrono::steady_clock::now();
    _lexingDuration = std::chrono::duration<double, std::milli>(end - start).count();
}

} // end namespace polyglot::CodeAnalysis
