#include "Delphi/Syntax/Expressions/DelphiBinaryExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiBinaryExpressionSyntax::DelphiBinaryExpressionSyntax(SyntaxKind syntaxKind,
                                                           DelphiExpressionSyntax* leftExpression,
                                                           ISyntaxToken* operatorToken,
                                                           DelphiExpressionSyntax* rightExpression) noexcept
    : DelphiExpressionSyntax{syntaxKind},
      _pLeftExpression{leftExpression},
      _pOperatorToken{operatorToken},
      _pRightExpression{rightExpression}
{
    _position = _pLeftExpression->position();
    adjustWidthAndFlags(_pLeftExpression);
    adjustWidthAndFlags(_pOperatorToken);
    adjustWidthAndFlags(_pRightExpression);
}

SyntaxVariant DelphiBinaryExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pLeftExpression);
        case 1: return SyntaxVariant::asToken(_pOperatorToken);
        case 2: return SyntaxVariant::asNode(_pRightExpression);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiBinaryExpressionSyntax* DelphiBinaryExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                   SyntaxKind syntaxKind,
                                                                   DelphiExpressionSyntax* leftExpression,
                                                                   ISyntaxToken* operatorToken,
                                                                   DelphiExpressionSyntax* rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(operatorToken != nullptr);
    assert(rightExpression != nullptr);

    auto ptrBinaryExpression = std::make_unique<DelphiBinaryExpressionSyntax>(syntaxKind, leftExpression, operatorToken, rightExpression);
    return static_cast<DelphiBinaryExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrBinaryExpression)));
}

} // end namespace polyglot::Delphi::Syntax
