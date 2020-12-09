#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/PrefixUnaryExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

PrefixUnaryExpressionSyntax::PrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                                         SyntaxToken* operatorToken,
                                                         ExpressionSyntax* operandExpression) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrOperatorToken{operatorToken},
      _ptrOperandExpression{operandExpression}
{}

PrefixUnaryExpressionSyntax* PrefixUnaryExpressionSyntax::create(SyntaxKind syntaxKind,
                                                                 SyntaxToken* operatorToken,
                                                                 ExpressionSyntax* operandExpression) noexcept
{
    assert(operatorToken != nullptr);
    assert(operandExpression != nullptr);

    auto ptrPrefixUnaryExpression = std::make_unique<PrefixUnaryExpressionSyntax>(syntaxKind, operatorToken, operandExpression);
    return static_cast<PrefixUnaryExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrPrefixUnaryExpression)));
}

} // end namespace polyglot::CodeAnalysis
