#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/TypeExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

TypeExpressionSyntax::TypeExpressionSyntax(SyntaxKind syntaxKind) noexcept
    : ExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
