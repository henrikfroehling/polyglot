#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/BinaryExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

BinaryExpressionSyntax::BinaryExpressionSyntax(SyntaxKind syntaxKind,
                                               ExpressionSyntax* leftExpression,
                                               SyntaxToken* operatorToken,
                                               ExpressionSyntax* rightExpression) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrLeftExpression{leftExpression},
      _ptrOperatorToken{operatorToken},
      _ptrRightExpression{rightExpression}
{}

BinaryExpressionSyntax* BinaryExpressionSyntax::create(SyntaxKind syntaxKind,
                                                       ExpressionSyntax* leftExpression,
                                                       SyntaxToken* operatorToken,
                                                       ExpressionSyntax* rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(operatorToken != nullptr);
    assert(rightExpression != nullptr);

    auto ptrBinaryExpression = std::make_unique<BinaryExpressionSyntax>(syntaxKind, leftExpression, operatorToken, rightExpression);
    return static_cast<BinaryExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrBinaryExpression)));
}

} // end namespace polyglot::CodeAnalysis
