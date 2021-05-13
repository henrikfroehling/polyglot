#include "Core/Syntax/Expressions/BinaryExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

BinaryExpressionSyntax::BinaryExpressionSyntax(SyntaxKind syntaxKind,
                                               ExpressionSyntax* leftExpression,
                                               ISyntaxToken* operatorToken,
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

SyntaxVariant BinaryExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pLeftExpression);
        case 1: return SyntaxVariant::asToken(_pOperatorToken);
        case 2: return SyntaxVariant::asNode(_pRightExpression);
    }

    throw std::out_of_range{"index out of range"};
}

BinaryExpressionSyntax* BinaryExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                       SyntaxKind syntaxKind,
                                                       ExpressionSyntax* leftExpression,
                                                       ISyntaxToken* operatorToken,
                                                       ExpressionSyntax* rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(operatorToken != nullptr);
    assert(rightExpression != nullptr);

    auto ptrBinaryExpression = std::make_unique<BinaryExpressionSyntax>(syntaxKind, leftExpression, operatorToken, rightExpression);
    return dynamic_cast<BinaryExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrBinaryExpression)));
}

} // end namespace polyglot::Core::Syntax
