#include "CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

StructuredTriviaSyntax::StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : SyntaxTrivia{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
