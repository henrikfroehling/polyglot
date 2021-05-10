#include "PrefixUnaryExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

PrefixUnaryExpressionSyntax::PrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                                         ISyntaxToken* operatorToken,
                                                         ExpressionSyntax* operandExpression) noexcept
    : ExpressionSyntax{syntaxKind},
      _pOperatorToken{operatorToken},
      _pOperandExpression{operandExpression}
{
    _position = _pOperatorToken->position();
    adjustWidthAndFlags(_pOperatorToken);
    adjustWidthAndFlags(_pOperandExpression);
}

SyntaxVariant PrefixUnaryExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pOperatorToken);
        case 1: return SyntaxVariant::asNode(_pOperandExpression);
    }

    throw std::out_of_range{"index out of range"};
}

PrefixUnaryExpressionSyntax* PrefixUnaryExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 SyntaxKind syntaxKind,
                                                                 ISyntaxToken* operatorToken,
                                                                 ExpressionSyntax* operandExpression) noexcept
{
    assert(operatorToken != nullptr);
    assert(operandExpression != nullptr);

    auto ptrPrefixUnaryExpression = std::make_unique<PrefixUnaryExpressionSyntax>(syntaxKind, operatorToken, operandExpression);
    return dynamic_cast<PrefixUnaryExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPrefixUnaryExpression)));
}

} // end namespace polyglot::Core::Syntax
