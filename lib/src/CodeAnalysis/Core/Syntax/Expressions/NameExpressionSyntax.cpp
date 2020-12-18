#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

NameExpressionSyntax::NameExpressionSyntax(SyntaxKind syntaxKind) noexcept
    : TypeExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
