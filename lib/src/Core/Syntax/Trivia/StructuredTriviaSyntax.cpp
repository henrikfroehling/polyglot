#include "StructuredTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

StructuredTriviaSyntax::StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : SyntaxTrivia{syntaxKind, ""}
{}

} // end namespace polyglot::Core::Syntax
