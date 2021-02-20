#include "CodeAnalysis/Core/Syntax/SyntaxMissingToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNodeFlags.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxMissingToken::SyntaxMissingToken() noexcept
    : SyntaxToken{}
{
    _flags |= SyntaxNodeFlags::IsMissing;
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
    _flags |= SyntaxNodeFlags::IsMissing;
}

SyntaxMissingToken::~SyntaxMissingToken() noexcept
{}

} // end namespace polyglot::CodeAnalysis
