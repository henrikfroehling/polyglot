#include "polyglot/CodeAnalysis/Delphi/DelphiDirectiveParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiDirectiveParser::DelphiDirectiveParser(std::shared_ptr<Lexer> lexer,
                                             const DirectiveStack& context) noexcept
    : Parser{lexer},
      _context{context}
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
