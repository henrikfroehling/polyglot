#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/ParenthesizedExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                                             SharedPtr<SyntaxToken> openParenthesisToken,
                                                             SharedPtr<ExpressionSyntax> expression,
                                                             SharedPtr<SyntaxToken> closeParenthesisToken) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrOpenParenthesisToken{std::move(openParenthesisToken)},
      _ptrExpression{std::move(expression)},
      _ptrCloseParenthesisToken{std::move(closeParenthesisToken)}
{}

SharedPtr<ParenthesizedExpressionSyntax> ParenthesizedExpressionSyntax::create(SharedPtr<SyntaxToken> openParenthesisToken,
                                                                               SharedPtr<ExpressionSyntax> expression,
                                                                               SharedPtr<SyntaxToken> closeParenthesisToken) noexcept
{
    assert(openParenthesisToken != nullptr);
    assert(openParenthesisToken->syntaxKind() == SyntaxKind::OpenParenthesisToken);
    assert(expression != nullptr);
    assert(closeParenthesisToken != nullptr);
    assert(closeParenthesisToken->syntaxKind() == SyntaxKind::CloseParenthesisToken);

    return std::make_shared<ParenthesizedExpressionSyntax>(SyntaxKind::ParenthesizedExpression, std::move(openParenthesisToken),
                                                           std::move(expression), std::move(closeParenthesisToken));
}

} // end namespace polyglot::CodeAnalysis
