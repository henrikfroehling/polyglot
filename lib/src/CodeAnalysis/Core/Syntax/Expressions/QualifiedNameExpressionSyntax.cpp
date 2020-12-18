#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

QualifiedNameExpressionSyntax::QualifiedNameExpressionSyntax(NameExpressionSyntax* leftExpression,
                                                             SyntaxToken* dotToken,
                                                             SimpleNameExpressionSyntax* rightExpression) noexcept
    : NameExpressionSyntax{SyntaxKind::QualifiedNameExpression},
      _pLeftExpression{leftExpression},
      _pDotToken{dotToken},
      _pRightExpression{rightExpression}
{
    _position = _pLeftExpression->position();
}

} // end namespace polyglot::CodeAnalysis
