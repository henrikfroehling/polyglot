#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

StructuredTriviaSyntax::StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : SyntaxTrivia{syntaxKind}
{
    _flags |= _impl::SyntaxNodeFlags::ContainsStructuredTrivia;

    if (syntaxKind == SyntaxKind::SkippedTokensTrivia)
        _flags |= _impl::SyntaxNodeFlags::ContainsSkippedText;
}

} // end namespace polyglot::CodeAnalysis
