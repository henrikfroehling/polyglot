#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

LiteralExpressionSyntax::LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                                 SyntaxTokenPtr token) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrToken{std::move(token)}
{}

LiteralExpressionSyntaxPtr LiteralExpressionSyntax::create(SyntaxKind syntaxKind,
                                                           SyntaxTokenPtr token) noexcept
{
    assert(token != nullptr);
    return std::make_shared<LiteralExpressionSyntax>(syntaxKind, std::move(token));
}

} // end namespace polyglot::CodeAnalysis
