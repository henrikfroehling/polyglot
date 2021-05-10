#include "Core/Syntax/SyntaxMissingToken.hpp"
#include "Core/Syntax/SyntaxFlags.hpp"

namespace polyglot::Core::Syntax
{

SyntaxMissingToken::SyntaxMissingToken() noexcept
    : SyntaxToken{}
{
    _flags |= SyntaxFlags::IsMissing;
}

SyntaxMissingToken::SyntaxMissingToken(SyntaxKind syntaxKind,
                                       std::string_view text,
                                       pg_size position,
                                       pg_size fullWidth,
                                       ISyntaxTriviaList* leadingTrivia,
                                       ISyntaxTriviaList* trailingTrivia,
                                       ISyntaxNode* parent) noexcept
    : SyntaxToken{syntaxKind, text, position, fullWidth, leadingTrivia, trailingTrivia, parent}
{
    _flags |= SyntaxFlags::IsMissing;
}

} // end namespace polyglot::Core::Syntax
