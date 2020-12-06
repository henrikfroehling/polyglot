#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

QualifiedNameExpressionSyntax::QualifiedNameExpressionSyntax(Ptr<NameExpressionSyntax> leftExpression,
                                                             Ptr<SyntaxToken> dotToken,
                                                             Ptr<SimpleNameExpressionSyntax> rightExpression) noexcept
    : NameExpressionSyntax{SyntaxKind::QualifiedNameExpression},
      _ptrLeftExpression{leftExpression},
      _ptrDotToken{dotToken},
      _ptrRightExpression{rightExpression}
{}

} // end namespace polyglot::CodeAnalysis
