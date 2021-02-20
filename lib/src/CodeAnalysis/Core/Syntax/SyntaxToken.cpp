#include "CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken() noexcept
    : ISyntaxToken{},
      SyntaxNode{},
      _text{},
      _pLeadingTrivia{nullptr},
      _pTrailingTrivia{nullptr}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text,
                         pg_size position,
                         pg_size fullWidth,
                         ISyntaxTriviaList* leadingTrivia,
                         ISyntaxTriviaList* trailingTrivia,
                         ISyntaxNode* parent) noexcept
    : ISyntaxToken{},
      SyntaxNode{syntaxKind, position, fullWidth, parent},
      _text{text},
      _pLeadingTrivia{leadingTrivia},
      _pTrailingTrivia{trailingTrivia}
{
    if (_pLeadingTrivia != nullptr)
        adjustWidthAndFlags(_pLeadingTrivia);

    if (_pTrailingTrivia != nullptr)
        adjustWidthAndFlags(_pTrailingTrivia);
}

SyntaxToken::~SyntaxToken() noexcept
{}

ISyntaxNode* SyntaxToken::child(pg_size index) const
{
    throw std::runtime_error{"invalid operation"};
}

TokenValue SyntaxToken::value() const noexcept
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

bool SyntaxToken::booleanValue() const noexcept
{
    const TokenValue val = value();

    if (auto pValue = std::get_if<bool>(&val))
        return *pValue;

    return false;
}

} // end namespace polyglot::CodeAnalysis
