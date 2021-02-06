#include "CodeAnalysis/Core/Syntax/Expressions/ParenthesizedExpressionSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                                             LanguageSyntaxToken* openParenthesisToken,
                                                             ExpressionSyntax* expression,
                                                             LanguageSyntaxToken* closeParenthesisToken) noexcept
    : ExpressionSyntax{syntaxKind},
      _pOpenParenthesisToken{openParenthesisToken},
      _pExpression{expression},
      _pCloseParenthesisToken{closeParenthesisToken}
{
    _position = _pOpenParenthesisToken->position();
    adjustWidthAndFlags(_pOpenParenthesisToken);
    adjustWidthAndFlags(_pExpression);
    adjustWidthAndFlags(_pCloseParenthesisToken);
}

ParenthesizedExpressionSyntax* ParenthesizedExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                     LanguageSyntaxToken* openParenthesisToken,
                                                                     ExpressionSyntax* expression,
                                                                     LanguageSyntaxToken* closeParenthesisToken) noexcept
{
    assert(openParenthesisToken != nullptr);
    assert(openParenthesisToken->syntaxKind() == SyntaxKind::OpenParenthesisToken);
    assert(expression != nullptr);
    assert(closeParenthesisToken != nullptr);
    assert(closeParenthesisToken->syntaxKind() == SyntaxKind::CloseParenthesisToken);

    auto ptrParenthesizedExpression = std::make_unique<ParenthesizedExpressionSyntax>(SyntaxKind::ParenthesizedExpression, openParenthesisToken,
                                                                                      expression, closeParenthesisToken);

    return static_cast<ParenthesizedExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrParenthesizedExpression)));
}

} // end namespace polyglot::CodeAnalysis
