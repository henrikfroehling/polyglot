#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

StructuredTriviaSyntax::StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : SyntaxTrivia{syntaxKind}
{
    _flags |= SyntaxNodeFlags::ContainsStructuredTrivia;

    if (syntaxKind == SyntaxKind::SkippedTokensTrivia)
        _flags |= SyntaxNodeFlags::ContainsSkippedText;
}

} // end namespace polyglot::CodeAnalysis
