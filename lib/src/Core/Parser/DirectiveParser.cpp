#include "Core/Parser/DirectiveParser.hpp"

namespace polyglot::Core::Parser
{

DirectiveParser::DirectiveParser(SharedPtr<Lexer> lexer,
                                 const DirectiveStack& context) noexcept
    : Parser{lexer},
      _context{context}
{
    lexer->setMode(LexerMode::Directive);
}

} // end namespace polyglot::Core::Parser
