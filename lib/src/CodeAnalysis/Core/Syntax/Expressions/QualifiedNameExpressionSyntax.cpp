#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

QualifiedNameExpressionSyntax::QualifiedNameExpressionSyntax(NameExpressionSyntaxPtr leftExpression,
                                                             SyntaxTokenPtr dotToken,
                                                             SimpleNameExpressionSyntaxPtr rightExpression) noexcept
    : NameExpressionSyntax{SyntaxKind::QualifiedNameExpression},
      _ptrLeftExpression{std::move(leftExpression)},
      _ptrDotToken{std::move(dotToken)},
      _ptrRightExpression{std::move(rightExpression)}
{}

} // end namespace polyglot::CodeAnalysis
