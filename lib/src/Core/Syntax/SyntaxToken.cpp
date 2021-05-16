#include "Core/Syntax/SyntaxToken.hpp"
#include <sstream>
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxTree.hpp"
#include "polyglot/Core/Text/SourceText.hpp"
#include "Core/Syntax/SyntaxTriviaList.hpp"

namespace polyglot::Core::Syntax
{

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text,
                         pg_size position,
                         pg_size fullWidth,
                         ISyntaxTriviaList* leadingTrivia,
                         ISyntaxTriviaList* trailingTrivia,
                         ISyntaxNode* parent,
                         ISyntaxTrivia* trivia) noexcept
    : ISyntaxToken{},
      _position{position},
      _fullWidth{fullWidth},
      _syntaxKind{syntaxKind},
      _flags{SyntaxFlags::None},
      _pParent{parent},
      _pTrivia{trivia},
      _text{text},
      _pLeadingTrivia{leadingTrivia},
      _pTrailingTrivia{trailingTrivia}
{
    if (_pLeadingTrivia != nullptr)
        adjustWidth(_pLeadingTrivia);

    if (_pTrailingTrivia != nullptr)
        adjustWidth(_pTrailingTrivia);
}

std::string_view SyntaxToken::textIncludingTrivia() const noexcept
{
    if (_pParent != nullptr && _pParent->syntaxTree() != nullptr)
        return _pParent->syntaxTree()->sourceText()->toString(fullSpan());

    return std::string_view{};
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
        pSyntaxTriviaList->setToken(this);
    }
}

void SyntaxToken::setTriviaParent(ISyntaxTrivia* trivia) noexcept
{
    _pParent = nullptr;
    _pTrivia = trivia;
}

std::string SyntaxToken::toString() const noexcept
{
    std::stringstream str;
    str << "Token(Position: " << _position << ", Kind: " << syntaxKindName(_syntaxKind) << ", Value: \"" << _text << "\"" << ", Width: " << width() << ")";
    return str.str();
}

} // end namespace polyglot::Core::Syntax
