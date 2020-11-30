#include "polyglot/CodeAnalysis/Core/DirectiveParser.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveParser::DirectiveParser(SharedPtr<Lexer> lexer,
                                 const DirectiveStack& context,
                                 SharedPtr<SyntaxFacts> syntaxFacts) noexcept
    : Parser{lexer},
      _context{context},
      _ptrSyntaxFacts{std::move(syntaxFacts)}
{
    lexer->setMode(LexerMode::Directive);
}

} // end namespace polyglot::CodeAnalysis
