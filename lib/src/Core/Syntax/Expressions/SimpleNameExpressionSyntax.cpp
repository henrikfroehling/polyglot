#include "SimpleNameExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

SimpleNameExpressionSyntax::SimpleNameExpressionSyntax(SyntaxKind syntaxKind) noexcept
    : NameExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::Core::Syntax
