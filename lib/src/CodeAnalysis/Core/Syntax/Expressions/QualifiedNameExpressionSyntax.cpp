#include "CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

QualifiedNameExpressionSyntax::QualifiedNameExpressionSyntax(NameExpressionSyntax* leftExpression,
                                                             LanguageSyntaxToken* dotToken,
                                                             SimpleNameExpressionSyntax* rightExpression) noexcept
    : NameExpressionSyntax{SyntaxKind::QualifiedNameExpression},
      _pLeftExpression{leftExpression},
      _pDotToken{dotToken},
      _pRightExpression{rightExpression}
{
    _position = _pLeftExpression->position();
}

} // end namespace polyglot::CodeAnalysis
