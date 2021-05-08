#include "NameExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

NameExpressionSyntax::NameExpressionSyntax(SyntaxKind syntaxKind) noexcept
    : TypeExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::Core::Syntax
