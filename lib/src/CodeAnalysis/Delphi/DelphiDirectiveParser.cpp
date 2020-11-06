#include "polyglot/CodeAnalysis/Delphi/DelphiDirectiveParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiDirectiveParser::DelphiDirectiveParser(std::shared_ptr<Lexer> lexer) noexcept
    : Parser{lexer}
{
    lexer->setMode(LexerMode::Directive);
}

SyntaxNodePtr DelphiDirectiveParser::parseDirective(bool isActive,
                                                    bool endIsActive,
                                                    bool isFirstAfterTokenInFile,
                                                    bool isAfterNonWhitespaceOnLine) noexcept
{
    return nullptr;
}

} // end namespace polyglot::CodeAnalysis
