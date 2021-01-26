#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

ExpressionSyntax::ExpressionSyntax(SyntaxKind syntaxKind) noexcept
    : LanguageSyntaxNode{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
