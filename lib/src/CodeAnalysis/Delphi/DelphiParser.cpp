#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"
#include <memory>
#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"

namespace polyglot::CodeAnalysis {

DelphiParser::DelphiParser(std::string code) noexcept
    : Parser{std::make_unique<DelphiLexer>(code)}
{}

} // end namespace polyglot::CodeAnalysis
