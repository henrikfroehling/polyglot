#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

LanguageSyntaxToken::LanguageSyntaxToken() noexcept
    : LanguageSyntaxNode{},
      _text{},
      _pLeadingTrivia{nullptr},
      _pTrailingTrivia{nullptr}
{}

LanguageSyntaxToken::LanguageSyntaxToken(SyntaxKind syntaxKind,
                                         std::string_view text,
                                         pg_size position,
                                         pg_size fullWidth,
                                         LanguageSyntaxList* leadingTrivia,
                                         LanguageSyntaxList* trailingTrivia) noexcept
    : LanguageSyntaxNode{syntaxKind, position, fullWidth},
      _text{text},
      _pLeadingTrivia{leadingTrivia},
      _pTrailingTrivia{trailingTrivia}
{}

LanguageSyntaxToken::~LanguageSyntaxToken() noexcept
{}

LanguageSyntaxNode* LanguageSyntaxToken::child(pg_size index) const noexcept
{
    throw std::runtime_error{"invalid operation"};
}

} // end namespace polyglot::CodeAnalysis
