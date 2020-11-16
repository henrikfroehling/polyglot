#include "polyglot/CodeAnalysis/Core/DirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/BinaryExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/ParenthesizedExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/PrefixUnaryExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BadDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ElseDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ElseIfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndIfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/RegionDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <vector>

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
