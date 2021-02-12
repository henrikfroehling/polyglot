#include "CodeAnalysis/Core/Syntax/Expressions/PrefixUnaryExpressionSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

PrefixUnaryExpressionSyntax::PrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                                         LanguageSyntaxToken* operatorToken,
                                                         ExpressionSyntax* operandExpression) noexcept
    : ExpressionSyntax{syntaxKind},
      _pOperatorToken{operatorToken},
      _pOperandExpression{operandExpression}
{
    _position = _pOperatorToken->position();
    adjustWidthAndFlags(_pOperatorToken);
    adjustWidthAndFlags(_pOperandExpression);
}

LanguageSyntaxNode* PrefixUnaryExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pOperatorToken;
        case 1: return _pOperandExpression;
    }

    throw std::out_of_range{"index out of range"};
}

PrefixUnaryExpressionSyntax* PrefixUnaryExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 SyntaxKind syntaxKind,
                                                                 LanguageSyntaxToken* operatorToken,
                                                                 ExpressionSyntax* operandExpression) noexcept
{
    assert(operatorToken != nullptr);
    assert(operandExpression != nullptr);

    auto ptrPrefixUnaryExpression = std::make_unique<PrefixUnaryExpressionSyntax>(syntaxKind, operatorToken, operandExpression);
    return static_cast<PrefixUnaryExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPrefixUnaryExpression)));
}

} // end namespace polyglot::CodeAnalysis
