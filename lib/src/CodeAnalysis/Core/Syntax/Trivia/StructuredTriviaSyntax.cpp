#include "CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

StructuredTriviaSyntax::StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : LanguageSyntaxTrivia{syntaxKind, ""}
{}

} // end namespace polyglot::CodeAnalysis
