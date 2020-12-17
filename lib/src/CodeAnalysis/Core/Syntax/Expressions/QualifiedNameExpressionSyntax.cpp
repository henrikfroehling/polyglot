#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

QualifiedNameExpressionSyntax::QualifiedNameExpressionSyntax(NameExpressionSyntax* leftExpression,
                                                             SyntaxToken* dotToken,
                                                             SimpleNameExpressionSyntax* rightExpression) noexcept
    : NameExpressionSyntax{SyntaxKind::QualifiedNameExpression},
      _ptrLeftExpression{leftExpression},
      _ptrDotToken{dotToken},
      _ptrRightExpression{rightExpression}
{
    _position = _ptrLeftExpression->position();
}

} // end namespace polyglot::CodeAnalysis
