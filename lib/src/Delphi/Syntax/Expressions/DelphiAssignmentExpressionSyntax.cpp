#include "Delphi/Syntax/Expressions/DelphiAssignmentExpressionSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiAssignmentExpressionSyntax::DelphiAssignmentExpressionSyntax(DelphiExpressionSyntax* leftExpression,
                                                                   Core::Syntax::ISyntaxToken* colonEqualToken,
                                                                   DelphiExpressionSyntax* rightExpression) noexcept
    : DelphiExpressionSyntax{SyntaxKind::AssignmentExpression},
      _pLeftExpression{leftExpression},
      _pColonEqualToken{colonEqualToken},
      _pRightExpression{rightExpression}
{}

DelphiAssignmentExpressionSyntax* DelphiAssignmentExpressionSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                           DelphiExpressionSyntax* leftExpression,
                                                                           Core::Syntax::ISyntaxToken* colonEqualToken,
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
