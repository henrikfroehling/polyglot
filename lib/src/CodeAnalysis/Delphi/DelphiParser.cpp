#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"

namespace polyglot::CodeAnalysis
{

DelphiParser::DelphiParser(SourceText* sourceText) noexcept
    : Parser{std::make_unique<DelphiLexer>(sourceText)}
{}

void DelphiParser::parse() noexcept
{
    Parser::parse();
}

} // end namespace polyglot::CodeAnalysis
