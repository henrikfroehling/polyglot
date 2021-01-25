#include "CodeAnalysis/Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

LiteralExpressionSyntax::LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                                 SyntaxToken* token) noexcept
    : ExpressionSyntax{syntaxKind},
      _pToken{token}
{
    _position = _pToken->position();
}

LiteralExpressionSyntax* LiteralExpressionSyntax::create(SyntaxKind syntaxKind,
                                                         SyntaxToken* token) noexcept
{
    assert(token != nullptr);
    auto ptrLiteralExpression = std::make_unique<LiteralExpressionSyntax>(syntaxKind, token);
    return static_cast<LiteralExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrLiteralExpression)));
}

} // end namespace polyglot::CodeAnalysis
