#include "CodeAnalysis/Core/DirectiveParser.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveParser::DirectiveParser(SharedPtr<Lexer> lexer,
                                 const DirectiveStack& context) noexcept
    : Parser{lexer},
      _context{context}
{
    lexer->setMode(LexerMode::Directive);
}

} // end namespace polyglot::CodeAnalysis
