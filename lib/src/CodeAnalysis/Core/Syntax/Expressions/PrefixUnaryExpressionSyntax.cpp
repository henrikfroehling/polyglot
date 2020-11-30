#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/PrefixUnaryExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

PrefixUnaryExpressionSyntax::PrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                                         SharedPtr<SyntaxToken> operatorToken,
                                                         SharedPtr<ExpressionSyntax> operandExpression) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrOperatorToken{std::move(operatorToken)},
      _ptrOperandExpression{std::move(operandExpression)}
{}

SharedPtr<PrefixUnaryExpressionSyntax> PrefixUnaryExpressionSyntax::create(SyntaxKind syntaxKind,
                                                                           SharedPtr<SyntaxToken> operatorToken,
                                                                           SharedPtr<ExpressionSyntax> operandExpression) noexcept
{
    assert(operatorToken != nullptr);
    assert(operandExpression != nullptr);

    return std::make_shared<PrefixUnaryExpressionSyntax>(syntaxKind, std::move(operatorToken), std::move(operandExpression));
}

} // end namespace polyglot::CodeAnalysis
