#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

LiteralExpressionSyntax::LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                                 Ptr<SyntaxToken> token) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrToken{token}
{}

Ptr<LiteralExpressionSyntax> LiteralExpressionSyntax::create(SyntaxKind syntaxKind,
                                                             Ptr<SyntaxToken> token) noexcept
{
    assert(token != nullptr);
    auto ptrLiteralExpression = std::make_unique<LiteralExpressionSyntax>(syntaxKind, token);
    return static_cast<LiteralExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrLiteralExpression)));
}

} // end namespace polyglot::CodeAnalysis
