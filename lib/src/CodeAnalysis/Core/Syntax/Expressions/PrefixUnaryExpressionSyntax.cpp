#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/PrefixUnaryExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

PrefixUnaryExpressionSyntax::PrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                                         SyntaxTokenPtr operatorToken,
                                                         ExpressionSyntaxPtr operandExpression) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrOperatorToken{std::move(operatorToken)},
      _ptrOperandExpression{std::move(operandExpression)}
{}

PrefixUnaryExpressionSyntaxPtr PrefixUnaryExpressionSyntax::create(SyntaxKind syntaxKind,
                                                                   SyntaxTokenPtr operatorToken,
                                                                   ExpressionSyntaxPtr operandExpression) noexcept
{
    assert(operatorToken != nullptr);
    assert(operandExpression != nullptr);

    return std::make_shared<PrefixUnaryExpressionSyntax>(syntaxKind, std::move(operatorToken), std::move(operandExpression));
}

} // end namespace polyglot::CodeAnalysis
