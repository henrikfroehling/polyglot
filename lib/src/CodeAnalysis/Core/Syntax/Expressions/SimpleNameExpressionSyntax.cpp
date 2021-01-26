#include "CodeAnalysis/Core/Syntax/Expressions/SimpleNameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

SimpleNameExpressionSyntax::SimpleNameExpressionSyntax(SyntaxKind syntaxKind) noexcept
    : NameExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
