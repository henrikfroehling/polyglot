#include "Delphi/Syntax/Expressions/DelphiAssignmentExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiAssignmentExpressionSyntax::DelphiAssignmentExpressionSyntax(DelphiExpressionSyntax* leftExpression,
                                                                   ISyntaxToken* colonEqualToken,
                                                                   DelphiExpressionSyntax* rightExpression) noexcept
    : DelphiExpressionSyntax{SyntaxKind::AssignmentExpression},
      _pLeftExpression{leftExpression},
      _pColonEqualToken{colonEqualToken},
      _pRightExpression{rightExpression}
{
    _position = _pLeftExpression->position();
    adjustWidthAndFlags(_pLeftExpression);
    adjustWidthAndFlags(_pColonEqualToken);
    adjustWidthAndFlags(_pRightExpression);
}

SyntaxVariant DelphiAssignmentExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pLeftExpression);
        case 1: return SyntaxVariant::asToken(_pColonEqualToken);
        case 2: return SyntaxVariant::asNode(_pRightExpression);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiAssignmentExpressionSyntax* DelphiAssignmentExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                           DelphiExpressionSyntax* leftExpression,
                                                                           ISyntaxToken* colonEqualToken,
                                                                           DelphiExpressionSyntax* rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(colonEqualToken != nullptr);
    assert(colonEqualToken->syntaxKind() == SyntaxKind::ColonEqualToken);
    assert(rightExpression != nullptr);

    auto ptrAssignmentExpressionSyntax = std::make_unique<DelphiAssignmentExpressionSyntax>(leftExpression, colonEqualToken, rightExpression);
    return static_cast<DelphiAssignmentExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrAssignmentExpressionSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
