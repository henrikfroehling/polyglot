#include "CodeAnalysis/Core/Syntax/Expressions/BinaryExpressionSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

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

LanguageSyntaxNode* BinaryExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pLeftExpression;
        case 1: return _pOperatorToken;
        case 2: return _pRightExpression;
    }

    throw std::out_of_range{"index out of range"};
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
