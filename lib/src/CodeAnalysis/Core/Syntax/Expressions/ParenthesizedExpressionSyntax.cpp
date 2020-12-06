#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/ParenthesizedExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                                             Ptr<SyntaxToken> openParenthesisToken,
                                                             Ptr<ExpressionSyntax> expression,
                                                             Ptr<SyntaxToken> closeParenthesisToken) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrOpenParenthesisToken{openParenthesisToken},
      _ptrExpression{expression},
      _ptrCloseParenthesisToken{closeParenthesisToken}
{}

Ptr<ParenthesizedExpressionSyntax> ParenthesizedExpressionSyntax::create(Ptr<SyntaxToken> openParenthesisToken,
                                                                         Ptr<ExpressionSyntax> expression,
                                                                         Ptr<SyntaxToken> closeParenthesisToken) noexcept
{
    assert(openParenthesisToken != nullptr);
    assert(openParenthesisToken->syntaxKind() == SyntaxKind::OpenParenthesisToken);
    assert(expression != nullptr);
    assert(closeParenthesisToken != nullptr);
    assert(closeParenthesisToken->syntaxKind() == SyntaxKind::CloseParenthesisToken);

    auto ptrParenthesizedExpression = std::make_unique<ParenthesizedExpressionSyntax>(SyntaxKind::ParenthesizedExpression, openParenthesisToken,
                                                                                      expression, closeParenthesisToken);

    return static_cast<ParenthesizedExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrParenthesizedExpression)));
}

} // end namespace polyglot::CodeAnalysis
