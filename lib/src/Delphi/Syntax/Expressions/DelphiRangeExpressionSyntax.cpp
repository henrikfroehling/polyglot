#include "Delphi/Syntax/Expressions/DelphiRangeExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiRangeExpressionSyntax::DelphiRangeExpressionSyntax(DelphiExpressionSyntax* leftExpression,
                                                         ISyntaxToken* dotDotToken,
                                                         DelphiExpressionSyntax* rightExpression) noexcept
    : DelphiExpressionSyntax{SyntaxKind::RangeExpression},
      _pLeftExpression{leftExpression},
      _pDotDotToken{dotDotToken},
      _pRightExpression{rightExpression}
{}

SyntaxVariant DelphiRangeExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pLeftExpression);
        case 1: return SyntaxVariant::asToken(_pDotDotToken);
        case 2: return SyntaxVariant::asNode(_pRightExpression);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiRangeExpressionSyntax* DelphiRangeExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 DelphiExpressionSyntax* leftExpression,
                                                                 ISyntaxToken* dotDotToken,
                                                                 DelphiExpressionSyntax* rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(dotDotToken != nullptr);
    assert(dotDotToken->syntaxKind() == SyntaxKind::DotDotToken);
    assert(rightExpression != nullptr);

    auto ptrRangeExpression = std::make_unique<DelphiRangeExpressionSyntax>(leftExpression, dotDotToken, rightExpression);
    return static_cast<DelphiRangeExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrRangeExpression)));
}

} // end namespace polyglot::Delphi::Syntax
