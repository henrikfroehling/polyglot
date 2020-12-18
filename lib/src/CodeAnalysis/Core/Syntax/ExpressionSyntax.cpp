#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

ExpressionSyntax::ExpressionSyntax(SyntaxKind syntaxKind) noexcept
    : SyntaxNode{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
