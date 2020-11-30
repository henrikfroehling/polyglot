#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/BinaryExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

BinaryExpressionSyntax::BinaryExpressionSyntax(SyntaxKind syntaxKind,
                                               SharedPtr<ExpressionSyntax> leftExpression,
                                               SharedPtr<SyntaxToken> operatorToken,
                                               SharedPtr<ExpressionSyntax> rightExpression) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrLeftExpression{std::move(leftExpression)},
      _ptrOperatorToken{std::move(operatorToken)},
      _ptrRightExpression{std::move(rightExpression)}
{}

SharedPtr<BinaryExpressionSyntax> BinaryExpressionSyntax::create(SyntaxKind syntaxKind,
                                                                 SharedPtr<ExpressionSyntax> leftExpression,
                                                                 SharedPtr<SyntaxToken> operatorToken,
                                                                 SharedPtr<ExpressionSyntax> rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(operatorToken != nullptr);
    assert(rightExpression != nullptr);

    return std::make_shared<BinaryExpressionSyntax>(syntaxKind, std::move(leftExpression),
                                                    std::move(operatorToken), std::move(rightExpression));
}

} // end namespace polyglot::CodeAnalysis
