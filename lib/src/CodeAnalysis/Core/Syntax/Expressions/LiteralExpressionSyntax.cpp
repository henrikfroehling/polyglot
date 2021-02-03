#include "CodeAnalysis/Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxPool.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

LiteralExpressionSyntax::LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                                 LanguageSyntaxToken* token) noexcept
    : ExpressionSyntax{syntaxKind},
      _pToken{token}
{
    _position = _pToken->position();
    adjustWidthAndFlags(_pToken);
}

LiteralExpressionSyntax* LiteralExpressionSyntax::create(SyntaxKind syntaxKind,
                                                         LanguageSyntaxToken* token) noexcept
{
    assert(token != nullptr);
    auto ptrLiteralExpression = std::make_unique<LiteralExpressionSyntax>(syntaxKind, token);
    return static_cast<LiteralExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrLiteralExpression)));
}

} // end namespace polyglot::CodeAnalysis
