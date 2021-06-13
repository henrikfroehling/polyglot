#include "Delphi/Syntax/Expressions/DelphiPrefixUnaryExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiPrefixUnaryExpressionSyntax::DelphiPrefixUnaryExpressionSyntax(SyntaxKind syntaxKind,
                                                                     ISyntaxToken* operatorToken,
                                                                     DelphiExpressionSyntax* operandExpression) noexcept
    : DelphiExpressionSyntax{syntaxKind},
      _pOperatorToken{operatorToken},
      _pOperandExpression{operandExpression}
{
    _position = _pOperatorToken->position();
    adjustWidthAndFlags(_pOperatorToken);
    adjustWidthAndFlags(_pOperandExpression);
}

SyntaxVariant DelphiPrefixUnaryExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pOperatorToken);
        case 1: return SyntaxVariant::asNode(_pOperandExpression);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiPrefixUnaryExpressionSyntax* DelphiPrefixUnaryExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                             SyntaxKind syntaxKind,
                                                                             ISyntaxToken* operatorToken,
                                                                             DelphiExpressionSyntax* operandExpression) noexcept
{
    assert(operatorToken != nullptr);
    assert(operandExpression != nullptr);

    auto ptrPrefixUnaryExpression = std::make_unique<DelphiPrefixUnaryExpressionSyntax>(syntaxKind, operatorToken, operandExpression);
    return static_cast<DelphiPrefixUnaryExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPrefixUnaryExpression)));
}

} // end namespace polyglot::Delphi::Syntax
