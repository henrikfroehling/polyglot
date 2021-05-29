#include "Delphi/Syntax/Expressions/DelphiQualifiedNameExpressionSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Expressions/DelphiSimpleNameExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiQualifiedNameExpressionSyntax::DelphiQualifiedNameExpressionSyntax(DelphiNameExpressionSyntax* leftExpression,
                                                                         ISyntaxToken* dotToken,
                                                                         DelphiSimpleNameExpressionSyntax* rightExpression) noexcept
    : DelphiNameExpressionSyntax{SyntaxKind::QualifiedNameExpression},
      _pLeftExpression{leftExpression},
      _pDotToken{dotToken},
      _pRightExpression{rightExpression}
{
    _position = _pLeftExpression->position();
    adjustWidthAndFlags(_pLeftExpression);
    adjustWidthAndFlags(_pDotToken);
    adjustWidthAndFlags(_pRightExpression);
}

SyntaxVariant DelphiQualifiedNameExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pLeftExpression);
        case 1: return SyntaxVariant::asToken(_pDotToken);
        case 2: return SyntaxVariant::asNode(_pRightExpression);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiQualifiedNameExpressionSyntax* DelphiQualifiedNameExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                                 DelphiNameExpressionSyntax* leftExpression,
                                                                                 ISyntaxToken* dotToken,
                                                                                 DelphiSimpleNameExpressionSyntax* rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    assert(rightExpression != nullptr);

    auto ptrQualifiedNameExpressionSyntax = std::make_unique<DelphiQualifiedNameExpressionSyntax>(leftExpression, dotToken, rightExpression);
    return static_cast<DelphiQualifiedNameExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrQualifiedNameExpressionSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
