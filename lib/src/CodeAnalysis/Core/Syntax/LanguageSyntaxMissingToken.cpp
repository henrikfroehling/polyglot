#include "CodeAnalysis/Core/Syntax/LanguageSyntaxMissingToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNodeFlags.hpp"

namespace polyglot::CodeAnalysis
{

LanguageSyntaxMissingToken::LanguageSyntaxMissingToken() noexcept
    : LanguageSyntaxToken{}
{
    _flags |= SyntaxNodeFlags::IsMissing;
}

LanguageSyntaxMissingToken::LanguageSyntaxMissingToken(SyntaxKind syntaxKind,
                                                       std::string_view text,
                                                       pg_size position,
                                                       pg_size fullWidth,
                                                       LanguageSyntaxList* leadingTrivia,
                                                       LanguageSyntaxList* trailingTrivia) noexcept
    : LanguageSyntaxToken{syntaxKind, text, position, fullWidth, leadingTrivia, trailingTrivia}
{
    _flags |= SyntaxNodeFlags::IsMissing;
}

LanguageSyntaxMissingToken::~LanguageSyntaxMissingToken() noexcept
{}

} // end namespace polyglot::CodeAnalysis
