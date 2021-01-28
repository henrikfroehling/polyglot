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
{
    if (_pLeadingTrivia != nullptr)
        adjustWidthAndFlags(_pLeadingTrivia);

    if (_pTrailingTrivia != nullptr)
        adjustWidthAndFlags(_pTrailingTrivia);
}

LanguageSyntaxToken::~LanguageSyntaxToken() noexcept
{}

LanguageSyntaxNode* LanguageSyntaxToken::child(pg_size index) const noexcept
{
    throw std::runtime_error{"invalid operation"};
}

TokenValue LanguageSyntaxToken::value() const noexcept
{
    switch (_syntaxKind)
    {
        case SyntaxKind::TrueKeyword:
            return true;
        case SyntaxKind::FalseKeyword:
            return false;
    }

    return TokenValue{};
}

bool LanguageSyntaxToken::booleanValue() const noexcept
{
    const TokenValue val = value();

    if (auto pValue = std::get_if<bool>(&val))
        return *pValue;

    return false;
}

} // end namespace polyglot::CodeAnalysis
