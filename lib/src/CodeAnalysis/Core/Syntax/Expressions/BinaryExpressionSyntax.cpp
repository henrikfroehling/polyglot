#include "CodeAnalysis/Core/Syntax/Expressions/BinaryExpressionSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

BinaryExpressionSyntax::BinaryExpressionSyntax(SyntaxKind syntaxKind,
                                               ExpressionSyntax* leftExpression,
                                               LanguageSyntaxToken* operatorToken,
                                               ExpressionSyntax* rightExpression) noexcept
    : ExpressionSyntax{syntaxKind},
      _pLeftExpression{leftExpression},
      _pOperatorToken{operatorToken},
      _pRightExpression{rightExpression}
{
    _position = _pLeftExpression->position();
    adjustWidthAndFlags(_pLeftExpression);
    adjustWidthAndFlags(_pOperatorToken);
    adjustWidthAndFlags(_pRightExpression);
}

BinaryExpressionSyntax* BinaryExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                       SyntaxKind syntaxKind,
                                                       ExpressionSyntax* leftExpression,
                                                       LanguageSyntaxToken* operatorToken,
                                                       ExpressionSyntax* rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(operatorToken != nullptr);
    assert(rightExpression != nullptr);

    auto ptrBinaryExpression = std::make_unique<BinaryExpressionSyntax>(syntaxKind, leftExpression, operatorToken, rightExpression);
    return static_cast<BinaryExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrBinaryExpression)));
}

} // end namespace polyglot::CodeAnalysis
