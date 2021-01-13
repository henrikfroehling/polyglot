#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken() noexcept
    : _syntaxKind{SyntaxKind::None},
      _position{},
      _text{},
      _leadingTrivia{},
      _trailingTrivia{},
      _fullWidth{},
      _pParent{nullptr}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text,
                         pg_size position) noexcept
    : _syntaxKind{syntaxKind},
      _position{position},
      _text{text},
      _leadingTrivia{},
      _trailingTrivia{},
      _fullWidth{},
      _pParent{nullptr}
{
    _fullWidth = _text.length();
}

void SyntaxToken::setLeadingTrivia(std::vector<SyntaxTrivia*>&& leadingTrivia) noexcept
{
    _leadingTrivia = std::move(leadingTrivia);
}

void SyntaxToken::setTrailingTrivia(std::vector<SyntaxTrivia*>&& trailingTrivia) noexcept
{
    _trailingTrivia = std::move(trailingTrivia);
}

void SyntaxToken::addLeadingTrivia(SyntaxTrivia* leadingTrivia) noexcept
{
    assert(leadingTrivia != nullptr);
    _leadingTrivia.push_back(leadingTrivia);
}

bool SyntaxToken::value() const noexcept
{
    switch (_syntaxKind)
    {
        case SyntaxKind::TrueKeyword: return true;
        case SyntaxKind::FalseKeyword: return false;
    }

    return false;
}

} // end namespace polyglot::CodeAnalysis
