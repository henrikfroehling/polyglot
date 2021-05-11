#include "Core/Syntax/SyntaxToken.hpp"
#include "Core/Syntax/SyntaxTriviaList.hpp"

namespace polyglot::Core::Syntax
{

SyntaxToken::SyntaxToken() noexcept
    : ISyntaxToken{},
      _position{},
      _fullWidth{},
      _syntaxKind{SyntaxKind::None},
      _flags{SyntaxFlags::None},
      _pParent{nullptr},
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
      _position{position},
      _fullWidth{fullWidth},
      _syntaxKind{syntaxKind},
      _flags{SyntaxFlags::None},
      _pParent{parent},
      _text{text},
      _pLeadingTrivia{leadingTrivia},
      _pTrailingTrivia{trailingTrivia}
{
    if (_pLeadingTrivia != nullptr)
        adjustWidth(_pLeadingTrivia);

    if (_pTrailingTrivia != nullptr)
        adjustWidth(_pTrailingTrivia);
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

void SyntaxToken::adjustWidth(ISyntaxTriviaList* trivia) noexcept
{
    if (trivia != nullptr)
    {
        SyntaxTriviaList* pSyntaxTriviaList = static_cast<SyntaxTriviaList*>(trivia);
        _fullWidth += pSyntaxTriviaList->width();
        pSyntaxTriviaList->_pToken = this;
    }
}

} // end namespace polyglot::Core::Syntax
