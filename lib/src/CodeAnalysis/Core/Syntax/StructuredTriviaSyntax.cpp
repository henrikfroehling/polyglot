#include "polyglot/CodeAnalysis/Core/Syntax/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

StructuredTriviaSyntax::StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : SyntaxNode{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
