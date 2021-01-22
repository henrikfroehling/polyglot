#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

LanguageSyntaxToken::LanguageSyntaxToken() noexcept
    : LanguageSyntaxNode{},
      _text{}
{}

LanguageSyntaxToken::LanguageSyntaxToken(SyntaxKind syntaxKind,
                                         std::string_view text,
                                         pg_size position,
                                         pg_size fullWidth) noexcept
    : LanguageSyntaxNode{syntaxKind, position, text.length()},
      _text{text}
{}

LanguageSyntaxToken::~LanguageSyntaxToken() noexcept
{}

LanguageSyntaxNode* LanguageSyntaxToken::child(pg_size index) const noexcept
{
    throw std::runtime_error{"invalid operation"};
}

pg_size LanguageSyntaxToken::leadingTriviaWidth() const noexcept
{
    LanguageSyntaxNode* pLeading = leadingTrivia();
    return pLeading != nullptr ? pLeading->fullWidth() : 0;
}

pg_size LanguageSyntaxToken::trailingTriviaWidth() const noexcept
{
    LanguageSyntaxNode* pTrailing = trailingTrivia();
    return pTrailing != nullptr ? pTrailing->fullWidth() : 0;
}

} // end namespace polyglot::CodeAnalysis
