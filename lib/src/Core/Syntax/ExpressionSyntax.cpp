#include "ExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

ExpressionSyntax::ExpressionSyntax(SyntaxKind syntaxKind) noexcept
    : SyntaxNode{syntaxKind}
{}

} // end namespace polyglot::Core::Syntax
