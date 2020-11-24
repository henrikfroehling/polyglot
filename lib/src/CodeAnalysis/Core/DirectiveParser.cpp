#include "polyglot/CodeAnalysis/Core/DirectiveParser.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveParser::DirectiveParser(std::shared_ptr<Lexer> lexer,
                                 const DirectiveStack& context,
                                 std::shared_ptr<SyntaxFacts> syntaxFacts) noexcept
    : Parser{lexer},
      _context{context},
      _ptrSyntaxFacts{std::move(syntaxFacts)}
{
    lexer->setMode(LexerMode::Directive);
}

} // end namespace polyglot::CodeAnalysis
